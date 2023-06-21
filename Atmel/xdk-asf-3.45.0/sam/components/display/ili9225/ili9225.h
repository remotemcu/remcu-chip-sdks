/**
 * \file
 *
 * \brief API driver for ILI9225 TFT display component.
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

#ifndef ILI9225_H_INCLUDED
#define ILI9225_H_INCLUDED

#include "compiler.h"
#include "board.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
 extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/* ILI9325 screen size */
#define ILI9225_LCD_WIDTH  176
#define ILI9225_LCD_HEIGHT 220
/* ILI9225 ID code */
#define ILI9225_DEVICE_CODE (0x9225u)

/* ILI9225 LCD Registers */

/* -------- ILI9225_DRIVER_OUTPUT_CTRL : (Offset: 0x01) Driver Output Control -------- */
#define ILI9225_DRIVER_OUTPUT_CTRL           (0x01u)
#define ILI9225_DRIVER_OUTPUT_CTRL_NL_POS    0
#define ILI9225_DRIVER_OUTPUT_CTRL_NL_MSK    (0x1fu << ILI9225_DRIVER_OUTPUT_CTRL_NL_POS)
#define ILI9225_DRIVER_OUTPUT_CTRL_NL(value) ((ILI9225_DRIVER_OUTPUT_CTRL_NL_MSK & ((value) << ILI9225_DRIVER_OUTPUT_CTRL_NL_POS)))
#define ILI9225_DRIVER_OUTPUT_CTRL_SS        (0x1u << 8)
#define ILI9225_DRIVER_OUTPUT_CTRL_GS        (0x1u << 9)
#define ILI9225_DRIVER_OUTPUT_CTRL_SM        (0x1u << 10)
#define ILI9225_DRIVER_OUTPUT_CTRL_EPL       (0x1u << 12)
#define ILI9225_DRIVER_OUTPUT_CTRL_DPL       (0x1u << 13)
#define ILI9225_DRIVER_OUTPUT_CTRL_HSPL      (0x1u << 14)
#define ILI9225_DRIVER_OUTPUT_CTRL_VSPL      (0x1u << 15)

/* -------- ILI9225_LCD_AC_DRIVING_CTRL : (Offset: 0x02) LCD AC Driving Control -------- */
#define ILI9225_LCD_AC_DRIVING_CTRL            (0x02u)
#define ILI9225_LCD_AC_DRIVING_CTRL_FLD        (0x1u << 0)
#define ILI9225_LCD_AC_DRIVING_CTRL_INV_POS    8
#define ILI9225_LCD_AC_DRIVING_CTRL_INV_MSK    (0x3u << ILI9225_LCD_AC_DRIVING_CTRL_INV_POS)
#define ILI9225_LCD_AC_DRIVING_CTRL_INV(value) ((ILI9225_LCD_AC_DRIVING_CTRL_INV_MSK & ((value) << ILI9225_LCD_AC_DRIVING_CTRL_INV_POS)))

/* -------- ILI9225_ENTRY_MODE : (Offset: 0x03) Entry Mode -------- */
#define ILI9225_ENTRY_MODE            (0x03u)
#define ILI9225_ENTRY_MODE_AM         (0x1u << 3)
#define ILI9225_ENTRY_MODE_ID_POS     4
#define ILI9225_ENTRY_MODE_ID_MSK     (0x3u << ILI9225_ENTRY_MODE_ID_POS)
#define ILI9225_ENTRY_MODE_ID(value)  ((ILI9225_ENTRY_MODE_ID_MSK & ((value) << ILI9225_ENTRY_MODE_ID_POS)))
#define ILI9225_ENTRY_MODE_MDT_POS    8
#define ILI9225_ENTRY_MODE_MDT_MSK    (0x3u << ILI9225_ENTRY_MODE_MDT_POS)
#define ILI9225_ENTRY_MODE_MDT(value) ((ILI9225_ENTRY_MODE_MDT_MSK & ((value) << ILI9225_ENTRY_MODE_MDT_POS)))
#define ILI9225_ENTRY_MODE_BGR        (0x1u << 12)

/* -------- ILI9225_DISP_CTRL1 : (Offset: 0x07) Display Control 1 -------- */
#define ILI9225_DISP_CTRL1          (0x07u)
#define ILI9225_DISP_CTRL1_D_POS    0
#define ILI9225_DISP_CTRL1_D_MSK    (0x3u << ILI9225_DISP_CTRL1_D_POS)
#define ILI9225_DISP_CTRL1_D(value) ((ILI9225_DISP_CTRL1_D_MSK & ((value) << ILI9225_DISP_CTRL1_D_POS)))
#define ILI9225_DISP_CTRL1_REV      (0x1u << 2)
#define ILI9225_DISP_CTRL1_CL       (0x1u << 3)
#define ILI9225_DISP_CTRL1_GON      (0x1u << 4)
#define ILI9225_DISP_CTRL1_TEMON    (0x1u << 12)

/* -------- ILI9225_BLANK_PERION_CTRL1 : (Offset: 0x08) Blank Period Control -------- */
#define ILI9225_BLANK_PERIOD_CTRL1           (0x08u)
#define ILI9225_BLANK_PERIOD_CTRL1_BP_POS    0
#define ILI9225_BLANK_PERIOD_CTRL1_BP_MSK    (0xfu << ILI9225_BLANK_PERIOD_CTRL1_BP_POS)
#define ILI9225_BLANK_PERIOD_CTRL1_BP(value) ((ILI9225_BLANK_PERIOD_CTRL1_BP_MSK & ((value) << ILI9225_BLANK_PERIOD_CTRL1_BP_POS)))
#define ILI9225_BLANK_PERIOD_CTRL1_FP_POS    8
#define ILI9225_BLANK_PERIOD_CTRL1_FP_MSK    (0xfu << ILI9225_BLANK_PERIOD_CTRL1_FP_POS)
#define ILI9225_BLANK_PERIOD_CTRL1_FP(value) ((ILI9225_BLANK_PERIOD_CTRL1_FP_MSK & ((value) << ILI9225_BLANK_PERIOD_CTRL1_FP_POS)))

/* -------- ILI9225_FRAME_CYCLE_CTRL : (Offset: 0x0B) Frame Cycle Control -------- */
#define ILI9225_FRAME_CYCLE_CTRL            (0x0Bu)
#define ILI9225_FRAME_CYCLE_CTRL_RTN_POS    0
#define ILI9225_FRAME_CYCLE_CTRL_RTN_MSK    (0xfu << ILI9225_FRAME_CYCLE_CTRL_RTN_POS)
#define ILI9225_FRAME_CYCLE_CTRL_RTN(value) ((ILI9225_FRAME_CYCLE_CTRL_RTN_MSK & ((value) << ILI9225_FRAME_CYCLE_CTRL_RTN_POS)))
#define ILI9225_FRAME_CYCLE_CTRL_SDT_POS    8
#define ILI9225_FRAME_CYCLE_CTRL_SDT_MSK    (0xfu << ILI9225_FRAME_CYCLE_CTRL_SDT_POS)
#define ILI9225_FRAME_CYCLE_CTRL_SDT(value) ((ILI9225_FRAME_CYCLE_CTRL_SDT_MSK & ((value) << ILI9225_FRAME_CYCLE_CTRL_SDT_POS)))
#define ILI9225_FRAME_CYCLE_CTRL_NO_POS     12
#define ILI9225_FRAME_CYCLE_CTRL_NO_MSK     (0xfu << ILI9225_FRAME_CYCLE_CTRL_NO_POS)
#define ILI9225_FRAME_CYCLE_CTRL_NO(value)  ((ILI9225_FRAME_CYCLE_CTRL_NO_MSK & ((value) << ILI9225_FRAME_CYCLE_CTRL_NO_POS)))

/* -------- ILI9225_INTERFACE_CTRL : (Offset: 0x0C) Interface Control -------- */
#define ILI9225_INTERFACE_CTRL            (0x0Cu)
#define ILI9225_INTERFACE_CTRL_RIM_POS    0
#define ILI9225_INTERFACE_CTRL_RIM_MSK    (0x3u << ILI9225_INTERFACE_CTRL_RIM_POS)
#define ILI9225_INTERFACE_CTRL_RIM(value) ((ILI9225_INTERFACE_CTRL_RIM_MSK & ((value) << ILI9225_INTERFACE_CTRL_RIM_POS)))
#define ILI9225_INTERFACE_CTRL_DM         (0x1u << 4)
#define ILI9225_INTERFACE_CTRL_RM         (0x1u << 8)

/* -------- ILI9225_OSC_CTRL : (Offset: 0x0F) Osc Control -------- */
#define ILI9225_OSC_CTRL             (0x0Fu)
#define ILI9225_OSC_CTRL_ON          (0x1u << 0)
#define ILI9225_OSC_CTRL_FOSC_POS    8
#define ILI9225_OSC_CTRL_FOSC_MSK    (0xfu << ILI9225_OSC_CTRL_FOSC_POS)
#define ILI9225_OSC_CTRL_FOSC(value) ((ILI9225_OSC_CTRL_FOSC_MSK & ((value) << ILI9225_OSC_CTRL_FOSC_POS)))

/* -------- ILI9225_POWER_CTRL1 : (Offset: 0x10) Power Control 1 -------- */
#define ILI9225_POWER_CTRL1            (0x10u)
#define ILI9225_POWER_CTRL1_STB        (0x1u << 0)
#define ILI9225_POWER_CTRL1_SAP_POS    8
#define ILI9225_POWER_CTRL1_SAP_MSK    (0xfu << ILI9225_POWER_CTRL1_SAP_POS)
#define ILI9225_POWER_CTRL1_SAP(value) ((ILI9225_POWER_CTRL1_SAP_MSK & ((value) << ILI9225_POWER_CTRL1_SAP_POS)))

/* -------- ILI9225_POWER_CTRL2 : (Offset: 0x11) Power Control 2 -------- */
#define ILI9225_POWER_CTRL2           (0x11u)
#define ILI9225_POWER_CTRL2_VC_POS    0
#define ILI9225_POWER_CTRL2_VC_MSK    (0xfu << ILI9225_POWER_CTRL2_VC_POS)
#define ILI9225_POWER_CTRL2_VC(value) ((ILI9225_POWER_CTRL2_VC_MSK & ((value) << ILI9225_POWER_CTRL2_VC_POS)))
#define ILI9225_POWER_CTRL2_VCI1      (0x1u << 4)
#define ILI9225_POWER_CTRL2_AON       (0x1u << 5)
#define ILI9225_POWER_CTRL2_PON       (0x1u << 8)
#define ILI9225_POWER_CTRL2_PON1      (0x1u << 9)
#define ILI9225_POWER_CTRL2_PON2      (0x1u << 10)
#define ILI9225_POWER_CTRL2_PON3      (0x1u << 11)
#define ILI9225_POWER_CTRL2_APON      (0x1u << 12)

/* -------- ILI9225_POWER_CTRL3 : (Offset: 0x12) Power Control 3 -------- */
#define ILI9225_POWER_CTRL3            (0x12u)
#define ILI9225_POWER_CTRL3_DC3_POS    0
#define ILI9225_POWER_CTRL3_DC3_MSK    (0x7u << ILI9225_POWER_CTRL3_DC3_POS)
#define ILI9225_POWER_CTRL3_DC3(value) ((ILI9225_POWER_CTRL3_DC3_MSK & ((value) << ILI9225_POWER_CTRL3_DC3_POS)))
#define ILI9225_POWER_CTRL3_DC2_POS    4
#define ILI9225_POWER_CTRL3_DC2_MSK    (0x7u << ILI9225_POWER_CTRL3_DC2_POS)
#define ILI9225_POWER_CTRL3_DC2(value) ((ILI9225_POWER_CTRL3_DC2_MSK & ((value) << ILI9225_POWER_CTRL3_DC2_POS)))
#define ILI9225_POWER_CTRL3_DC1_POS    8
#define ILI9225_POWER_CTRL3_DC1_MSK    (0x7u << ILI9225_POWER_CTRL3_DC1_POS)
#define ILI9225_POWER_CTRL3_DC1(value) ((ILI9225_POWER_CTRL3_DC1_MSK & ((value) << ILI9225_POWER_CTRL3_DC1_POS)))
#define ILI9225_POWER_CTRL3_BT_POS     12
#define ILI9225_POWER_CTRL3_BT_MSK     (0x7u << ILI9225_POWER_CTRL3_BT_POS)
#define ILI9225_POWER_CTRL3_BT(value)  ((ILI9225_POWER_CTRL3_BT_MSK & ((value) << ILI9225_POWER_CTRL3_BT_POS)))

/* -------- ILI9225_POWER_CTRL4 : (Offset: 0x13) Power Control 4 -------- */
#define ILI9225_POWER_CTRL4            (0x13u)
#define ILI9225_POWER_CTRL4_GVD_POS    0
#define ILI9225_POWER_CTRL4_GVD_MSK    (0x7fu << ILI9225_POWER_CTRL4_GVD_POS)
#define ILI9225_POWER_CTRL4_GVD(value) ((ILI9225_POWER_CTRL4_GVD_MSK & ((value) << ILI9225_POWER_CTRL4_GVD_POS)))

/* -------- ILI9225_POWER_CTRL5 : (Offset: 0x14) Power Control 5 -------- */
#define ILI9225_POWER_CTRL5            (0x14u)
#define ILI9225_POWER_CTRL5_VML_POS    0
#define ILI9225_POWER_CTRL5_VML_MSK    (0x7fu << ILI9225_POWER_CTRL5_VML_POS)
#define ILI9225_POWER_CTRL5_VML(value) ((ILI9225_POWER_CTRL5_VML_MSK & ((value) << ILI9225_POWER_CTRL5_VML_POS)))
#define ILI9225_POWER_CTRL5_VCM_POS    8
#define ILI9225_POWER_CTRL5_VCM_MSK    (0x7fu << ILI9225_POWER_CTRL5_VCM_POS)
#define ILI9225_POWER_CTRL5_VCM(value) ((ILI9225_POWER_CTRL5_VCM_MSK & ((value) << ILI9225_POWER_CTRL5_VCM_POS)))
#define ILI9225_POWER_CTRL5_VCOMG      (0x1u << 15)

/* -------- ILI9225_RAM_ADDR_SET1 : (Offset: 0x20) Horizontal GRAM Address Set -------- */
#define ILI9225_RAM_ADDR_SET1           (0x20u)
#define ILI9225_RAM_ADDR_SET1_AD_POS    0
#define ILI9225_RAM_ADDR_SET1_AD_MSK    (0xffu << ILI9225_RAM_ADDR_SET1_AD_POS)
#define ILI9225_RAM_ADDR_SET1_AD(value) ((ILI9225_RAM_ADDR_SET1_AD_MSK & ((value) << ILI9225_RAM_ADDR_SET1_AD_POS)))

/* -------- ILI9225_RAM_ADDR_SET2 : (Offset: 0x21) Vertical GRAM Address Set -------- */
#define ILI9225_RAM_ADDR_SET2           (0x21u)
#define ILI9225_RAM_ADDR_SET2_AD_POS    0
#define ILI9225_RAM_ADDR_SET2_AD_MSK    (0xffu << ILI9225_RAM_ADDR_SET2_AD_POS)
#define ILI9225_RAM_ADDR_SET2_AD(value) ((ILI9225_RAM_ADDR_SET2_AD_MSK & ((value) << ILI9225_RAM_ADDR_SET2_AD_POS)))

/* -------- ILI9225_GRAM_DATA_REG : (Offset: 0x22) GRAM Data Register -------- */
#define ILI9225_GRAM_DATA_REG           (0x22u)

/* -------- ILI9225_GATE_SCAN_REG : (Offset: 0x30) Gate Scan Control Register -------- */
#define ILI9225_GATE_SCAN_CTRL            (0x30u)
#define ILI9225_GATE_SCAN_CTRL_SCN_POS    0
#define ILI9225_GATE_SCAN_CTRL_SCN_MSK    (0x1fu << ILI9225_GATE_SCAN_CTRL_SCN_POS)
#define ILI9225_GATE_SCAN_CTRL_SCN(value) ((ILI9225_GATE_SCAN_CTRL_SCN_MSK & ((value) << ILI9225_GATE_SCAN_CTRL_SCN_POS)))

/* -------- ILI9225_VERTICAL_SCROLL_CTRL1 : (Offset: 0x31) Vertical Scroll Control 1 Register -------- */
#define ILI9225_VERTICAL_SCROLL_CTRL1            (0x31u)
#define ILI9225_VERTICAL_SCROLL_CTRL1_SEA_POS    0
#define ILI9225_VERTICAL_SCROLL_CTRL1_SEA_MSK    (0xffu << ILI9225_VERTICAL_SCROLL_CTRL1_SEA_POS)
#define ILI9225_VERTICAL_SCROLL_CTRL1_SEA(value) ((ILI9225_VERTICAL_SCROLL_CTRL1_SEA_MSK & ((value) << ILI9225_VERTICAL_SCROLL_CTRL1_SEA_POS)))

/* -------- ILI9225_VERTICAL_SCROLL_CTRL2 : (Offset: 0x32) Vertical Scroll Control 2 Register -------- */
#define ILI9225_VERTICAL_SCROLL_CTRL2            (0x32u)
#define ILI9225_VERTICAL_SCROLL_CTRL2_SSA_POS    0
#define ILI9225_VERTICAL_SCROLL_CTRL2_SSA_MSK    (0xffu << ILI9225_VERTICAL_SCROLL_CTRL2_SSA_POS)
#define ILI9225_VERTICAL_SCROLL_CTRL2_SSA(value) ((ILI9225_VERTICAL_SCROLL_CTRL2_SSA_MSK & ((value) << ILI9225_VERTICAL_SCROLL_CTRL2_SSA_POS)))

/* -------- ILI9225_VERTICAL_SCROLL_CTRL3 : (Offset: 0x33) Vertical Scroll Control 3 Register -------- */
#define ILI9225_VERTICAL_SCROLL_CTRL3            (0x33u)
#define ILI9225_VERTICAL_SCROLL_CTRL3_SST_POS    0
#define ILI9225_VERTICAL_SCROLL_CTRL3_SST_MSK    (0xffu << ILI9225_VERTICAL_SCROLL_CTRL3_SST_POS)
#define ILI9225_VERTICAL_SCROLL_CTRL3_SST(value) ((ILI9225_VERTICAL_SCROLL_CTRL3_SST_MSK & ((value) << ILI9225_VERTICAL_SCROLL_CTRL3_SST_POS)))

/* -------- ILI9225_PARTIAL_DRIVING_POS1 : (Offset: 0x34) Partial Driving Position 1 Register -------- */
#define ILI9225_PARTIAL_DRIVING_POS1            (0x34u)
#define ILI9225_PARTIAL_DRIVING_POS1_SE1_POS    0
#define ILI9225_PARTIAL_DRIVING_POS1_SE1_MSK    (0xffu << ILI9225_PARTIAL_DRIVING_POS1_SE1_POS)
#define ILI9225_PARTIAL_DRIVING_POS1_SE1(value) ((ILI9225_PARTIAL_DRIVING_POS1_SE1_MSK & ((value) << ILI9225_PARTIAL_DRIVING_POS1_SE1_POS)))

/* -------- ILI9225_PARTIAL_DRIVING_POS2 : (Offset: 0x35) Partial Driving Position 2 Register -------- */
#define ILI9225_PARTIAL_DRIVING_POS2            (0x35u)
#define ILI9225_PARTIAL_DRIVING_POS2_SS1_POS    0
#define ILI9225_PARTIAL_DRIVING_POS2_SS1_MSK    (0xffu << ILI9225_PARTIAL_DRIVING_POS2_SS1_POS)
#define ILI9225_PARTIAL_DRIVING_POS2_SS1(value) ((ILI9225_PARTIAL_DRIVING_POS2_SS1_MSK & ((value) << ILI9225_PARTIAL_DRIVING_POS2_SS1_POS)))

/* -------- ILI9225_HORIZONTAL_WINDOW_ADDR1 : (Offset: 0x36) Horizontal Address Start Position -------- */
#define ILI9225_HORIZONTAL_WINDOW_ADDR1            (0x36u)
#define ILI9225_HORIZONTAL_WINDOW_ADDR1_HEA_POS    0
#define ILI9225_HORIZONTAL_WINDOW_ADDR1_HEA_MSK    (0xffu << ILI9225_HORIZONTAL_WINDOW_ADDR1_HEA_POS)
#define ILI9225_HORIZONTAL_WINDOW_ADDR1_HEA(value) ((ILI9225_HORIZONTAL_WINDOW_ADDR1_HEA_MSK & ((value) << ILI9225_HORIZONTAL_WINDOW_ADDR1_HEA_POS)))

/* -------- ILI9225_HORIZONTAL_WINDOW_ADDR2 : (Offset: 0x37) Horizontal Address End Position -------- */
#define ILI9225_HORIZONTAL_WINDOW_ADDR2            (0x37u)
#define ILI9225_HORIZONTAL_WINDOW_ADDR2_HSA_POS    0
#define ILI9225_HORIZONTAL_WINDOW_ADDR2_HSA_MSK    (0xffu << ILI9225_HORIZONTAL_WINDOW_ADDR2_HSA_POS)
#define ILI9225_HORIZONTAL_WINDOW_ADDR2_HSA(value) ((ILI9225_HORIZONTAL_WINDOW_ADDR2_HSA_MSK & ((value) << ILI9225_HORIZONTAL_WINDOW_ADDR2_HSA_POS)))

/* -------- ILI9225_VERTICAL_WINDOW_ADDR1 : (Offset: 0x38) Vertical Address Start Position -------- */
#define ILI9225_VERTICAL_WINDOW_ADDR1            (0x38u)
#define ILI9225_VERTICAL_WINDOW_ADDR1_VEA_POS    0
#define ILI9225_VERTICAL_WINDOW_ADDR1_VEA_MSK    (0xffu << ILI9225_VERTICAL_WINDOW_ADDR1_VEA_POS)
#define ILI9225_VERTICAL_WINDOW_ADDR1_VEA(value) ((ILI9225_VERTICAL_WINDOW_ADDR1_VEA_MSK & ((value) << ILI9225_VERTICAL_WINDOW_ADDR1_VEA_POS)))

/* -------- ILI9225_VERTICAL_WINDOW_ADDR2 : (Offset: 0x39) Vertical Address End Position -------- */
#define ILI9225_VERTICAL_WINDOW_ADDR2            (0x39u)
#define ILI9225_VERTICAL_WINDOW_ADDR2_VSA_POS    0
#define ILI9225_VERTICAL_WINDOW_ADDR2_VSA_MSK    (0xffu << ILI9225_VERTICAL_WINDOW_ADDR2_VSA_POS)
#define ILI9225_VERTICAL_WINDOW_ADDR2_VSA(value) ((ILI9225_VERTICAL_WINDOW_ADDR2_VSA_MSK & ((value) << ILI9225_VERTICAL_WINDOW_ADDR2_VSA_POS)))

/* -------- ILI9225_GAMMA_CTRL1 : (Offset: 0x50) Gamma Control 1 -------- */
#define ILI9225_GAMMA_CTRL1            (0x50u)
#define ILI9225_GAMMA_CTRL1_KP0_POS    0
#define ILI9225_GAMMA_CTRL1_KP0_MSK    (0xfu << ILI9225_GAMMA_CTRL1_KP0_POS)
#define ILI9225_GAMMA_CTRL1_KP0(value) ((ILI9225_GAMMA_CTRL1_KP0_MSK & ((value) << ILI9225_GAMMA_CTRL1_KP0_POS)))
#define ILI9225_GAMMA_CTRL1_KP1_POS    8
#define ILI9225_GAMMA_CTRL1_KP1_MSK    (0xfu << ILI9225_GAMMA_CTRL1_KP1_POS)
#define ILI9225_GAMMA_CTRL1_KP1(value) ((ILI9225_GAMMA_CTRL1_KP1_MSK & ((value) << ILI9225_GAMMA_CTRL1_KP1_POS)))

/* -------- ILI9225_GAMMA_CTRL2 : (Offset: 0x51) Gamma Control 2 -------- */
#define ILI9225_GAMMA_CTRL2            (0x51u)
#define ILI9225_GAMMA_CTRL2_KP2_POS    0
#define ILI9225_GAMMA_CTRL2_KP2_MSK    (0xfu << ILI9225_GAMMA_CTRL2_KP2_POS)
#define ILI9225_GAMMA_CTRL2_KP2(value) ((ILI9225_GAMMA_CTRL2_KP2_MSK & ((value) << ILI9225_GAMMA_CTRL2_KP2_POS)))
#define ILI9225_GAMMA_CTRL2_KP3_POS    8
#define ILI9225_GAMMA_CTRL2_KP3_MSK    (0xfu << ILI9225_GAMMA_CTRL2_KP3_POS)
#define ILI9225_GAMMA_CTRL2_KP3(value) ((ILI9225_GAMMA_CTRL2_KP3_MSK & ((value) << ILI9225_GAMMA_CTRL2_KP3_POS)))

/* -------- ILI9225_GAMMA_CTRL3 : (Offset: 0x52) Gamma Control 3 -------- */
#define ILI9225_GAMMA_CTRL3            (0x52u)
#define ILI9225_GAMMA_CTRL3_KP4_POS    0
#define ILI9225_GAMMA_CTRL3_KP4_MSK    (0xfu << ILI9225_GAMMA_CTRL3_KP4_POS)
#define ILI9225_GAMMA_CTRL3_KP4(value) ((ILI9225_GAMMA_CTRL3_KP4_MSK & ((value) << ILI9225_GAMMA_CTRL3_KP4_POS)))
#define ILI9225_GAMMA_CTRL3_KP5_POS    8
#define ILI9225_GAMMA_CTRL3_KP5_MSK    (0xfu << ILI9225_GAMMA_CTRL3_KP5_POS)
#define ILI9225_GAMMA_CTRL3_KP5(value) ((ILI9225_GAMMA_CTRL3_KP5_MSK & ((value) << ILI9225_GAMMA_CTRL3_KP5_POS)))

/* -------- ILI9225_GAMMA_CTRL4 : (Offset: 0x53) Gamma Control 4 -------- */
#define ILI9225_GAMMA_CTRL4            (0x53u)
#define ILI9225_GAMMA_CTRL4_RP0_POS    0
#define ILI9225_GAMMA_CTRL4_RP0_MSK    (0xfu << ILI9225_GAMMA_CTRL4_RP0_POS)
#define ILI9225_GAMMA_CTRL4_RP0(value) ((ILI9225_GAMMA_CTRL4_RP0_MSK & ((value) << ILI9225_GAMMA_CTRL4_RP0_POS)))
#define ILI9225_GAMMA_CTRL4_RP1_POS    8
#define ILI9225_GAMMA_CTRL4_RP1_MSK    (0xfu << ILI9225_GAMMA_CTRL4_RP1_POS)
#define ILI9225_GAMMA_CTRL4_RP1(value) ((ILI9225_GAMMA_CTRL4_RP1_MSK & ((value) << ILI9225_GAMMA_CTRL4_RP1_POS)))

/* -------- ILI9225_GAMMA_CTRL5 : (Offset: 0x54) Gamma Control 5 -------- */
#define ILI9225_GAMMA_CTRL5            (0x54u)
#define ILI9225_GAMMA_CTRL5_KN0_POS    0
#define ILI9225_GAMMA_CTRL5_KN0_MSK    (0xfu << ILI9225_GAMMA_CTRL5_KN0_POS)
#define ILI9225_GAMMA_CTRL5_KN0(value) ((ILI9225_GAMMA_CTRL5_KN0_MSK & ((value) << ILI9225_GAMMA_CTRL5_KN0_POS)))
#define ILI9225_GAMMA_CTRL5_KN1_POS    8
#define ILI9225_GAMMA_CTRL5_KN1_MSK    (0xfu << ILI9225_GAMMA_CTRL5_KN1_POS)
#define ILI9225_GAMMA_CTRL5_KN1(value) ((ILI9225_GAMMA_CTRL5_KN1_MSK & ((value) << ILI9225_GAMMA_CTRL5_KN1_POS)))

/* -------- ILI9225_GAMMA_CTRL6 : (Offset: 0x55) Gamma Control 6 -------- */
#define ILI9225_GAMMA_CTRL6            (0x55u)
#define ILI9225_GAMMA_CTRL6_KN2_POS    0
#define ILI9225_GAMMA_CTRL6_KN2_MSK    (0xfu << ILI9225_GAMMA_CTRL6_KN2_POS)
#define ILI9225_GAMMA_CTRL6_KN2(value) ((ILI9225_GAMMA_CTRL6_KN2_MSK & ((value) << ILI9225_GAMMA_CTRL6_KN2_POS)))
#define ILI9225_GAMMA_CTRL6_KN3_POS    8
#define ILI9225_GAMMA_CTRL6_KN3_MSK    (0xfu << ILI9225_GAMMA_CTRL6_KN3_POS)
#define ILI9225_GAMMA_CTRL6_KN3(value) ((ILI9225_GAMMA_CTRL6_KN3_MSK & ((value) << ILI9225_GAMMA_CTRL6_KN3_POS)))

/* -------- ILI9225_GAMMA_CTRL7 : (Offset: 0x56) Gamma Control 7 -------- */
#define ILI9225_GAMMA_CTRL7            (0x56u)
#define ILI9225_GAMMA_CTRL7_KN4_POS    0
#define ILI9225_GAMMA_CTRL7_KN4_MSK    (0xfu << ILI9225_GAMMA_CTRL7_KN4_POS)
#define ILI9225_GAMMA_CTRL7_KN4(value) ((ILI9225_GAMMA_CTRL7_KN4_MSK & ((value) << ILI9225_GAMMA_CTRL7_KN4_POS)))
#define ILI9225_GAMMA_CTRL7_KN5_POS    8
#define ILI9225_GAMMA_CTRL7_KN5_MSK    (0xfu << ILI9225_GAMMA_CTRL7_KN5_POS)
#define ILI9225_GAMMA_CTRL7_KN5(value) ((ILI9225_GAMMA_CTRL7_KN5_MSK & ((value) << ILI9225_GAMMA_CTRL7_KN5_POS)))

/* -------- ILI9225_GAMMA_CTRL8 : (Offset: 0x57) Gamma Control 8 -------- */
#define ILI9225_GAMMA_CTRL8            (0x57u)
#define ILI9225_GAMMA_CTRL8_RN0_POS    0
#define ILI9225_GAMMA_CTRL8_RN0_MSK    (0xfu << ILI9225_GAMMA_CTRL8_RN0_POS)
#define ILI9225_GAMMA_CTRL8_RN0(value) ((ILI9225_GAMMA_CTRL8_RN0_MSK & ((value) << ILI9225_GAMMA_CTRL8_RN0_POS)))
#define ILI9225_GAMMA_CTRL8_RN1_POS    8
#define ILI9225_GAMMA_CTRL8_RN1_MSK    (0xfu << ILI9225_GAMMA_CTRL8_RN1_POS)
#define ILI9225_GAMMA_CTRL8_RN1(value) ((ILI9225_GAMMA_CTRL8_RN1_MSK & ((value) << ILI9225_GAMMA_CTRL8_RN1_POS)))

/* -------- ILI9225_GAMMA_CTRL9 : (Offset: 0x58) Gamma Control 9 -------- */
#define ILI9225_GAMMA_CTRL9             (0x58u)
#define ILI9225_GAMMA_CTRL9_VRP0_POS    0
#define ILI9225_GAMMA_CTRL9_VRP0_MSK    (0x1fu << ILI9225_GAMMA_CTRL9_VRP0_POS)
#define ILI9225_GAMMA_CTRL9_VRP0(value) ((ILI9225_GAMMA_CTRL9_VRP0_MSK & ((value) << ILI9225_GAMMA_CTRL9_VRP0_POS)))
#define ILI9225_GAMMA_CTRL9_VRP1_POS    8
#define ILI9225_GAMMA_CTRL9_VRP1_MSK    (0x1fu << ILI9225_GAMMA_CTRL9_VRP1_POS)
#define ILI9225_GAMMA_CTRL9_VRP1(value) ((ILI9225_GAMMA_CTRL9_VRP1_MSK & ((value) << ILI9225_GAMMA_CTRL9_VRP1_POS)))

/* -------- ILI9225_GAMMA_CTRL10 : (Offset: 0x59) Gamma Control 10 -------- */
#define ILI9225_GAMMA_CTRL10             (0x59u)
#define ILI9225_GAMMA_CTRL10_VRN0_POS    0
#define ILI9225_GAMMA_CTRL10_VRN0_MSK    (0x1fu << ILI9225_GAMMA_CTRL10_VRN0_POS)
#define ILI9225_GAMMA_CTRL10_VRN0(value) ((ILI9225_GAMMA_CTRL10_VRN0_MSK & ((value) << ILI9225_GAMMA_CTRL10_VRN0_POS)))
#define ILI9225_GAMMA_CTRL10_VRN1_POS    8
#define ILI9225_GAMMA_CTRL10_VRN1_MSK    (0x1fu << ILI9225_GAMMA_CTRL10_VRN1_POS)
#define ILI9225_GAMMA_CTRL10_VRN1(value) ((ILI9225_GAMMA_CTRL10_VRN1_MSK & ((value) << ILI9225_GAMMA_CTRL10_VRN1_POS)))

/* -------- ILI9225_NV_MEM_DATA_PROG : (Offset: 0x60) NV Memory Data Programming -------- */
#define ILI9225_NV_MEM_DATA_PROG              (0x60u)
#define ILI9225_NV_MEM_DATA_PROG_NVM_D_POS    0
#define ILI9225_NV_MEM_DATA_PROG_NVM_D_MSK    (0xffu << ILI9225_NV_MEM_DATA_PROG_NVM_D_POS)
#define ILI9225_NV_MEM_DATA_PROG_NVM_D(value) ((ILI9225_NV_MEM_DATA_PROG_NVM_D_MSK & ((value) << ILI9225_NV_MEM_DATA_PROG_NVM_D_POS)))

/* -------- ILI9225_NV_MEM_CTRL : (Offset: 0x61) NV Memory Control -------- */
#define ILI9225_NV_MEM_CTRL            (0x61u)
#define ILI9225_NV_MEM_CTRL_VCM_PGM_EN (0x1u << 0)
#define ILI9225_NV_MEM_CTRL_ID_PGM_EN  (0x1u << 1)
#define ILI9225_NV_MEM_CTRL_VCM_SEL    (0x1u << 8)

/* -------- ILI9225_NV_MEM_STATUS : (Offset: 0x62) NV Memory Status -------- */
#define ILI9225_NV_MEM_STATUS                (0x62u)
#define ILI9225_NV_MEM_STATUS_VCM_D_POS      0
#define ILI9225_NV_MEM_STATUS_VCM_D_MSK      (0x7fu << ILI9225_NV_MEM_STATUS_VCM_D_POS)
#define ILI9225_NV_MEM_STATUS_VCM_D(value)   ((ILI9225_NV_MEM_STATUS_VCM_D_MSK & ((value)ILI9225_NV_MEM_STATUS_VCM_D_POS)))
#define ILI9225_NV_MEM_STATUS_PGM_CNT_POS    12
#define ILI9225_NV_MEM_STATUS_PGM_CNT_MSK    (0x3u << ILI9225_NV_MEM_DATA_PROG_NVM_D_POS)
#define ILI9225_NV_MEM_STATUS_PGM_CNT(value) ((ILI9225_NV_MEM_STATUS_PGM_CNT_MSK & ((value) << ILI9225_NV_MEM_STATUS_PGM_CNT_POS)))

/* -------- ILI9225_NV_MEM_PROTECTION_KEY : (Offset: 0x63) NV Memory Protection Key -------- */
#define ILI9225_NV_MEM_PROTECTION_KEY            (0x63u)
#define ILI9225_NV_MEM_PROTECTION_KEY_KEY_POS    0
#define ILI9225_NV_MEM_PROTECTION_KEY_KEY_MSK    (0xffffu << ILI9225_NV_MEM_PROTECTION_KEY_KEY_POS)
#define ILI9225_NV_MEM_PROTECTION_KEY_KEY(value) ((ILI9225_NV_MEM_PROTECTION_KEY_KEY_MSK & ((value) << ILI9225_NV_MEM_PROTECTION_KEY_KEY_POS)))

/* -------- ILI9225_ID_CODE : (Offset: 0x65) LCM Vendor Code -------- */
#define ILI9225_ID_CODE           (0x65u)
#define ILI9225_ID_CODE_ID_POS    0
#define ILI9225_ID_CODE_ID_MSK    (0xfu << ILI9225_ID_CODE_ID_POS)
#define ILI9225_ID_CODE_ID(value) ((ILI9225_ID_CODE_ID_MSK & ((value) << ILI9225_ID_CODE_ID_POS)))

/* -------- ILI9225_SPI_RW_CTRL : (Offset: 0x65) Spi Read/Write Control -------- */
#define ILI9225_SPI_RW_CTRL     (0x66u)
#define ILI9225_SPI_RW_CTRL_RWX (0x1u << 0)

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
 * Data type for ili9225 color (RGB565)
 */
typedef uint16_t ili9225_color_t;

/**
 * Input parameters when initializing ili9225 driver.
 */
struct ili9225_opt_t {
	uint32_t ul_width;          //!< lcd width in pixel
	uint32_t ul_height;         //!< lcd height in pixel
	uint32_t foreground_color;  //!< lcd foreground color
	uint32_t background_color;  //!< lcd background color
};

/**
 * Font structure
 */
struct ili9225_font {
	/* Font width in pixels. */
	uint8_t width;
	/* Font height in pixels. */
	uint8_t height;
};

/**
 * Display direction option
 */
enum ili9225_display_direction {
	LANDSCAPE  = 0,
	PORTRAIT   = 1
};

/**
 * Shift direction option
 */
enum ili9225_shift_direction {
	H_INCREASE  = 0,
	H_DECREASE  = 1
};

/**
 * Scan direction option
 */
enum ili9225_scan_direction {
	V_INCREASE  = 0,
	V_DEREASE   = 1
};

uint32_t ili9225_init(struct ili9225_opt_t *p_opt);
void ili9225_spi_handler(void);
void ili9225_display_on(void);
void ili9225_display_off(void);
void ili9225_set_foreground_color(uint32_t ul_rgb24bits);
void ili9225_fill(ili9225_color_t ul_color);
void ili9225_set_window(uint32_t ul_x, uint32_t ul_y,
		uint32_t ul_width, uint32_t ul_height);
void ili9225_set_cursor_position(uint16_t us_x, uint16_t us_y);
void ili9225_scroll(uint8_t uc_startline, uint8_t uc_endline);
void ili9225_enable_scroll(uint8_t uc_linenum);
void ili9225_disable_scroll(void);
void ili9225_set_display_direction(enum ili9225_display_direction e_dd,
		enum ili9225_shift_direction e_shd, enum ili9225_scan_direction e_scd);
uint32_t ili9225_draw_pixel(uint32_t ul_x, uint32_t ul_y);
ili9225_color_t ili9225_get_pixel(uint32_t ul_x, uint32_t ul_y);
void ili9225_draw_line(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2);
void ili9225_draw_rectangle(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2);
void ili9225_draw_filled_rectangle(uint32_t ul_x1, uint32_t ul_y1,
		uint32_t ul_x2, uint32_t ul_y2);
uint32_t ili9225_draw_circle(uint32_t ul_x, uint32_t ul_y, uint32_t ul_r);
uint32_t ili9225_draw_filled_circle(uint32_t ul_x, uint32_t ul_y, uint32_t ul_r);
void ili9225_draw_string(uint32_t ul_x, uint32_t ul_y, const uint8_t *p_str);
void ili9225_draw_pixmap(uint32_t ul_x, uint32_t ul_y, uint32_t ul_width,
		uint32_t ul_height, const ili9225_color_t *p_ul_pixmap);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* ILI9225_H_INCLUDED */
