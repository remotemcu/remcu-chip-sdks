/**
 * \file
 *
 * \brief AT86RFX configuration
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#ifndef CONF_AT86RFX_H
#define CONF_AT86RFX_H

#include "gpio.h"
#include "unit_tests.h"
#include "cycle_counter.h"
#include "sysclk.h"

/*! \name Macros for IRQ and AT86RFX accessing GPIO
 */
//! @{
#define EXT_INT                         (AVR32_PIN_PA20)
#define EXT_INT_ISR_GROUP               2
#define EXT_INT_ISR_PRIORITY            1

 //! RESET pin of transceiver
#define TRX_RST       					(AVR32_PIN_PA17)
 //! Sleep Transceiver pin
#define SLP_TR                          (AVR32_PIN_PA19)
//! @}

#if (UC3)
/* This macro saves the global interrupt status */
#define ENTER_CRITICAL_REGION()                 AVR32_ENTER_CRITICAL_REGION( )

/* This macro restores the global interrupt status */
#define LEAVE_CRITICAL_REGION()                 AVR32_LEAVE_CRITICAL_REGION( )

/* Wait for 65 ns. */
#define  WAIT_65_NS()  {nop(); nop();}

/* Wait for 1 us. */
#define PAL_WAIT_1_US()      do {              \
                            cpu_delay_us(1, sysclk_get_cpu_hz()); \
} while (0)

/* Wait for 1 us. */
#define DELAY_US(delay)      do {              \
                            cpu_delay_us(delay, sysclk_get_cpu_hz()); \
} while (0)
#endif

/**
 * AT86RFX Module Callbacks definitions (Optional)
 * @{
 */
#define AT86RFX_RX_NOTIFY(frame)
#define AT86RFX_TX_STATUS_NOTIFY(status)  	at86rfx_tal_tx_status_cb(status)
//@}

#endif /* CONF_AT86RFX_H */
