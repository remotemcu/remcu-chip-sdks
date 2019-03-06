/**************************************************************************//**
 * @file
 * @brief API for enabling SWO and ETM trace.
 * @version 5.1.1
 ******************************************************************************
 * @section License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/



#include <stdbool.h>
#include "em_device.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "bsp_trace.h"
#include "bsp.h"

#if defined( BSP_ETM_TRACE ) && defined( ETM_PRESENT )

#if !defined(BSP_TRACE_ETM_CLKLOC)
#define BSP_TRACE_ETM_CLKLOC 0
#endif
#if !defined(BSP_TRACE_ETM_TD0LOC)
#define BSP_TRACE_ETM_TD0LOC 0
#endif
#if !defined(BSP_TRACE_ETM_TD1LOC)
#define BSP_TRACE_ETM_TD1LOC 0
#endif
#if !defined(BSP_TRACE_ETM_TD2LOC)
#define BSP_TRACE_ETM_TD2LOC 0
#endif
#if !defined(BSP_TRACE_ETM_TD3LOC)
#define BSP_TRACE_ETM_TD3LOC 0
#endif

/**************************************************************************//**
 * @brief Configure EFM32 for ETM trace output.
 * @note You need to configure ETM trace on kit config menu as well!
 *****************************************************************************/
void BSP_TraceEtmSetup(void)
{
  /* Enable peripheral clocks */
  CMU_ClockEnable(cmuClock_HFLE, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_OscillatorEnable(cmuOsc_AUXHFRCO, true, true);

  /* Configure trace output */
#if defined(_GPIO_ROUTE_TCLKPEN_MASK)
  /* Enable Port D, pins 3,4,5,6 for ETM Trace Data output */
  GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE3_MASK) | GPIO_P_MODEL_MODE3_PUSHPULL;
  GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE4_MASK) | GPIO_P_MODEL_MODE4_PUSHPULL;
  GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE5_MASK) | GPIO_P_MODEL_MODE5_PUSHPULL;
  GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE6_MASK) | GPIO_P_MODEL_MODE6_PUSHPULL;

  /* Enable Port D, pin 7 for DBG_TCLK */
  GPIO->P[3].MODEL = (GPIO->P[3].MODEL & ~_GPIO_P_MODEL_MODE7_MASK) | GPIO_P_MODEL_MODE7_PUSHPULL;
  
  GPIO->ROUTE = GPIO->ROUTE | GPIO_ROUTE_TCLKPEN | GPIO_ROUTE_TD0PEN | GPIO_ROUTE_TD1PEN
                | GPIO_ROUTE_TD2PEN | GPIO_ROUTE_TD3PEN
                | GPIO_ROUTE_ETMLOCATION_LOC0;
#else
  /* Enable GPIO Pins for ETM Trace Data output and ETM Clock */
  GPIO_PinModeSet((GPIO_Port_TypeDef)AF_ETM_TCLK_PORT(BSP_TRACE_ETM_CLKLOC), AF_ETM_TCLK_PIN(BSP_TRACE_ETM_CLKLOC), gpioModePushPull, 0);
  GPIO_PinModeSet((GPIO_Port_TypeDef)AF_ETM_TD0_PORT(BSP_TRACE_ETM_TD0LOC), AF_ETM_TD0_PIN(BSP_TRACE_ETM_TD0LOC), gpioModePushPull, 0);
  GPIO_PinModeSet((GPIO_Port_TypeDef)AF_ETM_TD1_PORT(BSP_TRACE_ETM_TD1LOC), AF_ETM_TD1_PIN(BSP_TRACE_ETM_TD1LOC), gpioModePushPull, 0);
  GPIO_PinModeSet((GPIO_Port_TypeDef)AF_ETM_TD2_PORT(BSP_TRACE_ETM_TD2LOC), AF_ETM_TD2_PIN(BSP_TRACE_ETM_TD2LOC), gpioModePushPull, 0);
  GPIO_PinModeSet((GPIO_Port_TypeDef)AF_ETM_TD3_PORT(BSP_TRACE_ETM_TD3LOC), AF_ETM_TD3_PIN(BSP_TRACE_ETM_TD3LOC), gpioModePushPull, 0);
  
  GPIO->ROUTELOC1 = (BSP_TRACE_ETM_CLKLOC << _GPIO_ROUTELOC1_ETMTCLKLOC_SHIFT)
                    | (BSP_TRACE_ETM_TD0LOC << _GPIO_ROUTELOC1_ETMTD0LOC_SHIFT)
                    | (BSP_TRACE_ETM_TD1LOC << _GPIO_ROUTELOC1_ETMTD1LOC_SHIFT)
                    | (BSP_TRACE_ETM_TD2LOC << _GPIO_ROUTELOC1_ETMTD2LOC_SHIFT)
                    | (BSP_TRACE_ETM_TD3LOC << _GPIO_ROUTELOC1_ETMTD3LOC_SHIFT);
  GPIO->ROUTEPEN = GPIO->ROUTEPEN
                   | GPIO_ROUTEPEN_ETMTCLKPEN 
                   | GPIO_ROUTEPEN_ETMTD0PEN
                   | GPIO_ROUTEPEN_ETMTD1PEN
                   | GPIO_ROUTEPEN_ETMTD2PEN
                   | GPIO_ROUTEPEN_ETMTD3PEN;
#endif
}
#endif

#if defined( _GPIO_ROUTE_SWOPEN_MASK ) || defined( _GPIO_ROUTEPEN_SWVPEN_MASK )
/**************************************************************************//**
 * @brief Configure trace output for energyAware Profiler
 * @note  Enabling trace will add 80uA current for the EFM32_Gxxx_STK.
 *        DK's needs to be initialized with SPI-mode:
 * @verbatim BSP_Init(BSP_INIT_DK_SPI); @endverbatim
 *****************************************************************************/
void BSP_TraceSwoSetup(void)
{
  uint32_t freq;
  uint32_t div;
  /* Enable GPIO clock */
#if defined( _CMU_HFPERCLKEN0_GPIO_MASK )
  CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
#elif defined( _CMU_HFBUSCLKEN0_GPIO_MASK )
  CMU->HFBUSCLKEN0 |= CMU_HFBUSCLKEN0_GPIO;
#endif

  /* Enable Serial wire output pin */
#if defined( _GPIO_ROUTE_SWOPEN_MASK )
  GPIO->ROUTE |= GPIO_ROUTE_SWOPEN;
#elif defined( _GPIO_ROUTEPEN_SWVPEN_MASK )
  GPIO->ROUTEPEN |= GPIO_ROUTEPEN_SWVPEN;
#endif

  /* Set correct location */
#if defined( _GPIO_ROUTE_SWOPEN_MASK )
  GPIO->ROUTE = (GPIO->ROUTE & ~(_GPIO_ROUTE_SWLOCATION_MASK)) | BSP_TRACE_SWO_LOCATION;
#elif defined( _GPIO_ROUTEPEN_SWVPEN_MASK )
  GPIO->ROUTELOC0 = (GPIO->ROUTELOC0 & ~(_GPIO_ROUTELOC0_SWVLOC_MASK)) | BSP_TRACE_SWO_LOCATION;
#endif

  /* Enable output on correct pin. */
  TRACE_ENABLE_PINS();

  /* Enable debug clock AUXHFRCO */
  CMU->OSCENCMD = CMU_OSCENCMD_AUXHFRCOEN;

  /* Wait until clock is ready */
  while (!(CMU->STATUS & CMU_STATUS_AUXHFRCORDY)) ;

  /* Enable trace in core debug */
  CoreDebug->DHCSR |= CoreDebug_DHCSR_C_DEBUGEN_Msk;
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  /* Enable PC and IRQ sampling output */
  DWT->CTRL = 0x400113FF;

  /* Set TPIU prescaler for the current debug clock frequency. Target frequency
     is 875 kHz so we choose a divider that gives us the closest match.
     Actual divider is TPI->ACPR + 1. */
  freq = CMU_ClockFreqGet(cmuClock_DBG) + (875000 / 2);
  div  = freq / 875000;
  TPI->ACPR = div - 1;

  /* Set protocol to NRZ */
  TPI->SPPR = 2;

  /* Disable continuous formatting */
  TPI->FFCR = 0x100;

  /* Unlock ITM and output data */
  ITM->LAR = 0xC5ACCE55;
  ITM->TCR = 0x10009;

  /* ITM Channel 0 is used for UART output */
  ITM->TER |= (1UL << 0);
}
#endif


#if defined( _GPIO_ROUTE_SWOPEN_MASK ) || defined( _GPIO_ROUTEPEN_SWVPEN_MASK )
/**************************************************************************//**
 * @brief  Profiler configuration.
 * @return true if energyAware Profiler/SWO is enabled, false if not
 * @note   If first word of the user page is zero, this will not
 *         enable SWO profiler output.
 *****************************************************************************/
bool BSP_TraceProfilerSetup(void)
{
  volatile uint32_t *userData = (uint32_t *) USER_PAGE;

  /* Check magic "trace" word in user page */
  if (*userData == 0x00000000UL)
  {
    return false;
  }
  else
  {
    BSP_TraceSwoSetup();
    return true;
  }
}
#endif
