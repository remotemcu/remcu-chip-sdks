/**
 * \file
 *
 * \brief Unit test configuration.
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

#ifndef CONF_TEST_H
#define CONF_TEST_H

/** USART Interface */
#define CONF_TEST_USART      CONSOLE_UART
/** Baudrate setting */
#define CONF_TEST_BAUDRATE   115200
/** Parity setting */
#define CONF_TEST_PARITY     UART_MR_PAR_NO

/* Default page count number */
#define DEFAULT_PAGE_COUNT (IFLASH1_SIZE/IFLASH1_PAGE_SIZE)

/* Default region count number */
#define DEFAULT_REGION_COUNT 1

/* Number of pages in a region */
#define IFLASH_NB_OF_PAGES IFLASH0_NB_OF_PAGES

/* Test page start address */
#define TEST_PAGE_ADDRESS (IFLASH1_ADDR + IFLASH1_SIZE - IFLASH1_PAGE_SIZE)

/* Flash start address */
#define IFLASH_ADDR IFLASH1_ADDR

/* Flash page size */
#define IFLASH_PAGE_SIZE IFLASH1_PAGE_SIZE

#endif /* CONF_TEST_H_INCLUDED */
