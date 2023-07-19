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
 * @defgroup nrf_dev_clock_example_main main.c
 * @{
 * @ingroup nrf_dev_clock_example
 * @brief Clock Example Application main file.
 *
 * This file contains the source code for a sample application using clock driver.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_drv_clock.h"
#include "nrf_drv_gpiote.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_ppi.h"
#include "nrf_gpiote.h"
#include "app_error.h"

const nrf_drv_rtc_t rtc = NRF_DRV_RTC_INSTANCE(1);

void rtc_evt_handler(nrf_drv_rtc_int_type_t int_type){}

void setup_example(void)
{
    uint32_t event;
    nrf_ppi_channel_t ppi_channel;
    uint32_t err_code;

    nrf_gpio_cfg_output(BSP_LED_0);

    nrf_drv_rtc_config_t config = NRF_DRV_RTC_DEFAULT_CONFIG;
    err_code = nrf_drv_rtc_init(&rtc, &config, rtc_evt_handler);
    APP_ERROR_CHECK(err_code);

    nrf_drv_rtc_tick_enable(&rtc, false);
    event = nrf_drv_rtc_event_address_get(&rtc, NRF_RTC_EVENT_TICK);

    if (!nrf_drv_gpiote_is_init())
    {
        err_code = nrf_drv_gpiote_init();
        APP_ERROR_CHECK(err_code);
    }

    nrf_drv_gpiote_out_config_t pin_out_config = GPIOTE_CONFIG_OUT_TASK_TOGGLE(false);
    err_code = nrf_drv_gpiote_out_init(BSP_LED_0,&pin_out_config);
    APP_ERROR_CHECK(err_code);

    nrf_drv_gpiote_out_task_enable(BSP_LED_0);

    uint32_t gpiote_task_addr = nrf_drv_gpiote_out_task_addr_get(BSP_LED_0);

    err_code = nrf_drv_ppi_init();
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_alloc(&ppi_channel);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_assign(ppi_channel,event,gpiote_task_addr);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_ppi_channel_enable(ppi_channel);
    APP_ERROR_CHECK(err_code);

    nrf_drv_rtc_enable(&rtc);
}


/**
 * @brief Function for application main entry.
 */
int main(void)
{
    uint32_t err_code;
    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);
    setup_example();

    while (true)
    {
        nrf_delay_ms(1000);
        nrf_drv_clock_lfclk_request(NULL);

        nrf_delay_ms(1000);
        nrf_drv_clock_lfclk_release();
    }
}


/** @} */
