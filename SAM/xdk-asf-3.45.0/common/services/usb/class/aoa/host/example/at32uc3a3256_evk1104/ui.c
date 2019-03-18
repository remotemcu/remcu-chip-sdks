/**
 * \file
 *
 * \brief User Interface
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

#include <asf.h>
#include "conf_qt60168.h"
#include <qt60168.h>
#include <et024006dhu.h>
#include "ui.h"
#include "usb_connector.h"
#include "cellphone.h"

/* Global Variables */

/** Stores if a button needs to be updated */
volatile uint8_t ui_button_state_changed;

/** Stores the state of the buttons */
volatile bool ui_button_state[5];

/** Stores the last message from/to the Android device */
COMPILER_WORD_ALIGNED
uint8_t ui_msg[512];

/** Indicates the status of a read from the Android device */
uint8_t read_complete_flag;

/* Notify the presence of a USB Android device */
static bool ui_aoa_plug = false;

/** Read ongoing */
#define AOA_READ_ONGOING    0x00
/** Read completed successfully */
#define AOA_READ_SUCCESS    0x01
/** Read timed out */
#define AOA_READ_TIMEOUT    0x02
/** Read Error */
#define AOA_READ_ERROR      0x03

/** Defines for Display */
#define DISPLAY_MAX_LINES        12
#define DISPLAY_FIRST_LINE_X     12
#define DISPLAY_FIRST_LINE_Y     22

/** IRQ line of RTC module is used. */
#define DISPLAY_RTC_IRQ            AVR32_RTC_IRQ
/** IRQ group for RTC */
#define DISPLAY_RTC_IRQ_GROUP      AVR32_RTC_IRQ_GROUP
/** Interrupt priority 1 is used for RTC in this example. */
#define DISPLAY_RTC_IRQ_PRIORITY   1

/** IRQ line of RTC module is used. */
#define BUTTON_RTC_IRQ             AVR32_RTC_IRQ
/** IRQ group for RTC */
#define BUTTON_RTC_IRQ_GROUP       AVR32_RTC_IRQ_GROUP
/** Interrupt priority 1 is used for RTC in this example. */
#define BUTTON_RTC_IRQ_PRIORITY    1

/*! \name Buttons
 * @{
 */
#define BUTTON_ONE   0x01
#define BUTTON_TWO   0x02
#define BUTTON_THREE 0x03
#define BUTTON_FOUR  0x04
/* @} */

/*! \brief Initializes and enables Display
 *
 */
static void ui_display_enable(void);

/*! \brief Displays Start Message called when there's no Device plugged in
 *
 */
static void ui_display_welcome_msg(void);

/*! \brief Creates help animation to plug in the device
 *
 */
void ui_display_draw_dot(void);

/*! \brief Initializes the RTC used to display the help message
 *
 */
static void ui_display_init_rtc(void);

/*! \brief Disables the RTC used to display the help message
 *
 */
static void ui_display_disable_rtc(void);

/*! \brief Draws an empty textbox
 *
 */
static void ui_display_draw_textbox(void);

/*! \brief Clears the rectangle in which messages from the Android device
 *     will be displayed
 */
static void ui_display_clr_screen(void);

/*! \brief Initializes the specified LED
 *  \param lednum
 */
void ui_pwm_led_init(uint8_t lednum);

/*! \brief updates the specified LED
 *  \param channum Number of the PWM Channel
 *  \param brightness 0 to 255
 */
void ui_pwm_update(uint8_t channum, uint8_t brightness);

/*! \brief Initializes and enables buttons
 *
 */
static void ui_buttons_enable(void);

/*! \brief Reads all buttons from the external Touch chip
 *
 */
void ui_buttons_read(void);

/*! \brief Initializes and enables Timer for Buttons
 *
 */
static void ui_button_rtc_init(void);

/*! \brief Initializes and enables the adc
 *
 */
static void ui_adc_init(void);

/*! \brief Reads the value from the light sensor
 *
 */
void ui_adc_read(void);

/**
 * \name Main user interface functions
 * @{
 */
void ui_init(void)
{
	LED_Off(LED2);
	LED_Off(LED3);

	ui_pwm_led_init(LED0);
	ui_pwm_led_init(LED1);

	ui_display_enable();

	ui_buttons_enable();

	ui_adc_init();

	read_complete_flag = AOA_READ_TIMEOUT;
}

void ui_usb_mode_change(bool b_host_mode)
{
	if (b_host_mode) {
		LED_On(LED3);
	} else {
		LED_Off(LED3);
	}
}

/** @} */

/**
 * \name Host mode user interface functions
 * @{
 */

/** Status of device enumeration */
static uhc_enum_status_t ui_enum_status = UHC_ENUM_DISCONNECT;

void ui_usb_vbus_change(bool b_vbus_present)
{
	(void)b_vbus_present;
}

void ui_usb_vbus_error(void)
{
}

void ui_usb_connection_event(uhc_device_t *dev, bool b_present)
{
	if (b_present == false) {
		ui_enum_status = UHC_ENUM_DISCONNECT;
		uhi_aoa_uninstall(dev);
		ui_display_init_rtc();
		ui_display_welcome_msg();
	}
}

void ui_usb_enum_event(uhc_device_t *dev, uhc_enum_status_t status)
{
	(void)dev;
	ui_enum_status = status;

	et024006_DrawFilledRect(0, 0, ET024006_WIDTH, ET024006_HEIGHT, BLACK );

	if (ui_enum_status != UHC_ENUM_SUCCESS) {
		/* Draw device incompatible */
		et024006_PrintString((char *)"This Device is not compatible!",
				(const uint8_t *)&FONT8x16, 30, 125, BLUE,
				WHITE);
	} else {
		ui_display_draw_textbox();
	}

	ui_display_disable_rtc();
	ui_button_rtc_init();
}

void ui_uhi_aoa_change(uhc_device_t * dev, bool b_plug)
{
	ui_aoa_plug = b_plug;
}

void ui_usb_wakeup_event(void)
{
}

void ui_usb_sof_event(void)
{
	static uint16_t counter_sof = 0;

	if (ui_enum_status == UHC_ENUM_SUCCESS) {
		/* Display device enumerated and in active mode */
		if (++counter_sof > 2000) {
			counter_sof = 0;
		}

		if (counter_sof % 1000 == 0) {
			ui_adc_read();
		}

		if (read_complete_flag != AOA_READ_ONGOING) {
			if (read_complete_flag == AOA_READ_SUCCESS) {
				ui_usb_message_reception();
			}

			read_complete_flag = AOA_READ_ONGOING;
			uhi_aoa_read(ui_msg, sizeof(ui_msg), read_complete);
		}

		/* Buttons */
		if (ui_button_state_changed) {
			ui_button_state[ui_button_state_changed - 1] =
				!ui_button_state[ui_button_state_changed - 1];
			ui_msg[0] = MESSAGE_ATD_SIMPLE_SWITCH;
			ui_msg[1] = ui_button_state_changed - 1;
			ui_msg[2] = 
				ui_button_state[ui_button_state_changed - 1];
			uhi_aoa_write(ui_msg, 3, NULL);
			ui_button_state_changed = 0x00;
		}
	}
}

/* End of Hostmode functions */
/** @} */
void read_complete(usb_add_t add, usb_ep_t ep, uhd_trans_status_t status,
		iram_size_t nb_transfered)
{
	(void)add;
	(void)nb_transfered;
	switch (status) {
	case UHD_TRANS_NOERROR:
		read_complete_flag = AOA_READ_SUCCESS;
		break;

	case UHD_TRANS_TIMEOUT:
		read_complete_flag = AOA_READ_TIMEOUT;
		break;

	case UHD_TRANS_DISCONNECT:
		read_complete_flag = AOA_READ_ERROR;
		break;

	case UHD_TRANS_CRC:
		read_complete_flag = AOA_READ_ERROR;
		break;

	case UHD_TRANS_DT_MISMATCH:
		read_complete_flag = AOA_READ_ERROR;
		break;

	case UHD_TRANS_STALL:
		read_complete_flag = AOA_READ_ERROR;
		break;

	case UHD_TRANS_NOTRESPONDING:
		read_complete_flag = AOA_READ_ERROR;
		break;

	case UHD_TRANS_PIDFAILURE:
		read_complete_flag = AOA_READ_ERROR;
		break;

	case UHD_TRANS_ABORTED:
		read_complete_flag = AOA_READ_ERROR;
		break;

	default:
		read_complete_flag = AOA_READ_ERROR;
		break;
	}
}

void ui_usb_message_reception(void)
{
	static uint8_t rowcounter = 0;
	uint8_t rows_in_message = 0;
	uint8_t i;

	switch (ui_msg[0]) {
	case MESSAGE_DTA_SIMPLE_LED:
		switch (ui_msg[1]) {
		case 0x00:
			ui_pwm_update(LED0, ui_msg[2]);
			break;

		case 0x01:
			ui_pwm_update(LED1, ui_msg[2]);
			break;

		case 0x02:
			if (ui_msg[2] > 0) {
				LED_On(LED2);
			} else {
				LED_Off(LED2);
			}

			break;

		default:
			break;
		}
		break;

	case MESSAGE_DTA_SIMPLE_DISPLAY_BACKLIGHT:
		switch (ui_msg[1]) {
		case 0x01:
		/* Not supported on this Board */

		default:
			break;
		}

	case MESSAGE_DTA_STRING_BASIC:
		if (ui_msg[2] > 37) {
			/* Truncate everything longer than 37 characters
			 * (command is 3 bytes long) */
			ui_msg[40] = '\0';
		} else {
			ui_msg[ui_msg[2] + 3] = '\0';
		}

		rows_in_message++;
		rowcounter++;
		for (i = 3; i < ui_msg[2] + 3; i++) {
			if (ui_msg[i] == '\n') {
				rows_in_message++;
				rowcounter++;
			}

			if (rowcounter >= DISPLAY_MAX_LINES) {
				i = 3;
				rowcounter = 1;
				rows_in_message = 1;
				ui_display_clr_screen();
			}
		}
		et024006_PrintString((char *)(&(ui_msg[3])),
				(const uint8_t*)&FONT8x16, DISPLAY_FIRST_LINE_X,
				DISPLAY_FIRST_LINE_Y+
				(rowcounter-rows_in_message)*17, BLUE, -1);

		break;

	default:
		break;
	}
}

/**
 * \name PWM functions
 * @{
 */
void ui_pwm_led_init(uint8_t lednum)
{
	/* Timer waveform options */
	static tc_waveform_opt_t waveform_options = {
		/* Channel selection. */
		.channel  = 1,

		.bswtrg   = TC_EVT_EFFECT_NOOP,
		.beevt    = TC_EVT_EFFECT_NOOP,
		.bcpc     = TC_EVT_EFFECT_NOOP,
		.bcpb     = TC_EVT_EFFECT_NOOP,

		.aswtrg   = TC_EVT_EFFECT_NOOP,
		.aeevt    = TC_EVT_EFFECT_NOOP,
		.acpc     = TC_EVT_EFFECT_NOOP,
		.acpa     = TC_EVT_EFFECT_NOOP,

		/* Waveform selection */
		.wavsel   = TC_WAVEFORM_SEL_UP_MODE_RC_TRIGGER,
		/* External event trigger enable. */
		.enetrg   = false,
		/* External event selection (non-zero for Channel B to work) */
		.eevt     = !0,
		/* External event edge selection. */
		.eevtedg  = TC_SEL_NO_EDGE,

		.cpcdis   = false,
		.cpcstop  = false,

		.burst    = false,
		.clki     = false,
		/* Internal source clock 5, fPBA/128. */
		.tcclks   = TC_CLOCK_SOURCE_TC5,
	};
	switch (lednum) {
	case LED0:
		/* Assign output pin to timer/counter 0 channel A */

		/* Channel selection. */
		waveform_options.channel = 1;

		waveform_options.bcpc = TC_EVT_EFFECT_NOOP;

		waveform_options.bcpb = TC_EVT_EFFECT_NOOP;
		/* RC compare effect on TIOA. */
		waveform_options.acpc = TC_EVT_EFFECT_CLEAR;
		/* RA compare effect on TIOA. */
		waveform_options.acpa = TC_EVT_EFFECT_SET;

		/* Setup timer/counter waveform mode */
		sysclk_enable_peripheral_clock(&AVR32_TC0);
		tc_init_waveform(&AVR32_TC0, &waveform_options);

		/* Write the TOP (RC) and COMPARE (RA) values */
		tc_write_ra(&AVR32_TC0, 1, 1);   /* Set RA value. */
		tc_write_rc(&AVR32_TC0, 1, 255); /* Set RC value. */

		/* Start the timer PWM channel */
		tc_start(&AVR32_TC0, 1);
		break;

	case LED1:
		/* Assign output pin to timer/counter 1 channel B */

		/* Channel selection. */
		waveform_options.channel = 2;

		waveform_options.acpc = TC_EVT_EFFECT_NOOP;

		waveform_options.acpa = TC_EVT_EFFECT_NOOP;
		/* RC compare effect on TIOB. */
		waveform_options.bcpc = TC_EVT_EFFECT_CLEAR;
		/* RB compare effect on TIOB. */
		waveform_options.bcpb = TC_EVT_EFFECT_SET;

		/* Setup timer/counter waveform mode */
		sysclk_enable_peripheral_clock(&AVR32_TC1);
		tc_init_waveform(&AVR32_TC1, &waveform_options);

		/* Write the TOP (RC) and COMPARE (RB) values */
		tc_write_rb(&AVR32_TC1, 2, 1);   /* Set RB value. */
		tc_write_rc(&AVR32_TC1, 2, 255); /* Set RC value. */

		/* Start the timer PWM channel */
		tc_start(&AVR32_TC1, 2);
		break;

	default:
		break;
	}
}

void ui_pwm_update(uint8_t channum, uint8_t brightness)
{
	switch (channum) {
	case LED0:
		if (brightness != 0) {
			gpio_enable_module_pin(AVR32_TC0_A1_0_1_PIN,
					AVR32_TC0_A1_0_1_FUNCTION);
			tc_start(&AVR32_TC0, 1);
			tc_write_ra(&AVR32_TC0, 1, brightness);
		} else {
			tc_stop(&AVR32_TC0, 1);
			LED_Off(LED0);
		}

		break;

	case LED1:
		if (brightness != 0) {
			gpio_enable_module_pin(AVR32_TC1_B2_0_PIN,
					AVR32_TC1_B2_0_FUNCTION);
			tc_start(&AVR32_TC1, 2);
			tc_write_rb(&AVR32_TC1, 2, brightness);
		} else {
			tc_stop(&AVR32_TC1, 2);
			LED_Off(LED0);
		}

		break;

	default:
		break;
	}
}

/* End of PWM */
/** @} */

/**
 * \name Display functions
 * @{
 */

static void ui_display_enable(void)
{
	delay_init(sysclk_get_cpu_hz());

	et024006_Init( sysclk_get_cpu_hz(), sysclk_get_hsb_hz());

	/* Clear the display i.e. make it black */
	et024006_DrawFilledRect(0, 0, ET024006_WIDTH, ET024006_HEIGHT, BLACK );

	/* Set the backlight. */
	gpio_set_gpio_pin(ET024006DHU_BL_PIN);

	ui_display_init_rtc();

	ui_display_welcome_msg();
}

static void ui_display_draw_textbox(void)
{
	/* Clear the display i.e. make it black */
	et024006_DrawFilledRect(0, 0, ET024006_WIDTH, ET024006_HEIGHT, BLACK );
	/* Draw blue Rectangle */
	et024006_DrawHorizLine(DISPLAY_FIRST_LINE_X - 2,
			DISPLAY_FIRST_LINE_Y - 2, ET024006_WIDTH - 20, BLUE);
	et024006_DrawVertLine(DISPLAY_FIRST_LINE_X - 2,
			DISPLAY_FIRST_LINE_Y - 2, ET024006_HEIGHT - 30, BLUE);
	et024006_DrawHorizLine(DISPLAY_FIRST_LINE_X - 2, ET024006_HEIGHT - 10,
			ET024006_WIDTH - 20, BLUE);
	et024006_DrawVertLine(ET024006_WIDTH - 10, DISPLAY_FIRST_LINE_Y - 2,
			ET024006_HEIGHT - 30, BLUE);
	/* Draw Welcome String */
	et024006_PrintString((char *)"Atmel Android Accessory Demo",
			(const uint8_t *)&FONT8x16, 12, 2, BLUE, WHITE);
}

static void ui_display_welcome_msg(void)
{
	/* Clear Display */
	et024006_DrawFilledRect(0, 0, ET024006_WIDTH, ET024006_HEIGHT, WHITE);
	/* Picture of Cellphone */
	et024006_PutPixmap(pic_cellphone, 80, 0, 0, 0, 0, 80, 99);
	/* Picture of USB Part */
	et024006_PutPixmap(pic_usb_connector, 160, 0, 0, 160, 120, 160, 120);
	/* Draw Welcome String */
	et024006_PrintString((char *)"Atmel Android",
			(const uint8_t *)&FONT8x16, 180, 30, BLUE, WHITE);
	et024006_PrintString((char *)"Accessory Demo",
			(const uint8_t *)&FONT8x16, 180, 50, BLUE, WHITE);
	/* Draw Plugin Android */
	et024006_PrintString((char *)"Please connect",
			(const uint8_t *)&FONT8x16, 20, 170, BLUE, WHITE);
	et024006_PrintString((char *)"an Android Device",
			(const uint8_t *)&FONT8x16, 20, 190, BLUE, WHITE);
}

void ui_display_draw_dot(void)
{
	static uint8_t dotnumber;

	switch (dotnumber) {
	case 0x00:
		et024006_DrawFilledRect(40, 105, 10, 10, BLACK);
		dotnumber++;
		break;

	case 0x01:
		et024006_DrawFilledRect(40, 125, 10, 10, BLACK);
		dotnumber++;
		break;

	case 0x02:
		et024006_DrawFilledRect(50, 145, 10, 10, BLACK);
		dotnumber++;
		break;

	case 0x03:
		et024006_DrawFilledRect(70, 145, 10, 10, BLACK);
		dotnumber++;
		break;

	case 0x04:
		et024006_DrawFilledRect(90, 125, 10, 10, BLACK);
		dotnumber++;
		break;

	case 0x05:
		et024006_DrawFilledRect(110, 105, 10, 10, BLACK);
		dotnumber++;
		break;

	case 0x06:
		et024006_DrawFilledRect(130, 95, 10, 10, BLACK);
		dotnumber++;
		break;

	case 0x07:
		et024006_DrawFilledRect(150, 95, 10, 10, BLACK);
		dotnumber++;
		break;

	case 0x08:
		et024006_DrawFilledRect(170, 95, 10, 10, BLACK);
		dotnumber++;
		break;

	case 0x09:
		et024006_DrawFilledRect(190, 95, 10, 10, BLACK);
		dotnumber++;
		break;

	case 0x0A:
		et024006_DrawFilledRect(195, 110, 10, 10, BLACK);
		dotnumber++;
		break;

	case 0x0B:
		et024006_DrawFilledRect(40, 105, 10, 10, WHITE);
		et024006_DrawFilledRect(40, 125, 10, 10, WHITE);
		et024006_DrawFilledRect(50, 145, 10, 10, WHITE);
		et024006_DrawFilledRect(70, 145, 10, 10, WHITE);
		et024006_DrawFilledRect(90, 125, 10, 10, WHITE);
		et024006_DrawFilledRect(110, 105, 10, 10, WHITE);
		et024006_DrawFilledRect(130, 95, 10, 10, WHITE);
		et024006_DrawFilledRect(150, 95, 10, 10, WHITE);
		et024006_DrawFilledRect(170, 95, 10, 10, WHITE);
		et024006_DrawFilledRect(190, 95, 10, 10, WHITE);
		et024006_DrawFilledRect(195, 110, 10, 10, WHITE);
		dotnumber = 0x00;
		break;

	default:
		break;
	}
}

ISR(display_rtc_irq, DISPLAY_RTC_IRQ_GROUP, DISPLAY_RTC_IRQ_PRIORITY)
{
	ui_display_draw_dot();

	/* clear the interrupt flag */
	rtc_clear_interrupt(&AVR32_RTC);
}

static void ui_display_init_rtc(void)
{
	irq_register_handler(display_rtc_irq, DISPLAY_RTC_IRQ,
			DISPLAY_RTC_IRQ_PRIORITY);

	rtc_init(&AVR32_RTC, RTC_OSC_32KHZ, RTC_PSEL_32KHZ_1HZ - 1);

	rtc_enable_wake_up(&AVR32_RTC);

	rtc_set_top_value(&AVR32_RTC, 0);

	rtc_enable_interrupt(&AVR32_RTC);

	rtc_enable(&AVR32_RTC);
}

static void ui_display_disable_rtc(void)
{
	rtc_disable_interrupt(&AVR32_RTC);

	rtc_disable(&AVR32_RTC);
}

static void ui_display_clr_screen(void)
{
	et024006_DrawFilledRect(DISPLAY_FIRST_LINE_X - 1,
			DISPLAY_FIRST_LINE_Y - 1, ET024006_WIDTH - 22,
			ET024006_HEIGHT - 32, BLACK );
}

/* End of Display */
/* @} */

/**
 * \name Button defines and functions
 * @{
 */
void ui_buttons_read()
{
	static uint8_t rr = 0;
	static uint8_t button_is_pressed;

	switch (rr) {
	case 0x00:
		if (qt60168_is_key_pressed(QT60168_TOUCH_SENSOR_BUTTON_0)) {
			if (!(button_is_pressed & (1 << BUTTON_ONE))) {
				ui_button_state_changed = BUTTON_ONE;
				button_is_pressed |= (1 << BUTTON_ONE);
			}
		} else {
			button_is_pressed &= ~(1 << BUTTON_ONE);
		}

		rr++;
		break;

	case 0x01:
		if (qt60168_is_key_pressed(QT60168_TOUCH_SENSOR_BUTTON_1)) {
			if (!(button_is_pressed & (1 << BUTTON_TWO))) {
				ui_button_state_changed = BUTTON_TWO;
				button_is_pressed |= (1 << BUTTON_TWO);
			}
		} else {
			button_is_pressed &= ~(1 << BUTTON_TWO);
		}

		rr++;
		break;

	case 0x02:
		if (qt60168_is_key_pressed(QT60168_TOUCH_SENSOR_BUTTON_2)) {
			if (!(button_is_pressed & (1 << BUTTON_THREE))) {
				ui_button_state_changed = BUTTON_THREE;
				button_is_pressed |= (1 << BUTTON_THREE);
			}
		} else {
			button_is_pressed &= ~(1 << BUTTON_THREE);
		}

		rr++;
		break;

	case 0x03:
		if (qt60168_is_key_pressed(QT60168_TOUCH_SENSOR_BUTTON_3)) {
			if (!(button_is_pressed & (1 << BUTTON_FOUR))) {
				ui_button_state_changed = BUTTON_FOUR;
				button_is_pressed |= (1 << BUTTON_FOUR);
			}
		} else {
			button_is_pressed &= ~(1 << BUTTON_FOUR);
		}

		rr = 0x00;
		break;

	default:
		break;
	}
}

/*! \brief Initializes QT60168 resources: GPIO and SPI
 */
static void ui_buttons_enable(void)
{
	static const gpio_map_t QT60168_SPI_GPIO_MAP = {
		{QT60168_SPI_SCK_PIN, QT60168_SPI_SCK_FUNCTION},
		{QT60168_SPI_MISO_PIN, QT60168_SPI_MISO_FUNCTION},
		{QT60168_SPI_MOSI_PIN, QT60168_SPI_MOSI_FUNCTION},
		{QT60168_SPI_NPCS0_PIN, QT60168_SPI_NPCS0_FUNCTION}
	};

	/* SPI options. */
	spi_options_t spiOptions = {
		.reg          = QT60168_SPI_NCPS,
		.baudrate     = QT60168_SPI_MASTER_SPEED,
		.bits         = QT60168_SPI_BITS,
		.spck_delay   = 0,
		.trans_delay  = 0,
		.stay_act     = 0,
		.spi_mode     = 3,
		.modfdis      = 1
	};

	/* Assign I/Os to SPI. */
	gpio_enable_module(QT60168_SPI_GPIO_MAP,
			sizeof(QT60168_SPI_GPIO_MAP) /
			sizeof(QT60168_SPI_GPIO_MAP[0]));

	/* Initialize as master */
	spi_initMaster(QT60168_SPI, &spiOptions);

	/* Set selection mode: variable_ps, pcs_decode, delay */
	spi_selectionMode(QT60168_SPI, 0, 0, 0);

	/* Enable SPI */
	spi_enable(QT60168_SPI);

	/* Initialize QT60168 with SPI clock Osc0. */
	spi_setupChipReg(QT60168_SPI, &spiOptions, sysclk_get_cpu_hz());

	qt60168_init(sysclk_get_cpu_hz());
}

ISR(button_rtc_irq, BUTTON_RTC_IRQ_GROUP, BUTTON_RTC_IRQ_PRIORITY)
{
	ui_buttons_read();

	/* clear the interrupt flag */
	rtc_clear_interrupt(&AVR32_RTC);
}

static void ui_button_rtc_init(void)
{
	irq_register_handler(button_rtc_irq, BUTTON_RTC_IRQ,
			BUTTON_RTC_IRQ_PRIORITY);

	rtc_init(&AVR32_RTC, RTC_OSC_32KHZ, 7);

	rtc_set_top_value(&AVR32_RTC, 0);

	rtc_enable_interrupt(&AVR32_RTC);

	rtc_enable(&AVR32_RTC);
}

/* End of Buttons */
/* @} */

/*! \name ADC channels function
 * @{
 */
#if BOARD == EVK1100
/* Connection of the temperature sensor */
#  define EXAMPLE_ADC_TEMPERATURE_CHANNEL     0
#  define EXAMPLE_ADC_TEMPERATURE_PIN         AVR32_ADC_AD_0_PIN
#  define EXAMPLE_ADC_TEMPERATURE_FUNCTION    AVR32_ADC_AD_0_FUNCTION
/* Connection of the light sensor */
#  define EXAMPLE_ADC_LIGHT_CHANNEL           2
#  define EXAMPLE_ADC_LIGHT_PIN               AVR32_ADC_AD_2_PIN
#  define EXAMPLE_ADC_LIGHT_FUNCTION          AVR32_ADC_AD_2_FUNCTION
/* Connection of the potentiometer */
#  define EXAMPLE_ADC_POTENTIOMETER_CHANNEL   1
#  define EXAMPLE_ADC_POTENTIOMETER_PIN       AVR32_ADC_AD_1_PIN
#  define EXAMPLE_ADC_POTENTIOMETER_FUNCTION  AVR32_ADC_AD_1_FUNCTION

/* Note: Corresponding defines are defined in /BOARDS/EVK1100/evk1100.h.
 * These are here for educational purposes only. */
#elif BOARD == EVK1101
/* Connection of the temperature sensor */
#  define EXAMPLE_ADC_TEMPERATURE_CHANNEL     7
#  define EXAMPLE_ADC_TEMPERATURE_PIN         AVR32_ADC_AD_7_PIN
#  define EXAMPLE_ADC_TEMPERATURE_FUNCTION    AVR32_ADC_AD_7_FUNCTION
/* Connection of the light sensor */
#  define EXAMPLE_ADC_LIGHT_CHANNEL           6
#  define EXAMPLE_ADC_LIGHT_PIN               AVR32_ADC_AD_6_PIN
#  define EXAMPLE_ADC_LIGHT_FUNCTION          AVR32_ADC_AD_6_FUNCTION

/* Note: Corresponding defines are defined in /BOARDS/EVK1101/evk1101.h.
 * These are here for educational purposes only. */
#elif BOARD == EVK1104
/* Connection of the light sensor */
#  define EXAMPLE_ADC_LIGHT_CHANNEL           0
#  define EXAMPLE_ADC_LIGHT_PIN               AVR32_ADC_AD_0_PIN
#  define EXAMPLE_ADC_LIGHT_FUNCTION          AVR32_ADC_AD_0_FUNCTION

/* Note: Corresponding defines are defined in /BOARDS/EVK1104/evk1104.h.
 * These are here for educational purposes only. */
#elif BOARD == UC3_A3_XPLAINED
/* Connection of the temperature sensor */
#  define EXAMPLE_ADC_TEMPERATURE_CHANNEL     1
#  define EXAMPLE_ADC_TEMPERATURE_PIN         AVR32_ADC_AD_1_PIN
#  define EXAMPLE_ADC_TEMPERATURE_FUNCTION    AVR32_ADC_AD_1_FUNCTION
#endif

static void ui_adc_init(void)
{
	/* GPIO pin/adc-function map */
	static const gpio_map_t ADC_GPIO_MAP = {
#if defined(EXAMPLE_ADC_TEMPERATURE_CHANNEL)
		{EXAMPLE_ADC_TEMPERATURE_PIN, EXAMPLE_ADC_TEMPERATURE_FUNCTION},
#endif
#if defined(EXAMPLE_ADC_LIGHT_CHANNEL)
		{EXAMPLE_ADC_LIGHT_PIN, EXAMPLE_ADC_LIGHT_FUNCTION},
#endif
#if defined(EXAMPLE_ADC_POTENTIOMETER_CHANNEL)
		{EXAMPLE_ADC_POTENTIOMETER_PIN,
		 EXAMPLE_ADC_POTENTIOMETER_FUNCTION}
#endif
	};

	/* Assign and enable GPIO pins to the ADC function */
	gpio_enable_module(ADC_GPIO_MAP,
			sizeof(ADC_GPIO_MAP) / sizeof(ADC_GPIO_MAP[0]));

	/* configure ADC
	 * Lower the ADC clock to match the ADC characteristics (because we
	 * configured the CPU clock to 12MHz, and the ADC clock characteristics
	 * are usually lower;
	 * cf. the ADC Characteristic section in the datasheet) */
	AVR32_ADC.mr |= AVR32_ADC_MR_PRESCAL_MASK;
	adc_configure(&AVR32_ADC);

	/* Enable the ADC channels */
#if defined(EXAMPLE_ADC_TEMPERATURE_CHANNEL)
	adc_enable(&AVR32_ADC, EXAMPLE_ADC_TEMPERATURE_CHANNEL);
#endif
#if defined(EXAMPLE_ADC_LIGHT_CHANNEL)
	adc_enable(&AVR32_ADC, EXAMPLE_ADC_LIGHT_CHANNEL);
#endif
#if defined(EXAMPLE_ADC_POTENTIOMETER_CHANNEL)
	adc_enable(&AVR32_ADC, EXAMPLE_ADC_POTENTIOMETER_CHANNEL);
#endif
}

void ui_adc_read(void)
{
#if defined(EXAMPLE_ADC_TEMPERATURE_CHANNEL)
	static signed short adc_value_temp = -1;
#endif
#if defined(EXAMPLE_ADC_LIGHT_CHANNEL)
	static uint16_t adc_value_light = -1;
#endif
#if defined(EXAMPLE_ADC_POTENTIOMETER_CHANNEL)
	static signed short adc_value_pot = -1;
#endif

	/* launch conversion on all enabled channels */
	adc_start(&AVR32_ADC);

#if defined(EXAMPLE_ADC_TEMPERATURE_CHANNEL)
	/* get value for the temperature adc channel */
	adc_value_temp = adc_get_value(&AVR32_ADC,
			EXAMPLE_ADC_TEMPERATURE_CHANNEL);
#endif

#if defined(EXAMPLE_ADC_LIGHT_CHANNEL)
	/*get value for the light adc channel */
	adc_value_light = adc_get_value(&AVR32_ADC, EXAMPLE_ADC_LIGHT_CHANNEL);
	ui_msg[0] = MESSAGE_ATD_SENSOR_LIGHT;
	ui_msg[1] = adc_value_light >> 8;
	ui_msg[2] = adc_value_light & 0xFF;
	uhi_aoa_write(ui_msg, 3, NULL);
#endif

#if defined(EXAMPLE_ADC_POTENTIOMETER_CHANNEL)
	/* get value for the potentiometer adc channel */
	adc_value_pot = adc_get_value(&AVR32_ADC,
			EXAMPLE_ADC_POTENTIOMETER_CHANNEL);
#endif
}

/* End of ADC */
/** @} */

/**
 * \defgroup UI User Interface
 *
 * Human interface on EVK1104 :
 * - Led 0 is on when USB OTG cable is plugged in
 * - Led 1 is controlled by the Android Application
 * - Led 2 is controlled by the Android Application
 * - Led 3 is controlled by the Android Application
 * - Buttons are reported to the Android Device
 * - Value of the Lightsensor is reported to the Android Device
 */
 
/**
 * \mainpage EVK1104 USB Android Accessory Application Documentation
 *
 * \section intro Introduction
 * This example shows how to implement a USB host for the Android Open
 * Accessory Protocol on a Atmel MCU with a USB module.
 *
 * \section startup Startup
 * After loading firmware, connect the board (EVK1104) to an Android device
 * (supporting Android Open Accessory protocol). The accessory will automatically
 * connect to the Android device
 *
 * \section example About example
 *
 * \copydoc UI
 *
 */
