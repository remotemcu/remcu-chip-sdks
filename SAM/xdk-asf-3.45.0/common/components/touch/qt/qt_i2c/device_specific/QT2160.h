/**
 * \file
 *
 * \brief Header file for the AT42QT2160 device.
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

#ifndef QT2160_H_INCLUDED
#define QT2160_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup qt_device_i2c_group
 *
 * @{
 */

/**
 * \defgroup qt_at42qt2160_group Definitions for Atmel AT42QT2160 device
 *
 * @{
 */

/** AT42QT2160 Chip ID */
#define QT_DEVICE_ID    0x11

/**
 * Definitions for AT42QT2160 registers map.
 *
 * This address map can be used for read or write particular information
 * from QT device using I2C interface.
 */
enum qt_reg_map {
	QT_REG_CHIP_ID = 0,
	QT_REG_CODE_VERSION,
	QT_REG_GENERAL_STATUS,
	QT_REG_KEY_STATUS_1,
	QT_REG_KEY_STATUS_2,
	QT_REG_SLIDER_POSITION,
	QT_REG_GPIO_READ,
	QT_REG_CALIBRATE = 10,
	QT_REG_RESET,
	QT_REG_LP_MODE,
	QT_REG_BREP,
	QT_REG_NEG_DRIFT_COMP = 15,
	QT_REG_POS_DRIFT_COMP,
	QT_REG_DI_LIMIT,
	QT_REG_NEG_RECAL_DELAY,
	QT_REG_DRIFT_HOLD_TIME,
	QT_REG_SLIDER_CONTROL,
	QT_REG_SLIDER_OPTIONS,
	QT_REG_KEY0_AKS_GRP,
	QT_REG_KEY1_AKS_GRP,
	QT_REG_KEY2_AKS_GRP,
	QT_REG_KEY3_AKS_GRP,
	QT_REG_KEY4_AKS_GRP,
	QT_REG_KEY5_AKS_GRP,
	QT_REG_KEY6_AKS_GRP,
	QT_REG_KEY7_AKS_GRP,
	QT_REG_KEY8_AKS_GRP,
	QT_REG_KEY9_AKS_GRP,
	QT_REG_KEY10_AKS_GRP,
	QT_REG_KEY11_AKS_GRP,
	QT_REG_KEY12_AKS_GRP,
	QT_REG_KEY13_AKS_GRP,
	QT_REG_KEY14_AKS_GRP,
	QT_REG_KEY15_AKS_GRP,
	QT_REG_KEY0_NTHR,
	QT_REG_KEY1_NTHR,
	QT_REG_KEY2_NTHR,
	QT_REG_KEY3_NTHR,
	QT_REG_KEY4_NTHR,
	QT_REG_KEY5_NTHR,
	QT_REG_KEY6_NTHR,
	QT_REG_KEY7_NTHR,
	QT_REG_KEY8_NTHR,
	QT_REG_KEY9_NTHR,
	QT_REG_KEY10_NTHR,
	QT_REG_KEY11_NTHR,
	QT_REG_KEY12_NTHR,
	QT_REG_KEY13_NTHR,
	QT_REG_KEY14_NTHR,
	QT_REG_KEY15_NTHR,
	QT_REG_KEY0_BL,
	QT_REG_KEY1_BL,
	QT_REG_KEY2_BL,
	QT_REG_KEY3_BL,
	QT_REG_KEY4_BL,
	QT_REG_KEY5_BL,
	QT_REG_KEY6_BL,
	QT_REG_KEY7_BL,
	QT_REG_KEY8_BL,
	QT_REG_KEY9_BL,
	QT_REG_KEY10_BL,
	QT_REG_KEY11_BL,
	QT_REG_KEY12_BL,
	QT_REG_KEY13_BL,
	QT_REG_KEY14_BL,
	QT_REG_KEY15_BL,
	QT_REG_GPO_DRIVE,
	QT_REG_GPIO_DRIVE,
	QT_REG_GPIO_DIR = 73,
	QT_REG_GPO_PWM,
	QT_REG_GPIO_PWM,
	QT_REG_PWM_LEVEL,
	QT_REG_GPIO_WAKE,
	QT_REG_COMM_CHG_KEYS_1,
	QT_REG_COMM_CHG_KEYS_2,
	QT_REG_KEY0_SIGNAL = 100,
	QT_REG_KEY1_SIGNAL = 102,
	QT_REG_KEY2_SIGNAL = 104,
	QT_REG_KEY3_SIGNAL = 106,
	QT_REG_KEY4_SIGNAL = 108,
	QT_REG_KEY5_SIGNAL = 110,
	QT_REG_KEY6_SIGNAL = 112,
	QT_REG_KEY7_SIGNAL = 114,
	QT_REG_KEY8_SIGNAL = 116,
	QT_REG_KEY9_SIGNAL = 118,
	QT_REG_KEY10_SIGNAL = 120,
	QT_REG_KEY11_SIGNAL = 122,
	QT_REG_KEY12_SIGNAL = 124,
	QT_REG_KEY13_SIGNAL = 126,
	QT_REG_KEY14_SIGNAL = 128,
	QT_REG_KEY15_SIGNAL = 130,
	QT_REG_KEY0_REFERENCE = 132,
	QT_REG_KEY1_REFERENCE = 134,
	QT_REG_KEY2_REFERENCE = 136,
	QT_REG_KEY3_REFERENCE = 138,
	QT_REG_KEY4_REFERENCE = 140,
	QT_REG_KEY5_REFERENCE = 142,
	QT_REG_KEY6_REFERENCE = 144,
	QT_REG_KEY7_REFERENCE = 146,
	QT_REG_KEY8_REFERENCE = 148,
	QT_REG_KEY9_REFERENCE = 150,
	QT_REG_KEY10_REFERENCE = 152,
	QT_REG_KEY11_REFERENCE = 154,
	QT_REG_KEY12_REFERENCE = 156,
	QT_REG_KEY13_REFERENCE = 158,
	QT_REG_KEY14_REFERENCE = 160,
	QT_REG_KEY15_REFERENCE = 162,
};

/** Start address of QT device setup block */
#define QT_SETUPS_BLOCK_ADDR    12

/**
 * Definitions for AT42QT2160 setup block.
 */
struct qt_setup_block {
	/** LP Mode */
	uint8_t lp_mode;

	/** Burst Repetition */
	uint8_t burst_repetition;

	/** Unused address */
	uint8_t reserved;

	/** Neg Drift Compensation */
	uint8_t neg_drift;

	/** Pos Drift Compensation */
	uint8_t pos_drift;

	/** Normal Detect Integrator */
	uint8_t detect_integrator;

	/** Negative Recal Delay */
	uint8_t negative_recal_delay;

	/** Drift Hold Time/Awake Timeout */
	uint8_t dht_awake;

	/** Slider Control */
	uint8_t slider_num_keys : 4;    /* Number of keys */
	uint8_t slider_hyst : 4;        /* Hysteresis */

	/** Slider Options */
	uint8_t slider_resolution; /* Resolution */
#define QT_SLIDER_RESOLUTION_2_BIT    6
#define QT_SLIDER_RESOLUTION_3_BIT    5
#define QT_SLIDER_RESOLUTION_4_BIT    4
#define QT_SLIDER_RESOLUTION_5_BIT    3
#define QT_SLIDER_RESOLUTION_6_BIT    2
#define QT_SLIDER_RESOLUTION_7_BIT    1
#define QT_SLIDER_RESOLUTION_8_BIT    0

	/** Key control (AKS Group) */
	uint8_t key0_aks;
	uint8_t key1_aks;
	uint8_t key2_aks;
	uint8_t key3_aks;
	uint8_t key4_aks;
	uint8_t key5_aks;
	uint8_t key6_aks;
	uint8_t key7_aks;
	uint8_t key8_aks;
	uint8_t key9_aks;
	uint8_t key10_aks;
	uint8_t key11_aks;
	uint8_t key12_aks;
	uint8_t key13_aks;
	uint8_t key14_aks;
	uint8_t key15_aks;
#define QT_KEY_AKS_GROUP_NONE    0
#define QT_KEY_AKS_GROUP_1       1
#define QT_KEY_AKS_GROUP_2       2
#define QT_KEY_AKS_GROUP_3       3

	/** Negative Threshold (NTHR) */
	uint8_t key0_nthr;
	uint8_t key1_nthr;
	uint8_t key2_nthr;
	uint8_t key3_nthr;
	uint8_t key4_nthr;
	uint8_t key5_nthr;
	uint8_t key6_nthr;
	uint8_t key7_nthr;
	uint8_t key8_nthr;
	uint8_t key9_nthr;
	uint8_t key10_nthr;
	uint8_t key11_nthr;
	uint8_t key12_nthr;
	uint8_t key13_nthr;
	uint8_t key14_nthr;
	uint8_t key15_nthr;

	/** Burst Length (BL) */
	uint8_t key0_burst_length;
	uint8_t key1_burst_length;
	uint8_t key2_burst_length;
	uint8_t key3_burst_length;
	uint8_t key4_burst_length;
	uint8_t key5_burst_length;
	uint8_t key6_burst_length;
	uint8_t key7_burst_length;
	uint8_t key8_burst_length;
	uint8_t key9_burst_length;
	uint8_t key10_burst_length;
	uint8_t key11_burst_length;
	uint8_t key12_burst_length;
	uint8_t key13_burst_length;
	uint8_t key14_burst_length;
	uint8_t key15_burst_length;

	/** GPIO/GPO Drive */
	uint8_t gpio_gpo_drive1;        /* Shared X line GPOs */
	uint8_t gpio_gpo_drive2;        /* GPIO Drive */

	/** Unused address */
	uint8_t reserved1;

	/** GPIO Direction */
	uint8_t gpio_direction;

	/** GPIO/GPO PWM */
	uint8_t gpio_gpo_pwm1;  /* Shared X line GPOs */
	uint8_t gpio_gpo_pwm2;  /* GPIOs */

	/** PWM Level */
	uint8_t pwm_level;

	/** GPIO Wake */
	uint8_t gpio_wake;

	/** Common Change keys */
	uint8_t cc_keys1; /* key0 to key7 */
	uint8_t cc_keys2; /* key8 to key15 */
};

/**
 * Structure for QT2160 device-status, include:
 *
 * \verbatim
 *
 * QtStatus[0] - General Status
 *     bit0 - SDET : This bit is set if a touch is detected on the slider.
 *     bit1 - CC : This Common Change bit is set if all the selected
 *                 keys have a signal change of more than half the
 *                 detection threshold, NTHR.
 *     bit6 - CYCLE OVERRUN : This bit is set if the cycle time more than 16ms.
 *     bit7 - RESET : This bit is set after a reset
 *
 * QtStatus[1] - Key Status
 *     bits 0 - 7 : Detect status for keys 0 to 7 (Touched keys report as 1)
 *
 * QtStatus[2] - Key Status
 *     bits 0 - 7 : Detect status for keys 8 to 15 (Touched keys report as 1)
 *
 * QtStatus[3] - Slider Touch Position
 *     bits 0 - 7 : Last position of the touch on the slider
 *
 * QtStatus[4] - GPIO Read
 *     bits 2 - 4 : indicates the state of GPIO1 to GPIO3
 *                  that are configured as inputs
 *
 * \endverbatim
 */
struct qt_status {
	uint8_t general_status;  /**< General Status */
#define QT_GENERAL_STATUS_SDET              (1u << 0)
#define QT_GENERAL_STATUS_CC                (1u << 1)
#define QT_GENERAL_STATUS_CYCLE_OVER_RUN    (1u << 6)
#define QT_GENERAL_STATUS_RESET             (1u << 8)
	uint8_t key_status_1;    /**< Key Status 1 */
	uint8_t key_status_2;    /**< Key Status 2 */
	uint8_t slider_position; /**< Slider Touch Position */
	uint8_t gpio_read;       /**< GPIO Read */
};

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* QT2160_H_INCLUDED */
