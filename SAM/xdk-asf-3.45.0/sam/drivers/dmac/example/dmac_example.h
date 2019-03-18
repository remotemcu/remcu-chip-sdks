/**
 * \file
 *
 * \brief DMAC (DMA Controller) driver example for SAM.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef DMAC_EXAMPLE_H_INCLUDED
#define DMAC_EXAMPLE_H_INCLUDED

/**
 * \page asfdoc_sam_drivers_dmac_example SAM Direct Memory Access Controller - Example Memory to Memory Transfer
 *
 * \section asfdoc_sam_drivers_dmac_example_purpose Purpose
 * This example demonstrates how to configure and use DMAC controller
 * for single and multiple memory to memory data buffer transfers.
 *
 * \section asfdoc_sam_drivers_dmac_example_requirements Requirements
 * This example can be used with SAM evaluation kits that have a DMA
 * Controller.
 *
 * \section asfdoc_sam_drivers_dmac_example_description Description
 * This example transfers data in one RAM buffer to another RAM buffer.
 * Two transfer modes will be used:
 * -# It uses single buffer transfer with polling mode.
 *    After transfer is done, the transferred data will be verified.
 * -# It uses multiple buffer transfer with interrupt mode.
 *    After transfer is done, the transferred data will be verified.
 *
 * \section asfdoc_sam_drivers_dmac_example_files Main Files
 * - dmac.c: Direct Memory Access Controller driver
 * - dmac.h: Direct Memory Access Controller driver header file
 * - dmac_example1.c: Direct Memory Access Controller example application
 *
 * \section asfdoc_sam_drivers_dmac_example_compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench&reg;
 * for Atmel&reg;. Other compilers may or may not work.
 *
 * \section asfdoc_sam_drivers_dmac_example_usage Usage
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft&reg; Windows&reg;) with these settings:
 *   - 115200 baud
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
 *     -- DMAC Example --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *     Test single buffer transfer......
 *     > Test OK
 *
 *     Test multiple buffer transfer......
 *     > Test OK. \endcode
 * \note Values depend on the board and the chip used.
 */
 
 #endif /* DMAC_EXAMPLE_H_INCLUDED */
