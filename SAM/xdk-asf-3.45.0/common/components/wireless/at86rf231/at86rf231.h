/**
 * \file
 *
 * \brief Driver for AT86RF231 transceiver.
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
#ifndef AT86RF231_H
#define AT86RF231_H


#include "conf_at86rfx.h"


#define TRX_SUPPORTED_CHANNELS          (0x07FFF800)

/**
 * Tolerance of the phyTransmitPower PIB attribute.  This is encoded
 * into the two MSBits of the attribute, and is effectively read-only.
 */
#define TX_PWR_TOLERANCE                (0x80)

/*
 * Typical timing values
 */
#define RST_PULSE_WIDTH_US                  (1)
#define P_ON_TO_CLKM_AVAILABLE_TYP_US       (330)
#define P_ON_TO_CLKM_AVAILABLE_MAX_US       (1000)
#define SLEEP_TO_TRX_OFF_TYP_US             (380)
#define SLEEP_TO_TRX_OFF_MAX_US             (1000)
#define TRX_OFF_TO_SLEEP_TIME_CLKM_CYCLES   (35)
#define TRX_OFF_TO_PLL_ON_TIME_US           (110)
#define TRX_IRQ_DELAY_US                    (9)
#define IRQ_PROCESSING_DLY_US               (32)
/*
 * CSMA timing parameters
 */
#define CCA_DETECTION_TIME_SYM          (8)
#define CCA_PROCESS_TIME_SYM            (1)
#define CCA_DURATION_SYM                (CCA_DETECTION_TIME_SYM + CCA_PROCESS_TIME_SYM)
#define CSMA_PROCESSING_TIME_US         (100)
#define CCA_PREPARATION_DURATION_US     (50)
#define CCA_PRE_START_DURATION_US       (20)
#define PRE_TX_DURATION_US              (32)	// 16 us processing delay +
		// 16 us software handling duration
/** Register addresses */
/** Base address for Transceiver AES address space **/
#define AES_BASE_ADDR   (0x80)
/** Offset for register AES_STATUS */
#define RG_AES_STATUS   (0x02)
/** Offset for register AES_CTRL */
#define RG_AES_CTRL   (0x03)
/** Offset for register AES_STATE_KEY_0 */
#define RG_AES_STATE_KEY_0   (0x04)
/** Offset for register ANT_DIV */
#define RG_ANT_DIV   (0x0d)
/** Offset for register BATMON */
#define RG_BATMON   (0x11)
/** Offset for register CCA_THRES */
#define RG_CCA_THRES   (0x09)
/** Offset for register CSMA_BE */
#define RG_CSMA_BE   (0x2f)
/** Offset for register CSMA_SEED_0 */
#define RG_CSMA_SEED_0   (0x2d)
/** Offset for register CSMA_SEED_1 */
#define RG_CSMA_SEED_1   (0x2e)
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
#define RG_IEEE_ADDR_6   (0x2a)
/** Offset for register IEEE_ADDR_7 */
#define RG_IEEE_ADDR_7   (0x2b)
/** Offset for register IRQ_MASK */
#define RG_IRQ_MASK   (0x0e)
/** Offset for register IRQ_STATUS */
#define RG_IRQ_STATUS   (0x0f)
/** Offset for register MAN_ID_0 */
#define RG_MAN_ID_0   (0x1e)
/** Offset for register MAN_ID_1 */
#define RG_MAN_ID_1   (0x1f)
/** Offset for register PAN_ID_0 */
#define RG_PAN_ID_0   (0x22)
/** Offset for register PAN_ID_1 */
#define RG_PAN_ID_1   (0x23)
/** Offset for register PART_NUM */
#define RG_PART_NUM   (0x1c)
/** Offset for register PHY_CC_CCA */
#define RG_PHY_CC_CCA   (0x08)
/** Offset for register PHY_ED_LEVEL */
#define RG_PHY_ED_LEVEL   (0x07)
/** Offset for register PHY_RSSI */
#define RG_PHY_RSSI   (0x06)
/** Offset for register PHY_TX_PWR */
#define RG_PHY_TX_PWR   (0x05)
/** Offset for register PLL_CF */
#define RG_PLL_CF   (0x1a)
/** Offset for register PLL_DCU */
#define RG_PLL_DCU   (0x1b)
/** Offset for register RX_CTRL */
#define RG_RX_CTRL   (0x0a)
/** Offset for register RX_SYN */
#define RG_RX_SYN   (0x15)
/** Offset for register SFD_VALUE */
#define RG_SFD_VALUE   (0x0b)
/** Offset for register SHORT_ADDR_0 */
#define RG_SHORT_ADDR_0   (0x20)
/** Offset for register SHORT_ADDR_1 */
#define RG_SHORT_ADDR_1   (0x21)
/** Offset for register TRX_CTRL_0 */
#define RG_TRX_CTRL_0   (0x03)
/** Offset for register TRX_CTRL_1 */
#define RG_TRX_CTRL_1   (0x04)
/** Offset for register TRX_CTRL_2 */
#define RG_TRX_CTRL_2   (0x0c)
/** Offset for register TRX_STATE */
#define RG_TRX_STATE   (0x02)
/** Offset for register TRX_STATUS */
#define RG_TRX_STATUS   (0x01)
/** Offset for register VERSION_NUM */
#define RG_VERSION_NUM   (0x1d)
/** Offset for register VREG_CTRL */
#define RG_VREG_CTRL   (0x10)
/** Offset for register XAH_CTRL_0 */
#define RG_XAH_CTRL_0   (0x2c)
/** Offset for register XAH_CTRL_1 */
#define RG_XAH_CTRL_1   (0x17)
/** Offset for register XOSC_CTRL */
#define RG_XOSC_CTRL   (0x12)
/** Subregister access */
/** Access parameters for sub-register AACK_ACK_TIME in register RG_XAH_CTRL_1 */
#define SR_AACK_ACK_TIME   0x17, 0x04, 2
/** Access parameters for sub-register AACK_DIS_ACK in register RG_CSMA_SEED_1 */
#define SR_AACK_DIS_ACK   0x2e, 0x10, 4
/** Access parameters for sub-register AACK_FLTR_RES_FT in register RG_XAH_CTRL_1 */
#define SR_AACK_FLTR_RES_FT   0x17, 0x20, 5
/** Access parameters for sub-register AACK_FVN_MODE in register RG_CSMA_SEED_1 */
#define SR_AACK_FVN_MODE   0x2e, 0xc0, 6
/** Access parameters for sub-register AACK_I_AM_COORD in register RG_CSMA_SEED_1 */
#define SR_AACK_I_AM_COORD   0x2e, 0x08, 3
/** Access parameters for sub-register AACK_PROM_MODE in register RG_XAH_CTRL_1 */
#define SR_AACK_PROM_MODE   0x17, 0x02, 1
/** Access parameters for sub-register AACK_SET_PD in register RG_CSMA_SEED_1 */
#define SR_AACK_SET_PD   0x2e, 0x20, 5
/** Access parameters for sub-register AACK_UPLD_RES_FT in register RG_XAH_CTRL_1 */
#define SR_AACK_UPLD_RES_FT   0x17, 0x10, 4
/** Access parameters for sub-register ANT_CTRL in register RG_ANT_DIV */
#define SR_ANT_CTRL   0x0d, 0x03, 0
/** Access parameters for sub-register ANT_DIV_EN in register RG_ANT_DIV */
#define SR_ANT_DIV_EN   0x0d, 0x08, 3
/** Access parameters for sub-register ANT_EXT_SW_EN in register RG_ANT_DIV */
#define SR_ANT_EXT_SW_EN   0x0d, 0x04, 2
/** Access parameters for sub-register ANT_SEL in register RG_ANT_DIV */
#define SR_ANT_SEL   0x0d, 0x80, 7
/** Access parameters for sub-register AVDD_OK in register RG_VREG_CTRL */
#define SR_AVDD_OK   0x10, 0x40, 6
/** Access parameters for sub-register AVREG_EXT in register RG_VREG_CTRL */
#define SR_AVREG_EXT   0x10, 0x80, 7
/** Access parameters for sub-register BATMON_HR in register RG_BATMON */
#define SR_BATMON_HR   0x11, 0x10, 4
/** Access parameters for sub-register BATMON_OK in register RG_BATMON */
#define SR_BATMON_OK   0x11, 0x20, 5
/** Access parameters for sub-register BATMON_VTH in register RG_BATMON */
#define SR_BATMON_VTH   0x11, 0x0f, 0
/** Access parameters for sub-register CCA_DONE in register RG_TRX_STATUS */
#define SR_CCA_DONE   0x01, 0x80, 7
/** Access parameters for sub-register CCA_ED_THRES in register RG_CCA_THRES */
#define SR_CCA_ED_THRES   0x09, 0x0f, 0
/** Access parameters for sub-register CCA_MODE in register RG_PHY_CC_CCA */
#define SR_CCA_MODE   0x08, 0x60, 5
/** Access parameters for sub-register CCA_REQUEST in register RG_PHY_CC_CCA */
#define SR_CCA_REQUEST   0x08, 0x80, 7
/** Access parameters for sub-register CCA_STATUS in register RG_TRX_STATUS */
#define SR_CCA_STATUS   0x01, 0x40, 6
/** Access parameters for sub-register CHANNEL in register RG_PHY_CC_CCA */
#define SR_CHANNEL   0x08, 0x1f, 0
/** Access parameters for sub-register CLKM_CTRL in register RG_TRX_CTRL_0 */
#define SR_CLKM_CTRL   0x03, 0x07, 0
/** Access parameters for sub-register CLKM_SHA_SEL in register RG_TRX_CTRL_0 */
#define SR_CLKM_SHA_SEL   0x03, 0x08, 3
/** Access parameters for sub-register CSMA_SEED_0 in register RG_CSMA_SEED_0 */
#define SR_CSMA_SEED_0   0x2d, 0xff, 0
/** Access parameters for sub-register CSMA_SEED_1 in register RG_CSMA_SEED_1 */
#define SR_CSMA_SEED_1   0x2e, 0x07, 0
/** Access parameters for sub-register DVDD_OK in register RG_VREG_CTRL */
#define SR_DVDD_OK   0x10, 0x04, 2
/** Access parameters for sub-register DVREG_EXT in register RG_VREG_CTRL */
#define SR_DVREG_EXT   0x10, 0x08, 3
/** Access parameters for sub-register ED_LEVEL in register RG_PHY_ED_LEVEL */
#define SR_ED_LEVEL   0x07, 0xff, 0
/** Access parameters for sub-register FTN_START in register RG_FTN_CTRL */
#define SR_FTN_START   0x18, 0x80, 7
/** Access parameters for sub-register IEEE_ADDR_0 in register RG_IEEE_ADDR_0 */
#define SR_IEEE_ADDR_0   0x24, 0xff, 0
/** Access parameters for sub-register IEEE_ADDR_1 in register RG_IEEE_ADDR_1 */
#define SR_IEEE_ADDR_1   0x25, 0xff, 0
/** Access parameters for sub-register IEEE_ADDR_2 in register RG_IEEE_ADDR_2 */
#define SR_IEEE_ADDR_2   0x26, 0xff, 0
/** Access parameters for sub-register IEEE_ADDR_3 in register RG_IEEE_ADDR_3 */
#define SR_IEEE_ADDR_3   0x27, 0xff, 0
/** Access parameters for sub-register IEEE_ADDR_4 in register RG_IEEE_ADDR_4 */
#define SR_IEEE_ADDR_4   0x28, 0xff, 0
/** Access parameters for sub-register IEEE_ADDR_5 in register RG_IEEE_ADDR_5 */
#define SR_IEEE_ADDR_5   0x29, 0xff, 0
/** Access parameters for sub-register IEEE_ADDR_6 in register RG_IEEE_ADDR_6 */
#define SR_IEEE_ADDR_6   0x2a, 0xff, 0
/** Access parameters for sub-register IEEE_ADDR_7 in register RG_IEEE_ADDR_7 */
#define SR_IEEE_ADDR_7   0x2b, 0xff, 0
/** Access parameters for sub-register IRQ_0_PLL_LOCK in register RG_IRQ_STATUS */
#define SR_IRQ_0_PLL_LOCK   0x0f, 0x01, 0
/** Access parameters for sub-register IRQ_1_PLL_UNLOCK in register RG_IRQ_STATUS */
#define SR_IRQ_1_PLL_UNLOCK   0x0f, 0x02, 1
/** Access parameters for sub-register IRQ_2_EXT_EN in register RG_TRX_CTRL_1 */
#define SR_IRQ_2_EXT_EN   0x04, 0x40, 6
/** Access parameters for sub-register IRQ_2_RX_START in register RG_IRQ_STATUS */
#define SR_IRQ_2_RX_START   0x0f, 0x04, 2
/** Access parameters for sub-register IRQ_3_TRX_END in register RG_IRQ_STATUS */
#define SR_IRQ_3_TRX_END   0x0f, 0x08, 3
/** Access parameters for sub-register IRQ_4_CCA_ED_READY in register RG_IRQ_STATUS */
#define SR_IRQ_4_CCA_ED_READY   0x0f, 0x10, 4
/** Access parameters for sub-register IRQ_5_AMI in register RG_IRQ_STATUS */
#define SR_IRQ_5_AMI   0x0f, 0x20, 5
/** Access parameters for sub-register IRQ_6_TRX_UR in register RG_IRQ_STATUS */
#define SR_IRQ_6_TRX_UR   0x0f, 0x40, 6
/** Access parameters for sub-register IRQ_7_BAT_LOW in register RG_IRQ_STATUS */
#define SR_IRQ_7_BAT_LOW   0x0f, 0x80, 7
/** Access parameters for sub-register IRQ_MASK in register RG_IRQ_MASK */
#define SR_IRQ_MASK   0x0e, 0xff, 0
/** Access parameters for sub-register IRQ_MASK_MODE in register RG_TRX_CTRL_1 */
#define SR_IRQ_MASK_MODE   0x04, 0x02, 1
/** Access parameters for sub-register IRQ_POLARITY in register RG_TRX_CTRL_1 */
#define SR_IRQ_POLARITY   0x04, 0x01, 0
/** Access parameters for sub-register MAN_ID_0 in register RG_MAN_ID_0 */
#define SR_MAN_ID_0   0x1e, 0xff, 0
/** Access parameters for sub-register MAN_ID_1 in register RG_MAN_ID_1 */
#define SR_MAN_ID_1   0x1f, 0xff, 0
/** Access parameters for sub-register MAX_BE in register RG_CSMA_BE */
#define SR_MAX_BE   0x2f, 0xf0, 4
/** Access parameters for sub-register MAX_CSMA_RETRIES in register RG_XAH_CTRL_0 */
#define SR_MAX_CSMA_RETRIES   0x2c, 0x0e, 1
/** Access parameters for sub-register MAX_FRAME_RETRIES in register RG_XAH_CTRL_0 */
#define SR_MAX_FRAME_RETRIES   0x2c, 0xf0, 4
/** Access parameters for sub-register MIN_BE in register RG_CSMA_BE */
#define SR_MIN_BE   0x2f, 0x0f, 0
/** Access parameters for sub-register OQPSK_DATA_RATE in register RG_TRX_CTRL_2 */
#define SR_OQPSK_DATA_RATE   0x0c, 0x03, 0
/** Access parameters for sub-register OQPSK_SCRAM_EN in register @ref RG_TRX_CTRL_2 */
#define SR_OQPSK_SCRAM_EN   0x0C, 0x20, 5
/** Access parameters for sub-register PA_BUF_LT in register RG_PHY_TX_PWR */
#define SR_PA_BUF_LT   0x05, 0xc0, 6
/** Access parameters for sub-register PA_EXT_EN in register RG_TRX_CTRL_1 */
#define SR_PA_EXT_EN   0x04, 0x80, 7
/** Access parameters for sub-register PA_LT in register RG_PHY_TX_PWR */
#define SR_PA_LT   0x05, 0x30, 4
/** Access parameters for sub-register PAD_IO in register RG_TRX_CTRL_0 */
#define SR_PAD_IO   0x03, 0xc0, 6
/** Access parameters for sub-register PAD_IO_CLKM in register RG_TRX_CTRL_0 */
#define SR_PAD_IO_CLKM   0x03, 0x30, 4
/** Access parameters for sub-register PAN_ID_0 in register RG_PAN_ID_0 */
#define SR_PAN_ID_0   0x22, 0xff, 0
/** Access parameters for sub-register PAN_ID_1 in register RG_PAN_ID_1 */
#define SR_PAN_ID_1   0x23, 0xff, 0
/** Access parameters for sub-register PART_NUM in register RG_PART_NUM */
#define SR_PART_NUM   0x1c, 0xff, 0
/** Access parameters for sub-register PDT_THRES in register RG_RX_CTRL */
#define SR_PDT_THRES   0x0a, 0x0f, 0
/** Access parameters for sub-register PLL_CF_START in register RG_PLL_CF */
#define SR_PLL_CF_START   0x1a, 0x80, 7
/** Access parameters for sub-register PLL_DCU_START in register RG_PLL_DCU */
#define SR_PLL_DCU_START   0x1b, 0x80, 7
/** Access parameters for sub-register RND_VALUE in register RG_PHY_RSSI */
#define SR_RND_VALUE   0x06, 0x60, 5
/** Access parameters for sub-register RSSI in register RG_PHY_RSSI */
#define SR_RSSI   0x06, 0x1f, 0
/** Access parameters for sub-register RX_BL_CTRL in register RG_TRX_CTRL_1 */
#define SR_RX_BL_CTRL   0x04, 0x10, 4
/** Access parameters for sub-register RX_CRC_VALID in register RG_PHY_RSSI */
#define SR_RX_CRC_VALID   0x06, 0x80, 7
/** Access parameters for sub-register RX_PDT_DIS in register RG_RX_SYN */
#define SR_RX_PDT_DIS   0x15, 0x80, 7
/** Access parameters for sub-register RX_PDT_LEVEL in register RG_RX_SYN */
#define SR_RX_PDT_LEVEL   0x15, 0x0f, 0
/** Access parameters for sub-register RX_SAFE_MODE in register RG_TRX_CTRL_2 */
#define SR_RX_SAFE_MODE   0x0c, 0x80, 7
/** Access parameters for sub-register SFD_VALUE in register RG_SFD_VALUE */
#define SR_SFD_VALUE   0x0b, 0xff, 0
/** Access parameters for sub-register SHORT_ADDR_0 in register RG_SHORT_ADDR_0 */
#define SR_SHORT_ADDR_0   0x20, 0xff, 0
/** Access parameters for sub-register SHORT_ADDR_1 in register RG_SHORT_ADDR_1 */
#define SR_SHORT_ADDR_1   0x21, 0xff, 0
/** Access parameters for sub-register SLOTTED_OPERATION in register RG_XAH_CTRL_0 */
#define SR_SLOTTED_OPERATION   0x2c, 0x01, 0
/** Access parameters for sub-register SPI_CMD_MODE in register RG_TRX_CTRL_1 */
#define SR_SPI_CMD_MODE   0x04, 0x0c, 2
/** Access parameters for sub-register TRAC_STATUS in register RG_TRX_STATE */
#define SR_TRAC_STATUS   0x02, 0xe0, 5
/** Access parameters for sub-register TRX_CMD in register RG_TRX_STATE */
#define SR_TRX_CMD   0x02, 0x1f, 0
/** Access parameters for sub-register TRX_STATUS in register RG_TRX_STATUS */
#define SR_TRX_STATUS   0x01, 0x1f, 0
/** Access parameters for sub-register TX_AUTO_CRC_ON in register RG_TRX_CTRL_1 */
#define SR_TX_AUTO_CRC_ON   0x04, 0x20, 5
/** Access parameters for sub-register TX_PWR in register RG_PHY_TX_PWR */
#define SR_TX_PWR   0x05, 0x0f, 0
/** Access parameters for sub-register VERSION_NUM in register RG_VERSION_NUM */
#define SR_VERSION_NUM   0x1d, 0xff, 0
/** Access parameters for sub-register XTAL_MODE in register RG_XOSC_CTRL */
#define SR_XTAL_MODE   0x12, 0xf0, 4
/** Access parameters for sub-register XTAL_TRIM in register RG_XOSC_CTRL */
#define SR_XTAL_TRIM   0x12, 0x0f, 0
/** Constants */
/** Constant AACK_ACK_TIME_12_symbols for sub-register SR_AACK_ACK_TIME */
#define AACK_ACK_TIME_12_SYMBOLS   (0)
/** Constant AACK_ACK_TIME_2_symbols for sub-register SR_AACK_ACK_TIME */
#define AACK_ACK_TIME_2_SYMBOLS   (1)
/** AES core operation direction: Decryption (ECB) */
#define AES_DIR_DECRYPT   (1)
/** AES core operation direction: Encryption (ECB, CBC) */
#define AES_DIR_ENCRYPT   (0)
/** Set CBC mode */
#define AES_MODE_CBC   (2)
/** Set ECB mode */
#define AES_MODE_ECB   (0)
/** Set key mode */
#define AES_MODE_KEY   (1)
/** Initiate an AES operation */
#define AES_REQUEST   (1)
/** AES core operation status: AES module finished */
#define AES_DONE   (1)
/** AES core operation status: AES module did not finish */
#define AES_NOT_DONE   (0)
/** Constant ALTRATE_1Mbps for sub-register SR_OQPSK_DATA_RATE */
#define ALTRATE_1MBPS   (2)
/** Constant ALTRATE_250kbps for sub-register SR_OQPSK_DATA_RATE */
#define ALTRATE_250KBPS   (0)
/** Constant ALTRATE_2Mbps for sub-register SR_OQPSK_DATA_RATE */
#define ALTRATE_2MBPS   (3)
/** Constant ALTRATE_500kbps for sub-register SR_OQPSK_DATA_RATE */
#define ALTRATE_500KBPS   (1)
/** Constant PA_EXT_disable for sub-register SR_PA_EXT_EN */
#define PA_EXT_DISABLE   (0)
/** Constant PA_EXT_enable for sub-register SR_PA_EXT_EN */
#define PA_EXT_ENABLE   (1)
/** Constant ANT_DIV_disable for sub-register SR_ANT_DIV_EN */
#define ANT_DIV_DISABLE   (0)
/** Constant ANT_DIV_enable for sub-register SR_ANT_DIV_EN */
#define ANT_DIV_ENABLE   (1)
/** Constant ANT_EXT_SW_switch_disable for sub-register SR_ANT_EXT_SW_EN */
#define ANT_EXT_SW_SWITCH_DISABLE   (0)
/** Constant ANT_EXT_SW_switch_enable for sub-register SR_ANT_EXT_SW_EN */
#define ANT_EXT_SW_SWITCH_ENABLE   (1)
/** Constant ANT_SEL_antenna_0 for sub-register SR_ANT_SEL */
#define ANT_SEL_ANTENNA_0   (0)
/** Constant ANT_SEL_antenna_1 for sub-register SR_ANT_SEL */
#define ANT_SEL_ANTENNA_1   (1)
/** Constant BATMON_BELOW_THRES for sub-register SR_BATMON_OK */
#define BATMON_BELOW_THRES   (0)
/** Constant BATMON_ABOVE_THRES for sub-register SR_BATMON_OK */
#define BATMON_ABOVE_THRES   (1)
/** Constant BATMON_LOW_RANGE for sub-register BATMON_HR in register RG_BATMON */
#define BATMON_LOW_RANGE        (0)
/** Constant BATMON_HIGH_RANGE for sub-register BATMON_HR in register RG_BATMON */
#define BATMON_HIGH_RANGE        (1)
/** Constant CCA_calculation_done for sub-register SR_CCA_DONE */
#define CCA_DETECTION_DONE   (1)
/** Constant CCA_calculation_not_finished for sub-register SR_CCA_DONE */
#define CCA_DETECTION_NOT_DONE   (0)
/** Constant CCA_Mode_0 for sub-register SR_CCA_MODE */
#define CCA_MODE_0   (0)
/** Constant CCA_Mode_1 for sub-register SR_CCA_MODE */
#define CCA_MODE_1   (1)
/** Constant CCA_Mode_2 for sub-register SR_CCA_MODE */
#define CCA_MODE_2   (2)
/** Constant CCA_Mode_3 for sub-register SR_CCA_MODE */
#define CCA_MODE_3   (3)
/** Constant CCA_STATUS_channel_is_busy for sub-register SR_CCA_STATUS */
#define CCA_STATUS_CHANNEL_IS_BUSY   (0)
/** Constant CCA_STATUS_channel_is_idle for sub-register SR_CCA_STATUS */
#define CCA_STATUS_CHANNEL_IS_IDLE   (1)
/** Constant CLKM_16MHz for sub-register SR_CLKM_CTRL */
#define CLKM_16MHZ   (5)
/** Constant CLKM_1_16MHz for sub-register SR_CLKM_CTRL */
#define CLKM_1_16MHZ   (7)
/** Constant CLKM_1_4MHz for sub-register SR_CLKM_CTRL */
#define CLKM_1_4MHZ   (6)
/** Constant CLKM_1MHz for sub-register SR_CLKM_CTRL */
#define CLKM_1MHZ   (1)
/** Constant CLKM_2MHz for sub-register SR_CLKM_CTRL */
#define CLKM_2MHZ   (2)
/** Constant CLKM_4MHz for sub-register SR_CLKM_CTRL */
#define CLKM_4MHZ   (3)
/** Constant CLKM_8MHz for sub-register SR_CLKM_CTRL */
#define CLKM_8MHZ   (4)
/** Constant CLKM_no_clock for sub-register SR_CLKM_CTRL */
#define CLKM_NO_CLOCK   (0)
/** Constant CLKM_SHA_disable for sub-register SR_CLKM_SHA_SEL */
#define CLKM_SHA_DISABLE   (0)
/** Constant CLKM_SHA_enable for sub-register SR_CLKM_SHA_SEL */
#define CLKM_SHA_ENABLE   (1)
/** Constant CRC16_not_valid for sub-register SR_RX_CRC_VALID */
#define CRC16_NOT_VALID   (0)
/** Constant CRC16_valid for sub-register SR_RX_CRC_VALID */
#define CRC16_VALID   (1)
/** Constant IRQ_MASK_MODE_off for sub-register SR_IRQ_MASK_MODE */
#define IRQ_MASK_MODE_OFF   (0)
/** Constant IRQ_MASK_MODE_on for sub-register SR_IRQ_MASK_MODE */
#define IRQ_MASK_MODE_ON   (1)
/** Constant IRQ_POL_high_active_IRQ for sub-register SR_IRQ_POLARITY */
#define IRQ_POL_HIGH_ACTIVE_IRQ   (0)
/** Constant IRQ_POL_low_active_IRQ for sub-register SR_IRQ_POLARITY */
#define IRQ_POL_LOW_ACTIVE_IRQ   (1)
/** Constant PA_BUF_LT_0s for sub-register SR_PA_BUF_LT */
#define PA_BUF_LT_0_US   (0)
/** Constant PA_BUF_LT_2s for sub-register SR_PA_BUF_LT */
#define PA_BUF_LT_2_US   (1)
/** Constant PA_BUF_LT_4s for sub-register SR_PA_BUF_LT */
#define PA_BUF_LT_4_US (2)
/** Constant PA_BUF_LT_6s for sub-register SR_PA_BUF_LT */
#define PA_BUF_LT_6_US (3)
/** Constant PA_LT_2s for sub-register SR_PA_LT */
#define PA_LT_2_US (0)
/** Constant PA_LT_4s for sub-register SR_PA_LT */
#define PA_LT_4_US   (1)
/** Constant PA_LT_6s for sub-register SR_PA_LT */
#define PA_LT_6_US   (2)
/** Constant PA_LT_8s for sub-register SR_PA_LT */
#define PA_LT_8_US   (3)
/** Constant PAD_CLKM_2mA for sub-register SR_PAD_IO_CLKM */
#define PAD_CLKM_2_MA   (0)
/** Constant PAD_CLKM_4mA for sub-register SR_PAD_IO_CLKM */
#define PAD_CLKM_4_MA   (1)
/** Constant PAD_CLKM_6mA for sub-register SR_PAD_IO_CLKM */
#define PAD_CLKM_6_MA   (2)
/** Constant PAD_CLKM_8mA for sub-register SR_PAD_IO_CLKM */
#define PAD_CLKM_8_MA   (3)
/** Constant PAD_IO_2mA for sub-register SR_PAD_IO */
#define PAD_IO_2_MA   (0)
/** Constant PAD_IO_4mA for sub-register SR_PAD_IO */
#define PAD_IO_4_MA   (1)
/** Constant PAD_IO_6mA for sub-register SR_PAD_IO */
#define PAD_IO_6_MA   (2)
/** Constant PAD_IO_8mA for sub-register SR_PAD_IO */
#define PAD_IO_8_MA   (3)
/** Constant RF231 for sub-register SR_PART_NUM */
#define AT86RF231_PART_NUM   (3)
/** Constant RF231 for sub-register SR_VERSION_NUM */
#define AT86RF231_VERSION_NUM   (2)
/** RF231 FIFO size. */
#define RF231_RAM_SIZE   (0x80)
/** mirrored version of AES_CTRL, SRAM address */
#define RG_AES_CTRL_MIRROR   (0x94)
/** Minimum RSSI sensitivity value in dBm, which is equivalent to the value 0 in sub register SR_RSSI. */
#define RSSI_BASE_VAL   (-90)
/** Constant SPI_CMD_MODE_default for sub-register SR_SPI_CMD_MODE */
#define SPI_CMD_MODE_DEFAULT   (0)
/** Constant SPI_CMD_MODE_monitor_IRQ_STATUS for sub-register SR_SPI_CMD_MODE */
#define SPI_CMD_MODE_MONITOR_IRQ_STATUS   (3)
/** Constant SPI_CMD_MODE_monitor_PHY_RSSI for sub-register SR_SPI_CMD_MODE */
#define SPI_CMD_MODE_MONITOR_PHY_RSSI   (2)
/** Constant SPI_CMD_MODE_monitor_TRX_STATUS for sub-register SR_SPI_CMD_MODE */
#define SPI_CMD_MODE_MONITOR_TRX_STATUS   (1)
/** Duration of an octet for 250kb/s OQPSK mode in us */
#define T_OCT   32
/** Duration of an symbol for 250kb/s OQPSK mode in us */
#define T_SYM   16
/** Constant RX_ENABLE for sub-register RX_PDT_DIS */
#define RX_ENABLE             (0)
/** Constant RX_DISABLE for sub-register RX_PDT_DIS */
#define RX_DISABLE             (1)
/** Constant TX_AUTO_CRC_ENABLE for sub-register TX_AUTO_CRC_ON in register RG_TRX_CTRL_1 */
#define TX_AUTO_CRC_DISABLE   (0)
/** Constant TX_AUTO_CRC_ENABLE for sub-register TX_AUTO_CRC_ON in register RG_TRX_CTRL_1 */
#define TX_AUTO_CRC_ENABLE   (1)
/** Constant TIMESTAMPING_DISABLE for sub-register SR_IRQ_2_EXT_EN in register RG_TRX_CTRL_1 */
#define TIMESTAMPING_DISABLE   (0)
/** Constant TIMESTAMPING_ENABLE for sub-register SR_IRQ_2_EXT_EN in register RG_TRX_CTRL_1 */
#define TIMESTAMPING_ENABLE   (1)
/** Constant UPLD_RES_FT_DISBALE for sub-register AACK_UPLD_RES_FT in register RG_XAH_CTRL_1 */
#define UPLD_RES_FT_DISABLE     (0)
/** Constant UPLD_RES_FT_DISBALE for sub-register AACK_UPLD_RES_FT in register RG_XAH_CTRL_1 */
#define UPLD_RES_FT_ENABLE     (1)
/** Constant PROM_MODE_DISABLE for sub-register AACK_PROM_MODE in register RG_XAH_CTRL_1 */
#define PROM_MODE_DISABLE        (0)
/** Constant PROM_MODE_ENABLE for sub-register AACK_PROM_MODE in register RG_XAH_CTRL_1 */
#define PROM_MODE_ENABLE        (1)
/** Constant RX_SAFE_MODE_DISABLE for sub-register RX_SAFE_MODE in register RG_TRX_CTRL_2 */
#define RX_SAFE_MODE_DISABLE     (0)
/** Constant RX_SAFE_MODE_ENABLE for sub-register RX_SAFE_MODE in register RG_TRX_CTRL_2 */
#define RX_SAFE_MODE_ENABLE     (1)
/** Constant OQPSK_SCRAM_DISABLE for sub-register OQPSK_SCRAM_EN in register RG_TRX_CTRL_2 */
#define OQPSK_SCRAM_DISABLE     (0)
/** Constant OQPSK_SCRAM_ENABLE for sub-register OQPSK_SCRAM_EN in register RG_TRX_CTRL_2 */
#define OQPSK_SCRAM_ENABLE     (1)
/** Constant ACK_DISABLE for sub-register AACK_DIS_ACK in register RG_CSMA_SEED_1 */
#define ACK_DISABLE             (1)
/** Constant ACK_ENABLE for sub-register AACK_DIS_ACK in register RG_CSMA_SEED_1 */
#define ACK_ENABLE             (0)
/** Constant PD_ACK_BIT_SET_DISABLE for sub-register AACK_SET_PD in register RG_CSMA_SEED_1 */
#define PD_ACK_BIT_SET_DISABLE      (0)
/** Constant PD_ACK_BIT_SET_ENABLE for sub-register AACK_SET_PD in register RG_CSMA_SEED_1 */
#define PD_ACK_BIT_SET_ENABLE      (1)
/** Constant FRAME_VERSION_0 for sub-register AACK_FVN_MODE in register RG_CSMA_SEED_1 */
#define FRAME_VERSION_0         (0)
/** Constant FRAME_VERSION_01 for sub-register AACK_FVN_MODE in register RG_CSMA_SEED_1 */
#define FRAME_VERSION_01         (1)
/** Constant FRAME_VERSION_012 for sub-register AACK_FVN_MODE in register RG_CSMA_SEED_1 */
#define FRAME_VERSION_012         (2)
/** Constant FRAME_VERSION_IGNORED for sub-register AACK_FVN_MODE in register RG_CSMA_SEED_1 */
#define FRAME_VERSION_IGNORED         (3)
/** Constant THRES_ANT_DIV_ENABLE for sub-register SR_PDT_THRES in register RG_RX_CTRL */
#define THRES_ANT_DIV_ENABLE        (0x3)
/** Constant THRES_ANT_DIV_DISABLED for sub-register SR_PDT_THRES in register RG_RX_CTRL */
#define THRES_ANT_DIV_DISABLED       (0x7)
/** Constant ENABLE_ANTENNA_0 for sub-register SR_ANT_CTRL in register RG_ANT_DIV */
#define ENABLE_ANTENNA_0        (1)
/** Constant ENABLE_ANTENNA_1 for sub-register SR_ANT_CTRL in register RG_ANT_DIV */
#define ENABLE_ANTENNA_1        (2)
/** Constant ENABLE_ANTENNA_X for sub-register SR_ANT_CTRL in register RG_ANT_DIV */
#define ENABLE_ANTENNA_X        (3)
/** Constant CCA_START for sub-register CCA_REQUEST in register RG_PHY_CC_CCA */
#define CCA_START               (1)
/** Access parameters for sub-register AES_DIR in register @ref RG_AES_CTRL */
#define SR_AES_DIR   0x03, 0x08, 3
/** Access parameters for sub-register AES_MODE in register @ref RG_AES_CTRL */
#define SR_AES_MODE   0x03, 0x70, 4
/** Access parameters for sub-register AES_REQUEST in register @ref RG_AES_CTRL */
#define SR_AES_REQUEST   0x03, 0x80, 7
/** Transceiver commands */
typedef enum trx_cmd_tag {
    /** Constant CMD_NOP for sub-register SR_TRX_CMD */
	CMD_NOP = (0),

    /** Constant CMD_TX_START for sub-register SR_TRX_CMD */
	CMD_TX_START = (2),

    /** Constant CMD_FORCE_TRX_OFF for sub-register SR_TRX_CMD */
	CMD_FORCE_TRX_OFF = (3),

    /** Constant CMD_FORCE_PLL_ON for sub-register SR_TRX_CMD */
	CMD_FORCE_PLL_ON = (4),

    /** Constant CMD_RX_ON for sub-register SR_TRX_CMD */
	CMD_RX_ON = (6),

    /** Constant CMD_TRX_OFF for sub-register SR_TRX_CMD */
	CMD_TRX_OFF = (8),

    /** Constant CMD_PLL_ON for sub-register SR_TRX_CMD */
	CMD_PLL_ON = (9),

    /** Software implemented command */
	CMD_SLEEP = (15),

    /** Constant CMD_RX_AACK_ON for sub-register SR_TRX_CMD */
	CMD_RX_AACK_ON = (22),

    /** Constant CMD_TX_ARET_ON for sub-register SR_TRX_CMD */
	CMD_TX_ARET_ON = (25)
} SHORTENUM trx_cmd_t;


/** Transceiver interrupt reasons */
typedef enum trx_irq_reason_tag {
    /** No interrupt is indicated by IRQ_STATUS register */
	TRX_NO_IRQ = (0x00),

    /** PLL goes to lock-state. */
	TRX_IRQ_PLL_LOCK = (0x01),

    /** Signals an unlocked PLL */
	TRX_IRQ_PLL_UNLOCK = (0x02),

    /** Signals begin of a receiving frame */
	TRX_IRQ_RX_START = (0x04),

    /** Signals end of frames (transmit and receive) */
	TRX_IRQ_TRX_END = (0x08),

    /**
     * Multi-functional interrupt:
     * AWAKE_END: Indicates that the radio transceiver reached TRX_OFF state after P_ON, RESET, or SLEEP states.
     * CCA_ED_READY: Signals the end of a CCA or ED measurement.
     */
	TRX_IRQ_CCA_ED_READY = (0x10),

    /** Signals an address match. */
	TRX_IRQ_AMI = (0x20),

    /** Signals a FIFO underrun */
	TRX_IRQ_TRX_UR = (0x40),

    /** Signals low battery */
	TRX_IRQ_BAT_LOW = (0x80)
} SHORTENUM trx_irq_reason_t;


/** Transceiver states */
typedef enum tal_trx_status_tag {
    /** Constant P_ON for sub-register SR_TRX_STATUS */
	P_ON = (0),

    /** Constant BUSY_RX for sub-register SR_TRX_STATUS */
	BUSY_RX = (1),

    /** Constant BUSY_TX for sub-register SR_TRX_STATUS */
	BUSY_TX = (2),

    /** Constant RX_ON for sub-register SR_TRX_STATUS */
	RX_ON = (6),

    /** Constant TRX_OFF for sub-register SR_TRX_STATUS */
	TRX_OFF = (8),

    /** Constant PLL_ON for sub-register SR_TRX_STATUS */
	PLL_ON = (9),

    /** Constant SLEEP for sub-register SR_TRX_STATUS */
	TRX_SLEEP = (15),

    /** Constant BUSY_RX_AACK for sub-register SR_TRX_STATUS */
	BUSY_RX_AACK = (17),

    /** Constant BUSY_TX_ARET for sub-register SR_TRX_STATUS */
	BUSY_TX_ARET = (18),

    /** Constant RX_AACK_ON for sub-register SR_TRX_STATUS */
	RX_AACK_ON = (22),

    /** Constant TX_ARET_ON for sub-register SR_TRX_STATUS */
	TX_ARET_ON = (25),

    /** Constant RX_ON_NOCLK for sub-register SR_TRX_STATUS */
	RX_ON_NOCLK = (28),

    /** Constant RX_AACK_ON_NOCLK for sub-register SR_TRX_STATUS */
	RX_AACK_ON_NOCLK = (29),

    /** Constant BUSY_RX_AACK_NOCLK for sub-register SR_TRX_STATUS */
	BUSY_RX_AACK_NOCLK = (30),

    /** Constant STATE_TRANSITION_IN_PROGRESS for sub-register SR_TRX_STATUS */
	STATE_TRANSITION_IN_PROGRESS = (31)
} SHORTENUM tal_trx_status_t;


/** Transceiver's trac status */
typedef enum trx_trac_status_tag {
	TRAC_SUCCESS = 0,
	TRAC_CHANNEL_ACCESS_FAILURE = 1,
	TRAC_INVALID = 2
} SHORTENUM trx_trac_status_t;

/** TAL states */
typedef enum tal_state_tag {
	TAL_IDLE = 0,
	TAL_TX_AUTO = 1,
	TAL_TX_END = 2
} SHORTENUM tal_state_t;

extern bool at86rfx_frame_rx;


/**
 * These are the return values of the AT86RF231 APIs.
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


//! @defgroup at86rf231_api Accessing AT86RF231 Transceiver
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

#endif /* AT86RF231_H */
