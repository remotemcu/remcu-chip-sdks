/**
 * \file
 *
 * \brief Communication between USART and SPI slave/I2C slave Demo.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage Communication between USART and SPI slave/I2C slave Demo
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This demo can run three modes for communication between SERCOM SPI slave with USART
 * or I2C slave with USART.
 * It consists of three modes for the following functionalities:
 * - Mode 0: I2C slave read & write with I2C master. In this mode, the message which received from
 * I2C master will display on terminal by USART. Press the key according to the menu and I2C slave
 * will send them to I2C master.
 * - Mode 1: SPI slave read & write with SPI master. In this mode, the message which received from
 * SPI master will display on terminal by USART. Press the key according to the menu and SPI slave
 * will send them to SPI master.
 * - Mode 2: SPI/I2C slave only read with SPI/I2C master. In this mode, the message both received from
 * SPI master and I2C master will display on terminal by USART.
 */

/**
 * \page appdoc_main Communication between USART and SPI slave/I2C slave Demo
 *
 * Overview:
 * - \ref appdoc_sam0_com_usart_spi_i2c_slave_demo_intro
 * - \ref appdoc_sam0_com_usart_spi_i2c_slave_demo_setup
 * - \ref appdoc_sam0_com_usart_spi_i2c_slave_demo_usage
 * - \ref appdoc_sam0_com_usart_spi_i2c_slave_demo_compinfo
 * - \ref appdoc_sam0_com_usart_spi_i2c_slave_demo_contactinfo
 *
 * \section appdoc_sam0_com_usart_spi_i2c_slave_demo_intro Introduction
 * \copydetails appdoc_preface
 *
 * The following kit is required for running the application:
 * - SAM D11 Xplained Pro board
 * - other boards which can play as SPI master or I2C master for validation
 *
 * \section appdoc_sam0_com_usart_spi_i2c_slave_demo_setup Setup
 * The following connections should be made using wires in related mode:
 * - SPI module
 *  - \b SS_0:  EXT1 PIN15
 *  - \b DO/DI: EXT1 PIN16
 *  - \b DI/DO: EXT1 PIN17
 *  - \b SCK:   EXT1 PIN18
 * - I2C module
 *  - \b SDA:   EXT1 PIN11
 *  - \b SCL:   EXT1 PIN12
 * \note the wires should be connected correctly with master, otherwise the application will
 * run unexpectedly.
 *
 * To run the application:
 *  - Connect the SAM D11 Xplained Pro board with SPI master board / I2C master board.
 *  - Connect the SAM D11 Xplained Pro board to the computer using a
 *    micro USB cable.
 *  - Open the virtual COM port in a terminal application.
 *    \note The USB composite firmware running on the Embedded Debugger (EDBG)
 *          will enumerate as debugger, virtual COM port and EDBG data
 *          gateway.
 *  - Build the project, program the target and run the application.
 *    The terminal shows related info according to the running mode.
 *
 * \section appdoc_sam0_com_usart_spi_i2c_slave_demo_usage
 *  - In Mode 0, the message received from I2C master will display in terminal. User can press
 *  the key according to menu, and I2C slave will send back message to I2C master.
 *  - In Mode 1, the message received from SPI master will display in terminal. User can press
 *  the key according to menu, and SPI slave will send back message to SPI master.
 *  - In Mode 2, the message received from both SPI master and I2C master will display
 *  in terminal.
 *
 * Application Menu:
 * - Press 'W': Return Welcome! to master.
 * - Press 'H': Return Hello world! to master.
 * - Press 'A': Return Atmel SamD1x! to master.
 *
 * \section appdoc_sam0_com_usart_spi_i2c_slave_demo_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_com_usart_spi_i2c_slave_demo_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"


#ifdef __cplusplus
extern "C" {
#endif

/* I2C slave read & write mode */
#define I2C_RD_WR_MODE 0

/* SPI slave read & write mode */
#define SPI_RD_WR_MODE 1

/* I2C/SPI slave read only mode */
#define SPI_I2C_RD_MODE 2

/* Running mode selection */
#define DEMO_RUN_MODE SPI_I2C_RD_MODE



/* Buffer size for SPI receiver array */
#define SPI_DATA_LENGTH 20

/* Buffer size for I2C receiver array */
#define I2C_DATA_LENGTH 20

/* Address for I2C slave */
#define I2C_SLAVE_ADDRESS 0x12

/* Baud rate for USART */
#define CONF_USART_BAUDRATE 9600

/* Buffer size for USART receiver array */
#define USART_DATA_LENGTH 1

/* Buffer size for Return Message array */
#define RET_DATA_LENGTH 20

/* Structures for USART instance */
static struct usart_module usart_instance;


#if DEMO_RUN_MODE == SPI_I2C_RD_MODE || DEMO_RUN_MODE == SPI_RD_WR_MODE
/* Flag whether SPI slave receive is done */
static volatile bool spi_slave_rd_flag = false;

/* Receive buffers used by SPI slave during demo */
static uint8_t spi_read_buffer[SPI_DATA_LENGTH];

#if DEMO_RUN_MODE == SPI_RD_WR_MODE
/* Transmit buffers used by slave during demo */
static uint8_t *spi_write_buffer;
#endif

/* Structures for SPI slave instance selection */
static struct spi_module spi_slave_instance;

/* Declaration for SPI slave initialization */
static void spi_slave_init(void);
#endif


#if DEMO_RUN_MODE == SPI_I2C_RD_MODE || DEMO_RUN_MODE == I2C_RD_WR_MODE
/* Flag whether I2C slave receive is done */
static volatile bool i2c_slave_rd_flag = false;

/* Receive buffers used by I2C slave during demo */
static uint8_t i2c_read_buffer [I2C_DATA_LENGTH];

/* Structures for I2C slave instance selection */
static struct i2c_slave_module i2c_slave_instance;

/* I2C slave read packet */
static struct i2c_slave_packet rd_packet;

#if DEMO_RUN_MODE == I2C_RD_WR_MODE
/* I2C slave write packet */
static struct i2c_slave_packet wr_packet;
#endif
#endif


#if DEMO_RUN_MODE == I2C_RD_WR_MODE ||  DEMO_RUN_MODE == SPI_RD_WR_MODE
/* Return Messages that can be sent to master by SPI slave or I2C slave */
static uint8_t ret_msg[][RET_DATA_LENGTH] = {
	{0},
	{'W', 'e', 'l', 'c', 'o', 'm', 'e', '!', 0},
	{'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', 0},
	{'A', 't', 'm', 'e', 'l', ' ', 'S', 'a', 'm', 'D', '1', 'x', '!', 0}
};

/* Buffer size for USART receiver array */
static uint8_t usart_read_buffer[USART_DATA_LENGTH];

/**
 * \internal
 * \brief USART receive complete interrupt callback function
 *
 * Called by USART driver when reception is complete.
 *
 * Update the write buffer for SPI slave or I2C slave according to the input char .
 *
 * \param module USART module causing the interrupt
 */
static void usart_read_callback(const struct usart_module *const usart_module)
{
	uint8_t* temp = NULL;
	switch(usart_read_buffer[0]){
	case 'W':
	case 'w':
			temp = ret_msg[1];
			break;
	case 'H':
	case 'h':
			temp = ret_msg[2];
			break;
	case 'A':
	case 'a':
			temp = ret_msg[3];
			break;
	default:
			break;
	}
	if (NULL != temp) {
#if DEMO_RUN_MODE == I2C_RD_WR_MODE
		wr_packet.data_length = RET_DATA_LENGTH;
		wr_packet.data        = temp;
#elif DEMO_RUN_MODE == SPI_RD_WR_MODE
		spi_write_buffer = temp;
#endif
	}
	usart_read_buffer_job((struct usart_module *const)usart_module, (uint8_t *)usart_read_buffer, USART_DATA_LENGTH);
}
#endif


#if DEMO_RUN_MODE == SPI_I2C_RD_MODE || DEMO_RUN_MODE == SPI_RD_WR_MODE
/**
 * \internal
 * \brief SPI slave transmission complete interrupt callback function
 *
 * Called by SPI driver when transmission is complete.
 *
 * Set SPI receive complete flag and call SPI slave init function.
 *
 * \param module SPI module causing the interrupt
 */
static void spi_slave_finish_callback(struct spi_module *const module)
{
	spi_slave_rd_flag = true;
	spi_slave_init();
}

/**
 * \internal
 * \brief SPI slave initialize function
 *
 * Register and enable related interrupt and its callback functions.
 * Restart a new round read buffer job.
 *
 * \param module SPI module causing the interrupt
 */
static void spi_slave_init(void)
{
	spi_register_callback(&spi_slave_instance, spi_slave_finish_callback,
		SPI_CALLBACK_SLAVE_TRANSMISSION_COMPLETE);
	spi_enable_callback(&spi_slave_instance, SPI_CALLBACK_SLAVE_TRANSMISSION_COMPLETE);
#if DEMO_RUN_MODE == SPI_RD_WR_MODE
	spi_transceive_buffer_job(&spi_slave_instance, spi_write_buffer,spi_read_buffer, SPI_DATA_LENGTH);
#else
	spi_read_buffer_job(&spi_slave_instance, spi_read_buffer, SPI_DATA_LENGTH,0);
#endif
}

/**
 * \internal
 * \brief Configure the SPI module in slave mode
 *
 * Initializes the SERCOM SPI module used for transferring or receiving bytes from SPI master.
 */
static void configure_spi_slave(void)
{
	struct spi_config config_spi_slave;

	spi_get_config_defaults(&config_spi_slave);

	config_spi_slave.mode = SPI_MODE_SLAVE;
	config_spi_slave.mode_specific.slave.preload_enable = true;
	config_spi_slave.mode_specific.slave.frame_format = SPI_FRAME_FORMAT_SPI_FRAME;
	config_spi_slave.mux_setting = EXT1_SPI_SERCOM_MUX_SETTING;
	config_spi_slave.pinmux_pad0 = EXT1_SPI_SERCOM_PINMUX_PAD0;
	config_spi_slave.pinmux_pad1 = EXT1_SPI_SERCOM_PINMUX_PAD1;
	config_spi_slave.pinmux_pad2 = EXT1_SPI_SERCOM_PINMUX_PAD2;
	config_spi_slave.pinmux_pad3 = EXT1_SPI_SERCOM_PINMUX_PAD3;

#if DEMO_RUN_MODE == SPI_RD_WR_MODE
	/* Reset to null by default */
	spi_write_buffer = ret_msg[0];
#endif

	spi_init(&spi_slave_instance, EXT1_SPI_MODULE, &config_spi_slave);
	spi_enable(&spi_slave_instance);
}
#endif

#if DEMO_RUN_MODE == SPI_I2C_RD_MODE || DEMO_RUN_MODE == I2C_RD_WR_MODE
/**
 * \internal
 * \brief I2C slave write request interrupt callback function
 *
 * Called by I2C driver when write request is received.
 *
 * I2C slave received write request from master and ready for receiving data.
 *
 * \param module SPI module causing the interrupt
 */
static void i2c_write_request_callback(struct i2c_slave_module *const module)
{
	rd_packet.data_length = I2C_DATA_LENGTH;
	rd_packet.data        = i2c_read_buffer;

	if (i2c_slave_read_packet_job(module, &rd_packet) == STATUS_OK) {
		i2c_slave_rd_flag = true;
	}
}

#if DEMO_RUN_MODE == I2C_RD_WR_MODE
/**
 * \internal
 * \brief I2C slave read request interrupt callback function
 *
 * Called by I2C driver when read request is received.
 *
 * I2C slave received read request from master and ready for transmitting data.
 *
 * \param module SPI module causing the interrupt
 */
static void i2c_read_request_callback(struct i2c_slave_module *const module)
{
	i2c_slave_write_packet_job(module, &wr_packet);
}
#endif

/**
 * \internal
 * \brief Configure the I2C module in slave mode
 *
 * Initializes the SERCOM I2C module used for transferring or receiving bytes from I2C master.
 */
static void configure_i2c_slave(void)
{
	struct i2c_slave_config config_i2c_slave;
	i2c_slave_get_config_defaults(&config_i2c_slave);

	config_i2c_slave.address      = I2C_SLAVE_ADDRESS;
	config_i2c_slave.address_mode = I2C_SLAVE_ADDRESS_MODE_MASK;

#if DEMO_RUN_MODE == I2C_RD_WR_MODE
	/* Reset to null by default */
	wr_packet.data        = ret_msg[0];
	wr_packet.data_length = RET_DATA_LENGTH;
#endif

	i2c_slave_init(&i2c_slave_instance, EXT1_I2C_MODULE, &config_i2c_slave);
	i2c_slave_enable(&i2c_slave_instance);
}

/**
 * \internal
 * \brief Configure I2C slave interrupt callback function
 *
 * Enable and register I2C slave write request / read request interrupt callback
 *
 */
static void configure_i2c_slave_callbacks(void)
{
#if  DEMO_RUN_MODE == I2C_RD_WR_MODE
	i2c_slave_register_callback(&i2c_slave_instance, i2c_read_request_callback,
		I2C_SLAVE_CALLBACK_READ_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance,
		I2C_SLAVE_CALLBACK_READ_REQUEST);
#endif

	i2c_slave_register_callback(&i2c_slave_instance, i2c_write_request_callback,
		I2C_SLAVE_CALLBACK_WRITE_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance,
		I2C_SLAVE_CALLBACK_WRITE_REQUEST);
}
#endif

#if DEMO_RUN_MODE == I2C_RD_WR_MODE ||  DEMO_RUN_MODE == SPI_RD_WR_MODE
/**
 * \internal
 * \brief Show the prompting message in USART-SPI slave Read-Write Mode or
 * USART-I2C slave Read-Write Mode
 *
 */
static void show_menu(void)
{
	uint8_t string[] =
	"\r\n--Press 'W': Return Welcome! to master\
	 \r\n--Press 'H': Return Hello world! to master\
	 \r\n--Press 'A': Return Atmel SamD1x! to master";
	usart_write_buffer_job(&usart_instance, string, sizeof(string));
	while(STATUS_OK != usart_get_job_status(&usart_instance,USART_TRANSCEIVER_TX)) {

	}
}

/**
 * \internal
 * \brief Configure USART interrupt callback function
 *
 * Enable and register USART buffer received interrupt callback
 *
 */
static void configure_usart_callbacks(void)
{
	usart_register_callback(&usart_instance,
		usart_read_callback, USART_CALLBACK_BUFFER_RECEIVED);

	usart_enable_callback(&usart_instance, USART_CALLBACK_BUFFER_RECEIVED);
}
#endif

/**
 * \internal
 * \brief Configure the USART module
 *
 * Initializes the SERCOM USART module used for display the info from SPI slave or I2C slave
 * and get char from PC to decide which message to send back in USART-SPI slave Read-Write Mode or
 * USART-I2C slave Read-Write Mode.
 */
static void configure_usart(void)
{
	struct usart_config config_usart;

	usart_get_config_defaults(&config_usart);

	config_usart.baudrate    = CONF_USART_BAUDRATE;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;

	while (usart_init(&usart_instance,
		EDBG_CDC_MODULE, &config_usart) != STATUS_OK) {
	}

	usart_enable(&usart_instance);
}

/**
 * \brief Run USART-SPI-I2C slave demo
 *
 * Initializes the system and serial output, then run the demo according to the selected mode.
 */
int main (void)
{
	system_init();

	configure_usart();
#if DEMO_RUN_MODE == I2C_RD_WR_MODE ||  DEMO_RUN_MODE == SPI_RD_WR_MODE
	configure_usart_callbacks();
	usart_read_buffer_job(&usart_instance, (uint8_t *)usart_read_buffer, USART_DATA_LENGTH);
#endif

#if DEMO_RUN_MODE == I2C_RD_WR_MODE
	uint8_t string[] = "SAMD1x Demo --- Com for USART and I2C slave mode";
	usart_write_buffer_job(&usart_instance, string, sizeof(string));
	while(STATUS_OK != usart_get_job_status(&usart_instance,USART_TRANSCEIVER_TX)) {

	}
	show_menu();
#elif DEMO_RUN_MODE == SPI_RD_WR_MODE
	uint8_t string[] = "SAMD1x Demo --- Com for USART and SPI slave mode";
	usart_write_buffer_job(&usart_instance, string, sizeof(string));
	while(STATUS_OK != usart_get_job_status(&usart_instance,USART_TRANSCEIVER_TX)) {

	}
	show_menu();
#elif DEMO_RUN_MODE == SPI_I2C_RD_MODE
	uint8_t string[] = "SAMD1x Demo --- Com for USART and SPI/I2C slave mode";
	usart_write_buffer_job(&usart_instance, string, sizeof(string));
#endif

#if DEMO_RUN_MODE == SPI_I2C_RD_MODE || DEMO_RUN_MODE == I2C_RD_WR_MODE
	configure_i2c_slave();
	configure_i2c_slave_callbacks();
#endif

#if DEMO_RUN_MODE == SPI_I2C_RD_MODE || DEMO_RUN_MODE == SPI_RD_WR_MODE
	configure_spi_slave();
	spi_slave_init();
#endif

	while (1) {
#if DEMO_RUN_MODE == SPI_I2C_RD_MODE || DEMO_RUN_MODE == SPI_RD_WR_MODE
		if (true == spi_slave_rd_flag) {
			uint8_t spi_msg[] = "\r\nSPI->USART:\r\n";
			usart_write_buffer_job(&usart_instance, spi_msg, sizeof(spi_msg));
			while(STATUS_OK != usart_get_job_status(&usart_instance,USART_TRANSCEIVER_TX)) {

			}
			usart_write_buffer_job(&usart_instance, (uint8_t *)spi_read_buffer,SPI_DATA_LENGTH);
			spi_slave_rd_flag = false;
		}
#endif

#if DEMO_RUN_MODE == SPI_I2C_RD_MODE || DEMO_RUN_MODE == I2C_RD_WR_MODE
		if (true == i2c_slave_rd_flag) {
			uint8_t i2c_msg[] = "\r\nI2C->USART:\r\n";
			usart_write_buffer_job(&usart_instance, i2c_msg, sizeof(i2c_msg));
			while(STATUS_OK != usart_get_job_status(&usart_instance,USART_TRANSCEIVER_TX)) {

			}
			usart_write_buffer_job(&usart_instance, (uint8_t *)rd_packet.data, I2C_DATA_LENGTH);
			i2c_slave_rd_flag = false;
		}
#endif
	}
}

#ifdef __cplusplus
}
#endif
