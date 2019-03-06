/***************************************************************************//**
 * @file retargetserialconfig.h
 * @brief Provide stdio retargeting configuration parameters
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

#ifndef __RETARGETSERIALCONFIG_H
#define __RETARGETSERIALCONFIG_H

/* Override if needed with commandline parameter -DRETARGET_xxx */

#if !defined(RETARGET_USART0) && !defined(RETARGET_VCOM)
#define RETARGET_USART0    /* Use USART0 by default. */
#endif

#if defined(RETARGET_USART0) || defined(RETARGET_VCOM)
  #define RETARGET_IRQ_NAME    USART0_RX_IRQHandler         /* UART IRQ Handler */
  #define RETARGET_CLK         cmuClock_USART0              /* HFPER Clock */
  #define RETARGET_IRQn        USART0_RX_IRQn               /* IRQ number */
  #define RETARGET_UART        USART0                       /* UART instance */
  #define RETARGET_TX          USART_Tx                     /* Set TX to USART_Tx */
  #define RETARGET_RX          USART_Rx                     /* Set RX to USART_Rx */

  #define RETARGET_TX_LOCATION 0                            /* Location of of USART TX pin */
  #define RETARGET_RX_LOCATION 0                            /* Location of of USART RX pin */

  #define RETARGET_TXPORT      gpioPortA                    /* UART transmission port */
  #define RETARGET_TXPIN       0                            /* UART transmission pin */
  #define RETARGET_RXPORT      gpioPortA                    /* UART reception port */
  #define RETARGET_RXPIN       1                            /* UART reception pin */
  #define RETARGET_USART       1                            /* Includes em_usart.h */

  #define RETARGET_PERIPHERAL_ENABLE()

#else
#error "Illegal USART selection."
#endif

#endif /* __RETARGETSERIALCONFIG_H */
