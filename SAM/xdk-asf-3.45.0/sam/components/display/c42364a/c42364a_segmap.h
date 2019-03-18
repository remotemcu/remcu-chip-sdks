/**
 * \file
 *
 * \brief Default configuration of C42364A LCD Segment Map.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef C42364A_TEMPLATE_H_INCLUDED
#define C42364A_TEMPLATE_H_INCLUDED

#include "board.h"

/**
 * \name LCD component C42364A segment map definitions in SAM4L-EK
 * @{
 */
#if BOARD == SAM4L_EK
/* name Icon with selected segments blinking feature */
#define C42364A_ICON_USB            1, 0
#define C42364A_ICON_COLON          0, 0
#define C42364A_ICON_WLESS          2, 0
#define C42364A_ICON_AUDIO          3, 0
#define C42364A_ICON_BAT            0, 1
#define C42364A_ICON_ERROR          1, 1
#define C42364A_ICON_CHINESE        2, 1
#define C42364A_ICON_ARM            3, 1
/* name Icon without selected segments blinking feature */
#define C42364A_ICON_MINUS          0, 37
#define C42364A_ICON_MINUS_SEG1     3, 30
#define C42364A_ICON_MINUS_SEG2     0, 33
#define C42364A_ICON_DOT_1          0, 29
#define C42364A_ICON_DOT_2          3, 10
#define C42364A_ICON_DOT_3          3, 8
#define C42364A_ICON_DOT_4          3, 6
#define C42364A_ICON_BAT_LEVEL_1    0, 21
#define C42364A_ICON_BAT_LEVEL_2    0, 17
#define C42364A_ICON_BAT_LEVEL_3    0, 25
#define C42364A_ICON_AUDIO_PAUSE    3, 38
#define C42364A_ICON_AUDIO_PLAY     3, 34
#define C42364A_ICON_AM             3, 4
#define C42364A_ICON_PM             3, 26
#define C42364A_ICON_DEGREE_C       3, 22
#define C42364A_ICON_DEGREE_F       3, 18
#define C42364A_ICON_VOLT           3, 14
#define C42364A_ICON_MILLI_VOLT     0, 13
/* @} */

/**
 * \name LCD component C42364A segment map definitions in SAM4C-EK
 * @{
 */
#elif BOARD == SAM4C_EK
/* SEG and COM Num of ICON */
#define C42364A_ICON_USB            1, 48
#define C42364A_ICON_COLON          0, 48
#define C42364A_ICON_WLESS          2, 48
#define C42364A_ICON_AUDIO          3, 48
#define C42364A_ICON_BAT            0, 49
#define C42364A_ICON_ERROR          1, 49
#define C42364A_ICON_CHINESE        2, 49
#define C42364A_ICON_ARM            3, 49
#define C42364A_ICON_DOT_1          0, 30
#define C42364A_ICON_DOT_2          3, 20
#define C42364A_ICON_DOT_3          3, 22
#define C42364A_ICON_DOT_4          3, 25
#define C42364A_ICON_BAT_LEVEL_1    0, 38
#define C42364A_ICON_BAT_LEVEL_2    0, 42
#define C42364A_ICON_BAT_LEVEL_3    0, 34
#define C42364A_ICON_AM             3, 27
#define C42364A_ICON_PM             3, 33
#define C42364A_ICON_DEGREE_C       3, 37
#define C42364A_ICON_DEGREE_F       3, 41
#define C42364A_ICON_VOLT           3, 45
#define C42364A_ICON_MILLI_VOLT     0, 46
 /* Seg Num of Pixel */
#define C42364A_G1_SEG_NUM            48
#define C42364A_G4_SEG_NUM            49
#define C42364A_D3A_SEG_NUM           27
#define C42364A_D3F_SEG_NUM           26
#define C42364A_D2A_SEG_NUM           25
#define C42364A_D2F_SEG_NUM           24
#define C42364A_D1A_SEG_NUM           22
#define C42364A_D1F_SEG_NUM           21
#define C42364A_D0A_SEG_NUM           20
#define C42364A_D0F_SEG_NUM           17
#define C42364A_A6H_SEG_NUM           47
#define C42364A_B14_SEG_NUM           46
#define C42364A_A6A_SEG_NUM           45
#define C42364A_A6G_SEG_NUM           44
#define C42364A_A5H_SEG_NUM           43
#define C42364A_B5_SEG_NUM            42
#define C42364A_A5A_SEG_NUM           41
#define C42364A_A5G_SEG_NUM           40
#define C42364A_A4H_SEG_NUM           39
#define C42364A_B6_SEG_NUM            38
#define C42364A_A4A_SEG_NUM           37
#define C42364A_A4G_SEG_NUM           36
#define C42364A_A3H_SEG_NUM           35
#define C42364A_B4_SEG_NUM            34
#define C42364A_A3A_SEG_NUM           33
#define C42364A_A3G_SEG_NUM           32
#define C42364A_A2H_SEG_NUM           31
#define C42364A_B3_SEG_NUM            30
#define C42364A_A2A_SEG_NUM           29
#define C42364A_A2G_SEG_NUM           28

/* The LCD segment map number */
#define C42364A_SEGMAP_NUM_0     0xff720000
#define C42364A_SEGMAP_NUM_1     0x3ffff
/* @} */
/**
 * \name LCD component C42364A segment map definitions in SAM4CP16BMB
 * @{
 */
#elif BOARD == SAM4CP16BMB
/* SEG and COM Num of ICON */
#define C42364A_ICON_USB            1, 3
#define C42364A_ICON_COLON          0, 3
#define C42364A_ICON_WLESS          2, 3
#define C42364A_ICON_AUDIO          3, 3
#define C42364A_ICON_BAT            0, 4
#define C42364A_ICON_ERROR          1, 4
#define C42364A_ICON_CHINESE        2, 4
#define C42364A_ICON_ARM            3, 4
#define C42364A_ICON_DOT_1          0, 46
#define C42364A_ICON_DOT_2          3, 17
#define C42364A_ICON_DOT_3          3, 15
#define C42364A_ICON_DOT_4          3, 9
#define C42364A_ICON_BAT_LEVEL_1    0, 37
#define C42364A_ICON_BAT_LEVEL_2    0, 27
#define C42364A_ICON_BAT_LEVEL_3    0, 42
#define C42364A_ICON_AM             3, 7
#define C42364A_ICON_PM             3, 43
#define C42364A_ICON_DEGREE_C       3, 38
#define C42364A_ICON_DEGREE_F       3, 28
#define C42364A_ICON_VOLT           3, 24
#define C42364A_ICON_MILLI_VOLT     0, 22
#define C42364A_ICON_ATMEL          3, 4
#define C42364A_ICON_PAUSE          3, 35
#define C42364A_ICON_PLAY           3, 12
 /* Seg Num of Pixel */
#define C42364A_G1_SEG_NUM            3
#define C42364A_G4_SEG_NUM            4
#define C42364A_D3A_SEG_NUM           7
#define C42364A_D3F_SEG_NUM           8
#define C42364A_D2A_SEG_NUM           9
#define C42364A_D2F_SEG_NUM           10
#define C42364A_D1A_SEG_NUM           15
#define C42364A_D1F_SEG_NUM           16
#define C42364A_D0A_SEG_NUM           17
#define C42364A_D0F_SEG_NUM           20
#define C42364A_A6H_SEG_NUM           21
#define C42364A_B14_SEG_NUM           22
#define C42364A_A6A_SEG_NUM           24
#define C42364A_A6G_SEG_NUM           25
#define C42364A_A5H_SEG_NUM           26
#define C42364A_B5_SEG_NUM            27
#define C42364A_A5A_SEG_NUM           28
#define C42364A_A5G_SEG_NUM           31
#define C42364A_A4H_SEG_NUM           36
#define C42364A_B6_SEG_NUM            37
#define C42364A_A4A_SEG_NUM           38
#define C42364A_A4G_SEG_NUM           39
#define C42364A_A3H_SEG_NUM           40
#define C42364A_B4_SEG_NUM            42
#define C42364A_A3A_SEG_NUM           43
#define C42364A_A3G_SEG_NUM           44
#define C42364A_A2H_SEG_NUM           45
#define C42364A_B3_SEG_NUM            46
#define C42364A_A2A_SEG_NUM           47
#define C42364A_A2G_SEG_NUM           5
#define C42364A_A1H_SEG_NUM           6
#define C42364A_B2_SEG_NUM            11
#define C42364A_A1A_SEG_NUM           12
#define C42364A_A1G_SEG_NUM           13
#define C42364A_A0H_SEG_NUM           14
#define C42364A_B0_SEG_NUM            34
#define C42364A_A0A_SEG_NUM           35

/* The LCD segment map number */
#define C42364A_SEGMAP_NUM_0     0x9F73FFF8
#define C42364A_SEGMAP_NUM_1     0x0FDFC
/* @} */

/**
 * \name LCD component C42364A segment map default definitions
 * @{
 */
#else
/* name Icon with selected segments blinking feature */
#define C42364A_ICON_USB            1, 0
#define C42364A_ICON_COLON          0, 0
#define C42364A_ICON_WLESS          2, 0
#define C42364A_ICON_AUDIO          3, 0
#define C42364A_ICON_BAT            0, 1
#define C42364A_ICON_ERROR          1, 1
#define C42364A_ICON_CHINESE        2, 1
#define C42364A_ICON_ARM            3, 1
/* name Icon without selected segments blinking feature */
#define C42364A_ICON_MINUS          0, 37
#define C42364A_ICON_MINUS_SEG1     3, 30
#define C42364A_ICON_MINUS_SEG2     0, 33
#define C42364A_ICON_DOT_1          0, 29
#define C42364A_ICON_DOT_2          3, 10
#define C42364A_ICON_DOT_3          3, 8
#define C42364A_ICON_DOT_4          3, 6
#define C42364A_ICON_BAT_LEVEL_1    0, 21
#define C42364A_ICON_BAT_LEVEL_2    0, 17
#define C42364A_ICON_BAT_LEVEL_3    0, 25
#define C42364A_ICON_AUDIO_PAUSE    3, 38
#define C42364A_ICON_AUDIO_PLAY     3, 34
#define C42364A_ICON_AM             3, 4
#define C42364A_ICON_PM             3, 26
#define C42364A_ICON_DEGREE_C       3, 22
#define C42364A_ICON_DEGREE_F       3, 18
#define C42364A_ICON_VOLT           3, 14
#define C42364A_ICON_MILLI_VOLT     0, 13
 /* Seg Num of Pixel */
#define C42364A_G1_SEG_NUM            48
#define C42364A_G4_SEG_NUM            49
#define C42364A_D3A_SEG_NUM           27
#define C42364A_D3F_SEG_NUM           26
#define C42364A_D2A_SEG_NUM           25
#define C42364A_D2F_SEG_NUM           24
#define C42364A_D1A_SEG_NUM           22
#define C42364A_D1F_SEG_NUM           21
#define C42364A_D0A_SEG_NUM           20
#define C42364A_D0F_SEG_NUM           17
#define C42364A_A6H_SEG_NUM           47
#define C42364A_B14_SEG_NUM           46
#define C42364A_A6A_SEG_NUM           45
#define C42364A_A6G_SEG_NUM           44
#define C42364A_A5H_SEG_NUM           43
#define C42364A_B5_SEG_NUM            42
#define C42364A_A5A_SEG_NUM           41
#define C42364A_A5G_SEG_NUM           40
#define C42364A_A4H_SEG_NUM           39
#define C42364A_B6_SEG_NUM            38
#define C42364A_A4A_SEG_NUM           37
#define C42364A_A4G_SEG_NUM           36
#define C42364A_A3H_SEG_NUM           35
#define C42364A_B4_SEG_NUM            34
#define C42364A_A3A_SEG_NUM           33
#define C42364A_A3G_SEG_NUM           32
#define C42364A_A2H_SEG_NUM           31
#define C42364A_B3_SEG_NUM            30
#define C42364A_A2A_SEG_NUM           29
#define C42364A_A2G_SEG_NUM           28
#define C42364A_A1H_SEG_NUM           27
#define C42364A_B2_SEG_NUM            26
#define C42364A_A1A_SEG_NUM           25
#define C42364A_A1G_SEG_NUM           24
#define C42364A_A0H_SEG_NUM           22
#define C42364A_B0_SEG_NUM            21
#define C42364A_A0A_SEG_NUM           20

/* The LCD segment map number */
#define C42364A_SEGMAP_NUM_0     0xff720000
#define C42364A_SEGMAP_NUM_1     0x3ffff
#endif
/* @} */

#endif  /* C42364A_TEMPLATE_H_INCLUDED */
