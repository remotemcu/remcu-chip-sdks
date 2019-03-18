/**
 * \file
 *
 * \brief SAM Uart driver with DMA quick start
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
//! [module_inst]
struct uart_module uart_instance;
//! [module_inst]


//! [dma_resource]
struct dma_resource uart_dma_resource_tx;
struct dma_resource uart_dma_resource_rx;
//! [dma_resource]

//! [usart_buffer]
#define BUFFER_LEN    8
static uint8_t string[BUFFER_LEN];
//! [usart_buffer]


//! [transfer_descriptor]
struct dma_descriptor example_descriptor_tx;
struct dma_descriptor example_descriptor_rx;
//! [transfer_descriptor]

//! [setup]
//! [transfer_done_tx]
static void transfer_done_tx(struct dma_resource* const resource )
{
	dma_start_transfer_job(&uart_dma_resource_rx);
}
//! [transfer_done_tx]

//! [transfer_done_rx]
static void transfer_done_rx(struct dma_resource* const resource )
{
	dma_start_transfer_job(&uart_dma_resource_tx);
}
//! [transfer_done_rx]

//! [config_dma_resource_tx]
static void configure_dma_resource_tx(struct dma_resource *resource)
{
//! [setup_tx_1]
	struct dma_resource_config config;
//! [setup_tx_1]

//! [setup_tx_2]
	dma_get_config_defaults(&config);
//! [setup_tx_2]

//! [setup_tx_3]
	config.des.periph = UART0TX_DMA_PERIPHERAL;
	config.des.enable_inc_addr = false;
	config.src.periph = UART0TX_DMA_PERIPHERAL;
//! [setup_tx_3]

//! [setup_tx_4]
	dma_allocate(resource, &config);
//! [setup_tx_4]
}
//! [config_dma_resource_tx]

//! [setup_dma_transfer_tx_descriptor]
static void setup_transfer_descriptor_tx(struct dma_descriptor *descriptor)
{

//! [setup_tx_5]
	dma_descriptor_get_config_defaults(descriptor);
//! [setup_tx_5]

//! [setup_tx_6]
	descriptor->buffer_size = BUFFER_LEN;
	descriptor->read_start_addr = (uint32_t)string;
	descriptor->write_start_addr = 
			(uint32_t)(&uart_instance.hw->TRANSMIT_DATA.reg);
//! [setup_tx_6]
}
//! [setup_dma_transfer_tx_descriptor]

//! [config_dma_resource_rx]
static void configure_dma_resource_rx(struct dma_resource *resource)
{
	//! [setup_rx_1]
	struct dma_resource_config config;
	//! [setup_rx_1]

	//! [setup_rx_2]
	dma_get_config_defaults(&config);
	//! [setup_rx_2]

	//! [setup_rx_3]
	config.src.periph = UART0RX_DMA_PERIPHERAL;
	config.src.enable_inc_addr = false;
	config.src.periph_delay = 1;
	//! [setup_rx_3]

	//! [setup_rx_4]
	dma_allocate(resource, &config);
	//! [setup_rx_4]
}
//! [config_dma_resource_rx]

//! [setup_dma_transfer_rx_descriptor]
static void setup_transfer_descriptor_rx(struct dma_descriptor *descriptor)
{
	//! [setup_rx_5]
	dma_descriptor_get_config_defaults(descriptor);
	//! [setup_rx_5]

	//! [setup_tx_6]
	descriptor->buffer_size = BUFFER_LEN;
	descriptor->read_start_addr =
			(uint32_t)(&uart_instance.hw->RECEIVE_DATA.reg);
	descriptor->write_start_addr = (uint32_t)string;
	//! [setup_tx_6]
}
//! [setup_dma_transfer_rx_descriptor]

//! [setup_usart]
static void configure_usart(void)
{
//! [setup_config]
	struct uart_config config_uart;
//! [setup_config]

//! [setup_config_defaults]
	uart_get_config_defaults(&config_uart);
//! [setup_config_defaults]

//! [setup_change_config]
	config_uart.baud_rate = 115200;
	config_uart.pin_number_pad[0] = EDBG_CDC_PIN_PAD0;
	config_uart.pin_number_pad[1] = EDBG_CDC_PIN_PAD1;
	config_uart.pin_number_pad[2] = EDBG_CDC_PIN_PAD2;
	config_uart.pin_number_pad[3] = EDBG_CDC_PIN_PAD3;
	config_uart.pinmux_sel_pad[0] = EDBG_CDC_MUX_PAD0;
	config_uart.pinmux_sel_pad[1] = EDBG_CDC_MUX_PAD1;
	config_uart.pinmux_sel_pad[2] = EDBG_CDC_MUX_PAD2;
	config_uart.pinmux_sel_pad[3] = EDBG_CDC_MUX_PAD3;
//! [setup_change_config]

//! [setup_set_config]
	while (uart_init(&uart_instance,
			EDBG_CDC_MODULE, &config_uart) != STATUS_OK) {
	}
//! [setup_set_config]

//! [enable_interrupt]
	uart_enable_transmit_dma(&uart_instance);
	uart_enable_receive_dma(&uart_instance);
//! [enable_interrupt]
}
//! [setup_usart]

//! [setup_callback]
static void configure_dma_callback(void)
{
//! [setup_callback_register]
	dma_register_callback(&uart_dma_resource_tx, transfer_done_tx, DMA_CALLBACK_TRANSFER_DONE);
	dma_register_callback(&uart_dma_resource_rx, transfer_done_rx, DMA_CALLBACK_TRANSFER_DONE);
//! [setup_callback_register]

//! [setup_enable_callback]
	dma_enable_callback(&uart_dma_resource_tx, DMA_CALLBACK_TRANSFER_DONE);
	dma_enable_callback(&uart_dma_resource_rx, DMA_CALLBACK_TRANSFER_DONE);
//! [setup_enable_callback]

//! [enable_inic]
	NVIC_EnableIRQ(PROV_DMA_CTRL0_IRQn);
//! [enable_inic]
}
//! [setup_callback]

//! [setup]

int main(void)
{
	/**
	 * For make this QS work, disable the systick to stop task switch.
	 * Should not do it if you want the BLE functions.
	 */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

//! [setup_init]
//! [init_system]
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);
//! [init_system]

//! [setup_usart]
	configure_usart();
//! [setup_usart]

//! [setup_dma_resource]
	configure_dma_resource_tx(&uart_dma_resource_tx);
	configure_dma_resource_rx(&uart_dma_resource_rx);
//! [setup_dma_resource]

//! [setup_transfer_descriptor]
	setup_transfer_descriptor_tx(&example_descriptor_tx);
	setup_transfer_descriptor_rx(&example_descriptor_rx);
//! [setup_transfer_descriptor]

//! [add_descriptor_to_resource]
	dma_add_descriptor(&uart_dma_resource_tx, &example_descriptor_tx);
	dma_add_descriptor(&uart_dma_resource_rx, &example_descriptor_rx);
//! [add_descriptor_to_resource]

//! [configure_callback]
	configure_dma_callback();
//! [configure_callback]
//! [setup_init]

//! [main]
//! [main_1]
	dma_start_transfer_job(&uart_dma_resource_rx);
//! [main_1]

//! [endless_loop]
	while (true) {
	}
//! [endless_loop]
//! [main]
}
