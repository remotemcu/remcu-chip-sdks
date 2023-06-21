/**
 * \file
 *
 * \brief QTouch Sensor example with I2C interface configuration.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_EXAMPLE_H_INCLUDED
#define CONF_EXAMPLE_H_INCLUDED

#define QT_SLIDER_RESOLUTION  QT_SLIDER_RESOLUTION_7_BIT
#define QT_SLIDER_MAX         ((0x01 << (8 - QT_SLIDER_RESOLUTION)) - 1)

/**
 * \brief Set QTouch parameter for the example
 *
 * \param setup_block Pointer to setup block buffer.
 */
static void example_set_qt_param(struct qt_setup_block *setup_block)
{
	/*
	 * Set parameter for QT slider.
	 */
	setup_block->slider_num_keys = 7; /* X0~X6 are for slider, total 7  */
	setup_block->slider_resolution = QT_SLIDER_RESOLUTION;

	/*
	 * Set all GPIO as output with low level.
	 */
	setup_block->gpio_direction = 0x1C; /* 0x1C is for GPIO1~GPIO3 */
	setup_block->gpio_gpo_drive2 = 0x0;
}

/**
 * \brief Process QT status for the example
 *
 * \param qt_status Pointer to QT status buffer.
 */
static void example_process_qt_status(struct qt_status *qt_status)
{
#define QT_LEFT_KEY_MASK     0x01
#define QT_RIGHT_KEY_MASK    0x02

	static bool key_left_pressed = false;
	static bool key_right_pressed = false;
	static uint8_t slide_position = 0;

	if (qt_status->key_status_2 & QT_LEFT_KEY_MASK) {
		if (!key_left_pressed) {
			printf("QT left key pressed.\r\n");
			key_left_pressed = true;
		}
	} else {
		if (key_left_pressed) {
			printf("QT left key released.\r\n");
			key_left_pressed = false;
		}
	}

	if (qt_status->key_status_2 & QT_RIGHT_KEY_MASK) {
		if (!key_right_pressed) {
			printf("QT right key pressed.\r\n");
			key_right_pressed = true;
		}
	} else {
		if (key_right_pressed) {
			printf("QT right key released.\r\n");
			key_right_pressed = false;
		}
	}

	if (qt_status->general_status & QT_GENERAL_STATUS_SDET) {
		if (qt_status->slider_position != slide_position) {
			slide_position = qt_status->slider_position;
			printf("QT slider: %d\r\n", QT_SLIDER_MAX - slide_position);
		}
	}
}

#endif /* CONF_EXAMPLE_H_INCLUDED */
