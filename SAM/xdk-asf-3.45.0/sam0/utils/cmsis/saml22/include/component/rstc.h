/**
 * \file
 *
 * \brief Component description for RSTC
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _SAML22_RSTC_COMPONENT_
#define _SAML22_RSTC_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR RSTC */
/* ========================================================================== */
/** \addtogroup SAML22_RSTC Reset Controller */
/*@{*/

#define RSTC_U2239
#define REV_RSTC                    0x300

/* -------- RSTC_RCAUSE : (RSTC Offset: 0x00) (R/   8) Reset Cause -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  POR:1;            /*!< bit:      0  Power On Reset                     */
    uint8_t  BODCORE:1;        /*!< bit:      1  Brown Out CORE Detector Reset      */
    uint8_t  BODVDD:1;         /*!< bit:      2  Brown Out VDD Detector Reset       */
    uint8_t  :1;               /*!< bit:      3  Reserved                           */
    uint8_t  EXT:1;            /*!< bit:      4  External Reset                     */
    uint8_t  WDT:1;            /*!< bit:      5  Watchdog Reset                     */
    uint8_t  SYST:1;           /*!< bit:      6  System Reset Request               */
    uint8_t  BACKUP:1;         /*!< bit:      7  Backup Reset                       */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} RSTC_RCAUSE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RSTC_RCAUSE_OFFSET          0x00         /**< \brief (RSTC_RCAUSE offset) Reset Cause */

#define RSTC_RCAUSE_POR_Pos         0            /**< \brief (RSTC_RCAUSE) Power On Reset */
#define RSTC_RCAUSE_POR             (0x1u << RSTC_RCAUSE_POR_Pos)
#define RSTC_RCAUSE_BODCORE_Pos     1            /**< \brief (RSTC_RCAUSE) Brown Out CORE Detector Reset */
#define RSTC_RCAUSE_BODCORE         (0x1u << RSTC_RCAUSE_BODCORE_Pos)
#define RSTC_RCAUSE_BODVDD_Pos      2            /**< \brief (RSTC_RCAUSE) Brown Out VDD Detector Reset */
#define RSTC_RCAUSE_BODVDD          (0x1u << RSTC_RCAUSE_BODVDD_Pos)
#define RSTC_RCAUSE_EXT_Pos         4            /**< \brief (RSTC_RCAUSE) External Reset */
#define RSTC_RCAUSE_EXT             (0x1u << RSTC_RCAUSE_EXT_Pos)
#define RSTC_RCAUSE_WDT_Pos         5            /**< \brief (RSTC_RCAUSE) Watchdog Reset */
#define RSTC_RCAUSE_WDT             (0x1u << RSTC_RCAUSE_WDT_Pos)
#define RSTC_RCAUSE_SYST_Pos        6            /**< \brief (RSTC_RCAUSE) System Reset Request */
#define RSTC_RCAUSE_SYST            (0x1u << RSTC_RCAUSE_SYST_Pos)
#define RSTC_RCAUSE_BACKUP_Pos      7            /**< \brief (RSTC_RCAUSE) Backup Reset */
#define RSTC_RCAUSE_BACKUP          (0x1u << RSTC_RCAUSE_BACKUP_Pos)
#define RSTC_RCAUSE_MASK            0xF7u        /**< \brief (RSTC_RCAUSE) MASK Register */

/* -------- RSTC_BKUPEXIT : (RSTC Offset: 0x02) (R/   8) Backup Exit Source -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  EXTWAKE:1;        /*!< bit:      0  External Wakeup                    */
    uint8_t  RTC:1;            /*!< bit:      1  Real Timer Counter Interrupt       */
    uint8_t  BBPS:1;           /*!< bit:      2  Battery Backup Power Switch        */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} RSTC_BKUPEXIT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RSTC_BKUPEXIT_OFFSET        0x02         /**< \brief (RSTC_BKUPEXIT offset) Backup Exit Source */
#define RSTC_BKUPEXIT_RESETVALUE    0x00u        /**< \brief (RSTC_BKUPEXIT reset_value) Backup Exit Source */

#define RSTC_BKUPEXIT_EXTWAKE_Pos   0            /**< \brief (RSTC_BKUPEXIT) External Wakeup */
#define RSTC_BKUPEXIT_EXTWAKE       (0x1u << RSTC_BKUPEXIT_EXTWAKE_Pos)
#define RSTC_BKUPEXIT_RTC_Pos       1            /**< \brief (RSTC_BKUPEXIT) Real Timer Counter Interrupt */
#define RSTC_BKUPEXIT_RTC           (0x1u << RSTC_BKUPEXIT_RTC_Pos)
#define RSTC_BKUPEXIT_BBPS_Pos      2            /**< \brief (RSTC_BKUPEXIT) Battery Backup Power Switch */
#define RSTC_BKUPEXIT_BBPS          (0x1u << RSTC_BKUPEXIT_BBPS_Pos)
#define RSTC_BKUPEXIT_MASK          0x07u        /**< \brief (RSTC_BKUPEXIT) MASK Register */

/** \brief RSTC hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  __I  RSTC_RCAUSE_Type          RCAUSE;      /**< \brief Offset: 0x00 (R/   8) Reset Cause */
       RoReg8                    Reserved1[0x1];
  __I  RSTC_BKUPEXIT_Type        BKUPEXIT;    /**< \brief Offset: 0x02 (R/   8) Backup Exit Source */
} Rstc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAML22_RSTC_COMPONENT_ */
