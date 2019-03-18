/**
 * \file
 *
 * \brief Component description for SUPC
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

#ifndef _SAMC21_SUPC_COMPONENT_
#define _SAMC21_SUPC_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR SUPC */
/* ========================================================================== */
/** \addtogroup SAMC21_SUPC Supply Controller */
/*@{*/

#define SUPC_U2117
#define REV_SUPC                    0x210

/* -------- SUPC_INTENCLR : (SUPC Offset: 0x00) (R/W 32) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t BODVDDRDY:1;      /*!< bit:      0  BODVDD Ready                       */
    uint32_t BODVDDDET:1;      /*!< bit:      1  BODVDD Detection                   */
    uint32_t BVDDSRDY:1;       /*!< bit:      2  BODVDD Synchronization Ready       */
    uint32_t BODCORERDY:1;     /*!< bit:      3  BODCORE Ready                      */
    uint32_t BODCOREDET:1;     /*!< bit:      4  BODCORE Detection                  */
    uint32_t BCORESRDY:1;      /*!< bit:      5  BODCORE Synchronization Ready      */
    uint32_t :26;              /*!< bit:  6..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SUPC_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_INTENCLR_OFFSET        0x00         /**< \brief (SUPC_INTENCLR offset) Interrupt Enable Clear */
#define SUPC_INTENCLR_RESETVALUE    0x00000000ul /**< \brief (SUPC_INTENCLR reset_value) Interrupt Enable Clear */

#define SUPC_INTENCLR_BODVDDRDY_Pos 0            /**< \brief (SUPC_INTENCLR) BODVDD Ready */
#define SUPC_INTENCLR_BODVDDRDY     (0x1ul << SUPC_INTENCLR_BODVDDRDY_Pos)
#define SUPC_INTENCLR_BODVDDDET_Pos 1            /**< \brief (SUPC_INTENCLR) BODVDD Detection */
#define SUPC_INTENCLR_BODVDDDET     (0x1ul << SUPC_INTENCLR_BODVDDDET_Pos)
#define SUPC_INTENCLR_BVDDSRDY_Pos  2            /**< \brief (SUPC_INTENCLR) BODVDD Synchronization Ready */
#define SUPC_INTENCLR_BVDDSRDY      (0x1ul << SUPC_INTENCLR_BVDDSRDY_Pos)
#define SUPC_INTENCLR_BODCORERDY_Pos 3            /**< \brief (SUPC_INTENCLR) BODCORE Ready */
#define SUPC_INTENCLR_BODCORERDY    (0x1ul << SUPC_INTENCLR_BODCORERDY_Pos)
#define SUPC_INTENCLR_BODCOREDET_Pos 4            /**< \brief (SUPC_INTENCLR) BODCORE Detection */
#define SUPC_INTENCLR_BODCOREDET    (0x1ul << SUPC_INTENCLR_BODCOREDET_Pos)
#define SUPC_INTENCLR_BCORESRDY_Pos 5            /**< \brief (SUPC_INTENCLR) BODCORE Synchronization Ready */
#define SUPC_INTENCLR_BCORESRDY     (0x1ul << SUPC_INTENCLR_BCORESRDY_Pos)
#define SUPC_INTENCLR_MASK          0x0000003Ful /**< \brief (SUPC_INTENCLR) MASK Register */

/* -------- SUPC_INTENSET : (SUPC Offset: 0x04) (R/W 32) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t BODVDDRDY:1;      /*!< bit:      0  BODVDD Ready                       */
    uint32_t BODVDDDET:1;      /*!< bit:      1  BODVDD Detection                   */
    uint32_t BVDDSRDY:1;       /*!< bit:      2  BODVDD Synchronization Ready       */
    uint32_t BODCORERDY:1;     /*!< bit:      3  BODCORE Ready                      */
    uint32_t BODCOREDET:1;     /*!< bit:      4  BODCORE Detection                  */
    uint32_t BCORESRDY:1;      /*!< bit:      5  BODCORE Synchronization Ready      */
    uint32_t :26;              /*!< bit:  6..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SUPC_INTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_INTENSET_OFFSET        0x04         /**< \brief (SUPC_INTENSET offset) Interrupt Enable Set */
#define SUPC_INTENSET_RESETVALUE    0x00000000ul /**< \brief (SUPC_INTENSET reset_value) Interrupt Enable Set */

#define SUPC_INTENSET_BODVDDRDY_Pos 0            /**< \brief (SUPC_INTENSET) BODVDD Ready */
#define SUPC_INTENSET_BODVDDRDY     (0x1ul << SUPC_INTENSET_BODVDDRDY_Pos)
#define SUPC_INTENSET_BODVDDDET_Pos 1            /**< \brief (SUPC_INTENSET) BODVDD Detection */
#define SUPC_INTENSET_BODVDDDET     (0x1ul << SUPC_INTENSET_BODVDDDET_Pos)
#define SUPC_INTENSET_BVDDSRDY_Pos  2            /**< \brief (SUPC_INTENSET) BODVDD Synchronization Ready */
#define SUPC_INTENSET_BVDDSRDY      (0x1ul << SUPC_INTENSET_BVDDSRDY_Pos)
#define SUPC_INTENSET_BODCORERDY_Pos 3            /**< \brief (SUPC_INTENSET) BODCORE Ready */
#define SUPC_INTENSET_BODCORERDY    (0x1ul << SUPC_INTENSET_BODCORERDY_Pos)
#define SUPC_INTENSET_BODCOREDET_Pos 4            /**< \brief (SUPC_INTENSET) BODCORE Detection */
#define SUPC_INTENSET_BODCOREDET    (0x1ul << SUPC_INTENSET_BODCOREDET_Pos)
#define SUPC_INTENSET_BCORESRDY_Pos 5            /**< \brief (SUPC_INTENSET) BODCORE Synchronization Ready */
#define SUPC_INTENSET_BCORESRDY     (0x1ul << SUPC_INTENSET_BCORESRDY_Pos)
#define SUPC_INTENSET_MASK          0x0000003Ful /**< \brief (SUPC_INTENSET) MASK Register */

/* -------- SUPC_INTFLAG : (SUPC Offset: 0x08) (R/W 32) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint32_t BODVDDRDY:1;      /*!< bit:      0  BODVDD Ready                       */
    __I uint32_t BODVDDDET:1;      /*!< bit:      1  BODVDD Detection                   */
    __I uint32_t BVDDSRDY:1;       /*!< bit:      2  BODVDD Synchronization Ready       */
    __I uint32_t BODCORERDY:1;     /*!< bit:      3  BODCORE Ready                      */
    __I uint32_t BODCOREDET:1;     /*!< bit:      4  BODCORE Detection                  */
    __I uint32_t BCORESRDY:1;      /*!< bit:      5  BODCORE Synchronization Ready      */
    __I uint32_t :26;              /*!< bit:  6..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SUPC_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_INTFLAG_OFFSET         0x08         /**< \brief (SUPC_INTFLAG offset) Interrupt Flag Status and Clear */
#define SUPC_INTFLAG_RESETVALUE     0x00000000ul /**< \brief (SUPC_INTFLAG reset_value) Interrupt Flag Status and Clear */

#define SUPC_INTFLAG_BODVDDRDY_Pos  0            /**< \brief (SUPC_INTFLAG) BODVDD Ready */
#define SUPC_INTFLAG_BODVDDRDY      (0x1ul << SUPC_INTFLAG_BODVDDRDY_Pos)
#define SUPC_INTFLAG_BODVDDDET_Pos  1            /**< \brief (SUPC_INTFLAG) BODVDD Detection */
#define SUPC_INTFLAG_BODVDDDET      (0x1ul << SUPC_INTFLAG_BODVDDDET_Pos)
#define SUPC_INTFLAG_BVDDSRDY_Pos   2            /**< \brief (SUPC_INTFLAG) BODVDD Synchronization Ready */
#define SUPC_INTFLAG_BVDDSRDY       (0x1ul << SUPC_INTFLAG_BVDDSRDY_Pos)
#define SUPC_INTFLAG_BODCORERDY_Pos 3            /**< \brief (SUPC_INTFLAG) BODCORE Ready */
#define SUPC_INTFLAG_BODCORERDY     (0x1ul << SUPC_INTFLAG_BODCORERDY_Pos)
#define SUPC_INTFLAG_BODCOREDET_Pos 4            /**< \brief (SUPC_INTFLAG) BODCORE Detection */
#define SUPC_INTFLAG_BODCOREDET     (0x1ul << SUPC_INTFLAG_BODCOREDET_Pos)
#define SUPC_INTFLAG_BCORESRDY_Pos  5            /**< \brief (SUPC_INTFLAG) BODCORE Synchronization Ready */
#define SUPC_INTFLAG_BCORESRDY      (0x1ul << SUPC_INTFLAG_BCORESRDY_Pos)
#define SUPC_INTFLAG_MASK           0x0000003Ful /**< \brief (SUPC_INTFLAG) MASK Register */

/* -------- SUPC_STATUS : (SUPC Offset: 0x0C) (R/  32) Power and Clocks Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t BODVDDRDY:1;      /*!< bit:      0  BODVDD Ready                       */
    uint32_t BODVDDDET:1;      /*!< bit:      1  BODVDD Detection                   */
    uint32_t BVDDSRDY:1;       /*!< bit:      2  BODVDD Synchronization Ready       */
    uint32_t BODCORERDY:1;     /*!< bit:      3  BODCORE Ready                      */
    uint32_t BODCOREDET:1;     /*!< bit:      4  BODCORE Detection                  */
    uint32_t BCORESRDY:1;      /*!< bit:      5  BODCORE Synchronization Ready      */
    uint32_t :26;              /*!< bit:  6..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SUPC_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_STATUS_OFFSET          0x0C         /**< \brief (SUPC_STATUS offset) Power and Clocks Status */
#define SUPC_STATUS_RESETVALUE      0x00000000ul /**< \brief (SUPC_STATUS reset_value) Power and Clocks Status */

#define SUPC_STATUS_BODVDDRDY_Pos   0            /**< \brief (SUPC_STATUS) BODVDD Ready */
#define SUPC_STATUS_BODVDDRDY       (0x1ul << SUPC_STATUS_BODVDDRDY_Pos)
#define SUPC_STATUS_BODVDDDET_Pos   1            /**< \brief (SUPC_STATUS) BODVDD Detection */
#define SUPC_STATUS_BODVDDDET       (0x1ul << SUPC_STATUS_BODVDDDET_Pos)
#define SUPC_STATUS_BVDDSRDY_Pos    2            /**< \brief (SUPC_STATUS) BODVDD Synchronization Ready */
#define SUPC_STATUS_BVDDSRDY        (0x1ul << SUPC_STATUS_BVDDSRDY_Pos)
#define SUPC_STATUS_BODCORERDY_Pos  3            /**< \brief (SUPC_STATUS) BODCORE Ready */
#define SUPC_STATUS_BODCORERDY      (0x1ul << SUPC_STATUS_BODCORERDY_Pos)
#define SUPC_STATUS_BODCOREDET_Pos  4            /**< \brief (SUPC_STATUS) BODCORE Detection */
#define SUPC_STATUS_BODCOREDET      (0x1ul << SUPC_STATUS_BODCOREDET_Pos)
#define SUPC_STATUS_BCORESRDY_Pos   5            /**< \brief (SUPC_STATUS) BODCORE Synchronization Ready */
#define SUPC_STATUS_BCORESRDY       (0x1ul << SUPC_STATUS_BCORESRDY_Pos)
#define SUPC_STATUS_MASK            0x0000003Ful /**< \brief (SUPC_STATUS) MASK Register */

/* -------- SUPC_BODVDD : (SUPC Offset: 0x10) (R/W 32) BODVDD Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t :1;               /*!< bit:      0  Reserved                           */
    uint32_t ENABLE:1;         /*!< bit:      1  Enable                             */
    uint32_t HYST:1;           /*!< bit:      2  Hysteresis Enable                  */
    uint32_t ACTION:2;         /*!< bit:  3.. 4  Action when Threshold Crossed      */
    uint32_t STDBYCFG:1;       /*!< bit:      5  Configuration in Standby mode      */
    uint32_t RUNSTDBY:1;       /*!< bit:      6  Run during Standby                 */
    uint32_t :1;               /*!< bit:      7  Reserved                           */
    uint32_t ACTCFG:1;         /*!< bit:      8  Configuration in Active mode       */
    uint32_t :3;               /*!< bit:  9..11  Reserved                           */
    uint32_t PSEL:4;           /*!< bit: 12..15  Prescaler Select                   */
    uint32_t LEVEL:6;          /*!< bit: 16..21  Threshold Level for VDD            */
    uint32_t :10;              /*!< bit: 22..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SUPC_BODVDD_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_BODVDD_OFFSET          0x10         /**< \brief (SUPC_BODVDD offset) BODVDD Control */
#define SUPC_BODVDD_RESETVALUE      0x00000000ul /**< \brief (SUPC_BODVDD reset_value) BODVDD Control */

#define SUPC_BODVDD_ENABLE_Pos      1            /**< \brief (SUPC_BODVDD) Enable */
#define SUPC_BODVDD_ENABLE          (0x1ul << SUPC_BODVDD_ENABLE_Pos)
#define SUPC_BODVDD_HYST_Pos        2            /**< \brief (SUPC_BODVDD) Hysteresis Enable */
#define SUPC_BODVDD_HYST            (0x1ul << SUPC_BODVDD_HYST_Pos)
#define SUPC_BODVDD_ACTION_Pos      3            /**< \brief (SUPC_BODVDD) Action when Threshold Crossed */
#define SUPC_BODVDD_ACTION_Msk      (0x3ul << SUPC_BODVDD_ACTION_Pos)
#define SUPC_BODVDD_ACTION(value)   (SUPC_BODVDD_ACTION_Msk & ((value) << SUPC_BODVDD_ACTION_Pos))
#define   SUPC_BODVDD_ACTION_NONE_Val     0x0ul  /**< \brief (SUPC_BODVDD) No action */
#define   SUPC_BODVDD_ACTION_RESET_Val    0x1ul  /**< \brief (SUPC_BODVDD) The BOD33 generates a reset */
#define   SUPC_BODVDD_ACTION_INT_Val      0x2ul  /**< \brief (SUPC_BODVDD) The BOD33 generates an interrupt */
#define SUPC_BODVDD_ACTION_NONE     (SUPC_BODVDD_ACTION_NONE_Val   << SUPC_BODVDD_ACTION_Pos)
#define SUPC_BODVDD_ACTION_RESET    (SUPC_BODVDD_ACTION_RESET_Val  << SUPC_BODVDD_ACTION_Pos)
#define SUPC_BODVDD_ACTION_INT      (SUPC_BODVDD_ACTION_INT_Val    << SUPC_BODVDD_ACTION_Pos)
#define SUPC_BODVDD_STDBYCFG_Pos    5            /**< \brief (SUPC_BODVDD) Configuration in Standby mode */
#define SUPC_BODVDD_STDBYCFG        (0x1ul << SUPC_BODVDD_STDBYCFG_Pos)
#define SUPC_BODVDD_RUNSTDBY_Pos    6            /**< \brief (SUPC_BODVDD) Run during Standby */
#define SUPC_BODVDD_RUNSTDBY        (0x1ul << SUPC_BODVDD_RUNSTDBY_Pos)
#define SUPC_BODVDD_ACTCFG_Pos      8            /**< \brief (SUPC_BODVDD) Configuration in Active mode */
#define SUPC_BODVDD_ACTCFG          (0x1ul << SUPC_BODVDD_ACTCFG_Pos)
#define SUPC_BODVDD_PSEL_Pos        12           /**< \brief (SUPC_BODVDD) Prescaler Select */
#define SUPC_BODVDD_PSEL_Msk        (0xFul << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL(value)     (SUPC_BODVDD_PSEL_Msk & ((value) << SUPC_BODVDD_PSEL_Pos))
#define   SUPC_BODVDD_PSEL_DIV2_Val       0x0ul  /**< \brief (SUPC_BODVDD) Divide clock by 2 */
#define   SUPC_BODVDD_PSEL_DIV4_Val       0x1ul  /**< \brief (SUPC_BODVDD) Divide clock by 4 */
#define   SUPC_BODVDD_PSEL_DIV8_Val       0x2ul  /**< \brief (SUPC_BODVDD) Divide clock by 8 */
#define   SUPC_BODVDD_PSEL_DIV16_Val      0x3ul  /**< \brief (SUPC_BODVDD) Divide clock by 16 */
#define   SUPC_BODVDD_PSEL_DIV32_Val      0x4ul  /**< \brief (SUPC_BODVDD) Divide clock by 32 */
#define   SUPC_BODVDD_PSEL_DIV64_Val      0x5ul  /**< \brief (SUPC_BODVDD) Divide clock by 64 */
#define   SUPC_BODVDD_PSEL_DIV128_Val     0x6ul  /**< \brief (SUPC_BODVDD) Divide clock by 128 */
#define   SUPC_BODVDD_PSEL_DIV256_Val     0x7ul  /**< \brief (SUPC_BODVDD) Divide clock by 256 */
#define   SUPC_BODVDD_PSEL_DIV512_Val     0x8ul  /**< \brief (SUPC_BODVDD) Divide clock by 512 */
#define   SUPC_BODVDD_PSEL_DIV1024_Val    0x9ul  /**< \brief (SUPC_BODVDD) Divide clock by 1024 */
#define   SUPC_BODVDD_PSEL_DIV2048_Val    0xAul  /**< \brief (SUPC_BODVDD) Divide clock by 2048 */
#define   SUPC_BODVDD_PSEL_DIV4096_Val    0xBul  /**< \brief (SUPC_BODVDD) Divide clock by 4096 */
#define   SUPC_BODVDD_PSEL_DIV8192_Val    0xCul  /**< \brief (SUPC_BODVDD) Divide clock by 8192 */
#define   SUPC_BODVDD_PSEL_DIV16384_Val   0xDul  /**< \brief (SUPC_BODVDD) Divide clock by 16384 */
#define   SUPC_BODVDD_PSEL_DIV32768_Val   0xEul  /**< \brief (SUPC_BODVDD) Divide clock by 32768 */
#define   SUPC_BODVDD_PSEL_DIV65536_Val   0xFul  /**< \brief (SUPC_BODVDD) Divide clock by 65536 */
#define SUPC_BODVDD_PSEL_DIV2       (SUPC_BODVDD_PSEL_DIV2_Val     << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV4       (SUPC_BODVDD_PSEL_DIV4_Val     << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV8       (SUPC_BODVDD_PSEL_DIV8_Val     << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV16      (SUPC_BODVDD_PSEL_DIV16_Val    << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV32      (SUPC_BODVDD_PSEL_DIV32_Val    << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV64      (SUPC_BODVDD_PSEL_DIV64_Val    << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV128     (SUPC_BODVDD_PSEL_DIV128_Val   << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV256     (SUPC_BODVDD_PSEL_DIV256_Val   << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV512     (SUPC_BODVDD_PSEL_DIV512_Val   << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV1024    (SUPC_BODVDD_PSEL_DIV1024_Val  << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV2048    (SUPC_BODVDD_PSEL_DIV2048_Val  << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV4096    (SUPC_BODVDD_PSEL_DIV4096_Val  << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV8192    (SUPC_BODVDD_PSEL_DIV8192_Val  << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV16384   (SUPC_BODVDD_PSEL_DIV16384_Val << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV32768   (SUPC_BODVDD_PSEL_DIV32768_Val << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_PSEL_DIV65536   (SUPC_BODVDD_PSEL_DIV65536_Val << SUPC_BODVDD_PSEL_Pos)
#define SUPC_BODVDD_LEVEL_Pos       16           /**< \brief (SUPC_BODVDD) Threshold Level for VDD */
#define SUPC_BODVDD_LEVEL_Msk       (0x3Ful << SUPC_BODVDD_LEVEL_Pos)
#define SUPC_BODVDD_LEVEL(value)    (SUPC_BODVDD_LEVEL_Msk & ((value) << SUPC_BODVDD_LEVEL_Pos))
#define SUPC_BODVDD_MASK            0x003FF17Eul /**< \brief (SUPC_BODVDD) MASK Register */

/* -------- SUPC_BODCORE : (SUPC Offset: 0x14) (R/W 32) BODCORE Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t :1;               /*!< bit:      0  Reserved                           */
    uint32_t ENABLE:1;         /*!< bit:      1  Enable                             */
    uint32_t HYST:1;           /*!< bit:      2  Hysteresis Enable                  */
    uint32_t ACTION:2;         /*!< bit:  3.. 4  Action when Threshold Crossed      */
    uint32_t STDBYCFG:1;       /*!< bit:      5  Configuration in Standby mode      */
    uint32_t RUNSTDBY:1;       /*!< bit:      6  Run during Standby                 */
    uint32_t :1;               /*!< bit:      7  Reserved                           */
    uint32_t ACTCFG:1;         /*!< bit:      8  Configuration in Active mode       */
    uint32_t :3;               /*!< bit:  9..11  Reserved                           */
    uint32_t PSEL:4;           /*!< bit: 12..15  Prescaler Select                   */
    uint32_t LEVEL:6;          /*!< bit: 16..21  Threshold Level                    */
    uint32_t :10;              /*!< bit: 22..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SUPC_BODCORE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_BODCORE_OFFSET         0x14         /**< \brief (SUPC_BODCORE offset) BODCORE Control */
#define SUPC_BODCORE_RESETVALUE     0x00000000ul /**< \brief (SUPC_BODCORE reset_value) BODCORE Control */

#define SUPC_BODCORE_ENABLE_Pos     1            /**< \brief (SUPC_BODCORE) Enable */
#define SUPC_BODCORE_ENABLE         (0x1ul << SUPC_BODCORE_ENABLE_Pos)
#define SUPC_BODCORE_HYST_Pos       2            /**< \brief (SUPC_BODCORE) Hysteresis Enable */
#define SUPC_BODCORE_HYST           (0x1ul << SUPC_BODCORE_HYST_Pos)
#define SUPC_BODCORE_ACTION_Pos     3            /**< \brief (SUPC_BODCORE) Action when Threshold Crossed */
#define SUPC_BODCORE_ACTION_Msk     (0x3ul << SUPC_BODCORE_ACTION_Pos)
#define SUPC_BODCORE_ACTION(value)  (SUPC_BODCORE_ACTION_Msk & ((value) << SUPC_BODCORE_ACTION_Pos))
#define   SUPC_BODCORE_ACTION_NONE_Val    0x0ul  /**< \brief (SUPC_BODCORE) No action */
#define   SUPC_BODCORE_ACTION_RESET_Val   0x1ul  /**< \brief (SUPC_BODCORE) The BOD12 generates a reset */
#define   SUPC_BODCORE_ACTION_INT_Val     0x2ul  /**< \brief (SUPC_BODCORE) The BOD12 generates an interrupt */
#define SUPC_BODCORE_ACTION_NONE    (SUPC_BODCORE_ACTION_NONE_Val  << SUPC_BODCORE_ACTION_Pos)
#define SUPC_BODCORE_ACTION_RESET   (SUPC_BODCORE_ACTION_RESET_Val << SUPC_BODCORE_ACTION_Pos)
#define SUPC_BODCORE_ACTION_INT     (SUPC_BODCORE_ACTION_INT_Val   << SUPC_BODCORE_ACTION_Pos)
#define SUPC_BODCORE_STDBYCFG_Pos   5            /**< \brief (SUPC_BODCORE) Configuration in Standby mode */
#define SUPC_BODCORE_STDBYCFG       (0x1ul << SUPC_BODCORE_STDBYCFG_Pos)
#define SUPC_BODCORE_RUNSTDBY_Pos   6            /**< \brief (SUPC_BODCORE) Run during Standby */
#define SUPC_BODCORE_RUNSTDBY       (0x1ul << SUPC_BODCORE_RUNSTDBY_Pos)
#define SUPC_BODCORE_ACTCFG_Pos     8            /**< \brief (SUPC_BODCORE) Configuration in Active mode */
#define SUPC_BODCORE_ACTCFG         (0x1ul << SUPC_BODCORE_ACTCFG_Pos)
#define SUPC_BODCORE_PSEL_Pos       12           /**< \brief (SUPC_BODCORE) Prescaler Select */
#define SUPC_BODCORE_PSEL_Msk       (0xFul << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL(value)    (SUPC_BODCORE_PSEL_Msk & ((value) << SUPC_BODCORE_PSEL_Pos))
#define   SUPC_BODCORE_PSEL_DIV2_Val      0x0ul  /**< \brief (SUPC_BODCORE) Divide clock by 2 */
#define   SUPC_BODCORE_PSEL_DIV4_Val      0x1ul  /**< \brief (SUPC_BODCORE) Divide clock by 4 */
#define   SUPC_BODCORE_PSEL_DIV8_Val      0x2ul  /**< \brief (SUPC_BODCORE) Divide clock by 8 */
#define   SUPC_BODCORE_PSEL_DIV16_Val     0x3ul  /**< \brief (SUPC_BODCORE) Divide clock by 16 */
#define   SUPC_BODCORE_PSEL_DIV32_Val     0x4ul  /**< \brief (SUPC_BODCORE) Divide clock by 32 */
#define   SUPC_BODCORE_PSEL_DIV64_Val     0x5ul  /**< \brief (SUPC_BODCORE) Divide clock by 64 */
#define   SUPC_BODCORE_PSEL_DIV128_Val    0x6ul  /**< \brief (SUPC_BODCORE) Divide clock by 128 */
#define   SUPC_BODCORE_PSEL_DIV256_Val    0x7ul  /**< \brief (SUPC_BODCORE) Divide clock by 256 */
#define   SUPC_BODCORE_PSEL_DIV512_Val    0x8ul  /**< \brief (SUPC_BODCORE) Divide clock by 512 */
#define   SUPC_BODCORE_PSEL_DIV1024_Val   0x9ul  /**< \brief (SUPC_BODCORE) Divide clock by 1024 */
#define   SUPC_BODCORE_PSEL_DIV2048_Val   0xAul  /**< \brief (SUPC_BODCORE) Divide clock by 2048 */
#define   SUPC_BODCORE_PSEL_DIV4096_Val   0xBul  /**< \brief (SUPC_BODCORE) Divide clock by 4096 */
#define   SUPC_BODCORE_PSEL_DIV8192_Val   0xCul  /**< \brief (SUPC_BODCORE) Divide clock by 8192 */
#define   SUPC_BODCORE_PSEL_DIV16384_Val  0xDul  /**< \brief (SUPC_BODCORE) Divide clock by 16384 */
#define   SUPC_BODCORE_PSEL_DIV32768_Val  0xEul  /**< \brief (SUPC_BODCORE) Divide clock by 32768 */
#define   SUPC_BODCORE_PSEL_DIV65536_Val  0xFul  /**< \brief (SUPC_BODCORE) Divide clock by 65536 */
#define SUPC_BODCORE_PSEL_DIV2      (SUPC_BODCORE_PSEL_DIV2_Val    << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV4      (SUPC_BODCORE_PSEL_DIV4_Val    << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV8      (SUPC_BODCORE_PSEL_DIV8_Val    << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV16     (SUPC_BODCORE_PSEL_DIV16_Val   << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV32     (SUPC_BODCORE_PSEL_DIV32_Val   << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV64     (SUPC_BODCORE_PSEL_DIV64_Val   << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV128    (SUPC_BODCORE_PSEL_DIV128_Val  << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV256    (SUPC_BODCORE_PSEL_DIV256_Val  << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV512    (SUPC_BODCORE_PSEL_DIV512_Val  << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV1024   (SUPC_BODCORE_PSEL_DIV1024_Val << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV2048   (SUPC_BODCORE_PSEL_DIV2048_Val << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV4096   (SUPC_BODCORE_PSEL_DIV4096_Val << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV8192   (SUPC_BODCORE_PSEL_DIV8192_Val << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV16384  (SUPC_BODCORE_PSEL_DIV16384_Val << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV32768  (SUPC_BODCORE_PSEL_DIV32768_Val << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_PSEL_DIV65536  (SUPC_BODCORE_PSEL_DIV65536_Val << SUPC_BODCORE_PSEL_Pos)
#define SUPC_BODCORE_LEVEL_Pos      16           /**< \brief (SUPC_BODCORE) Threshold Level */
#define SUPC_BODCORE_LEVEL_Msk      (0x3Ful << SUPC_BODCORE_LEVEL_Pos)
#define SUPC_BODCORE_LEVEL(value)   (SUPC_BODCORE_LEVEL_Msk & ((value) << SUPC_BODCORE_LEVEL_Pos))
#define SUPC_BODCORE_MASK           0x003FF17Eul /**< \brief (SUPC_BODCORE) MASK Register */

/* -------- SUPC_VREG : (SUPC Offset: 0x18) (R/W 32) VREG Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t :1;               /*!< bit:      0  Reserved                           */
    uint32_t ENABLE:1;         /*!< bit:      1  Enable                             */
    uint32_t :4;               /*!< bit:  2.. 5  Reserved                           */
    uint32_t RUNSTDBY:1;       /*!< bit:      6  Run during Standby                 */
    uint32_t :25;              /*!< bit:  7..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SUPC_VREG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_VREG_OFFSET            0x18         /**< \brief (SUPC_VREG offset) VREG Control */
#define SUPC_VREG_RESETVALUE        0x00000000ul /**< \brief (SUPC_VREG reset_value) VREG Control */

#define SUPC_VREG_ENABLE_Pos        1            /**< \brief (SUPC_VREG) Enable */
#define SUPC_VREG_ENABLE            (0x1ul << SUPC_VREG_ENABLE_Pos)
#define SUPC_VREG_RUNSTDBY_Pos      6            /**< \brief (SUPC_VREG) Run during Standby */
#define SUPC_VREG_RUNSTDBY          (0x1ul << SUPC_VREG_RUNSTDBY_Pos)
#define SUPC_VREG_MASK              0x00000042ul /**< \brief (SUPC_VREG) MASK Register */

/* -------- SUPC_VREF : (SUPC Offset: 0x1C) (R/W 32) VREF Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t :1;               /*!< bit:      0  Reserved                           */
    uint32_t TSEN:1;           /*!< bit:      1  Temperature Sensor Output Enable   */
    uint32_t VREFOE:1;         /*!< bit:      2  Voltage Reference Output Enable    */
    uint32_t :3;               /*!< bit:  3.. 5  Reserved                           */
    uint32_t RUNSTDBY:1;       /*!< bit:      6  Run during Standby                 */
    uint32_t ONDEMAND:1;       /*!< bit:      7  On Demand Contrl                   */
    uint32_t :8;               /*!< bit:  8..15  Reserved                           */
    uint32_t SEL:4;            /*!< bit: 16..19  Voltage Reference Selection        */
    uint32_t :12;              /*!< bit: 20..31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} SUPC_VREF_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SUPC_VREF_OFFSET            0x1C         /**< \brief (SUPC_VREF offset) VREF Control */
#define SUPC_VREF_RESETVALUE        0x00000000ul /**< \brief (SUPC_VREF reset_value) VREF Control */

#define SUPC_VREF_TSEN_Pos          1            /**< \brief (SUPC_VREF) Temperature Sensor Output Enable */
#define SUPC_VREF_TSEN              (0x1ul << SUPC_VREF_TSEN_Pos)
#define SUPC_VREF_VREFOE_Pos        2            /**< \brief (SUPC_VREF) Voltage Reference Output Enable */
#define SUPC_VREF_VREFOE            (0x1ul << SUPC_VREF_VREFOE_Pos)
#define SUPC_VREF_RUNSTDBY_Pos      6            /**< \brief (SUPC_VREF) Run during Standby */
#define SUPC_VREF_RUNSTDBY          (0x1ul << SUPC_VREF_RUNSTDBY_Pos)
#define SUPC_VREF_ONDEMAND_Pos      7            /**< \brief (SUPC_VREF) On Demand Contrl */
#define SUPC_VREF_ONDEMAND          (0x1ul << SUPC_VREF_ONDEMAND_Pos)
#define SUPC_VREF_SEL_Pos           16           /**< \brief (SUPC_VREF) Voltage Reference Selection */
#define SUPC_VREF_SEL_Msk           (0xFul << SUPC_VREF_SEL_Pos)
#define SUPC_VREF_SEL(value)        (SUPC_VREF_SEL_Msk & ((value) << SUPC_VREF_SEL_Pos))
#define   SUPC_VREF_SEL_1V024_Val         0x0ul  /**< \brief (SUPC_VREF) 1.024V voltage reference typical value */
#define   SUPC_VREF_SEL_2V048_Val         0x2ul  /**< \brief (SUPC_VREF) 2.048V voltage reference typical value */
#define   SUPC_VREF_SEL_4V096_Val         0x3ul  /**< \brief (SUPC_VREF) 4.096V voltage reference typical value */
#define SUPC_VREF_SEL_1V024         (SUPC_VREF_SEL_1V024_Val       << SUPC_VREF_SEL_Pos)
#define SUPC_VREF_SEL_2V048         (SUPC_VREF_SEL_2V048_Val       << SUPC_VREF_SEL_Pos)
#define SUPC_VREF_SEL_4V096         (SUPC_VREF_SEL_4V096_Val       << SUPC_VREF_SEL_Pos)
#define SUPC_VREF_MASK              0x000F00C6ul /**< \brief (SUPC_VREF) MASK Register */

/** \brief SUPC hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  __IO SUPC_INTENCLR_Type        INTENCLR;    /**< \brief Offset: 0x00 (R/W 32) Interrupt Enable Clear */
  __IO SUPC_INTENSET_Type        INTENSET;    /**< \brief Offset: 0x04 (R/W 32) Interrupt Enable Set */
  __IO SUPC_INTFLAG_Type         INTFLAG;     /**< \brief Offset: 0x08 (R/W 32) Interrupt Flag Status and Clear */
  __I  SUPC_STATUS_Type          STATUS;      /**< \brief Offset: 0x0C (R/  32) Power and Clocks Status */
  __IO SUPC_BODVDD_Type          BODVDD;      /**< \brief Offset: 0x10 (R/W 32) BODVDD Control */
  __IO SUPC_BODCORE_Type         BODCORE;     /**< \brief Offset: 0x14 (R/W 32) BODCORE Control */
  __IO SUPC_VREG_Type            VREG;        /**< \brief Offset: 0x18 (R/W 32) VREG Control */
  __IO SUPC_VREF_Type            VREF;        /**< \brief Offset: 0x1C (R/W 32) VREF Control */
} Supc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMC21_SUPC_COMPONENT_ */
