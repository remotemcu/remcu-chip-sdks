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
 * @defgroup nrf_twi_master_example main.c
 * @{
 * @ingroup nrf_twi_example
 * @brief TWI Example Application main file.
 *
 * This file contains the source code for a sample application using TWI.
 */

#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "nrf_drv_rtc.h"
#include "nrf_drv_clock.h"
#include "bsp.h"
#include "app_error.h"
#include "app_timer.h"
#include "app_twi.h"
#include "lm75b.h"
#include "mma7660.h"
#include "compiler_abstraction.h"
#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"


#define MAX_PENDING_TRANSACTIONS    5

#define APP_TIMER_PRESCALER         0
#define APP_TIMER_OP_QUEUE_SIZE     2

// Pin number for indicating communication with sensors.
#ifdef BSP_LED_3
    #define READ_ALL_INDICATOR  BSP_BOARD_LED_3
#else
    #error "Please choose an output pin"
#endif


static app_twi_t m_app_twi = APP_TWI_INSTANCE(0);

static nrf_drv_rtc_t const m_rtc = NRF_DRV_RTC_INSTANCE(0);


// Buffer for data read from sensors.
#define BUFFER_SIZE  11
static uint8_t m_buffer[BUFFER_SIZE];

// Data structures needed for averaging of data read from sensors.
// [max 32, otherwise "int16_t" won't be sufficient to hold the sum
//  of temperature samples]
#define NUMBER_OF_SAMPLES  16
typedef struct
{
    int16_t temp;
    int16_t x;
    int16_t y;
    int16_t z;
} sum_t;
static sum_t m_sum = { 0, 0, 0, 0 };
typedef struct
{
    // [use bit fields to fit whole structure into one 32-bit word]
    int16_t temp : 11;
    int8_t  x    : 6;
    int8_t  y    : 6;
    int8_t  z    : 6;
} sample_t;
static sample_t m_samples[NUMBER_OF_SAMPLES] = { { 0, 0, 0, 0 } };
static uint8_t m_sample_idx = 0;

// Value previously read from MMA7660's Tilt register - used to detect change
// in orientation, shake signaling etc.
static uint8_t m_prev_tilt = 0;

#if defined( __GNUC__ ) && (__LINT__ == 0)
    // This is required if one wants to use floating-point values in 'printf'
    // (by default this feature is not linked together with newlib-nano).
    // Please note, however, that this adds about 13 kB code footprint...
    __ASM(".global _printf_float");
#endif


////////////////////////////////////////////////////////////////////////////////
// Reading of data from sensors - current temperature from LM75B and from
// MMA7660: X, Y, Z and tilt status.
#if (BUFFER_SIZE < 6)
    #error Buffer too small.
#endif
#define GET_ACC_VALUE(axis, reg_data) \
    do { \
        if (MMA7660_DATA_IS_VALID(reg_data)) \
        { \
            axis = MMA7660_GET_ACC(reg_data); \
        } \
    } while (0)

void read_all_cb(ret_code_t result, void * p_user_data)
{
    if (result != NRF_SUCCESS)
    {
        NRF_LOG_INFO("read_all_cb - error: %d\r\n", (int)result);
        return;
    }

    sample_t * p_sample = &m_samples[m_sample_idx];
    m_sum.temp -= p_sample->temp;
    m_sum.x    -= p_sample->x;
    m_sum.y    -= p_sample->y;
    m_sum.z    -= p_sample->z;

    uint8_t temp_hi = m_buffer[0];
    uint8_t temp_lo = m_buffer[1];
    uint8_t x_out   = m_buffer[2];
    uint8_t y_out   = m_buffer[3];
    uint8_t z_out   = m_buffer[4];
    uint8_t tilt    = m_buffer[5];

    p_sample->temp = LM75B_GET_TEMPERATURE_VALUE(temp_hi, temp_lo);
    GET_ACC_VALUE(p_sample->x, x_out);
    GET_ACC_VALUE(p_sample->y, y_out);
    GET_ACC_VALUE(p_sample->z, z_out);
    if (!MMA7660_DATA_IS_VALID(tilt))
    {
        tilt = m_prev_tilt;
    }

    m_sum.temp += p_sample->temp;
    m_sum.x    += p_sample->x;
    m_sum.y    += p_sample->y;
    m_sum.z    += p_sample->z;

    ++m_sample_idx;
    if (m_sample_idx >= NUMBER_OF_SAMPLES)
    {
        m_sample_idx = 0;
    }

    // Show current average values every time sample index rolls over (for RTC
    // ticking at 32 Hz and 16 samples it will be every 500 ms) or when tilt
    // status changes.
    if (m_sample_idx == 0 || (m_prev_tilt && m_prev_tilt != tilt))
    {
        char const * orientation;
        switch (MMA7660_GET_ORIENTATION(tilt))
        {
            case MMA7660_ORIENTATION_LEFT:  orientation = "LEFT";  break;
            case MMA7660_ORIENTATION_RIGHT: orientation = "RIGHT"; break;
            case MMA7660_ORIENTATION_DOWN:  orientation = "DOWN";  break;
            case MMA7660_ORIENTATION_UP:    orientation = "UP";    break;
            default:                        orientation = "?";     break;
        }

        NRF_LOG_INFO("Temp: " NRF_LOG_FLOAT_MARKER " | X: %3d, Y: %3d, Z: %3d ",
            NRF_LOG_FLOAT((float)((m_sum.temp * 0.125) / NUMBER_OF_SAMPLES)),
            m_sum.x / NUMBER_OF_SAMPLES,
            m_sum.y / NUMBER_OF_SAMPLES,
            m_sum.z / NUMBER_OF_SAMPLES);

        NRF_LOG_RAW_INFO("| %s%s%s\r\n",
            (uint32_t)orientation,
            (uint32_t)(MMA7660_TAP_DETECTED(tilt)   ? " TAP"   : ""),
            (uint32_t)(MMA7660_SHAKE_DETECTED(tilt) ? " SHAKE" : ""));
        m_prev_tilt = tilt;
    }
}
static void read_all(void)
{
    // Signal on LED that something is going on.
    bsp_board_led_invert(READ_ALL_INDICATOR);

    // [these structures have to be "static" - they cannot be placed on stack
    //  since the transaction is scheduled and these structures most likely
    //  will be referred after this function returns]
    static app_twi_transfer_t const transfers[] =
    {
        LM75B_READ_TEMP(&m_buffer[0])
        ,
        MMA7660_READ_XYZ_AND_TILT(&m_buffer[2])
    };
    static app_twi_transaction_t const transaction =
    {
        .callback            = read_all_cb,
        .p_user_data         = NULL,
        .p_transfers         = transfers,
        .number_of_transfers = sizeof(transfers) / sizeof(transfers[0])
    };

    APP_ERROR_CHECK(app_twi_schedule(&m_app_twi, &transaction));
}

#if (BUFFER_SIZE < 7)
    #error Buffer too small.
#endif
static void read_lm75b_registers_cb(ret_code_t result, void * p_user_data)
{
    if (result != NRF_SUCCESS)
    {
        NRF_LOG_INFO("read_lm75b_registers_cb - error: %d\r\n", (int)result);
        return;
    }

    NRF_LOG_INFO("LM75B:\r\n");
    NRF_LOG_HEXDUMP_INFO(m_buffer, 7);
}
static void read_lm75b_registers(void)
{
    // [these structures have to be "static" - they cannot be placed on stack
    //  since the transaction is scheduled and these structures most likely
    //  will be referred after this function returns]
    static app_twi_transfer_t const transfers[] =
    {
        LM75B_READ(&lm75b_conf_reg_addr,  &m_buffer[0], 1),
        LM75B_READ(&lm75b_temp_reg_addr,  &m_buffer[1], 2),
        LM75B_READ(&lm75b_tos_reg_addr,   &m_buffer[3], 2),
        LM75B_READ(&lm75b_thyst_reg_addr, &m_buffer[5], 2)
    };
    static app_twi_transaction_t const transaction =
    {
        .callback            = read_lm75b_registers_cb,
        .p_user_data         = NULL,
        .p_transfers         = transfers,
        .number_of_transfers = sizeof(transfers) / sizeof(transfers[0])
    };

    APP_ERROR_CHECK(app_twi_schedule(&m_app_twi, &transaction));
}


#if (BUFFER_SIZE < MMA7660_NUMBER_OF_REGISTERS)
    #error Buffer too small.
#endif
static void read_mma7660_registers_cb(ret_code_t result, void * p_user_data)
{
    if (result != NRF_SUCCESS)
    {
        NRF_LOG_INFO("read_mma7660_registers_cb - error: %d\r\n", (int)result);
        return;
    }

    NRF_LOG_INFO("MMA7660:\r\n");
    NRF_LOG_HEXDUMP_INFO(m_buffer, MMA7660_NUMBER_OF_REGISTERS);
}
static void read_mma7660_registers(void)
{
    // [these structures have to be "static" - they cannot be placed on stack
    //  since the transaction is scheduled and these structures most likely
    //  will be referred after this function returns]
    static app_twi_transfer_t const transfers[] =
    {
        MMA7660_READ(&mma7660_xout_reg_addr,
            m_buffer, MMA7660_NUMBER_OF_REGISTERS)
    };
    static app_twi_transaction_t const transaction =
    {
        .callback            = read_mma7660_registers_cb,
        .p_user_data         = NULL,
        .p_transfers         = transfers,
        .number_of_transfers = sizeof(transfers) / sizeof(transfers[0])
    };

    APP_ERROR_CHECK(app_twi_schedule(&m_app_twi, &transaction));
}


////////////////////////////////////////////////////////////////////////////////
// Buttons handling (by means of BSP).
//
static void bsp_event_handler(bsp_event_t event)
{
    // Each time the button 1 or 4 is pushed we start a transaction reading
    // values of all registers from LM75B or MMA7660 respectively.
    switch (event)
    {
    case BSP_EVENT_KEY_0: // Button 1 pushed.
        read_lm75b_registers();
        break;

    case BSP_EVENT_KEY_3: // Button 4 pushed.
        read_mma7660_registers();
        break;

    default:
        break;
    }
}
static void bsp_config(void)
{
    uint32_t err_code;

    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, NULL);

    err_code = bsp_init(BSP_INIT_BUTTONS,
                        APP_TIMER_TICKS(100, APP_TIMER_PRESCALER),
                        bsp_event_handler);
    APP_ERROR_CHECK(err_code);
}

// TWI (with transaction manager) initialization.
static void twi_config(void)
{
    uint32_t err_code;

    nrf_drv_twi_config_t const config = {
       .scl                = ARDUINO_SCL_PIN,
       .sda                = ARDUINO_SDA_PIN,
       .frequency          = NRF_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_LOWEST,
       .clear_bus_init     = false
    };

    APP_TWI_INIT(&m_app_twi, &config, MAX_PENDING_TRANSACTIONS, err_code);
    APP_ERROR_CHECK(err_code);
}


// RTC tick events generation.
static void rtc_handler(nrf_drv_rtc_int_type_t int_type)
{
    if (int_type == NRF_DRV_RTC_INT_TICK)
    {
        // On each RTC tick (their frequency is set in "nrf_drv_config.h")
        // we read data from our sensors.
        read_all();
    }
}
static void rtc_config(void)
{
    uint32_t err_code;

    // Initialize RTC instance with default configuration.
    nrf_drv_rtc_config_t config = NRF_DRV_RTC_DEFAULT_CONFIG;
    config.prescaler = RTC_FREQ_TO_PRESCALER(32); //Set RTC frequency to 32Hz
    err_code = nrf_drv_rtc_init(&m_rtc, &config, rtc_handler);
    APP_ERROR_CHECK(err_code);

    // Enable tick event and interrupt.
    nrf_drv_rtc_tick_enable(&m_rtc, true);

    // Power on RTC instance.
    nrf_drv_rtc_enable(&m_rtc);
}


static void lfclk_config(void)
{
    uint32_t err_code;

    err_code = nrf_drv_clock_init();
    APP_ERROR_CHECK(err_code);

    nrf_drv_clock_lfclk_request(NULL);
}


int main(void)
{
    bsp_board_leds_init();

    // Start internal LFCLK XTAL oscillator - it is needed by BSP to handle
    // buttons with the use of APP_TIMER and for "read_all" ticks generation
    // (by RTC).
    lfclk_config();

    bsp_config();

    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));

    NRF_LOG_INFO("TWI master example\r\n");
    NRF_LOG_FLUSH();
    twi_config();

    // Initialize sensors.
    APP_ERROR_CHECK(app_twi_perform(&m_app_twi, lm75b_init_transfers,
        LM75B_INIT_TRANSFER_COUNT, NULL));
    APP_ERROR_CHECK(app_twi_perform(&m_app_twi, mma7660_init_transfers,
        MMA7660_INIT_TRANSFER_COUNT, NULL));

    rtc_config();

    while (true)
    {
        __WFI();
        NRF_LOG_FLUSH();
    }
}


/** @} */
