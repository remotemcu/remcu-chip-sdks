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
*
* @defgroup ppi_example_main main.c
* @{
* @ingroup ppi_example
* @brief PPI Example Application main file.
*
* This file contains the source code for a sample application using PPI to communicate between timers.
*
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "nrf_delay.h"
#include "app_error.h"
#include "boards.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "nordic_common.h"

#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

const nrf_drv_timer_t timer0 = NRF_DRV_TIMER_INSTANCE(0);
const nrf_drv_timer_t timer1 = NRF_DRV_TIMER_INSTANCE(1);
const nrf_drv_timer_t timer2 = NRF_DRV_TIMER_INSTANCE(2);

nrf_ppi_channel_t ppi_channel1, ppi_channel2;


// Timer even handler. Not used since timer is used only for PPI.
void timer_event_handler(nrf_timer_event_t event_type, void * p_context){}

/** @brief Function for initializing the PPI peripheral.
*/
static void ppi_init(void)
{
    uint32_t err_code = NRF_SUCCESS;

    err_code = nrf_drv_ppi_init();
    APP_ERROR_CHECK(err_code);

    // Configure 1st available PPI channel to stop TIMER0 counter on TIMER1 COMPARE[0] match, which is every even number of seconds.
    err_code = nrf_drv_ppi_channel_alloc(&ppi_channel1);
    APP_ERROR_CHECK(err_code);
    err_code = nrf_drv_ppi_channel_assign(ppi_channel1,
                                          nrf_drv_timer_event_address_get(&timer1, NRF_TIMER_EVENT_COMPARE0),
                                          nrf_drv_timer_task_address_get(&timer0, NRF_TIMER_TASK_STOP));
    APP_ERROR_CHECK(err_code);

    // Configure 2nd available PPI channel to start timer0 counter at TIMER2 COMPARE[0] match, which is every odd number of seconds.
    err_code = nrf_drv_ppi_channel_alloc(&ppi_channel2);
    APP_ERROR_CHECK(err_code);
    err_code = nrf_drv_ppi_channel_assign(ppi_channel2,
                                          nrf_drv_timer_event_address_get(&timer2, NRF_TIMER_EVENT_COMPARE0),
                                          nrf_drv_timer_task_address_get(&timer0, NRF_TIMER_TASK_START));
    APP_ERROR_CHECK(err_code);

    // Enable both configured PPI channels
    err_code = nrf_drv_ppi_channel_enable(ppi_channel1);
    APP_ERROR_CHECK(err_code);
    err_code = nrf_drv_ppi_channel_enable(ppi_channel2);
    APP_ERROR_CHECK(err_code);
}


/** @brief Function for Timer 0 initialization, which will be started and stopped by timer1 and timer2 using PPI.
*/
static void timer0_init(void)
{
    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    timer_cfg.mode = NRF_TIMER_MODE_COUNTER;
    ret_code_t err_code = nrf_drv_timer_init(&timer0, &timer_cfg, timer_event_handler);
    APP_ERROR_CHECK(err_code);
}


/** @brief Function for Timer 1 initialization.
 *  @details Initializes Timer 1 peripheral, creates event and interrupt every 2 seconds,
 *           by configuring CC[0] to timer overflow value, we create events at even number of seconds
 *           for example, events are created at 2,4,6 ... seconds. This event can be used to stop Timer 0
 *           with Timer1->Event_Compare[0] triggering Timer 0 TASK_STOP through PPI.
*/
static void timer1_init(void)
{
    // Configure Timer 1 to overflow every 2 seconds. Check TIMER1 configuration for details
    // The overflow occurs every 0xFFFF/(SysClk/2^PRESCALER).
    // = 65535/31250 = 2.097 sec
    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    timer_cfg.frequency = NRF_TIMER_FREQ_31250Hz;
    ret_code_t err_code = nrf_drv_timer_init(&timer1, &timer_cfg, timer_event_handler);
    APP_ERROR_CHECK(err_code);

    nrf_drv_timer_extended_compare(&timer1, NRF_TIMER_CC_CHANNEL0, 0xFFFFUL, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, false);
}


/** @brief Function for Timer 2 initialization.
 *  @details Initializes Timer 2 peripheral, creates event and interrupt every 2 seconds
 *           by configuring CC[0] to half of timer overflow value. Events are created at odd number of seconds.
 *           For example, events are created at 1,3,5,... seconds. This event can be used to start Timer 0
 *           with Timer2->Event_Compare[0] triggering Timer 0 TASK_START through PPI.
*/
static void timer2_init(void)
{
    // Generate interrupt/event when half of time before the timer overflows has past, that is at 1,3,5,7... seconds from start.
    // Check TIMER1 configuration for details
    // now the overflow occurs every 0xFFFF/(SysClk/2^PRESCALER)
    // = 65535/31250 = 2.097 sec */
    nrf_drv_timer_config_t timer_cfg = NRF_DRV_TIMER_DEFAULT_CONFIG;
    timer_cfg.frequency = NRF_TIMER_FREQ_31250Hz;
    ret_code_t err_code = nrf_drv_timer_init(&timer2, &timer_cfg, timer_event_handler);
    APP_ERROR_CHECK(err_code);

    nrf_drv_timer_extended_compare(&timer2, NRF_TIMER_CC_CHANNEL0, 0x7FFFUL, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, false);
}


/**
 * @brief Function for application main entry.
 */
int main(void)
{
    timer0_init(); // Timer used to blink the LEDs.
    timer1_init(); // Timer to generate events on even number of seconds.
    timer2_init(); // Timer to generate events on odd number of seconds.
    ppi_init();    // PPI to redirect the event to timer start/stop tasks.

    uint32_t err_code;

    err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    // Enabling constant latency as indicated by PAN 11 "HFCLK: Base current with HFCLK
    // running is too high" found at Product Anomaly document found at
    // https://www.nordicsemi.com/eng/Products/Bluetooth-R-low-energy/nRF51822/#Downloads
    //
    // @note This example does not go to low power mode therefore constant latency is not needed.
    //       However this setting will ensure correct behaviour when routing TIMER events through
    //       PPI (shown in this example) and low power mode simultaneously.
    NRF_POWER->TASKS_CONSTLAT = 1;

    // Start clock.
    nrf_drv_timer_enable(&timer0);
    nrf_drv_timer_enable(&timer1);
    nrf_drv_timer_enable(&timer2);

    // Loop and increment the timer count value and capture value into LEDs. @note counter is only incremented between TASK_START and TASK_STOP.
    while (true)
    {

        NRF_LOG_INFO("Current count: %d\r\n", (int)nrf_drv_timer_capture(&timer0, NRF_TIMER_CC_CHANNEL0));

        /* increment the counter */
        nrf_drv_timer_increment(&timer0);

        nrf_delay_ms(100);
        NRF_LOG_FLUSH();
    }
}


/** @} */
