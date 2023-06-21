/**
 * \file
 *
 * \brief KS8851SNL driver for SAM0.
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

#include "ksz8851snl.h"
#include "ksz8851snl_reg.h"
#include "extint.h"

struct spi_module ksz8851snl_master;
struct spi_slave_inst ksz8851snl_slave;

/**
 * \internal
 * \brief Initialize the hardware interface.
 */
static void ksz8851snl_interface_init(void)
{
	struct spi_config config;
	struct spi_slave_inst_config slave_config;

	spi_slave_inst_get_config_defaults(&slave_config);
	slave_config.ss_pin = KSZ8851SNL_CS_PIN;
	spi_attach_slave(&ksz8851snl_slave, &slave_config);

	spi_get_config_defaults(&config);

	config.mux_setting = KSZ8851SNL_SPI_PINMUX_SETTING;
	config.pinmux_pad0 = KSZ8851SNL_SPI_PINMUX_PAD0;
	config.pinmux_pad1 = KSZ8851SNL_SPI_PINMUX_PAD1;
	config.pinmux_pad2 = KSZ8851SNL_SPI_PINMUX_PAD2;
	config.pinmux_pad3 = KSZ8851SNL_SPI_PINMUX_PAD3;
	config.mode_specific.master.baudrate = KSZ8851SNL_CLOCK_SPEED;

	spi_init(&ksz8851snl_master, KSZ8851SNL_SPI, &config);
	spi_enable(&ksz8851snl_master);

	/* Configure RSTN pin. */
	struct port_config pin;
	port_get_config_defaults(&pin);
	pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(KSZ8851SNL_RSTN_PIN, &pin);
}

/**
 * \internal
 * \brief Perform hardware reset of the PHY.
 */
static inline void ksz8851snl_hard_reset(void)
{
	/* Perform hardware reset with respect to the reset timing from the datasheet. */
	port_pin_set_output_level(KSZ8851SNL_RSTN_PIN, false);
	delay_ms(100);
	port_pin_set_output_level(KSZ8851SNL_RSTN_PIN, true);
	delay_ms(100);
}

/**
 * \brief Configure the INTN interrupt.
 *
 * \param p_handler callback pointer to use when INTN interrupt raises.
 */
void configure_intn(void (*p_handler) (void))
{
	struct extint_chan_conf eic_conf;

	/* Configure the external interrupt channel. */
	extint_chan_get_config_defaults(&eic_conf);
	eic_conf.gpio_pin            = KSZ8851SNL_INTN_EIC_PIN;
	eic_conf.gpio_pin_mux        = KSZ8851SNL_INTN_EIC_PIN_MUX;
	eic_conf.gpio_pin_pull       = EXTINT_PULL_UP;
	eic_conf.detection_criteria  = EXTINT_DETECT_FALLING;
	eic_conf.filter_input_signal = true;
	extint_chan_set_config(KSZ8851SNL_INTN_EIC_CHANNEL, &eic_conf);

	/* Register and enable the callback function. */
	extint_register_callback(p_handler,
			KSZ8851SNL_INTN_EIC_CHANNEL,
			EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(KSZ8851SNL_INTN_EIC_CHANNEL,
			EXTINT_CALLBACK_TYPE_DETECT);
}

/**
 * \brief Read internal fifo buffer.
 *
 * \param buf the buffer to store the data from the fifo buffer.
 * \param len the amount of data to read.
 */
void ksz8851_fifo_read(uint8_t *buf, uint32_t len)
{
	uint8_t tmpbuf[9];

	spi_select_slave(&ksz8851snl_master, &ksz8851snl_slave, true);

	tmpbuf[0] = FIFO_READ;

	/* Perform SPI transfer. */
	spi_transceive_buffer_wait(&ksz8851snl_master, tmpbuf, tmpbuf, 9);
	spi_read_buffer_wait(&ksz8851snl_master, buf, len, 0xff);

	/* Read CRC (don't care). */
	spi_read_buffer_wait(&ksz8851snl_master, tmpbuf, 4, 0xff);
	len += 4;

	/* Keep internal memory alignment. */
	len &= 3;
	if (len) {
		spi_read_buffer_wait(&ksz8851snl_master, tmpbuf, len, 0xff);
	}

	spi_select_slave(&ksz8851snl_master, &ksz8851snl_slave, false);
}

/**
 * \brief Start to write internal fifo buffer.
 *
 * \param tot_len the total amount of data to write.
 */
void ksz8851_fifo_write_begin(uint32_t tot_len)
{
	uint8_t	outbuf[5];
	static uint8_t frameID = 0;

	spi_select_slave(&ksz8851snl_master, &ksz8851snl_slave, true);

	/* Prepare control word and byte count. */
	outbuf[0] = FIFO_WRITE;
	outbuf[1] = frameID++ & 0x3f;
	outbuf[2] = 0;
	outbuf[3] = tot_len & 0xff;
	outbuf[4] = tot_len >> 8;

	/* Perform SPI transfer. */
	spi_write_buffer_wait(&ksz8851snl_master, outbuf, 5);
}

/**
 * \brief Write internal fifo buffer.
 *
 * \param buf the buffer to send to the fifo buffer.
 * \param len the size of the pbuf element to write.
 */
void ksz8851_fifo_write(uint8_t *buf, uint32_t len)
{
	/* Perform SPI transfer. */
	spi_write_buffer_wait(&ksz8851snl_master, buf, len);
}

/**
 * \brief Complete write operation.
 *
 * \param pad amount of dummy data (bytes) to write to keep 32 bits alignment
 * in the internal FIFO.
 */
void ksz8851_fifo_write_end(uint32_t pad)
{
	uint8_t	outbuf[5];

	if (pad > 0) {
		spi_write_buffer_wait(&ksz8851snl_master, outbuf, 4 - pad);
	}
	spi_select_slave(&ksz8851snl_master, &ksz8851snl_slave, false);
}

/**
 * \brief Read a register value.
 *
 * \param reg the register address to modify.
 *
 * \return the register value.
 */
uint16_t ksz8851_reg_read(uint16_t reg)
{
	uint8_t	inbuf[4];
	uint8_t	outbuf[4];
	uint16_t cmd = 0;
	uint16_t res = 0;

	spi_select_slave(&ksz8851snl_master, &ksz8851snl_slave, true);

	/* Move register address to cmd bits 9-2, make 32-bit address. */
	cmd = (reg << 2) & REG_ADDR_MASK;

	/* Last 2 bits still under "don't care bits" handled with byte enable. */
	/* Select byte enable for command. */
	if (reg & 2) {
		/* Odd word address writes bytes 2 and 3 */
		cmd |= (0xc << 10);
	} else {
		/* Even word address write bytes 0 and 1 */
		cmd |= (0x3 << 10);
	}

	/* Add command read code. */
	cmd |= CMD_READ;
	outbuf[0] = cmd >> 8;
	outbuf[1] = cmd & 0xff;
	outbuf[2] = 0xff;
	outbuf[3] = 0xff;

	/* Perform SPI transfer. */
	spi_transceive_buffer_wait(&ksz8851snl_master, outbuf, inbuf, 4);

	spi_select_slave(&ksz8851snl_master, &ksz8851snl_slave, false);

	res = (inbuf[3] << 8) | inbuf[2];
	return res;
}

/**
 * \brief Write a register value.
 *
 * \param reg the register address to modify.
 * \param wrdata the new register value.
 */
void ksz8851_reg_write(uint16_t reg, uint16_t wrdata)
{
	uint8_t	inbuf[4];
	uint8_t	outbuf[4];
	uint16_t cmd = 0;

	spi_select_slave(&ksz8851snl_master, &ksz8851snl_slave, true);

	/* Move register address to cmd bits 9-2, make 32-bit address. */
	cmd = (reg << 2) & REG_ADDR_MASK;

	/* Last 2 bits still under "don't care bits" handled with byte enable. */
	/* Select byte enable for command. */
	if (reg & 2) {
		/* Odd word address writes bytes 2 and 3 */
		cmd |= (0xc << 10);
	} else {
		/* Even word address write bytes 0 and 1 */
		cmd |= (0x3 << 10);
	}

	/* Add command write code. */
	cmd |= CMD_WRITE;
	outbuf[0] = cmd >> 8;
	outbuf[1] = cmd & 0xff;
	outbuf[2] = wrdata & 0xff;
	outbuf[3] = wrdata >> 8;

	/* Perform SPI transfer. */
	spi_transceive_buffer_wait(&ksz8851snl_master, outbuf, inbuf, 4);

	spi_select_slave(&ksz8851snl_master, &ksz8851snl_slave, false);
}

/**
 * \brief Read register content, set bitmask and write back to register.
 *
 * \param reg the register address to modify.
 * \param bits_to_set bitmask to apply.
 */
void ksz8851_reg_setbits(uint16_t reg, uint16_t bits_to_set)
{
   uint16_t	temp;

   temp = ksz8851_reg_read(reg);
   temp |= bits_to_set;
   ksz8851_reg_write(reg, temp);
}

/**
 * \brief Read register content, clear bitmask and write back to register.
 *
 * \param reg the register address to modify.
 * \param bits_to_set bitmask to apply.
 */
void ksz8851_reg_clrbits(uint16_t reg, uint16_t bits_to_clr)
{
   uint16_t	temp;

   temp = ksz8851_reg_read(reg);
   temp &= ~(uint32_t) bits_to_clr;
   ksz8851_reg_write(reg, temp);
}

/**
 * \brief Initialize the PHY controller
 *
 * Call this function to initialize the hardware interface and the PHY
 * controller. When initialization is done the PHY is turned on and ready
 * to receive data.
 */
uint32_t ksz8851snl_init(void)
{
	uint32_t count = 0;
	uint16_t dev_id = 0;

	/* Initialize delay routine. */
	delay_init();

	/* Initialize the SPI interface. */
	ksz8851snl_interface_init();

	/* Reset the Micrel in a proper state. */
	do {
		ksz8851snl_hard_reset();

		/* Init step1: read chip ID. */
		dev_id = ksz8851_reg_read(REG_CHIP_ID);
		if (++count > 10)
			return 1;
	} while ((dev_id & 0xFFF0) != CHIP_ID_8851_16);

	/* Init step2-4: write QMU MAC address (low, middle then high). */
	ksz8851_reg_write(REG_MAC_ADDR_0, (ETHERNET_CONF_ETHADDR4 << 8) | ETHERNET_CONF_ETHADDR5);
	ksz8851_reg_write(REG_MAC_ADDR_2, (ETHERNET_CONF_ETHADDR2 << 8) | ETHERNET_CONF_ETHADDR3);
	ksz8851_reg_write(REG_MAC_ADDR_4, (ETHERNET_CONF_ETHADDR0 << 8) | ETHERNET_CONF_ETHADDR1);

	/* Init step5: enable QMU Transmit Frame Data Pointer Auto Increment. */
	ksz8851_reg_write(REG_TX_ADDR_PTR, ADDR_PTR_AUTO_INC);

	/* Init step6: configure QMU transmit control register. */
	ksz8851_reg_write(REG_TX_CTRL,
			TX_CTRL_ICMP_CHECKSUM |
			TX_CTRL_UDP_CHECKSUM |
			TX_CTRL_TCP_CHECKSUM |
			TX_CTRL_IP_CHECKSUM |
			TX_CTRL_FLOW_ENABLE |
			TX_CTRL_PAD_ENABLE |
			TX_CTRL_CRC_ENABLE
		);

	/* Init step7: enable QMU Receive Frame Data Pointer Auto Increment. */
	ksz8851_reg_write(REG_RX_ADDR_PTR, ADDR_PTR_AUTO_INC);

	/* Init step8: configure QMU Receive Frame Threshold for one frame. */
	ksz8851_reg_write(REG_RX_FRAME_CNT_THRES, 1);

	/* Init step9: configure QMU receive control register1. */
	ksz8851_reg_write(REG_RX_CTRL1,
			RX_CTRL_UDP_CHECKSUM |
			RX_CTRL_TCP_CHECKSUM |
			RX_CTRL_IP_CHECKSUM |
			RX_CTRL_MAC_FILTER |
			RX_CTRL_FLOW_ENABLE |
			RX_CTRL_BROADCAST |
			RX_CTRL_ALL_MULTICAST|
			RX_CTRL_UNICAST);

	/* Init step10: configure QMU receive control register2. */
	ksz8851_reg_write(REG_RX_CTRL2,
			RX_CTRL_IPV6_UDP_NOCHECKSUM |
			RX_CTRL_UDP_LITE_CHECKSUM |
            RX_CTRL_ICMP_CHECKSUM |
			RX_CTRL_BURST_LEN_FRAME);

	/* Init step11: configure QMU receive queue: trigger INT and auto-dequeue frame. */
	ksz8851_reg_write(REG_RXQ_CMD, RXQ_CMD_CNTL | RXQ_TWOBYTE_OFFSET);

	/* Init step12: adjust SPI data output delay. */
	ksz8851_reg_write(REG_BUS_CLOCK_CTRL, BUS_CLOCK_166 | BUS_CLOCK_DIVIDEDBY_1);

	/* Init step13: restart auto-negotiation. */
	ksz8851_reg_setbits(REG_PORT_CTRL, PORT_AUTO_NEG_RESTART);

	/* Init step13.1: force link in half duplex if auto-negotiation failed. */
	if ((ksz8851_reg_read(REG_PORT_CTRL) & PORT_AUTO_NEG_RESTART) != PORT_AUTO_NEG_RESTART)
	{
		ksz8851_reg_clrbits(REG_PORT_CTRL, PORT_FORCE_FULL_DUPLEX);
	}

	/* Init step14: clear interrupt status. */
	ksz8851_reg_write(REG_INT_STATUS, 0xFFFF);

	/* Init step15: set interrupt mask. */
	ksz8851_reg_write(REG_INT_MASK, INT_RX);

	/* Init step16: enable QMU Transmit. */
	ksz8851_reg_setbits(REG_TX_CTRL, TX_CTRL_ENABLE);

	/* Init step17: enable QMU Receive. */
	ksz8851_reg_setbits(REG_RX_CTRL1, RX_CTRL_ENABLE);

	return 0;
}
