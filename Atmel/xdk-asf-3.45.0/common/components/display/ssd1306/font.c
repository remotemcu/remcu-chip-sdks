/**
 * \file
 *
 * \brief SSD1306 fonts.
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

#include "compiler.h"
#include "font.h"

/*============================================*/
/*========= Character pointers table =========*/
/*============================================*/

uint8_t * font_table[95] = {
	Font08px_32,
	Font08px_33,
	Font08px_34,
	Font08px_35,
	Font08px_36,
	Font08px_37,
	Font08px_38,
	Font08px_39,
	Font08px_40,
	Font08px_41,
	Font08px_42,
	Font08px_43,
	Font08px_44,
	Font08px_45,
	Font08px_46,
	Font08px_47,
	Font08px_N0,
	Font08px_N1,
	Font08px_N2,
	Font08px_N3,
	Font08px_N4,
	Font08px_N5,
	Font08px_N6,
	Font08px_N7,
	Font08px_N8,
	Font08px_N9,
	Font08px_58,
	Font08px_59,
	Font08px_60,
	Font08px_61,
	Font08px_62,
	Font08px_63,
	Font08px_64,
	Font08px_UA,
	Font08px_UB,
	Font08px_UC,
	Font08px_UD,
	Font08px_UE,
	Font08px_UF,
	Font08px_UG,
	Font08px_UH,
	Font08px_UI,
	Font08px_UJ,
	Font08px_UK,
	Font08px_UL,
	Font08px_UM,
	Font08px_UN,
	Font08px_UO,
	Font08px_UP,
	Font08px_UQ,
	Font08px_UR,
	Font08px_US,
	Font08px_UT,
	Font08px_UU,
	Font08px_UV,
	Font08px_UW,
	Font08px_UX,
	Font08px_UY,
	Font08px_UZ,
	Font08px_91,
	Font08px_92,
	Font08px_93,
	Font08px_94,
	Font08px_95,
	Font08px_96,
	Font08px_la,
	Font08px_lb,
	Font08px_lc,
	Font08px_ld,
	Font08px_le,
	Font08px_lf,
	Font08px_lg,
	Font08px_lh,
	Font08px_li,
	Font08px_lj,
	Font08px_lk,
	Font08px_ll,
	Font08px_lm,
	Font08px_ln,
	Font08px_lo,
	Font08px_lp,
	Font08px_lq,
	Font08px_lr,
	Font08px_ls,
	Font08px_lt,
	Font08px_lu,
	Font08px_lv,
	Font08px_lw,
	Font08px_lx,
	Font08px_ly,
	Font08px_lz,
	Font08px_123,
	Font08px_124,
	Font08px_125,
	Font08px_126
};

/*===================================*/
/*========= Characters data =========*/
/*===================================*/

/**  0x20 - 32  - ' '  **/
uint8_t Font08px_32[3] = {2,
	bits2bytes(0,0,0,0,0,0,0,0),
	bits2bytes(0,0,0,0,0,0,0,0)};

/**  0x21 - 33  - '!'  **/
uint8_t Font08px_33[2] = {1,
	bits2bytes(1,0,1,1,1,1,1,0)};

/**  0x22 - 34  - '"'  **/
uint8_t Font08px_34[4] = {3,
	bits2bytes(0,0,0,0,0,1,1,0),
	bits2bytes(0,0,0,0,0,0,0,0),
	bits2bytes(0,0,0,0,0,1,1,0)};

/**  0x23 - 35  - '#'  **/
uint8_t Font08px_35[6] = {5,
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,1,0,1,0,0,0)};

/**  0x24 - 36  - '$'  **/
uint8_t Font08px_36[6] = {5,
	bits2bytes(0,1,0,0,1,0,0,0),
	bits2bytes(0,1,0,1,0,1,0,0),
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,1,0,1,0,1,0,0),
	bits2bytes(0,0,1,0,0,1,0,0)};

/**  0x25 - 37  - '%'  **/
uint8_t Font08px_37[6] = {5,
	bits2bytes(0,1,0,0,0,1,1,0),
	bits2bytes(0,0,1,0,0,1,1,0),
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(1,1,0,0,1,0,0,0),
	bits2bytes(1,1,0,0,0,1,0,0)};

/**  0x26 - 38  - '&'  **/
uint8_t Font08px_38[6] = {5,
	bits2bytes(0,1,1,0,1,1,0,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,1,0,1,1,0,0),
	bits2bytes(0,1,0,0,0,0,0,0),
	bits2bytes(1,0,1,0,0,0,0,0)};

/**  0x27 - 39  - '''  **/
uint8_t Font08px_39[2] = {1,
	bits2bytes(0,0,0,0,0,1,1,0)};

/**  0x28 - 40  - '('  **/
uint8_t Font08px_40[4] = {3,
	bits2bytes(0,0,1,1,1,0,0,0),
	bits2bytes(0,1,0,0,0,1,0,0),
	bits2bytes(1,0,0,0,0,0,1,0)};

/**  0x29 - 41  - ')'  **/
uint8_t Font08px_41[4] = {3,
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(0,1,0,0,0,1,0,0),
	bits2bytes(0,0,1,1,1,0,0,0)};

/**  0x2A - 42  - '*'  **/
uint8_t Font08px_42[4] = {3,
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,1,0,1,0,0,0)};

/**  0x2B - 43  - '+'  **/
uint8_t Font08px_43[4] = {3,
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,1,1,1,0,0,0),
	bits2bytes(0,0,0,1,0,0,0,0)};

/**  0x2C - 44  - ','  **/
uint8_t Font08px_44[2] = {1,
	bits2bytes(1,1,0,0,0,0,0,0)};

/**  0x2D - 45  - '-'  **/
uint8_t Font08px_45[4] = {3,
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,0,1,0,0,0,0)};

/**  0x2E - 46  - '.'  **/
uint8_t Font08px_46[2] = {1,
	bits2bytes(1,0,0,0,0,0,0,0)};

/**  0x2F - 47  - '/'  **/
uint8_t Font08px_47[4] = {3,
	bits2bytes(1,1,0,0,0,0,0,0),
	bits2bytes(0,0,1,1,1,0,0,0),
	bits2bytes(0,0,0,0,0,1,1,0)};

/**  0x30 - 48  - '0'  **/
uint8_t Font08px_N0[6] = {5,
	bits2bytes(0,1,1,1,1,1,0,0),
	bits2bytes(1,0,1,0,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,0,1,0,1,0),
	bits2bytes(0,1,1,1,1,1,0,0)};

/**  0x31 - 49  - '1'  **/
uint8_t Font08px_N1[6] = {5,
	bits2bytes(0,0,0,0,0,0,0,0),
	bits2bytes(1,0,0,0,0,1,0,0),
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(0,0,0,0,0,0,0,0)};

/**  0x32 - 50  - '2'  **/
uint8_t Font08px_N2[6] = {5,
	bits2bytes(1,0,0,0,0,1,0,0),
	bits2bytes(1,1,0,0,0,0,1,0),
	bits2bytes(1,0,1,0,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,0,1,1,0,0)};

/**  0x33 - 51  - '3'  **/
uint8_t Font08px_N3[6] = {5,
	bits2bytes(0,1,0,0,0,1,0,0),
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(0,1,1,0,1,1,0,0)};

/**  0x34 - 52  - '4'  **/
uint8_t Font08px_N4[6] = {5,
	bits2bytes(0,0,1,1,0,0,0,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(0,0,1,0,0,1,0,0),
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,1,0,0,0,0,0)};

/**  0x35 - 53  - '5'  **/
uint8_t Font08px_N5[6] = {5,
	bits2bytes(0,1,0,1,1,1,1,0),
	bits2bytes(1,0,0,0,1,0,1,0),
	bits2bytes(1,0,0,0,1,0,1,0),
	bits2bytes(1,0,0,0,1,0,1,0),
	bits2bytes(0,1,1,1,0,0,1,0)};

/**  0x36 - 54  - '6'  **/
uint8_t Font08px_N6[6] = {5,
	bits2bytes(0,1,1,1,1,1,0,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(0,1,1,0,0,1,0,0)};

/**  0x37 - 55  - '7'  **/
uint8_t Font08px_N7[6] = {5,
	bits2bytes(0,0,0,0,0,0,1,0),
	bits2bytes(0,0,0,0,0,0,1,0),
	bits2bytes(1,1,1,1,0,0,1,0),
	bits2bytes(0,0,0,0,1,0,1,0),
	bits2bytes(0,0,0,0,0,1,1,0)};

/**  0x38 - 56  - '8'  **/
uint8_t Font08px_N8[6] = {5,
	bits2bytes(0,1,1,0,1,1,0,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(0,1,1,0,1,1,0,0)};

/**  0x39 - 57  - '9'  **/
uint8_t Font08px_N9[6] = {5,
	bits2bytes(0,1,0,0,1,1,0,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(0,1,1,1,1,1,0,0)};

/**  0x3A - 58  - ':'  **/
uint8_t Font08px_58[2] = {1,
	bits2bytes(0,1,0,0,0,1,0,0)};

/**  0x3B - 59  - ';'  **/
uint8_t Font08px_59[2] = {1,
	bits2bytes(1,1,0,0,0,1,0,0)};

/**  0x3C - 60  - '<'  **/
uint8_t Font08px_60[5] = {4,
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(0,1,0,0,0,1,0,0),
	bits2bytes(1,0,0,0,0,0,1,0)};

/**  0x3D - 61  - '='  **/
uint8_t Font08px_61[5] = {4,
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(0,0,1,0,1,0,0,0)};

/**  0x3E - 62  - '>'  **/
uint8_t Font08px_62[5] = {4,
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(0,1,0,0,0,1,0,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(0,0,0,1,0,0,0,0)};

/**  0x3F - 63  - '?'  **/
uint8_t Font08px_63[6] = {5,
	bits2bytes(0,0,0,0,0,1,0,0),
	bits2bytes(0,0,0,0,0,0,1,0),
	bits2bytes(1,0,1,0,0,0,1,0),
	bits2bytes(0,0,0,1,0,0,1,0),
	bits2bytes(0,0,0,0,1,1,0,0)};

/**  0x40 - 64  - '@'  **/
uint8_t Font08px_64[9] = {8,
	bits2bytes(0,0,1,1,1,0,0,0),
	bits2bytes(0,1,0,0,0,1,0,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,1,0,1,0,1,0),
	bits2bytes(1,0,1,0,1,0,1,0),
	bits2bytes(1,0,1,1,1,0,1,0),
	bits2bytes(0,0,1,0,0,1,0,0),
	bits2bytes(0,0,0,1,1,0,0,0)};

/**  0x41 - 65  - 'A'  **/
uint8_t Font08px_UA[6] = {5,
	bits2bytes(1,1,1,1,1,0,0,0),
	bits2bytes(0,0,0,1,0,1,0,0),
	bits2bytes(0,0,0,1,0,0,1,0),
	bits2bytes(0,0,0,1,0,1,0,0),
	bits2bytes(1,1,1,1,1,0,0,0)};

/**  0x42 - 66  - 'B'  **/
uint8_t Font08px_UB[5] = {4,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(0,1,1,0,1,1,0,0)};

/**  0x43 - 67  - 'C'  **/
uint8_t Font08px_UC[5] = {4,
	bits2bytes(0,1,1,1,1,1,0,0),
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(0,1,0,0,0,1,0,0)};

/**  0x44 - 68  - 'D'  **/
uint8_t Font08px_UD[5] = {4,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(0,1,1,1,1,1,0,0)};

/**  0x45 - 69  - 'E'  **/
uint8_t Font08px_UE[5] = {4,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,0,0,0,1,0)};

/**  0x46 - 70  - 'F'  **/
uint8_t Font08px_UF[5] = {4,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,0,1,0,0,1,0),
	bits2bytes(0,0,0,1,0,0,1,0),
	bits2bytes(0,0,0,0,0,0,1,0)};

/**  0x47 - 71  - 'G'  **/
uint8_t Font08px_UG[6] = {5,
	bits2bytes(0,1,1,1,1,1,0,0),
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,1,1,1,0,1,0,0)};

/**  0x48 - 72  - 'H'  **/
uint8_t Font08px_UH[5] = {4,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(1,1,1,1,1,1,1,0)};

/**  0x49 - 73  - 'I'  **/
uint8_t Font08px_UI[4] = {3,
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(1,0,0,0,0,0,1,0)};

/**  0x4A - 74  - 'J'  **/
uint8_t Font08px_UJ[5] = {4,
	bits2bytes(0,1,0,0,0,0,0,0),
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(0,1,1,1,1,1,1,0)};

/**  0x4B - 75  - 'K'  **/
uint8_t Font08px_UK[6] = {5,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(0,1,0,0,0,1,0,0),
	bits2bytes(1,0,0,0,0,0,1,0)};

/**  0x4C - 76  - 'L'  **/
uint8_t Font08px_UL[5] = {4,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(1,0,0,0,0,0,0,0)};

/**  0x4D - 77  - 'M'  **/
uint8_t Font08px_UM[6] = {5,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,0,0,0,1,0,0),
	bits2bytes(0,0,0,0,1,0,0,0),
	bits2bytes(0,0,0,0,0,1,0,0),
	bits2bytes(1,1,1,1,1,1,1,0)};

/**  0x4E - 78  - 'N'  **/
uint8_t Font08px_UN[6] = {5,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,0,0,0,1,0,0),
	bits2bytes(0,0,0,1,1,0,0,0),
	bits2bytes(0,1,1,0,0,0,0,0),
	bits2bytes(1,1,1,1,1,1,1,0)};

/**  0x4F - 79  - 'O'  **/
uint8_t Font08px_UO[5] = {4,
	bits2bytes(0,1,1,1,1,1,0,0),
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(0,1,1,1,1,1,0,0)};

/**  0x50 - 80  - 'P'  **/
uint8_t Font08px_UP[5] = {4,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,0,1,0,0,1,0),
	bits2bytes(0,0,0,1,0,0,1,0),
	bits2bytes(0,0,0,0,1,1,0,0)};

/**  0x51 - 81  - 'Q'  **/
uint8_t Font08px_UQ[6] = {5,
	bits2bytes(0,1,1,1,1,1,0,0),
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(1,0,1,0,0,0,1,0),
	bits2bytes(0,1,0,0,0,0,1,0),
	bits2bytes(1,0,1,1,1,1,0,0)};

/**  0x52 - 82  - 'R'  **/
uint8_t Font08px_UR[5] = {4,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,0,1,0,0,1,0),
	bits2bytes(0,0,1,1,0,0,1,0),
	bits2bytes(1,1,0,0,1,1,0,0)};

/**  0x53 - 83  - 'S'  **/
uint8_t Font08px_US[5] = {4,
	bits2bytes(0,1,0,0,1,1,0,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(0,1,1,0,0,1,0,0)};

/**  0x54 - 84  - 'T'  **/
uint8_t Font08px_UT[6] = {5,
	bits2bytes(0,0,0,0,0,0,1,0),
	bits2bytes(0,0,0,0,0,0,1,0),
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,0,0,0,0,1,0),
	bits2bytes(0,0,0,0,0,0,1,0)};

/**  0x55 - 85  - 'U'  **/
uint8_t Font08px_UU[5] = {4,
	bits2bytes(0,1,1,1,1,1,1,0),
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(0,1,1,1,1,1,1,0)};

/**  0x56 - 86  - 'V'  **/
uint8_t Font08px_UV[6] = {5,
	bits2bytes(0,0,0,0,1,1,1,0),
	bits2bytes(0,0,1,1,0,0,0,0),
	bits2bytes(1,1,0,0,0,0,0,0),
	bits2bytes(0,0,1,1,0,0,0,0),
	bits2bytes(0,0,0,0,1,1,1,0)};

/**  0x57 - 87  - 'W'  **/
uint8_t Font08px_UW[6] = {5,
	bits2bytes(0,0,1,1,1,1,1,0),
	bits2bytes(1,1,0,0,0,0,0,0),
	bits2bytes(0,0,1,1,1,0,0,0),
	bits2bytes(1,1,0,0,0,0,0,0),
	bits2bytes(0,0,1,1,1,1,1,0)};

/**  0x58 - 88  - 'X'  **/
uint8_t Font08px_UX[6] = {5,
	bits2bytes(1,1,0,0,0,1,1,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(1,1,0,0,0,1,1,0)};

/**  0x59 - 89  - 'Y'  **/
uint8_t Font08px_UY[6] = {5,
	bits2bytes(0,0,0,0,0,1,1,0),
	bits2bytes(0,0,0,0,1,0,0,0),
	bits2bytes(1,1,1,1,0,0,0,0),
	bits2bytes(0,0,0,0,1,0,0,0),
	bits2bytes(0,0,0,0,0,1,1,0)};

/**  0x5A - 90  - 'Z'  **/
uint8_t Font08px_UZ[6] = {5,
	bits2bytes(1,1,0,0,0,0,1,0),
	bits2bytes(1,0,1,0,0,0,1,0),
	bits2bytes(1,0,0,1,0,0,1,0),
	bits2bytes(1,0,0,0,1,0,1,0),
	bits2bytes(1,0,0,0,0,1,1,0)};

/**  0x5B - 91  - '['  **/
uint8_t Font08px_91[4] = {3,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(1,0,0,0,0,0,1,0)};

/**  0x5C - 92  - '\'  **/
uint8_t Font08px_92[4] = {3,
	bits2bytes(0,0,0,0,0,1,1,0),
	bits2bytes(0,0,1,1,1,0,0,0),
	bits2bytes(1,1,0,0,0,0,0,0)};

/**  0x5D - 93  - ']'  **/
uint8_t Font08px_93[4] = {3,
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(1,1,1,1,1,1,1,0)};

/**  0x5E - 94  - '^'  **/
uint8_t Font08px_94[4] = {3,
	bits2bytes(0,0,0,0,0,1,0,0),
	bits2bytes(0,0,0,0,0,0,1,0),
	bits2bytes(0,0,0,0,0,1,0,0)};

/**  0x5F - 95  - '_'  **/
uint8_t Font08px_95[4] = {3,
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(1,0,0,0,0,0,0,0)};

/**  0x60 - 96  - '`'  **/
uint8_t Font08px_96[3] = {2,
	bits2bytes(0,0,0,0,0,0,1,0),
	bits2bytes(0,0,0,0,0,1,0,0)};

/**  0x61 - 97  - 'a'  **/
uint8_t Font08px_la[5] = {4,
	bits2bytes(0,1,1,1,0,0,0,0),
	bits2bytes(1,0,0,0,1,0,0,0),
	bits2bytes(1,0,0,0,1,0,0,0),
	bits2bytes(1,1,1,1,1,0,0,0)};

/**  0x62 - 98  - 'b'  **/
uint8_t Font08px_lb[5] = {4,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(1,0,0,0,1,0,0,0),
	bits2bytes(1,0,0,0,1,0,0,0),
	bits2bytes(0,1,1,1,0,0,0,0)};

/**  0x63 - 99  - 'c'  **/
uint8_t Font08px_lc[5] = {4,
	bits2bytes(0,1,1,1,0,0,0,0),
	bits2bytes(1,0,0,0,1,0,0,0),
	bits2bytes(1,0,0,0,1,0,0,0),
	bits2bytes(1,0,0,0,1,0,0,0)};

/**  0x64 - 100 - 'd'  **/
uint8_t Font08px_ld[5] = {4,
	bits2bytes(0,1,1,1,0,0,0,0),
	bits2bytes(1,0,0,0,1,0,0,0),
	bits2bytes(1,0,0,0,1,0,0,0),
	bits2bytes(1,1,1,1,1,1,1,0)};

/**  0x65 - 101 - 'e'  **/
uint8_t Font08px_le[5] = {4,
	bits2bytes(0,1,1,1,0,0,0,0),
	bits2bytes(1,0,1,0,1,0,0,0),
	bits2bytes(1,0,1,0,1,0,0,0),
	bits2bytes(0,0,1,1,0,0,0,0)};

/**  0x66 - 102 - 'f'  **/
uint8_t Font08px_lf[4] = {3,
	bits2bytes(1,1,1,1,1,1,0,0),
	bits2bytes(0,0,0,1,0,0,1,0),
	bits2bytes(0,0,0,0,0,0,1,0)};

/**  0x67 - 103 - 'g'  **/
uint8_t Font08px_lg[5] = {4,
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(1,0,1,0,1,0,0,0),
	bits2bytes(1,0,1,0,1,0,0,0),
	bits2bytes(0,1,1,1,1,0,0,0)};

/**  0x68 - 104 - 'h'  **/
uint8_t Font08px_lh[5] = {4,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,0,0,1,0,0,0),
	bits2bytes(1,1,1,1,0,0,0,0)};

/**  0x69 - 105 - 'i'  **/
uint8_t Font08px_li[2] = {1,
	bits2bytes(1,1,1,1,1,0,1,0)};

/**  0x6A - 106 - 'j'  **/
uint8_t Font08px_lj[3] = {2,
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(0,1,1,1,1,0,1,0)};

/**  0x6B - 107 - 'k'  **/
uint8_t Font08px_lk[5] = {4,
	bits2bytes(1,1,1,1,1,1,1,0),
	bits2bytes(0,0,1,0,0,0,0,0),
	bits2bytes(0,1,0,1,0,0,0,0),
	bits2bytes(1,0,0,0,1,0,0,0)};

/**  0x6C - 108 - 'l'  **/
uint8_t Font08px_ll[2] = {1,
	bits2bytes(1,1,1,1,1,1,1,0)};

/**  0x6D - 109 - 'm'  **/
uint8_t Font08px_lm[6] = {5,
	bits2bytes(1,1,1,1,1,0,0,0),
	bits2bytes(0,0,0,0,1,0,0,0),
	bits2bytes(1,1,1,1,0,0,0,0),
	bits2bytes(0,0,0,0,1,0,0,0),
	bits2bytes(1,1,1,1,0,0,0,0)};

/**  0x6E - 110 - 'n'  **/
uint8_t Font08px_ln[5] = {4,
	bits2bytes(1,1,1,1,1,0,0,0),
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,0,0,1,0,0,0),
	bits2bytes(1,1,1,1,0,0,0,0)};

/**  0x6F - 111 - 'o'  **/
uint8_t Font08px_lo[5] = {4,
	bits2bytes(0,1,1,1,0,0,0,0),
	bits2bytes(1,0,0,0,1,0,0,0),
	bits2bytes(1,0,0,0,1,0,0,0),
	bits2bytes(0,1,1,1,0,0,0,0)};

/**  0x70 - 112 - 'p'  **/
uint8_t Font08px_lp[5] = {4,
	bits2bytes(1,1,1,1,1,0,0,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(0,0,0,1,0,0,0,0)};

/**  0x71 - 113 - 'q'  **/
uint8_t Font08px_lq[5] = {4,
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(0,0,1,0,1,0,0,0),
	bits2bytes(1,1,1,1,1,0,0,0)};

/**  0x72 - 114 - 'r'  **/
uint8_t Font08px_lr[4] = {3,
	bits2bytes(1,1,1,1,1,0,0,0),
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,0,0,1,0,0,0)};

/**  0x73 - 115 - 's'  **/
uint8_t Font08px_ls[5] = {4,
	bits2bytes(1,0,0,1,0,0,0,0),
	bits2bytes(1,0,1,0,1,0,0,0),
	bits2bytes(1,0,1,0,1,0,0,0),
	bits2bytes(0,1,0,0,1,0,0,0)};

/**  0x74 - 116 - 't'  **/
uint8_t Font08px_lt[4] = {3,
	bits2bytes(0,0,0,0,1,0,0,0),
	bits2bytes(0,1,1,1,1,1,0,0),
	bits2bytes(1,0,0,0,1,0,0,0)};

/**  0x75 - 117 - 'u'  **/
uint8_t Font08px_lu[5] = {4,
	bits2bytes(0,1,1,1,1,0,0,0),
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(1,1,1,1,1,0,0,0)};

/**  0x76 - 118 - 'v'  **/
uint8_t Font08px_lv[6] = {5,
	bits2bytes(0,0,0,1,1,0,0,0),
	bits2bytes(0,1,1,0,0,0,0,0),
	bits2bytes(1,0,0,0,0,0,0,0),
	bits2bytes(0,1,1,0,0,0,0,0),
	bits2bytes(0,0,0,1,1,0,0,0)};

/**  0x77 - 119 - 'w'  **/
uint8_t Font08px_lw[6] = {5,
	bits2bytes(0,0,1,1,1,0,0,0),
	bits2bytes(1,1,0,0,0,0,0,0),
	bits2bytes(0,0,1,1,0,0,0,0),
	bits2bytes(1,1,0,0,0,0,0,0),
	bits2bytes(0,0,1,1,1,0,0,0)};

/**  0x78 - 120 - 'x'  **/
uint8_t Font08px_lx[6] = {5,
	bits2bytes(1,0,0,0,1,0,0,0),
	bits2bytes(0,1,0,1,0,0,0,0),
	bits2bytes(0,0,1,0,0,0,0,0),
	bits2bytes(0,1,0,1,0,0,0,0),
	bits2bytes(1,0,0,0,1,0,0,0)};

/**  0x79 - 121 - 'y'  **/
uint8_t Font08px_ly[5] = {4,
	bits2bytes(0,0,0,1,1,0,0,0),
	bits2bytes(1,0,1,0,0,0,0,0),
	bits2bytes(1,0,1,0,0,0,0,0),
	bits2bytes(0,1,1,1,1,0,0,0)};

/**  0x7A - 122 - 'z'  **/
uint8_t Font08px_lz[4] = {3,
	bits2bytes(1,1,0,0,1,0,0,0),
	bits2bytes(1,0,1,0,1,0,0,0),
	bits2bytes(1,0,0,1,1,0,0,0)};

/**  0x7B - 123 - '{'  **/
uint8_t Font08px_123[4] = {3,
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,1,1,0,1,1,0,0),
	bits2bytes(1,0,0,0,0,0,1,0)};

/**  0x7C - 124 - '|'  **/
uint8_t Font08px_124[2] = {1,
	bits2bytes(1,1,1,1,1,1,1,0)};

/**  0x7D - 125 - '}'  **/
uint8_t Font08px_125[4] = {3,
	bits2bytes(1,0,0,0,0,0,1,0),
	bits2bytes(0,1,1,0,1,1,0,0),
	bits2bytes(0,0,0,1,0,0,0,0)};

/**  0x7E - 126 - '~'  **/
uint8_t Font08px_126[6] = {5,
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,0,0,1,0,0,0),
	bits2bytes(0,0,0,1,0,0,0,0),
	bits2bytes(0,0,1,0,0,0,0,0),
	bits2bytes(0,0,0,1,0,0,0,0)};
