/**
 * \file
 *
 * \brief Management of C42412A LCD Glass component.
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

#include "compiler.h"
#include "c42412a.h"
#include "conf_c42412a_lcdca.h"
#include "lcdca.h"

status_code_t c42412a_init(void)
{
	struct lcdca_config lcdca_cfg;

	lcdca_clk_init();
	lcdca_cfg.port_mask = C42412A_PORT_MASK;
	lcdca_cfg.x_bias = CONF_C42412A_X_BIAS;
	lcdca_cfg.lp_wave = true;
	lcdca_cfg.duty_type = C42412A_LCD_DUTY;
	lcdca_cfg.lcd_pres = CONF_C42412A_PRES;
	lcdca_cfg.lcd_clkdiv = CONF_C42412A_CLKDIV;
	lcdca_cfg.fc0 = CONF_C42412A_FC0;
	lcdca_cfg.fc1 = CONF_C42412A_FC1;
	lcdca_cfg.fc2 = CONF_C42412A_FC2;
	lcdca_cfg.contrast = CONF_C42412A_CONTRAST;
	lcdca_set_config(&lcdca_cfg);
	lcdca_enable();
	lcdca_enable_timer(LCDCA_TIMER_FC0);
	lcdca_enable_timer(LCDCA_TIMER_FC1);
	lcdca_enable_timer(LCDCA_TIMER_FC2);

	return STATUS_OK;
}

void c42412a_show_all(void)
{
	lcdca_blink_disable();
	lcdca_circular_shift_disable();
	lcdca_automated_char_stop();
	lcdca_set_display_memory();
}

void c42412a_clear_all(void)
{
	lcdca_blink_disable();
	lcdca_circular_shift_disable();
	lcdca_automated_char_stop();
	lcdca_clear_display_memory();
}

void c42412a_show_text(const uint8_t *data)
{
	lcdca_write_packet(LCDCA_TDG_14SEG4COM, C42412A_FIRST_14SEG_4C, data,
			C42412A_WIDTH_14SEG_4C, LCDCA_CMCFG_DREV_RIGHT);
}

void c42412a_clear_text(void)
{
	uint8_t clear_data[5] = {0x0F, 0x0F, 0x0F, 0x0F, 0x0F};

	lcdca_write_packet(LCDCA_TDG_14SEG4COM, C42412A_FIRST_14SEG_4C,
			clear_data, C42412A_WIDTH_14SEG_4C, LCDCA_CMCFG_DREV_RIGHT);
}

void c42412a_show_icon(uint8_t icon_com, uint8_t icon_seg)
{
	if (icon_com < 2) {
		lcdca_clear_blink_pixel(icon_com, icon_seg);
	}

	lcdca_set_pixel(icon_com, icon_seg);
}

void c42412a_clear_icon(uint8_t icon_com, uint8_t icon_seg)
{
	lcdca_clear_pixel(icon_com, icon_seg);
}

void c42412a_blink_icon_start(uint8_t icon_com, uint8_t icon_seg)
{
	struct lcdca_blink_config blink_cfg;

	blink_cfg.lcd_blink_timer = CONF_C42412A_BLINK_TIMER;
	blink_cfg.lcd_blink_mode = LCDCA_BLINK_SELECTED;
	lcdca_blink_set_config(&blink_cfg);

	/* Be sure to blink only pixel that can do that by hardware. */
	if (icon_seg < 2) {
		lcdca_set_blink_pixel(icon_com, icon_seg);
	}

	lcdca_blink_enable();
	lcdca_set_pixel(icon_com, icon_seg);
}

void c42412a_blink_icon_stop(uint8_t icon_com, uint8_t icon_seg)
{
	lcdca_clear_blink_pixel(icon_com, icon_seg);
}

void c42412a_blink_screen(void)
{
	struct lcdca_blink_config blink_cfg;

	lcdca_clear_blink_all_pixel();

	blink_cfg.lcd_blink_timer = CONF_C42412A_BLINK_TIMER;
	blink_cfg.lcd_blink_mode = LCDCA_BLINK_FULL;
	lcdca_blink_set_config(&blink_cfg);

	lcdca_blink_enable();
}

void c42412a_blink_disable(void)
{
	lcdca_blink_disable();
}

void c42412a_set_contrast(int8_t contrast)
{
	lcdca_set_contrast(contrast);
}

void c42412a_show_battery(enum c42412a_battery_value val)
{
	lcdca_clear_pixel(C42412A_ICON_BAT_LEVEL_1);
	lcdca_clear_pixel(C42412A_ICON_BAT_LEVEL_2);
	lcdca_clear_pixel(C42412A_ICON_BAT_LEVEL_3);
	lcdca_set_pixel(C42412A_ICON_BAT);
	if (val > 2) {
		lcdca_set_pixel(C42412A_ICON_BAT_LEVEL_3);
	}
	if (val > 1) {
		lcdca_set_pixel(C42412A_ICON_BAT_LEVEL_2);
	}
	if (val > 0) {
		lcdca_set_pixel(C42412A_ICON_BAT_LEVEL_1);
	}
}

void c42412a_show_wireless(enum c42412a_wireless_value val)
{
	lcdca_clear_pixel(C42412A_ICON_WLESS_LEVEL_1);
	lcdca_clear_pixel(C42412A_ICON_WLESS_LEVEL_2);
	lcdca_clear_pixel(C42412A_ICON_WLESS_LEVEL_3);
	lcdca_set_pixel(C42412A_ICON_WLESS_LEVEL_0);
	if (val > 2) {
		lcdca_set_pixel(C42412A_ICON_WLESS_LEVEL_3);
	}
	if (val > 1) {
		lcdca_set_pixel(C42412A_ICON_WLESS_LEVEL_2);
	}
	if (val > 0) {
		lcdca_set_pixel(C42412A_ICON_WLESS_LEVEL_1);
	}
}

void c42412a_show_numeric_dec(int32_t value)
{
	uint8_t lcd_num[6];

	Assert(value > -200000);
	Assert(value < 200000);

	if(value < 0) {
		lcdca_set_pixel(C42412A_ICON_MINUS);
	} else {
		lcdca_clear_pixel(C42412A_ICON_MINUS);
	}

	value = Abs(value);

	if(value > 99999) {
		value -= 100000;
		lcdca_set_pixel(C42412A_ICON_MINUS_SEG1);
		lcdca_set_pixel(C42412A_ICON_MINUS_SEG2);
	} else {
		lcdca_clear_pixel(C42412A_ICON_MINUS_SEG1);
		lcdca_clear_pixel(C42412A_ICON_MINUS_SEG2);
	}

	sprintf((char*)lcd_num, "%4d", (int)value);

	c42412a_show_text((uint8_t const*)&lcd_num);
}

void c42412a_clear_numeric_dec(void)
{
	uint8_t clear_data[5] = {0x0F, 0x0F, 0x0F, 0x0F, 0x0F};

	lcdca_clear_pixel(C42412A_ICON_MINUS);
	lcdca_clear_pixel(C42412A_ICON_MINUS_SEG1);
	lcdca_clear_pixel(C42412A_ICON_MINUS_SEG2);
	c42412a_show_text((uint8_t const*)clear_data);
}

void c42412a_text_scrolling_start(const uint8_t *data, uint32_t length)
{
	/* Settings of automated display */
	struct lcdca_automated_char_config automated_char_config;

	automated_char_config.automated_mode = LCDCA_AUTOMATED_MODE_SCROLLING;
	automated_char_config.automated_timer =
			CONF_C42412A_TEXT_SCROLLING_TIMER;
	automated_char_config.lcd_tdg = LCDCA_TDG_14SEG4COM;
	automated_char_config.stseg = C42412A_FIRST_14SEG_4C;
	automated_char_config.dign = C42412A_WIDTH_14SEG_4C;
	/* STEPS = string length - DIGN + 1 */
	automated_char_config.steps = length - C42412A_WIDTH_14SEG_4C + 1;
	automated_char_config.dir_reverse = LCDCA_AUTOMATED_DIR_NOT_REVERSE;
	lcdca_automated_char_set_config(&automated_char_config);
	lcdca_automated_char_start(data, length);
}

void c42412a_text_scrolling_stop(void)
{
	lcdca_automated_char_stop();
}
