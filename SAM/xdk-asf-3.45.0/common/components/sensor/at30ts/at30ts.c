/**
 * \file
 *
 * \brief Management of the AT30TS Temperature Sensor component.
 *
 * This file contains definitions and services related to the features of the
 * AT30TS Temperature Sensor.
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

#include "at30ts.h"

const uint8_t copy_vol_nonvol_register[]        = { CPY_VOL_NVOL_REG };
const uint8_t copy_nonvol_vol_register[]        = { CPY_NVOL_VOL_REG };
const uint8_t nv_config[]                       = { NV_CONFIG_REG };

static ts_device_t at30ts_attached_device;
static uint8_t at30ts_status;
static uint8_t at30ts_iobuf[3];

#define valtobuf(val, buf) {     buf[2] = (val) & 0xFF;	\
				 buf[1] = ((val) >> 8) & 0xFF; }

#define buftoval(val, buf) {     (val) = (at30ts_iobuf[0]); \
				 (val) <<= 8; \
				 (val) |= (at30ts_iobuf[1]); }

/**
 * \brief ACK polling function
 *
 * \param addr device address to ACK poll
 * \return AT30TS_SUCCESS if all bytes were read, otherwise error code:
 * AT30TS_TWI_WRITE_NACK
 */

int8_t ts_ack_polling(uint8_t addr)
{
	uint16_t n = ACK_POLLING_ITERATION;

	do {
		/* Perform a write access & check write result */
		if (twi_probe_device(addr) == TWI_SUCCESS) {
			return AT30TS_SUCCESS;
		}
	} while (--n);

	return AT30TS_TWI_WRITE_NACK;
}

/**
 * \brief attach_device, initialize epprom variable associcated with device
 *
 * \param device_addr  device address register offset address
 * \param type         device type
 * \return none
 */
void attach_device(uint8_t device_addr, device_type_t type)
{
	at30ts_attached_device.ts_reg_addr = device_addr;
	at30ts_attached_device.device_type = type;

	switch (type) {
	case AT30TS75:
	case AT30TS750:
		at30ts_attached_device.eeprom_size = 0;
		break;

	case AT30TSE002B:
	case AT30TSE752:
		at30ts_attached_device.eeprom_size = 256;
		break;

	case AT30TSE754:
		at30ts_attached_device.eeprom_size = 512;
		break;

	case AT30TSE758:
		at30ts_attached_device.eeprom_size = 1024;
		break;

	default:
		at30ts_attached_device.eeprom_size = 0;
		break;
	}
}

/**
 * \brief Write configuration register
 *
 * \param *obuf Package information and data
 * \return TWI_SUCCESS if all bytes were written, error code otherwise
 */
int8_t ts_write_register(uint8_t *obuf)
{
	twi_package_t packet;
	uint8_t nonvolatile_regs
		= ((obuf[0] == NV_CONFIG_REG) || (obuf[0] == NV_TLOLIM_REG) ||
			(obuf[0] == NV_THILIM_REG));
	uint8_t nv_regs_supported
		= (at30ts_attached_device.device_type == AT30TS750) ||
			(at30ts_attached_device.device_type == AT30TSE758);

	/* Before writing nonvolatile registers,
	 * first check to see if NVRBSY is busy */
	if (nv_regs_supported && nonvolatile_regs) {
		if ((at30ts_status = check_NVRBSY()) !=  AT30TS_SUCCESS) {
			return at30ts_status;
		}
	}

	/* TWI chip address to communicate with */
	packet.chip         = at30ts_attached_device.ts_reg_addr;
	packet.addr_length  = 0x00;
	/* Data to be written */
	packet.buffer       = obuf;
	/* How many bytes do we want to write */
	packet.length       = 0x03;

	/* Perform a write access */
	at30ts_status = twi_write(&packet);

	if (at30ts_status != TWI_SUCCESS) {
		return AT30TS_TWI_WRITE_NACK;
	}

	if (nv_regs_supported && nonvolatile_regs) {
		/* Wait max time for nonvol write to complete */
		if (nonvolatile_regs) {
			at30ts_status |= check_NVRBSY();
		}
	}

	return at30ts_status;
}

/**
 * \brief Read at30ts75xx configuration register
 *
 * \param pointer_reg register offset address
 * \param *buf			store temperature data
 * \return TWI_SUCCESS if all bytes were read, error code otherwise
 */
int8_t ts_read_register(const uint8_t pointer_reg, uint8_t *buf)
{
	twi_package_t packet;

	/* TWI chip address to communicate with */
	packet.chip = at30ts_attached_device.ts_reg_addr;
	packet.addr_length = 0x00;

	/* To prevent warning pointer_reg being const */
	uint8_t reg = pointer_reg;
	packet.buffer = &reg;
	packet.length = 0x01;

	/* Perform a write access & check result */
	if (twi_write(&packet) != TWI_SUCCESS) {
		return AT30TS_TWI_WRITE_NACK;
	}

	/* How many bytes to read */
	packet.length = 0x02;
	/* Where to put the read data */
	packet.buffer = buf;

	/* Perform a read access & check result */
	if (twi_read(&packet) != TWI_SUCCESS) {
		return AT30TS_TWI_READ_NACK;
	}

	return TWI_SUCCESS;
}

/**
 * \brief Write EEPROM
 *
 * \param address      Data word address
 * \param size		   Size of the data to write
 * \param *buf		   Data to be written
 *
 * \return TWI_SUCCESS if all bytes were written, error code otherwise
 */
int8_t ts_write_eeprom(uint16_t address, uint16_t size, uint8_t *buf)
{
	twi_package_t packet;
	/* Page size for AT30TS is 16 */
	uint8_t data[16];
	/* Check for valid eeprom address */
	if ((address + size) > at30ts_attached_device.eeprom_size) {
		return AT30TS_INVALID_EEPROM_ADDRESS;
	}

	if (size > PAGE_SIZE) {
		return AT30TS_INVALID_SIZE;
	}

	ts_construct_eeprom_address(&packet, address);
	packet.addr[0] = address & 0xff;
	packet.addr_length = 0x01;
	memcpy(data, buf, size);
	packet.length = size;
	/* Data to be written */
	packet.buffer = data;
	/* Perform a write access */
	at30ts_status = twi_write(&packet);

	if (at30ts_status != TWI_SUCCESS) {
		return AT30TS_TWI_WRITE_NACK;
	}

	/* Wait for write cycle to complete (max 5ms) */
	at30ts_status |= ts_ack_polling(packet.chip);

	return at30ts_status;
}

/**
 * \brief Read EEPROM
 *
 * \param address     Data word address
 * \param size		  Size of the data to read
 * \param *buf		  Where to store the data
 * \return TWI_SUCCESS if all bytes were read, error code otherwise
 */
int8_t ts_read_eeprom(uint16_t address, uint16_t size, uint8_t *buf)
{
	twi_package_t packet;

	/* Check for valid eeprom address */
	if ((address + size) > at30ts_attached_device.eeprom_size) {
		return AT30TS_INVALID_EEPROM_ADDRESS;
	}

	ts_construct_eeprom_address(&packet, address);
	packet.addr[0] = address & 0xff;
	packet.addr_length = 0x01;
	packet.length = 0x00;

	/* Perform a write access & check result */
	at30ts_status = twi_write(&packet);
	if (at30ts_status != TWI_SUCCESS) {
		return AT30TS_TWI_WRITE_NACK;
	}

	/* How many bytes to read */
	packet.length = size;
	/* Where to put the read data */
	packet.buffer = buf;

	/* Perform a read access & check result */
	at30ts_status = twi_read(&packet);
	if (at30ts_status != TWI_SUCCESS) {
		return AT30TS_TWI_READ_NACK;
	}

	return TWI_SUCCESS;
}

/**
 * \brief Copy volatile registers to nonvolatile registers
 *
 * \return TWI_SUCCESS if copy was successful, error code otherwise
 */
int8_t ts75_copy_vol_nonvol_register()
{
	twi_package_t packet;

	/* TWI chip address to communicate with */
	packet.chip = at30ts_attached_device.ts_reg_addr;
	packet.addr_length = 0x00;
	/* Copy the command to the buffer */
	packet.buffer = (void *)copy_vol_nonvol_register;
	/* How many bytes do we want to write */
	packet.length = 0x01;

	/* Before writing nonvolatile registers,
	 * first check to see if NVRBSY is busy
	 */
	if ((at30ts_status = check_NVRBSY()) !=  AT30TS_SUCCESS) {
		return at30ts_status;
	}

	/* Perform a write access */
	at30ts_status = twi_write(&packet);
	if (at30ts_status != TWI_SUCCESS) {
		return AT30TS_TWI_WRITE_NACK;
	}

	at30ts_status |= check_NVRBSY();

	return at30ts_status;
}

/**
 * \brief Copy nonvolatile registers to volatile registers
 *
 * \return TWI_SUCCESS if copy was successful, error code otherwise
 */
int8_t ts75_copy_nonvol_vol_register()
{
	twi_package_t packet;

	/* TWI chip address to communicate with */
	packet.chip = at30ts_attached_device.ts_reg_addr;
	packet.addr_length = 0x00;
	/* Copy the command to the buffer */
	packet.buffer = (void *)copy_nonvol_vol_register;
	/* How many bytes do we want to write */
	packet.length = 0x01;

	/* Before writing nonvolatile registers,
	 * first check to see if NVRBSY is busy
	 */
	if ((at30ts_status = check_NVRBSY()) !=  AT30TS_SUCCESS) {
		return at30ts_status;
	}

	/* Perform a write access */
	at30ts_status = twi_write(&packet);
	if (at30ts_status != TWI_SUCCESS) {
		return AT30TS_TWI_WRITE_NACK;
	}

	return at30ts_status;
}

/** \brief Constructs an eeprom address.
 *
 * \param[in, out] packet pointer to packet structure
 * \param[in] address eeprom address
 */
void ts_construct_eeprom_address(twi_package_t *packet, uint16_t address)
{
	/* Serial eeprom address upper nibble */
	packet->chip = 0x50;

	if ((at30ts_attached_device.device_type == AT30TSE002B) | 
            (at30ts_attached_device.device_type == AT30TSE752)) {
		/* 256 Bytes of EEPROM */
		packet->chip |= (at30ts_attached_device.ts_reg_addr & 0x07);
	} else if (at30ts_attached_device.device_type == AT30TSE754) {
		/* 512 Bytes of EEPROM; Obtain A2 and A1 bits
		 * from device address
		 */
		packet->chip |= (at30ts_attached_device.ts_reg_addr & 0x06);
		/* obtain the page bit (P0): [101] [0 A2 A1 P0] */
		packet->chip |= ((address >> 8) & 0x01);
	} else if (at30ts_attached_device.device_type == AT30TSE758) {
		/* 1024 Bytes of EEPROM; Obtain A2 bit from device address*/
		packet->chip |= (at30ts_attached_device.ts_reg_addr & 0x04);
		/* obtain the page bits (P1, P0): [101] [0 A2 P1 P0] */
		packet->chip |= ((address >> 8) & 0x03);
	}
}

/**
 * \brief Probe at30ts75 nonvolatile configuration register
 *
 * \param device_addr   at30ts75 device address
 * \return TWI_SUCCESS if device ACK's, error code otherwise
 */
int8_t ts75_probe_nonvol_register(uint8_t device_addr)
{
	twi_package_t packet;

	/* TWI chip address to communicate with */
	packet.chip = device_addr;
	packet.addr_length = 0x00;
	packet.buffer = (void *)nv_config;
	packet.length = 0x01;

	/* Perform a write access & check write result */
	at30ts_status = twi_write(&packet);
	if (at30ts_status != TWI_SUCCESS) {
		return AT30TS_TWI_WRITE_NACK;
	}

	return TWI_SUCCESS;
}

/**
 * \brief Checks at30ts75 NVRBSY, RLCKDWN and RCLK bits
 *
 * \return AT30TS_SUCCESS if all bits = 0, error code otherwise
 */
int8_t check_NVRBSY(void)
{
	uint8_t buf[2];
	uint8_t n = 80;

	do {
		/* Read vol configuration register */
		ts_read_register(CONFIG_REG, buf);

		/* Do n-attempts, then abort */
		if (!n) {
			return AT30TS_NVRBSY_BUSY;
		}

		n--;
	} while (buf[1] & NVRBSY);

	at30ts_status = ts_read_register(NV_CONFIG_REG, buf);

	if (at30ts_status != TWI_SUCCESS) {
		return at30ts_status;
	}

	if (buf[1] & RLCKDWN_MSK || buf[1] & RLCK_MSK) {
		return AT30TS_REG_LOCKED;
	}

	return AT30TS_SUCCESS;
}

/**
 * \brief Read tLOW limit register
 *
 * \param *sensor_data	Where to store the retrieved data
 * \return				TWI_SUCCESS if all bytes were read,
 *						error code otherwise
 */
uint8_t read_temperature_low(sensor_data_t *sensor_data)
{
#if defined _AT30TS00_ || defined _AT30TSE002B_
	at30ts_status = ts_read_register(TRIP_LWR_REG, at30ts_iobuf);
	buftoval(sensor_data->limits.low, at30ts_iobuf);
#else
	at30ts_status = ts_read_register(TLOLIM_REG, at30ts_iobuf);
	buftoval(sensor_data->limits.low, at30ts_iobuf);
#endif

	return at30ts_status;
}

/**
 * \brief Read tHIGH limit register
 *
 * \param *sensor_data	Where to store the retrieved data
 * \return				TWI_SUCCESS if all bytes were read,
 *						error code otherwise
 */
uint8_t read_temperature_high(sensor_data_t *sensor_data)
{
#if defined _AT30TS00_ || defined _AT30TSE002B_
	at30ts_status = ts_read_register(TRIP_UPR_REG, at30ts_iobuf);
	buftoval(sensor_data->limits.high, at30ts_iobuf);
#else
	at30ts_status = ts_read_register(THILIM_REG, at30ts_iobuf);
	buftoval(sensor_data->limits.high, at30ts_iobuf);
#endif

	return at30ts_status;
}

/**
 * \brief Read nonvolatile config register
 *
 * \param *sensor_data	Where to store the retrieved data
 * \return				TWI_SUCCESS if all bytes were read,
 *						error code otherwise
 */
uint8_t read_config(sensor_data_t *sensor_data)
{
#if defined _AT30TS00_ || defined _AT30TSE002B_
	at30ts_status =  ts_read_register(CONFIGUR_REG, at30ts_iobuf);
#else
	at30ts_status =  ts_read_register(CONFIG_REG, at30ts_iobuf);
#endif

	buftoval(sensor_data->config_reg.value, at30ts_iobuf);
	return at30ts_status;
}

/**
 * \brief Write tLOW limit register
 *
 * \param sign		   temperature sign, used for conversion
 * \param itemp		   Integer data part to be written
 * \param ftemp		   Fractional data to be written
 *
 * \return TWI_SUCCESS if all bytes were written, error code otherwise
 */

uint8_t write_temperature_low(uint8_t sign, uint8_t itemp, uint16_t ftemp)
{
	uint16_t val;

#if defined _AT30TS00_ || defined _AT30TSE002B_
	val = (itemp << 4) | ((ftemp / 2500) << 2);
	/* Set pointer register */
	at30ts_iobuf[0] = TRIP_LWR_REG;
#else
	val = (itemp << 8) | ((ftemp / 625) << 4);
	/* Set pointer register */
	at30ts_iobuf[0] = TLOLIM_REG;
#endif

	/* 2's compliment */
	if (sign == neg) {
		val = ~val;
		val += 1;
	}

	/* Load val into buf */
	valtobuf(val, at30ts_iobuf);

	/* Write the tLOW limit register */
	return ts_write_register(at30ts_iobuf);
}

/**
 * \brief Write tHIGH limit register
 *
 * \param sign		   temperature sign, used for conversion
 * \param itemp		   Integer data part to be written
 * \param ftemp		   Fractional data to be written
 *
 * \return TWI_SUCCESS if all bytes were written, error code otherwise
 */

uint8_t write_temperature_high(uint8_t sign, uint8_t itemp, uint16_t ftemp)
{
	uint16_t val;

#if defined _AT30TS00_ || defined _AT30TSE002B_
	val = (itemp << 4) | ((ftemp / 2500) << 2);
	/* Set pointer register */
	at30ts_iobuf[0] = TRIP_UPR_REG;
#else
	val = (itemp << 8) | ((ftemp / 625) << 4);
	/* Set pointer register */
	at30ts_iobuf[0] = THILIM_REG;
#endif

	/* 2's compliment */
	if (sign == neg) {
		val = ~val;
		val += 1;
	}

	/* Load val into buf */
	valtobuf(val, at30ts_iobuf);

	/* Write the tHIGH limit register */
	return ts_write_register(at30ts_iobuf);
}

/**
 * \brief Write configuration register
 *
 * \param val		   Data to be written
 * \return TWI_SUCCESS if all bytes were written, error code otherwise
 */
uint8_t write_config(uint16_t val)
{
	/* Set pointer register */
#if defined _AT30TS00_ || defined _AT30TSE002B_
	at30ts_iobuf[0] = CONFIGUR_REG;
#else
	at30ts_iobuf[0] = CONFIG_REG;
#endif

	/* Load val into buf */
	valtobuf(val, at30ts_iobuf);

	/* Write the configuration register */
	return ts_write_register(at30ts_iobuf);
}

/**
 * \brief Set Configuration Options
 * \param data		   Sensor data type, holds sensor information
 * \param flag		   Defines which option to change
 * \param opt		   Option(s) settings
 *
 * \return AT30TS_SUCCESS if all bits = 0, error code otherwise
 */
uint8_t set_config_option(sensor_data_t *data, opt_flag_t flag,
							config_options_t opt)
{
#if defined _AT30TS00_ || defined _AT30TSE002B_
	/* Read current configuration setting */
	at30ts_status =  ts_read_register(CONFIGUR_REG, at30ts_iobuf);

	/* Save current configuration setting */
	buftoval(data->config_reg_002b.value, at30ts_iobuf);

	switch (flag) {
	case AT30TS_002B_CONFBIT_EVTMOD:
		/* Set configuration resolution parameter */
		data->config_reg_002b.option.EVTMOD =  opt;
		break;

	case AT30TS_002B_CONFBIT_EVTPOL:
		/* Set configuration register fault parameter */
		data->config_reg_002b.option.EVTPOL =  opt;
		break;

	case AT30TS_002B_CONFBIT_CRITEVT:
		/* Set configuration register polarity parameter */
		data->config_reg_002b.option.CRITEVT =  opt;
		break;

	case AT30TS_002B_CONFBIT_EVTOUT:
		/* Set configuration register comparator/interrupt parameter */
		data->config_reg_002b.option.EVTOUT  =  opt;
		break;

	case AT30TS_002B_CONFBIT_EVTSTS:
		/* Set configuration register shutdown parameter */
		data->config_reg_002b.option.EVTSTS  =  opt;
		break;

	case AT30TS_002B_CONFBIT_EVTCLR:
		/* Set configuration register one-shot parameter */
		data->config_reg_002b.option.EVTCLR  =  opt;
		break;

	case AT30TS_002B_CONFBIT_WINLOCK:
		/* Set configuration register one-shot parameter */
		data->config_reg_002b.option.WINLOCK  =  opt;
		break;

	case AT30TS_002B_CONFBIT_CRTALML:
		/* Set configuration register one-shot parameter */
		data->config_reg_002b.option.CRTALML  =  opt;
		break;

	case AT30TS_002B_CONFBIT_SHTDWN:
		/* Set configuration register one-shot parameter */
		data->config_reg_002b.option.SHTDWN  =  opt;
		break;

	case AT30TS_002B_CONFBIT_HYSTENB:
		/* Set configuration register one-shot parameter */
		data->config_reg_002b.option.HYSTENB  =  opt;
		break;
	}

	return write_config(data->config_reg_002b.value);

#else
	/* Read current configuration setting */
	ts_read_register(CONFIG_REG, at30ts_iobuf);

	/* Save current configuration setting */
	buftoval(data->config_reg.value, at30ts_iobuf);

	switch (flag) {
	case AT30TS_RES:
		/* Set configuration resolution parameter */
		data->config_reg.option.RES =  opt;
		break;

	case AT30TS_FAULT:
		/* Set configuration register fault parameter */
		data->config_reg.option.FAULT =  opt;
		break;

	case AT30TS_POL:
		/* Set configuration register polarity parameter */
		data->config_reg.option.POL =  opt;
		break;

	case AT30TS_CMP_INT_MODE:
		/* Set configuration register comparator/interrupt parameter */
		data->config_reg.option.CMP_INT  =  opt;
		break;

	case AT30TS_SD:
		/* Set configuration register shutdown parameter */
		data->config_reg.option.SD  =  opt;
		break;

	case AT30TS_OS:
		/* Set configuration register one-shot parameter */
		data->config_reg.option.OS  =  opt;
		break;

	/* Parameters are not valid for volatile configuration register */
	case AT30TS_RLCK:
	case AT30TS_RLCKDWN:
		break;
	}

	return write_config(data->config_reg.value);
 #endif
}

/**
 * \brief Read temperature register
 *
 * \param *sensor_data	Where to store the retrieved data
 * \return				TWI_SUCCESS if all bytes were read,
 *						error code otherwise
 */
int8_t read_temperature(sensor_data_t *sensor_data)
{
	uint16_t val;
	uint8_t buf[2];

	/* Get temperature data */
#if defined _AT30TS00_ || defined _AT30TSE002B_
	at30ts_status = ts_read_register(TEMP_DATA_REG, buf);

	if (at30ts_status == TWI_SUCCESS) {
		val = buf[0]; /* MSB */
		val <<= 8;
		val |= buf[1]; /* LSB */

		/* Bits 15 - 0 */
		sensor_data->temperature.raw_value = val;
		/* Check 12th Bit for sign */
		sensor_data->temperature.sign = val & (1 << 12);
		/* Neg value */
		if (sensor_data->temperature.sign) {
			/* 2's compliment */
			val = ~val;
			val += 1;

			sensor_data->temperature.ftemp
				= ((val >> 2) & 0x0F) * 2500;
			sensor_data->temperature.itemp = (val  >> 4) & 0xFF;
		} else {
			/* Pos value */
			sensor_data->temperature.itemp = (val >> 4);
			sensor_data->temperature.ftemp
				= (val >> 1 & 0x07) * 1250;
		}

		return TWI_SUCCESS;
	}

#else
	at30ts_status = ts_read_register(TEMPER_REG, buf);

	if (at30ts_status == TWI_SUCCESS) {
		val = buf[0];
		val <<= 8;
		val |= buf[1];

		sensor_data->temperature.raw_value = val;
		/* Check 15th Bit for sign */
		sensor_data->temperature.sign = (val & 1 << 15);

		/* Neg value */
		if (sensor_data->temperature.sign) {
			/* 2's compliment */
			val = ~val;
			val += 1;

			sensor_data->temperature.ftemp
				= ((val & 0xff) >> 4) * 625;
			sensor_data->temperature.itemp = (val >> 8) & 0xff;
		} else {
			/* Pos value */
			sensor_data->temperature.itemp = buf[0];
			sensor_data->temperature.ftemp = (buf[1] >> 4) * 625;
		}

		return TWI_SUCCESS;
	}
 #endif
	else {
		return AT30TS_TWI_WRITE_NACK;
	}
}

#if defined _AT30TS750_  || defined _AT30TSE752_ || \
	defined _AT30TSE754_ || defined _AT30TSE758_

/**
 * \brief Read nonvolatile tLOW limit register
 *
 * \param *sensor_data	Where to store the retrieved data
 * \return				TWI_SUCCESS if all bytes were read,
 *						error code otherwise
 */
uint8_t read_nvtlow(sensor_data_t *sensor_data)
{
	at30ts_status = ts_read_register(NV_TLOLIM_REG, at30ts_iobuf);
	buftoval(sensor_data->nv_limits.low, at30ts_iobuf);

	return at30ts_status;
}

/**
 * \brief Read nonvolatile tHIGH limit register
 *
 * \param *sensor_data	Where to store the retrieved data
 * \return TWI_SUCCESS if all bytes were read, error code otherwise
 */
uint8_t read_nvthigh(sensor_data_t *sensor_data)
{
	at30ts_status = ts_read_register(NV_THILIM_REG, at30ts_iobuf);
	buftoval(sensor_data->nv_limits.high, at30ts_iobuf);

	return at30ts_status;
}

/**
 * \brief Read nonvolatile config register
 *
 * \param *sensor_data  Where to store the retrieved data
 * \return AT30TS_SUCCESS if all bits = 0, error code otherwise
 */
uint8_t read_nvconfig(sensor_data_t *sensor_data)
{
	at30ts_status =  ts_read_register(NV_CONFIG_REG, at30ts_iobuf);
	buftoval(sensor_data->nvconfig_reg.value, at30ts_iobuf);

	return at30ts_status;
}

/**
 * \brief Write nonvolatile tLOW limit register
 *
 * \param val		   Data to be written
 * \return TWI_SUCCESS if all bytes were written, error code otherwise
 */

uint8_t write_nvtlow(uint8_t sign, uint8_t itemp, uint16_t ftemp)
{
	uint16_t val;

	val = (itemp << 8) | ((ftemp / 625) << 4);

	/* 2's compliment */
	if (sign == neg) {
		val = ~val;
		val += 1;
	}

	/* Set pointer register */
	at30ts_iobuf[0] = NV_TLOLIM_REG;

	/* Load val into buf */
	valtobuf(val, at30ts_iobuf);

	/* Write the tLOW limit register */
	return ts_write_register(at30ts_iobuf);
}

/**
 * \brief Write nonvolatile tHIGH limit register
 *
 * \param val		   Data to be written
 * \return TWI_SUCCESS if all bytes were written, error code otherwise
 */

uint8_t write_nvthigh(uint8_t sign, uint8_t itemp, uint16_t ftemp)
{
	uint16_t val;

	val = (itemp << 8) | ((ftemp / 625) << 4);

	/* 2's compliment */
	if (sign == neg) {
		val = ~val;
		val += 1;
	}

	/* Set pointer register */
	at30ts_iobuf[0] = NV_THILIM_REG;

	/* Load val into buf */
	valtobuf(val, at30ts_iobuf);

	/* Write the tHIGH limit register */
	return ts_write_register(at30ts_iobuf);
}

/**
 * \brief Write nonvolatile configuration register
 *
 * \param val		   Data to be written
 * \return TWI_SUCCESS if all bytes were written, error code otherwise
 */
uint8_t write_nvconfig(uint16_t val)
{
	/* Set pointer register */
	at30ts_iobuf[0] = NV_CONFIG_REG;

	/* Load val into buf */
	valtobuf(val, at30ts_iobuf);

	/* Write the configuration register */
	return ts_write_register(at30ts_iobuf);
}

/**
 * \brief Set bit(s) in nonvolatile configuration register
 *
 * \return AT30TS_SUCCESS if all bits = 0, error code otherwise
 */
uint8_t set_nvconfig_option(sensor_data_t *data, opt_flag_t flag,
			    nvconfig_options_t opt)
{
	/* Read current configuration setting */
	ts_read_register(NV_CONFIG_REG, at30ts_iobuf);

	/* Save current configuration setting */
	buftoval(data->nvconfig_reg.value, at30ts_iobuf);

	switch (flag) {
	case AT30TS_RES:
		/* Set configuration resolution parameter */
		data->nvconfig_reg.option.NVRES =  opt;
		break;

	case AT30TS_FAULT:
		/* Set configuration register fault parameter */
		data->nvconfig_reg.option.NVFT =  opt;
		break;

	case AT30TS_POL:
		/* Set configuration register polarity parameter */
		data->nvconfig_reg.option.NVPOL =  opt;
		break;

	case AT30TS_CMP_INT_MODE:
		/* Set configuration register comparator/interrupt parameter */
		data->nvconfig_reg.option.NVCMP_INT =  opt;
		break;

	case AT30TS_SD:
		/* Set configuration register shutdown parameter */
		data->nvconfig_reg.option.NVSD  =  opt;
		break;

	case AT30TS_RLCK:
		/* Set configuration register lock parameter */
		data->nvconfig_reg.option.RLCK  =  opt;
		break;

	case AT30TS_RLCKDWN:
		/* Set configuration register lockdown parameter */
		data->nvconfig_reg.option.RLCKDWN  =  opt;
		break;

	case AT30TS_OS:
		/* Parameter not valid for nonvolatile register */
		break;
	}

	return write_config(data->nvconfig_reg.value);
}

#endif

/**
 * \brief Write memory, this function manages writing
 *        data beyond a pages size (16 bytes)
 *
 * \param address      Data word address
 * \param size		   Size of the data to write
 * \param *buf		   Data to be written
 *
 * \return TWI_SUCCESS if all bytes were written, error code otherwise
 */

uint8_t ts_write_memory(uint16_t address, uint16_t size, uint8_t *buf)
{
	uint8_t write_size              = 0;
	uint8_t n                       = 0;
	uint16_t end_page_addr          = 0;
	uint8_t *buf_ptr                = 0;

	buf_ptr = buf;

	do {
		n = (uint16_t)(address / PAGE_SIZE);
		end_page_addr = ((n + 1) * PAGE_SIZE);

		if ((address + size) > end_page_addr) {
			/* Response_data doesn't fit, do a partial write */
			write_size = end_page_addr - address;
		} else {
			write_size = size;
		}

		at30ts_status = ts_write_eeprom(address, write_size, buf_ptr);

		if (at30ts_status != TWI_SUCCESS) {
			return at30ts_status;
		}

		size -= write_size;
		address += write_size;
		buf_ptr += write_size;
	} while (size);

	return TWI_SUCCESS;
}

void parse_temp_reading(sensor_data_t *sensor_data)
{
	uint16_t raw_temp_reading = sensor_data->temperature.raw_value;

#if defined _AT30TS00_ || defined _AT30TSE002B_
	sensor_data->temperature.itemp = (raw_temp_reading  >> 4) & 0xFF;
	sensor_data->temperature.ftemp
		= ((raw_temp_reading  >> 2) & 0x0F) * 2500;
	sensor_data->temperature.sign  = raw_temp_reading  & 0x1000;

#else
	sensor_data->temperature.itemp = (raw_temp_reading  >> 8) & 0xFF;
	sensor_data->temperature.ftemp
		= ((raw_temp_reading  >> 4) & 0x0F) * 625;
	sensor_data->temperature.sign  = raw_temp_reading  & 0x8000;
#endif
}

#if defined _AT30TS00_ || defined _AT30TSE002B_

/**
 * \brief Read capability register
 *
 * \param *buf		  Where to store the retrieved data
 * \return AT30TS_SUCCESS if all bits = 0, error code otherwise
 */
uint8_t read_capability(sensor_data_t *sensor_data)
{
	at30ts_status =  ts_read_register(CAPABIL_REG, at30ts_iobuf);
	buftoval(sensor_data->_002b.capability, at30ts_iobuf);

	return at30ts_status;
}

/**
 * \brief Read manufacture ID register
 *
 * \param *buf		  Where to store the retrieved data
 * \return AT30TS_SUCCESS if all bits = 0, error code otherwise
 */
uint8_t read_manfid(sensor_data_t *sensor_data)
{
	at30ts_status =  ts_read_register(MANF_ID_REG, at30ts_iobuf);
	buftoval(sensor_data->_002b.manf_id, at30ts_iobuf);

	return at30ts_status;
}

/**
 * \brief Read device ID register
 *
 * \param *buf		  Where to store the retrieved data
 * \return AT30TS_SUCCESS if all bits = 0, error code otherwise
 */
uint8_t read_devid(sensor_data_t *sensor_data)
{
	at30ts_status =  ts_read_register(DEV_ID_REG, at30ts_iobuf);
	buftoval(sensor_data->_002b.device_id, at30ts_iobuf);

	return at30ts_status;
}

/**
 * \brief Read SMBUS register
 *
 * \param *buf		  Where to store the retrieved data
 * \return AT30TS_SUCCESS if all bits = 0, error code otherwise
 */
uint8_t read_smbus(sensor_data_t *sensor_data)
{
	at30ts_status =  ts_read_register(SMBUS_TO_REG, at30ts_iobuf);
	buftoval(sensor_data->_002b.smbus, at30ts_iobuf);

	return at30ts_status;
}

/**
 * \brief Read tCRIT limit register
 *
 * \param *buf		  Where to store the retrieved data
 * \return TWI_SUCCESS if all bytes were read, error code otherwise
 */
uint8_t read_tcrit(sensor_data_t *sensor_data)
{
	at30ts_status = ts_read_register(TRIP_CRT_REG, at30ts_iobuf);
	buftoval(sensor_data->limits.critical, at30ts_iobuf);

	return at30ts_status;
}

/**
 * \brief Write tCRIT limit register
 *
 * \param val		   Data to be written
 * \return TWI_SUCCESS if all bytes were written, error code otherwise
 */

uint8_t write_tcrit(uint8_t sign, uint8_t itemp, uint16_t ftemp)
{
	uint16_t val;

	val = (itemp << 4) | ((ftemp / 2500) << 2);

	/* 2's compliment */
	if (sign == neg) {
		val = ~val;
		val += 1;
	}

	/* Set pointer register */
	at30ts_iobuf[0] = TRIP_CRT_REG;

	/* Load val into buf */
	valtobuf(val, at30ts_iobuf);

	/* Write the tCRIT limit register */
	return ts_write_register(at30ts_iobuf);
}

#endif

uint8_t twi_write(twi_package_t *packet)
{
	return twi_master_write(TWI_MODULE, packet);
}

uint8_t twi_read(twi_package_t *packet)
{
	return twi_master_read(TWI_MODULE, packet);
}

uint8_t twi_probe_device(uint8_t addr)
{
	twi_package_t packet;
	unsigned char test_buff[1] = {0};

	packet.chip = addr;
	packet.addr[0] = 0;
	packet.addr_length = 1;
	packet.buffer = test_buff;
	packet.length = 0;

	return twi_master_write(TWI_MODULE, &packet);
}
