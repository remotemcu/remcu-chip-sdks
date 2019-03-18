/**
* \file
*
* \brief AT25DFx SerialFlash driver quick start
*
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef QS_AT25DFX_BASIC_H
#define QS_AT25DFX_BASIC_H

/**
* \page asfdoc_common2_at25dfx_basic_use Quick Start Guide for AT25DFx SerialFlash Driver
*
* This quick start will read, unprotect, erase and write bytes to an AT25DF081A
* that is connected to the SPI interface on EXT1 header of SAM D20 Xplained Pro or EXT3 of SAM D21 Xplained Pro.
*
* The SERCOM SPI will be configured with the following settings:
*
* For SAM D20 Xplained Pro
* - 500 kHz baud rate
* - SCK, MISO and MOSI on EXT1 header's SPI pins
*
* For SAM D21 Xplained Pro 
* - 120 kHz baud rate
* - SCK, MISO and MOSI on EXT3
*
* The AT25DFx driver instance will be configured with the following settings:
*
* For SAM D20 Xplained Pro 
* - CS on EXT1 header's SS0 pin
*
* For SAM D21 Xplained Pro 
* - CS on EXT3 PA13
*
*
* \section asfdoc_common2_at25dfx_basic_setup Setup
*
* \subsection asfdoc_common2_at25dfx_basic_prereq Prerequisites
*
* There are no special setup requirements for this use-case.
*
*
* \subsection asfdoc_common2_at25dfx_basic_setup_code Code
*
* Add to the main application source file, outside of any functions:
* \snippet qs_at25dfx_basic.c buffers
* \snippet qs_at25dfx_basic.c driver_instances
*
* Create a new function for initializing the AT25DFx:
* \snippet qs_at25dfx_basic.c init_function
*
* If not already present, add to the initialization code:
* \snippet qs_at25dfx_basic.c init_calls
*
*
* \subsection asfdoc_common2_at25dfx_basic_setup_flow Workflow
*
* -# Create read and write buffers.
*    \snippet qs_at25dfx_basic.c buffers
* -# Create global instances of SPI and AT25DFx chip.
*    \snippet qs_at25dfx_basic.c driver_instances
* -# Create a function to contain the AT25DFx initialization code.
* -# Create local instances of SPI and AT25DFx configurations.
*    \snippet qs_at25dfx_basic.c config_instances
* -# Initialize the SPI for AT25DFx connected to EXT1 header.
*    \snippet qs_at25dfx_basic.c spi_setup
* -# Initialize the AT25DFx instance for AT25DF081A, with Slave Select on the
* SS_0 pin on EXT1.
*    \snippet qs_at25dfx_basic.c chip_setup
*
*
* \section asfdoc_common2_at25dfx_basic_use_case Use Case
*
* \subsection asfdoc_common2_at25dfx_basic_use_case_code Code
*
* Copy into main application:
* \snippet qs_at25dfx_basic.c use_code
*
*
* \subsection asfdoc_common2_at25dfx_basic_use_case_flow Workflow
*
* -# Wakeup serialFlash.
*    \snippet qs_at25dfx_basic.c wake_chip
* -# Check that the SerialFlash is present.
*    \snippet qs_at25dfx_basic.c check_presence
* -# Read out the first \ref AT25DFX_BUFFER_SIZE bytes, starting at the very
* first flash address.
*    \snippet qs_at25dfx_basic.c read_buffer
* -# Disable protection of the second sector.
*    \note This device has sectors with a uniform size of 64 kB, so the address
* \c 0x10000 marks the start of the second sector. This can differ between
* devices.
*
*    \snippet qs_at25dfx_basic.c unprotect_sector
* -# Erase the first 4 kB of the second 64 kB block (64-68 kB range).
*    \snippet qs_at25dfx_basic.c erase_block
* -# Write \ref AT25DFX_BUFFER_SIZE bytes, starting at the beginning of the
* sector and the newly erased memory locations.
*    \snippet qs_at25dfx_basic.c write_buffer
* -# Enable protection of all sectors, to prevent accidental erases of content.
*    \snippet qs_at25dfx_basic.c global_protect
* -# Put SerialFlash device to sleep, to conserve power.
*    \snippet qs_at25dfx_basic.c sleep
*
*/

#endif // QS_AT25DFX_BASIC_H