/**
 * \file
 *
 * \brief Component description for PM
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

#ifndef _SAMC21_PM_COMPONENT_
#define _SAMC21_PM_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR PM */
/* ========================================================================== */
/** \addtogroup SAMC21_PM Power Manager */
/*@{*/

#define PM_U2240
#define REV_PM                      0x210

/* -------- PM_SLEEPCFG : (PM Offset: 0x01) (R/W  8) Sleep Configuration -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  SLEEPMODE:3;      /*!< bit:  0.. 2  Sleep Mode                         */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} PM_SLEEPCFG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PM_SLEEPCFG_OFFSET          0x01         /**< \brief (PM_SLEEPCFG offset) Sleep Configuration */
#define PM_SLEEPCFG_RESETVALUE      0x00ul       /**< \brief (PM_SLEEPCFG reset_value) Sleep Configuration */

#define PM_SLEEPCFG_SLEEPMODE_Pos   0            /**< \brief (PM_SLEEPCFG) Sleep Mode */
#define PM_SLEEPCFG_SLEEPMODE_Msk   (0x7ul << PM_SLEEPCFG_SLEEPMODE_Pos)
#define PM_SLEEPCFG_SLEEPMODE(value) (PM_SLEEPCFG_SLEEPMODE_Msk & ((value) << PM_SLEEPCFG_SLEEPMODE_Pos))
#define   PM_SLEEPCFG_SLEEPMODE_IDLE0_Val 0x0ul  /**< \brief (PM_SLEEPCFG) CPU clock is OFF */
#define   PM_SLEEPCFG_SLEEPMODE_IDLE1_Val 0x1ul  /**< \brief (PM_SLEEPCFG) AHB clock is OFF */
#define   PM_SLEEPCFG_SLEEPMODE_IDLE2_Val 0x2ul  /**< \brief (PM_SLEEPCFG) APB clock are OFF */
#define   PM_SLEEPCFG_SLEEPMODE_STANDBY_Val 0x4ul  /**< \brief (PM_SLEEPCFG) All Clocks are OFF */
#define PM_SLEEPCFG_SLEEPMODE_IDLE0 (PM_SLEEPCFG_SLEEPMODE_IDLE0_Val << PM_SLEEPCFG_SLEEPMODE_Pos)
#define PM_SLEEPCFG_SLEEPMODE_IDLE1 (PM_SLEEPCFG_SLEEPMODE_IDLE1_Val << PM_SLEEPCFG_SLEEPMODE_Pos)
#define PM_SLEEPCFG_SLEEPMODE_IDLE2 (PM_SLEEPCFG_SLEEPMODE_IDLE2_Val << PM_SLEEPCFG_SLEEPMODE_Pos)
#define PM_SLEEPCFG_SLEEPMODE_STANDBY (PM_SLEEPCFG_SLEEPMODE_STANDBY_Val << PM_SLEEPCFG_SLEEPMODE_Pos)
#define PM_SLEEPCFG_MASK            0x07ul       /**< \brief (PM_SLEEPCFG) MASK Register */

/* -------- PM_STDBYCFG : (PM Offset: 0x08) (R/W 16) Standby Configuration -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t :6;               /*!< bit:  0.. 5  Reserved                           */
    uint16_t VREGSMOD:2;       /*!< bit:  6.. 7  Voltage Regulator Standby mode     */
    uint16_t :2;               /*!< bit:  8.. 9  Reserved                           */
    uint16_t BBIASHS:1;        /*!< bit:     10  Back Bias for HMCRAMCHS            */
    uint16_t :5;               /*!< bit: 11..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} PM_STDBYCFG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PM_STDBYCFG_OFFSET          0x08         /**< \brief (PM_STDBYCFG offset) Standby Configuration */
#define PM_STDBYCFG_RESETVALUE      0x0400ul     /**< \brief (PM_STDBYCFG reset_value) Standby Configuration */

#define PM_STDBYCFG_VREGSMOD_Pos    6            /**< \brief (PM_STDBYCFG) Voltage Regulator Standby mode */
#define PM_STDBYCFG_VREGSMOD_Msk    (0x3ul << PM_STDBYCFG_VREGSMOD_Pos)
#define PM_STDBYCFG_VREGSMOD(value) (PM_STDBYCFG_VREGSMOD_Msk & ((value) << PM_STDBYCFG_VREGSMOD_Pos))
#define   PM_STDBYCFG_VREGSMOD_AUTO_Val   0x0ul  /**< \brief (PM_STDBYCFG) Automatic mode */
#define   PM_STDBYCFG_VREGSMOD_PERFORMANCE_Val 0x1ul  /**< \brief (PM_STDBYCFG) Performance oriented */
#define   PM_STDBYCFG_VREGSMOD_LP_Val     0x2ul  /**< \brief (PM_STDBYCFG) Low Power oriented */
#define PM_STDBYCFG_VREGSMOD_AUTO   (PM_STDBYCFG_VREGSMOD_AUTO_Val << PM_STDBYCFG_VREGSMOD_Pos)
#define PM_STDBYCFG_VREGSMOD_PERFORMANCE (PM_STDBYCFG_VREGSMOD_PERFORMANCE_Val << PM_STDBYCFG_VREGSMOD_Pos)
#define PM_STDBYCFG_VREGSMOD_LP     (PM_STDBYCFG_VREGSMOD_LP_Val   << PM_STDBYCFG_VREGSMOD_Pos)
#define PM_STDBYCFG_BBIASHS_Pos     10           /**< \brief (PM_STDBYCFG) Back Bias for HMCRAMCHS */
#define PM_STDBYCFG_BBIASHS_Msk     (0x1ul << PM_STDBYCFG_BBIASHS_Pos)
#define PM_STDBYCFG_BBIASHS(value)  (PM_STDBYCFG_BBIASHS_Msk & ((value) << PM_STDBYCFG_BBIASHS_Pos))
#define PM_STDBYCFG_MASK            0x04C0ul     /**< \brief (PM_STDBYCFG) MASK Register */

/** \brief PM hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
       RoReg8                    Reserved1[0x1];
  __IO PM_SLEEPCFG_Type          SLEEPCFG;    /**< \brief Offset: 0x01 (R/W  8) Sleep Configuration */
       RoReg8                    Reserved2[0x6];
  __IO PM_STDBYCFG_Type          STDBYCFG;    /**< \brief Offset: 0x08 (R/W 16) Standby Configuration */
} Pm;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMC21_PM_COMPONENT_ */
