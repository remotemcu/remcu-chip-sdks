/**
 * \file
 *
 * \brief USB configuration file
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

#ifndef _CONF_USB_H_
#define _CONF_USB_H_

#include "compiler.h"

/**
 * USB Device Configuration
 * @{
 */

/* ! Device definition (mandatory) */
#define  USB_DEVICE_VENDOR_ID             USB_VID_ATMEL
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_ASF_PHDC
#define  USB_DEVICE_MAJOR_VERSION         1
#define  USB_DEVICE_MINOR_VERSION         0
#define  USB_DEVICE_POWER                 100 /* Consumption on Vbus line (mA) */
#define  USB_DEVICE_ATTR \
	(USB_CONFIG_ATTR_SELF_POWERED)
/* (USB_CONFIG_ATTR_BUS_POWERED) */
/* (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_SELF_POWERED) */
/* (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_BUS_POWERED) */

/* ! USB Device string definitions (Optional) */
#define  USB_DEVICE_MANUFACTURE_NAME      "ATMEL AVR"
#define  USB_DEVICE_PRODUCT_NAME          "PHDC"
/* #define  USB_DEVICE_SERIAL_NAME           "12...EF" */

/**
 * Device speeds support
 * Low speed is not authorized
 * @{
 */
/* ! To authorize the High speed */
#if (UC3A3 || UC3A4)
/* #define  USB_DEVICE_HS_SUPPORT */
#elif (SAM3XA || SAM3U)
/* #define  USB_DEVICE_HS_SUPPORT */
#endif
/* @} */

/**
 * USB Device Callbacks definitions (Optional)
 * @{
 */
#define  UDC_VBUS_EVENT(b_vbus_high)
#define  UDC_SOF_EVENT()                  main_sof_action()
#define  UDC_SUSPEND_EVENT()              main_suspend_action()
#define  UDC_RESUME_EVENT()               main_resume_action()
/* ! Mandatory when USB_DEVICE_ATTR authorizes remote wakeup feature */
/* #define  UDC_REMOTEWAKEUP_ENABLE()        user_callback_remotewakeup_enable() */
/* extern void user_callback_remotewakeup_enable(void); */
/* #define  UDC_REMOTEWAKEUP_DISABLE()
 *       user_callback_remotewakeup_disable() */
/* extern void user_callback_remotewakeup_disable(void); */
/* ! When a extra string descriptor must be supported
 * other than manufacturer, product and serial string */
/* #define  UDC_GET_EXTRA_STRING() */
/* @} */
/* @} */

/**
 * USB Interface Configuration
 * @{
 */

/**
 * Configuration of PHDC interface
 * @{
 */
/* ! Interface callback definition */
#define  UDI_PHDC_ENABLE_EXT()          main_phdc_enable()
#define  UDI_PHDC_DISABLE_EXT()         main_phdc_disable()

/* ! Select data format of application */
/* ! USB_PHDC_DATAMSG_FORMAT_VENDOR or USB_PHDC_DATAMSG_FORMAT_11073_20601 */
#define  UDI_PHDC_DATAMSG_FORMAT       USB_PHDC_DATAMSG_FORMAT_11073_20601
/* ! If USB_PHDC_DATAMSG_FORMAT_11073_20601 then define specialization(s)
 * Note: 4113(Dec) for BloodGlucose Define in 11073_20601 */
#define  UDI_PHDC_SPECIALIZATION       {0x1011}

/* ! Defines the QOS need for each transfer direction */

/*
#define  UDI_PHDC_QOS_OUT              \
		(USB_PHDC_QOS_MEDIUM_BETTER|USB_PHDC_QOS_HIGH_BEST)
#define  UDI_PHDC_QOS_IN               \
		(USB_PHDC_QOS_LOW_GOOD|USB_PHDC_QOS_MEDIUM_BETTER|USB_PHDC_QOS_MEDIUM_BEST)
*/
#define  UDI_PHDC_QOS_OUT \
	(USB_PHDC_QOS_MEDIUM_BEST)
#define  UDI_PHDC_QOS_IN \
	(USB_PHDC_QOS_MEDIUM_BEST)

/* ! The following METADATAs can be send during USB enumeration
 * for each endpoints (optional).
 * It can define the Opaque data format of each endpoints
 * These must be up to 253 and recommended to be less than 30.
 */

/*
#define  UDI_PHDC_METADATA_DESC_BULK_IN   {0x01,0x02,0x03}
#define  UDI_PHDC_METADATA_DESC_BULK_OUT  {0x01,0x02,0x03}
#define  UDI_PHDC_METADATA_DESC_INT_IN    {0x01,0x02,0x03}
*/

/* @} */
/* @} */

/**
 * USB Device Driver Configuration
 * @{
 */
/* @} */

/* ! The includes of classes and other headers must be done at the end of this
 * file to avoid compile error */
#include "udi_phdc_conf.h"
#include "main.h"

#endif /* _CONF_USB_H_ */
