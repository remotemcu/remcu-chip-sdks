/**
 * \file
 *
 * \brief GFX task for the FreeRTOS Web/DSP Demo.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "task_demo.h"
#include "arm_math.h"
#include "logo_atmel.h"
#include <FreeRTOS.h>
#include <StackMacros.h>
#include <croutine.h>
#include <list.h>
#include <mpu_wrappers.h>
#include <portable.h>
#include <projdefs.h>
#include <queue.h>
#include <semphr.h>
#include <task.h>
#include <timers.h>
#include <pmc.h>
#include <sysclk.h>
#include "ili93xx.h"
#include "ili9325_regs.h"
#include "ili9341_regs.h"
#include "aat31xx.h"
#include "pio_handler.h"
#include "smc.h"
#include "ethernet_sam.h"
#include "timer_mgt_sam.h"
#include "rtouch.h"

static void gfx_task(void *pvParameters);
static void gfx_init(void);
static void gfx_refresh_wav(void);
static void gfx_refresh_mag(void);
static void gfx_draw_bmpfile(const uint8_t *bmpImage);

/** Chip select number to be set */
#define ILI93XX_LCD_CS  1

/** IRQ priority for PIO (The lower the value, the greater the priority) */
#define IRQ_PRIOR_PIO  9

const portTickType instructions_delay = 50UL / portTICK_RATE_MS;
static const portTickType presentation_delay = 2000UL / portTICK_RATE_MS;
static const portTickType max_block_time_ticks = 1UL / portTICK_RATE_MS;
static const portTickType touch_delay = 10UL / portTICK_RATE_MS;

/** Hold the instructions screen and prevent other task from running. */
uint32_t app_hold = 1;

/** IP mode: 0 unselected, 1 static, 2 dhcp.*/
uint32_t g_ip_mode = 0;

int8_t g_c_ipconfig[25];

/** Wave input buffer defined in DSP task. */
extern float32_t wav_in_buffer[];

/** Magnitude input buffer defined in DSP task. */
extern float32_t mag_in_buffer[];
extern uint32_t mag_in_buffer_int[];

/** GFX notification semaphore. Triggered from DSP task. */
extern xSemaphoreHandle gfx_notification_semaphore;

static uint32_t button1_filter_cnt = 0;
static uint32_t button2_filter_cnt = 0;
static uint32_t touch_sel = 0;
#define COLOR_CUSTOM_GREY  0xE4E4E4u

/** The Y value to determine which button is pressed. */
#define BUTTON_DETECT_Y  160

/** BMP (Windows) Header Format. */
COMPILER_PACK_SET(1)
struct bmpfile_header {
	/** signature, must be 4D42 hex */
	uint16_t type;
	/** size of BMP file in bytes (unreliable) */
	uint32_t file_size;
	/** reserved, must be zero */
	uint16_t reserved1;
	/** reserved, must be zero */
	uint16_t reserved2;
	/** offset to start of image data in bytes */
	uint32_t offset;
	/** size of BITMAPINFOHEADER structure, must be 40 */
	uint32_t header_size;
	/** image width in pixels */
	uint32_t width;
	/** image height in pixels */
	uint32_t height;
	/** number of planes in the image, must be 1 */
	uint16_t planes;
	/** number of bits per pixel (1, 4, 8, 16, 24, 32) */
	uint16_t bits;
	/** compression type (0=none, 1=RLE-8, 2=RLE-4) */
	uint32_t compression;
	/** size of image data in bytes (including padding) */
	uint32_t inage_size;
	/** horizontal resolution in pixels per meter */
	uint32_t h_resolution;
	/** vertical resolution in pixels per meter */
	uint32_t v_resolution;
	/** number of colors in image, or zero */
	uint32_t colours;
	/** number of important colors, or zero */
	uint32_t important_colors;
};
COMPILER_PACK_RESET()

/**
 * \brief Callback called when the pen is pressed on the touchscreen.
 *
 * \param x horizontal position (in pixel if ts calibrated).
 * \param y vertical position (in pixel if ts calibrated).
 */
static void event_handler(rtouch_event_t const *event)
{
	static uint32_t selected = 0;

	switch(event->type) {
	case RTOUCH_MOVE:
	case RTOUCH_PRESS:
	case RTOUCH_RELEASE:
		if (event->panel.y < BUTTON_DETECT_Y) {
			if (selected != 1) {
				selected = 1;
				/* Static IP button selected. */
				/* Button 1. */
				ili93xx_set_foreground_color(COLOR_BLACK);
				ili93xx_draw_rectangle(20,70,220,130);
				ili93xx_set_foreground_color(COLOR_CUSTOM_GREY);
				ili93xx_draw_rectangle(22,72,222,132);
				ili93xx_set_foreground_color(COLOR_LIGHTGREY);
				ili93xx_draw_filled_rectangle(21,71,221,131);
				ili93xx_set_foreground_color(COLOR_BLACK);
				ili93xx_draw_string(92, 91, (uint8_t *)"Static");

				/* Button 2. */
				ili93xx_set_foreground_color(COLOR_CUSTOM_GREY);
				ili93xx_draw_rectangle(20,170,220,230);
				ili93xx_set_foreground_color(COLOR_BLACK);
				ili93xx_draw_rectangle(22,172,222,232);
				ili93xx_set_foreground_color(COLOR_LIGHTGREY);
				ili93xx_draw_filled_rectangle(21,171,221,231);
				ili93xx_set_foreground_color(COLOR_BLACK);
				ili93xx_draw_string(102, 191, (uint8_t *)"DHCP");
			}
		}
		else {
			if (selected != 2) {
				selected = 2;
				/* DHCP IP button selected. */
				/* Button 1. */
				ili93xx_set_foreground_color(COLOR_CUSTOM_GREY);
				ili93xx_draw_rectangle(20,70,220,130);
				ili93xx_set_foreground_color(COLOR_BLACK);
				ili93xx_draw_rectangle(22,72,222,132);
				ili93xx_set_foreground_color(COLOR_LIGHTGREY);
				ili93xx_draw_filled_rectangle(21,71,221,131);
				ili93xx_set_foreground_color(COLOR_BLACK);
				ili93xx_draw_string(92, 91, (uint8_t *)"Static");

				/* Button 2. */
				ili93xx_set_foreground_color(COLOR_BLACK);
				ili93xx_draw_rectangle(20,170,220,230);
				ili93xx_set_foreground_color(COLOR_CUSTOM_GREY);
				ili93xx_draw_rectangle(22,172,222,232);
				ili93xx_set_foreground_color(COLOR_LIGHTGREY);
				ili93xx_draw_filled_rectangle(21,171,221,231);
				ili93xx_set_foreground_color(COLOR_BLACK);
				ili93xx_draw_string(102, 191, (uint8_t *)"DHCP");
			}
		}
		break;
	}

	/** If released, freeze buttons and perform IP settings. */
	if (event->type == RTOUCH_RELEASE) {
		ili93xx_set_foreground_color(COLOR_GRAY);
		ili93xx_draw_string(92, 91, (uint8_t *)"Static");
		ili93xx_draw_string(102, 191, (uint8_t *)"DHCP");
		if (event->panel.y < 160)
			g_ip_mode = 1;
		else
			g_ip_mode = 2;
	}
}

/**
 * \brief Create the GFX task.
 *
 * \param stack_depth_words Task stack size in 32 bits word.
 * \param task_priority Task priority.
 */
void create_gfx_task(uint16_t stack_depth_words,
		unsigned portBASE_TYPE task_priority)
{
	/** Initialize display. */
	gfx_init();

	/** Create the task as described above. */
	xTaskCreate(gfx_task, (const signed char *const) "GFX",
			stack_depth_words, NULL, task_priority, NULL);
}

/**
 * \brief GFX task core function.
 *
 * \param pvParameters Junk parameter.
 */
static void gfx_task(void *pvParameters)
{
	/* Just to avoid compiler warnings. */
	UNUSED(pvParameters);

	/* Enable display, backlight and print ATMEL logo. */
	ili93xx_set_cursor_position(0,0);
	ili93xx_set_foreground_color(COLOR_WHITE);
	ili93xx_draw_filled_rectangle(0, 0, ILI93XX_LCD_WIDTH, ILI93XX_LCD_HEIGHT);
	gfx_draw_bmpfile(logo_atmel_bmp);
	ili93xx_display_on();
	for (uint32_t i = AAT31XX_MIN_BACKLIGHT_LEVEL; i <= AAT31XX_MAX_BACKLIGHT_LEVEL; ++i) {
		aat31xx_set_backlight(i);
		vTaskDelay(40);
	}
	vTaskDelay(presentation_delay);

	/** Initialize touchscreen with default calibration */
	pmc_enable_periph_clk(ID_PIOA);
	pio_handler_set_priority(PIOA, PIOA_IRQn, IRQ_PRIOR_PIO);
	pmc_enable_periph_clk(ID_SPI);
	rtouch_init(ILI93XX_LCD_WIDTH, ILI93XX_LCD_HEIGHT);
	rtouch_enable();
	rtouch_set_event_handler(event_handler);
	/*
	 * Set touch screen calibration parameters which are got
	 * from manual calibration when developing.
	 */
	rtouch_set_calibration_parameter(7432, -5637, 318, 1845);

	/** Draw IP config menu. */
	ili93xx_set_foreground_color(COLOR_WHITE);
	ili93xx_draw_filled_rectangle(0, 0, ILI93XX_LCD_WIDTH, ILI93XX_LCD_HEIGHT);

	/** Button 1. */
	ili93xx_set_foreground_color(COLOR_CUSTOM_GREY);
	ili93xx_draw_rectangle(20,70,220,130);
	ili93xx_set_foreground_color(COLOR_BLACK);
	ili93xx_draw_rectangle(22,72,222,132);
	ili93xx_set_foreground_color(COLOR_LIGHTGREY);
	ili93xx_draw_filled_rectangle(21,71,221,131);
	ili93xx_set_foreground_color(COLOR_BLACK);
	ili93xx_draw_string(92, 91, (uint8_t *)"Static");

	/** Button 2. */
	ili93xx_set_foreground_color(COLOR_CUSTOM_GREY);
	ili93xx_draw_rectangle(20,170,220,230);
	ili93xx_set_foreground_color(COLOR_BLACK);
	ili93xx_draw_rectangle(22,172,222,232);
	ili93xx_set_foreground_color(COLOR_LIGHTGREY);
	ili93xx_draw_filled_rectangle(21,171,221,231);
	ili93xx_set_foreground_color(COLOR_BLACK);
	ili93xx_draw_string(102, 191, (uint8_t *)"DHCP");
	ili93xx_draw_string(22, 30, (uint8_t *)"IP Configuration");
	ili93xx_draw_string(20, 260, (uint8_t *)"Assigned IP:");
	ili93xx_draw_rectangle(20,280,220,310);

	while (g_ip_mode == 0) {
		rtouch_process();
		vTaskDelay(touch_delay);
	}

	/** Bring up the ethernet interface & initializes timer0, channel0 */
	ili93xx_draw_string(30, 290, (uint8_t *)"Please wait...");
	init_ethernet();
	app_hold = 0;

	/** Wait for IP to be configured. Done in LwIP. */
	while (g_ip_mode != 3) {
		vTaskDelay(touch_delay);
	}

	/** Show configured IP and unlock all other waiting tasks. */
	ili93xx_set_foreground_color(COLOR_WHITE);
	ili93xx_draw_filled_rectangle(20, 280, 220, 310);
	ili93xx_draw_filled_rectangle(0, 0, 240, 60);
	ili93xx_set_foreground_color(COLOR_BLACK);
	ili93xx_draw_rectangle(20, 280, 220, 310);
	ili93xx_draw_string(30, 290, (uint8_t const *)g_c_ipconfig);
	ili93xx_draw_string(5, 30, (uint8_t *)"Hit screen to start!");
	while (rtouch_is_pressed() == false) {
		vTaskDelay(touch_delay);
	}

	/** Draw application context. */
	ili93xx_set_foreground_color(COLOR_WHITE);
	ili93xx_draw_filled_rectangle(0, 0, ILI93XX_LCD_WIDTH, ILI93XX_LCD_HEIGHT);
	ili93xx_set_foreground_color(COLOR_BLACK);
#if SAM4E
	ili93xx_draw_string(10, 30, (uint8_t *)"SAM4E Web/DSP Demo");
#else
# error No proper title found!
#endif
	ili93xx_draw_rectangle(20, 60, 220, 160);
	ili93xx_draw_line(15, 110, 225, 110);
	ili93xx_draw_rectangle(20, 180, 220, 280);
	ili93xx_draw_string(15, 295, (uint8_t *)"0Hz");
	ili93xx_draw_string(165, 295, (uint8_t *)"10kHz");

	/** GFX task Loop. */
	while (1) {
		/** Wait for DSP task processing to complete. */
		if (xSemaphoreTake(gfx_notification_semaphore, max_block_time_ticks)) {

			/** Display sampled signal */
			/* 800 cyles at most in approx. 6ms */
			gfx_refresh_wav();

			/** Refresh magnitude */
			/* 800.000 cyles at most in approx. 6ms */
			gfx_refresh_mag();
		}
	}
}

/**
 * \brief Initialize the LCD.
 */
static void gfx_init(void)
{
	struct ili93xx_opt_t g_ili93xx_display_opt;

	/** Enable peripheral clock */
	pmc_enable_periph_clk(ID_SMC);

	/** Configure SMC interface for Lcd */
	smc_set_setup_timing(SMC,ILI93XX_LCD_CS,SMC_SETUP_NWE_SETUP(2)
			| SMC_SETUP_NCS_WR_SETUP(2)
			| SMC_SETUP_NRD_SETUP(2)
			| SMC_SETUP_NCS_RD_SETUP(2));
	smc_set_pulse_timing(SMC, ILI93XX_LCD_CS , SMC_PULSE_NWE_PULSE(4)
			| SMC_PULSE_NCS_WR_PULSE(4)
			| SMC_PULSE_NRD_PULSE(10)
			| SMC_PULSE_NCS_RD_PULSE(10));
	smc_set_cycle_timing(SMC, ILI93XX_LCD_CS, SMC_CYCLE_NWE_CYCLE(10)
			| SMC_CYCLE_NRD_CYCLE(22));
	smc_set_mode(SMC, ILI93XX_LCD_CS, SMC_MODE_READ_MODE
			| SMC_MODE_WRITE_MODE);

	/** Initialize display parameter */
	g_ili93xx_display_opt.ul_width = ILI93XX_LCD_WIDTH;
	g_ili93xx_display_opt.ul_height = ILI93XX_LCD_HEIGHT;
	g_ili93xx_display_opt.foreground_color = COLOR_WHITE;
	g_ili93xx_display_opt.background_color = COLOR_WHITE;

	/** Initialize LCD */
	if (1 == ili93xx_init(&g_ili93xx_display_opt)) {
		while(1);
	}
}

/**
 * \brief Refresh wave rendering on the LCD.
 */
static void gfx_refresh_wav(void) {
	uint32_t i = 0;
	uint32_t col = 21;
	float32_t display_factor = 40;
	float32_t pixel;

	/** Clear previous wave drawing. */
	ili93xx_set_foreground_color(COLOR_WHITE);
	ili93xx_draw_filled_rectangle(21, 61, 219, 159);
	ili93xx_set_foreground_color(COLOR_BLACK);
	ili93xx_draw_line(10, 110, 230, 110);

	/** Draw wave with available data. */
	ili93xx_set_foreground_color(COLOR_BLUE);

	/** Limit to 398, ie. ~200 to fit the rendering frame. */
	while (i < 398) {
		pixel = (wav_in_buffer[i] * display_factor);
		if ((pixel < 50) && (pixel > -50)) {
			ili93xx_draw_pixel(col, (uint32_t)(110 - pixel));
		}

		i = i + 2;
		col = col + 1;
	}
}

/**
 * \brief Refresh magnitude rendering on the LCD.
 */
static void gfx_refresh_mag(void) {
	uint32_t i = 0;
	uint32_t col = 22;

	/** Clear previous magnitude drawing. */
	ili93xx_set_foreground_color(COLOR_WHITE);
	ili93xx_draw_filled_rectangle(21, 181, 219, 279);

	/** Refresh FFT MAG display. */
	ili93xx_set_foreground_color(COLOR_RED);

	/**
	 * Limit to 99, even if we got 128 magnitudes to display.
	 * Bins are printed using col, incremented by mean of 2 to keep
	 * a clean rendering. Hence we cannot render all the magnitudes,
	 * because of the screen width. It would require a 128*2 space.
	 */
	for (i = 0; i < 99; i += 1, col += 2) {
		if (mag_in_buffer_int[i] > 0) {
			ili93xx_draw_line(col, 279, col, 279 - mag_in_buffer_int[i]);
		}
	}
}

/**
 * \brief Draw a bitmap image.
 * Expected file format is 320x240, 24 bits, RGB888.
 *
 * \param bmpImage Pointer to the bmp file image.
 */
static void gfx_draw_bmpfile(const uint8_t *bmpImage)
{
	struct bmpfile_header *bmp_header;
	uint32_t length;
	uint32_t i = 0;
	uint32_t offset;

	bmp_header = (struct bmpfile_header *) bmpImage;
	length = bmp_header->height * bmp_header->width * 3;
	offset = sizeof(struct bmpfile_header);

	if (ili93xx_device_type() == DEVICE_TYPE_ILI9325) {
		ili93xx_set_cursor_position(0, 0);

		/* Prepare to write in GRAM. */
		LCD_IR(0);
		LCD_IR(ILI9325_GRAM_DATA_REG);
		for (i = offset; i < length; i += 3) {
			/* Invert red and blue. */
			LCD_WD(bmpImage[i + 2]);
			LCD_WD(bmpImage[i + 1]);
			LCD_WD(bmpImage[i]);
		}
	}
	else if (ili93xx_device_type() == DEVICE_TYPE_ILI9341) {
		ili93xx_set_window(0, 0, bmp_header->width - 15, bmp_header->height);
		LCD_IR(ILI9341_CMD_MEMORY_WRITE); /* memory write command (R2Ch) */
		LCD_IR(ILI9341_CMD_WRITE_MEMORY_CONTINUE);

		/* The original image is mirrored. */
		for (i = bmp_header->height - 1 ; (i * bmp_header->width * 3) > offset ; i -= 1)
			for (uint16_t j = 45; j < (bmp_header->width * 3); j += 3) {
				LCD_WD(bmpImage[i * bmp_header->width * 3 + j + 2]);
				LCD_WD(bmpImage[i * bmp_header->width * 3 + j + 1]);
				LCD_WD(bmpImage[i * bmp_header->width * 3 + j]);
			}
	}
}
