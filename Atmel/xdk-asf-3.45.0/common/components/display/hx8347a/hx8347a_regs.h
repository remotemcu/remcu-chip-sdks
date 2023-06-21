/**
 * \file
 *
 * \brief HX8347A display controller register and bitfield definitions
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
#ifndef DRIVERS_GFX_HX8347A_HX8347A_REGS_H_INCLUDED
#define DRIVERS_GFX_HX8347A_HX8347A_REGS_H_INCLUDED

/* SPI communication start byte bit fields */

#define HX8347A_START_ID  0x70
#define HX8347A_START_BS0 0x04
#define HX8347A_START_RS  0x02
#define HX8347A_START_RW  0x01

#define HX8347A_START_WRITEIDX (HX8347A_START_ID | HX8347A_START_BS0)
#define HX8347A_START_WRITEREG (HX8347A_START_ID | HX8347A_START_BS0 | \
		HX8347A_START_RS)
#define HX8347A_START_READREG (HX8347A_START_ID | HX8347A_START_BS0 | \
		HX8347A_START_RS | HX8347A_START_RW)


/* HIMAX controller register addresses and bit values */

#define HX8347A_DISPMODECTRL 0x01
#define HX8347A_INVON 2

#define HX8347A_COLSTARTHIGH 0x02
#define HX8347A_COLSTARTLOW  0x03
#define HX8347A_COLENDHIGH   0x04
#define HX8347A_COLENDLOW    0x05
#define HX8347A_ROWSTARTHIGH 0x06
#define HX8347A_ROWSTARTLOW  0x07
#define HX8347A_ROWENDHIGH   0x08
#define HX8347A_ROWENDLOW    0x09

#define HX8347A_MEMACCESSCTRL 0x16
#define HX8347A_MY 7
#define HX8347A_MX 6
#define HX8347A_MV 5
#define HX8347A_BGR 3

#define HX8347A_OSCCTRL1 0x19
/* Default 0 */
#define HX8347A_OSC_EN 0
#define HX8347A_OSCCTRL2 0x1A
#define HX8347A_OSCCTRL3 0x93

#define HX8347A_POWERCTRL1 0x1B
/* Default 0 */
#define HX8347A_GASENB   7
/* Default 0 */
#define HX8347A_PON      4
/* Default 1 */
#define HX8347A_DK       3
/* Default 0 */
#define HX8347A_XDK      2
/* Default 0 */
#define HX8347A_VTFT_TRI 1
/* Default 1 */
#define HX8347A_STB      0

#define HX8347A_POWERCTRL2 0x1C
/* Default 0 */
#define HX8347A_AP2 2
/* Default 0 */
#define HX8347A_AP1 1
/* Default 0 */
#define HX8347A_AP0 0
#define HX8347A_POWERCTRL3 0x1D
#define HX8347A_POWERCTRL4 0x1E
#define HX8347A_POWERCTRL5 0x1F
#define HX8347A_POWERCTRL6 0x20

#define HX8347A_SRAMWRITE 0x22
#define HX8347A_CYCLECTRL1_X 0x23
#define HX8347A_CYCLECTRL2_X 0x24
#define HX8347A_CYCLECTRL3_X 0x25

#define HX8347A_DISPCTRL1 0x26
/* Default 0 */
#define HX8347A_PT1 7
/* Default 0 */
#define HX8347A_PT0 6
/* Default 1 */
#define HX8347A_GON 5
/* Default 0 */
#define HX8347A_DTE 4
/* Default 0 */
#define HX8347A_D1 3
/* Default 0 */
#define HX8347A_D0 2
#define HX8347A_DISPCTRL2 0x27
#define HX8347A_DISPCTRL3 0x28
#define HX8347A_DISPCTRL4 0x29
#define HX8347A_DISPCTRL5 0x2A
#define HX8347A_DISPCTRL6 0x2C
#define HX8347A_DISPCTRL7 0x2D
#define HX8347A_DISPCTRL9 0x35
#define HX8347A_DISPCTRL10 0x36

#define HX8347A_CYCLECTRL1 0x3A
#define HX8347A_CYCLECTRL2 0x3B
#define HX8347A_CYCLECTRL3 0x3C
#define HX8347A_CYCLECTRL4 0x3D
#define HX8347A_CYCLECTRL5 0x3E
#define HX8347A_CYCLECTRL6 0x40
#define HX8347A_CYCLECTRL7 0x41

#define HX8347A_VCOMCTRL1 0x43
/* Default 0*/
#define HX8347A_VCOMG 7
#define HX8347A_VCOMCTRL2 0x44
#define HX8347A_VCOMCTRL3 0x45

#define HX8347A_GAMMACTRL1  0x46
#define HX8347A_GAMMACTRL2  0x47
#define HX8347A_GAMMACTRL3  0x48
#define HX8347A_GAMMACTRL4  0x49
#define HX8347A_GAMMACTRL5  0x4A
#define HX8347A_GAMMACTRL6  0x4B
#define HX8347A_GAMMACTRL7  0x4C
#define HX8347A_GAMMACTRL8  0x4D
#define HX8347A_GAMMACTRL9  0x4E
#define HX8347A_GAMMACTRL10 0x4F
#define HX8347A_GAMMACTRL11 0x50
#define HX8347A_GAMMACTRL12 0x51

#define HX8347A_INTERNAL28 0x70
#define HX8347A_TEON 3

#define HX8347A_SAP 0x90
#define HX8347A_DISPCTRL8 0x90

/* Bitmask used by gfx_set_orientation to flip X direction */
#define HX8347A_FLIP_X_MASK (1 << HX8347A_MX)
/* Bitmask used by gfx_set_orientation to flip Y direction */
#define HX8347A_FLIP_Y_MASK (1 << HX8347A_MY)
/* Bitmask used by gfx_set_orientation to switch X and Y coordinates */
#define HX8347A_SWITCH_XY_MASK (1 << HX8347A_MV)

#endif /* DRIVERS_GFX_HX8347A_HX8347A_REGS_H_INCLUDED */
