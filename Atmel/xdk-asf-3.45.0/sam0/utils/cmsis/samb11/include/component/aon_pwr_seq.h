/**
 * \file
 *
 * \brief Component description for AON_PWR_SEQ
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

#ifndef _SAMB11_AON_PWR_SEQ_COMPONENT_
#define _SAMB11_AON_PWR_SEQ_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR AON_PWR_SEQ */
/* ========================================================================== */
/** \addtogroup SAMB11_AON_PWR_SEQ Always On Power Sequencer 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define AON_PWR_SEQ_AONPS1234
#define REV_AON_PWR_SEQ                  0x100

/* -------- AON_PWR_SEQ_GPIO_WAKEUP_CTRL : (AON_PWR_SEQ Offset: 0x00) (R/W 8) Controls the wakeup enable for GPIO_0, GPIO_1 and GPIO_2 (Pinmux will control the ARM wakeup) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  :1;                        /**< bit:      0  Reserved */
    uint8_t  BLE_ENABLE:1;              /**< bit:      1  If set, this will enable GPIO_0 to wake up the BLE domain (PD4, PD5 and PD6) */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AON_PWR_SEQ_GPIO_WAKEUP_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_GPIO_WAKEUP_CTRL_OFFSET 0x00                                          /**<  (AON_PWR_SEQ_GPIO_WAKEUP_CTRL) Controls the wakeup enable for GPIO_0, GPIO_1 and GPIO_2 (Pinmux will control the ARM wakeup)  Offset */
#define AON_PWR_SEQ_GPIO_WAKEUP_CTRL_RESETVALUE 0x02u                                         /**<  (AON_PWR_SEQ_GPIO_WAKEUP_CTRL) Controls the wakeup enable for GPIO_0, GPIO_1 and GPIO_2 (Pinmux will control the ARM wakeup)  Reset Value */

#define AON_PWR_SEQ_GPIO_WAKEUP_CTRL_BLE_ENABLE_Pos 1                                              /**< (AON_PWR_SEQ_GPIO_WAKEUP_CTRL) If set, this will enable GPIO_0 to wake up the BLE domain (PD4, PD5 and PD6) Position */
#define AON_PWR_SEQ_GPIO_WAKEUP_CTRL_BLE_ENABLE_Msk (0x1u << AON_PWR_SEQ_GPIO_WAKEUP_CTRL_BLE_ENABLE_Pos)  /**< (AON_PWR_SEQ_GPIO_WAKEUP_CTRL) If set, this will enable GPIO_0 to wake up the BLE domain (PD4, PD5 and PD6) Mask */
#define AON_PWR_SEQ_GPIO_WAKEUP_CTRL_BLE_ENABLE AON_PWR_SEQ_GPIO_WAKEUP_CTRL_BLE_ENABLE_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_GPIO_WAKEUP_CTRL_BLE_ENABLE_Msk instead */
#define AON_PWR_SEQ_GPIO_WAKEUP_CTRL_MASK   0x02u                                          /**< \deprecated (AON_PWR_SEQ_GPIO_WAKEUP_CTRL) Register MASK  (Use AON_PWR_SEQ_GPIO_WAKEUP_CTRL_Msk instead)  */
#define AON_PWR_SEQ_GPIO_WAKEUP_CTRL_Msk    0x02u                                          /**< (AON_PWR_SEQ_GPIO_WAKEUP_CTRL) Register Mask  */

/* -------- AON_PWR_SEQ_AON_ST_WAKEUP_CTRL : (AON_PWR_SEQ Offset: 0x0c) (R/W 8) Controls the wakeup enable for the Always On Sleep Timer (AON_ST) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ARM_ENABLE:1;              /**< bit:      0  If set, this will enable the AON_ST to wake up the ARM domain (PD1, PD2 and PD3) */
    uint8_t  BLE_ENABLE:1;              /**< bit:      1  If set, this will enable the AON_ST to wake up the BLE domain (PD4, PD5 and PD6) */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_OFFSET 0x0C                                          /**<  (AON_PWR_SEQ_AON_ST_WAKEUP_CTRL) Controls the wakeup enable for the Always On Sleep Timer (AON_ST)  Offset */
#define AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_RESETVALUE 0x00u                                         /**<  (AON_PWR_SEQ_AON_ST_WAKEUP_CTRL) Controls the wakeup enable for the Always On Sleep Timer (AON_ST)  Reset Value */

#define AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_ARM_ENABLE_Pos 0                                              /**< (AON_PWR_SEQ_AON_ST_WAKEUP_CTRL) If set, this will enable the AON_ST to wake up the ARM domain (PD1, PD2 and PD3) Position */
#define AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_ARM_ENABLE_Msk (0x1u << AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_ARM_ENABLE_Pos)  /**< (AON_PWR_SEQ_AON_ST_WAKEUP_CTRL) If set, this will enable the AON_ST to wake up the ARM domain (PD1, PD2 and PD3) Mask */
#define AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_ARM_ENABLE AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_ARM_ENABLE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_ARM_ENABLE_Msk instead */
#define AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_BLE_ENABLE_Pos 1                                              /**< (AON_PWR_SEQ_AON_ST_WAKEUP_CTRL) If set, this will enable the AON_ST to wake up the BLE domain (PD4, PD5 and PD6) Position */
#define AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_BLE_ENABLE_Msk (0x1u << AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_BLE_ENABLE_Pos)  /**< (AON_PWR_SEQ_AON_ST_WAKEUP_CTRL) If set, this will enable the AON_ST to wake up the BLE domain (PD4, PD5 and PD6) Mask */
#define AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_BLE_ENABLE AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_BLE_ENABLE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_BLE_ENABLE_Msk instead */
#define AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_MASK 0x03u                                          /**< \deprecated (AON_PWR_SEQ_AON_ST_WAKEUP_CTRL) Register MASK  (Use AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_Msk instead)  */
#define AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_Msk  0x03u                                          /**< (AON_PWR_SEQ_AON_ST_WAKEUP_CTRL) Register Mask  */

/* -------- AON_PWR_SEQ_LPMCU_WAKEUP_CTRL : (AON_PWR_SEQ Offset: 0x10) (R/W 16) Controls the wakeup enable for the Low Power Micro Controller Unit (LPMCU) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t :6;                        /**< bit:   0..5  Reserved */
    uint16_t BLE_ENABLE:1;              /**< bit:      6  If set, this will enable the LPMCU to wake up the BLE domain (PD4, PD5 and PD6) */
    uint16_t :2;                        /**< bit:   7..8  Reserved */
    uint16_t PD7_ENABLE:1;              /**< bit:      9  If set, this will enable the LPMCU to wakeup the PD7 domain (EFUSE) */
    uint16_t :6;                        /**< bit: 10..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_OFFSET 0x10                                          /**<  (AON_PWR_SEQ_LPMCU_WAKEUP_CTRL) Controls the wakeup enable for the Low Power Micro Controller Unit (LPMCU)  Offset */
#define AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_RESETVALUE 0x00u                                         /**<  (AON_PWR_SEQ_LPMCU_WAKEUP_CTRL) Controls the wakeup enable for the Low Power Micro Controller Unit (LPMCU)  Reset Value */

#define AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_BLE_ENABLE_Pos 6                                              /**< (AON_PWR_SEQ_LPMCU_WAKEUP_CTRL) If set, this will enable the LPMCU to wake up the BLE domain (PD4, PD5 and PD6) Position */
#define AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_BLE_ENABLE_Msk (0x1u << AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_BLE_ENABLE_Pos)  /**< (AON_PWR_SEQ_LPMCU_WAKEUP_CTRL) If set, this will enable the LPMCU to wake up the BLE domain (PD4, PD5 and PD6) Mask */
#define AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_BLE_ENABLE AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_BLE_ENABLE_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_BLE_ENABLE_Msk instead */
#define AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_PD7_ENABLE_Pos 9                                              /**< (AON_PWR_SEQ_LPMCU_WAKEUP_CTRL) If set, this will enable the LPMCU to wakeup the PD7 domain (EFUSE) Position */
#define AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_PD7_ENABLE_Msk (0x1u << AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_PD7_ENABLE_Pos)  /**< (AON_PWR_SEQ_LPMCU_WAKEUP_CTRL) If set, this will enable the LPMCU to wakeup the PD7 domain (EFUSE) Mask */
#define AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_PD7_ENABLE AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_PD7_ENABLE_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_PD7_ENABLE_Msk instead */
#define AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_MASK  0x240u                                         /**< \deprecated (AON_PWR_SEQ_LPMCU_WAKEUP_CTRL) Register MASK  (Use AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_Msk instead)  */
#define AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_Msk   0x240u                                         /**< (AON_PWR_SEQ_LPMCU_WAKEUP_CTRL) Register Mask  */

/* -------- AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL : (AON_PWR_SEQ Offset: 0x14) (R/W 8) Controls the wakeup enable for the BLE Sleep Timer (BLE_ST) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ARM_ENABLE:1;              /**< bit:      0  If set, this will enable the BLE_ST to wake up the ARM domain */
    uint8_t  BLE_ENABLE:1;              /**< bit:      1  If set, this will enable the BLE_ST to wake up the BLE domain */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_OFFSET 0x14                                          /**<  (AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL) Controls the wakeup enable for the BLE Sleep Timer (BLE_ST)  Offset */
#define AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_RESETVALUE 0x00u                                         /**<  (AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL) Controls the wakeup enable for the BLE Sleep Timer (BLE_ST)  Reset Value */

#define AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_ARM_ENABLE_Pos 0                                              /**< (AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL) If set, this will enable the BLE_ST to wake up the ARM domain Position */
#define AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_ARM_ENABLE_Msk (0x1u << AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_ARM_ENABLE_Pos)  /**< (AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL) If set, this will enable the BLE_ST to wake up the ARM domain Mask */
#define AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_ARM_ENABLE AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_ARM_ENABLE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_ARM_ENABLE_Msk instead */
#define AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_BLE_ENABLE_Pos 1                                              /**< (AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL) If set, this will enable the BLE_ST to wake up the BLE domain Position */
#define AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_BLE_ENABLE_Msk (0x1u << AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_BLE_ENABLE_Pos)  /**< (AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL) If set, this will enable the BLE_ST to wake up the BLE domain Mask */
#define AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_BLE_ENABLE AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_BLE_ENABLE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_BLE_ENABLE_Msk instead */
#define AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_MASK 0x03u                                          /**< \deprecated (AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL) Register MASK  (Use AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_Msk instead)  */
#define AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_Msk  0x03u                                          /**< (AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL) Register Mask  */

/* -------- AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL : (AON_PWR_SEQ Offset: 0x20) (R/W 32) Controls the sleep and retention options for SLEEP request 1 from the ARM -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t ARM_SLEEP_EN:1;            /**< bit:      0  Enables the SLEEP request 1 to put all ARM domains in sleep or retention (PD1, PD2A, PD2B, PD3, PD8).  PD7 has its own control */
    uint32_t :5;                        /**< bit:   1..5  Reserved */
    uint32_t BLE_SLEEP_EN:1;            /**< bit:      6  Enables the SLEEP request 1 to put PD4 domain in sleep (BLE Core) and PD5 (BLE memories) in sleep or retention */
    uint32_t :1;                        /**< bit:      7  Reserved */
    uint32_t PD6_SLEEP_EN:1;            /**< bit:      8  Enables the SLEEP request 1 to put PD6 domain in sleep (BLE Sleep Timer) */
    uint32_t PD7_SLEEP_EN:1;            /**< bit:      9  Enables the SLEEP request 1 to put PD7 domain in sleep (EFUSE) */
    uint32_t :6;                        /**< bit: 10..15  Reserved */
    uint32_t PD2A_RETENTION_EN:1;       /**< bit:     16  If 1, then PD2A will be put in retention mode when instructed to go to sleep (First ARM Memory 16K) */
    uint32_t PD2B_RETENTION_EN:1;       /**< bit:     17  If 1, then PD2B will be put in retention mode when instructed to go to sleep (Second ARM Memory 16K) */
    uint32_t PD3_RETENTION_EN:1;        /**< bit:     18  If 1, then PD3 will be put in retention mode when instructed to go to sleep (Third, Fourth and Fifth ARM Memories 3x32K = 96K) */
    uint32_t :2;                        /**< bit: 19..20  Reserved */
    uint32_t PD5_RETENTION_EN:1;        /**< bit:     21  If 1, then PD5 will be put in retention mode when instructed to go to sleep (BLE Retention Memory) */
    uint32_t PD8_RETENTION_EN:1;        /**< bit:     22  If 1, then PD8 will be put in retention mode when instructed to go to sleep (BLE LP Memory) */
    uint32_t :9;                        /**< bit: 23..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_OFFSET 0x20                                          /**<  (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) Controls the sleep and retention options for SLEEP request 1 from the ARM  Offset */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_RESETVALUE 0x00u                                         /**<  (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) Controls the sleep and retention options for SLEEP request 1 from the ARM  Reset Value */

#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_ARM_SLEEP_EN_Pos 0                                              /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) Enables the SLEEP request 1 to put all ARM domains in sleep or retention (PD1, PD2A, PD2B, PD3, PD8).  PD7 has its own control Position */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_ARM_SLEEP_EN_Msk (0x1u << AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_ARM_SLEEP_EN_Pos)  /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) Enables the SLEEP request 1 to put all ARM domains in sleep or retention (PD1, PD2A, PD2B, PD3, PD8).  PD7 has its own control Mask */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_ARM_SLEEP_EN AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_ARM_SLEEP_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_ARM_SLEEP_EN_Msk instead */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_BLE_SLEEP_EN_Pos 6                                              /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) Enables the SLEEP request 1 to put PD4 domain in sleep (BLE Core) and PD5 (BLE memories) in sleep or retention Position */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_BLE_SLEEP_EN_Msk (0x1u << AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_BLE_SLEEP_EN_Pos)  /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) Enables the SLEEP request 1 to put PD4 domain in sleep (BLE Core) and PD5 (BLE memories) in sleep or retention Mask */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_BLE_SLEEP_EN AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_BLE_SLEEP_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_BLE_SLEEP_EN_Msk instead */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD6_SLEEP_EN_Pos 8                                              /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) Enables the SLEEP request 1 to put PD6 domain in sleep (BLE Sleep Timer) Position */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD6_SLEEP_EN_Msk (0x1u << AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD6_SLEEP_EN_Pos)  /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) Enables the SLEEP request 1 to put PD6 domain in sleep (BLE Sleep Timer) Mask */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD6_SLEEP_EN AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD6_SLEEP_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD6_SLEEP_EN_Msk instead */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD7_SLEEP_EN_Pos 9                                              /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) Enables the SLEEP request 1 to put PD7 domain in sleep (EFUSE) Position */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD7_SLEEP_EN_Msk (0x1u << AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD7_SLEEP_EN_Pos)  /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) Enables the SLEEP request 1 to put PD7 domain in sleep (EFUSE) Mask */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD7_SLEEP_EN AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD7_SLEEP_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD7_SLEEP_EN_Msk instead */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD2A_RETENTION_EN_Pos 16                                             /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) If 1, then PD2A will be put in retention mode when instructed to go to sleep (First ARM Memory 16K) Position */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD2A_RETENTION_EN_Msk (0x1u << AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD2A_RETENTION_EN_Pos)  /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) If 1, then PD2A will be put in retention mode when instructed to go to sleep (First ARM Memory 16K) Mask */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD2A_RETENTION_EN AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD2A_RETENTION_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD2A_RETENTION_EN_Msk instead */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD2B_RETENTION_EN_Pos 17                                             /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) If 1, then PD2B will be put in retention mode when instructed to go to sleep (Second ARM Memory 16K) Position */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD2B_RETENTION_EN_Msk (0x1u << AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD2B_RETENTION_EN_Pos)  /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) If 1, then PD2B will be put in retention mode when instructed to go to sleep (Second ARM Memory 16K) Mask */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD2B_RETENTION_EN AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD2B_RETENTION_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD2B_RETENTION_EN_Msk instead */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD3_RETENTION_EN_Pos 18                                             /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) If 1, then PD3 will be put in retention mode when instructed to go to sleep (Third, Fourth and Fifth ARM Memories 3x32K = 96K) Position */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD3_RETENTION_EN_Msk (0x1u << AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD3_RETENTION_EN_Pos)  /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) If 1, then PD3 will be put in retention mode when instructed to go to sleep (Third, Fourth and Fifth ARM Memories 3x32K = 96K) Mask */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD3_RETENTION_EN AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD3_RETENTION_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD3_RETENTION_EN_Msk instead */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD5_RETENTION_EN_Pos 21                                             /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) If 1, then PD5 will be put in retention mode when instructed to go to sleep (BLE Retention Memory) Position */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD5_RETENTION_EN_Msk (0x1u << AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD5_RETENTION_EN_Pos)  /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) If 1, then PD5 will be put in retention mode when instructed to go to sleep (BLE Retention Memory) Mask */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD5_RETENTION_EN AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD5_RETENTION_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD5_RETENTION_EN_Msk instead */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD8_RETENTION_EN_Pos 22                                             /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) If 1, then PD8 will be put in retention mode when instructed to go to sleep (BLE LP Memory) Position */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD8_RETENTION_EN_Msk (0x1u << AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD8_RETENTION_EN_Pos)  /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) If 1, then PD8 will be put in retention mode when instructed to go to sleep (BLE LP Memory) Mask */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD8_RETENTION_EN AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD8_RETENTION_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_PD8_RETENTION_EN_Msk instead */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_MASK 0x670341u                                      /**< \deprecated (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) Register MASK  (Use AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_Msk instead)  */
#define AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_Msk  0x670341u                                      /**< (AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL) Register Mask  */

/* -------- AON_PWR_SEQ_OFF_DELAY_0_CTRL : (AON_PWR_SEQ Offset: 0x40) (R/W 32) Power OFF Delays -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CLOCK_EN_EARLY:6;          /**< bit:   0..5  Number of clock cycles before setting clock_en_early to low (clock_en is +1 of this value) */
    uint32_t :10;                       /**< bit:  6..15  Reserved */
    uint32_t ISOLATE:6;                 /**< bit: 16..21  Number of clock cycles before enabling the isolation cells */
    uint32_t :2;                        /**< bit: 22..23  Reserved */
    uint32_t RESETN:6;                  /**< bit: 24..29  Number of clock cycles before asserting RESETN */
    uint32_t :2;                        /**< bit: 30..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_PWR_SEQ_OFF_DELAY_0_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_OFFSET 0x40                                          /**<  (AON_PWR_SEQ_OFF_DELAY_0_CTRL) Power OFF Delays  Offset */
#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_RESETVALUE 0x4030001u                                    /**<  (AON_PWR_SEQ_OFF_DELAY_0_CTRL) Power OFF Delays  Reset Value */

#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_CLOCK_EN_EARLY_Pos 0                                              /**< (AON_PWR_SEQ_OFF_DELAY_0_CTRL) Number of clock cycles before setting clock_en_early to low (clock_en is +1 of this value) Position */
#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_CLOCK_EN_EARLY_Msk (0x3Fu << AON_PWR_SEQ_OFF_DELAY_0_CTRL_CLOCK_EN_EARLY_Pos)  /**< (AON_PWR_SEQ_OFF_DELAY_0_CTRL) Number of clock cycles before setting clock_en_early to low (clock_en is +1 of this value) Mask */
#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_CLOCK_EN_EARLY(value) (AON_PWR_SEQ_OFF_DELAY_0_CTRL_CLOCK_EN_EARLY_Msk & ((value) << AON_PWR_SEQ_OFF_DELAY_0_CTRL_CLOCK_EN_EARLY_Pos))
#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_ISOLATE_Pos 16                                             /**< (AON_PWR_SEQ_OFF_DELAY_0_CTRL) Number of clock cycles before enabling the isolation cells Position */
#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_ISOLATE_Msk (0x3Fu << AON_PWR_SEQ_OFF_DELAY_0_CTRL_ISOLATE_Pos)  /**< (AON_PWR_SEQ_OFF_DELAY_0_CTRL) Number of clock cycles before enabling the isolation cells Mask */
#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_ISOLATE(value) (AON_PWR_SEQ_OFF_DELAY_0_CTRL_ISOLATE_Msk & ((value) << AON_PWR_SEQ_OFF_DELAY_0_CTRL_ISOLATE_Pos))
#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_RESETN_Pos 24                                             /**< (AON_PWR_SEQ_OFF_DELAY_0_CTRL) Number of clock cycles before asserting RESETN Position */
#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_RESETN_Msk (0x3Fu << AON_PWR_SEQ_OFF_DELAY_0_CTRL_RESETN_Pos)  /**< (AON_PWR_SEQ_OFF_DELAY_0_CTRL) Number of clock cycles before asserting RESETN Mask */
#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_RESETN(value) (AON_PWR_SEQ_OFF_DELAY_0_CTRL_RESETN_Msk & ((value) << AON_PWR_SEQ_OFF_DELAY_0_CTRL_RESETN_Pos))
#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_MASK   0x3F3F003Fu                                    /**< \deprecated (AON_PWR_SEQ_OFF_DELAY_0_CTRL) Register MASK  (Use AON_PWR_SEQ_OFF_DELAY_0_CTRL_Msk instead)  */
#define AON_PWR_SEQ_OFF_DELAY_0_CTRL_Msk    0x3F3F003Fu                                    /**< (AON_PWR_SEQ_OFF_DELAY_0_CTRL) Register Mask  */

/* -------- AON_PWR_SEQ_OFF_DELAY_1_CTRL : (AON_PWR_SEQ Offset: 0x44) (R/W 32) Power OFF Delays -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BTRIM:6;                   /**< bit:   0..5  Number of clock cycles before applying BTRIM mux select */
    uint32_t :2;                        /**< bit:   6..7  Reserved */
    uint32_t STDBY_N:6;                 /**< bit:  8..13  Number of clock cycles before applying STDBY_N */
    uint32_t :2;                        /**< bit: 14..15  Reserved */
    uint32_t POWER_VDD:6;               /**< bit: 16..21  Number of clock cycles before cutting off power (VDD and standard cells) */
    uint32_t :2;                        /**< bit: 22..23  Reserved */
    uint32_t POWER_VDM:6;               /**< bit: 24..29  Number of clock cycles before cutting off or lowering power (VDM) */
    uint32_t :2;                        /**< bit: 30..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_PWR_SEQ_OFF_DELAY_1_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_OFFSET 0x44                                          /**<  (AON_PWR_SEQ_OFF_DELAY_1_CTRL) Power OFF Delays  Offset */
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_RESETVALUE 0x8070605u                                    /**<  (AON_PWR_SEQ_OFF_DELAY_1_CTRL) Power OFF Delays  Reset Value */

#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_BTRIM_Pos 0                                              /**< (AON_PWR_SEQ_OFF_DELAY_1_CTRL) Number of clock cycles before applying BTRIM mux select Position */
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_BTRIM_Msk (0x3Fu << AON_PWR_SEQ_OFF_DELAY_1_CTRL_BTRIM_Pos)  /**< (AON_PWR_SEQ_OFF_DELAY_1_CTRL) Number of clock cycles before applying BTRIM mux select Mask */
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_BTRIM(value) (AON_PWR_SEQ_OFF_DELAY_1_CTRL_BTRIM_Msk & ((value) << AON_PWR_SEQ_OFF_DELAY_1_CTRL_BTRIM_Pos))
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_STDBY_N_Pos 8                                              /**< (AON_PWR_SEQ_OFF_DELAY_1_CTRL) Number of clock cycles before applying STDBY_N Position */
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_STDBY_N_Msk (0x3Fu << AON_PWR_SEQ_OFF_DELAY_1_CTRL_STDBY_N_Pos)  /**< (AON_PWR_SEQ_OFF_DELAY_1_CTRL) Number of clock cycles before applying STDBY_N Mask */
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_STDBY_N(value) (AON_PWR_SEQ_OFF_DELAY_1_CTRL_STDBY_N_Msk & ((value) << AON_PWR_SEQ_OFF_DELAY_1_CTRL_STDBY_N_Pos))
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_POWER_VDD_Pos 16                                             /**< (AON_PWR_SEQ_OFF_DELAY_1_CTRL) Number of clock cycles before cutting off power (VDD and standard cells) Position */
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_POWER_VDD_Msk (0x3Fu << AON_PWR_SEQ_OFF_DELAY_1_CTRL_POWER_VDD_Pos)  /**< (AON_PWR_SEQ_OFF_DELAY_1_CTRL) Number of clock cycles before cutting off power (VDD and standard cells) Mask */
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_POWER_VDD(value) (AON_PWR_SEQ_OFF_DELAY_1_CTRL_POWER_VDD_Msk & ((value) << AON_PWR_SEQ_OFF_DELAY_1_CTRL_POWER_VDD_Pos))
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_POWER_VDM_Pos 24                                             /**< (AON_PWR_SEQ_OFF_DELAY_1_CTRL) Number of clock cycles before cutting off or lowering power (VDM) Position */
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_POWER_VDM_Msk (0x3Fu << AON_PWR_SEQ_OFF_DELAY_1_CTRL_POWER_VDM_Pos)  /**< (AON_PWR_SEQ_OFF_DELAY_1_CTRL) Number of clock cycles before cutting off or lowering power (VDM) Mask */
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_POWER_VDM(value) (AON_PWR_SEQ_OFF_DELAY_1_CTRL_POWER_VDM_Msk & ((value) << AON_PWR_SEQ_OFF_DELAY_1_CTRL_POWER_VDM_Pos))
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_MASK   0x3F3F3F3Fu                                    /**< \deprecated (AON_PWR_SEQ_OFF_DELAY_1_CTRL) Register MASK  (Use AON_PWR_SEQ_OFF_DELAY_1_CTRL_Msk instead)  */
#define AON_PWR_SEQ_OFF_DELAY_1_CTRL_Msk    0x3F3F3F3Fu                                    /**< (AON_PWR_SEQ_OFF_DELAY_1_CTRL) Register Mask  */

/* -------- AON_PWR_SEQ_ON_DELAY_0_CTRL : (AON_PWR_SEQ Offset: 0x48) (R/W 16) Power ON Delays -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t CLOCK_EN_EARLY_ARM:6;      /**< bit:   0..5  Number of clock cycles before setting clock_en_early to high for ARM domain clock_en is +1 of this value isolate is -2 of this value resetn is -1 of this value  */
    uint16_t :2;                        /**< bit:   6..7  Reserved */
    uint16_t CLOCK_EN_EARLY_BLE:6;      /**< bit:  8..13  Number of clock cycles before setting clock_en_early to high for BLE domain clock_en is +1 of this value isolate is -2 of this value resetn is -1 of this value  */
    uint16_t :2;                        /**< bit: 14..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} AON_PWR_SEQ_ON_DELAY_0_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_ON_DELAY_0_CTRL_OFFSET  0x48                                          /**<  (AON_PWR_SEQ_ON_DELAY_0_CTRL) Power ON Delays  Offset */
#define AON_PWR_SEQ_ON_DELAY_0_CTRL_RESETVALUE 0x2727u                                       /**<  (AON_PWR_SEQ_ON_DELAY_0_CTRL) Power ON Delays  Reset Value */

#define AON_PWR_SEQ_ON_DELAY_0_CTRL_CLOCK_EN_EARLY_ARM_Pos 0                                              /**< (AON_PWR_SEQ_ON_DELAY_0_CTRL) Number of clock cycles before setting clock_en_early to high for ARM domain clock_en is +1 of this value isolate is -2 of this value resetn is -1 of this value  Position */
#define AON_PWR_SEQ_ON_DELAY_0_CTRL_CLOCK_EN_EARLY_ARM_Msk (0x3Fu << AON_PWR_SEQ_ON_DELAY_0_CTRL_CLOCK_EN_EARLY_ARM_Pos)  /**< (AON_PWR_SEQ_ON_DELAY_0_CTRL) Number of clock cycles before setting clock_en_early to high for ARM domain clock_en is +1 of this value isolate is -2 of this value resetn is -1 of this value  Mask */
#define AON_PWR_SEQ_ON_DELAY_0_CTRL_CLOCK_EN_EARLY_ARM(value) (AON_PWR_SEQ_ON_DELAY_0_CTRL_CLOCK_EN_EARLY_ARM_Msk & ((value) << AON_PWR_SEQ_ON_DELAY_0_CTRL_CLOCK_EN_EARLY_ARM_Pos))
#define AON_PWR_SEQ_ON_DELAY_0_CTRL_CLOCK_EN_EARLY_BLE_Pos 8                                              /**< (AON_PWR_SEQ_ON_DELAY_0_CTRL) Number of clock cycles before setting clock_en_early to high for BLE domain clock_en is +1 of this value isolate is -2 of this value resetn is -1 of this value  Position */
#define AON_PWR_SEQ_ON_DELAY_0_CTRL_CLOCK_EN_EARLY_BLE_Msk (0x3Fu << AON_PWR_SEQ_ON_DELAY_0_CTRL_CLOCK_EN_EARLY_BLE_Pos)  /**< (AON_PWR_SEQ_ON_DELAY_0_CTRL) Number of clock cycles before setting clock_en_early to high for BLE domain clock_en is +1 of this value isolate is -2 of this value resetn is -1 of this value  Mask */
#define AON_PWR_SEQ_ON_DELAY_0_CTRL_CLOCK_EN_EARLY_BLE(value) (AON_PWR_SEQ_ON_DELAY_0_CTRL_CLOCK_EN_EARLY_BLE_Msk & ((value) << AON_PWR_SEQ_ON_DELAY_0_CTRL_CLOCK_EN_EARLY_BLE_Pos))
#define AON_PWR_SEQ_ON_DELAY_0_CTRL_MASK    0x3F3Fu                                        /**< \deprecated (AON_PWR_SEQ_ON_DELAY_0_CTRL) Register MASK  (Use AON_PWR_SEQ_ON_DELAY_0_CTRL_Msk instead)  */
#define AON_PWR_SEQ_ON_DELAY_0_CTRL_Msk     0x3F3Fu                                        /**< (AON_PWR_SEQ_ON_DELAY_0_CTRL) Register Mask  */

/* -------- AON_PWR_SEQ_ON_DELAY_1_CTRL : (AON_PWR_SEQ Offset: 0x4c) (R/W 32) Power ON Delays -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BTRIM:6;                   /**< bit:   0..5  Number of clock cycles before removing BTRIM mux select */
    uint32_t :2;                        /**< bit:   6..7  Reserved */
    uint32_t STDBY_N:6;                 /**< bit:  8..13  Number of clock cycles before de-asserting the STDBY_N */
    uint32_t :2;                        /**< bit: 14..15  Reserved */
    uint32_t POWER_VDD:6;               /**< bit: 16..21  Number of clock cycles before applying VDD power */
    uint32_t :2;                        /**< bit: 22..23  Reserved */
    uint32_t POWER_VDM:6;               /**< bit: 24..29  Number of clock cycles before applying VDM power */
    uint32_t :2;                        /**< bit: 30..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_PWR_SEQ_ON_DELAY_1_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_ON_DELAY_1_CTRL_OFFSET  0x4C                                          /**<  (AON_PWR_SEQ_ON_DELAY_1_CTRL) Power ON Delays  Offset */
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_RESETVALUE 0x1020304u                                    /**<  (AON_PWR_SEQ_ON_DELAY_1_CTRL) Power ON Delays  Reset Value */

#define AON_PWR_SEQ_ON_DELAY_1_CTRL_BTRIM_Pos 0                                              /**< (AON_PWR_SEQ_ON_DELAY_1_CTRL) Number of clock cycles before removing BTRIM mux select Position */
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_BTRIM_Msk (0x3Fu << AON_PWR_SEQ_ON_DELAY_1_CTRL_BTRIM_Pos)  /**< (AON_PWR_SEQ_ON_DELAY_1_CTRL) Number of clock cycles before removing BTRIM mux select Mask */
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_BTRIM(value) (AON_PWR_SEQ_ON_DELAY_1_CTRL_BTRIM_Msk & ((value) << AON_PWR_SEQ_ON_DELAY_1_CTRL_BTRIM_Pos))
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_STDBY_N_Pos 8                                              /**< (AON_PWR_SEQ_ON_DELAY_1_CTRL) Number of clock cycles before de-asserting the STDBY_N Position */
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_STDBY_N_Msk (0x3Fu << AON_PWR_SEQ_ON_DELAY_1_CTRL_STDBY_N_Pos)  /**< (AON_PWR_SEQ_ON_DELAY_1_CTRL) Number of clock cycles before de-asserting the STDBY_N Mask */
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_STDBY_N(value) (AON_PWR_SEQ_ON_DELAY_1_CTRL_STDBY_N_Msk & ((value) << AON_PWR_SEQ_ON_DELAY_1_CTRL_STDBY_N_Pos))
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_POWER_VDD_Pos 16                                             /**< (AON_PWR_SEQ_ON_DELAY_1_CTRL) Number of clock cycles before applying VDD power Position */
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_POWER_VDD_Msk (0x3Fu << AON_PWR_SEQ_ON_DELAY_1_CTRL_POWER_VDD_Pos)  /**< (AON_PWR_SEQ_ON_DELAY_1_CTRL) Number of clock cycles before applying VDD power Mask */
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_POWER_VDD(value) (AON_PWR_SEQ_ON_DELAY_1_CTRL_POWER_VDD_Msk & ((value) << AON_PWR_SEQ_ON_DELAY_1_CTRL_POWER_VDD_Pos))
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_POWER_VDM_Pos 24                                             /**< (AON_PWR_SEQ_ON_DELAY_1_CTRL) Number of clock cycles before applying VDM power Position */
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_POWER_VDM_Msk (0x3Fu << AON_PWR_SEQ_ON_DELAY_1_CTRL_POWER_VDM_Pos)  /**< (AON_PWR_SEQ_ON_DELAY_1_CTRL) Number of clock cycles before applying VDM power Mask */
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_POWER_VDM(value) (AON_PWR_SEQ_ON_DELAY_1_CTRL_POWER_VDM_Msk & ((value) << AON_PWR_SEQ_ON_DELAY_1_CTRL_POWER_VDM_Pos))
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_MASK    0x3F3F3F3Fu                                    /**< \deprecated (AON_PWR_SEQ_ON_DELAY_1_CTRL) Register MASK  (Use AON_PWR_SEQ_ON_DELAY_1_CTRL_Msk instead)  */
#define AON_PWR_SEQ_ON_DELAY_1_CTRL_Msk     0x3F3F3F3Fu                                    /**< (AON_PWR_SEQ_ON_DELAY_1_CTRL) Register Mask  */

/* -------- AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL : (AON_PWR_SEQ Offset: 0x50) (R/W 16) VDD_DCDC_EN Delay Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t OFF:6;                     /**< bit:   0..5  Number of clock cycles before disabling the DCDC */
    uint16_t :2;                        /**< bit:   6..7  Reserved */
    uint16_t ON:6;                      /**< bit:  8..13  Number of clock cycles before turning on the DCDC */
    uint16_t :2;                        /**< bit: 14..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_OFFSET 0x50                                          /**<  (AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL) VDD_DCDC_EN Delay Control  Offset */
#define AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_RESETVALUE 0x2106u                                       /**<  (AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL) VDD_DCDC_EN Delay Control  Reset Value */

#define AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_OFF_Pos 0                                              /**< (AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL) Number of clock cycles before disabling the DCDC Position */
#define AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_OFF_Msk (0x3Fu << AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_OFF_Pos)  /**< (AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL) Number of clock cycles before disabling the DCDC Mask */
#define AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_OFF(value) (AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_OFF_Msk & ((value) << AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_OFF_Pos))
#define AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_ON_Pos 8                                              /**< (AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL) Number of clock cycles before turning on the DCDC Position */
#define AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_ON_Msk (0x3Fu << AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_ON_Pos)  /**< (AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL) Number of clock cycles before turning on the DCDC Mask */
#define AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_ON(value) (AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_ON_Msk & ((value) << AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_ON_Pos))
#define AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_MASK 0x3F3Fu                                        /**< \deprecated (AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL) Register MASK  (Use AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_Msk instead)  */
#define AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_Msk 0x3F3Fu                                        /**< (AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL) Register Mask  */

/* -------- AON_PWR_SEQ_MISC_BYPASS_0_CTRL : (AON_PWR_SEQ Offset: 0x218) (R/W 16) Bypass control for misc signals -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t :2;                        /**< bit:   0..1  Reserved */
    uint16_t PD0_LOW_VOLTAGE_EN_VAL:1;  /**< bit:      2  Bypass value for pd0_low_voltage_en      */
    uint16_t PD0_LOW_VOLTAGE_EN_EN:1;   /**< bit:      3  Bypass enable for pd0_low_voltage_en     */
    uint16_t ENABLE_CLOCK_GATE:1;       /**< bit:      4  If set, allows the AON PS to gate its own clock while waiting for an event to enable it again */
    uint16_t :1;                        /**< bit:      5  Reserved */
    uint16_t VDD_DCDC_EN_VAL:1;         /**< bit:      6  Bypass value for vdd_dcdc_en             */
    uint16_t VDD_DCDC_EN_EN:1;          /**< bit:      7  Bypass enable for vdd_dcdc_en            */
    uint16_t FORCE_ON_BLE_CORE:1;       /**< bit:      8  If set, this will keep the power enabled for the BLE Core (enables the DCDC operation) */
    uint16_t FORCE_ON_BLE_MEMORIES:1;   /**< bit:      9  If set, this will keep the power enabled for the BLE memories (enables the DCDC operation) */
    uint16_t :6;                        /**< bit: 10..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} AON_PWR_SEQ_MISC_BYPASS_0_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_OFFSET 0x218                                         /**<  (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) Bypass control for misc signals  Offset */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_RESETVALUE 0x88u                                         /**<  (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) Bypass control for misc signals  Reset Value */

#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_PD0_LOW_VOLTAGE_EN_VAL_Pos 2                                              /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) Bypass value for pd0_low_voltage_en Position */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_PD0_LOW_VOLTAGE_EN_VAL_Msk (0x1u << AON_PWR_SEQ_MISC_BYPASS_0_CTRL_PD0_LOW_VOLTAGE_EN_VAL_Pos)  /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) Bypass value for pd0_low_voltage_en Mask */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_PD0_LOW_VOLTAGE_EN_VAL AON_PWR_SEQ_MISC_BYPASS_0_CTRL_PD0_LOW_VOLTAGE_EN_VAL_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_MISC_BYPASS_0_CTRL_PD0_LOW_VOLTAGE_EN_VAL_Msk instead */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_PD0_LOW_VOLTAGE_EN_EN_Pos 3                                              /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) Bypass enable for pd0_low_voltage_en Position */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_PD0_LOW_VOLTAGE_EN_EN_Msk (0x1u << AON_PWR_SEQ_MISC_BYPASS_0_CTRL_PD0_LOW_VOLTAGE_EN_EN_Pos)  /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) Bypass enable for pd0_low_voltage_en Mask */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_PD0_LOW_VOLTAGE_EN_EN AON_PWR_SEQ_MISC_BYPASS_0_CTRL_PD0_LOW_VOLTAGE_EN_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_MISC_BYPASS_0_CTRL_PD0_LOW_VOLTAGE_EN_EN_Msk instead */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_ENABLE_CLOCK_GATE_Pos 4                                              /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) If set, allows the AON PS to gate its own clock while waiting for an event to enable it again Position */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_ENABLE_CLOCK_GATE_Msk (0x1u << AON_PWR_SEQ_MISC_BYPASS_0_CTRL_ENABLE_CLOCK_GATE_Pos)  /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) If set, allows the AON PS to gate its own clock while waiting for an event to enable it again Mask */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_ENABLE_CLOCK_GATE AON_PWR_SEQ_MISC_BYPASS_0_CTRL_ENABLE_CLOCK_GATE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_MISC_BYPASS_0_CTRL_ENABLE_CLOCK_GATE_Msk instead */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_VDD_DCDC_EN_VAL_Pos 6                                              /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) Bypass value for vdd_dcdc_en Position */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_VDD_DCDC_EN_VAL_Msk (0x1u << AON_PWR_SEQ_MISC_BYPASS_0_CTRL_VDD_DCDC_EN_VAL_Pos)  /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) Bypass value for vdd_dcdc_en Mask */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_VDD_DCDC_EN_VAL AON_PWR_SEQ_MISC_BYPASS_0_CTRL_VDD_DCDC_EN_VAL_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_MISC_BYPASS_0_CTRL_VDD_DCDC_EN_VAL_Msk instead */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_VDD_DCDC_EN_EN_Pos 7                                              /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) Bypass enable for vdd_dcdc_en Position */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_VDD_DCDC_EN_EN_Msk (0x1u << AON_PWR_SEQ_MISC_BYPASS_0_CTRL_VDD_DCDC_EN_EN_Pos)  /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) Bypass enable for vdd_dcdc_en Mask */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_VDD_DCDC_EN_EN AON_PWR_SEQ_MISC_BYPASS_0_CTRL_VDD_DCDC_EN_EN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_MISC_BYPASS_0_CTRL_VDD_DCDC_EN_EN_Msk instead */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_FORCE_ON_BLE_CORE_Pos 8                                              /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) If set, this will keep the power enabled for the BLE Core (enables the DCDC operation) Position */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_FORCE_ON_BLE_CORE_Msk (0x1u << AON_PWR_SEQ_MISC_BYPASS_0_CTRL_FORCE_ON_BLE_CORE_Pos)  /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) If set, this will keep the power enabled for the BLE Core (enables the DCDC operation) Mask */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_FORCE_ON_BLE_CORE AON_PWR_SEQ_MISC_BYPASS_0_CTRL_FORCE_ON_BLE_CORE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_MISC_BYPASS_0_CTRL_FORCE_ON_BLE_CORE_Msk instead */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_FORCE_ON_BLE_MEMORIES_Pos 9                                              /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) If set, this will keep the power enabled for the BLE memories (enables the DCDC operation) Position */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_FORCE_ON_BLE_MEMORIES_Msk (0x1u << AON_PWR_SEQ_MISC_BYPASS_0_CTRL_FORCE_ON_BLE_MEMORIES_Pos)  /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) If set, this will keep the power enabled for the BLE memories (enables the DCDC operation) Mask */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_FORCE_ON_BLE_MEMORIES AON_PWR_SEQ_MISC_BYPASS_0_CTRL_FORCE_ON_BLE_MEMORIES_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_MISC_BYPASS_0_CTRL_FORCE_ON_BLE_MEMORIES_Msk instead */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_MASK 0x3DCu                                         /**< \deprecated (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) Register MASK  (Use AON_PWR_SEQ_MISC_BYPASS_0_CTRL_Msk instead)  */
#define AON_PWR_SEQ_MISC_BYPASS_0_CTRL_Msk  0x3DCu                                         /**< (AON_PWR_SEQ_MISC_BYPASS_0_CTRL) Register Mask  */

/* -------- AON_PWR_SEQ_RAW_WAKEUP_BITS : (AON_PWR_SEQ Offset: 0x300) (R/ 8) Raw Wakeup Bits -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  GPIO_0:1;                  /**< bit:      0  AO_GPIO_0 wakeup raw status              */
    uint8_t  GPIO_1:1;                  /**< bit:      1  AO_GPIO_1 wakeup raw status              */
    uint8_t  GPIO_2:1;                  /**< bit:      2  AO_GPIO_2 wakeup raw status              */
    uint8_t  AON_ST:1;                  /**< bit:      3  AON_ST wakeup raw status                 */
    uint8_t  LPMCU:1;                   /**< bit:      4  LPMCU wakeup raw status                  */
    uint8_t  BLE_ST:1;                  /**< bit:      5  BLE_ST wakeup raw status                 */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  GPIO_:3;                   /**< bit:   0..2  AO_GPIO_x wakeup raw status              */
    uint8_t  :5;                        /**< bit:   3..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} AON_PWR_SEQ_RAW_WAKEUP_BITS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_RAW_WAKEUP_BITS_OFFSET  0x300                                         /**<  (AON_PWR_SEQ_RAW_WAKEUP_BITS) Raw Wakeup Bits  Offset */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_RESETVALUE 0x00u                                         /**<  (AON_PWR_SEQ_RAW_WAKEUP_BITS) Raw Wakeup Bits  Reset Value */

#define AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_0_Pos 0                                              /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) AO_GPIO_0 wakeup raw status Position */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_0_Msk (0x1u << AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_0_Pos)  /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) AO_GPIO_0 wakeup raw status Mask */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_0  AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_0_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_0_Msk instead */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_1_Pos 1                                              /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) AO_GPIO_1 wakeup raw status Position */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_1_Msk (0x1u << AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_1_Pos)  /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) AO_GPIO_1 wakeup raw status Mask */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_1  AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_1_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_1_Msk instead */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_2_Pos 2                                              /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) AO_GPIO_2 wakeup raw status Position */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_2_Msk (0x1u << AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_2_Pos)  /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) AO_GPIO_2 wakeup raw status Mask */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_2  AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_2_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_2_Msk instead */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_AON_ST_Pos 3                                              /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) AON_ST wakeup raw status Position */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_AON_ST_Msk (0x1u << AON_PWR_SEQ_RAW_WAKEUP_BITS_AON_ST_Pos)  /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) AON_ST wakeup raw status Mask */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_AON_ST  AON_PWR_SEQ_RAW_WAKEUP_BITS_AON_ST_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_RAW_WAKEUP_BITS_AON_ST_Msk instead */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_LPMCU_Pos 4                                              /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) LPMCU wakeup raw status Position */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_LPMCU_Msk (0x1u << AON_PWR_SEQ_RAW_WAKEUP_BITS_LPMCU_Pos)  /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) LPMCU wakeup raw status Mask */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_LPMCU   AON_PWR_SEQ_RAW_WAKEUP_BITS_LPMCU_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_RAW_WAKEUP_BITS_LPMCU_Msk instead */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_BLE_ST_Pos 5                                              /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) BLE_ST wakeup raw status Position */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_BLE_ST_Msk (0x1u << AON_PWR_SEQ_RAW_WAKEUP_BITS_BLE_ST_Pos)  /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) BLE_ST wakeup raw status Mask */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_BLE_ST  AON_PWR_SEQ_RAW_WAKEUP_BITS_BLE_ST_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_RAW_WAKEUP_BITS_BLE_ST_Msk instead */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO__Pos 0                                              /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS Position) AO_GPIO_x wakeup raw status */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO__Msk (0x7u << AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO__Pos)  /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS Mask) GPIO_ */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO_(value) (AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO__Msk & ((value) << AON_PWR_SEQ_RAW_WAKEUP_BITS_GPIO__Pos))  
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_MASK    0x3Fu                                          /**< \deprecated (AON_PWR_SEQ_RAW_WAKEUP_BITS) Register MASK  (Use AON_PWR_SEQ_RAW_WAKEUP_BITS_Msk instead)  */
#define AON_PWR_SEQ_RAW_WAKEUP_BITS_Msk     0x3Fu                                          /**< (AON_PWR_SEQ_RAW_WAKEUP_BITS) Register Mask  */

/* -------- AON_PWR_SEQ_PD_WAKEUP_BITS : (AON_PWR_SEQ Offset: 0x304) (R/ 16) Individual Power Domain Wakeup Bits -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t ARM:1;                     /**< bit:      0  Indicates ARM (PD1, PD2A, PD2B, PD3, PD8) currently has a wakeup active */
    uint16_t :5;                        /**< bit:   1..5  Reserved */
    uint16_t BLE:1;                     /**< bit:      6  Indicates BLE (PD4 and PD5) currently has a wakeup active */
    uint16_t :1;                        /**< bit:      7  Reserved */
    uint16_t PD6:1;                     /**< bit:      8  Indicates PD6 currently has a wakeup active */
    uint16_t PD7:1;                     /**< bit:      9  Indicates PD7 currently has a wakeup active */
    uint16_t :6;                        /**< bit: 10..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint16_t :8;                        /**< bit:   0..7  Reserved */
    uint16_t PD:2;                      /**< bit:   8..9  Indicates PD7 currently has a wakeup active */
    uint16_t :6;                        /**< bit: 10..15 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint16_t reg;                         /**< Type used for register access */
} AON_PWR_SEQ_PD_WAKEUP_BITS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_PD_WAKEUP_BITS_OFFSET   0x304                                         /**<  (AON_PWR_SEQ_PD_WAKEUP_BITS) Individual Power Domain Wakeup Bits  Offset */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_RESETVALUE 0x00u                                         /**<  (AON_PWR_SEQ_PD_WAKEUP_BITS) Individual Power Domain Wakeup Bits  Reset Value */

#define AON_PWR_SEQ_PD_WAKEUP_BITS_ARM_Pos  0                                              /**< (AON_PWR_SEQ_PD_WAKEUP_BITS) Indicates ARM (PD1, PD2A, PD2B, PD3, PD8) currently has a wakeup active Position */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_ARM_Msk  (0x1u << AON_PWR_SEQ_PD_WAKEUP_BITS_ARM_Pos)   /**< (AON_PWR_SEQ_PD_WAKEUP_BITS) Indicates ARM (PD1, PD2A, PD2B, PD3, PD8) currently has a wakeup active Mask */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_ARM      AON_PWR_SEQ_PD_WAKEUP_BITS_ARM_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_PD_WAKEUP_BITS_ARM_Msk instead */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_BLE_Pos  6                                              /**< (AON_PWR_SEQ_PD_WAKEUP_BITS) Indicates BLE (PD4 and PD5) currently has a wakeup active Position */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_BLE_Msk  (0x1u << AON_PWR_SEQ_PD_WAKEUP_BITS_BLE_Pos)   /**< (AON_PWR_SEQ_PD_WAKEUP_BITS) Indicates BLE (PD4 and PD5) currently has a wakeup active Mask */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_BLE      AON_PWR_SEQ_PD_WAKEUP_BITS_BLE_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_PD_WAKEUP_BITS_BLE_Msk instead */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_PD6_Pos  8                                              /**< (AON_PWR_SEQ_PD_WAKEUP_BITS) Indicates PD6 currently has a wakeup active Position */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_PD6_Msk  (0x1u << AON_PWR_SEQ_PD_WAKEUP_BITS_PD6_Pos)   /**< (AON_PWR_SEQ_PD_WAKEUP_BITS) Indicates PD6 currently has a wakeup active Mask */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_PD6      AON_PWR_SEQ_PD_WAKEUP_BITS_PD6_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_PD_WAKEUP_BITS_PD6_Msk instead */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_PD7_Pos  9                                              /**< (AON_PWR_SEQ_PD_WAKEUP_BITS) Indicates PD7 currently has a wakeup active Position */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_PD7_Msk  (0x1u << AON_PWR_SEQ_PD_WAKEUP_BITS_PD7_Pos)   /**< (AON_PWR_SEQ_PD_WAKEUP_BITS) Indicates PD7 currently has a wakeup active Mask */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_PD7      AON_PWR_SEQ_PD_WAKEUP_BITS_PD7_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_PD_WAKEUP_BITS_PD7_Msk instead */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_PD_Pos   8                                              /**< (AON_PWR_SEQ_PD_WAKEUP_BITS Position) Indicates PD7 currently has a wakeup active */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_PD_Msk   (0x3u << AON_PWR_SEQ_PD_WAKEUP_BITS_PD_Pos)    /**< (AON_PWR_SEQ_PD_WAKEUP_BITS Mask) PD */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_PD(value) (AON_PWR_SEQ_PD_WAKEUP_BITS_PD_Msk & ((value) << AON_PWR_SEQ_PD_WAKEUP_BITS_PD_Pos))  
#define AON_PWR_SEQ_PD_WAKEUP_BITS_MASK     0x341u                                         /**< \deprecated (AON_PWR_SEQ_PD_WAKEUP_BITS) Register MASK  (Use AON_PWR_SEQ_PD_WAKEUP_BITS_Msk instead)  */
#define AON_PWR_SEQ_PD_WAKEUP_BITS_Msk      0x341u                                         /**< (AON_PWR_SEQ_PD_WAKEUP_BITS) Register Mask  */

/* -------- AON_PWR_SEQ_SERVICED_REQUEST : (AON_PWR_SEQ Offset: 0x308) (R/ 16) Serviced Request Status Bits -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t GPIO_WAKEUP:1;             /**< bit:      0  Indicates GPIO wakeup has been serviced  */
    uint16_t :2;                        /**< bit:   1..2  Reserved */
    uint16_t AON_ST_WAKEUP:1;           /**< bit:      3  Indicates AON_ST wakeup has been serviced */
    uint16_t LPMCU_WAKEUP:1;            /**< bit:      4  Indicates LPMCU wakeup has been serviced */
    uint16_t BLE_ST_WAKEUP:1;           /**< bit:      5  Indicates BLE_ST wakeup has been serviced */
    uint16_t :2;                        /**< bit:   6..7  Reserved */
    uint16_t SLEEP_1:1;                 /**< bit:      8  Indicates SLEEP 1 has been serviced      */
    uint16_t :7;                        /**< bit:  9..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} AON_PWR_SEQ_SERVICED_REQUEST_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_SERVICED_REQUEST_OFFSET 0x308                                         /**<  (AON_PWR_SEQ_SERVICED_REQUEST) Serviced Request Status Bits  Offset */
#define AON_PWR_SEQ_SERVICED_REQUEST_RESETVALUE 0x00u                                         /**<  (AON_PWR_SEQ_SERVICED_REQUEST) Serviced Request Status Bits  Reset Value */

#define AON_PWR_SEQ_SERVICED_REQUEST_GPIO_WAKEUP_Pos 0                                              /**< (AON_PWR_SEQ_SERVICED_REQUEST) Indicates GPIO wakeup has been serviced Position */
#define AON_PWR_SEQ_SERVICED_REQUEST_GPIO_WAKEUP_Msk (0x1u << AON_PWR_SEQ_SERVICED_REQUEST_GPIO_WAKEUP_Pos)  /**< (AON_PWR_SEQ_SERVICED_REQUEST) Indicates GPIO wakeup has been serviced Mask */
#define AON_PWR_SEQ_SERVICED_REQUEST_GPIO_WAKEUP AON_PWR_SEQ_SERVICED_REQUEST_GPIO_WAKEUP_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_SERVICED_REQUEST_GPIO_WAKEUP_Msk instead */
#define AON_PWR_SEQ_SERVICED_REQUEST_AON_ST_WAKEUP_Pos 3                                              /**< (AON_PWR_SEQ_SERVICED_REQUEST) Indicates AON_ST wakeup has been serviced Position */
#define AON_PWR_SEQ_SERVICED_REQUEST_AON_ST_WAKEUP_Msk (0x1u << AON_PWR_SEQ_SERVICED_REQUEST_AON_ST_WAKEUP_Pos)  /**< (AON_PWR_SEQ_SERVICED_REQUEST) Indicates AON_ST wakeup has been serviced Mask */
#define AON_PWR_SEQ_SERVICED_REQUEST_AON_ST_WAKEUP AON_PWR_SEQ_SERVICED_REQUEST_AON_ST_WAKEUP_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_SERVICED_REQUEST_AON_ST_WAKEUP_Msk instead */
#define AON_PWR_SEQ_SERVICED_REQUEST_LPMCU_WAKEUP_Pos 4                                              /**< (AON_PWR_SEQ_SERVICED_REQUEST) Indicates LPMCU wakeup has been serviced Position */
#define AON_PWR_SEQ_SERVICED_REQUEST_LPMCU_WAKEUP_Msk (0x1u << AON_PWR_SEQ_SERVICED_REQUEST_LPMCU_WAKEUP_Pos)  /**< (AON_PWR_SEQ_SERVICED_REQUEST) Indicates LPMCU wakeup has been serviced Mask */
#define AON_PWR_SEQ_SERVICED_REQUEST_LPMCU_WAKEUP AON_PWR_SEQ_SERVICED_REQUEST_LPMCU_WAKEUP_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_SERVICED_REQUEST_LPMCU_WAKEUP_Msk instead */
#define AON_PWR_SEQ_SERVICED_REQUEST_BLE_ST_WAKEUP_Pos 5                                              /**< (AON_PWR_SEQ_SERVICED_REQUEST) Indicates BLE_ST wakeup has been serviced Position */
#define AON_PWR_SEQ_SERVICED_REQUEST_BLE_ST_WAKEUP_Msk (0x1u << AON_PWR_SEQ_SERVICED_REQUEST_BLE_ST_WAKEUP_Pos)  /**< (AON_PWR_SEQ_SERVICED_REQUEST) Indicates BLE_ST wakeup has been serviced Mask */
#define AON_PWR_SEQ_SERVICED_REQUEST_BLE_ST_WAKEUP AON_PWR_SEQ_SERVICED_REQUEST_BLE_ST_WAKEUP_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_SERVICED_REQUEST_BLE_ST_WAKEUP_Msk instead */
#define AON_PWR_SEQ_SERVICED_REQUEST_SLEEP_1_Pos 8                                              /**< (AON_PWR_SEQ_SERVICED_REQUEST) Indicates SLEEP 1 has been serviced Position */
#define AON_PWR_SEQ_SERVICED_REQUEST_SLEEP_1_Msk (0x1u << AON_PWR_SEQ_SERVICED_REQUEST_SLEEP_1_Pos)  /**< (AON_PWR_SEQ_SERVICED_REQUEST) Indicates SLEEP 1 has been serviced Mask */
#define AON_PWR_SEQ_SERVICED_REQUEST_SLEEP_1 AON_PWR_SEQ_SERVICED_REQUEST_SLEEP_1_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_SERVICED_REQUEST_SLEEP_1_Msk instead */
#define AON_PWR_SEQ_SERVICED_REQUEST_MASK   0x139u                                         /**< \deprecated (AON_PWR_SEQ_SERVICED_REQUEST) Register MASK  (Use AON_PWR_SEQ_SERVICED_REQUEST_Msk instead)  */
#define AON_PWR_SEQ_SERVICED_REQUEST_Msk    0x139u                                         /**< (AON_PWR_SEQ_SERVICED_REQUEST) Register Mask  */

/* -------- AON_PWR_SEQ_ACTIVE_REQUEST : (AON_PWR_SEQ Offset: 0x30c) (R/ 16) Active Request Status Bits -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t GPIO_WAKEUP:1;             /**< bit:      0  Indicates GPIO wakeup is the active request */
    uint16_t :2;                        /**< bit:   1..2  Reserved */
    uint16_t AON_ST_WAKEUP:1;           /**< bit:      3  Indicates AON_ST wakeup is the active request */
    uint16_t LPMCU_WAKEUP:1;            /**< bit:      4  Indicates LPMCU wakeup is the active request */
    uint16_t BLE_ST_WAKEUP:1;           /**< bit:      5  Indicates BLE_ST wakeup is the active request */
    uint16_t :2;                        /**< bit:   6..7  Reserved */
    uint16_t SLEEP_1:1;                 /**< bit:      8  Indicates SLEEP 1 is the active request  */
    uint16_t :7;                        /**< bit:  9..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} AON_PWR_SEQ_ACTIVE_REQUEST_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_ACTIVE_REQUEST_OFFSET   0x30C                                         /**<  (AON_PWR_SEQ_ACTIVE_REQUEST) Active Request Status Bits  Offset */
#define AON_PWR_SEQ_ACTIVE_REQUEST_RESETVALUE 0x00u                                         /**<  (AON_PWR_SEQ_ACTIVE_REQUEST) Active Request Status Bits  Reset Value */

#define AON_PWR_SEQ_ACTIVE_REQUEST_GPIO_WAKEUP_Pos 0                                              /**< (AON_PWR_SEQ_ACTIVE_REQUEST) Indicates GPIO wakeup is the active request Position */
#define AON_PWR_SEQ_ACTIVE_REQUEST_GPIO_WAKEUP_Msk (0x1u << AON_PWR_SEQ_ACTIVE_REQUEST_GPIO_WAKEUP_Pos)  /**< (AON_PWR_SEQ_ACTIVE_REQUEST) Indicates GPIO wakeup is the active request Mask */
#define AON_PWR_SEQ_ACTIVE_REQUEST_GPIO_WAKEUP AON_PWR_SEQ_ACTIVE_REQUEST_GPIO_WAKEUP_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_ACTIVE_REQUEST_GPIO_WAKEUP_Msk instead */
#define AON_PWR_SEQ_ACTIVE_REQUEST_AON_ST_WAKEUP_Pos 3                                              /**< (AON_PWR_SEQ_ACTIVE_REQUEST) Indicates AON_ST wakeup is the active request Position */
#define AON_PWR_SEQ_ACTIVE_REQUEST_AON_ST_WAKEUP_Msk (0x1u << AON_PWR_SEQ_ACTIVE_REQUEST_AON_ST_WAKEUP_Pos)  /**< (AON_PWR_SEQ_ACTIVE_REQUEST) Indicates AON_ST wakeup is the active request Mask */
#define AON_PWR_SEQ_ACTIVE_REQUEST_AON_ST_WAKEUP AON_PWR_SEQ_ACTIVE_REQUEST_AON_ST_WAKEUP_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_ACTIVE_REQUEST_AON_ST_WAKEUP_Msk instead */
#define AON_PWR_SEQ_ACTIVE_REQUEST_LPMCU_WAKEUP_Pos 4                                              /**< (AON_PWR_SEQ_ACTIVE_REQUEST) Indicates LPMCU wakeup is the active request Position */
#define AON_PWR_SEQ_ACTIVE_REQUEST_LPMCU_WAKEUP_Msk (0x1u << AON_PWR_SEQ_ACTIVE_REQUEST_LPMCU_WAKEUP_Pos)  /**< (AON_PWR_SEQ_ACTIVE_REQUEST) Indicates LPMCU wakeup is the active request Mask */
#define AON_PWR_SEQ_ACTIVE_REQUEST_LPMCU_WAKEUP AON_PWR_SEQ_ACTIVE_REQUEST_LPMCU_WAKEUP_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_ACTIVE_REQUEST_LPMCU_WAKEUP_Msk instead */
#define AON_PWR_SEQ_ACTIVE_REQUEST_BLE_ST_WAKEUP_Pos 5                                              /**< (AON_PWR_SEQ_ACTIVE_REQUEST) Indicates BLE_ST wakeup is the active request Position */
#define AON_PWR_SEQ_ACTIVE_REQUEST_BLE_ST_WAKEUP_Msk (0x1u << AON_PWR_SEQ_ACTIVE_REQUEST_BLE_ST_WAKEUP_Pos)  /**< (AON_PWR_SEQ_ACTIVE_REQUEST) Indicates BLE_ST wakeup is the active request Mask */
#define AON_PWR_SEQ_ACTIVE_REQUEST_BLE_ST_WAKEUP AON_PWR_SEQ_ACTIVE_REQUEST_BLE_ST_WAKEUP_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_ACTIVE_REQUEST_BLE_ST_WAKEUP_Msk instead */
#define AON_PWR_SEQ_ACTIVE_REQUEST_SLEEP_1_Pos 8                                              /**< (AON_PWR_SEQ_ACTIVE_REQUEST) Indicates SLEEP 1 is the active request Position */
#define AON_PWR_SEQ_ACTIVE_REQUEST_SLEEP_1_Msk (0x1u << AON_PWR_SEQ_ACTIVE_REQUEST_SLEEP_1_Pos)  /**< (AON_PWR_SEQ_ACTIVE_REQUEST) Indicates SLEEP 1 is the active request Mask */
#define AON_PWR_SEQ_ACTIVE_REQUEST_SLEEP_1  AON_PWR_SEQ_ACTIVE_REQUEST_SLEEP_1_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_ACTIVE_REQUEST_SLEEP_1_Msk instead */
#define AON_PWR_SEQ_ACTIVE_REQUEST_MASK     0x139u                                         /**< \deprecated (AON_PWR_SEQ_ACTIVE_REQUEST) Register MASK  (Use AON_PWR_SEQ_ACTIVE_REQUEST_Msk instead)  */
#define AON_PWR_SEQ_ACTIVE_REQUEST_Msk      0x139u                                         /**< (AON_PWR_SEQ_ACTIVE_REQUEST) Register Mask  */

/* -------- AON_PWR_SEQ_LOGIC_FSM_STATES : (AON_PWR_SEQ Offset: 0x3f0) (R/ 32) Current Logic FSM States -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t MAIN_FSM_STATE:3;          /**< bit:   0..2  Main FSM State                           */
    uint32_t :5;                        /**< bit:   3..7  Reserved */
    uint32_t BLE_ON_STATE:1;            /**< bit:      8  If 1, then PD4 and PD5 are ON            */
    uint32_t BLE_OFF_STATE:1;           /**< bit:      9  If 1, then PD4 and PD5 are OFF (PD5 is in RET if set by ARM) */
    uint32_t :2;                        /**< bit: 10..11  Reserved */
    uint32_t PD6_ON_STATE:1;            /**< bit:     12  If 1, then PD6 is ON                     */
    uint32_t PD6_OFF_STATE:1;           /**< bit:     13  If 1, then PD6 is OFF                    */
    uint32_t :2;                        /**< bit: 14..15  Reserved */
    uint32_t PD7_ON_STATE:1;            /**< bit:     16  If 1, then PD7 is ON                     */
    uint32_t PD7_OFF_STATE:1;           /**< bit:     17  If 1, then PD7 is OFF                    */
    uint32_t :14;                       /**< bit: 18..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_PWR_SEQ_LOGIC_FSM_STATES_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_PWR_SEQ_LOGIC_FSM_STATES_OFFSET 0x3F0                                         /**<  (AON_PWR_SEQ_LOGIC_FSM_STATES) Current Logic FSM States  Offset */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_RESETVALUE 0x00u                                         /**<  (AON_PWR_SEQ_LOGIC_FSM_STATES) Current Logic FSM States  Reset Value */

#define AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_Pos 0                                              /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) Main FSM State Position */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_Msk (0x7u << AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) Main FSM State Mask */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE(value) (AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_Msk & ((value) << AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_Pos))
#define   AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_0_Val 0x0u                                           /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) RESET  */
#define   AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_1_Val 0x1u                                           /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) READY  */
#define   AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_2_Val 0x2u                                           /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) TRANS  */
#define   AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_3_Val 0x3u                                           /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) RESET_TO_READY  */
#define   AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_4_Val 0x4u                                           /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) READY_TO_TRANS  */
#define   AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_5_Val 0x5u                                           /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) TRANS_TO_READY  */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_0 (AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_0_Val << AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) RESET Position  */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_1 (AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_1_Val << AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) READY Position  */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_2 (AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_2_Val << AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) TRANS Position  */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_3 (AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_3_Val << AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) RESET_TO_READY Position  */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_4 (AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_4_Val << AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) READY_TO_TRANS Position  */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_5 (AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_5_Val << AON_PWR_SEQ_LOGIC_FSM_STATES_MAIN_FSM_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) TRANS_TO_READY Position  */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_BLE_ON_STATE_Pos 8                                              /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) If 1, then PD4 and PD5 are ON Position */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_BLE_ON_STATE_Msk (0x1u << AON_PWR_SEQ_LOGIC_FSM_STATES_BLE_ON_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) If 1, then PD4 and PD5 are ON Mask */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_BLE_ON_STATE AON_PWR_SEQ_LOGIC_FSM_STATES_BLE_ON_STATE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LOGIC_FSM_STATES_BLE_ON_STATE_Msk instead */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_BLE_OFF_STATE_Pos 9                                              /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) If 1, then PD4 and PD5 are OFF (PD5 is in RET if set by ARM) Position */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_BLE_OFF_STATE_Msk (0x1u << AON_PWR_SEQ_LOGIC_FSM_STATES_BLE_OFF_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) If 1, then PD4 and PD5 are OFF (PD5 is in RET if set by ARM) Mask */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_BLE_OFF_STATE AON_PWR_SEQ_LOGIC_FSM_STATES_BLE_OFF_STATE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LOGIC_FSM_STATES_BLE_OFF_STATE_Msk instead */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_PD6_ON_STATE_Pos 12                                             /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) If 1, then PD6 is ON Position */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_PD6_ON_STATE_Msk (0x1u << AON_PWR_SEQ_LOGIC_FSM_STATES_PD6_ON_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) If 1, then PD6 is ON Mask */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_PD6_ON_STATE AON_PWR_SEQ_LOGIC_FSM_STATES_PD6_ON_STATE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LOGIC_FSM_STATES_PD6_ON_STATE_Msk instead */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_PD6_OFF_STATE_Pos 13                                             /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) If 1, then PD6 is OFF Position */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_PD6_OFF_STATE_Msk (0x1u << AON_PWR_SEQ_LOGIC_FSM_STATES_PD6_OFF_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) If 1, then PD6 is OFF Mask */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_PD6_OFF_STATE AON_PWR_SEQ_LOGIC_FSM_STATES_PD6_OFF_STATE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LOGIC_FSM_STATES_PD6_OFF_STATE_Msk instead */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_PD7_ON_STATE_Pos 16                                             /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) If 1, then PD7 is ON Position */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_PD7_ON_STATE_Msk (0x1u << AON_PWR_SEQ_LOGIC_FSM_STATES_PD7_ON_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) If 1, then PD7 is ON Mask */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_PD7_ON_STATE AON_PWR_SEQ_LOGIC_FSM_STATES_PD7_ON_STATE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LOGIC_FSM_STATES_PD7_ON_STATE_Msk instead */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_PD7_OFF_STATE_Pos 17                                             /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) If 1, then PD7 is OFF Position */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_PD7_OFF_STATE_Msk (0x1u << AON_PWR_SEQ_LOGIC_FSM_STATES_PD7_OFF_STATE_Pos)  /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) If 1, then PD7 is OFF Mask */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_PD7_OFF_STATE AON_PWR_SEQ_LOGIC_FSM_STATES_PD7_OFF_STATE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_PWR_SEQ_LOGIC_FSM_STATES_PD7_OFF_STATE_Msk instead */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_MASK   0x33307u                                       /**< \deprecated (AON_PWR_SEQ_LOGIC_FSM_STATES) Register MASK  (Use AON_PWR_SEQ_LOGIC_FSM_STATES_Msk instead)  */
#define AON_PWR_SEQ_LOGIC_FSM_STATES_Msk    0x33307u                                       /**< (AON_PWR_SEQ_LOGIC_FSM_STATES) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief AON_PWR_SEQ hardware registers */
typedef struct {  /* Always On Power Sequencer */
  RwReg8  GPIO_WAKEUP_CTRL; /**< (AON_PWR_SEQ Offset: 0x00) Controls the wakeup enable for GPIO_0, GPIO_1 and GPIO_2 (Pinmux will control the ARM wakeup) */
  __I  uint8_t  Reserved1[11];
  RwReg8  AON_ST_WAKEUP_CTRL; /**< (AON_PWR_SEQ Offset: 0x0C) Controls the wakeup enable for the Always On Sleep Timer (AON_ST) */
  __I  uint8_t  Reserved2[3];
  RwReg16 LPMCU_WAKEUP_CTRL; /**< (AON_PWR_SEQ Offset: 0x10) Controls the wakeup enable for the Low Power Micro Controller Unit (LPMCU) */
  __I  uint8_t  Reserved3[2];
  RwReg8  BLE_ST_WAKEUP_CTRL; /**< (AON_PWR_SEQ Offset: 0x14) Controls the wakeup enable for the BLE Sleep Timer (BLE_ST) */
  __I  uint8_t  Reserved4[11];
  RwReg   LPMCU_SLEEP_1_CTRL; /**< (AON_PWR_SEQ Offset: 0x20) Controls the sleep and retention options for SLEEP request 1 from the ARM */
  __I  uint32_t Reserved5[7];
  RwReg   OFF_DELAY_0_CTRL; /**< (AON_PWR_SEQ Offset: 0x40) Power OFF Delays */
  RwReg   OFF_DELAY_1_CTRL; /**< (AON_PWR_SEQ Offset: 0x44) Power OFF Delays */
  RwReg16 ON_DELAY_0_CTRL; /**< (AON_PWR_SEQ Offset: 0x48) Power ON Delays */
  __I  uint8_t  Reserved6[2];
  RwReg   ON_DELAY_1_CTRL; /**< (AON_PWR_SEQ Offset: 0x4C) Power ON Delays */
  RwReg16 VDD_DCDC_EN_DELAY_CTRL; /**< (AON_PWR_SEQ Offset: 0x50) VDD_DCDC_EN Delay Control */
  __I  uint8_t  Reserved7[454];
  RwReg16 MISC_BYPASS_0_CTRL; /**< (AON_PWR_SEQ Offset: 0x218) Bypass control for misc signals */
  __I  uint8_t  Reserved8[230];
  RoReg8  RAW_WAKEUP_BITS; /**< (AON_PWR_SEQ Offset: 0x300) Raw Wakeup Bits */
  __I  uint8_t  Reserved9[3];
  RoReg16 PD_WAKEUP_BITS; /**< (AON_PWR_SEQ Offset: 0x304) Individual Power Domain Wakeup Bits */
  __I  uint8_t  Reserved10[2];
  RoReg16 SERVICED_REQUEST; /**< (AON_PWR_SEQ Offset: 0x308) Serviced Request Status Bits */
  __I  uint8_t  Reserved11[2];
  RoReg16 ACTIVE_REQUEST; /**< (AON_PWR_SEQ Offset: 0x30C) Active Request Status Bits */
  __I  uint8_t  Reserved12[226];
  RoReg   LOGIC_FSM_STATES; /**< (AON_PWR_SEQ Offset: 0x3F0) Current Logic FSM States */
} AonPwrSeq;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief AON_PWR_SEQ hardware registers */
typedef struct {  /* Always On Power Sequencer */
  __IO AON_PWR_SEQ_GPIO_WAKEUP_CTRL_Type GPIO_WAKEUP_CTRL; /**< Offset: 0x00 (R/W   8) Controls the wakeup enable for GPIO_0, GPIO_1 and GPIO_2 (Pinmux will control the ARM wakeup) */
       RoReg8                         Reserved1[0xB];
  __IO AON_PWR_SEQ_AON_ST_WAKEUP_CTRL_Type AON_ST_WAKEUP_CTRL; /**< Offset: 0x0C (R/W   8) Controls the wakeup enable for the Always On Sleep Timer (AON_ST) */
       RoReg8                         Reserved2[0x3];
  __IO AON_PWR_SEQ_LPMCU_WAKEUP_CTRL_Type LPMCU_WAKEUP_CTRL; /**< Offset: 0x10 (R/W  16) Controls the wakeup enable for the Low Power Micro Controller Unit (LPMCU) */
       RoReg8                         Reserved3[0x2];
  __IO AON_PWR_SEQ_BLE_ST_WAKEUP_CTRL_Type BLE_ST_WAKEUP_CTRL; /**< Offset: 0x14 (R/W   8) Controls the wakeup enable for the BLE Sleep Timer (BLE_ST) */
       RoReg8                         Reserved4[0xB];
  __IO AON_PWR_SEQ_LPMCU_SLEEP_1_CTRL_Type LPMCU_SLEEP_1_CTRL; /**< Offset: 0x20 (R/W  32) Controls the sleep and retention options for SLEEP request 1 from the ARM */
       RoReg8                         Reserved5[0x1C];
  __IO AON_PWR_SEQ_OFF_DELAY_0_CTRL_Type OFF_DELAY_0_CTRL; /**< Offset: 0x40 (R/W  32) Power OFF Delays */
  __IO AON_PWR_SEQ_OFF_DELAY_1_CTRL_Type OFF_DELAY_1_CTRL; /**< Offset: 0x44 (R/W  32) Power OFF Delays */
  __IO AON_PWR_SEQ_ON_DELAY_0_CTRL_Type ON_DELAY_0_CTRL; /**< Offset: 0x48 (R/W  16) Power ON Delays */
       RoReg8                         Reserved6[0x2];
  __IO AON_PWR_SEQ_ON_DELAY_1_CTRL_Type ON_DELAY_1_CTRL; /**< Offset: 0x4C (R/W  32) Power ON Delays */
  __IO AON_PWR_SEQ_VDD_DCDC_EN_DELAY_CTRL_Type VDD_DCDC_EN_DELAY_CTRL; /**< Offset: 0x50 (R/W  16) VDD_DCDC_EN Delay Control */
       RoReg8                         Reserved7[0x1C6];
  __IO AON_PWR_SEQ_MISC_BYPASS_0_CTRL_Type MISC_BYPASS_0_CTRL; /**< Offset: 0x218 (R/W  16) Bypass control for misc signals */
       RoReg8                         Reserved8[0xE6];
  __I  AON_PWR_SEQ_RAW_WAKEUP_BITS_Type RAW_WAKEUP_BITS; /**< Offset: 0x300 (R/    8) Raw Wakeup Bits */
       RoReg8                         Reserved9[0x3];
  __I  AON_PWR_SEQ_PD_WAKEUP_BITS_Type PD_WAKEUP_BITS; /**< Offset: 0x304 (R/   16) Individual Power Domain Wakeup Bits */
       RoReg8                         Reserved10[0x2];
  __I  AON_PWR_SEQ_SERVICED_REQUEST_Type SERVICED_REQUEST; /**< Offset: 0x308 (R/   16) Serviced Request Status Bits */
       RoReg8                         Reserved11[0x2];
  __I  AON_PWR_SEQ_ACTIVE_REQUEST_Type ACTIVE_REQUEST; /**< Offset: 0x30C (R/   16) Active Request Status Bits */
       RoReg8                         Reserved12[0xE2];
  __I  AON_PWR_SEQ_LOGIC_FSM_STATES_Type LOGIC_FSM_STATES; /**< Offset: 0x3F0 (R/   32) Current Logic FSM States */
} AonPwrSeq;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_AON_PWR_SEQ_COMPONENT_ */
