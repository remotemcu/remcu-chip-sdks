/***************************************************************************//**
 * @file mic.c
 * @brief Driver for the SPV1840LR5H-B MEMS Microphone
 * @version 5.1.1
 *******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include "em_device.h"
#include "em_adc.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_prs.h"
#include "em_letimer.h"
#include "dmadrv.h"

#include "thunderboard/util.h"
#include "thunderboard/board.h"
#include "thunderboard/mic.h"

#include <math.h>

/***************************************************************************//**
 * @defgroup Mic MIC - Microphone Driver
 * @{
 * @brief Driver for the Knowles SPV1840LR5H-B MEMS Microphone
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @defgroup Mic_Locals MEMS Microphone Local Variables
 * @{
 * @brief MEMS microphone local variables
 ******************************************************************************/

static unsigned int  dmadrvChannelId;      /**< The channel Id assigned by DMADRV                         */
static uint16_t     *sampleBuffer;         /**< Buffer used to store the microphone samples               */
static size_t        sampleBufferLen;      /**< The length of the sample buffer                           */
static volatile bool sampleBufferReady;    /**< Flag to show that the buffer is filled with new samples   */
static uint32_t      sampleCount;          /**< The number of collected samples                           */

static volatile bool dmaBusy;              /**< Flag to show if DMA operation is in progress              */
static float         soundLevel;           /**< The measured sound level in dB                            */
static uint32_t      cmuClkoutSel1;        /**< Variable to store the current clock output mode           */

/** @} {end defgroup Mic_Locals} */

/** @endcond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @defgroup Mic_Functions MEMS Microphone Functions
 * @{
 * @brief MEMS microphone driver and support functions
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

static bool dmaCompleteCallback( unsigned int channel, unsigned int sequenceNo, void *userParam );
static void adcEnable( bool enable );

/** @endcond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @brief
 *    Initializes MEMS microphone and sets up the DMA, ADC and clocking
 *
 * @param[in] fs
 *    The desired sample rate in Hz
 *
 * @param[in] buffer
 *    Pointer to the sample buffer to store the ADC data
 *
 * @param[in] len
 *    The size of the sample buffer
 *
 * @return
 *    Returns zero on OK, non-zero otherwise
 ******************************************************************************/
uint32_t MIC_init( uint32_t fs, uint16_t *buffer, size_t len )
{

   uint32_t status;
   uint32_t auxhfrcoFreq;

   ADC_Init_TypeDef adcInit = ADC_INIT_DEFAULT;
   ADC_InitScan_TypeDef adcInitScan = ADC_INITSCAN_DEFAULT;

   CMU_ClockEnable( cmuClock_ADC0, true );
   CMU_ClockEnable( cmuClock_PRS, true );
   CMU ->ADCCTRL = CMU_ADCCTRL_ADC0CLKSEL_AUXHFRCO;

   auxhfrcoFreq = CMU_ClockFreqGet( cmuClock_AUX );

   /* Enable microphone circuit and wait for it to settle properly */
   BOARD_micEnable( true );

   /* Setup ADC */
   adcInit.em2ClockConfig = adcEm2ClockOnDemand;
   adcInit.timebase = ADC_TimebaseCalc( auxhfrcoFreq );
   adcInit.prescale = ADC_PrescaleCalc( MIC_ADC_CLOCK_FREQ, auxhfrcoFreq );
   ADC_Init( ADC0, &adcInit );

   /* Setup ADC channel */
   adcInitScan.reference = adcRef2V5;
   adcInitScan.prsEnable = true;
   adcInitScan.prsSel = MIC_CONFIG_ADC_PRSSEL;
   adcInitScan.scanDmaEm2Wu = true;

   /* Add microphone scan channel */
   ADC_ScanInputClear( &adcInitScan );
   ADC_ScanSingleEndedInputAdd( &adcInitScan, adcScanInputGroup0, MIC_CONFIG_ADC_POSSEL );

   ADC_InitScan( ADC0, &adcInitScan );

   /* Setup PRS channel to trigger ADC */
   PRS_SourceAsyncSignalSet( MIC_CONFIG_PRS_CH, MIC_CONFIG_PRS_SOURCE, MIC_CONFIG_PRS_SIGNAL );

#if MIC_CONFIG_USE_LETIMER

   /* Setup LETIMER to trigger ADC in EM2 */
   LETIMER_Init_TypeDef letimerInit = LETIMER_INIT_DEFAULT;
   uint16_t timerTop;
   uint32_t timerFreq;

   CMU_ClockSelectSet( cmuClock_LFA, cmuSelect_LFXO );
   CMU_ClockEnable( MIC_CONFIG_TIMER_CMU_CLK, true );
   timerFreq = CMU_ClockFreqGet( MIC_CONFIG_TIMER_CMU_CLK );

   letimerInit.comp0Top = true;
   letimerInit.enable = false;
   letimerInit.ufoa0 = letimerUFOAPulse;

   LETIMER_Init( MIC_CONFIG_TIMER, &letimerInit );
   LETIMER_RepeatSet( MIC_CONFIG_TIMER, 0, 1 );

   timerTop = timerFreq / fs - 1;
   fs = timerFreq / (timerTop + 1);
   LETIMER_CompareSet( MIC_CONFIG_TIMER, 0, timerTop );

#else

   if( fs == 1000 ) {
      /* Use ULFRCO which runs at 1 kHz */
      cmuClkoutSel1 = CMU_CTRL_CLKOUTSEL1_ULFRCOQ;
   }
   else {
      /* Use LFXO clock which runs at 32.768 kHz */
      cmuClkoutSel1 = CMU_CTRL_CLKOUTSEL1_LFXOQ;
      fs = 32768;
   }

#endif

   /* Setup DMA driver to move samples from ADC to memory */
   DMADRV_Init();
   status = DMADRV_AllocateChannel( &dmadrvChannelId, NULL );
   if( status != ECODE_EMDRV_DMADRV_OK ) {
      return status;
   }

   soundLevel = 35.0;
   sampleBufferReady = false;
   sampleBuffer = buffer;
   sampleBufferLen = len;
   dmaBusy = false;

   return fs;

}

/***************************************************************************//**
 * @brief
 *    Powers down the MEMS microphone stops the ADC and frees up the DMA channel
 *
 * @return
 *    None
 ******************************************************************************/
void MIC_deInit( void )
{

   /* Stop sampling */
   adcEnable( false );

   /* Clear PRS channel configuration */
   PRS_SourceAsyncSignalSet( MIC_CONFIG_PRS_CH, 0, 0 );

   /* Power down microphone */
   BOARD_micEnable( false );

   DMADRV_FreeChannel( dmadrvChannelId );

   return;

}

/***************************************************************************//**
 * @brief
 *    Starts taking samples using DMA from the microphone
 *
 * @param[in] nSamples
 *    The number of the samples to take
 *
 * @return
 *    None
 ******************************************************************************/
void MIC_start( uint32_t nSamples )
{

   if( nSamples > sampleBufferLen ) {
      sampleCount = sampleBufferLen;
   }
   else {
      sampleCount = nSamples;
   }

   if( !dmaBusy ) {

      /* Configure DMA */
      DMADRV_PeripheralMemory( dmadrvChannelId,                   // channelId
                               dmadrvPeripheralSignal_ADC0_SCAN,  // peripheralSignal
                               (void *) sampleBuffer,             // *dst
                               (void *) &( ADC0 ->SCANDATA ),     // *src
                               true,                              // dstInc
                               sampleCount,                       // len
                               dmadrvDataSize2,                   // size
                               dmaCompleteCallback,               // callback
                               NULL );                            // *cbUserParam

      adcEnable( true );
      dmaBusy = true;
      sampleBufferReady = false;
   }

   return;

}

/***************************************************************************//**
 * @brief
 *    Gets the sample buffer
 *
 * @return
 *    Returns a pointer to the sample buffer
 ******************************************************************************/
uint16_t *MIC_getSampleBuffer( void )
{

   return sampleBuffer;

}

/***************************************************************************//**
 * @brief
 *    Calculates the average value of the samples in the buffer
 *
 * @return
 *    The mean value of the samples in the buffer
 ******************************************************************************/
float MIC_getMean( void )
{

   size_t i;
   float mean;

   mean = 0.0f;

   for( i = 0; i < sampleCount; i++ ) {
      mean += (float) sampleBuffer[i];
   }
   mean = mean / (float) sampleCount;

   return mean;

}

/***************************************************************************//**
 * @brief
 *    Calculates the sound level
 *
 * @param[out] var
 *    The variance of the samples
 *
 * @return
 *    The sound level in dB
 ******************************************************************************/
float MIC_getSoundLevel( float *var )
{

   float sample;
   float mean;
   float power;
   size_t i;

   if( sampleBufferReady ) {

      /* Estimate mean */
      mean = MIC_getMean();

      /* Estimate variance */
      power = 0;
      for( i = 0; i < sampleCount; i++ ) {
         sample = ( (float) sampleBuffer[i] - mean ) / 2047.5;
         power += sample * sample;
      }
      power = power / (float) sampleCount;

      /* Convert to decibel*/
      soundLevel = 10.0f * log10f( power );
      //soundLevel = soundLevel + 97.94f;
      sampleBufferReady = false;
   }

   if( var != NULL ) {
      *var = power;
   }

   return soundLevel;

}

/***************************************************************************//**
 * @brief
 *    Checks if the microphone is in use
 *
 * @return
 *    Returns true if the DMA is busy taking microphone samples
 ******************************************************************************/
bool MIC_isBusy( void )
{

   return dmaBusy;

}

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @brief
 *    Called when the DMA complete interrupt fired
 *
 * @param[in] channel
 *    DMA channel
 *
 * @param[in] sequenceNo
 *    Sequence number
 *
 * @param[in] userParam
 *    User parameters
 *
 * @return
 *    Returns false to stop transfers
 ******************************************************************************/
static bool dmaCompleteCallback( unsigned int channel, unsigned int sequenceNo, void *userParam )
{

   /* Stop ADC samples */
   adcEnable( false );

   sampleBufferReady = true;
   dmaBusy = false;

   return false;

}

/***************************************************************************//**
 * @brief
 *    Enables the ADC by enabling its clock
 *
 * @param[in] enable
 *    If true enables the ADC, if false disables.
 *
 * @return
 *    None
 ******************************************************************************/
static void adcEnable( bool enable )
{

#if MIC_CONFIG_USE_LETIMER
   /* Enable LETIMER to trigger ADC */
   LETIMER_Enable( MIC_CONFIG_TIMER, enable );
#else
   if( enable ) {
      /* Set up CLKOUT1 to start sampling */
      CMU->CTRL |=  cmuClkoutSel1;
   }
   else {
      CMU->CTRL &= ~cmuClkoutSel1;
   }
#endif

   return;

}

/** @endcond DO_NOT_INCLUDE_WITH_DOXYGEN */

/** @} {end defgroup Mic_Functions} */

/** @} {end defgroup Mic} */
