/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_debug_console.h"
#include "fsl_smc.h"
#include "fsl_pmc.h"
#include "fsl_adc16.h"
#include "board.h"
#include "fsl_lptmr.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_ADC16_BASEADDR ADC0
#define DEMO_ADC16_CHANNEL_GROUP 0U

#define DEMO_ADC16_IRQ_ID ADC0_IRQn
#define DEMO_ADC16_IRQ_HANDLER_FUNC ADC0_IRQHandler

#define DEMO_LPTMR_BASE LPTMR0

/*
 * These values are used to get the temperature. DO NOT MODIFY
 * The method used in this demo to calculate temperature of chip is mapped to
 * Temperature Sensor for the HCS08 Microcontroller Family document (Document Number: AN3031)
 */
#define ADCR_VDD (65535U) /* Maximum value when use 16b resolution */
#define V_BG (1000U)      /* BANDGAP voltage in mV (trim to 1.0V) */
#define V_TEMP25 (716U)   /* Typical VTEMP25 in mV */
#define M (1620U)         /* Typical slope: (mV x 1000)/oC */
#define STANDARD_TEMP (25U)

#define LED1_INIT() LED_RED_INIT(LOGIC_LED_OFF)
#define LED1_ON() LED_RED_ON()
#define LED1_OFF() LED_RED_OFF()

#define LED2_INIT() LED_GREEN_INIT(LOGIC_LED_OFF)
#define LED2_ON() LED_GREEN_ON()
#define LED2_OFF() LED_GREEN_OFF()
#define kAdcChannelTemperature (26U) /*! ADC channel of temperature sensor */
#define kAdcChannelBandgap (27U)     /*! ADC channel of BANDGAP */

#define UPPER_VALUE_LIMIT (1U) /*! This value/10 is going to be added to current Temp to set the upper boundary*/
#define LOWER_VALUE_LIMIT                                                               \
    (1U) /*! This Value/10 is going to be subtracted from current Temp to set the lower \
            boundary*/
#define UPDATE_BOUNDARIES_TIME                                                       \
    (20U) /*! This value indicates the number of cycles needed to update boundaries. \
              To know the Time it will take, multiply this value times LPTMR_COMPARE_VALUE*/

#define LPTMR_COMPARE_VALUE (500U) /* Low Power Timer interrupt time in miliseconds */

/*!
* @brief Boundaries struct
*/
typedef struct lowPowerAdcBoundaries
{
    int32_t upperBoundary; /*! upper boundary in degree */
    int32_t lowerBoundary; /*! lower boundary in degree */
} lowPowerAdcBoundaries_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void BOARD_ConfigTriggerSource(void);
/*!
 * @brief ADC stop conversion
 *
 * @param base The ADC instance number
 */
static void ADC16_PauseConversion(ADC_Type *base);

/*!
 * @brief calibrate parameters: VDD and ADCR_TEMP25
 *
 * @param base The ADC instance number
 */
static void ADC16_CalibrateParams(ADC_Type *base);

/*!
 * @brief User-defined function to init trigger source  of LPTimer
 *
 * @param base The LPTMR instance number
 */
static void LPTMR_InitTriggerSourceOfAdc(LPTMR_Type *base);

/*!
 * @brief Initialize the ADCx for HW trigger.
 *
 * @param base The ADC instance number
 *
 * @return true if success
 */
static bool ADC16_InitHardwareTrigger(ADC_Type *base);

/*!
 * @brief Calculate current temperature.
 *
 * @return uint32_t Returns current temperature.
 */
static int32_t GetCurrentTempValue(void);

/*!
 * @brief Calculate current temperature.
 *
 * @param updateBoundariesCounter Indicate number of values into tempArray.
 *
 * @param tempArray Store temperature value.
 *
 * @return lowPowerAdcBoundaries_t Returns upper and lower temperature boundaries.
 */
static lowPowerAdcBoundaries_t TempSensorCalibration(uint32_t updateBoundariesCounter, int32_t *tempArray);

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile static uint32_t adcValue = 0; /*! ADC value */
static uint32_t adcrTemp25 = 0;        /*! Calibrated ADCR_TEMP25 */
static uint32_t adcr100m = 0;
volatile bool conversionCompleted = false; /*! Conversion is completed Flag */

/*******************************************************************************
 * Code
 ******************************************************************************/

void BOARD_ConfigTriggerSource(void)
{
    /* Configure SIM for ADC hw trigger source selection */
    SIM->SOPT7 |= 0x0000008EU;
}
/* Enable the trigger source of LPTimer */
static void LPTMR_InitTriggerSourceOfAdc(LPTMR_Type *base)
{
    lptmr_config_t lptmrUserConfig;

    /*
     * lptmrUserConfig.timerMode = kLPTMR_TimerModeTimeCounter;
     * lptmrUserConfig.pinSelect = kLPTMR_PinSelectInput_0;
     * lptmrUserConfig.pinPolarity = kLPTMR_PinPolarityActiveHigh;
     * lptmrUserConfig.enableFreeRunning = false;
     * lptmrUserConfig.bypassPrescaler = true;
     * lptmrUserConfig.prescalerClockSource = kLPTMR_PrescalerClock_1;
     * lptmrUserConfig.value = kLPTMR_Prescale_Glitch_0;
     */
    LPTMR_GetDefaultConfig(&lptmrUserConfig);
    /* Init LPTimer driver */
    LPTMR_Init(base, &lptmrUserConfig);

    /* Set the LPTimer period */
    LPTMR_SetTimerPeriod(base, LPTMR_COMPARE_VALUE);

    /* Start the LPTimer */
    LPTMR_StartTimer(base);

    /* Configure SIM for ADC hw trigger source selection */
    BOARD_ConfigTriggerSource();
}

/*!
 * @brief ADC stop conversion
 */
static void ADC16_PauseConversion(ADC_Type *base)
{
    adc16_channel_config_t adcChnConfig;

    adcChnConfig.channelNumber = 31U; /*!< AD31 channel */
    adcChnConfig.enableInterruptOnConversionCompleted = false;
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adcChnConfig.enableDifferentialConversion = false;
#endif
    ADC16_SetChannelConfig(base, DEMO_ADC16_CHANNEL_GROUP, &adcChnConfig);
}

/*!
 * @brief calibrate parameters: VDD and ADCR_TEMP25
 */
static void ADC16_CalibrateParams(ADC_Type *base)
{
    uint32_t bandgapValue = 0; /*! ADC value of BANDGAP */
    uint32_t vdd = 0;          /*! VDD in mV */

    adc16_config_t adcUserConfig;
    adc16_channel_config_t adcChnConfig;
    pmc_bandgap_buffer_config_t pmcBandgapConfig;

    pmcBandgapConfig.enable = true;

#if (defined(FSL_FEATURE_PMC_HAS_BGEN) && FSL_FEATURE_PMC_HAS_BGEN)
    pmcBandgapConfig.enableInLowPowerMode = false;
#endif
#if (defined(FSL_FEATURE_PMC_HAS_BGBDS) && FSL_FEATURE_PMC_HAS_BGBDS)
    pmcBandgapConfig.drive = kPmcBandgapBufferDriveLow;
#endif
    /* Enable BANDGAP reference voltage */
    PMC_ConfigureBandgapBuffer(PMC, &pmcBandgapConfig);

    /*
    * Initialization ADC for
    * 16bit resolution, interrupt mode, hw trigger disabled.
    * normal convert speed, VREFH/L as reference,
    * disable continuous convert mode
    */
    /*
     * adcUserConfig.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
     * adcUserConfig.clockSource = kADC16_ClockSourceAsynchronousClock;
     * adcUserConfig.enableAsynchronousClock = true;
     * adcUserConfig.clockDivider = kADC16_ClockDivider8;
     * adcUserConfig.resolution = kADC16_ResolutionSE12Bit;
     * adcUserConfig.longSampleMode = kADC16_LongSampleDisabled;
     * adcUserConfig.enableHighSpeed = false;
     * adcUserConfig.enableLowPower = false;
     * adcUserConfig.enableContinuousConversion = false;
     */
    ADC16_GetDefaultConfig(&adcUserConfig);
#if defined(FSL_FEATURE_ADC16_MAX_RESOLUTION) && (FSL_FEATURE_ADC16_MAX_RESOLUTION >= 16U)
    adcUserConfig.resolution = kADC16_Resolution16Bit;
#else
    adcUserConfig.resolution = kADC16_ResolutionSE12Bit;
#endif
    adcUserConfig.enableContinuousConversion = false;
    adcUserConfig.clockSource = kADC16_ClockSourceAsynchronousClock;
    adcUserConfig.enableLowPower = 1;
    adcUserConfig.longSampleMode = kADC16_LongSampleCycle24;
#ifdef BOARD_ADC_USE_ALT_VREF
    adcUserConfig.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
#endif
    ADC16_Init(base, &adcUserConfig);

#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    /* Auto calibration */
    ADC16_DoAutoCalibration(base);
#endif

#if defined(FSL_FEATURE_ADC16_HAS_HW_AVERAGE) && FSL_FEATURE_ADC16_HAS_HW_AVERAGE
    /* Use hardware average to increase stability of the measurement  */
    ADC16_SetHardwareAverage(base, kADC16_HardwareAverageCount32);
#endif /* FSL_FEATURE_ADC16_HAS_HW_AVERAGE */

    adcChnConfig.channelNumber = kAdcChannelBandgap;
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adcChnConfig.enableDifferentialConversion = false;
#endif
    adcChnConfig.enableInterruptOnConversionCompleted = false;
    ADC16_SetChannelConfig(base, DEMO_ADC16_CHANNEL_GROUP, &adcChnConfig);

    /* Wait for the conversion to be done */
    while (!ADC16_GetChannelStatusFlags(base, DEMO_ADC16_CHANNEL_GROUP))
    {
    }

    /* Get current ADC BANDGAP value */
    bandgapValue = ADC16_GetChannelConversionValue(base, DEMO_ADC16_CHANNEL_GROUP);

    ADC16_PauseConversion(base);

    /* Get VDD value measured in mV: VDD = (ADCR_VDD x V_BG) / ADCR_BG */
    vdd = ADCR_VDD * V_BG / bandgapValue;
    /* Calibrate ADCR_TEMP25: ADCR_TEMP25 = ADCR_VDD x V_TEMP25 / VDD */
    adcrTemp25 = ADCR_VDD * V_TEMP25 / vdd;
    /* ADCR_100M = ADCR_VDD x M x 100 / VDD */
    adcr100m = (ADCR_VDD * M) / (vdd * 10);

    /* Disable BANDGAP reference voltage */
    pmcBandgapConfig.enable = false;
    PMC_ConfigureBandgapBuffer(PMC, &pmcBandgapConfig);
}

/*!
 * @brief Initialize the ADCx for Hardware trigger.
 */
static bool ADC16_InitHardwareTrigger(ADC_Type *base)
{
#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    uint16_t offsetValue = 0; /*!< Offset error from correction value. */
#endif
    adc16_config_t adcUserConfig;
    adc16_channel_config_t adcChnConfig;

#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    /* Auto calibration */
    ADC16_DoAutoCalibration(base);
    offsetValue = base->OFS;
    ADC16_SetOffsetValue(base, offsetValue);
#endif
    /*
    * Initialization ADC for
    * 16bit resolution, interrupt mode, hw trigger enabled.
    * normal convert speed, VREFH/L as reference,
    * disable continuous convert mode.
    */
    /*
     * adcUserConfig.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
     * adcUserConfig.clockSource = kADC16_ClockSourceAsynchronousClock;
     * adcUserConfig.enableAsynchronousClock = true;
     * adcUserConfig.clockDivider = kADC16_ClockDivider8;
     * adcUserConfig.resolution = kADC16_ResolutionSE12Bit;
     * adcUserConfig.longSampleMode = kADC16_LongSampleDisabled;
     * adcUserConfig.enableHighSpeed = false;
     * adcUserConfig.enableLowPower = false;
     * adcUserConfig.enableContinuousConversion = false;
     */
    ADC16_GetDefaultConfig(&adcUserConfig);
#if defined(FSL_FEATURE_ADC16_MAX_RESOLUTION) && (FSL_FEATURE_ADC16_MAX_RESOLUTION >= 16U)
    adcUserConfig.resolution = kADC16_Resolution16Bit;
#else
    adcUserConfig.resolution = kADC16_ResolutionSE12Bit;
#endif
    /* enabled hardware trigger  */
    ADC16_EnableHardwareTrigger(base, true);
    adcUserConfig.enableContinuousConversion = false;
    adcUserConfig.clockSource = kADC16_ClockSourceAsynchronousClock;

    adcUserConfig.longSampleMode = kADC16_LongSampleCycle24;
    adcUserConfig.enableLowPower = 1;
#if ((defined BOARD_ADC_USE_ALT_VREF) && BOARD_ADC_USE_ALT_VREF)
    adcUserConfig.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
#endif
    ADC16_Init(base, &adcUserConfig);

    adcChnConfig.channelNumber = kAdcChannelTemperature;
#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adcChnConfig.enableDifferentialConversion = false;
#endif
    adcChnConfig.enableInterruptOnConversionCompleted = true;
    /* Configure channel 0 */
    ADC16_SetChannelConfig(base, DEMO_ADC16_CHANNEL_GROUP, &adcChnConfig);
    return true;
}

static int32_t GetCurrentTempValue(void)
{
    int32_t currentTemperature = 0;
    /* Temperature = 25 - (ADCR_T - ADCR_TEMP25) * 100 / ADCR_100M */
    currentTemperature = (int32_t)(STANDARD_TEMP - ((int32_t)adcValue - (int32_t)adcrTemp25) * 100 / (int32_t)adcr100m);
    return currentTemperature;
}

static lowPowerAdcBoundaries_t TempSensorCalibration(uint32_t updateBoundariesCounter, int32_t *tempArray)
{
    uint32_t avgTemp = 0;
    lowPowerAdcBoundaries_t boundaries;

    for (int i = 0; i < updateBoundariesCounter; i++)
    {
        avgTemp += tempArray[i];
    }
    /* Get average temperature */
    avgTemp /= updateBoundariesCounter;

    /* Set upper boundary */
    boundaries.upperBoundary = avgTemp + UPPER_VALUE_LIMIT;

    /* Set lower boundary */
    boundaries.lowerBoundary = avgTemp - LOWER_VALUE_LIMIT;

    return boundaries;
}

/*!
 * @brief ADC Interrupt handler
 *
 * Get current ADC value and set conversionCompleted flag.
 */
void DEMO_ADC16_IRQ_HANDLER_FUNC(void)
{
    /* Get current ADC value */
    adcValue = ADC16_GetChannelConversionValue(DEMO_ADC16_BASEADDR, DEMO_ADC16_CHANNEL_GROUP);
    /* Set conversionCompleted flag. This prevents an wrong conversion in main function */
    conversionCompleted = true;
}

/*!
 * @brief main function
 */
int main(void)
{
    int32_t currentTemperature = 0;
    uint32_t updateBoundariesCounter = 0;
    int32_t tempArray[UPDATE_BOUNDARIES_TIME * 2];
    lowPowerAdcBoundaries_t boundaries;

    /* Init hardware */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    /* Init using Led in Demo app */
    LED1_INIT();
    LED2_INIT();

    /* Set to allow entering vlps mode */
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeVlp);

    /* Calibrate param Temperature sensor */
    ADC16_CalibrateParams(DEMO_ADC16_BASEADDR);

    /* Initialize Demo ADC */
    if (!ADC16_InitHardwareTrigger(DEMO_ADC16_BASEADDR))
    {
        PRINTF("Failed to do the ADC init\r\n");
        return -1;
    }

    PRINTF("\n\r ADC LOW POWER DEMO\n");
    PRINTF("\r The Low Power ADC project is designed to work with the Tower System or in a stand alone setting\n\n");
    PRINTF("\r 1. Set your target board in a place where the temperature is constant.\n");
    PRINTF("\r 2. Wait until two Led light turns on.\n");
    PRINTF("\r 3. Increment or decrement the temperature to see the changes.\n");
    PRINTF("\r Wait two led on...\n\r");

    /* setup the HW trigger source */
    LPTMR_InitTriggerSourceOfAdc(DEMO_LPTMR_BASE);
#if defined(FSL_FEATURE_ADC16_MAX_RESOLUTION) && (FSL_FEATURE_ADC16_MAX_RESOLUTION >= 16U)
    ADC16_EnableDMA(DEMO_ADC16_BASEADDR, false);
#endif
    NVIC_EnableIRQ(DEMO_ADC16_IRQ_ID);
    /* Warm up microcontroller and allow to set first boundaries */
    while (updateBoundariesCounter < (UPDATE_BOUNDARIES_TIME * 2))
    {
        while (!conversionCompleted)
        {
        }
        currentTemperature = GetCurrentTempValue();
        tempArray[updateBoundariesCounter] = currentTemperature;
        updateBoundariesCounter++;
        conversionCompleted = false;
    }

    /* Temp Sensor Calibration */
    boundaries = TempSensorCalibration(updateBoundariesCounter, tempArray);
    updateBoundariesCounter = 0;

    /* Two LED is turned on indicating calibration is done */
    LED1_ON();
    LED2_ON();

    /* Wait for user input before beginning demo */
    PRINTF("\r Enter any character to begin...\n");
    GETCHAR();
    PRINTF("\r ---> OK! Main process is running...!\n");

    while (1)
    {
        /* Prevents the use of wrong values */
        while (!conversionCompleted)
        {
        }

        /* Get current Temperature Value */
        currentTemperature = GetCurrentTempValue();
        /* Store temperature values that are going to be use to calculate average temperature */
        tempArray[updateBoundariesCounter] = currentTemperature;

        if (currentTemperature > boundaries.upperBoundary)
        {
            LED2_OFF();
            LED1_ON();
        }
        else if (currentTemperature < boundaries.lowerBoundary)
        {
            LED2_ON();
            LED1_OFF();
        }
        else
        {
            LED2_ON();
            LED1_ON();
        }

        /* Call update function */
        if (updateBoundariesCounter >= (UPDATE_BOUNDARIES_TIME))
        {
            boundaries = TempSensorCalibration(updateBoundariesCounter, tempArray);
            updateBoundariesCounter = 0;
        }
        else
        {
            updateBoundariesCounter++;
        }

        /* Clear conversionCompleted flag */
        conversionCompleted = false;

        /* Enter to Very Low Power Stop Mode */
        SMC_SetPowerModeVlps(SMC);
    }
}
