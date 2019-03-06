/***************************************************************************//**
 * @file util_supply.c
 * @brief Power Supply Related Utility Functions for the Thunderboard Sense
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

#include <stdio.h>

#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_emu.h"
#include "em_adc.h"
#include "em_cmu.h"
#include "em_prs.h"

#include "thunderboard/board.h"
#include "thunderboard/util.h"
#include "thunderboard/si7021.h"

/***************************************************************************//**
 * @addtogroup Util
 * @{
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @addtogroup Util_Locals
 * @{
 ******************************************************************************/
static float   measureSupplyVoltage      ( unsigned int avg );
static float   measureSupplyIR           ( uint8_t loadSetting );

float UTIL_supplyVoltage;  /**< Loaded supply voltage                */
float UTIL_supplyIR;       /**< Internal resistance of the supply    */
uint8_t UTIL_supplyType;   /**< Type of the connected supply         */

/** @} {end addtogroup Util_Locals} */

/** @endcond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @addtogroup Util_Functions
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *    Initializes the A/D converter
 *
 * @return
 *    None
 ******************************************************************************/
static void adcInit( void )
{

   ADC_Init_TypeDef init = ADC_INIT_DEFAULT;
   ADC_InitSingle_TypeDef initSingle = ADC_INITSINGLE_DEFAULT;

   CMU_ClockEnable( cmuClock_ADC0, true );
   CMU_ClockEnable( cmuClock_PRS, true );

   /* Only configure the ADC if it is not already running */
   if( ADC0 ->CTRL == _ADC_CTRL_RESETVALUE ) {

      init.timebase = ADC_TimebaseCalc( 0 );
      init.prescale = ADC_PrescaleCalc( 1000000, 0 );
      ADC_Init( ADC0, &init );
   }

   initSingle.acqTime = adcAcqTime16;
   initSingle.reference = adcRef5VDIFF;
   initSingle.posSel = adcPosSelAVDD;
   initSingle.negSel = adcNegSelVSS;
   initSingle.prsEnable = true;
   initSingle.prsSel = adcPRSSELCh4;

   ADC_InitSingle( ADC0, &initSingle );

   return;

}

/***************************************************************************//**
 * @brief
 *    De-initializes the A/D converter
 *
 * @return
 *    None
 ******************************************************************************/
static void adcDeInit( void )
{

   PRS_SourceAsyncSignalSet( 4, 0, 0 );
   CMU->CTRL &= ~_CMU_CTRL_CLKOUTSEL1_MASK;

   return;

}

/***************************************************************************//**
 * @brief
 *    Initiates an A/D conversion and reads the sample when done
 *
 * @return
 *    The output of the A/D conversion
 ******************************************************************************/
static uint16_t getAdcSample( void )
{

   ADC_Start( ADC0, adcStartSingle );
   while( !( ADC_IntGet( ADC0 ) & ADC_IF_SINGLE ) )
      ;

   return ADC_DataSingleGet( ADC0 );

}

/***************************************************************************//**
 * @brief
 *    Measures the supply voltage by averaging multiple readings
 *
 * @param[in] avg
 *    Number of measurements to average
 *
 * @return
 *    The measured voltage
 ******************************************************************************/
static float measureSupplyVoltage( unsigned int avg )
{

   uint16_t adcData;
   float supplyVoltage;
   int i;

   adcInit();

   supplyVoltage = 0;

   for( i = 0; i < avg; i++ ) {
      adcData = getAdcSample();
      supplyVoltage += (float) adcData * 5.0 / 4095.0;
   }

   adcDeInit();

   supplyVoltage = supplyVoltage / (float) avg;

   return supplyVoltage;

}

/***************************************************************************//**
 * @brief
 *    Measures the unladed and loaded supply voltage and calculates the intermal
 *    resistance of the connected supply. The load is provided by the heater
 *    element built in the Si7021.
 *
 * @param[in] loadSetting
 *    Heater current setting of the Si7021
 *
 * @return
 *    The measured internal resistance of the connected supply
 ******************************************************************************/
static float measureSupplyIR( uint8_t loadSetting )
{

   float supplyVoltage;
   float supplyVoltageLoad;
   float i, r;

   uint8_t cmd;
   uint8_t data;

   UTIL_delay( 250 );
   supplyVoltage = measureSupplyVoltage( 16 );

   /* Enable heater in Si7021 - 9.81 mA */
   cmd = SI7021_CMD_WRITE_HEATER_CTRL;
   data = loadSetting;
   SI7021_cmdWrite( &cmd, 1, &data, 1 );

   cmd = SI7021_CMD_WRITE_USER_REG1;
   data = 0x04;
   SI7021_cmdWrite( &cmd, 1, &data, 1 );

   /* Wait for battery voltage to settle */
   UTIL_delay( 250 );
   supplyVoltageLoad = measureSupplyVoltage( 16 );

   /* Turn off heater */
   cmd = SI7021_CMD_WRITE_USER_REG1;
   data = 0x00;
   SI7021_cmdWrite( &cmd, 1, &data, 1 );

   i = 0.006074 * loadSetting + 0.00309;
   r = ( supplyVoltage - supplyVoltageLoad ) / i;

   printf( " sv = %.3f  svl = %.3f   i = %.3f   r = %.3f\r\n",
         supplyVoltage, supplyVoltageLoad, i, r );

   return r;

}

/***************************************************************************//**
 * @brief
 *    Probes the connected supply and determines its type. The results are
 *    stored in global variables.
 *
 * @return
 *    None
 ******************************************************************************/
void UTIL_supplyProbe( void )
{

   SI7021_init();

   uint8_t type;
   float r, v;

   type = UTIL_SUPPLY_TYPE_UNKNOWN;

   /* Try to measure using 9.18 mA first */
   v = measureSupplyVoltage( 16 );
   r = measureSupplyIR( 0x00 );
   if( r > 5.0 ) {
      type = UTIL_SUPPLY_TYPE_CR2032;
   }
   else if( ( v < 3.20 ) || ( r > 0.5 ) ) {
      type = UTIL_SUPPLY_TYPE_AAA;
   }
   else {
      type = UTIL_SUPPLY_TYPE_USB;
   }

   UTIL_supplyVoltage = v;
   UTIL_supplyIR = r;
   UTIL_supplyType = type;

   SI7021_deInit();

   return;

}

/***************************************************************************//**
 * @brief
 *    Retrieves the supply characteristic variables
 *
 * @param[in] type
 *    Supply type
 *
 * @param[in] voltage
 *    Loaded supply voltage
 *
 * @param[in] ir
 *    Internal resistance of the supply
 *
 * @return
 *    None
 ******************************************************************************/
void UTIL_supplyGetCharacteristics( uint8_t *type, float *voltage, float *ir )
{

   *type    = UTIL_supplyType;
   *voltage = UTIL_supplyVoltage;
   *ir      = UTIL_supplyIR;

   return;

}

/***************************************************************************//**
 * @brief
 *    Returns the type of the power supply
 *
 * @return
 *    The type of the supply
 ******************************************************************************/
uint8_t UTIL_supplyGetType( void )
{

   return UTIL_supplyType;

}

/***************************************************************************//**
 * @brief
 *    Checks if the current power supply has low power capability
 *
 * @return
 *    True if the supply is low power type, false otherwise
 ******************************************************************************/
bool UTIL_isLowPower( void )
{

   bool lp;

   if( ( UTIL_supplyType != UTIL_SUPPLY_TYPE_CR2032 ) && ( UTIL_supplyType != UTIL_SUPPLY_TYPE_UNKNOWN ) ) {
      lp = false;
   }
   else {
      lp = true;
   }

   return lp;

}

/** @} {end addtogroup Util_Functions} */

/** @} {end addtogroup Util} */
