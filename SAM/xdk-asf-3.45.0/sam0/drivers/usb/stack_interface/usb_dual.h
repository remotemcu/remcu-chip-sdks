/**
 * \file
 *
 * \brief SAM USB Dual Role driver header file.
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

#ifndef _USB_DUAL_H_
#define _USB_DUAL_H_

#include "compiler.h"
#include "preprocessor.h"

/* Get USB pads pins configuration in board configuration */
#include "conf_board.h"
#include "board.h"
#include "extint.h"
#include "port.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup usb_group
 * \defgroup usb_dual_group USB dual role driver
 * USB low-level driver for dual role features
 *
 * @{
 */

bool usb_dual_enable(void);
void usb_dual_disable(void);

/**
 * @name USB ID pin management
 *
 * The ID pin come from the USB connector (A and B receptable) and
 * allows to select the USB mode between host or device.
 * The ID pin can be managed through EIC pin.
 * This feature is optional, and it is enabled if USB_ID_PIN
 * is defined in board.h and CONF_BOARD_USB_ID_DETECT defined in
 * conf_board.h.
*
* @{
*/
#define USB_ID_DETECT        (defined(CONF_BOARD_USB_ID_DETECT))
#define USB_ID_EIC           (defined(USB_ID_PIN) && USB_ID_DETECT)
/** @} */

/**
 * @name USB Vbus management
 *
 * The VBus line can be monitored through a EIC pin and
 * a basic resistor voltage divider.
 * This feature is optional, and it is enabled if USB_VBUS_PIN
 * is defined in board.h and CONF_BOARD_USB_VBUS_DETECT defined in
 * conf_board.h.
 *
 * @{
 */
#define USB_VBUS_DETECT      (defined(CONF_BOARD_USB_VBUS_DETECT))
#define USB_VBUS_EIC         (defined(USB_VBUS_PIN) && USB_VBUS_DETECT)
/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif // _USB_DUAL_H_
