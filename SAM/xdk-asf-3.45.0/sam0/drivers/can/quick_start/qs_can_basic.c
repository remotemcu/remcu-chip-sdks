/**
 * \file
 *
 * \brief SAM CAN basic Quick Start
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <string.h>
#include <conf_can.h>

//! [module_var]

//! [module_inst]
static struct usart_module cdc_instance;
static struct can_module can_instance;
//! [module_inst]


//! [can_filter_setting]
#define CAN_RX_STANDARD_FILTER_INDEX_0    0
#define CAN_RX_STANDARD_FILTER_INDEX_1    1
#define CAN_RX_STANDARD_FILTER_ID_0     0x45A
#define CAN_RX_STANDARD_FILTER_ID_0_BUFFER_INDEX     2
#define CAN_RX_STANDARD_FILTER_ID_1     0x469
#define CAN_RX_EXTENDED_FILTER_INDEX_0    0
#define CAN_RX_EXTENDED_FILTER_INDEX_1    1
#define CAN_RX_EXTENDED_FILTER_ID_0     0x100000A5
#define CAN_RX_EXTENDED_FILTER_ID_0_BUFFER_INDEX     1
#define CAN_RX_EXTENDED_FILTER_ID_1     0x10000096
//! [can_filter_setting]

//! [can_transfer_message_setting]
#define CAN_TX_BUFFER_INDEX    0
static uint8_t tx_message_0[CONF_CAN_ELEMENT_DATA_SIZE];
static uint8_t tx_message_1[CONF_CAN_ELEMENT_DATA_SIZE];
//! [can_transfer_message_setting]

//! [can_receive_message_setting]
static volatile uint32_t standard_receive_index = 0;
static volatile uint32_t extended_receive_index = 0;
static struct can_rx_element_fifo_0 rx_element_fifo_0;
static struct can_rx_element_fifo_1 rx_element_fifo_1;
static struct can_rx_element_buffer rx_element_buffer;
//! [can_receive_message_setting]

//! [module_var]

//! [setup]

//! [cdc_setup]
static void configure_usart_cdc(void)
{

	struct usart_config config_cdc;
	usart_get_config_defaults(&config_cdc);
	config_cdc.baudrate	 = 38400;
	config_cdc.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_cdc.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_cdc.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_cdc.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_cdc.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	stdio_serial_init(&cdc_instance, EDBG_CDC_MODULE, &config_cdc);
	usart_enable(&cdc_instance);
}
//! [cdc_setup]

//! [can_init_setup]
static void configure_can(void)
{
	uint32_t i;
	/* Initialize the memory. */
	for (i = 0; i < CONF_CAN_ELEMENT_DATA_SIZE; i++) {
		tx_message_0[i] = i;
		tx_message_1[i] = i + 0x80;
	}

	/* Set up the CAN TX/RX pins */
	struct system_pinmux_config pin_config;
	system_pinmux_get_config_defaults(&pin_config);
	pin_config.mux_position = CAN_TX_MUX_SETTING;
	system_pinmux_pin_set_config(CAN_TX_PIN, &pin_config);
	pin_config.mux_position = CAN_RX_MUX_SETTING;
	system_pinmux_pin_set_config(CAN_RX_PIN, &pin_config);

	/* Initialize the module. */
	struct can_config config_can;
	can_get_config_defaults(&config_can);
	can_init(&can_instance, CAN_MODULE, &config_can);

	can_start(&can_instance);

	/* Enable interrupts for this CAN module */
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_CAN0);
	can_enable_interrupt(&can_instance, CAN_PROTOCOL_ERROR_ARBITRATION
			| CAN_PROTOCOL_ERROR_DATA);
}
//! [can_init_setup]

//! [can_receive_filter_setup]
static void can_set_standard_filter_0(void)
{
	struct can_standard_message_filter_element sd_filter;

	can_get_standard_message_filter_element_default(&sd_filter);
	sd_filter.S0.bit.SFID2 = CAN_RX_STANDARD_FILTER_ID_0_BUFFER_INDEX;
	sd_filter.S0.bit.SFID1 = CAN_RX_STANDARD_FILTER_ID_0;
	sd_filter.S0.bit.SFEC =
			CAN_STANDARD_MESSAGE_FILTER_ELEMENT_S0_SFEC_STRXBUF_Val;

	can_set_rx_standard_filter(&can_instance, &sd_filter,
			CAN_RX_STANDARD_FILTER_INDEX_0);
	can_enable_interrupt(&can_instance, CAN_RX_BUFFER_NEW_MESSAGE);
}

static void can_set_standard_filter_1(void)
{
	struct can_standard_message_filter_element sd_filter;

	can_get_standard_message_filter_element_default(&sd_filter);
	sd_filter.S0.bit.SFID1 = CAN_RX_STANDARD_FILTER_ID_1;

	can_set_rx_standard_filter(&can_instance, &sd_filter,
			CAN_RX_STANDARD_FILTER_INDEX_1);
	can_enable_interrupt(&can_instance, CAN_RX_FIFO_0_NEW_MESSAGE);
}

static void can_set_extended_filter_0(void)
{
	struct can_extended_message_filter_element et_filter;

	can_get_extended_message_filter_element_default(&et_filter);
	et_filter.F0.bit.EFID1 = CAN_RX_EXTENDED_FILTER_ID_0;
	et_filter.F0.bit.EFEC =
			CAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC_STRXBUF_Val;
	et_filter.F1.bit.EFID2 = CAN_RX_EXTENDED_FILTER_ID_0_BUFFER_INDEX;

	can_set_rx_extended_filter(&can_instance, &et_filter,
			CAN_RX_EXTENDED_FILTER_INDEX_0);
	can_enable_interrupt(&can_instance, CAN_RX_BUFFER_NEW_MESSAGE);
}

static void can_set_extended_filter_1(void)
{
	struct can_extended_message_filter_element et_filter;

	can_get_extended_message_filter_element_default(&et_filter);
	et_filter.F0.bit.EFID1 = CAN_RX_EXTENDED_FILTER_ID_1;

	can_set_rx_extended_filter(&can_instance, &et_filter,
			CAN_RX_EXTENDED_FILTER_INDEX_1);
	can_enable_interrupt(&can_instance, CAN_RX_FIFO_1_NEW_MESSAGE);
}

//! [can_receive_filter_setup]

//! [can_transfer_message_setup]
static void can_send_standard_message(uint32_t id_value, uint8_t *data,
		uint32_t data_length)
{
	uint32_t i;
	struct can_tx_element tx_element;

	can_get_tx_buffer_element_defaults(&tx_element);
	tx_element.T0.reg |= CAN_TX_ELEMENT_T0_STANDARD_ID(id_value);
	tx_element.T1.bit.DLC = data_length;
	for (i = 0; i < data_length; i++) {
		tx_element.data[i] = *data;
		data++;
	}

	can_set_tx_buffer_element(&can_instance, &tx_element,
			CAN_TX_BUFFER_INDEX);
	can_tx_transfer_request(&can_instance, 1 << CAN_TX_BUFFER_INDEX);
}

static void can_send_extended_message(uint32_t id_value, uint8_t *data,
		uint32_t data_length)
{
	uint32_t i;
	struct can_tx_element tx_element;

	can_get_tx_buffer_element_defaults(&tx_element);
	tx_element.T0.reg |= CAN_TX_ELEMENT_T0_EXTENDED_ID(id_value) |
			CAN_TX_ELEMENT_T0_XTD;
	tx_element.T1.bit.DLC = data_length;
	for (i = 0; i < data_length; i++) {
		tx_element.data[i] = *data;
		data++;
	}

	can_set_tx_buffer_element(&can_instance, &tx_element,
			CAN_TX_BUFFER_INDEX);
	can_tx_transfer_request(&can_instance, 1 << CAN_TX_BUFFER_INDEX);
}

//! [can_transfer_message_setup]

//! [can_interrupt_handler]
void CAN0_Handler(void)
{
	volatile uint32_t status, i, rx_buffer_index;
	status = can_read_interrupt_status(&can_instance);

	if (status & CAN_RX_BUFFER_NEW_MESSAGE) {
		can_clear_interrupt_status(&can_instance, CAN_RX_BUFFER_NEW_MESSAGE);
		for (i = 0; i < CONF_CAN0_RX_BUFFER_NUM; i++) {
			if (can_rx_get_buffer_status(&can_instance, i)) {
				rx_buffer_index = i;
				can_rx_clear_buffer_status(&can_instance, i);
				can_get_rx_buffer_element(&can_instance, &rx_element_buffer,
				rx_buffer_index);
				if (rx_element_buffer.R0.bit.XTD) {
					printf("\n\r Extended message received in Rx buffer. The received data is: \r\n");
				} else {
					printf("\n\r Standard message received in Rx buffer. The received data is: \r\n");
				}
				for (i = 0; i < rx_element_buffer.R1.bit.DLC; i++) {
					printf("  %d",rx_element_buffer.data[i]);
				}
				printf("\r\n\r\n");
			}
		}
	}

	if (status & CAN_RX_FIFO_0_NEW_MESSAGE) {
		can_clear_interrupt_status(&can_instance, CAN_RX_FIFO_0_NEW_MESSAGE);
		can_get_rx_fifo_0_element(&can_instance, &rx_element_fifo_0,
				standard_receive_index);
		can_rx_fifo_acknowledge(&can_instance, 0,
				standard_receive_index);
		standard_receive_index++;
		if (standard_receive_index == CONF_CAN0_RX_FIFO_0_NUM) {
			standard_receive_index = 0;
		}

		printf("\n\r Standard message received in FIFO 0. The received data is: \r\n");
		for (i = 0; i < rx_element_fifo_0.R1.bit.DLC; i++) {
			printf("  %d",rx_element_fifo_0.data[i]);
		}
		printf("\r\n\r\n");
	}

	if (status & CAN_RX_FIFO_1_NEW_MESSAGE) {
		can_clear_interrupt_status(&can_instance, CAN_RX_FIFO_1_NEW_MESSAGE);
		can_get_rx_fifo_1_element(&can_instance, &rx_element_fifo_1,
				extended_receive_index);
		can_rx_fifo_acknowledge(&can_instance, 0,
				extended_receive_index);
		extended_receive_index++;
		if (extended_receive_index == CONF_CAN0_RX_FIFO_1_NUM) {
			extended_receive_index = 0;
		}

		printf("\n\r Extended message received in FIFO 1. The received data is: \r\n");
		for (i = 0; i < rx_element_fifo_1.R1.bit.DLC; i++) {
			printf("  %d",rx_element_fifo_1.data[i]);
		}
		printf("\r\n\r\n");
	}

	if ((status & CAN_PROTOCOL_ERROR_ARBITRATION)
			|| (status & CAN_PROTOCOL_ERROR_DATA)) {
		can_clear_interrupt_status(&can_instance, CAN_PROTOCOL_ERROR_ARBITRATION
			 	| CAN_PROTOCOL_ERROR_DATA);
		printf("Protocol error, please double check the clock in two boards. \r\n\r\n");
	}
}
//! [can_interrupt_handler]

//! [user_menu]
static void display_menu(void)
{
	printf("Menu :\r\n"
			"  -- Select the action:\r\n"
			"  0: Set standard filter ID 0: 0x45A, store into Rx buffer. \r\n"
			"  1: Set standard filter ID 1: 0x469, store into Rx FIFO 0. \r\n"
			"  2: Send standard message with ID: 0x45A and 4 byte data 0 to 3. \r\n"
			"  3: Send standard message with ID: 0x469 and 4 byte data 128 to 131. \r\n"
			"  4: Set extended filter ID 0: 0x100000A5, store into Rx buffer. \r\n"
			"  5: Set extended filter ID 1: 0x10000096, store into Rx FIFO 1. \r\n"
			"  6: Send extended message with ID: 0x100000A5 and 8 byte data 0 to 7. \r\n"
			"  7: Send extended message with ID: 0x10000096 and 8 byte data 128 to 135. \r\n"
			"  h: Display menu \r\n\r\n");
}
//! [user_menu]

//! [setup]

int main(void)
{
	uint8_t key;

//! [setup_init]
	system_init();
	configure_usart_cdc();
//! [setup_init]

//! [main_setup]

//! [configure_can]
	configure_can();
//! [configure_can]

//! [display_user_menu]
	display_menu();
//! [display_user_menu]

//! [main_loop]
	while(1) {
		scanf("%c", (char *)&key);

		switch (key) {
		case 'h':
			display_menu();
			break;

		case '0':
			printf("  0: Set standard filter ID 0: 0x45A, store into Rx buffer. \r\n");
			can_set_standard_filter_0();
			break;

		case '1':
			printf("  1: Set standard filter ID 1: 0x469, store into Rx FIFO 0. \r\n");
			can_set_standard_filter_1();
			break;

		case '2':
			printf("  2: Send standard message with ID: 0x45A and 4 byte data 0 to 3. \r\n");
			can_send_standard_message(CAN_RX_STANDARD_FILTER_ID_0, tx_message_0,
					CONF_CAN_ELEMENT_DATA_SIZE / 2);
			break;

		case '3':
			printf("  3: Send standard message with ID: 0x469 and 4 byte data 128 to 131. \r\n");
			can_send_standard_message(CAN_RX_STANDARD_FILTER_ID_1, tx_message_1,
					CONF_CAN_ELEMENT_DATA_SIZE / 2);
			break;

		case '4':
			printf("  4: Set extended filter ID 0: 0x100000A5, store into Rx buffer. \r\n");
			can_set_extended_filter_0();
			break;

		case '5':
			printf("  5: Set extended filter ID 1: 0x10000096, store into Rx FIFO 1. \r\n");
			can_set_extended_filter_1();
			break;

		case '6':
			printf("  6: Send extended message with ID: 0x100000A5 and 8 byte data 0 to 7. \r\n");
			can_send_extended_message(CAN_RX_EXTENDED_FILTER_ID_0, tx_message_0,
					CONF_CAN_ELEMENT_DATA_SIZE);
			break;

		case '7':
			printf("  7: Send extended message with ID: 0x10000096 and 8 byte data 128 to 135. \r\n");
			can_send_extended_message(CAN_RX_EXTENDED_FILTER_ID_1, tx_message_1,
					CONF_CAN_ELEMENT_DATA_SIZE);
			break;

		default:
			break;
		}
	}
//! [main_loop]

//! [main_setup]
}
