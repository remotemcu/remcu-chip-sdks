/***************************************************************************//**
 * @file
 * @brief Board support package API for GPIO leds on STK's.
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

#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "bsp.h"
#if defined(BSP_IO_EXPANDER)
#include "bsp_stk_ioexp.h"
#endif

#if defined( BSP_GPIO_LEDS ) || defined( BSP_IO_EXPANDER )
/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

#if !defined( BSP_IO_EXPANDER )
typedef struct
{
  GPIO_Port_TypeDef   port;
  unsigned int        pin;
} tLedArray;
#endif

#if !defined( BSP_IO_EXPANDER )
static const tLedArray ledArray[ BSP_NO_OF_LEDS ] = BSP_GPIO_LEDARRAY_INIT;
#endif

int BSP_LedsInit(void)
{
  /* If an I/O expander is used, assume that BSP_Init(BSP_INIT_IOEXP)
   * and BSP_PeripheralAccess(BSP_IOEXP_LEDS, true) has been called.
   */
#if !defined(BSP_IO_EXPANDER)
  int i;

  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  for ( i=0; i<BSP_NO_OF_LEDS; i++ )
  {
    GPIO_PinModeSet(ledArray[i].port, ledArray[i].pin, gpioModePushPull, 0);
  }
#endif
  return BSP_STATUS_OK;
}

uint32_t BSP_LedsGet(void)
{
#if defined(BSP_IO_EXPANDER)
  uint8_t value;
  uint32_t retVal;

  ioexpReadReg(BSP_IOEXP_REG_LED_CTRL, &value);
  retVal = value & BSP_IOEXP_REG_LED_CTRL_LED_MASK;

#else
  int i;
  uint32_t retVal, mask;

  for ( i=0, retVal=0, mask=0x1; i<BSP_NO_OF_LEDS; i++, mask <<= 1 )
  {
    if (GPIO_PinOutGet(ledArray[i].port, ledArray[i].pin))
      retVal |= mask;
  }
#endif
  return retVal;
}

int BSP_LedsSet(uint32_t leds)
{
#if defined(BSP_IO_EXPANDER)
  uint8_t value;

  value = (leds & BSP_IOEXP_REG_LED_CTRL_LED_MASK)
          | BSP_IOEXP_REG_LED_CTRL_DIRECT;
  return ioexpWriteReg(BSP_IOEXP_REG_LED_CTRL, value);

#else
  int i;
  uint32_t mask;

  for ( i=0, mask=0x1; i<BSP_NO_OF_LEDS; i++, mask <<= 1 )
  {
    if ( leds & mask )
      GPIO_PinOutSet(ledArray[i].port, ledArray[i].pin);
    else
      GPIO_PinOutClear(ledArray[i].port, ledArray[i].pin);
  }
  return BSP_STATUS_OK;
#endif
}

int BSP_LedClear(int ledNo)
{
  if ((ledNo >= 0) && (ledNo < BSP_NO_OF_LEDS))
  {
#if defined(BSP_IO_EXPANDER)
    return ioexpRegBitsSet(BSP_IOEXP_REG_LED_CTRL, false, 1 << ledNo);
#else
    GPIO_PinOutClear(ledArray[ledNo].port, ledArray[ledNo].pin);
    return BSP_STATUS_OK;
#endif
  }
  return BSP_STATUS_ILLEGAL_PARAM;
}

int BSP_LedGet(int ledNo)
{
#if defined(BSP_IO_EXPANDER)
  uint8_t value;
#endif
  int retVal = BSP_STATUS_ILLEGAL_PARAM;

  if ((ledNo >= 0) && (ledNo < BSP_NO_OF_LEDS))
  {
#if defined(BSP_IO_EXPANDER)
    ioexpReadReg(BSP_IOEXP_REG_LED_CTRL, &value);
    retVal = (value & BSP_IOEXP_REG_LED_CTRL_LED_MASK) >> ledNo;
#else
    retVal = (int)GPIO_PinOutGet(ledArray[ledNo].port, ledArray[ledNo].pin);
#endif
  }
  return retVal;
}

int BSP_LedSet(int ledNo)
{
  if ((ledNo >= 0) && (ledNo < BSP_NO_OF_LEDS))
  {
#if defined(BSP_IO_EXPANDER)
    return ioexpRegBitsSet(BSP_IOEXP_REG_LED_CTRL, true, (1 << ledNo));
#else
    GPIO_PinOutSet(ledArray[ledNo].port, ledArray[ledNo].pin);
    return BSP_STATUS_OK;
#endif
  }
  return BSP_STATUS_ILLEGAL_PARAM;
}

int BSP_LedToggle(int ledNo)
{
#if defined(BSP_IO_EXPANDER)
  uint8_t value;
#endif

  if ((ledNo >= 0) && (ledNo < BSP_NO_OF_LEDS))
  {
#if defined(BSP_IO_EXPANDER)
    ioexpReadReg(BSP_IOEXP_REG_LED_CTRL, &value);
    value &= BSP_IOEXP_REG_LED_CTRL_LED_MASK;
    value ^= (1 << ledNo);
    value |= BSP_IOEXP_REG_LED_CTRL_DIRECT;
    return ioexpWriteReg(BSP_IOEXP_REG_LED_CTRL, value);
#else
    GPIO_PinOutToggle(ledArray[ledNo].port, ledArray[ledNo].pin);
    return BSP_STATUS_OK;
#endif
  }
  return BSP_STATUS_ILLEGAL_PARAM;
}

/** @endcond */
#endif  /* BSP_GPIO_LEDS */
