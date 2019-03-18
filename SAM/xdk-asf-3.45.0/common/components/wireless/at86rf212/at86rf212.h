/**
 * \file
 *
 * \brief Driver for AT86RF212 transceiver.
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

/* Prevent double inclusion */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#ifndef AT86RF212_H
#define AT86RF212_H

#include "conf_at86rfx.h"


/** Parameter definitions */

/** Important parameters. */
#define TRX_SUPPORTED_CHANNELS   (0x000007FF)	/* TRX Parameter: Bit mask of transceiver supported channels */
#define TRX_SUPPORTED_CHANNELS_CHINA   (0x0000000F)	/* TRX Parameter: Bit mask of transceiver supported channels when
							   operating in the People's Republic of China */
#define TX_PWR_TOLERANCE   (0x80)	/* TRX Parameter: Tolerance of the phyTransmitPower PIB attribute.
					   This is encoded into the two MSBits of the attribute,
					   and is effectively read-only.
					 */

/** Typical timing values. */
#define RST_PULSE_WIDTH_NS                (625)	/* TRX Parameter: t10 */
#define P_ON_TO_CLKM_AVAILABLE_TYP_US     (330)	/* TRX Parameter: tTR1 typical value */
#define SLEEP_TO_TRX_OFF_TYP_US           (380)	/* TRX Parameter: tTR2 typical value */
#define TRX_OFF_TO_SLEEP_TIME_CLKM_CYCLES (35)	/* TRX Parameter: tTR3 */
#define TRX_OFF_TO_PLL_ON_TIME_US         (200)	/* TRX Parameter: tTR4 */
#define TRX_IRQ_DELAY_US                  (9)	/* TRX Parameter: tIRQ */
#define RSSI_BASE_VAL_BPSK_20_DBM         (-100)	/* TRX Parameter: RSSI_BASE_VAL */
#define RSSI_BASE_VAL_BPSK_40_DBM         (-100)	/* TRX Parameter: RSSI_BASE_VAL */
#define RSSI_BASE_VAL_OQPSK_100_DBM       (-98)	/* TRX Parameter: RSSI_BASE_VAL */
#define RSSI_BASE_VAL_OQPSK_SIN_250_DBM   (-98)	/* TRX Parameter: RSSI_BASE_VAL */
#define RSSI_BASE_VAL_OQPSK_RC_250_DBM    (-97)	/* TRX Parameter: RSSI_BASE_VAL */
#define CCA_DETECTION_TIME_SYMBOL         (8)	/* TRX Parameter: tTR28 */
#define P_ON_TO_CLKM_AVAILABLE_MAX_US   (1000)	/* TRX Parameter: tTR1 max. value */
#define SLEEP_TO_TRX_OFF_MAX_US   (1000)	/* TRX Parameter: tTR2 max. value */
#define T_OCT_US   (32)	/* TRX Parameter: Duration of an octet for 250kb/s OQPSK mode */
#define T_SYM_US   (16)	/* TRX Parameter: Duration of an symbol for 250kb/s OQPSK mode */
#define PRE_TX_DURATION_US   (32)	/* TRX Parameter: 16 us processing delay + 16 us software handling duration */
#define CCA_PRE_START_DURATION_US   (20)	/* TRX Parameter: Duration before start of CCA */
#define CCA_PROCESS_TIME_SYM   (1)	/* TRX Parameter: CCA processing time in symbols */
#define CCA_PREPARATION_DURATION_US   (50)	/* TRX Parameter: Preparation time for CCA */
#define CCA_DURATION_SYM   (CCA_DETECTION_TIME_SYMBOL + CCA_PROCESS_TIME_SYM)	/* TRX Parameter: Complete CCA Duration in symbols */
#define RST_PULSE_WIDTH_US   ((RST_PULSE_WIDTH_NS + 999) / 1000)	/* TRX Parameter: Round up RST_PULSE_WIDTH_NS value to µs */

/** Register addresses */

/** Base address for transceiver **/
#define REGISTER_BASE_ADDR    (0x00)

/** Base address for transceiver AES address space **/
#define AES_BASE_ADDR   (0x80)

/** Offset for register AES_CTRL */
#define RG_AES_CTRL   (0x03)

/** Offset for register AES_CTRL_MIRROR */
#define RG_AES_CTRL_MIRROR   (0x14)

/** Offset for register AES_STATE_KEY_0 */
#define RG_AES_STATE_KEY_0   (0x04)

/** Offset for register AES_STATUS */
#define RG_AES_STATUS   (0x02)

/** Offset for register ANT_DIV */
#define RG_ANT_DIV   (0x0D)

/** Offset for register BATMON */
#define RG_BATMON   (0x11)

/** Offset for register CCA_THRES */
#define RG_CCA_THRES   (0x09)

/** Offset for register CC_CTRL_0 */
#define RG_CC_CTRL_0   (0x13)

/** Offset for register CC_CTRL_1 */
#define RG_CC_CTRL_1   (0x14)

/** Offset for register CSMA_BE */
#define RG_CSMA_BE   (0x2F)

/** Offset for register CSMA_SEED_0 */
#define RG_CSMA_SEED_0   (0x2D)

/** Offset for register CSMA_SEED_1 */
#define RG_CSMA_SEED_1   (0x2E)

/** Offset for register FTN_CTRL */
#define RG_FTN_CTRL   (0x18)

/** Offset for register IEEE_ADDR_0 */
#define RG_IEEE_ADDR_0   (0x24)

/** Offset for register IEEE_ADDR_1 */
#define RG_IEEE_ADDR_1   (0x25)

/** Offset for register IEEE_ADDR_2 */
#define RG_IEEE_ADDR_2   (0x26)

/** Offset for register IEEE_ADDR_3 */
#define RG_IEEE_ADDR_3   (0x27)

/** Offset for register IEEE_ADDR_4 */
#define RG_IEEE_ADDR_4   (0x28)

/** Offset for register IEEE_ADDR_5 */
#define RG_IEEE_ADDR_5   (0x29)

/** Offset for register IEEE_ADDR_6 */
#define RG_IEEE_ADDR_6   (0x2A)

/** Offset for register IEEE_ADDR_7 */
#define RG_IEEE_ADDR_7   (0x2B)

/** Offset for register IRQ_MASK */
#define RG_IRQ_MASK   (0x0E)

/** Offset for register IRQ_STATUS */
#define RG_IRQ_STATUS   (0x0F)

/** Offset for register MAN_ID_0 */
#define RG_MAN_ID_0   (0x1E)

/** Offset for register MAN_ID_1 */
#define RG_MAN_ID_1   (0x1F)

/** Offset for register PAN_ID_0 */
#define RG_PAN_ID_0   (0x22)

/** Offset for register PAN_ID_1 */
#define RG_PAN_ID_1   (0x23)

/** Offset for register PART_NUM */
#define RG_PART_NUM   (0x1C)

/** Offset for register PHY_CC_CCA */
#define RG_PHY_CC_CCA   (0x08)

/** Offset for register PHY_ED_LEVEL */
#define RG_PHY_ED_LEVEL   (0x07)

/** Offset for register PHY_RSSI */
#define RG_PHY_RSSI   (0x06)

/** Offset for register PHY_TX_PWR */
#define RG_PHY_TX_PWR   (0x05)

/** Offset for register PLL_CF */
#define RG_PLL_CF   (0x1A)

/** Offset for register PLL_DCU */
#define RG_PLL_DCU   (0x1B)

/** Offset for register RF_CTRL_0 */
#define RG_RF_CTRL_0   (0x16)

/** Offset for register RF_CTRL_1 */
#define RG_RF_CTRL_1   (0x19)

/** Offset for register RX_CTRL */
#define RG_RX_CTRL   (0x0A)

/** Offset for register RX_SYN */
#define RG_RX_SYN   (0x15)

/** Offset for register SFD_VALUE */
#define RG_SFD_VALUE   (0x0B)

/** Offset for register SHORT_ADDR_0 */
#define RG_SHORT_ADDR_0   (0x20)

/** Offset for register SHORT_ADDR_1 */
#define RG_SHORT_ADDR_1   (0x21)

/** Offset for register TRX_CTRL_0 */
#define RG_TRX_CTRL_0   (0x03)

/** Offset for register TRX_CTRL_1 */
#define RG_TRX_CTRL_1   (0x04)

/** Offset for register TRX_CTRL_2 */
#define RG_TRX_CTRL_2   (0x0C)

/** Offset for register TRX_STATE */
#define RG_TRX_STATE   (0x02)

/** Offset for register TRX_STATUS */
#define RG_TRX_STATUS   (0x01)

/** Offset for register VERSION_NUM */
#define RG_VERSION_NUM   (0x1D)

/** Offset for register VREG_CTRL */
#define RG_VREG_CTRL   (0x10)

/** Offset for register XAH_CTRL_0 */
#define RG_XAH_CTRL_0   (0x2C)

/** Offset for register XAH_CTRL_1 */
#define RG_XAH_CTRL_1   (0x17)

/** Offset for register XOSC_CTRL */
#define RG_XOSC_CTRL   (0x12)


/** Sub-register access */

/** Access parameters for sub-register AACK_ACK_TIME in register @ref RG_XAH_CTRL_1 */
#define SR_AACK_ACK_TIME   0x17, 0x04, 2

/** Access parameters for sub-register AACK_DIS_ACK in register @ref RG_CSMA_SEED_1 */
#define SR_AACK_DIS_ACK   0x2E, 0x10, 4

/** Access parameters for sub-register AACK_FLTR_RES_FT in register @ref RG_XAH_CTRL_1 */
#define SR_AACK_FLTR_RES_FT   0x17, 0x20, 5

/** Access parameters for sub-register AACK_FVN_MODE in register @ref RG_CSMA_SEED_1 */
#define SR_AACK_FVN_MODE   0x2E, 0xC0, 6

/** Access parameters for sub-register AACK_I_AM_COORD in register @ref RG_CSMA_SEED_1 */
#define SR_AACK_I_AM_COORD   0x2E, 0x08, 3

/** Access parameters for sub-register AACK_PROM_MODE in register @ref RG_XAH_CTRL_1 */
#define SR_AACK_PROM_MODE   0x17, 0x02, 1

/** Access parameters for sub-register AACK_SET_PD in register @ref RG_CSMA_SEED_1 */
#define SR_AACK_SET_PD   0x2E, 0x20, 5

/** Access parameters for sub-register AACK_UPLD_RES_FT in register @ref RG_XAH_CTRL_1 */
#define SR_AACK_UPLD_RES_FT   0x17, 0x10, 4

/** Access parameters for sub-register AES_DIR in register @ref RG_AES_CTRL */
#define SR_AES_DIR   0x03, 0x08, 3

/** Access parameters for sub-register AES_DONE in register @ref RG_AES_STATUS */
#define SR_AES_DONE   0x02, 0x01, 0

/** Access parameters for sub-register AES_ER in register @ref RG_AES_STATUS */
#define SR_AES_ER   0x02, 0x80, 7

/** Access parameters for sub-register AES_MODE in register @ref RG_AES_CTRL */
#define SR_AES_MODE   0x03, 0x70, 4

/** Access parameters for sub-register AES_REQUEST in register @ref RG_AES_CTRL */
#define SR_AES_REQUEST   0x03, 0x80, 7

/** Access parameters for sub-register ANT_CTRL in register @ref RG_ANT_DIV */
#define SR_ANT_CTRL   0x0D, 0x03, 0

/** Access parameters for sub-register ANT_EXT_SW_EN in register @ref RG_ANT_DIV */
#define SR_ANT_EXT_SW_EN   0x0D, 0x04, 2

/** Access parameters for sub-register AVDD_OK in register @ref RG_VREG_CTRL */
#define SR_AVDD_OK   0x10, 0x40, 6

/** Access parameters for sub-register AVREG_EXT in register @ref RG_VREG_CTRL */
#define SR_AVREG_EXT   0x10, 0x80, 7

/** Access parameters for sub-register BATMON_HR in register @ref RG_BATMON */
#define SR_BATMON_HR   0x11, 0x10, 4

/** Access parameters for sub-register BATMON_OK in register @ref RG_BATMON */
#define SR_BATMON_OK   0x11, 0x20, 5

/** Access parameters for sub-register BATMON_VTH in register @ref RG_BATMON */
#define SR_BATMON_VTH   0x11, 0x0F, 0

/** Access parameters for sub-register BPSK_OQPSK in register @ref RG_TRX_CTRL_2 */
#define SR_BPSK_OQPSK   0x0C, 0x08, 3

/** Access parameters for sub-register CCA_DONE in register @ref RG_TRX_STATUS */
#define SR_CCA_DONE   0x01, 0x80, 7

/** Access parameters for sub-register CCA_ED_THRES in register @ref RG_CCA_THRES */
#define SR_CCA_ED_THRES   0x09, 0x0F, 0

/** Access parameters for sub-register CCA_MODE in register @ref RG_PHY_CC_CCA */
#define SR_CCA_MODE   0x08, 0x60, 5

/** Access parameters for sub-register CCA_REQUEST in register @ref RG_PHY_CC_CCA */
#define SR_CCA_REQUEST   0x08, 0x80, 7

/** Access parameters for sub-register CCA_STATUS in register @ref RG_TRX_STATUS */
#define SR_CCA_STATUS   0x01, 0x40, 6

/** Access parameters for sub-register CC_BAND in register @ref RG_CC_CTRL_1 */
#define SR_CC_BAND   0x14, 0x07, 0

/** Access parameters for sub-register CC_NUMBER in register @ref RG_CC_CTRL_0 */
#define SR_CC_NUMBER   0x13, 0xFF, 0

/** Access parameters for sub-register CHANNEL in register @ref RG_PHY_CC_CCA */
#define SR_CHANNEL   0x08, 0x1F, 0

/** Access parameters for sub-register CLKM_CTRL in register @ref RG_TRX_CTRL_0 */
#define SR_CLKM_CTRL   0x03, 0x07, 0

/** Access parameters for sub-register CLKM_SHA_SEL in register @ref RG_TRX_CTRL_0 */
#define SR_CLKM_SHA_SEL   0x03, 0x08, 3

/** Access parameters for sub-register CSMA_LBT_MODE in register @ref RG_XAH_CTRL_1 */
#define SR_CSMA_LBT_MODE   0x17, 0x40, 6

/** Access parameters for sub-register CSMA_SEED_0 in register @ref RG_CSMA_SEED_0 */
#define SR_CSMA_SEED_0   0x2D, 0xFF, 0

/** Access parameters for sub-register CSMA_SEED_1 in register @ref RG_CSMA_SEED_1 */
#define SR_CSMA_SEED_1   0x2E, 0x07, 0

/** Access parameters for sub-register DVDD_OK in register @ref RG_VREG_CTRL */
#define SR_DVDD_OK   0x10, 0x04, 2

/** Access parameters for sub-register DVREG_EXT in register @ref RG_VREG_CTRL */
#define SR_DVREG_EXT   0x10, 0x08, 3

/** Access parameters for sub-register ED_LEVEL in register @ref RG_PHY_ED_LEVEL */
#define SR_ED_LEVEL   0x07, 0xFF, 0

/** Access parameters for sub-register FTN_START in register @ref RG_FTN_CTRL */
#define SR_FTN_START   0x18, 0x80, 7

/** Access parameters for sub-register GC_PA in register @ref RG_PHY_TX_PWR */
#define SR_GC_PA   0x05, 0x60, 5

/** Access parameters for sub-register GC_TX_OFFS in register @ref RG_RF_CTRL_0 */
#define SR_GC_TX_OFFS   0x16, 0x03, 0

/** Access parameters for sub-register IEEE_ADDR_0 in register @ref RG_IEEE_ADDR_0 */
#define SR_IEEE_ADDR_0   0x24, 0xFF, 0

/** Access parameters for sub-register IEEE_ADDR_1 in register @ref RG_IEEE_ADDR_1 */
#define SR_IEEE_ADDR_1   0x25, 0xFF, 0

/** Access parameters for sub-register IEEE_ADDR_2 in register @ref RG_IEEE_ADDR_2 */
#define SR_IEEE_ADDR_2   0x26, 0xFF, 0

/** Access parameters for sub-register IEEE_ADDR_3 in register @ref RG_IEEE_ADDR_3 */
#define SR_IEEE_ADDR_3   0x27, 0xFF, 0

/** Access parameters for sub-register IEEE_ADDR_4 in register @ref RG_IEEE_ADDR_4 */
#define SR_IEEE_ADDR_4   0x28, 0xFF, 0

/** Access parameters for sub-register IEEE_ADDR_5 in register @ref RG_IEEE_ADDR_5 */
#define SR_IEEE_ADDR_5   0x29, 0xFF, 0

/** Access parameters for sub-register IEEE_ADDR_6 in register @ref RG_IEEE_ADDR_6 */
#define SR_IEEE_ADDR_6   0x2A, 0xFF, 0

/** Access parameters for sub-register IEEE_ADDR_7 in register @ref RG_IEEE_ADDR_7 */
#define SR_IEEE_ADDR_7   0x2B, 0xFF, 0

/** Access parameters for sub-register IRQ_0_PLL_LOCK in register @ref RG_IRQ_STATUS */
#define SR_IRQ_0_PLL_LOCK   0x0F, 0x01, 0

/** Access parameters for sub-register IRQ_1_PLL_UNLOCK in register @ref RG_IRQ_STATUS */
#define SR_IRQ_1_PLL_UNLOCK   0x0F, 0x02, 1

/** Access parameters for sub-register IRQ_2_EXT_EN in register @ref RG_TRX_CTRL_1 */
#define SR_IRQ_2_EXT_EN   0x04, 0x40, 6

/** Access parameters for sub-register IRQ_2_RX_START in register @ref RG_IRQ_STATUS */
#define SR_IRQ_2_RX_START   0x0F, 0x04, 2

/** Access parameters for sub-register IRQ_3_TRX_END in register @ref RG_IRQ_STATUS */
#define SR_IRQ_3_TRX_END   0x0F, 0x08, 3

/** Access parameters for sub-register IRQ_4_CCA_ED_DONE in register @ref RG_IRQ_STATUS */
#define SR_IRQ_4_CCA_ED_DONE   0x0F, 0x10, 4

/** Access parameters for sub-register IRQ_5_AMI in register @ref RG_IRQ_STATUS */
#define SR_IRQ_5_AMI   0x0F, 0x20, 5

/** Access parameters for sub-register IRQ_6_TRX_UR in register @ref RG_IRQ_STATUS */
#define SR_IRQ_6_TRX_UR   0x0F, 0x40, 6

/** Access parameters for sub-register IRQ_7_BAT_LOW in register @ref RG_IRQ_STATUS */
#define SR_IRQ_7_BAT_LOW   0x0F, 0x80, 7

/** Access parameters for sub-register IRQ_MASK in register @ref RG_IRQ_MASK */
#define SR_IRQ_MASK   0x0E, 0xFF, 0

/** Access parameters for sub-register IRQ_MASK_MODE in register @ref RG_TRX_CTRL_1 */
#define SR_IRQ_MASK_MODE   0x04, 0x02, 1

/** Access parameters for sub-register IRQ_POLARITY in register @ref RG_TRX_CTRL_1 */
#define SR_IRQ_POLARITY   0x04, 0x01, 0

/** Access parameters for sub-register JCM_EN in register @ref RG_RX_CTRL */
#define SR_JCM_EN   0x0A, 0x20, 5

/** Access parameters for sub-register MAN_ID_0 in register @ref RG_MAN_ID_0 */
#define SR_MAN_ID_0   0x1E, 0xFF, 0

/** Access parameters for sub-register MAN_ID_1 in register @ref RG_MAN_ID_1 */
#define SR_MAN_ID_1   0x1F, 0xFF, 0

/** Access parameters for sub-register MAX_BE in register @ref RG_CSMA_BE */
#define SR_MAX_BE   0x2F, 0xF0, 4

/** Access parameters for sub-register MAX_CSMA_RETRIES in register @ref RG_XAH_CTRL_0 */
#define SR_MAX_CSMA_RETRIES   0x2C, 0x0E, 1

/** Access parameters for sub-register MAX_FRAME_RETRIES in register @ref RG_XAH_CTRL_0 */
#define SR_MAX_FRAME_RETRIES   0x2C, 0xF0, 4

/** Access parameters for sub-register MIN_BE in register @ref RG_CSMA_BE */
#define SR_MIN_BE   0x2F, 0x0F, 0

/** Access parameters for sub-register OQPSK_DATA_RATE in register @ref RG_TRX_CTRL_2 */
#define SR_OQPSK_DATA_RATE   0x0C, 0x03, 0

/** Access parameters for sub-register OQPSK_SCRAM_EN in register @ref RG_TRX_CTRL_2 */
#define SR_OQPSK_SCRAM_EN   0x0C, 0x20, 5

/** Access parameters for sub-register OQPSK_SUB1_RC_EN in register @ref RG_TRX_CTRL_2 */
#define SR_OQPSK_SUB1_RC_EN   0x0C, 0x10, 4

/** Access parameters for sub-register PAD_IO in register @ref RG_TRX_CTRL_0 */
#define SR_PAD_IO   0x03, 0xC0, 6

/** Access parameters for sub-register PAD_IO_CLKM in register @ref RG_TRX_CTRL_0 */
#define SR_PAD_IO_CLKM   0x03, 0x30, 4

/** Access parameters for sub-register PAN_ID_0 in register @ref RG_PAN_ID_0 */
#define SR_PAN_ID_0   0x22, 0xFF, 0

/** Access parameters for sub-register PAN_ID_1 in register @ref RG_PAN_ID_1 */
#define SR_PAN_ID_1   0x23, 0xFF, 0

/** Access parameters for sub-register PART_NUM in register @ref RG_PART_NUM */
#define SR_PART_NUM   0x1C, 0xFF, 0

/** Access parameters for sub-register PA_BOOST in register @ref RG_PHY_TX_PWR */
#define SR_PA_BOOST   0x05, 0x80, 7

/** Access parameters for sub-register PA_EXT_EN in register @ref RG_TRX_CTRL_1 */
#define SR_PA_EXT_EN   0x04, 0x80, 7

/** Access parameters for sub-register PA_LT in register @ref RG_RF_CTRL_0 */
#define SR_PA_LT   0x16, 0xC0, 6

/** Access parameters for sub-register PLL_CF_START in register @ref RG_PLL_CF */
#define SR_PLL_CF_START   0x1A, 0x80, 7

/** Access parameters for sub-register PLL_DCU_START in register @ref RG_PLL_DCU */
#define SR_PLL_DCU_START   0x1B, 0x80, 7

/** Access parameters for sub-register PLL_LOCK_CP in register @ref RG_BATMON */
#define SR_PLL_LOCK_CP   0x11, 0x80, 7

/** Access parameters for sub-register RF_MC in register @ref RG_RF_CTRL_1 */
#define SR_RF_MC   0x19, 0xF0, 4

/** Access parameters for sub-register RND_VALUE in register @ref RG_PHY_RSSI */
#define SR_RND_VALUE   0x06, 0x60, 5

/** Access parameters for sub-register RSSI in register @ref RG_PHY_RSSI */
#define SR_RSSI   0x06, 0x1F, 0

/** Access parameters for sub-register RX_BL_CTRL in register @ref RG_TRX_CTRL_1 */
#define SR_RX_BL_CTRL   0x04, 0x10, 4

/** Access parameters for sub-register RX_CRC_VALID in register @ref RG_PHY_RSSI */
#define SR_RX_CRC_VALID   0x06, 0x80, 7

/** Access parameters for sub-register RX_PDT_DIS in register @ref RG_RX_SYN */
#define SR_RX_PDT_DIS   0x15, 0x80, 7

/** Access parameters for sub-register RX_PDT_LEVEL in register @ref RG_RX_SYN */
#define SR_RX_PDT_LEVEL   0x15, 0x0F, 0

/** Access parameters for sub-register RX_SAFE_MODE in register @ref RG_TRX_CTRL_2 */
#define SR_RX_SAFE_MODE   0x0C, 0x80, 7

/** Access parameters for sub-register SFD_VALUE in register @ref RG_SFD_VALUE */
#define SR_SFD_VALUE   0x0B, 0xFF, 0

/** Access parameters for sub-register SHORT_ADDR_0 in register @ref RG_SHORT_ADDR_0 */
#define SR_SHORT_ADDR_0   0x20, 0xFF, 0

/** Access parameters for sub-register SHORT_ADDR_1 in register @ref RG_SHORT_ADDR_1 */
#define SR_SHORT_ADDR_1   0x21, 0xFF, 0

/** Access parameters for sub-register SLOTTED_OPERATION in register @ref RG_XAH_CTRL_0 */
#define SR_SLOTTED_OPERATION   0x2C, 0x01, 0

/** Access parameters for sub-register SPI_CMD_MODE in register @ref RG_TRX_CTRL_1 */
#define SR_SPI_CMD_MODE   0x04, 0x0C, 2

/** Access parameters for sub-register SUB_MODE in register @ref RG_TRX_CTRL_2 */
#define SR_SUB_MODE   0x0C, 0x04, 2

/** Access parameters for sub-register TRAC_STATUS in register @ref RG_TRX_STATE */
#define SR_TRAC_STATUS   0x02, 0xE0, 5

/** Access parameters for sub-register TRX_CMD in register @ref RG_TRX_STATE */
#define SR_TRX_CMD   0x02, 0x1F, 0

/** Access parameters for sub-register TRX_OFF_AVDD_EN in register @ref RG_TRX_CTRL_2 */
#define SR_TRX_OFF_AVDD_EN   0x0C, 0x40, 6

/** Access parameters for sub-register TRX_STATUS in register @ref RG_TRX_STATUS */
#define SR_TRX_STATUS   0x01, 0x1F, 0

/** Access parameters for sub-register TX_AUTO_CRC_ON in register @ref RG_TRX_CTRL_1 */
#define SR_TX_AUTO_CRC_ON   0x04, 0x20, 5

/** Access parameters for sub-register TX_PWR in register @ref RG_PHY_TX_PWR */
#define SR_TX_PWR   0x05, 0x1F, 0

/** Access parameters for sub-register VERSION_NUM in register @ref RG_VERSION_NUM */
#define SR_VERSION_NUM   0x1D, 0xFF, 0

/** Access parameters for sub-register XTAL_MODE in register @ref RG_XOSC_CTRL */
#define SR_XTAL_MODE   0x12, 0xF0, 4

/** Access parameters for sub-register XTAL_TRIM in register @ref RG_XOSC_CTRL */
#define SR_XTAL_TRIM   0x12, 0x0F, 0


/** Constants */

/** Constant ACK_TIME_12_SYMBOLS for sub-register @ref SR_AACK_ACK_TIME in register XAH_CTRL_1 */
#define ACK_TIME_12_SYMBOLS   (0)

/** Constant ACK_TIME_2_SYMBOLS for sub-register @ref SR_AACK_ACK_TIME in register XAH_CTRL_1 */
#define ACK_TIME_2_SYMBOLS   (1)

/** Constant AES_DIR_DECRYPT for sub-register @ref SR_AES_DIR in register AES_CTRL */
#define AES_DIR_DECRYPT   (1)

/** Constant AES_DIR_ENCRYPT for sub-register @ref SR_AES_DIR in register AES_CTRL */
#define AES_DIR_ENCRYPT   (0)

/** Constant AES_DONE for sub-register @ref SR_AES_DONE in register AES_STATUS */
#define AES_DONE   (1)

/** Constant AES_ERROR for sub-register @ref SR_AES_ER in register AES_STATUS */
#define AES_ERROR   (1)

/** Constant AES_MODE_CBC for sub-register @ref SR_AES_MODE in register AES_CTRL */
#define AES_MODE_CBC   (2)

/** Constant AES_MODE_ECB for sub-register @ref SR_AES_MODE in register AES_CTRL */
#define AES_MODE_ECB   (0)

/** Constant AES_MODE_KEY for sub-register @ref SR_AES_MODE in register AES_CTRL */
#define AES_MODE_KEY   (1)

/** Constant AES_NOT_DONE for sub-register @ref SR_AES_DONE in register AES_STATUS */
#define AES_NOT_DONE   (0)

/** Constant AES_NO_ERROR for sub-register @ref SR_AES_ER in register AES_STATUS */
#define AES_NO_ERROR   (0)

/** Constant AES_REQUEST for sub-register @ref SR_AES_REQUEST in register AES_CTRL */
#define AES_REQUEST   (1)

/** Constant ALTRATE_100_KBPS_OR_250_KBPS for sub-register @ref SR_OQPSK_DATA_RATE in register TRX_CTRL_2 */
#define ALTRATE_100_KBPS_OR_250_KBPS   (0)

/** Constant ALTRATE_200_KBPS_OR_500_KBPS for sub-register @ref SR_OQPSK_DATA_RATE in register TRX_CTRL_2 */
#define ALTRATE_200_KBPS_OR_500_KBPS   (1)

/** Constant ALTRATE_400_KBPS_OR_1_MBPS for sub-register @ref SR_OQPSK_DATA_RATE in register TRX_CTRL_2 */
#define ALTRATE_400_KBPS_OR_1_MBPS   (2)

/** Constant BATMON_HR_HIGH for sub-register @ref SR_BATMON_HR in register BATMON */
#define BATMON_HR_HIGH   (1)

/** Constant BATMON_HR_LOW for sub-register @ref SR_BATMON_HR in register BATMON */
#define BATMON_HR_LOW   (0)

/** Constant BATMON_NOT_VALID for sub-register @ref SR_BATMON_OK in register BATMON */
#define BATMON_NOT_VALID   (0)

/** Constant BATMON_VALID for sub-register @ref SR_BATMON_OK in register BATMON */
#define BATMON_VALID   (1)

/** Constant BPSK_MODE for sub-register @ref SR_BPSK_OQPSK in register TRX_CTRL_2 */
#define BPSK_MODE   (0)

/** Constant BPSK_TX_OFFSET for sub-register @ref SR_GC_TX_OFFS in register RF_CTRL_0 */
#define BPSK_TX_OFFSET   (3)

/** Constant CCA_CH_BUSY for sub-register @ref SR_CCA_STATUS in register TRX_STATUS */
#define CCA_CH_BUSY   (0)

/** Constant CCA_CH_IDLE for sub-register @ref SR_CCA_STATUS in register TRX_STATUS */
#define CCA_CH_IDLE   (1)

/** Constant CCA_COMPLETED for sub-register @ref SR_CCA_DONE in register TRX_STATUS */
#define CCA_COMPLETED   (1)

/** Constant CCA_MODE_0 for sub-register @ref SR_CCA_MODE in register PHY_CC_CCA */
#define CCA_MODE_0   (0)

/** Constant CCA_MODE_1 for sub-register @ref SR_CCA_MODE in register PHY_CC_CCA */
#define CCA_MODE_1   (1)

/** Constant CCA_MODE_2 for sub-register @ref SR_CCA_MODE in register PHY_CC_CCA */
#define CCA_MODE_2   (2)

/** Constant CCA_MODE_3 for sub-register @ref SR_CCA_MODE in register PHY_CC_CCA */
#define CCA_MODE_3   (3)

/** Constant CCA_NO_START for sub-register @ref SR_CCA_REQUEST in register PHY_CC_CCA */
#define CCA_NO_START   (0)

/** Constant CCA_ONGOING for sub-register @ref SR_CCA_DONE in register TRX_STATUS */
#define CCA_ONGOING   (0)

/** Constant CCA_START for sub-register @ref SR_CCA_REQUEST in register PHY_CC_CCA */
#define CCA_START   (1)

/** Constant CLEAR_PD for sub-register @ref SR_AACK_SET_PD in register CSMA_SEED_1 */
#define CLEAR_PD   (0)

/** Constant CLKM_16MHZ for sub-register @ref SR_CLKM_CTRL in register TRX_CTRL_0 */
#define CLKM_16MHZ   (5)

/** Constant CLKM_1MHZ for sub-register @ref SR_CLKM_CTRL in register TRX_CTRL_0 */
#define CLKM_1MHZ   (1)

/** Constant CLKM_1_4MHZ for sub-register @ref SR_CLKM_CTRL in register TRX_CTRL_0 */
#define CLKM_1_4MHZ   (6)

/** Constant CLKM_2MHZ for sub-register @ref SR_CLKM_CTRL in register TRX_CTRL_0 */
#define CLKM_2MHZ   (2)

/** Constant CLKM_4MHZ for sub-register @ref SR_CLKM_CTRL in register TRX_CTRL_0 */
#define CLKM_4MHZ   (3)

/** Constant CLKM_8MHZ for sub-register @ref SR_CLKM_CTRL in register TRX_CTRL_0 */
#define CLKM_8MHZ   (4)

/** Constant CLKM_NO_CLOCK for sub-register @ref SR_CLKM_CTRL in register TRX_CTRL_0 */
#define CLKM_NO_CLOCK   (0)

/** Constant CLKM_SHA_DISABLE for sub-register @ref SR_CLKM_SHA_SEL in register TRX_CTRL_0 */
#define CLKM_SHA_DISABLE   (0)

/** Constant CLKM_SHA_ENABLE for sub-register @ref SR_CLKM_SHA_SEL in register TRX_CTRL_0 */
#define CLKM_SHA_ENABLE   (1)

/** Constant CLKM_SYMBOL_RATE for sub-register @ref SR_CLKM_CTRL in register TRX_CTRL_0 */
#define CLKM_SYMBOL_RATE   (7)

/** Constant CRC16_NOT_VALID for sub-register @ref SR_RX_CRC_VALID in register PHY_RSSI */
#define CRC16_NOT_VALID   (0)

/** Constant CRC16_VALID for sub-register @ref SR_RX_CRC_VALID in register PHY_RSSI */
#define CRC16_VALID   (1)

/** Constant HALF_SINE_FILTERING for sub-register @ref SR_OQPSK_SUB1_RC_EN in register TRX_CTRL_2 */
#define HALF_SINE_FILTERING   (0)

/** Constant HIGH_DATA_RATE for sub-register @ref SR_SUB_MODE in register TRX_CTRL_2 */
#define HIGH_DATA_RATE   (1)

/** Constant IRQ_MASK_MODE_OFF for sub-register @ref SR_IRQ_MASK_MODE in register TRX_CTRL_1 */
#define IRQ_MASK_MODE_OFF   (0)

/** Constant IRQ_MASK_MODE_ON for sub-register @ref SR_IRQ_MASK_MODE in register TRX_CTRL_1 */
#define IRQ_MASK_MODE_ON   (1)

/** Constant LOW_DATA_RATE for sub-register @ref SR_SUB_MODE in register TRX_CTRL_2 */
#define LOW_DATA_RATE   (0)

/** Constant OQPSK_MODE for sub-register @ref SR_BPSK_OQPSK in register TRX_CTRL_2 */
#define OQPSK_MODE   (1)

/** Constant OQPSK_TX_OFFSET for sub-register @ref SR_GC_TX_OFFS in register RF_CTRL_0 */
#define OQPSK_TX_OFFSET   (2)

/** Constant PAD_CLKM_2_MA for sub-register @ref SR_PAD_IO_CLKM in register TRX_CTRL_0 */
#define PAD_CLKM_2_MA   (0)

/** Constant PAD_CLKM_4_MA for sub-register @ref SR_PAD_IO_CLKM in register TRX_CTRL_0 */
#define PAD_CLKM_4_MA   (1)

/** Constant PAD_CLKM_6_MA for sub-register @ref SR_PAD_IO_CLKM in register TRX_CTRL_0 */
#define PAD_CLKM_6_MA   (2)

/** Constant PAD_CLKM_8_MA for sub-register @ref SR_PAD_IO_CLKM in register TRX_CTRL_0 */
#define PAD_CLKM_8_MA   (3)

/** Constant PAD_IO_2_MA for sub-register @ref SR_PAD_IO in register TRX_CTRL_0 */
#define PAD_IO_2_MA   (0)

/** Constant PAD_IO_4_MA for sub-register @ref SR_PAD_IO in register TRX_CTRL_0 */
#define PAD_IO_4_MA   (1)

/** Constant PAD_IO_6_MA for sub-register @ref SR_PAD_IO in register TRX_CTRL_0 */
#define PAD_IO_6_MA   (2)

/** Constant PAD_IO_8_MA for sub-register @ref SR_PAD_IO in register TRX_CTRL_0 */
#define PAD_IO_8_MA   (3)

/** Constant PART_NUM_AT86RF212 for sub-register @ref SR_PART_NUM in register PART_NUM */
#define PART_NUM_AT86RF212   (0x07)

/** Constant RC_0_8_FILTERING for sub-register @ref SR_OQPSK_SUB1_RC_EN in register TRX_CTRL_2 */
#define RC_0_8_FILTERING   (1)

/** Constant RX_DISABLE for sub-register @ref SR_RX_PDT_DIS in register RX_SYN */
#define RX_DISABLE   (1)

/** Constant RX_ENABLE for sub-register @ref SR_RX_PDT_DIS in register RX_SYN */
#define RX_ENABLE   (0)

/** Constant TX_AUTO_CRC_ENABLE for sub-register TX_AUTO_CRC_ON in register RG_TRX_CTRL_1 */
#define TX_AUTO_CRC_DISABLE   (0)

/** Constant TX_AUTO_CRC_ENABLE for sub-register TX_AUTO_CRC_ON in register RG_TRX_CTRL_1 */
#define TX_AUTO_CRC_ENABLE   (1)

/** Constant RX_SAFE_MODE_DISABLE for sub-register @ref SR_RX_SAFE_MODE in register TRX_CTRL_2 */
#define RX_SAFE_MODE_DISABLE   (0)

/** Constant RX_SAFE_MODE_ENABLE for sub-register @ref SR_RX_SAFE_MODE in register TRX_CTRL_2 */
#define RX_SAFE_MODE_ENABLE   (1)

/** Constant RX_TIMESTAMPING_DISABLE for sub-register @ref SR_IRQ_2_EXT_EN in register TRX_CTRL_1 */
#define RX_TIMESTAMPING_DISABLE   (0)

/** Constant RX_TIMESTAMPING_ENABLE for sub-register @ref SR_IRQ_2_EXT_EN in register TRX_CTRL_1 */
#define RX_TIMESTAMPING_ENABLE   (1)

/** Constant PROM_MODE_DISABLE for sub-register AACK_PROM_MODE in register RG_XAH_CTRL_1 */
#define PROM_MODE_DISABLE        (0)

/** Constant PROM_MODE_ENABLE for sub-register AACK_PROM_MODE in register RG_XAH_CTRL_1 */
#define PROM_MODE_ENABLE        (1)

/** Constant SET_PD for sub-register @ref SR_AACK_SET_PD in register CSMA_SEED_1 */
#define SET_PD   (1)

/** Constant SPI_CMD_MODE_DEFAULT for sub-register @ref SR_SPI_CMD_MODE in register TRX_CTRL_1 */
#define SPI_CMD_MODE_DEFAULT   (0)

/** Constant SPI_CMD_MODE_IRQ_STATUS for sub-register @ref SR_SPI_CMD_MODE in register TRX_CTRL_1 */
#define SPI_CMD_MODE_IRQ_STATUS   (3)

/** Constant SPI_CMD_MODE_PHY_RSSI for sub-register @ref SR_SPI_CMD_MODE in register TRX_CTRL_1 */
#define SPI_CMD_MODE_PHY_RSSI   (2)

/** Constant SPI_CMD_MODE_TRX_STATUS for sub-register @ref SR_SPI_CMD_MODE in register TRX_CTRL_1 */
#define SPI_CMD_MODE_TRX_STATUS   (1)

/** Constant TRX_IRQ_AMI for sub-register @ref SR_IRQ_MASK in register IRQ_MASK */
#define TRX_IRQ_AMI   (0x20)

/** Constant TRX_IRQ_AWAKE_END for sub-register @ref SR_IRQ_MASK in register IRQ_MASK */
#define TRX_IRQ_AWAKE_END   (0x10)

/** Constant TRX_IRQ_BAT_LOW for sub-register @ref SR_IRQ_MASK in register IRQ_MASK */
#define TRX_IRQ_BAT_LOW   (0x80)

/** Constant TRX_IRQ_CCA_ED_DONE for sub-register @ref SR_IRQ_MASK in register IRQ_MASK */
#define TRX_IRQ_CCA_ED_DONE   (0x10)

/** Constant TRX_IRQ_PLL_LOCK for sub-register @ref SR_IRQ_MASK in register IRQ_MASK */
#define TRX_IRQ_PLL_LOCK   (0x01)

/** Constant TRX_IRQ_PLL_UNLOCK for sub-register @ref SR_IRQ_MASK in register IRQ_MASK */
#define TRX_IRQ_PLL_UNLOCK   (0x02)

/** Constant TRX_IRQ_RX_START for sub-register @ref SR_IRQ_MASK in register IRQ_MASK */
#define TRX_IRQ_RX_START   (0x04)

/** Constant TRX_IRQ_TRX_END for sub-register @ref SR_IRQ_MASK in register IRQ_MASK */
#define TRX_IRQ_TRX_END   (0x08)

/** Constant TRX_IRQ_TRX_UR for sub-register @ref SR_IRQ_MASK in register IRQ_MASK */
#define TRX_IRQ_TRX_UR   (0x40)


/** Enumerations */

/** sub-register TRX_CMD in register TRX_STATE */
typedef enum trx_cmd_tag {
/** Constant CMD_NOP for sub-register @ref SR_TRX_CMD */
	CMD_NOP = (0x00),

/** Constant CMD_TX_START for sub-register @ref SR_TRX_CMD */
	CMD_TX_START = (0x02),

/** Constant CMD_FORCE_TRX_OFF for sub-register @ref SR_TRX_CMD */
	CMD_FORCE_TRX_OFF = (0x03),

/** Constant CMD_FORCE_PLL_ON for sub-register @ref SR_TRX_CMD */
	CMD_FORCE_PLL_ON = (0x04),

/** Constant CMD_RX_ON for sub-register @ref SR_TRX_CMD */
	CMD_RX_ON = (0x06),

/** Constant CMD_TRX_OFF for sub-register @ref SR_TRX_CMD */
	CMD_TRX_OFF = (0x08),

/** Constant CMD_PLL_ON for sub-register @ref SR_TRX_CMD */
	CMD_PLL_ON = (0x09),

/** Constant CMD_RX_AACK_ON for sub-register @ref SR_TRX_CMD */
	CMD_RX_AACK_ON = (0x16),

/** Constant CMD_TX_ARET_ON for sub-register @ref SR_TRX_CMD */
	CMD_TX_ARET_ON = (0x19),

/** Software implemented command */
	CMD_SLEEP = (0x0F)
} SHORTENUM trx_cmd_t;

/** sub-register TRX_STATUS in register TRX_STATUS */
typedef enum tal_trx_status_tag {
/** Constant P_ON for sub-register @ref SR_TRX_STATUS */
	P_ON = (0x00),

/** Constant BUSY_RX for sub-register @ref SR_TRX_STATUS */
	BUSY_RX = (0x01),

/** Constant BUSY_TX for sub-register @ref SR_TRX_STATUS */
	BUSY_TX = (0x02),

/** Constant RX_ON for sub-register @ref SR_TRX_STATUS */
	RX_ON = (0x06),

/** Constant TRX_OFF for sub-register @ref SR_TRX_STATUS */
	TRX_OFF = (0x08),

/** Constant PLL_ON for sub-register @ref SR_TRX_STATUS */
	PLL_ON = (0x09),

/** Constant TRX_SLEEP for sub-register @ref SR_TRX_STATUS */
	TRX_SLEEP = (0x0F),

/** Constant BUSY_RX_AACK for sub-register @ref SR_TRX_STATUS */
	BUSY_RX_AACK = (0x11),

/** Constant BUSY_TX_ARET for sub-register @ref SR_TRX_STATUS */
	BUSY_TX_ARET = (0x12),

/** Constant RX_AACK_ON for sub-register @ref SR_TRX_STATUS */
	RX_AACK_ON = (0x16),

/** Constant TX_ARET_ON for sub-register @ref SR_TRX_STATUS */
	TX_ARET_ON = (0x19),

/** Constant RX_ON_NOCLK for sub-register @ref SR_TRX_STATUS */
	RX_ON_NOCLK = (0x1C),

/** Constant RX_AACK_ON_NOCLK for sub-register @ref SR_TRX_STATUS */
	RX_AACK_ON_NOCLK = (0x1D),

/** Constant BUSY_RX_AACK_NOCLK for sub-register @ref SR_TRX_STATUS */
	BUSY_RX_AACK_NOCLK = (0x1E),

/** Constant STATE_TRANSITION_IN_PROGRESS for sub-register @ref SR_TRX_STATUS */
	STATE_TRANSITION_IN_PROGRESS = (0x1F)
} SHORTENUM tal_trx_status_t;

/** sub-register IRQ_7_BAT_LOW IRQ_6_TRX_UR IRQ_5_AMI IRQ_4_CCA_ED_DONE IRQ_3_TRX_END IRQ_2_RX_START IRQ_1_PLL_UNLOCK IRQ_0_PLL_LOCK in register IRQ_STATUS */
typedef enum trx_irq_reason_tag {
/** Constant TRX_IRQ_7_BAT_LOW for sub-register @ref SR_IRQ_7_BAT_LOW */
	TRX_IRQ_7_BAT_LOW = (0x80),

/** Constant TRX_IRQ_6_TRX_UR for sub-register @ref SR_IRQ_6_TRX_UR */
	TRX_IRQ_6_TRX_UR = (0x40),

/** Constant TRX_IRQ_5_AMI for sub-register @ref SR_IRQ_5_AMI */
	TRX_IRQ_5_AMI = (0x20),

/** Constant TRX_IRQ_4_CCA_ED_DONE for sub-register @ref SR_IRQ_4_CCA_ED_DONE */
	TRX_IRQ_4_CCA_ED_DONE = (0x10),

/** Constant TRX_IRQ_3_TRX_END for sub-register @ref SR_IRQ_3_TRX_END */
	TRX_IRQ_3_TRX_END = (0x08),

/** Constant TRX_IRQ_2_RX_START for sub-register @ref SR_IRQ_2_RX_START */
	TRX_IRQ_2_RX_START = (0x04),

/** Constant TRX_IRQ_1_PLL_UNLOCK for sub-register @ref SR_IRQ_1_PLL_UNLOCK */
	TRX_IRQ_1_PLL_UNLOCK = (0x02),

/** Constant TRX_IRQ_0_PLL_LOCK for sub-register @ref SR_IRQ_0_PLL_LOCK */
	TRX_IRQ_0_PLL_LOCK = (0x01),

/** No interrupt is indicated by IRQ_STATUS register */
	TRX_NO_IRQ = (0x00)
} SHORTENUM trx_irq_reason_t;

/** sub-register TRAC_STATUS in register TRX_STATE */
typedef enum trx_trac_status_tag {
/** Constant TRAC_SUCCESS for sub-register @ref SR_TRAC_STATUS */
	TRAC_SUCCESS = (0),

/** Constant TRAC_SUCCESS_DATA_PENDING for sub-register @ref SR_TRAC_STATUS */
	TRAC_SUCCESS_DATA_PENDING = (1),

/** Constant TRAC_SUCCESS_WAIT_FOR_ACK for sub-register @ref SR_TRAC_STATUS */
	TRAC_SUCCESS_WAIT_FOR_ACK = (2),

/** Constant TRAC_CHANNEL_ACCESS_FAILURE for sub-register @ref SR_TRAC_STATUS */
	TRAC_CHANNEL_ACCESS_FAILURE = (3),

/** Constant TRAC_NO_ACK for sub-register @ref SR_TRAC_STATUS */
	TRAC_NO_ACK = (5),

/** Constant TRAC_INVALID for sub-register @ref SR_TRAC_STATUS */
	TRAC_INVALID = (7)
} SHORTENUM trx_trac_status_t;

/** TAL states */
typedef enum tal_state_tag {
	TAL_IDLE = 0,
	TAL_TX_AUTO = 1,
	TAL_TX_END = 2
} SHORTENUM tal_state_t;

extern bool at86rfx_frame_rx;

/**
 * These are the return values of the AT86RF212 APIs.
 */
typedef enum
#if !defined(DOXYGEN)
 trx_retval_tag
#endif
{
	TRX_SUCCESS = 0x00,
	TRX_FAILURE = 0x01,
	TRX_CHANNEL_ACCESS_FAILURE = 0x02
} SHORTENUM trx_retval_t;


//! @defgroup at86rf212_api Accessing AT86RF212 Transceiver
//!
//! @{

/**
 * \brief Transceiver interrupt handler
 *
 * This function handles the transceiver generated interrupts.
 */
void trx_irq_handler_cb(void);

/**
 * \brief Initializes the TAL
 *
 * This function is called to initialize the TAL. The transceiver is
 * initialized and the TAL state is set to TAL_IDLE state.
 *
 * \return TRX_SUCCESS if the transceiver state is changed to TRX_OFF and the
 *                     current device part number and version number are correct;
 *         TRX_FAILURE otherwise
 */
trx_retval_t tal_init(void);

/**
 * \brief Handles the transceiver state
 */
void handle_tal_state(void);

/**
 * \brief Configures the transceiver for frame transmission
 */
void tx_frame_config(void);
    //! @}

#endif /* AT86RF212_H */
