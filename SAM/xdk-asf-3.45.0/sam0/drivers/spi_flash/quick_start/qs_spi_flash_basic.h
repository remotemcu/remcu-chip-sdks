/**
 * \file
 *
 * \brief SAM SPI Flash Driver Quick Start for SAMB11
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

/**
 * \page asfdoc_samb_spi_flash_basic_use_case Quick Start Guide for SPI-Flash - Basic
 *
 * In this use case, the SPI-Flash module is configured for:
 *  \li Spi flash initial.
 *
 * This use case sets up the SPI-Flash to erase, write and read flash data via
 * defualt spi-flash gpio configration.
 *
 * \section asfdoc_samb_spi_flash_basic_use_case_setup Setup
 *
 * \subsection asfdoc_samb_spi_flash_basic_use_case_setup_prereq Prerequisites
 * There are no special setup requirements for this use-case.
 *
 * \subsection asfdoc_samb_spi_flash_basic_use_case_setup_code Code
 * The following must be added to the user application source file, outside
 * any functions:
 * Read and write buffer to operate spi-flash.
 * \snippet qs_spi_flash_basic.c buffer
 * A function for configuring the GPIO.
 * \snippet qs_spi_flash_basic.c configure_gpio
 *
 * Add to user application initialization (typically the start of \c main()):
 * \snippet qs_spi_flash_basic.c system_init
 * \snippet qs_spi_flash_basic.c run_config_gpio
 *
 * \snippet qs_spi_flash_basic.c setup_init
 *
 * \subsection asfdoc_samb_spi_flash_basic_use_case_setup_flow Workflow
 * -# Initialize write buffer with default values.
 *    \snippet qs_spi_flash_basic.c setup_1
 * -# Initialize spi-flash and enable.
 *    \snippet qs_spi_flash_basic.c setup_2
 *
 * \section asfdoc_samb_spi_flash_basic_use_case_use_main Use Case
 *
 * \subsection asfdoc_samb_spi_flash_basic_use_case_code Code
 * Copy-paste the following code to your user application:
 * \snippet qs_spi_flash_basic.c main_use_case
 *
 * \subsection asfdoc_samb_spi_flash_basic_use_case_flow Workflow
 * -# Erase spi-flash designated area. If failure, LED will flash quickly. If
 *    successful, it will continue.
 *    \snippet qs_spi_flash_basic.c main_1
 * -# Read spi-flash designated area.
 *    \snippet qs_spi_flash_basic.c main_2
 * -# Compare read data. If there is one data which isn't 0xFFFFFFFF, LED will
 *    flash quickly. If matched, it will continue.
 *    \snippet qs_spi_flash_basic.c main_3
 * -# Write spi-flash designated area.
 *    \snippet qs_spi_flash_basic.c main_4
 * -# Read spi-flash designated area.
 *    \snippet qs_spi_flash_basic.c main_5
 * -# Compare write in and read out data. If the data isn't matched, LED will
 *    flash quickly. If matched, it will continue.
 *    \snippet qs_spi_flash_basic.c main_6
 * -# Infinite loop. If all the operation is right, LED will flash slowly.
 *    \snippet qs_spi_flash_basic.c inf_loop
 */
