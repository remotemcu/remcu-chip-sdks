/**
 * \file
 *
 * \brief Common User Interface for USB application
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _UI_H_
#define _UI_H_

//! \brief Initializes the user interface
void ui_init(void);

//! \brief Sets the user interface in power down mode
void ui_powerdown(void);

//! \brief Enables the asynchronous interrupts of the user interface
void ui_wakeup_enable(void);

//! \brief Disables the asynchronous interrupts of the user interface
void ui_wakeup_disable(void);

//! \brief Exits the user interface of power down mode
void ui_wakeup(void);

//! \name Callback to show the MSC read and write access
//! @{
void ui_start_read(void);
void ui_stop_read(void);
void ui_start_write(void);
void ui_stop_write(void);
//! @}

/*! \brief This process is called each 1ms
 * It is called only if the USB interface is enabled.
 *
 * \param framenumber  Current frame number
 */
void ui_process(uint16_t framenumber);

#endif // _UI_H_
