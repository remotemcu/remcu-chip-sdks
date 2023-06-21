/**
 * \file
 *
 * \brief SAML22 RTC Tamper Detection Example
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
/**
 * \mainpage SAML22 RTC Tamper Detection Example
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This application demonstrates different modes of tamper detection which is
 * available as an additional feature of RTC in SAM L22. Once the tamper occurs
 * this application performs the following actions 
 * Detect Tamper, starts DMA transfer when the timestamp occurs
 * store timestamp value in NVM of MCU. 
 * Display error message on LCD & terminal window
 * Set alarm for 5 seconds.
 * It also reads and erases the NVM contents on user input.
 */

/**
 * \page appdoc_main SAML22 RTC Tamper Detection Example
 *
 * Overview:
 * - \ref appdoc_sam0_tamper_detection_example_intro
 * - \ref appdoc_sam0_tamper_detection_example_setup
 * - \ref appdoc_sam0_tamper_detection_example_imp
 * - \ref appdoc_sam0_tamper_detection_example_compinfo
 * - \ref appdoc_sam0_tamper_detection_example_contactinfo
 *
 * \section appdoc_sam0_tamper_detection_example_intro Introduction
 * This application demonstrates different modes of tamper detection which is
 * available as an additional feature of RTC in SAM L22. Once the tamper occurs
 * this application performs the following actions
 * Detect Tamper, starts DMA transfer when the timestamp occurs
 * store timestamp value in NVM of MCU.
 * Display error message on LCD & terminal window
 * Set alarm for 5 seconds.
 * It also reads and erases the NVM contents on user input.
 *
 * This application has been tested on following board:
 * - SAM L22 Xplained Pro
 *
 *\section deviceinfo Device Information
 * SEGMENT LCD1 Xplained Pro extension board connected to SAM L22 Xplained Pro
 * board.
 *
 * \section appdoc_sam0_tamper_detection_example_setup Hardware Setup
 * This application use user switch SW0 on SAM L22 Xplained Pro board as tamper
 * input source. No hardware setup is required for testing this project.
 *
 * The application can easily be modified to use other tamper input pin for
 * tamper detection.
 *
 * \section appdoc_sam0_tamper_detection_example_imp Implementation Details
 *
 * \subsection appdoc_sam0_tamper_detection_example_OFF Disable tamper 
 * Disables the tamper detection based on the user input.
 * 
 * \subsection appdoc_sam0_tamper_detection_example_wake Tamper in wake mode
 * Enables tamper in wake mode. When tamper occurs in this mode, the
 * application will display the error message on LCD and terminal window and
 * set alarm after 5 secs 
 *
 * \subsection appdoc_sam0_tamper_detection_example_capture Tamper enabled 
 * in capture mode
 * Enables tamper in capture mode. When tamper occurs in this mode, the
 * application will display tamper occurred time on LCD and terminal  window,
 * set alarm after 5 secs and store the time in the NVM memory 
 *
 * \subsection appdoc_sam0_tamper_detection_example_read_history read tamper 
 * history
 * Read the tamper occurrence history from NVM.
 *
 * \subsection appdoc_sam0_tamper_detection_example_erase erase tamper history
 * history
 * erase the tamper history in NVM.
 * 
 * \section appdoc_sam0_tamper_detection_example_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_tamper_detection_example_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <string.h>
#include <asf.h>
#include <stdio_serial.h>
#include <conf_example.h>

/** Create DMA descriptor */
COMPILER_ALIGNED(32)
DmacDescriptor example_descriptor;

/** Peripheral instance structures **/
struct rtc_module rtc_instance;
struct usart_module usart_instance;
struct rtc_calendar_time time;
struct rtc_calendar_alarm_time alarm;
struct rtc_calendar_time tamper_time;
struct rtc_calendar_time read_time;
struct tcc_module tcc_instance;
struct dma_resource example_resource;

/* Global variable declaration*/

/*status flag to detect whether tamper occurred or not*/
static volatile bool tamper_flag = false;
/*Array to get time value to print in LCD*/
char time_value[5];
/*destination memory of DMA to store timestamp value*/
volatile uint32_t buffer_rtc_tamper;
/*index which stores the number tamper occurrence in the emulated EEPROM*/
volatile uint16_t memory_index;

/**
* \brief tamper callback function for tamper occurrence.
*
* This function sets alarm after 5 seconds, enables timer for SLCD back light
* toggle and set the tamper_flag 
*
*/
void rtc_tamper_callback(void)
{
	struct rtc_module *module = &rtc_instance;
	Rtc *const rtc_module = module->hw;
    /*turn on LED*/
	LCD_BACKLIGHT_OFF;
	/*clear the LCD display*/
	slcd_clear_display_memory();
	/*Turn off the LED*/
	LCD_BACKLIGHT_ON;
	/*enable alarm callback*/
	rtc_calendar_enable_callback(&rtc_instance, RTC_CALENDAR_CALLBACK_ALARM_0);

	/*setup enable TCC*/
	tcc_enable(&tcc_instance);

	/*Get current time from clock register*/
	rtc_calendar_get_time(&rtc_instance, &time);

	/*copy the time values to alarm structure*/
	alarm.time.second = time.second;

	/* Set alarm in 5 seconds */
	alarm.mask = RTC_CALENDAR_ALARM_MASK_SEC;
	alarm.time.second += SET_ALARM_TIME;
	alarm.time.second = alarm.time.second % 60;

	/*set alarm*/
	rtc_calendar_set_alarm(&rtc_instance, &alarm, RTC_CALENDAR_ALARM_0);

	/*clear tamper flag and tamper_id*/
	rtc_module->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_TAMPER;
	rtc_tamper_clear_detect_flag(&rtc_instance,
	rtc_tamper_get_detect_flag(&rtc_instance));
	/*set the tamper flag*/
	tamper_flag = true;
}

/**
* \brief alarm callback function
*
* This function clears the SLCD display and back light toggling
*
*/
void rtc_match_callback(void)
{
	/*turn Off LCD backlight*/
	LCD_BACKLIGHT_OFF;

	/*disable alarm callback*/
	rtc_calendar_disable_callback(&rtc_instance, RTC_CALENDAR_CALLBACK_ALARM_0);

	/*clear LCD display*/
	slcd_clear_display_memory();

	/*disable_TCC*/
	tcc_disable(&tcc_instance);
}

/**
* \brief Configure tamper detection in capture mode
*
* This function configures the tamper detection in capture mode and starts the
* DMA transfer to read the timestamp register
*
* \note This function disables RTC, configures tamper in capture mode and
* enables the RTC
*/
void configure_tamper_capture_mode(void)
{
	struct rtc_module *module = &rtc_instance;
	Rtc *const rtc_module = module->hw;
	     
	/* Initialize tamper in capture mode. */
	struct rtc_tamper_config config_rtc_tamper;
	rtc_tamper_get_config_defaults(&config_rtc_tamper);

	/* disable GP0*/
	config_rtc_tamper.gp0_enable = false;

	/*enable DMA on tamper detection*/
	config_rtc_tamper.dma_tamper_enable = true;

	/*configure the input action,pin and level*/
	config_rtc_tamper.in_cfg[TAMPER_INPUT_PIN].level = RTC_TAMPER_LEVEL_RISING;
	config_rtc_tamper.in_cfg[TAMPER_INPUT_PIN].action = 
			RTC_TAMPER_INPUT_ACTION_CAPTURE;

	/*disable_RTC*/
	rtc_calendar_disable(&rtc_instance);

	/*set tamper configuration*/
	rtc_tamper_set_config(&rtc_instance, &config_rtc_tamper);

	/*enable_RTC*/
	rtc_calendar_enable(&rtc_instance);

	/*dummy read timestamp value*/
	volatile uint32_t time_stamp = rtc_module->MODE2.TIMESTAMP.reg;
	
	/*dummy write to avoid warning*/
	time_stamp = time_stamp;

	/*configure DMA*/
	config_dma();
	
	/*start the DMA transfer*/
	dma_start_transfer_job(&example_resource);
		
	/*enable callback for tamper*/
	rtc_calendar_enable_callback(&rtc_instance, RTC_CALENDAR_CALLBACK_TAMPER);

	/*set the mode flag to two*/
	mode = SET_TO_CAPTURE;
	previous_mode = mode;
	printf("\r\nTamper enabled in CAPTURE mode\r\n");
}

/**
* \brief Configure tamper detection in wake mode
*
* \note This function disables RTC, configures tamper in wake mode and
* enables the RTC
*/
void configure_tamper_wake_mode(void)
{
	/* Initialize tamper */
	struct rtc_tamper_config config_rtc_tamper;
	rtc_tamper_get_config_defaults(&config_rtc_tamper);

	/* disable GP0*/
	config_rtc_tamper. gp0_enable = false;

	/*configure the input action,pin and level*/
	config_rtc_tamper.in_cfg[TAMPER_INPUT_PIN].level = RTC_TAMPER_LEVEL_RISING;
	config_rtc_tamper.in_cfg[TAMPER_INPUT_PIN].action = 
			RTC_TAMPER_INPUT_ACTION_WAKE;

	/*disable_RTC*/
	rtc_calendar_disable(&rtc_instance);

	/*set tamper configuration*/
	rtc_tamper_set_config(&rtc_instance, &config_rtc_tamper);

	/*enable_RTC*/
	rtc_calendar_enable(&rtc_instance);

	/*enable callback for tamper*/
	rtc_calendar_enable_callback(&rtc_instance, RTC_CALENDAR_CALLBACK_TAMPER);

	/*set the mode flag to one*/
	mode = SET_TO_WAKE;
	previous_mode = mode;
	printf("\r\nTamper enabled in WAKE mode\r\n");
}

/**
* \brief Disable tamper detection
*
* \note This function disables RTC, disables tamper and enables the RTC
*/
void configure_tamper_off_mode(void)
{
	struct rtc_module *module = &rtc_instance;
	Rtc *const rtc_module = module->hw;
	/* Initialize tamper */
	struct rtc_tamper_config config_rtc_tamper;
	rtc_tamper_get_config_defaults(&config_rtc_tamper);

	/* disable GP0*/
	config_rtc_tamper. gp0_enable = false;

	/*disable_RTC*/
	rtc_calendar_disable(&rtc_instance);

	/*set tamper configuration*/
	rtc_tamper_set_config(&rtc_instance, &config_rtc_tamper);

	/*enable_RTC*/
	rtc_calendar_enable(&rtc_instance);

	/*enable callback for tamper*/
	rtc_calendar_disable_callback(&rtc_instance, RTC_CALENDAR_CALLBACK_TAMPER);

	/*clear tamper flag and tamper_id*/
	rtc_module->MODE2.INTFLAG.reg = RTC_MODE2_INTFLAG_TAMPER;
			rtc_tamper_clear_detect_flag(&rtc_instance,
	rtc_tamper_get_detect_flag(&rtc_instance));

	mode = SET_TO_DISABLE;
	printf("\r\nTamper disabled\r\n");
	/*turn off SLCD back light*/
	LCD_BACKLIGHT_OFF;
}

/**
* \brief Configure RTC calender time
*/
void configure_rtc_calender_time(void)
{
	rtc_calendar_get_time_defaults(&time);
	/*set time*/
	time.year = YEAR;
	time.month = MONTH;
	time.day = DAY;
	time.hour = HOUR;
	time.minute = MINUTE;
	time.second = SECOND;
	time.pm = TIME_PM;

	/*set calender time*/
	rtc_calendar_set_time(&rtc_instance, &time);
}

/**
* \brief Configure RTC in calendar mode
*
* This function configures the RTC in calendar mode with alarm enabled
*
*/
void configure_rtc_calendar(void)
{
	/* Initialize RTC in calendar mode. */
	struct rtc_calendar_config config_rtc_calendar;
	rtc_calendar_get_config_defaults(&config_rtc_calendar);

	/*configure for 12 hours time mode*/
	config_rtc_calendar.clock_24h = false;

	/*set alarm time to alarm mask register*/
	config_rtc_calendar.alarm[0].time = alarm.time;

	/*mask the alarm for entire year*/
	config_rtc_calendar.alarm[0].mask = RTC_CALENDAR_ALARM_MASK_YEAR;

	/*initialize rtc*/
	rtc_calendar_init(&rtc_instance, RTC, &config_rtc_calendar);
	
	/*enable_RTC*/
	rtc_calendar_enable(&rtc_instance);
}

/**
* \brief Configure RTC callback for tamper and alarm function
*/
void configure_rtc_callbacks(void)
{
	/*register callback for tamper*/
	rtc_calendar_register_callback(
	&rtc_instance, rtc_tamper_callback, RTC_CALENDAR_CALLBACK_TAMPER);

	/*register callback for alarm*/
	rtc_calendar_register_callback(
	&rtc_instance, rtc_match_callback, RTC_CALENDAR_CALLBACK_ALARM_0);
}

/**
* \brief Configure TCC callback
*/
void tcc_callback_to_toggle_led(struct tcc_module *const module_inst)
{
	/*toggle the LED*/
	port_pin_toggle_output_level(LED0_PIN);
}

/**
* \brief Configure the TCC for SLCD back light blinking
*/

void configure_tcc(void)
{
	struct tcc_config config_tcc;
	tcc_get_config_defaults(&config_tcc, TCC0);

	config_tcc.counter.clock_source = GCLK_GENERATOR_0;
	config_tcc.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV64;

	/*set TCC overflow value*/
	config_tcc.counter.period = SLCD_BLINK_SPEED;

	/*set TCC configuration*/
	tcc_init(&tcc_instance, TCC0, &config_tcc);
}

/**
* \brief Configure and enable TCC callback
*/
void configure_tcc_callbacks(void)
{
	/*register callback for TCC*/
	tcc_register_callback(&tcc_instance, tcc_callback_to_toggle_led,
	TCC_CALLBACK_OVERFLOW);

	/*enable callback for TCC*/
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_OVERFLOW);
}


/**
* \brief Pinmux configuration for SLCD pins
*/
static void config_slcd(void)
{
	#if 1
		struct system_pinmux_config pin_conf;
		system_pinmux_get_config_defaults(&pin_conf);

		pin_conf.direction = SYSTEM_PINMUX_PIN_DIR_OUTPUT;
		pin_conf.input_pull = SYSTEM_PINMUX_PIN_PULL_NONE;

		pin_conf.mux_position = MUX_PA06B_SLCD_LP6;
		system_pinmux_pin_set_config(PIN_PA06B_SLCD_LP6, &pin_conf);

		pin_conf.mux_position = MUX_PA07B_SLCD_LP7;
		system_pinmux_pin_set_config(PIN_PA07B_SLCD_LP7, &pin_conf);

		pin_conf.mux_position = MUX_PC05B_SLCD_LP8;
		system_pinmux_pin_set_config(PIN_PC05B_SLCD_LP8, &pin_conf);

		pin_conf.mux_position = MUX_PC06B_SLCD_LP9;
		system_pinmux_pin_set_config(PIN_PC06B_SLCD_LP9, &pin_conf);

		pin_conf.mux_position = MUX_PA11B_SLCD_LP14;
		system_pinmux_pin_set_config(PIN_PA11B_SLCD_LP14, &pin_conf);

		pin_conf.mux_position = MUX_PC08B_SLCD_LP15;
		system_pinmux_pin_set_config(PIN_PC08B_SLCD_LP15, &pin_conf);

		pin_conf.mux_position = MUX_PC09B_SLCD_LP16;
		system_pinmux_pin_set_config(PIN_PC09B_SLCD_LP16, &pin_conf);

		pin_conf.mux_position = MUX_PC10B_SLCD_LP17;
		system_pinmux_pin_set_config(PIN_PC10B_SLCD_LP17, &pin_conf);

		pin_conf.mux_position = MUX_PC11B_SLCD_LP18;
		system_pinmux_pin_set_config(PIN_PC11B_SLCD_LP18, &pin_conf);

		pin_conf.mux_position = MUX_PC12B_SLCD_LP19;
		system_pinmux_pin_set_config(PIN_PC12B_SLCD_LP19, &pin_conf);

		pin_conf.mux_position = MUX_PC13B_SLCD_LP20;
		system_pinmux_pin_set_config(PIN_PC13B_SLCD_LP20, &pin_conf);

		pin_conf.mux_position = MUX_PB11B_SLCD_LP21;
		system_pinmux_pin_set_config(PIN_PB11B_SLCD_LP21, &pin_conf);

		pin_conf.mux_position = MUX_PB12B_SLCD_LP22;
		system_pinmux_pin_set_config(PIN_PB12B_SLCD_LP22, &pin_conf);

		pin_conf.mux_position = MUX_PB13B_SLCD_LP23;
		system_pinmux_pin_set_config(PIN_PB13B_SLCD_LP23, &pin_conf);

		pin_conf.mux_position = MUX_PB14B_SLCD_LP24;
		system_pinmux_pin_set_config(PIN_PB14B_SLCD_LP24, &pin_conf);

		pin_conf.mux_position = MUX_PB15B_SLCD_LP25;
		system_pinmux_pin_set_config(PIN_PB15B_SLCD_LP25, &pin_conf);

		pin_conf.mux_position = MUX_PC14B_SLCD_LP26;
		system_pinmux_pin_set_config(PIN_PC14B_SLCD_LP26, &pin_conf);

		pin_conf.mux_position = MUX_PC15B_SLCD_LP27;
		system_pinmux_pin_set_config(PIN_PC15B_SLCD_LP27, &pin_conf);

		pin_conf.mux_position = MUX_PA14B_SLCD_LP30;
		system_pinmux_pin_set_config(PIN_PA14B_SLCD_LP30, &pin_conf);

		pin_conf.mux_position = MUX_PA15B_SLCD_LP31;
		system_pinmux_pin_set_config(PIN_PA15B_SLCD_LP31, &pin_conf);

		pin_conf.mux_position = MUX_PC16B_SLCD_LP36;
		system_pinmux_pin_set_config(PIN_PC16B_SLCD_LP36, &pin_conf);

		pin_conf.mux_position = MUX_PC17B_SLCD_LP37;
		system_pinmux_pin_set_config(PIN_PC17B_SLCD_LP37, &pin_conf);

		pin_conf.mux_position = MUX_PC18B_SLCD_LP38;
		system_pinmux_pin_set_config(PIN_PC18B_SLCD_LP38, &pin_conf);

		pin_conf.mux_position = MUX_PC19B_SLCD_LP39;
		system_pinmux_pin_set_config(PIN_PC19B_SLCD_LP39, &pin_conf);

		pin_conf.mux_position = MUX_PC20B_SLCD_LP40;
		system_pinmux_pin_set_config(PIN_PC20B_SLCD_LP40, &pin_conf);

		pin_conf.mux_position = MUX_PC21B_SLCD_LP41;
		system_pinmux_pin_set_config(PIN_PC21B_SLCD_LP41, &pin_conf);

		pin_conf.mux_position = MUX_PB16B_SLCD_LP42;
		system_pinmux_pin_set_config(PIN_PB16B_SLCD_LP42, &pin_conf);

		pin_conf.mux_position = MUX_PB17B_SLCD_LP43;
		system_pinmux_pin_set_config(PIN_PB17B_SLCD_LP43, &pin_conf);

		pin_conf.mux_position = MUX_PB18B_SLCD_LP44;
		system_pinmux_pin_set_config(PIN_PB18B_SLCD_LP44, &pin_conf);
	#endif
}

/**
* \brief Initialize the SLCD Glass component.
*
* This function initializes the LCD driver to control the LCD glass.
* It perform LCD module initialization according to the XPRO_LCD
* characteristics.
*
*/
status_code_genare_t xpro_lcd_init(void)
{
	/* configure SLCD */
	struct slcd_config config;
	slcd_get_config_defaults(&config);

	/*SLCD_STANDARD_WAVEFORM_MODE*/
	config.waveform_mode = SLCD_STANDARD_WAVEFORM_MODE;

	/*Initialize SLCD*/
	slcd_init(&config);

	/*set frame count of SLCD*/
	slcd_set_frame_counter(SLCD_FRAME_COUNTER_0, false, FRAME_COUNT_OVERFLOW);
	slcd_set_frame_counter(SLCD_FRAME_COUNTER_1, false, FRAME_COUNT_OVERFLOW);
	slcd_set_frame_counter(SLCD_FRAME_COUNTER_2, false, FRAME_COUNT_OVERFLOW);
	/*set maximum contrast of SLCD*/
	slcd_set_contrast(SLCD_CONTRAST);

	return STATUS_OK;
}

/**
* \brief Initializes the SLCD
*/
void lcd_init(void)
{
	uint8_t com, seg;
	/*configure slcd*/
	config_slcd();

	/*initialize slcd*/
	xpro_lcd_init();

	/*enable slcd*/
	slcd_enable();

	/*clear display memory*/
	slcd_clear_display_memory();

	/*Set the connected pixels*/
	for(com = 0; com <= 3; com++) {
		for (seg = 0; seg <= 23; seg++) {
			slcd_set_pixel(com, seg);
			delay_ms(10);
		}
	}
	/*clear display memory*/
	slcd_clear_display_memory();

	LCD_BACKLIGHT_OFF;
}

/**
* \brief Displays the string on the SLCD screen
*
* \param *data  string to be displayed on the SLCD.
*
*/
void xpro_lcd_show_text(const char *data)
{
	Assert(data);
	uint32_t len = (uint32_t)strlen((char *) data);

	len = (len > XPRO_LCD_MAX_CHAR) ? XPRO_LCD_MAX_CHAR : len;

	slcd_character_map_set(SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT,
	SEGMENT_LINE_NUMBER);
	for(uint32_t i = 0 ; *data != '\0' ; i++) {
		slcd_character_write_data(SET_TO_ZERO,
		XPRO_LCD_TXT_SEG_INDEX_S+i*SEGMENT_LENGTH,
		DIGI_LUT[*(data++) - 32], 0x4002);
	}
}

/**
* \brief Displays the tamper occurrence time on SLCD
*/
void lcd_display_time(void)
{
	/*converts time value to string for SLCD display*/
	snprintf(time_value,sizeof(time_value),"%02d%02d ", tamper_time.hour,
			tamper_time.minute);
	/*checks whether time is AM or PM*/
	if(tamper_time.pm) {
		/*displays PM on SLCD*/
		slcd_set_pixel(COM_FOR_TIME, SEGMENT_FOR_PM);
	} else {
		/*displays AM on SLCD*/
		slcd_set_pixel(COM_FOR_TIME, SEGMENT_FOR_AM);
	}
	/*Displays colon(:) on SLCD*/
	slcd_set_pixel(COM_FOR_COLON, SEGMENT_FOR_COLON);
	/*displays the tamper time on SLCD*/
	xpro_lcd_show_text(time_value);
	/*writes the tamper time to RWW EEPROM memory*/
}

/**
* \brief Config DMA to make register-to-register transfer copying the
* timestamp value. 
*/
void config_dma(void)
{
	/*setup_dma_resource*/
	configure_dma_resource(&example_resource);

	/*setup_transfer_descriptor*/
	setup_transfer_descriptor(&example_descriptor);

	/*add_descriptor_to_resource*/
	dma_add_descriptor(&example_resource, &example_descriptor);
}

/**
* \brief configure DMA transfer descriptor.
*/
void setup_transfer_descriptor(DmacDescriptor *descriptor )
{
	/*initialize DMA*/
	struct dma_descriptor_config descriptor_config;
	dma_descriptor_get_config_defaults(&descriptor_config);

	/*configure DMA */
	descriptor_config.beat_size = DMA_BEAT_SIZE_WORD;
	descriptor_config.dst_increment_enable = false;
	descriptor_config.src_increment_enable = false;
	descriptor_config.block_transfer_count = sizeof(uint32_t);
	descriptor_config.source_address = 
			(uint32_t)(&(rtc_instance.hw->MODE0.TIMESTAMP));
	descriptor_config.destination_address = (uint32_t)&(buffer_rtc_tamper);
	descriptor_config.next_descriptor_address = (uint32_t)&example_descriptor;

	/*create DMA descriptor*/
	dma_descriptor_create(descriptor, &descriptor_config);
}

/**
* \brief configure DMA resource.
*/
void configure_dma_resource(struct dma_resource *resource)
{
	/*initialize DMA resources*/
	struct dma_resource_config config;
	dma_get_config_defaults(&config);

	/*configure TImestamp event as trigger source for DMA*/
	config.peripheral_trigger = RTC_DMAC_ID_TIMESTAMP;

	/*allocate DMA resource*/
	dma_allocate(resource, &config);
}

/**
* \brief Configure usart
*/
static void configure_usart(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate = SET_BAUD_RATE;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	stdio_serial_init(&usart_instance, EDBG_CDC_MODULE, &config_usart);
	usart_enable(&usart_instance);
}

/**
* \brief Display menu on the terminal window.
*/

static void display_menu(void)
{
	printf("\n\r");
	printf("============================================================\n\r");
	printf("Menu: press any key to continue.\n\r");
	printf("============================================================\n\r");

	printf(" a : OFF mode: To disable tamper detection\n\r");
	printf(" b : WAKE mode: Wake on tamper detection\n\r");
	printf(" c : CAPTURE mode: Wake on tamper and capture timestamp\n\r");
	printf(" d : Show Tamper History\n\r");
	printf(" e : Clear Tamper History\n\r");

	printf("============================================================\n\r");
	printf(">> ");
}

/**
* \brief Configure eeprom
*/
void configure_eeprom(void)
{
	/* Setup EEPROM emulator service */
	enum status_code error_code = rww_eeprom_emulator_init();

	/*check_init_ok*/
	if (error_code == STATUS_ERR_NO_MEMORY) {
		while (true) {
			/* No EEPROM section has been set in the device's fuses */
		}
	} else if (error_code != STATUS_OK) {
		/* Erase the emulated EEPROM memory (assume it is unformatted or
		* irrecoverably corrupt) */
		rww_eeprom_emulator_erase_memory();
		rww_eeprom_emulator_init();
	}
}

#if (SAMD21) || (SAMDA1)
	void SYSCTRL_Handler(void)
	{
		if (SYSCTRL->INTFLAG.reg & SYSCTRL_INTFLAG_BOD33DET) {
			SYSCTRL->INTFLAG.reg = SYSCTRL_INTFLAG_BOD33DET;
			rww_eeprom_emulator_commit_page_buffer();
		}
	}
#endif

/**
* \brief Configure BOD
*/
static void configure_bod(void)
{
	#if (SAMD21) || (SAMDA1)
		struct bod_config config_bod33;
		bod_get_config_defaults(&config_bod33);
		config_bod33.action = BOD_ACTION_INTERRUPT;
		/* BOD33 threshold level is about 3.2V */
		config_bod33.level = 48;
		bod_set_config(BOD_BOD33, &config_bod33);
		bod_enable(BOD_BOD33);

		SYSCTRL->INTENSET.reg = SYSCTRL_INTENCLR_BOD33DET;
		system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_SYSCTRL);
	#endif
}

/**
* \brief writes the timestamp value to RWW EEPROM once the tamper occurs.
*/
void write_tamper_data(void)
{
	/*offset pointing to next read location*/
	volatile uint8_t off_set = 2 ; 
	/*RWW EEPRM read memory index*/
	rww_eeprom_emulator_read_buffer(SET_TO_ZERO, (uint8_t *)&memory_index,
			LENGTH_OF_MEMORY_INDEX);
	if(memory_index<MAXIMUM_ENTRIES_STORED) {
		off_set = (memory_index*LENGTH_OF_TIME_STRUCT) + LENGTH_OF_MEMORY_INDEX;
		/*RWW EEPRM write page buffer*/
		rww_eeprom_emulator_write_buffer(off_set, (const uint8_t *)&tamper_time,
				LENGTH_OF_TIME_STRUCT);
		memory_index++;
		/*RWW EEPRM write memory index*/
		rww_eeprom_emulator_write_buffer(SET_TO_ZERO, (const uint8_t *)&memory_index,
				LENGTH_OF_MEMORY_INDEX);
		/*RWW EEPRM commit page buffer*/
		rww_eeprom_emulator_commit_page_buffer();
	} else {
		printf("\r\nMemory Full\n\r");
		printf("\r\nNext tamper time will not be recorded\n\r");
		printf("\r\nClear tamper history\n\r");
	}
}

/**
* \brief  Reads the timestamp value stored in the RWW EEPROM
*
* This function disables the tamper detection during read operation
*
*/
void read_tamper_history(void)
{
	/*offset pointing to next read location*/
	volatile uint8_t read_off_set ; 
	/*Disable Tamper*/
	configure_tamper_off_mode();
	/*clear the LCD display*/
	slcd_clear_display_memory();
	/*Read the entire EEPROM memory*/
	printf("\r\nRead Tamper History\r\n");
	/*initialize read offset*/
	read_off_set = LENGTH_OF_MEMORY_INDEX;
	/*RWW EEPRM read memory index*/
	rww_eeprom_emulator_read_buffer(SET_TO_ZERO, (uint8_t *)&memory_index,
	LENGTH_OF_MEMORY_INDEX);
	if(memory_index == SET_TO_ZERO) {
		printf("\r\n No Tamper History available\r\n");
	} else {
		printf("\r\nTamper Detection Disabled\r\n");
		printf("\r\nShowing tamper History:\r\n");
		for(uint8_t i = 0; i<memory_index; i++) {
			/*RWW EEPRM read page buffer*/
			rww_eeprom_emulator_read_buffer(read_off_set,(uint8_t *)&read_time,
			LENGTH_OF_TIME_STRUCT);
			read_off_set = read_off_set + LENGTH_OF_TIME_STRUCT;
			printf("\r\nTamper occurred at[HH:MM:SS] = [%02d:%02d:%02d]%s\r\n",
					read_time.hour, read_time.minute, read_time.second,
					read_time.pm?"PM":"AM");
		}
	}
	enable_tamper();
}

/**
* \brief  Erase entire RWW EEPROM section.
*/
void erase_tamper_history (void)
{
	/*RWW EEPRM erase page buffer*/
	rww_eeprom_emulator_erase_memory();
	/*initialize memory buffer*/
	memory_index = SET_TO_ZERO;
	/*RWW EEPRM write page buffer*/
	rww_eeprom_emulator_write_buffer(SET_TO_ZERO,
	(const uint8_t *)&memory_index, LENGTH_OF_MEMORY_INDEX);
	/*RWW EEPRM commit page buffer*/
	rww_eeprom_emulator_commit_page_buffer();
	printf("\r\nTamper History erased\r\n");
}

/**
* \brief  Configures the RWW EEPROM memory during the startup
*
* This function will assign the first two bytes of RWW EEPROM as memory index
* representing number of entries stored and initializes the memory index
* 
*/
void memory_index_init(void)
{
	/*RWW EEPRM read page buffer*/
	rww_eeprom_emulator_read_buffer(SET_TO_ZERO, (uint8_t *)&memory_index,
	LENGTH_OF_MEMORY_INDEX);

	if(memory_index == EEPROM_EMPTY_CHAR) {
		/*initialize memory index*/
		memory_index = SET_TO_ZERO;
		/*RWW EEPRM write page buffer*/
		rww_eeprom_emulator_write_buffer(SET_TO_ZERO,
				(const uint8_t *)&memory_index, LENGTH_OF_MEMORY_INDEX);
		/*RWW EEPRM commit page buffer*/
		rww_eeprom_emulator_commit_page_buffer();
	}
}

/**
* \brief  Enables tamper after read operation
*
* This function enables the tamper in previous operating mode after read 
* operation
*
*/
void enable_tamper(void)
{
	/*checks whether previous mode is capture mode*/
	if(previous_mode == SET_TO_CAPTURE)
		/*enable tamper in capture mode*/
		configure_tamper_capture_mode();

	/*checks whether previous mode is wake mode*/
	if(previous_mode == SET_TO_WAKE)
		/*enable tamper in wake mode*/
		configure_tamper_wake_mode();
}

int main(void)
{
	/*initialize the key input from user*/
	uint16_t key = 0;

	/*system_init*/
	system_init();

	/*setup_bod*/
	configure_bod();

	/*setup_init*/
	configure_eeprom();

	/*Configure and enable RTC */
	configure_rtc_calendar();

	/*configure RTC callback*/
	configure_rtc_callbacks();

	/*configure current time to RTC*/
	configure_rtc_calender_time();

	/*configure TCC*/
	configure_tcc();

	/*configure TCC callback*/
	configure_tcc_callbacks();

	/*configure usart*/
	configure_usart();

	/* Initialize SLCD*/
	lcd_init();

	/*configure the memory index for tamper history storage*/
	memory_index_init();

	/*enable_global_interrupts*/
	system_interrupt_enable_global();

	/*Display menu*/
	display_menu();

	/* while*/
	while (1) {
		/*checks whether key is pressed*/
		if(!usart_read_wait(&usart_instance, &key)) {
			printf("\r\nKey Entered: %c\r\n", key);
			switch (key) {
			case DISABLE_TAMPER:
				/*enable tamper in capture mode*/
				configure_tamper_off_mode();
				break;

			case ENABLE_TAMPER_IN_WAKE_MODE:
				/*enable tamper in wake mode*/
				configure_tamper_wake_mode();
				/*enable standby sleep mode*/
				system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
				/*put the device in sleep*/
				system_sleep();
				break;

			case ENABLE_TAMPER_IN_CAPTURE_MODE:
				/*enable tamper in capture mode*/
				configure_tamper_capture_mode();
				/*enable standby sleep mode*/
				system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
				/*put the device in sleep*/
				system_sleep();
				break;

			case READ_TAMPER_HISTORY:
				/*read RWW EEPROM memory*/
				read_tamper_history();
				break;

			case ERASE_TAMPER_HISTORY:
				/*erase RWW EEPROM memory*/
				erase_tamper_history();
				break;

			default:
				break;
			}
		}
		/*checks for the tamper occurrence*/
		if(tamper_flag == true) {
			/*checks whether capture or wake mode*/
			if(mode == SET_TO_CAPTURE) {
				rtc_tamper_get_stamp(&rtc_instance, &tamper_time);
				printf("\r\nTamper occurred at[HH:MM:SS] = [%02d:%02d:%02d]%s\r\n",
					   tamper_time.hour, tamper_time.minute, tamper_time.second,
					   tamper_time.pm?"PM":"AM");
				lcd_display_time();
				write_tamper_data();
				/*clear tamper flag*/
				tamper_flag = false;
			} else {
				printf("\r\nTamper occurred.\n\r");
				/*displays the tamper error message on SLCD*/
				xpro_lcd_show_text(ERROR_STRING);
				/*clear tamper flag*/
				tamper_flag = false;
			}
		}
	}
}
