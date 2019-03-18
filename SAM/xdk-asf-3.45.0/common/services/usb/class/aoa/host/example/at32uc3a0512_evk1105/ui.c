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
#include <et024006dhu.h>
#include <qt1081.h>
#include "usb_connector.h"
#include "cellphone.h"
#include "ui.h"


/** Stores if a button needs to be updated */
volatile uint8_t ui_button_state_toggle[5];

/** Stores the state of the buttons */
bool ui_button_state[5];

/** Stores the last message from/to the Android device */
COMPILER_WORD_ALIGNED
uint8_t ui_msg[64];

/** Indicates the status of a read operation from the Android device */
uint8_t read_complete_flag;

/** Notify the presence of a USB Android device */
static bool ui_aoa_plug = false;

/** Read ongoing */
#define AOA_READ_ONGOING    0x00
/** Read completed successfully */
#define AOA_READ_SUCCESS    0x01
/** Read timed out */
#define AOA_READ_TIMEOUT    0x02
/** Read Error */
#define AOA_READ_ERROR      0x03

/** Definitions for PWM Settings */
#define LED2_PWM_PIN             AVR32_PWM_4_0_PIN
#undef  LED2_PWM_FUNCTION /* Alternate Channel */
#define LED2_PWM_FUNCTION        AVR32_PWM_4_0_FUNCTION
#define LED2_PWM_CHANNEL_ID      AVR32_PWM_ENA_CHID4

#define LED3_PWM_PIN             AVR32_PWM_5_0_PIN
#undef  LED3_PWM_FUNCTION /* Alternate Channel */
#define LED3_PWM_FUNCTION        AVR32_PWM_5_0_FUNCTION
#define LED3_PWM_CHANNEL_ID      AVR32_PWM_ENA_CHID5

#define DISPLAY_PWM_PIN          AVR32_PWM_6_PIN
#define DISPLAY_PWM_FUNCTION     AVR32_PWM_6_FUNCTION
#define DISPLAY_PWM_CHANNEL_ID   AVR32_PWM_ENA_CHID6

/** Display Values */
#define DISPLAY_MAX_LINES        12
#define DISPLAY_FIRST_LINE_X     12
#define DISPLAY_FIRST_LINE_Y     22

/** IRQ line of RTC module is used. */
#define DISPLAY_RTC_IRQ             AVR32_RTC_IRQ
/** IRQ group for RTC */
#define DISPLAY_RTC_IRQ_GROUP       AVR32_RTC_IRQ_GROUP
/** Interrupt priority 1 is used for RTC in this example. */
#define DISPLAY_RTC_IRQ_PRIORITY    1


/*! \brief Initializes and enables Display
 *
 */
static void ui_display_enable(void);

/*! \brief Initializes backlight
 *
 */
static void tft_bl_init(void);

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

/*! \brief Clears the rectangle in which messages from the Android device will
 *       be displayed
 */
static void ui_display_clr_screen(void);

/*! \brief Initializes and enables buttons
 *
 */
static void ui_buttons_enable(void);

/*! \brief Reports if the specified button has changed its state
 *  \param pbutton
 */
bool button_changed(uint8_t pbutton);

/*! \brief Initializes the PWM module
 *
 */
static void ui_pwm_init(void);

/*! \brief Initializes the specified LED
 *  \param lednum
 */
void ui_pwm_led_init(uint8_t lednum);

/*! \brief updates the specified LED
 *  \param channum Number of the PWM Channel
 *  \param brightness 0 to 255
 */
void ui_pwm_update(uint8_t channum, uint8_t brightness);

/**
 * \name Main user interface functions
 * @{
 */
void ui_init(void)
{
	LED_Off(LED0);
	LED_Off(LED1);

	ui_pwm_init();

	ui_pwm_led_init(LED2);
	ui_pwm_led_init(LED3);

	ui_display_enable();

	ui_buttons_enable();

	read_complete_flag = AOA_READ_TIMEOUT;
}

void ui_uhi_aoa_change(uhc_device_t * dev, bool b_plug)
{
	ui_aoa_plug = b_plug;
}

void ui_usb_mode_change(bool b_host_mode)
{
	if (b_host_mode) {
		LED_On(LED0);
	} else {
		LED_Off(LED0);
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
		/* Draw Device incompatible */
		et024006_PrintString((char *)"This Device is not compatible!",
				(const uint8_t *)&FONT8x16, 30, 125, BLUE,
				WHITE);
	} else {
		ui_display_draw_textbox();
	}

	ui_display_disable_rtc();
}

void ui_usb_wakeup_event(void)
{
}

void ui_usb_sof_event(void)
{
	static uint16_t counter_sof = 0;
	uint8_t i = 0;

	if (ui_enum_status == UHC_ENUM_SUCCESS) {
		if (++counter_sof > 2000) {
			counter_sof = 0;
		}

		if (read_complete_flag != AOA_READ_ONGOING) {
			if (read_complete_flag == AOA_READ_SUCCESS) {
				ui_usb_message_reception();
			}

			read_complete_flag = AOA_READ_ONGOING;
			uhi_aoa_read(ui_msg, sizeof(ui_msg), read_complete);
		}

		/* Buttons */
		for (i = 0; i < 5; i++) {
			if (button_changed(i)) {
				ui_button_state[i] = !ui_button_state[i];
				ui_msg[0] = MESSAGE_ATD_SIMPLE_SWITCH;
				ui_msg[1] = i;
				ui_msg[2] = ui_button_state[i];
				uhi_aoa_write(ui_msg, 3, NULL);
				ui_button_state_toggle[i] = 0;
			}
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
			if (ui_msg[2] > 0) {
				LED_On(LED1);
			} else {
				LED_Off(LED1);
			}

			break;

		case 0x01:
			ui_pwm_update(LED2_PWM_CHANNEL_ID, ui_msg[2]);
			break;

		case 0x02:
			ui_pwm_update(LED3_PWM_CHANNEL_ID, ui_msg[2]);
			break;

		default:
			break;
		}
		break;

	case MESSAGE_DTA_SIMPLE_DISPLAY_BACKLIGHT:
		switch (ui_msg[1]) {
		case 0x01:
			ui_pwm_update(DISPLAY_PWM_CHANNEL_ID, ui_msg[2]);
			break;

		default:
			break;
		}

	case MESSAGE_DTA_STRING_BASIC:
		if (ui_msg[2] > 37) {
			/* Truncate message longer than 37 characters */
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

			if (rowcounter > DISPLAY_MAX_LINES) {
				i = 3;
				rowcounter = 1;
				rows_in_message = 1;
				ui_display_clr_screen();
			}
		}
		et024006_PrintString((char *)(&(ui_msg[3])),
				(const uint8_t *)&FONT8x16,
				DISPLAY_FIRST_LINE_X,
				DISPLAY_FIRST_LINE_Y +
				(rowcounter - rows_in_message) * 17, BLUE, -1);
		break;

	default:
		break;
	}
}

/** @} */

/**
 * \name PWM functions
 * @{
 */

avr32_pwm_channel_t led2_pwm = {
	.cdty = 0,
	.cprd = 255
};
avr32_pwm_channel_t led3_pwm = {
	.cdty = 0,
	.cprd = 255
};
avr32_pwm_channel_t backlight_strength = {
	.cdty = 255,
	.cprd = 255
};

static void ui_pwm_init(void)
{
	pwm_opt_t opt = {
		.diva = 0,
		.divb = 0,
		.prea = 0,
		.preb = 0
	};
	pwm_init(&opt);
}

void ui_pwm_led_init(uint8_t lednum)
{
	switch (lednum) {
	case LED1:
		break;

	case LED2:
		gpio_enable_module_pin(LED2_PWM_PIN, LED2_PWM_FUNCTION);

		led2_pwm.CMR.calg = PWM_MODE_LEFT_ALIGNED;
		led2_pwm.CMR.cpol = PWM_POLARITY_LOW;
		led2_pwm.CMR.cpd = PWM_UPDATE_DUTY;
		led2_pwm.CMR.cpre = AVR32_PWM_CMR_CPRE_MCK_DIV_2;

		pwm_channel_init(LED2_PWM_CHANNEL_ID, &led2_pwm);
		pwm_start_channels(1 << LED2_PWM_CHANNEL_ID);
		break;

	case LED3:
		gpio_enable_module_pin(LED3_PWM_PIN, LED3_PWM_FUNCTION);

		led3_pwm.CMR.calg = PWM_MODE_LEFT_ALIGNED;
		led3_pwm.CMR.cpol = PWM_POLARITY_LOW;
		led3_pwm.CMR.cpd = PWM_UPDATE_DUTY;
		led3_pwm.CMR.cpre = AVR32_PWM_CMR_CPRE_MCK_DIV_2;

		pwm_channel_init(LED3_PWM_CHANNEL_ID, &led3_pwm);
		pwm_start_channels(1 << LED3_PWM_CHANNEL_ID);
		break;

	default:
		break;
	}
}

void ui_pwm_update(uint8_t channum, uint8_t brightness)
{
	switch (channum) {
	case 0x04:
		led2_pwm.cmr = PWM_UPDATE_DUTY;
		led2_pwm.cdty = brightness;
		led2_pwm.cupd = led2_pwm.cdty;
		pwm_sync_update_channel(LED2_PWM_CHANNEL_ID, &led2_pwm);
		break;

	case 0x05:
		led3_pwm.cmr = PWM_UPDATE_DUTY;
		led3_pwm.cdty = brightness;
		led3_pwm.cupd = led3_pwm.cdty;
		pwm_sync_update_channel(LED3_PWM_CHANNEL_ID, &led3_pwm);
		break;

	case 0x06:
		backlight_strength.cmr = PWM_UPDATE_DUTY;
		backlight_strength.cdty = brightness;
		backlight_strength.cupd = backlight_strength.cdty;
		pwm_sync_update_channel(DISPLAY_PWM_CHANNEL_ID,
				&backlight_strength);
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

	tft_bl_init();

	ui_display_welcome_msg();

	ui_display_init_rtc();
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
	et024006_DrawFilledRect(0, 0, ET024006_WIDTH, ET024006_HEIGHT, WHITE);
	et024006_PutPixmap(pic_cellphone, 80, 0, 0, 0, 0, 80, 99);
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

	// There is no OSC32 on this kit. Use the RC115 for the RTC.
	rtc_init(&AVR32_RTC, RTC_OSC_RC, RTC_PSEL_RC_1_76HZ - 1);

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

static void tft_bl_init(void)
{
	gpio_enable_module_pin(DISPLAY_PWM_PIN, DISPLAY_PWM_FUNCTION);

	backlight_strength.CMR.calg = PWM_MODE_LEFT_ALIGNED;
	backlight_strength.CMR.cpol = PWM_POLARITY_HIGH;
	backlight_strength.CMR.cpd = PWM_UPDATE_DUTY;
	backlight_strength.CMR.cpre = AVR32_PWM_CMR_CPRE_MCK_DIV_2;

	pwm_channel_init(DISPLAY_PWM_CHANNEL_ID, &backlight_strength);
	pwm_start_channels(1 << DISPLAY_PWM_CHANNEL_ID);

	ui_pwm_update(DISPLAY_PWM_CHANNEL_ID, 0);
}

/* End of Display */
/** @} */

/**
 * \name Button defines and functions
 * @{
 */

#define is_touch_up()       is_touch_sensor_0()
#define is_touch_down()     is_touch_sensor_1()
#define is_touch_right()    is_touch_sensor_2()
#define is_touch_left()     is_touch_sensor_3()
#define is_touch_center()   is_touch_sensor_4()

/** Structure holding the configuration parameters of the EIC module */
eic_options_t eic_options[2];

#define BUTTON_INTERRUPT_LEVEL 1

ISR(touch_button_isr, AVR32_EIC_IRQ_GROUP, BUTTON_INTERRUPT_LEVEL)
{
	if (is_touch_up()) {
		ui_button_state_toggle[0] = true;
	}

	if (is_touch_down()) {
		ui_button_state_toggle[1] = true;
	}

	if (is_touch_right()) {
		ui_button_state_toggle[2] = true;
	}

	if (is_touch_left()) {
		ui_button_state_toggle[3] = true;
	}

	if (is_touch_center()) {
		ui_button_state_toggle[4] = true;
	}

	eic_clear_interrupt_line(&AVR32_EIC, QT1081_EIC_EXTINT_INT);
}

static void ui_buttons_enable(void)
{
	uint8_t i;
	for (i = 0; i < 5; i++) {
		ui_button_state_toggle[i] = 0;
	}

	/* Enable edge-triggered interrupt */
	eic_options[0].eic_mode  = EIC_MODE_EDGE_TRIGGERED;

	/* Interrupt will trigger on falling edge (this is a must-do for the
	 * keypad scan feature if the chosen mode is edge-triggered) */
	eic_options[0].eic_edge  = EIC_EDGE_RISING_EDGE;

	/* Initialize in synchronous mode, interrupt is synchronized to the
	 * clock */
	eic_options[0].eic_async = EIC_SYNCH_MODE;

	/* Set the interrupt line number */
	eic_options[0].eic_line  = QT1081_EIC_EXTINT_INT;

	gpio_enable_module_pin( QT1081_EIC_EXTINT_PIN,
			QT1081_EIC_EXTINT_FUNCTION);

	Disable_global_interrupt();

	irq_register_handler(touch_button_isr, QT1081_EIC_EXTINT_IRQ,
			BUTTON_INTERRUPT_LEVEL);

	/* Init the EIC controller with the options */
	eic_init(&AVR32_EIC, eic_options, 1);
	/* Enable the EIC lines */
	eic_enable_lines(&AVR32_EIC, (1 << eic_options[0].eic_line));
	/* Enable the interrupt for each EIC line */
	eic_enable_interrupt_lines(&AVR32_EIC, (1 << eic_options[0].eic_line));

	Enable_global_interrupt();
}

bool button_changed(uint8_t pButton)
{
	return ui_button_state_toggle[pButton];
}

/* End of Buttons */
/** @} */

/**
 * \defgroup UI User Interface
 *
 * Human interface on EVK1105 :
 * - PWR led is on when power present
 * - Led 0 is on when USB OTG cable is plugged in
 * - Led 1 is controlled by the Android Application
 * - Led 2 is controlled by the Android Application
 * - Led 3 is controlled by the Android Application
 * - Display is controlled by the Android Application
 * - Status of Buttons is send to the Android Application
 */

/**
 * \mainpage EVK1105 USB Android Accessory Application Documentation
 *
 * \section intro Introduction
 * This example shows how to implement a USB host for the Android Open
 * Accessory Protocol on a Atmel MCU with a USB module.
 *
 * \section startup Startup
 * After loading firmware, connect the board (EVK1105) to an Android device
 * (supporting Android Open Accessory protocol). The accessory will automatically
 * connect to the Android device
 *
 * \section example About example
 *
 * \copydoc UI
 *
 */
