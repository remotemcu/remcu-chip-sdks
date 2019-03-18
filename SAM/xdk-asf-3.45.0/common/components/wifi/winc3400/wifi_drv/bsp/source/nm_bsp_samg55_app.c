/**
 *
 * \file
 *
 * \brief This module contains SAMG55 BSP APIs implementation.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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

#include "bsp/include/nm_bsp_samg55_app.h"
#include "common/include/nm_common.h"

#define BSP_MIN(x,y) ((x)>(y)?(y):(x))


#define SW1_PIN
#define SW1_MUX
#define SW1_LINE 

#ifdef WING_BOARD_WITH_LEDS_BUTTON
#define SW2_LINE	    3
#define SW2_PIN			PIN_PB03
#define SW2_MUX			MUX_PB03A_EIC_EXTINT3
#endif /* WING_BOARD_WITH_LEDS_BUTTON */

/*
   ---------------------------------
   ------ Module Pin Settings ------
   ---------------------------------
*/

#define LONG_PRESS_TIME			500//(1500/TICK_RES)	// ~2 sec
#define DEBOUNCE_TIME			(40/TICK_RES)	// ~50ms


#define SHORT_PRESS_DEBOUNCE	(800/TICK_RES) // ~ 0.8s
#define LONG_PRESS_DEBOUNCE		(1500/TICK_RES) // ~ 1.5s

#if (0 == SHORT_PRESS_DEBOUNCE)
#undef SHORT_PRESS_DEBOUNCE
#define SHORT_PRESS_DEBOUNCE 1
#endif

/*
* Structure
*
*/
typedef struct
{
	tpfNmBspTimerCb	pfCb;
	uint32 u32Timeout;
	uint32 u32Period;
} tstrTimer;


typedef struct
{
	tstrTimer strTimer;
	uint8 u8Enabled;
} tstrWakeTimer;
/**
*
* Global variables
*/
uint32 gu32Jiffies1ms;
uint32 gu32Jiffies20ms;
typedef void (*tick_timer_cb_t)(void);
static tick_timer_cb_t tick_timer_cb = NULL;
volatile uint32_t ms_ticks = 0;

static uint16 gu16Btn1Cnt, gu16Btn2Cnt;
static tpfNmBspBtnPress gpfBtns;
static uint8 gu8BtnIfg;
static tstrTimer gstrTimer20ms, gstrTimer1ms, gstrConfigurableTimer;
#if (defined _STATIC_PS_)||(defined _DYNAMIC_PS_)
static tstrWakeTimer gstrWakeTimer;
#endif

static void btn_isr(uint32 ul_id, uint32 ul_mask);

#if !defined(__DAMD21J18A__)
struct tcc_module {
	/** Hardware module pointer of the associated Timer/Counter peripheral. */
	void *hw;

	#  ifdef TCC_ASYNC
	/** Array of callbacks. */
	tcc_callback_t callback[TCC_CALLBACK_N];
	/** Bit mask for callbacks registered. */
	uint32_t register_callback_mask;
	/** Bit mask for callbacks enabled. */
	uint32_t enable_callback_mask;
	#  endif

	/** Set to \c true to write to buffered registers. */
	bool double_buffering_enabled;
};
#endif

struct tcc_module tcc_instance;
struct tcc_module configurable_tcc;
/**
*
* Static functions
*/

static void btn_poll(void)
{
	bool btn_inactive;
		if (gu8BtnIfg & SW1) {
		gu16Btn1Cnt++;
	
	btn_inactive = ioport_get_pin_level(BUTTON_0_PIN);
	
		if (gu16Btn1Cnt >= SHORT_PRESS_DEBOUNCE) {
			
			if(btn_inactive == BUTTON_0_INACTIVE)
			{
				gpfBtns(SW1, 0); /* Short press callback */
				gu16Btn1Cnt = 0;
			} else {
				if (gu16Btn1Cnt >= LONG_PRESS_DEBOUNCE) {

					gpfBtns(SW1, 1); /* long press callback */
					gu16Btn1Cnt = 0;
				}
			}
		}
	}

#ifdef WING_BOARD_WITH_LEDS_BUTTON
	if (gu8BtnIfg & SW2) {
		gu16Btn2Cnt++;

		if (gu16Btn2Cnt >= SHORT_PRESS_DEBOUNCE) {
			if (ioport_get_pin_level(SW2_PIN) == BUTTON_0_INACTIVE) {
				gpfBtns(SW2, 0); /* Short press callback */
				gu16Btn2Cnt = 0;
			} else {
				if (gu16Btn2Cnt >= LONG_PRESS_DEBOUNCE) {
					gpfBtns(SW2, 1); /* long press callback */
					gu16Btn2Cnt = 0;
				}
			}
		}
	}
#endif /* WING_BOARD_WITH_LEDS_BUTTON */

	if(!gu16Btn1Cnt)
	{
		gu8BtnIfg &= ~SW1;
		//extint_chan_enable_callback(BUTTON_0_EIC_LINE,
		//EXTINT_CALLBACK_TYPE_DETECT);
	}
#ifdef WING_BOARD_WITH_LEDS_BUTTON
	if (!gu16Btn2Cnt) {
		gu8BtnIfg &= ~SW2;
		//extint_chan_enable_callback(SW2_LINE,
		//EXTINT_CALLBACK_TYPE_DETECT);
	}
#endif /* WING_BOARD_WITH_LEDS_BUTTON */
}

void SysTick_Handler(void)
{
	ms_ticks++;

	//while (timers && ((ms_ticks -  timers->timeout) & 0x80000000)) {
	//	timers->cb();
	//	timers = timers->next;
	//}

	if (tick_timer_cb) {
		tick_timer_cb();
	}
}
static void _tcc_callback_to_change_duty_cycle(void)
{
	gu32Jiffies1ms++;
	if(gstrTimer1ms.pfCb)
		gstrTimer1ms.pfCb();

	if(gu32Jiffies1ms%20 == 0)
	{
#ifdef _STATIC_PS_
		if((gstrWakeTimer.strTimer.pfCb)&&(gstrWakeTimer.u8Enabled))
		{
			gu32Jiffies20ms+=(TICK_RES_SLEEP/TICK_RES);
		}
else
#endif
		{
			gu32Jiffies20ms++;
		}
#ifdef _STATIC_PS_
		if(gstrWakeTimer.strTimer.pfCb)
		{
			if(NM_BSP_TIME_MSEC >= gstrWakeTimer.strTimer.u32Timeout)
			{
				nm_bsp_wake_ctrl(0);
				gstrWakeTimer.strTimer.pfCb();
				gstrWakeTimer.strTimer.u32Timeout = NM_BSP_TIME_MSEC + gstrWakeTimer.strTimer.u32Period;
			}
		}
#endif
		if(gstrTimer20ms.pfCb)
		{
			if(NM_BSP_TIME_MSEC >= gstrTimer20ms.u32Timeout)
			{
				gstrTimer20ms.pfCb();
				gstrTimer20ms.u32Timeout = NM_BSP_TIME_MSEC + gstrTimer20ms.u32Period;
			}
		}
		btn_poll();		
	}
}

/*
*	@fn			_tcc_configurable_timer_callback
*	@brief		Configurable Timer Callback
*	@date		08 October 2015
*	@version	1.0
*/
#ifdef ENABLE_TIMER_CALLBACK
static void _tcc_configurable_timer_callback(struct tcc_module *const module_inst)
{
	if(gstrConfigurableTimer.pfCb)
		gstrConfigurableTimer.pfCb();
}
#endif

static void timer0_init(void)
{
	tick_timer_cb = _tcc_callback_to_change_duty_cycle;
}

/*
*	@fn			configurable_timer_init
*	@brief		Initialize the Configurable Timer
*	@date		08 October 2015
*	@version	1.0
*/

static void configurable_timer_init(uint32_t u32Period)
{
}


static void btn_isr(uint32 ul_id, uint32 ul_mask)
{
		gu8BtnIfg |= SW1;
		//extint_chan_disable_callback(BUTTON_0_EIC_LINE,
		//EXTINT_CALLBACK_TYPE_DETECT);
}

#ifdef WING_BOARD_WITH_LEDS_BUTTON
static void btn2_isr(void)
{
#if defined(__DAMD21J18A__)
	gu8BtnIfg |= SW2;
	extint_chan_disable_callback(SW2_LINE,
	EXTINT_CALLBACK_TYPE_DETECT);
#endif
}
#endif /* WING_BOARD_WITH_LEDS_BUTTON */

/*
*	@fn		nm_bsp_init
*	@brief	Initialize BSP
*	@return	0 in case of success and -1 in case of failure
*	@author	M.S.M
*	@date	11 July 2012
*	@version	1.0
*/
sint8 nm_bsp_app_init(void)
{
	gstrTimer20ms.pfCb = NULL;
	gstrTimer20ms.u32Timeout = 0;
	gstrTimer20ms.u32Period = 0;

#ifdef _STATIC_PS_
	gstrWakeTimer.strTimer.pfCb = NULL;
	gstrWakeTimer.strTimer.u32Timeout = 0;
	gstrWakeTimer.strTimer.u32Period = ((uint32)-1);
	gstrWakeTimer.u8Enabled = 0;
#endif

	gstrTimer1ms.pfCb = NULL;
	gstrTimer1ms.u32Timeout = 0;
	gstrTimer1ms.u32Period = 0;
	
	gstrConfigurableTimer.pfCb = NULL;
	gstrConfigurableTimer.u32Timeout = 0;
	gstrConfigurableTimer.u32Period = 0;
		
	timer0_init();
	
	return M2M_SUCCESS;
}

/*
*	@fn			nm_bsp_app_configurable_timer_init
*	@brief		Initialize the Configurable Timer
*	@date		08 October 2015
*	@version	1.0
*/
void nm_bsp_app_configurable_timer_init(uint32_t u32Period)
{
	configurable_timer_init(u32Period);	
}

/**
*	@fn		nm_bsp_deinit
*	@brief	De-iInitialize BSP
*	@return	0 in case of success and -1 in case of failure
*	@author	
*	@date	
*	@version	1.0
*/
sint8 nm_bsp_app_deinit(void)
{
	return M2M_SUCCESS;
}

/*
*	@fn		nm_bsp_btn_init
*	@brief	Initialize buttons driver
*	@author	M.S.M
*	@date	28 OCT 2013
*	@version	1.0
*/
#define PIN_PUSHBUTTON_1_ATTR_LOCAL PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE

void nm_bsp_btn_init(tpfNmBspBtnPress pfBtnCb)
{
	
	//struct extint_chan_conf config_extint_chan;
		
	gpfBtns = pfBtnCb;
	gu8BtnIfg = 0;
	gu16Btn1Cnt = 0;
	gu16Btn2Cnt = 0;
	
	/* Configure Pushbutton 1. */
	pmc_enable_periph_clk(PIN_PUSHBUTTON_1_ID);
	pio_set_debounce_filter(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_MASK, 200);
	pio_handler_set(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_ID,
			PIN_PUSHBUTTON_1_MASK, PIN_PUSHBUTTON_1_ATTR_LOCAL, btn_isr);
	NVIC_EnableIRQ((IRQn_Type) PIN_PUSHBUTTON_1_ID);
	pio_handler_set_priority(PIN_PUSHBUTTON_1_PIO, (IRQn_Type) PIN_PUSHBUTTON_1_ID, 0);
	pio_enable_interrupt(PIN_PUSHBUTTON_1_PIO, PIN_PUSHBUTTON_1_MASK);

	//ioport_set_pin_dir(BUTTON_0_PIN, IOPORT_DIR_INPUT);
	//ioport_set_pin_mode(BUTTON_0_PIN, IOPORT_MODE_PULLUP);		
	//ioport_set_pin_level(BUTTON_0_PIN, false);
	
}

/*
*	@fn		nm_bsp_uart_sendnm_bsp_uart_send
*	@author	M.S.M
*	@date	28 OCT 2013
*	@version	1.0
*/
void nm_bsp_uart_send(const uint8 *pu8Buf, uint16 u16Sz)
{
}

/**
*	@fn		nm_bsp_start_timer
*	@brief	Start 20ms timer
*	@author	M.S.M
*	@date	28 OCT 2013
*	@version	1.0
*/
void nm_bsp_start_timer(tpfNmBspTimerCb pfCb, uint32 u32Period)
{
	gstrTimer20ms.pfCb = pfCb;
	gstrTimer20ms.u32Timeout = u32Period+ NM_BSP_TIME_MSEC;
	gstrTimer20ms.u32Period = u32Period;
}

/*
*	@fn			nm_bsp_start_1ms_timer
*	@brief		Start 1ms timer
*	@date		08 October 2015
*	@version	1.0
*/
void nm_bsp_start_1ms_timer(tpfNmBspTimerCb pfCb)
{
	gstrTimer1ms.pfCb = pfCb;
}

/*
*	@fn			nm_bsp_start_configurable_timer
*	@brief		Start configurable timer
*	@date		08 October 2015
*	@version	1.0
*/
void nm_bsp_start_configurable_timer(tpfNmBspTimerCb pfCb)
{
}

/**
*	@fn		nm_bsp_stop_timer
*	@brief	Start 20ms timer
*	@author	M.S.M
*	@date	28 OCT 2013
*	@version	1.0
*/
void nm_bsp_stop_timer(void)
{
	gstrTimer20ms.pfCb = NULL;
}

/*
*	@fn			nm_bsp_stop_1ms_timer
*	@brief		Stop 1ms timer
*	@date		08 October 2015
*	@version	1.0
*/
void nm_bsp_stop_1ms_timer(void)
{
	gstrTimer1ms.pfCb = NULL;
}

/*
*	@fn			nm_bsp_stop_configurable_timer
*	@brief		Stop configurable timer
*	@date		08 October 2015
*	@version	1.0
*/
void nm_bsp_stop_configurable_timer(void)
{
}

#ifdef _STATIC_PS_
/**
*	@fn		nm_bsp_register_wake_isr
*	@brief	REGISTER wake up timer 
*	@author	M.S.M
*	@date	28 OCT 2013
*	@version	1.0
*/
void nm_bsp_register_wake_isr(tpfNmBspIsr pfIsr,uint32 u32MsPeriod)
{

	gstrWakeTimer.strTimer.pfCb = pfIsr;
	gstrWakeTimer.strTimer.u32Timeout = u32MsPeriod + NM_BSP_TIME_MSEC;
	gstrWakeTimer.strTimer.u32Period = u32MsPeriod;
	gstrWakeTimer.u8Enabled = 0;
}
/**
*	@fn		nm_bsp_wake_ctrl
*	@brief	control wake up timer
*	@author	M.S.M
*	@date	28 OCT 2013
*	@version	1.0
*/
void nm_bsp_wake_ctrl(uint8 en)
{
	gstrWakeTimer.u8Enabled = en;
	if(en)
	{
		gstrWakeTimer.strTimer.u32Timeout = gstrWakeTimer.strTimer.u32Period + NM_BSP_TIME_MSEC;
	}
}
#endif
#if (defined _STATIC_PS_)||(defined _DYNAMIC_PS_)
/**
*	@fn		nm_bsp_enable_mcu_ps
*	@brief	Start POWER SAVE FOR MCU 
*	@author	M.S.M
*	@date	28 OCT 2013
*	@version	1.0
*/
void nm_bsp_enable_mcu_ps(void)
{
	if(!gu8BtnIfg)
	{
		if(gstrWakeTimer.u8Enabled)
		{

		}
	}
}
#endif


