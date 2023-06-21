/*
 * \file
 *
 * \brief SAM Low Power Application
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
 * \mainpage SAM Low Power Application
 * See \ref appdoc_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 *
 * \page appdoc_preface Overview
 * This example demonstrates different sleep modes and
 * performance level feature.
 */

/**
 * \page appdoc_main SAM Low Power Application
 *
 * Overview:
 * - \ref appdoc_sam0_low_power_intro
 * - \ref appdoc_sam0_low_power_setup
 * - \ref appdoc_sam0_low_power_imp
 * - \ref appdoc_sam0_low_power_compinfo
 * - \ref appdoc_sam0_low_power_contactinfo
 *
 * \section appdoc_sam0_low_power_intro Introduction
 * This application demonstrates different sleep modes and performance levels, it can
 * switch among ACTIVE mode, IDLE mode, STANDBY mode and BACKUP mode.
 *
 * This application has been tested on following boards:
 * - SAM L22  Xplained Pro
 * 
 * \section appdoc_sam0_low_power_setup Hardware Setup
 * 
 * BUTTON0(EIC interrupt) is used to wake up system from standby mode and IDLE mode.
 * RTC is used to wake up system from BACKUP mode,
 * The power consumption can be measured in data visualizer tool
 * 
 * I/O jumper - BYPASS  
 * MCU jumper - MEASURE
 * VBAT SELECT jumper - OPEN 
 * \section appdoc_sam0_low_power_imp Implementation Details
 *
 * The application covers the following case:
 * Case 1: ACTIVE mode: Performance Level 0 at 8 MHz
 * Case 2: ACTIVE mode: Performance Level 2 at 24 MHz
 * Case 3: IDLE mode: Performance Level 0 at 8 MHz
 * Case 4: STANDBY mode 
 * Case 5: BACKUP mode
 * Case 6: OFF mode
 * 
 *
 * When in active Performance Level 2 mode, DFLL48M using XOSC32K as reference and running at 24 MHz.
 * When in active Performance Level 0 mode, internal Multi RC Oscillator running at 8 MHz.
 * When 'debug_enable' user constant is enabled ,EDBG can be used to input command to select different modes.
 *
 * IDLE and STANDBY modes can be waked up by BUTTON0 - SW0 in the SAML22 xplained pro.
 * BACKUP mode can be waked up by 5 second RTC time out.
 * OFF mode can only exit if the RESET pin is activated.
 * 
 * \section appdoc_sam0_low_power_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_low_power_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */
 /**
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <string.h>
#include <asf.h>
#include "reset.h"
#include "conf_app.h"

void rtc_overflow_callback(void);
void configure_rtc_count(void);
void configure_rtc_callbacks(void);

static struct usart_module usart_instance;
static struct rtc_module rtc_instance;

#ifdef DEBUG_ENABLE 

/**
 * \brief Configure usart.
 */
static void configure_usart(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate    = CONF_STDIO_BAUDRATE;
	config_usart.mux_setting = CONF_STDIO_MUX_SETTING;
	config_usart.pinmux_pad0 = CONF_STDIO_PINMUX_PAD0;
	config_usart.pinmux_pad1 = CONF_STDIO_PINMUX_PAD1;
	config_usart.pinmux_pad2 = CONF_STDIO_PINMUX_PAD2;
	config_usart.pinmux_pad3 = CONF_STDIO_PINMUX_PAD3;
	stdio_serial_init(&usart_instance, CONF_STDIO_USART, &config_usart);
	usart_enable(&usart_instance);
}

/**
 * \brief Display menu.
 */
static void display_menu(void)
{
	printf("\n\r");
	printf("===============================================\n\r");
	printf("Menu: press a key to continue.\n\r");
	printf("===============================================\n\r");

	printf("  a : ACTIVE mode: Performance Level 0 at 8 MHz\n\r");
	printf("  b : ACTIVE mode: Performance Level 2 at 32 MHz\n\r");
	printf("  c : IDLE mode: Performance Level 0 at 8 MHz\n\r");
	printf("  d : STANDBY mode\n\r");
	printf("  e : BACKUP mode\n\r");
	printf("  f : OFF mode\n\r");
	
	printf("-----------------------------------------------\n\r");
	printf(">>");
}

#endif

/**
 * \external interrupt ISR.
 */
static void extint_callback(void)
{

}

/**
 * \brief Config external interrupt.
 */
static void configure_extint_channel(void)
{
	struct extint_chan_conf config_extint_chan;
	
	extint_chan_get_config_defaults(&config_extint_chan);
	
	config_extint_chan.gpio_pin           = BUTTON_0_EIC_PIN;
	config_extint_chan.gpio_pin_mux       = BUTTON_0_EIC_MUX;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_UP;
	config_extint_chan.detection_criteria = EXTINT_DETECT_BOTH;
	
	extint_chan_set_config(BUTTON_0_EIC_LINE, &config_extint_chan);
	
	extint_register_callback(extint_callback,BUTTON_0_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
 	extint_chan_enable_callback(BUTTON_0_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
	
	while (extint_chan_is_detected(BUTTON_0_EIC_LINE)) 
	{
		extint_chan_clear_detected(BUTTON_0_EIC_LINE);
	}
}

/**
 * \brief Setect OSC16M as main clock source.
 */
static void main_clock_select_osc16m(void)
{
	struct system_gclk_gen_config gclk_conf;
	struct system_clock_source_osc16m_config osc16m_conf;

	/* Switch to new frequency selection and enable OSC16M */
	system_clock_source_osc16m_get_config_defaults(&osc16m_conf);	

	osc16m_conf.fsel = CONF_CLOCK_OSC16M_FREQ_SEL;
	osc16m_conf.on_demand = 0;
	osc16m_conf.run_in_standby = CONF_CLOCK_OSC16M_RUN_IN_STANDBY;
	
	system_clock_source_osc16m_set_config(&osc16m_conf);
	
	system_clock_source_enable(SYSTEM_CLOCK_SOURCE_OSC16M);

	while(!system_clock_source_is_ready(SYSTEM_CLOCK_SOURCE_OSC16M));

	/* Select OSC16M as mainclock */
	system_gclk_gen_get_config_defaults(&gclk_conf);

	gclk_conf.source_clock = SYSTEM_CLOCK_SOURCE_OSC16M;

	system_gclk_gen_set_config(GCLK_GENERATOR_0, &gclk_conf);

	if (CONF_CLOCK_OSC16M_ON_DEMAND) 
	{
		OSCCTRL->OSC16MCTRL.reg |= OSCCTRL_OSC16MCTRL_ONDEMAND;
	}
}

/**
 * \brief Setect DFLL as main clock source.
 */
static void main_clock_select_dfll(void)
{
	struct system_gclk_gen_config gclk_conf;

	/* Select OSCULP32K as new clock source for main clock temporarily */
	system_gclk_gen_get_config_defaults(&gclk_conf);
	
	gclk_conf.source_clock = SYSTEM_CLOCK_SOURCE_XOSC32K;
	
	system_gclk_gen_set_config(GCLK_GENERATOR_0, &gclk_conf);

	/* Select XOSC32K for GCLK1. */
	system_gclk_gen_get_config_defaults(&gclk_conf);
	
	gclk_conf.source_clock = SYSTEM_CLOCK_SOURCE_XOSC32K;
	
	system_gclk_gen_set_config(GCLK_GENERATOR_1, &gclk_conf);
	
	system_gclk_gen_enable(GCLK_GENERATOR_1);

	struct system_gclk_chan_config dfll_gclk_chan_conf;

	system_gclk_chan_get_config_defaults(&dfll_gclk_chan_conf);
	
	dfll_gclk_chan_conf.source_generator = GCLK_GENERATOR_1;
	
	system_gclk_chan_set_config(OSCCTRL_GCLK_ID_DFLL48, &dfll_gclk_chan_conf);
	
	system_gclk_chan_enable(OSCCTRL_GCLK_ID_DFLL48);

	struct system_clock_source_dfll_config dfll_conf;
	system_clock_source_dfll_get_config_defaults(&dfll_conf);

	dfll_conf.loop_mode      = SYSTEM_CLOCK_DFLL_LOOP_MODE_CLOSED;
	dfll_conf.on_demand      = false;
	dfll_conf.run_in_stanby  = CONF_CLOCK_DFLL_RUN_IN_STANDBY;
	dfll_conf.multiply_factor = CONF_CLOCK_DFLL_MULTIPLY_FACTOR;
	
	system_clock_source_dfll_set_config(&dfll_conf);
	
	system_clock_source_enable(SYSTEM_CLOCK_SOURCE_DFLL);
	
	while(!system_clock_source_is_ready(SYSTEM_CLOCK_SOURCE_DFLL));
	
	if (CONF_CLOCK_DFLL_ON_DEMAND) 
	{
		OSCCTRL->DFLLCTRL.bit.ONDEMAND = 1;
	}

	/* Select DFLL for mainclock. */
	system_gclk_gen_get_config_defaults(&gclk_conf);
	
	gclk_conf.division_factor = 2;
	gclk_conf.source_clock = SYSTEM_CLOCK_SOURCE_DFLL;
	
	system_gclk_gen_set_config(GCLK_GENERATOR_0, &gclk_conf);
}

/**
 * \brief Main clock source selection between DFLL and OSC16M.
 */
static void main_clock_select(const enum system_clock_source clock_source)
{
	if (clock_source == SYSTEM_CLOCK_SOURCE_DFLL) 
	{
		main_clock_select_dfll();
		system_clock_source_disable(SYSTEM_CLOCK_SOURCE_OSC16M);
	} 
	else if (clock_source == SYSTEM_CLOCK_SOURCE_OSC16M) 
	{
		main_clock_select_osc16m();
		system_clock_source_disable(SYSTEM_CLOCK_SOURCE_DFLL);
		system_gclk_chan_disable(OSCCTRL_GCLK_ID_DFLL48);
		system_gclk_gen_disable(GCLK_GENERATOR_1);
	} 
	else 
	{
		return ;
	}
}

/**
 * \brief Active mode test case.
 */
static void test_active_mode(const enum system_performance_level performance_level)
{
	enum system_performance_level curr_pl = system_get_performance_level();

	#ifdef DEBUG_ENABLE
	printf("System will switch to PL:%d \r\n",performance_level);
	#endif
	
	if (curr_pl == performance_level) 
	{
		return ;
	}

	if (curr_pl < performance_level) 
	{
		/* Scaling up the performance level first and then increase clock frequency */
		system_switch_performance_level(performance_level);
		main_clock_select(SYSTEM_CLOCK_SOURCE_DFLL);
	} 
	else 
	{
		/* Scaling down clock frequency and then Scaling down the performance level */
		main_clock_select(SYSTEM_CLOCK_SOURCE_OSC16M);
		system_switch_performance_level(performance_level);
	}

	#ifdef  DEBUG_ENABLE 
	usart_reset(&usart_instance);
	configure_usart();
	#endif
}

/**
 * \brief Idle mode test case.
 */
static void test_idle_mode(void)
{
	test_active_mode(SYSTEM_PERFORMANCE_LEVEL_0);
	
	#ifdef DEBUG_ENABLE
	printf("System will enter IDLE mode \r\n");
	#endif
			
	system_set_sleepmode(SYSTEM_SLEEPMODE_IDLE);
	system_sleep();

	#ifdef  DEBUG_ENABLE  
	usart_reset(&usart_instance);
	configure_usart();
	printf("System has woken up from IDLE sleep mode \r\n");
	#endif
}

/**
 * \brief STANDBY mode test case.
*/
static void test_standby_mode(void)
{    
	test_active_mode(SYSTEM_PERFORMANCE_LEVEL_0);
	
	#ifdef DEBUG_ENABLE
	printf("System will enter STANDBY mode \r\n");	
	#endif
		
	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
	system_sleep();		
	
	#ifdef  DEBUG_ENABLE 
	usart_reset(&usart_instance);
	configure_usart();	
	printf("System has woken up from STAND BY sleep mode \r\n");
	#endif
}

/**
 * \RTC ISR.
 */
void rtc_overflow_callback(void)
{

}

/**
 * \brief rtc module initialization.
*/
void configure_rtc_count(void)
{
	struct rtc_count_config config_rtc_count;

	rtc_count_get_config_defaults(&config_rtc_count);

	config_rtc_count.prescaler           = RTC_COUNT_PRESCALER_DIV_1;
	config_rtc_count.mode                = RTC_COUNT_MODE_16BIT;

	#ifdef FEATURE_RTC_CONTINUOUSLY_UPDATED
	config_rtc_count.continuously_update = true;
	#endif

	rtc_count_init(&rtc_instance, RTC, &config_rtc_count);
	rtc_count_enable(&rtc_instance);
}

/**
 * \brief setup rtc callback.
*/
void configure_rtc_callbacks(void)
{
	rtc_count_register_callback(
	&rtc_instance, rtc_overflow_callback, RTC_COUNT_CALLBACK_OVERFLOW);

	rtc_count_enable_callback(&rtc_instance, RTC_COUNT_CALLBACK_OVERFLOW);
}

/**
 * \brief BACKUP mode test case.
 */
static void test_backup_mode(void)
{
	system_apb_clock_clear_mask(SYSTEM_CLOCK_APB_APBC, MCLK_APBCMASK_SERCOM4);
	system_gclk_chan_disable(SERCOM0_GCLK_ID_CORE + 4);

	struct port_config pin_conf;

	port_get_config_defaults(&pin_conf);

	pin_conf.direction = PORT_PIN_DIR_OUTPUT;

	port_pin_set_config(CONF_STDIO_PAD0_PIN, &pin_conf);
	port_pin_set_config(CONF_STDIO_PAD1_PIN, &pin_conf);

    /* RTC - 5 seconds - wake up source */
	configure_rtc_count();
	configure_rtc_callbacks();
	rtc_count_set_period(&rtc_instance, CONF_RTC_WAKEUP);

	system_set_sleepmode(SYSTEM_SLEEPMODE_BACKUP);
	system_sleep();		
}

/**
 * \brief OFF mode test case.
 */
static void test_off_mode(void)
{
	/* Enter OFF mode */
	system_set_sleepmode(SYSTEM_SLEEPMODE_OFF);
	system_sleep();
}

/**
 * \brief sleep modes menu.
 */
static void test_sleep_mode(uint16_t mode)
{
		switch (mode) 
		{
			case ACTIVE_MODE_PL0:
			test_active_mode(SYSTEM_PERFORMANCE_LEVEL_0);
			break;
			case ACTIVE_MODE_PL2:
			test_active_mode(SYSTEM_PERFORMANCE_LEVEL_2);
			break;
			case IDLE_MODE:
			test_idle_mode();
			break;
			case STANDBY_MODE:
			test_standby_mode();
			break;
			case BACKUP_MODE:
			test_backup_mode();
			break;
			case OFF_MODE:
			test_off_mode();
			break;
			default:
			break;
		}
}

/**
 * \brief main function.
 */
int main(void)
{	
	
	/* Declare regulator configuration structure */
	struct system_voltage_regulator_config reg_conf ;

	/* Initialize the mode to default PL0 level in active mode */
	uint16_t key = ACTIVE_MODE_PL0;
	
	#ifdef UNUSED_GPIO_POWER_SAVE
	/* Declare port regulator configuration */
	struct port_config port_conf;
	port_get_config_defaults(&port_conf);
	
	port_conf.powersave = true;
	
	port_group_set_config(&PORTA,0x3FFFFFFC,&port_conf);
	port_group_set_config(&PORTB,0x3FFFFF0F,&port_conf);
	port_group_set_config(&PORTC,0xF4DFFFFC,&port_conf);
	
	#endif
	
	/* Initialize clock system */
	system_init();

	/* BOD33 disabled */
	SUPC->BOD33.reg &= ~SUPC_BOD33_ENABLE;

	/* VDDCORE is supplied BUCK converter */
	system_voltage_regulator_get_config_defaults(&reg_conf);
	reg_conf.regulator_sel = SYSTEM_VOLTAGE_REGULATOR_BUCK;
	system_voltage_regulator_set_config(&reg_conf);

	#ifdef  DEBUG_ENABLE 
	configure_usart();	
	#endif
	
	/* User button - Wake up source for idle and stand by sleep mode */
	configure_extint_channel();
	
	if (system_get_reset_cause() == SYSTEM_RESET_CAUSE_BACKUP
		&& system_get_backup_exit_source() == SYSTEM_RESET_BACKKUP_EXIT_RTC) 
	{

		#ifdef  DEBUG_ENABLE 
		printf("System has woken up from BACKUP reset\r\n");
		#endif
	}
	
	#ifdef  DEBUG_ENABLE 
		while (true) 
		{
			display_menu();
			
			while (usart_read_wait(&usart_instance, &key)) 
			{
			}
			
			printf("\r\nYou input :%c\r\n",key);
			
			test_sleep_mode(key);

		}
	#else

		key=TEST_ACTIVE_PL0_MODE;
		test_sleep_mode(key);
		
		while(1)
		{
		}
		
	#endif
	
}
