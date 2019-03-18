/**
 * \file
 *
 * \brief Monitor functions for SAM-BA on SAM0
 * Port of rom monitor functions from legacy sam-ba software
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <string.h>
#include "sam_ba_monitor.h"
#include "usart_sam_ba.h"
#include "conf_board.h"

const char RomBOOT_Version[] = SAM_BA_VERSION;

/* Provides one common interface to handle both USART and USB-CDC */
typedef struct
{
	/* send one byte of data */
	int (*putc)(int value);
	/* Get one byte */
	int (*getc)(void);
	/* Receive buffer not empty */
	bool (*is_rx_ready)(void);
	/* Send given data (polling) */
	uint32_t (*putdata)(void const* data, uint32_t length);
	/* Get data from comm. device */
	uint32_t (*getdata)(void* data, uint32_t length);
	/* Send given data (polling) using xmodem (if necessary) */
	uint32_t (*putdata_xmd)(void const* data, uint32_t length);
	/* Get data from comm. device using xmodem (if necessary) */
	uint32_t (*getdata_xmd)(void* data, uint32_t length);
} t_monitor_if;

/* Initialize structures with function pointers from supported interfaces */
const t_monitor_if uart_if =
{ usart_putc, usart_getc, usart_is_rx_ready, usart_putdata, usart_getdata,
		usart_putdata_xmd, usart_getdata_xmd };

#ifdef CONF_USBCDC_INTERFACE_SUPPORT
//Please note that USB doesn't use Xmodem protocol, since USB already includes flow control and data verification
//Data are simply forwarded without further coding.
const t_monitor_if usbcdc_if =
{ udi_cdc_putc, udi_cdc_getc, udi_cdc_is_rx_ready, udi_cdc_write_buf,
		udi_cdc_read_no_polling, udi_cdc_write_buf, udi_cdc_read_buf };
#endif

/* The pointer to the interface object use by the monitor */
t_monitor_if * ptr_monitor_if;

/* b_terminal_mode mode (ascii) or hex mode */
volatile bool b_terminal_mode = false;


/**
 * \brief This function initializes the SAM-BA monitor
 *
 * \param com_interface  Communication interface to be used.
 */
void sam_ba_monitor_init(uint8_t com_interface)
{
	/* Selects the requested interface for future actions */
	if (com_interface == SAM_BA_INTERFACE_USART)
		ptr_monitor_if = (t_monitor_if*) &uart_if;
#ifdef CONF_USBCDC_INTERFACE_SUPPORT
	if (com_interface == SAM_BA_INTERFACE_USBCDC)
		ptr_monitor_if = (t_monitor_if*) &usbcdc_if;
#endif
}


/**
 * \brief This function allows data rx by USART
 *
 * \param *data  Data pointer
 * \param length Length of the data
 */
void sam_ba_putdata_term(uint8_t* data, uint32_t length)
{
	uint8_t temp, buf[12], *data_ascii;
	uint32_t i, int_value;

	if (b_terminal_mode)
	{
		if (length == 4)
			int_value = *(uint32_t *) data;
		else if (length == 2)
			int_value = *(uint16_t *) data;
		else
			int_value = *(uint8_t *) data;

		data_ascii = buf + 2;
		data_ascii += length * 2 - 1;

		for (i = 0; i < length * 2; i++)
		{
			temp = (uint8_t) (int_value & 0xf);

			if (temp <= 0x9)
				*data_ascii = temp | 0x30;
			else
				*data_ascii = temp + 0x37;

			int_value >>= 4;
			data_ascii--;
		}
		buf[0] = '0';
		buf[1] = 'x';
		buf[length * 2 + 2] = '\n';
		buf[length * 2 + 3] = '\r';
		ptr_monitor_if->putdata(buf, length * 2 + 4);
	}
	else
		ptr_monitor_if->putdata(data, length);
	return;
}

volatile uint32_t sp;
/**
 * \brief Execute an applet from the specified address
 *
 * \param address Applet address
 */
void call_applet(uint32_t address)
{
	uint32_t app_start_address;

	cpu_irq_disable();

	sp = __get_MSP();

	/* Rebase the Stack Pointer */
	__set_MSP(*(uint32_t *) address);

	/* Load the Reset Handler address of the application */
	app_start_address = *(uint32_t *)(address + 4);

	/* Jump to application Reset Handler in the application */
	asm("bx %0"::"r"(app_start_address));
}


uint32_t current_number;
uint32_t i, length;
uint8_t command, *ptr_data, *ptr, data[SIZEBUFMAX];
uint8_t j;
uint32_t u32tmp;


/**
 * \brief This function starts the SAM-BA monitor.
 */
void sam_ba_monitor_run(void)
{
	ptr_data = NULL;
	command = 'z';

	// Start waiting some cmd
	while (1)
	{
		length = ptr_monitor_if->getdata(data, SIZEBUFMAX);
		ptr = data;
		for (i = 0; i < length; i++)
		{
			if (*ptr != 0xff)
			{
				if (*ptr == '#')
				{
					if (b_terminal_mode)
					{
						ptr_monitor_if->putdata("\n\r", 2);
					}
					if (command == 'S')
					{
						//Check if some data are remaining in the "data" buffer
						if(length>i)
						{
							//Move current indexes to next avail data (currently ptr points to "#")
							ptr++;
							i++;
							//We need to add first the remaining data of the current buffer already read from usb
							//read a maximum of "current_number" bytes
							u32tmp=min((length-i),current_number);
							for(j=0;j<u32tmp;j++)
							{
								*ptr_data = *ptr;
								ptr_data++;
								ptr++;
								i++;
							}
						}
						//update i with the data read from the buffer
						i--;
						ptr--;
						//Do we expect more data ?
						if(j<current_number)
							ptr_monitor_if->getdata_xmd(ptr_data, current_number-j);

						__asm("nop");
					}
					else if (command == 'R')
					{
						ptr_monitor_if->putdata_xmd(ptr_data, current_number);
					}
					else if (command == 'O')
					{
						*ptr_data = (char) current_number;
					}
					else if (command == 'H')
					{
						*((uint16_t *) ptr_data) = (uint16_t) current_number;
					}
					else if (command == 'W')
					{
						*((int *) ptr_data) = current_number;
					}
					else if (command == 'o')
					{
						sam_ba_putdata_term(ptr_data, 1);
					}
					else if (command == 'h')
					{
						current_number = *((uint16_t *) ptr_data);
						sam_ba_putdata_term((uint8_t*) &current_number, 2);
					}
					else if (command == 'w')
					{
						current_number = *((uint32_t *) ptr_data);
						sam_ba_putdata_term((uint8_t*) &current_number, 4);
					}
					else if (command == 'G')
					{
						call_applet(current_number);
						/* Rebase the Stack Pointer */
						__set_MSP(sp);
						cpu_irq_enable();
					}
					else if (command == 'T')
					{
						b_terminal_mode = 1;
						ptr_monitor_if->putdata("\n\r", 2);
					}
					else if (command == 'N')
					{
						if (b_terminal_mode == 0)
						{
							ptr_monitor_if->putdata("\n\r", 2);
						}
						b_terminal_mode = 0;
					}
					else if (command == 'V')
					{
						ptr_monitor_if->putdata("v", 1);
						ptr_monitor_if->putdata((uint8_t *) RomBOOT_Version,
								strlen(RomBOOT_Version));
						ptr_monitor_if->putdata(" ", 1);
						ptr = (uint8_t*) &(__DATE__);
						i = 0;
						while (*ptr++ != '\0')
							i++;
						ptr_monitor_if->putdata((uint8_t *) &(__DATE__), i);
						ptr_monitor_if->putdata(" ", 1);
						i = 0;
						ptr = (uint8_t*) &(__TIME__);
						while (*ptr++ != '\0')
							i++;
						ptr_monitor_if->putdata((uint8_t *) &(__TIME__), i);
						ptr_monitor_if->putdata("\n\r", 2);
					}

					command = 'z';
					current_number = 0;

					if (b_terminal_mode)
					{
						ptr_monitor_if->putdata(">", 1);
					}
				}
				else
				{
					if (('0' <= *ptr) && (*ptr <= '9'))
					{
						current_number = (current_number << 4) | (*ptr - '0');

					}
					else if (('A' <= *ptr) && (*ptr <= 'F'))
					{
						current_number = (current_number << 4)
								| (*ptr - 'A' + 0xa);

					}
					else if (('a' <= *ptr) && (*ptr <= 'f'))
					{
						current_number = (current_number << 4)
								| (*ptr - 'a' + 0xa);

					}
					else if (*ptr == ',')
					{
						ptr_data = (uint8_t *) current_number;
						current_number = 0;

					}
					else
					{
						command = *ptr;
						current_number = 0;
					}
				}
				ptr++;
			}
		}
	}
}
