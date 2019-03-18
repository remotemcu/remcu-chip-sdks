/**
 * \file
 *
 * \brief ADP service implementation
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

#include "adp_window.h"
#include "adp.h"
#include <string.h>


/* Terminal configuration. Global, so we can change it later */
struct adp_msg_conf_terminal terminal_config = {
	.terminal_id = 0,
	.width = 80,
	.height = 50,
	.background_color = {ADP_COLOR_WHITE},
	.foreground_color = {ADP_COLOR_GREEN}
};

/**
* \brief Config and add all new streams.
*
*/
static void adp_window_add_terminal(void)
{
	struct adp_msg_configure_stream stream;
	
	//terminal_config.terminal_id = 0;
	//terminal_config.width = 80;
	//terminal_config.height = 50;
	//memcpy(terminal_config.background_color, ADP_COLOR_WHITE, 3);
	//memcpy(terminal_config.foreground_color, ADP_COLOR_GREEN, 3);
	
	/* Add terminal stream */
	stream.stream_id = STREAM_ID_STATUS_MESSAGE;
	stream.type = ADP_STREAM_UINT_8;
	stream.mode = ADP_STREAM_OUT;
	stream.state = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Status messages");
	
	adp_configure_terminal(&terminal_config, TERMINAL_LABEL);
	
	/* Connect stream and terminal */
	struct adp_msg_add_stream_to_terminal conf_stream = {
		.terminal_id = 0,
		.stream_id = STREAM_ID_STATUS_MESSAGE,
		.mode = 0xFF,
		.text_color = {ADP_COLOR_BLACK},
		.tag_text_color = {ADP_COLOR_BLACK}
	};
	adp_add_stream_to_terminal(&conf_stream, "Status messages");
}

/**
* \brief Add all labels to the dashboard light sensor.
*
*/
static void adp_window_add_label_to_light_sensor_dashboard(void)
{
	struct adp_msg_conf_dashboard_element_label label1 = {
		.dashboard_id = DASHBOARD_ID_LIGHT_SENSOR,
		.element_id = ELEMENT_ID_LABEL_TITEL,
		.z_index = 0,
		.x = 5,
		.y = 5,
		.width = 300,
		.height = 35,
		.element_type = ADP_ELEMENT_TYPE_LABEL,
		.font_size = 24,
		.attribute = BOLD_OFF_ITALIC_OFF,
		.horisontal_alignment = HORISONTAL_ALIGNMENT_CENTER,
		.vertical_alignment = VERTICAL_ALIGNMENT_CENTER,
		.background_transparency = 0,
		.background_color = {ADP_COLOR_WHITE},
		.foreground_transparency = 255,
		.foreground_color = {ADP_COLOR_BLACK},
	};
	adp_add_label_to_dashboard(&label1, "Light Sensor Example");
	
	/* Add a label: Light Sensor Value */
	struct adp_msg_conf_dashboard_element_label label2 = {
		.dashboard_id = DASHBOARD_ID_LIGHT_SENSOR,
		.element_id = ELEMENT_ID_LABEL_VALUE_VOL,
		.z_index = 0,
		.x = 5,
		.y = 60,
		.width = 129,
		.height = 25,
		.element_type = ADP_ELEMENT_TYPE_LABEL,
		.font_size = 14,
		.attribute = BOLD_ON_ITALIC_OFF,
		.horisontal_alignment = HORISONTAL_ALIGNMENT_LEFT,
		.vertical_alignment = VERTICAL_ALIGNMENT_CENTER,
		.background_transparency = 0,
		.background_color = {ADP_COLOR_WHITE},
		.foreground_transparency = 255,
		.foreground_color = {ADP_COLOR_BLACK},
	};
	adp_add_label_to_dashboard(&label2, "Light Sensor Value");
	
	/* Add a label: Night Light */
	struct adp_msg_conf_dashboard_element_label label3 = {
		.dashboard_id = DASHBOARD_ID_LIGHT_SENSOR,
		.element_id = ELEMENT_ID_LABEL_NIGHT_LIGHT,
		.z_index = 0,
		.x = 5,
		.y = 100,
		.width = 82,
		.height = 25,
		.element_type = ADP_ELEMENT_TYPE_LABEL,
		.font_size = 14,
		.attribute = BOLD_ON_ITALIC_OFF,
		.horisontal_alignment = HORISONTAL_ALIGNMENT_LEFT,
		.vertical_alignment = VERTICAL_ALIGNMENT_CENTER,
		.background_transparency = 0,
		.background_color = {ADP_COLOR_WHITE},
		.foreground_transparency = 255,
		.foreground_color = {ADP_COLOR_BLACK}, 
	};
	adp_add_label_to_dashboard(&label3, "Night Light");
	
	/* Add a label: LED Control */
	struct adp_msg_conf_dashboard_element_label label4 = {
		.dashboard_id = DASHBOARD_ID_LIGHT_SENSOR,
		.element_id = ELEMENT_ID_LABEL_LED_CONTROL,
		.z_index = 0,
		.x = 5,
		.y = 230,
		.width = 80,
		.height = 25,
		.element_type = ADP_ELEMENT_TYPE_LABEL,
		.font_size = 14,
		.attribute = BOLD_ON_ITALIC_OFF,
		.horisontal_alignment = HORISONTAL_ALIGNMENT_LEFT,
		.vertical_alignment = VERTICAL_ALIGNMENT_CENTER,
		.background_transparency = 0,
		.background_color = {ADP_COLOR_WHITE},
		.foreground_transparency = 255,
		.foreground_color = {ADP_COLOR_BLACK}, 
	};
	adp_add_label_to_dashboard(&label4, "LED Control");
}

/**
* \brief Add all elements to the dashboard ligth sensor.
*
*/
static void adp_window_add_element_strem_to_light_sensor_dashboard(void)
{
	struct adp_msg_configure_stream stream;
	struct adp_conf_add_stream_to_element element_stream = {
		.dashboard_id = DASHBOARD_ID_LIGHT_SENSOR,
	};
	
	/* Add progress bar and graph stream(light sensor value) */
	stream.stream_id = STREAM_ID_LIGHT_SENSOR;
	stream.type = ADP_STREAM_FLOAT;
	stream.mode = ADP_STREAM_OUT;
	stream.state = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Light Sensor");
	
	/* Add progress bar to dashboard */
	struct adp_msg_conf_dashboard_element_progress progress_bar_value = {
		.dashboard_id = DASHBOARD_ID_LIGHT_SENSOR,
		.element_id = ELEMENT_ID_BAR,
		.z_index = 0,
		.x = 140,
		.y = 60,
		.width = 145,
		.height = 25,
		.element_type = ADP_ELEMENT_TYPE_PROGRESS,
		.minimum_value = 0,
		.maximum_value = 4,
		.initial_value = 0,
		.color = {ADP_COLOR_GREEN},
	};
	adp_add_progress_to_dashboard(&progress_bar_value);
	
	element_stream.element_id = ELEMENT_ID_BAR;
	element_stream.stream_id = STREAM_ID_LIGHT_SENSOR;
	adp_add_stream_to_element(&element_stream);
	
	/* Add a graph to dashboard */
	struct adp_msg_conf_dashboard_element_graph graph_value = {
		.dashboard_id = DASHBOARD_ID_LIGHT_SENSOR,
		.element_id = ELEMENT_ID_GRAPH,
		.z_index = 0,
		.x = 310,
		.y = 10,
		.width = 320,
		.height = 240,
		.element_type = ADP_ELEMENT_TYPE_GRAPH,
		.title_color = {ADP_COLOR_WHITE},
		.background_color = {ADP_COLOR_BLACK},
		.graph_background_color = {ADP_COLOR_BLACK},
		.plot_count = 1,
		.x_min = 0,
		.x_max = 10,
		.y_min = 0,
		.y_max = 5,
		.mode.bit.mouse = 0,
		.mode.bit.fit_graph = 0,
	};
	adp_add_graph_to_dashboard(&graph_value, "Light level");
	
	element_stream.element_id = ELEMENT_ID_GRAPH;
	element_stream.stream_id = STREAM_ID_LIGHT_SENSOR;
	adp_add_stream_to_element(&element_stream);
	
	/* Add signal stream(night mode) */
	stream.stream_id = STREAM_ID_NIGHT_MODE;
	stream.type = ADP_STREAM_UINT_8;
	stream.mode = ADP_STREAM_OUT;
	stream.state = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Night Mode");
	
	/* Add a signal to dashboard */
	struct adp_msg_conf_dashboard_element_signal signal_mode = {
		.dashboard_id = DASHBOARD_ID_LIGHT_SENSOR,
		.element_id = ELEMENT_ID_SIGNAL,
		.z_index = 0,
		.x = 140,
		.y = 100,
		.width = 25,
		.height = 25,
		.element_type = ADP_ELEMENT_TYPE_SIGNAL,
		.on_transparency = 0xFF,
		.on_color = {ADP_COLOR_GREEN},
		.off_transparency = 0xFF,
		.off_color = {ADP_COLOR_BLACK},
	};
	adp_add_signal_to_dashboard(&signal_mode);
	
	element_stream.element_id = ELEMENT_ID_SIGNAL;
	element_stream.stream_id = STREAM_ID_NIGHT_MODE;
	adp_add_stream_to_element(&element_stream);
	
	/* Add button stream(LED Toggle) */
	stream.stream_id = STREAM_ID_LED_TOGGLE;
	stream.type = ADP_STREAM_UINT_8;
	stream.mode = ADP_STREAM_IN;
	stream.state = ADP_STREAM_ON;
	adp_configure_stream(&stream, "LED Toggle");
	
	/* Add a button to dashboard */
	struct adp_msg_conf_dashboard_element_button button = {
		.dashboard_id = DASHBOARD_ID_LIGHT_SENSOR,
		.element_id = ELEMENT_ID_BUTTON,
		.z_index = 0,
		.x = 110,
		.y = 230,
		.width = 75,
		.height = 50,
		.element_type = ADP_ELEMENT_TYPE_BUTTON,
		.font_size = 10,
	};
	adp_add_button_to_dashboard(&button, "LED Toggle");
	
	element_stream.element_id = ELEMENT_ID_BUTTON;
	element_stream.stream_id = STREAM_ID_LED_TOGGLE;
	adp_add_stream_to_element(&element_stream);
}

/**
* \brief Add a dashboard light sensor and add all elements to the dashboard.
*
*/
static void adp_window_add_dashboard_light_sensor(void)
{
	/* Add a dashboard */
	struct adp_msg_conf_dashboard dashboard = {
		.dashboard_id = DASHBOARD_ID_LIGHT_SENSOR,
		.color = {ADP_COLOR_WHITE},
		.height = 300,
	};
	adp_add_dashboard(&dashboard, DASHBOARD_DIS_LABEL);
	
	adp_window_add_label_to_light_sensor_dashboard();
	adp_window_add_element_strem_to_light_sensor_dashboard();
}

/**
* \brief Add all labels to the dashboard control.
*
*/
static void adp_window_add_label_to_control_dashboard(void)
{
	/* Add a label: Hysteresis Values: */
	struct adp_msg_conf_dashboard_element_label label1 = {
		.dashboard_id = DASHBOARD_ID_CONTROL,
		.element_id = ELEMENT_ID_LABEL_HYSTERESIS,
		.z_index = 0,
		.x = 5,
		.y = 20,
		.width = 128,
		.height = 25,
		.element_type = ADP_ELEMENT_TYPE_LABEL,
		.font_size = 14,
		.attribute = BOLD_ON_ITALIC_OFF,
		.horisontal_alignment = HORISONTAL_ALIGNMENT_LEFT,
		.vertical_alignment = VERTICAL_ALIGNMENT_CENTER,
		.background_transparency = 0,
		.background_color = {ADP_COLOR_WHITE},
		.foreground_transparency = 255,
		.foreground_color = {ADP_COLOR_BLACK},
	};
	adp_add_label_to_dashboard(&label1, "Hysteresis Values:");
	
	/* Add a label: High */
	struct adp_msg_conf_dashboard_element_label label2 = {
		.dashboard_id = DASHBOARD_ID_CONTROL,
		.element_id = ELEMENT_ID_LABEL_HIGH,
		.z_index = 0,
		.x = 25,
		.y = 100,
		.width = 30,
		.height = 25,
		.element_type = ADP_ELEMENT_TYPE_LABEL,
		.font_size = 14,
		.attribute = BOLD_OFF_ITALIC_ON,
		.horisontal_alignment = HORISONTAL_ALIGNMENT_LEFT,
		.vertical_alignment = VERTICAL_ALIGNMENT_CENTER,
		.background_transparency = 0,
		.background_color = {ADP_COLOR_WHITE},
		.foreground_transparency = 255,
		.foreground_color = {ADP_COLOR_BLACK},
	};
	adp_add_label_to_dashboard(&label2, "High");
	
	/* Add a label: Low */
	struct adp_msg_conf_dashboard_element_label label3 = {
		.dashboard_id = DASHBOARD_ID_CONTROL,
		.element_id = ELEMENT_ID_LABEL_LOW,
		.z_index = 0,
		.x = 25,
		.y = 60,
		.width = 30,
		.height = 25,
		.element_type = ADP_ELEMENT_TYPE_LABEL,
		.font_size = 14,
		.attribute = BOLD_OFF_ITALIC_ON,
		.horisontal_alignment = HORISONTAL_ALIGNMENT_LEFT,
		.vertical_alignment = VERTICAL_ALIGNMENT_CENTER,
		.background_transparency = 0,
		.background_color = {ADP_COLOR_WHITE},
		.foreground_transparency = 255,
		.foreground_color = {ADP_COLOR_BLACK},
	};
	adp_add_label_to_dashboard(&label3, "Low");
	
	/* Add a label: ADC sample value */
	struct adp_msg_conf_dashboard_element_label label4 = {
		.dashboard_id = DASHBOARD_ID_CONTROL,
		.element_id = ELEMENT_ID_LABEL_VALUE_ADC,
		.z_index = 0,
		.x = 350,
		.y = 20,
		.width = 130,
		.height = 25,
		.element_type = ADP_ELEMENT_TYPE_LABEL,
		.font_size = 14,
		.attribute = BOLD_ON_ITALIC_OFF,
		.horisontal_alignment = HORISONTAL_ALIGNMENT_LEFT,
		.vertical_alignment = VERTICAL_ALIGNMENT_CENTER,
		.background_transparency = 0,
		.background_color = {ADP_COLOR_WHITE},
		.foreground_transparency = 255,
		.foreground_color = {ADP_COLOR_BLACK},
	};
	adp_add_label_to_dashboard(&label4, "ADC Sample Value:");
}

/**
* \brief Add all labels to the dashboard control.
*
*/
static void adp_window_add_element_strem_to_control_dashboard(void)
{
	struct adp_msg_configure_stream stream;
	struct adp_conf_add_stream_to_element element_stream = {
		.dashboard_id = DASHBOARD_ID_CONTROL,
	};
	
	/* Add slider stream(slider_high) */
	stream.stream_id = STREAM_ID_HYST_HIGH;
	stream.type = ADP_STREAM_UINT_16;
	stream.mode = ADP_STREAM_IN;
	stream.state = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Hyst. High");
	
	/* Add a slider to dashboard */
	struct adp_msg_conf_dashboard_element_slider slider_high = {
		.dashboard_id = DASHBOARD_ID_CONTROL,
		.element_id = ELEMENT_ID_SLIDER_HIGH,
		.z_index = 0,
		.x = 75,
		.y = 100,
		.width = 156,
		.height = 25,
		.element_type = ADP_ELEMENT_TYPE_SLIDER,
		.minimum_value = 2500,
		.maximum_value = 4000,
		.initial_value = 3000,
	};
	adp_add_slider_to_dashboard(&slider_high);
	
	element_stream.element_id = ELEMENT_ID_SLIDER_HIGH;
	element_stream.stream_id = STREAM_ID_HYST_HIGH;
	adp_add_stream_to_element(&element_stream);
	
	/* Add slider stream(slider_low) */
	stream.stream_id = STREAM_ID_HYST_LOW;
	stream.type = ADP_STREAM_UINT_16;
	stream.mode = ADP_STREAM_IN;
	stream.state = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Hyst. Low");
	
	/* Add a slider to dashboard */
	struct adp_msg_conf_dashboard_element_slider slider_low = {
		.dashboard_id = DASHBOARD_ID_CONTROL,
		.element_id = ELEMENT_ID_SLIDER_LOW,
		.z_index = 0,
		.x = 75,
		.y = 60,
		.width = 156,
		.height = 25,
		.element_type = ADP_ELEMENT_TYPE_SLIDER,
		.minimum_value = 1000,
		.maximum_value = 2400,
		.initial_value = 2000,
	};
	adp_add_slider_to_dashboard(&slider_low);
	
	element_stream.element_id = ELEMENT_ID_SLIDER_LOW;
	element_stream.stream_id = STREAM_ID_HYST_LOW;
	adp_add_stream_to_element(&element_stream);
	
	/* Add segment to dashboard, use light sensor stream */
	/* Add segment stream(light sensor ADC value) */
	stream.stream_id = STREAM_ID_LIGHT_SENSOR_ADC;
	stream.type = ADP_STREAM_UINT_16;
	stream.mode = ADP_STREAM_OUT;
	stream.state = ADP_STREAM_ON;
	adp_configure_stream(&stream, "Light Sensor ADC");
	
	struct adp_msg_conf_dashboard_element_segment segment = {
		.dashboard_id = DASHBOARD_ID_CONTROL,
		.element_id = ELEMENT_ID_SEGMENT,
		.z_index = 0,
		.x = 500,
		.y = 20,
		.width = 150,
		.height = 50,
		.element_type = ADP_ELEMENT_TYPE_SEGMENT,
		.segment_count = 4,
		.base = 10,
		.transparency = 255,
		.color = {ADP_COLOR_RED}
	};
	adp_add_segment_to_dashboard(&segment);
	
	element_stream.element_id = ELEMENT_ID_SEGMENT;
	element_stream.stream_id = STREAM_ID_LIGHT_SENSOR_ADC;
	adp_add_stream_to_element(&element_stream);
}

/**
* \brief Add a dashboard and add all elements to the dashboard.
*
*/
static void adp_window_add_dashboard_control(void)
{
	/* Add a dashboard */	
	struct adp_msg_conf_dashboard dashboard_con = {
		.dashboard_id = DASHBOARD_ID_CONTROL,
		.color = {ADP_COLOR_WHITE},
		.height = 150,
	};
	adp_add_dashboard(&dashboard_con, DASHBOARD_CON_LABEL);
	
	adp_window_add_label_to_control_dashboard();
	adp_window_add_element_strem_to_control_dashboard();
}

void adp_window_init(void)
{
	adp_configure_info("Light Sensor Example for Xplained Pro",
					"This example demonstrates light intensity measurements "
					"through the ADC of a Xplained Pro board. You will need the "
					"IO1 Xplained Pro (EXT1).");
	
	adp_window_add_terminal();
	adp_window_add_dashboard_light_sensor();
	adp_window_add_dashboard_control();
}
