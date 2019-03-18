/**
 * \file
 *
 * \brief Board configuration.
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

#ifndef CONF_BOARD_H_INCLUDED
#define CONF_BOARD_H_INCLUDED

/** Enable AAT3155 component to control LCD backlight. */
#define CONF_BOARD_AAT3155

/** Enable ILI9325 component to control LCD. */
#define CONF_BOARD_ILI9325

/** Enable OV7740 image sensor. */
#define CONF_BOARD_OV7740_IMAGE_SENSOR

/** Configure TWI0 pins (for OV7740  communications). */
#define CONF_BOARD_TWI0

/** Configure PCK0 pins (for OV7740  communications). */
#define CONF_BOARD_PCK0

/* Enable SRAM. */
#define CONF_BOARD_SRAM

/* TWI board defines. */
#define ID_BOARD_TWI                   ID_TWI0
#define BOARD_TWI                      TWI0
#define BOARD_TWI_IRQn                 TWI0_IRQn

/* Push button board defines. */
#define PUSH_BUTTON_ID                 PIN_PUSHBUTTON_1_ID
#define PUSH_BUTTON_PIO                PIN_PUSHBUTTON_1_PIO
#define PUSH_BUTTON_PIN_MSK            PIN_PUSHBUTTON_1_MASK
#define PUSH_BUTTON_ATTR               PIN_PUSHBUTTON_1_ATTR

/* SRAM board defines. */
#define SRAM_BASE                      (0x60000000UL) // SRAM adress
#define SRAM_CS                        (0UL)
#define CAP_DEST                       SRAM_BASE

/* LCD board defines. */
#define ILI9325_LCD_CS                 (2UL) // Chip select number
#define IMAGE_WIDTH                    (320UL)
#define IMAGE_HEIGHT                   (240UL)

/* Image sensor board defines. */
// Image sensor Power pin.
#define OV_POWER_PIO                   OV_SW_OVT_PIO
#define OV_POWER_MASK                  OV_SW_OVT_MASK
// Image sensor VSYNC pin.
#define OV7740_VSYNC_PIO	       OV_VSYNC_PIO
#define OV7740_VSYNC_ID		       OV_VSYNC_ID
#define OV7740_VSYNC_MASK              OV_VSYNC_MASK
#define OV7740_VSYNC_TYPE              OV_VSYNC_TYPE
// Image sensor data pin.
#define OV7740_DATA_BUS_PIO            OV_DATA_BUS_PIO
#define OV7740_DATA_BUS_ID             OV_DATA_BUS_ID

#endif /* CONF_BOARD_H_INCLUDED */
