/**
 * \file
 *
 * \brief Declaration of main function used by CDC unit test
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _UNIT_TEST_H_
#define _UNIT_TEST_H_

/*! \brief Called by UDI interface
 * Callback running when USB Host enable CDC interface
 *
 * \retval true if CDC startup is ok
 */
bool main_cdc_enable(void);

/*! \brief Called by UDI interface
 * Callback running when USB Host disable CDC interface
 */
void main_cdc_disable(void);

/*! \brief Called by UDI interface
 * Callback running when USB Host send a port configuration
 */
void main_cdc_config(void);

/*! \brief Called when Vbus line state change
 */
void main_vbus_action(bool b_high);

/*! \brief Called when a start of frame is received on USB line
 */
void main_sof_action(void);

/*! \brief Enters the application in low power mode
 * Callback called when USB host sets USB line in suspend state
 */
void main_suspend_action(void);

/*! \brief Called by UDD when the USB line exit of suspend state
 */
void main_resume_action(void);

/*! \brief Called by UDC when USB Host request to enable remote wakeup
 */
void main_remotewakeup_enable(void);

/*! \brief Called by UDC when USB Host request to disable remote wakeup
 */
void main_remotewakeup_disable(void);

#endif // _UNIT_TEST_H_
