/**
 * \file
 *
 * \brief IL9341 display controller register and bitfield definitions
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
#ifndef DRIVERS_GFX_ILI9341_ILI9341_REGS_H_INCLUDED
#define DRIVERS_GFX_ILI9341_ILI9341_REGS_H_INCLUDED

/* Level 1 Commands (from the display Datasheet) */
#define ILI9341_CMD_NOP                             0x00
#define ILI9341_CMD_SOFTWARE_RESET                  0x01
#define ILI9341_CMD_READ_DISP_ID                    0x04
#define ILI9341_CMD_READ_DISP_STATUS                0x09
#define ILI9341_CMD_READ_DISP_MADCTRL               0x0B
#define ILI9341_CMD_READ_DISP_PIXEL_FORMAT          0x0C
#define ILI9341_CMD_READ_DISP_IMAGE_FORMAT          0x0D
#define ILI9341_CMD_READ_DISP_SIGNAL_MODE           0x0E
#define ILI9341_CMD_READ_DISP_SELF_DIAGNOSTIC       0x0F
#define ILI9341_CMD_ENTER_SLEEP_MODE                0x10
#define ILI9341_CMD_SLEEP_OUT                       0x11
#define ILI9341_CMD_PARTIAL_MODE_ON                 0x12
#define ILI9341_CMD_NORMAL_DISP_MODE_ON             0x13
#define ILI9341_CMD_DISP_INVERSION_OFF              0x20
#define ILI9341_CMD_DISP_INVERSION_ON               0x21
#define ILI9341_CMD_GAMMA_SET                       0x26
#define ILI9341_CMD_DISPLAY_OFF                     0x28
#define ILI9341_CMD_DISPLAY_ON                      0x29
#define ILI9341_CMD_COLUMN_ADDRESS_SET              0x2A
#define ILI9341_CMD_PAGE_ADDRESS_SET                0x2B
#define ILI9341_CMD_MEMORY_WRITE                    0x2C
#define ILI9341_CMD_COLOR_SET                       0x2D
#define ILI9341_CMD_MEMORY_READ                     0x2E
#define ILI9341_CMD_PARTIAL_AREA                    0x30
#define ILI9341_CMD_VERT_SCROLL_DEFINITION          0x33
#define ILI9341_CMD_TEARING_EFFECT_LINE_OFF         0x34
#define ILI9341_CMD_TEARING_EFFECT_LINE_ON          0x35
#define ILI9341_CMD_MEMORY_ACCESS_CONTROL           0x36
#define ILI9341_CMD_VERT_SCROLL_START_ADDRESS       0x37
#define ILI9341_CMD_IDLE_MODE_OFF                   0x38
#define ILI9341_CMD_IDLE_MODE_ON                    0x39
#define ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET         0x3A
#define ILI9341_CMD_WRITE_MEMORY_CONTINUE           0x3C
#define ILI9341_CMD_READ_MEMORY_CONTINUE            0x3E
#define ILI9341_CMD_SET_TEAR_SCANLINE               0x44
#define ILI9341_CMD_GET_SCANLINE                    0x45
#define ILI9341_CMD_WRITE_DISPLAY_BRIGHTNESS        0x51
#define ILI9341_CMD_READ_DISPLAY_BRIGHTNESS         0x52
#define ILI9341_CMD_WRITE_CTRL_DISPLAY              0x53
#define ILI9341_CMD_READ_CTRL_DISPLAY               0x54
#define ILI9341_CMD_WRITE_CONTENT_ADAPT_BRIGHTNESS  0x55
#define ILI9341_CMD_READ_CONTENT_ADAPT_BRIGHTNESS   0x56
#define ILI9341_CMD_WRITE_MIN_CAB_LEVEL             0x5E
#define ILI9341_CMD_READ_MIN_CAB_LEVEL              0x5F
#define ILI9341_CMD_READ_ID1                        0xDA
#define ILI9341_CMD_READ_ID2                        0xDB
#define ILI9341_CMD_READ_ID3                        0xDC

/* Level 2 Commands (from the display Datasheet) */
#define ILI9341_CMD_RGB_SIGNAL_CONTROL              0xB0
#define ILI9341_CMD_FRAME_RATE_CONTROL_NORMAL       0xB1
#define ILI9341_CMD_FRAME_RATE_CONTROL_IDLE_8COLOR  0xB2
#define ILI9341_CMD_FRAME_RATE_CONTROL_PARTIAL      0xB3
#define ILI9341_CMD_DISPLAY_INVERSION_CONTROL       0xB4
#define ILI9341_CMD_BLANKING_PORCH_CONTROL          0xB5
#define ILI9341_CMD_DISPLAY_FUNCTION_CONTROL        0xB6
#define ILI9341_CMD_ENTRY_MODE_SET                  0xB7
#define ILI9341_CMD_BACKLIGHT_CONTROL_1             0xB8
#define ILI9341_CMD_BACKLIGHT_CONTROL_2             0xB9
#define ILI9341_CMD_BACKLIGHT_CONTROL_3             0xBA
#define ILI9341_CMD_BACKLIGHT_CONTROL_4             0xBB
#define ILI9341_CMD_BACKLIGHT_CONTROL_5             0xBC
#define ILI9341_CMD_BACKLIGHT_CONTROL_6             0xBD
#define ILI9341_CMD_BACKLIGHT_CONTROL_7             0xBE
#define ILI9341_CMD_BACKLIGHT_CONTROL_8             0xBF
#define ILI9341_CMD_POWER_CONTROL_1                 0xC0
#define ILI9341_CMD_POWER_CONTROL_2                 0xC1
#define ILI9341_CMD_VCOM_CONTROL_1                  0xC5
#define ILI9341_CMD_VCOM_CONTROL_2                  0xC7
#define ILI9341_CMD_POWER_ON_SEQ_CONTROL            0xCB
#define ILI9341_CMD_POWER_CONTROL_A                 0xCD
#define ILI9341_CMD_POWER_CONTROL_B                 0xCF
#define ILI9341_CMD_NVMEM_WRITE                     0xD0
#define ILI9341_CMD_NVMEM_PROTECTION_KEY            0xD1
#define ILI9341_CMD_NVMEM_STATUS_READ               0xD2
#define ILI9341_CMD_READ_ID4                        0xD3
#define ILI9341_CMD_POSITIVE_GAMMA_CORRECTION       0xE0
#define ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION       0xE1
#define ILI9341_CMD_DIGITAL_GAMMA_CONTROL_1         0xE2
#define ILI9341_CMD_DIGITAL_GAMMA_CONTROL_2         0xE3
#define ILI9341_CMD_DRIVER_TIMING_CONTROL_A         0xE8
#define ILI9341_CMD_DRIVER_TIMING_CONTROL_B         0xEA
#define ILI9341_CMD_ENABLE_3_GAMMA_CONTROL          0xF2
#define ILI9341_CMD_INTERFACE_CONTROL               0xF6
#define ILI9341_CMD_PUMP_RATIO_CONTROL              0xF7

#endif /* DRIVERS_GFX_ILI9341_ILI9341_REGS_H_INCLUDED */
