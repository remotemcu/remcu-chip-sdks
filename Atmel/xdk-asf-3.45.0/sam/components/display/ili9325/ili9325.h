/**
 * \file
 *
 * \brief API driver for ILI9325 TFT display component.
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef ILI9325_H_INCLUDED
#define ILI9325_H_INCLUDED

#include "compiler.h"
#include "board.h"
#include "conf_ili9325.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
 extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/** Type define for an integer type large enough to store a pixel color. */
typedef uint32_t ili9325_color_t;

/** Type define for an integer type large enough to store a pixel coordinate.
 */
typedef int16_t ili9325_coord_t;


/** This macro generates a 16-bit native color for the display from a
 *  24-bit RGB value.
 */
#define ILI9325_COLOR(r, g, b) ((r<<16) | (g << 8) | b)

typedef ili9325_color_t gfx_color_t;
typedef int16_t gfx_coord_t;

/** Bit mask for flipping X for ili9325_set_orientation() */
#define ILI9325_FLIP_X 1
/** Bit mask for flipping Y for ili9325_set_orientation() */
#define ILI9325_FLIP_Y 2
/** Bit mask for swapping X and Y for ili9325_set_orientation() */
#define ILI9325_SWITCH_XY 4

/** Height of display using swapped X/Y orientation */
#define ILI9325_SWITCH_XY_HEIGHT 240

/** Width of display using swapped X/Y orientation */
#define ILI9325_SWITCH_XY_WIDTH  320

/* ILI9325 screen size */
#define ILI9325_LCD_WIDTH  240
#define ILI9325_LCD_HEIGHT 320
/* ILI9325 ID code */
#define ILI9325_DEVICE_CODE (0x9325u)

/* ILI9325 LCD Registers */

/* Driver Code Read */
#define ILI9325_DEVICE_CODE_REG (0x00u)

/* -------- ILI9325_START_OSC_CTRL : (Offset: 0x00) Start Oscillator Control -------- */
#define ILI9325_START_OSC_CTRL    (0x00u)
#define ILI9325_START_OSC_CTRL_EN (0x1u << 0)

/* -------- ILI9325_DRIVER_OUTPUT_CTRL1 : (Offset: 0x01) Driver Output Control 1 -------- */
#define ILI9325_DRIVER_OUTPUT_CTRL1    (0x01u)
#define ILI9325_DRIVER_OUTPUT_CTRL1_SS (0x1u << 8)
#define ILI9325_DRIVER_OUTPUT_CTRL1_SM (0x1u << 10)

/* -------- ILI9325_LCD_DRIVING_CTRL : (Offset: 0x02) LCD Driving Control -------- */
#define ILI9325_LCD_DRIVING_CTRL       (0x02u)
#define ILI9325_LCD_DRIVING_CTRL_EOR   (0x1u << 8)
#define ILI9325_LCD_DRIVING_CTRL_BC0   (0x1u << 9)
#define ILI9325_LCD_DRIVING_CTRL_BIT10 (0x1u << 10)

/* -------- ILI9325_ENTRY_MODE : (Offset: 0x03) Entry Mode -------- */
#define ILI9325_ENTRY_MODE           (0x03u)
#define ILI9325_ENTRY_MODE_AM        (0x1u << 3)
#define ILI9325_ENTRY_MODE_ID_POS     4
#define ILI9325_ENTRY_MODE_ID_MSK    (0x3u << ILI9325_ENTRY_MODE_ID_POS)
#define ILI9325_ENTRY_MODE_ID(value) ((ILI9325_ENTRY_MODE_ID_MSK & ((value) << ILI9325_ENTRY_MODE_ID_POS)))
#define ILI9325_ENTRY_MODE_ORG       (0x1u << 7)
#define ILI9325_ENTRY_MODE_HWM       (0x1u << 9)
#define ILI9325_ENTRY_MODE_BGR       (0x1u << 12)
#define ILI9325_ENTRY_MODE_DFM       (0x1u << 14)
#define ILI9325_ENTRY_MODE_TRI       (0x1u << 15)

/* -------- ILI9325_RESIZE_CTRL : (Offset: 0x04) Resize Control -------- */
#define ILI9325_RESIZE_CTRL            (0x04u)
#define ILI9325_RESIZE_CTRL_RSZ_POS     0
#define ILI9325_RESIZE_CTRL_RSZ_MSK    (0x3u << ILI9325_RESIZE_CTRL_RSZ_POS)
#define ILI9325_RESIZE_CTRL_RSZ(value) ((ILI9325_RESIZE_CTRL_RSZ_MSK & ((value) << ILI9325_RESIZE_CTRL_RSZ_POS)))
#define ILI9325_RESIZE_CTRL_RCH_POS     4
#define ILI9325_RESIZE_CTRL_RCH_MSK    (0x3u << ILI9325_RESIZE_CTRL_RCH_POS)
#define ILI9325_RESIZE_CTRL_RCH(value) ((ILI9325_RESIZE_CTRL_RCH_MSK & ((value) << ILI9325_RESIZE_CTRL_RCH_POS)))
#define ILI9325_RESIZE_CTRL_RCV_POS     8
#define ILI9325_RESIZE_CTRL_RCV_MSK    (0x3u << ILI9325_RESIZE_CTRL_RCV_POS)
#define ILI9325_RESIZE_CTRL_RCV(value) ((ILI9325_RESIZE_CTRL_RCV_MSK & ((value) << ILI9325_RESIZE_CTRL_RCV_POS)))

/* -------- ILI9325_DISP_CTRL1 : (Offset: 0x07) Display Control 1 -------- */
#define ILI9325_DISP_CTRL1             (0x07u)
#define ILI9325_DISP_CTRL1_D_POS        0
#define ILI9325_DISP_CTRL1_D_MSK       (0x3u << ILI9325_DISP_CTRL1_D_POS)
#define ILI9325_DISP_CTRL1_D(value)    ((ILI9325_DISP_CTRL1_D_MSK & ((value) << ILI9325_DISP_CTRL1_D_POS)))
#define ILI9325_DISP_CTRL1_CL          (0x1u << 3)
#define ILI9325_DISP_CTRL1_DTE         (0x1u << 4)
#define ILI9325_DISP_CTRL1_GON         (0x1u << 5)
#define ILI9325_DISP_CTRL1_BASEE       (0x1u << 8)
#define ILI9325_DISP_CTRL1_PTDE_POS     12
#define ILI9325_DISP_CTRL1_PTDE_MSK    (0x3u << ILI9325_DISP_CTRL1_PTDE_POS)
#define ILI9325_DISP_CTRL1_PTDE(value) ((ILI9325_DISP_CTRL1_PTDE_MSK & ((value) << ILI9325_DISP_CTRL1_PTDE_POS)))

/* -------- ILI9325_DISP_CTRL2 : (Offset: 0x08) Display Control 2 -------- */
#define ILI9325_DISP_CTRL2           (0x08u)
#define ILI9325_DISP_CTRL2_BP_POS     0
#define ILI9325_DISP_CTRL2_BP_MSK    (0xfu << ILI9325_DISP_CTRL2_BP_POS)
#define ILI9325_DISP_CTRL2_BP(value) ((ILI9325_DISP_CTRL2_BP_MSK & ((value) << ILI9325_DISP_CTRL2_BP_POS)))
#define ILI9325_DISP_CTRL2_FP_POS     8
#define ILI9325_DISP_CTRL2_FP_MSK    (0xfu << ILI9325_DISP_CTRL2_FP_POS)
#define ILI9325_DISP_CTRL2_FP(value) ((ILI9325_DISP_CTRL2_FP_MSK & ((value) << ILI9325_DISP_CTRL2_FP_POS)))

/* -------- ILI9325_DISP_CTRL3 : (Offset: 0x09) Display Control 3 -------- */
#define ILI9325_DISP_CTRL3            (0x09u)
#define ILI9325_DISP_CTRL3_ISC_POS     0
#define ILI9325_DISP_CTRL3_ISC_MSK    (0xfu << ILI9325_DISP_CTRL3_ISC_POS)
#define ILI9325_DISP_CTRL3_ISC(value) ((ILI9325_DISP_CTRL3_ISC_MSK & ((value) << ILI9325_DISP_CTRL3_ISC_POS)))
#define ILI9325_DISP_CTRL3_PTG_POS     4
#define ILI9325_DISP_CTRL3_PTG_MSK    (0x3u << ILI9325_DISP_CTRL3_PTG_POS)
#define ILI9325_DISP_CTRL3_PTG(value) ((ILI9325_DISP_CTRL3_PTG_MSK & ((value) << ILI9325_DISP_CTRL3_PTG_POS)))
#define ILI9325_DISP_CTRL3_PTS_POS     8
#define ILI9325_DISP_CTRL3_PTS_MSK    (0x7u << ILI9325_DISP_CTRL3_PTS_POS)
#define ILI9325_DISP_CTRL3_PTS(value) ((ILI9325_DISP_CTRL3_PTS_MSK & ((value) << ILI9325_DISP_CTRL3_PTS_POS)))

/* -------- ILI9325_DISP_CTRL4 : (Offset: 0x0A) Display Control 4 -------- */
#define ILI9325_DISP_CTRL4            (0x0Au)
#define ILI9325_DISP_CTRL4_FMI_POS     0
#define ILI9325_DISP_CTRL4_FMI_MSK    (0x7u << ILI9325_DISP_CTRL4_FMI_POS)
#define ILI9325_DISP_CTRL4_FMI(value) ((ILI9325_DISP_CTRL4_FMI_MSK & ((value) << ILI9325_DISP_CTRL4_FMI_POS)))
#define ILI9325_DISP_CTRL4_FMARKOE    (0x1u << 3)

/* -------- ILI9325_RGB_DISP_INTERFACE_CTRL1 : (Offset: 0x0C) RGB Display Interface Control 1 -------- */
#define ILI9325_RGB_DISP_INTERFACE_CTRL1            (0x0Cu)
#define ILI9325_RGB_DISP_INTERFACE_CTRL1_RIM_POS     0
#define ILI9325_RGB_DISP_INTERFACE_CTRL1_RIM_MSK    (0x3u << ILI9325_RGB_DISP_INTERFACE_CTRL1_RIM_POS)
#define ILI9325_RGB_DISP_INTERFACE_CTRL1_RIM(value) ((ILI9325_RGB_DISP_INTERFACE_CTRL1_RIM_MSK & ((value) << ILI9325_RGB_DISP_INTERFACE_CTRL1_RIM_POS)))
#define ILI9325_RGB_DISP_INTERFACE_CTRL1_DM0        (0x1u << 4)
#define ILI9325_RGB_DISP_INTERFACE_CTRL1_DM1        (0x1u << 5)
#define ILI9325_RGB_DISP_INTERFACE_CTRL1_DM_POS      4
#define ILI9325_RGB_DISP_INTERFACE_CTRL1_DM_MSK     (0x3u << ILI9325_RGB_DISP_INTERFACE_CTRL1_DM_POS)
#define ILI9325_RGB_DISP_INTERFACE_CTRL1_DM(value)  ((ILI9325_RGB_DISP_INTERFACE_CTRL1_DM_MSK & ((value) << ILI9325_RGB_DISP_INTERFACE_CTRL1_DM_POS)))
#define ILI9325_RGB_DISP_INTERFACE_CTRL1_RM         (0x1u << 8)
#define ILI9325_RGB_DISP_INTERFACE_CTRL1_ENC_POS     12
#define ILI9325_RGB_DISP_INTERFACE_CTRL1_ENC_MSK    (0x7u << ILI9325_RGB_DISP_INTERFACE_CTRL1_ENC_POS)
#define ILI9325_RGB_DISP_INTERFACE_CTRL1_ENC(value) ((ILI9325_RGB_DISP_INTERFACE_CTRL1_ENC_MSK & ((value) <ILI9325_RGB_DISP_INTERFACE_CTRL1_ENC_POS)))

/* -------- ILI9325_FRAME_MAKER_POS : (Offset: 0x0D) Frame Maker Position -------- */
#define ILI9325_FRAME_MAKER_POS            (0x0Du)
#define ILI9325_FRAME_MAKER_POS_FMP_POS     0
#define ILI9325_FRAME_MAKER_POS_FMP_MSK    (0x1ffu << ILI9325_FRAME_MAKER_POS_FMP_POS)
#define ILI9325_FRAME_MAKER_POS_FMP(value) ((ILI9325_FRAME_MAKER_POS_FMP_MSK & ((value) << ILI9325_FRAME_MAKER_POS_FMP_POS)))

/* -------- ILI9325_RGB_DISP_INTERFACE_CTRL2 : (Offset: 0x0F) RGB Display Interface Control 2 -------- */
#define ILI9325_RGB_DISP_INTERFACE_CTRL2      (0x0Fu)
#define ILI9325_RGB_DISP_INTERFACE_CTRL2_EPL  (0x1u << 0)
#define ILI9325_RGB_DISP_INTERFACE_CTRL2_DPL  (0x1u << 1)
#define ILI9325_RGB_DISP_INTERFACE_CTRL2_HSPL (0x1u << 3)
#define ILI9325_RGB_DISP_INTERFACE_CTRL2_VSPL (0x1u << 4)

/* -------- ILI9325_POWER_CTRL1 : (Offset: 0x10) Power Control 1 -------- */
#define ILI9325_POWER_CTRL1           (0x10u)
#define ILI9325_POWER_CTRL1_STB       (0x1u << 0)
#define ILI9325_POWER_CTRL1_SLP       (0x1u << 1)
#define ILI9325_POWER_CTRL1_DSTB      (0x1u << 2)
#define ILI9325_POWER_CTRL1_AP_POS     4
#define ILI9325_POWER_CTRL1_AP_MSK    (0x7u << ILI9325_POWER_CTRL1_AP_POS)
#define ILI9325_POWER_CTRL1_AP(value) ((ILI9325_POWER_CTRL1_AP_MSK & ((value) << ILI9325_POWER_CTRL1_AP_POS)))
#define ILI9325_POWER_CTRL1_APE       (0x1u << 7)
#define ILI9325_POWER_CTRL1_BT_POS     8
#define ILI9325_POWER_CTRL1_BT_MSK    (0x7u << ILI9325_POWER_CTRL1_BT_POS)
#define ILI9325_POWER_CTRL1_BT(value) ((ILI9325_POWER_CTRL1_BT_MSK & ((value) << ILI9325_POWER_CTRL1_BT_POS)))
#define ILI9325_POWER_CTRL1_SAP       (0x1u << 12)

/* -------- ILI9325_POWER_CTRL2 : (Offset: 0x11) Power Control 2 -------- */
#define ILI9325_POWER_CTRL2            (0x11u)
#define ILI9325_POWER_CTRL2_VC_POS      0
#define ILI9325_POWER_CTRL2_VC_MSK     (0x7u << ILI9325_POWER_CTRL2_VC_POS)
#define ILI9325_POWER_CTRL2_VC(value)  ((ILI9325_POWER_CTRL2_VC_MSK & ((value) << ILI9325_POWER_CTRL2_VC_POS)))
#define ILI9325_POWER_CTRL2_DC0_POS     4
#define ILI9325_POWER_CTRL2_DC0_MSK    (0x7u << ILI9325_POWER_CTRL2_DC0_POS)
#define ILI9325_POWER_CTRL2_DC0(value) ((ILI9325_POWER_CTRL2_DC0_MSK & ((value) << ILI9325_POWER_CTRL2_DC0_POS)))
#define ILI9325_POWER_CTRL2_DC1_POS     8
#define ILI9325_POWER_CTRL2_DC1_MSK    (0x7u << ILI9325_POWER_CTRL2_DC1_POS)
#define ILI9325_POWER_CTRL2_DC1(value) ((ILI9325_POWER_CTRL2_DC1_MSK & ((value) << ILI9325_POWER_CTRL2_DC1_POS)))

/* -------- ILI9325_POWER_CTRL3 : (Offset: 0x12) Power Control 3 -------- */
#define ILI9325_POWER_CTRL3            (0x12u)
#define ILI9325_POWER_CTRL3_VRH_POS     0
#define ILI9325_POWER_CTRL3_VRH_MSK    (0xfu << ILI9325_POWER_CTRL3_VRH_POS)
#define ILI9325_POWER_CTRL3_VRH(value) ((ILI9325_POWER_CTRL3_VRH_MSK & ((value) << ILI9325_POWER_CTRL3_VRH_POS)))
#define ILI9325_POWER_CTRL3_PON        (0x1u << 4)
#define ILI9325_POWER_CTRL3_VCIRE      (0x1u << 7)

/* -------- ILI9325_POWER_CTRL4 : (Offset: 0x13) Power Control 4 -------- */
#define ILI9325_POWER_CTRL4            (0x13u)
#define ILI9325_POWER_CTRL4_VDV_POS     8
#define ILI9325_POWER_CTRL4_VDV_MSK    (0x1fu << ILI9325_POWER_CTRL4_VDV_POS)
#define ILI9325_POWER_CTRL4_VDV(value) ((ILI9325_POWER_CTRL4_VDV_MSK & ((value) << ILI9325_POWER_CTRL4_VDV_POS)))

/* -------- ILI9325_HORIZONTAL_GRAM_ADDR_SET : (Offset: 0x20) Horizontal GRAM Address Set -------- */
#define ILI9325_HORIZONTAL_GRAM_ADDR_SET           (0x20u)
#define ILI9325_HORIZONTAL_GRAM_ADDR_SET_AD_POS     0
#define ILI9325_HORIZONTAL_GRAM_ADDR_SET_AD_MSK    (0xffu << ILI9325_HORIZONTAL_GRAM_ADDR_SET_AD_POS)
#define ILI9325_HORIZONTAL_GRAM_ADDR_SET_AD(value) ((ILI9325_HORIZONTAL_GRAM_ADDR_SET_AD_MSK & ((value) << ILI9325_HORIZONTAL_GRAM_ADDR_SET_AD_POS)))

/* -------- ILI9325_VERTICAL_GRAM_ADDR_SET : (Offset: 0x21) Vertical  GRAM Address Set -------- */
#define ILI9325_VERTICAL_GRAM_ADDR_SET           (0x21u)
#define ILI9325_VERTICAL_GRAM_ADDR_SET_AD_POS     0
#define ILI9325_VERTICAL_GRAM_ADDR_SET_AD_MSK    (0xffu << ILI9325_VERTICAL_GRAM_ADDR_SET_AD_POS)
#define ILI9325_VERTICAL_GRAM_ADDR_SET_AD(value) ((ILI9325_VERTICAL_GRAM_ADDR_SET_AD_MSK & ((value) << ILI9325_VERTICAL_GRAM_ADDR_SET_AD_POS)))

/* -------- ILI9325_GRAM_DATA_REG : (Offset: 0x22) GRAM Data Register -------- */
#define ILI9325_GRAM_DATA_REG (0x22u)

/* -------- ILI9325_POWER_CTRL7 : (Offset: 0x29) Power Control 7 -------- */
#define ILI9325_POWER_CTRL7            (0x29u)
#define ILI9325_POWER_CTRL7_VCM_POS     0
#define ILI9325_POWER_CTRL7_VCM_MSK    (0x3fu << ILI9325_POWER_CTRL7_VCM_POS)
#define ILI9325_POWER_CTRL7_VCM(value) ((ILI9325_POWER_CTRL7_VCM_MSK & ((value) << ILI9325_POWER_CTRL7_VCM_POS)))

/* -------- ILI9325_FRAME_RATE_AND_COLOR_CTRL : (Offset: 0x2B) Frame Rate and Color Control -------- */
#define ILI9325_FRAME_RATE_AND_COLOR_CTRL            (0x2Bu)
#define ILI9325_FRAME_RATE_AND_COLOR_CTRL_FRS_POS     0
#define ILI9325_FRAME_RATE_AND_COLOR_CTRL_FRS_MSK    (0xfu << ILI9325_FRAME_RATE_AND_COLOR_CTRL_FRS_POS)
#define ILI9325_FRAME_RATE_AND_COLOR_CTRL_FRS(value) ((ILI9325_FRAME_RATE_AND_COLOR_CTRL_FRS_MSK & ((value) << ILI9325_FRAME_RATE_AND_COLOR_CTRL_FRS_POS)))

/* -------- ILI9325_GAMMA_CTRL1 : (Offset: 0x30) Gamma Control 1 -------- */
#define ILI9325_GAMMA_CTRL1            (0x30u)
#define ILI9325_GAMMA_CTRL1_KP0_POS     0
#define ILI9325_GAMMA_CTRL1_KP0_MSK    (0x7u << ILI9325_GAMMA_CTRL1_KP0_POS)
#define ILI9325_GAMMA_CTRL1_KP0(value) ((ILI9325_GAMMA_CTRL1_KP0_MSK & ((value) << ILI9325_GAMMA_CTRL1_KP0_POS)))
#define ILI9325_GAMMA_CTRL1_KP1_POS     8
#define ILI9325_GAMMA_CTRL1_KP1_MSK    (0x7u << ILI9325_GAMMA_CTRL1_KP1_POS)
#define ILI9325_GAMMA_CTRL1_KP1(value) ((ILI9325_GAMMA_CTRL1_KP1_MSK & ((value) << ILI9325_GAMMA_CTRL1_KP1_POS)))

/* -------- ILI9325_GAMMA_CTRL2 : (Offset: 0x31) Gamma Control 2 -------- */
#define ILI9325_GAMMA_CTRL2            (0x31u)
#define ILI9325_GAMMA_CTRL2_KP2_POS     0
#define ILI9325_GAMMA_CTRL2_KP2_MSK    (0x7u << ILI9325_GAMMA_CTRL2_KP2_POS)
#define ILI9325_GAMMA_CTRL2_KP2(value) ((ILI9325_GAMMA_CTRL2_KP2_MSK & ((value) << ILI9325_GAMMA_CTRL2_KP2_POS)))
#define ILI9325_GAMMA_CTRL2_KP3_POS     8
#define ILI9325_GAMMA_CTRL2_KP3_MSK    (0x7u << ILI9325_GAMMA_CTRL2_KP3_POS)
#define ILI9325_GAMMA_CTRL2_KP3(value) ((ILI9325_GAMMA_CTRL2_KP3_MSK & ((value) << ILI9325_GAMMA_CTRL2_KP3_POS)))

/* -------- ILI9325_GAMMA_CTRL3 : (Offset: 0x32) Gamma Control 3 -------- */
#define ILI9325_GAMMA_CTRL3            (0x32u)
#define ILI9325_GAMMA_CTRL3_KP4_POS     0
#define ILI9325_GAMMA_CTRL3_KP4_MSK    (0x7u << ILI9325_GAMMA_CTRL3_KP4_POS)
#define ILI9325_GAMMA_CTRL3_KP4(value) ((ILI9325_GAMMA_CTRL3_KP4_MSK & ((value) << ILI9325_GAMMA_CTRL3_KP4_POS)))
#define ILI9325_GAMMA_CTRL3_KP5_POS     8
#define ILI9325_GAMMA_CTRL3_KP5_MSK    (0x7u << ILI9325_GAMMA_CTRL3_KP5_POS)
#define ILI9325_GAMMA_CTRL3_KP5(value) ((ILI9325_GAMMA_CTRL3_KP5_MSK & ((value) << ILI9325_GAMMA_CTRL3_KP5_POS)))

/* -------- ILI9325_GAMMA_CTRL4 : (Offset: 0x35) Gamma Control 4 -------- */
#define ILI9325_GAMMA_CTRL4            (0x35u)
#define ILI9325_GAMMA_CTRL4_RP0_POS     0
#define ILI9325_GAMMA_CTRL4_RP0_MSK    (0x7u << ILI9325_GAMMA_CTRL4_RP0_POS)
#define ILI9325_GAMMA_CTRL4_RP0(value) ((ILI9325_GAMMA_CTRL4_RP0_MSK & ((value) << ILI9325_GAMMA_CTRL4_RP0_POS)))
#define ILI9325_GAMMA_CTRL4_RP1_POS     8
#define ILI9325_GAMMA_CTRL4_RP1_MSK    (0x7u << ILI9325_GAMMA_CTRL4_RP1_POS)
#define ILI9325_GAMMA_CTRL4_RP1(value) ((ILI9325_GAMMA_CTRL4_RP1_MSK & ((value) << ILI9325_GAMMA_CTRL4_RP1_POS)))

/* -------- ILI9325_GAMMA_CTRL5 : (Offset: 0x36) Gamma Control 5 -------- */
#define ILI9325_GAMMA_CTRL5             (0x36u)
#define ILI9325_GAMMA_CTRL5_VRP0_POS     0
#define ILI9325_GAMMA_CTRL5_VRP0_MSK    (0xfu << ILI9325_GAMMA_CTRL5_VRP0_POS)
#define ILI9325_GAMMA_CTRL5_VRP0(value) ((ILI9325_GAMMA_CTRL5_VRP0_MSK & ((value) << ILI9325_GAMMA_CTRL5_VRP0_POS)))
#define ILI9325_GAMMA_CTRL5_VRP1_POS     8
#define ILI9325_GAMMA_CTRL5_VRP1_MSK    (0x1fu << ILI9325_GAMMA_CTRL5_VRP1_POS)
#define ILI9325_GAMMA_CTRL5_VRP1(value) ((ILI9325_GAMMA_CTRL5_VRP1_MSK & ((value) << ILI9325_GAMMA_CTRL5_VRP1_POS)))

/* -------- ILI9325_GAMMA_CTRL6 : (Offset: 0x37) Gamma Control 6 -------- */
#define ILI9325_GAMMA_CTRL6            (0x37u)
#define ILI9325_GAMMA_CTRL6_KN0_POS     0
#define ILI9325_GAMMA_CTRL6_KN0_MSK    (0x7u << ILI9325_GAMMA_CTRL6_KN0_POS)
#define ILI9325_GAMMA_CTRL6_KN0(value) ((ILI9325_GAMMA_CTRL6_KN0_MSK & ((value) << ILI9325_GAMMA_CTRL6_KN0_POS)))
#define ILI9325_GAMMA_CTRL6_KN1_POS     8
#define ILI9325_GAMMA_CTRL6_KN1_MSK    (0x7u << ILI9325_GAMMA_CTRL6_KN1_POS)
#define ILI9325_GAMMA_CTRL6_KN1(value) ((ILI9325_GAMMA_CTRL6_KN1_MSK & ((value) << ILI9325_GAMMA_CTRL6_KN1_POS)))

/* -------- ILI9325_GAMMA_CTRL7 : (Offset: 0x38) Gamma Control 7 -------- */
#define ILI9325_GAMMA_CTRL7            (0x38u)
#define ILI9325_GAMMA_CTRL7_KN2_POS     0
#define ILI9325_GAMMA_CTRL7_KN2_MSK    (0x7u << ILI9325_GAMMA_CTRL7_KN2_POS)
#define ILI9325_GAMMA_CTRL7_KN2(value) ((ILI9325_GAMMA_CTRL7_KN2_MSK & ((value) << ILI9325_GAMMA_CTRL7_KN2_POS)))
#define ILI9325_GAMMA_CTRL7_KN3_POS     8
#define ILI9325_GAMMA_CTRL7_KN3_MSK    (0x7u << ILI9325_GAMMA_CTRL7_KN3_POS)
#define ILI9325_GAMMA_CTRL7_KN3(value) ((ILI9325_GAMMA_CTRL7_KN3_MSK & ((value) << ILI9325_GAMMA_CTRL7_KN3_POS)))

/* -------- ILI9325_GAMMA_CTRL8 : (Offset: 0x39) Gamma Control 8 -------- */
#define ILI9325_GAMMA_CTRL8            (0x39u)
#define ILI9325_GAMMA_CTRL8_KN4_POS     0
#define ILI9325_GAMMA_CTRL8_KN4_MSK    (0x7u << ILI9325_GAMMA_CTRL8_KN4_POS)
#define ILI9325_GAMMA_CTRL8_KN4(value) ((ILI9325_GAMMA_CTRL8_KN4_MSK & ((value) << ILI9325_GAMMA_CTRL8_KN4_POS)))
#define ILI9325_GAMMA_CTRL8_KN5_POS     8
#define ILI9325_GAMMA_CTRL8_KN5_MSK    (0x7u << ILI9325_GAMMA_CTRL8_KN5_POS)
#define ILI9325_GAMMA_CTRL8_KN5(value) ((ILI9325_GAMMA_CTRL8_KN5_MSK & ((value) << ILI9325_GAMMA_CTRL8_KN5_POS)))

/* -------- ILI9325_GAMMA_CTRL9 : (Offset: 0x3C) Gamma Control 9 -------- */
#define ILI9325_GAMMA_CTRL9            (0x3Cu)
#define ILI9325_GAMMA_CTRL9_RN0_POS     0
#define ILI9325_GAMMA_CTRL9_RN0_MSK    (0x7u << ILI9325_GAMMA_CTRL9_RN0_POS)
#define ILI9325_GAMMA_CTRL9_RN0(value) ((ILI9325_GAMMA_CTRL9_RN0_MSK & ((value) << ILI9325_GAMMA_CTRL9_RN0_POS)))
#define ILI9325_GAMMA_CTRL9_RN1_POS     8
#define ILI9325_GAMMA_CTRL9_RN1_MSK    (0x7u << ILI9325_GAMMA_CTRL9_RN1_POS)
#define ILI9325_GAMMA_CTRL9_RN1(value) ((ILI9325_GAMMA_CTRL9_RN1_MSK & ((value) << ILI9325_GAMMA_CTRL9_RN1_POS)))

/* -------- ILI9325_GAMMA_CTRL10 : (Offset: 0x3D) Gamma Control 10 -------- */
#define ILI9325_GAMMA_CTRL10             (0x3Du)
#define ILI9325_GAMMA_CTRL10_VRN0_POS     0
#define ILI9325_GAMMA_CTRL10_VRN0_MSK    (0xfu << ILI9325_GAMMA_CTRL10_VRN0_POS)
#define ILI9325_GAMMA_CTRL10_VRN0(value) ((ILI9325_GAMMA_CTRL10_VRN0_MSK & ((value) << ILI9325_GAMMA_CTRL10_VRN0_POS)))
#define ILI9325_GAMMA_CTRL10_VRN1_POS     8
#define ILI9325_GAMMA_CTRL10_VRN1_MSK    (0x1fu << ILI9325_GAMMA_CTRL10_VRN1_POS)
#define ILI9325_GAMMA_CTRL10_VRN1(value) ((ILI9325_GAMMA_CTRL10_VRN1_MSK & ((value) << ILI9325_GAMMA_CTRL10_VRN1_POS)))

/* -------- ILI9325_HORIZONTAL_ADDR_START : (Offset: 0x50) Horizontal Address Start Position -------- */
#define ILI9325_HORIZONTAL_ADDR_START            (0x50u)
#define ILI9325_HORIZONTAL_ADDR_START_HSA_POS     0
#define ILI9325_HORIZONTAL_ADDR_START_HSA_MSK    (0xffu << ILI9325_HORIZONTAL_ADDR_START_HSA_POS)
#define ILI9325_HORIZONTAL_ADDR_START_HSA(value) ((ILI9325_HORIZONTAL_ADDR_START_HSA_MSK & ((value) << ILI9325_HORIZONTAL_ADDR_START_HSA_POS)))

/* -------- ILI9325_HORIZONTAL_ADDR_END : (Offset: 0x51) Horizontal Address End Position -------- */
#define ILI9325_HORIZONTAL_ADDR_END            (0x51u)
#define ILI9325_HORIZONTAL_ADDR_END_HEA_POS     0
#define ILI9325_HORIZONTAL_ADDR_END_HEA_MSK    (0xffu << ILI9325_HORIZONTAL_ADDR_END_HEA_POS)
#define ILI9325_HORIZONTAL_ADDR_END_HEA(value) ((ILI9325_HORIZONTAL_ADDR_END_HEA_MSK & ((value) << ILI9325_HORIZONTAL_ADDR_END_HEA_POS)))

/* -------- ILI9325_VERTICAL_ADDR_START : (Offset: 0x52) Vertical Address Start Position -------- */
#define ILI9325_VERTICAL_ADDR_START            (0x52u)
#define ILI9325_VERTICAL_ADDR_START_VSA_POS     0
#define ILI9325_VERTICAL_ADDR_START_VSA_MSK    (0x1ffu << ILI9325_VERTICAL_ADDR_START_VSA_POS)
#define ILI9325_VERTICAL_ADDR_START_VSA(value) ((ILI9325_VERTICAL_ADDR_START_VSA_MSK & ((value) << ILI9325_VERTICAL_ADDR_START_VSA_POS)))

/* -------- ILI9325_VERTICAL_ADDR_END : (Offset: 0x53) Vertical Address End Position -------- */
#define ILI9325_VERTICAL_ADDR_END            (0x53u)
#define ILI9325_VERTICAL_ADDR_END_VEA_POS     0
#define ILI9325_VERTICAL_ADDR_END_VEA_MSK    (0x1ffu << ILI9325_VERTICAL_ADDR_END_VEA_POS)
#define ILI9325_VERTICAL_ADDR_END_VEA(value) ((ILI9325_VERTICAL_ADDR_END_VEA_MSK & ((value) << ILI9325_VERTICAL_ADDR_END_VEA_POS)))

/* -------- ILI9325_DRIVER_OUTPUT_CTRL2 : (Offset: 0x60) Driver Output Control 2 -------- */
#define ILI9325_DRIVER_OUTPUT_CTRL2            (0x60u)
#define ILI9325_DRIVER_OUTPUT_CTRL2_SCN_POS     0
#define ILI9325_DRIVER_OUTPUT_CTRL2_SCN_MSK    (0x3fu << ILI9325_DRIVER_OUTPUT_CTRL2_SCN_POS)
#define ILI9325_DRIVER_OUTPUT_CTRL2_SCN(value) ((ILI9325_DRIVER_OUTPUT_CTRL2_SCN_MSK & ((value) << ILI9325_DRIVER_OUTPUT_CTRL2_SCN_POS)))
#define ILI9325_DRIVER_OUTPUT_CTRL2_NL_POS      8
#define ILI9325_DRIVER_OUTPUT_CTRL2_NL_MSK     (0x3fu << ILI9325_DRIVER_OUTPUT_CTRL2_NL_POS)
#define ILI9325_DRIVER_OUTPUT_CTRL2_NL(value)  ((ILI9325_DRIVER_OUTPUT_CTRL2_NL_MSK & ((value) << ILI9325_DRIVER_OUTPUT_CTRL2_NL_POS)))
#define ILI9325_DRIVER_OUTPUT_CTRL2_GS         (0x1u << 15)

/* -------- ILI9325_BASE_IMG_DISP_CTRL : (Offset: 0x61) Base Image Display Control -------- */
#define ILI9325_BASE_IMG_DISP_CTRL     (0x61u)
#define ILI9325_BASE_IMG_DISP_CTRL_REV (0x1u << 0)
#define ILI9325_BASE_IMG_DISP_CTRL_VLE (0x1u << 1)
#define ILI9325_BASE_IMG_DISP_CTRL_NDL (0x1u << 2)

/* -------- ILI9325_VERTICAL_SCROLL_CTRL : (Offset: 0x6A) Vertical Scroll Control -------- */
#define ILI9325_VERTICAL_SCROLL_CTRL           (0x6Au)
#define ILI9325_VERTICAL_SCROLL_CTRL_VL_POS     0
#define ILI9325_VERTICAL_SCROLL_CTRL_VL_MSK    (0x1ffu << ILI9325_VERTICAL_SCROLL_CTRL_VL_POS)
#define ILI9325_VERTICAL_SCROLL_CTRL_VL(value) ((ILI9325_VERTICAL_SCROLL_CTRL_VL_MSK & ((value) << ILI9325_VERTICAL_SCROLL_CTRL_VL_POS)))

/* -------- ILI9325_PARTIAL_IMG1_DISP_POS : (Offset: 0x80) Partial Image 1 Display Position -------- */
#define ILI9325_PARTIAL_IMG1_DISP_POS              (0x80u)
#define ILI9325_PARTIAL_IMG1_DISP_POS_PTDP0_POS     0
#define ILI9325_PARTIAL_IMG1_DISP_POS_PTDP0_MSK    (0x1ffu << ILI9325_PARTIAL_IMG1_DISP_POS_PTDP0_POS)
#define ILI9325_PARTIAL_IMG1_DISP_POS_PTDP0(value) ((ILI9325_PARTIAL_IMG1_DISP_POS_PTDP0_MSK & ((value) << ILI9325_PARTIAL_IMG1_DISP_POS_PTDP0_POS)))

/* -------- ILI9325_PARTIAL_IMG1_AREA_START_LINE : (Offset: 0x81) Partial Image 1 Area (Start Line) -------- */
#define ILI9325_PARTIAL_IMG1_AREA_START_LINE              (0x81u)
#define ILI9325_PARTIAL_IMG1_AREA_START_LINE_PTSA0_POS     0
#define ILI9325_PARTIAL_IMG1_AREA_START_LINE_PTSA0_MSK    (0x1ffu << ILI9325_PARTIAL_IMG1_AREA_START_LINE_PTSA0_POS)
#define ILI9325_PARTIAL_IMG1_AREA_START_LINE_PTSA0(value) ((ILI9325_PARTIAL_IMG1_AREA_START_LINE_PTSA0_MSK & ((value) << ILI9325_PARTIAL_IMG1_AREA_START_LINE_PTSA0_POS)))

/* -------- ILI9325_PARTIAL_IMG1_AREA_END_LINE : (Offset: 0x82) Partial Image 1 Area (End Line) -------- */
#define ILI9325_PARTIAL_IMG1_AREA_END_LINE              (0x82u)
#define ILI9325_PARTIAL_IMG1_AREA_END_LINE_PTEA0_POS     0
#define ILI9325_PARTIAL_IMG1_AREA_END_LINE_PTEA0_MSK    (0x1ffu << ILI9325_PARTIAL_IMG1_AREA_END_LINE_PTEA0_POS)
#define ILI9325_PARTIAL_IMG1_AREA_END_LINE_PTEA0(value) ((ILI9325_PARTIAL_IMG1_AREA_END_LINE_PTEA0_MSK & ((value) << ILI9325_PARTIAL_IMG1_AREA_END_LINE_PTEA0_POS)))

/* -------- ILI9325_PARTIAL_IMG2_DISP_POS : (Offset: 0x83) Partial Image 2 Display Position -------- */
#define ILI9325_PARTIAL_IMG2_DISP_POS              (0x83u)
#define ILI9325_PARTIAL_IMG2_DISP_POS_PTDP1_POS     0
#define ILI9325_PARTIAL_IMG2_DISP_POS_PTDP1_MSK    (0x1ffu << ILI9325_PARTIAL_IMG2_DISP_POS_PTDP1_POS)
#define ILI9325_PARTIAL_IMG2_DISP_POS_PTDP1(value) ((ILI9325_PARTIAL_IMG2_DISP_POS_PTDP1_MSK & ((value) << ILI9325_PARTIAL_IMG2_DISP_POS_PTDP1_POS)))

/* -------- ILI9325_PARTIAL_IMG2_AREA_START_LINE : (Offset: 0x84) Partial Image 2 Area (Start Line) -------- */
#define ILI9325_PARTIAL_IMG2_AREA_START_LINE              (0x84u)
#define ILI9325_PARTIAL_IMG2_AREA_START_LINE_PTSA1_POS     0
#define ILI9325_PARTIAL_IMG2_AREA_START_LINE_PTSA1_MSK    (0x1ffu << ILI9325_PARTIAL_IMG2_AREA_START_LINE_PTSA1_POS)
#define ILI9325_PARTIAL_IMG2_AREA_START_LINE_PTSA1(value) ((ILI9325_PARTIAL_IMG2_AREA_START_LINE_PTSA1_MSK & ((value) << ILI9325_PARTIAL_IMG2_AREA_START_LINE_PTSA1_POS)))

/* -------- ILI9325_PARTIAL_IMG2_AREA_END_LINE : (Offset: 0x85) Partial Image 2 Area (End Line) -------- */
#define ILI9325_PARTIAL_IMG2_AREA_END_LINE              (0x85u)
#define ILI9325_PARTIAL_IMG2_AREA_END_LINE_PTEA1_POS     0
#define ILI9325_PARTIAL_IMG2_AREA_END_LINE_PTEA1_MSK    (0x1ffu << ILI9325_PARTIAL_IMG2_AREA_END_LINE_PTEA1_POS)
#define ILI9325_PARTIAL_IMG2_AREA_END_LINE_PTEA1(value) ((ILI9325_PARTIAL_IMG2_AREA_END_LINE_PTEA1_MSK & ((value) << ILI9325_PARTIAL_IMG2_AREA_END_LINE_PTEA1_POS)))

/* -------- ILI9325_PANEL_INTERFACE_CTRL1 : (Offset: 0x90) Panel Interface Control 1 -------- */
#define ILI9325_PANEL_INTERFACE_CTRL1             (0x90u)
#define ILI9325_PANEL_INTERFACE_CTRL1_RTNI_POS     0
#define ILI9325_PANEL_INTERFACE_CTRL1_RTNI_MSK    (0x1fu << ILI9325_PANEL_INTERFACE_CTRL1_RTNI_POS)
#define ILI9325_PANEL_INTERFACE_CTRL1_RTNI(value) ((ILI9325_PANEL_INTERFACE_CTRL1_RTNI_MSK & ((value) << ILI9325_PANEL_INTERFACE_CTRL1_RTNI_POS)))
#define ILI9325_PANEL_INTERFACE_CTRL1_DIVI_POS     8
#define ILI9325_PANEL_INTERFACE_CTRL1_DIVI_MSK    (0x3u << ILI9325_PANEL_INTERFACE_CTRL1_DIVI_POS)
#define ILI9325_PANEL_INTERFACE_CTRL1_DIVI(value) ((ILI9325_PANEL_INTERFACE_CTRL1_DIVI_MSK & ((value) << ILI9325_PANEL_INTERFACE_CTRL1_DIVI_POS)))

/* -------- ILI9325_PANEL_INTERFACE_CTRL2 : (Offset: 0x92) Panel Interface Control 2 -------- */
#define ILI9325_PANEL_INTERFACE_CTRL2             (0x92u)
#define ILI9325_PANEL_INTERFACE_CTRL2_NOWI_POS     8
#define ILI9325_PANEL_INTERFACE_CTRL2_NOWI_MSK    (0x7u << ILI9325_PANEL_INTERFACE_CTRL2_NOWI_POS)
#define ILI9325_PANEL_INTERFACE_CTRL2_NOWI(value) ((ILI9325_PANEL_INTERFACE_CTRL2_NOWI_MSK & ((value) << ILI9325_PANEL_INTERFACE_CTRL2_NOWI_POS)))

/* -------- ILI9325_PANEL_INTERFACE_CTRL4 : (Offset: 0x95) Panel Interface Control 4 -------- */
#define ILI9325_PANEL_INTERFACE_CTRL4             (0x95u)
#define ILI9325_PANEL_INTERFACE_CTRL4_RTNE_POS     0
#define ILI9325_PANEL_INTERFACE_CTRL4_RTNE_MSK    (0x3fu << ILI9325_PANEL_INTERFACE_CTRL4_RTNE_POS)
#define ILI9325_PANEL_INTERFACE_CTRL4_RTNE(value) ((ILI9325_PANEL_INTERFACE_CTRL4_RTNE_MSK & ((value) << ILI9325_PANEL_INTERFACE_CTRL4_RTNE_POS)))
#define ILI9325_PANEL_INTERFACE_CTRL4_DIVE_POS     8
#define ILI9325_PANEL_INTERFACE_CTRL4_DIVE_MSK    (0x3u << ILI9325_PANEL_INTERFACE_CTRL4_DIVE_POS)
#define ILI9325_PANEL_INTERFACE_CTRL4_DIVE(value) ((ILI9325_PANEL_INTERFACE_CTRL4_DIVE_MSK & ((value) << ILI9325_PANEL_INTERFACE_CTRL4_DIVE_POS)))

/* -------- ILI9325_OTP_VCM_PROG_CTRL : (Offset: 0xA1) OTP VCM Programming Control -------- */
#define ILI9325_OTP_VCM_PROG_CTRL                (0xA1u)
#define ILI9325_OTP_VCM_PROG_CTRL_VCM_OTP_POS     0
#define ILI9325_OTP_VCM_PROG_CTRL_VCM_OTP_MSK    (0x3fu << ILI9325_OTP_VCM_PROG_CTRL_VCM_OTP_POS)
#define ILI9325_OTP_VCM_PROG_CTRL_VCM_OTP(value) ((ILI9325_OTP_VCM_PROG_CTRL_VCM_OTP_MSK & ((value) << ILI9325_OTP_VCM_PROG_CTRL_VCM_OTP_POS)))
#define ILI9325_OTP_VCM_PROG_CTRL_OTP_PGM_EN     (0x1u << 11)

/* -------- ILI9325_OTP_VCM_STATUS_AND_ENABLE : (Offset: 0xA2) OTP VCM Status and Enable -------- */
#define ILI9325_OTP_VCM_STATUS_AND_ENABLE                (0xA2u)
#define ILI9325_OTP_VCM_STATUS_AND_ENABLE_VCM_EN         (0x1u << 0)
#define ILI9325_OTP_VCM_STATUS_AND_ENABLE_VCM_D_POS       8
#define ILI9325_OTP_VCM_STATUS_AND_ENABLE_VCM_D_MSK      (0x3fu << ILI9325_OTP_VCM_STATUS_AND_ENABLE_VCM_D_POS)
#define ILI9325_OTP_VCM_STATUS_AND_ENABLE_VCM_D(value)   ((ILI9325_OTP_VCM_STATUS_AND_ENABLE_VCM_D_MSK & ((value) << ILI9325_OTP_VCM_STATUS_AND_ENABLE_VCM_D_POS)))
#define ILI9325_OTP_VCM_STATUS_AND_ENABLE_PGM_CNT_POS     14
#define ILI9325_OTP_VCM_STATUS_AND_ENABLE_PGM_CNT_MSK    (0x3u << ILI9325_OTP_VCM_STATUS_AND_ENABLE_PGM_CNT_POS)
#define ILI9325_OTP_VCM_STATUS_AND_ENABLE_PGM_CNT(value) ((ILI9325_OTP_VCM_STATUS_AND_ENABLE_PGM_CNT_MSK & ((value) << IILI9325_OTP_VCM_STATUS_AND_ENABLE_PGM_CNT_POS)))

/* -------- ILI9325_OTP_PROG_ID_KEY : (Offset: 0xA5) OTP Programming ID Key -------- */
#define ILI9325_OTP_PROG_ID_KEY            (0xA5u)
#define ILI9325_OTP_PROG_ID_KEY_KEY_POS     0
#define ILI9325_OTP_PROG_ID_KEY_KEY_MSK    (0xffffu << ILI9325_OTP_PROG_ID_KEY_KEY_POS)
#define ILI9325_OTP_PROG_ID_KEY_KEY(value) ((ILI9325_OTP_PROG_ID_KEY_KEY_MSK & ((value) << ILI9325_OTP_PROG_ID_KEY_KEY_POS)))

/* Define EBI access for ILI9325 8-bit System Interface.*/
#if defined(BOARD_ILI9325_ADDR) && defined (BOARD_ILI9325_RS)
	static inline void LCD_IR(uint8_t lcd_index)
	{
		*((volatile uint8_t *)(BOARD_ILI9325_ADDR)) = lcd_index; /* ILI9325 index register address */
	}
	static inline void LCD_WD(uint8_t lcd_data)
	{
		*((volatile uint8_t *)((BOARD_ILI9325_ADDR) | (BOARD_ILI9325_RS))) = lcd_data;
	}
	static inline uint8_t LCD_RD(void)
	{
		return *((volatile uint8_t *)((BOARD_ILI9325_ADDR) | (BOARD_ILI9325_RS)));
	}
#else
	#error "Missing module configuration for ILI9325!"
#endif

/* RGB 24-bits color table definition (RGB888). */
#define COLOR_BLACK          (0x000000u)
#define COLOR_WHITE          (0xFFFFFFu)
#define COLOR_BLUE           (0x0000FFu)
#define COLOR_GREEN          (0x00FF00u)
#define COLOR_RED            (0xFF0000u)
#define COLOR_NAVY           (0x000080u)
#define COLOR_DARKBLUE       (0x00008Bu)
#define COLOR_DARKGREEN      (0x006400u)
#define COLOR_DARKCYAN       (0x008B8Bu)
#define COLOR_CYAN           (0x00FFFFu)
#define COLOR_TURQUOISE      (0x40E0D0u)
#define COLOR_INDIGO         (0x4B0082u)
#define COLOR_DARKRED        (0x800000u)
#define COLOR_OLIVE          (0x808000u)
#define COLOR_GRAY           (0x808080u)
#define COLOR_SKYBLUE        (0x87CEEBu)
#define COLOR_BLUEVIOLET     (0x8A2BE2u)
#define COLOR_LIGHTGREEN     (0x90EE90u)
#define COLOR_DARKVIOLET     (0x9400D3u)
#define COLOR_YELLOWGREEN    (0x9ACD32u)
#define COLOR_BROWN          (0xA52A2Au)
#define COLOR_DARKGRAY       (0xA9A9A9u)
#define COLOR_SIENNA         (0xA0522Du)
#define COLOR_LIGHTBLUE      (0xADD8E6u)
#define COLOR_GREENYELLOW    (0xADFF2Fu)
#define COLOR_SILVER         (0xC0C0C0u)
#define COLOR_LIGHTGREY      (0xD3D3D3u)
#define COLOR_LIGHTCYAN      (0xE0FFFFu)
#define COLOR_VIOLET         (0xEE82EEu)
#define COLOR_AZUR           (0xF0FFFFu)
#define COLOR_BEIGE          (0xF5F5DCu)
#define COLOR_MAGENTA        (0xFF00FFu)
#define COLOR_TOMATO         (0xFF6347u)
#define COLOR_GOLD           (0xFFD700u)
#define COLOR_ORANGE         (0xFFA500u)
#define COLOR_SNOW           (0xFFFAFAu)
#define COLOR_YELLOW         (0xFFFF00u)

/**
 * Input parameters when initializing ili9325 driver.
 */
struct ili9325_opt_t{
	uint32_t ul_width;          //!< lcd width in pixel
	uint32_t ul_height;         //!< lcd height in pixel
	uint32_t foreground_color;  //!< lcd foreground color
	uint32_t background_color;  //!< lcd background color
};

/**
 * Font structure
 */
struct ili9325_font{
	/* Font width in pixels. */
	uint8_t width;
	/* Font height in pixels. */
	uint8_t height;
};

/**
 * Display direction option
 */
enum ili9325_display_direction{
	LANDSCAPE  = 0,
	PORTRAIT   = 1
};

/**
 * Shift direction option
 */
enum ili9325_shift_direction{
	H_INCREASE  = 0,
	H_DECREASE  = 1
};

/**
 * Scan direction option
 */
enum ili9325_scan_direction{
	V_INCREASE  = 0,
	V_DEREASE   = 1
};

uint32_t ili9325_init(struct ili9325_opt_t *p_opt);
void ili9325_display_on(void);
void ili9325_display_off(void);
void ili9325_set_foreground_color(ili9325_color_t ul_color);
void ili9325_fill(ili9325_color_t ul_color);
void ili9325_set_window(uint32_t ul_x, uint32_t ul_y,
		uint32_t ul_width, uint32_t ul_height);
void ili9325_set_cursor_position(uint16_t us_x, uint16_t us_y);
void ili9325_scroll (int32_t ul_lines);
void ili9325_enable_scroll (void);
void ili9325_disable_scroll(void);
void ili9325_set_display_direction(enum ili9325_display_direction e_dd,
		enum ili9325_shift_direction e_shd, enum ili9325_scan_direction e_scd);
uint32_t ili9325_draw_pixel(uint32_t ul_x, uint32_t ul_y);
ili9325_color_t ili9325_get_pixel(uint32_t ul_x, uint32_t ul_y);
void ili9325_draw_line(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2);
void ili9325_draw_rectangle(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2);
void ili9325_draw_filled_rectangle(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2);
uint32_t ili9325_draw_circle(uint32_t ul_x, uint32_t ul_y, uint32_t ul_r);
uint32_t ili9325_draw_filled_circle(uint32_t ul_x, uint32_t ul_y, uint32_t ul_r);
void ili9325_draw_prepare(uint32_t ul_x, uint32_t ul_y, uint32_t ul_width,
		    uint32_t ul_height);
void ili9325_draw_string(uint32_t ul_x, uint32_t ul_y, const uint8_t *p_str);
void ili9325_draw_pixmap(uint32_t ul_x, uint32_t ul_y, uint32_t ul_width,
		uint32_t ul_height, const ili9325_color_t *p_ul_pixmap);
void ili9325_set_top_left_limit(ili9325_coord_t x, ili9325_coord_t y);
void ili9325_set_bottom_right_limit(ili9325_coord_t x, ili9325_coord_t y);
void ili9325_set_limits(ili9325_coord_t start_x, ili9325_coord_t start_y,
		ili9325_coord_t end_x, ili9325_coord_t end_y);
ili9325_color_t ili9325_read_gram(void);
void ili9325_write_gram(ili9325_color_t color);
void ili9325_copy_pixels_to_screen(const ili9325_color_t *pixels, uint32_t count);
void ili9325_copy_raw_pixel_24bits_to_screen(const uint8_t *raw_pixels, uint32_t count);
void ili9325_duplicate_pixel(const ili9325_color_t color, uint32_t count);
void ili9325_copy_pixels_from_screen(ili9325_color_t *pixels, uint32_t count);
void ili9325_set_orientation(uint8_t flags);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* ILI9325_H_INCLUDED */
