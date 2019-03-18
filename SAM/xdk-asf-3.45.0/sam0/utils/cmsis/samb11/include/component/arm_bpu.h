/**
 * \file
 *
 * \brief Component description for ARM_BPU
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

#ifndef _SAMB11_ARM_BPU_COMPONENT_
#define _SAMB11_ARM_BPU_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR ARM_BPU */
/* ========================================================================== */
/** \addtogroup SAMB11_ARM_BPU ARM Breakpoint Control 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define ARM_BPU_ABP1234
#define REV_ARM_BPU                      0x100

/* -------- ARM_BPU_BP_CTRL : (ARM_BPU Offset: 0x00) (R/W 8) Break Point Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ENABLE:1;                  /**< bit:      0  BPU is Enabled                           */
    uint8_t  KEY:1;                     /**< bit:      1  Must Write this bit to a 1 for register write to be accepted */
    uint8_t  :2;                        /**< bit:   2..3  Reserved */
    uint8_t  NUM_CODE:4;                /**< bit:   4..7  Number of breakpoint comparators         */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_BPU_BP_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_CTRL_OFFSET              0x00                                          /**<  (ARM_BPU_BP_CTRL) Break Point Control Register  Offset */
#define ARM_BPU_BP_CTRL_RESETVALUE          0x00u                                         /**<  (ARM_BPU_BP_CTRL) Break Point Control Register  Reset Value */

#define ARM_BPU_BP_CTRL_ENABLE_Pos          0                                              /**< (ARM_BPU_BP_CTRL) BPU is Enabled Position */
#define ARM_BPU_BP_CTRL_ENABLE_Msk          (0x1u << ARM_BPU_BP_CTRL_ENABLE_Pos)           /**< (ARM_BPU_BP_CTRL) BPU is Enabled Mask */
#define ARM_BPU_BP_CTRL_ENABLE              ARM_BPU_BP_CTRL_ENABLE_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use ARM_BPU_BP_CTRL_ENABLE_Msk instead */
#define ARM_BPU_BP_CTRL_KEY_Pos             1                                              /**< (ARM_BPU_BP_CTRL) Must Write this bit to a 1 for register write to be accepted Position */
#define ARM_BPU_BP_CTRL_KEY_Msk             (0x1u << ARM_BPU_BP_CTRL_KEY_Pos)              /**< (ARM_BPU_BP_CTRL) Must Write this bit to a 1 for register write to be accepted Mask */
#define ARM_BPU_BP_CTRL_KEY                 ARM_BPU_BP_CTRL_KEY_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use ARM_BPU_BP_CTRL_KEY_Msk instead */
#define ARM_BPU_BP_CTRL_NUM_CODE_Pos        4                                              /**< (ARM_BPU_BP_CTRL) Number of breakpoint comparators Position */
#define ARM_BPU_BP_CTRL_NUM_CODE_Msk        (0xFu << ARM_BPU_BP_CTRL_NUM_CODE_Pos)         /**< (ARM_BPU_BP_CTRL) Number of breakpoint comparators Mask */
#define ARM_BPU_BP_CTRL_NUM_CODE(value)     (ARM_BPU_BP_CTRL_NUM_CODE_Msk & ((value) << ARM_BPU_BP_CTRL_NUM_CODE_Pos))
#define ARM_BPU_BP_CTRL_MASK                0xF3u                                          /**< \deprecated (ARM_BPU_BP_CTRL) Register MASK  (Use ARM_BPU_BP_CTRL_Msk instead)  */
#define ARM_BPU_BP_CTRL_Msk                 0xF3u                                          /**< (ARM_BPU_BP_CTRL) Register Mask  */

/* -------- ARM_BPU_BP_COMP0 : (ARM_BPU Offset: 0x08) (R/W 32) Break Point Compare Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t ENABLE:1;                  /**< bit:      0  Comparator is enabled                    */
    uint32_t :1;                        /**< bit:      1  Reserved */
    uint32_t COMP:27;                   /**< bit:  2..28  Bits 28:2 of the comparison address      */
    uint32_t :1;                        /**< bit:     29  Reserved */
    uint32_t BP_MATCH:2;                /**< bit: 30..31  Behavior when the COMP address is matched */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} ARM_BPU_BP_COMP0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_COMP0_OFFSET             0x08                                          /**<  (ARM_BPU_BP_COMP0) Break Point Compare Register 0  Offset */
#define ARM_BPU_BP_COMP0_RESETVALUE         0x1FFFFFFFu                                   /**<  (ARM_BPU_BP_COMP0) Break Point Compare Register 0  Reset Value */

#define ARM_BPU_BP_COMP0_ENABLE_Pos         0                                              /**< (ARM_BPU_BP_COMP0) Comparator is enabled Position */
#define ARM_BPU_BP_COMP0_ENABLE_Msk         (0x1u << ARM_BPU_BP_COMP0_ENABLE_Pos)          /**< (ARM_BPU_BP_COMP0) Comparator is enabled Mask */
#define ARM_BPU_BP_COMP0_ENABLE             ARM_BPU_BP_COMP0_ENABLE_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use ARM_BPU_BP_COMP0_ENABLE_Msk instead */
#define ARM_BPU_BP_COMP0_COMP_Pos           2                                              /**< (ARM_BPU_BP_COMP0) Bits 28:2 of the comparison address Position */
#define ARM_BPU_BP_COMP0_COMP_Msk           (0x7FFFFFFu << ARM_BPU_BP_COMP0_COMP_Pos)      /**< (ARM_BPU_BP_COMP0) Bits 28:2 of the comparison address Mask */
#define ARM_BPU_BP_COMP0_COMP(value)        (ARM_BPU_BP_COMP0_COMP_Msk & ((value) << ARM_BPU_BP_COMP0_COMP_Pos))
#define ARM_BPU_BP_COMP0_BP_MATCH_Pos       30                                             /**< (ARM_BPU_BP_COMP0) Behavior when the COMP address is matched Position */
#define ARM_BPU_BP_COMP0_BP_MATCH_Msk       (0x3u << ARM_BPU_BP_COMP0_BP_MATCH_Pos)        /**< (ARM_BPU_BP_COMP0) Behavior when the COMP address is matched Mask */
#define ARM_BPU_BP_COMP0_BP_MATCH(value)    (ARM_BPU_BP_COMP0_BP_MATCH_Msk & ((value) << ARM_BPU_BP_COMP0_BP_MATCH_Pos))
#define   ARM_BPU_BP_COMP0_BP_MATCH_0_Val   0x0u                                           /**< (ARM_BPU_BP_COMP0) No Breakpoint Matching  */
#define   ARM_BPU_BP_COMP0_BP_MATCH_1_Val   0x1u                                           /**< (ARM_BPU_BP_COMP0) Breakpoint on lower halfword  */
#define   ARM_BPU_BP_COMP0_BP_MATCH_2_Val   0x2u                                           /**< (ARM_BPU_BP_COMP0) Breakpoint on upper halfword  */
#define   ARM_BPU_BP_COMP0_BP_MATCH_3_Val   0x3u                                           /**< (ARM_BPU_BP_COMP0) Breakpoint on both halfwords  */
#define ARM_BPU_BP_COMP0_BP_MATCH_0         (ARM_BPU_BP_COMP0_BP_MATCH_0_Val << ARM_BPU_BP_COMP0_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP0) No Breakpoint Matching Position  */
#define ARM_BPU_BP_COMP0_BP_MATCH_1         (ARM_BPU_BP_COMP0_BP_MATCH_1_Val << ARM_BPU_BP_COMP0_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP0) Breakpoint on lower halfword Position  */
#define ARM_BPU_BP_COMP0_BP_MATCH_2         (ARM_BPU_BP_COMP0_BP_MATCH_2_Val << ARM_BPU_BP_COMP0_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP0) Breakpoint on upper halfword Position  */
#define ARM_BPU_BP_COMP0_BP_MATCH_3         (ARM_BPU_BP_COMP0_BP_MATCH_3_Val << ARM_BPU_BP_COMP0_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP0) Breakpoint on both halfwords Position  */
#define ARM_BPU_BP_COMP0_MASK               0xDFFFFFFDu                                    /**< \deprecated (ARM_BPU_BP_COMP0) Register MASK  (Use ARM_BPU_BP_COMP0_Msk instead)  */
#define ARM_BPU_BP_COMP0_Msk                0xDFFFFFFDu                                    /**< (ARM_BPU_BP_COMP0) Register Mask  */

/* -------- ARM_BPU_BP_COMP1 : (ARM_BPU Offset: 0x0c) (R/W 32) Break Point Compare Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t ENABLE:1;                  /**< bit:      0  Comparator is enabled                    */
    uint32_t :1;                        /**< bit:      1  Reserved */
    uint32_t COMP:27;                   /**< bit:  2..28  Bits 28:2 of the comparison address      */
    uint32_t :1;                        /**< bit:     29  Reserved */
    uint32_t BP_MATCH:2;                /**< bit: 30..31  Behavior when the COMP address is matched */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} ARM_BPU_BP_COMP1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_COMP1_OFFSET             0x0C                                          /**<  (ARM_BPU_BP_COMP1) Break Point Compare Register 1  Offset */
#define ARM_BPU_BP_COMP1_RESETVALUE         0x1FFFFFFFu                                   /**<  (ARM_BPU_BP_COMP1) Break Point Compare Register 1  Reset Value */

#define ARM_BPU_BP_COMP1_ENABLE_Pos         0                                              /**< (ARM_BPU_BP_COMP1) Comparator is enabled Position */
#define ARM_BPU_BP_COMP1_ENABLE_Msk         (0x1u << ARM_BPU_BP_COMP1_ENABLE_Pos)          /**< (ARM_BPU_BP_COMP1) Comparator is enabled Mask */
#define ARM_BPU_BP_COMP1_ENABLE             ARM_BPU_BP_COMP1_ENABLE_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use ARM_BPU_BP_COMP1_ENABLE_Msk instead */
#define ARM_BPU_BP_COMP1_COMP_Pos           2                                              /**< (ARM_BPU_BP_COMP1) Bits 28:2 of the comparison address Position */
#define ARM_BPU_BP_COMP1_COMP_Msk           (0x7FFFFFFu << ARM_BPU_BP_COMP1_COMP_Pos)      /**< (ARM_BPU_BP_COMP1) Bits 28:2 of the comparison address Mask */
#define ARM_BPU_BP_COMP1_COMP(value)        (ARM_BPU_BP_COMP1_COMP_Msk & ((value) << ARM_BPU_BP_COMP1_COMP_Pos))
#define ARM_BPU_BP_COMP1_BP_MATCH_Pos       30                                             /**< (ARM_BPU_BP_COMP1) Behavior when the COMP address is matched Position */
#define ARM_BPU_BP_COMP1_BP_MATCH_Msk       (0x3u << ARM_BPU_BP_COMP1_BP_MATCH_Pos)        /**< (ARM_BPU_BP_COMP1) Behavior when the COMP address is matched Mask */
#define ARM_BPU_BP_COMP1_BP_MATCH(value)    (ARM_BPU_BP_COMP1_BP_MATCH_Msk & ((value) << ARM_BPU_BP_COMP1_BP_MATCH_Pos))
#define   ARM_BPU_BP_COMP1_BP_MATCH_0_Val   0x0u                                           /**< (ARM_BPU_BP_COMP1) No Breakpoint Matching  */
#define   ARM_BPU_BP_COMP1_BP_MATCH_1_Val   0x1u                                           /**< (ARM_BPU_BP_COMP1) Breakpoint on lower halfword  */
#define   ARM_BPU_BP_COMP1_BP_MATCH_2_Val   0x2u                                           /**< (ARM_BPU_BP_COMP1) Breakpoint on upper halfword  */
#define   ARM_BPU_BP_COMP1_BP_MATCH_3_Val   0x3u                                           /**< (ARM_BPU_BP_COMP1) Breakpoint on both halfwords  */
#define ARM_BPU_BP_COMP1_BP_MATCH_0         (ARM_BPU_BP_COMP1_BP_MATCH_0_Val << ARM_BPU_BP_COMP1_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP1) No Breakpoint Matching Position  */
#define ARM_BPU_BP_COMP1_BP_MATCH_1         (ARM_BPU_BP_COMP1_BP_MATCH_1_Val << ARM_BPU_BP_COMP1_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP1) Breakpoint on lower halfword Position  */
#define ARM_BPU_BP_COMP1_BP_MATCH_2         (ARM_BPU_BP_COMP1_BP_MATCH_2_Val << ARM_BPU_BP_COMP1_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP1) Breakpoint on upper halfword Position  */
#define ARM_BPU_BP_COMP1_BP_MATCH_3         (ARM_BPU_BP_COMP1_BP_MATCH_3_Val << ARM_BPU_BP_COMP1_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP1) Breakpoint on both halfwords Position  */
#define ARM_BPU_BP_COMP1_MASK               0xDFFFFFFDu                                    /**< \deprecated (ARM_BPU_BP_COMP1) Register MASK  (Use ARM_BPU_BP_COMP1_Msk instead)  */
#define ARM_BPU_BP_COMP1_Msk                0xDFFFFFFDu                                    /**< (ARM_BPU_BP_COMP1) Register Mask  */

/* -------- ARM_BPU_BP_COMP2 : (ARM_BPU Offset: 0x10) (R/W 32) Break Point Compare Register 2 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t ENABLE:1;                  /**< bit:      0  Comparator is enabled                    */
    uint32_t :1;                        /**< bit:      1  Reserved */
    uint32_t COMP:27;                   /**< bit:  2..28  Bits 28:2 of the comparison address      */
    uint32_t :1;                        /**< bit:     29  Reserved */
    uint32_t BP_MATCH:2;                /**< bit: 30..31  Behavior when the COMP address is matched */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} ARM_BPU_BP_COMP2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_COMP2_OFFSET             0x10                                          /**<  (ARM_BPU_BP_COMP2) Break Point Compare Register 2  Offset */
#define ARM_BPU_BP_COMP2_RESETVALUE         0x1FFFFFFFu                                   /**<  (ARM_BPU_BP_COMP2) Break Point Compare Register 2  Reset Value */

#define ARM_BPU_BP_COMP2_ENABLE_Pos         0                                              /**< (ARM_BPU_BP_COMP2) Comparator is enabled Position */
#define ARM_BPU_BP_COMP2_ENABLE_Msk         (0x1u << ARM_BPU_BP_COMP2_ENABLE_Pos)          /**< (ARM_BPU_BP_COMP2) Comparator is enabled Mask */
#define ARM_BPU_BP_COMP2_ENABLE             ARM_BPU_BP_COMP2_ENABLE_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use ARM_BPU_BP_COMP2_ENABLE_Msk instead */
#define ARM_BPU_BP_COMP2_COMP_Pos           2                                              /**< (ARM_BPU_BP_COMP2) Bits 28:2 of the comparison address Position */
#define ARM_BPU_BP_COMP2_COMP_Msk           (0x7FFFFFFu << ARM_BPU_BP_COMP2_COMP_Pos)      /**< (ARM_BPU_BP_COMP2) Bits 28:2 of the comparison address Mask */
#define ARM_BPU_BP_COMP2_COMP(value)        (ARM_BPU_BP_COMP2_COMP_Msk & ((value) << ARM_BPU_BP_COMP2_COMP_Pos))
#define ARM_BPU_BP_COMP2_BP_MATCH_Pos       30                                             /**< (ARM_BPU_BP_COMP2) Behavior when the COMP address is matched Position */
#define ARM_BPU_BP_COMP2_BP_MATCH_Msk       (0x3u << ARM_BPU_BP_COMP2_BP_MATCH_Pos)        /**< (ARM_BPU_BP_COMP2) Behavior when the COMP address is matched Mask */
#define ARM_BPU_BP_COMP2_BP_MATCH(value)    (ARM_BPU_BP_COMP2_BP_MATCH_Msk & ((value) << ARM_BPU_BP_COMP2_BP_MATCH_Pos))
#define   ARM_BPU_BP_COMP2_BP_MATCH_0_Val   0x0u                                           /**< (ARM_BPU_BP_COMP2) No Breakpoint Matching  */
#define   ARM_BPU_BP_COMP2_BP_MATCH_1_Val   0x1u                                           /**< (ARM_BPU_BP_COMP2) Breakpoint on lower halfword  */
#define   ARM_BPU_BP_COMP2_BP_MATCH_2_Val   0x2u                                           /**< (ARM_BPU_BP_COMP2) Breakpoint on upper halfword  */
#define   ARM_BPU_BP_COMP2_BP_MATCH_3_Val   0x3u                                           /**< (ARM_BPU_BP_COMP2) Breakpoint on both halfwords  */
#define ARM_BPU_BP_COMP2_BP_MATCH_0         (ARM_BPU_BP_COMP2_BP_MATCH_0_Val << ARM_BPU_BP_COMP2_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP2) No Breakpoint Matching Position  */
#define ARM_BPU_BP_COMP2_BP_MATCH_1         (ARM_BPU_BP_COMP2_BP_MATCH_1_Val << ARM_BPU_BP_COMP2_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP2) Breakpoint on lower halfword Position  */
#define ARM_BPU_BP_COMP2_BP_MATCH_2         (ARM_BPU_BP_COMP2_BP_MATCH_2_Val << ARM_BPU_BP_COMP2_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP2) Breakpoint on upper halfword Position  */
#define ARM_BPU_BP_COMP2_BP_MATCH_3         (ARM_BPU_BP_COMP2_BP_MATCH_3_Val << ARM_BPU_BP_COMP2_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP2) Breakpoint on both halfwords Position  */
#define ARM_BPU_BP_COMP2_MASK               0xDFFFFFFDu                                    /**< \deprecated (ARM_BPU_BP_COMP2) Register MASK  (Use ARM_BPU_BP_COMP2_Msk instead)  */
#define ARM_BPU_BP_COMP2_Msk                0xDFFFFFFDu                                    /**< (ARM_BPU_BP_COMP2) Register Mask  */

/* -------- ARM_BPU_BP_COMP3 : (ARM_BPU Offset: 0x14) (R/W 32) Break Point Compare Register 3 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t ENABLE:1;                  /**< bit:      0  Comparator is enabled                    */
    uint32_t :1;                        /**< bit:      1  Reserved */
    uint32_t COMP:27;                   /**< bit:  2..28  Bits 28:2 of the comparison address      */
    uint32_t :1;                        /**< bit:     29  Reserved */
    uint32_t BP_MATCH:2;                /**< bit: 30..31  Behavior when the COMP address is matched */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} ARM_BPU_BP_COMP3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_COMP3_OFFSET             0x14                                          /**<  (ARM_BPU_BP_COMP3) Break Point Compare Register 3  Offset */
#define ARM_BPU_BP_COMP3_RESETVALUE         0x1FFFFFFFu                                   /**<  (ARM_BPU_BP_COMP3) Break Point Compare Register 3  Reset Value */

#define ARM_BPU_BP_COMP3_ENABLE_Pos         0                                              /**< (ARM_BPU_BP_COMP3) Comparator is enabled Position */
#define ARM_BPU_BP_COMP3_ENABLE_Msk         (0x1u << ARM_BPU_BP_COMP3_ENABLE_Pos)          /**< (ARM_BPU_BP_COMP3) Comparator is enabled Mask */
#define ARM_BPU_BP_COMP3_ENABLE             ARM_BPU_BP_COMP3_ENABLE_Msk                    /**< \deprecated Old style mask definition for 1 bit bitfield. Use ARM_BPU_BP_COMP3_ENABLE_Msk instead */
#define ARM_BPU_BP_COMP3_COMP_Pos           2                                              /**< (ARM_BPU_BP_COMP3) Bits 28:2 of the comparison address Position */
#define ARM_BPU_BP_COMP3_COMP_Msk           (0x7FFFFFFu << ARM_BPU_BP_COMP3_COMP_Pos)      /**< (ARM_BPU_BP_COMP3) Bits 28:2 of the comparison address Mask */
#define ARM_BPU_BP_COMP3_COMP(value)        (ARM_BPU_BP_COMP3_COMP_Msk & ((value) << ARM_BPU_BP_COMP3_COMP_Pos))
#define ARM_BPU_BP_COMP3_BP_MATCH_Pos       30                                             /**< (ARM_BPU_BP_COMP3) Behavior when the COMP address is matched Position */
#define ARM_BPU_BP_COMP3_BP_MATCH_Msk       (0x3u << ARM_BPU_BP_COMP3_BP_MATCH_Pos)        /**< (ARM_BPU_BP_COMP3) Behavior when the COMP address is matched Mask */
#define ARM_BPU_BP_COMP3_BP_MATCH(value)    (ARM_BPU_BP_COMP3_BP_MATCH_Msk & ((value) << ARM_BPU_BP_COMP3_BP_MATCH_Pos))
#define   ARM_BPU_BP_COMP3_BP_MATCH_0_Val   0x0u                                           /**< (ARM_BPU_BP_COMP3) No Breakpoint Matching  */
#define   ARM_BPU_BP_COMP3_BP_MATCH_1_Val   0x1u                                           /**< (ARM_BPU_BP_COMP3) Breakpoint on lower halfword  */
#define   ARM_BPU_BP_COMP3_BP_MATCH_2_Val   0x2u                                           /**< (ARM_BPU_BP_COMP3) Breakpoint on upper halfword  */
#define   ARM_BPU_BP_COMP3_BP_MATCH_3_Val   0x3u                                           /**< (ARM_BPU_BP_COMP3) Breakpoint on both halfwords  */
#define ARM_BPU_BP_COMP3_BP_MATCH_0         (ARM_BPU_BP_COMP3_BP_MATCH_0_Val << ARM_BPU_BP_COMP3_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP3) No Breakpoint Matching Position  */
#define ARM_BPU_BP_COMP3_BP_MATCH_1         (ARM_BPU_BP_COMP3_BP_MATCH_1_Val << ARM_BPU_BP_COMP3_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP3) Breakpoint on lower halfword Position  */
#define ARM_BPU_BP_COMP3_BP_MATCH_2         (ARM_BPU_BP_COMP3_BP_MATCH_2_Val << ARM_BPU_BP_COMP3_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP3) Breakpoint on upper halfword Position  */
#define ARM_BPU_BP_COMP3_BP_MATCH_3         (ARM_BPU_BP_COMP3_BP_MATCH_3_Val << ARM_BPU_BP_COMP3_BP_MATCH_Pos)  /**< (ARM_BPU_BP_COMP3) Breakpoint on both halfwords Position  */
#define ARM_BPU_BP_COMP3_MASK               0xDFFFFFFDu                                    /**< \deprecated (ARM_BPU_BP_COMP3) Register MASK  (Use ARM_BPU_BP_COMP3_Msk instead)  */
#define ARM_BPU_BP_COMP3_Msk                0xDFFFFFFDu                                    /**< (ARM_BPU_BP_COMP3) Register Mask  */

/* -------- ARM_BPU_BP_PID4 : (ARM_BPU Offset: 0xfd0) (R/ 8) Peripheral ID Register 4 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  JEP106_C_CODE:4;           /**< bit:   0..3  JEP106 C Code                            */
    uint8_t  BLOCK_COUNT:4;             /**< bit:   4..7  Block Count                              */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_BPU_BP_PID4_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_PID4_OFFSET              0xFD0                                         /**<  (ARM_BPU_BP_PID4) Peripheral ID Register 4  Offset */
#define ARM_BPU_BP_PID4_RESETVALUE          0x04u                                         /**<  (ARM_BPU_BP_PID4) Peripheral ID Register 4  Reset Value */

#define ARM_BPU_BP_PID4_JEP106_C_CODE_Pos   0                                              /**< (ARM_BPU_BP_PID4) JEP106 C Code Position */
#define ARM_BPU_BP_PID4_JEP106_C_CODE_Msk   (0xFu << ARM_BPU_BP_PID4_JEP106_C_CODE_Pos)    /**< (ARM_BPU_BP_PID4) JEP106 C Code Mask */
#define ARM_BPU_BP_PID4_JEP106_C_CODE(value) (ARM_BPU_BP_PID4_JEP106_C_CODE_Msk & ((value) << ARM_BPU_BP_PID4_JEP106_C_CODE_Pos))
#define ARM_BPU_BP_PID4_BLOCK_COUNT_Pos     4                                              /**< (ARM_BPU_BP_PID4) Block Count Position */
#define ARM_BPU_BP_PID4_BLOCK_COUNT_Msk     (0xFu << ARM_BPU_BP_PID4_BLOCK_COUNT_Pos)      /**< (ARM_BPU_BP_PID4) Block Count Mask */
#define ARM_BPU_BP_PID4_BLOCK_COUNT(value)  (ARM_BPU_BP_PID4_BLOCK_COUNT_Msk & ((value) << ARM_BPU_BP_PID4_BLOCK_COUNT_Pos))
#define ARM_BPU_BP_PID4_MASK                0xFFu                                          /**< \deprecated (ARM_BPU_BP_PID4) Register MASK  (Use ARM_BPU_BP_PID4_Msk instead)  */
#define ARM_BPU_BP_PID4_Msk                 0xFFu                                          /**< (ARM_BPU_BP_PID4) Register Mask  */

/* -------- ARM_BPU_BP_PID0 : (ARM_BPU Offset: 0xfe0) (R/ 8) Peripheral ID Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PART_NUMBER:8;             /**< bit:   0..7  Part Number Bits 7:0                     */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_BPU_BP_PID0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_PID0_OFFSET              0xFE0                                         /**<  (ARM_BPU_BP_PID0) Peripheral ID Register 0  Offset */
#define ARM_BPU_BP_PID0_RESETVALUE          0x0Bu                                         /**<  (ARM_BPU_BP_PID0) Peripheral ID Register 0  Reset Value */

#define ARM_BPU_BP_PID0_PART_NUMBER_Pos     0                                              /**< (ARM_BPU_BP_PID0) Part Number Bits 7:0 Position */
#define ARM_BPU_BP_PID0_PART_NUMBER_Msk     (0xFFu << ARM_BPU_BP_PID0_PART_NUMBER_Pos)     /**< (ARM_BPU_BP_PID0) Part Number Bits 7:0 Mask */
#define ARM_BPU_BP_PID0_PART_NUMBER(value)  (ARM_BPU_BP_PID0_PART_NUMBER_Msk & ((value) << ARM_BPU_BP_PID0_PART_NUMBER_Pos))
#define ARM_BPU_BP_PID0_MASK                0xFFu                                          /**< \deprecated (ARM_BPU_BP_PID0) Register MASK  (Use ARM_BPU_BP_PID0_Msk instead)  */
#define ARM_BPU_BP_PID0_Msk                 0xFFu                                          /**< (ARM_BPU_BP_PID0) Register Mask  */

/* -------- ARM_BPU_BP_PID1 : (ARM_BPU Offset: 0xfe4) (R/ 8) Peripheral ID Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PART_NUMBER:4;             /**< bit:   0..3  Part Number Bits 11:8                    */
    uint8_t  JEP106_ID_3_0:4;           /**< bit:   4..7  JEP106 ID Code Bits 3:0                  */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_BPU_BP_PID1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_PID1_OFFSET              0xFE4                                         /**<  (ARM_BPU_BP_PID1) Peripheral ID Register 1  Offset */
#define ARM_BPU_BP_PID1_RESETVALUE          0xB0u                                         /**<  (ARM_BPU_BP_PID1) Peripheral ID Register 1  Reset Value */

#define ARM_BPU_BP_PID1_PART_NUMBER_Pos     0                                              /**< (ARM_BPU_BP_PID1) Part Number Bits 11:8 Position */
#define ARM_BPU_BP_PID1_PART_NUMBER_Msk     (0xFu << ARM_BPU_BP_PID1_PART_NUMBER_Pos)      /**< (ARM_BPU_BP_PID1) Part Number Bits 11:8 Mask */
#define ARM_BPU_BP_PID1_PART_NUMBER(value)  (ARM_BPU_BP_PID1_PART_NUMBER_Msk & ((value) << ARM_BPU_BP_PID1_PART_NUMBER_Pos))
#define ARM_BPU_BP_PID1_JEP106_ID_3_0_Pos   4                                              /**< (ARM_BPU_BP_PID1) JEP106 ID Code Bits 3:0 Position */
#define ARM_BPU_BP_PID1_JEP106_ID_3_0_Msk   (0xFu << ARM_BPU_BP_PID1_JEP106_ID_3_0_Pos)    /**< (ARM_BPU_BP_PID1) JEP106 ID Code Bits 3:0 Mask */
#define ARM_BPU_BP_PID1_JEP106_ID_3_0(value) (ARM_BPU_BP_PID1_JEP106_ID_3_0_Msk & ((value) << ARM_BPU_BP_PID1_JEP106_ID_3_0_Pos))
#define ARM_BPU_BP_PID1_MASK                0xFFu                                          /**< \deprecated (ARM_BPU_BP_PID1) Register MASK  (Use ARM_BPU_BP_PID1_Msk instead)  */
#define ARM_BPU_BP_PID1_Msk                 0xFFu                                          /**< (ARM_BPU_BP_PID1) Register Mask  */

/* -------- ARM_BPU_BP_PID2 : (ARM_BPU Offset: 0xfe8) (R/ 8) Peripheral ID Register 2 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  JEP106_ID_6_4:3;           /**< bit:   0..2  JEP106 ID Code Bits 6:4                  */
    uint8_t  JEDEC_USED:1;              /**< bit:      3  JEDEC Used                               */
    uint8_t  REVISION:4;                /**< bit:   4..7  Revision                                 */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_BPU_BP_PID2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_PID2_OFFSET              0xFE8                                         /**<  (ARM_BPU_BP_PID2) Peripheral ID Register 2  Offset */
#define ARM_BPU_BP_PID2_RESETVALUE          0x0Bu                                         /**<  (ARM_BPU_BP_PID2) Peripheral ID Register 2  Reset Value */

#define ARM_BPU_BP_PID2_JEP106_ID_6_4_Pos   0                                              /**< (ARM_BPU_BP_PID2) JEP106 ID Code Bits 6:4 Position */
#define ARM_BPU_BP_PID2_JEP106_ID_6_4_Msk   (0x7u << ARM_BPU_BP_PID2_JEP106_ID_6_4_Pos)    /**< (ARM_BPU_BP_PID2) JEP106 ID Code Bits 6:4 Mask */
#define ARM_BPU_BP_PID2_JEP106_ID_6_4(value) (ARM_BPU_BP_PID2_JEP106_ID_6_4_Msk & ((value) << ARM_BPU_BP_PID2_JEP106_ID_6_4_Pos))
#define ARM_BPU_BP_PID2_JEDEC_USED_Pos      3                                              /**< (ARM_BPU_BP_PID2) JEDEC Used Position */
#define ARM_BPU_BP_PID2_JEDEC_USED_Msk      (0x1u << ARM_BPU_BP_PID2_JEDEC_USED_Pos)       /**< (ARM_BPU_BP_PID2) JEDEC Used Mask */
#define ARM_BPU_BP_PID2_JEDEC_USED          ARM_BPU_BP_PID2_JEDEC_USED_Msk                 /**< \deprecated Old style mask definition for 1 bit bitfield. Use ARM_BPU_BP_PID2_JEDEC_USED_Msk instead */
#define ARM_BPU_BP_PID2_REVISION_Pos        4                                              /**< (ARM_BPU_BP_PID2) Revision Position */
#define ARM_BPU_BP_PID2_REVISION_Msk        (0xFu << ARM_BPU_BP_PID2_REVISION_Pos)         /**< (ARM_BPU_BP_PID2) Revision Mask */
#define ARM_BPU_BP_PID2_REVISION(value)     (ARM_BPU_BP_PID2_REVISION_Msk & ((value) << ARM_BPU_BP_PID2_REVISION_Pos))
#define ARM_BPU_BP_PID2_MASK                0xFFu                                          /**< \deprecated (ARM_BPU_BP_PID2) Register MASK  (Use ARM_BPU_BP_PID2_Msk instead)  */
#define ARM_BPU_BP_PID2_Msk                 0xFFu                                          /**< (ARM_BPU_BP_PID2) Register Mask  */

/* -------- ARM_BPU_BP_PID3 : (ARM_BPU Offset: 0xfec) (R/ 8) Peripheral ID Register 3 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CUSTOMER_MOD_NUMBER:4;     /**< bit:   0..3  Customer Modification Number             */
    uint8_t  ECO_REV_NUMBER:4;          /**< bit:   4..7  ECO Revision Number                      */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_BPU_BP_PID3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_PID3_OFFSET              0xFEC                                         /**<  (ARM_BPU_BP_PID3) Peripheral ID Register 3  Offset */
#define ARM_BPU_BP_PID3_RESETVALUE          0x00u                                         /**<  (ARM_BPU_BP_PID3) Peripheral ID Register 3  Reset Value */

#define ARM_BPU_BP_PID3_CUSTOMER_MOD_NUMBER_Pos 0                                              /**< (ARM_BPU_BP_PID3) Customer Modification Number Position */
#define ARM_BPU_BP_PID3_CUSTOMER_MOD_NUMBER_Msk (0xFu << ARM_BPU_BP_PID3_CUSTOMER_MOD_NUMBER_Pos)  /**< (ARM_BPU_BP_PID3) Customer Modification Number Mask */
#define ARM_BPU_BP_PID3_CUSTOMER_MOD_NUMBER(value) (ARM_BPU_BP_PID3_CUSTOMER_MOD_NUMBER_Msk & ((value) << ARM_BPU_BP_PID3_CUSTOMER_MOD_NUMBER_Pos))
#define ARM_BPU_BP_PID3_ECO_REV_NUMBER_Pos  4                                              /**< (ARM_BPU_BP_PID3) ECO Revision Number Position */
#define ARM_BPU_BP_PID3_ECO_REV_NUMBER_Msk  (0xFu << ARM_BPU_BP_PID3_ECO_REV_NUMBER_Pos)   /**< (ARM_BPU_BP_PID3) ECO Revision Number Mask */
#define ARM_BPU_BP_PID3_ECO_REV_NUMBER(value) (ARM_BPU_BP_PID3_ECO_REV_NUMBER_Msk & ((value) << ARM_BPU_BP_PID3_ECO_REV_NUMBER_Pos))
#define ARM_BPU_BP_PID3_MASK                0xFFu                                          /**< \deprecated (ARM_BPU_BP_PID3) Register MASK  (Use ARM_BPU_BP_PID3_Msk instead)  */
#define ARM_BPU_BP_PID3_Msk                 0xFFu                                          /**< (ARM_BPU_BP_PID3) Register Mask  */

/* -------- ARM_BPU_BP_CID0 : (ARM_BPU Offset: 0xff0) (R/ 8) Component ID Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  BP_CID0:8;                 /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_BPU_BP_CID0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_CID0_OFFSET              0xFF0                                         /**<  (ARM_BPU_BP_CID0) Component ID Register 0  Offset */
#define ARM_BPU_BP_CID0_RESETVALUE          0x0Du                                         /**<  (ARM_BPU_BP_CID0) Component ID Register 0  Reset Value */

#define ARM_BPU_BP_CID0_BP_CID0_Pos         0                                              /**< (ARM_BPU_BP_CID0)  Position */
#define ARM_BPU_BP_CID0_BP_CID0_Msk         (0xFFu << ARM_BPU_BP_CID0_BP_CID0_Pos)         /**< (ARM_BPU_BP_CID0)  Mask */
#define ARM_BPU_BP_CID0_BP_CID0(value)      (ARM_BPU_BP_CID0_BP_CID0_Msk & ((value) << ARM_BPU_BP_CID0_BP_CID0_Pos))
#define ARM_BPU_BP_CID0_MASK                0xFFu                                          /**< \deprecated (ARM_BPU_BP_CID0) Register MASK  (Use ARM_BPU_BP_CID0_Msk instead)  */
#define ARM_BPU_BP_CID0_Msk                 0xFFu                                          /**< (ARM_BPU_BP_CID0) Register Mask  */

/* -------- ARM_BPU_BP_CID1 : (ARM_BPU Offset: 0xff4) (R/ 8) Component ID Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  BP_CID1:8;                 /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_BPU_BP_CID1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_CID1_OFFSET              0xFF4                                         /**<  (ARM_BPU_BP_CID1) Component ID Register 1  Offset */
#define ARM_BPU_BP_CID1_RESETVALUE          0xE0u                                         /**<  (ARM_BPU_BP_CID1) Component ID Register 1  Reset Value */

#define ARM_BPU_BP_CID1_BP_CID1_Pos         0                                              /**< (ARM_BPU_BP_CID1)  Position */
#define ARM_BPU_BP_CID1_BP_CID1_Msk         (0xFFu << ARM_BPU_BP_CID1_BP_CID1_Pos)         /**< (ARM_BPU_BP_CID1)  Mask */
#define ARM_BPU_BP_CID1_BP_CID1(value)      (ARM_BPU_BP_CID1_BP_CID1_Msk & ((value) << ARM_BPU_BP_CID1_BP_CID1_Pos))
#define ARM_BPU_BP_CID1_MASK                0xFFu                                          /**< \deprecated (ARM_BPU_BP_CID1) Register MASK  (Use ARM_BPU_BP_CID1_Msk instead)  */
#define ARM_BPU_BP_CID1_Msk                 0xFFu                                          /**< (ARM_BPU_BP_CID1) Register Mask  */

/* -------- ARM_BPU_BP_CID2 : (ARM_BPU Offset: 0xff8) (R/ 8) Component ID Register 2 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  BP_CID2:8;                 /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_BPU_BP_CID2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_CID2_OFFSET              0xFF8                                         /**<  (ARM_BPU_BP_CID2) Component ID Register 2  Offset */
#define ARM_BPU_BP_CID2_RESETVALUE          0x05u                                         /**<  (ARM_BPU_BP_CID2) Component ID Register 2  Reset Value */

#define ARM_BPU_BP_CID2_BP_CID2_Pos         0                                              /**< (ARM_BPU_BP_CID2)  Position */
#define ARM_BPU_BP_CID2_BP_CID2_Msk         (0xFFu << ARM_BPU_BP_CID2_BP_CID2_Pos)         /**< (ARM_BPU_BP_CID2)  Mask */
#define ARM_BPU_BP_CID2_BP_CID2(value)      (ARM_BPU_BP_CID2_BP_CID2_Msk & ((value) << ARM_BPU_BP_CID2_BP_CID2_Pos))
#define ARM_BPU_BP_CID2_MASK                0xFFu                                          /**< \deprecated (ARM_BPU_BP_CID2) Register MASK  (Use ARM_BPU_BP_CID2_Msk instead)  */
#define ARM_BPU_BP_CID2_Msk                 0xFFu                                          /**< (ARM_BPU_BP_CID2) Register Mask  */

/* -------- ARM_BPU_BP_CID3 : (ARM_BPU Offset: 0xffc) (R/ 8) Component ID Register 3 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  BP_CID3:8;                 /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} ARM_BPU_BP_CID3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define ARM_BPU_BP_CID3_OFFSET              0xFFC                                         /**<  (ARM_BPU_BP_CID3) Component ID Register 3  Offset */
#define ARM_BPU_BP_CID3_RESETVALUE          0xB1u                                         /**<  (ARM_BPU_BP_CID3) Component ID Register 3  Reset Value */

#define ARM_BPU_BP_CID3_BP_CID3_Pos         0                                              /**< (ARM_BPU_BP_CID3)  Position */
#define ARM_BPU_BP_CID3_BP_CID3_Msk         (0xFFu << ARM_BPU_BP_CID3_BP_CID3_Pos)         /**< (ARM_BPU_BP_CID3)  Mask */
#define ARM_BPU_BP_CID3_BP_CID3(value)      (ARM_BPU_BP_CID3_BP_CID3_Msk & ((value) << ARM_BPU_BP_CID3_BP_CID3_Pos))
#define ARM_BPU_BP_CID3_MASK                0xFFu                                          /**< \deprecated (ARM_BPU_BP_CID3) Register MASK  (Use ARM_BPU_BP_CID3_Msk instead)  */
#define ARM_BPU_BP_CID3_Msk                 0xFFu                                          /**< (ARM_BPU_BP_CID3) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief ARM_BPU hardware registers */
typedef struct {  /* ARM Breakpoint Control */
  RwReg8  BP_CTRL;        /**< (ARM_BPU Offset: 0x00) Break Point Control Register */
  __I  uint8_t  Reserved1[7];
  RwReg   BP_COMP0;       /**< (ARM_BPU Offset: 0x08) Break Point Compare Register 0 */
  RwReg   BP_COMP1;       /**< (ARM_BPU Offset: 0x0C) Break Point Compare Register 1 */
  RwReg   BP_COMP2;       /**< (ARM_BPU Offset: 0x10) Break Point Compare Register 2 */
  RwReg   BP_COMP3;       /**< (ARM_BPU Offset: 0x14) Break Point Compare Register 3 */
  __I  uint32_t Reserved2[1006];
  RoReg8  BP_PID4;        /**< (ARM_BPU Offset: 0xFD0) Peripheral ID Register 4 */
  __I  uint8_t  Reserved3[15];
  RoReg8  BP_PID0;        /**< (ARM_BPU Offset: 0xFE0) Peripheral ID Register 0 */
  __I  uint8_t  Reserved4[3];
  RoReg8  BP_PID1;        /**< (ARM_BPU Offset: 0xFE4) Peripheral ID Register 1 */
  __I  uint8_t  Reserved5[3];
  RoReg8  BP_PID2;        /**< (ARM_BPU Offset: 0xFE8) Peripheral ID Register 2 */
  __I  uint8_t  Reserved6[3];
  RoReg8  BP_PID3;        /**< (ARM_BPU Offset: 0xFEC) Peripheral ID Register 3 */
  __I  uint8_t  Reserved7[3];
  RoReg8  BP_CID0;        /**< (ARM_BPU Offset: 0xFF0) Component ID Register 0 */
  __I  uint8_t  Reserved8[3];
  RoReg8  BP_CID1;        /**< (ARM_BPU Offset: 0xFF4) Component ID Register 1 */
  __I  uint8_t  Reserved9[3];
  RoReg8  BP_CID2;        /**< (ARM_BPU Offset: 0xFF8) Component ID Register 2 */
  __I  uint8_t  Reserved10[3];
  RoReg8  BP_CID3;        /**< (ARM_BPU Offset: 0xFFC) Component ID Register 3 */
} ArmBpu;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief ARM_BPU hardware registers */
typedef struct {  /* ARM Breakpoint Control */
  __IO ARM_BPU_BP_CTRL_Type           BP_CTRL;        /**< Offset: 0x00 (R/W   8) Break Point Control Register */
       RoReg8                         Reserved1[0x7];
  __IO ARM_BPU_BP_COMP0_Type          BP_COMP0;       /**< Offset: 0x08 (R/W  32) Break Point Compare Register 0 */
  __IO ARM_BPU_BP_COMP1_Type          BP_COMP1;       /**< Offset: 0x0C (R/W  32) Break Point Compare Register 1 */
  __IO ARM_BPU_BP_COMP2_Type          BP_COMP2;       /**< Offset: 0x10 (R/W  32) Break Point Compare Register 2 */
  __IO ARM_BPU_BP_COMP3_Type          BP_COMP3;       /**< Offset: 0x14 (R/W  32) Break Point Compare Register 3 */
       RoReg8                         Reserved2[0xFB8];
  __I  ARM_BPU_BP_PID4_Type           BP_PID4;        /**< Offset: 0xFD0 (R/    8) Peripheral ID Register 4 */
       RoReg8                         Reserved3[0xF];
  __I  ARM_BPU_BP_PID0_Type           BP_PID0;        /**< Offset: 0xFE0 (R/    8) Peripheral ID Register 0 */
       RoReg8                         Reserved4[0x3];
  __I  ARM_BPU_BP_PID1_Type           BP_PID1;        /**< Offset: 0xFE4 (R/    8) Peripheral ID Register 1 */
       RoReg8                         Reserved5[0x3];
  __I  ARM_BPU_BP_PID2_Type           BP_PID2;        /**< Offset: 0xFE8 (R/    8) Peripheral ID Register 2 */
       RoReg8                         Reserved6[0x3];
  __I  ARM_BPU_BP_PID3_Type           BP_PID3;        /**< Offset: 0xFEC (R/    8) Peripheral ID Register 3 */
       RoReg8                         Reserved7[0x3];
  __I  ARM_BPU_BP_CID0_Type           BP_CID0;        /**< Offset: 0xFF0 (R/    8) Component ID Register 0 */
       RoReg8                         Reserved8[0x3];
  __I  ARM_BPU_BP_CID1_Type           BP_CID1;        /**< Offset: 0xFF4 (R/    8) Component ID Register 1 */
       RoReg8                         Reserved9[0x3];
  __I  ARM_BPU_BP_CID2_Type           BP_CID2;        /**< Offset: 0xFF8 (R/    8) Component ID Register 2 */
       RoReg8                         Reserved10[0x3];
  __I  ARM_BPU_BP_CID3_Type           BP_CID3;        /**< Offset: 0xFFC (R/    8) Component ID Register 3 */
} ArmBpu;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_ARM_BPU_COMPONENT_ */
