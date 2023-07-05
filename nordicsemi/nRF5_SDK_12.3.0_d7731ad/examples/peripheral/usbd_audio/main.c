/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "nrf.h"
#include "nrf_drv_usbd.h"
#include "nrf_drv_clock.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_drv_power.h"

#include "app_usbd.h"
#include "app_usbd_core.h"
#include "app_usbd_string_desc.h"
#include "app_usbd_audio.h"
#include "boards.h"

#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

/**@file
 * @defgroup usbd_aduio_example main.c
 * @{
 * @ingroup usbd_audio_example
 * @brief USBD Audio class example
 *
 */

#define LED_USB_RESUME (BSP_BOARD_LED_0)
#define LED_USB_START  (BSP_BOARD_LED_1)
#define LED_AUDIO_RX   (BSP_BOARD_LED_2)
#define LED_AUDIO_TX   (BSP_BOARD_LED_3)

/**
 * @brief Enable power USB detection
 *
 * Configure if example supports USB port connection
 */
#ifndef USBD_POWER_DETECTION
#define USBD_POWER_DETECTION true
#endif

/**
 * @brief Audio class user event handler
 * */
static void hp_audio_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_audio_user_event_t   event);
static void mic_audio_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_audio_user_event_t   event);
/**
 * @brief   Input terminal channel configuration
 * */
#define HP_TERMINAL_CH_CONFIG()                                                                       \
        (APP_USBD_AUDIO_IN_TERM_CH_CONFIG_LEFT_FRONT | APP_USBD_AUDIO_IN_TERM_CH_CONFIG_RIGHT_FRONT)

/**
 * @brief   Feature controls
 *
 *      general
 *      channel 0
 *      channel 1
 * */
#define HP_FEATURE_CONTROLS()                                                                         \
        APP_USBD_U16_TO_RAW_DSC(APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_MUTE),                         \
        APP_USBD_U16_TO_RAW_DSC(APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_MUTE),                         \
        APP_USBD_U16_TO_RAW_DSC(APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_MUTE)
/**
 * @brief Audio control interface descriptor list:
 *  - input terminal 1
 *  - feature unit descriptor
 *  - output terminal
 * */
#define HP_AUDIO_CONTROL_DSC_LIST() (                                                                           \
        APP_USBD_AUDIO_INPUT_TERMINAL_DSC(1, APP_USBD_AUDIO_TERMINAL_USB_STREAMING, 2, HP_TERMINAL_CH_CONFIG()) \
        APP_USBD_AUDIO_FEATURE_UNIT_DSC(2, 1, HP_FEATURE_CONTROLS())                                            \
        APP_USBD_AUDIO_OUTPUT_TERMINAL_DSC(3, APP_USBD_AUDIO_TERMINAL_OUT_HEADPHONES, 2)                     \
)

/**
 * @brief Raw array of audio descriptors for headphones
 *
 *  AUDIO_CONTROL_INTERFACE
 *  AUDIO_CONTROL_HEADER
 *     INPUT_TERMINAL
 *     FEATURE_UNIT
 *     OUTPUT_TERMINAL
 *  AUDIO_STREAMING_INTERFACE_ALTERNATE0
 *  AUDIO_STREAMING_INTERFACE_ALTERNATE1
 *     AS_FORMAT_III
 *     EP_GENERAL
 *     ISO_EP_OUT
 *
 * */
static const uint8_t m_hp_audio_class_descriptors[] = {
        /* Audio control interface descriptor descriptor: 0
         * + descriptors defined by AUDIO_CONTROL_DSC_LIST*/
        APP_USBD_AUDIO_CONTROL_DSC(0, HP_AUDIO_CONTROL_DSC_LIST(), (1))

        /*Audio streaming interface descriptor descriptor: 1, setting: 0*/
        APP_USBD_AUDIO_STREAMING_DSC(1, 0, 0)

        /*Audio streaming interface descriptor descriptor: 1, setting: 1*/
        APP_USBD_AUDIO_STREAMING_DSC(1, 1, 1)

        /*Audio class specific interface descriptor*/
        APP_USBD_AUDIO_AS_IFACE_DSC(1, 0, APP_USBD_AUDIO_AS_IFACE_FORMAT_PCM)

        /*Audio class specific format I descriptor*/
        APP_USBD_AUDIO_AS_FORMAT_III_DSC(2, 2, 16, 1, APP_USBD_U24_TO_RAW_DSC(48000))

        /*Audio class specific endpoint general descriptor*/
        APP_USBD_AUDIO_EP_GENERAL_DSC(0x00, 0, 0)

        /*Standard ISO endpoint descriptor*/
        APP_USBD_AUDIO_ISO_EP_OUT_DSC(192)
};


/**
 * @brief   Input terminal channel configuration
 * */
#define MIC_TERMINAL_CH_CONFIG()                                                                       \
        (APP_USBD_AUDIO_IN_TERM_CH_CONFIG_LEFT_FRONT | APP_USBD_AUDIO_IN_TERM_CH_CONFIG_RIGHT_FRONT)

/**
 * @brief   Feature controls
 *
 *      general
 *      channel 0
 *      channel 1
 * */
#define MIC_FEATURE_CONTROLS()                                                                     \
        APP_USBD_U16_TO_RAW_DSC(APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_MUTE),                         \
        APP_USBD_U16_TO_RAW_DSC(APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_MUTE),                         \
        APP_USBD_U16_TO_RAW_DSC(APP_USBD_AUDIO_FEATURE_UNIT_CONTROL_MUTE)

/**
 * @brief Audio control interface descriptor list:
 *  - input terminal 1
 *  - feature unit descriptor
 *  - output terminal
 * */
#define MIC_AUDIO_CONTROL_DSC_LIST() (                                                                           \
        APP_USBD_AUDIO_INPUT_TERMINAL_DSC(1, APP_USBD_AUDIO_TERMINAL_IN_MICROPHONE, 2, MIC_TERMINAL_CH_CONFIG()) \
        APP_USBD_AUDIO_FEATURE_UNIT_DSC(2, 1, MIC_FEATURE_CONTROLS())                                            \
        APP_USBD_AUDIO_OUTPUT_TERMINAL_DSC(3, APP_USBD_AUDIO_TERMINAL_USB_STREAMING, 2)                          \
)

/**
 * @brief Raw array of audio descriptors for Microphone
 *
 *  AUDIO_CONTROL_INTERFACE
 *  AUDIO_CONTROL_HEADER
 *     INPUT_TERMINAL
 *     FEATURE_UNIT
 *     OUTPUT_TERMINAL
 *  AUDIO_STREAMING_INTERFACE_ALTERNATE0
 *  AUDIO_STREAMING_INTERFACE_ALTERNATE1
 *     AS_FORMAT_III
 *     EP_GENERAL
 *     ISO_EP_IN
 *
 * */
static const uint8_t m_mic_audio_class_descriptors[] = {
        /* Audio control interface descriptor descriptor: 2
         * + descriptors defined by AUDIO_CONTROL_DSC_LIST*/
        APP_USBD_AUDIO_CONTROL_DSC(2, MIC_AUDIO_CONTROL_DSC_LIST(), (3))

        /*Audio streaming interface descriptor descriptor: 3, setting: 0*/
        APP_USBD_AUDIO_STREAMING_DSC(3, 0, 0)

        /*Audio streaming interface descriptor descriptor: 3, setting: 1*/
        APP_USBD_AUDIO_STREAMING_DSC(3, 1, 1)

        /*Audio class specific interface descriptor*/
        APP_USBD_AUDIO_AS_IFACE_DSC(3, 0, APP_USBD_AUDIO_AS_IFACE_FORMAT_PCM)

        /*Audio class specific format I descriptor*/
        APP_USBD_AUDIO_AS_FORMAT_I_DSC(2, 2, 16, 1, APP_USBD_U24_TO_RAW_DSC(48000))

        /*Audio class specific endpoint general descriptor*/
        APP_USBD_AUDIO_EP_GENERAL_DSC(0x00, 0, 0)

        /*Standard ISO endpoint descriptor*/
        APP_USBD_AUDIO_ISO_EP_IN_DSC(192)
};


/**
 * @brief Interfaces list passed to @ref APP_USBD_AUDIO_GLOBAL_DEF
 * */
#define HP_INTERFACES_CONFIG() APP_USBD_AUDIO_CONFIG_OUT(0, 1)

/**
 * @brief Interfaces list passed to @ref APP_USBD_AUDIO_GLOBAL_DEF
 * */
#define MIC_INTERFACES_CONFIG() APP_USBD_AUDIO_CONFIG_IN(2, 3)

/*lint -save -e26 -e64 -e123 -e505 -e651*/

/**
 * @brief Headphone Audio class instance
 * */
APP_USBD_AUDIO_GLOBAL_DEF(m_app_audio_headphone,
                          HP_INTERFACES_CONFIG(),
                          hp_audio_user_ev_handler,
                          m_hp_audio_class_descriptors
);

/**
 * @brief Headphone Audio class instance
 * */
APP_USBD_AUDIO_GLOBAL_DEF(m_app_audio_microphone,
                          MIC_INTERFACES_CONFIG(),
                          mic_audio_user_ev_handler,
                          m_mic_audio_class_descriptors
);


/*lint -restore*/

/**
 * @brief I2S output data counter
 * */
static size_t m_tx_counter;

/**
 * @brief USB audio receive data counter
 * */
static size_t m_rx_counter;

/**
 * @brief USB audio buffer size
 * */
#define BUFFER_SIZE  (48)

/**
 * @brief USB audio receive buffer
 * */
static int16_t  m_rx_buffer[2 * BUFFER_SIZE];

static int16_t  m_temp_buffer[2 * BUFFER_SIZE];

static int16_t  m_tx_buffer[2 * BUFFER_SIZE];

/**
 * @brief Actual headphones mute
 * */
static uint8_t  m_mute_hp;

/**
 * @brief Actual sampling frequency
 * */
static uint32_t m_freq_hp;

/**
 * @brief Audio class specific request handle (headphones)
 * */
static void hp_audio_user_class_req(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_audio_t const * p_audio = app_usbd_audio_class_get(p_inst);
    app_usbd_audio_req_t * p_req = app_usbd_audio_class_request_get(p_audio);

    UNUSED_VARIABLE(m_mute_hp);
    UNUSED_VARIABLE(m_freq_hp);

    switch (p_req->req_target)
    {
        case APP_USBD_AUDIO_CLASS_REQ_IN:

            if (p_req->req_type == APP_USBD_AUDIO_REQ_SET_CUR)
            {
                //Only mute control is defined
                p_req->payload[0] = m_mute_hp;
            }

            break;
        case APP_USBD_AUDIO_CLASS_REQ_OUT:

            if (p_req->req_type == APP_USBD_AUDIO_REQ_SET_CUR)
            {
                //Only mute control is defined
                m_mute_hp = p_req->payload[0];
            }

            break;
        case APP_USBD_AUDIO_EP_REQ_IN:
            break;
        case APP_USBD_AUDIO_EP_REQ_OUT:

            if (p_req->req_type == APP_USBD_AUDIO_REQ_SET_CUR)
            {
                //Only set frequency is supported
                m_freq_hp = p_req->payload[0] + (p_req->payload[1] << 8) + (p_req->payload[2] << 16);
            }

            break;
        default:
            break;
    }
}


/**
 * @brief Actual microphone mute state
 * */
static uint8_t  m_mute_mic;

/**
 * @brief Actual microphone sampling frequency
 * */
static uint32_t m_freq_mic;

/**
 * @brief Audio class specific request handle (microphone)
 * */
static void mic_audio_user_class_req(app_usbd_class_inst_t const * p_inst)
{
    app_usbd_audio_t const * p_audio = app_usbd_audio_class_get(p_inst);
    app_usbd_audio_req_t * p_req = app_usbd_audio_class_request_get(p_audio);

    UNUSED_VARIABLE(m_mute_mic);
    UNUSED_VARIABLE(m_freq_mic);

    switch (p_req->req_target)
    {
        case APP_USBD_AUDIO_CLASS_REQ_IN:

            if (p_req->req_type == APP_USBD_AUDIO_REQ_SET_CUR)
            {
                //Only mute control is defined
                p_req->payload[0] = m_mute_mic;
            }

            break;
        case APP_USBD_AUDIO_CLASS_REQ_OUT:

            if (p_req->req_type == APP_USBD_AUDIO_REQ_SET_CUR)
            {
                //Only mute control is defined
                m_mute_mic = p_req->payload[0];
            }

            break;
        case APP_USBD_AUDIO_EP_REQ_IN:
            break;
        case APP_USBD_AUDIO_EP_REQ_OUT:

            if (p_req->req_type == APP_USBD_AUDIO_REQ_SET_CUR)
            {
                //Only set frequency is supported
                m_freq_mic = p_req->payload[0] + (p_req->payload[1] << 8) + (p_req->payload[2] << 16);
            }

            break;
        default:
            break;
    }
}

/**
 * @brief User event handler @ref app_usbd_audio_user_ev_handler_t (headphones)
 * */
static void hp_audio_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                     app_usbd_audio_user_event_t   event)
{
    app_usbd_audio_t const * p_audio = app_usbd_audio_class_get(p_inst);
    UNUSED_VARIABLE(p_audio);
    UNUSED_VARIABLE(m_rx_counter);
    switch (event)
    {
        case APP_USBD_AUDIO_USER_EVT_SUSPEND:
            bsp_board_led_off(LED_USB_RESUME);
            break;
        case APP_USBD_AUDIO_USER_EVT_RESUME:
            bsp_board_led_on(LED_USB_RESUME);
            break;
        case APP_USBD_AUDIO_USER_EVT_START:
            /*Setup receive buffer*/
            app_usbd_audio_class_rx_buf_set(p_inst, m_rx_buffer, sizeof(m_rx_buffer));
            bsp_board_led_on(LED_USB_START);
            break;
        case APP_USBD_AUDIO_USER_EVT_STOP:
            bsp_board_leds_off();
            break;
        case APP_USBD_AUDIO_USER_EVT_CLASS_REQ:
            hp_audio_user_class_req(p_inst);
            break;
        case APP_USBD_AUDIO_USER_EVT_RX_DONE:
        {
            m_rx_counter++;
            memcpy(m_temp_buffer, m_rx_buffer, sizeof(m_rx_buffer));
            bsp_board_led_invert(LED_AUDIO_RX);
            break;
        }
        default:
            break;
    }
}

/**
 * @brief User event handler @ref app_usbd_audio_user_ev_handler_t (microphone)
 * */
static void mic_audio_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_audio_user_event_t   event)
{
    app_usbd_audio_t const * p_audio = app_usbd_audio_class_get(p_inst);
    UNUSED_VARIABLE(p_audio);
    UNUSED_VARIABLE(m_tx_counter);

    switch (event)
    {
        case APP_USBD_AUDIO_USER_EVT_START:
            /*Setup receive buffer*/
            app_usbd_audio_class_tx_buf_set(p_inst, m_tx_buffer, sizeof(m_tx_buffer));
            break;
        case APP_USBD_AUDIO_USER_EVT_CLASS_REQ:
            mic_audio_user_class_req(p_inst);
            break;
        case APP_USBD_AUDIO_USER_EVT_TX_DONE:
        {
            m_tx_counter++;
            memcpy(m_tx_buffer, m_temp_buffer, sizeof(m_tx_buffer));
            bsp_board_led_invert(LED_AUDIO_TX);
            break;
        }
        default:
            break;
    }
}

/**
 * @brief  USB connection status
 * */
static bool m_usb_connected = false;

static void power_usb_event_handler(nrf_drv_power_usb_evt_t event)
{
    switch(event)
    {
        case NRF_DRV_POWER_USB_EVT_DETECTED:
            NRF_LOG_INFO("USB power detected\r\n");

            if (!nrf_drv_usbd_is_enabled())
            {
                app_usbd_enable();
            }
            break;
        case NRF_DRV_POWER_USB_EVT_REMOVED:
            NRF_LOG_INFO("USB power removed\r\n");
            m_usb_connected = false;
            break;
        case NRF_DRV_POWER_USB_EVT_READY:
            NRF_LOG_INFO("USB ready\r\n");
            m_usb_connected = true;
            break;
        default:
            ASSERT(false);
    }
}

static void usb_start(void)
{
    if (USBD_POWER_DETECTION)
    {
        static const nrf_drv_power_usbevt_config_t config =
        {
            .handler = power_usb_event_handler
        };

        nrf_drv_power_usbevt_init(&config);
    }
    else
    {
        NRF_LOG_INFO("No USB power detection enabled\r\nStarting USB now\r\n");

        app_usbd_enable();
        app_usbd_start();
        m_usb_connected = true;
    }
}

static bool usb_connection_handle(bool last_usb_conn_status)
{
    if (last_usb_conn_status != m_usb_connected)
    {
        last_usb_conn_status = m_usb_connected;
        m_usb_connected ? app_usbd_start() : app_usbd_disable();
    }

    return last_usb_conn_status;
}
int main(void)
{
    ret_code_t ret;

    ret = nrf_drv_clock_init();
    APP_ERROR_CHECK(ret);
    ret = nrf_drv_power_init(NULL);
    APP_ERROR_CHECK(ret);

    ret = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(ret);
    NRF_LOG_INFO("Hello USB!\r\n");

    bsp_board_leds_init();
    bsp_board_buttons_init();

    ret = app_usbd_init();
    APP_ERROR_CHECK(ret);

    app_usbd_class_inst_t const * class_inst_hp =
            app_usbd_audio_class_inst_get(&m_app_audio_headphone);
    ret = app_usbd_class_append(class_inst_hp);
    APP_ERROR_CHECK(ret);

    app_usbd_class_inst_t const * class_inst_mic =
            app_usbd_audio_class_inst_get(&m_app_audio_microphone);
    ret = app_usbd_class_append(class_inst_mic);
    APP_ERROR_CHECK(ret);

    bool last_usb_conn_status = false;
    usb_start();

    while (true)
    {
        last_usb_conn_status = usb_connection_handle(last_usb_conn_status);
        UNUSED_RETURN_VALUE(NRF_LOG_PROCESS());
    }
}

/** @} */
