/**
 * \file
 *
 * \brief Component description for ARM_DWT
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

#ifndef _SAMB11_ARM_DWT_COMPONENT_
#define _SAMB11_ARM_DWT_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR ARM_DWT */
/* ========================================================================== */
/** \addtogroup SAMB11_ARM_DWT ARM DWT Control 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define ARM_DWT_ADWT1234
#define REV_ARM_DWT                      0x100

/* -------- ARM_DWT_DWT_CTRL : (ARM_DWT Offset: 0x00) (R/ 32) Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :28;                       /**< bit:  0..27  Reserved */
    uint32_t NUMCOMP:4;                 /**< bit: 28..31  Number of comparators available          */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} ARM_DWT_DWT_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_CTRL_OFFSET             0x00                                          /**<  (ARM_DWT_DWT_CTRL) Control Register  Offset */
#define ARM_DWT_DWT_CTRL_RESETVALUE         0x00u                                         /**<  (ARM_DWT_DWT_CTRL) Control Register  Reset Value */

#define ARM_DWT_DWT_CTRL_NUMCOMP_Pos        28                                             /**< (ARM_DWT_DWT_CTRL) Number of comparators available Position */
#define ARM_DWT_DWT_CTRL_NUMCOMP_Msk        (0xFu << ARM_DWT_DWT_CTRL_NUMCOMP_Pos)         /**< (ARM_DWT_DWT_CTRL) Number of comparators available Mask */
#define ARM_DWT_DWT_CTRL_NUMCOMP(value)     (ARM_DWT_DWT_CTRL_NUMCOMP_Msk & ((value) << ARM_DWT_DWT_CTRL_NUMCOMP_Pos))
#define ARM_DWT_DWT_CTRL_MASK               0xF0000000u                                    /**< \deprecated (ARM_DWT_DWT_CTRL) Register MASK  (Use ARM_DWT_DWT_CTRL_Msk instead)  */
#define ARM_DWT_DWT_CTRL_Msk                0xF0000000u                                    /**< (ARM_DWT_DWT_CTRL) Register Mask  */

/* -------- ARM_DWT_DWT_PCSR : (ARM_DWT Offset: 0x1c) (R/ 32) Program Counter Sample Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EIASAMPLE:32;              /**< bit:  0..31  Executed Instruction Address sample value */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} ARM_DWT_DWT_PCSR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_PCSR_OFFSET             0x1C                                          /**<  (ARM_DWT_DWT_PCSR) Program Counter Sample Register  Offset */
#define ARM_DWT_DWT_PCSR_RESETVALUE         0x00u                                         /**<  (ARM_DWT_DWT_PCSR) Program Counter Sample Register  Reset Value */

#define ARM_DWT_DWT_PCSR_EIASAMPLE_Pos      0                                              /**< (ARM_DWT_DWT_PCSR) Executed Instruction Address sample value Position */
#define ARM_DWT_DWT_PCSR_EIASAMPLE_Msk      (0xFFFFFFFFu << ARM_DWT_DWT_PCSR_EIASAMPLE_Pos)  /**< (ARM_DWT_DWT_PCSR) Executed Instruction Address sample value Mask */
#define ARM_DWT_DWT_PCSR_EIASAMPLE(value)   (ARM_DWT_DWT_PCSR_EIASAMPLE_Msk & ((value) << ARM_DWT_DWT_PCSR_EIASAMPLE_Pos))
#define ARM_DWT_DWT_PCSR_MASK               0xFFFFFFFFu                                    /**< \deprecated (ARM_DWT_DWT_PCSR) Register MASK  (Use ARM_DWT_DWT_PCSR_Msk instead)  */
#define ARM_DWT_DWT_PCSR_Msk                0xFFFFFFFFu                                    /**< (ARM_DWT_DWT_PCSR) Register Mask  */

/* -------- ARM_DWT_DWT_COMP0 : (ARM_DWT Offset: 0x20) (R/W 32) DWT Compare Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t COMP:32;                   /**< bit:  0..31  Reference Value for Comparison           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} ARM_DWT_DWT_COMP0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_COMP0_OFFSET            0x20                                          /**<  (ARM_DWT_DWT_COMP0) DWT Compare Register 0  Offset */
#define ARM_DWT_DWT_COMP0_RESETVALUE        0x00u                                         /**<  (ARM_DWT_DWT_COMP0) DWT Compare Register 0  Reset Value */

#define ARM_DWT_DWT_COMP0_COMP_Pos          0                                              /**< (ARM_DWT_DWT_COMP0) Reference Value for Comparison Position */
#define ARM_DWT_DWT_COMP0_COMP_Msk          (0xFFFFFFFFu << ARM_DWT_DWT_COMP0_COMP_Pos)    /**< (ARM_DWT_DWT_COMP0) Reference Value for Comparison Mask */
#define ARM_DWT_DWT_COMP0_COMP(value)       (ARM_DWT_DWT_COMP0_COMP_Msk & ((value) << ARM_DWT_DWT_COMP0_COMP_Pos))
#define ARM_DWT_DWT_COMP0_MASK              0xFFFFFFFFu                                    /**< \deprecated (ARM_DWT_DWT_COMP0) Register MASK  (Use ARM_DWT_DWT_COMP0_Msk instead)  */
#define ARM_DWT_DWT_COMP0_Msk               0xFFFFFFFFu                                    /**< (ARM_DWT_DWT_COMP0) Register Mask  */

/* -------- ARM_DWT_DWT_MASK0 : (ARM_DWT Offset: 0x24) (R/W 8) DWT Mask Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  MASK_VALUE:5;              /**< bit:   0..4  Size of the ignore mask applied to address range matching */
    uint8_t  :3;                        /**< bit:   5..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_DWT_DWT_MASK0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_MASK0_OFFSET            0x24                                          /**<  (ARM_DWT_DWT_MASK0) DWT Mask Register 0  Offset */
#define ARM_DWT_DWT_MASK0_RESETVALUE        0x00u                                         /**<  (ARM_DWT_DWT_MASK0) DWT Mask Register 0  Reset Value */

#define ARM_DWT_DWT_MASK0_MASK_VALUE_Pos    0                                              /**< (ARM_DWT_DWT_MASK0) Size of the ignore mask applied to address range matching Position */
#define ARM_DWT_DWT_MASK0_MASK_VALUE_Msk    (0x1Fu << ARM_DWT_DWT_MASK0_MASK_VALUE_Pos)    /**< (ARM_DWT_DWT_MASK0) Size of the ignore mask applied to address range matching Mask */
#define ARM_DWT_DWT_MASK0_MASK_VALUE(value) (ARM_DWT_DWT_MASK0_MASK_VALUE_Msk & ((value) << ARM_DWT_DWT_MASK0_MASK_VALUE_Pos))
#define ARM_DWT_DWT_MASK0_Msk               0x1Fu                                          /**< (ARM_DWT_DWT_MASK0) Register Mask  */

/* -------- ARM_DWT_DWT_FUNCTION0 : (ARM_DWT Offset: 0x28) (R/ 32) DWT Function Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t FUNCTION:4;                /**< bit:   0..3  Select action on comparator match        */
    uint32_t :20;                       /**< bit:  4..23  Reserved */
    uint32_t MATCHED:1;                 /**< bit:     24  Comparator Match                         */
    uint32_t :7;                        /**< bit: 25..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} ARM_DWT_DWT_FUNCTION0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_FUNCTION0_OFFSET        0x28                                          /**<  (ARM_DWT_DWT_FUNCTION0) DWT Function Register 0  Offset */
#define ARM_DWT_DWT_FUNCTION0_RESETVALUE    0x00u                                         /**<  (ARM_DWT_DWT_FUNCTION0) DWT Function Register 0  Reset Value */

#define ARM_DWT_DWT_FUNCTION0_FUNCTION_Pos  0                                              /**< (ARM_DWT_DWT_FUNCTION0) Select action on comparator match Position */
#define ARM_DWT_DWT_FUNCTION0_FUNCTION_Msk  (0xFu << ARM_DWT_DWT_FUNCTION0_FUNCTION_Pos)   /**< (ARM_DWT_DWT_FUNCTION0) Select action on comparator match Mask */
#define ARM_DWT_DWT_FUNCTION0_FUNCTION(value) (ARM_DWT_DWT_FUNCTION0_FUNCTION_Msk & ((value) << ARM_DWT_DWT_FUNCTION0_FUNCTION_Pos))
#define   ARM_DWT_DWT_FUNCTION0_FUNCTION_0_Val 0x0u                                           /**< (ARM_DWT_DWT_FUNCTION0) Disabled  */
#define   ARM_DWT_DWT_FUNCTION0_FUNCTION_4_Val 0x4u                                           /**< (ARM_DWT_DWT_FUNCTION0) PC Watchpoint Event (Instruction)  */
#define   ARM_DWT_DWT_FUNCTION0_FUNCTION_5_Val 0x5u                                           /**< (ARM_DWT_DWT_FUNCTION0) Watchpoint Event Read Only (Data)  */
#define   ARM_DWT_DWT_FUNCTION0_FUNCTION_6_Val 0x6u                                           /**< (ARM_DWT_DWT_FUNCTION0) Watchpoint Event Write Only (Data)  */
#define   ARM_DWT_DWT_FUNCTION0_FUNCTION_7_Val 0x7u                                           /**< (ARM_DWT_DWT_FUNCTION0) Watchpoing Event Write-Read (Data)  */
#define ARM_DWT_DWT_FUNCTION0_FUNCTION_0    (ARM_DWT_DWT_FUNCTION0_FUNCTION_0_Val << ARM_DWT_DWT_FUNCTION0_FUNCTION_Pos)  /**< (ARM_DWT_DWT_FUNCTION0) Disabled Position  */
#define ARM_DWT_DWT_FUNCTION0_FUNCTION_4    (ARM_DWT_DWT_FUNCTION0_FUNCTION_4_Val << ARM_DWT_DWT_FUNCTION0_FUNCTION_Pos)  /**< (ARM_DWT_DWT_FUNCTION0) PC Watchpoint Event (Instruction) Position  */
#define ARM_DWT_DWT_FUNCTION0_FUNCTION_5    (ARM_DWT_DWT_FUNCTION0_FUNCTION_5_Val << ARM_DWT_DWT_FUNCTION0_FUNCTION_Pos)  /**< (ARM_DWT_DWT_FUNCTION0) Watchpoint Event Read Only (Data) Position  */
#define ARM_DWT_DWT_FUNCTION0_FUNCTION_6    (ARM_DWT_DWT_FUNCTION0_FUNCTION_6_Val << ARM_DWT_DWT_FUNCTION0_FUNCTION_Pos)  /**< (ARM_DWT_DWT_FUNCTION0) Watchpoint Event Write Only (Data) Position  */
#define ARM_DWT_DWT_FUNCTION0_FUNCTION_7    (ARM_DWT_DWT_FUNCTION0_FUNCTION_7_Val << ARM_DWT_DWT_FUNCTION0_FUNCTION_Pos)  /**< (ARM_DWT_DWT_FUNCTION0) Watchpoing Event Write-Read (Data) Position  */
#define ARM_DWT_DWT_FUNCTION0_MATCHED_Pos   24                                             /**< (ARM_DWT_DWT_FUNCTION0) Comparator Match Position */
#define ARM_DWT_DWT_FUNCTION0_MATCHED_Msk   (0x1u << ARM_DWT_DWT_FUNCTION0_MATCHED_Pos)    /**< (ARM_DWT_DWT_FUNCTION0) Comparator Match Mask */
#define ARM_DWT_DWT_FUNCTION0_MATCHED       ARM_DWT_DWT_FUNCTION0_MATCHED_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use ARM_DWT_DWT_FUNCTION0_MATCHED_Msk instead */
#define ARM_DWT_DWT_FUNCTION0_MASK          0x100000Fu                                     /**< \deprecated (ARM_DWT_DWT_FUNCTION0) Register MASK  (Use ARM_DWT_DWT_FUNCTION0_Msk instead)  */
#define ARM_DWT_DWT_FUNCTION0_Msk           0x100000Fu                                     /**< (ARM_DWT_DWT_FUNCTION0) Register Mask  */

/* -------- ARM_DWT_DWT_COMP1 : (ARM_DWT Offset: 0x30) (R/W 32) DWT Compare Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t COMP:32;                   /**< bit:  0..31  Reference Value for Comparison           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} ARM_DWT_DWT_COMP1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_COMP1_OFFSET            0x30                                          /**<  (ARM_DWT_DWT_COMP1) DWT Compare Register 1  Offset */
#define ARM_DWT_DWT_COMP1_RESETVALUE        0x00u                                         /**<  (ARM_DWT_DWT_COMP1) DWT Compare Register 1  Reset Value */

#define ARM_DWT_DWT_COMP1_COMP_Pos          0                                              /**< (ARM_DWT_DWT_COMP1) Reference Value for Comparison Position */
#define ARM_DWT_DWT_COMP1_COMP_Msk          (0xFFFFFFFFu << ARM_DWT_DWT_COMP1_COMP_Pos)    /**< (ARM_DWT_DWT_COMP1) Reference Value for Comparison Mask */
#define ARM_DWT_DWT_COMP1_COMP(value)       (ARM_DWT_DWT_COMP1_COMP_Msk & ((value) << ARM_DWT_DWT_COMP1_COMP_Pos))
#define ARM_DWT_DWT_COMP1_MASK              0xFFFFFFFFu                                    /**< \deprecated (ARM_DWT_DWT_COMP1) Register MASK  (Use ARM_DWT_DWT_COMP1_Msk instead)  */
#define ARM_DWT_DWT_COMP1_Msk               0xFFFFFFFFu                                    /**< (ARM_DWT_DWT_COMP1) Register Mask  */

/* -------- ARM_DWT_DWT_MASK1 : (ARM_DWT Offset: 0x34) (R/W 8) DWT Mask Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  MASK_VALUE:5;              /**< bit:   0..4  Size of the ignore mask applied to address range matching */
    uint8_t  :3;                        /**< bit:   5..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_DWT_DWT_MASK1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_MASK1_OFFSET            0x34                                          /**<  (ARM_DWT_DWT_MASK1) DWT Mask Register 1  Offset */
#define ARM_DWT_DWT_MASK1_RESETVALUE        0x00u                                         /**<  (ARM_DWT_DWT_MASK1) DWT Mask Register 1  Reset Value */

#define ARM_DWT_DWT_MASK1_MASK_VALUE_Pos    0                                              /**< (ARM_DWT_DWT_MASK1) Size of the ignore mask applied to address range matching Position */
#define ARM_DWT_DWT_MASK1_MASK_VALUE_Msk    (0x1Fu << ARM_DWT_DWT_MASK1_MASK_VALUE_Pos)    /**< (ARM_DWT_DWT_MASK1) Size of the ignore mask applied to address range matching Mask */
#define ARM_DWT_DWT_MASK1_MASK_VALUE(value) (ARM_DWT_DWT_MASK1_MASK_VALUE_Msk & ((value) << ARM_DWT_DWT_MASK1_MASK_VALUE_Pos))
#define ARM_DWT_DWT_MASK1_Msk               0x1Fu                                          /**< (ARM_DWT_DWT_MASK1) Register Mask  */

/* -------- ARM_DWT_DWT_FUNCTION1 : (ARM_DWT Offset: 0x38) (R/ 32) DWT Function Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t FUNCTION:4;                /**< bit:   0..3  Select action on comparator match        */
    uint32_t :20;                       /**< bit:  4..23  Reserved */
    uint32_t MATCHED:1;                 /**< bit:     24  Comparator Match                         */
    uint32_t :7;                        /**< bit: 25..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} ARM_DWT_DWT_FUNCTION1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_FUNCTION1_OFFSET        0x38                                          /**<  (ARM_DWT_DWT_FUNCTION1) DWT Function Register 1  Offset */
#define ARM_DWT_DWT_FUNCTION1_RESETVALUE    0x00u                                         /**<  (ARM_DWT_DWT_FUNCTION1) DWT Function Register 1  Reset Value */

#define ARM_DWT_DWT_FUNCTION1_FUNCTION_Pos  0                                              /**< (ARM_DWT_DWT_FUNCTION1) Select action on comparator match Position */
#define ARM_DWT_DWT_FUNCTION1_FUNCTION_Msk  (0xFu << ARM_DWT_DWT_FUNCTION1_FUNCTION_Pos)   /**< (ARM_DWT_DWT_FUNCTION1) Select action on comparator match Mask */
#define ARM_DWT_DWT_FUNCTION1_FUNCTION(value) (ARM_DWT_DWT_FUNCTION1_FUNCTION_Msk & ((value) << ARM_DWT_DWT_FUNCTION1_FUNCTION_Pos))
#define   ARM_DWT_DWT_FUNCTION1_FUNCTION_0_Val 0x0u                                           /**< (ARM_DWT_DWT_FUNCTION1) Disabled  */
#define   ARM_DWT_DWT_FUNCTION1_FUNCTION_4_Val 0x4u                                           /**< (ARM_DWT_DWT_FUNCTION1) PC Watchpoint Event (Instruction)  */
#define   ARM_DWT_DWT_FUNCTION1_FUNCTION_5_Val 0x5u                                           /**< (ARM_DWT_DWT_FUNCTION1) Watchpoint Event Read Only (Data)  */
#define   ARM_DWT_DWT_FUNCTION1_FUNCTION_6_Val 0x6u                                           /**< (ARM_DWT_DWT_FUNCTION1) Watchpoint Event Write Only (Data)  */
#define   ARM_DWT_DWT_FUNCTION1_FUNCTION_7_Val 0x7u                                           /**< (ARM_DWT_DWT_FUNCTION1) Watchpoing Event Write-Read (Data)  */
#define ARM_DWT_DWT_FUNCTION1_FUNCTION_0    (ARM_DWT_DWT_FUNCTION1_FUNCTION_0_Val << ARM_DWT_DWT_FUNCTION1_FUNCTION_Pos)  /**< (ARM_DWT_DWT_FUNCTION1) Disabled Position  */
#define ARM_DWT_DWT_FUNCTION1_FUNCTION_4    (ARM_DWT_DWT_FUNCTION1_FUNCTION_4_Val << ARM_DWT_DWT_FUNCTION1_FUNCTION_Pos)  /**< (ARM_DWT_DWT_FUNCTION1) PC Watchpoint Event (Instruction) Position  */
#define ARM_DWT_DWT_FUNCTION1_FUNCTION_5    (ARM_DWT_DWT_FUNCTION1_FUNCTION_5_Val << ARM_DWT_DWT_FUNCTION1_FUNCTION_Pos)  /**< (ARM_DWT_DWT_FUNCTION1) Watchpoint Event Read Only (Data) Position  */
#define ARM_DWT_DWT_FUNCTION1_FUNCTION_6    (ARM_DWT_DWT_FUNCTION1_FUNCTION_6_Val << ARM_DWT_DWT_FUNCTION1_FUNCTION_Pos)  /**< (ARM_DWT_DWT_FUNCTION1) Watchpoint Event Write Only (Data) Position  */
#define ARM_DWT_DWT_FUNCTION1_FUNCTION_7    (ARM_DWT_DWT_FUNCTION1_FUNCTION_7_Val << ARM_DWT_DWT_FUNCTION1_FUNCTION_Pos)  /**< (ARM_DWT_DWT_FUNCTION1) Watchpoing Event Write-Read (Data) Position  */
#define ARM_DWT_DWT_FUNCTION1_MATCHED_Pos   24                                             /**< (ARM_DWT_DWT_FUNCTION1) Comparator Match Position */
#define ARM_DWT_DWT_FUNCTION1_MATCHED_Msk   (0x1u << ARM_DWT_DWT_FUNCTION1_MATCHED_Pos)    /**< (ARM_DWT_DWT_FUNCTION1) Comparator Match Mask */
#define ARM_DWT_DWT_FUNCTION1_MATCHED       ARM_DWT_DWT_FUNCTION1_MATCHED_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use ARM_DWT_DWT_FUNCTION1_MATCHED_Msk instead */
#define ARM_DWT_DWT_FUNCTION1_MASK          0x100000Fu                                     /**< \deprecated (ARM_DWT_DWT_FUNCTION1) Register MASK  (Use ARM_DWT_DWT_FUNCTION1_Msk instead)  */
#define ARM_DWT_DWT_FUNCTION1_Msk           0x100000Fu                                     /**< (ARM_DWT_DWT_FUNCTION1) Register Mask  */

/* -------- ARM_DWT_DWT_PID4 : (ARM_DWT Offset: 0xfd0) (R/ 8) Peripheral ID Register 4 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  JEP106_C_CODE:4;           /**< bit:   0..3  JEP106 C Code                            */
    uint8_t  BLOCK_COUNT:4;             /**< bit:   4..7  Block Count                              */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_DWT_DWT_PID4_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_PID4_OFFSET             0xFD0                                         /**<  (ARM_DWT_DWT_PID4) Peripheral ID Register 4  Offset */
#define ARM_DWT_DWT_PID4_RESETVALUE         0x04u                                         /**<  (ARM_DWT_DWT_PID4) Peripheral ID Register 4  Reset Value */

#define ARM_DWT_DWT_PID4_JEP106_C_CODE_Pos  0                                              /**< (ARM_DWT_DWT_PID4) JEP106 C Code Position */
#define ARM_DWT_DWT_PID4_JEP106_C_CODE_Msk  (0xFu << ARM_DWT_DWT_PID4_JEP106_C_CODE_Pos)   /**< (ARM_DWT_DWT_PID4) JEP106 C Code Mask */
#define ARM_DWT_DWT_PID4_JEP106_C_CODE(value) (ARM_DWT_DWT_PID4_JEP106_C_CODE_Msk & ((value) << ARM_DWT_DWT_PID4_JEP106_C_CODE_Pos))
#define ARM_DWT_DWT_PID4_BLOCK_COUNT_Pos    4                                              /**< (ARM_DWT_DWT_PID4) Block Count Position */
#define ARM_DWT_DWT_PID4_BLOCK_COUNT_Msk    (0xFu << ARM_DWT_DWT_PID4_BLOCK_COUNT_Pos)     /**< (ARM_DWT_DWT_PID4) Block Count Mask */
#define ARM_DWT_DWT_PID4_BLOCK_COUNT(value) (ARM_DWT_DWT_PID4_BLOCK_COUNT_Msk & ((value) << ARM_DWT_DWT_PID4_BLOCK_COUNT_Pos))
#define ARM_DWT_DWT_PID4_MASK               0xFFu                                          /**< \deprecated (ARM_DWT_DWT_PID4) Register MASK  (Use ARM_DWT_DWT_PID4_Msk instead)  */
#define ARM_DWT_DWT_PID4_Msk                0xFFu                                          /**< (ARM_DWT_DWT_PID4) Register Mask  */

/* -------- ARM_DWT_DWT_PID0 : (ARM_DWT Offset: 0xfe0) (R/ 8) Peripheral ID Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PART_NUMBER:8;             /**< bit:   0..7  Part Number Bits 7:0                     */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_DWT_DWT_PID0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_PID0_OFFSET             0xFE0                                         /**<  (ARM_DWT_DWT_PID0) Peripheral ID Register 0  Offset */
#define ARM_DWT_DWT_PID0_RESETVALUE         0x0Au                                         /**<  (ARM_DWT_DWT_PID0) Peripheral ID Register 0  Reset Value */

#define ARM_DWT_DWT_PID0_PART_NUMBER_Pos    0                                              /**< (ARM_DWT_DWT_PID0) Part Number Bits 7:0 Position */
#define ARM_DWT_DWT_PID0_PART_NUMBER_Msk    (0xFFu << ARM_DWT_DWT_PID0_PART_NUMBER_Pos)    /**< (ARM_DWT_DWT_PID0) Part Number Bits 7:0 Mask */
#define ARM_DWT_DWT_PID0_PART_NUMBER(value) (ARM_DWT_DWT_PID0_PART_NUMBER_Msk & ((value) << ARM_DWT_DWT_PID0_PART_NUMBER_Pos))
#define ARM_DWT_DWT_PID0_MASK               0xFFu                                          /**< \deprecated (ARM_DWT_DWT_PID0) Register MASK  (Use ARM_DWT_DWT_PID0_Msk instead)  */
#define ARM_DWT_DWT_PID0_Msk                0xFFu                                          /**< (ARM_DWT_DWT_PID0) Register Mask  */

/* -------- ARM_DWT_DWT_PID1 : (ARM_DWT Offset: 0xfe4) (R/ 8) Peripheral ID Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PART_NUMBER:4;             /**< bit:   0..3  Part Number Bits 11:8                    */
    uint8_t  JEP106_ID_3_0:4;           /**< bit:   4..7  JEP106 ID Code Bits 3:0                  */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_DWT_DWT_PID1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_PID1_OFFSET             0xFE4                                         /**<  (ARM_DWT_DWT_PID1) Peripheral ID Register 1  Offset */
#define ARM_DWT_DWT_PID1_RESETVALUE         0xB0u                                         /**<  (ARM_DWT_DWT_PID1) Peripheral ID Register 1  Reset Value */

#define ARM_DWT_DWT_PID1_PART_NUMBER_Pos    0                                              /**< (ARM_DWT_DWT_PID1) Part Number Bits 11:8 Position */
#define ARM_DWT_DWT_PID1_PART_NUMBER_Msk    (0xFu << ARM_DWT_DWT_PID1_PART_NUMBER_Pos)     /**< (ARM_DWT_DWT_PID1) Part Number Bits 11:8 Mask */
#define ARM_DWT_DWT_PID1_PART_NUMBER(value) (ARM_DWT_DWT_PID1_PART_NUMBER_Msk & ((value) << ARM_DWT_DWT_PID1_PART_NUMBER_Pos))
#define ARM_DWT_DWT_PID1_JEP106_ID_3_0_Pos  4                                              /**< (ARM_DWT_DWT_PID1) JEP106 ID Code Bits 3:0 Position */
#define ARM_DWT_DWT_PID1_JEP106_ID_3_0_Msk  (0xFu << ARM_DWT_DWT_PID1_JEP106_ID_3_0_Pos)   /**< (ARM_DWT_DWT_PID1) JEP106 ID Code Bits 3:0 Mask */
#define ARM_DWT_DWT_PID1_JEP106_ID_3_0(value) (ARM_DWT_DWT_PID1_JEP106_ID_3_0_Msk & ((value) << ARM_DWT_DWT_PID1_JEP106_ID_3_0_Pos))
#define ARM_DWT_DWT_PID1_MASK               0xFFu                                          /**< \deprecated (ARM_DWT_DWT_PID1) Register MASK  (Use ARM_DWT_DWT_PID1_Msk instead)  */
#define ARM_DWT_DWT_PID1_Msk                0xFFu                                          /**< (ARM_DWT_DWT_PID1) Register Mask  */

/* -------- ARM_DWT_DWT_PID2 : (ARM_DWT Offset: 0xfe8) (R/ 8) Peripheral ID Register 2 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  JEP106_ID_6_4:3;           /**< bit:   0..2  JEP106 ID Code Bits 6:4                  */
    uint8_t  JEDEC_USED:1;              /**< bit:      3  JEDEC Used                               */
    uint8_t  REVISION:4;                /**< bit:   4..7  Revision                                 */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_DWT_DWT_PID2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_PID2_OFFSET             0xFE8                                         /**<  (ARM_DWT_DWT_PID2) Peripheral ID Register 2  Offset */
#define ARM_DWT_DWT_PID2_RESETVALUE         0x0Bu                                         /**<  (ARM_DWT_DWT_PID2) Peripheral ID Register 2  Reset Value */

#define ARM_DWT_DWT_PID2_JEP106_ID_6_4_Pos  0                                              /**< (ARM_DWT_DWT_PID2) JEP106 ID Code Bits 6:4 Position */
#define ARM_DWT_DWT_PID2_JEP106_ID_6_4_Msk  (0x7u << ARM_DWT_DWT_PID2_JEP106_ID_6_4_Pos)   /**< (ARM_DWT_DWT_PID2) JEP106 ID Code Bits 6:4 Mask */
#define ARM_DWT_DWT_PID2_JEP106_ID_6_4(value) (ARM_DWT_DWT_PID2_JEP106_ID_6_4_Msk & ((value) << ARM_DWT_DWT_PID2_JEP106_ID_6_4_Pos))
#define ARM_DWT_DWT_PID2_JEDEC_USED_Pos     3                                              /**< (ARM_DWT_DWT_PID2) JEDEC Used Position */
#define ARM_DWT_DWT_PID2_JEDEC_USED_Msk     (0x1u << ARM_DWT_DWT_PID2_JEDEC_USED_Pos)      /**< (ARM_DWT_DWT_PID2) JEDEC Used Mask */
#define ARM_DWT_DWT_PID2_JEDEC_USED         ARM_DWT_DWT_PID2_JEDEC_USED_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use ARM_DWT_DWT_PID2_JEDEC_USED_Msk instead */
#define ARM_DWT_DWT_PID2_REVISION_Pos       4                                              /**< (ARM_DWT_DWT_PID2) Revision Position */
#define ARM_DWT_DWT_PID2_REVISION_Msk       (0xFu << ARM_DWT_DWT_PID2_REVISION_Pos)        /**< (ARM_DWT_DWT_PID2) Revision Mask */
#define ARM_DWT_DWT_PID2_REVISION(value)    (ARM_DWT_DWT_PID2_REVISION_Msk & ((value) << ARM_DWT_DWT_PID2_REVISION_Pos))
#define ARM_DWT_DWT_PID2_MASK               0xFFu                                          /**< \deprecated (ARM_DWT_DWT_PID2) Register MASK  (Use ARM_DWT_DWT_PID2_Msk instead)  */
#define ARM_DWT_DWT_PID2_Msk                0xFFu                                          /**< (ARM_DWT_DWT_PID2) Register Mask  */

/* -------- ARM_DWT_DWT_PID3 : (ARM_DWT Offset: 0xfec) (R/ 8) Peripheral ID Register 3 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CUSTOMER_MOD_NUMBER:4;     /**< bit:   0..3  Customer Modification Number             */
    uint8_t  ECO_REV_NUMBER:4;          /**< bit:   4..7  ECO Revision Number                      */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_DWT_DWT_PID3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_PID3_OFFSET             0xFEC                                         /**<  (ARM_DWT_DWT_PID3) Peripheral ID Register 3  Offset */
#define ARM_DWT_DWT_PID3_RESETVALUE         0x00u                                         /**<  (ARM_DWT_DWT_PID3) Peripheral ID Register 3  Reset Value */

#define ARM_DWT_DWT_PID3_CUSTOMER_MOD_NUMBER_Pos 0                                              /**< (ARM_DWT_DWT_PID3) Customer Modification Number Position */
#define ARM_DWT_DWT_PID3_CUSTOMER_MOD_NUMBER_Msk (0xFu << ARM_DWT_DWT_PID3_CUSTOMER_MOD_NUMBER_Pos)  /**< (ARM_DWT_DWT_PID3) Customer Modification Number Mask */
#define ARM_DWT_DWT_PID3_CUSTOMER_MOD_NUMBER(value) (ARM_DWT_DWT_PID3_CUSTOMER_MOD_NUMBER_Msk & ((value) << ARM_DWT_DWT_PID3_CUSTOMER_MOD_NUMBER_Pos))
#define ARM_DWT_DWT_PID3_ECO_REV_NUMBER_Pos 4                                              /**< (ARM_DWT_DWT_PID3) ECO Revision Number Position */
#define ARM_DWT_DWT_PID3_ECO_REV_NUMBER_Msk (0xFu << ARM_DWT_DWT_PID3_ECO_REV_NUMBER_Pos)  /**< (ARM_DWT_DWT_PID3) ECO Revision Number Mask */
#define ARM_DWT_DWT_PID3_ECO_REV_NUMBER(value) (ARM_DWT_DWT_PID3_ECO_REV_NUMBER_Msk & ((value) << ARM_DWT_DWT_PID3_ECO_REV_NUMBER_Pos))
#define ARM_DWT_DWT_PID3_MASK               0xFFu                                          /**< \deprecated (ARM_DWT_DWT_PID3) Register MASK  (Use ARM_DWT_DWT_PID3_Msk instead)  */
#define ARM_DWT_DWT_PID3_Msk                0xFFu                                          /**< (ARM_DWT_DWT_PID3) Register Mask  */

/* -------- ARM_DWT_DWT_CID0 : (ARM_DWT Offset: 0xff0) (R/ 8) Component ID Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DWT_CID0:8;                /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_DWT_DWT_CID0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_CID0_OFFSET             0xFF0                                         /**<  (ARM_DWT_DWT_CID0) Component ID Register 0  Offset */
#define ARM_DWT_DWT_CID0_RESETVALUE         0x0Du                                         /**<  (ARM_DWT_DWT_CID0) Component ID Register 0  Reset Value */

#define ARM_DWT_DWT_CID0_DWT_CID0_Pos       0                                              /**< (ARM_DWT_DWT_CID0)  Position */
#define ARM_DWT_DWT_CID0_DWT_CID0_Msk       (0xFFu << ARM_DWT_DWT_CID0_DWT_CID0_Pos)       /**< (ARM_DWT_DWT_CID0)  Mask */
#define ARM_DWT_DWT_CID0_DWT_CID0(value)    (ARM_DWT_DWT_CID0_DWT_CID0_Msk & ((value) << ARM_DWT_DWT_CID0_DWT_CID0_Pos))
#define ARM_DWT_DWT_CID0_MASK               0xFFu                                          /**< \deprecated (ARM_DWT_DWT_CID0) Register MASK  (Use ARM_DWT_DWT_CID0_Msk instead)  */
#define ARM_DWT_DWT_CID0_Msk                0xFFu                                          /**< (ARM_DWT_DWT_CID0) Register Mask  */

/* -------- ARM_DWT_DWT_CID1 : (ARM_DWT Offset: 0xff4) (R/ 8) Component ID Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DWT_CID1:8;                /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_DWT_DWT_CID1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_CID1_OFFSET             0xFF4                                         /**<  (ARM_DWT_DWT_CID1) Component ID Register 1  Offset */
#define ARM_DWT_DWT_CID1_RESETVALUE         0xE0u                                         /**<  (ARM_DWT_DWT_CID1) Component ID Register 1  Reset Value */

#define ARM_DWT_DWT_CID1_DWT_CID1_Pos       0                                              /**< (ARM_DWT_DWT_CID1)  Position */
#define ARM_DWT_DWT_CID1_DWT_CID1_Msk       (0xFFu << ARM_DWT_DWT_CID1_DWT_CID1_Pos)       /**< (ARM_DWT_DWT_CID1)  Mask */
#define ARM_DWT_DWT_CID1_DWT_CID1(value)    (ARM_DWT_DWT_CID1_DWT_CID1_Msk & ((value) << ARM_DWT_DWT_CID1_DWT_CID1_Pos))
#define ARM_DWT_DWT_CID1_MASK               0xFFu                                          /**< \deprecated (ARM_DWT_DWT_CID1) Register MASK  (Use ARM_DWT_DWT_CID1_Msk instead)  */
#define ARM_DWT_DWT_CID1_Msk                0xFFu                                          /**< (ARM_DWT_DWT_CID1) Register Mask  */

/* -------- ARM_DWT_DWT_CID2 : (ARM_DWT Offset: 0xff8) (R/ 8) Component ID Register 2 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DWT_CID2:8;                /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_DWT_DWT_CID2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_CID2_OFFSET             0xFF8                                         /**<  (ARM_DWT_DWT_CID2) Component ID Register 2  Offset */
#define ARM_DWT_DWT_CID2_RESETVALUE         0x05u                                         /**<  (ARM_DWT_DWT_CID2) Component ID Register 2  Reset Value */

#define ARM_DWT_DWT_CID2_DWT_CID2_Pos       0                                              /**< (ARM_DWT_DWT_CID2)  Position */
#define ARM_DWT_DWT_CID2_DWT_CID2_Msk       (0xFFu << ARM_DWT_DWT_CID2_DWT_CID2_Pos)       /**< (ARM_DWT_DWT_CID2)  Mask */
#define ARM_DWT_DWT_CID2_DWT_CID2(value)    (ARM_DWT_DWT_CID2_DWT_CID2_Msk & ((value) << ARM_DWT_DWT_CID2_DWT_CID2_Pos))
#define ARM_DWT_DWT_CID2_MASK               0xFFu                                          /**< \deprecated (ARM_DWT_DWT_CID2) Register MASK  (Use ARM_DWT_DWT_CID2_Msk instead)  */
#define ARM_DWT_DWT_CID2_Msk                0xFFu                                          /**< (ARM_DWT_DWT_CID2) Register Mask  */

/* -------- ARM_DWT_DWT_CID3 : (ARM_DWT Offset: 0xffc) (R/ 8) Component ID Register 3 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DWT_CID3:8;                /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_DWT_DWT_CID3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_DWT_DWT_CID3_OFFSET             0xFFC                                         /**<  (ARM_DWT_DWT_CID3) Component ID Register 3  Offset */
#define ARM_DWT_DWT_CID3_RESETVALUE         0xB1u                                         /**<  (ARM_DWT_DWT_CID3) Component ID Register 3  Reset Value */

#define ARM_DWT_DWT_CID3_DWT_CID3_Pos       0                                              /**< (ARM_DWT_DWT_CID3)  Position */
#define ARM_DWT_DWT_CID3_DWT_CID3_Msk       (0xFFu << ARM_DWT_DWT_CID3_DWT_CID3_Pos)       /**< (ARM_DWT_DWT_CID3)  Mask */
#define ARM_DWT_DWT_CID3_DWT_CID3(value)    (ARM_DWT_DWT_CID3_DWT_CID3_Msk & ((value) << ARM_DWT_DWT_CID3_DWT_CID3_Pos))
#define ARM_DWT_DWT_CID3_MASK               0xFFu                                          /**< \deprecated (ARM_DWT_DWT_CID3) Register MASK  (Use ARM_DWT_DWT_CID3_Msk instead)  */
#define ARM_DWT_DWT_CID3_Msk                0xFFu                                          /**< (ARM_DWT_DWT_CID3) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief ARM_DWT hardware registers */
typedef struct {  /* ARM DWT Control */
  RoReg   DWT_CTRL;       /**< (ARM_DWT Offset: 0x00) Control Register */
  __I  uint32_t Reserved1[6];
  RoReg   DWT_PCSR;       /**< (ARM_DWT Offset: 0x1C) Program Counter Sample Register */
  RwReg   DWT_COMP0;      /**< (ARM_DWT Offset: 0x20) DWT Compare Register 0 */
  RwReg8  DWT_MASK0;      /**< (ARM_DWT Offset: 0x24) DWT Mask Register 0 */
  __I  uint8_t  Reserved2[3];
  RoReg   DWT_FUNCTION0;  /**< (ARM_DWT Offset: 0x28) DWT Function Register 0 */
  __I  uint32_t Reserved3[1];
  RwReg   DWT_COMP1;      /**< (ARM_DWT Offset: 0x30) DWT Compare Register 1 */
  RwReg8  DWT_MASK1;      /**< (ARM_DWT Offset: 0x34) DWT Mask Register 1 */
  __I  uint8_t  Reserved4[3];
  RoReg   DWT_FUNCTION1;  /**< (ARM_DWT Offset: 0x38) DWT Function Register 1 */
  __I  uint32_t Reserved5[997];
  RoReg8  DWT_PID4;       /**< (ARM_DWT Offset: 0xFD0) Peripheral ID Register 4 */
  __I  uint8_t  Reserved6[15];
  RoReg8  DWT_PID0;       /**< (ARM_DWT Offset: 0xFE0) Peripheral ID Register 0 */
  __I  uint8_t  Reserved7[3];
  RoReg8  DWT_PID1;       /**< (ARM_DWT Offset: 0xFE4) Peripheral ID Register 1 */
  __I  uint8_t  Reserved8[3];
  RoReg8  DWT_PID2;       /**< (ARM_DWT Offset: 0xFE8) Peripheral ID Register 2 */
  __I  uint8_t  Reserved9[3];
  RoReg8  DWT_PID3;       /**< (ARM_DWT Offset: 0xFEC) Peripheral ID Register 3 */
  __I  uint8_t  Reserved10[3];
  RoReg8  DWT_CID0;       /**< (ARM_DWT Offset: 0xFF0) Component ID Register 0 */
  __I  uint8_t  Reserved11[3];
  RoReg8  DWT_CID1;       /**< (ARM_DWT Offset: 0xFF4) Component ID Register 1 */
  __I  uint8_t  Reserved12[3];
  RoReg8  DWT_CID2;       /**< (ARM_DWT Offset: 0xFF8) Component ID Register 2 */
  __I  uint8_t  Reserved13[3];
  RoReg8  DWT_CID3;       /**< (ARM_DWT Offset: 0xFFC) Component ID Register 3 */
} ArmDwt;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief ARM_DWT hardware registers */
typedef struct {  /* ARM DWT Control */
  __I  ARM_DWT_DWT_CTRL_Type          DWT_CTRL;       /**< Offset: 0x00 (R/   32) Control Register */
       RoReg8                         Reserved1[0x18];
  __I  ARM_DWT_DWT_PCSR_Type          DWT_PCSR;       /**< Offset: 0x1C (R/   32) Program Counter Sample Register */
  __IO ARM_DWT_DWT_COMP0_Type         DWT_COMP0;      /**< Offset: 0x20 (R/W  32) DWT Compare Register 0 */
  __IO ARM_DWT_DWT_MASK0_Type         DWT_MASK0;      /**< Offset: 0x24 (R/W   8) DWT Mask Register 0 */
       RoReg8                         Reserved2[0x3];
  __I  ARM_DWT_DWT_FUNCTION0_Type     DWT_FUNCTION0;  /**< Offset: 0x28 (R/   32) DWT Function Register 0 */
       RoReg8                         Reserved3[0x4];
  __IO ARM_DWT_DWT_COMP1_Type         DWT_COMP1;      /**< Offset: 0x30 (R/W  32) DWT Compare Register 1 */
  __IO ARM_DWT_DWT_MASK1_Type         DWT_MASK1;      /**< Offset: 0x34 (R/W   8) DWT Mask Register 1 */
       RoReg8                         Reserved4[0x3];
  __I  ARM_DWT_DWT_FUNCTION1_Type     DWT_FUNCTION1;  /**< Offset: 0x38 (R/   32) DWT Function Register 1 */
       RoReg8                         Reserved5[0xF94];
  __I  ARM_DWT_DWT_PID4_Type          DWT_PID4;       /**< Offset: 0xFD0 (R/    8) Peripheral ID Register 4 */
       RoReg8                         Reserved6[0xF];
  __I  ARM_DWT_DWT_PID0_Type          DWT_PID0;       /**< Offset: 0xFE0 (R/    8) Peripheral ID Register 0 */
       RoReg8                         Reserved7[0x3];
  __I  ARM_DWT_DWT_PID1_Type          DWT_PID1;       /**< Offset: 0xFE4 (R/    8) Peripheral ID Register 1 */
       RoReg8                         Reserved8[0x3];
  __I  ARM_DWT_DWT_PID2_Type          DWT_PID2;       /**< Offset: 0xFE8 (R/    8) Peripheral ID Register 2 */
       RoReg8                         Reserved9[0x3];
  __I  ARM_DWT_DWT_PID3_Type          DWT_PID3;       /**< Offset: 0xFEC (R/    8) Peripheral ID Register 3 */
       RoReg8                         Reserved10[0x3];
  __I  ARM_DWT_DWT_CID0_Type          DWT_CID0;       /**< Offset: 0xFF0 (R/    8) Component ID Register 0 */
       RoReg8                         Reserved11[0x3];
  __I  ARM_DWT_DWT_CID1_Type          DWT_CID1;       /**< Offset: 0xFF4 (R/    8) Component ID Register 1 */
       RoReg8                         Reserved12[0x3];
  __I  ARM_DWT_DWT_CID2_Type          DWT_CID2;       /**< Offset: 0xFF8 (R/    8) Component ID Register 2 */
       RoReg8                         Reserved13[0x3];
  __I  ARM_DWT_DWT_CID3_Type          DWT_CID3;       /**< Offset: 0xFFC (R/    8) Component ID Register 3 */
} ArmDwt;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_ARM_DWT_COMPONENT_ */
