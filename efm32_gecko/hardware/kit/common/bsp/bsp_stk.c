/***************************************************************************//**
 * @file
 * @brief Board support package API implementation STK's.
 * @version 5.1.1
 *******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include <string.h>
#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "bsp.h"
#if defined( BSP_STK_USE_EBI )
#include "em_ebi.h"
#endif
#if defined(BSP_IO_EXPANDER)
#include "bsp_stk_ioexp.h"
#endif

#if defined( BSP_STK )

/***************************************************************************//**
 * @addtogroup BSP
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup BSP_STK API for STK's and WSTK's
 * @{
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
/**************************************************************************//**
 * @brief Deinitialize board support package functionality.
 *        Reverse actions performed by @ref BSP_Init().
 *
 * @return @ref BSP_STATUS_OK.
 *****************************************************************************/
int BSP_Disable(void)
{
  BSP_BccDeInit();
  BSP_EbiDeInit();

#if defined(BSP_IO_EXPANDER)
  ioexpDisable();
#endif

  return BSP_STATUS_OK;
}
/** @endcond */

/**************************************************************************//**
 * @brief Initialize the EBI interface for accessing the onboard nandflash.
 *
 * @note This function is not relevant for Gxxx_STK's.
 *
 * @return
 *   @ref BSP_STATUS_OK or @ref BSP_STATUS_NOT_IMPLEMENTED
 *****************************************************************************/
int BSP_EbiInit(void)
{
#if defined( BSP_STK_USE_EBI )
  /* ------------------------------------------ */
  /* NAND Flash, Bank0, Base Address 0x80000000 */
  /* Micron flash NAND256W3A                    */
  /* ------------------------------------------ */

  EBI_Init_TypeDef ebiConfig =
  {   ebiModeD8A8,       /* 8 bit address, 8 bit data */
      ebiActiveLow,      /* ARDY polarity */
      ebiActiveLow,      /* ALE polarity */
      ebiActiveLow,      /* WE polarity */
      ebiActiveLow,      /* RE polarity */
      ebiActiveLow,      /* CS polarity */
      ebiActiveLow,      /* BL polarity */
      false,             /* disble BL */
      true,              /* enable NOIDLE */
      false,             /* disable ARDY */
      true,              /* disable ARDY timeout */
      EBI_BANK0,         /* enable bank 0 */
      0,                 /* no chip select */
      0,                 /* addr setup cycles */
      0,                 /* addr hold cycles */
      false,             /* disable half cycle ALE strobe */
      0,                 /* read setup cycles */
      2,                 /* read strobe cycles */
      1,                 /* read hold cycles */
      false,             /* disable page mode */
      false,             /* disable prefetch */
      false,             /* disable half cycle REn strobe */
      0,                 /* write setup cycles */
      2,                 /* write strobe cycles */
      1,                 /* write hold cycles */
      false,             /* enable the write buffer */
      false,             /* disable half cycle WEn strobe */
      ebiALowA24,        /* ALB - Low bound, address lines */
      ebiAHighA26,       /* APEN - High bound, address lines */
      ebiLocation1,      /* Use Location 1 */
      true,              /* enable EBI */
  };

  /* Enable clocks */
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_EBI, true);

  /* Enable GPIO's */
  /* ALE and CLE */
  GPIO_PinModeSet(gpioPortC, 1, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortC, 2, gpioModePushPull, 0);

  /* WP, CE and R/B */
  GPIO_PinModeSet(gpioPortD, 13, gpioModePushPull, 0);   /* active low write-protect */
  GPIO_PinModeSet(gpioPortD, 14, gpioModePushPull, 1);   /* active low chip-enable */
  GPIO_PinModeSet(gpioPortD, 15, gpioModeInput, 0);      /* ready/busy */

  /* IO pins */
  GPIO_PinModeSet(gpioPortE, 8, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 9, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 10, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 11, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 12, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 13, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 14, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortE, 15, gpioModePushPull, 0);

  /* WE and RE */
  GPIO_PinModeSet(gpioPortF, 8, gpioModePushPull, 1);
  GPIO_PinModeSet(gpioPortF, 9, gpioModePushPull, 1);

  /* NAND Power Enable */
  GPIO_PinModeSet(gpioPortB, 15, gpioModePushPull, 1);

  EBI_Init(&ebiConfig);
  EBI->NANDCTRL = (EBI_NANDCTRL_BANKSEL_BANK0 | EBI_NANDCTRL_EN);

  return BSP_STATUS_OK;
#else
  return BSP_STATUS_NOT_IMPLEMENTED;
#endif
}

/**************************************************************************//**
 * @brief Deinitialize the EBI interface for accessing the onboard nandflash.
 *
 * @note This function is not relevant for Gxxx_STK's.
 *       This function is provided for API completeness, it does not perform
 *       an actual EBI deinitialization.
 *
 * @return
 *   @ref BSP_STATUS_OK or @ref BSP_STATUS_NOT_IMPLEMENTED
 *****************************************************************************/
int BSP_EbiDeInit( void )
{
#if defined( BSP_STK_USE_EBI )
  return BSP_STATUS_OK;
#else
  return BSP_STATUS_NOT_IMPLEMENTED;
#endif
}

/**************************************************************************//**
 * @brief Get IO Expander Device id.
 *
 * @return
 *   The device id of a connected IO Expander Device id or 0 if no IO expander
 *   is connected.
 *****************************************************************************/
uint32_t BSP_IOExpGetDeviceId( void )
{
#if defined(BSP_IO_EXPANDER)
  return ioexpGetDeviceId();
#else
  return 0;
#endif
}

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
/**************************************************************************//**
 * @brief Initialize board support package functionality.
 *
 * @param[in] flags Initialization mask, use 0 or @ref BSP_INIT_BCC.
 *
 * @return
 *   @ref BSP_STATUS_OK or BSP_STATUS_IOEXP_FAILURE
 *****************************************************************************/
int BSP_Init( uint32_t flags )
{
#if defined(BSP_IO_EXPANDER)
  int status;
#endif

  if ( flags & BSP_INIT_BCC )
  {
    BSP_BccInit();
  }

#if defined(BSP_IO_EXPANDER)
  if (flags & BSP_INIT_IOEXP)
  {
    status = ioexpEnable();
    if (status != BSP_STATUS_OK)
    {
      return status;
    }
  }
#endif

  return BSP_STATUS_OK;
}
/** @endcond */

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
/**************************************************************************//**
 * @brief STK Peripheral Access Control
 *    Enable or disable access to on-board peripherals using the IO-expander.
 *
 * @param[in] perf
 *    Which peripheral to configure. Use enum @ref BSP_Peripheral_TypeDef.
 *
 * @param[in] enable
 *    If true, set up access to peripheral, if false disable access.
 *
 * @return
 *   @ref BSP_STATUS_OK, @ref BSP_STATUS_NOT_IMPLEMENTED
 *   or @ref BSP_STATUS_IOEXP_FAILURE
 *****************************************************************************/
int BSP_PeripheralAccess(BSP_Peripheral_TypeDef perf, bool enable)
{
#if defined(BSP_IO_EXPANDER)
  int status = BSP_STATUS_OK;

  if (enable)
  {
    switch (perf)
    {
      case BSP_IOEXP_LEDS:
        status = ioexpWriteReg(BSP_IOEXP_REG_LED_CTRL,
                               BSP_IOEXP_REG_LED_CTRL_DIRECT);
        break;

      case BSP_IOEXP_SENSORS:
        status = ioexpWriteReg(BSP_IOEXP_REG_SENSOR_CTRL, 1);
        break;

      case BSP_IOEXP_DISPLAY:
        /* Cant use VCOM together with the display. */
        status = ioexpWriteReg(BSP_IOEXP_REG_VCOM_CTRL, 0);
        if (status == BSP_STATUS_OK)
        {
          status = ioexpWriteReg(BSP_IOEXP_REG_DISP_CTRL,
                                 BSP_IOEXP_REG_DISP_CTRL_ENABLE
                                 | BSP_IOEXP_REG_DISP_CTRL_AUTO_EXTCOMIN);
        }
        break;

      case BSP_IOEXP_VCOM:
        /* Cant use the display together with VCOM. */
        status = ioexpWriteReg(BSP_IOEXP_REG_DISP_CTRL, 0);
        if (status == BSP_STATUS_OK)
        {
          status = ioexpWriteReg(BSP_IOEXP_REG_VCOM_CTRL, 1);
        }
        break;
    }
  }
  else
  {
    switch (perf)
    {
      case BSP_IOEXP_LEDS:
        status = ioexpWriteReg(BSP_IOEXP_REG_LED_CTRL, 0);
        break;

      case BSP_IOEXP_SENSORS:
        status = ioexpWriteReg(BSP_IOEXP_REG_SENSOR_CTRL, 0);
        break;

      case BSP_IOEXP_DISPLAY:
        status = ioexpWriteReg(BSP_IOEXP_REG_DISP_CTRL, 0);
        break;

      case BSP_IOEXP_VCOM:
        status = ioexpWriteReg(BSP_IOEXP_REG_VCOM_CTRL, 0);
        break;
    }
  }

  return status;
#else
  (void)perf;
  (void)enable;

  return BSP_STATUS_NOT_IMPLEMENTED;
#endif
}
/** @endcond */

/**************************************************************************//**
 * @brief Request AEM (Advanced Energy Monitoring) current from board controller.
 *
 * @note Assumes that BSP_Init() has been called with @ref BSP_INIT_BCC
 *       bitmask.
 *
 * @return
 *   The current expressed in milliamperes. Returns 0.0 on board controller
 *   communication error.
 *****************************************************************************/
float BSP_CurrentGet( void )
{
   BCP_Packet pkt;
   float      *pcurrent;

   pkt.type          = BSP_BCP_CURRENT_REQ;
   pkt.payloadLength = 0;

   /* Send Request/Get reply */
   BSP_BccPacketSend( &pkt );
   BSP_BccPacketReceive( &pkt );

   /* Process reply */
   pcurrent = (float *)pkt.data;
   if ( pkt.type != BSP_BCP_CURRENT_REPLY )
   {
      *pcurrent = 0.0f;
   }

   return *pcurrent;
}

/**************************************************************************//**
 * @brief Request AEM (Advanced Energy Monitoring) voltage from board controller.
 *
 * @note Assumes that BSP_Init() has been called with @ref BSP_INIT_BCC
 *       bitmask.
 *
 * @return
 *   The voltage. Returns 0.0 on board controller communication
 *   error.
 *****************************************************************************/
float BSP_VoltageGet( void )
{
   BCP_Packet pkt;
   float      *pvoltage;

   pkt.type          = BSP_BCP_VOLTAGE_REQ;
   pkt.payloadLength = 0;

   /* Send Request/Get reply */
   BSP_BccPacketSend( &pkt );
   BSP_BccPacketReceive( &pkt );

   /* Process reply */
   pvoltage = (float *)pkt.data;
   if ( pkt.type != BSP_BCP_VOLTAGE_REPLY )
   {
      *pvoltage = 0.0f;
   }

   return *pvoltage;
}

/** @} (end group BSP_STK) */
/** @} (end group BSP) */

#endif /* BSP_STK */
