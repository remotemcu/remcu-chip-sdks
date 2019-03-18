/**
 * \file
 *
 * \brief SAM USART Quick Start
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
#include <asf.h>

void configure_usart(void);

//! [module_inst]
struct usart_module usart_instance;
//! [module_inst]

//! [setup]
void configure_usart(void)
{
//! [setup_config]
	struct usart_config config_usart;
//! [setup_config]
//! [setup_config_defaults]
	usart_get_config_defaults(&config_usart);
//! [setup_config_defaults]

//! [setup_change_config]
#if(SAMR30E)
{
	config_usart.baudrate    = 9600;
config_usart.mux_setting = CDC_SERCOM_MUX_SETTING;
config_usart.pinmux_pad0 = CDC_SERCOM_PINMUX_PAD0;
config_usart.pinmux_pad1 = CDC_SERCOM_PINMUX_PAD1;
config_usart.pinmux_pad2 = CDC_SERCOM_PINMUX_PAD2;
config_usart.pinmux_pad3 = CDC_SERCOM_PINMUX_PAD3;
//! [setup_change_config]

//! [setup_set_config]
while (usart_init(&usart_instance,
  CDC_MODULE, &config_usart) != STATUS_OK) {
}
//! [setup_set_config]
}
#else
{
	config_usart.baudrate    = 9600;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
//! [setup_change_config]

//! [setup_set_config]
	while (usart_init(&usart_instance,
			EDBG_CDC_MODULE, &config_usart) != STATUS_OK) {
	}
//! [setup_set_config]
}
#endif
//! [setup_enable]
	usart_enable(&usart_instance);
//! [setup_enable]
}
//! [setup]

int main(void)
{
	system_init();

//! [setup_init]
	configure_usart();
//! [setup_init]

//! [main]
//! [main_send_string]
	uint8_t string[] = "Hello World!\r\n";
	usart_write_buffer_wait(&usart_instance, string, sizeof(string));
//! [main_send_string]

//! [main_rec_var]
	uint16_t temp;
//! [main_rec_var]

//! [main_loop]
	while (true) {
//! [main_read]
		if (usart_read_wait(&usart_instance, &temp) == STATUS_OK) {
//! [main_read]
//! [main_write]
			while (usart_write_wait(&usart_instance, temp) != STATUS_OK) {
			}
//! [main_write]
		}
	}
//! [main_loop]
//! [main]
}
