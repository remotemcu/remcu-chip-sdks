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

#include <asf.h>

/** \internal Sensor Platform Board Configuration */
#include "conf_sensors.h"
#include "sensor_bus.h"

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
uint8_t bus_reg_fieldget(bus_desc_t *bus, uint8_t addr, uint8_t mask)
{
	uint8_t const value = mask & bus_get(bus, addr);
	return (value / (mask & ~(mask << 1)));
}

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
		uint8_t value)
{
	uint8_t const reg = ~mask &bus_get(bus, addr);

	value *= (mask & ~(mask << 1));
	bus_put(bus, addr, reg | (value & mask));
}

/** \internal Sensor API Bus I/O Implementations */

#if defined(CONF_SENSOR_BUS_SPI)

#define spi_bus_init    bus_init
#define spi_bus_read    bus_read
#define spi_bus_write   bus_write
#define spi_bus_probe   bus_probe

/** \internal Initialize the SPI master bus I/O interface.
 *
 * \param   bus        The address of an AVR or AVR32 bus interface descriptor.
 * \param   bus_speed  The bus data rate.
 *
 * \retval  true       The bus was initialized.
 * \retval  false      The bus was not initialized.
 */
bool spi_bus_init(volatile void *bus, uint32_t bus_speed)
{
	spi_if const spi = (spi_if)bus;
	struct spi_device device;

	/* Initialize the Atmel Software Framework SPI master driver. */

	spi_master_init(spi);
	spi_master_setup_device(spi, &device, SPI_MODE_0, bus_speed, 0);
	spi_enable(spi);

	return spi_is_enabled(spi);
}

/** \internal Read bytes from remote device using SPI (master) interface
 *
 * This routine reads "count" Bytes of data into location "data" from
 * a specified SPI "bus_id" device register or memory address, "addr".
 *
 * The caller must ensure that "data" specifies a valid memory address
 * that is capable of storing the specified "count" Bytes of data.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The destination read buffer address.
 * \param   count   The destination read buffer size (Bytes).
 *
 * \return The number of Bytes read, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t spi_bus_read
	(bus_desc_t *bus, uint8_t addr, void *data, size_t count)
{
	spi_if const spi = (spi_if)bus->id;
	struct spi_device device = { .id = bus->addr };

	spi_select_device(spi, &device);
	bus->status = spi_read_packet(spi, data, count);
	spi_deselect_device(spi, &device);

	return (STATUS_OK == bus->status) ? count : 0;
}

/** \internal Write bytes to remote device using SPI (master) interface
 *
 * This routine writes "count" Bytes of data from location "data" to
 * a specified SPI "bus_id" device register or memory address, "addr".
 *
 * The caller must ensure that "data" specifies a valid memory address.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The source write buffer address.
 * \param   count   The source write buffer size (Bytes).
 *
 * \return The number of Bytes written, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t spi_bus_write
	(bus_desc_t *bus, uint8_t addr, const void *data, size_t count)
{
	spi_if const spi = (spi_if)bus->id;
	struct spi_device device = { .id = bus->addr };

	spi_select_device(spi, &device);
	bus->status = spi_write_packet(spi, data, count);
	spi_deselect_device(spi, &device);

	return (STATUS_OK == bus->status) ? count : 0;
}

/** \internal Determine the existence of a bus device
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
bool spi_bus_probe(bus_desc_t *bus, int arg)
{
	bus->status = ERR_UNSUPPORTED_DEV;
	return false;
}

#endif /* defined(CONF_SENSOR_BUS_SPI) */

#if defined(CONF_SENSOR_BUS_TWI)

#define twi_bus_init    bus_init
#define twi_bus_read    bus_read
#define twi_bus_write   bus_write
#define twi_bus_probe   bus_probe

/** \internal Initialize the TWI (master) bus I/O interface.
 *
 * \param   bus        The address of an AVR or AVR32 bus interface descriptor.
 * \param   bus_speed  The bus data rate.
 *
 * \retval  true       The bus was initialized.
 * \retval  false      The bus was not initialized.
 */
bool twi_bus_init(volatile void *bus, uint32_t bus_speed)
{
	twi_master_t const twi = (twi_master_t)bus;

	/* Specify TWI master bus configuration options. */

	twi_options_t twi_options = { .speed = bus_speed, .chip = 0 };

	/* Initialize the Atmel Software Framework TWI master driver. */

	return (STATUS_OK == twi_master_setup(twi, &twi_options));
}

/** \internal Read bytes from remote device using TWI (master) interface
 *
 * This routine reads "count" Bytes of data into location "data" from
 * a specified TWI "bus_id" device register or memory address, "addr".
 *
 * The caller must ensure that "data" specifies a valid memory address
 * that is capable of storing the specified "count" Bytes of data.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The destination read buffer address.
 * \param   count   The destination read buffer size (Bytes).
 *
 * \return The number of Bytes read, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t twi_bus_read
	(bus_desc_t *bus, uint8_t addr, void *data, size_t count)
{
	twi_package_t const pkg = {
		.chip        = bus->addr,
		.addr        = {addr},
		.addr_length = sizeof(addr),
		.buffer      = data,
		.length      = count,
		.no_wait     = bus->no_wait
	};

	bus->status = twi_master_read((twi_master_t)(bus->id), &pkg);
	return (STATUS_OK == bus->status) ? count : 0;
}

/** \internal Write bytes to remote device using TWI (master) interface
 *
 * This routine writes "count" Bytes of data from location "data" to
 * a specified TWI "bus_id" device register or memory address, "addr".
 *
 * The caller must ensure that "data" specifies a valid memory address.
 *
 * \param   bus     An initialized bus interface descriptor.
 * \param   addr    The device register or memory address.
 * \param   data    The source write buffer address.
 * \param   count   The source write buffer size (Bytes).
 *
 * \return The number of Bytes written, which may be less than the
 *         requested number of Bytes in the event of an error.
 */
size_t twi_bus_write(bus_desc_t *bus, uint8_t addr, const void *data,
		size_t count)
{
	twi_package_t const pkg = {
		.chip        = bus->addr,
		.addr        = {addr},
		.addr_length = sizeof(addr),
		.buffer      = (void *)data,
		.length      = count,
		.no_wait     = bus->no_wait
	};

	bus->status = twi_master_write((twi_master_t)(bus->id), &pkg);
	return (STATUS_OK == bus->status) ? count : 0;
}

/** \internal Determine the existence of a bus device
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
bool twi_bus_probe(bus_desc_t *bus, int arg)
{
	bus->status = ERR_UNSUPPORTED_DEV;
	return false;
}

#endif /* defined(CONF_SENSOR_BUS_TWI) */
