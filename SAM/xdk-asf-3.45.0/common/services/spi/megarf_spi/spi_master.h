/**
 * \file
 *
 * \brief SPI master driver definition for megaRF.
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

#ifndef _SPI_MASTER_H_
#define _SPI_MASTER_H_

#include "compiler.h"
#include "status_codes.h"
#include "ioport.h"
#include "spi_megarf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup spi_master_megarf MEGARF SPI master service.
 *
 * This is the API for SPI master service on MEGARF.
 *
 * @{
 *
 * \section spi_master_megarf_qucikstart_section Quick Start Guide
 * See \ref common_spi_master_quickstart
 */

/*! \name Spi Master Management Configuration
 */
/* ! @{ */
#include "conf_spi_master.h"

/* ! Default Config Spi Master Dummy Field */
#ifndef CONFIG_SPI_MASTER_DUMMY
#define CONFIG_SPI_MASTER_DUMMY              0xFF
#endif
/* ! @} */

/**
 * \brief Clock phase
 */
#define SPI_CPHA        (1 << 0)

/**
 * \brief Clock polarity
 */
#define SPI_CPOL        (1 << 1)

/**
 * \brief SPI mode 0
 */
#define SPI_MODE_0      0

/**
 * \brief SPI mode 1
 */
#define SPI_MODE_1      (SPI_CPHA)

/**
 * \brief SPI mode 2
 */
#define SPI_MODE_2      (SPI_CPOL)

/**
 * \brief SPI mode 3
 */
#define SPI_MODE_3      (SPI_CPOL | SPI_CPHA)

typedef uint8_t spi_flags_t;
typedef uint32_t board_spi_select_id_t;

/* \brief Polled SPI device definition */
struct spi_device {
	/* ! Board specific select id */
	port_pin_t id;
};

/**
 * \brief Initializes the SPI in master mode.
 *
 * \param spi Base address of the SPI instance.
 *
 */
extern void spi_master_init(volatile void *spi);

/**
 * \brief Setup a SPI device.
 *
 * The returned device descriptor structure must be passed to the driver
 * whenever that device should be used as current slave device.
 *
 * \param spi Base address of the SPI instance.
 * \param device    Pointer to SPI device struct that should be initialized.
 * \param flags     SPI configuration flags. Common flags for all
 *                  implementations are the SPI modes SPI_MODE_0 ...
 *                  SPI_MODE_3.
 * \param baud_rate Divider for Baud rate setting.
 * \param sel_id    Board specific select id
 */
extern void spi_master_setup_device(volatile void *spi,
		struct spi_device *device,
		spi_flags_t flags, unsigned long baud_rate,
		board_spi_select_id_t sel_id);

/**
 * \brief Select given device on the SPI bus
 *
 * Set device specific setting and calls board chip select.
 *
 * \param spi Base address of the SPI instance.
 * \param device SPI device
 *
 */
extern void spi_select_device(volatile void *spi, struct spi_device *device);

/**
 * \brief Deselect given device on the SPI bus
 *
 * Calls board chip deselect.
 *
 * \param spi Base address of the SPI instance.
 * \param device SPI device
 */
extern void spi_deselect_device(volatile void *spi, struct spi_device *device);

/**
 * \brief Send a sequence of bytes to a SPI device
 *
 * Received bytes on the SPI bus are discarded.
 *
 * \param spi Base address of the SPI instance.
 * \param data   data buffer to write
 * \param len    Length of data
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
extern status_code_t spi_write_packet(volatile void *spi, const uint8_t *data,
		size_t len);

/**
 * \brief Receive a sequence of bytes from a SPI device
 *
 * All bytes sent out on SPI bus are sent as value 0.
 *
 * \param spi Base address of the SPI instance.
 * \param data   data buffer to read
 * \param len    Length of data
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
extern status_code_t spi_read_packet(volatile void *spi, uint8_t *data,
		size_t len);

/**
 * \brief Receive one byte from a SPI device.
 *
 * \param spi Base address of the SPI instance.
 * \param data Pointer to the data byte where to store the received data.
 *
 */
inline static void spi_read_single(volatile void *spi, uint8_t *data)
{
	*data = spi_get(spi);
}

/**
 * \brief Write one byte to a SPI device.
 *
 * \param spi Base address of the SPI instance.
 * \param data The data byte to be loaded
 *
 */
__always_inline static void spi_write_single(volatile void *spi, uint8_t data)
{
	spi_put(spi, data);
}

/**
 * \brief Checks if all transmissions are complete.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval 1  All transmissions complete.
 *   \retval 0  Transmissions not complete.
 */
inline static bool spi_is_tx_empty(volatile void *spi)
{
	return spi_is_tx_ok(spi);
}

/**
 * \brief Checks if all transmissions is ready.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval 1  All transmissions complete.
 *   \retval 0  Transmissions not complete.
 */
inline static bool spi_is_tx_ready(volatile void *spi)
{
	return spi_is_tx_ok(spi);
}

/**
 * \brief Tests if the SPI contains a received character.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI Receive Holding Register is full, otherwise \c 0.
 */
inline static bool spi_is_rx_full(volatile void *spi)
{
	return spi_is_tx_ok(spi);
}

/**
 * \brief Checks if all reception is ready.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI Receiver is ready, otherwise \c 0.
 */
inline static bool spi_is_rx_ready(volatile void *spi)
{
	return spi_is_tx_ok(spi);
}

/* ! @} */

#ifdef __cplusplus
}
#endif

/**
 * \page spi_master_megarf Quick start guide for SPI master on MEGARF devices
 *
 * \section spi_master_megarf_basic Basic setup for MEGARF devices
 * The SPI module will be set up as master:
 *  - SPI on PORTB
 *  - FOSC/16 as SPI clock speed
 *  - Slave Chip Select connected on PORTB pin 0
 *  - SPI mode 0 (data on rising clock edge)
 *
 * \section  spi_master_megarf_basic_setup Setup steps
 * \subsection spi_master_megarf_basic_setup_code Example code
 * Add to application C-file (e.g. main.c):
 * \code
	  #define SPI_SCK       IOPORT_CREATE_PIN(PORTB, 1)
	  #define SPI_MOSI      IOPORT_CREATE_PIN(PORTB, 2)
	  #define SPI_MISO      IOPORT_CREATE_PIN(PORTB, 3)
	  #define SPI_SS        IOPORT_CREATE_PIN(PORTB, 0)

	   void spi_init_pins(void)
	   {
	       gpio_configure_pin(SPI_SCK, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	       gpio_configure_pin(SPI_MOSI, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	       gpio_configure_pin(SPI_MISO, IOPORT_DIR_INPUT);
	       gpio_configure_pin(SPI_SS, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	   }

	   void spi_init_module(void)
	   {
	      struct spi_device spi_device_conf = {
	          .id = IOPORT_CREATE_PIN(PORTB, 0)
	      };

	      spi_master_init(&SPCR);
	      spi_master_setup_device(&SPCR, &spi_device_conf, SPI_MODE_0,
	        1000000,0);
	      spi_enable(&SPCR);
	   }
\endcode
 *
 * \subsection spi_master_megarf_basic_setup Workflow
 * -# Ensure that \ref conf_spi_master.h is present for the driver.
 *  - \note This file is only for the driver and should not be included by the
 * user. In this example the file can be left empty.
 * -# Initialize the pins used by the SPI interface (this initialization is for
 * the ATmega128rfa1 device).
 * -# Define the pins used by the SPI interface
 *  - \code
	#define SPI_SCK       IOPORT_CREATE_PIN(PORTB, 1)
	#define SPI_MOSI      IOPORT_CREATE_PIN(PORTB, 2)
	#define SPI_MISO      IOPORT_CREATE_PIN(PORTB, 3)
	#define SPI_SS        IOPORT_CREATE_PIN(PORTB, 0)
\endcode
 *  -# Set the pin used for slave select as output high:
 *    \code
	ioport_configure_port_pin(SPI_SS, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
\endcode
 *  -# Set MOSI and SCL as output high, and set MISO as input:
 *    \code
	ioport_configure_port_pin(SPI_SCK, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(SPI_MOSI, IOPORT_INIT_HIGH | IOPORT_DIR_OUTPUT);
	ioport_configure_port_pin(SPI_MISO, IOPORT_DIR_INPUT);
\endcode
 * -# Define the SPI device configuration struct to describe which pin the
 * slave select (slave chip select) is connected to, in this case the slave
 * select pin has been connected to PORTB pin 0 (PB0):
 *  - \code
	struct spi_device spi_device_conf = {
	    .id = IOPORT_CREATE_PIN(PORTB, 0)
	};
\endcode
 * -# Initialize the SPI module:
 *  - \code
	spi_master_init(&SPCR);
\endcode
 * -# Setup the SPI master module for a specific device:
 *  - \code
	spi_master_setup_device(&SPCR, &spi_device_conf, SPI_MODE_0, 1000000, 0);
\endcode
 *  - \note The last argument, which is zero in this case, can be ignored and is
 *  only included for compatibility purposes.
 * -# Then enable the SPI:
 *  - \code
	spi_enable(&SPCR);
\endcode
 *
 * \section spi_master_megarf_basic_usage Usage steps
 * \subsection spi_master_megarf_basic_usage_code Example code
 * Add to, e.g., the main loop in the application C-file:
 * \code
	   uint8_t data_buffer[1] = {0xD7};

	   struct spi_device spi_device_conf = {
	       .id = IOPORT_CREATE_PIN(PORTB, 0)
	   };

	   spi_select_device(&SPCR, &spi_device_conf);

	   spi_write_packet(&SPCR, data_buffer, 1);
	   spi_read_packet(&SPCR, data_buffer, 1);

	   spi_deselect_device(&SPCR, &spi_device_conf);
\endcode
 *
 * \subsection spi_master_megarf_basic_usage_flow Workflow
 * -# Create a buffer for data to be sent/received on the SPI bus, in this case
 * a single byte buffer is used. The buffer can be of arbitrary size as long as
 * there is space left in SRAM:
 *  - \code
	uint8_t data_buffer[1] = {0xD7};
\endcode
 * -# Define the SPI device configuration struct to describe which pin the
 * slave select (slave chip select) is connected to, in this case the slave
 * select pin has been connected to PORTB pin01 (PB0):
 *  - \code
	struct spi_device spi_device_conf = {
	    .id = IOPORT_CREATE_PIN(PORTB, 0)
	};
\endcode
 *  - \note As this struct is the same for both the initializing part and the
 *usage
 * part it could be a good idea to make the struct global, and hence accessible
 * for both the initializing part and usage part. Another solution could be to
 * create the struct in the main function and pass the address of the struct to
 * the spi_init_module() function, e.g.:
 *  \code
	   void spi_init_module(struct spi_device *spi_device_conf)
	   {
	       ...

	       spi_master_setup_device(&SPCR, spi_device_conf, SPI_MODE_0, 
	       1000000, 0);

	       ...
	   }
\endcode
 * -# Write data to the SPI slave device, in this case write one byte from the
 * data_buffer:
 *  - \code
	spi_write_packet(&SPCR, data_buffer, 1);
\endcode
 * -# Read data from the SPI slave device, in this case read one byte and put it
 * into the data_buffer:
 *  - \code
	spi_read_packet(&SPCR, data_buffer, 1);
\endcode
 *  - \attention As the SPI works as a shift register so that data is shifted in
 * at the same time as data is shifted out a read operation will mean that a dummy
 * byte \ref CONFIG_SPI_MASTER_DUMMY is written to the SPI bus. \ref
 *  CONFIG_SPI_MASTER_DUMMY
 * defaults to 0xFF, but can be changed by defining it inside the \ref
 * conf_spi_master.h file.
 * -# When read and write operations is done de-select the slave:
 *  - \code
	spi_deselect_device(&SPCR, &spi_device_conf);
\endcode
 *
 */

#endif  /* _SPI_MASTER_H_ */
