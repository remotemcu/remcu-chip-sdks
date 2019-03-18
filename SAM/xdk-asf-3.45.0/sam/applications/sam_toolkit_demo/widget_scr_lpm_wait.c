/**
 * \file
 *
 * \brief Wait mode widget for SAM toolkit demo application.
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
 
#include "demo.h"
#include <asf.h>
#include "string.h"
#include "bitmaps.h"
#include "conf_clock.h"

/** Widget application context */
struct widget_context_lpm_wait {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/** Pointer to frame for application */
	struct wtk_basic_frame *logo_frame;
	/** Label widget for board name */
	struct wtk_label *lbl_board_name;
	/** Label widget for function name */
	struct wtk_label *lbl_func_name;
	/** Pointer to frame for application */
	struct wtk_basic_frame *lpm_wait_frame;
	/** Label widget for wait mode indications */
	struct wtk_label *lbl_indication[2];
};

/** Statically allocated context pointer */
static struct widget_context_lpm_wait *widget_ctx_lpm_wait;

static char demo_func_name[] = "Low-Power Mode";
static char str_wait_mode[] = "Wait Mode";
static char str_wait_ret[] = "Touch the screen\n to wake-up";

/** Wait mode bitmap */
static struct gfx_bitmap win_lpm_wait_icon = {
	.width = 64, .height = 64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_WAIT_MODE
};

/** Logo bitmap */
static struct gfx_bitmap win_root_logo_icon = {
	.width = 87, .height = 40,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_LOGO_ATMEL
};

/** PLLA count */
#define PLLA_COUNT    0x3Fu

/** Wakeup pin for wait mode: Touchscreen controller IRQ pin */
#define WAKEUP_WAIT_INPUT_ID    LPM_WAKEUP_INPUT_ID

/**
 * \brief Configure UART console.
 */
static void reconfigure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 *  \brief System enter wait mode.
 */
static void sys_enter_wait_mode(void)
{
	/* Disable all ITs */
	taskENTER_CRITICAL();

	/* Disable RTC */
	NVIC_DisableIRQ( RTC_IRQn );
	NVIC_ClearPendingIRQ( RTC_IRQn );
	NVIC_DisableIRQ( RTC_IRQn );
	rtc_disable_interrupt( RTC, RTC_IER_SECEN );

	/* Configure 4Mhz fast RC oscillator */
	pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);
	pmc_switch_mainck_to_fastrc(CKGR_MOR_MOSCRCF_4_MHz);
	pmc_switch_mck_to_mainck(PMC_PCK_PRES_CLK_1);

	/* Disable unused clock to save power */
	pmc_osc_disable_xtal(0);
	pmc_disable_pllack();

	/* Set wakeup input for fast startup */
	pmc_set_fast_startup_input(WAKEUP_WAIT_INPUT_ID);

	/* Enter wait mode */
	pmc_enable_waitmode();

	/* Switch MCK to slow clock  */
	pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);

	/* Switch mainck to external xtal */
	pmc_switch_mainck_to_xtal(0, BOARD_OSC_STARTUP_US);

	pmc_enable_pllack(CONFIG_PLL0_MUL-1, PLLA_COUNT, 1);

	pmc_switch_mck_to_pllack(PMC_MCKR_PRES_CLK_2);

	taskEXIT_CRITICAL();

	/* Reset wakeup inputs */
	reconfigure_console();
}

/**
 * \brief Setup wait mode widget.
 *
 * Allocates memory for the application context, and creates all widgets that
 * make up its interface. If memory allocation or widget creation fails, the
 * application exits immediately.
 */
static void app_widget_launch_lpm_wait(void)
{
	struct win_window *parent;
	struct win_area area;

	/* Create a new context for the GUI, clear new context state */
	widget_ctx_lpm_wait = membag_alloc(
		sizeof(struct widget_context_lpm_wait));

	/* Set the background information for the GUI window */
	widget_ctx_lpm_wait->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx_lpm_wait->frame_bg.data.color = GFX_COLOR(255, 255, 255);

	/* Set the area for the GUI window */
	area = win_get_attributes(win_get_root())->area;

	/* Create and show the main GUI frame */
	widget_ctx_lpm_wait->frame = wtk_basic_frame_create(
			win_get_root(), &area, &widget_ctx_lpm_wait->frame_bg, NULL,
			NULL, NULL);
	if (!widget_ctx_lpm_wait->frame) {
		goto error_frame;
	}

	parent = wtk_basic_frame_as_child(widget_ctx_lpm_wait->frame);
	win_show(parent);

	/* Set area for logo bitmap */
	area.pos.x = 0;
	area.pos.y = 0;
	area.size.x = 87;
	area.size.y = 40;
	/* Create and show the main GUI frame */
	widget_ctx_lpm_wait->logo_frame = wtk_basic_frame_create(
			parent, &area, &win_root_logo_icon, NULL,
			NULL, NULL);
	if (!widget_ctx_lpm_wait->frame) {
		goto error_frame;
	}

	win_show(wtk_basic_frame_as_child(widget_ctx_lpm_wait->logo_frame));

	/* Set area for board name */
	area.pos.x = 100;
	area.pos.y = 0;
	wtk_label_size_hint(&area.size, demo_board_name);

	/* Create label inside frame */
	widget_ctx_lpm_wait->lbl_board_name = wtk_label_create(
			parent, &area, demo_board_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm_wait->lbl_board_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm_wait->lbl_board_name));

	/* Set area for function name */
	area.pos.x = 100;
	area.pos.y = 20;
	wtk_label_size_hint(&area.size, demo_func_name);

	/* Create label inside frame */
	widget_ctx_lpm_wait->lbl_func_name = wtk_label_create(
			parent, &area, demo_func_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm_wait->lbl_func_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm_wait->lbl_func_name));

	/* Set area for wait icon */
	area.pos.x = 91;
	area.pos.y = 66;
	area.size.x = 64;
	area.size.y = 64;
	/* Create and show the main GUI frame */
	widget_ctx_lpm_wait->lpm_wait_frame = wtk_basic_frame_create(
			parent, &area, &win_lpm_wait_icon, NULL,
			NULL, NULL);
	if (!widget_ctx_lpm_wait->lpm_wait_frame) {
		goto error_frame;
	}

	win_show(wtk_basic_frame_as_child(widget_ctx_lpm_wait->lpm_wait_frame));

	/* Set area for wait mode indication */
	area.pos.x = 66;
	area.pos.y = 150;
	wtk_label_size_hint(&area.size, str_wait_mode);

	/* Create label inside frame */
	widget_ctx_lpm_wait->lbl_indication[0] = wtk_label_create(
			parent, &area, str_wait_mode,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm_wait->lbl_indication[0]) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm_wait->lbl_indication[0]));

	/* Set area for return indicaiton */
	area.pos.x = 42;
	area.pos.y = 240;
	wtk_label_size_hint(&area.size, str_wait_ret);

	/* Create label inside frame */
	widget_ctx_lpm_wait->lbl_indication[1] = wtk_label_create(
			parent, &area, str_wait_ret,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm_wait->lbl_indication[1]) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm_wait->lbl_indication[1]));

	/* System enter wait mode */
	sys_enter_wait_mode();
	win_destroy(wtk_basic_frame_as_child(widget_ctx_lpm_wait->frame));

	/* Enable special wait mode */
	demo_set_special_mode_status(DEMO_WAIT_MODE, 1);

	return;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx_lpm_wait->frame));
error_frame:
	membag_free(widget_ctx_lpm_wait);
}

/**
 * \brief Enable/disable wait mode widget.
 *
 * \param on Turn on/off wait mode widget.
 */
void app_widget_lpm_wait_on(uint8_t on)
{
	if (on) {
		app_widget_launch_lpm_wait();
	} else {
		if (widget_ctx_lpm_wait->frame) {
			win_destroy(wtk_basic_frame_as_child(widget_ctx_lpm_wait->frame));
		}
	}
}
