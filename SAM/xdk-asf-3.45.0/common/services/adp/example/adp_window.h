/**
 * \file
 *
 * \brief ADP window configuration
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

#ifndef ADP_WINDOW_H_INCLUDED
#define ADP_WINDOW_H_INCLUDED

/** Stream number defines */
/* Status messages stream id */
#define STREAM_ID_STATUS_MESSAGE    0x00
/* Outgoing voltage value stream id */
#define STREAM_ID_LIGHT_SENSOR      0x01
/* Outgoing ADC value stream id */
#define STREAM_ID_LIGHT_SENSOR_ADC  0x02
/* Incoming stream setting high hysteresis */
#define STREAM_ID_HYST_HIGH         0x10
/* Incoming stream setting low hysteresis */
#define STREAM_ID_HYST_LOW          0x11
/* Night mode signal stream id */
#define STREAM_ID_NIGHT_MODE        0x29
/* Led toggle stream id */
#define STREAM_ID_LED_TOGGLE        0x30

/** Dashboard and elements defines */
/* Light sensor example dashboard id */
#define DASHBOARD_ID_LIGHT_SENSOR       0x00
#define DASHBOARD_ID_CONTROL            0x01

/* Terminal label */
#define TERMINAL_LABEL "Status terminal"
/* Graph label */
#define GRAPH_LABEL    "Light Sensor Output"
/* Dashboard label */
#define DASHBOARD_DIS_LABEL "Light Sensor Example Dashboard"
#define DASHBOARD_CON_LABEL "Control Dashboard"

extern struct adp_msg_conf_terminal terminal_config;

enum adp_example_element_id {
	/* Dashboard example */
	ELEMENT_ID_LABEL_TITEL,
	ELEMENT_ID_LABEL_VALUE_VOL,
	ELEMENT_ID_LABEL_NIGHT_LIGHT,
	ELEMENT_ID_LABEL_LED_CONTROL,
	ELEMENT_ID_BAR,
	ELEMENT_ID_SIGNAL,
	ELEMENT_ID_BUTTON,
	ELEMENT_ID_GRAPH,
	
	/* Dashboard config */
	ELEMENT_ID_LABEL_HYSTERESIS,
	ELEMENT_ID_LABEL_LOW,
	ELEMENT_ID_LABEL_HIGH,
	ELEMENT_ID_LABEL_VALUE_ADC,
	ELEMENT_ID_SLIDER_LOW,
	ELEMENT_ID_SLIDER_HIGH,
	ELEMENT_ID_SEGMENT,
};

void adp_window_init(void);

#endif
