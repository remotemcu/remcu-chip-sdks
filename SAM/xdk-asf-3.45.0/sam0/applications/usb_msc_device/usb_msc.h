/**
 * \file
 *
 * \brief USB Mass Storage Class Driver
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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* USB GCLK generator */
#define USB_GCLK_GEN                    1
/* USB SOF callback*/
#define USB_CALLBACK_SOF                main_callback_sof

/*Total number of endpoint is 3 control endpoint -1, BULK OUT Endpoint -2*/
#define TOTAL_EP                        3
/* Default Control Endpoint is 0 */
#define CTRL_EP                         0
/* BULK IN Endpoint is 1 */
#define MSC_BULK_IN_EP                  1
/* BULK OUT Endpoint is 2 */
#define MSC_BULK_OUT_EP                 2
/*Control Endpoint size - 64 bytes */
#define CTRL_EP_SIZE                    64
/*BULK IN/OUT Endpoint size - 64 bytes */
#define MSC_BULK_IN_EP_SIZE             64
#define MSC_BULK_OUT_EP_SIZE            64

/* USB standard request code */
#define STD_GET_STATUS_ZERO             0x0080
#define STD_GET_STATUS_INTERFACE        0x0081
#define STD_GET_STATUS_ENDPOINT         0x0082

#define STD_CLEAR_FEATURE_ZERO          0x0100
#define STD_CLEAR_FEATURE_INTERFACE     0x0101
#define STD_CLEAR_FEATURE_ENDPOINT      0x0102

#define STD_SET_FEATURE_ZERO            0x0300
#define STD_SET_FEATURE_INTERFACE       0x0301
#define STD_SET_FEATURE_ENDPOINT        0x0302

#define STD_SET_ADDRESS                 0x0500
#define STD_GET_DESCRIPTOR              0x0680
#define STD_SET_DESCRIPTOR              0x0700
#define STD_GET_CONFIGURATION           0x0880
#define STD_SET_CONFIGURATION           0x0900
#define STD_GET_INTERFACE               0x0A81
#define STD_SET_INTERFACE               0x0B01
#define STD_SYNCH_FRAME                 0x0C82

/*MSC class specific request*/
#define GET_MAX_LUN                     0xFEA1
#define MASS_STORAGE_RESET              0xFF21

#define MIN(a, b)                       (((a) < (b)) ? (a) : (b))
#define COMPILER_PACK_SET(alignment)    COMPILER_PRAGMA(pack(alignment))
#define COMPILER_PACK_RESET()           COMPILER_PRAGMA(pack())

#if defined (USB_CALLBACK_SOF)
typedef void (*callback_t)(void);

void usb_set_callback(callback_t callback_func);
void main_callback_sof(void);

#endif

void usb_init(void);
int32_t USB_Write(uint8_t *pData, int32_t length, uint8_t ep_num);
