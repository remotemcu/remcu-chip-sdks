/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

/** @file
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example_rtx
 *
 * @brief Blinky RTX Example Application main file.
 *
 * This file contains the source code for a sample application using RTX to blink LEDs.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "boards.h"
#include "cmsis_os.h"
#include "nordic_common.h"

#if LEDS_NUMBER <= 2
#error "Board is not equipped with enough amount of LEDs"
#endif

#define OUTPUT_0_INTERVAL      100                       /**< BOARD_LED_0 toggle interval (ms). */
#define OUTPUT_1_INTERVAL      400                       /**< BOARD_LED_1 toggle interval (ms). */

#define SIGNAL_OUTPUT_1_TOGGLE 0x01                      /**< ID of signal sended to blinky_thread. */

static void blinky_thread(void const * arg);             /**< Prototype of blinky_thread. */
osThreadDef(blinky_thread, osPriorityAboveNormal, 1, 0); /**< Definition of blinky_thread */

static void led_toggle_timer_handler(void const * arg);  /**< Prototype of timer callback function. */
osTimerDef(led_toggle_timer, led_toggle_timer_handler);  /**< Definition of timer callback function. */


/**@brief Thread for toggling LED_1.
 *
 * @details This thread is receiving signals from main loop and toggle BSP_LED_1.
 *
 * @param[in]   arg   Pointer used for passing some arbitrary information (context) from the
 *                    osThreadCreate() call to the thread.
 */
static void blinky_thread(void const * arg)
{
    UNUSED_PARAMETER(arg);
    osEvent evt;

    while (true)
    {
        evt = osSignalWait(SIGNAL_OUTPUT_1_TOGGLE, osWaitForever);

        if (evt.status == osEventSignal)
        {
            bsp_board_led_invert(BSP_BOARD_LED_1);
        }
    }
}

/**@brief Function for handling the timer timeout and blinking LED_0.
 *
 * @details This function will be called each time the timer expires.
 *
 * @param[in]   p_context   Pointer used for passing some arbitrary information (context) from the
 *                          osTimerCreate() call to the timeout handler.
 */
static void led_toggle_timer_handler(void const * arg)
{
    UNUSED_PARAMETER(arg);
    bsp_board_led_invert(BSP_BOARD_LED_0);
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    osThreadId blinky_thread_id;
    osTimerId  led_toggle_timer_id;
    osStatus   status;

    /* Configure LED-pins as outputs */
    bsp_board_leds_init();

    /* Create the blinky_thread */
    blinky_thread_id    = osThreadCreate(osThread(blinky_thread), NULL);

    /* Create the timer */
    led_toggle_timer_id = osTimerCreate(osTimer(led_toggle_timer), osTimerPeriodic, NULL);

    /* Get timer status */
    status              = osTimerStart(led_toggle_timer_id, OUTPUT_0_INTERVAL);

    /* Handle thread creation and starting timer errors */
    if ((blinky_thread_id == NULL) || (status != osOK))
    {
        while (true)
        {
            /* do nothing, error */
        }
    }

    while (true)
    {
        UNUSED_VARIABLE(osSignalSet(blinky_thread_id, SIGNAL_OUTPUT_1_TOGGLE));
        UNUSED_VARIABLE(osDelay(OUTPUT_1_INTERVAL));
    }
}

/**
 *@}
 **/
