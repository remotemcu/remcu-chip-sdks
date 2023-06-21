/**
 * \file
 *
 * \brief SAM USART RS485 Quick Start
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "conf_rs485.h"


void usart_read_callback(struct usart_module *const usart_module);
void usart_write_callback(struct usart_module *const usart_module);

void configure_usart(void);
static void cdc_uart_init(void);
void configure_usart_callbacks(void);
void print_menu(void);

//Structure for UART module connected to EDBG
struct usart_module cdc_uart_module;
//Struct for RS485 USART
struct usart_module rs485_module;
//Data from RS485
uint16_t rec_data;
uint16_t tx_data;

char rs485_mode = CONF_RS485_MODE;

static void cdc_uart_init(void){
	struct usart_config usart_conf;

	//Configure USART for unit test output
	usart_get_config_defaults(&usart_conf);
	usart_conf.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	usart_conf.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	usart_conf.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	usart_conf.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	usart_conf.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	usart_conf.baudrate    = 9600;

	stdio_serial_init(&cdc_uart_module, EDBG_CDC_MODULE, &usart_conf);
	usart_enable(&cdc_uart_module);
}

void configure_usart(void){
	
	struct usart_config config_usart;
	
	usart_get_config_defaults(&config_usart);
	
	config_usart.baudrate    = 9600;
	config_usart.mux_setting = EXT1_RS485_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EXT1_RS485_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EXT1_RS485_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EXT1_RS485_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EXT1_RS485_SERCOM_PINMUX_PAD3;
	config_usart.rs485_guard_time = RS485_GUARD_TIME_1_BIT;
	
	while (usart_init(&rs485_module,EXT1_RS485_MODULE, &config_usart) != STATUS_OK){};
	
	usart_enable(&rs485_module);
	
}

void configure_usart_callbacks(void){
	
	usart_register_callback(&rs485_module,usart_write_callback, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_register_callback(&rs485_module,usart_read_callback, USART_CALLBACK_BUFFER_RECEIVED);
	
	usart_enable_callback(&rs485_module, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&rs485_module, USART_CALLBACK_BUFFER_RECEIVED);
	
}

void usart_read_callback(struct usart_module *const usart_module){
	if(rs485_mode == RS485_SLAVE){
		printf("\r\nRecieved: %c\r\n", rec_data);
		//Set up the next read...
		usart_read_job(&rs485_module, &rec_data);
		//Echo back to Master
		usart_write_job(&rs485_module, &rec_data);	
		}
	else{
		printf("\r\nEchoed: %c\r\n", rec_data);
		//Set up the next read...
		usart_read_job(&rs485_module, &rec_data);
		}
	
	
}

void usart_write_callback(struct usart_module *const usart_module){
	if(rs485_mode == RS485_MASTER)
		printf("\r\nSent: %c\r\n", tx_data);
}

void print_menu(void){
	printf("RS485 Half-Duplex Test\r\n");
	printf("Press 1:  Master Mode Set\r\n");
	printf("Press 2:  Slave Mode Set\r\n");
	printf("Press ?:  Display This Menu\r\n");
	if(rs485_mode == RS485_MASTER){	
		printf("Current Mode:  Master\r\n");
		printf("Send a character to the Slave:   ");
		}
	else
		printf("Current Mode:  Slave\r\n");	
}

int main(void)
{
	char txrx;
		
	system_init();

	//Start UART using EDBG for STDIO
	cdc_uart_init();
	//Configure RS485 USART
	configure_usart();
	//Callbacks for RS485 Comms
	configure_usart_callbacks();
	//Enable system Interrupts
	system_interrupt_enable_global();
	
	printf("RS485 Demonstration\r\n");
	print_menu();
	
	//set up first read job
	usart_read_job(&rs485_module, &rec_data);
	
	while (true) {
		if(rs485_mode == RS485_MASTER){
			scanf("%c",&txrx);
			if(txrx == RS485_MASTER || txrx == RS485_SLAVE)
				rs485_mode = txrx;
			else if(txrx == 0x03F)
				print_menu();
			else{
				tx_data = txrx;
				usart_write_job(&rs485_module, &tx_data);
				}			
			}		
		else{
			scanf("%c",&txrx);
			if(txrx == RS485_MASTER){
				//Switch to Master
				rs485_mode = RS485_MASTER;				
				}
			else if(txrx == 0x03F)
				print_menu();
			}
		}
}

