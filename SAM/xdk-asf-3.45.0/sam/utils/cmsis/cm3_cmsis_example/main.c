/**
 * \file
 *
 * \brief CMSIS Example.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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
 * \mainpage CMSIS Example
 *
 * \section Purpose
 *
 * The cmsis example will help new users get familiar with
 * basic cmsis utilities of SAM3 microcontrollers.
 *
 * The example will execute the following tests:
 * - The application will flash the LED per second. The second 
 * is calculated by the standard system tick interface of cmsis.
 *
 * \section Requirements
 *
 * This package can be used with SAM3 evaluation kits.
 *
 * \section Description
 * The cmsis example will use the system tick of the Cortex-M3.
 *
 * \section Usage
 *
 * -# Build the program and download it into the evaluation board.
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "asf.h"
#include "conf_board.h"

__INLINE static void delay_ms(uint32_t ul_dly_ticks);
__INLINE static void led_config(void);
__INLINE static void led_on(uint32_t ul_led);
__INLINE static void led_off(uint32_t ul_led);

/* Systick Counter */
static volatile uint32_t g_ul_ms_ticks = 0U;

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \brief SysTick_Handler.
 */
void SysTick_Handler(void)
{
	/* Increment counter necessary in delay(). */
	g_ul_ms_ticks++;
}

/**
 * \brief Delay number of tick Systicks (happens every 1 ms).
 */
__INLINE static void delay_ms(uint32_t ul_dly_ticks)
{
	uint32_t ul_cur_ticks;

	ul_cur_ticks = g_ul_ms_ticks;
	while ((g_ul_ms_ticks - ul_cur_ticks) < ul_dly_ticks) {
	}
}

 /**
 * \brief Configure LED pins.
 */
__INLINE static void led_config(void)
{
	/* Set up LED pins. */
	LED0_PIO->PIO_PER = LED0_MASK;
	LED0_PIO->PIO_OER = LED0_MASK;
	LED0_PIO->PIO_PUDR = LED0_MASK;
}

/**
* \brief Switch on LED.
*/
__INLINE static void led_on(uint32_t ul_led)
{
	/* Turn On LED. */
	LED0_PIO->PIO_CODR = ul_led;
}

/**
* \brief Switch off LED.
*/
__INLINE static void led_off(uint32_t ul_led)
{
	/* Turn Off LED. */
	LED0_PIO->PIO_SODR = ul_led;
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the SAM3 system */
	SystemInit();

	WDT->WDT_MR = WDT_MR_WDDIS;

	/* Set up SysTick Timer for 1 msec interrupts. */
	if (SysTick_Config(SystemCoreClock / (uint32_t) 1000)) {
		/* Capture error. */
		while (1) {
		}
	}

	led_config();

	/* Flash the LED. */
	while (1) {
		/* Turn on the LED. */
		led_on(LED0_MASK);
		/* Delay  1000 Msec. */
		delay_ms((uint32_t) 1000);

		/* Turn off the LED. */
		led_off(LED0_MASK);
		/* Delay  1000 Msec. */
		delay_ms((uint32_t) 1000);
	}
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
