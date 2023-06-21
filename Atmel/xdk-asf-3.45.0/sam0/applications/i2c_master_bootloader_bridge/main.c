/**
 * \file
 *
 * \brief I2C Master Bootloader Bridge Application
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

/**
 * \mainpage SAM I2C Master Bootloader Bridge
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Features
 * \li Application as a bridge for I2C slave bootloader self programming
 * \li Uses USB Communication Device Class(CDC)
 * \li I2C Master sends the data to be programmed over I2C bus
 */

/**
 * \page appdoc_main SAM I2C Master Bootloader Bridge
 *
 * Overview:
 * - \ref appdoc_sam0_i2c_master_bootloader_bridge_features
 * - \ref appdoc_sam0_i2c_master_bootloader_bridge_intro
 * - \ref appdoc_sam0_i2c_master_bootloader_bridge_prereq
 * - \ref appdoc_sam0_i2c_master_bootloader_bridge_hw
 * - \ref appdoc_sam0_i2c_master_bootloader_bridge_protocol
 * - \ref appdoc_sam0_i2c_master_bootloader_bridge_compinfo
 * - \ref appdoc_sam0_i2c_master_bootloader_bridge_contactinfo
 *
 * \section appdoc_sam0_i2c_master_bootloader_bridge_features Features
 * \li Application as a bridge for I2C slave bootloader self programming
 * \li Uses USB Communication Device Class(CDC)
 * \li I2C master sends the data to be programmed over I2C bus
 *
 * \section appdoc_sam0_i2c_master_bootloader_bridge_intro Introduction
 * This application implements a USB Device CDC and a I2C master for SAM devices,
 * it works as a bridge between I2C slave and the USB CDC interface.
 *
 * This application has been tested on following boards:
 * - SAM D21 Xplained Pro
 *
 * \section appdoc_sam0_i2c_master_bootloader_bridge_prereq Prerequisites
 * A python script (bootloader.py in script folder) is used on the host PC to send data over
 * USB CDC  interface, example application bin file(to be programmed) starts at 0x2000.
 * To run the python script, execute a command for example as below:
 * python  bootloader.py -p COM20 -i led_toggle_flash.bin
 * Make sure that python environment is installed on your PC,
 *
 * \section appdoc_sam0_i2c_master_bootloader_bridge_hw Hardware Setup
 * For SAM D21 Xplained Pro:
 * I2C slave should be connected to PIN11 (PA08 - SDA) and PIN12 (PA09 - SCL)
 * on External header 1 (EXT1).
 *
 * \section appdoc_sam0_i2c_master_bootloader_bridge_protocol Communication Protocol
 *   - I2C Master first receives 4 bytes of data which contains the length of
 *     the data to be programmed for I2C slave.
 *   - Read a block from CDC interface of size NVMCTRL_PAGE_SIZE
 *   - Receive an acknowledgement byte 's' from I2C slave to indicate it has
 *     received the data and finished programming
 *   - Repeat till entire length of data has transferred and programmed.
 *
 *
 * \section appdoc_sam0_i2c_master_bootloader_bridge_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_i2c_master_bootloader_bridge_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 *
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <string.h>
#include <asf.h>
#include "conf_usb.h"
#include "ui.h"
#include "conf_app.h"

#define PATTERN_TEST_LENGTH (5 * UDI_CDC_DATA_EPS_FS_SIZE)
uint8_t cdc_data[PATTERN_TEST_LENGTH];

static volatile bool main_b_cdc_enable = false, b_cdc_data_rx = false;
static volatile bool b_wait = false, b_com_port_opened = false;

struct usart_module usart_instance;
struct i2c_master_module i2c_master_instance;

/**
 *  Configure UART console.
 */
static void configure_usart(void)
{

	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.generator_source = GCLK_GENERATOR_3;
	config_usart.baudrate    = 115200;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	stdio_serial_init(&usart_instance, EDBG_CDC_MODULE, &config_usart);
	usart_enable(&usart_instance);
}

/**
 *  Configure I2C master.
 */
static void configure_i2c_master(void)
{

	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	config_i2c_master.generator_source = GCLK_GENERATOR_3;
	config_i2c_master.buffer_timeout = 10000;
	config_i2c_master.pinmux_pad0	= BOOT_I2C_PAD0;
	config_i2c_master.pinmux_pad1	= BOOT_I2C_PAD1;
	i2c_master_init(&i2c_master_instance, SERCOM2, &config_i2c_master);

	i2c_master_enable(&i2c_master_instance);

}

/*! \brief Main function. Execution starts here.
 */
int main(void)
{

	uint8_t write_data[PATTERN_TEST_LENGTH];
	uint8_t read_data[PATTERN_TEST_LENGTH];
	uint32_t file_size = 0, remaining_len = 0;

	struct i2c_master_packet tx_buf = {
		.address     = SLAVE_ADDRESS,
		.data_length = PATTERN_TEST_LENGTH,
		.data        = write_data,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	struct i2c_master_packet rx_buf = {
		.address     = SLAVE_ADDRESS,
		.data_length = 1,
		.data        = read_data,
		.ten_bit_address = false,
		.high_speed      = false,
		.hs_master_code  = 0x0,
	};
	uint8_t nb_twi_packets_sent;
	uint16_t cdc_rx_size;

	irq_initialize_vectors();
	cpu_irq_enable();

	sleepmgr_init();
	system_init();
	configure_usart();

	ui_init();
	ui_powerdown();

	udc_start();
	printf("Start application\r\n");
	while (true) {

		if (!b_com_port_opened) {
			continue;
		}
		if (b_cdc_data_rx == true) {
			b_cdc_data_rx = false;
			cdc_rx_size = udi_cdc_get_nb_received_data();
			udi_cdc_read_buf((void *)cdc_data, cdc_rx_size);
			if (file_size == 0 && cdc_rx_size == 4) {
				MSB0W(file_size) = cdc_data[0];
				MSB1W(file_size) = cdc_data[1];
				MSB2W(file_size) = cdc_data[2];
				MSB3W(file_size) = cdc_data[3];
				printf("File size :%ld\r\n",file_size);
			}
			remaining_len += cdc_rx_size;

			if (cdc_rx_size == TARGET_PAGE_SIZE/2) {
				if (!b_wait) {
					memcpy((void *)(write_data), (const void *)cdc_data, cdc_rx_size);
					b_wait = true;
					if (file_size + 4 == remaining_len) {
						tx_buf.data_length = TARGET_PAGE_SIZE/2;
						while (i2c_master_write_packet_wait(&i2c_master_instance, &tx_buf) != STATUS_OK) ;
					}
				}
				else {
					memcpy((void *)(write_data + (TARGET_PAGE_SIZE/2)), (const void *)cdc_data, cdc_rx_size);
					tx_buf.data_length = TARGET_PAGE_SIZE;
					while (i2c_master_write_packet_wait(&i2c_master_instance, &tx_buf) != STATUS_OK) ;
					b_wait = false;
				}

			} else {
				if ((cdc_rx_size) <= PATTERN_TEST_LENGTH) {
					tx_buf.data_length = cdc_rx_size;
					memcpy((void *)(write_data), (const void *)cdc_data, cdc_rx_size);
					while (i2c_master_write_packet_wait(&i2c_master_instance, &tx_buf) != STATUS_OK) ;
				} else {
					nb_twi_packets_sent = 0;
					while(cdc_rx_size / PATTERN_TEST_LENGTH) {
						tx_buf.data_length = PATTERN_TEST_LENGTH;
						memcpy((void *)(write_data), (const void *)(&cdc_data[(nb_twi_packets_sent++) * (PATTERN_TEST_LENGTH)]), PATTERN_TEST_LENGTH);
						while (i2c_master_write_packet_wait(&i2c_master_instance, &tx_buf) != STATUS_OK) ;
						cdc_rx_size -= (PATTERN_TEST_LENGTH);
					}
					if(cdc_rx_size) {
						tx_buf.data_length = cdc_rx_size;
						memcpy((void *)(write_data), (const void *)(&cdc_data[(nb_twi_packets_sent) * (PATTERN_TEST_LENGTH)]), cdc_rx_size);
						while (i2c_master_write_packet_wait(&i2c_master_instance, &tx_buf) != STATUS_OK) ;
						cdc_rx_size = 0;
					}
				}
			}
		}
		if (i2c_master_read_packet_wait(&i2c_master_instance, &rx_buf) == STATUS_OK) {
			udi_cdc_write_buf((const void *)(rx_buf.data),(iram_size_t)read_data[0]);
			if (file_size + 4 == remaining_len) {
				printf("File transfer successfully, file size:%ld, transefer size :%ld\r\n",file_size,remaining_len-4);
			}
		}

	}
}

void main_suspend_action(void)
{
	ui_powerdown();
}

void main_resume_action(void)
{
	ui_wakeup();
}

void main_sof_action(void)
{
	if (!main_b_cdc_enable)
		return;
	ui_process(udd_get_frame_number());
}

#ifdef USB_DEVICE_LPM_SUPPORT
void main_suspend_lpm_action(void)
{
	ui_powerdown();
}

void main_remotewakeup_lpm_disable(void)
{
	ui_wakeup_disable();
}

void main_remotewakeup_lpm_enable(void)
{
	ui_wakeup_enable();
}
#endif

bool main_cdc_enable(uint8_t port)
{
	main_b_cdc_enable = true;
	configure_i2c_master();
	return true;
}

void main_cdc_disable(uint8_t port)
{
	main_b_cdc_enable = false;
	b_com_port_opened = false;
	i2c_master_disable(&i2c_master_instance);
}
void cdc_rx_notify(uint8_t port)
{
	b_cdc_data_rx = true;

}

void main_cdc_set_dtr(uint8_t port, bool b_enable)
{
	if (b_enable) {
		ui_com_open(port);
		b_com_port_opened = true;
	}else{
		ui_com_close(port);
		b_com_port_opened = false;
	}
}
