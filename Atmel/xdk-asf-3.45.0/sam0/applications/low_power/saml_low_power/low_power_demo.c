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
 * This example demonstrates different sleep modes, performance level
 * and power gating feature.
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
 * - SAM L21  Xplained Pro
 * - SAM R30  Xplained Pro
 *
 * \section appdoc_sam0_low_power_setup Hardware Setup
 * This application of SAML21 use AIN0(PA02, EXT1 pin10) and
 * SAMR30 use (AIN6(PA06, EXT1 pin3)) as ADC input channel.
 * BUTTON0 is used to wake up system from standby mode and IDLE mode.
 * BUTTON0 is used as an external wake up pin to wake up system from BACKUP mode,
 * the wakeup pin level is low.
 *
 *
 * \section appdoc_sam0_low_power_imp Implementation Details
 *
 * The application covers the following case:
 * Case 1: ACTIVE mode: Performance Level 0 at 12MHz
 * Case 2: ACTIVE mode: Performance Level 2 at 48MHz
 * Case 3: IDLE mode: Performance Level 0 at 12MHz
 * Case 4: STANDBY mode:PD0,PD1 and PD2 in retention state
 * Case 5: BACKUP mode
 * Case 6: OFF mode
 * Case 7: STANDBY mode:dynamic power sleepwalking
 *
 * When in active Performance Level 2 mode, DFLL48M using XOSC32K as reference and running at 48MHz.
 * When in active Performance Level 0 mode, internal Multi RC Oscillator running at 12MHz.
 * In active mode, EDBG can be used to input command to select different modes.
 *
 * IDLE,BACKUP and STANDBY modes can be waked up by BUTTON0.
 * OFF mode can only exit if the RESET pin is activated.
 *
 * In stanby mode(dynamic power sleepwalking), RTC, ADC, EVENT, and DMA modules are used.
 * RTC generates compare value matched EVENT at a fixed interval and route it
 * to ADC, ADC start to sample based on the EVENT, when one conversion is completed,
 * DMA make peripheral-to-memory transfer from the ADC to the HMCRAMLP memory.
 *
 * RTC is clocked by the internal ULP 32kHz oscillator divided by 64, giving a 512Hz input,
 * and the compare value is 1000. ADC is clocked by the 4MHz from OSC16M divided by 64,
 * giving a 64KHz input. So we can observe the consumption during the STANDBY mode.
 *
 * The STANDBY mode takes about 30 seconds, and it covers the following cases:
 * Case 13-1 PD0, PD1 and PD2 all in retention state.
 * Case 13-2 PD0 in active state while PD1 and PD2 in retention state.
 * Case 13-3 PD0 and PD1  in active state while PD2  in retention mode.
 * Case 13-4 PD0, PD1 and PD2 all in active mode, and system wakes up.
 * Case 13-4 PD0, PD1 and PD2 all in active mode, and system wakes up.
 *
 * LED0 is used as an indication for different mode.
 * when GCL0 clock frequency changes, LED0 will toggles \c LED0_TOGGLE_2 times.
 * when exits from IDLE mode, LED0 will toggles \c LED0_TOGGLE_4 times.
 * when exits from STANDBY mode, LED0 will toggles \c LED0_TOGGLE_6 times.
 * when exits from BACKUP mode, LED0 will toggles \c LED0_TOGGLE_8 times.
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
#include "conf_app.h"

/* Module instances */
static struct adc_module adc_instance;
static struct rtc_module rtc_instance;
static struct usart_module usart_instance;
static struct events_resource event;

/* DMA buffer length */
#define BUFFER_LEN 10

/* MCU revision number */
#define _SYSTEM_MCU_REVISION_B 1

/* DMA resource and descriptor */
struct dma_resource example_resource;
COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor SECTION_DMAC_DESCRIPTOR;
static uint16_t adc_rslt[BUFFER_LEN] SECTION_DMAC_DESCRIPTOR;

/**
 * \brief LED0 toggles times.
 */
enum led_toggle_times {
	/* Indication clock frequency switch in ACTIVE mode*/
	LED0_TOGGLE_2 = 2,
	/* Indication system wake up from IDLE mode*/
	LED0_TOGGLE_4 = 4,
	/* Indication system wake up from STANDBY mode*/
	LED0_TOGGLE_6 = 6,
	/* Indication system wake up from BACKUP mode*/
	LED0_TOGGLE_8 = 8,
};

#define LED0_TOGGLE_TIME  200

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
 * \brief Configure RTC as ADC sample timer.
 */
static void configure_rtc(void)
{
	struct rtc_count_config conf;

	rtc_count_get_config_defaults(&conf);

	conf.prescaler         = RTC_COUNT_PRESCALER_DIV_64;
	conf.mode              = RTC_COUNT_MODE_32BIT;
	conf.clear_on_match    = true;
	conf.compare_values[0] = 1000;

	struct rtc_count_events evconfig;
	evconfig.generate_event_on_compare[0] = true;

	rtc_count_init(&rtc_instance, RTC, &conf);
	rtc_count_enable_events(&rtc_instance, &evconfig);
	rtc_count_enable(&rtc_instance);
}

/**
 * \brief Configure EVENT to route RTC events to the ADC.
 */
static void configure_event(void)
{
	struct events_config config;

	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBD,MCLK_APBDMASK_EVSYS);

	events_get_config_defaults(&config);

	config.generator    = EVSYS_ID_GEN_RTC_CMP_0;
	config.path         = EVENTS_PATH_ASYNCHRONOUS;
    config.run_in_standby = true;
    config.on_demand      = true;
	config.clock_source = GCLK_GENERATOR_0;
	events_allocate(&event, &config);

	events_attach_user(&event, EVSYS_ID_USER_ADC_START);
}

/**
 * \brief Configure ADC to sample the internal scaled VCC.
 */
static void configure_adc(void)
{
	struct adc_config config;

	adc_get_config_defaults(&config);
	config.clock_source = GCLK_GENERATOR_0;
	config.clock_prescaler = ADC_CLOCK_PRESCALER_DIV4;
	config.reference = ADC_REFERENCE_INTREF;
	config.event_action = ADC_EVENT_ACTION_START_CONV;
	config.run_in_standby = true;
	config.on_demand = true;
	config.resolution = ADC_RESOLUTION_12BIT;

	adc_init(&adc_instance, ADC, &config);
	adc_enable(&adc_instance);
}

/**
 * \brief DMA callback function for transfer complete.
 */
static void dma_callback(void)
{
	printf("DMA interrupt occurs\r\n");
}

/**
 * \brief Config DMA to make peripheral-to-memory transfer from the ADC to the HMCRAMLP memory.
 */
static void configure_dma(void)
{
	struct dma_resource_config config;
	dma_get_config_defaults(&config);

	config.peripheral_trigger = ADC_DMAC_ID_RESRDY;
	config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
	config.run_in_standby = true;
	dma_allocate(&example_resource, &config);

	struct dma_descriptor_config descriptor_config;

	dma_descriptor_get_config_defaults(&descriptor_config);

	descriptor_config.beat_size = DMA_BEAT_SIZE_HWORD;
	descriptor_config.src_increment_enable = false;
	descriptor_config.block_transfer_count = BUFFER_LEN;
	descriptor_config.source_address = (uint32_t)(&adc_instance.hw->RESULT.reg);
	descriptor_config.destination_address = (uint32_t)adc_rslt + 2*BUFFER_LEN;
	descriptor_config.next_descriptor_address = ( uint32_t )&example_descriptor;
	dma_descriptor_create(&example_descriptor, &descriptor_config);

	dma_add_descriptor(&example_resource, &example_descriptor);

	dma_register_callback(&example_resource, (dma_callback_t)dma_callback, DMA_CALLBACK_TRANSFER_DONE);
    dma_enable_callback(&example_resource,DMA_CALLBACK_TRANSFER_DONE);
	dma_start_transfer_job(&example_resource);
}

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
	while (extint_chan_is_detected(BUTTON_0_EIC_LINE)) {
		extint_chan_clear_detected(BUTTON_0_EIC_LINE);
	}
}

/**
 * \brief Toggles LED as an indication.
 */
static void led_toggle_indication(uint32_t count)
{
	for (uint32_t i = 0; i < count; i++) {
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		delay_ms(LED0_TOGGLE_TIME);
		port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
		delay_ms(LED0_TOGGLE_TIME);
	}
	port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
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
	if (CONF_CLOCK_OSC16M_ON_DEMAND) {
		OSCCTRL->OSC16MCTRL.reg |= OSCCTRL_OSC16MCTRL_ONDEMAND;
	}

}

/**
 * \brief Setect DFLL as main clock source.
 */
static void main_clock_select_dfll(void)
{
	struct system_gclk_gen_config gclk_conf;

	/* Select OSCULP32K as new clock source for mainclock temporarily */
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
	if (CONF_CLOCK_DFLL_ON_DEMAND) {
		OSCCTRL->DFLLCTRL.bit.ONDEMAND = 1;
	}

	/* Select DFLL for mainclock. */
	system_gclk_gen_get_config_defaults(&gclk_conf);
	gclk_conf.source_clock = SYSTEM_CLOCK_SOURCE_DFLL;
	system_gclk_gen_set_config(GCLK_GENERATOR_0, &gclk_conf);

}

/**
 * \brief Main clock source selection between DFLL and OSC16M.
 */
static void main_clock_select(const enum system_clock_source clock_source)
{
	if (clock_source == SYSTEM_CLOCK_SOURCE_DFLL) {
		main_clock_select_dfll();
		system_clock_source_disable(SYSTEM_CLOCK_SOURCE_OSC16M);
	} else if (clock_source == SYSTEM_CLOCK_SOURCE_OSC16M) {
		main_clock_select_osc16m();
		system_clock_source_disable(SYSTEM_CLOCK_SOURCE_DFLL);
		system_gclk_chan_disable(OSCCTRL_GCLK_ID_DFLL48);
		system_gclk_gen_disable(GCLK_GENERATOR_1);
	} else {
		return ;
	}
}

/**
 * \brief Active mode test case.
 */
static void test_active_mode(const enum system_performance_level performance_level)
{

	enum system_performance_level curr_pl = system_get_performance_level();

	printf("System will switch to PL:%d \r\n",performance_level);
	if (curr_pl == performance_level) {
		return ;
	}

	if (curr_pl < performance_level) {

		/* Scaling up the performance level first and then increase clock frequency */
		system_switch_performance_level(performance_level);
		main_clock_select(SYSTEM_CLOCK_SOURCE_DFLL);

	} else {
		/* Scaling down clock frequency and then Scaling down the performance level */
		main_clock_select(SYSTEM_CLOCK_SOURCE_OSC16M);
		system_switch_performance_level(performance_level);
	}

	/* Toggles LED0 once clock frequency successfully */
	led_toggle_indication(LED0_TOGGLE_2);
}

/**
 * \brief Idle mode test case.
 */
static void test_idle_mode(void)
{
	printf("Warning:System will enter IDLE mode,please wait until LED0 becomes OFF \r\n");
	test_active_mode(SYSTEM_PERFORMANCE_LEVEL_0);
	port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
	system_set_sleepmode(SYSTEM_SLEEPMODE_IDLE);
	system_sleep();

    /* Toggles LED0 once wake up from IDLE sleep mode */
	led_toggle_indication(LED0_TOGGLE_4);
}

/**
 * \brief STANDBY mode test case:Dynamic Power SleepWalking.
 */
static void test_standby_mode_dynamic_power_sleepwalking(void)
{
	/* Get MCU revision */
	uint32_t rev = system_get_device_id();

	rev &= DSU_DID_REVISION_Msk;
	rev = rev >> DSU_DID_REVISION_Pos;

	printf("System will enter STANDBY mode:Dynamic Power SleepWalking\r\n");

	/* When entering standby mode, the FDPLL is still running even if not
	 *	requested by any module causing extra consumption. Errata reference:12244
	 */
	if (rev < _SYSTEM_MCU_REVISION_B) {
		test_active_mode(SYSTEM_PERFORMANCE_LEVEL_0);
	}

	memset(adc_rslt, 0, sizeof(adc_rslt));
	configure_event();
	configure_adc();
	configure_dma();
	configure_rtc();

	struct system_standby_config config;
	system_standby_get_config_defaults(&config);
	config.enable_dpgpd0 = true;
	config.enable_dpgpd1 = true;
	config.power_domain = SYSTEM_POWER_DOMAIN_DEFAULT;

	/* Errata 13599:
	 * In Standby mode, when Power Domain 1 is power gated,
	 * devices can show higher consumption than expected.
	*/
	if (rev < _SYSTEM_MCU_REVISION_B) {
		config.power_domain = SYSTEM_POWER_DOMAIN_PD01;
	}

	system_standby_set_config(&config);

	/* Errata 13901:
	 * In standby mode, when running modules from GCLK clock with 32Khz source,
	 * the main voltage regulator is used instead of the low power regulator,
	 * causing higher power consumption.
	*/
	if (rev < _SYSTEM_MCU_REVISION_B) {
		if (system_get_performance_level() == SYSTEM_PERFORMANCE_LEVEL_0) {
			uint32_t *const tmp = (void *)(0x4000141C);
			*tmp |= (1 << 8);
		}
	}
	dma_start_transfer_job(&example_resource);

	port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
	system_sleep();

	system_clock_source_enable(SYSTEM_CLOCK_SOURCE_XOSC32K);
	usart_reset(&usart_instance);
	configure_usart();

	printf("System wake up from stanby mode, ADC result\r\n");
	for (int i = 0; i < BUFFER_LEN; i ++) {
		printf("%d ",adc_rslt[i]);
	}
	printf("\r\n");

	/* Toggles LED0  once wake up from STANDBY sleep mode */
	led_toggle_indication(LED0_TOGGLE_6);

	/* Errata 13901:
	 * In standby mode, when running modules from GCLK clock with 32Khz source,
	 * the main voltage regulator is used instead of the low power regulator,
	 * causing higher power consumption.
	*/
	if (rev < _SYSTEM_MCU_REVISION_B) {
		if (system_get_performance_level() == SYSTEM_PERFORMANCE_LEVEL_0) {
			uint32_t *const tmp = (void *)(0x4000141C);
			*tmp &= ~(1 << 8);
		}
	}

}

/**
 * \brief STANDBY mode test case: static power sleepwalking.
*/
static void test_standby_mode_static_power_sleepwalking(void)
{
	/* Get MCU revision */
	uint32_t rev = system_get_device_id();

	rev &= DSU_DID_REVISION_Msk;
	rev = rev >> DSU_DID_REVISION_Pos;

	printf("System will enter STANDBY mode:static power sleepwalking.\r\n");

	/* When entering standby mode, the FDPLL is still running even if not
	 *	requested by any module causing extra consumption. Errata reference:12244
	 */
	if (rev < _SYSTEM_MCU_REVISION_B) {
		test_active_mode(SYSTEM_PERFORMANCE_LEVEL_0);
	}

	system_clock_source_disable(SYSTEM_CLOCK_SOURCE_XOSC32K);

	/*
		When VDDCORE is supplied by the BUCK converter in performance
		level 0, the chip cannot wake-up from standby mode because the
		VCORERDY status is stuck at 0. Errata reference: 13551
	*/
	if (rev < _SYSTEM_MCU_REVISION_B) {
		SUPC->VREG.bit.SEL = SUPC_VREG_SEL_LDO_Val;
	}

	struct system_standby_config config;
	system_standby_get_config_defaults(&config);
	config.enable_dpgpd0       = false;
	config.enable_dpgpd1       = false;
	config.power_domain        = SYSTEM_POWER_DOMAIN_DEFAULT;
#if (SAML21XXXB) || (SAMR30)
	config.vregs_mode          = SYSTEM_SYSTEM_VREG_SWITCH_AUTO;
#else
	config.disable_avregsd     = false;
#endif
	config.linked_power_domain = SYSTEM_LINKED_POWER_DOMAIN_DEFAULT;
	config.hmcramchs_back_bias = SYSTEM_RAM_BACK_BIAS_STANDBY_OFF;
	config.hmcramclp_back_bias = SYSTEM_RAM_BACK_BIAS_STANDBY_OFF;

	system_standby_set_config(&config);

	/* Errata 13901:
	 * In standby mode, when running modules from GCLK clock with 32Khz source,
	 * the main voltage regulator is used instead of the low power regulator,
	 * causing higher power consumption.
	*/
	if (rev < _SYSTEM_MCU_REVISION_B) {
		if (system_get_performance_level() == SYSTEM_PERFORMANCE_LEVEL_0) {
			uint32_t *const tmp = (void *)(0x4000141C);
			*tmp |= (1 << 8);
		}
	}

	port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);
	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
	system_sleep();

	system_clock_source_enable(SYSTEM_CLOCK_SOURCE_XOSC32K);

	usart_reset(&usart_instance);
	configure_usart();

	printf("System wake up from stanby mode\r\n");

	/* Toggles LED0  once wake up from STANDBY sleep mode */
	led_toggle_indication(LED0_TOGGLE_6);

	/* Errata 13901:
	 * In standby mode, when running modules from GCLK clock with 32Khz source,
	 * the main voltage regulator is used instead of the low power regulator,
	 * causing higher power consumption.
	*/
	if (rev < _SYSTEM_MCU_REVISION_B) {
		if (system_get_performance_level() == SYSTEM_PERFORMANCE_LEVEL_0) {
			uint32_t *const tmp = (void *)(0x4000141C);
			*tmp &= ~(1 << 8);
		}
	}

	SUPC->VREG.bit.SEL = SUPC_VREG_SEL_BUCK_Val;
}

/**
 * \brief BACKUP mode test case.
 */
static void test_backup_mode(void)
{

	system_apb_clock_clear_mask(SYSTEM_CLOCK_APB_APBC, MCLK_APBCMASK_SERCOM3);
	system_gclk_chan_disable(SERCOM0_GCLK_ID_CORE + 3);

	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);

	pin_conf.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(CONF_STDIO_PAD0_PIN, &pin_conf);
	port_pin_set_config(CONF_STDIO_PAD1_PIN, &pin_conf);

	port_pin_set_output_level(LED_0_PIN, LED_0_INACTIVE);

	/* Set external wakeup pin polarity */
	system_set_pin_wakeup_polarity_low(1 << CONF_EXT_WAKEUP_PIN);

	/* Set external wakeup detector */
	system_enable_pin_wakeup(1 << CONF_EXT_WAKEUP_PIN);
	system_set_pin_wakeup_debounce_counter(SYSTEM_WAKEUP_DEBOUNCE_2CK32);
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
 * \brief Display menu.
 */
static void display_menu(void)
{
	printf("\n\r");
	printf("===============================================\n\r");
	printf("Menu: press a key to continue.\n\r");
	printf("===============================================\n\r");

	printf("  a : ACTIVE mode: Performance Level 0 at 12MHz\n\r");
	printf("  b : ACTIVE mode: Performance Level 2 at 48MHz\n\r");
	printf("  c : IDLE mode: Performance Level 0 at 12MHz\n\r");
	printf("  d : STANDBY mode:PD0,PD1 and PD2 in retention state\n\r");
	printf("  e : BACKUP mode\n\r");
	printf("  f : OFF mode\n\r");
	printf("  q : Enter dynamic power gating example\n\r");

	printf("-----------------------------------------------\n\r");
	printf(">>");
}


int main(void)
{

	uint16_t key = 0;

	/* Initialize clock system */
	system_init();

	/* BOD33 disabled */
	SUPC->BOD33.reg &= ~SUPC_BOD33_ENABLE;
#ifndef SAMR30
	/* VDDCORE is supplied BUCK converter */
	SUPC->VREG.bit.SEL = SUPC_VREG_SEL_BUCK_Val;
#endif
	delay_init();
	configure_usart();
	configure_extint_channel();

	/* Turn LED0 ON */
	port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);

	if (system_get_reset_cause() == SYSTEM_RESET_CAUSE_BACKUP
		&& system_get_backup_exit_source() == SYSTEM_RESET_BACKKUP_EXIT_EXTWAKE
		&& (system_get_pin_wakeup_cause() & (1 << CONF_EXT_WAKEUP_PIN))){

		printf("System wake up from BACKUP reset\r\n");
		/* Toggles LED0 once wake up from BACKUP sleep mode */
		led_toggle_indication(LED0_TOGGLE_8);
	}

	while (true) {
		display_menu();
		while (usart_read_wait(&usart_instance, &key)) {
		}
		printf("\r\nYou input :%c\r\n",key);
		switch (key) {
		case 'a':
			test_active_mode(SYSTEM_PERFORMANCE_LEVEL_0);
			break;
		case 'b':
			test_active_mode(SYSTEM_PERFORMANCE_LEVEL_2);
			break;
		case 'c':
			test_idle_mode();
			break;
		case 'd':
			test_standby_mode_static_power_sleepwalking();
			break;
		case 'e':
			test_backup_mode();
			break;
		case 'f':
			test_off_mode();
			break;
		default:
			break;
		}
		if (key == 'q') {
			break;
		}
		usart_reset(&usart_instance);
		configure_usart();
	}

	test_standby_mode_dynamic_power_sleepwalking();

	while(1) {
		;
	}
}
