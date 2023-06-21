/**
 * \file
 *
 * \brief  LIN service for SAM.
 *
 * This file contains basic functions for the SAM USART, with support for all
 * modes, settings and clock speeds.
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
#ifndef LIN_H_INCLUDED
#define LIN_H_INCLUDED

#include "compiler.h"
#include "usart.h"

#include "conf_lin.h"

/*! \name LIN Versions
 */
//! @{
#define LIN_2x                        0      //!< LIN 2.x Version.
#define LIN_1x                        1      //!< LIN 1.x Version.
//! @}

/** LIN error type */
#define US_CSR_LIN_ERROR (US_CSR_LINBE | US_CSR_LINISFE | US_CSR_LINIPE | \
	US_CSR_LINCE | US_CSR_LINSNRE)

/*! @brief This enumeration is used to select an action for a specific message
 *        declared in st_lin_message structure.
 *        Note: XXX_STAND_BY keeps the direction (PUBLISH or SUBSCRIBE) for a
 *             message that will be IGNORE. When the 'stand_by' will be
 *             finished, PUBLISH_STAND_BY would become PUBLISH and
 *             SUBSCRIBE_STAND_BY would become SUBSCRIBE. An IGNORE message
 *             could become either PUBLISH or SUBSCRIBE.
 */
typedef enum {
  PUBLISH,            //!< The node sends the response
  SUBSCRIBE,          //!< The node receives the response
  IGNORE              //!< The node is not concerned by the response, it doesn't send or receive
} enum_lin_cmd;

/*! @brief This structure allows to handle a LIN message and, at the end of the
 *        received/transmitted message, allows to call a function associated
 *        to this message, the update or the capture of "signals".
 */
typedef  struct {
    //! LIN message ID (in case of LIN 1.3 - without lenght)
    uint8_t             uc_id;

    //! Length of the LIN message, it is the number of data bytes
    //! of the LIN response
    uint8_t             uc_dlc;

    //! Select an action for a specific message
    enum_lin_cmd   lin_cmd;

    //! Status of the last communication:
    //! - == 0x00: RXOK or TXOK
    //! - != 0x00: LINERR, content of LIN Error Register 'LINERR'
    uint8_t             uc_status;

    //! Pointer on the data buffer, the data buffer where the
    //! bytes of the LIN response are stored
    uint8_t*            uc_pt_data;

    //! Pointer on the function which handles the data. This
    //! has as parameter 'uc_pt_data'. This function could update
    //! the received 'signals' and could capture and store signals
    //! for the next transmission.
    void         (*pt_function)(uint8_t*);
} st_lin_message;

/*! @brief Error report definitions
 */
#define  LIN_OVERLOAD_INT     ((uint16_t)0x00FF)  //!< More than ONE interrupt in the same time !
#ifndef  LIN_LAST_ERR_LENGHT
#define  LIN_LAST_ERR_LENGHT   0x04          //!< Default lenght of the 'lin_last_error[]' array
#endif

uint8_t lin_init(Usart *usart_node, bool b_master, uint8_t uc_node,
		uint16_t us_rate, uint32_t ul_mck);

uint8_t lin_register_descriptor(uint8_t uc_node, uint8_t uc_frame_id,
		st_lin_message *lin_desc);

uint8_t lin_send_cmd(uint8_t uc_node, uint8_t uc_id, uint8_t uc_len);

void usart_lin_handler(uint8_t uc_node);

/**
 * \page sam_lin_quickstart Quick start guide for the SAM LIN module
 *
 * This is the quick start guide for the \ref sam_service_network_lin_group
 * "LIN module", with step-by-step instructions on how to configure and
 * use the driver in a selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section lin_use_cases LIN use cases
 * - \ref lin_master_use_case
 * - \ref lin_slave_use_case
 *
 * \section lin_master_use_case LIN master use case - Setup LIN master.
 * In this use case, the LIN node is set as a master PUBLISH. A
 * specific data will be sent via it.
 *
 * \subsection lin_master_use_case_setup_prereq Prerequisites
 * -# \ref gpio_group "General Purpose I/O Management (gpio)"
 * -# \ref sam_drivers_usart_group "Universal Synchronous Asynchronous Receiver Transmitter (USART)"
 * -# \ref sam_drivers_tc_group "Timer Counter (TC)"
 *
 * \subsection lin_master_use_case_setup_code Code
 * The following definitions must be added to the project.
 * \code
	#define LIN_FRAME_ID_12    0x12
	#define LIN_TRANSFER_BYTE    0x55
	#define LIN_MASTER_NODE_NUM 0
	#define TC_CHANNEL        0
	#define TC_FREQ             20
\endcode
 *
 * An array for the transfer bytes must be added:
 * \code
	uint8_t lin_data_node[8];
\endcode
 *
 * The Timer Counter are used to generate period cycle for the LIN
 * master transfer. More information about how to configure and
 * use TC can be found at \ref sam_drivers_tc_group.
 * \code
	 void configure_tc(void)
	 {
		uint32_t ul_div;
		uint32_t ul_tcclks;
		static uint32_t ul_sysclk;

		ul_sysclk = sysclk_get_cpu_hz();

		pmc_enable_periph_clk(ID_TC0);

		tc_find_mck_divisor(TC_FREQ, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
		tc_init(TC0, 0, ul_tcclks | TC_CMR_CPCTRG);
		tc_write_rc(TC0, 0, (ul_sysclk / ul_div) / TC_FREQ);

		NVIC_EnableIRQ((IRQn_Type)ID_TC0);
		tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
	 }
\endcode
 *
 * Add to application initialization:
 * \code
	 {
	    sysclk_init();
		board_init();

		pmc_enable_periph_clk(BOARD_ID_USART);

		lin_init( USART0, true, LIN_MASTER_NODE_NUM, 9600, sysclk_get_cpu_hz());

		lin_desc.uc_id = LIN_FRAME_ID_12;
		lin_desc.uc_dlc = sizeof(lin_data_node);
		lin_desc.lin_cmd = PUBLISH;
		lin_desc.uc_status = 0;
		lin_desc.uc_pt_data = lin_data_node;
		lin_register_desciptor(LIN_MASTER_NODE_NUM, 0, &lin_desc);

		configure_tc();
		tc_start(TC0, 0);
	 }
\endcode
 *
 * \subsection lin_basic_use_case_setup_code_lin_master Workflow
 * -# LIN master node ID:
 *   \code
	#define LIN_FRAME_ID_12    0x12
\endcode
 * -# First data of the transfer:
 *   \code
	#define LIN_TRANSFER_BYTE    0x55
\endcode
 * -# Mater node number:
 *   \code
	#define LIN_MASTER_NODE_NUM 0
\endcode
 * -# Timer Counter channel number:
 *   \code
	#define TC_CHANNEL        0
\endcode
 * -# Timer Counter frequency:
 *   \code
	#define TC_FREQ             20
\endcode
 * -# Initialize system clock:
 *   \code
	sysclk_init();
\endcode
 * -# Initialize board peripherals:
 *   \code
	board_init();
\endcode
 * -# Enable PMC for USART:
 *   \code
	pmc_enable_periph_clk(BOARD_ID_USART);
\endcode
 * -# Initialize LIN master, set the master with baudrate 9600:
 *   \code
	lin_init( USART0, true, LIN_MASTER_NODE_NUM, 9600, sysclk_get_cpu_hz());
\endcode
 * -# Set LIN master descriptor ID:
 *   \code
	lin_desc.uc_id = LIN_FRAME_ID_12;
\endcode
 * -# Set LIN master descriptor transfer size:
 *   \code
	lin_desc.uc_dlc = sizeof(lin_data_node);
\endcode
 * -# Set LIN master transfer type PUBLISHER:
 *   \code
	lin_desc.lin_cmd = PUBLISH;
\endcode
 * -# Set LIN master default transfer status:
 *   \code
	lin_desc.uc_status = 0;
\endcode
 * -# Set LIN master transfer data buffer:
 *   \code
	lin_desc.uc_pt_data = lin_data_node;
\endcode
 * -# Setup the master descriptor:
 *   \code
	lin_register_desciptor(LIN_MASTER_NODE_NUM, 0, &lin_desc);
\endcode
 * -# Initialize the Timer Counter:
 *   \code
	configure_tc();
\endcode
 * -# Start the Timer Counter:
 *   \code
	configure_tc();
\endcode
 *
 * \section lin_master_use_case_usage Use case
 *
 * \subsection lin_basic_use_case_usage_code Example code
 * Add to application C-file:
 * \code
	 void TC0_Handler(void)
	 {
		tc_get_status(TC0, 0);

		lin_data_node[0] = LIN_FIRST_BYTE;
		lin_send_cmd(LIN_MASTER_NODE_NUM, LIN_FRAME_ID_12,
				sizeof(lin_data_node));
	 }
\endcode
 *
 * \subsection lin_master_use_case_usage_flow Workflow
 * -# The LIN master period is generated by TC interrupt service routine:
 *   \code
	void TC0_Handler(void)
\endcode
 * -# Clear Timer Counter status:
 *   \code
	tc_get_status(TC0, 0);
\endcode
 * -# Set the first byte of the transfer:
 *   \code
	lin_data_node[0] = LIN_FIRST_BYTE;
\endcode
 * -# Start the transfer:
 *   \code
	       lin_send_cmd(LIN_MASTER_NODE_NUM, LIN_FRAME_ID_12,
				sizeof(lin_data_node));
\endcode
 *
 *
 * \section lin_slave_use_case LIN slave use case - Setup LIN slave.
 * In this use case, the LIN node is set as a slave subscriber. An LED will be
 * flash when a specific data received.
 *
 * \subsection lin_slave_use_case_setup_prereq Prerequisites
 * -# \ref gpio_group "General Purpose I/O Management (gpio)"
 * -# \ref sam_drivers_usart_group "Universal Synchronous Asynchronous Receiver Transmitter (USART)"
 * -# \ref sam_drivers_tc_group "Timer Counter (TC)"
 *
 * \subsection lin_slave_use_case_setup_code Code
 * The following definitions must be added to the project.
 * \code
	#define LIN_FRAME_ID_12    0x12
	#define LIN_SPECIFIC_BYTE    0x55
	#define LIN_SLAVE_NODE_NUM 0
\endcode
 *
 * An array for the received byte must be added:
 * \code
	uint8_t lin_data_node[8];
\endcode
 *
 * The usart0 interrupt service handler must be created to receive the LIN
 * frame.
 * \code
	void USART0_Handler(void)
	{
	     usart_lin_handler(LIN_SLAVE_NODE_NUM);
	}
\endcode
 *
 * Add to application initialization:
 * \code
	 {
	    sysclk_init();
		board_init();

		pmc_enable_periph_clk(BOARD_ID_USART);

		lin_init( USART0, false, LIN_SLAVE_NODE_NUM, 9600, sysclk_get_cpu_hz());

		lin_desc.uc_id = LIN_FRAME_ID_12;
		lin_desc.uc_dlc = sizeof(lin_data_node);
		lin_desc.lin_cmd = SUBSCRIBE;
		lin_desc.uc_status = 0;
		lin_desc.uc_pt_data = lin_data_node;
	    lin_desc.pt_function = lin_slave_task_ID12;
		lin_register_desciptor(LIN_MASTER_NODE_NUM, 0, &lin_desc);

		NVIC_EnableIRQ(USART0_IRQn);
		usart_enable_interrupt(USART0, US_IER_LINID);
\endcode
 *
 * \subsection lin_slave_use_case_setup_code Workflow
 * -# LIN slave node ID:
 *   \code
	#define LIN_FRAME_ID_12    0x12
\endcode
 * -# Specific data to flash the LED:
 *   \code
	#define LIN_SPECIFIC_BYTE    0x55
\endcode
 * -# Slave node number:
 *   \code
	#define LIN_SLAVE_NODE_NUM 0
\endcode
 * -# Initialize system clock:
 *   \code
	sysclk_init();
\endcode
 * -# Initialize board peripherals:
 *   \code
	board_init();
\endcode
 * -# Enable PMC for USART:
 *   \code
	pmc_enable_periph_clk(BOARD_ID_USART);
\endcode
 * -# Initialize LIN master, set the master with baudrate 9600:
 *   \code
	lin_init( USART0, false, LIN_SLAVE_NODE_NUM, 9600, sysclk_get_cpu_hz());
\endcode
 * -# Set LIN slave descriptor ID:
 *   \code
	lin_desc.uc_id = LIN_FRAME_ID_12;
\endcode
 * -# Set LIN master descriptor transfer size:
 *   \code
	lin_desc.uc_dlc = sizeof(lin_data_node);
\endcode
 * -# Set LIN slave transfer type SUBSCRIBE:
 *   \code
	lin_desc.lin_cmd = SUBSCRIBE;
\endcode
 * -# Set LIN master default transfer status:
 *   \code
	lin_desc.uc_status = 0;
\endcode
 * -# Set LIN slave transfer data buffer:
 *   \code
	lin_desc.uc_pt_data = lin_data_node;
\endcode
 * -# Set LIN slave task handle:
 *   \code
	lin_desc.pt_function = lin_slave_task_ID12;
\endcode
 * -# Setup the salve descriptor:
 *   \code
	lin_register_desciptor(LIN_SLAVE_NODE_NUM, 0, &lin_desc);
\endcode
 *
 * \section lin_slave_use_case_usage Use case
 *
 * \subsection lin_basic_use_case_usage_code Example code
 * Add to application C-file:
 * \code
	void  lin_slave_task_ID12(uint8_t *uc_buf)
	{
	     if (uc_buf[0] == LIN_SPECIFIC_BYTE) {
	                     LED_Toggle(LED0_GPIO);
	             }
	}
\endcode
 *
 * \subsection lin_master_use_case_usage_flow Workflow
 * -# The slave task is defined in the LIN descriptor.
 * \code
	void  lin_slave_task_ID12(uint8_t *uc_buf)
\endcode
 * -# Check if received the spcific byte and flash the LED.
 * \code
	if (uc_buf[0] == LIN_SPECIFIC_BYTE) {
	                LED_Toggle(LED0_GPIO);
	        }
\endcode
 */

#endif  /* LIN_H_INCLUDED */
