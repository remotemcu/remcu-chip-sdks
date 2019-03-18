/**
 * \file
 *
 * \brief Component description for GPIO
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

#ifndef _SAMB11_GPIO_COMPONENT_
#define _SAMB11_GPIO_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR GPIO */
/* ========================================================================== */
/** \addtogroup SAMB11_GPIO GPIO Controller 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define GPIO_G1234
#define REV_GPIO                         0x100

/* -------- GPIO_DATA : (GPIO Offset: 0x00) (R/W 16) Data Value -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t VALUE:16;                  /**< bit:  0..15  Read = Sampled at Pin : Write = To Output Data Register */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} GPIO_DATA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_DATA_OFFSET                    0x00                                          /**<  (GPIO_DATA) Data Value  Offset */
#define GPIO_DATA_RESETVALUE                0x00u                                         /**<  (GPIO_DATA) Data Value  Reset Value */

#define GPIO_DATA_VALUE_Pos                 0                                              /**< (GPIO_DATA) Read = Sampled at Pin : Write = To Output Data Register Position */
#define GPIO_DATA_VALUE_Msk                 (0xFFFFu << GPIO_DATA_VALUE_Pos)               /**< (GPIO_DATA) Read = Sampled at Pin : Write = To Output Data Register Mask */
#define GPIO_DATA_VALUE(value)              (GPIO_DATA_VALUE_Msk & ((value) << GPIO_DATA_VALUE_Pos))
#define GPIO_DATA_MASK                      0xFFFFu                                        /**< \deprecated (GPIO_DATA) Register MASK  (Use GPIO_DATA_Msk instead)  */
#define GPIO_DATA_Msk                       0xFFFFu                                        /**< (GPIO_DATA) Register Mask  */

/* -------- GPIO_DATAOUT : (GPIO Offset: 0x04) (R/W 16) Data Output Register Value -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t VALUE:16;                  /**< bit:  0..15  Read = Current Value of Data Output Register : Write = To Output Data Register */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} GPIO_DATAOUT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_DATAOUT_OFFSET                 0x04                                          /**<  (GPIO_DATAOUT) Data Output Register Value  Offset */
#define GPIO_DATAOUT_RESETVALUE             0x00u                                         /**<  (GPIO_DATAOUT) Data Output Register Value  Reset Value */

#define GPIO_DATAOUT_VALUE_Pos              0                                              /**< (GPIO_DATAOUT) Read = Current Value of Data Output Register : Write = To Output Data Register Position */
#define GPIO_DATAOUT_VALUE_Msk              (0xFFFFu << GPIO_DATAOUT_VALUE_Pos)            /**< (GPIO_DATAOUT) Read = Current Value of Data Output Register : Write = To Output Data Register Mask */
#define GPIO_DATAOUT_VALUE(value)           (GPIO_DATAOUT_VALUE_Msk & ((value) << GPIO_DATAOUT_VALUE_Pos))
#define GPIO_DATAOUT_MASK                   0xFFFFu                                        /**< \deprecated (GPIO_DATAOUT) Register MASK  (Use GPIO_DATAOUT_Msk instead)  */
#define GPIO_DATAOUT_Msk                    0xFFFFu                                        /**< (GPIO_DATAOUT) Register Mask  */

/* -------- GPIO_OUTENSET : (GPIO Offset: 0x10) (R/W 16) Output Enable Set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t VALUE:16;                  /**< bit:  0..15  Write 1 to set the output enable bit     */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} GPIO_OUTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_OUTENSET_OFFSET                0x10                                          /**<  (GPIO_OUTENSET) Output Enable Set  Offset */
#define GPIO_OUTENSET_RESETVALUE            0x00u                                         /**<  (GPIO_OUTENSET) Output Enable Set  Reset Value */

#define GPIO_OUTENSET_VALUE_Pos             0                                              /**< (GPIO_OUTENSET) Write 1 to set the output enable bit Position */
#define GPIO_OUTENSET_VALUE_Msk             (0xFFFFu << GPIO_OUTENSET_VALUE_Pos)           /**< (GPIO_OUTENSET) Write 1 to set the output enable bit Mask */
#define GPIO_OUTENSET_VALUE(value)          (GPIO_OUTENSET_VALUE_Msk & ((value) << GPIO_OUTENSET_VALUE_Pos))
#define GPIO_OUTENSET_MASK                  0xFFFFu                                        /**< \deprecated (GPIO_OUTENSET) Register MASK  (Use GPIO_OUTENSET_Msk instead)  */
#define GPIO_OUTENSET_Msk                   0xFFFFu                                        /**< (GPIO_OUTENSET) Register Mask  */

/* -------- GPIO_OUTENCLR : (GPIO Offset: 0x14) (R/W 16) Output Enable Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t VALUE:16;                  /**< bit:  0..15  Write 1 to clear the output enable bit   */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} GPIO_OUTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_OUTENCLR_OFFSET                0x14                                          /**<  (GPIO_OUTENCLR) Output Enable Clear  Offset */
#define GPIO_OUTENCLR_RESETVALUE            0x00u                                         /**<  (GPIO_OUTENCLR) Output Enable Clear  Reset Value */

#define GPIO_OUTENCLR_VALUE_Pos             0                                              /**< (GPIO_OUTENCLR) Write 1 to clear the output enable bit Position */
#define GPIO_OUTENCLR_VALUE_Msk             (0xFFFFu << GPIO_OUTENCLR_VALUE_Pos)           /**< (GPIO_OUTENCLR) Write 1 to clear the output enable bit Mask */
#define GPIO_OUTENCLR_VALUE(value)          (GPIO_OUTENCLR_VALUE_Msk & ((value) << GPIO_OUTENCLR_VALUE_Pos))
#define GPIO_OUTENCLR_MASK                  0xFFFFu                                        /**< \deprecated (GPIO_OUTENCLR) Register MASK  (Use GPIO_OUTENCLR_Msk instead)  */
#define GPIO_OUTENCLR_Msk                   0xFFFFu                                        /**< (GPIO_OUTENCLR) Register Mask  */

/* -------- GPIO_INTENSET : (GPIO Offset: 0x20) (R/W 16) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t VALUE:16;                  /**< bit:  0..15  Write 1 to set the enable bit            */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} GPIO_INTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_INTENSET_OFFSET                0x20                                          /**<  (GPIO_INTENSET) Interrupt Enable Set  Offset */
#define GPIO_INTENSET_RESETVALUE            0x00u                                         /**<  (GPIO_INTENSET) Interrupt Enable Set  Reset Value */

#define GPIO_INTENSET_VALUE_Pos             0                                              /**< (GPIO_INTENSET) Write 1 to set the enable bit Position */
#define GPIO_INTENSET_VALUE_Msk             (0xFFFFu << GPIO_INTENSET_VALUE_Pos)           /**< (GPIO_INTENSET) Write 1 to set the enable bit Mask */
#define GPIO_INTENSET_VALUE(value)          (GPIO_INTENSET_VALUE_Msk & ((value) << GPIO_INTENSET_VALUE_Pos))
#define GPIO_INTENSET_MASK                  0xFFFFu                                        /**< \deprecated (GPIO_INTENSET) Register MASK  (Use GPIO_INTENSET_Msk instead)  */
#define GPIO_INTENSET_Msk                   0xFFFFu                                        /**< (GPIO_INTENSET) Register Mask  */

/* -------- GPIO_INTENCLR : (GPIO Offset: 0x24) (R/W 16) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t VALUE:16;                  /**< bit:  0..15  Write 1 to clear the enable bit          */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} GPIO_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_INTENCLR_OFFSET                0x24                                          /**<  (GPIO_INTENCLR) Interrupt Enable Clear  Offset */
#define GPIO_INTENCLR_RESETVALUE            0x00u                                         /**<  (GPIO_INTENCLR) Interrupt Enable Clear  Reset Value */

#define GPIO_INTENCLR_VALUE_Pos             0                                              /**< (GPIO_INTENCLR) Write 1 to clear the enable bit Position */
#define GPIO_INTENCLR_VALUE_Msk             (0xFFFFu << GPIO_INTENCLR_VALUE_Pos)           /**< (GPIO_INTENCLR) Write 1 to clear the enable bit Mask */
#define GPIO_INTENCLR_VALUE(value)          (GPIO_INTENCLR_VALUE_Msk & ((value) << GPIO_INTENCLR_VALUE_Pos))
#define GPIO_INTENCLR_MASK                  0xFFFFu                                        /**< \deprecated (GPIO_INTENCLR) Register MASK  (Use GPIO_INTENCLR_Msk instead)  */
#define GPIO_INTENCLR_Msk                   0xFFFFu                                        /**< (GPIO_INTENCLR) Register Mask  */

/* -------- GPIO_INTTYPESET : (GPIO Offset: 0x28) (R/W 16) Interrupt Type Set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t VALUE:16;                  /**< bit:  0..15  Write 1 for edge                         */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} GPIO_INTTYPESET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_INTTYPESET_OFFSET              0x28                                          /**<  (GPIO_INTTYPESET) Interrupt Type Set  Offset */
#define GPIO_INTTYPESET_RESETVALUE          0x00u                                         /**<  (GPIO_INTTYPESET) Interrupt Type Set  Reset Value */

#define GPIO_INTTYPESET_VALUE_Pos           0                                              /**< (GPIO_INTTYPESET) Write 1 for edge Position */
#define GPIO_INTTYPESET_VALUE_Msk           (0xFFFFu << GPIO_INTTYPESET_VALUE_Pos)         /**< (GPIO_INTTYPESET) Write 1 for edge Mask */
#define GPIO_INTTYPESET_VALUE(value)        (GPIO_INTTYPESET_VALUE_Msk & ((value) << GPIO_INTTYPESET_VALUE_Pos))
#define GPIO_INTTYPESET_MASK                0xFFFFu                                        /**< \deprecated (GPIO_INTTYPESET) Register MASK  (Use GPIO_INTTYPESET_Msk instead)  */
#define GPIO_INTTYPESET_Msk                 0xFFFFu                                        /**< (GPIO_INTTYPESET) Register Mask  */

/* -------- GPIO_INTTYPECLR : (GPIO Offset: 0x2c) (R/W 16) Interrupt Type Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t VALUE:16;                  /**< bit:  0..15  Write 1 to clear the interrupt type      */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} GPIO_INTTYPECLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_INTTYPECLR_OFFSET              0x2C                                          /**<  (GPIO_INTTYPECLR) Interrupt Type Clear  Offset */
#define GPIO_INTTYPECLR_RESETVALUE          0x00u                                         /**<  (GPIO_INTTYPECLR) Interrupt Type Clear  Reset Value */

#define GPIO_INTTYPECLR_VALUE_Pos           0                                              /**< (GPIO_INTTYPECLR) Write 1 to clear the interrupt type Position */
#define GPIO_INTTYPECLR_VALUE_Msk           (0xFFFFu << GPIO_INTTYPECLR_VALUE_Pos)         /**< (GPIO_INTTYPECLR) Write 1 to clear the interrupt type Mask */
#define GPIO_INTTYPECLR_VALUE(value)        (GPIO_INTTYPECLR_VALUE_Msk & ((value) << GPIO_INTTYPECLR_VALUE_Pos))
#define GPIO_INTTYPECLR_MASK                0xFFFFu                                        /**< \deprecated (GPIO_INTTYPECLR) Register MASK  (Use GPIO_INTTYPECLR_Msk instead)  */
#define GPIO_INTTYPECLR_Msk                 0xFFFFu                                        /**< (GPIO_INTTYPECLR) Register Mask  */

/* -------- GPIO_INTPOLSET : (GPIO Offset: 0x30) (R/W 16) Polarity-level, edge IRQ Configuration -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t VALUE:16;                  /**< bit:  0..15  Write 1 for HIGH level or rising edge    */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} GPIO_INTPOLSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_INTPOLSET_OFFSET               0x30                                          /**<  (GPIO_INTPOLSET) Polarity-level, edge IRQ Configuration  Offset */
#define GPIO_INTPOLSET_RESETVALUE           0x00u                                         /**<  (GPIO_INTPOLSET) Polarity-level, edge IRQ Configuration  Reset Value */

#define GPIO_INTPOLSET_VALUE_Pos            0                                              /**< (GPIO_INTPOLSET) Write 1 for HIGH level or rising edge Position */
#define GPIO_INTPOLSET_VALUE_Msk            (0xFFFFu << GPIO_INTPOLSET_VALUE_Pos)          /**< (GPIO_INTPOLSET) Write 1 for HIGH level or rising edge Mask */
#define GPIO_INTPOLSET_VALUE(value)         (GPIO_INTPOLSET_VALUE_Msk & ((value) << GPIO_INTPOLSET_VALUE_Pos))
#define GPIO_INTPOLSET_MASK                 0xFFFFu                                        /**< \deprecated (GPIO_INTPOLSET) Register MASK  (Use GPIO_INTPOLSET_Msk instead)  */
#define GPIO_INTPOLSET_Msk                  0xFFFFu                                        /**< (GPIO_INTPOLSET) Register Mask  */

/* -------- GPIO_INTPOLCLR : (GPIO Offset: 0x34) (R/W 16) IRQ Configuration Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t VALUE:16;                  /**< bit:  0..15  Write 1 to Clear Interrupt Polarity Bit  */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} GPIO_INTPOLCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_INTPOLCLR_OFFSET               0x34                                          /**<  (GPIO_INTPOLCLR) IRQ Configuration Clear  Offset */
#define GPIO_INTPOLCLR_RESETVALUE           0x00u                                         /**<  (GPIO_INTPOLCLR) IRQ Configuration Clear  Reset Value */

#define GPIO_INTPOLCLR_VALUE_Pos            0                                              /**< (GPIO_INTPOLCLR) Write 1 to Clear Interrupt Polarity Bit Position */
#define GPIO_INTPOLCLR_VALUE_Msk            (0xFFFFu << GPIO_INTPOLCLR_VALUE_Pos)          /**< (GPIO_INTPOLCLR) Write 1 to Clear Interrupt Polarity Bit Mask */
#define GPIO_INTPOLCLR_VALUE(value)         (GPIO_INTPOLCLR_VALUE_Msk & ((value) << GPIO_INTPOLCLR_VALUE_Pos))
#define GPIO_INTPOLCLR_MASK                 0xFFFFu                                        /**< \deprecated (GPIO_INTPOLCLR) Register MASK  (Use GPIO_INTPOLCLR_Msk instead)  */
#define GPIO_INTPOLCLR_Msk                  0xFFFFu                                        /**< (GPIO_INTPOLCLR) Register Mask  */

/* -------- GPIO_INTSTATUSCLEAR : (GPIO Offset: 0x38) (R/W 16) Interrupt Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t VALUE:16;                  /**< bit:  0..15  Write 1 to Clear Interrupt               */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} GPIO_INTSTATUSCLEAR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_INTSTATUSCLEAR_OFFSET          0x38                                          /**<  (GPIO_INTSTATUSCLEAR) Interrupt Status  Offset */
#define GPIO_INTSTATUSCLEAR_RESETVALUE      0x00u                                         /**<  (GPIO_INTSTATUSCLEAR) Interrupt Status  Reset Value */

#define GPIO_INTSTATUSCLEAR_VALUE_Pos       0                                              /**< (GPIO_INTSTATUSCLEAR) Write 1 to Clear Interrupt Position */
#define GPIO_INTSTATUSCLEAR_VALUE_Msk       (0xFFFFu << GPIO_INTSTATUSCLEAR_VALUE_Pos)     /**< (GPIO_INTSTATUSCLEAR) Write 1 to Clear Interrupt Mask */
#define GPIO_INTSTATUSCLEAR_VALUE(value)    (GPIO_INTSTATUSCLEAR_VALUE_Msk & ((value) << GPIO_INTSTATUSCLEAR_VALUE_Pos))
#define GPIO_INTSTATUSCLEAR_MASK            0xFFFFu                                        /**< \deprecated (GPIO_INTSTATUSCLEAR) Register MASK  (Use GPIO_INTSTATUSCLEAR_Msk instead)  */
#define GPIO_INTSTATUSCLEAR_Msk             0xFFFFu                                        /**< (GPIO_INTSTATUSCLEAR) Register Mask  */

/* -------- GPIO_PID4 : (GPIO Offset: 0xfd0) (R/ 8) Peripheral ID Register 4 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  JEP106_C_CODE:4;           /**< bit:   0..3  JEP106 C Code                            */
    uint8_t  BLOCK_COUNT:4;             /**< bit:   4..7  Block Count                              */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} GPIO_PID4_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_PID4_OFFSET                    0xFD0                                         /**<  (GPIO_PID4) Peripheral ID Register 4  Offset */
#define GPIO_PID4_RESETVALUE                0x04u                                         /**<  (GPIO_PID4) Peripheral ID Register 4  Reset Value */

#define GPIO_PID4_JEP106_C_CODE_Pos         0                                              /**< (GPIO_PID4) JEP106 C Code Position */
#define GPIO_PID4_JEP106_C_CODE_Msk         (0xFu << GPIO_PID4_JEP106_C_CODE_Pos)          /**< (GPIO_PID4) JEP106 C Code Mask */
#define GPIO_PID4_JEP106_C_CODE(value)      (GPIO_PID4_JEP106_C_CODE_Msk & ((value) << GPIO_PID4_JEP106_C_CODE_Pos))
#define GPIO_PID4_BLOCK_COUNT_Pos           4                                              /**< (GPIO_PID4) Block Count Position */
#define GPIO_PID4_BLOCK_COUNT_Msk           (0xFu << GPIO_PID4_BLOCK_COUNT_Pos)            /**< (GPIO_PID4) Block Count Mask */
#define GPIO_PID4_BLOCK_COUNT(value)        (GPIO_PID4_BLOCK_COUNT_Msk & ((value) << GPIO_PID4_BLOCK_COUNT_Pos))
#define GPIO_PID4_MASK                      0xFFu                                          /**< \deprecated (GPIO_PID4) Register MASK  (Use GPIO_PID4_Msk instead)  */
#define GPIO_PID4_Msk                       0xFFu                                          /**< (GPIO_PID4) Register Mask  */

/* -------- GPIO_PID5 : (GPIO Offset: 0xfd4) (R/ 8) Peripheral ID Register 5 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PID5:8;                    /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} GPIO_PID5_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_PID5_OFFSET                    0xFD4                                         /**<  (GPIO_PID5) Peripheral ID Register 5  Offset */
#define GPIO_PID5_RESETVALUE                0x00u                                         /**<  (GPIO_PID5) Peripheral ID Register 5  Reset Value */

#define GPIO_PID5_PID5_Pos                  0                                              /**< (GPIO_PID5)  Position */
#define GPIO_PID5_PID5_Msk                  (0xFFu << GPIO_PID5_PID5_Pos)                  /**< (GPIO_PID5)  Mask */
#define GPIO_PID5_PID5(value)               (GPIO_PID5_PID5_Msk & ((value) << GPIO_PID5_PID5_Pos))
#define GPIO_PID5_MASK                      0xFFu                                          /**< \deprecated (GPIO_PID5) Register MASK  (Use GPIO_PID5_Msk instead)  */
#define GPIO_PID5_Msk                       0xFFu                                          /**< (GPIO_PID5) Register Mask  */

/* -------- GPIO_PID6 : (GPIO Offset: 0xfd8) (R/ 8) Peripheral ID Register 6 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PID6:8;                    /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} GPIO_PID6_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_PID6_OFFSET                    0xFD8                                         /**<  (GPIO_PID6) Peripheral ID Register 6  Offset */
#define GPIO_PID6_RESETVALUE                0x00u                                         /**<  (GPIO_PID6) Peripheral ID Register 6  Reset Value */

#define GPIO_PID6_PID6_Pos                  0                                              /**< (GPIO_PID6)  Position */
#define GPIO_PID6_PID6_Msk                  (0xFFu << GPIO_PID6_PID6_Pos)                  /**< (GPIO_PID6)  Mask */
#define GPIO_PID6_PID6(value)               (GPIO_PID6_PID6_Msk & ((value) << GPIO_PID6_PID6_Pos))
#define GPIO_PID6_MASK                      0xFFu                                          /**< \deprecated (GPIO_PID6) Register MASK  (Use GPIO_PID6_Msk instead)  */
#define GPIO_PID6_Msk                       0xFFu                                          /**< (GPIO_PID6) Register Mask  */

/* -------- GPIO_PID7 : (GPIO Offset: 0xfdc) (R/ 8) Peripheral ID Register 7 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PID7:8;                    /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} GPIO_PID7_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_PID7_OFFSET                    0xFDC                                         /**<  (GPIO_PID7) Peripheral ID Register 7  Offset */
#define GPIO_PID7_RESETVALUE                0x00u                                         /**<  (GPIO_PID7) Peripheral ID Register 7  Reset Value */

#define GPIO_PID7_PID7_Pos                  0                                              /**< (GPIO_PID7)  Position */
#define GPIO_PID7_PID7_Msk                  (0xFFu << GPIO_PID7_PID7_Pos)                  /**< (GPIO_PID7)  Mask */
#define GPIO_PID7_PID7(value)               (GPIO_PID7_PID7_Msk & ((value) << GPIO_PID7_PID7_Pos))
#define GPIO_PID7_MASK                      0xFFu                                          /**< \deprecated (GPIO_PID7) Register MASK  (Use GPIO_PID7_Msk instead)  */
#define GPIO_PID7_Msk                       0xFFu                                          /**< (GPIO_PID7) Register Mask  */

/* -------- GPIO_PID0 : (GPIO Offset: 0xfe0) (R/ 8) Peripheral ID Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PART_NUMBER:8;             /**< bit:   0..7  Part Number Bits 7:0                     */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} GPIO_PID0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_PID0_OFFSET                    0xFE0                                         /**<  (GPIO_PID0) Peripheral ID Register 0  Offset */
#define GPIO_PID0_RESETVALUE                0x20u                                         /**<  (GPIO_PID0) Peripheral ID Register 0  Reset Value */

#define GPIO_PID0_PART_NUMBER_Pos           0                                              /**< (GPIO_PID0) Part Number Bits 7:0 Position */
#define GPIO_PID0_PART_NUMBER_Msk           (0xFFu << GPIO_PID0_PART_NUMBER_Pos)           /**< (GPIO_PID0) Part Number Bits 7:0 Mask */
#define GPIO_PID0_PART_NUMBER(value)        (GPIO_PID0_PART_NUMBER_Msk & ((value) << GPIO_PID0_PART_NUMBER_Pos))
#define GPIO_PID0_MASK                      0xFFu                                          /**< \deprecated (GPIO_PID0) Register MASK  (Use GPIO_PID0_Msk instead)  */
#define GPIO_PID0_Msk                       0xFFu                                          /**< (GPIO_PID0) Register Mask  */

/* -------- GPIO_PID1 : (GPIO Offset: 0xfe4) (R/ 8) Peripheral ID Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PART_NUMBER:4;             /**< bit:   0..3  Part Number Bits 11:8                    */
    uint8_t  JEP106_ID_3_0:4;           /**< bit:   4..7  JEP106 ID Bits 3:0                       */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} GPIO_PID1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_PID1_OFFSET                    0xFE4                                         /**<  (GPIO_PID1) Peripheral ID Register 1  Offset */
#define GPIO_PID1_RESETVALUE                0xB8u                                         /**<  (GPIO_PID1) Peripheral ID Register 1  Reset Value */

#define GPIO_PID1_PART_NUMBER_Pos           0                                              /**< (GPIO_PID1) Part Number Bits 11:8 Position */
#define GPIO_PID1_PART_NUMBER_Msk           (0xFu << GPIO_PID1_PART_NUMBER_Pos)            /**< (GPIO_PID1) Part Number Bits 11:8 Mask */
#define GPIO_PID1_PART_NUMBER(value)        (GPIO_PID1_PART_NUMBER_Msk & ((value) << GPIO_PID1_PART_NUMBER_Pos))
#define GPIO_PID1_JEP106_ID_3_0_Pos         4                                              /**< (GPIO_PID1) JEP106 ID Bits 3:0 Position */
#define GPIO_PID1_JEP106_ID_3_0_Msk         (0xFu << GPIO_PID1_JEP106_ID_3_0_Pos)          /**< (GPIO_PID1) JEP106 ID Bits 3:0 Mask */
#define GPIO_PID1_JEP106_ID_3_0(value)      (GPIO_PID1_JEP106_ID_3_0_Msk & ((value) << GPIO_PID1_JEP106_ID_3_0_Pos))
#define GPIO_PID1_MASK                      0xFFu                                          /**< \deprecated (GPIO_PID1) Register MASK  (Use GPIO_PID1_Msk instead)  */
#define GPIO_PID1_Msk                       0xFFu                                          /**< (GPIO_PID1) Register Mask  */

/* -------- GPIO_PID2 : (GPIO Offset: 0xfe8) (R/ 8) Peripheral ID Register 2 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  JEP106_ID_6_4:3;           /**< bit:   0..2  JEP106 ID Bits 6:4                       */
    uint8_t  JEDEC_USED:1;              /**< bit:      3  JEDEC Used                               */
    uint8_t  REVISION:4;                /**< bit:   4..7  Revision                                 */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} GPIO_PID2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_PID2_OFFSET                    0xFE8                                         /**<  (GPIO_PID2) Peripheral ID Register 2  Offset */
#define GPIO_PID2_RESETVALUE                0x1Bu                                         /**<  (GPIO_PID2) Peripheral ID Register 2  Reset Value */

#define GPIO_PID2_JEP106_ID_6_4_Pos         0                                              /**< (GPIO_PID2) JEP106 ID Bits 6:4 Position */
#define GPIO_PID2_JEP106_ID_6_4_Msk         (0x7u << GPIO_PID2_JEP106_ID_6_4_Pos)          /**< (GPIO_PID2) JEP106 ID Bits 6:4 Mask */
#define GPIO_PID2_JEP106_ID_6_4(value)      (GPIO_PID2_JEP106_ID_6_4_Msk & ((value) << GPIO_PID2_JEP106_ID_6_4_Pos))
#define GPIO_PID2_JEDEC_USED_Pos            3                                              /**< (GPIO_PID2) JEDEC Used Position */
#define GPIO_PID2_JEDEC_USED_Msk            (0x1u << GPIO_PID2_JEDEC_USED_Pos)             /**< (GPIO_PID2) JEDEC Used Mask */
#define GPIO_PID2_JEDEC_USED                GPIO_PID2_JEDEC_USED_Msk                       /**< \deprecated Old style mask definition for 1 bit bitfield. Use GPIO_PID2_JEDEC_USED_Msk instead */
#define GPIO_PID2_REVISION_Pos              4                                              /**< (GPIO_PID2) Revision Position */
#define GPIO_PID2_REVISION_Msk              (0xFu << GPIO_PID2_REVISION_Pos)               /**< (GPIO_PID2) Revision Mask */
#define GPIO_PID2_REVISION(value)           (GPIO_PID2_REVISION_Msk & ((value) << GPIO_PID2_REVISION_Pos))
#define GPIO_PID2_MASK                      0xFFu                                          /**< \deprecated (GPIO_PID2) Register MASK  (Use GPIO_PID2_Msk instead)  */
#define GPIO_PID2_Msk                       0xFFu                                          /**< (GPIO_PID2) Register Mask  */

/* -------- GPIO_PID3 : (GPIO Offset: 0xfec) (R/ 8) Peripheral ID Register 3 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CUSTOMER_MOD_NUMBER:4;     /**< bit:   0..3  Customer Modification Number             */
    uint8_t  ECO_REV_NUMBER:4;          /**< bit:   4..7  ECO Revision Number                      */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} GPIO_PID3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_PID3_OFFSET                    0xFEC                                         /**<  (GPIO_PID3) Peripheral ID Register 3  Offset */
#define GPIO_PID3_RESETVALUE                0x00u                                         /**<  (GPIO_PID3) Peripheral ID Register 3  Reset Value */

#define GPIO_PID3_CUSTOMER_MOD_NUMBER_Pos   0                                              /**< (GPIO_PID3) Customer Modification Number Position */
#define GPIO_PID3_CUSTOMER_MOD_NUMBER_Msk   (0xFu << GPIO_PID3_CUSTOMER_MOD_NUMBER_Pos)    /**< (GPIO_PID3) Customer Modification Number Mask */
#define GPIO_PID3_CUSTOMER_MOD_NUMBER(value) (GPIO_PID3_CUSTOMER_MOD_NUMBER_Msk & ((value) << GPIO_PID3_CUSTOMER_MOD_NUMBER_Pos))
#define GPIO_PID3_ECO_REV_NUMBER_Pos        4                                              /**< (GPIO_PID3) ECO Revision Number Position */
#define GPIO_PID3_ECO_REV_NUMBER_Msk        (0xFu << GPIO_PID3_ECO_REV_NUMBER_Pos)         /**< (GPIO_PID3) ECO Revision Number Mask */
#define GPIO_PID3_ECO_REV_NUMBER(value)     (GPIO_PID3_ECO_REV_NUMBER_Msk & ((value) << GPIO_PID3_ECO_REV_NUMBER_Pos))
#define GPIO_PID3_MASK                      0xFFu                                          /**< \deprecated (GPIO_PID3) Register MASK  (Use GPIO_PID3_Msk instead)  */
#define GPIO_PID3_Msk                       0xFFu                                          /**< (GPIO_PID3) Register Mask  */

/* -------- GPIO_CID0 : (GPIO Offset: 0xff0) (R/ 8) Component ID Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CID0:8;                    /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} GPIO_CID0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_CID0_OFFSET                    0xFF0                                         /**<  (GPIO_CID0) Component ID Register 0  Offset */
#define GPIO_CID0_RESETVALUE                0x0Du                                         /**<  (GPIO_CID0) Component ID Register 0  Reset Value */

#define GPIO_CID0_CID0_Pos                  0                                              /**< (GPIO_CID0)  Position */
#define GPIO_CID0_CID0_Msk                  (0xFFu << GPIO_CID0_CID0_Pos)                  /**< (GPIO_CID0)  Mask */
#define GPIO_CID0_CID0(value)               (GPIO_CID0_CID0_Msk & ((value) << GPIO_CID0_CID0_Pos))
#define GPIO_CID0_MASK                      0xFFu                                          /**< \deprecated (GPIO_CID0) Register MASK  (Use GPIO_CID0_Msk instead)  */
#define GPIO_CID0_Msk                       0xFFu                                          /**< (GPIO_CID0) Register Mask  */

/* -------- GPIO_CID1 : (GPIO Offset: 0xff4) (R/ 8) Component ID Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CID1:8;                    /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} GPIO_CID1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_CID1_OFFSET                    0xFF4                                         /**<  (GPIO_CID1) Component ID Register 1  Offset */
#define GPIO_CID1_RESETVALUE                0xF0u                                         /**<  (GPIO_CID1) Component ID Register 1  Reset Value */

#define GPIO_CID1_CID1_Pos                  0                                              /**< (GPIO_CID1)  Position */
#define GPIO_CID1_CID1_Msk                  (0xFFu << GPIO_CID1_CID1_Pos)                  /**< (GPIO_CID1)  Mask */
#define GPIO_CID1_CID1(value)               (GPIO_CID1_CID1_Msk & ((value) << GPIO_CID1_CID1_Pos))
#define GPIO_CID1_MASK                      0xFFu                                          /**< \deprecated (GPIO_CID1) Register MASK  (Use GPIO_CID1_Msk instead)  */
#define GPIO_CID1_Msk                       0xFFu                                          /**< (GPIO_CID1) Register Mask  */

/* -------- GPIO_CID2 : (GPIO Offset: 0xff8) (R/ 8) Component ID Register 2 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CID2:8;                    /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} GPIO_CID2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_CID2_OFFSET                    0xFF8                                         /**<  (GPIO_CID2) Component ID Register 2  Offset */
#define GPIO_CID2_RESETVALUE                0x05u                                         /**<  (GPIO_CID2) Component ID Register 2  Reset Value */

#define GPIO_CID2_CID2_Pos                  0                                              /**< (GPIO_CID2)  Position */
#define GPIO_CID2_CID2_Msk                  (0xFFu << GPIO_CID2_CID2_Pos)                  /**< (GPIO_CID2)  Mask */
#define GPIO_CID2_CID2(value)               (GPIO_CID2_CID2_Msk & ((value) << GPIO_CID2_CID2_Pos))
#define GPIO_CID2_MASK                      0xFFu                                          /**< \deprecated (GPIO_CID2) Register MASK  (Use GPIO_CID2_Msk instead)  */
#define GPIO_CID2_Msk                       0xFFu                                          /**< (GPIO_CID2) Register Mask  */

/* -------- GPIO_CID3 : (GPIO Offset: 0xffc) (R/ 8) Component ID Register 3 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CID3:8;                    /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} GPIO_CID3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define GPIO_CID3_OFFSET                    0xFFC                                         /**<  (GPIO_CID3) Component ID Register 3  Offset */
#define GPIO_CID3_RESETVALUE                0xB1u                                         /**<  (GPIO_CID3) Component ID Register 3  Reset Value */

#define GPIO_CID3_CID3_Pos                  0                                              /**< (GPIO_CID3)  Position */
#define GPIO_CID3_CID3_Msk                  (0xFFu << GPIO_CID3_CID3_Pos)                  /**< (GPIO_CID3)  Mask */
#define GPIO_CID3_CID3(value)               (GPIO_CID3_CID3_Msk & ((value) << GPIO_CID3_CID3_Pos))
#define GPIO_CID3_MASK                      0xFFu                                          /**< \deprecated (GPIO_CID3) Register MASK  (Use GPIO_CID3_Msk instead)  */
#define GPIO_CID3_Msk                       0xFFu                                          /**< (GPIO_CID3) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief GPIO hardware registers */
typedef struct {  /* GPIO Controller */
  RwReg16 DATA;           /**< (GPIO Offset: 0x00) Data Value */
  __I  uint8_t  Reserved1[2];
  RwReg16 DATAOUT;        /**< (GPIO Offset: 0x04) Data Output Register Value */
  __I  uint8_t  Reserved2[10];
  RwReg16 OUTENSET;       /**< (GPIO Offset: 0x10) Output Enable Set */
  __I  uint8_t  Reserved3[2];
  RwReg16 OUTENCLR;       /**< (GPIO Offset: 0x14) Output Enable Clear */
  __I  uint8_t  Reserved4[10];
  RwReg16 INTENSET;       /**< (GPIO Offset: 0x20) Interrupt Enable Set */
  __I  uint8_t  Reserved5[2];
  RwReg16 INTENCLR;       /**< (GPIO Offset: 0x24) Interrupt Enable Clear */
  __I  uint8_t  Reserved6[2];
  RwReg16 INTTYPESET;     /**< (GPIO Offset: 0x28) Interrupt Type Set */
  __I  uint8_t  Reserved7[2];
  RwReg16 INTTYPECLR;     /**< (GPIO Offset: 0x2C) Interrupt Type Clear */
  __I  uint8_t  Reserved8[2];
  RwReg16 INTPOLSET;      /**< (GPIO Offset: 0x30) Polarity-level, edge IRQ Configuration */
  __I  uint8_t  Reserved9[2];
  RwReg16 INTPOLCLR;      /**< (GPIO Offset: 0x34) IRQ Configuration Clear */
  __I  uint8_t  Reserved10[2];
  RwReg16 INTSTATUSCLEAR; /**< (GPIO Offset: 0x38) Interrupt Status */
  __I  uint8_t  Reserved11[3990];
  RoReg8  PID4;           /**< (GPIO Offset: 0xFD0) Peripheral ID Register 4 */
  __I  uint8_t  Reserved12[3];
  RoReg8  PID5;           /**< (GPIO Offset: 0xFD4) Peripheral ID Register 5 */
  __I  uint8_t  Reserved13[3];
  RoReg8  PID6;           /**< (GPIO Offset: 0xFD8) Peripheral ID Register 6 */
  __I  uint8_t  Reserved14[3];
  RoReg8  PID7;           /**< (GPIO Offset: 0xFDC) Peripheral ID Register 7 */
  __I  uint8_t  Reserved15[3];
  RoReg8  PID0;           /**< (GPIO Offset: 0xFE0) Peripheral ID Register 0 */
  __I  uint8_t  Reserved16[3];
  RoReg8  PID1;           /**< (GPIO Offset: 0xFE4) Peripheral ID Register 1 */
  __I  uint8_t  Reserved17[3];
  RoReg8  PID2;           /**< (GPIO Offset: 0xFE8) Peripheral ID Register 2 */
  __I  uint8_t  Reserved18[3];
  RoReg8  PID3;           /**< (GPIO Offset: 0xFEC) Peripheral ID Register 3 */
  __I  uint8_t  Reserved19[3];
  RoReg8  CID0;           /**< (GPIO Offset: 0xFF0) Component ID Register 0 */
  __I  uint8_t  Reserved20[3];
  RoReg8  CID1;           /**< (GPIO Offset: 0xFF4) Component ID Register 1 */
  __I  uint8_t  Reserved21[3];
  RoReg8  CID2;           /**< (GPIO Offset: 0xFF8) Component ID Register 2 */
  __I  uint8_t  Reserved22[3];
  RoReg8  CID3;           /**< (GPIO Offset: 0xFFC) Component ID Register 3 */
} Gpio;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief GPIO hardware registers */
typedef struct {  /* GPIO Controller */
  __IO GPIO_DATA_Type                 DATA;           /**< Offset: 0x00 (R/W  16) Data Value */
       RoReg8                         Reserved1[0x2];
  __IO GPIO_DATAOUT_Type              DATAOUT;        /**< Offset: 0x04 (R/W  16) Data Output Register Value */
       RoReg8                         Reserved2[0xA];
  __IO GPIO_OUTENSET_Type             OUTENSET;       /**< Offset: 0x10 (R/W  16) Output Enable Set */
       RoReg8                         Reserved3[0x2];
  __IO GPIO_OUTENCLR_Type             OUTENCLR;       /**< Offset: 0x14 (R/W  16) Output Enable Clear */
       RoReg8                         Reserved4[0xA];
  __IO GPIO_INTENSET_Type             INTENSET;       /**< Offset: 0x20 (R/W  16) Interrupt Enable Set */
       RoReg8                         Reserved5[0x2];
  __IO GPIO_INTENCLR_Type             INTENCLR;       /**< Offset: 0x24 (R/W  16) Interrupt Enable Clear */
       RoReg8                         Reserved6[0x2];
  __IO GPIO_INTTYPESET_Type           INTTYPESET;     /**< Offset: 0x28 (R/W  16) Interrupt Type Set */
       RoReg8                         Reserved7[0x2];
  __IO GPIO_INTTYPECLR_Type           INTTYPECLR;     /**< Offset: 0x2C (R/W  16) Interrupt Type Clear */
       RoReg8                         Reserved8[0x2];
  __IO GPIO_INTPOLSET_Type            INTPOLSET;      /**< Offset: 0x30 (R/W  16) Polarity-level, edge IRQ Configuration */
       RoReg8                         Reserved9[0x2];
  __IO GPIO_INTPOLCLR_Type            INTPOLCLR;      /**< Offset: 0x34 (R/W  16) IRQ Configuration Clear */
       RoReg8                         Reserved10[0x2];
  __IO GPIO_INTSTATUSCLEAR_Type       INTSTATUSCLEAR; /**< Offset: 0x38 (R/W  16) Interrupt Status */
       RoReg8                         Reserved11[0xF96];
  __I  GPIO_PID4_Type                 PID4;           /**< Offset: 0xFD0 (R/    8) Peripheral ID Register 4 */
       RoReg8                         Reserved12[0x3];
  __I  GPIO_PID5_Type                 PID5;           /**< Offset: 0xFD4 (R/    8) Peripheral ID Register 5 */
       RoReg8                         Reserved13[0x3];
  __I  GPIO_PID6_Type                 PID6;           /**< Offset: 0xFD8 (R/    8) Peripheral ID Register 6 */
       RoReg8                         Reserved14[0x3];
  __I  GPIO_PID7_Type                 PID7;           /**< Offset: 0xFDC (R/    8) Peripheral ID Register 7 */
       RoReg8                         Reserved15[0x3];
  __I  GPIO_PID0_Type                 PID0;           /**< Offset: 0xFE0 (R/    8) Peripheral ID Register 0 */
       RoReg8                         Reserved16[0x3];
  __I  GPIO_PID1_Type                 PID1;           /**< Offset: 0xFE4 (R/    8) Peripheral ID Register 1 */
       RoReg8                         Reserved17[0x3];
  __I  GPIO_PID2_Type                 PID2;           /**< Offset: 0xFE8 (R/    8) Peripheral ID Register 2 */
       RoReg8                         Reserved18[0x3];
  __I  GPIO_PID3_Type                 PID3;           /**< Offset: 0xFEC (R/    8) Peripheral ID Register 3 */
       RoReg8                         Reserved19[0x3];
  __I  GPIO_CID0_Type                 CID0;           /**< Offset: 0xFF0 (R/    8) Component ID Register 0 */
       RoReg8                         Reserved20[0x3];
  __I  GPIO_CID1_Type                 CID1;           /**< Offset: 0xFF4 (R/    8) Component ID Register 1 */
       RoReg8                         Reserved21[0x3];
  __I  GPIO_CID2_Type                 CID2;           /**< Offset: 0xFF8 (R/    8) Component ID Register 2 */
       RoReg8                         Reserved22[0x3];
  __I  GPIO_CID3_Type                 CID3;           /**< Offset: 0xFFC (R/    8) Component ID Register 3 */
} Gpio;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_GPIO_COMPONENT_ */
