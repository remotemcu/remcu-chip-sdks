/**
 *
 * \file
 *
 * \brief SAM SLCD Quick Start.
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

struct usart_module usart_instance;

//! [slcd_data]
/* Character map 0-9, A-Z */
const uint32_t character_map[] = {
	0xE85C, 0x2008, 0xA314, 0xA30C, 0x6308, 0xC30C, 0xC31C, 0xA008, 0xE31C, 0xE30C, /* 0-9 */
	0xE318, 0xA68C, 0xC014, 0xA48C, 0xC314, 0xC310, 0xC21C, /* A-G */
	0x6318, 0x8484, 0x201C, 0x4930, 0x4014, 0x7818, 0x7038, /* H-N */
	0xE01C, 0xE310, 0xE03C, 0xE330, 0xC30C, 0x8480, /* O-T */
	0x601C, 0x4850, 0x6078, 0x1860, 0x1880, 0x8844  /* U-Z */
};

/* Digital map 0-9 */
const uint32_t digital_map[] = {
	0x77, 0x24, 0x5d, 0x6d, 0x2e, 0x6b, 0x7b, 0x25, 0x7f, 0x6f 
};

/*ICON COM/SEG map */
#define C8263A_ICON_WIFI0          0, 2
#define C8263A_ICON_WIFI1          0, 3
#define C8263A_ICON_WIFI2          1, 2
#define C8263A_ICON_WIFI3          1, 3
#define C8263A_ICON_BAT0           4, 2
#define C8263A_ICON_BAT1           4, 3
#define C8263A_ICON_BAT2           5, 2
#define C8263A_ICON_BAT3           5, 3

//! [slcd_data]

//! [setup]
/**
 *  Configure serial console.
 */
static void configure_console(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate    = 38400;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	stdio_serial_init(&usart_instance, EDBG_CDC_MODULE, &config_usart);
	usart_enable(&usart_instance);
}
//! [setup]

int main(void)
{
//! [setup_init]

	struct slcd_config config;
	system_init();
	configure_console();
	delay_init();

	/* Turn on the backlight. */
	port_pin_set_output_level(SLCD_BACLKLIGHT,true);

	printf("SLCD example starts\r\n");
//! [setup_config]
	slcd_get_config_defaults(&config);
	config.enable_bias_buffer = true;
	slcd_init(&config);
	slcd_set_contrast(0xc);
//! [setup_config]

//! [module_enable]
	slcd_enable();
//! [module_enable]

//! [setup_init]

//! [use_cases]
//! [use_cases_1]
	/* 1. Display all*/
	slcd_set_display_memory();
	delay_s(1);
	slcd_clear_display_memory();
//! [use_cases_1]

//! [use_cases_2]
	/* 2. Display icon*/
	for(uint32_t i=0; i<8; i++){
		slcd_set_pixel(i,0);
	}
	slcd_set_pixel(C8263A_ICON_WIFI0);
	slcd_set_pixel(C8263A_ICON_WIFI1);
	slcd_set_pixel(C8263A_ICON_WIFI2);
	slcd_set_pixel(C8263A_ICON_WIFI3);
	slcd_set_pixel(C8263A_ICON_BAT0);
	slcd_set_pixel(C8263A_ICON_BAT1);
	slcd_set_pixel(C8263A_ICON_BAT2);
	slcd_set_pixel(C8263A_ICON_BAT3);
	
	delay_s(1);
//! [use_cases_2]

//! [use_cases_3]
	/* 3. Character map*/
	slcd_character_map_set(SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT, 1);
	for(uint32_t i = 0; i < 8; i++) {
		slcd_character_write_data(0, 8 + i*2, character_map[10+i], 0xffff0003);
	}
//! [use_cases_3]
	
//! [use_cases_4]
	/* 4. Digital map*/
	slcd_character_map_set(SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT, 0);
	slcd_character_write_data(0, 1, digital_map[0], 0xffffff80);
	slcd_character_write_data(0, 4, digital_map[1], 0xffffff80);
	slcd_character_write_data(0, 5, digital_map[2], 0xffffff80);
	slcd_character_write_data(0, 6, digital_map[3], 0xffffff80);
	slcd_character_write_data(0, 7, digital_map[4], 0xffffff80);
	delay_s(2);
//! [use_cases_4]

//! [use_cases_5]
	/* 4. Blinking*/
	slcd_disable();
	struct slcd_blink_config blink_config;
	slcd_blink_get_config_defaults(&blink_config);
	blink_config.blink_all_seg = false;
	slcd_blink_set_config(&blink_config);

	for(uint32_t i=0; i<8; i++){
		slcd_set_blink_pixel(i,0);
		slcd_set_blink_pixel(i,1);
	}

	slcd_set_frame_counter(SLCD_FRAME_COUNTER_0,true,0x1f);
	slcd_enable_frame_counter(SLCD_FRAME_COUNTER_0);

	slcd_enable_blink();
	slcd_enable();
	delay_s(2);
//! [use_cases_5]
//! [use_cases]
    while(1){

    }

}

