/**
 * \file
 *
 * \brief Component description for WDT
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

#ifndef _SAMB11_WDT_COMPONENT_
#define _SAMB11_WDT_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR WDT */
/* ========================================================================== */
/** \addtogroup SAMB11_WDT Watchdog0 Timer 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define WDT_W1234
#define REV_WDT                          0x100

/* -------- WDT_WDOGLOAD : (WDT Offset: 0x00) (R/W 32) Watchdog Load Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t WDOGLOAD:32;               /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} WDT_WDOGLOAD_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGLOAD_OFFSET                 0x00                                          /**<  (WDT_WDOGLOAD) Watchdog Load Register  Offset */
#define WDT_WDOGLOAD_RESETVALUE             0xFFFFFFFFu                                   /**<  (WDT_WDOGLOAD) Watchdog Load Register  Reset Value */

#define WDT_WDOGLOAD_WDOGLOAD_Pos           0                                              /**< (WDT_WDOGLOAD)  Position */
#define WDT_WDOGLOAD_WDOGLOAD_Msk           (0xFFFFFFFFu << WDT_WDOGLOAD_WDOGLOAD_Pos)     /**< (WDT_WDOGLOAD)  Mask */
#define WDT_WDOGLOAD_WDOGLOAD(value)        (WDT_WDOGLOAD_WDOGLOAD_Msk & ((value) << WDT_WDOGLOAD_WDOGLOAD_Pos))
#define WDT_WDOGLOAD_MASK                   0xFFFFFFFFu                                    /**< \deprecated (WDT_WDOGLOAD) Register MASK  (Use WDT_WDOGLOAD_Msk instead)  */
#define WDT_WDOGLOAD_Msk                    0xFFFFFFFFu                                    /**< (WDT_WDOGLOAD) Register Mask  */

/* -------- WDT_WDOGVALUE : (WDT Offset: 0x04) (R/ 32) Watchdog Value Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t WDOGVALUE:32;              /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} WDT_WDOGVALUE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGVALUE_OFFSET                0x04                                          /**<  (WDT_WDOGVALUE) Watchdog Value Register  Offset */
#define WDT_WDOGVALUE_RESETVALUE            0xFFFFFFFFu                                   /**<  (WDT_WDOGVALUE) Watchdog Value Register  Reset Value */

#define WDT_WDOGVALUE_WDOGVALUE_Pos         0                                              /**< (WDT_WDOGVALUE)  Position */
#define WDT_WDOGVALUE_WDOGVALUE_Msk         (0xFFFFFFFFu << WDT_WDOGVALUE_WDOGVALUE_Pos)   /**< (WDT_WDOGVALUE)  Mask */
#define WDT_WDOGVALUE_WDOGVALUE(value)      (WDT_WDOGVALUE_WDOGVALUE_Msk & ((value) << WDT_WDOGVALUE_WDOGVALUE_Pos))
#define WDT_WDOGVALUE_MASK                  0xFFFFFFFFu                                    /**< \deprecated (WDT_WDOGVALUE) Register MASK  (Use WDT_WDOGVALUE_Msk instead)  */
#define WDT_WDOGVALUE_Msk                   0xFFFFFFFFu                                    /**< (WDT_WDOGVALUE) Register Mask  */

/* -------- WDT_WDOGCONTROL : (WDT Offset: 0x08) (R/W 8) Watchdog Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  INTEN:1;                   /**< bit:      0  Active High Enable Interrupt Event       */
    uint8_t  RESEN:1;                   /**< bit:      1  Active High Enable Watchdog Reset Output */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGCONTROL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGCONTROL_OFFSET              0x08                                          /**<  (WDT_WDOGCONTROL) Watchdog Control Register  Offset */
#define WDT_WDOGCONTROL_RESETVALUE          0x00u                                         /**<  (WDT_WDOGCONTROL) Watchdog Control Register  Reset Value */

#define WDT_WDOGCONTROL_INTEN_Pos           0                                              /**< (WDT_WDOGCONTROL) Active High Enable Interrupt Event Position */
#define WDT_WDOGCONTROL_INTEN_Msk           (0x1u << WDT_WDOGCONTROL_INTEN_Pos)            /**< (WDT_WDOGCONTROL) Active High Enable Interrupt Event Mask */
#define WDT_WDOGCONTROL_INTEN               WDT_WDOGCONTROL_INTEN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_WDOGCONTROL_INTEN_Msk instead */
#define WDT_WDOGCONTROL_RESEN_Pos           1                                              /**< (WDT_WDOGCONTROL) Active High Enable Watchdog Reset Output Position */
#define WDT_WDOGCONTROL_RESEN_Msk           (0x1u << WDT_WDOGCONTROL_RESEN_Pos)            /**< (WDT_WDOGCONTROL) Active High Enable Watchdog Reset Output Mask */
#define WDT_WDOGCONTROL_RESEN               WDT_WDOGCONTROL_RESEN_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_WDOGCONTROL_RESEN_Msk instead */
#define WDT_WDOGCONTROL_MASK                0x03u                                          /**< \deprecated (WDT_WDOGCONTROL) Register MASK  (Use WDT_WDOGCONTROL_Msk instead)  */
#define WDT_WDOGCONTROL_Msk                 0x03u                                          /**< (WDT_WDOGCONTROL) Register Mask  */

/* -------- WDT_WDOGINTCLR : (WDT Offset: 0x0c) (/W 8) Watchdog Clear Interrupt Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WDOGINTCLR:1;              /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGINTCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGINTCLR_OFFSET               0x0C                                          /**<  (WDT_WDOGINTCLR) Watchdog Clear Interrupt Register  Offset */
#define WDT_WDOGINTCLR_RESETVALUE           0x00u                                         /**<  (WDT_WDOGINTCLR) Watchdog Clear Interrupt Register  Reset Value */

#define WDT_WDOGINTCLR_WDOGINTCLR_Pos       0                                              /**< (WDT_WDOGINTCLR)  Position */
#define WDT_WDOGINTCLR_WDOGINTCLR_Msk       (0x1u << WDT_WDOGINTCLR_WDOGINTCLR_Pos)        /**< (WDT_WDOGINTCLR)  Mask */
#define WDT_WDOGINTCLR_WDOGINTCLR           WDT_WDOGINTCLR_WDOGINTCLR_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_WDOGINTCLR_WDOGINTCLR_Msk instead */
#define WDT_WDOGINTCLR_MASK                 0x01u                                          /**< \deprecated (WDT_WDOGINTCLR) Register MASK  (Use WDT_WDOGINTCLR_Msk instead)  */
#define WDT_WDOGINTCLR_Msk                  0x01u                                          /**< (WDT_WDOGINTCLR) Register Mask  */

/* -------- WDT_WDOGRIS : (WDT Offset: 0x10) (R/ 8) Watchdog Raw Interrupt Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WDOGRIS:1;                 /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGRIS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGRIS_OFFSET                  0x10                                          /**<  (WDT_WDOGRIS) Watchdog Raw Interrupt Status Register  Offset */
#define WDT_WDOGRIS_RESETVALUE              0x00u                                         /**<  (WDT_WDOGRIS) Watchdog Raw Interrupt Status Register  Reset Value */

#define WDT_WDOGRIS_WDOGRIS_Pos             0                                              /**< (WDT_WDOGRIS)  Position */
#define WDT_WDOGRIS_WDOGRIS_Msk             (0x1u << WDT_WDOGRIS_WDOGRIS_Pos)              /**< (WDT_WDOGRIS)  Mask */
#define WDT_WDOGRIS_WDOGRIS                 WDT_WDOGRIS_WDOGRIS_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_WDOGRIS_WDOGRIS_Msk instead */
#define WDT_WDOGRIS_MASK                    0x01u                                          /**< \deprecated (WDT_WDOGRIS) Register MASK  (Use WDT_WDOGRIS_Msk instead)  */
#define WDT_WDOGRIS_Msk                     0x01u                                          /**< (WDT_WDOGRIS) Register Mask  */

/* -------- WDT_WDOGMIS : (WDT Offset: 0x14) (R/ 8) Watchdog Interrupt Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WDOGMIS:1;                 /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGMIS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGMIS_OFFSET                  0x14                                          /**<  (WDT_WDOGMIS) Watchdog Interrupt Status Register  Offset */
#define WDT_WDOGMIS_RESETVALUE              0x00u                                         /**<  (WDT_WDOGMIS) Watchdog Interrupt Status Register  Reset Value */

#define WDT_WDOGMIS_WDOGMIS_Pos             0                                              /**< (WDT_WDOGMIS)  Position */
#define WDT_WDOGMIS_WDOGMIS_Msk             (0x1u << WDT_WDOGMIS_WDOGMIS_Pos)              /**< (WDT_WDOGMIS)  Mask */
#define WDT_WDOGMIS_WDOGMIS                 WDT_WDOGMIS_WDOGMIS_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_WDOGMIS_WDOGMIS_Msk instead */
#define WDT_WDOGMIS_MASK                    0x01u                                          /**< \deprecated (WDT_WDOGMIS) Register MASK  (Use WDT_WDOGMIS_Msk instead)  */
#define WDT_WDOGMIS_Msk                     0x01u                                          /**< (WDT_WDOGMIS) Register Mask  */

/* -------- WDT_WDOGLOCK : (WDT Offset: 0xc00) (R/W 32) Watchdog Lock Register (Write 0x1ACCE551 to enable write access to all other registers) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t ENABLE_STATUS:1;           /**< bit:      0  Read back of 1 indicates that write access is enabled */
    uint32_t ENABLE_REGISTER_WRITES:31;  /**< bit:  1..31  Read back all 0s, write 0x1ACCE551 to enable write access to all other registers */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} WDT_WDOGLOCK_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGLOCK_OFFSET                 0xC00                                         /**<  (WDT_WDOGLOCK) Watchdog Lock Register (Write 0x1ACCE551 to enable write access to all other registers)  Offset */
#define WDT_WDOGLOCK_RESETVALUE             0x00u                                         /**<  (WDT_WDOGLOCK) Watchdog Lock Register (Write 0x1ACCE551 to enable write access to all other registers)  Reset Value */

#define WDT_WDOGLOCK_ENABLE_STATUS_Pos      0                                              /**< (WDT_WDOGLOCK) Read back of 1 indicates that write access is enabled Position */
#define WDT_WDOGLOCK_ENABLE_STATUS_Msk      (0x1u << WDT_WDOGLOCK_ENABLE_STATUS_Pos)       /**< (WDT_WDOGLOCK) Read back of 1 indicates that write access is enabled Mask */
#define WDT_WDOGLOCK_ENABLE_STATUS          WDT_WDOGLOCK_ENABLE_STATUS_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_WDOGLOCK_ENABLE_STATUS_Msk instead */
#define WDT_WDOGLOCK_ENABLE_REGISTER_WRITES_Pos 1                                              /**< (WDT_WDOGLOCK) Read back all 0s, write 0x1ACCE551 to enable write access to all other registers Position */
#define WDT_WDOGLOCK_ENABLE_REGISTER_WRITES_Msk (0x7FFFFFFFu << WDT_WDOGLOCK_ENABLE_REGISTER_WRITES_Pos)  /**< (WDT_WDOGLOCK) Read back all 0s, write 0x1ACCE551 to enable write access to all other registers Mask */
#define WDT_WDOGLOCK_ENABLE_REGISTER_WRITES(value) (WDT_WDOGLOCK_ENABLE_REGISTER_WRITES_Msk & ((value) << WDT_WDOGLOCK_ENABLE_REGISTER_WRITES_Pos))
#define WDT_WDOGLOCK_MASK                   0xFFFFFFFFu                                    /**< \deprecated (WDT_WDOGLOCK) Register MASK  (Use WDT_WDOGLOCK_Msk instead)  */
#define WDT_WDOGLOCK_Msk                    0xFFFFFFFFu                                    /**< (WDT_WDOGLOCK) Register Mask  */

/* -------- WDT_WDOGITCR : (WDT Offset: 0xf00) (R/W 8) Watchdog Integration Test Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ENABLE:1;                  /**< bit:      0  Set HIGH to place watchdog into integration test mode */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGITCR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGITCR_OFFSET                 0xF00                                         /**<  (WDT_WDOGITCR) Watchdog Integration Test Control Register  Offset */
#define WDT_WDOGITCR_RESETVALUE             0x00u                                         /**<  (WDT_WDOGITCR) Watchdog Integration Test Control Register  Reset Value */

#define WDT_WDOGITCR_ENABLE_Pos             0                                              /**< (WDT_WDOGITCR) Set HIGH to place watchdog into integration test mode Position */
#define WDT_WDOGITCR_ENABLE_Msk             (0x1u << WDT_WDOGITCR_ENABLE_Pos)              /**< (WDT_WDOGITCR) Set HIGH to place watchdog into integration test mode Mask */
#define WDT_WDOGITCR_ENABLE                 WDT_WDOGITCR_ENABLE_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_WDOGITCR_ENABLE_Msk instead */
#define WDT_WDOGITCR_MASK                   0x01u                                          /**< \deprecated (WDT_WDOGITCR) Register MASK  (Use WDT_WDOGITCR_Msk instead)  */
#define WDT_WDOGITCR_Msk                    0x01u                                          /**< (WDT_WDOGITCR) Register Mask  */

/* -------- WDT_WDOGITOP : (WDT Offset: 0xf04) (R/W 8) Watchdog Integration Test Output Set Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WDOGRES_VALUE:1;           /**< bit:      0  Value output on WDOGRES when in Integration Test Mode */
    uint8_t  WDOGINT_VALUE:1;           /**< bit:      1  Value output on WDOGINT when in Integration Test Mode */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGITOP_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGITOP_OFFSET                 0xF04                                         /**<  (WDT_WDOGITOP) Watchdog Integration Test Output Set Register  Offset */
#define WDT_WDOGITOP_RESETVALUE             0x00u                                         /**<  (WDT_WDOGITOP) Watchdog Integration Test Output Set Register  Reset Value */

#define WDT_WDOGITOP_WDOGRES_VALUE_Pos      0                                              /**< (WDT_WDOGITOP) Value output on WDOGRES when in Integration Test Mode Position */
#define WDT_WDOGITOP_WDOGRES_VALUE_Msk      (0x1u << WDT_WDOGITOP_WDOGRES_VALUE_Pos)       /**< (WDT_WDOGITOP) Value output on WDOGRES when in Integration Test Mode Mask */
#define WDT_WDOGITOP_WDOGRES_VALUE          WDT_WDOGITOP_WDOGRES_VALUE_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_WDOGITOP_WDOGRES_VALUE_Msk instead */
#define WDT_WDOGITOP_WDOGINT_VALUE_Pos      1                                              /**< (WDT_WDOGITOP) Value output on WDOGINT when in Integration Test Mode Position */
#define WDT_WDOGITOP_WDOGINT_VALUE_Msk      (0x1u << WDT_WDOGITOP_WDOGINT_VALUE_Pos)       /**< (WDT_WDOGITOP) Value output on WDOGINT when in Integration Test Mode Mask */
#define WDT_WDOGITOP_WDOGINT_VALUE          WDT_WDOGITOP_WDOGINT_VALUE_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_WDOGITOP_WDOGINT_VALUE_Msk instead */
#define WDT_WDOGITOP_MASK                   0x03u                                          /**< \deprecated (WDT_WDOGITOP) Register MASK  (Use WDT_WDOGITOP_Msk instead)  */
#define WDT_WDOGITOP_Msk                    0x03u                                          /**< (WDT_WDOGITOP) Register Mask  */

/* -------- WDT_WDOGPERIPHID4 : (WDT Offset: 0xfd0) (R/ 8) Peripheral ID Register 4 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  JEP106_C_CODE:4;           /**< bit:   0..3  JEP106 C Code                            */
    uint8_t  BLOCK_COUNT:4;             /**< bit:   4..7  Block Count                              */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGPERIPHID4_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGPERIPHID4_OFFSET            0xFD0                                         /**<  (WDT_WDOGPERIPHID4) Peripheral ID Register 4  Offset */
#define WDT_WDOGPERIPHID4_RESETVALUE        0x04u                                         /**<  (WDT_WDOGPERIPHID4) Peripheral ID Register 4  Reset Value */

#define WDT_WDOGPERIPHID4_JEP106_C_CODE_Pos 0                                              /**< (WDT_WDOGPERIPHID4) JEP106 C Code Position */
#define WDT_WDOGPERIPHID4_JEP106_C_CODE_Msk (0xFu << WDT_WDOGPERIPHID4_JEP106_C_CODE_Pos)  /**< (WDT_WDOGPERIPHID4) JEP106 C Code Mask */
#define WDT_WDOGPERIPHID4_JEP106_C_CODE(value) (WDT_WDOGPERIPHID4_JEP106_C_CODE_Msk & ((value) << WDT_WDOGPERIPHID4_JEP106_C_CODE_Pos))
#define WDT_WDOGPERIPHID4_BLOCK_COUNT_Pos   4                                              /**< (WDT_WDOGPERIPHID4) Block Count Position */
#define WDT_WDOGPERIPHID4_BLOCK_COUNT_Msk   (0xFu << WDT_WDOGPERIPHID4_BLOCK_COUNT_Pos)    /**< (WDT_WDOGPERIPHID4) Block Count Mask */
#define WDT_WDOGPERIPHID4_BLOCK_COUNT(value) (WDT_WDOGPERIPHID4_BLOCK_COUNT_Msk & ((value) << WDT_WDOGPERIPHID4_BLOCK_COUNT_Pos))
#define WDT_WDOGPERIPHID4_MASK              0xFFu                                          /**< \deprecated (WDT_WDOGPERIPHID4) Register MASK  (Use WDT_WDOGPERIPHID4_Msk instead)  */
#define WDT_WDOGPERIPHID4_Msk               0xFFu                                          /**< (WDT_WDOGPERIPHID4) Register Mask  */

/* -------- WDT_WDOGPERIPHID5 : (WDT Offset: 0xfd4) (R/ 8) Peripheral ID Register 5 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WDOGPERIPHID5:8;           /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGPERIPHID5_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGPERIPHID5_OFFSET            0xFD4                                         /**<  (WDT_WDOGPERIPHID5) Peripheral ID Register 5  Offset */
#define WDT_WDOGPERIPHID5_RESETVALUE        0x00u                                         /**<  (WDT_WDOGPERIPHID5) Peripheral ID Register 5  Reset Value */

#define WDT_WDOGPERIPHID5_WDOGPERIPHID5_Pos 0                                              /**< (WDT_WDOGPERIPHID5)  Position */
#define WDT_WDOGPERIPHID5_WDOGPERIPHID5_Msk (0xFFu << WDT_WDOGPERIPHID5_WDOGPERIPHID5_Pos)  /**< (WDT_WDOGPERIPHID5)  Mask */
#define WDT_WDOGPERIPHID5_WDOGPERIPHID5(value) (WDT_WDOGPERIPHID5_WDOGPERIPHID5_Msk & ((value) << WDT_WDOGPERIPHID5_WDOGPERIPHID5_Pos))
#define WDT_WDOGPERIPHID5_MASK              0xFFu                                          /**< \deprecated (WDT_WDOGPERIPHID5) Register MASK  (Use WDT_WDOGPERIPHID5_Msk instead)  */
#define WDT_WDOGPERIPHID5_Msk               0xFFu                                          /**< (WDT_WDOGPERIPHID5) Register Mask  */

/* -------- WDT_WDOGPERIPHID6 : (WDT Offset: 0xfd8) (R/ 8) Peripheral ID Register 6 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WDOGPERIPHID6:8;           /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGPERIPHID6_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGPERIPHID6_OFFSET            0xFD8                                         /**<  (WDT_WDOGPERIPHID6) Peripheral ID Register 6  Offset */
#define WDT_WDOGPERIPHID6_RESETVALUE        0x00u                                         /**<  (WDT_WDOGPERIPHID6) Peripheral ID Register 6  Reset Value */

#define WDT_WDOGPERIPHID6_WDOGPERIPHID6_Pos 0                                              /**< (WDT_WDOGPERIPHID6)  Position */
#define WDT_WDOGPERIPHID6_WDOGPERIPHID6_Msk (0xFFu << WDT_WDOGPERIPHID6_WDOGPERIPHID6_Pos)  /**< (WDT_WDOGPERIPHID6)  Mask */
#define WDT_WDOGPERIPHID6_WDOGPERIPHID6(value) (WDT_WDOGPERIPHID6_WDOGPERIPHID6_Msk & ((value) << WDT_WDOGPERIPHID6_WDOGPERIPHID6_Pos))
#define WDT_WDOGPERIPHID6_MASK              0xFFu                                          /**< \deprecated (WDT_WDOGPERIPHID6) Register MASK  (Use WDT_WDOGPERIPHID6_Msk instead)  */
#define WDT_WDOGPERIPHID6_Msk               0xFFu                                          /**< (WDT_WDOGPERIPHID6) Register Mask  */

/* -------- WDT_WDOGPERIPHID7 : (WDT Offset: 0xfdc) (R/ 8) Peripheral ID Register 7 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WDOGPERIPHID7:8;           /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGPERIPHID7_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGPERIPHID7_OFFSET            0xFDC                                         /**<  (WDT_WDOGPERIPHID7) Peripheral ID Register 7  Offset */
#define WDT_WDOGPERIPHID7_RESETVALUE        0x00u                                         /**<  (WDT_WDOGPERIPHID7) Peripheral ID Register 7  Reset Value */

#define WDT_WDOGPERIPHID7_WDOGPERIPHID7_Pos 0                                              /**< (WDT_WDOGPERIPHID7)  Position */
#define WDT_WDOGPERIPHID7_WDOGPERIPHID7_Msk (0xFFu << WDT_WDOGPERIPHID7_WDOGPERIPHID7_Pos)  /**< (WDT_WDOGPERIPHID7)  Mask */
#define WDT_WDOGPERIPHID7_WDOGPERIPHID7(value) (WDT_WDOGPERIPHID7_WDOGPERIPHID7_Msk & ((value) << WDT_WDOGPERIPHID7_WDOGPERIPHID7_Pos))
#define WDT_WDOGPERIPHID7_MASK              0xFFu                                          /**< \deprecated (WDT_WDOGPERIPHID7) Register MASK  (Use WDT_WDOGPERIPHID7_Msk instead)  */
#define WDT_WDOGPERIPHID7_Msk               0xFFu                                          /**< (WDT_WDOGPERIPHID7) Register Mask  */

/* -------- WDT_WDOGPERIPHID0 : (WDT Offset: 0xfe0) (R/ 8) Peripheral ID Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PART_NUMBER:8;             /**< bit:   0..7  Part Number Bits 7:0                     */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGPERIPHID0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGPERIPHID0_OFFSET            0xFE0                                         /**<  (WDT_WDOGPERIPHID0) Peripheral ID Register 0  Offset */
#define WDT_WDOGPERIPHID0_RESETVALUE        0x24u                                         /**<  (WDT_WDOGPERIPHID0) Peripheral ID Register 0  Reset Value */

#define WDT_WDOGPERIPHID0_PART_NUMBER_Pos   0                                              /**< (WDT_WDOGPERIPHID0) Part Number Bits 7:0 Position */
#define WDT_WDOGPERIPHID0_PART_NUMBER_Msk   (0xFFu << WDT_WDOGPERIPHID0_PART_NUMBER_Pos)   /**< (WDT_WDOGPERIPHID0) Part Number Bits 7:0 Mask */
#define WDT_WDOGPERIPHID0_PART_NUMBER(value) (WDT_WDOGPERIPHID0_PART_NUMBER_Msk & ((value) << WDT_WDOGPERIPHID0_PART_NUMBER_Pos))
#define WDT_WDOGPERIPHID0_MASK              0xFFu                                          /**< \deprecated (WDT_WDOGPERIPHID0) Register MASK  (Use WDT_WDOGPERIPHID0_Msk instead)  */
#define WDT_WDOGPERIPHID0_Msk               0xFFu                                          /**< (WDT_WDOGPERIPHID0) Register Mask  */

/* -------- WDT_WDOGPERIPHID1 : (WDT Offset: 0xfe4) (R/ 8) Peripheral ID Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PART_NUMBER:4;             /**< bit:   0..3  Part Number Bits 11:8                    */
    uint8_t  JEP106_ID_3_0:4;           /**< bit:   4..7  JEP106 ID Bits 3:0                       */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGPERIPHID1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGPERIPHID1_OFFSET            0xFE4                                         /**<  (WDT_WDOGPERIPHID1) Peripheral ID Register 1  Offset */
#define WDT_WDOGPERIPHID1_RESETVALUE        0xB8u                                         /**<  (WDT_WDOGPERIPHID1) Peripheral ID Register 1  Reset Value */

#define WDT_WDOGPERIPHID1_PART_NUMBER_Pos   0                                              /**< (WDT_WDOGPERIPHID1) Part Number Bits 11:8 Position */
#define WDT_WDOGPERIPHID1_PART_NUMBER_Msk   (0xFu << WDT_WDOGPERIPHID1_PART_NUMBER_Pos)    /**< (WDT_WDOGPERIPHID1) Part Number Bits 11:8 Mask */
#define WDT_WDOGPERIPHID1_PART_NUMBER(value) (WDT_WDOGPERIPHID1_PART_NUMBER_Msk & ((value) << WDT_WDOGPERIPHID1_PART_NUMBER_Pos))
#define WDT_WDOGPERIPHID1_JEP106_ID_3_0_Pos 4                                              /**< (WDT_WDOGPERIPHID1) JEP106 ID Bits 3:0 Position */
#define WDT_WDOGPERIPHID1_JEP106_ID_3_0_Msk (0xFu << WDT_WDOGPERIPHID1_JEP106_ID_3_0_Pos)  /**< (WDT_WDOGPERIPHID1) JEP106 ID Bits 3:0 Mask */
#define WDT_WDOGPERIPHID1_JEP106_ID_3_0(value) (WDT_WDOGPERIPHID1_JEP106_ID_3_0_Msk & ((value) << WDT_WDOGPERIPHID1_JEP106_ID_3_0_Pos))
#define WDT_WDOGPERIPHID1_MASK              0xFFu                                          /**< \deprecated (WDT_WDOGPERIPHID1) Register MASK  (Use WDT_WDOGPERIPHID1_Msk instead)  */
#define WDT_WDOGPERIPHID1_Msk               0xFFu                                          /**< (WDT_WDOGPERIPHID1) Register Mask  */

/* -------- WDT_WDOGPERIPHID2 : (WDT Offset: 0xfe8) (R/ 8) Peripheral ID Register 2 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  JEP106_ID_6_4:3;           /**< bit:   0..2  JEP106 ID Bits 6:4                       */
    uint8_t  JEDEC_USED:1;              /**< bit:      3  JEDEC Used                               */
    uint8_t  REVISION:4;                /**< bit:   4..7  Revision                                 */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGPERIPHID2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGPERIPHID2_OFFSET            0xFE8                                         /**<  (WDT_WDOGPERIPHID2) Peripheral ID Register 2  Offset */
#define WDT_WDOGPERIPHID2_RESETVALUE        0x1Bu                                         /**<  (WDT_WDOGPERIPHID2) Peripheral ID Register 2  Reset Value */

#define WDT_WDOGPERIPHID2_JEP106_ID_6_4_Pos 0                                              /**< (WDT_WDOGPERIPHID2) JEP106 ID Bits 6:4 Position */
#define WDT_WDOGPERIPHID2_JEP106_ID_6_4_Msk (0x7u << WDT_WDOGPERIPHID2_JEP106_ID_6_4_Pos)  /**< (WDT_WDOGPERIPHID2) JEP106 ID Bits 6:4 Mask */
#define WDT_WDOGPERIPHID2_JEP106_ID_6_4(value) (WDT_WDOGPERIPHID2_JEP106_ID_6_4_Msk & ((value) << WDT_WDOGPERIPHID2_JEP106_ID_6_4_Pos))
#define WDT_WDOGPERIPHID2_JEDEC_USED_Pos    3                                              /**< (WDT_WDOGPERIPHID2) JEDEC Used Position */
#define WDT_WDOGPERIPHID2_JEDEC_USED_Msk    (0x1u << WDT_WDOGPERIPHID2_JEDEC_USED_Pos)     /**< (WDT_WDOGPERIPHID2) JEDEC Used Mask */
#define WDT_WDOGPERIPHID2_JEDEC_USED        WDT_WDOGPERIPHID2_JEDEC_USED_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use WDT_WDOGPERIPHID2_JEDEC_USED_Msk instead */
#define WDT_WDOGPERIPHID2_REVISION_Pos      4                                              /**< (WDT_WDOGPERIPHID2) Revision Position */
#define WDT_WDOGPERIPHID2_REVISION_Msk      (0xFu << WDT_WDOGPERIPHID2_REVISION_Pos)       /**< (WDT_WDOGPERIPHID2) Revision Mask */
#define WDT_WDOGPERIPHID2_REVISION(value)   (WDT_WDOGPERIPHID2_REVISION_Msk & ((value) << WDT_WDOGPERIPHID2_REVISION_Pos))
#define WDT_WDOGPERIPHID2_MASK              0xFFu                                          /**< \deprecated (WDT_WDOGPERIPHID2) Register MASK  (Use WDT_WDOGPERIPHID2_Msk instead)  */
#define WDT_WDOGPERIPHID2_Msk               0xFFu                                          /**< (WDT_WDOGPERIPHID2) Register Mask  */

/* -------- WDT_WDOGPERIPHID3 : (WDT Offset: 0xfec) (R/ 8) Peripheral ID Register 3 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CUSTOMER_MOD_NUMBER:4;     /**< bit:   0..3  Customer Modification Number             */
    uint8_t  ECO_REV_NUMBER:4;          /**< bit:   4..7  ECO Revision Number                      */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGPERIPHID3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGPERIPHID3_OFFSET            0xFEC                                         /**<  (WDT_WDOGPERIPHID3) Peripheral ID Register 3  Offset */
#define WDT_WDOGPERIPHID3_RESETVALUE        0x00u                                         /**<  (WDT_WDOGPERIPHID3) Peripheral ID Register 3  Reset Value */

#define WDT_WDOGPERIPHID3_CUSTOMER_MOD_NUMBER_Pos 0                                              /**< (WDT_WDOGPERIPHID3) Customer Modification Number Position */
#define WDT_WDOGPERIPHID3_CUSTOMER_MOD_NUMBER_Msk (0xFu << WDT_WDOGPERIPHID3_CUSTOMER_MOD_NUMBER_Pos)  /**< (WDT_WDOGPERIPHID3) Customer Modification Number Mask */
#define WDT_WDOGPERIPHID3_CUSTOMER_MOD_NUMBER(value) (WDT_WDOGPERIPHID3_CUSTOMER_MOD_NUMBER_Msk & ((value) << WDT_WDOGPERIPHID3_CUSTOMER_MOD_NUMBER_Pos))
#define WDT_WDOGPERIPHID3_ECO_REV_NUMBER_Pos 4                                              /**< (WDT_WDOGPERIPHID3) ECO Revision Number Position */
#define WDT_WDOGPERIPHID3_ECO_REV_NUMBER_Msk (0xFu << WDT_WDOGPERIPHID3_ECO_REV_NUMBER_Pos)  /**< (WDT_WDOGPERIPHID3) ECO Revision Number Mask */
#define WDT_WDOGPERIPHID3_ECO_REV_NUMBER(value) (WDT_WDOGPERIPHID3_ECO_REV_NUMBER_Msk & ((value) << WDT_WDOGPERIPHID3_ECO_REV_NUMBER_Pos))
#define WDT_WDOGPERIPHID3_MASK              0xFFu                                          /**< \deprecated (WDT_WDOGPERIPHID3) Register MASK  (Use WDT_WDOGPERIPHID3_Msk instead)  */
#define WDT_WDOGPERIPHID3_Msk               0xFFu                                          /**< (WDT_WDOGPERIPHID3) Register Mask  */

/* -------- WDT_WDOGPCELLID0 : (WDT Offset: 0xff0) (R/ 8) Component ID Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WDOGPCELLID0:8;            /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGPCELLID0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGPCELLID0_OFFSET             0xFF0                                         /**<  (WDT_WDOGPCELLID0) Component ID Register 0  Offset */
#define WDT_WDOGPCELLID0_RESETVALUE         0x0Du                                         /**<  (WDT_WDOGPCELLID0) Component ID Register 0  Reset Value */

#define WDT_WDOGPCELLID0_WDOGPCELLID0_Pos   0                                              /**< (WDT_WDOGPCELLID0)  Position */
#define WDT_WDOGPCELLID0_WDOGPCELLID0_Msk   (0xFFu << WDT_WDOGPCELLID0_WDOGPCELLID0_Pos)   /**< (WDT_WDOGPCELLID0)  Mask */
#define WDT_WDOGPCELLID0_WDOGPCELLID0(value) (WDT_WDOGPCELLID0_WDOGPCELLID0_Msk & ((value) << WDT_WDOGPCELLID0_WDOGPCELLID0_Pos))
#define WDT_WDOGPCELLID0_MASK               0xFFu                                          /**< \deprecated (WDT_WDOGPCELLID0) Register MASK  (Use WDT_WDOGPCELLID0_Msk instead)  */
#define WDT_WDOGPCELLID0_Msk                0xFFu                                          /**< (WDT_WDOGPCELLID0) Register Mask  */

/* -------- WDT_WDOGPCELLID1 : (WDT Offset: 0xff4) (R/ 8) Component ID Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WDOGPCELLID1:8;            /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGPCELLID1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGPCELLID1_OFFSET             0xFF4                                         /**<  (WDT_WDOGPCELLID1) Component ID Register 1  Offset */
#define WDT_WDOGPCELLID1_RESETVALUE         0xF0u                                         /**<  (WDT_WDOGPCELLID1) Component ID Register 1  Reset Value */

#define WDT_WDOGPCELLID1_WDOGPCELLID1_Pos   0                                              /**< (WDT_WDOGPCELLID1)  Position */
#define WDT_WDOGPCELLID1_WDOGPCELLID1_Msk   (0xFFu << WDT_WDOGPCELLID1_WDOGPCELLID1_Pos)   /**< (WDT_WDOGPCELLID1)  Mask */
#define WDT_WDOGPCELLID1_WDOGPCELLID1(value) (WDT_WDOGPCELLID1_WDOGPCELLID1_Msk & ((value) << WDT_WDOGPCELLID1_WDOGPCELLID1_Pos))
#define WDT_WDOGPCELLID1_MASK               0xFFu                                          /**< \deprecated (WDT_WDOGPCELLID1) Register MASK  (Use WDT_WDOGPCELLID1_Msk instead)  */
#define WDT_WDOGPCELLID1_Msk                0xFFu                                          /**< (WDT_WDOGPCELLID1) Register Mask  */

/* -------- WDT_WDOGPCELLID2 : (WDT Offset: 0xff8) (R/ 8) Component ID Register 2 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WDOGPCELLID2:8;            /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGPCELLID2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGPCELLID2_OFFSET             0xFF8                                         /**<  (WDT_WDOGPCELLID2) Component ID Register 2  Offset */
#define WDT_WDOGPCELLID2_RESETVALUE         0x05u                                         /**<  (WDT_WDOGPCELLID2) Component ID Register 2  Reset Value */

#define WDT_WDOGPCELLID2_WDOGPCELLID2_Pos   0                                              /**< (WDT_WDOGPCELLID2)  Position */
#define WDT_WDOGPCELLID2_WDOGPCELLID2_Msk   (0xFFu << WDT_WDOGPCELLID2_WDOGPCELLID2_Pos)   /**< (WDT_WDOGPCELLID2)  Mask */
#define WDT_WDOGPCELLID2_WDOGPCELLID2(value) (WDT_WDOGPCELLID2_WDOGPCELLID2_Msk & ((value) << WDT_WDOGPCELLID2_WDOGPCELLID2_Pos))
#define WDT_WDOGPCELLID2_MASK               0xFFu                                          /**< \deprecated (WDT_WDOGPCELLID2) Register MASK  (Use WDT_WDOGPCELLID2_Msk instead)  */
#define WDT_WDOGPCELLID2_Msk                0xFFu                                          /**< (WDT_WDOGPCELLID2) Register Mask  */

/* -------- WDT_WDOGPCELLID3 : (WDT Offset: 0xffc) (R/ 8) Component ID Register 3 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  WDOGPCELLID3:8;            /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} WDT_WDOGPCELLID3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define WDT_WDOGPCELLID3_OFFSET             0xFFC                                         /**<  (WDT_WDOGPCELLID3) Component ID Register 3  Offset */
#define WDT_WDOGPCELLID3_RESETVALUE         0xB1u                                         /**<  (WDT_WDOGPCELLID3) Component ID Register 3  Reset Value */

#define WDT_WDOGPCELLID3_WDOGPCELLID3_Pos   0                                              /**< (WDT_WDOGPCELLID3)  Position */
#define WDT_WDOGPCELLID3_WDOGPCELLID3_Msk   (0xFFu << WDT_WDOGPCELLID3_WDOGPCELLID3_Pos)   /**< (WDT_WDOGPCELLID3)  Mask */
#define WDT_WDOGPCELLID3_WDOGPCELLID3(value) (WDT_WDOGPCELLID3_WDOGPCELLID3_Msk & ((value) << WDT_WDOGPCELLID3_WDOGPCELLID3_Pos))
#define WDT_WDOGPCELLID3_MASK               0xFFu                                          /**< \deprecated (WDT_WDOGPCELLID3) Register MASK  (Use WDT_WDOGPCELLID3_Msk instead)  */
#define WDT_WDOGPCELLID3_Msk                0xFFu                                          /**< (WDT_WDOGPCELLID3) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief WDT hardware registers */
typedef struct {  /* Watchdog0 Timer */
  RwReg   WDOGLOAD;       /**< (WDT Offset: 0x00) Watchdog Load Register */
  RoReg   WDOGVALUE;      /**< (WDT Offset: 0x04) Watchdog Value Register */
  RwReg8  WDOGCONTROL;    /**< (WDT Offset: 0x08) Watchdog Control Register */
  __I  uint8_t  Reserved1[3];
  WoReg8  WDOGINTCLR;     /**< (WDT Offset: 0x0C) Watchdog Clear Interrupt Register */
  __I  uint8_t  Reserved2[3];
  RoReg8  WDOGRIS;        /**< (WDT Offset: 0x10) Watchdog Raw Interrupt Status Register */
  __I  uint8_t  Reserved3[3];
  RoReg8  WDOGMIS;        /**< (WDT Offset: 0x14) Watchdog Interrupt Status Register */
  __I  uint8_t  Reserved4[3051];
  RwReg   WDOGLOCK;       /**< (WDT Offset: 0xC00) Watchdog Lock Register (Write 0x1ACCE551 to enable write access to all other registers) */
  __I  uint32_t Reserved5[191];
  RwReg8  WDOGITCR;       /**< (WDT Offset: 0xF00) Watchdog Integration Test Control Register */
  __I  uint8_t  Reserved6[3];
  RwReg8  WDOGITOP;       /**< (WDT Offset: 0xF04) Watchdog Integration Test Output Set Register */
  __I  uint8_t  Reserved7[203];
  RoReg8  WDOGPERIPHID4;  /**< (WDT Offset: 0xFD0) Peripheral ID Register 4 */
  __I  uint8_t  Reserved8[3];
  RoReg8  WDOGPERIPHID5;  /**< (WDT Offset: 0xFD4) Peripheral ID Register 5 */
  __I  uint8_t  Reserved9[3];
  RoReg8  WDOGPERIPHID6;  /**< (WDT Offset: 0xFD8) Peripheral ID Register 6 */
  __I  uint8_t  Reserved10[3];
  RoReg8  WDOGPERIPHID7;  /**< (WDT Offset: 0xFDC) Peripheral ID Register 7 */
  __I  uint8_t  Reserved11[3];
  RoReg8  WDOGPERIPHID0;  /**< (WDT Offset: 0xFE0) Peripheral ID Register 0 */
  __I  uint8_t  Reserved12[3];
  RoReg8  WDOGPERIPHID1;  /**< (WDT Offset: 0xFE4) Peripheral ID Register 1 */
  __I  uint8_t  Reserved13[3];
  RoReg8  WDOGPERIPHID2;  /**< (WDT Offset: 0xFE8) Peripheral ID Register 2 */
  __I  uint8_t  Reserved14[3];
  RoReg8  WDOGPERIPHID3;  /**< (WDT Offset: 0xFEC) Peripheral ID Register 3 */
  __I  uint8_t  Reserved15[3];
  RoReg8  WDOGPCELLID0;   /**< (WDT Offset: 0xFF0) Component ID Register 0 */
  __I  uint8_t  Reserved16[3];
  RoReg8  WDOGPCELLID1;   /**< (WDT Offset: 0xFF4) Component ID Register 1 */
  __I  uint8_t  Reserved17[3];
  RoReg8  WDOGPCELLID2;   /**< (WDT Offset: 0xFF8) Component ID Register 2 */
  __I  uint8_t  Reserved18[3];
  RoReg8  WDOGPCELLID3;   /**< (WDT Offset: 0xFFC) Component ID Register 3 */
} Wdt;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief WDT hardware registers */
typedef struct {  /* Watchdog0 Timer */
  __IO WDT_WDOGLOAD_Type              WDOGLOAD;       /**< Offset: 0x00 (R/W  32) Watchdog Load Register */
  __I  WDT_WDOGVALUE_Type             WDOGVALUE;      /**< Offset: 0x04 (R/   32) Watchdog Value Register */
  __IO WDT_WDOGCONTROL_Type           WDOGCONTROL;    /**< Offset: 0x08 (R/W   8) Watchdog Control Register */
       RoReg8                         Reserved1[0x3];
  __O  WDT_WDOGINTCLR_Type            WDOGINTCLR;     /**< Offset: 0x0C ( /W   8) Watchdog Clear Interrupt Register */
       RoReg8                         Reserved2[0x3];
  __I  WDT_WDOGRIS_Type               WDOGRIS;        /**< Offset: 0x10 (R/    8) Watchdog Raw Interrupt Status Register */
       RoReg8                         Reserved3[0x3];
  __I  WDT_WDOGMIS_Type               WDOGMIS;        /**< Offset: 0x14 (R/    8) Watchdog Interrupt Status Register */
       RoReg8                         Reserved4[0xBEB];
  __IO WDT_WDOGLOCK_Type              WDOGLOCK;       /**< Offset: 0xC00 (R/W  32) Watchdog Lock Register (Write 0x1ACCE551 to enable write access to all other registers) */
       RoReg8                         Reserved5[0x2FC];
  __IO WDT_WDOGITCR_Type              WDOGITCR;       /**< Offset: 0xF00 (R/W   8) Watchdog Integration Test Control Register */
       RoReg8                         Reserved6[0x3];
  __IO WDT_WDOGITOP_Type              WDOGITOP;       /**< Offset: 0xF04 (R/W   8) Watchdog Integration Test Output Set Register */
       RoReg8                         Reserved7[0xCB];
  __I  WDT_WDOGPERIPHID4_Type         WDOGPERIPHID4;  /**< Offset: 0xFD0 (R/    8) Peripheral ID Register 4 */
       RoReg8                         Reserved8[0x3];
  __I  WDT_WDOGPERIPHID5_Type         WDOGPERIPHID5;  /**< Offset: 0xFD4 (R/    8) Peripheral ID Register 5 */
       RoReg8                         Reserved9[0x3];
  __I  WDT_WDOGPERIPHID6_Type         WDOGPERIPHID6;  /**< Offset: 0xFD8 (R/    8) Peripheral ID Register 6 */
       RoReg8                         Reserved10[0x3];
  __I  WDT_WDOGPERIPHID7_Type         WDOGPERIPHID7;  /**< Offset: 0xFDC (R/    8) Peripheral ID Register 7 */
       RoReg8                         Reserved11[0x3];
  __I  WDT_WDOGPERIPHID0_Type         WDOGPERIPHID0;  /**< Offset: 0xFE0 (R/    8) Peripheral ID Register 0 */
       RoReg8                         Reserved12[0x3];
  __I  WDT_WDOGPERIPHID1_Type         WDOGPERIPHID1;  /**< Offset: 0xFE4 (R/    8) Peripheral ID Register 1 */
       RoReg8                         Reserved13[0x3];
  __I  WDT_WDOGPERIPHID2_Type         WDOGPERIPHID2;  /**< Offset: 0xFE8 (R/    8) Peripheral ID Register 2 */
       RoReg8                         Reserved14[0x3];
  __I  WDT_WDOGPERIPHID3_Type         WDOGPERIPHID3;  /**< Offset: 0xFEC (R/    8) Peripheral ID Register 3 */
       RoReg8                         Reserved15[0x3];
  __I  WDT_WDOGPCELLID0_Type          WDOGPCELLID0;   /**< Offset: 0xFF0 (R/    8) Component ID Register 0 */
       RoReg8                         Reserved16[0x3];
  __I  WDT_WDOGPCELLID1_Type          WDOGPCELLID1;   /**< Offset: 0xFF4 (R/    8) Component ID Register 1 */
       RoReg8                         Reserved17[0x3];
  __I  WDT_WDOGPCELLID2_Type          WDOGPCELLID2;   /**< Offset: 0xFF8 (R/    8) Component ID Register 2 */
       RoReg8                         Reserved18[0x3];
  __I  WDT_WDOGPCELLID3_Type          WDOGPCELLID3;   /**< Offset: 0xFFC (R/    8) Component ID Register 3 */
} Wdt;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_WDT_COMPONENT_ */
