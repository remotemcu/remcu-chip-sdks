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
#include "app_usbd_hid_mouse.h"
#include "app_usbd_hid_kbd.h"
#include "boards.h"

#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

/**
 * @brief User event handler, HID mouse
 * */
static void hid_mouse_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_hid_user_event_t event);

/**
 * @brief User event handler, HID keyboard
 * */
static void hid_kbd_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_hid_user_event_t event);

/**
 * @brief Enable HID mouse class
 * */
#define CONFIG_HAS_MOUSE    1

/**
 * @brief Enable HID keyboard class
 * */
#define CONFIG_HAS_KBD      1


/**
 * @brief USB composite interface enumerator
 * */
enum {
    APP_USBD_INTERFACE_MOUSE = 0,
    APP_USBD_INTERFACE_KBD = APP_USBD_INTERFACE_MOUSE + CONFIG_HAS_MOUSE,
    APP_USBD_INTERFACE_LAST = APP_USBD_INTERFACE_KBD + CONFIG_HAS_KBD,
};


/**
 * @brief Mouse button count
 * */
#define MOUSE_BUTTON_COUNT 2

/*lint -save -e26 -e64 -e123 -e505 -e651*/

/**
 * @brief Global HID mouse instance
 * */
APP_USBD_HID_MOUSE_GLOBAL_DEF(m_app_hid_mouse,
                              APP_USBD_INTERFACE_MOUSE,
                              NRF_DRV_USBD_EPIN1,
                              MOUSE_BUTTON_COUNT,
                              hid_mouse_user_ev_handler
);

/**
 * @brief Global HID keyboard instance
 * */
APP_USBD_HID_KBD_GLOBAL_DEF(m_app_hid_kbd,
                            APP_USBD_INTERFACE_KBD,
                            NRF_DRV_USBD_EPIN2,
                            hid_kbd_user_ev_handler
);

/*lint -restore*/

/**
 * @brief Button debounce time
 *
 * Number of microseconds to wait after button press detection
 */
#define DEBOUNCE_DELAY 5000

#define LED_USB_RESUME     (BSP_BOARD_LED_0)
#define LED_USB_START      (BSP_BOARD_LED_1)
#define LED_HID_REP_IN     (BSP_BOARD_LED_2)
#define LED_HID_REP_OUT    (BSP_BOARD_LED_3)

#define BTN_MOUSE_X_POS    (BSP_BOARD_BUTTON_0)
#define BTN_MOUSE_LEFT     (BSP_BOARD_BUTTON_1)
#define BTN_KBD_SHIFT      (BSP_BOARD_BUTTON_2)
#define BTN_KBD_LETTER     (BSP_BOARD_BUTTON_3)

/**
 * @brief Enable power USB detection
 *
 * Configure if example supports USB port connection
 */
#ifndef USBD_POWER_DETECTION
#define USBD_POWER_DETECTION true
#endif

/**
 * @brief Mouse speed (value send via HID when board button is pressed).
 * */
#define PRESS_OFFSET (3)

static void mouse_action(uint32_t button_state)
{
    bool val;

    val = (button_state & (1u << BTN_MOUSE_X_POS));
    (void)app_usbd_hid_mouse_x_move(&m_app_hid_mouse, val ? PRESS_OFFSET : 0);

    val = (button_state & (1u << BTN_MOUSE_LEFT));
    (void)app_usbd_hid_mouse_button_state(&m_app_hid_mouse, 0, val);

}

static void kbd_action(uint32_t button_state)
{
    bool val;

    val = (button_state & (1u << BTN_KBD_SHIFT));
    (void)app_usbd_hid_kbd_modifier_state_set(&m_app_hid_kbd, APP_USBD_HID_KBD_MODIFIER_LEFT_SHIFT, val);

    val = (button_state & (1u << BTN_KBD_LETTER));
    (void)app_usbd_hid_kbd_key_control(&m_app_hid_kbd, APP_USBD_HID_KBD_G, val);
}


static void kbd_status(void)
{
    bool v;
    v = app_usbd_hid_kbd_led_state_get(&m_app_hid_kbd, APP_USBD_HID_KBD_LED_NUM_LOCK);
    v ? bsp_board_led_on(LED_HID_REP_IN) : bsp_board_led_off(LED_HID_REP_IN);

    v = app_usbd_hid_kbd_led_state_get(&m_app_hid_kbd, APP_USBD_HID_KBD_LED_CAPS_LOCK);
    v ? bsp_board_led_on(LED_HID_REP_OUT) : bsp_board_led_off(LED_HID_REP_OUT);
}


static void hid_mouse_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                      app_usbd_hid_user_event_t event)
{
    UNUSED_PARAMETER(p_inst);
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
            /* No output report defined for HID mouse.*/
            ASSERT(0);
            break;
        case APP_USBD_HID_USER_EVT_IN_REPORT_DONE:
            bsp_board_led_invert(LED_HID_REP_IN);
            break;
        default:
            break;
    }
}

static void hid_kbd_user_ev_handler(app_usbd_class_inst_t const * p_inst,
                                    app_usbd_hid_user_event_t event)
{
    UNUSED_PARAMETER(p_inst);
    switch (event) {
        case APP_USBD_HID_USER_EVT_OUT_REPORT_READY:
            /* Only one output report IS defined for HID keyboard class. Update LEDs state. */
            bsp_board_led_invert(LED_HID_REP_OUT);
            kbd_status();
            break;
        case APP_USBD_HID_USER_EVT_IN_REPORT_DONE:
            bsp_board_led_invert(LED_HID_REP_IN);
            break;
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

    /* Configure LEDs and buttons */
    bsp_board_leds_init();
    bsp_board_buttons_init();

    ret = app_usbd_init();
    APP_ERROR_CHECK(ret);

#if CONFIG_HAS_MOUSE
    app_usbd_class_inst_t const * class_inst_mouse;
    class_inst_mouse = app_usbd_hid_mouse_class_inst_get(&m_app_hid_mouse);
    ret = app_usbd_class_append(class_inst_mouse);
    APP_ERROR_CHECK(ret);
#endif

#if CONFIG_HAS_KBD
    app_usbd_class_inst_t const * class_inst_kbd;
    class_inst_kbd = app_usbd_hid_kbd_class_inst_get(&m_app_hid_kbd);
    ret = app_usbd_class_append(class_inst_kbd);
    APP_ERROR_CHECK(ret);
#endif

    bool last_usb_conn_status = false;
    usb_start();

    while (true)
    {
        last_usb_conn_status = usb_connection_handle(last_usb_conn_status);

        /*Perform buttons read and simple debounce*/
        uint32_t previous =
             (((uint32_t)bsp_board_button_state_get(BTN_MOUSE_X_POS ) ? 1 : 0)
                     << BTN_MOUSE_X_POS) |
             (((uint32_t)bsp_board_button_state_get(BTN_MOUSE_LEFT )? 1 : 0)
                     << BTN_MOUSE_LEFT)  |
             (((uint32_t)bsp_board_button_state_get(BTN_KBD_SHIFT ) ? 1 : 0)
                     << BTN_KBD_SHIFT)   |
             (((uint32_t)bsp_board_button_state_get(BTN_KBD_LETTER )? 1 : 0)
                     << BTN_KBD_LETTER);
        nrf_delay_us(DEBOUNCE_DELAY);
        uint32_t actual =
             (((uint32_t)bsp_board_button_state_get(BTN_MOUSE_X_POS ) ? 1 : 0)
                     << BTN_MOUSE_X_POS) |
             (((uint32_t)bsp_board_button_state_get(BTN_MOUSE_LEFT ) ? 1 : 0)
                     << BTN_MOUSE_LEFT)  |
             (((uint32_t)bsp_board_button_state_get(BTN_KBD_SHIFT ) ? 1 : 0)
                     << BTN_KBD_SHIFT)   |
             (((uint32_t)bsp_board_button_state_get(BTN_KBD_LETTER ) ? 1 : 0)
                     << BTN_KBD_LETTER);

        if (previous == actual)
        {
            mouse_action(actual);
            kbd_action(actual);
        }

        UNUSED_RETURN_VALUE(NRF_LOG_PROCESS());
    }
}
