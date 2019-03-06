/***************************************************************************//**
 * @file
 * @brief Provide stdio retargeting configuration parameters.
 * @version 5.1.1
 *******************************************************************************
 * @section License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef __SILICON_LABS_RETARGETSERIALCONFIG_H
#define __SILICON_LABS_RETARGETSERIALCONFIG_H

#include "bsp.h"

/* Override if needed with commandline parameter -DRETARGET_xxx */

#if !defined(RETARGET_USART0) && \
    !defined(RETARGET_USART1) && \
    !defined(RETARGET_LEUART0)
#define RETARGET_USART1    /* Use USART1 by default. */
#endif

/* Note: USART1 conflicts with board controller BCC communication port. */
#if defined(RETARGET_USART1)
  #define RETARGET_IRQ_NAME    USART1_RX_IRQHandler         /* USART IRQ Handler */
  #define RETARGET_CLK         cmuClock_USART1              /* HFPER Clock */
  #define RETARGET_IRQn        USART1_RX_IRQn               /* IRQ number */
  #define RETARGET_UART        USART1                       /* UART instance */
  #define RETARGET_TX          USART_Tx                     /* Set TX to USART_Tx */
  #define RETARGET_RX          USART_Rx                     /* Set RX to USART_Rx */
  #define RETARGET_LOCATION    USART_ROUTE_LOCATION_LOC0    /* Location of of the USART I/O pins */
  #define RETARGET_TXPORT      gpioPortC                    /* USART transmission port */
  #define RETARGET_TXPIN       0                            /* USART transmission pin */
  #define RETARGET_RXPORT      gpioPortC                    /* USART reception port */
  #define RETARGET_RXPIN       1                            /* USART reception pin */
  #define RETARGET_USART       1                            /* Includes em_usart.h */
  #define RETARGET_PERIPHERAL_ENABLE()

/* Note: USART0 conflicts with memory LCD SPI communication port. */
#elif defined(RETARGET_USART0)
  #define RETARGET_IRQ_NAME    USART0_RX_IRQHandler         /* USART IRQ Handler */
  #define RETARGET_CLK         cmuClock_USART0              /* HFPER Clock */
  #define RETARGET_IRQn        USART0_RX_IRQn               /* IRQ number */
  #define RETARGET_UART        USART0                       /* UART instance */
  #define RETARGET_TX          USART_Tx                     /* Set TX to USART_Tx */
  #define RETARGET_RX          USART_Rx                     /* Set RX to USART_Rx */
  #define RETARGET_LOCATION    USART_ROUTE_LOCATION_LOC0    /* Location of of the USART I/O pins */
  #define RETARGET_TXPORT      gpioPortE                    /* USART transmission port */
  #define RETARGET_TXPIN       10                           /* USART transmission pin */
  #define RETARGET_RXPORT      gpioPortE                    /* USART reception port */
  #define RETARGET_RXPIN       11                           /* USART reception pin */
  #define RETARGET_USART       1                            /* Includes em_usart.h */
  #define RETARGET_PERIPHERAL_ENABLE()

#elif defined(RETARGET_LEUART0)
  #define RETARGET_IRQ_NAME    LEUART0_IRQHandler           /* LEUART IRQ Handler */
  #define RETARGET_CLK         cmuClock_LEUART0             /* LFB Clock */
  #define RETARGET_IRQn        LEUART0_IRQn                 /* IRQ number */
  #define RETARGET_UART        LEUART0                      /* LEUART instance */
  #define RETARGET_TX          LEUART_Tx                    /* Set TX to LEUART_Tx */
  #define RETARGET_RX          LEUART_Rx                    /* Set RX to LEUART_Rx */
  #define RETARGET_TXPORT      gpioPortD                    /* LEUART transmission port */
  #define RETARGET_TXPIN       4                            /* LEUART transmission pin */
  #define RETARGET_RXPORT      gpioPortD                    /* LEUART reception port */
  #define RETARGET_RXPIN       5                            /* LEUART reception pin */
  #define RETARGET_LOCATION    LEUART_ROUTE_LOCATION_LOC0   /* Location of of the LEUART I/O pins */
  #define RETARGET_LEUART      1                            /* Includes em_leuart.h */
  #define RETARGET_PERIPHERAL_ENABLE()

#else
#error "Illegal USART/LEUART selection."
#endif

#endif /* __SILICON_LABS_RETARGETSERIALCONFIG_H */
