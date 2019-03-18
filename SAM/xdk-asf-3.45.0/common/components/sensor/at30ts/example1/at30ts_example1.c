/**
 * \file
 *
 * \brief AT30TS Temperature Sensor driver example.
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
 * \mainpage
 *
 * \section intro Introduction
 * This is an example application for the AT30TS Temperature Sensor. 
 * The TEMPSENSORX kit has got an AT30TSE758 device and an AT30TSE002B.
 * Here, we've selected AT30TSE758 as test device in this example
 * \section files Main Files
 * - \ref at30ts_example1.c
 * - \ref conf_example.h
 * - \ref conf_board.h
 * - \ref conf_clock.h
 * - \ref conf_st7565r.h
 * - \ref conf_sysfont.h
 * - \ref conf_twim.h
 * - \ref conf_usart_spi.h
 * 
 *
 * \section device_info Device Info
 * All AVR devices with TWI Master driver support in ASF can be used.
 * This example has been tested with the following setup:
 * - XMEGA-A3BU Xplained with ATAVRTEMPSENSORX
 *
 * \section exampledescription Description of the example application
 * The example application test the different driver functions 
 * for the selected AT30TS temperature sensor device. It indicates 
 * test Success/Failure on the LEDs available on ATAVRTEMPSENSORX 
 * and displays corresponding messages on the LCD screen of 
 * XMEGA-A3BU Xplained
 *
 * \section dependencies Dependencies
 * This driver depends on the following modules:
 * - \ref twi_group for interfacing with a TWI Master.
 *
 * \section compinfo Compilation info
 * This software was written for the GNU GCC and IAR for AVR. Other compilers
 * may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit <a href="http://www.microchip.com/">Microchip</a>.\n
 */

#include <asf.h>
#include <stdio.h>
#include <conf_example.h>

void test_fail_indication(void);
 
/**
 * \brief This function is used to indicate a test failure
 */
void test_fail_indication(void)
{
	while (1) {
		ioport_set_pin_low(LED_CRIT);
		delay_ms(200);
		ioport_set_pin_high(LED_CRIT);
		delay_ms(200);
	}
}

/**
 * \brief Main entry of example application
 */

int main(void)
{
	static uint8_t ret = 0;
	uint8_t i = 0;
	uint8_t ibuf[16] = {0};
	static uint8_t test_pattern[PATTERN_TEST_LENGTH];
	sensor_data_t sensor_data;
	twi_master_options_t opt;

	irq_initialize_vectors();

	sysclk_init();

	/* Initialize the board.
	 * The board-specific conf_board.h file contains the configuration of
	 * the board initialization.
	 */
	board_init();
	gfx_mono_init();
	ioport_set_pin_high(NHD_C12832A1Z_BACKLIGHT);
	gfx_mono_draw_string("Reading....\r\n", 0, 0, &sysfont);
	gfx_mono_generic_draw_filled_rect(0, 8, 128, 8, GFX_PIXEL_CLR);

	/* configure the pins connected to LEDs as output and set their default
	 * initial state to low (LEDs off).
	 */
	ioport_configure_pin(LED_LOW, IOPORT_DIR_OUTPUT);
	ioport_configure_pin(LED_HIGH, IOPORT_DIR_OUTPUT);
	ioport_configure_pin(LED_CRIT, IOPORT_DIR_OUTPUT);
	ioport_configure_pin(LED_NORM, IOPORT_DIR_OUTPUT);

	ioport_set_pin_low(LED_LOW);
	ioport_set_pin_low(LED_HIGH);
	ioport_set_pin_low(LED_CRIT);
	ioport_set_pin_low(LED_NORM);

	/* Configure the ALERT/EVENT pin which is
	 * routed to pin 2 of J2 on A3BU Xplained
	 * This pin can be used for polling or interrupt
	 */
	ioport_configure_pin(EVENT_PIN, IOPORT_DIR_INPUT);

	attach_device(EXAMPLE_TS_DEVICE_ADDR, EXAMPLE_TS_DEVICE);
	opt.chip = EXAMPLE_TS_DEVICE_ADDR;
	opt.speed = TWI_SPEED;

	/* Initialize TWI driver with options */
	twi_master_setup(TWI_MODULE, &opt);

	sensor_data.config_reg.value = 0;
	/* Set configuration register to 12-bis resolution */
	sensor_data.config_reg.option.RES  = AT30TS7_RES12;

	if (write_config(sensor_data.config_reg.value) != TWI_SUCCESS) {
		test_fail_indication();
	}

	/* Set the polarity of ALERT/EVENT pin to low */

	if (set_config_option(&sensor_data, AT30TS_POL, AT30TS7_POL_ACTIVE_LOW) !=
	TWI_SUCCESS) {
	test_fail_indication();
	}

	/* Read the configuration register */
	if (read_config(&sensor_data) != TWI_SUCCESS) {
		test_fail_indication();
	}

#if defined _AT30TS00_ || defined _AT30TSE002B_
	/* Set t_high limit register to +75.0000C */
	if (write_tcrit(pos, 75, 0000) != TWI_SUCCESS) {
		test_fail_indication();
	}
#endif

	/* Set t_high limit register to +50.7500C */
	if (write_temperature_high(pos, 50, 7500) != TWI_SUCCESS) {
		test_fail_indication();
	}

	/* Set t_low limit register to -25.2500C */

	/*
	 * if (write_temperature_low(neg, 25, 2500)!= TWI_SUCCESS) {
	 * test_fail_indication();
	 * }
	 */

	/* Set t_low limit register to +35.5000C */
	if (write_temperature_low(pos, 35, 5000) != TWI_SUCCESS) {
		test_fail_indication();
	}

#if defined _AT30TS00_ || defined _AT30TSE002B_
	/* Read t_crit register register */
	if (read_tcrit(&sensor_data) != TWI_SUCCESS) {
		test_fail_indication();
	}
#endif

	/* Read t_high limit register */
	if (read_temperature_high(&sensor_data) != TWI_SUCCESS) {
		test_fail_indication();
	}

	/* Read t_low register register */
	if (read_temperature_low(&sensor_data) != TWI_SUCCESS) {
		test_fail_indication();
	}

	/* Non volatile register functionality */
#if defined _AT30TS750_  || defined _AT30TSE752_ || \
	defined _AT30TSE754_ || defined _AT30TSE758_

	/* Copy volatile registers to nonvolatile registers
	 * vol configuration register  -> nonvol configuration register
	 * vol t_high register -> nonvol t_high register
	 * vol t_low  register -> nonvol t_low register
	 */
        ret = ts75_copy_vol_nonvol_register();
	if (ret != TWI_SUCCESS) {
		test_fail_indication();
	}

	/* Read the nonvol configuration register */
	if (read_nvconfig(&sensor_data) != TWI_SUCCESS) {
		test_fail_indication();
	}

	/* Read the nonvol t_high register */
	if (read_nvthigh(&sensor_data) != TWI_SUCCESS) {
		test_fail_indication();
	}

	/* Read the nonvol t_low register */
	if (read_nvtlow(&sensor_data) != TWI_SUCCESS) {
		test_fail_indication();
	}

	/* Clear vol configuration register */
	if (write_config(0x0000) != TWI_SUCCESS) {
		test_fail_indication();
	}

	/* Read the vol configuration register */
	if (read_config(&sensor_data) != TWI_SUCCESS) {
		test_fail_indication();
	}

	/* Copy nonvolatile registers to volatile registers */
	if (ts75_copy_nonvol_vol_register() != TWI_SUCCESS) {
		test_fail_indication();
	}

	/* Read the configuration register */
	if (read_config(&sensor_data) != TWI_SUCCESS) {
		test_fail_indication();
	}
#endif
        /* To avoid 'variable unused' warning */
        test_pattern[0] = ibuf[0];
        ibuf[0] = test_pattern[0];

	/* EEPROM Test */
#if defined _AT30TSE002B_  || defined _AT30TSE752_ || \
	defined _AT30TSE754_   || defined _AT30TSE758_

	/* Generate Test Pattern */
	for (i = 0; i < PATTERN_TEST_LENGTH; i++) {
		test_pattern[i] = 0x41 + i; // 'ABCD...'
	}

	/* Perform a write access & check write result */
	if ((ret = ts_write_memory(EE_TEST_ADDR, PATTERN_TEST_LENGTH,
	(void *)test_pattern)) != TWI_SUCCESS) {
		gfx_mono_draw_string("EE Write Failed ", 0, 24, &sysfont);
		test_fail_indication();
	}

	/* Allow time for EEPROM to settle */
	delay_ms(5);
	/* Clear test_pattern */
	memset(ibuf, 0, sizeof(ibuf));

	/* Perform a read access & check read result */
	if (ts_read_eeprom(EE_TEST_ADDR, PATTERN_TEST_LENGTH,
			ibuf) != TWI_SUCCESS) {
		gfx_mono_draw_string("EE Read Failed ", 0, 24, &sysfont);
		test_fail_indication();
	}

	/* Check received data against sent data */
	for (i = 0; i < PATTERN_TEST_LENGTH; i++) {
		if (ibuf[i] != test_pattern[i]) {
			gfx_mono_draw_string("EE Read mismatch ", 0, 24,
				&sysfont);
			test_fail_indication();
		}
	}

	gfx_mono_draw_string("EE Write/Read OK", 0, 24, &sysfont);
	gfx_mono_draw_string((char const*)ibuf, 0, 16, &sysfont);
#endif
	/*
	 * Temperature reading contained in struct,i.e.
	 * temperature register value = 0x3240 (+50.25C), AT30TSE758 device
	 * sensor_data.temperature.itemp = 50 //!< integer part
	 * sensor_data.temperature.ftemp = 2500 //!< fractional part
	 * sensor_data.temperature.sign = 0 //!< sign (pos(+) = 0, neg(-) = 1)
	 * sensor_data.temperature.raw_value = 0x324 //!< raw data
	 */

	char senseData[50] = {0};
	while (1) {
		/* Read temperature */
		read_temperature(&sensor_data);
		sprintf(senseData, "%d.%04d DegC",
					sensor_data.temperature.itemp,
						sensor_data.temperature.ftemp);
		gfx_mono_draw_string(senseData, 0, 8, &sysfont);
		ioport_set_pin_low(LED_NORM);
		delay_ms(200);
		ioport_set_pin_high(LED_NORM);
		delay_ms(200);
	}
}
