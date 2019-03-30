/*
* Copyright (C) 2014 Infineon Technologies AG. All rights reserved.
*
* Infineon Technologies AG (Infineon) is supplying this software for use with
* Infineon's microcontrollers.
* This file can be freely distributed within development tools that are
* supporting such microcontrollers.
*
* THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
* INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
* OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*
*/

/**
 * @file
 * @date 18 Feb, 2015
 * @version 1.0.0
 *
 * @brief USB demo example
 *
 * The example implements a communication through WINUSB with a Host (Computer).
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */
/*********************************************************************************************************************
 * HEADER FILES
 ********************************************************************************************************************/
#include "WinUSB.h"
/*********************************************************************************************************************
 * MACROS
 ********************************************************************************************************************/
/* Pin P14.1 is measured and converted */
#define CHANNEL_NUMBER    (1U)
#define VADC_GROUP_PTR    (VADC_G0)

/* Register result */
#define RES_REG_NUMBER    (0)

/* IO expander address on HMI board */
#define HMI_PCA9502_ADDRESS (0x9A)

#define IO_EXPANDER_ADDRESS HMI_PCA9502_ADDRESS

/* PCA9502 register address */
typedef enum PCA9502_REGADDR {
    IO_DIR    = 0xA << 3,
    IO_STATE  = 0xB << 3,
    IO_INTE   = 0xC << 3,
    IO_CTRL   = 0xE << 3
} PCA9502_REGADDR_t;

#define SDA_PIN P2_14
#define SCL_PIN P5_8

/*********************************************************************************************************************
 * GLOBAL DATA
 ********************************************************************************************************************/

/* Clock configuration */
/* fPLL = 120MHz */
/* fSYS = 120MHz */
/* fUSBPLL = 192MHz */
/* fUSB = 48MHz */
const XMC_SCU_CLOCK_CONFIG_t clock_config =
{
 .syspll_config.p_div = 2,
 .syspll_config.n_div = 80,
 .syspll_config.k_div = 4,
 .syspll_config.mode = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
 .syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
 .enable_oschp = true,
 .calibration_mode = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
 .fsys_clksrc = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
 .fsys_clkdiv = 1,
 .fcpu_clkdiv = 1,
 .fccu_clkdiv = 1,
 .fperipheral_clkdiv = 1
};


void SystemCoreClockSetup(void)
{
 /* Setup settings for USB clock */
 XMC_SCU_CLOCK_Init(&clock_config);

 XMC_SCU_CLOCK_EnableUsbPll();
 XMC_SCU_CLOCK_StartUsbPll(2, 64);
 XMC_SCU_CLOCK_SetUsbClockDivider(4);
 XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
 XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);

 SystemCoreClockUpdate();
}

/* VADC configuration */


/* Initialization data of VADC Global resources */
XMC_VADC_GLOBAL_CONFIG_t g_global_config =
{
  .clock_config =
  {
    .analog_clock_divider  = 3,
    .msb_conversion_clock  = 0,
    .arbiter_clock_divider = 1
  },
};

/* Initialization data of a VADC group */
XMC_VADC_GROUP_CONFIG_t g_group_config =
{
  .class1 =
  {
    .conversion_mode_standard 	 =  XMC_VADC_CONVMODE_12BIT,
    .sample_time_std_conv 	     = 3U,
  }
};

XMC_VADC_QUEUE_CONFIG_t g_queue_config;

/* Channel configuration data */
XMC_VADC_CHANNEL_CONFIG_t  g_channel_config =
{
  .input_class       = XMC_VADC_CHANNEL_CONV_GROUP_CLASS1,
  .result_reg_number = RES_REG_NUMBER,
  .alias_channel     = -1
};

/* Result configuration data */
XMC_VADC_RESULT_CONFIG_t g_result_config =
{
  .wait_for_read_mode = true
};

/* Queue Entry */
XMC_VADC_QUEUE_ENTRY_t g_queue_entry =
{
  .channel_num = CHANNEL_NUMBER,
  .refill_needed = true, /* Refill is needed */
  .generate_interrupt = false, /* Interrupt generation is needed */
  .external_trigger = false  /* External trigger is required */
};


/* I2C configuration */

XMC_I2C_CH_CONFIG_t i2c_cfg =
{
  .baudrate = 100000U,
};

/*********************************************************************************************************************
 * MAIN APPLICATION
 ********************************************************************************************************************/
void LED_SetIODir(uint8_t dir)
{

  /* Start I2C transaction */
  XMC_I2C_CH_MasterStart(XMC_I2C1_CH0, IO_EXPANDER_ADDRESS, XMC_I2C_CH_CMD_WRITE);
  while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
  {
	/* wait for ACK */
  }
  XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

  /* Transmit IO_DIR */
  XMC_I2C_CH_MasterTransmit(XMC_I2C1_CH0, IO_DIR);
  while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
  {
	/* wait for ACK */
  }
  XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

  /* Transmit Direction*/
  XMC_I2C_CH_MasterTransmit(XMC_I2C1_CH0, dir);
  while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
  {
	/* wait for ACK */
  }
  XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

 /* Finish I2C transaction */
  XMC_I2C_CH_MasterStop(XMC_I2C1_CH0);
}

void LED_SetIOState(uint8_t state)
{

  /* Start I2C transaction */
  XMC_I2C_CH_MasterStart(XMC_I2C1_CH0, IO_EXPANDER_ADDRESS, XMC_I2C_CH_CMD_WRITE);
  while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
  {
    /* wait for ACK */
  }
  XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

  /* Write register address */
  XMC_I2C_CH_MasterTransmit(XMC_I2C1_CH0, IO_STATE);
  while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
  {
    /* wait for ACK */
  }
  XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

  /* Write IO state */
  XMC_I2C_CH_MasterTransmit(XMC_I2C1_CH0, state);
  while((XMC_I2C_CH_GetStatusFlag(XMC_I2C1_CH0) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
  {
    /* wait for ACK */
  }
  XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH0, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

  /* Finish I2C transaction */
  XMC_I2C_CH_MasterStop(XMC_I2C1_CH0);
}


/**
* Main program entry point. This routine configures the hardware required by
* the application, then enters a loop to run the application tasks in sequence.
*/
int main(void)
{

  /* Variables Initialization*/

  XMC_VADC_RESULT_SIZE_t adc;
  uint8_t led = 0;


  /* VADC Initialization */

  /* Initialize the VADC global registers */
  XMC_VADC_GLOBAL_Init(VADC, &g_global_config);

  /* Configure a conversion kernel */
  XMC_VADC_GROUP_Init(VADC_GROUP_PTR, &g_group_config);

  XMC_VADC_GROUP_QueueInit(VADC_GROUP_PTR, &g_queue_config);

  /* Configure a channel belonging to the aforesaid conversion kernel */
  XMC_VADC_GROUP_ChannelInit(VADC_GROUP_PTR,CHANNEL_NUMBER, &g_channel_config);

  /* Configure a result resource belonging to the aforesaid conversion kernel */
  XMC_VADC_GROUP_ResultInit(VADC_GROUP_PTR, RES_REG_NUMBER, &g_result_config);

  /* Add the channel to the queue */
  XMC_VADC_GROUP_QueueInsertChannel(VADC_GROUP_PTR, g_queue_entry);

  /* Enable the analog converters */
  XMC_VADC_GROUP_SetPowerMode(VADC_GROUP_PTR, XMC_VADC_GROUP_POWERMODE_NORMAL);

  /* Perform calibration of the converter */
  XMC_VADC_GLOBAL_StartupCalibration(VADC);


  /* I2C Initialization */

  XMC_I2C_CH_Init(XMC_I2C1_CH0, &i2c_cfg);
  XMC_I2C_CH_SetInputSource(XMC_I2C1_CH0, XMC_I2C_CH_INPUT_SDA, USIC1_C0_DX0_P2_14);
  XMC_I2C_CH_SetInputSource(XMC_I2C1_CH0, XMC_I2C_CH_INPUT_SCL, USIC1_C0_DX1_P5_8);
  XMC_I2C_CH_Start(XMC_I2C1_CH0);

  /* GPIO Initialization */

  XMC_GPIO_SetMode(SCL_PIN, XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2);
  XMC_GPIO_SetMode(SDA_PIN, XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2);

  /* USB Initialization */
  USB_Init();

  /*Set IO directions on the HMI OLED board to output mode*/
  LED_SetIODir(0xff);

  /*Turn ON the LEDs on OLED board*/
  LED_SetIOState(0x00);

  /* Trigger next conversion */
  XMC_VADC_GROUP_QueueTriggerConversion(VADC_GROUP_PTR);

  while (1)
  {
    /* Check for the reception of LED state info from USB host */
    if (USBD_WINUSB_BytesReceived(WinUSBInfo.Config.OutEndpoint.Address))
    {

      /* Read the data received */
      USBD_WINUSB_ReadData(WinUSBInfo.Config.OutEndpoint.Address,&led,1);
      LED_SetIOState(led);
    }
    /* Get the ADC result according to Pot value */
    adc =  XMC_VADC_GROUP_GetResult(VADC_GROUP_PTR, RES_REG_NUMBER);

    /*Send the adc result to USB host*/
    USBD_WINUSB_WriteData(WinUSBInfo.Config.InEndpoint.Address,&adc,2);
  }
}
