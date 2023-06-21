/**
 * \file
 *
 * \brief AFEC XDMAC example for SAM.
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
 * \mainpage AFEC Temperature Sensor Example
 *
 * \section Purpose
 *
 * The example demonstrates how to use the temperature sensor
 * feature inside the microcontroller. The RAW data of temperature sampled by
 * AFEC is taken by XDMAC and converted to temperature value ,which is output
 * to terminal console.  Three columns will be output to console, first column
 * is AFEC channel,for temperature sensor on SAMV71/SAME70,it's channel 11, the second column
 * is RAW data sampled, the third column is converted temperature value.
 *
 * \section Requirements
 *
 * This example can be used on SAMV71-Xplained-Ultra/SAME70-Xplained-Pro board.
 *
 * \section Description
 *
 * The example is aimed to demonstrate the temperature sensor feature
 * inside the device and get temperature by XDMAC. To use this feature, the
 * temperature sensor should be automatically
 * turned on by RTC event. The channel 11 is connected to the sensor by default.
 * If set RTCT = 1, TRGEN is disabled and all channels are disabled (AFE_CHSR = 0),
 * then only channel 11 is converted at a rate of 1 conversion per second.
 *
 * The temperature sensor provides an output voltage (VT) that is proportional
 * to absolute temperature (PTAT). The relationship between measured voltage and
 * actual temperature could be found in Electrical Characteristics part of the
 * datasheet.
 *
 * \section Usage
 *
 * -# Build the program and download it into the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g., HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the
 *    following text should appear (values depend on the board and the chip used):
 *    \code
	-- AFEC Temperature Sensor xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# The application will output current Celsius temperature on the terminal.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "asf.h"

/** Reference voltage for AFEC,in mv. */
#define VOLT_REF        (3300)

/** The maximal digital value */
#define MAX_DIGITAL     (4095UL)


/** XDMAC channel used in this example. */
#define XDMAC_CH 0

/** XDMAC channel HW Interface number for AFEC0. */
#define AFEC0_XDMAC_CH_NUM  35

/** XDMAC channel configuration. */
static xdmac_channel_config_t xdmac_channel_cfg;

/** The buffer size for transfer  */
#define BUFFER_SIZE          100

COMPILER_ALIGNED(8)
static uint32_t afec_buf[BUFFER_SIZE];

#define STRING_EOL    "\r"
#define STRING_HEADER "-- AFEC XDMAC Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

/**
 * \brief Configure UART console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 * \brief configure xdmac for afec.
 *
 * \param afec  Base address of the AFEC
 */
static void afec_xdmac_configure(Afec *const afec)
{
	uint32_t xdmaint;
	/* Initialize and enable DMA controller */
	pmc_enable_periph_clk(ID_XDMAC);

	/*Enable XDMA interrupt */
	NVIC_ClearPendingIRQ(XDMAC_IRQn);
	NVIC_SetPriority( XDMAC_IRQn ,1);
	NVIC_EnableIRQ(XDMAC_IRQn);

	/* Initialize channel config */
	xdmac_channel_cfg.mbr_ubc = XDMAC_UBC_NVIEW_NDV0 |
		XDMAC_UBC_NDE_FETCH_DIS |
		XDMAC_UBC_NDEN_UPDATED |
		BUFFER_SIZE;

	xdmac_channel_cfg.mbr_sa = (uint32_t)&(afec->AFEC_LCDR);
	xdmac_channel_cfg.mbr_da = (uint32_t)afec_buf;
	xdmac_channel_cfg.mbr_cfg = XDMAC_CC_TYPE_PER_TRAN |
		XDMAC_CC_MBSIZE_SINGLE |
		XDMAC_CC_DSYNC_PER2MEM |
		XDMAC_CC_CSIZE_CHK_1 |
		XDMAC_CC_DWIDTH_WORD|
		XDMAC_CC_SIF_AHB_IF1 |
		XDMAC_CC_DIF_AHB_IF0 |
		XDMAC_CC_SAM_FIXED_AM |
		XDMAC_CC_DAM_INCREMENTED_AM |
		XDMAC_CC_PERID(AFEC0_XDMAC_CH_NUM);

	xdmac_channel_cfg.mbr_bc = 0;
	xdmac_channel_cfg.mbr_ds =  0;
	xdmac_channel_cfg.mbr_sus = 0;
	xdmac_channel_cfg.mbr_dus = 0;

	xdmac_configure_transfer(XDMAC, XDMAC_CH, &xdmac_channel_cfg);

	xdmac_channel_set_descriptor_control(XDMAC, XDMAC_CH, 0);

	xdmac_enable_interrupt(XDMAC, XDMAC_CH);
	xdmaint =  (XDMAC_CIE_BIE   |
		XDMAC_CIE_DIE   |
		XDMAC_CIE_FIE   |
		XDMAC_CIE_RBIE  |
		XDMAC_CIE_WBIE  |
		XDMAC_CIE_ROIE);

	xdmac_channel_enable_interrupt(XDMAC, XDMAC_CH, xdmaint);
	xdmac_channel_enable(XDMAC, XDMAC_CH);

}

/**
 *  \brief Callback function for AFE interrupt
 *
 */
static void afec_callback(void)
{
	uint32_t i;
	uint32_t ch;
	uint32_t voltage;
	int32_t temp;

	printf("\n\rCH  AFE   temperature \n\r");
	for ( i = 0; i < BUFFER_SIZE; i++ ) {
		ch = (afec_buf[i] & AFEC_LCDR_CHNB_Msk ) >> AFEC_LCDR_CHNB_Pos;
		voltage = (afec_buf[i] & 0xFFFF) * VOLT_REF / MAX_DIGITAL;
		temp = ((int)voltage - 720)  * 100 / 233 + 27;
		if(ch == AFEC_TEMPERATURE_SENSOR) {
			printf("%02u  %04x  %04d\n\r" ,(unsigned int)ch,
					(unsigned int)(afec_buf[i]& 0xFFFF) , (int)temp);
		}

	}
}

/**
 * \brief XDMAC interrupt handler.
 */
void XDMAC_Handler(void)
{
	uint32_t dma_status;

	dma_status = xdmac_channel_get_interrupt_status(XDMAC, XDMAC_CH);

	if (dma_status & XDMAC_CIS_BIS) {
		afec_callback();
	}
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{

	/* Initialize the SAM system. */
	sysclk_init();
	board_init();

	configure_console();

	/* Output example information. */
	puts(STRING_HEADER);

	afec_enable(AFEC0);

	struct afec_config afec_cfg;

	afec_get_config_defaults(&afec_cfg);

	afec_init(AFEC0, &afec_cfg);

	afec_set_trigger(AFEC0, AFEC_TRIG_FREERUN);

	struct afec_ch_config afec_ch_cfg;
	afec_ch_get_config_defaults(&afec_ch_cfg);

	afec_ch_cfg.gain = AFEC_GAINVALUE_0;

	afec_ch_set_config(AFEC0, AFEC_TEMPERATURE_SENSOR, &afec_ch_cfg);

	/*
	 * Because the internal ADC offset is 0x200, it should cancel it and shift
	 * down to 0.
	 */
	afec_channel_set_analog_offset(AFEC0, AFEC_TEMPERATURE_SENSOR, 0x200);

	struct afec_temp_sensor_config afec_temp_sensor_cfg;

	afec_temp_sensor_get_config_defaults(&afec_temp_sensor_cfg);
	afec_temp_sensor_cfg.rctc = true;
	afec_temp_sensor_set_config(AFEC0, &afec_temp_sensor_cfg);

	afec_xdmac_configure(AFEC0);

	afec_channel_enable(AFEC0, AFEC_TEMPERATURE_SENSOR);


	while(1) {
		
	}

}
