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

#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

/*======= binar input =======*/
#define bits2bytes(b7,b6,b5,b4,b3,b2,b1,b0) ((uint8_t)((b7<<7)|(b6<<6)|(b5<<5)|(b4<<4)|(b3<<3)|(b2<<2)|(b1<<1)|(b0<<0)))

/*======= Character pointers table =======*/
extern uint8_t *font_table[95];

/*======= Characters data =======*/
extern uint8_t Font08px_32[3];
extern uint8_t Font08px_33[2];
extern uint8_t Font08px_34[4];
extern uint8_t Font08px_35[6];
extern uint8_t Font08px_36[6];
extern uint8_t Font08px_37[6];
extern uint8_t Font08px_38[6];
extern uint8_t Font08px_39[2];
extern uint8_t Font08px_40[4];
extern uint8_t Font08px_41[4];
extern uint8_t Font08px_42[4];
extern uint8_t Font08px_43[4];
extern uint8_t Font08px_44[2];
extern uint8_t Font08px_45[4];
extern uint8_t Font08px_46[2];
extern uint8_t Font08px_47[4];
extern uint8_t Font08px_N0[6];
extern uint8_t Font08px_N1[6];
extern uint8_t Font08px_N2[6];
extern uint8_t Font08px_N3[6];
extern uint8_t Font08px_N4[6];
extern uint8_t Font08px_N5[6];
extern uint8_t Font08px_N6[6];
extern uint8_t Font08px_N7[6];
extern uint8_t Font08px_N8[6];
extern uint8_t Font08px_N9[6];
extern uint8_t Font08px_58[2];
extern uint8_t Font08px_59[2];
extern uint8_t Font08px_60[5];
extern uint8_t Font08px_61[5];
extern uint8_t Font08px_62[5];
extern uint8_t Font08px_63[6];
extern uint8_t Font08px_64[9];
extern uint8_t Font08px_UA[6];
extern uint8_t Font08px_UB[5];
extern uint8_t Font08px_UC[5];
extern uint8_t Font08px_UD[5];
extern uint8_t Font08px_UE[5];
extern uint8_t Font08px_UF[5];
extern uint8_t Font08px_UG[6];
extern uint8_t Font08px_UH[5];
extern uint8_t Font08px_UI[4];
extern uint8_t Font08px_UJ[5];
extern uint8_t Font08px_UK[6];
extern uint8_t Font08px_UL[5];
extern uint8_t Font08px_UM[6];
extern uint8_t Font08px_UN[6];
extern uint8_t Font08px_UO[5];
extern uint8_t Font08px_UP[5];
extern uint8_t Font08px_UQ[6];
extern uint8_t Font08px_UR[5];
extern uint8_t Font08px_US[5];
extern uint8_t Font08px_UT[6];
extern uint8_t Font08px_UU[5];
extern uint8_t Font08px_UV[6];
extern uint8_t Font08px_UW[6];
extern uint8_t Font08px_UX[6];
extern uint8_t Font08px_UY[6];
extern uint8_t Font08px_UZ[6];
extern uint8_t Font08px_91[4];
extern uint8_t Font08px_92[4];
extern uint8_t Font08px_93[4];
extern uint8_t Font08px_94[4];
extern uint8_t Font08px_95[4];
extern uint8_t Font08px_96[3];
extern uint8_t Font08px_la[5];
extern uint8_t Font08px_lb[5];
extern uint8_t Font08px_lc[5];
extern uint8_t Font08px_ld[5];
extern uint8_t Font08px_le[5];
extern uint8_t Font08px_lf[4];
extern uint8_t Font08px_lg[5];
extern uint8_t Font08px_lh[5];
extern uint8_t Font08px_li[2];
extern uint8_t Font08px_lj[3];
extern uint8_t Font08px_lk[5];
extern uint8_t Font08px_ll[2];
extern uint8_t Font08px_lm[6];
extern uint8_t Font08px_ln[5];
extern uint8_t Font08px_lo[5];
extern uint8_t Font08px_lp[5];
extern uint8_t Font08px_lq[5];
extern uint8_t Font08px_lr[4];
extern uint8_t Font08px_ls[5];
extern uint8_t Font08px_lt[4];
extern uint8_t Font08px_lu[5];
extern uint8_t Font08px_lv[6];
extern uint8_t Font08px_lw[6];
extern uint8_t Font08px_lx[6];
extern uint8_t Font08px_ly[5];
extern uint8_t Font08px_lz[4];
extern uint8_t Font08px_123[4];
extern uint8_t Font08px_124[2];
extern uint8_t Font08px_125[4];
extern uint8_t Font08px_126[6];

#endif /* FONT_H_INCLUDED */
