/**
 *
 * \file
 *
 * \brief WINC3400 BLE Application example code.
 *
 * Copyright (c) 2017-2018 Microchip Technology Inc. and its subsidiaries.
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
#ifndef M2M_BLE_H_
#define M2M_BLE_H_

#include "driver/include/m2m_types.h"
#include "driver/include/m2m_wifi.h"
#include "at_ble_api.h"
#include "ble_manager.h"

#define M2M_DEVICE_NAME				"WINC3400_00:00"
#define MAC_ADDRESS					{0xf8, 0xf0, 0x05, 0x45, 0xD4, 0x84}

sint8 m2m_ble_init(void);

sint8 m2m_ble_wifi_init(tstrWifiInitParam * param);

sint8 m2m_ble_event_get(at_ble_events_t* event, at_ble_event_parameter_t* params);

void m2m_ble_api_write_func(uint8* msg, uint32 len);
void m2m_ble_wifi_callback(uint8 u8MsgType, void * pvMsg);

#endif /* M2M_BLE_H_ */