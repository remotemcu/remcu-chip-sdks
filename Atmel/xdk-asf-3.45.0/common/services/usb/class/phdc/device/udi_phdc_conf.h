/**
 * \file
 *
 * \brief Default PHDC configuration for a USB Device with a single interface
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

#ifndef _UDI_PHDC_CONF_H_
#define _UDI_PHDC_CONF_H_

/**
 * \addtogroup udi_phdc_group_single_desc
 * @{
 */

/* ! Control endpoint size */
#define  USB_DEVICE_EP_CTRL_SIZE       32 /* 8 is not supported by PHDC */

/* ! Endpoint numbers used by PHDC interface */
#define  UDI_PHDC_EP_BULK_OUT          (1 | USB_EP_DIR_OUT)
#define  UDI_PHDC_EP_BULK_IN           (2 | USB_EP_DIR_IN)
#define  UDI_PHDC_EP_INTERRUPT_IN      (3 | USB_EP_DIR_IN)

/* ! Endpoint sizes used by PHDC interface */
#define  UDI_PHDC_EP_SIZE_BULK_OUT     32
#define  UDI_PHDC_EP_SIZE_BULK_IN      32
#define  UDI_PHDC_EP_SIZE_INT_IN       8

/* ! Interface number */
#define  UDI_PHDC_IFACE_NUMBER          0

/**
 * \name UDD Configuration
 * @{
 */
#undef USB_DEVICE_MAX_EP   // undefine this definition in header file
/* ! 2 or 3 endpoints used by PHDC interface */
#if ((UDI_PHDC_QOS_IN & USB_PHDC_QOS_LOW_GOOD) == USB_PHDC_QOS_LOW_GOOD)
#define  USB_DEVICE_MAX_EP             3
#else
#define  USB_DEVICE_MAX_EP             2
#endif
/* @} */

/* @} */

#include "udi_phdc.h"

#endif /* _UDI_PHDC_CONF_H_ */
