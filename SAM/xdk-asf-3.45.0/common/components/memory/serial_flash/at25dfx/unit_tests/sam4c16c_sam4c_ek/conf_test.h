/**
 * \file
 *
 * \brief Unit test configuration.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef CONF_TEST_H_INCLUDED
#define CONF_TEST_H_INCLUDED

/** USART Interface */
#define CONF_TEST_USART      CONSOLE_UART
/** Baudrate setting */
#define CONF_TEST_BAUDRATE   115200UL
/** Char setting     : 8-bit character length (don't care for UART) */
#define CONF_TEST_CHARLENGTH 0
/** Parity setting */
#define CONF_TEST_PARITY     UART_MR_PAR_NO
/** Stopbit setting  : No extra stopbit, i.e., use 1 (don't care for UART) */
#define CONF_TEST_STOPBITS   false

/** Total size of the SerialFlash used in the unit test */
#define AT25DFX_UNIT_TEST_TOTAL_SIZE   (4*1024*1024)

/** Block size of the SerialFlash used in the unit test */
#define AT25DFX_UNIT_TEST_BLOCK_SIZE   (64*1024)

/** Page size of the SerialFlash used in the unit test */
#define AT25DFX_UNIT_TEST_PAGE_SIZE   (256)

/** Unit test block start address */
#define AT25DFX_UNIT_TEST_BLOCK_ADDR  (0)

#endif /* CONF_TEST_H_INCLUDED */
