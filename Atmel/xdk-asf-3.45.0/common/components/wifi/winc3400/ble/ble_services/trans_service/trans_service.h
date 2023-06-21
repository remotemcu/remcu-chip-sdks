/**
 * \file
 *
 * \brief Transparent Service declarations
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#ifndef __TRANS_SERVICE_H__
#define __TRANS_SERVICE_H__

#include "at_ble_api.h"
#include "ble_manager.h"

/**
@defgroup sdk Atmel BLE SDK

@{
*/

/**@brief Tx characteristic value after defining the services using bat_primary_service_define
 *
 * @param[in] trans_service trans service instance
 * @param[in] trans_tx_value value for Tx
  * @param[in] len of Tx value
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t trans_update_tx_char_value (gatt_service_handler_t *trans_service, uint8_t* trans_tx_value, uint8_t len);

/**@brief Ctrl characteristic value after defining the services using bat_primary_service_define
 *
 * @param[in] trans_service trans service instance
 * @param[in] trans_ctrl_value value for ctrl
  * @param[in] len of Tx value
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t trans_update_ctrl_char_value (gatt_service_handler_t *trans_service, uint8_t* trans_ctrl_value, uint8_t len);

/**@brief transparent service and characteristic initialization(Called only once by user).
 *
 * @param[in] trans_service trans service instance
 *
 * @return none
 */
void trans_service_init(gatt_service_handler_t *trans_service);

/**@brief Register a transparent service instance inside stack. 
 *
 * @param[in] trans_service trans service instance
 *
 * @return @ref AT_BLE_SUCCESS operation completed successfully
 * @return @ref AT_BLE_FAILURE Generic error.
 */
at_ble_status_t trans_service_primary_service_define(gatt_service_handler_t *trans_service);

 /** @}*/

#endif /* __TRANS_SERVICE_H__ */
