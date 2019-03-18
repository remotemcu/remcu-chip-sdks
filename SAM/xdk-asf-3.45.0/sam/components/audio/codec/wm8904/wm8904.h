/**
 * \file
 *
 * \brief WM8904 driver for SAM
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef WM8904_H_INCLUDED
#define WM8904_H_INCLUDED

/**
 * \defgroup sam_components_audio_codec_wm8904_group WM8904 Audio Codec
 *
 * See \ref sam_wm8904_quickstart
 *
 * \par Purpose
 *
 * The module provides useful API of WM8904 audio codec through a TWI interface.
 *
 * \section dependencies Dependencies
 * This driver depends on the following module:
 * - \ref twi_group for common TWI service.
 * @{
 */

#include "twihs_master.h"
#include "conf_wm8904.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#define WM8904_CLK_MCLK 1
#define WM8904_CLK_FLL  2

#define WM8904_FLL_MCLK          1
#define WM8904_FLL_BCLK          2
#define WM8904_FLL_LRCLK         3
#define WM8904_FLL_FREE_RUNNING  4

/*
 * Register index.
 */
#define WM8904_SW_RESET_AND_ID                  0x00
#define WM8904_REVISION                         0x01
#define WM8904_BIAS_CONTROL_0                   0x04
#define WM8904_VMID_CONTROL_0                   0x05
#define WM8904_MIC_BIAS_CONTROL_0               0x06
#define WM8904_MIC_BIAS_CONTROL_1               0x07
#define WM8904_ANALOGUE_DAC_0                   0x08
#define WM8904_MIC_FILTER_CONTROL               0x09
#define WM8904_ANALOGUE_ADC_0                   0x0A
#define WM8904_POWER_MANAGEMENT_0               0x0C
#define WM8904_POWER_MANAGEMENT_2               0x0E
#define WM8904_POWER_MANAGEMENT_3               0x0F
#define WM8904_POWER_MANAGEMENT_6               0x12
#define WM8904_CLOCK_RATES_0                    0x14
#define WM8904_CLOCK_RATES_1                    0x15
#define WM8904_CLOCK_RATES_2                    0x16
#define WM8904_AUDIO_INTERFACE_0                0x18
#define WM8904_AUDIO_INTERFACE_1                0x19
#define WM8904_AUDIO_INTERFACE_2                0x1A
#define WM8904_AUDIO_INTERFACE_3                0x1B
#define WM8904_DAC_DIGITAL_VOLUME_LEFT          0x1E
#define WM8904_DAC_DIGITAL_VOLUME_RIGHT         0x1F
#define WM8904_DAC_DIGITAL_0                    0x20
#define WM8904_DAC_DIGITAL_1                    0x21
#define WM8904_ADC_DIGITAL_VOLUME_LEFT          0x24
#define WM8904_ADC_DIGITAL_VOLUME_RIGHT         0x25
#define WM8904_ADC_DIGITAL_0                    0x26
#define WM8904_DIGITAL_MICROPHONE_0             0x27
#define WM8904_DRC_0                            0x28
#define WM8904_DRC_1                            0x29
#define WM8904_DRC_2                            0x2A
#define WM8904_DRC_3                            0x2B
#define WM8904_ANALOGUE_LEFT_INPUT_0            0x2C
#define WM8904_ANALOGUE_RIGHT_INPUT_0           0x2D
#define WM8904_ANALOGUE_LEFT_INPUT_1            0x2E
#define WM8904_ANALOGUE_RIGHT_INPUT_1           0x2F
#define WM8904_ANALOGUE_OUT1_LEFT               0x39
#define WM8904_ANALOGUE_OUT1_RIGHT              0x3A
#define WM8904_ANALOGUE_OUT2_LEFT               0x3B
#define WM8904_ANALOGUE_OUT2_RIGHT              0x3C
#define WM8904_ANALOGUE_OUT12_ZC                0x3D
#define WM8904_DC_SERVO_0                       0x43
#define WM8904_DC_SERVO_1                       0x44
#define WM8904_DC_SERVO_2                       0x45
#define WM8904_DC_SERVO_4                       0x47
#define WM8904_DC_SERVO_5                       0x48
#define WM8904_DC_SERVO_6                       0x49
#define WM8904_DC_SERVO_7                       0x4A
#define WM8904_DC_SERVO_8                       0x4B
#define WM8904_DC_SERVO_9                       0x4C
#define WM8904_DC_SERVO_READBACK_0              0x4D
#define WM8904_ANALOGUE_HP_0                    0x5A
#define WM8904_ANALOGUE_LINEOUT_0               0x5E
#define WM8904_CHARGE_PUMP_0                    0x62
#define WM8904_CLASS_W_0                        0x68
#define WM8904_WRITE_SEQUENCER_0                0x6C
#define WM8904_WRITE_SEQUENCER_1                0x6D
#define WM8904_WRITE_SEQUENCER_2                0x6E
#define WM8904_WRITE_SEQUENCER_3                0x6F
#define WM8904_WRITE_SEQUENCER_4                0x70
#define WM8904_FLL_CONTROL_1                    0x74
#define WM8904_FLL_CONTROL_2                    0x75
#define WM8904_FLL_CONTROL_3                    0x76
#define WM8904_FLL_CONTROL_4                    0x77
#define WM8904_FLL_CONTROL_5                    0x78
#define WM8904_GPIO_CONTROL_1                   0x79
#define WM8904_GPIO_CONTROL_2                   0x7A
#define WM8904_GPIO_CONTROL_3                   0x7B
#define WM8904_GPIO_CONTROL_4                   0x7C
#define WM8904_DIGITAL_PULLS                    0x7E
#define WM8904_INTERRUPT_STATUS                 0x7F
#define WM8904_INTERRUPT_STATUS_MASK            0x80
#define WM8904_INTERRUPT_POLARITY               0x81
#define WM8904_INTERRUPT_DEBOUNCE               0x82
#define WM8904_EQ1                              0x86
#define WM8904_EQ2                              0x87
#define WM8904_EQ3                              0x88
#define WM8904_EQ4                              0x89
#define WM8904_EQ5                              0x8A
#define WM8904_EQ6                              0x8B
#define WM8904_EQ7                              0x8C
#define WM8904_EQ8                              0x8D
#define WM8904_EQ9                              0x8E
#define WM8904_EQ10                             0x8F
#define WM8904_EQ11                             0x90
#define WM8904_EQ12                             0x91
#define WM8904_EQ13                             0x92
#define WM8904_EQ14                             0x93
#define WM8904_EQ15                             0x94
#define WM8904_EQ16                             0x95
#define WM8904_EQ17                             0x96
#define WM8904_EQ18                             0x97
#define WM8904_EQ19                             0x98
#define WM8904_EQ20                             0x99
#define WM8904_EQ21                             0x9A
#define WM8904_EQ22                             0x9B
#define WM8904_EQ23                             0x9C
#define WM8904_EQ24                             0x9D
#define WM8904_CONTROL_INTERFACE_TEST_1         0xA1
#define WM8904_ADC_TEST_0                       0xC6
#define WM8904_ANALOGUE_OUTPUT_BIAS_0           0xCC
#define WM8904_FLL_NCO_TEST_0                   0xF7
#define WM8904_FLL_NCO_TEST_1                   0xF8

#define WM8904_REGISTER_COUNT                   101
#define WM8904_MAX_REGISTER                     0xF8

/*
 * Field Definitions.
 */

/*
 * R0 (0x00) - SW Reset and ID
 */
#define WM8904_SW_RST_DEV_ID1_Pos               0  /* SW_RST_DEV_ID1 - [15:0] */
#define WM8904_SW_RST_DEV_ID1                   0x8904

/*
 * R4 (0x04) - Bias Control 0
 */
#define WM8904_ISEL_Pos                         2  /* ISEL - [3:2] */
#define WM8904_ISEL_Msk                         0x000C
#define WM8904_ISEL(Value)                      (WM8904_ISEL_Msk & ((Value) << WM8904_ISEL_Pos))
#define WM8904_ISEL_LP_BIAS                     WM8904_ISEL(0) 
#define WM8904_ISEL_HP_BIAS                     WM8904_ISEL(2)
#define WM8904_BIAS_ENA_Pos                     0  /* BIAS_ENA */
#define WM8904_BIAS_ENA                         0x0001

/*
 * R5 (0x05) - VMID Control 0
 */
#define WM8904_VMID_BUF_ENA_Pos                 6  /* VMID_BUF_ENA */
#define WM8904_VMID_BUF_ENA                     0x0040
#define WM8904_VMID_RES_Pos                     1  /* VMID_RES - [2:1] */
#define WM8904_VMID_RES_Msk                     0x0006
#define WM8904_VMID_RES(Value)                  (WM8904_VMID_RES_Msk & ((Value) << WM8904_VMID_RES_Pos))
#define WM8904_VMID_RES_OFF                     WM8904_VMID_RES(0)
#define WM8904_VMID_RES_NORMAL                  WM8904_VMID_RES(1)
#define WM8904_VMID_RES_LP                      WM8904_VMID_RES(2)
#define WM8904_VMID_RES_FAST                    WM8904_VMID_RES(3)
#define WM8904_VMID_ENA_Pos                     0  /* VMID_ENA */
#define WM8904_VMID_ENA                         0x0001

/*
 * R6 (0x06) - Mic Bias Control 0
 */
#define WM8904_MICDET_THR_Pos                   4  /* MICDET_THR - [6:4] */
#define WM8904_MICDET_THR_Msk                   0x0070
#define WM8904_MICDET_THR(Value)                (WM8904_MICDET_THR_Msk & ((Value) << WM8904_MICDET_THR_Pos))
#define WM8904_MICSHORT_THR_Pos                 2  /* MICSHORT_THR - [3:2] */
#define WM8904_MICSHORT_THR_Msk                 0x000C
#define WM8904_MICSHORT_THR(Value)              (WM8904_MICSHORT_THR_Msk & ((Value) << WM8904_MICSHORT_THR_Pos))
#define WM8904_MICDET_ENA_Pos                   1  /* MICDET_ENA */
#define WM8904_MICDET_ENA                       0x002
#define WM8904_MICBIAS_ENA_Pos                  0  /* MICBIAS_ENA */
#define WM8904_MICBIAS_ENA                      0x0001

/*
 * R9 (0x07) - Mic Bias Control 1
 */
#define WM8904_MICBIAS_SEL_Pos                  0  /* MICBIAS_SEL - [2:0] */
#define WM8904_MICBIAS_SEL_Msk                  0x0007  
#define WM8904_MICBIAS_SEL(Value)               (WM8904_MICBIAS_SEL_Msk & ((Value) << WM8904_MICBIAS_SEL_Pos))

/*
 * R10 (0x0A) - Analogue ADC 0
 */
#define WM8904_ADC_OSR128_Pos                   0  /* ADC_OSR128 */
#define WM8904_ADC_OSR128                       0x0001

/*
 * R12 (0x0C) - Power Management 0
 */
#define WM8904_INL_ENA_Pos                      1  /* INL_ENA */
#define WM8904_INL_ENA                          0x0002
#define WM8904_INR_ENA_Pos                      0  /* INR_ENA */
#define WM8904_INR_ENA                          0x0001

/*
 * R14 (0x0E) - Power Management 2
 */
#define WM8904_HPL_PGA_ENA_Pos                  1  /* HPL_PGA_ENA */
#define WM8904_HPL_PGA_ENA                      0x0002
#define WM8904_HPR_PGA_ENA_Pos                  0  /* HPR_PGA_ENA */
#define WM8904_HPR_PGA_ENA                      0x0001

/*
 * R15 (0x0F) - Power Management 3
 */
#define WM8904_LINEOUTL_PGA_ENA_Pos             1  /* LINEOUTL_PGA_ENA */
#define WM8904_LINEOUTL_PGA_ENA                 0x0002
#define WM8904_LINEOUTR_PGA_ENA_Pos             0  /* LINEOUTR_PGA_ENA */
#define WM8904_LINEOUTR_PGA_ENA                 0x0001

/*
 * R18 (0x12) - Power Management 6
 */
#define WM8904_DACL_ENA_Pos                     3  /* DACL_ENA */
#define WM8904_DACL_ENA                         0x0008
#define WM8904_DACR_ENA_Pos                     2  /* DACR_ENA */
#define WM8904_DACR_ENA                         0x0004
#define WM8904_ADCL_ENA_Pos                     1  /* ADCL_ENA */
#define WM8904_ADCL_ENA                         0x0002
#define WM8904_ADCR_ENA_Pos                     0  /* ADCR_ENA */
#define WM8904_ADCR_ENA                         0x0001

/*
 * R20 (0x14) - Clock Rates 0
 */
#define WM8904_TOCLK_RATE_DIV16_Pos             14  /* TOCLK_RATE_DIV16 */
#define WM8904_TOCLK_RATE_DIV16                 0x4000
#define WM8904_TOCLK_RATE_X4_Pos                13  /* TOCLK_RATE_X4 */
#define WM8904_TOCLK_RATE_X4                    0x2000
#define WM8904_MCLK_DIV_Pos                     0  /* MCLK_DIV */
#define WM8904_MCLK_DIV                         0x0001

/*
 * R21 (0x15) - Clock Rates 1
 */
#define WM8904_CLK_SYS_RATE_Pos                 10  /* CLK_SYS_RATE - [13:10] */
#define WM8904_CLK_SYS_RATE_Msk                 0x3C00
#define WM8904_CLK_SYS_RATE(Value)              (WM8904_CLK_SYS_RATE_Msk & ((Value) << WM8904_CLK_SYS_RATE_Pos))
#define WM8904_SAMPLE_RATE_Pos                  0  /* SAMPLE_RATE - [2:0] */
#define WM8904_SAMPLE_RATE_Msk                  0x0007
#define WM8904_SAMPLE_RATE(Value)               (WM8904_SAMPLE_RATE_Msk & ((Value) << WM8904_SAMPLE_RATE_Pos))

/*
 * R22 (0x16) - Clock Rates 2
 */
#define WM8904_MCLK_INV_Pos                     15  /* MCLK_INV */
#define WM8904_MCLK_INV                         0x8000
#define WM8904_SYSCLK_SRC_Pos                   14  /* SYSCLK_SRC */
#define WM8904_SYSCLK_SRC                       0x4000
#define WM8904_TOCLK_RATE_Pos                   12  /* TOCLK_RATE */
#define WM8904_TOCLK_RATE                       0x1000
#define WM8904_OPCLK_ENA_Pos                    3  /* OPCLK_ENA */
#define WM8904_OPCLK_ENA                        0x0008
#define WM8904_CLK_SYS_ENA_Pos                  2  /* CLK_SYS_ENA */
#define WM8904_CLK_SYS_ENA                      0x0004
#define WM8904_CLK_DSP_ENA_Pos                  1  /* CLK_DSP_ENA */
#define WM8904_CLK_DSP_ENA                      0x0002
#define WM8904_TOCLK_ENA_Pos                    0  /* TOCLK_ENA */
#define WM8904_TOCLK_ENA                        0x0001

/*
 * R24 (0x18) - Audio Interface 0
 */
#define WM8904_DACL_DATINV_Pos                  12  /* DACL_DATINV */
#define WM8904_DACL_DATINV                      0x1000
#define WM8904_DACR_DATINV_Pos                  11  /* DACR_DATINV */
#define WM8904_DACR_DATINV                      0x0800
#define WM8904_DAC_BOOST_Pos                    9  /* DAC_BOOST - [10:9] */
#define WM8904_DAC_BOOST_Msk                    0x0600
#define WM8904_DAC_BOOST(Value)                 (WM8904_DAC_BOOST_Msk & ((Value) << WM8904_DAC_BOOST_Pos))
#define WM8904_LOOPBACK_Pos                     8  /* LOOPBACK */
#define WM8904_LOOPBACK                         0x0100
#define WM8904_AIFADCL_SRC_Pos                  7  /* AIFADCL_SRC */
#define WM8904_AIFADCL_SRC                      0x0080
#define WM8904_AIFADCR_SRC_Pos                  6  /* AIFADCR_SRC */
#define WM8904_AIFADCR_SRC                      0x0040
#define WM8904_AIFDACL_SRC_Pos                  5  /* AIFDACL_SRC */
#define WM8904_AIFDACL_SRC                      0x0020
#define WM8904_AIFDACR_SRC_Pos                  4  /* AIFDACR_SRC */
#define WM8904_AIFDACR_SRC                      0x0010
#define WM8904_ADC_COMP_Pos                     3  /* ADC_COMP */
#define WM8904_ADC_COMP                         0x0008
#define WM8904_ADC_COMPMODE_Pos                 2  /* ADC_COMPMODE */
#define WM8904_ADC_COMPMODE                     0x0004
#define WM8904_DAC_COMP_Pos                     1  /* DAC_COMP */
#define WM8904_DAC_COMP                         0x0002
#define WM8904_DAC_COMPMODE_Pos                 0  /* DAC_COMPMODE */
#define WM8904_DAC_COMPMODE                     0x0001

/*
 * R25 (0x19) - Audio Interface 1
 */
#define WM8904_AIFDAC_TDM_Pos                   13  /* AIFDAC_TDM */
#define WM8904_AIFDAC_TDM                       0x2000
#define WM8904_AIFDAC_TDM_CHAN_Pos              12  /* AIFDAC_TDM_CHAN */
#define WM8904_AIFDAC_TDM_CHAN                  0x1000
#define WM8904_AIFADC_TDM_Pos                   11  /* AIFADC_TDM */
#define WM8904_AIFADC_TDM                       0x0800
#define WM8904_AIFADC_TDM_CHAN_Pos              10  /* AIFADC_TDM_CHAN */
#define WM8904_AIFADC_TDM_CHAN                  0x0400
#define WM8904_AIF_TRIS_Pos                     8  /* AIF_TRIS */
#define WM8904_AIF_TRIS                         0x0100
#define WM8904_AIF_BCLK_INV_Pos                 7  /* AIF_BCLK_INV */
#define WM8904_AIF_BCLK_INV                     0x0080
#define WM8904_BCLK_DIR_Pos                     6  /* BCLK_DIR */
#define WM8904_BCLK_DIR                         0x0040
#define WM8904_AIF_LRCLK_INV_Pos                4  /* AIF_LRCLK_INV */
#define WM8904_AIF_LRCLK_INV                    0x0010
#define WM8904_AIF_WL_Pos                       2  /* AIF_WL - [3:2] */
#define WM8904_AIF_WL_Msk                       0x000C
#define WM8904_AIF_WL(Value)                    (WM8904_AIF_WL_Msk & ((Value) << WM8904_AIF_WL_Pos))
#define WM8904_AIF_WL_16BIT                     WM8904_AIF_WL(0)
#define WM8904_AIF_WL_20BIT                     WM8904_AIF_WL(1)
#define WM8904_AIF_WL_24BIT                     WM8904_AIF_WL(2)
#define WM8904_AIF_WL_32BIT                     WM8904_AIF_WL(3)
#define WM8904_AIF_FMT_Pos                      0  /* AIF_FMT - [1:0] */
#define WM8904_AIF_FMT_Msk                      0x0003
#define WM8904_AIF_FMT(Value)                   (WM8904_AIF_FMT_Msk & ((Value) << WM8904_AIF_FMT_Pos))
#define WM8904_AIF_FMT_RIGHT                    WM8904_AIF_FMT(0) 
#define WM8904_AIF_FMT_LEFT                     WM8904_AIF_FMT(1) 
#define WM8904_AIF_FMT_I2S                      WM8904_AIF_FMT(2) 
#define WM8904_AIF_FMT_DSP                      WM8904_AIF_FMT(3) 

/*
 * R26 (0x1A) - Audio Interface 2
 */
#define WM8904_OPCLK_DIV_Pos                    8  /* OPCLK_DIV - [11:8] */
#define WM8904_OPCLK_DIV_Msk                    0x0F00
#define WM8904_OPCLK_DIV(Value)                 (WM8904_OPCLK_DIV_Msk & ((Value) << WM8904_OPCLK_DIV_Pos))
#define WM8904_BCLK_DIV_Pos                     0  /* BCLK_DIV - [4:0] */
#define WM8904_BCLK_DIV_Msk                     0x001F
#define WM8904_BCLK_DIV(Value)                  (WM8904_BCLK_DIV_Msk & ((Value) << WM8904_BCLK_DIV_Pos))

/*
 * R27 (0x1B) - Audio Interface 3
 */
#define WM8904_LRCLK_DIR_Pos                    11  /* LRCLK_DIR */
#define WM8904_LRCLK_DIR                        0x0800
#define WM8904_LRCLK_RATE_Pos                   0  /* LRCLK_RATE - [10:0] */
#define WM8904_LRCLK_RATE_Msk                   0x07FF
#define WM8904_LRCLK_RATE(Value)                (WM8904_LRCLK_RATE_Msk & ((Value) << WM8904_LRCLK_RATE_Pos))

/*
 * R30 (0x1E) - DAC Digital Volume Left
 */
#define WM8904_DAC_VU_Pos                       8  /* DAC_VU */
#define WM8904_DAC_VU                           0x0100
#define WM8904_DACL_VOL_Pos                     0  /* DACL_VOL - [7:0] */
#define WM8904_DACL_VOL_Msk                     0x00FF  /* DACL_VOL - [7:0] */
#define WM8904_DACL_VOL(Value)                  (WM8904_DACL_VOL_Msk & ((Value) << WM8904_DACL_VOL_Pos))

/*
 * R31 (0x1F) - DAC Digital Volume Right
 */
#define WM8904_DAC_VU_Pos                       8  /* DAC_VU */
#define WM8904_DAC_VU                           0x0100
#define WM8904_DACR_VOL_Pos                     0  /* DACR_VOL - [7:0] */
#define WM8904_DACR_VOL_Msk                     0x00FF
#define WM8904_DACR_VOL(Value)                  (WM8904_DACR_VOL_Msk & ((Value) << WM8904_DACR_VOL_Pos))

/*
 * R32 (0x20) - DAC Digital 0
 */
#define WM8904_ADCL_DAC_SVOL_Pos                8  /* ADCL_DAC_SVOL - [11:8] */
#define WM8904_ADCL_DAC_SVOL_Msk                0x0F00
#define WM8904_ADCL_DAC_SVOL(Value)             (WM8904_ADCL_DAC_SVOL_Msk & ((Value) << WM8904_ADCL_DAC_SVOL_Pos))
#define WM8904_ADCR_DAC_SVOL_Pos                4  /* ADCR_DAC_SVOL - [7:4] */
#define WM8904_ADCR_DAC_SVOL_Msk                0x00F0
#define WM8904_ADCR_DAC_SVOL(Value)             (WM8904_ADCR_DAC_SVOL_Msk & ((Value) << WM8904_ADCR_DAC_SVOL_Pos))
#define WM8904_ADC_TO_DACL_Pos                  2  /* ADC_TO_DACL - [3:2] */
#define WM8904_ADC_TO_DACL_Msk                  0x000C
#define WM8904_ADC_TO_DACL(Value)               (WM8904_ADC_TO_DACL_Msk & ((Value) << WM8904_ADC_TO_DACL_Pos))
#define WM8904_ADC_TO_DACR_Pos                  0  /* ADC_TO_DACR - [1:0] */
#define WM8904_ADC_TO_DACR_Msk                  0x0003
#define WM8904_ADC_TO_DACR(Value)               (WM8904_ADC_TO_DACR_Msk & ((Value) << WM8904_ADC_TO_DACR_Pos))

/*
 * R33 (0x21) - DAC Digital 1
 */
#define WM8904_DAC_MONO_Pos                     12  /* DAC_MONO */
#define WM8904_DAC_MONO                         0x1000
#define WM8904_DAC_SB_FILT_Pos                  11  /* DAC_SB_FILT */
#define WM8904_DAC_SB_FILT                      0x0800
#define WM8904_DAC_MUTERATE_Pos                 10  /* DAC_MUTERATE */
#define WM8904_DAC_MUTERATE                     0x0400
#define WM8904_DAC_UNMUTE_RAMP_Pos              9  /* DAC_UNMUTE_RAMP */
#define WM8904_DAC_UNMUTE_RAMP                  0x0200
#define WM8904_DAC_OSR128_Pos                   6  /* DAC_OSR128 */
#define WM8904_DAC_OSR128                       0x0040
#define WM8904_DAC_MUTE_Pos                     3  /* DAC_MUTE */
#define WM8904_DAC_MUTE                         0x0008
#define WM8904_DEEMPH_Pos                       1  /* DEEMPH - [2:1] */
#define WM8904_DEEMPH_Msk                       0x0006
#define WM8904_DEEMPH(Value)                    (WM8904_DEEMPH_Msk & ((Value) << WM8904_DEEMPH_Pos))

/*
 * R36 (0x24) - ADC Digital Volume Left
 */
#define WM8904_ADC_VU_Pos                       8  /* ADC_VU */
#define WM8904_ADC_VU                           0x0100
#define WM8904_ADCL_VOL_Pos                     0  /* ADCL_VOL - [7:0] */
#define WM8904_ADCL_VOL_Msk                     0x00FF
#define WM8904_ADCL_VOL(Value)                  (WM8904_ADCL_VOL_Msk & ((Value) << WM8904_ADCL_VOL_Pos))

/*
 * R37 (0x25) - ADC Digital Volume Right
 */
#define WM8904_ADC_VU_Pos                       8  /* ADC_VU */
#define WM8904_ADC_VU                           0x0100
#define WM8904_ADCR_VOL_Pos                     0  /* ADCR_VOL - [7:0] */
#define WM8904_ADCR_VOL_Msk                     0x00FF
#define WM8904_ADCR_VOL(Value)                  (WM8904_ADCR_VOL_Msk & ((Value) << WM8904_ADCR_VOL_Pos))

/*
 * R38 (0x26) - ADC Digital 0
 */
#define WM8904_ADC_HPF_CUT_Pos                  5  /* ADC_HPF_CUT - [6:5] */
#define WM8904_ADC_HPF_CUT_Msk                  0x0060  /* ADC_HPF_CUT - [6:5] */
#define WM8904_ADC_HPF_CUT(Value)               (WM8904_ADC_HPF_CUT_Msk & ((Value) << WM8904_ADC_HPF_CUT_Pos))
#define WM8904_ADC_HPF_Pos                      4  /* ADC_HPF */
#define WM8904_ADC_HPF                          0x0010
#define WM8904_ADCL_DATINV_Pos                  1  /* ADCL_DATINV */
#define WM8904_ADCL_DATINV                      0x0002
#define WM8904_ADCR_DATINV_Pos                  0  /* ADCR_DATINV */
#define WM8904_ADCR_DATINV                      0x0001

/*
 * R39 (0x27) - Digital Microphone 0
 */
#define WM8904_DMIC_ENA_Pos                     12  /* DMIC_ENA */
#define WM8904_DMIC_ENA                         0x1000
#define WM8904_DMIC_SRC_Pos                     11  /* DMIC_SRC */
#define WM8904_DMIC_SRC                         0x0800

/*
 * R40 (0x28) - DRC 0
 */
#define WM8904_DRC_ENA_Pos                      15  /* DRC_ENA */
#define WM8904_DRC_ENA                          0x8000
#define WM8904_DRC_DAC_PATH_Pos                 14  /* DRC_DAC_PATH */
#define WM8904_DRC_DAC_PATH                     0x4000
#define WM8904_DRC_GS_HYST_LVL_Pos              11  /* DRC_GS_HYST_LVL - [12:11] */
#define WM8904_DRC_GS_HYST_LVL_Msk              0x1800
#define WM8904_DRC_GS_HYST_LVL(Value)           (WM8904_DRC_GS_HYST_LVL_Msk & ((Value) << WM8904_DRC_GS_HYST_LVL_Pos))
#define WM8904_DRC_STARTUP_GAIN_Pos             6  /* DRC_STARTUP_GAIN - [10:6] */
#define WM8904_DRC_STARTUP_GAIN_Msk             0x07C0
#define WM8904_DRC_STARTUP_GAIN(Value)          (WM8904_DRC_STARTUP_GAIN_Msk & ((Value) << WM8904_DRC_STARTUP_GAIN_Pos))
#define WM8904_DRC_FF_DELAY_Pos                 5  /* DRC_FF_DELAY */
#define WM8904_DRC_FF_DELAY                     0x0020
#define WM8904_DRC_GS_ENA_Pos                   3  /* DRC_GS_ENA */
#define WM8904_DRC_GS_ENA                       0x0008
#define WM8904_DRC_QR_Pos                       2  /* DRC_QR */
#define WM8904_DRC_QR                           0x0004
#define WM8904_DRC_ANTICLIP_Pos                 1  /* DRC_ANTICLIP */
#define WM8904_DRC_ANTICLIP                     0x0002
#define WM8904_DRC_GS_HYST_Pos                  0  /* DRC_GS_HYST */
#define WM8904_DRC_GS_HYST                      0x0001

/*
 * R41 (0x29) - DRC 1
 */
#define WM8904_DRC_ATK_Pos                      12  /* DRC_ATK - [15:12] */
#define WM8904_DRC_ATK_Msk                      0xF000
#define WM8904_DRC_ATK(Value)                   (WM8904_DRC_ATK_Msk & ((Value) << WM8904_DRC_ATK_Pos))
#define WM8904_DRC_DCY_Pos                      8  /* DRC_DCY - [11:8] */
#define WM8904_DRC_DCY_Msk                      0x0F00 
#define WM8904_DRC_DCY(Value)                   (WM8904_DRC_DCY_Msk & ((Value) << WM8904_DRC_DCY_Pos))
#define WM8904_DRC_QR_THR_Pos                   6  /* DRC_QR_THR - [7:6] */
#define WM8904_DRC_QR_THR_Msk                   0x00C0
#define WM8904_DRC_QR_THR(Value)                (WM8904_DRC_QR_THR_Msk & ((Value) << WM8904_DRC_QR_THR_Pos))
#define WM8904_DRC_QR_DCY_Pos                   4  /* DRC_QR_DCY - [5:4] */
#define WM8904_DRC_QR_DCY_Msk                   0x0030
#define WM8904_DRC_QR_DCY(Value)                (WM8904_DRC_QR_DCY_Msk & ((Value) << WM8904_DRC_QR_DCY_Pos))
#define WM8904_DRC_MINGAIN_Pos                  2  /* DRC_MINGAIN - [3:2] */
#define WM8904_DRC_MINGAIN_Msk                  0x000C 
#define WM8904_DRC_MINGAIN(Value)               (WM8904_DRC_MINGAIN_Msk & ((Value) << WM8904_DRC_MINGAIN_Pos))
#define WM8904_DRC_MAXGAIN_Pos                  0  /* DRC_MAXGAIN - [1:0] */
#define WM8904_DRC_MAXGAIN_Msk                  0x0003 
#define WM8904_DRC_MAXGAIN(Value)               (WM8904_DRC_MAXGAIN_Msk & ((Value) << WM8904_DRC_MAXGAIN_Pos))

/*
 * R42 (0x2A) - DRC 2
 */
#define WM8904_DRC_HI_COMP_Pos                  3  /* DRC_HI_COMP - [5:3] */
#define WM8904_DRC_HI_COMP_Msk                  0x0038
#define WM8904_DRC_HI_COMP(Value)               (WM8904_DRC_HI_COMP_Msk & ((Value) << WM8904_DRC_HI_COMP_Pos))
#define WM8904_DRC_LO_COMP_Pos                  0  /* DRC_LO_COMP - [2:0] */
#define WM8904_DRC_LO_COMP_Msk                  0x0007
#define WM8904_DRC_LO_COMP(Value)               (WM8904_DRC_LO_COMP_Msk & ((Value) << WM8904_DRC_LO_COMP_Pos))

/*
 * R43 (0x2B) - DRC 3
 */
#define WM8904_DRC_KNEE_IP_Pos                  5  /* DRC_KNEE_IP - [10:5] */
#define WM8904_DRC_KNEE_IP_Msk                  0x07E0
#define WM8904_DRC_KNEE_IP(Value)               (WM8904_DRC_KNEE_IP_Msk & ((Value) << WM8904_DRC_KNEE_IP_Pos))
#define WM8904_DRC_KNEE_OP_Pos                  0  /* DRC_KNEE_OP - [4:0] */
#define WM8904_DRC_KNEE_OP_Msk                  0x001F
#define WM8904_DRC_KNEE_OP(Value)               (WM8904_DRC_KNEE_OP_Msk & ((Value) << WM8904_DRC_KNEE_OP_Pos))

/*
 * R44 (0x2C) - Analogue Left Input 0
 */
#define WM8904_LINMUTE_Pos                      7  /* LINMUTE */
#define WM8904_LINMUTE                          0x0080
#define WM8904_LIN_VOL_Pos                      0  /* LIN_VOL - [4:0] */
#define WM8904_LIN_VOL_Msk                      0x001F
#define WM8904_LIN_VOL(Value)                   (WM8904_LIN_VOL_Msk & ((Value) << WM8904_LIN_VOL_Pos))

/*
 * R45 (0x2D) - Analogue Right Input 0
 */
#define WM8904_RINMUTE_Pos                      7  /* RINMUTE */
#define WM8904_RINMUTE                          0x0080
#define WM8904_RIN_VOL_Pos                      0  /* RIN_VOL - [4:0] */
#define WM8904_RIN_VOL_Msk                      0x001F
#define WM8904_RIN_VOL(Value)                   (WM8904_RIN_VOL_Msk & ((Value) << WM8904_RIN_VOL_Pos))

/*
 * R46 (0x2E) - Analogue Left Input 1
 */
#define WM8904_INL_CM_ENA_Pos                   6  /* INL_CM_ENA */
#define WM8904_INL_CM_ENA                       0x0040 
#define WM8904_L_IP_SEL_N_Pos                   4  /* L_IP_SEL_N - [5:4] */
#define WM8904_L_IP_SEL_N_Msk                   0x0030
#define WM8904_L_IP_SEL_N(Value)                (WM8904_L_IP_SEL_N_Msk & ((Value) << WM8904_L_IP_SEL_N_Pos))
#define WM8904_L_IP_SEL_N_IN1L                  WM8904_L_IP_SEL_N(0)
#define WM8904_L_IP_SEL_N_IN2L                  WM8904_L_IP_SEL_N(1)
#define WM8904_L_IP_SEL_N_IN3L                  WM8904_L_IP_SEL_N(2)
#define WM8904_L_IP_SEL_P_Pos                   2  /* L_IP_SEL_P - [3:2] */
#define WM8904_L_IP_SEL_P_Msk                   0x000C 
#define WM8904_L_IP_SEL_P(Value)                (WM8904_L_IP_SEL_P_Msk & ((Value) << WM8904_L_IP_SEL_P_Pos))
#define WM8904_L_IP_SEL_P_IN1L                  WM8904_L_IP_SEL_P(0)
#define WM8904_L_IP_SEL_P_IN2L                  WM8904_L_IP_SEL_P(1)
#define WM8904_L_IP_SEL_P_IN3L                  WM8904_L_IP_SEL_P(2)
#define WM8904_L_MODE_Pos                       0  /* L_MODE - [1:0] */
#define WM8904_L_MODE_Msk                       0x0003 
#define WM8904_L_MODE(Value)                    (WM8904_L_MODE_Msk & ((Value) << WM8904_L_MODE_Pos))
#define WM8904_L_MODE_SINGLE_ENDED              WM8904_L_MODE(0) 
#define WM8904_L_MODE_DIFF_LINE                 WM8904_L_MODE(1) 
#define WM8904_L_MODE_DIFF_MIC                  WM8904_L_MODE(2) 

/*
 * R47 (0x2F) - Analogue Right Input 1
 */
#define WM8904_INR_CM_ENA_Pos                   6  /* INR_CM_ENA */
#define WM8904_INR_CM_ENA                       0x0040
#define WM8904_R_IP_SEL_N_Pos                   4  /* R_IP_SEL_N - [5:4] */
#define WM8904_R_IP_SEL_N_Msk                   0x0030
#define WM8904_R_IP_SEL_N(Value)                (WM8904_R_IP_SEL_N_Msk & ((Value) << WM8904_R_IP_SEL_N_Pos))
#define WM8904_R_IP_SEL_N_IN1L                  WM8904_R_IP_SEL_N(0)
#define WM8904_R_IP_SEL_N_IN2L                  WM8904_R_IP_SEL_N(1)
#define WM8904_R_IP_SEL_N_IN3L                  WM8904_R_IP_SEL_N(2)
#define WM8904_R_IP_SEL_P_Pos                   2  /* R_IP_SEL_P - [3:2] */
#define WM8904_R_IP_SEL_P_Msk                   0x000C
#define WM8904_R_IP_SEL_P(Value)                (WM8904_R_IP_SEL_P_Msk & ((Value) << WM8904_R_IP_SEL_P_Pos))
#define WM8904_R_IP_SEL_P_IN1L                  WM8904_R_IP_SEL_P(0)
#define WM8904_R_IP_SEL_P_IN2L                  WM8904_R_IP_SEL_P(1)
#define WM8904_R_IP_SEL_P_IN3L                  WM8904_R_IP_SEL_P(2)
#define WM8904_R_MODE_Pos                       0  /* R_MODE - [1:0] */
#define WM8904_R_MODE_Msk                       0x0003
#define WM8904_R_MODE(Value)                    (WM8904_R_MODE_Msk & ((Value) << WM8904_R_MODE_Pos))
#define WM8904_R_MODE_SINGLE_ENDED              WM8904_R_MODE(0) 
#define WM8904_R_MODE_DIFF_LINE                 WM8904_R_MODE(1) 
#define WM8904_R_MODE_DIFF_MIC                  WM8904_R_MODE(2) 

/*
 * R57 (0x39) - Analogue OUT1 Left
 */
#define WM8904_HPOUTL_MUTE_Pos                  8  /* HPOUTL_MUTE */
#define WM8904_HPOUTL_MUTE                      0x0100
#define WM8904_HPOUT_VU_Pos                     7  /* HPOUT_VU */
#define WM8904_HPOUT_VU                         0x0080
#define WM8904_HPOUTLZC_Pos                     6  /* HPOUTLZC */
#define WM8904_HPOUTLZC                         0x0040
#define WM8904_HPOUTL_VOL_Pos                   0  /* HPOUTL_VOL - [5:0] */
#define WM8904_HPOUTL_VOL_Msk                   0x003F
#define WM8904_HPOUTL_VOL(Value)                (WM8904_HPOUTL_VOL_Msk & ((Value) << WM8904_HPOUTL_VOL_Pos))

/*
 * R58 (0x3A) - Analogue OUT1 Right
 */
#define WM8904_HPOUTR_MUTE_Pos                  8  /* HPOUTR_MUTE */
#define WM8904_HPOUTR_MUTE                      0x0100
#define WM8904_HPOUT_VU_Pos                     7  /* HPOUT_VU */
#define WM8904_HPOUT_VU                         0x0080
#define WM8904_HPOUTRZC_Pos                     6  /* HPOUTRZC */
#define WM8904_HPOUTRZC                         0x0040
#define WM8904_HPOUTR_VOL_Pos                   0  /* HPOUTR_VOL - [5:0] */
#define WM8904_HPOUTR_VOL_Msk                   0x003F
#define WM8904_HPOUTR_VOL(Value)                (WM8904_HPOUTR_VOL_Msk & ((Value) << WM8904_HPOUTR_VOL_Pos))

/*
 * R59 (0x3B) - Analogue OUT2 Left
 */
#define WM8904_LINEOUTL_MUTE_Pos                8  /* LINEOUTL_MUTE */
#define WM8904_LINEOUTL_MUTE                    0x0100
#define WM8904_LINEOUT_VU_Pos                   7  /* LINEOUT_VU */
#define WM8904_LINEOUT_VU                       0x0080
#define WM8904_LINEOUTLZC_Pos                   6  /* LINEOUTLZC */
#define WM8904_LINEOUTLZC                       0x0040
#define WM8904_LINEOUTL_VOL_Pos                 0  /* LINEOUTL_VOL - [5:0] */
#define WM8904_LINEOUTL_VOL_Msk                 0x003F
#define WM8904_LINEOUTL_VOL(Value)              (WM8904_LINEOUTL_VOL_Msk & ((Value) << WM8904_LINEOUTL_VOL_Pos))

/*
 * R60 (0x3C) - Analogue OUT2 Right
 */
#define WM8904_LINEOUTR_MUTE_Pos                8  /* LINEOUTR_MUTE */
#define WM8904_LINEOUTR_MUTE                    0x0100
#define WM8904_LINEOUT_VU_Pos                   7  /* LINEOUT_VU */
#define WM8904_LINEOUT_VU                       0x0080
#define WM8904_LINEOUTRZC_Pos                   6  /* LINEOUTRZC */
#define WM8904_LINEOUTRZC                       0x0040
#define WM8904_LINEOUTR_VOL_Pos                 0  /* LINEOUTR_VOL - [5:0] */
#define WM8904_LINEOUTR_VOL_Msk                 0x003F
#define WM8904_LINEOUTR_VOL(Value)              (WM8904_LINEOUTR_VOL_Msk & ((Value) << WM8904_LINEOUTR_VOL_Pos))

/*
 * R61 (0x3D) - Analogue OUT12 ZC
 */
#define WM8904_HPL_BYP_ENA_Pos                  3  /* HPL_BYP_ENA */
#define WM8904_HPL_BYP_ENA                      0x0008
#define WM8904_HPR_BYP_ENA_Pos                  2  /* HPR_BYP_ENA */
#define WM8904_HPR_BYP_ENA                      0x0004
#define WM8904_LINEOUTL_BYP_ENA_Pos             1  /* LINEOUTL_BYP_ENA */
#define WM8904_LINEOUTL_BYP_ENA                 0x0002
#define WM8904_LINEOUTR_BYP_ENA_Pos             0  /* LINEOUTR_BYP_ENA */
#define WM8904_LINEOUTR_BYP_ENA                 0x0001

/*
 * R67 (0x43) - DC Servo 0
 */
#define WM8904_DCS_ENA_CHAN_3_Pos               3  /* DCS_ENA_CHAN_3 */
#define WM8904_DCS_ENA_CHAN_3                   0x0008
#define WM8904_DCS_ENA_CHAN_2_Pos               2  /* DCS_ENA_CHAN_2 */
#define WM8904_DCS_ENA_CHAN_2                   0x0004
#define WM8904_DCS_ENA_CHAN_1_Pos               1  /* DCS_ENA_CHAN_1 */
#define WM8904_DCS_ENA_CHAN_1                   0x0002
#define WM8904_DCS_ENA_CHAN_0_Pos               0  /* DCS_ENA_CHAN_0 */
#define WM8904_DCS_ENA_CHAN_0                   0x0001

/*
 * R68 (0x44) - DC Servo 1
 */
#define WM8904_DCS_TRIG_SINGLE_3_Pos            15  /* DCS_TRIG_SINGLE_3 */
#define WM8904_DCS_TRIG_SINGLE_3                0x8000
#define WM8904_DCS_TRIG_SINGLE_2_Pos            14  /* DCS_TRIG_SINGLE_2 */
#define WM8904_DCS_TRIG_SINGLE_2                0x4000
#define WM8904_DCS_TRIG_SINGLE_1_Pos            13  /* DCS_TRIG_SINGLE_1 */
#define WM8904_DCS_TRIG_SINGLE_1                0x2000
#define WM8904_DCS_TRIG_SINGLE_0_Pos            12  /* DCS_TRIG_SINGLE_0 */
#define WM8904_DCS_TRIG_SINGLE_0                0x1000
#define WM8904_DCS_TRIG_SERIES_3_Pos            11  /* DCS_TRIG_SERIES_3 */
#define WM8904_DCS_TRIG_SERIES_3                0x0800
#define WM8904_DCS_TRIG_SERIES_2_Pos            10  /* DCS_TRIG_SERIES_2 */
#define WM8904_DCS_TRIG_SERIES_2                0x0400
#define WM8904_DCS_TRIG_SERIES_1_Pos            9  /* DCS_TRIG_SERIES_1 */
#define WM8904_DCS_TRIG_SERIES_1                0x0200
#define WM8904_DCS_TRIG_SERIES_0_Pos            8  /* DCS_TRIG_SERIES_0 */
#define WM8904_DCS_TRIG_SERIES_0                0x0100
#define WM8904_DCS_TRIG_STARTUP_3_Pos           7  /* DCS_TRIG_STARTUP_3 */
#define WM8904_DCS_TRIG_STARTUP_3               0x0080
#define WM8904_DCS_TRIG_STARTUP_2_Pos           6  /* DCS_TRIG_STARTUP_2 */
#define WM8904_DCS_TRIG_STARTUP_2               0x0040
#define WM8904_DCS_TRIG_STARTUP_1_Pos           5  /* DCS_TRIG_STARTUP_1 */
#define WM8904_DCS_TRIG_STARTUP_1               0x0020
#define WM8904_DCS_TRIG_STARTUP_0_Pos           4  /* DCS_TRIG_STARTUP_0 */
#define WM8904_DCS_TRIG_STARTUP_0               0x0010
#define WM8904_DCS_TRIG_DAC_WR_3_Pos            3  /* DCS_TRIG_DAC_WR_3 */
#define WM8904_DCS_TRIG_DAC_WR_3                0x0008
#define WM8904_DCS_TRIG_DAC_WR_2_Pos            2  /* DCS_TRIG_DAC_WR_2 */
#define WM8904_DCS_TRIG_DAC_WR_2                0x0004
#define WM8904_DCS_TRIG_DAC_WR_1_Pos            1  /* DCS_TRIG_DAC_WR_1 */
#define WM8904_DCS_TRIG_DAC_WR_1                0x0002
#define WM8904_DCS_TRIG_DAC_WR_0_Pos            0  /* DCS_TRIG_DAC_WR_0 */
#define WM8904_DCS_TRIG_DAC_WR_0                0x0001

/*
 * R69 (0x45) - DC Servo 2
 */
#define WM8904_DCS_TIMER_PERIOD_23_Pos          8  /* DCS_TIMER_PERIOD_23 - [11:8] */
#define WM8904_DCS_TIMER_PERIOD_23_Msk          0x0F00
#define WM8904_DCS_TIMER_PERIOD_23(Value)       (WM8904_DCS_TIMER_PERIOD_23_Msk & ((Value) << WM8904_DCS_TIMER_PERIOD_23_Pos))
#define WM8904_DCS_TIMER_PERIOD_01_Pos          0  /* DCS_TIMER_PERIOD_01 - [3:0] */
#define WM8904_DCS_TIMER_PERIOD_01_Msk          0x000F
#define WM8904_DCS_TIMER_PERIOD_01(Value)       (WM8904_DCS_TIMER_PERIOD_01_Msk & ((Value) << WM8904_DCS_TIMER_PERIOD_01_Pos))

/*
 * R71 (0x47) - DC Servo 4
 */
#define WM8904_DCS_SERIES_NO_23_Pos             0  /* DCS_SERIES_NO_23 - [6:0] */
#define WM8904_DCS_SERIES_NO_23_Msk             0x007F
#define WM8904_DCS_SERIES_NO_23(Value)          (WM8904_DCS_SERIES_NO_23_Msk & ((Value) << WM8904_DCS_SERIES_NO_23_Pos))

/*
 * R72 (0x48) - DC Servo 5
 */
#define WM8904_DCS_SERIES_NO_01_Pos             0  /* DCS_SERIES_NO_01 - [6:0] */
#define WM8904_DCS_SERIES_NO_01_Msk             0x007F
#define WM8904_DCS_SERIES_NO_01(Value)          (WM8904_DCS_SERIES_NO_01_Msk & ((Value) << WM8904_DCS_SERIES_NO_01_Pos))

/*
 * R73 (0x49) - DC Servo 6
 */
#define WM8904_DCS_DAC_WR_VAL_3_Pos             0  /* DCS_DAC_WR_VAL_3 - [7:0] */
#define WM8904_DCS_DAC_WR_VAL_3_Msk             0x00FF
#define WM8904_DCS_DAC_WR_VAL_3(Value)          (WM8904_DCS_DAC_WR_VAL_3_Msk & ((Value) << WM8904_DCS_DAC_WR_VAL_3_Pos))

/*
 * R74 (0x4A) - DC Servo 7
 */
#define WM8904_DCS_DAC_WR_VAL_2_Pos             0  /* DCS_DAC_WR_VAL_2 - [7:0] */
#define WM8904_DCS_DAC_WR_VAL_2_Msk             0x00FF
#define WM8904_DCS_DAC_WR_VAL_2(Value)          (WM8904_DCS_DAC_WR_VAL_2_Msk & ((Value) << WM8904_DCS_DAC_WR_VAL_2_Pos))

/*
 * R75 (0x4B) - DC Servo 8
 */
#define WM8904_DCS_DAC_WR_VAL_1_Pos             0  /* DCS_DAC_WR_VAL_1 - [7:0] */
#define WM8904_DCS_DAC_WR_VAL_1_Msk             0x00FF
#define WM8904_DCS_DAC_WR_VAL_1(Value)          (WM8904_DCS_DAC_WR_VAL_1_Msk & ((Value) << WM8904_DCS_DAC_WR_VAL_1_Pos))

/*
 * R76 (0x4C) - DC Servo 9
 */
#define WM8904_DCS_DAC_WR_VAL_0_Pos             0  /* DCS_DAC_WR_VAL_0 - [7:0] */
#define WM8904_DCS_DAC_WR_VAL_0_Msk             0x00FF
#define WM8904_DCS_DAC_WR_VAL_0(Value)          (WM8904_DCS_DAC_WR_VAL_0_Msk & ((Value) << WM8904_DCS_DAC_WR_VAL_0_Pos))

/*
 * R77 (0x4D) - DC Servo Readback 0
 */
#define WM8904_DCS_CAL_COMPLETE_Pos             8  /* DCS_CAL_COMPLETE - [11:8] */
#define WM8904_DCS_CAL_COMPLETE_Msk             0x0F00
#define WM8904_DCS_CAL_COMPLETE(Value)          (WM8904_DCS_CAL_COMPLETE_Msk & ((Value) << WM8904_DCS_CAL_COMPLETE_Pos))
#define WM8904_DCS_DAC_WR_COMPLETE_Pos          4  /* DCS_DAC_WR_COMPLETE - [7:4] */
#define WM8904_DCS_DAC_WR_COMPLETE_Msk          0x00F0
#define WM8904_DCS_DAC_WR_COMPLETE(Value)       (WM8904_DCS_DAC_WR_COMPLETE_Msk & ((Value) << WM8904_DCS_DAC_WR_COMPLETE_Pos))
#define WM8904_DCS_STARTUP_COMPLETE_Pos         0  /* DCS_STARTUP_COMPLETE - [3:0] */
#define WM8904_DCS_STARTUP_COMPLETE_Msk         0x000F
#define WM8904_DCS_STARTUP_COMPLETE(Value)      (WM8904_DCS_STARTUP_COMPLETE_Msk & ((Value) << WM8904_DCS_STARTUP_COMPLETE_Pos))

/*
 * R90 (0x5A) - Analogue HP 0
 */
#define WM8904_HPL_RMV_SHORT_Pos                7  /* HPL_RMV_SHORT */
#define WM8904_HPL_RMV_SHORT                    0x0080
#define WM8904_HPL_ENA_OUTP_Pos                 6  /* HPL_ENA_OUTP */
#define WM8904_HPL_ENA_OUTP                     0x0040
#define WM8904_HPL_ENA_DLY_Pos                  5  /* HPL_ENA_DLY */
#define WM8904_HPL_ENA_DLY                      0x0020
#define WM8904_HPL_ENA_Pos                      4  /* HPL_ENA */
#define WM8904_HPL_ENA                          0x0010
#define WM8904_HPR_RMV_SHORT_Pos                3  /* HPR_RMV_SHORT */
#define WM8904_HPR_RMV_SHORT                    0x0008
#define WM8904_HPR_ENA_OUTP_Pos                 2  /* HPR_ENA_OUTP */
#define WM8904_HPR_ENA_OUTP                     0x0004
#define WM8904_HPR_ENA_DLY_Pos                  1  /* HPR_ENA_DLY */
#define WM8904_HPR_ENA_DLY                      0x0002
#define WM8904_HPR_ENA_Pos                      0  /* HPR_ENA */
#define WM8904_HPR_ENA                          0x0001

/*
 * R94 (0x5E) - Analogue Lineout 0
 */
#define WM8904_LINEOUTL_RMV_SHORT_Pos           7  /* LINEOUTL_RMV_SHORT */
#define WM8904_LINEOUTL_RMV_SHORT               0x0080
#define WM8904_LINEOUTL_ENA_OUTP_Pos            6  /* LINEOUTL_ENA_OUTP */
#define WM8904_LINEOUTL_ENA_OUTP                0x0040
#define WM8904_LINEOUTL_ENA_DLY_Pos             5  /* LINEOUTL_ENA_DLY */
#define WM8904_LINEOUTL_ENA_DLY                 0x0020
#define WM8904_LINEOUTL_ENA_Pos                 4  /* LINEOUTL_ENA */
#define WM8904_LINEOUTL_ENA                     0x0010
#define WM8904_LINEOUTR_RMV_SHORT_Pos           3  /* LINEOUTR_RMV_SHORT */
#define WM8904_LINEOUTR_RMV_SHORT               0x0008
#define WM8904_LINEOUTR_ENA_OUTP_Pos            2  /* LINEOUTR_ENA_OUTP */
#define WM8904_LINEOUTR_ENA_OUTP                0x0004
#define WM8904_LINEOUTR_ENA_DLY_Pos             1  /* LINEOUTR_ENA_DLY */
#define WM8904_LINEOUTR_ENA_DLY                 0x0002
#define WM8904_LINEOUTR_ENA_Pos                 0  /* LINEOUTR_ENA */
#define WM8904_LINEOUTR_ENA                     0x0001

/*
 * R98 (0x62) - Charge Pump 0
 */
#define WM8904_CP_ENA_Pos                       0  /* CP_ENA */
#define WM8904_CP_ENA                           0x0001

/*
 * R104 (0x68) - Class W 0
 */
#define WM8904_CP_DYN_PWR_Pos                   0  /* CP_DYN_PWR */
#define WM8904_CP_DYN_PWR                       0x0001

/*
 * R108 (0x6C) - Write Sequencer 0
 */
#define WM8904_WSEQ_ENA_Pos                     8  /* WSEQ_ENA */
#define WM8904_WSEQ_ENA                         0x0100
#define WM8904_WSEQ_WRITE_INDEX_Pos             0  /* WSEQ_WRITE_INDEX - [4:0] */
#define WM8904_WSEQ_WRITE_INDEX_Msk             0x001F
#define WM8904_WSEQ_WRITE_INDEX(Value)          (WM8904_WSEQ_WRITE_INDEX_Msk & ((Value) << WM8904_WSEQ_WRITE_INDEX_Pos))

/*
 * R109 (0x6D) - Write Sequencer 1
 */
#define WM8904_WSEQ_DATA_WIDTH_Pos              12  /* WSEQ_DATA_WIDTH - [14:12] */
#define WM8904_WSEQ_DATA_WIDTH_Msk              0x7000
#define WM8904_WSEQ_DATA_WIDTH(Value)           (WM8904_WSEQ_DATA_WIDTH_Msk & ((Value) << WM8904_WSEQ_DATA_WIDTH_Pos))
#define WM8904_WSEQ_DATA_START_Pos              8  /* WSEQ_DATA_START - [11:8] */
#define WM8904_WSEQ_DATA_START_Msk              0x0F00
#define WM8904_WSEQ_DATA_START(Value)           (WM8904_WSEQ_DATA_START_Msk & ((Value) << WM8904_WSEQ_DATA_START_Pos))
#define WM8904_WSEQ_ADDR_Pos                    0  /* WSEQ_ADDR - [7:0] */
#define WM8904_WSEQ_ADDR_Msk                    0x00FF
#define WM8904_WSEQ_ADDR(Value)                 (WM8904_WSEQ_ADDR_Msk & ((Value) << WM8904_WSEQ_ADDR_Pos))

/*
 * R110 (0x6E) - Write Sequencer 2
 */
#define WM8904_WSEQ_EOS_Pos                     14  /* WSEQ_EOS */
#define WM8904_WSEQ_EOS                         0x4000
#define WM8904_WSEQ_DELAY_Pos                   8  /* WSEQ_DELAY - [11:8] */
#define WM8904_WSEQ_DELAY_Msk                   0x0F00
#define WM8904_WSEQ_DELAY(Value)                (WM8904_WSEQ_DELAY_Msk & ((Value) << WM8904_WSEQ_DELAY_Pos))
#define WM8904_WSEQ_DATA_Pos                    0  /* WSEQ_DATA - [7:0] */
#define WM8904_WSEQ_DATA_Msk                    0x00FF
#define WM8904_WSEQ_DATA(Value)                 (WM8904_WSEQ_DATA_Msk & ((Value) << WM8904_WSEQ_DATA_Pos))

/*
 * R111 (0x6F) - Write Sequencer 3
 */
#define WM8904_WSEQ_ABORT_Pos                   9  /* WSEQ_ABORT */
#define WM8904_WSEQ_ABORT                       0x0200
#define WM8904_WSEQ_START_Pos                   8  /* WSEQ_START */
#define WM8904_WSEQ_START                       0x0100
#define WM8904_WSEQ_START_INDEX_Pos             0  /* WSEQ_START_INDEX - [5:0] */
#define WM8904_WSEQ_START_INDEX_Msk             0x003F
#define WM8904_WSEQ_START_INDEX(Value)          (WM8904_WSEQ_START_INDEX_Msk & ((Value) << WM8904_WSEQ_START_INDEX_Pos))

/*
 * R112 (0x70) - Write Sequencer 4
 */
#define WM8904_WSEQ_CURRENT_INDEX_Pos           4  /* WSEQ_CURRENT_INDEX - [9:4] */
#define WM8904_WSEQ_CURRENT_INDEX_Msk           0x03F0
#define WM8904_WSEQ_CURRENT_INDEX(Value)        (WM8904_WSEQ_CURRENT_INDEX_Msk & ((Value) << WM8904_WSEQ_CURRENT_INDEX_Pos))
#define WM8904_WSEQ_BUSY_Pos                    0  /* WSEQ_BUSY */
#define WM8904_WSEQ_BUSY                        0x0001

/*
 * R116 (0x74) - FLL Control 1
 */
#define WM8904_FLL_FRACN_ENA_Pos                2  /* FLL_FRACN_ENA */
#define WM8904_FLL_FRACN_ENA                    0x0004
#define WM8904_FLL_OSC_ENA_Pos                  1  /* FLL_OSC_ENA */
#define WM8904_FLL_OSC_ENA                      0x0002
#define WM8904_FLL_ENA_Pos                      0  /* FLL_ENA */
#define WM8904_FLL_ENA                          0x0001

/*
 * R117 (0x75) - FLL Control 2
 */
#define WM8904_FLL_OUTDIV_Pos                   8  /* FLL_OUTDIV - [13:8] */
#define WM8904_FLL_OUTDIV_Msk                   0x3F00
#define WM8904_FLL_OUTDIV(Value)                (WM8904_FLL_OUTDIV_Msk & ((Value) << WM8904_FLL_OUTDIV_Pos))
#define WM8904_FLL_CTRL_RATE_Pos                4  /* FLL_CTRL_RATE - [6:4] */
#define WM8904_FLL_CTRL_RATE_Msk                0x0070
#define WM8904_FLL_CTRL_RATE(Value)             (WM8904_FLL_CTRL_RATE_Msk & ((Value) << WM8904_FLL_CTRL_RATE_Pos))
#define WM8904_FLL_FRATIO_Pos                   0  /* FLL_FRATIO - [2:0] */
#define WM8904_FLL_FRATIO_Msk                   0x0007
#define WM8904_FLL_FRATIO(Value)                (WM8904_FLL_FRATIO_Msk & ((Value) << WM8904_FLL_FRATIO_Pos))

/*
 * R118 (0x76) - FLL Control 3
 */
#define WM8904_FLL_K_Pos                        0  /* FLL_K - [15:0] */
#define WM8904_FLL_K_Msk                        0xFFFF
#define WM8904_FLL_K(Value)                     (WM8904_FLL_K_Msk & ((Value) << WM8904_FLL_K_Pos))

/*
 * R119 (0x77) - FLL Control 4
 */
#define WM8904_FLL_N_Pos                        5  /* FLL_N - [14:5] */
#define WM8904_FLL_N_Msk                        0x7FE0
#define WM8904_FLL_N(Value)                     (WM8904_FLL_N_Msk & ((Value) << WM8904_FLL_N_Pos))
#define WM8904_FLL_GAIN_Pos                     0  /* FLL_GAIN - [3:0] */
#define WM8904_FLL_GAIN_Msk                     0x000F
#define WM8904_FLL_GAIN(Value)                  (WM8904_FLL_GAIN_Msk & ((Value) << WM8904_FLL_GAIN_Pos))

/*
 * R120 (0x78) - FLL Control 5
 */
#define WM8904_FLL_CLK_REF_DIV_Pos              3  /* FLL_CLK_REF_DIV - [4:3] */
#define WM8904_FLL_CLK_REF_DIV_Msk              0x0018
#define WM8904_FLL_CLK_REF_DIV(Value)           (WM8904_FLL_CLK_REF_DIV_Msk & ((Value) << WM8904_FLL_CLK_REF_DIV_Pos))
#define WM8904_FLL_CLK_REF_SRC_Pos              0  /* FLL_CLK_REF_SRC - [1:0] */
#define WM8904_FLL_CLK_REF_SRC_Msk              0x0003
#define WM8904_FLL_CLK_REF_SRC(Value)           (WM8904_FLL_CLK_REF_SRC_Msk & ((Value) << WM8904_FLL_CLK_REF_SRC_Pos))

/*
 * R121 (0x79) - GPIO Control 1
 */
#define WM8904_GPIO1_PU_Pos                     5  /* GPIO1_PU */
#define WM8904_GPIO1_PU                         0x0020
#define WM8904_GPIO1_PD_Pos                     4  /* GPIO1_PD */
#define WM8904_GPIO1_PD                         0x0010
#define WM8904_GPIO1_SEL_Pos                    0  /* GPIO1_SEL - [3:0] */
#define WM8904_GPIO1_SEL_Msk                    0x000F
#define WM8904_GPIO1_SEL(Value)                 (WM8904_GPIO1_SEL_Msk & ((Value) << WM8904_GPIO1_SEL_Pos))

/*
 * R122 (0x7A) - GPIO Control 2
 */
#define WM8904_GPIO2_PU_Pos                     5  /* GPIO2_PU */
#define WM8904_GPIO2_PU                         0x0020
#define WM8904_GPIO2_PD_Pos                     4  /* GPIO2_PD */
#define WM8904_GPIO2_PD                         0x0010
#define WM8904_GPIO2_SEL_Pos                    0  /* GPIO2_SEL - [3:0] */
#define WM8904_GPIO2_SEL_Msk                    0x000F
#define WM8904_GPIO2_SEL(Value)                 (WM8904_GPIO2_SEL_Msk & ((Value) << WM8904_GPIO2_SEL_Pos))

/*
 * R123 (0x7B) - GPIO Control 3
 */
#define WM8904_GPIO3_PU_Pos                     5  /* GPIO3_PU */
#define WM8904_GPIO3_PU                         0x0020
#define WM8904_GPIO3_PD_Pos                     4  /* GPIO3_PD */
#define WM8904_GPIO3_PD                         0x0010
#define WM8904_GPIO3_SEL_Pos                    0  /* GPIO3_SEL - [3:0] */
#define WM8904_GPIO3_SEL_Msk                    0x000F
#define WM8904_GPIO3_SEL(Value)                 (WM8904_GPIO3_SEL_Msk & ((Value) << WM8904_GPIO3_SEL_Pos))

/*
 * R124 (0x7C) - GPIO Control 4
 */
#define WM8904_GPI7_ENA_Pos                     9  /* GPI7_ENA */
#define WM8904_GPI7_ENA                         0x0200
#define WM8904_GPI8_ENA_Pos                     8  /* GPI8_ENA */
#define WM8904_GPI8_ENA                         0x0100
#define WM8904_GPIO_BCLK_MODE_ENA_Pos           7  /* GPIO_BCLK_MODE_ENA */
#define WM8904_GPIO_BCLK_MODE_ENA               0x0080
#define WM8904_GPIO_BCLK_SEL_Pos                0  /* GPIO_BCLK_SEL - [3:0] */
#define WM8904_GPIO_BCLK_SEL_Msk                0x000F
#define WM8904_GPIO_BCLK_SEL(Value)             (WM8904_GPIO_BCLK_SEL_Msk & ((Value) << WM8904_GPIO_BCLK_SEL_Pos))

/*
 * R126 (0x7E) - Digital Pulls
 */
#define WM8904_MCLK_PU_Pos                      7  /* MCLK_PU */
#define WM8904_MCLK_PU                          0x0080
#define WM8904_MCLK_PD_Pos                      6  /* MCLK_PD */
#define WM8904_MCLK_PD                          0x0040
#define WM8904_DACDAT_PU_Pos                    5  /* DACDAT_PU */
#define WM8904_DACDAT_PU                        0x0020
#define WM8904_DACDAT_PD_Pos                    4  /* DACDAT_PD */
#define WM8904_DACDAT_PD                        0x0010
#define WM8904_LRCLK_PU_Pos                     3  /* LRCLK_PU */
#define WM8904_LRCLK_PU                         0x0008
#define WM8904_LRCLK_PD_Pos                     2  /* LRCLK_PD */
#define WM8904_LRCLK_PD                         0x0004
#define WM8904_BCLK_PU_Pos                      1  /* BCLK_PU */
#define WM8904_BCLK_PU                          0x0002
#define WM8904_BCLK_PD_Pos                      0  /* BCLK_PD */
#define WM8904_BCLK_PD                          0x0001

/*
 * R127 (0x7F) - Interrupt Status
 */
#define WM8904_IRQ_Pos                          10  /* IRQ */
#define WM8904_IRQ                              0x0400
#define WM8904_GPIO_BCLK_EINT_Pos               9  /* GPIO_BCLK_EINT */
#define WM8904_GPIO_BCLK_EINT                   0x0200
#define WM8904_WSEQ_EINT_Pos                    8  /* WSEQ_EINT */
#define WM8904_WSEQ_EINT                        0x0100
#define WM8904_GPIO3_EINT_Pos                   7  /* GPIO3_EINT */
#define WM8904_GPIO3_EINT                       0x0080
#define WM8904_GPIO2_EINT_Pos                   6  /* GPIO2_EINT */
#define WM8904_GPIO2_EINT                       0x0040
#define WM8904_GPIO1_EINT_Pos                   5  /* GPIO1_EINT */
#define WM8904_GPIO1_EINT                       0x0020
#define WM8904_GPI8_EINT_Pos                    4  /* GPI8_EINT */
#define WM8904_GPI8_EINT                        0x0010
#define WM8904_GPI7_EINT_Pos                    3  /* GPI7_EINT */
#define WM8904_GPI7_EINT                        0x0008
#define WM8904_FLL_LOCK_EINT_Pos                2  /* FLL_LOCK_EINT */
#define WM8904_FLL_LOCK_EINT                    0x0004
#define WM8904_MIC_SHRT_EINT_Pos                1  /* MIC_SHRT_EINT */
#define WM8904_MIC_SHRT_EINT                    0x0002
#define WM8904_MIC_DET_EINT_Pos                 0  /* MIC_DET_EINT */
#define WM8904_MIC_DET_EINT                     0x0001

/*
 * R128 (0x80) - Interrupt Status Mask
 */
#define WM8904_IM_GPIO_BCLK_EINT_Pos            9  /* IM_GPIO_BCLK_EINT */
#define WM8904_IM_GPIO_BCLK_EINT                0x0200
#define WM8904_IM_WSEQ_EINT_Pos                 8  /* IM_WSEQ_EINT */
#define WM8904_IM_WSEQ_EINT                     0x0100
#define WM8904_IM_GPIO3_EINT_Pos                7  /* IM_GPIO3_EINT */
#define WM8904_IM_GPIO3_EINT                    0x0080
#define WM8904_IM_GPIO2_EINT_Pos                6  /* IM_GPIO2_EINT */
#define WM8904_IM_GPIO2_EINT                    0x0040
#define WM8904_IM_GPIO1_EINT_Pos                5  /* IM_GPIO1_EINT */
#define WM8904_IM_GPIO1_EINT                    0x0020
#define WM8904_IM_GPI8_EINT_Pos                 4  /* IM_GPI8_EINT */
#define WM8904_IM_GPI8_EINT                     0x0010
#define WM8904_IM_GPI7_EINT_Pos                 3  /* IM_GPI7_EINT */
#define WM8904_IM_GPI7_EINT                     0x0008
#define WM8904_IM_FLL_LOCK_EINT_Pos             2  /* IM_FLL_LOCK_EINT */
#define WM8904_IM_FLL_LOCK_EINT                 0x0004
#define WM8904_IM_MIC_SHRT_EINT_Pos             1  /* IM_MIC_SHRT_EINT */
#define WM8904_IM_MIC_SHRT_EINT                 0x0002
#define WM8904_IM_MIC_DET_EINT_Pos              0  /* IM_MIC_DET_EINT */
#define WM8904_IM_MIC_DET_EINT                  0x0001

/*
 * R129 (0x81) - Interrupt Polarity
 */
#define WM8904_GPIO_BCLK_EINT_POL_Pos           9  /* GPIO_BCLK_EINT_POL */
#define WM8904_GPIO_BCLK_EINT_POL               0x0200
#define WM8904_WSEQ_EINT_POL_Pos                8  /* WSEQ_EINT_POL */
#define WM8904_WSEQ_EINT_POL                    0x0100
#define WM8904_GPIO3_EINT_POL_Pos               7  /* GPIO3_EINT_POL */
#define WM8904_GPIO3_EINT_POL                   0x0080
#define WM8904_GPIO2_EINT_POL_Pos               6  /* GPIO2_EINT_POL */
#define WM8904_GPIO2_EINT_POL                   0x0040
#define WM8904_GPIO1_EINT_POL_Pos               5  /* GPIO1_EINT_POL */
#define WM8904_GPIO1_EINT_POL                   0x0020
#define WM8904_GPI8_EINT_POL_Pos                4  /* GPI8_EINT_POL */
#define WM8904_GPI8_EINT_POL                    0x0010
#define WM8904_GPI7_EINT_POL_Pos                3  /* GPI7_EINT_POL */
#define WM8904_GPI7_EINT_POL                    0x0008
#define WM8904_FLL_LOCK_EINT_POL_Pos            2  /* FLL_LOCK_EINT_POL */
#define WM8904_FLL_LOCK_EINT_POL                0x0004
#define WM8904_MIC_SHRT_EINT_POL_Pos            1  /* MIC_SHRT_EINT_POL */
#define WM8904_MIC_SHRT_EINT_POL                0x0002
#define WM8904_MIC_DET_EINT_POL_Pos             0  /* MIC_DET_EINT_POL */
#define WM8904_MIC_DET_EINT_POL                 0x0001

/*
 * R130 (0x82) - Interrupt Debounce
 */
#define WM8904_GPIO_BCLK_EINT_DB_Pos            9  /* GPIO_BCLK_EINT_DB */
#define WM8904_GPIO_BCLK_EINT_DB                0x0200
#define WM8904_WSEQ_EINT_DB_Pos                 8  /* WSEQ_EINT_DB */
#define WM8904_WSEQ_EINT_DB                     0x0100
#define WM8904_GPIO3_EINT_DB_Pos                7  /* GPIO3_EINT_DB */
#define WM8904_GPIO3_EINT_DB                    0x0080
#define WM8904_GPIO2_EINT_DB_Pos                6  /* GPIO2_EINT_DB */
#define WM8904_GPIO2_EINT_DB                    0x0040
#define WM8904_GPIO1_EINT_DB_Pos                5  /* GPIO1_EINT_DB */
#define WM8904_GPIO1_EINT_DB                    0x0020
#define WM8904_GPI8_EINT_DB_Pos                 4  /* GPI8_EINT_DB */
#define WM8904_GPI8_EINT_DB                     0x0010
#define WM8904_GPI7_EINT_DB_Pos                 3  /* GPI7_EINT_DB */
#define WM8904_GPI7_EINT_DB                     0x0008
#define WM8904_FLL_LOCK_EINT_DB_Pos             2  /* FLL_LOCK_EINT_DB */
#define WM8904_FLL_LOCK_EINT_DB                 0x0004
#define WM8904_MIC_SHRT_EINT_DB_Pos             1  /* MIC_SHRT_EINT_DB */
#define WM8904_MIC_SHRT_EINT_DB                 0x0002
#define WM8904_MIC_DET_EINT_DB_Pos              0  /* MIC_DET_EINT_DB */
#define WM8904_MIC_DET_EINT_DB                  0x0001

/*
 * R134 (0x86) - EQ1
 */
#define WM8904_EQ_ENA_Pos                       0  /* EQ_ENA */
#define WM8904_EQ_ENA                           0x0001

/*
 * R135 (0x87) - EQ2
 */
#define WM8904_EQ_B1_GAIN_Pos                   0  /* EQ_B1_GAIN - [4:0] */
#define WM8904_EQ_B1_GAIN_Msk                   0x001F
#define WM8904_EQ_B1_GAIN(Value)                (WM8904_EQ_B1_GAIN_Msk & ((Value) << WM8904_EQ_B1_GAIN_Pos))

/*
 * R136 (0x88) - EQ3
 */
#define WM8904_EQ_B2_GAIN_Pos                   0  /* EQ_B2_GAIN - [4:0] */
#define WM8904_EQ_B2_GAIN_Msk                   0x001F
#define WM8904_EQ_B2_GAIN(Value)                (WM8904_EQ_B2_GAIN_Msk & ((Value) << WM8904_EQ_B2_GAIN_Pos))

/*
 * R137 (0x89) - EQ4
 */
#define WM8904_EQ_B3_GAIN_Pos                   0  /* EQ_B3_GAIN - [4:0] */
#define WM8904_EQ_B3_GAIN_Msk                   0x001F
#define WM8904_EQ_B3_GAIN(Value)                (WM8904_EQ_B3_GAIN_Msk & ((Value) << WM8904_EQ_B3_GAIN_Pos))

/*
 * R138 (0x8A) - EQ5
 */
#define WM8904_EQ_B4_GAIN_Pos                   0  /* EQ_B4_GAIN - [4:0] */
#define WM8904_EQ_B4_GAIN_Msk                   0x001F
#define WM8904_EQ_B4_GAIN(Value)                (WM8904_EQ_B4_GAIN_Msk & ((Value) << WM8904_EQ_B4_GAIN_Pos))

/*
 * R139 (0x8B) - EQ6
 */
#define WM8904_EQ_B5_GAIN_Pos                   0  /* EQ_B5_GAIN - [4:0] */
#define WM8904_EQ_B5_GAIN_Msk                   0x001F
#define WM8904_EQ_B5_GAIN(Value)                (WM8904_EQ_B5_GAIN_Msk & ((Value) << WM8904_EQ_B5_GAIN_Pos))

/*
 * R140 (0x8C) - EQ7
 */
#define WM8904_EQ_B1_A_Pos                      0  /* EQ_B1_A - [15:0] */
#define WM8904_EQ_B1_A_Msk                      0xFFFF
#define WM8904_EQ_B1_A(Value)                   (WM8904_EQ_B1_A_Msk & ((Value) << WM8904_EQ_B1_A_Pos))

/*
 * R141 (0x8D) - EQ8
 */
#define WM8904_EQ_B1_B_Pos                      0  /* EQ_B1_B - [15:0] */
#define WM8904_EQ_B1_B_Msk                      0xFFFF
#define WM8904_EQ_B1_B(Value)                   (WM8904_EQ_B1_B_Msk & ((Value) << WM8904_EQ_B1_B_Pos))

/*
 * R142 (0x8E) - EQ9
 */
#define WM8904_EQ_B1_PG_Pos                     0  /* EQ_B1_PG - [15:0] */
#define WM8904_EQ_B1_PG_Msk                     0xFFFF
#define WM8904_EQ_B1_PG(Value)                  (WM8904_EQ_B1_PG_Msk & ((Value) << WM8904_EQ_B1_PG_Pos))

/*
 * R143 (0x8F) - EQ10
 */
#define WM8904_EQ_B2_A_Pos                      0  /* EQ_B2_A - [15:0] */
#define WM8904_EQ_B2_A_Msk                      0xFFFF
#define WM8904_EQ_B2_A(Value)                   (WM8904_EQ_B2_A_Msk & ((Value) << WM8904_EQ_B2_A_Pos))

/*
 * R144 (0x90) - EQ11
 */
#define WM8904_EQ_B2_B_Pos                      0  /* EQ_B2_B - [15:0] */
#define WM8904_EQ_B2_B_Msk                      0xFFFF
#define WM8904_EQ_B2_B(Value)                   (WM8904_EQ_B2_B_Msk & ((Value) << WM8904_EQ_B2_B_Pos))

/*
 * R145 (0x91) - EQ12
 */
#define WM8904_EQ_B2_C_Pos                      0  /* EQ_B2_C - [15:0] */
#define WM8904_EQ_B2_C_Msk                      0xFFFF
#define WM8904_EQ_B2_C(Value)                   (WM8904_EQ_B2_C_Msk & ((Value) << WM8904_EQ_B2_C_Pos))

/*
 * R146 (0x92) - EQ13
 */
#define WM8904_EQ_B2_PG_Pos                     0  /* EQ_B2_PG - [15:0] */
#define WM8904_EQ_B2_PG_Msk                     0xFFFF
#define WM8904_EQ_B2_PG(Value)                  (WM8904_EQ_B2_PG_Msk & ((Value) << WM8904_EQ_B2_PG_Pos))

/*
 * R147 (0x93) - EQ14
 */
#define WM8904_EQ_B3_A_Pos                      0  /* EQ_B3_A - [15:0] */
#define WM8904_EQ_B3_A_Msk                      0xFFFF
#define WM8904_EQ_B3_A(Value)                   (WM8904_EQ_B3_A_Msk & ((Value) << WM8904_EQ_B3_A_Pos))

/*
 * R148 (0x94) - EQ15
 */
#define WM8904_EQ_B3_B_Pos                      0  /* EQ_B3_B - [15:0] */
#define WM8904_EQ_B3_B_Msk                      0xFFFF
#define WM8904_EQ_B3_B(Value)                   (WM8904_EQ_B3_B_Msk & ((Value) << WM8904_EQ_B3_B_Pos))

/*
 * R149 (0x95) - EQ16
 */
#define WM8904_EQ_B3_C_Pos                      0  /* EQ_B3_C - [15:0] */
#define WM8904_EQ_B3_C_Msk                      0xFFFF
#define WM8904_EQ_B3_C(Value)                   (WM8904_EQ_B3_C_Msk & ((Value) << WM8904_EQ_B3_C_Pos))

/*
 * R150 (0x96) - EQ17
 */
#define WM8904_EQ_B3_PG_Pos                     0  /* EQ_B3_PG - [15:0] */
#define WM8904_EQ_B3_PG_Msk                     0xFFFF
#define WM8904_EQ_B3_PG(Value)                  (WM8904_EQ_B3_PG_Msk & ((Value) << WM8904_EQ_B3_PG_Pos))

/*
 * R151 (0x97) - EQ18
 */
#define WM8904_EQ_B4_A_Pos                      0  /* EQ_B4_A - [15:0] */
#define WM8904_EQ_B4_A_Msk                      0xFFFF
#define WM8904_EQ_B4_A(Value)                   (WM8904_EQ_B4_A_Msk & ((Value) << WM8904_EQ_B4_A_Pos))

/*
 * R152 (0x98) - EQ19
 */
#define WM8904_EQ_B4_B_Pos                      0  /* EQ_B4_B - [15:0] */
#define WM8904_EQ_B4_B_Msk                      0xFFFF
#define WM8904_EQ_B4_B(Value)                   (WM8904_EQ_B4_B_Msk & ((Value) << WM8904_EQ_B4_B_Pos))

/*
 * R153 (0x99) - EQ20
 */
#define WM8904_EQ_B4_C_Pos                      0  /* EQ_B4_C - [15:0] */
#define WM8904_EQ_B4_C_Msk                      0xFFFF
#define WM8904_EQ_B4_C(Value)                   (WM8904_EQ_B4_C_Msk & ((Value) << WM8904_EQ_B4_C_Pos))

/*
 * R154 (0x9A) - EQ21
 */
#define WM8904_EQ_B4_PG_Pos                     0  /* EQ_B4_PG - [15:0] */
#define WM8904_EQ_B4_PG_Msk                     0xFFFF
#define WM8904_EQ_B4_PG(Value)                  (WM8904_EQ_B4_PG_Msk & ((Value) << WM8904_EQ_B4_PG_Pos))

/*
 * R155 (0x9B) - EQ22
 */
#define WM8904_EQ_B5_A_Pos                      0  /* EQ_B5_A - [15:0] */
#define WM8904_EQ_B5_A_Msk                      0xFFFF
#define WM8904_EQ_B5_A(Value)                   (WM8904_EQ_B5_A_Msk & ((Value) << WM8904_EQ_B5_A_Pos))

/*
 * R156 (0x9C) - EQ23
 */
#define WM8904_EQ_B5_B_Pos                      0  /* EQ_B5_B - [15:0] */
#define WM8904_EQ_B5_B_Msk                      0xFFFF
#define WM8904_EQ_B5_B(Value)                   (WM8904_EQ_B5_B_Msk & ((Value) << WM8904_EQ_B5_B_Pos))

/*
 * R157 (0x9D) - EQ24
 */
#define WM8904_EQ_B5_PG_Pos                     0  /* EQ_B5_PG - [15:0] */
#define WM8904_EQ_B5_PG_Msk                     0xFFFF
#define WM8904_EQ_B5_PG(Value)                  (WM8904_EQ_B5_PG_Msk & ((Value) << WM8904_EQ_B5_PG_Pos))

/*
 * R198 (0xC6) - ADC Test 0
 */
#define WM8904_ADC_128_OSR_TST_MODE_Pos         2  /* ADC_128_OSR_TST_MODE */
#define WM8904_ADC_128_OSR_TST_MODE             0x0004
#define WM8904_ADC_BIASX1P5_Pos                 0  /* ADC_BIASX1P5 */
#define WM8904_ADC_BIASX1P5                     0x0001

/*
 * R247 (0xF7) - FLL NCO Test 0
 */
#define WM8904_FLL_FRC_NCO_Pos                  0  /* FLL_FRC_NCO */
#define WM8904_FLL_FRC_NCO                      0x0001

/*
 * R248 (0xF8) - FLL NCO Test 1
 */
#define WM8904_FLL_FRC_NCO_VAL_Pos              0  /* FLL_FRC_NCO_VAL - [5:0] */
#define WM8904_FLL_FRC_NCO_VAL_Msk              0x003F
#define WM8904_FLL_FRC_NCO_VAL(Value)           (WM8904_FLL_FRC_NCO_VAL_Msk & ((Value) << WM8904_FLL_FRC_NCO_VAL_Pos))


void wm8904_write_register(uint8_t uc_register_address, uint16_t us_data);
uint16_t wm8904_read_register(uint8_t uc_register_address);
uint32_t wm8904_twi_init(void);

//@}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \page sam_wm8904_quickstart Quick start guide for the SAM WM8904 module
 *
 * This is the quick start guide for the \ref sam_components_audio_codec_wm8904_group
 * "WM8904 Audio Codec", with step-by-step instructions on how to configure
 * and use the driver in a selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section wm8904_use_cases WM8904 use cases
 * - \ref wm8904_basic_use_case Basic use case - Configurate the WM8904 to LINEIN
 * and Headphone out mode
 *
 * \section wm8904_basic_use_case Basic use case - Configurate the WM8904 to LINEIN
 * and Headphone out mode
 * In this use case, the WM8904 module is configured to analog LINEIN to ADC with
 * I2S audio output. I2S audio input to DAC with headphone analog output.
 *
 * \section wm8904_basic_use_case_setup Setup
 *
 * \subsection wm8904_basic_use_case_setup_prereq Prerequisites
 * -# \ref sam_drivers_pio_group "PIO Driver (pio)"
 *
 * \subsection wm8904_basic_use_case_setup_flow Workflow
 * The following function needs to be added to the user application
 * -# Initialize the TWI interface.
 * \code wm8904_twi_init(); \endcode
 * -# reset the WM8904.
 * \code
	wm8904_write_register(WM8904_SW_RESET_AND_ID, 0xFFFF);
	data = wm8904_read_register(WM8904_SW_RESET_AND_ID);
	if(data != 0x8904) {
		printf("WM8904 not found!\n\r");
		while(1);
	}
\endcode
 * -# Configure the WM8904 codec.
 *
 */

#endif