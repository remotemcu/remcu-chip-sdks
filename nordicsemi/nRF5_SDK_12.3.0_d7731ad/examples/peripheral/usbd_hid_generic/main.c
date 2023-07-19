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
#include "app_usbd_hid_generic.h"
#include "app_usbd_hid_mouse.h"
#include "app_usbd_hid_kbd.h"
#include "boards.h"

#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

/**@file
 * @defgroup usbd_hid_generic_example main.c
 * @{
 * @ingroup usbd_hid_generic_example
 * @brief HID generic example
 *
 * This example shows how to use HID class generic. It basically works same as hid_mouse_example.
 * However, generic class allows user to define any other type of reports. All reports in HID generic
 * class has to be handled manually.
 *
 */

/**
 * @brief User event handler
 * */
static void hid_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                app_usbd_hid_user_event_t event);

/**
 * @brief Reuse HID mouse report descriptor for HID generic class
 */
static uint8_t m_generic_rep_dsc[] = APP_USBD_HID_MOUSE_REPORT_DSC_BUTTON(2);


/**
 * @brief Mandatory REPORT descriptor item and optional list of physical descriptors
 */
#define HID_DESCRIPTOR_ITEM_LIST()                           \
(                                                            \
        m_generic_rep_dsc                                    \
)

#define ENDPOINT_LIST()                                      \
(                                                            \
        NRF_DRV_USBD_EPIN1                                   \
)

/**
 * @brief Number of reports defined in report descriptor
 */
#define REPORT_COUNT        1

/**
 * @brief Size of maximum output report. HID generic class will reserve
 *        this buffer size + 1 memory space. */
#define REPORT_OUT_MAXSIZE  0

/*lint -save -e26 -e64 -e123 -e505 -e651*/

/**
 * @brief Global HID generic instance
 */
APP_USBD_HID_GENERIC_GLOBAL_DEF(m_app_hid_generic, 0, hid_user_ev_handler,
                                ENDPOINT_LIST(), HID_DESCRIPTOR_ITEM_LIST(),
                                REPORT_COUNT, REPORT_OUT_MAXSIZE);

/*lint -restore*/

/**
 * @brief Generic (Mouse) report IN buffer
 */
static uint8_t m_input_report[4];

/**
 * @brief GPIO used as LED & buttons in this example
 */
#define LED_USB_RESUME   (BSP_BOARD_LED_0)
#define LED_USB_START    (BSP_BOARD_LED_1)
#define LED_HID_REP_IN   (BSP_BOARD_LED_2)

#define BTN_MOUSE_X_POS    (BSP_BOARD_BUTTON_0)
#define BTN_MOUSE_Y_POS    (BSP_BOARD_BUTTON_1)
#define BTN_MOUSE_LEFT     (BSP_BOARD_BUTTON_2)
#define BTN_MOUSE_RIGHT    (BSP_BOARD_BUTTON_3)

/**
 * @brief Enable power USB detection
 *
 * Configure if example supports USB port connection
 */
#ifndef USBD_POWER_DETECTION
#define USBD_POWER_DETECTION true
#endif

/**
 * @brief Button debounce time
 *
 * Number of microseconds to wait after button press detection
 */
#define DEBOUNCE_DELAY 5000

static void hid_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                app_usbd_hid_user_event_t event)
{
    app_usbd_hid_generic_t const * p_generic = app_usbd_hid_generic_class_get(p_inst);

    switch (event) {
        case APP_USBD_HID_USER_EVT_SUSPEND:
            bsp_board_led_off(LED_USB_RESUME);
            break;
        case APP_USBD_HID_USER_EVT_RESUME:
            bsp_board_led_on(LED_USB_RESUME);
            break;
        case APP_USBD_HID_USER_EVT_START:
            bsp_board_led_on(LED_USB_START);
            break;
        case APP_USBD_HID_USER_EVT_STOP:
            bsp_board_leds_off();
            break;
        case APP_USBD_HID_USER_EVT_OUT_REPORT_READY:
        {
            /* No output report defined for this example.*/
            ASSERT(0);
            break;
        }
        case APP_USBD_HID_USER_EVT_IN_REPORT_DONE:
        {
            uint8_t rep_id = app_usbd_hid_generic_in_report_last_id(p_generic);

            bsp_board_led_invert(LED_HID_REP_IN);

            /*Just assert. Mouse descriptor has only one IN report ID (default, equal to 0)*/
            ASSERT(rep_id == 0);

            break;
        }
        default:
            break;
    }
}

/**
 * @brief HID generic mouse action types
 */
typedef enum {
    HID_GENERIC_MOUSE_VERTICAL,
    HID_GENERIC_MOUSE_HORIZONTAL,
    HID_GENERIC_MOUSE_BTN_LEFT,
    HID_GENERIC_MOUSE_BTN_RIGHT,
} hid_generic_mouse_action_t;


/**
 * @brief HID generic IN report send handling
 * */
static void hid_generic_mouse_action(hid_generic_mouse_action_t action, int8_t param)
{
    uint8_t * in_rep = m_input_report;

    uint8_t * in_rep_buttons = &in_rep[0];
    int8_t  * in_rep_x_axis  = (int8_t *)&in_rep[1];
    int8_t  * in_rep_y_axis  = (int8_t *)&in_rep[2];
    int8_t  * in_rep_wheel   = (int8_t *)&in_rep[3];

    UNUSED_VARIABLE(in_rep_wheel);

    if (param == 0)
    {
        /*No action*/
        return;
    }

    /*
     * Update IN transfer buffer.
     *  - increment for axis
     *  - bit SET/CLR for buttons
     */
    switch (action)
    {
        case HID_GENERIC_MOUSE_VERTICAL:
            *in_rep_x_axis += param;
            break;
        case HID_GENERIC_MOUSE_HORIZONTAL:
            *in_rep_y_axis += param;
            break;
        case HID_GENERIC_MOUSE_BTN_RIGHT:
            param == 1 ? SET_BIT(*in_rep_buttons, 0) : CLR_BIT(*in_rep_buttons, 0);
            break;
        case HID_GENERIC_MOUSE_BTN_LEFT:
            param == 1 ? SET_BIT(*in_rep_buttons, 1) : CLR_BIT(*in_rep_buttons, 1);
            break;
    }
}

/**
 * @brief Mouse speed (value send via HID when board button is pressed).
 * */
#define PRESS_OFFSET (3)

static void hid_action(uint32_t btn_state)
{
    bool val;
    bool in_report_required = true;

    /*Get last button state.*/
    uint8_t button_previous = m_input_report[0];

    if (app_usbd_hid_generic_report_in_done(&m_app_hid_generic, 0))
    {
        /* Clear relative mouse offsets only if previous transfer has been done. */
        m_input_report[1] = m_input_report[2] = m_input_report[3] = 0;
    }

    val = (btn_state & (1u << BTN_MOUSE_X_POS));
    hid_generic_mouse_action(HID_GENERIC_MOUSE_VERTICAL, val ? PRESS_OFFSET : 0);

    val = (btn_state & (1u << BTN_MOUSE_Y_POS));
    hid_generic_mouse_action(HID_GENERIC_MOUSE_HORIZONTAL, val ? PRESS_OFFSET : 0);

    val = (btn_state & (1u << BTN_MOUSE_RIGHT));
    hid_generic_mouse_action(HID_GENERIC_MOUSE_BTN_RIGHT, val ? 1 : -1);

    val = (btn_state & (1u << BTN_MOUSE_LEFT));
    hid_generic_mouse_action(HID_GENERIC_MOUSE_BTN_LEFT, val ? 1 : -1);

    if ((m_input_report[1]  == 0)  &&
        (m_input_report[2] == 0)   &&
        (m_input_report[3]   == 0) &&
        (m_input_report[0] == button_previous))
    {

        /* New IN transfer is not required. State hasn't been changed */
        in_report_required = false;
    }

    if (in_report_required != false)
    {
        /*Trigger new IN report*/
        (void)app_usbd_hid_generic_report_in_set(&m_app_hid_generic,
                                                 0,
                                                 m_input_report,
                                                 sizeof(m_input_report));
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

    /* Configure LEDs and buttons */
    bsp_board_leds_init();
    bsp_board_buttons_init();

    ret = app_usbd_init();
    APP_ERROR_CHECK(ret);

    app_usbd_class_inst_t const * class_inst_generic;
    class_inst_generic = app_usbd_hid_generic_class_inst_get(&m_app_hid_generic);
    ret = app_usbd_class_append(class_inst_generic);
    APP_ERROR_CHECK(ret);

    bool last_usb_conn_status = false;
    usb_start();

    while (true)
    {
        last_usb_conn_status = usb_connection_handle(last_usb_conn_status);

        /*Perform buttons read and simple debounce*/
        uint32_t previous =
             (((uint32_t)bsp_board_button_state_get(BTN_MOUSE_X_POS ) ? 1 : 0)
                     << BTN_MOUSE_X_POS) |
             (((uint32_t)bsp_board_button_state_get(BTN_MOUSE_Y_POS )? 1 : 0)
                     << BTN_MOUSE_Y_POS)  |
             (((uint32_t)bsp_board_button_state_get(BTN_MOUSE_LEFT ) ? 1 : 0)
                     << BTN_MOUSE_LEFT)   |
             (((uint32_t)bsp_board_button_state_get(BTN_MOUSE_RIGHT )? 1 : 0)
                     << BTN_MOUSE_RIGHT);
        nrf_delay_us(DEBOUNCE_DELAY);
        uint32_t actual =
             (((uint32_t)bsp_board_button_state_get(BTN_MOUSE_X_POS ) ? 1 : 0)
                     << BTN_MOUSE_X_POS) |
             (((uint32_t)bsp_board_button_state_get(BTN_MOUSE_Y_POS ) ? 1 : 0)
                     << BTN_MOUSE_Y_POS)  |
             (((uint32_t)bsp_board_button_state_get(BTN_MOUSE_LEFT ) ? 1 : 0)
                     << BTN_MOUSE_LEFT)   |
             (((uint32_t)bsp_board_button_state_get(BTN_MOUSE_RIGHT ) ? 1 : 0)
                     << BTN_MOUSE_RIGHT);

        if (previous == actual)
        {
            hid_action(actual);
        }

        UNUSED_RETURN_VALUE(NRF_LOG_PROCESS());
    }
}
