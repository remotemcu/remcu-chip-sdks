/**
 * \file
 *
 * \brief Common API for USB Host Interface
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

#ifndef _UHI_H_
#define _UHI_H_

#include "conf_usb_host.h"
#include "usb_protocol.h"
#include "uhc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup usb_host_group
 * \defgroup uhi_group USB Host Interface (UHI)
 * The UHI provides a common API for all classes,
 * and this is used by UHC for the main control of USB host interface.
 * @{
 */

/**
 * \brief UHI API.
 *
 * The callbacks within this structure are called only by
 * USB Host Controller (UHC)
 */
typedef struct {
	/**
	 * \brief Install interface
	 * Allocate interface endpoints if supported.
	 *
	 * \param uhc_device_t    Device to request
	 *
	 * \return status of the install
	 */
	uhc_enum_status_t (*install)(uhc_device_t*);

	/**
	 * \brief Enable the interface.
	 *
	 * Enable a USB interface corresponding to UHI.
	 *
	 * \param uhc_device_t    Device to request
	 */
	void (*enable)(uhc_device_t*);

	/**
	 * \brief Uninstall the interface (if installed)
	 *
	 * \param uhc_device_t    Device to request
	 */
	void (*uninstall)(uhc_device_t*);

	/**
	 * \brief Signal that a SOF has occurred
	 */
	void (*sof_notify)(bool b_micro);
} uhi_api_t;

//@}

#ifdef __cplusplus
}
#endif
#endif // _UHI_H_
