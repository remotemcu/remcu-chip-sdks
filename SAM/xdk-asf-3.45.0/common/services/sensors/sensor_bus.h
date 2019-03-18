/**
 * \file
 *
 * \brief Sensor API Platform Bus Interfaces
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

#ifndef _SENSOR_BUS_H_
#define _SENSOR_BUS_H_

#include <status_codes.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \brief Platform Bus Type Constants */
typedef enum {
	BUS_TYPE_UNKNOWN,                   /**< Unknown bus */
	BUS_TYPE_TWI,                       /**< TWI/I2C bus */
	BUS_TYPE_SPI,                       /**< SPI bus */
	BUS_TYPE_PMBUS,                     /**< PMBus protocol */
	BUS_TYPE_SMBUS                      /**< SMBus protocol */
} bus_type_t;

/** \brief Platform Bus Status Constants */
typedef status_code_t bus_status_t;

/** \internal Platform Bus Interface Types */

#if UC3
typedef volatile avr32_spi_t *spi_if;
#else
typedef SPI_t *spi_if;
#endif

/** \brief Platform Bus Interface Descriptor */
typedef struct {
	bus_type_t type;                    /**< Bus type and protocol */
	volatile void *id;                  /**< Bus interface address */
	uint16_t addr;                      /**< Device bus address */
	bus_status_t status;                /**< Bus transaction status */
	bool no_wait;                       /**< Bus transaction non-wait option */
} bus_desc_t;

/** \name System Bus I/O Access Methods */
/** @{ */

/** \internal Initialize the bus I/O interface.
 *
 * \param   busif   The address of a system bus (registers) interface.
 * \param   speed   The bus data rate.
 *
 * \retval  true    The bus was initialized.
 * \retval  false   The bus was not initialized.
 */
bool bus_init(volatile void *busif, uint32_t speed);

/** \brief Read multiple Bytes from a bus interface.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The destination read buffer address.
 * \param   count   The destination read buffer size (Bytes).
 *
 * \return The number of Bytes read, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t bus_read(bus_desc_t *bus, uint8_t addr, void *data, size_t count);

/** \brief Write multiple Bytes to a bus interface.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The source write buffer address.
 * \param   count   The source write buffer size (Bytes).
 *
 * \return The number of Bytes written, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t bus_write(bus_desc_t *bus, uint8_t addr, const void *data, size_t count);

/** \brief Determine the existence of a bus device
 *
 * This routine determines the existence of a device located at a bus interface
 * and address specified by an initialized \c bus descriptor.
 * Implementations are only required to return \c true when it can be determined
 * that a device is installed at the bus interface address.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   arg     Ignored reserved argument.
 *
 * \retval  true    A device responded to the bus address.
 * \retval  false   A device did not respond to the bus address.
 */
bool bus_probe(bus_desc_t *bus, int arg);

/** \brief Read a single Byte from a bus interface.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 *
 * \return A value fetched from the device.  This value is
 *         undefined in the event of an I/O error.
 */
static inline uint8_t bus_get(bus_desc_t *bus, uint8_t addr)
{
	uint8_t data = 0;
	bus_read(bus, addr, &data, sizeof(uint8_t));

	return data;
}

/** \brief Write a single Byte to a bus interface.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The value of the Byte to write.
 *
 * \return  Nothing
 */
static inline void bus_put(bus_desc_t *bus, uint8_t addr, uint8_t data)
{
	bus_write(bus, addr, &data, sizeof(uint8_t));
}

/** \brief Clear a bit at a bus device register or memory address.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   mask    The mask value of the bit to clear.
 *
 * \return  Nothing
 */
static inline void bus_reg_bitclear(bus_desc_t *bus, uint8_t addr,
		uint8_t mask)
{
	bus_put(bus, addr, ~mask & bus_get(bus, addr));
}

/** \brief Set a bit at a bus device register or memory address.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   mask    The mask value of the bit to set.
 *
 * \return  Nothing
 */
static inline void bus_reg_bitset(bus_desc_t *bus, uint8_t addr, uint8_t mask)
{
	bus_put(bus, addr, mask | bus_get(bus, addr));
}

/** \brief Read a field stored at a device register or memory address
 *
 * This routine reads a specified value from a bit field within a 1-Byte
 * device register or memory address. The set bits in the mask parameter
 * determine the field location. For example, if the mask is 30h and the
 * value AFh is stored in the register, the value 2h will be returned.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   mask    The mask of the field to set.
 *
 * \return  The value stored in the register or memory field.
 */
uint8_t bus_reg_fieldget(bus_desc_t *bus, uint8_t addr, uint8_t mask);

/** \brief Write a field stored at a device register or memory address
 *
 * This routine writes a specified value to a bit field within a 1-Byte
 * device register or memory address. The set bits in the mask parameter
 * determine the field location. For example, if the mask is 30h and the
 * value is 2h, the value 20h will be bitwise logically OR'd into the
 * 1-Byte register value after clearing the bit values in the field.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   mask    The mask of the field to set.
 * \param   value   The value of the field to set.
 *
 * \return  Nothing
 */
void bus_reg_fieldset(bus_desc_t *bus, uint8_t addr, uint8_t mask,
		uint8_t value);

/** @} */

#ifdef __cplusplus
}
#endif

#endif
