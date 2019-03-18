/**
 * \file
 *
 * \brief Backup mode widget for SAM toolkit demo application.
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

/** Widget application context */
struct widget_context_lpm_backup {
	/** Pointer to frame for application */
	struct wtk_basic_frame *frame;
	/** Frame background object */
	struct gfx_bitmap frame_bg;
	/** Pointer to frame for application */
	struct wtk_basic_frame *logo_frame;
	/** Label widget for user selection feedback */
	struct wtk_label *lbl_board_name;
	/** Label widget for user selection feedback */
	struct wtk_label *lbl_func_name;
	/** Pointer to frame for application */
	struct wtk_basic_frame *lpm_backup_frame;
	/** Label widget for user selection feedback */
	struct wtk_label *lbl_indication[2];
};

/** Statically allocated context pointer */
static struct widget_context_lpm_backup *widget_ctx_lpm_backup;

static char demo_func_name[] = "Low-Power Mode";
static char str_backup_mode[] = "Backup Mode";
static char str_backup_ret[] = "Touch the screen\n to reset";

/** Logo bitmap */
static struct gfx_bitmap win_root_logo_icon = {
	.width = 87, .height = 40,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_LOGO_ATMEL
};

/** Backup mode bitmap */
static struct gfx_bitmap win_lpm_backup_icon = {
	.width = 64, .height = 64,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_BACKUP_MODE
};

/**
 * \brief Setup backup mode widget.
 *
 * Allocates memory for the application context, and creates all widgets that
 * make up its interface. If memory allocation or widget creation fails, the
 * application exits immediately.
 */
static void app_widget_launch_lpm_backup(void)
{
	struct win_window *parent;
	struct win_area area;

	/* Create a new context for the GUI, clear new context state */
	widget_ctx_lpm_backup
		= membag_alloc(sizeof(struct widget_context_lpm_backup));

	/* Set the background information for the GUI window */
	widget_ctx_lpm_backup->frame_bg.type = GFX_BITMAP_SOLID;
	widget_ctx_lpm_backup->frame_bg.data.color = GFX_COLOR(255, 255, 255);

	/* Set the area for the GUI window */
	area = win_get_attributes(win_get_root())->area;

	/* Create and show the main GUI frame */
	widget_ctx_lpm_backup->frame = wtk_basic_frame_create(
			win_get_root(), &area, &widget_ctx_lpm_backup->frame_bg, NULL,
			NULL, NULL);
	if (!widget_ctx_lpm_backup->frame) {
		goto error_frame;
	}

	parent = wtk_basic_frame_as_child(widget_ctx_lpm_backup->frame);
	win_show(parent);

	/* Set area for the logo */
	area.pos.x = 0;
	area.pos.y = 0;
	area.size.x = 87;
	area.size.y = 40;
	/* Create and show the main GUI frame */
	widget_ctx_lpm_backup->logo_frame = wtk_basic_frame_create(
			parent, &area, &win_root_logo_icon, NULL,
			NULL, NULL);
	if (!widget_ctx_lpm_backup->frame) {
		goto error_frame;
	}

	win_show(wtk_basic_frame_as_child(widget_ctx_lpm_backup->logo_frame));

	/* Update area for board name */
	area.pos.x = 100;
	area.pos.y = 0;
	wtk_label_size_hint(&area.size, demo_board_name);

	/* Create label inside frame */
	widget_ctx_lpm_backup->lbl_board_name = wtk_label_create(
			parent, &area, demo_board_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm_backup->lbl_board_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm_backup->lbl_board_name));

	/* Update area for function name */
	area.pos.x = 100;
	area.pos.y = 20;
	wtk_label_size_hint(&area.size, demo_func_name);

	/* Create label inside frame */
	widget_ctx_lpm_backup->lbl_func_name = wtk_label_create(
			parent, &area, demo_func_name,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm_backup->lbl_func_name) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm_backup->lbl_func_name));

	/* Set area for backup icon */
	area.pos.x = 91;
	area.pos.y = 66;
	area.size.x = 64;
	area.size.y = 64;
	/* Create and show the main GUI frame */
	widget_ctx_lpm_backup->lpm_backup_frame = wtk_basic_frame_create(
			parent, &area, &win_lpm_backup_icon, NULL,
			NULL, NULL);
	if (!widget_ctx_lpm_backup->lpm_backup_frame) {
		goto error_frame;
	}

	win_show(wtk_basic_frame_as_child(widget_ctx_lpm_backup->	lpm_backup_frame));

	/* Set area for the label widget */
	area.pos.x = 66;
	area.pos.y = 150;
	wtk_label_size_hint(&area.size, str_backup_mode);

	/* Create label inside frame */
	widget_ctx_lpm_backup->lbl_indication[0] = wtk_label_create(
			parent, &area, str_backup_mode,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm_backup->lbl_indication[0]) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm_backup->lbl_indication[0]));

	/* Update area for the return indication*/
	area.pos.x = 42;
	area.pos.y = 240;
	wtk_label_size_hint(&area.size, str_backup_ret);

	/* Create label inside frame */
	widget_ctx_lpm_backup->lbl_indication[1] = wtk_label_create(
			parent, &area, str_backup_ret,
			GFX_COLOR(0, 0, 0), NULL, false);
	if (!widget_ctx_lpm_backup->lbl_indication[1]) {
		goto error_widget;
	}

	win_show(wtk_label_as_child(widget_ctx_lpm_backup->lbl_indication[1]));

	/* Disable unused peripherals */
	NVIC_DisableIRQ( RTC_IRQn );
	NVIC_ClearPendingIRQ( RTC_IRQn );
	NVIC_DisableIRQ( RTC_IRQn );
	rtc_disable_interrupt( RTC, RTC_IER_SECEN );

	/* Enable the PIO for wake-up */
	supc_set_wakeup_inputs(SUPC, LPM_WAKEUP_INPUT_ID,
			LPM_WAKEUP_INPUT_ID);

	/* Disable unused clock to save power */
	pmc_switch_mck_to_sclk(PMC_MCKR_PRES_CLK_1);
	pmc_osc_disable_xtal(0);
	pmc_disable_pllack();

	/* Enter into backup mode */
	pmc_enable_backupmode();
	supc_enable_backup_mode(SUPC);
	return;

	/* Error handling to clean up allocations after an error */
error_widget:
	win_destroy(wtk_basic_frame_as_child(widget_ctx_lpm_backup->frame));
error_frame:
	membag_free(widget_ctx_lpm_backup);
}

/**
 * \brief Enable/disable backup mode widget.
 *
 * \param on Turn on/off backup mode widget.
 */
void app_widget_lpm_backup_on(uint8_t on)
{
	if (on) {
		app_widget_launch_lpm_backup();
	} else {
		if (widget_ctx_lpm_backup->frame) {
			win_destroy(wtk_basic_frame_as_child(
					widget_ctx_lpm_backup->frame));
		}
	}
}
