/**
 * \file
 *
 * \brief SAM toolkit demo application.
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage SAM Toolkit Demo Application
 *
 * \section Purpose
 *
 * The SAM toolkit demo will help new users get familiar with Atmel's
 * SAM family of microcontrollers. This demo application shows the basic
 * usages of several SAM and 3rd party modules in the ASF.
 *
 * \section Requirements
 *
 * This package can be used with SAM4S-EK/SAM4S-EK2.
 *
 * \section Description
 *
 * This demo program presents the general features of the SAM-EK boards.
 * The basic features involved include FreeRTOS, QTouch, FatFS, Nandflash,
 * USB Mass Storage and LCD.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board.
 * -# Unzip the resource files in the resource directory, which is located at
 * ./sam/applications/sam_toolkit_demo/resources/disk.
 * -# Erase the nand flash through SAM-BA.
 * -# Power OFF and ON the board with the USB cable always connected.
 * -# A new Removable Disk should appear in the computer explorer.
 * -# Copy the resource files to the root directory of this removable disk.
 * -# When the copy operation is achieved, disconnect the USB cable, and
 * Power OFF and ON the board. The root directory in the removable disk should
 * be "/demo".
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear (values depend
 * on the board and chip used):
 *    \code
	-- SAM Toolkit Demo Example xxx --
	-- xxxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
\endcode
 * -# Pressing and release the icon buttons on the LCD. The corresponding window
 * will show and display the result.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "conf_board.h"
#include "demo.h"
#include <asf.h>
#include "bitmaps.h"
#include "task.h"
#include "string.h"
#include "rtouch_calibrate.h"
#include "demo_board.h"

/** USB task stack size  */
#define TASK_USB_STACK_SIZE                (3072 / sizeof(portSTACK_TYPE))
#define TASK_USB_STACK_PRIORITY            (configMAX_PRIORITIES - 2)

/** Window stack size  */
#define TASK_WIN_STACK_SIZE                (8192 / sizeof(portSTACK_TYPE))
#define TASK_WIN_STACK_PRIORITY            (configMAX_PRIORITIES - 2)

/** PPT player parameters */
#define SCR_PPT_SLIDE_DELAY_MIN     1
#define SCR_PPT_SLIDE_DELAY_MAX     20
#define SCR_PPT_SLIDE_MAX           2
#define SCR_PPT_SLIDE_PATH          "/demo/slideshow/"
#define SCR_PPT_SLIDE_FOLDER        "24bpp/"
#define SCR_PPT_SLIDE_BASENAME      "Slide"
#define SCR_PPT_SLIDE_EXT           ".bmp"

/** Total slider number supported */
#define TOTAL_SLIDER_NUM 2

#if	!defined(ADC_CHANNEL_POTENTIOMETER)
	#warning The potentiometer channel does not exist in the board definition file. Using default settings.

	#define ADC_CHANNEL_POTENTIOMETER  ADC_CHANNEL_5
#endif

#if SAM3S || SAM4S || SAM3XA || SAM3N
/* Tracking Time*/
#define  TRACKING_TIME            1
/* Transfer Period */
#define  TRANSFER_PERIOD       1 
#endif

#if SAM3U
#ifdef ADC_12B
/* Start Up Time */
#define   STARTUP_TIME                           7
/* Off Mode Startup Time */
#define   OFF_MODE_STARTUP_TIME      7
#else
#define   STARTUP_TIME                           3
#endif
/* Sample & Hold Time */
#define   SAMPLE_HOLD_TIME   6
#endif

/* A message is posted each time the values goes outside the [-5,+5] interval
 * around the previous measure */
#define NB_INTERVALS 5

/** Demo bitmap used for PPT player */
static struct gfx_bitmap demo_ppt = {
	.width = 240, .height = 320,
	.type = GFX_BITMAP_EXT,
};

/** Demo background bitmap */
static struct gfx_bitmap win_root_background = {
	.type = GFX_BITMAP_SOLID,
	.data.color = GFX_COLOR(255, 255, 255),
};

/** Demo startup bitmap */
static struct gfx_bitmap win_startup_bmp = {
	.width = 240, .height = 240,
	.type = GFX_BITMAP_EXT,
	.data.custom = DEMO_BMP_INTRO_SAM4S
};

/* Handle to the semaphore protecting memories transfer. */
static xSemaphoreHandle main_trans_semphr = NULL;

/** Tick Counter united by ms */
static volatile uint32_t g_ul_tick_count = 0;

/** Demo spcial mode; during these special mode, the GUI is not handled by
 * widget */
static uint8_t demo_spcial_mode[DEMO_SPEC_MODE_MAX];

/** The ppt player is existed by touch event */
static uint8_t touch_event_on_ppt = 0;

/** Demo current time */
static char demo_cur_time[20];

/** Demo current date */
static char demo_cur_date[20];

/** Slide index of PPT player */
static uint32_t ppt_silder_index;

/** PPT player clapse delay counter */
static volatile uint32_t ppt_delay_clapse_counter = 0;

/** Slide path */
static char ppt_slide_path[128];

/* Pontentiometer value */
static volatile uint32_t pontentiometer_value;

/** ADC on/off flag */
static volatile uint8_t demo_adc_on = 0;

/** FFT delay counter */
uint32_t fft_delay = 0;

/** FFT update flag */
bool fft_update = true;

/* Frame buffer to store the FFT data */
extern uint16_t frame_buffer[AUDIO_NB_BUFFER][AUDIO_FRAME_SIZE];

/* Number of ADC samples */
extern uint32_t adc_nb_samples;

/* ADC buffer index */
extern uint8_t adc_buf_ndx;

/** Flag set by timer ISR when it's time to measure touch */
extern uint8_t time_to_measure_touch;

/** Current time, set by timer ISR */
extern uint16_t current_time_ms_touch;

/** Timer period in msec */
extern uint16_t qt_measurement_period_msec;

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,
		signed char *pcTaskName);
extern void vApplicationIdleHook(void);
extern void vApplicationTickHook(void);

extern void xPortSysTickHandler(void);

/**
 * \brief Handler for Sytem Tick interrupt.
 */
void SysTick_Handler(void)
{
	static uint8_t update_delay = 0;

	/* Set flag: it's time to measure touch */
	time_to_measure_touch = 1u;

	/* Update the current time */
	current_time_ms_touch += qt_measurement_period_msec;

	g_ul_tick_count++;

	/* Call TSD_TimerHandler per 10ms */
	if ((g_ul_tick_count % 10) == 0) {
		rtouch_process();
	}

	if (fft_delay < SYSTICK_FREQ) {
		/* 1S */
		fft_delay++;
	}

	if (++update_delay == 20) {
		update_delay = 0;
		fft_update = true;
	}

	xPortSysTickHandler();
}

/**
 * \brief Handler for ADC interrupt.
 */
void ADC_Handler(void)
{
	uint32_t low_threshold;
	uint32_t high_threshold;
	uint32_t status = adc_get_status(ADC);

	/* Read the status to ack the IT */
	if ((status & ADC_ISR_COMPE) == ADC_ISR_COMPE) {
		/* Get the potentiometer initial value */
		pontentiometer_value = adc_get_channel_value( ADC,
				ADC_CHANNEL_POTENTIOMETER );

		/* Set Window threshold according to the initial values */
		low_threshold = pontentiometer_value -
				(NB_INTERVALS * (0x1000 / 256));
		if (low_threshold > 0xf0000000) {
			low_threshold = 0;
		}

		high_threshold = pontentiometer_value +
				(NB_INTERVALS * (0x1000 / 256));
		if (high_threshold >= 0x1000) {
			high_threshold = 0x1000 - 1;
		}

		/* Normalize the value 0 -> 255 */
		pontentiometer_value
			= pontentiometer_value*100 + 1;
		ppt_delay_clapse_counter = 0;

		/* Setup Threshold*/
		adc_set_comparison_window( ADC, low_threshold,
				high_threshold);

		/* Compare mode, in the window. */
		adc_enable_interrupt(ADC, ADC_IER_COMPE);
	}

	if (status & ADC_ISR_ENDRX) {
		/* Start next buffer */
		ADC->ADC_RNPR = (uint32_t)
				frame_buffer[(adc_buf_ndx + 2) % AUDIO_NB_BUFFER];
		ADC->ADC_RNCR = AUDIO_FRAME_SIZE;

		adc_buf_ndx = (adc_buf_ndx + 1) % AUDIO_NB_BUFFER;
		adc_nb_samples += AUDIO_FRAME_SIZE;
	}
}

/**
 * \brief Called if stack overflow during execution
 */
extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,
		signed char *pcTaskName)
{
	printf("stack overflow %x %s\r\n", pxTask, (portCHAR *)pcTaskName);

	/* If the parameters have been corrupted then inspect pxCurrentTCB to
	 * identify which task has overflowed its stack.
	 */
	for (;;) {
	}
}

/**
 * \brief This function is called by FreeRTOS idle task
 */
extern void vApplicationIdleHook(void)
{
}

/**
 * \brief This function is called by FreeRTOS each tick
 */
extern void vApplicationTickHook(void)
{
}

static void demo_start_adc(bool on);

/**
 * \brief Process USB tasks.
 */
static void task_usb(void *pvParameters)
{
	UNUSED(pvParameters);

	while (true) {
		/* Wait for a semaphore which signals that a transfer is
		 * requested */
		if (xSemaphoreTake( main_trans_semphr,
				portMAX_DELAY ) == pdTRUE) {
			udi_msc_process_trans();
		}
	}
}

/**
 * \brief This task, when activated, send every ten seconds on debug UART the
 * whole report of free heap and total tasks status
 */
static void task_win(void *pvParameters)
{
	uint32_t hour, minute, second;
	uint32_t year, month, date,week;

	uint8_t uc_result;

	UNUSED(pvParameters);

	for (;;) {
		while (demo_get_special_mode_status(DEMO_LCD_CALIBRATE_MODE)) {
			app_widget_settings_on(false);
			uc_result = rtouch_calibrate();
			if (uc_result == 0) {
				demo_set_special_mode_status(
						DEMO_LCD_CALIBRATE_MODE, 0);
				app_widget_settings_on(true);
				puts("Calibration successful !\r");
				break;
			} else {
				puts("Calibration failed; error delta is too big ! Please retry calibration procedure...\r");
			}
		}

		if (demo_get_special_mode_status(DEMO_WAIT_MODE) ||
				demo_get_special_mode_status(DEMO_SLEEP_MODE)) {
			app_widget_lpm_on(true);
			demo_set_special_mode_status(DEMO_WAIT_MODE, 0);
			demo_set_special_mode_status(DEMO_SLEEP_MODE, 0);
		}

		/* Play PPT */
		if (demo_get_special_mode_status(DEMO_PPT_MODE)) {
			demo_start_adc(true);
			if (pontentiometer_value == ppt_delay_clapse_counter) {
				snprintf( ppt_slide_path,
						sizeof(ppt_slide_path),
						"%s%s%s%u%s",
						SCR_PPT_SLIDE_PATH,
						SCR_PPT_SLIDE_FOLDER,
						SCR_PPT_SLIDE_BASENAME,
						ppt_silder_index,
						SCR_PPT_SLIDE_EXT );

				demo_ppt.data.custom = ppt_slide_path;

				gfx_draw_bitmap(&demo_ppt, 0, 0);
				ppt_delay_clapse_counter = 0;
				ppt_silder_index++;

				if (ppt_silder_index >= SCR_PPT_SLIDE_MAX) {
					ppt_silder_index = 0;
				}
			}

			ppt_delay_clapse_counter++;

			continue;
		}

		if (touch_event_on_ppt == 1) {
			app_widget_main_on(true);
			touch_event_on_ppt = 0;
		}

		demo_qtouch_event_handler();
		/* Process queued events in the windowing system */
		win_process_events();

		if (demo_get_special_mode_status(DEMO_MAIN_MODE)) {
			/* Retrieve date and time */
			rtc_get_time( RTC, &hour, &minute, &second );
			snprintf( demo_cur_time, sizeof(demo_cur_time),
					"%02u:%02u:%02u",
					hour, minute, second );
			/* Draw the time text */
			gfx_draw_string(demo_cur_time, 15, 300,
					&sysfont, COLOR_WHITE, COLOR_WHITE);
			gfx_draw_string(demo_cur_time, 15, 300,
					&sysfont, GFX_COLOR_TRANSPARENT,
					COLOR_BLUE);

			/* Retrieve date and time */
			rtc_get_date( RTC, &year, &month, &date, &week );
			snprintf( demo_cur_date, sizeof(demo_cur_date),
					"%04u/%02u/%02u",
					year, month, date );
			/* Draw the help text */
			gfx_draw_string(demo_cur_date, 135, 300,
					&sysfont, COLOR_WHITE, COLOR_WHITE);
			gfx_draw_string(demo_cur_date, 135, 300,
					&sysfont, GFX_COLOR_TRANSPARENT,
					COLOR_BLUE);
		}

		vTaskDelay(100);
	}
}


/**
 * \brief Configure Timer Counter 0 (TC0) to generate an interrupt every
 * second.
 */
static void demo_configure_tc0( void )
{
	/* Enable TC0 peripheral clock. */
	pmc_enable_periph_clk(ID_TC1);

	/* Configure TC for a 1s (= 1Hz) tick. */
	tc_init(TC0, 1, 0x4 | TC_CMR_ACPC_SET | TC_CMR_WAVE
			| TC_CMR_ACPA_CLEAR | TC_CMR_WAVSEL_UP_RC);

	/* 50% duty, 1s frequency */
	tc_write_ra(TC0, 1, 16384);
	tc_write_rc(TC0, 1, 32768);
}

/**
 * \brief Initialize ADC.
 */
static void demo_config_adc( void )
{
	/* Enable peripheral clock. */
	pmc_enable_periph_clk(ID_ADC);
	/* Initialize ADC. */
	/*
	 * Formula: ADCClock = MCK / ( (PRESCAL+1) * 2 )
	 * For example, MCK = 64MHZ, PRESCAL = 4, then:
	 * ADCClock = 64 / ((4+1) * 2) = 6.4MHz;
	 */
	/* Formula:
	 *     Startup  Time = startup value / ADCClock
	 *     Startup time = 64 / 6.4MHz = 10 us
	 */
	adc_init(ADC, sysclk_get_cpu_hz(), 6400000, ADC_STARTUP_TIME_4);
	/* Formula:
	 *     Transfer Time = (TRANSFER * 2 + 3) / ADCClock
	 *     Tracking Time = (TRACKTIM + 1) / ADCClock
	 *     Settling Time = settling value / ADCClock
	 *
	 *     Transfer Time = (1 * 2 + 3) / 6.4MHz = 781 ns
	 *     Tracking Time = (1 + 1) / 6.4MHz = 312 ns
	 *     Settling Time = 3 / 6.4MHz = 469 ns
	 */
	adc_configure_timing(ADC, TRACKING_TIME, ADC_SETTLING_TIME_3, TRANSFER_PERIOD);
	adc_check(ADC, sysclk_get_cpu_hz());

	/* Hardware trigger TIOA0. */
	adc_configure_trigger(ADC, ADC_TRIG_TIO_CH_1, 0);
	/* Enable channels for x,y and z. */
	adc_enable_channel(ADC, ADC_CHANNEL_POTENTIOMETER);

	/* Configure TC. */
	demo_configure_tc0();
}

/**
 * \brief Turn on/off ADC module.
 *
 * \param on True to start ADC, false to turn off.
 */
static void demo_start_adc(bool on)
{
	uint32_t low_threshold, high_threshold;

	if (on == true) {
		/* Check if already enabled */
		if (demo_adc_on) {
			return;
		}

		demo_config_adc();

		/* Start TC0 and hardware trigger. */
		tc_start(TC0, 1);

		/* Get the potentiometer initial value */
		pontentiometer_value = adc_get_channel_value(ADC,
				ADC_CHANNEL_POTENTIOMETER);

		/* Set Window threshold according to the initial values */
		low_threshold  = pontentiometer_value -
				(NB_INTERVALS * (0x1000 / 256));
		if (low_threshold > 0xf000000) {
			low_threshold = 0;
		}

		high_threshold = pontentiometer_value +
				(NB_INTERVALS * (0x1000 / 256));
		if (high_threshold >= 0x1000) {
			high_threshold = 0x1000 - 1;
		}

		pontentiometer_value
			= pontentiometer_value*100 + 1;

		/* Channel 5 has to be compared. */
		adc_set_comparison_channel(ADC, ADC_CHANNEL_POTENTIOMETER);
		/* Compare mode, out the window. */
		adc_set_comparison_mode(ADC, ADC_EMR_CMPMODE_OUT);

		/* Set up Threshold. */
		adc_set_comparison_window(ADC, low_threshold,
				high_threshold);

		/* Enable ADC interrupt. */
		NVIC_EnableIRQ(ADC_IRQn);

		/* Enable Compare Interrupt. */
		adc_enable_interrupt(ADC, ADC_IER_COMPE);

		/* Set adc on flag */
		demo_adc_on = 1;

		/* Reset clapse time */
		ppt_delay_clapse_counter = 0;
	} else {
		tc_stop(TC0, 1);
		/* Enable ADC interrupt. */
		NVIC_DisableIRQ(ADC_IRQn);
		/* Enable Compare Interrupt. */
		adc_disable_interrupt(ADC, ADC_IDR_COMPE);
		/* Set adc off flag */
		demo_adc_on = 0;
	}
}

/**
 * \brief USB VBUS actions.
 */
static void main_vbus_action(bool b_high)
{
	if (b_high) {
		/* Attach USB Device */
		udc_attach();
	} else {
		/* VBUS not present */
		udc_detach();
	}
}

/**
 * \brief Configure the console UART.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);

	/* Specify that stdout should not be buffered. */
#if defined(__GNUC__)
	setbuf(stdout, NULL);
#else

	/* Already the case in IAR's Normal DLIB default configuration: printf()
	 * emits one character at a time.
	 */
#endif
}

/**
 * \brief Configure the root GUI window.
 *
 * Configures the root window background to blank white.
 */
static void setup_gui_root_window(void)
{
	struct win_attributes root_attr;
	struct win_window *win_root;

	win_root = win_get_root();
	root_attr = *win_get_attributes(win_root);
	root_attr.background = &win_root_background;
	win_set_attributes(win_root, &root_attr, WIN_ATTR_BACKGROUND);

	win_show(win_root);
}


/*
 * \brief Callback called when the pen is pressed on the touchscreen.
 *
 * \param event Pointer to the touch event.
 */
static void event_handler(rtouch_event_t const *event)
{
	struct win_pointer_event win_touch_event;

	switch (event->type) {
	case RTOUCH_MOVE:
		win_touch_event.type = WIN_POINTER_MOVE;
		break;

	case RTOUCH_PRESS:
		win_touch_event.type = WIN_POINTER_PRESS;
		break;

	case RTOUCH_RELEASE:
		win_touch_event.type = WIN_POINTER_RELEASE;

		/* If in PPT mode, clear the PPT mode and set the
		  * touch_event_on_ppt flag to exist ppt mode in win task.*/
		if (demo_get_special_mode_status(DEMO_PPT_MODE)) {
			demo_set_special_mode_status(DEMO_PPT_MODE, 0);
			demo_start_adc(false);
			touch_event_on_ppt = 1;
			return;
		}

		/* If in FFT mode, clear the FFT mode flag to back to main. */
		if (demo_get_special_mode_status(DEMO_FFT_MODE)) {
			demo_set_special_mode_status(DEMO_FFT_MODE, 0);

			/* Return directly */
			return;
		}

		break;

	default:
		/* None pointer event received, exist evnet handler. */
		return;
	}

	/* Queue the touch move, press or release event to wtk service. */
	win_touch_event.is_relative = false;
	win_touch_event.buttons = WIN_TOUCH_BUTTON;

	/* Translate the touch X and Y position into a screen coordinate */
	win_touch_event.pos.x
		= (uint32_t)event->panel.x;
	win_touch_event.pos.y
		= (uint32_t)event->panel.y;
	win_queue_pointer_event(&win_touch_event);
}

/** \brief Main function. Execution starts here.
 */
int main(void)
{
	uint8_t uc_result;

	/* Initialize the sleep manager */
	sleepmgr_init();
	membag_init();
	sysclk_init();
	init_specific_board();

	/* Initialize the console uart */
	configure_console();

	/* Output demo infomation. */
	printf("-- SAM Toolkit Demo Example --\n\r");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	/* Configure systick for 1 ms. */
	puts("Configure system tick to get 1ms tick period.\r");
	if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
		puts("Systick configuration error\r");
		while (1) {
		}
	}

	/* Initialize gfx module */
	gfx_init();
	win_init();

	/* Initialize FatFS and bitmap draw interface */
	demo_draw_bmpfile_init();

	/* Initialize touchscreen without calibration */
	rtouch_init(LCD_WIDTH, LCD_HEIGHT);
	rtouch_enable();
	rtouch_set_event_handler(event_handler);

	/* Initialize demo parameters */
	demo_parameters_initialize();
	while (g_demo_parameters.calib_points[0].raw.x == 0) {
		uc_result = rtouch_calibrate();
		if (uc_result == 0) {
			demo_set_special_mode_status(DEMO_LCD_CALIBRATE_MODE, 0);
			puts("Calibration successful !\r");
			break;
		} else {
			puts("Calibration failed; error delta is too big ! Please retry calibration procedure...\r");
		}
	}

	/* Re-caculate the calibration data */
	rtouch_compute_calibration(
			(rtouch_calibration_point_t *)&g_demo_parameters.calib_points[0]);

	/* Setup root window */
	setup_gui_root_window();
	gfx_draw_bitmap(&win_startup_bmp, 0, 40);

	/* Set backlight by the data read from demo parameters */
	aat31xx_set_backlight(g_demo_parameters.backlight);

	/* Default RTC configuration, 24-hour mode */
	rtc_set_hour_mode(RTC, 0);
	rtc_set_time(RTC, g_demo_parameters.hour, g_demo_parameters.minute,
			g_demo_parameters.second);
	rtc_set_date( RTC, g_demo_parameters.year, g_demo_parameters.month,
			g_demo_parameters.day, 1 );

	/* Create a semaphore to manage the memories data transfer */
	vSemaphoreCreateBinary(main_trans_semphr);

	/* Turn on main widget */
	app_widget_main_on(true);

	/* Initialize QTouch */
	demo_qt_init();

	/* Start USB stack to authorize VBus monitoring */
	udc_start();
	if (!udc_include_vbus_monitoring()) {
		/* VBUS monitoring is not available on this product
		 * thereby VBUS has to be considered as present */
		main_vbus_action(true);
	}

	/* Create task to window task */
	if (xTaskCreate(task_win, "WIN", TASK_WIN_STACK_SIZE, NULL,
			TASK_WIN_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed to create test led task\r\n");
	}

	/* Create task to usb mass storage task */
	if (xTaskCreate(task_usb, "USB", TASK_USB_STACK_SIZE, NULL,
			TASK_USB_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed to create test led task\r\n");
	}

	/* Start the scheduler. */
	vTaskStartScheduler();

	/* Will only get here if there was insufficient memory to create the
	 * idle task. */
	return 0;
}

/**
 * \brief Set special mode status.
 *
 * \param id Special mode ID.
 * \param status special mode status.
 */
void demo_set_special_mode_status( demo_special_mode_id id, uint8_t status )
{
	demo_spcial_mode[id] = status;
}

/**
 * \brief Get if the specific window is active.
 *
 * \param id Special mode ID.
 *
 * \return Special mode status.
 */
uint8_t demo_get_special_mode_status( demo_special_mode_id id )
{
	return demo_spcial_mode[id];
}

/**
 * \brief Notify USB transfer.
 */
void main_msc_notify_trans(void)
{
	static signed portBASE_TYPE higher_prior_task_woken;
	higher_prior_task_woken = pdFALSE;
	/* One transfer is requested */
	/* It is now time for main_memories_trans_task() to run */
	xSemaphoreGiveFromISR( main_trans_semphr, &higher_prior_task_woken );
}

/**
 * \brief USB mass storage enable.
 */
bool main_msc_enable(void)
{
	return true;
}

/**
 * \brief USB mass storage disable.
 */
void main_msc_disable(void)
{
	/* Doing nothing here, compatiable with USB driver */
}

