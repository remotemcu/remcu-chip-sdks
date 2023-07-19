/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
 * @defgroup nrf_drv_csense_example_main main.c
 * @{
 * @ingroup nrf_drv_csense_example
 * @brief Capacitive Sensor Example main file.
 *
 * This file contains the source code for a sample application that uses a capacitive sensor.
 *
 */

#include <stdio.h>
#include "boards.h"
#include "nrf_drv_csense.h"
#include "app_error.h"
#include "nrf_drv_clock.h"
#include "app_timer.h"
#include "nrf_delay.h"

#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

/* Time between RTC interrupts. */
#define APP_TIMER_TICKS_TIMEOUT 2000

/* Pin used to measure capacitor charging time. */
#ifdef NRF51
#define OUTPUT_PIN 30
#endif

/* Timer initialization parameters. */
#define OP_QUEUES_SIZE          4
#define APP_TIMER_PRESCALER     0

/* Analog inputs. */
#define AIN_1                   1
#define AIN_2                   2
#define AIN_7                   7

/* Masks of analog channels to be used by library. */
#ifdef NRF51
#define PAD_1_MASK              (1UL << AIN_2)
#else
#define PAD_1_MASK              (1UL << AIN_1)
#endif
#define PAD_2_MASK              (1UL << AIN_7)

#define PAD_ID_0                0
#define PAD_ID_1                1

#define UART_TX_BUF_SIZE 512                                                /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 1                                                  /**< UART RX buffer size. */


/* Threshold number of ticks (if COMP module present) or voltage in millivolts on sensor. */
volatile uint32_t threshold_value_pad1 = 850;
volatile uint32_t threshold_value_pad2 = 850;

/* Variables needed to properly configure threshold. */
volatile uint32_t max_value[2];
volatile uint32_t min_value[2];
bool conf_mode;

/** 
 * @brief Function for starting the internal LFCLK XTAL oscillator.
 *
 * Note that when using a SoftDevice, LFCLK is always on.
 *
 * @return Values returned by @ref nrf_drv_clock_init.
 */
static ret_code_t clock_config(void)
{
    ret_code_t err_code;

    err_code = nrf_drv_clock_init();
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    nrf_drv_clock_lfclk_request(NULL);

    return NRF_SUCCESS;
}

static inline void find_min_and_max(uint32_t val, uint8_t pad)
{
    if (val > max_value[pad])
    {
        max_value[pad] = val;
    }
    if (val < min_value[pad])
    {
        min_value[pad] = val;
    }
}

/**
 * @brief Capacitive sensor event handler.
 */
void csense_handler(nrf_drv_csense_evt_t * p_event_struct)
{
    switch (p_event_struct->analog_channel)
    {
        case AIN_1:
        case AIN_2:
            if (conf_mode)
            {
                NRF_LOG_INFO("PAD1: %d.\r\n", p_event_struct->read_value);
                find_min_and_max(p_event_struct->read_value, PAD_ID_0);
                break;
            }
            if (p_event_struct->read_value >= threshold_value_pad1)
            {
                bsp_board_led_on(BSP_BOARD_LED_0);
            }
            else
            {
                bsp_board_led_off(BSP_BOARD_LED_0);
            }
            break;
        case AIN_7:
            if (conf_mode)
            {
                NRF_LOG_INFO("PAD2: %d.\r\n", p_event_struct->read_value);
                find_min_and_max(p_event_struct->read_value, PAD_ID_1);
                break;
            }
            if (p_event_struct->read_value >= threshold_value_pad2)
            {
                bsp_board_led_on(BSP_BOARD_LED_2);
            }
            else
            {
                bsp_board_led_off(BSP_BOARD_LED_2);
            }
            break;
        default:
            break;
    }
}
/**
 * @brief Function for initializing the capacitive sensor.
 */
void csense_initialize(void)
{
    ret_code_t err_code;

    nrf_drv_csense_config_t csense_config = { 0 };

#ifdef NRF51
    csense_config.output_pin = OUTPUT_PIN;
#endif

    err_code = nrf_drv_csense_init(&csense_config, csense_handler);
    APP_ERROR_CHECK(err_code);

    nrf_drv_csense_channels_enable(PAD_1_MASK | PAD_2_MASK);
}

/**
 * @brief Timer event handler for the capacitive sensor.
 *
 * @param[in] p_context             General purpose pointer. Will be passed to the time-out handler
 *                                  when the timer expires.
 *
 */
static void csense_timeout_handler(void * p_context)
{
    ret_code_t err_code;

    err_code = nrf_drv_csense_sample();
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Busy.\r\n");
        return;
    }
}

/**
 * @brief Function for initalizing app timer.
 */
void start_app_timer(void)
{
    ret_code_t err_code;
        
    /* APP_TIMER definition for csense example. */
    APP_TIMER_DEF(timer_0);

    err_code = app_timer_create(&timer_0, APP_TIMER_MODE_REPEATED, csense_timeout_handler);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_start(timer_0, APP_TIMER_TICKS_TIMEOUT, NULL);
    APP_ERROR_CHECK(err_code);
}

/**
 * @brief Function for configuring pads threshold.
 */
void configure_thresholds(void)
{
    ret_code_t err_code;
    uint32_t new_th_pad_1;
    uint32_t new_th_pad_2;
    
    for (int i = 0; i < 2; i++)
    {
        max_value[i] = 0;
        min_value[i] = UINT32_MAX;
    }
    
    NRF_LOG_INFO("Touch both pads.\r\n");
    NRF_LOG_FLUSH();
    nrf_delay_ms(1000);
    NRF_LOG_INFO("3...\r\n");
    NRF_LOG_FLUSH();
    nrf_delay_ms(1000);
    NRF_LOG_INFO("2...\r\n");
    NRF_LOG_FLUSH();
    nrf_delay_ms(1000);
    NRF_LOG_INFO("1...\r\n");
    NRF_LOG_FLUSH();
    
    err_code = nrf_drv_csense_sample();   
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Busy.\n");
        return;
    }
    while (nrf_drv_csense_is_busy());
    
    NRF_LOG_INFO("Release both pads.\r\n");
    NRF_LOG_FLUSH();
    nrf_delay_ms(1000);
    NRF_LOG_INFO("3...\r\n");
    NRF_LOG_FLUSH();
    nrf_delay_ms(1000);
    NRF_LOG_INFO("2...\r\n");
    NRF_LOG_FLUSH();
    nrf_delay_ms(1000);
    NRF_LOG_INFO("1...\r\n");
    NRF_LOG_FLUSH();
    
    err_code = nrf_drv_csense_sample();   
    if (err_code != NRF_SUCCESS)
    {
        NRF_LOG_INFO("Busy.\n");
        return;
    }
    while (nrf_drv_csense_is_busy());

    nrf_delay_ms(100);    
    new_th_pad_1 = max_value[PAD_ID_0];
    new_th_pad_1 += min_value[PAD_ID_0];
    new_th_pad_1 /= 2;
    new_th_pad_2 = max_value[PAD_ID_1];
    new_th_pad_2 += min_value[PAD_ID_1];
    new_th_pad_2 /= 2;
    threshold_value_pad1 = new_th_pad_1;
    threshold_value_pad2 = new_th_pad_2;
    NRF_LOG_INFO("New thresholds, AIN1: %d, AIN7: %d.\r\n", (unsigned int)new_th_pad_1,
                                                      (unsigned int)new_th_pad_2);
}


/**
 * @brief Function for main application entry.
 */
int main(void)
{
    ret_code_t err_code;
    char config;
    
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    
    bsp_board_leds_init();

    err_code = clock_config();
    APP_ERROR_CHECK(err_code);
    
    APP_TIMER_INIT(APP_TIMER_PRESCALER, OP_QUEUES_SIZE, NULL);

    
    NRF_LOG_INFO("Capacitive sensing driver example.\r\n");
    
    csense_initialize();    

    NRF_LOG_INFO("Do you want to enter configuration mode to set thresholds?(y/n)\r\n");
    NRF_LOG_FLUSH();
    
    config = NRF_LOG_GETCHAR();
    
    conf_mode = (config == 'y') ? true : false;
    
    if (conf_mode)
    {
        configure_thresholds();
        conf_mode = false;
    }

    NRF_LOG_INFO("Module ready.\r\n");
    
    start_app_timer();    

    while (1)
    {
        NRF_LOG_FLUSH();
        __WFI();
    }
}

/** @} */
