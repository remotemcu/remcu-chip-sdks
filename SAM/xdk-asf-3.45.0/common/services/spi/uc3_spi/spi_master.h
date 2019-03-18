/*****************************************************************************
 *
 * \file
 *
 * \brief SPI Master driver for AVR UC3.
 *
 * This file defines a useful set of functions for the SPI interface on AVR UC3
 * devices.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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
 ******************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#ifndef _SPI_MASTER_H_
#define _SPI_MASTER_H_

#include "compiler.h"
#include "sysclk.h"
#include "status_codes.h"
#include "spi.h"

/*! \name Spi Master Management Configuration
 */
//! @{
#include "conf_spi_master.h"

//! Default Config Spi Master Delay BCS
#ifndef CONFIG_SPI_MASTER_DELAY_BCS
#define CONFIG_SPI_MASTER_DELAY_BCS                  0
#endif

//! Default Config Spi Master Bits per Transfer Definition
#ifndef CONFIG_SPI_MASTER_BITS_PER_TRANSFER
#define CONFIG_SPI_MASTER_BITS_PER_TRANSFER          8
#endif

//! Default Config Spi Master Delay BCT
#ifndef CONFIG_SPI_MASTER_DELAY_BCT
#define CONFIG_SPI_MASTER_DELAY_BCT                  0
#endif

//! Default Config Spi Master Delay BS
#ifndef CONFIG_SPI_MASTER_DELAY_BS
#define CONFIG_SPI_MASTER_DELAY_BS                   0
#endif

//! Default Config Spi Master Dummy Field
#ifndef CONFIG_SPI_MASTER_DUMMY
#define CONFIG_SPI_MASTER_DUMMY                      0xFF
#endif
//! @}

//! Spi Flags definition
typedef uint8_t spi_flags_t;

//! Board Spi Select Id Definition
typedef uint8_t board_spi_select_id_t;

//! \brief Polled SPI device definition
struct spi_device {
	//! Board specific select id
	board_spi_select_id_t	id;
};

/*! \brief Initializes the SPI in master mode.
 *
 * \param spi       Base address of the SPI instance.
 *
 */
static inline void spi_master_init(volatile avr32_spi_t *spi)
{
#ifdef AVR32_SPI
	sysclk_enable_pba_module(SYSCLK_SPI);
#else
	if ((uint32_t)spi == AVR32_SPI0_ADDRESS) {
#if UC3C
	sysclk_enable_pbc_module(SYSCLK_SPI0);
#else
	sysclk_enable_pba_module(SYSCLK_SPI0);
#endif
	}
#ifdef AVR32_SPI1
	else if ((uint32_t)spi == AVR32_SPI1_ADDRESS) {
	sysclk_enable_pba_module(SYSCLK_SPI1);
	}
#endif
#endif

	spi_reset(spi);
	spi_set_master_mode(spi);
	spi_disable_modfault(spi);
	spi_disable_loopback(spi);
	spi_set_chipselect(spi,(1 << AVR32_SPI_MR_PCS_SIZE) - 1);
	spi_disable_variable_chipselect(spi);
	spi_disable_chipselect_decoding(spi);
	spi_set_delay(spi,CONFIG_SPI_MASTER_DELAY_BCS);
}

/**
 * \brief Setup a SPI device.
 *
 * The returned device descriptor structure must be passed to the driver
 * whenever that device should be used as current slave device.
 *
 * \param spi       Base address of the SPI instance.
 * \param device    Pointer to SPI device struct that should be initialized.
 * \param flags     SPI configuration flags. Common flags for all
 *                  implementations are the SPI modes SPI_MODE_0 ...
 *                  SPI_MODE_3.
 * \param baud_rate Baud rate for communication with slave device in Hz.
 * \param sel_id    Board specific select id
 */
extern void spi_master_setup_device(volatile avr32_spi_t *spi,
		struct spi_device *device, spi_flags_t flags, uint32_t baud_rate,
		board_spi_select_id_t sel_id);

/*! \brief Enables the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
extern void spi_enable(volatile avr32_spi_t *spi);

/*! \brief Disables the SPI.
 *
 * Ensures that nothing is transferred while setting up buffers.
 *
 * \param spi Base address of the SPI instance.
 *
 * \warning This may cause data loss if used on a slave SPI.
 */
extern void spi_disable(volatile avr32_spi_t *spi);

/*! \brief Tests if the SPI is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c true if the SPI is enabled, otherwise \c false.
 */
extern bool spi_is_enabled(volatile avr32_spi_t *spi);

/**
 * \brief Select given device on the SPI bus
 *
 * Set device specific setting and calls board chip select.
 *
 * \param spi Base address of the SPI instance.
 * \param device SPI device
 *
 */
static inline void spi_select_device(volatile avr32_spi_t *spi,
		struct spi_device *device)
{
	spi_selectChip(spi,device->id);
}

/**
 * \brief Deselect given device on the SPI bus
 *
 * Calls board chip deselect.
 *
 * \param spi Base address of the SPI instance.
 * \param device SPI device
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
static inline void spi_deselect_device(volatile avr32_spi_t *spi,
		struct spi_device *device)
{
	spi_unselectChip(spi,device->id);
}

/*! \brief Write one byte to a SPI device.
 *
 * \param spi    Base address of the SPI instance.
 * \param data   Data to write
 *
 */
static inline void spi_write_single(volatile avr32_spi_t *spi, uint8_t data)
{
	spi_put(spi,(uint16_t)data);
}

/**
 * \brief Send a sequence of bytes to a SPI device
 *
 * Received bytes on the SPI bus are discarded.
 *
 * \param spi    Base address of the SPI instance.
 * \param data   Data buffer to write
 * \param len    Length of data
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
extern status_code_t spi_write_packet(volatile avr32_spi_t *spi,
		const uint8_t *data, size_t len);

/*! \brief Receive one byte from a SPI device.
 *
 * \param spi    Base address of the SPI instance.
 * \param data   Data to read
 *
 */
static inline void spi_read_single(volatile avr32_spi_t *spi, uint8_t *data)
{
	*data = (uint8_t)spi_get(spi);
}

/**
 * \brief Receive a sequence of bytes from a SPI device
 *
 * All bytes sent out on SPI bus are sent as value 0.
 *
 * \param spi    Base address of the SPI instance.
 * \param data   Data buffer to read
 * \param len    Length of data
 *
 * \pre SPI device must be selected with spi_select_device() first
 */
extern status_code_t spi_read_packet(volatile avr32_spi_t *spi,
		uint8_t *data, size_t len);

/*! \brief Checks if all transmissions are complete.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval 1  All transmissions complete.
 *   \retval 0  Transmissions not complete.
 */
extern bool spi_is_tx_empty(volatile avr32_spi_t *spi);

/*! \brief Checks if all transmissions is ready.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return Status.
 *   \retval 1  All transmissions complete.
 *   \retval 0  Transmissions not complete.
 */
extern bool spi_is_tx_ready(volatile avr32_spi_t *spi);

/*! \brief Check if the SPI contains a received character.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI Receive Holding Register is full, otherwise \c 0.
 */
extern bool spi_is_rx_full(volatile avr32_spi_t *spi);

/*! \brief Checks if all reception is ready.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 1 if the SPI Receiver is ready, otherwise \c 0.
 */
extern bool spi_is_rx_ready(volatile avr32_spi_t *spi);


/**
 * \page spi_master_uc3 Quick start guide for SPI master on UC3 devices
 *
 * \section spi_master_uc3_basic Basic setup for UC3 devices
 * The SPI module will be set up as master:
 *  - SPI on module SPI0
 *  - 1MHz SPI clock speed
 *  - Slave Chip Select connected on NPCS1
 *  - 8 bits per transfer
 *  - SPI mode 0 (data on rising clock edge)
 *
 * \section   spi_master_uc3_basic_setup Setup steps
 * \subsection spi_master_uc3_basic_setup_code Example code
 * Add to application C-file (e.g. main.c):  
 * \code
	#define SPI_EXAMPLE             (&AVR32_SPI0)
	struct spi_device spi_device_conf = {
	    .id = 1
	};

	void spi_init_module(void)
	{
	  //Init SPI module as master
	  spi_master_init(SPI_EXAMPLE);
	  //Setup parameters for the slave device
	  spi_master_setup_device(SPI_EXAMPLE, &spi_device_conf, SPI_MODE_0, 1000000, 0);
	  //Allow the module to transfer data
	  spi_enable(SPI_EXAMPLE);
	}
\endcode 
 * \subsection spi_master_uc3_basic_setup Workflow
 * -# Ensure that board_init() has configured selected I/Os for SPI function.
 * -# Ensure that \ref conf_spi_master.h is present for the driver.
 *  - \note This file is only for the driver and should not be included by the
 * user. In this example, the file can be left empty.
 * -# Define an alias for the SPI module you want to use :
 * \code
	#define SPI_EXAMPLE             (&AVR32_SPI0)
\endcode 
 * -# Create the structure for the device id (Chip select)
 * \code
	struct spi_device spi_device_conf = {
	    .id = 1
	};
\endcode 
 *  - \note As this struct is the same for both the initializing part and the usage
 * part it could be a good idea to make the struct global, and hence accessible
 * for both the initializing part and usage part. 
 * -# Write the initialization function to setup the module :
 * \code 
	void spi_init_module(void)
	{
	   //Init SPI module as master
	   spi_master_init(SPI_EXAMPLE); 
	   //Setup parameters for the slave device : id, mode, baudrate
	   spi_master_setup_device(SPI_EXAMPLE, &spi_device_conf, SPI_MODE_0, 1000000, 0);
	   //Allow the module to transfer data
	   spi_enable(SPI_EXAMPLE);
	}
\endcode
 *  - \note The last argument of spi_master_setup_device, which is zero in this 
 *  case, can be ignored and is only included for compatibility purposes.
 *
 * -# Call the initialization routine from your application.
 *  - \code
	spi_init_module();
\endcode
 *
 * \section spi_master_uc3_basic_usage Usage steps
 * \subsection spi_master_uc3_basic_usage_code Example code
 * Use in application C-file:
 * \code
	//Buffer to send data to SPI slave
	uint8_t txdata[1]={0xD7};
	//Buffer to receive data from SPI slave
	uint8_t rxdata[1];
	...
	 	// Select the slave device with chip select
	 	spi_select_device(SPI_EXAMPLE,&spi_device_conf);
	 	// Send the data to slave
	 	spi_write_packet(SPI_EXAMPLE, txdata, 1);
	 	// Read data from slave
	 	spi_read_packet(SPI_EXAMPLE, rxdata,1);
	 	// Deselect the slave
	 	spi_deselect_device(SPI_EXAMPLE,&spi_device_conf);
\endcode
 *
 * \subsection spi_master_uc3_basic_usage_flow Workflow
 * -# Create two buffers for data to be sent/received on the SPI bus, 
 * The buffer can be of arbitrary size as long as there is space left in SRAM:
 *  - \code
	//Buffer to send data to SPI slave
	uint8_t txdata[1]={0xD7};
	//Buffer to receive data from SPI slave
	uint8_t rxdata[1];
\endcode
 *  - \note In this case, we have set a default value for the txdata which is 
 * a status read command to a spi memory chip.
 * -# Call the spi_select_device routine to enable the chip select line for 
 * the slave you want to communicate with.
 * The chip select enabled is defined by the value of the id field in the 
 * spi_device_conf struct
 * \code
	spi_select_device(SPI_EXAMPLE,&spi_device_conf);
\endcode
 * -# Write data to the SPI slave device, in this case write one byte from the
 * data buffer txdata:
 *  - \code
	spi_write_packet(SPI_EXAMPLE, txdata, 1);
\endcode
 * -# Read data from the SPI slave device, in this case read one byte and put it
 * into the data buffer rxdata:
 *  - \code
	spi_read_packet(SPI_EXAMPLE, rxdata,1);
\endcode
 *  - \attention As the SPI works as a shift register so that data is shifted in at
 * the same time as data is shifted out a read operation will mean that a dummy
 * byte \ref CONFIG_SPI_MASTER_DUMMY is written to the SPI bus. \ref CONFIG_SPI_MASTER_DUMMY
 * defaults to 0xFF, but can be changed by defining it inside the \ref conf_spi_master.h
 * file.
 * -# When read and write operations is done, de-select the slave:
 *  - \code
	spi_deselect_device(SPI_EXAMPLE,&spi_device_conf);
\endcode
 * -# Now you can use the data read from the slave which is in rxdata
 *  - \code
	//Check read content
	if(rxdata[0]<0x3C)
	  do_something();
\endcode
 */

#endif  // _SPI_MASTER_H_
