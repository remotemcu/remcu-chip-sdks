/***************************************************************************//**
 * @file
 * @brief Provide BSP (board support package) configuration parameters.
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

#ifndef BSPCONFIG_H
#define BSPCONFIG_H

#define BSP_STK
#define BSP_WSTK
#define BSP_WSTK_BRD4150A

#define BSP_BCC_USART         USART0
#define BSP_BCC_CLK           cmuClock_USART0
#define BSP_BCC_TX_LOCATION   USART_ROUTELOC0_TXLOC_LOC0
#define BSP_BCC_RX_LOCATION   USART_ROUTELOC0_RXLOC_LOC0
#define BSP_BCC_TXPORT        gpioPortA
#define BSP_BCC_TXPIN         0
#define BSP_BCC_RXPORT        gpioPortA
#define BSP_BCC_RXPIN         1
#define BSP_BCC_ENABLE_PORT   gpioPortA
#define BSP_BCC_ENABLE_PIN    5                 /* VCOM_ENABLE */

#define BSP_DISP_ENABLE_PORT  gpioPortD
#define BSP_DISP_ENABLE_PIN   15                /* MemLCD display enable */

#define BSP_GPIO_LEDS
#define BSP_NO_OF_LEDS          2
#define BSP_GPIO_LED0_PORT      gpioPortF
#define BSP_GPIO_LED0_PIN       4
#define BSP_GPIO_LED1_PORT      gpioPortF
#define BSP_GPIO_LED1_PIN       5
#define BSP_GPIO_LEDARRAY_INIT  {{BSP_GPIO_LED0_PORT,BSP_GPIO_LED0_PIN}, {BSP_GPIO_LED1_PORT,BSP_GPIO_LED1_PIN}}

#define BSP_GPIO_BUTTONS
#define BSP_NO_OF_BUTTONS       2
#define BSP_GPIO_PB0_PORT       gpioPortF
#define BSP_GPIO_PB0_PIN        6
#define BSP_GPIO_PB1_PORT       gpioPortF
#define BSP_GPIO_PB1_PIN        7

#define BSP_GPIO_BUTTONARRAY_INIT {{BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN}, {BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN}}

#define BSP_INIT_DEFAULT  0

#if !defined(EMU_DCDCINIT_WSTK_DEFAULT)
/* Use emlib defaults */
#define EMU_DCDCINIT_WSTK_DEFAULT       EMU_DCDCINIT_DEFAULT
#endif

#if !defined(CMU_HFXOINIT_WSTK_DEFAULT)
#define CMU_HFXOINIT_WSTK_DEFAULT                                               \
{                                                                               \
  false,        /* Low-noise mode for EFR32 */                                  \
  false,        /* Disable auto-start on EM0/1 entry */                         \
  false,        /* Disable auto-select on EM0/1 entry */                        \
  false,        /* Disable auto-start and select on RAC wakeup */               \
  _CMU_HFXOSTARTUPCTRL_CTUNE_DEFAULT,                                           \
  0x142,        /* Steady-state CTUNE for WSTK boards without load caps */      \
  _CMU_HFXOSTEADYSTATECTRL_REGISH_DEFAULT,                                      \
  0x20,         /* Matching errata fix in CHIP_Init() */                        \
  0x7,          /* Recommended steady-state osc core bias current */            \
  0x6,          /* Recommended peak detection threshold */                      \
  _CMU_HFXOTIMEOUTCTRL_SHUNTOPTTIMEOUT_DEFAULT,                                 \
  0xA,          /* Recommended peak detection timeout  */                       \
  0x4,          /* Recommended steady timeout */                                \
  _CMU_HFXOTIMEOUTCTRL_STARTUPTIMEOUT_DEFAULT,                                  \
  cmuOscMode_Crystal,                                                           \
}
#endif

#if !defined(RADIO_PTI_INIT)
#define RADIO_PTI_INIT                                                        \
  {                                                                           \
    RADIO_PTI_MODE_UART,    /* Simplest output mode is UART mode */           \
    1600000,                /* Choose 1.6 MHz for best compatibility */       \
    6,                      /* WSTK uses location 6 for DOUT */               \
    gpioPortB,              /* Get the port for this loc */                   \
    12,                     /* Get the pin, location should match above */    \
    6,                      /* WSTK uses location 6 for DCLK */               \
    gpioPortB,              /* Get the port for this loc */                   \
    11,                     /* Get the pin, location should match above */    \
    6,                      /* WSTK uses location 6 for DFRAME */             \
    gpioPortB,              /* Get the port for this loc */                   \
    13,                     /* Get the pin, location should match above */    \
  }
#endif

#if !defined(RADIO_PA_2P4_INIT)
#define RADIO_PA_2P4_INIT                                                     \
  {                                                                           \
    PA_SEL_2P4_HP,    /* Power Amplifier mode */                              \
    PA_VOLTMODE_DCDC, /* Power Amplifier vPA Voltage mode */                  \
    100,              /* Desired output power in dBm * 10 */                  \
    0,                /* Output power offset in dBm * 10 */                   \
    10,               /* Desired ramp time in us */                           \
  }
#endif

#if !defined(RADIO_PA_SUBGIG_INIT)
#define RADIO_PA_SUBGIG_INIT                                                  \
  {                                                                           \
    PA_SEL_SUBGIG,    /* Power Amplifier mode */                              \
    PA_VOLTMODE_DCDC, /* Power Amplifier vPA Voltage mode */                  \
    100,              /* Desired output power in dBm * 10 */                  \
    0,                /* Output power offset in dBm * 10 */                   \
    10,               /* Desired ramp time in us */                           \
  }
#endif

#define BSP_BCP_VERSION 2
#include "bsp_bcp.h"

#endif /* BSPCONFIG_H */
