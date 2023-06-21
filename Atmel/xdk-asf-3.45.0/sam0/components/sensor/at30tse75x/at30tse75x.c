/**
 * \file
 *
 * \brief AT30TSE75X driver
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

#include <at30tse75x.h>

#ifdef __cplusplus
extern "C" {
#endif

struct i2c_master_module dev_inst_at30tse75x;
uint8_t resolution = AT30TSE_CONFIG_RES_9_bit;

/**
 * \brief Configures the SERCOM I2C master to be used with the AT30TSE75X device.
 */
void at30tse_init(void)
{
    /* Initialize config structure and device instance. */
	struct i2c_master_config conf;
	i2c_master_get_config_defaults(&conf);

	/* Change buffer timeout to something longer. */
	conf.buffer_timeout = 10000;

	conf.pinmux_pad0 = AT30TSE_PINMUX_PAD0;
	conf.pinmux_pad1 = AT30TSE_PINMUX_PAD1;

	/* Initialize and enable device with config. */
	i2c_master_init(&dev_inst_at30tse75x, AT30TSE_SERCOM, &conf);
	i2c_master_enable(&dev_inst_at30tse75x);
}

/**
 * \brief Writes the EEPROM with data provided.
 *
 * \param[out] *data Pointer to the data buffer.
 * \param[in]  length Number of data bytes.
 * \param[in]  word_addr Word address of the EEPROM.
 * \param[in]  page Page number of the EEPROM.
 */
void at30tse_eeprom_write(uint8_t *data, uint8_t length, uint8_t word_addr, uint8_t page)
{
	/* ACK polling for consecutive writing not implemented! */
	uint8_t buffer[17];
	/* Byte addr in page (0-15) */
	buffer[0] = word_addr & 0x0F;
	/* 4 lower bits of page addr in EEPROM	 */
	buffer[0] |= (0x0F & page) << 4;

	/* Copy data to be sent */
	for (uint8_t i=1; i<17; i++){
		buffer[i] = data[i-1];
	}

	/* Set up TWI transfer */
    struct i2c_master_packet packet = {
		.address     = AT30TSE758_EEPROM_TWI_ADDR | ((0x30 & page)>>4),
		.data_length = length+1,
		.data        = buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	/* Do the transfer */
    i2c_master_write_packet_wait(&dev_inst_at30tse75x, &packet);
}

/**
 * \brief Reads data from the EEPROM.
 *
 * \param[out] *data Pointer to the data buffer.
 * \param[in]  length Number of data bytes.
 * \param[in]  word_addr Word address of the EEPROM.
 * \param[in]  page Page number of the EEPROM.
 */
void at30tse_eeprom_read(uint8_t *data, uint8_t length, uint8_t word_addr, uint8_t page)
{
	/* ACK polling for consecutive reading not implemented! */
	uint8_t buffer[1];
	/* Byte addr in page (0-15) */
	buffer[0] = word_addr & 0x0F;
	/* 4 lower bits of page addr in EEPROM */
	buffer[0] |= (0x0F & page) << 4;

	/* Set up internal EEPROM addr write */
    struct i2c_master_packet addr_transfer = {
		.address     = AT30TSE758_EEPROM_TWI_ADDR | ( (0x30 & page) >> 4 ),
		.data_length = 1,
		.data        = buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	/* Reading sequence */
    struct i2c_master_packet read_transfer = {
		.address     = AT30TSE758_EEPROM_TWI_ADDR | ( (0x30 & page) >> 4 ),
		.data_length = length,
		.data        = data,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};

	/* Do the transfer */
    i2c_master_write_packet_wait_no_stop(&dev_inst_at30tse75x, &addr_transfer);
    i2c_master_read_packet_wait(&dev_inst_at30tse75x, &read_transfer);
}

/**
 * \brief Sets the register pointer with specified reg value.
 *
 * \param[in] reg Register value of the pointer register.
 * \param[in] reg_type Register type being pointed by pointer register.
 */
void at30tse_set_register_pointer(uint8_t reg, uint8_t reg_type)
{
	uint8_t buffer[] = {reg | reg_type};
    struct i2c_master_packet transfer = {
		.address     = AT30TSE_TEMPERATURE_TWI_ADDR,
		.data_length = 1,
		.data        = buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	/* Do the transfer */
    i2c_master_write_packet_wait(&dev_inst_at30tse75x, &transfer);
}

/**
 * \brief Reads the value from the register reg.
 *
 * \param[in] reg Register to read.
 * \param[in] reg_type Type of the register (Volatile or Non-volatile).
 * \param[in] reg_size Register size.
 *
 * \return Register value.
 */
uint16_t at30tse_read_register(uint8_t reg, uint8_t reg_type, uint8_t reg_size)
{
	uint8_t buffer[2];
	buffer[0] = reg | reg_type;
	buffer[1] = 0;

	/* Internal register pointer in AT30TSE */
    struct i2c_master_packet write_transfer = {
		.address     = AT30TSE_TEMPERATURE_TWI_ADDR,
		.data_length = 1,
		.data        = buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	/* Read data */
    struct i2c_master_packet read_transfer = {
		.address     = AT30TSE_TEMPERATURE_TWI_ADDR,
		.data_length = reg_size,
		.data        = buffer,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	/* Do the transfer */
	i2c_master_write_packet_wait_no_stop(&dev_inst_at30tse75x, &write_transfer);
    i2c_master_read_packet_wait(&dev_inst_at30tse75x, &read_transfer);

	return (buffer[0] << 8) | buffer[1];
}

/**
 * \brief Writes the specified register reg with the reg_value passed
 *
 * \param[in] reg Register to write.
 * \param[in] reg_type Type of the register (Volatile or Non-volatile).
 * \param[in] reg_size Register size.
 * \param[in] reg_value Value to be written to reg.
 */
void at30tse_write_register(uint8_t reg, uint8_t reg_type, uint8_t reg_size, uint16_t reg_value)
{
	uint8_t data[3];
	data[0] = reg | reg_type;
	data[1] = 0x00FF & (reg_value >> 8);
	data[2] = 0x00FF & reg_value;

	/* Internal register pointer in AT30TSE */
    struct i2c_master_packet transfer = {
		.address     = AT30TSE_TEMPERATURE_TWI_ADDR,
		.data_length = 1 + reg_size,
		.data        = data,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	/* Do the transfer */
	i2c_master_write_packet_wait(&dev_inst_at30tse75x, &transfer);
}

/**
 * \brief Writes the configuration register reg with the value passed
 *
 * \param[in] value Register value to be written.
 */
void at30tse_write_config_register(uint16_t value)
{
	at30tse_write_register(AT30TSE_CONFIG_REG,
							AT30TSE_NON_VOLATILE_REG,
							AT30TSE_CONFIG_REG_SIZE-1,
							value);

	resolution = ( value >> AT30TSE_CONFIG_RES_Pos ) & ( AT30TSE_CONFIG_RES_Msk >> AT30TSE_CONFIG_RES_Pos);

}

/**
 * \brief Reads the temperature value.
 *
 * \return Temperature data.
 */
double at30tse_read_temperature()
{
	/* Read the 16-bit temperature register. */
	uint16_t data = at30tse_read_register(AT30TSE_TEMPERATURE_REG,
											AT30TSE_NON_VOLATILE_REG,
											AT30TSE_TEMPERATURE_REG_SIZE);

	double temperature = 0;
	int8_t sign = 1;

	/*Check if negative and clear sign bit. */
	if (data & (1 << 15)){
		sign *= -1;
		data &= ~(1 << 15);
	}

	/* Convert to temperature  */
	switch (resolution){
		case AT30TSE_CONFIG_RES_9_bit:
			data = (data >> 7);
			temperature = data * sign * 0.5;
			break;
		case AT30TSE_CONFIG_RES_10_bit:
			data = (data >> 6);
			temperature = data * sign * 0.25;
			break;
		case AT30TSE_CONFIG_RES_11_bit:
			data = (data >> 5);
			temperature = data * sign * 0.125;
			break;
		case AT30TSE_CONFIG_RES_12_bit:
			data = (data >> 4);
			temperature = data * sign * 0.0625;
			break;
		default:
			break;
	}
	return temperature;
}

#ifdef __cplusplus
}
#endif
