/**
 * \file
 *
 * \brief SERCOM SPI master with vectored I/O driver quick start
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

/**
 * \page asfdoc_sam0_sercom_spi_master_vec_basic Quick Start Guide for SERCOM SPI Master Driver w/ Vectored I/O
 *
 * This quick start will receive, transmit and transceive bytes on the EXT1
 * header. In this use case the SERCOM SPI will be configured with the following
 * settings:
 * - 200 kHz SCK
 * - SCK, MISO and MOSI on EXT1 header's SPI pins
 * - CPOL = 1 and CPHA = 1 (idle SCK high, setup on falling edge, sample on
 *   rising)
 *
 *
 * \section asfdoc_sam0_sercom_spi_master_vec_basic_setup Setup
 *
 *
 * \subsection asfdoc_sam0_sercom_spi_master_vec_basic_prereq Prerequisites
 *
 * There are no special setup requirements for this use-case.
 *
 *
 * \subsection asfdoc_sam0_sercom_spi_master_vec_basic_setup_code Code
 *
 * Add to the main application source file, outside of any functions:
 * \snippet qs_spi_master_vec_basic.c transceive_buffers
 * \snippet qs_spi_master_vec_basic.c buffer_descriptors
 * \snippet qs_spi_master_vec_basic.c driver_instance
 *
 * If not already present, add to the initialization code:
 * \snippet qs_spi_master_vec_basic.c init_system
 *
 * Add to the initialization code:
 * \snippet qs_spi_master_vec_basic.c config_instance
 * \snippet qs_spi_master_vec_basic.c set_up_config_instance
 * \snippet qs_spi_master_vec_basic.c init_instance
 *
 *
 * \subsection asfdoc_sam0_sercom_spi_master_vec_basic_setup_flow Workflow
 *
 * -# Create data buffers to transfer to/from.
 *    \snippet qs_spi_master_vec_basic.c transceive_buffers
 *    \note These example buffers are in total 6 bytes long for transmit (TX)
 *        and 3 bytes long for receive (RX).
 *
 * -# Create descriptors for the data buffers. For reception, we will discard
 *        two bytes after the first one.
 *    \snippet qs_spi_master_vec_basic.c buffer_descriptors
 *    \attention The last descriptor in the array \e must specify zero length
 *        for the driver to know when it has reached the last buffer.
 *
 * -# Create an instance of the driver to operate on.
 *
 *    \snippet qs_spi_master_vec_basic.c driver_instance
 * -# In the initialization code, add a config struct for the driver.
 *
 *    \snippet qs_spi_master_vec_basic.c driver_instance
 * -# Initialize the config struct and change to the desired configuration.
 *
 *    \snippet qs_spi_master_vec_basic.c set_up_config_instance
 * -# Initialize the device instance with the configuration and SERCOM to use.
 *
 *    \snippet qs_spi_master_vec_basic.c init_instance
 *
 *
 * \subsection asfdoc_sam0_sercom_spi_master_vec_basic_main_code Code
 *
 * Add to the application code:
 * \snippet qs_spi_master_vec_basic.c enable_instance
 * \snippet qs_spi_master_vec_basic.c start_reception_wait
 * \snippet qs_spi_master_vec_basic.c start_transmission
 * \snippet qs_spi_master_vec_basic.c start_transception
 * \snippet qs_spi_master_vec_basic.c wait_transception
 *
 * \subsection asfdoc_sam0_sercom_spi_master_vec_basic_main_flow Workflow
 * -# Enable the SERCOM module before using it.
 *
 *    \snippet qs_spi_master_vec_basic.c enable_instance
 * -# Start and wait for first transfer: receive 5 bytes, 3 of which will be
 *        written into the RX buffers.
 *
 *    \snippet qs_spi_master_vec_basic.c start_reception_wait
 * -# Start transmission of the 6 bytes from TX buffers.
 *
 *    \snippet qs_spi_master_vec_basic.c start_transmission
 * -# Keep trying to start next transfer until it succeeds: transmit the 6 bytes
 *        from the TX buffers and receive 5 bytes, writing 3 of them into the RX
 *        buffers simultaneously.
 *
 *    \snippet qs_spi_master_vec_basic.c start_transception
 * -# Wait for transfer to complete.
 *
 *    \snippet qs_spi_master_vec_basic.c wait_transception
 *//*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
