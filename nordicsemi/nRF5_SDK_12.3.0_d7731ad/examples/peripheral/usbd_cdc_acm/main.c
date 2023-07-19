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
#include <stdio.h>

#include "nrf.h"
#include "nrf_drv_usbd.h"
#include "nrf_drv_clock.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_drv_power.h"

#include "app_error.h"
#include "app_util.h"
#include "app_usbd_core.h"
#include "app_usbd.h"
#include "app_usbd_string_desc.h"
#include "app_usbd_cdc_acm.h"

#include "boards.h"

#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"


/**@file
 * @defgroup usbd_cdc_acm_example main.c
 * @{
 * @ingroup usbd_cdc_acm_example
 * @brief USBD CDC ACM example
 *
 */

#define LED_USB_RESUME     (BSP_BOARD_LED_0)
#define LED_CDC_ACM_OPEN   (BSP_BOARD_LED_1)
#define LED_CDC_ACM_RX     (BSP_BOARD_LED_2)
#define LED_CDC_ACM_TX     (BSP_BOARD_LED_3)

#define BTN_CDC_DATA_SEND         (BSP_BOARD_BUTTON_0)
#define BTN_CDC_NOTIFY_SEND       (BSP_BOARD_BUTTON_1)

/**
 * @brief Enable power USB detection
 *
 * Configure if example supports USB port connection
 */
#ifndef USBD_POWER_DETECTION
#define USBD_POWER_DETECTION true
#endif


static void cdc_acm_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_cdc_acm_user_event_t event);

#define CDC_ACM_COMM_INTERFACE  0
#define CDC_ACM_COMM_EPIN       NRF_DRV_USBD_EPIN2

#define CDC_ACM_DATA_INTERFACE  1
#define CDC_ACM_DATA_EPIN       NRF_DRV_USBD_EPIN1
#define CDC_ACM_DATA_EPOUT      NRF_DRV_USBD_EPOUT1

/**
 * @brief Interfaces list passed to @ref APP_USBD_CDC_ACM_GLOBAL_DEF
 * */
#define CDC_ACM_INTERFACES_CONFIG()                 \
    APP_USBD_CDC_ACM_CONFIG(CDC_ACM_COMM_INTERFACE, \
                            CDC_ACM_COMM_EPIN,      \
                            CDC_ACM_DATA_INTERFACE, \
                            CDC_ACM_DATA_EPIN,      \
                            CDC_ACM_DATA_EPOUT)


static const uint8_t m_cdc_acm_class_descriptors[] = {
        APP_USBD_CDC_ACM_DEFAULT_DESC(CDC_ACM_COMM_INTERFACE,
                                      CDC_ACM_COMM_EPIN,
                                      CDC_ACM_DATA_INTERFACE,
                                      CDC_ACM_DATA_EPIN,
                                      CDC_ACM_DATA_EPOUT)
};

/*lint -save -e26 -e64 -e123 -e505 -e651*/

/**
 * @brief CDC_ACM class instance
 * */
APP_USBD_CDC_ACM_GLOBAL_DEF(m_app_cdc_acm,
                            CDC_ACM_INTERFACES_CONFIG(),
                            cdc_acm_user_ev_handler,
                            m_cdc_acm_class_descriptors
);

/*lint -restore*/

static char m_rx_buffer[NRF_DRV_USBD_EPSIZE * 16];
static char m_tx_buffer[NRF_DRV_USBD_EPSIZE * 16];

/**
 * @brief User event handler @ref app_usbd_cdc_acm_user_ev_handler_t (headphones)
 * */
static void cdc_acm_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_cdc_acm_user_event_t event)
{
    app_usbd_cdc_acm_t const * p_cdc_acm = app_usbd_cdc_acm_class_get(p_inst);

    switch (event)
    {
        case APP_USBD_CDC_ACM_USER_EVT_RESUME:
            bsp_board_led_on(LED_USB_RESUME);
            break;
        case APP_USBD_CDC_ACM_USER_EVT_START:
            break;
        case APP_USBD_CDC_ACM_USER_EVT_SUSPEND:
            bsp_board_led_off(LED_USB_RESUME);
            break;
        case APP_USBD_CDC_ACM_USER_EVT_STOP:
            bsp_board_leds_off();
            break;
        case APP_USBD_CDC_ACM_USER_EVT_PORT_OPEN:
        {
            bsp_board_led_on(LED_CDC_ACM_OPEN);

            /*Setup first transfer*/
            ret_code_t ret = app_usbd_cdc_acm_read(&m_app_cdc_acm,
                                                   m_rx_buffer,
                                                   sizeof(m_rx_buffer));
            APP_ERROR_CHECK(ret);
            break;
        }
        case APP_USBD_CDC_ACM_USER_EVT_PORT_CLOSE:
            bsp_board_led_off(LED_CDC_ACM_OPEN);
            break;
        case APP_USBD_CDC_ACM_USER_EVT_TX_DONE:
            bsp_board_led_invert(LED_CDC_ACM_TX);
            break;
        case APP_USBD_CDC_ACM_USER_EVT_RX_DONE:
        {
            /*Get amount of data transfered*/
            size_t size = app_usbd_cdc_acm_rx_size(p_cdc_acm);
            NRF_LOG_INFO("RX: size: %lu char: %c\r\n", size, m_rx_buffer[0]);


            /*Setup next transfer*/
            ret_code_t ret = app_usbd_cdc_acm_read(&m_app_cdc_acm,
                                                   m_rx_buffer,
                                                   sizeof(m_rx_buffer));

            ASSERT(ret == NRF_SUCCESS); /*Should not happen*/
            bsp_board_led_invert(LED_CDC_ACM_RX);
            break;
        }
        default:
            break;
    }
}

#define SERIAL_NUMBER_STRING_SIZE (16)

uint16_t g_extern_serial_number[SERIAL_NUMBER_STRING_SIZE + 1];

static void serial_number_string_create(void)
{
    g_extern_serial_number[0] = (uint16_t)APP_USBD_DESCRIPTOR_STRING << 8 |
                                          sizeof(g_extern_serial_number);

    uint32_t dev_id_hi = NRF_FICR->DEVICEID[1];
    uint32_t dev_id_lo = NRF_FICR->DEVICEID[0];

    uint64_t device_id = (((uint64_t)dev_id_hi) << 32) | dev_id_lo;

    for (size_t i = 1; i < SERIAL_NUMBER_STRING_SIZE + 1; ++i)
    {
        char tmp[2];
        (void)snprintf(tmp, sizeof(tmp), "%x", (unsigned int)(device_id & 0xF));
        g_extern_serial_number[i] = tmp[0];
        device_id >>= 4;
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

    /* Configure LEDs */
    bsp_board_leds_init();
    bsp_board_buttons_init();

    serial_number_string_create();

    ret = app_usbd_init();
    APP_ERROR_CHECK(ret);

    app_usbd_class_inst_t const * class_cdc_acm = app_usbd_cdc_acm_class_inst_get(&m_app_cdc_acm);
    ret = app_usbd_class_append(class_cdc_acm);
    APP_ERROR_CHECK(ret);

    bool last_usb_conn_status = false;
    usb_start();

    while (true)
    {
        last_usb_conn_status = usb_connection_handle(last_usb_conn_status);

        if (bsp_board_button_state_get(BTN_CDC_DATA_SEND))
        {
            static int  frame_counter;

            sprintf(m_tx_buffer, "Hello USB CDC FA demo: %u\r\n", frame_counter);

            ret = app_usbd_cdc_acm_write(&m_app_cdc_acm, m_tx_buffer, sizeof(m_tx_buffer));
            if (ret == NRF_SUCCESS)
            {
                ++frame_counter;
            }
        }

        if (bsp_board_button_state_get(BTN_CDC_NOTIFY_SEND))
        {
            ret = app_usbd_cdc_acm_serial_state_notify(&m_app_cdc_acm,
                                                       APP_USBD_CDC_ACM_SERIAL_STATE_BREAK,
                                                       false);
            UNUSED_VARIABLE(ret);
        }

        UNUSED_RETURN_VALUE(NRF_LOG_PROCESS());
    }
}

/** @} */
