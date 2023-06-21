/**
 * \file
 *
 * \brief Configuration for PIO example.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef CONF_PIO_EXAMPLE_H_INCLUDED
#define CONF_PIO_EXAMPLE_H_INCLUDED

/** Button name. */
#define BUTTON_STRING            "SW0"

/** Push button pin definition. */
#define PUSH_BUTTON_PIO          PIOA
#define PUSH_BUTTON_ID           ID_PIOA
#define PUSH_BUTTON_PIN_MSK      (1 << 9)
#define PUSH_BUTTON_ATTR         (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_RISE_EDGE)

/** The erase pin mask value in the PIO mode and erase mode. */
#define PIN_PIO_MODE_MSK         (matrix_get_system_io() | CCFG_SYSIO_SYSIO12)
#define PIN_ERASE_MODE_MSK       (matrix_get_system_io() & (~CCFG_SYSIO_SYSIO12))

/** Test page start address. */
#define TEST_PAGE_ADDRESS        (IFLASH_ADDR + IFLASH_SIZE - IFLASH_PAGE_SIZE * 4)

#endif /* CONF_PIO_EXAMPLE_H_INCLUDED */
