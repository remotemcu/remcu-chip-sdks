/**
 * \file
 *
 * \brief Component description for EFUSE_MISC_REGS
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

#ifndef _SAMB11_EFUSE_MISC_REGS_COMPONENT_
#define _SAMB11_EFUSE_MISC_REGS_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR EFUSE_MISC_REGS */
/* ========================================================================== */
/** \addtogroup SAMB11_EFUSE_MISC_REGS EFUSE Misc Registers 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define EFUSE_MISC_REGS_EMR1234
#define REV_EFUSE_MISC_REGS              0x100

/* -------- EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET : (EFUSE_MISC_REGS Offset: 0x00) (R/W 8) Active Low Global Reset -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  GLOBAL_RSTN:1;             /**< bit:      0  Global Reset                             */
    uint8_t  EFUSE_1_RSTN:1;            /**< bit:      1  EFUSE 1 Reset                            */
    uint8_t  EFUSE_2_RSTN:1;            /**< bit:      2  EFUSE 2 Reset                            */
    uint8_t  EFUSE_3_RSTN:1;            /**< bit:      3  EFUSE 3 Reset                            */
    uint8_t  EFUSE_4_RSTN:1;            /**< bit:      4  EFUSE 4 Reset                            */
    uint8_t  EFUSE_5_RSTN:1;            /**< bit:      5  EFUSE 5 Reset                            */
    uint8_t  EFUSE_6_RSTN:1;            /**< bit:      6  EFUSE 6 Reset                            */
    uint8_t  :1;                        /**< bit:      7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_OFFSET 0x00                                          /**<  (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) Active Low Global Reset  Offset */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_RESETVALUE 0x7Fu                                         /**<  (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) Active Low Global Reset  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_GLOBAL_RSTN_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) Global Reset Position */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_GLOBAL_RSTN_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_GLOBAL_RSTN_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) Global Reset Mask */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_GLOBAL_RSTN EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_GLOBAL_RSTN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_GLOBAL_RSTN_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_1_RSTN_Pos 1                                              /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) EFUSE 1 Reset Position */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_1_RSTN_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_1_RSTN_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) EFUSE 1 Reset Mask */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_1_RSTN EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_1_RSTN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_1_RSTN_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_2_RSTN_Pos 2                                              /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) EFUSE 2 Reset Position */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_2_RSTN_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_2_RSTN_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) EFUSE 2 Reset Mask */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_2_RSTN EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_2_RSTN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_2_RSTN_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_3_RSTN_Pos 3                                              /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) EFUSE 3 Reset Position */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_3_RSTN_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_3_RSTN_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) EFUSE 3 Reset Mask */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_3_RSTN EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_3_RSTN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_3_RSTN_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_4_RSTN_Pos 4                                              /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) EFUSE 4 Reset Position */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_4_RSTN_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_4_RSTN_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) EFUSE 4 Reset Mask */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_4_RSTN EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_4_RSTN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_4_RSTN_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_5_RSTN_Pos 5                                              /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) EFUSE 5 Reset Position */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_5_RSTN_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_5_RSTN_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) EFUSE 5 Reset Mask */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_5_RSTN EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_5_RSTN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_5_RSTN_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_6_RSTN_Pos 6                                              /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) EFUSE 6 Reset Position */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_6_RSTN_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_6_RSTN_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) EFUSE 6 Reset Mask */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_6_RSTN EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_6_RSTN_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_EFUSE_6_RSTN_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_MASK 0x7Fu                                          /**< \deprecated (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_Msk 0x7Fu                                          /**< (EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_1_CONTROL : (EFUSE_MISC_REGS Offset: 0x04) (R/W 32) EFUSE 1 Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t FORCE_LOAD:1;              /**< bit:      0  Efuse Control Force Load                 */
    uint32_t START_PROGRAM:1;           /**< bit:      1  When set to 1 will start programming EFUSE */
    uint32_t FIRST_READ_COUNT:9;        /**< bit:  2..10  First Read Count                         */
    uint32_t FIRST_PROG_COUNT:4;        /**< bit: 11..14  First Program Count                      */
    uint32_t PROG_CLK_H_COUNT:9;        /**< bit: 15..23  First Clock High Count                   */
    uint32_t DEBUG_BUS_SEL:3;           /**< bit: 24..26  EFUSE Debug Bus Selection                */
    uint32_t :4;                        /**< bit: 27..30  Reserved */
    uint32_t EFUSE_LOAD_DONE:1;         /**< bit:     31  Efuse Load Done Indication               */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_1_CONTROL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_OFFSET 0x04                                          /**<  (EFUSE_MISC_REGS_EFUSE_1_CONTROL) EFUSE 1 Control Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_RESETVALUE 0x3FCu                                        /**<  (EFUSE_MISC_REGS_EFUSE_1_CONTROL) EFUSE 1 Control Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_FORCE_LOAD_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) Efuse Control Force Load Position */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_FORCE_LOAD_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_1_CONTROL_FORCE_LOAD_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) Efuse Control Force Load Mask */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_FORCE_LOAD EFUSE_MISC_REGS_EFUSE_1_CONTROL_FORCE_LOAD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_1_CONTROL_FORCE_LOAD_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_START_PROGRAM_Pos 1                                              /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) When set to 1 will start programming EFUSE Position */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_START_PROGRAM_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_1_CONTROL_START_PROGRAM_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) When set to 1 will start programming EFUSE Mask */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_START_PROGRAM EFUSE_MISC_REGS_EFUSE_1_CONTROL_START_PROGRAM_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_1_CONTROL_START_PROGRAM_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_FIRST_READ_COUNT_Pos 2                                              /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) First Read Count Position */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_FIRST_READ_COUNT_Msk (0x1FFu << EFUSE_MISC_REGS_EFUSE_1_CONTROL_FIRST_READ_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) First Read Count Mask */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_FIRST_READ_COUNT(value) (EFUSE_MISC_REGS_EFUSE_1_CONTROL_FIRST_READ_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_1_CONTROL_FIRST_READ_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_FIRST_PROG_COUNT_Pos 11                                             /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) First Program Count Position */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_FIRST_PROG_COUNT_Msk (0xFu << EFUSE_MISC_REGS_EFUSE_1_CONTROL_FIRST_PROG_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) First Program Count Mask */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_FIRST_PROG_COUNT(value) (EFUSE_MISC_REGS_EFUSE_1_CONTROL_FIRST_PROG_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_1_CONTROL_FIRST_PROG_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_PROG_CLK_H_COUNT_Pos 15                                             /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) First Clock High Count Position */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_PROG_CLK_H_COUNT_Msk (0x1FFu << EFUSE_MISC_REGS_EFUSE_1_CONTROL_PROG_CLK_H_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) First Clock High Count Mask */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_PROG_CLK_H_COUNT(value) (EFUSE_MISC_REGS_EFUSE_1_CONTROL_PROG_CLK_H_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_1_CONTROL_PROG_CLK_H_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_DEBUG_BUS_SEL_Pos 24                                             /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) EFUSE Debug Bus Selection Position */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_DEBUG_BUS_SEL_Msk (0x7u << EFUSE_MISC_REGS_EFUSE_1_CONTROL_DEBUG_BUS_SEL_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) EFUSE Debug Bus Selection Mask */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_DEBUG_BUS_SEL(value) (EFUSE_MISC_REGS_EFUSE_1_CONTROL_DEBUG_BUS_SEL_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_1_CONTROL_DEBUG_BUS_SEL_Pos))
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_EFUSE_LOAD_DONE_Pos 31                                             /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) Efuse Load Done Indication Position */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_EFUSE_LOAD_DONE_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_1_CONTROL_EFUSE_LOAD_DONE_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) Efuse Load Done Indication Mask */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_EFUSE_LOAD_DONE EFUSE_MISC_REGS_EFUSE_1_CONTROL_EFUSE_LOAD_DONE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_1_CONTROL_EFUSE_LOAD_DONE_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_MASK 0x87FFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_1_CONTROL) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_1_CONTROL_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_1_CONTROL_Msk 0x87FFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_1_CONTROL) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_2_CONTROL : (EFUSE_MISC_REGS Offset: 0x08) (R/W 32) EFUSE 2 Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t FORCE_LOAD:1;              /**< bit:      0  Efuse Control Force Load                 */
    uint32_t START_PROGRAM:1;           /**< bit:      1  When set to 1 will start programming EFUSE */
    uint32_t FIRST_READ_COUNT:9;        /**< bit:  2..10  First Read Count                         */
    uint32_t FIRST_PROG_COUNT:4;        /**< bit: 11..14  First Program Count                      */
    uint32_t PROG_CLK_H_COUNT:9;        /**< bit: 15..23  First Clock High Count                   */
    uint32_t DEBUG_BUS_SEL:3;           /**< bit: 24..26  EFUSE Debug Bus Selection                */
    uint32_t :4;                        /**< bit: 27..30  Reserved */
    uint32_t EFUSE_LOAD_DONE:1;         /**< bit:     31  Efuse Load Done Indication               */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_2_CONTROL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_OFFSET 0x08                                          /**<  (EFUSE_MISC_REGS_EFUSE_2_CONTROL) EFUSE 2 Control Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_RESETVALUE 0x3FCu                                        /**<  (EFUSE_MISC_REGS_EFUSE_2_CONTROL) EFUSE 2 Control Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_FORCE_LOAD_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) Efuse Control Force Load Position */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_FORCE_LOAD_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_2_CONTROL_FORCE_LOAD_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) Efuse Control Force Load Mask */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_FORCE_LOAD EFUSE_MISC_REGS_EFUSE_2_CONTROL_FORCE_LOAD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_2_CONTROL_FORCE_LOAD_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_START_PROGRAM_Pos 1                                              /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) When set to 1 will start programming EFUSE Position */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_START_PROGRAM_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_2_CONTROL_START_PROGRAM_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) When set to 1 will start programming EFUSE Mask */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_START_PROGRAM EFUSE_MISC_REGS_EFUSE_2_CONTROL_START_PROGRAM_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_2_CONTROL_START_PROGRAM_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_FIRST_READ_COUNT_Pos 2                                              /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) First Read Count Position */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_FIRST_READ_COUNT_Msk (0x1FFu << EFUSE_MISC_REGS_EFUSE_2_CONTROL_FIRST_READ_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) First Read Count Mask */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_FIRST_READ_COUNT(value) (EFUSE_MISC_REGS_EFUSE_2_CONTROL_FIRST_READ_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_2_CONTROL_FIRST_READ_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_FIRST_PROG_COUNT_Pos 11                                             /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) First Program Count Position */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_FIRST_PROG_COUNT_Msk (0xFu << EFUSE_MISC_REGS_EFUSE_2_CONTROL_FIRST_PROG_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) First Program Count Mask */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_FIRST_PROG_COUNT(value) (EFUSE_MISC_REGS_EFUSE_2_CONTROL_FIRST_PROG_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_2_CONTROL_FIRST_PROG_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_PROG_CLK_H_COUNT_Pos 15                                             /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) First Clock High Count Position */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_PROG_CLK_H_COUNT_Msk (0x1FFu << EFUSE_MISC_REGS_EFUSE_2_CONTROL_PROG_CLK_H_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) First Clock High Count Mask */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_PROG_CLK_H_COUNT(value) (EFUSE_MISC_REGS_EFUSE_2_CONTROL_PROG_CLK_H_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_2_CONTROL_PROG_CLK_H_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_DEBUG_BUS_SEL_Pos 24                                             /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) EFUSE Debug Bus Selection Position */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_DEBUG_BUS_SEL_Msk (0x7u << EFUSE_MISC_REGS_EFUSE_2_CONTROL_DEBUG_BUS_SEL_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) EFUSE Debug Bus Selection Mask */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_DEBUG_BUS_SEL(value) (EFUSE_MISC_REGS_EFUSE_2_CONTROL_DEBUG_BUS_SEL_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_2_CONTROL_DEBUG_BUS_SEL_Pos))
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_EFUSE_LOAD_DONE_Pos 31                                             /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) Efuse Load Done Indication Position */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_EFUSE_LOAD_DONE_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_2_CONTROL_EFUSE_LOAD_DONE_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) Efuse Load Done Indication Mask */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_EFUSE_LOAD_DONE EFUSE_MISC_REGS_EFUSE_2_CONTROL_EFUSE_LOAD_DONE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_2_CONTROL_EFUSE_LOAD_DONE_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_MASK 0x87FFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_2_CONTROL) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_2_CONTROL_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_2_CONTROL_Msk 0x87FFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_2_CONTROL) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_3_CONTROL : (EFUSE_MISC_REGS Offset: 0x0c) (R/W 32) EFUSE 3 Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t FORCE_LOAD:1;              /**< bit:      0  Efuse Control Force Load                 */
    uint32_t START_PROGRAM:1;           /**< bit:      1  When set to 1 will start programming EFUSE */
    uint32_t FIRST_READ_COUNT:9;        /**< bit:  2..10  First Read Count                         */
    uint32_t FIRST_PROG_COUNT:4;        /**< bit: 11..14  First Program Count                      */
    uint32_t PROG_CLK_H_COUNT:9;        /**< bit: 15..23  First Clock High Count                   */
    uint32_t DEBUG_BUS_SEL:3;           /**< bit: 24..26  EFUSE Debug Bus Selection                */
    uint32_t :4;                        /**< bit: 27..30  Reserved */
    uint32_t EFUSE_LOAD_DONE:1;         /**< bit:     31  Efuse Load Done Indication               */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_3_CONTROL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_OFFSET 0x0C                                          /**<  (EFUSE_MISC_REGS_EFUSE_3_CONTROL) EFUSE 3 Control Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_RESETVALUE 0x3FCu                                        /**<  (EFUSE_MISC_REGS_EFUSE_3_CONTROL) EFUSE 3 Control Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_FORCE_LOAD_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) Efuse Control Force Load Position */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_FORCE_LOAD_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_3_CONTROL_FORCE_LOAD_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) Efuse Control Force Load Mask */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_FORCE_LOAD EFUSE_MISC_REGS_EFUSE_3_CONTROL_FORCE_LOAD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_3_CONTROL_FORCE_LOAD_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_START_PROGRAM_Pos 1                                              /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) When set to 1 will start programming EFUSE Position */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_START_PROGRAM_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_3_CONTROL_START_PROGRAM_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) When set to 1 will start programming EFUSE Mask */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_START_PROGRAM EFUSE_MISC_REGS_EFUSE_3_CONTROL_START_PROGRAM_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_3_CONTROL_START_PROGRAM_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_FIRST_READ_COUNT_Pos 2                                              /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) First Read Count Position */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_FIRST_READ_COUNT_Msk (0x1FFu << EFUSE_MISC_REGS_EFUSE_3_CONTROL_FIRST_READ_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) First Read Count Mask */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_FIRST_READ_COUNT(value) (EFUSE_MISC_REGS_EFUSE_3_CONTROL_FIRST_READ_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_3_CONTROL_FIRST_READ_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_FIRST_PROG_COUNT_Pos 11                                             /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) First Program Count Position */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_FIRST_PROG_COUNT_Msk (0xFu << EFUSE_MISC_REGS_EFUSE_3_CONTROL_FIRST_PROG_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) First Program Count Mask */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_FIRST_PROG_COUNT(value) (EFUSE_MISC_REGS_EFUSE_3_CONTROL_FIRST_PROG_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_3_CONTROL_FIRST_PROG_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_PROG_CLK_H_COUNT_Pos 15                                             /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) First Clock High Count Position */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_PROG_CLK_H_COUNT_Msk (0x1FFu << EFUSE_MISC_REGS_EFUSE_3_CONTROL_PROG_CLK_H_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) First Clock High Count Mask */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_PROG_CLK_H_COUNT(value) (EFUSE_MISC_REGS_EFUSE_3_CONTROL_PROG_CLK_H_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_3_CONTROL_PROG_CLK_H_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_DEBUG_BUS_SEL_Pos 24                                             /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) EFUSE Debug Bus Selection Position */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_DEBUG_BUS_SEL_Msk (0x7u << EFUSE_MISC_REGS_EFUSE_3_CONTROL_DEBUG_BUS_SEL_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) EFUSE Debug Bus Selection Mask */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_DEBUG_BUS_SEL(value) (EFUSE_MISC_REGS_EFUSE_3_CONTROL_DEBUG_BUS_SEL_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_3_CONTROL_DEBUG_BUS_SEL_Pos))
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_EFUSE_LOAD_DONE_Pos 31                                             /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) Efuse Load Done Indication Position */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_EFUSE_LOAD_DONE_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_3_CONTROL_EFUSE_LOAD_DONE_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) Efuse Load Done Indication Mask */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_EFUSE_LOAD_DONE EFUSE_MISC_REGS_EFUSE_3_CONTROL_EFUSE_LOAD_DONE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_3_CONTROL_EFUSE_LOAD_DONE_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_MASK 0x87FFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_3_CONTROL) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_3_CONTROL_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_3_CONTROL_Msk 0x87FFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_3_CONTROL) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_4_CONTROL : (EFUSE_MISC_REGS Offset: 0x10) (R/W 32) EFUSE 4 Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t FORCE_LOAD:1;              /**< bit:      0  Efuse Control Force Load                 */
    uint32_t START_PROGRAM:1;           /**< bit:      1  When set to 1 will start programming EFUSE */
    uint32_t FIRST_READ_COUNT:9;        /**< bit:  2..10  First Read Count                         */
    uint32_t FIRST_PROG_COUNT:4;        /**< bit: 11..14  First Program Count                      */
    uint32_t PROG_CLK_H_COUNT:9;        /**< bit: 15..23  First Clock High Count                   */
    uint32_t DEBUG_BUS_SEL:3;           /**< bit: 24..26  EFUSE Debug Bus Selection                */
    uint32_t :4;                        /**< bit: 27..30  Reserved */
    uint32_t EFUSE_LOAD_DONE:1;         /**< bit:     31  Efuse Load Done Indication               */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_4_CONTROL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_OFFSET 0x10                                          /**<  (EFUSE_MISC_REGS_EFUSE_4_CONTROL) EFUSE 4 Control Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_RESETVALUE 0x3FCu                                        /**<  (EFUSE_MISC_REGS_EFUSE_4_CONTROL) EFUSE 4 Control Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_FORCE_LOAD_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) Efuse Control Force Load Position */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_FORCE_LOAD_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_4_CONTROL_FORCE_LOAD_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) Efuse Control Force Load Mask */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_FORCE_LOAD EFUSE_MISC_REGS_EFUSE_4_CONTROL_FORCE_LOAD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_4_CONTROL_FORCE_LOAD_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_START_PROGRAM_Pos 1                                              /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) When set to 1 will start programming EFUSE Position */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_START_PROGRAM_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_4_CONTROL_START_PROGRAM_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) When set to 1 will start programming EFUSE Mask */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_START_PROGRAM EFUSE_MISC_REGS_EFUSE_4_CONTROL_START_PROGRAM_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_4_CONTROL_START_PROGRAM_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_FIRST_READ_COUNT_Pos 2                                              /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) First Read Count Position */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_FIRST_READ_COUNT_Msk (0x1FFu << EFUSE_MISC_REGS_EFUSE_4_CONTROL_FIRST_READ_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) First Read Count Mask */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_FIRST_READ_COUNT(value) (EFUSE_MISC_REGS_EFUSE_4_CONTROL_FIRST_READ_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_4_CONTROL_FIRST_READ_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_FIRST_PROG_COUNT_Pos 11                                             /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) First Program Count Position */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_FIRST_PROG_COUNT_Msk (0xFu << EFUSE_MISC_REGS_EFUSE_4_CONTROL_FIRST_PROG_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) First Program Count Mask */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_FIRST_PROG_COUNT(value) (EFUSE_MISC_REGS_EFUSE_4_CONTROL_FIRST_PROG_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_4_CONTROL_FIRST_PROG_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_PROG_CLK_H_COUNT_Pos 15                                             /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) First Clock High Count Position */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_PROG_CLK_H_COUNT_Msk (0x1FFu << EFUSE_MISC_REGS_EFUSE_4_CONTROL_PROG_CLK_H_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) First Clock High Count Mask */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_PROG_CLK_H_COUNT(value) (EFUSE_MISC_REGS_EFUSE_4_CONTROL_PROG_CLK_H_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_4_CONTROL_PROG_CLK_H_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_DEBUG_BUS_SEL_Pos 24                                             /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) EFUSE Debug Bus Selection Position */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_DEBUG_BUS_SEL_Msk (0x7u << EFUSE_MISC_REGS_EFUSE_4_CONTROL_DEBUG_BUS_SEL_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) EFUSE Debug Bus Selection Mask */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_DEBUG_BUS_SEL(value) (EFUSE_MISC_REGS_EFUSE_4_CONTROL_DEBUG_BUS_SEL_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_4_CONTROL_DEBUG_BUS_SEL_Pos))
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_EFUSE_LOAD_DONE_Pos 31                                             /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) Efuse Load Done Indication Position */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_EFUSE_LOAD_DONE_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_4_CONTROL_EFUSE_LOAD_DONE_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) Efuse Load Done Indication Mask */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_EFUSE_LOAD_DONE EFUSE_MISC_REGS_EFUSE_4_CONTROL_EFUSE_LOAD_DONE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_4_CONTROL_EFUSE_LOAD_DONE_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_MASK 0x87FFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_4_CONTROL) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_4_CONTROL_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_4_CONTROL_Msk 0x87FFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_4_CONTROL) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_5_CONTROL : (EFUSE_MISC_REGS Offset: 0x14) (R/W 32) EFUSE 5 Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t FORCE_LOAD:1;              /**< bit:      0  Efuse Control Force Load                 */
    uint32_t START_PROGRAM:1;           /**< bit:      1  When set to 1 will start programming EFUSE */
    uint32_t FIRST_READ_COUNT:9;        /**< bit:  2..10  First Read Count                         */
    uint32_t FIRST_PROG_COUNT:4;        /**< bit: 11..14  First Program Count                      */
    uint32_t PROG_CLK_H_COUNT:9;        /**< bit: 15..23  First Clock High Count                   */
    uint32_t DEBUG_BUS_SEL:3;           /**< bit: 24..26  EFUSE Debug Bus Selection                */
    uint32_t :4;                        /**< bit: 27..30  Reserved */
    uint32_t EFUSE_LOAD_DONE:1;         /**< bit:     31  Efuse Load Done Indication               */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_5_CONTROL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_OFFSET 0x14                                          /**<  (EFUSE_MISC_REGS_EFUSE_5_CONTROL) EFUSE 5 Control Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_RESETVALUE 0x3FCu                                        /**<  (EFUSE_MISC_REGS_EFUSE_5_CONTROL) EFUSE 5 Control Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_FORCE_LOAD_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) Efuse Control Force Load Position */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_FORCE_LOAD_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_5_CONTROL_FORCE_LOAD_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) Efuse Control Force Load Mask */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_FORCE_LOAD EFUSE_MISC_REGS_EFUSE_5_CONTROL_FORCE_LOAD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_5_CONTROL_FORCE_LOAD_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_START_PROGRAM_Pos 1                                              /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) When set to 1 will start programming EFUSE Position */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_START_PROGRAM_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_5_CONTROL_START_PROGRAM_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) When set to 1 will start programming EFUSE Mask */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_START_PROGRAM EFUSE_MISC_REGS_EFUSE_5_CONTROL_START_PROGRAM_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_5_CONTROL_START_PROGRAM_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_FIRST_READ_COUNT_Pos 2                                              /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) First Read Count Position */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_FIRST_READ_COUNT_Msk (0x1FFu << EFUSE_MISC_REGS_EFUSE_5_CONTROL_FIRST_READ_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) First Read Count Mask */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_FIRST_READ_COUNT(value) (EFUSE_MISC_REGS_EFUSE_5_CONTROL_FIRST_READ_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_5_CONTROL_FIRST_READ_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_FIRST_PROG_COUNT_Pos 11                                             /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) First Program Count Position */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_FIRST_PROG_COUNT_Msk (0xFu << EFUSE_MISC_REGS_EFUSE_5_CONTROL_FIRST_PROG_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) First Program Count Mask */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_FIRST_PROG_COUNT(value) (EFUSE_MISC_REGS_EFUSE_5_CONTROL_FIRST_PROG_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_5_CONTROL_FIRST_PROG_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_PROG_CLK_H_COUNT_Pos 15                                             /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) First Clock High Count Position */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_PROG_CLK_H_COUNT_Msk (0x1FFu << EFUSE_MISC_REGS_EFUSE_5_CONTROL_PROG_CLK_H_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) First Clock High Count Mask */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_PROG_CLK_H_COUNT(value) (EFUSE_MISC_REGS_EFUSE_5_CONTROL_PROG_CLK_H_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_5_CONTROL_PROG_CLK_H_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_DEBUG_BUS_SEL_Pos 24                                             /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) EFUSE Debug Bus Selection Position */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_DEBUG_BUS_SEL_Msk (0x7u << EFUSE_MISC_REGS_EFUSE_5_CONTROL_DEBUG_BUS_SEL_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) EFUSE Debug Bus Selection Mask */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_DEBUG_BUS_SEL(value) (EFUSE_MISC_REGS_EFUSE_5_CONTROL_DEBUG_BUS_SEL_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_5_CONTROL_DEBUG_BUS_SEL_Pos))
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_EFUSE_LOAD_DONE_Pos 31                                             /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) Efuse Load Done Indication Position */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_EFUSE_LOAD_DONE_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_5_CONTROL_EFUSE_LOAD_DONE_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) Efuse Load Done Indication Mask */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_EFUSE_LOAD_DONE EFUSE_MISC_REGS_EFUSE_5_CONTROL_EFUSE_LOAD_DONE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_5_CONTROL_EFUSE_LOAD_DONE_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_MASK 0x87FFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_5_CONTROL) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_5_CONTROL_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_5_CONTROL_Msk 0x87FFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_5_CONTROL) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_6_CONTROL : (EFUSE_MISC_REGS Offset: 0x18) (R/W 32) EFUSE 6 Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t FORCE_LOAD:1;              /**< bit:      0  Efuse Control Force Load                 */
    uint32_t START_PROGRAM:1;           /**< bit:      1  When set to 1 will start programming EFUSE */
    uint32_t FIRST_READ_COUNT:9;        /**< bit:  2..10  First Read Count                         */
    uint32_t FIRST_PROG_COUNT:4;        /**< bit: 11..14  First Program Count                      */
    uint32_t PROG_CLK_H_COUNT:9;        /**< bit: 15..23  First Clock High Count                   */
    uint32_t DEBUG_BUS_SEL:3;           /**< bit: 24..26  EFUSE Debug Bus Selection                */
    uint32_t :4;                        /**< bit: 27..30  Reserved */
    uint32_t EFUSE_LOAD_DONE:1;         /**< bit:     31  Efuse Load Done Indication               */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_6_CONTROL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_OFFSET 0x18                                          /**<  (EFUSE_MISC_REGS_EFUSE_6_CONTROL) EFUSE 6 Control Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_RESETVALUE 0x3FCu                                        /**<  (EFUSE_MISC_REGS_EFUSE_6_CONTROL) EFUSE 6 Control Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_FORCE_LOAD_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) Efuse Control Force Load Position */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_FORCE_LOAD_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_6_CONTROL_FORCE_LOAD_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) Efuse Control Force Load Mask */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_FORCE_LOAD EFUSE_MISC_REGS_EFUSE_6_CONTROL_FORCE_LOAD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_6_CONTROL_FORCE_LOAD_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_START_PROGRAM_Pos 1                                              /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) When set to 1 will start programming EFUSE Position */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_START_PROGRAM_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_6_CONTROL_START_PROGRAM_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) When set to 1 will start programming EFUSE Mask */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_START_PROGRAM EFUSE_MISC_REGS_EFUSE_6_CONTROL_START_PROGRAM_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_6_CONTROL_START_PROGRAM_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_FIRST_READ_COUNT_Pos 2                                              /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) First Read Count Position */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_FIRST_READ_COUNT_Msk (0x1FFu << EFUSE_MISC_REGS_EFUSE_6_CONTROL_FIRST_READ_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) First Read Count Mask */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_FIRST_READ_COUNT(value) (EFUSE_MISC_REGS_EFUSE_6_CONTROL_FIRST_READ_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_6_CONTROL_FIRST_READ_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_FIRST_PROG_COUNT_Pos 11                                             /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) First Program Count Position */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_FIRST_PROG_COUNT_Msk (0xFu << EFUSE_MISC_REGS_EFUSE_6_CONTROL_FIRST_PROG_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) First Program Count Mask */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_FIRST_PROG_COUNT(value) (EFUSE_MISC_REGS_EFUSE_6_CONTROL_FIRST_PROG_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_6_CONTROL_FIRST_PROG_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_PROG_CLK_H_COUNT_Pos 15                                             /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) First Clock High Count Position */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_PROG_CLK_H_COUNT_Msk (0x1FFu << EFUSE_MISC_REGS_EFUSE_6_CONTROL_PROG_CLK_H_COUNT_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) First Clock High Count Mask */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_PROG_CLK_H_COUNT(value) (EFUSE_MISC_REGS_EFUSE_6_CONTROL_PROG_CLK_H_COUNT_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_6_CONTROL_PROG_CLK_H_COUNT_Pos))
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_DEBUG_BUS_SEL_Pos 24                                             /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) EFUSE Debug Bus Selection Position */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_DEBUG_BUS_SEL_Msk (0x7u << EFUSE_MISC_REGS_EFUSE_6_CONTROL_DEBUG_BUS_SEL_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) EFUSE Debug Bus Selection Mask */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_DEBUG_BUS_SEL(value) (EFUSE_MISC_REGS_EFUSE_6_CONTROL_DEBUG_BUS_SEL_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_6_CONTROL_DEBUG_BUS_SEL_Pos))
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_EFUSE_LOAD_DONE_Pos 31                                             /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) Efuse Load Done Indication Position */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_EFUSE_LOAD_DONE_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_6_CONTROL_EFUSE_LOAD_DONE_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) Efuse Load Done Indication Mask */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_EFUSE_LOAD_DONE EFUSE_MISC_REGS_EFUSE_6_CONTROL_EFUSE_LOAD_DONE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_6_CONTROL_EFUSE_LOAD_DONE_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_MASK 0x87FFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_6_CONTROL) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_6_CONTROL_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_6_CONTROL_Msk 0x87FFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_6_CONTROL) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_1_PROG_0 : (EFUSE_MISC_REGS Offset: 0x1c) (R/W 32) EFUSE_1_0 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_1_PROG_0:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_1_PROG_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_1_PROG_0_OFFSET 0x1C                                          /**<  (EFUSE_MISC_REGS_EFUSE_1_PROG_0) EFUSE_1_0 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_0_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_1_PROG_0) EFUSE_1_0 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_1_PROG_0_EFUSE_1_PROG_0_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_1_PROG_0)  Position */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_0_EFUSE_1_PROG_0_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_1_PROG_0_EFUSE_1_PROG_0_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_PROG_0)  Mask */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_0_EFUSE_1_PROG_0(value) (EFUSE_MISC_REGS_EFUSE_1_PROG_0_EFUSE_1_PROG_0_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_1_PROG_0_EFUSE_1_PROG_0_Pos))
#define EFUSE_MISC_REGS_EFUSE_1_PROG_0_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_1_PROG_0) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_1_PROG_0_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_0_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_1_PROG_0) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_1_PROG_1 : (EFUSE_MISC_REGS Offset: 0x20) (R/W 32) EFUSE_1_1 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_1_PROG_1:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_1_PROG_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_1_PROG_1_OFFSET 0x20                                          /**<  (EFUSE_MISC_REGS_EFUSE_1_PROG_1) EFUSE_1_1 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_1_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_1_PROG_1) EFUSE_1_1 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_1_PROG_1_EFUSE_1_PROG_1_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_1_PROG_1)  Position */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_1_EFUSE_1_PROG_1_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_1_PROG_1_EFUSE_1_PROG_1_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_PROG_1)  Mask */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_1_EFUSE_1_PROG_1(value) (EFUSE_MISC_REGS_EFUSE_1_PROG_1_EFUSE_1_PROG_1_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_1_PROG_1_EFUSE_1_PROG_1_Pos))
#define EFUSE_MISC_REGS_EFUSE_1_PROG_1_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_1_PROG_1) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_1_PROG_1_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_1_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_1_PROG_1) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_1_PROG_2 : (EFUSE_MISC_REGS Offset: 0x24) (R/W 32) EFUSE_1_2 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_1_PROG_2:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_1_PROG_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_1_PROG_2_OFFSET 0x24                                          /**<  (EFUSE_MISC_REGS_EFUSE_1_PROG_2) EFUSE_1_2 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_2_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_1_PROG_2) EFUSE_1_2 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_1_PROG_2_EFUSE_1_PROG_2_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_1_PROG_2)  Position */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_2_EFUSE_1_PROG_2_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_1_PROG_2_EFUSE_1_PROG_2_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_PROG_2)  Mask */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_2_EFUSE_1_PROG_2(value) (EFUSE_MISC_REGS_EFUSE_1_PROG_2_EFUSE_1_PROG_2_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_1_PROG_2_EFUSE_1_PROG_2_Pos))
#define EFUSE_MISC_REGS_EFUSE_1_PROG_2_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_1_PROG_2) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_1_PROG_2_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_2_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_1_PROG_2) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_1_PROG_3 : (EFUSE_MISC_REGS Offset: 0x28) (R/W 32) EFUSE_1_3 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_1_PROG_3:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_1_PROG_3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_1_PROG_3_OFFSET 0x28                                          /**<  (EFUSE_MISC_REGS_EFUSE_1_PROG_3) EFUSE_1_3 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_3_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_1_PROG_3) EFUSE_1_3 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_1_PROG_3_EFUSE_1_PROG_3_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_1_PROG_3)  Position */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_3_EFUSE_1_PROG_3_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_1_PROG_3_EFUSE_1_PROG_3_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_PROG_3)  Mask */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_3_EFUSE_1_PROG_3(value) (EFUSE_MISC_REGS_EFUSE_1_PROG_3_EFUSE_1_PROG_3_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_1_PROG_3_EFUSE_1_PROG_3_Pos))
#define EFUSE_MISC_REGS_EFUSE_1_PROG_3_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_1_PROG_3) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_1_PROG_3_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_1_PROG_3_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_1_PROG_3) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_1_STATUS_0 : (EFUSE_MISC_REGS Offset: 0x2c) (R/ 32) EFUSE_1_0 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_1_STATUS_0:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_1_STATUS_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_1_STATUS_0_OFFSET 0x2C                                          /**<  (EFUSE_MISC_REGS_EFUSE_1_STATUS_0) EFUSE_1_0 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_0_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_1_STATUS_0) EFUSE_1_0 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_1_STATUS_0_EFUSE_1_STATUS_0_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_1_STATUS_0)  Position */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_0_EFUSE_1_STATUS_0_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_1_STATUS_0_EFUSE_1_STATUS_0_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_STATUS_0)  Mask */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_0_EFUSE_1_STATUS_0(value) (EFUSE_MISC_REGS_EFUSE_1_STATUS_0_EFUSE_1_STATUS_0_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_1_STATUS_0_EFUSE_1_STATUS_0_Pos))
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_0_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_1_STATUS_0) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_1_STATUS_0_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_0_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_1_STATUS_0) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_1_STATUS_1 : (EFUSE_MISC_REGS Offset: 0x30) (R/ 32) EFUSE_1_1 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_1_STATUS_1:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_1_STATUS_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_1_STATUS_1_OFFSET 0x30                                          /**<  (EFUSE_MISC_REGS_EFUSE_1_STATUS_1) EFUSE_1_1 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_1_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_1_STATUS_1) EFUSE_1_1 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_1_STATUS_1_EFUSE_1_STATUS_1_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_1_STATUS_1)  Position */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_1_EFUSE_1_STATUS_1_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_1_STATUS_1_EFUSE_1_STATUS_1_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_STATUS_1)  Mask */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_1_EFUSE_1_STATUS_1(value) (EFUSE_MISC_REGS_EFUSE_1_STATUS_1_EFUSE_1_STATUS_1_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_1_STATUS_1_EFUSE_1_STATUS_1_Pos))
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_1_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_1_STATUS_1) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_1_STATUS_1_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_1_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_1_STATUS_1) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_1_STATUS_2 : (EFUSE_MISC_REGS Offset: 0x34) (R/ 32) EFUSE_1_2 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_1_STATUS_2:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_1_STATUS_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_1_STATUS_2_OFFSET 0x34                                          /**<  (EFUSE_MISC_REGS_EFUSE_1_STATUS_2) EFUSE_1_2 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_2_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_1_STATUS_2) EFUSE_1_2 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_1_STATUS_2_EFUSE_1_STATUS_2_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_1_STATUS_2)  Position */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_2_EFUSE_1_STATUS_2_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_1_STATUS_2_EFUSE_1_STATUS_2_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_STATUS_2)  Mask */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_2_EFUSE_1_STATUS_2(value) (EFUSE_MISC_REGS_EFUSE_1_STATUS_2_EFUSE_1_STATUS_2_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_1_STATUS_2_EFUSE_1_STATUS_2_Pos))
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_2_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_1_STATUS_2) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_1_STATUS_2_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_2_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_1_STATUS_2) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_1_STATUS_3 : (EFUSE_MISC_REGS Offset: 0x38) (R/ 32) EFUSE_1_3 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_1_STATUS_3:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_1_STATUS_3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_1_STATUS_3_OFFSET 0x38                                          /**<  (EFUSE_MISC_REGS_EFUSE_1_STATUS_3) EFUSE_1_3 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_3_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_1_STATUS_3) EFUSE_1_3 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_1_STATUS_3_EFUSE_1_STATUS_3_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_1_STATUS_3)  Position */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_3_EFUSE_1_STATUS_3_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_1_STATUS_3_EFUSE_1_STATUS_3_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_1_STATUS_3)  Mask */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_3_EFUSE_1_STATUS_3(value) (EFUSE_MISC_REGS_EFUSE_1_STATUS_3_EFUSE_1_STATUS_3_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_1_STATUS_3_EFUSE_1_STATUS_3_Pos))
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_3_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_1_STATUS_3) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_1_STATUS_3_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_1_STATUS_3_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_1_STATUS_3) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_2_PROG_0 : (EFUSE_MISC_REGS Offset: 0x3c) (R/W 32) EFUSE_2_0 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_2_PROG_0:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_2_PROG_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_2_PROG_0_OFFSET 0x3C                                          /**<  (EFUSE_MISC_REGS_EFUSE_2_PROG_0) EFUSE_2_0 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_0_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_2_PROG_0) EFUSE_2_0 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_2_PROG_0_EFUSE_2_PROG_0_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_2_PROG_0)  Position */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_0_EFUSE_2_PROG_0_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_2_PROG_0_EFUSE_2_PROG_0_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_PROG_0)  Mask */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_0_EFUSE_2_PROG_0(value) (EFUSE_MISC_REGS_EFUSE_2_PROG_0_EFUSE_2_PROG_0_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_2_PROG_0_EFUSE_2_PROG_0_Pos))
#define EFUSE_MISC_REGS_EFUSE_2_PROG_0_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_2_PROG_0) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_2_PROG_0_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_0_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_2_PROG_0) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_2_PROG_1 : (EFUSE_MISC_REGS Offset: 0x40) (R/W 32) EFUSE_2_1 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_2_PROG_1:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_2_PROG_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_2_PROG_1_OFFSET 0x40                                          /**<  (EFUSE_MISC_REGS_EFUSE_2_PROG_1) EFUSE_2_1 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_1_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_2_PROG_1) EFUSE_2_1 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_2_PROG_1_EFUSE_2_PROG_1_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_2_PROG_1)  Position */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_1_EFUSE_2_PROG_1_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_2_PROG_1_EFUSE_2_PROG_1_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_PROG_1)  Mask */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_1_EFUSE_2_PROG_1(value) (EFUSE_MISC_REGS_EFUSE_2_PROG_1_EFUSE_2_PROG_1_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_2_PROG_1_EFUSE_2_PROG_1_Pos))
#define EFUSE_MISC_REGS_EFUSE_2_PROG_1_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_2_PROG_1) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_2_PROG_1_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_1_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_2_PROG_1) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_2_PROG_2 : (EFUSE_MISC_REGS Offset: 0x44) (R/W 32) EFUSE_2_2 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_2_PROG_2:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_2_PROG_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_2_PROG_2_OFFSET 0x44                                          /**<  (EFUSE_MISC_REGS_EFUSE_2_PROG_2) EFUSE_2_2 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_2_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_2_PROG_2) EFUSE_2_2 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_2_PROG_2_EFUSE_2_PROG_2_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_2_PROG_2)  Position */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_2_EFUSE_2_PROG_2_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_2_PROG_2_EFUSE_2_PROG_2_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_PROG_2)  Mask */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_2_EFUSE_2_PROG_2(value) (EFUSE_MISC_REGS_EFUSE_2_PROG_2_EFUSE_2_PROG_2_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_2_PROG_2_EFUSE_2_PROG_2_Pos))
#define EFUSE_MISC_REGS_EFUSE_2_PROG_2_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_2_PROG_2) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_2_PROG_2_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_2_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_2_PROG_2) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_2_PROG_3 : (EFUSE_MISC_REGS Offset: 0x48) (R/W 32) EFUSE_2_3 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_2_PROG_3:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_2_PROG_3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_2_PROG_3_OFFSET 0x48                                          /**<  (EFUSE_MISC_REGS_EFUSE_2_PROG_3) EFUSE_2_3 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_3_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_2_PROG_3) EFUSE_2_3 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_2_PROG_3_EFUSE_2_PROG_3_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_2_PROG_3)  Position */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_3_EFUSE_2_PROG_3_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_2_PROG_3_EFUSE_2_PROG_3_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_PROG_3)  Mask */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_3_EFUSE_2_PROG_3(value) (EFUSE_MISC_REGS_EFUSE_2_PROG_3_EFUSE_2_PROG_3_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_2_PROG_3_EFUSE_2_PROG_3_Pos))
#define EFUSE_MISC_REGS_EFUSE_2_PROG_3_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_2_PROG_3) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_2_PROG_3_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_2_PROG_3_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_2_PROG_3) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_2_STATUS_0 : (EFUSE_MISC_REGS Offset: 0x4c) (R/ 32) EFUSE_2_0 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_2_STATUS_0:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_2_STATUS_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_2_STATUS_0_OFFSET 0x4C                                          /**<  (EFUSE_MISC_REGS_EFUSE_2_STATUS_0) EFUSE_2_0 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_0_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_2_STATUS_0) EFUSE_2_0 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_2_STATUS_0_EFUSE_2_STATUS_0_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_2_STATUS_0)  Position */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_0_EFUSE_2_STATUS_0_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_2_STATUS_0_EFUSE_2_STATUS_0_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_STATUS_0)  Mask */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_0_EFUSE_2_STATUS_0(value) (EFUSE_MISC_REGS_EFUSE_2_STATUS_0_EFUSE_2_STATUS_0_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_2_STATUS_0_EFUSE_2_STATUS_0_Pos))
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_0_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_2_STATUS_0) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_2_STATUS_0_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_0_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_2_STATUS_0) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_2_STATUS_1 : (EFUSE_MISC_REGS Offset: 0x50) (R/ 32) EFUSE_2_1 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_2_STATUS_1:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_2_STATUS_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_2_STATUS_1_OFFSET 0x50                                          /**<  (EFUSE_MISC_REGS_EFUSE_2_STATUS_1) EFUSE_2_1 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_1_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_2_STATUS_1) EFUSE_2_1 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_2_STATUS_1_EFUSE_2_STATUS_1_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_2_STATUS_1)  Position */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_1_EFUSE_2_STATUS_1_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_2_STATUS_1_EFUSE_2_STATUS_1_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_STATUS_1)  Mask */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_1_EFUSE_2_STATUS_1(value) (EFUSE_MISC_REGS_EFUSE_2_STATUS_1_EFUSE_2_STATUS_1_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_2_STATUS_1_EFUSE_2_STATUS_1_Pos))
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_1_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_2_STATUS_1) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_2_STATUS_1_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_1_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_2_STATUS_1) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_2_STATUS_2 : (EFUSE_MISC_REGS Offset: 0x54) (R/ 32) EFUSE_2_2 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_2_STATUS_2:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_2_STATUS_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_2_STATUS_2_OFFSET 0x54                                          /**<  (EFUSE_MISC_REGS_EFUSE_2_STATUS_2) EFUSE_2_2 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_2_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_2_STATUS_2) EFUSE_2_2 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_2_STATUS_2_EFUSE_2_STATUS_2_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_2_STATUS_2)  Position */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_2_EFUSE_2_STATUS_2_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_2_STATUS_2_EFUSE_2_STATUS_2_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_STATUS_2)  Mask */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_2_EFUSE_2_STATUS_2(value) (EFUSE_MISC_REGS_EFUSE_2_STATUS_2_EFUSE_2_STATUS_2_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_2_STATUS_2_EFUSE_2_STATUS_2_Pos))
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_2_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_2_STATUS_2) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_2_STATUS_2_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_2_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_2_STATUS_2) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_2_STATUS_3 : (EFUSE_MISC_REGS Offset: 0x58) (R/ 32) EFUSE_2_3 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_2_STATUS_3:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_2_STATUS_3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_2_STATUS_3_OFFSET 0x58                                          /**<  (EFUSE_MISC_REGS_EFUSE_2_STATUS_3) EFUSE_2_3 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_3_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_2_STATUS_3) EFUSE_2_3 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_2_STATUS_3_EFUSE_2_STATUS_3_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_2_STATUS_3)  Position */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_3_EFUSE_2_STATUS_3_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_2_STATUS_3_EFUSE_2_STATUS_3_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_2_STATUS_3)  Mask */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_3_EFUSE_2_STATUS_3(value) (EFUSE_MISC_REGS_EFUSE_2_STATUS_3_EFUSE_2_STATUS_3_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_2_STATUS_3_EFUSE_2_STATUS_3_Pos))
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_3_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_2_STATUS_3) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_2_STATUS_3_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_2_STATUS_3_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_2_STATUS_3) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_3_PROG_0 : (EFUSE_MISC_REGS Offset: 0x5c) (R/W 32) EFUSE_3_0 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_3_PROG_0:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_3_PROG_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_3_PROG_0_OFFSET 0x5C                                          /**<  (EFUSE_MISC_REGS_EFUSE_3_PROG_0) EFUSE_3_0 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_0_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_3_PROG_0) EFUSE_3_0 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_3_PROG_0_EFUSE_3_PROG_0_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_3_PROG_0)  Position */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_0_EFUSE_3_PROG_0_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_3_PROG_0_EFUSE_3_PROG_0_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_PROG_0)  Mask */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_0_EFUSE_3_PROG_0(value) (EFUSE_MISC_REGS_EFUSE_3_PROG_0_EFUSE_3_PROG_0_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_3_PROG_0_EFUSE_3_PROG_0_Pos))
#define EFUSE_MISC_REGS_EFUSE_3_PROG_0_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_3_PROG_0) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_3_PROG_0_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_0_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_3_PROG_0) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_3_PROG_1 : (EFUSE_MISC_REGS Offset: 0x60) (R/W 32) EFUSE_3_1 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_3_PROG_1:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_3_PROG_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_3_PROG_1_OFFSET 0x60                                          /**<  (EFUSE_MISC_REGS_EFUSE_3_PROG_1) EFUSE_3_1 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_1_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_3_PROG_1) EFUSE_3_1 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_3_PROG_1_EFUSE_3_PROG_1_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_3_PROG_1)  Position */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_1_EFUSE_3_PROG_1_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_3_PROG_1_EFUSE_3_PROG_1_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_PROG_1)  Mask */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_1_EFUSE_3_PROG_1(value) (EFUSE_MISC_REGS_EFUSE_3_PROG_1_EFUSE_3_PROG_1_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_3_PROG_1_EFUSE_3_PROG_1_Pos))
#define EFUSE_MISC_REGS_EFUSE_3_PROG_1_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_3_PROG_1) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_3_PROG_1_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_1_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_3_PROG_1) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_3_PROG_2 : (EFUSE_MISC_REGS Offset: 0x64) (R/W 32) EFUSE_3_2 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_3_PROG_2:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_3_PROG_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_3_PROG_2_OFFSET 0x64                                          /**<  (EFUSE_MISC_REGS_EFUSE_3_PROG_2) EFUSE_3_2 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_2_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_3_PROG_2) EFUSE_3_2 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_3_PROG_2_EFUSE_3_PROG_2_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_3_PROG_2)  Position */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_2_EFUSE_3_PROG_2_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_3_PROG_2_EFUSE_3_PROG_2_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_PROG_2)  Mask */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_2_EFUSE_3_PROG_2(value) (EFUSE_MISC_REGS_EFUSE_3_PROG_2_EFUSE_3_PROG_2_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_3_PROG_2_EFUSE_3_PROG_2_Pos))
#define EFUSE_MISC_REGS_EFUSE_3_PROG_2_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_3_PROG_2) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_3_PROG_2_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_2_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_3_PROG_2) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_3_PROG_3 : (EFUSE_MISC_REGS Offset: 0x68) (R/W 32) EFUSE_3_3 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_3_PROG_3:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_3_PROG_3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_3_PROG_3_OFFSET 0x68                                          /**<  (EFUSE_MISC_REGS_EFUSE_3_PROG_3) EFUSE_3_3 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_3_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_3_PROG_3) EFUSE_3_3 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_3_PROG_3_EFUSE_3_PROG_3_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_3_PROG_3)  Position */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_3_EFUSE_3_PROG_3_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_3_PROG_3_EFUSE_3_PROG_3_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_PROG_3)  Mask */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_3_EFUSE_3_PROG_3(value) (EFUSE_MISC_REGS_EFUSE_3_PROG_3_EFUSE_3_PROG_3_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_3_PROG_3_EFUSE_3_PROG_3_Pos))
#define EFUSE_MISC_REGS_EFUSE_3_PROG_3_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_3_PROG_3) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_3_PROG_3_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_3_PROG_3_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_3_PROG_3) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_3_STATUS_0 : (EFUSE_MISC_REGS Offset: 0x6c) (R/ 32) EFUSE_3_0 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_3_STATUS_0:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_3_STATUS_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_3_STATUS_0_OFFSET 0x6C                                          /**<  (EFUSE_MISC_REGS_EFUSE_3_STATUS_0) EFUSE_3_0 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_0_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_3_STATUS_0) EFUSE_3_0 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_3_STATUS_0_EFUSE_3_STATUS_0_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_3_STATUS_0)  Position */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_0_EFUSE_3_STATUS_0_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_3_STATUS_0_EFUSE_3_STATUS_0_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_STATUS_0)  Mask */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_0_EFUSE_3_STATUS_0(value) (EFUSE_MISC_REGS_EFUSE_3_STATUS_0_EFUSE_3_STATUS_0_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_3_STATUS_0_EFUSE_3_STATUS_0_Pos))
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_0_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_3_STATUS_0) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_3_STATUS_0_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_0_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_3_STATUS_0) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_3_STATUS_1 : (EFUSE_MISC_REGS Offset: 0x70) (R/ 32) EFUSE_3_1 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_3_STATUS_1:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_3_STATUS_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_3_STATUS_1_OFFSET 0x70                                          /**<  (EFUSE_MISC_REGS_EFUSE_3_STATUS_1) EFUSE_3_1 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_1_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_3_STATUS_1) EFUSE_3_1 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_3_STATUS_1_EFUSE_3_STATUS_1_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_3_STATUS_1)  Position */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_1_EFUSE_3_STATUS_1_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_3_STATUS_1_EFUSE_3_STATUS_1_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_STATUS_1)  Mask */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_1_EFUSE_3_STATUS_1(value) (EFUSE_MISC_REGS_EFUSE_3_STATUS_1_EFUSE_3_STATUS_1_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_3_STATUS_1_EFUSE_3_STATUS_1_Pos))
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_1_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_3_STATUS_1) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_3_STATUS_1_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_1_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_3_STATUS_1) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_3_STATUS_2 : (EFUSE_MISC_REGS Offset: 0x74) (R/ 32) EFUSE_3_2 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_3_STATUS_2:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_3_STATUS_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_3_STATUS_2_OFFSET 0x74                                          /**<  (EFUSE_MISC_REGS_EFUSE_3_STATUS_2) EFUSE_3_2 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_2_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_3_STATUS_2) EFUSE_3_2 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_3_STATUS_2_EFUSE_3_STATUS_2_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_3_STATUS_2)  Position */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_2_EFUSE_3_STATUS_2_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_3_STATUS_2_EFUSE_3_STATUS_2_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_STATUS_2)  Mask */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_2_EFUSE_3_STATUS_2(value) (EFUSE_MISC_REGS_EFUSE_3_STATUS_2_EFUSE_3_STATUS_2_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_3_STATUS_2_EFUSE_3_STATUS_2_Pos))
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_2_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_3_STATUS_2) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_3_STATUS_2_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_2_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_3_STATUS_2) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_3_STATUS_3 : (EFUSE_MISC_REGS Offset: 0x78) (R/ 32) EFUSE_3_3 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_3_STATUS_3:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_3_STATUS_3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_3_STATUS_3_OFFSET 0x78                                          /**<  (EFUSE_MISC_REGS_EFUSE_3_STATUS_3) EFUSE_3_3 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_3_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_3_STATUS_3) EFUSE_3_3 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_3_STATUS_3_EFUSE_3_STATUS_3_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_3_STATUS_3)  Position */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_3_EFUSE_3_STATUS_3_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_3_STATUS_3_EFUSE_3_STATUS_3_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_3_STATUS_3)  Mask */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_3_EFUSE_3_STATUS_3(value) (EFUSE_MISC_REGS_EFUSE_3_STATUS_3_EFUSE_3_STATUS_3_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_3_STATUS_3_EFUSE_3_STATUS_3_Pos))
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_3_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_3_STATUS_3) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_3_STATUS_3_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_3_STATUS_3_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_3_STATUS_3) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_4_PROG_0 : (EFUSE_MISC_REGS Offset: 0x7c) (R/W 32) EFUSE_4_0 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_4_PROG_0:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_4_PROG_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_4_PROG_0_OFFSET 0x7C                                          /**<  (EFUSE_MISC_REGS_EFUSE_4_PROG_0) EFUSE_4_0 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_0_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_4_PROG_0) EFUSE_4_0 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_4_PROG_0_EFUSE_4_PROG_0_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_4_PROG_0)  Position */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_0_EFUSE_4_PROG_0_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_4_PROG_0_EFUSE_4_PROG_0_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_PROG_0)  Mask */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_0_EFUSE_4_PROG_0(value) (EFUSE_MISC_REGS_EFUSE_4_PROG_0_EFUSE_4_PROG_0_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_4_PROG_0_EFUSE_4_PROG_0_Pos))
#define EFUSE_MISC_REGS_EFUSE_4_PROG_0_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_4_PROG_0) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_4_PROG_0_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_0_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_4_PROG_0) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_4_PROG_1 : (EFUSE_MISC_REGS Offset: 0x80) (R/W 32) EFUSE_4_1 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_4_PROG_1:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_4_PROG_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_4_PROG_1_OFFSET 0x80                                          /**<  (EFUSE_MISC_REGS_EFUSE_4_PROG_1) EFUSE_4_1 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_1_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_4_PROG_1) EFUSE_4_1 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_4_PROG_1_EFUSE_4_PROG_1_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_4_PROG_1)  Position */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_1_EFUSE_4_PROG_1_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_4_PROG_1_EFUSE_4_PROG_1_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_PROG_1)  Mask */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_1_EFUSE_4_PROG_1(value) (EFUSE_MISC_REGS_EFUSE_4_PROG_1_EFUSE_4_PROG_1_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_4_PROG_1_EFUSE_4_PROG_1_Pos))
#define EFUSE_MISC_REGS_EFUSE_4_PROG_1_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_4_PROG_1) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_4_PROG_1_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_1_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_4_PROG_1) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_4_PROG_2 : (EFUSE_MISC_REGS Offset: 0x84) (R/W 32) EFUSE_4_2 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_4_PROG_2:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_4_PROG_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_4_PROG_2_OFFSET 0x84                                          /**<  (EFUSE_MISC_REGS_EFUSE_4_PROG_2) EFUSE_4_2 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_2_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_4_PROG_2) EFUSE_4_2 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_4_PROG_2_EFUSE_4_PROG_2_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_4_PROG_2)  Position */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_2_EFUSE_4_PROG_2_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_4_PROG_2_EFUSE_4_PROG_2_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_PROG_2)  Mask */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_2_EFUSE_4_PROG_2(value) (EFUSE_MISC_REGS_EFUSE_4_PROG_2_EFUSE_4_PROG_2_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_4_PROG_2_EFUSE_4_PROG_2_Pos))
#define EFUSE_MISC_REGS_EFUSE_4_PROG_2_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_4_PROG_2) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_4_PROG_2_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_2_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_4_PROG_2) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_4_PROG_3 : (EFUSE_MISC_REGS Offset: 0x88) (R/W 32) EFUSE_4_3 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_4_PROG_3:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_4_PROG_3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_4_PROG_3_OFFSET 0x88                                          /**<  (EFUSE_MISC_REGS_EFUSE_4_PROG_3) EFUSE_4_3 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_3_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_4_PROG_3) EFUSE_4_3 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_4_PROG_3_EFUSE_4_PROG_3_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_4_PROG_3)  Position */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_3_EFUSE_4_PROG_3_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_4_PROG_3_EFUSE_4_PROG_3_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_PROG_3)  Mask */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_3_EFUSE_4_PROG_3(value) (EFUSE_MISC_REGS_EFUSE_4_PROG_3_EFUSE_4_PROG_3_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_4_PROG_3_EFUSE_4_PROG_3_Pos))
#define EFUSE_MISC_REGS_EFUSE_4_PROG_3_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_4_PROG_3) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_4_PROG_3_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_4_PROG_3_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_4_PROG_3) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_4_STATUS_0 : (EFUSE_MISC_REGS Offset: 0x8c) (R/ 32) EFUSE_4_0 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_4_STATUS_0:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_4_STATUS_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_4_STATUS_0_OFFSET 0x8C                                          /**<  (EFUSE_MISC_REGS_EFUSE_4_STATUS_0) EFUSE_4_0 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_0_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_4_STATUS_0) EFUSE_4_0 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_4_STATUS_0_EFUSE_4_STATUS_0_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_4_STATUS_0)  Position */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_0_EFUSE_4_STATUS_0_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_4_STATUS_0_EFUSE_4_STATUS_0_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_STATUS_0)  Mask */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_0_EFUSE_4_STATUS_0(value) (EFUSE_MISC_REGS_EFUSE_4_STATUS_0_EFUSE_4_STATUS_0_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_4_STATUS_0_EFUSE_4_STATUS_0_Pos))
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_0_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_4_STATUS_0) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_4_STATUS_0_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_0_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_4_STATUS_0) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_4_STATUS_1 : (EFUSE_MISC_REGS Offset: 0x90) (R/ 32) EFUSE_4_1 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_4_STATUS_1:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_4_STATUS_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_4_STATUS_1_OFFSET 0x90                                          /**<  (EFUSE_MISC_REGS_EFUSE_4_STATUS_1) EFUSE_4_1 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_1_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_4_STATUS_1) EFUSE_4_1 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_4_STATUS_1_EFUSE_4_STATUS_1_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_4_STATUS_1)  Position */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_1_EFUSE_4_STATUS_1_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_4_STATUS_1_EFUSE_4_STATUS_1_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_STATUS_1)  Mask */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_1_EFUSE_4_STATUS_1(value) (EFUSE_MISC_REGS_EFUSE_4_STATUS_1_EFUSE_4_STATUS_1_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_4_STATUS_1_EFUSE_4_STATUS_1_Pos))
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_1_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_4_STATUS_1) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_4_STATUS_1_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_1_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_4_STATUS_1) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_4_STATUS_2 : (EFUSE_MISC_REGS Offset: 0x94) (R/ 32) EFUSE_4_2 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_4_STATUS_2:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_4_STATUS_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_4_STATUS_2_OFFSET 0x94                                          /**<  (EFUSE_MISC_REGS_EFUSE_4_STATUS_2) EFUSE_4_2 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_2_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_4_STATUS_2) EFUSE_4_2 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_4_STATUS_2_EFUSE_4_STATUS_2_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_4_STATUS_2)  Position */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_2_EFUSE_4_STATUS_2_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_4_STATUS_2_EFUSE_4_STATUS_2_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_STATUS_2)  Mask */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_2_EFUSE_4_STATUS_2(value) (EFUSE_MISC_REGS_EFUSE_4_STATUS_2_EFUSE_4_STATUS_2_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_4_STATUS_2_EFUSE_4_STATUS_2_Pos))
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_2_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_4_STATUS_2) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_4_STATUS_2_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_2_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_4_STATUS_2) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_4_STATUS_3 : (EFUSE_MISC_REGS Offset: 0x98) (R/ 32) EFUSE_4_3 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_4_STATUS_3:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_4_STATUS_3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_4_STATUS_3_OFFSET 0x98                                          /**<  (EFUSE_MISC_REGS_EFUSE_4_STATUS_3) EFUSE_4_3 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_3_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_4_STATUS_3) EFUSE_4_3 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_4_STATUS_3_EFUSE_4_STATUS_3_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_4_STATUS_3)  Position */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_3_EFUSE_4_STATUS_3_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_4_STATUS_3_EFUSE_4_STATUS_3_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_4_STATUS_3)  Mask */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_3_EFUSE_4_STATUS_3(value) (EFUSE_MISC_REGS_EFUSE_4_STATUS_3_EFUSE_4_STATUS_3_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_4_STATUS_3_EFUSE_4_STATUS_3_Pos))
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_3_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_4_STATUS_3) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_4_STATUS_3_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_4_STATUS_3_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_4_STATUS_3) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_5_PROG_0 : (EFUSE_MISC_REGS Offset: 0x9c) (R/W 32) EFUSE_4_0 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_5_PROG_0:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_5_PROG_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_5_PROG_0_OFFSET 0x9C                                          /**<  (EFUSE_MISC_REGS_EFUSE_5_PROG_0) EFUSE_4_0 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_0_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_5_PROG_0) EFUSE_4_0 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_5_PROG_0_EFUSE_5_PROG_0_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_5_PROG_0)  Position */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_0_EFUSE_5_PROG_0_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_5_PROG_0_EFUSE_5_PROG_0_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_PROG_0)  Mask */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_0_EFUSE_5_PROG_0(value) (EFUSE_MISC_REGS_EFUSE_5_PROG_0_EFUSE_5_PROG_0_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_5_PROG_0_EFUSE_5_PROG_0_Pos))
#define EFUSE_MISC_REGS_EFUSE_5_PROG_0_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_5_PROG_0) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_5_PROG_0_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_0_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_5_PROG_0) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_5_PROG_1 : (EFUSE_MISC_REGS Offset: 0xa0) (R/W 32) EFUSE_5_1 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_5_PROG_1:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_5_PROG_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_5_PROG_1_OFFSET 0xA0                                          /**<  (EFUSE_MISC_REGS_EFUSE_5_PROG_1) EFUSE_5_1 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_1_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_5_PROG_1) EFUSE_5_1 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_5_PROG_1_EFUSE_5_PROG_1_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_5_PROG_1)  Position */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_1_EFUSE_5_PROG_1_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_5_PROG_1_EFUSE_5_PROG_1_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_PROG_1)  Mask */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_1_EFUSE_5_PROG_1(value) (EFUSE_MISC_REGS_EFUSE_5_PROG_1_EFUSE_5_PROG_1_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_5_PROG_1_EFUSE_5_PROG_1_Pos))
#define EFUSE_MISC_REGS_EFUSE_5_PROG_1_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_5_PROG_1) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_5_PROG_1_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_1_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_5_PROG_1) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_5_PROG_2 : (EFUSE_MISC_REGS Offset: 0xa4) (R/W 32) EFUSE_5_2 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_5_PROG_2:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_5_PROG_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_5_PROG_2_OFFSET 0xA4                                          /**<  (EFUSE_MISC_REGS_EFUSE_5_PROG_2) EFUSE_5_2 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_2_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_5_PROG_2) EFUSE_5_2 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_5_PROG_2_EFUSE_5_PROG_2_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_5_PROG_2)  Position */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_2_EFUSE_5_PROG_2_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_5_PROG_2_EFUSE_5_PROG_2_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_PROG_2)  Mask */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_2_EFUSE_5_PROG_2(value) (EFUSE_MISC_REGS_EFUSE_5_PROG_2_EFUSE_5_PROG_2_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_5_PROG_2_EFUSE_5_PROG_2_Pos))
#define EFUSE_MISC_REGS_EFUSE_5_PROG_2_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_5_PROG_2) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_5_PROG_2_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_2_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_5_PROG_2) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_5_PROG_3 : (EFUSE_MISC_REGS Offset: 0xa8) (R/W 32) EFUSE_5_3 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_5_PROG_3:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_5_PROG_3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_5_PROG_3_OFFSET 0xA8                                          /**<  (EFUSE_MISC_REGS_EFUSE_5_PROG_3) EFUSE_5_3 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_3_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_5_PROG_3) EFUSE_5_3 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_5_PROG_3_EFUSE_5_PROG_3_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_5_PROG_3)  Position */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_3_EFUSE_5_PROG_3_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_5_PROG_3_EFUSE_5_PROG_3_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_PROG_3)  Mask */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_3_EFUSE_5_PROG_3(value) (EFUSE_MISC_REGS_EFUSE_5_PROG_3_EFUSE_5_PROG_3_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_5_PROG_3_EFUSE_5_PROG_3_Pos))
#define EFUSE_MISC_REGS_EFUSE_5_PROG_3_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_5_PROG_3) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_5_PROG_3_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_5_PROG_3_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_5_PROG_3) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_5_STATUS_0 : (EFUSE_MISC_REGS Offset: 0xac) (R/ 32) EFUSE_5_0 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_5_STATUS_0:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_5_STATUS_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_5_STATUS_0_OFFSET 0xAC                                          /**<  (EFUSE_MISC_REGS_EFUSE_5_STATUS_0) EFUSE_5_0 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_0_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_5_STATUS_0) EFUSE_5_0 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_5_STATUS_0_EFUSE_5_STATUS_0_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_5_STATUS_0)  Position */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_0_EFUSE_5_STATUS_0_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_5_STATUS_0_EFUSE_5_STATUS_0_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_STATUS_0)  Mask */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_0_EFUSE_5_STATUS_0(value) (EFUSE_MISC_REGS_EFUSE_5_STATUS_0_EFUSE_5_STATUS_0_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_5_STATUS_0_EFUSE_5_STATUS_0_Pos))
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_0_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_5_STATUS_0) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_5_STATUS_0_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_0_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_5_STATUS_0) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_5_STATUS_1 : (EFUSE_MISC_REGS Offset: 0xb0) (R/ 32) EFUSE_5_1 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_5_STATUS_1:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_5_STATUS_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_5_STATUS_1_OFFSET 0xB0                                          /**<  (EFUSE_MISC_REGS_EFUSE_5_STATUS_1) EFUSE_5_1 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_1_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_5_STATUS_1) EFUSE_5_1 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_5_STATUS_1_EFUSE_5_STATUS_1_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_5_STATUS_1)  Position */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_1_EFUSE_5_STATUS_1_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_5_STATUS_1_EFUSE_5_STATUS_1_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_STATUS_1)  Mask */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_1_EFUSE_5_STATUS_1(value) (EFUSE_MISC_REGS_EFUSE_5_STATUS_1_EFUSE_5_STATUS_1_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_5_STATUS_1_EFUSE_5_STATUS_1_Pos))
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_1_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_5_STATUS_1) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_5_STATUS_1_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_1_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_5_STATUS_1) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_5_STATUS_2 : (EFUSE_MISC_REGS Offset: 0xb4) (R/ 32) EFUSE_5_2 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_5_STATUS_2:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_5_STATUS_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_5_STATUS_2_OFFSET 0xB4                                          /**<  (EFUSE_MISC_REGS_EFUSE_5_STATUS_2) EFUSE_5_2 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_2_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_5_STATUS_2) EFUSE_5_2 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_5_STATUS_2_EFUSE_5_STATUS_2_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_5_STATUS_2)  Position */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_2_EFUSE_5_STATUS_2_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_5_STATUS_2_EFUSE_5_STATUS_2_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_STATUS_2)  Mask */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_2_EFUSE_5_STATUS_2(value) (EFUSE_MISC_REGS_EFUSE_5_STATUS_2_EFUSE_5_STATUS_2_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_5_STATUS_2_EFUSE_5_STATUS_2_Pos))
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_2_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_5_STATUS_2) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_5_STATUS_2_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_2_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_5_STATUS_2) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_5_STATUS_3 : (EFUSE_MISC_REGS Offset: 0xb8) (R/ 32) EFUSE_5_3 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_5_STATUS_3:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_5_STATUS_3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_5_STATUS_3_OFFSET 0xB8                                          /**<  (EFUSE_MISC_REGS_EFUSE_5_STATUS_3) EFUSE_5_3 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_3_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_5_STATUS_3) EFUSE_5_3 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_5_STATUS_3_EFUSE_5_STATUS_3_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_5_STATUS_3)  Position */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_3_EFUSE_5_STATUS_3_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_5_STATUS_3_EFUSE_5_STATUS_3_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_5_STATUS_3)  Mask */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_3_EFUSE_5_STATUS_3(value) (EFUSE_MISC_REGS_EFUSE_5_STATUS_3_EFUSE_5_STATUS_3_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_5_STATUS_3_EFUSE_5_STATUS_3_Pos))
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_3_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_5_STATUS_3) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_5_STATUS_3_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_5_STATUS_3_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_5_STATUS_3) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_6_PROG_0 : (EFUSE_MISC_REGS Offset: 0xbc) (R/W 32) EFUSE_6_0 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_6_PROG_0:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_6_PROG_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_6_PROG_0_OFFSET 0xBC                                          /**<  (EFUSE_MISC_REGS_EFUSE_6_PROG_0) EFUSE_6_0 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_0_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_6_PROG_0) EFUSE_6_0 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_6_PROG_0_EFUSE_6_PROG_0_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_6_PROG_0)  Position */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_0_EFUSE_6_PROG_0_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_6_PROG_0_EFUSE_6_PROG_0_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_PROG_0)  Mask */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_0_EFUSE_6_PROG_0(value) (EFUSE_MISC_REGS_EFUSE_6_PROG_0_EFUSE_6_PROG_0_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_6_PROG_0_EFUSE_6_PROG_0_Pos))
#define EFUSE_MISC_REGS_EFUSE_6_PROG_0_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_6_PROG_0) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_6_PROG_0_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_0_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_6_PROG_0) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_6_PROG_1 : (EFUSE_MISC_REGS Offset: 0xc0) (R/W 32) EFUSE_6_1 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_6_PROG_1:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_6_PROG_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_6_PROG_1_OFFSET 0xC0                                          /**<  (EFUSE_MISC_REGS_EFUSE_6_PROG_1) EFUSE_6_1 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_1_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_6_PROG_1) EFUSE_6_1 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_6_PROG_1_EFUSE_6_PROG_1_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_6_PROG_1)  Position */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_1_EFUSE_6_PROG_1_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_6_PROG_1_EFUSE_6_PROG_1_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_PROG_1)  Mask */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_1_EFUSE_6_PROG_1(value) (EFUSE_MISC_REGS_EFUSE_6_PROG_1_EFUSE_6_PROG_1_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_6_PROG_1_EFUSE_6_PROG_1_Pos))
#define EFUSE_MISC_REGS_EFUSE_6_PROG_1_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_6_PROG_1) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_6_PROG_1_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_1_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_6_PROG_1) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_6_PROG_2 : (EFUSE_MISC_REGS Offset: 0xc4) (R/W 32) EFUSE_6_2 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_6_PROG_2:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_6_PROG_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_6_PROG_2_OFFSET 0xC4                                          /**<  (EFUSE_MISC_REGS_EFUSE_6_PROG_2) EFUSE_6_2 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_2_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_6_PROG_2) EFUSE_6_2 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_6_PROG_2_EFUSE_6_PROG_2_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_6_PROG_2)  Position */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_2_EFUSE_6_PROG_2_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_6_PROG_2_EFUSE_6_PROG_2_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_PROG_2)  Mask */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_2_EFUSE_6_PROG_2(value) (EFUSE_MISC_REGS_EFUSE_6_PROG_2_EFUSE_6_PROG_2_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_6_PROG_2_EFUSE_6_PROG_2_Pos))
#define EFUSE_MISC_REGS_EFUSE_6_PROG_2_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_6_PROG_2) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_6_PROG_2_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_2_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_6_PROG_2) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_6_PROG_3 : (EFUSE_MISC_REGS Offset: 0xc8) (R/W 32) EFUSE_6_3 Program Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_6_PROG_3:32;         /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_6_PROG_3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_6_PROG_3_OFFSET 0xC8                                          /**<  (EFUSE_MISC_REGS_EFUSE_6_PROG_3) EFUSE_6_3 Program Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_3_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_6_PROG_3) EFUSE_6_3 Program Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_6_PROG_3_EFUSE_6_PROG_3_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_6_PROG_3)  Position */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_3_EFUSE_6_PROG_3_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_6_PROG_3_EFUSE_6_PROG_3_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_PROG_3)  Mask */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_3_EFUSE_6_PROG_3(value) (EFUSE_MISC_REGS_EFUSE_6_PROG_3_EFUSE_6_PROG_3_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_6_PROG_3_EFUSE_6_PROG_3_Pos))
#define EFUSE_MISC_REGS_EFUSE_6_PROG_3_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_6_PROG_3) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_6_PROG_3_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_6_PROG_3_Msk  0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_6_PROG_3) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_6_STATUS_0 : (EFUSE_MISC_REGS Offset: 0xcc) (R/ 32) EFUSE_6_0 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_6_STATUS_0:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_6_STATUS_0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_6_STATUS_0_OFFSET 0xCC                                          /**<  (EFUSE_MISC_REGS_EFUSE_6_STATUS_0) EFUSE_6_0 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_0_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_6_STATUS_0) EFUSE_6_0 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_6_STATUS_0_EFUSE_6_STATUS_0_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_6_STATUS_0)  Position */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_0_EFUSE_6_STATUS_0_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_6_STATUS_0_EFUSE_6_STATUS_0_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_STATUS_0)  Mask */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_0_EFUSE_6_STATUS_0(value) (EFUSE_MISC_REGS_EFUSE_6_STATUS_0_EFUSE_6_STATUS_0_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_6_STATUS_0_EFUSE_6_STATUS_0_Pos))
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_0_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_6_STATUS_0) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_6_STATUS_0_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_0_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_6_STATUS_0) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_6_STATUS_1 : (EFUSE_MISC_REGS Offset: 0xd0) (R/ 32) EFUSE_6_1 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_6_STATUS_1:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_6_STATUS_1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_6_STATUS_1_OFFSET 0xD0                                          /**<  (EFUSE_MISC_REGS_EFUSE_6_STATUS_1) EFUSE_6_1 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_1_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_6_STATUS_1) EFUSE_6_1 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_6_STATUS_1_EFUSE_6_STATUS_1_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_6_STATUS_1)  Position */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_1_EFUSE_6_STATUS_1_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_6_STATUS_1_EFUSE_6_STATUS_1_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_STATUS_1)  Mask */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_1_EFUSE_6_STATUS_1(value) (EFUSE_MISC_REGS_EFUSE_6_STATUS_1_EFUSE_6_STATUS_1_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_6_STATUS_1_EFUSE_6_STATUS_1_Pos))
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_1_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_6_STATUS_1) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_6_STATUS_1_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_1_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_6_STATUS_1) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_6_STATUS_2 : (EFUSE_MISC_REGS Offset: 0xd4) (R/ 32) EFUSE_6_2 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_6_STATUS_2:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_6_STATUS_2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_6_STATUS_2_OFFSET 0xD4                                          /**<  (EFUSE_MISC_REGS_EFUSE_6_STATUS_2) EFUSE_6_2 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_2_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_6_STATUS_2) EFUSE_6_2 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_6_STATUS_2_EFUSE_6_STATUS_2_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_6_STATUS_2)  Position */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_2_EFUSE_6_STATUS_2_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_6_STATUS_2_EFUSE_6_STATUS_2_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_STATUS_2)  Mask */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_2_EFUSE_6_STATUS_2(value) (EFUSE_MISC_REGS_EFUSE_6_STATUS_2_EFUSE_6_STATUS_2_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_6_STATUS_2_EFUSE_6_STATUS_2_Pos))
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_2_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_6_STATUS_2) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_6_STATUS_2_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_2_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_6_STATUS_2) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_6_STATUS_3 : (EFUSE_MISC_REGS Offset: 0xd8) (R/ 32) EFUSE_6_3 Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t EFUSE_6_STATUS_3:32;       /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_6_STATUS_3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_6_STATUS_3_OFFSET 0xD8                                          /**<  (EFUSE_MISC_REGS_EFUSE_6_STATUS_3) EFUSE_6_3 Status  Offset */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_3_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_6_STATUS_3) EFUSE_6_3 Status  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_6_STATUS_3_EFUSE_6_STATUS_3_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_6_STATUS_3)  Position */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_3_EFUSE_6_STATUS_3_Msk (0xFFFFFFFFu << EFUSE_MISC_REGS_EFUSE_6_STATUS_3_EFUSE_6_STATUS_3_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_6_STATUS_3)  Mask */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_3_EFUSE_6_STATUS_3(value) (EFUSE_MISC_REGS_EFUSE_6_STATUS_3_EFUSE_6_STATUS_3_Msk & ((value) << EFUSE_MISC_REGS_EFUSE_6_STATUS_3_EFUSE_6_STATUS_3_Pos))
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_3_MASK 0xFFFFFFFFu                                    /**< \deprecated (EFUSE_MISC_REGS_EFUSE_6_STATUS_3) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_6_STATUS_3_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_6_STATUS_3_Msk 0xFFFFFFFFu                                    /**< (EFUSE_MISC_REGS_EFUSE_6_STATUS_3) Register Mask  */

/* -------- EFUSE_MISC_REGS_EFUSE_MISC_CTRL : (EFUSE_MISC_REGS Offset: 0xdc) (R/ 8) EFUSE 6 Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  OUT_OF_RESET:1;            /**< bit:      0  Read back the status of the eFuse out of reset */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} EFUSE_MISC_REGS_EFUSE_MISC_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define EFUSE_MISC_REGS_EFUSE_MISC_CTRL_OFFSET 0xDC                                          /**<  (EFUSE_MISC_REGS_EFUSE_MISC_CTRL) EFUSE 6 Control Register  Offset */
#define EFUSE_MISC_REGS_EFUSE_MISC_CTRL_RESETVALUE 0x00u                                         /**<  (EFUSE_MISC_REGS_EFUSE_MISC_CTRL) EFUSE 6 Control Register  Reset Value */

#define EFUSE_MISC_REGS_EFUSE_MISC_CTRL_OUT_OF_RESET_Pos 0                                              /**< (EFUSE_MISC_REGS_EFUSE_MISC_CTRL) Read back the status of the eFuse out of reset Position */
#define EFUSE_MISC_REGS_EFUSE_MISC_CTRL_OUT_OF_RESET_Msk (0x1u << EFUSE_MISC_REGS_EFUSE_MISC_CTRL_OUT_OF_RESET_Pos)  /**< (EFUSE_MISC_REGS_EFUSE_MISC_CTRL) Read back the status of the eFuse out of reset Mask */
#define EFUSE_MISC_REGS_EFUSE_MISC_CTRL_OUT_OF_RESET EFUSE_MISC_REGS_EFUSE_MISC_CTRL_OUT_OF_RESET_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use EFUSE_MISC_REGS_EFUSE_MISC_CTRL_OUT_OF_RESET_Msk instead */
#define EFUSE_MISC_REGS_EFUSE_MISC_CTRL_MASK 0x01u                                          /**< \deprecated (EFUSE_MISC_REGS_EFUSE_MISC_CTRL) Register MASK  (Use EFUSE_MISC_REGS_EFUSE_MISC_CTRL_Msk instead)  */
#define EFUSE_MISC_REGS_EFUSE_MISC_CTRL_Msk 0x01u                                          /**< (EFUSE_MISC_REGS_EFUSE_MISC_CTRL) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief EFUSE_MISC_REGS hardware registers */
typedef struct {  /* EFUSE Misc Registers */
  RwReg8  EFUSE_GLOBAL_RESET; /**< (EFUSE_MISC_REGS Offset: 0x00) Active Low Global Reset */
  __I  uint8_t  Reserved1[3];
  RwReg   EFUSE_1_CONTROL; /**< (EFUSE_MISC_REGS Offset: 0x04) EFUSE 1 Control Register */
  RwReg   EFUSE_2_CONTROL; /**< (EFUSE_MISC_REGS Offset: 0x08) EFUSE 2 Control Register */
  RwReg   EFUSE_3_CONTROL; /**< (EFUSE_MISC_REGS Offset: 0x0C) EFUSE 3 Control Register */
  RwReg   EFUSE_4_CONTROL; /**< (EFUSE_MISC_REGS Offset: 0x10) EFUSE 4 Control Register */
  RwReg   EFUSE_5_CONTROL; /**< (EFUSE_MISC_REGS Offset: 0x14) EFUSE 5 Control Register */
  RwReg   EFUSE_6_CONTROL; /**< (EFUSE_MISC_REGS Offset: 0x18) EFUSE 6 Control Register */
  RwReg   EFUSE_1_PROG_0; /**< (EFUSE_MISC_REGS Offset: 0x1C) EFUSE_1_0 Program Register */
  RwReg   EFUSE_1_PROG_1; /**< (EFUSE_MISC_REGS Offset: 0x20) EFUSE_1_1 Program Register */
  RwReg   EFUSE_1_PROG_2; /**< (EFUSE_MISC_REGS Offset: 0x24) EFUSE_1_2 Program Register */
  RwReg   EFUSE_1_PROG_3; /**< (EFUSE_MISC_REGS Offset: 0x28) EFUSE_1_3 Program Register */
  RoReg   EFUSE_1_STATUS_0; /**< (EFUSE_MISC_REGS Offset: 0x2C) EFUSE_1_0 Status */
  RoReg   EFUSE_1_STATUS_1; /**< (EFUSE_MISC_REGS Offset: 0x30) EFUSE_1_1 Status */
  RoReg   EFUSE_1_STATUS_2; /**< (EFUSE_MISC_REGS Offset: 0x34) EFUSE_1_2 Status */
  RoReg   EFUSE_1_STATUS_3; /**< (EFUSE_MISC_REGS Offset: 0x38) EFUSE_1_3 Status */
  RwReg   EFUSE_2_PROG_0; /**< (EFUSE_MISC_REGS Offset: 0x3C) EFUSE_2_0 Program Register */
  RwReg   EFUSE_2_PROG_1; /**< (EFUSE_MISC_REGS Offset: 0x40) EFUSE_2_1 Program Register */
  RwReg   EFUSE_2_PROG_2; /**< (EFUSE_MISC_REGS Offset: 0x44) EFUSE_2_2 Program Register */
  RwReg   EFUSE_2_PROG_3; /**< (EFUSE_MISC_REGS Offset: 0x48) EFUSE_2_3 Program Register */
  RoReg   EFUSE_2_STATUS_0; /**< (EFUSE_MISC_REGS Offset: 0x4C) EFUSE_2_0 Status */
  RoReg   EFUSE_2_STATUS_1; /**< (EFUSE_MISC_REGS Offset: 0x50) EFUSE_2_1 Status */
  RoReg   EFUSE_2_STATUS_2; /**< (EFUSE_MISC_REGS Offset: 0x54) EFUSE_2_2 Status */
  RoReg   EFUSE_2_STATUS_3; /**< (EFUSE_MISC_REGS Offset: 0x58) EFUSE_2_3 Status */
  RwReg   EFUSE_3_PROG_0; /**< (EFUSE_MISC_REGS Offset: 0x5C) EFUSE_3_0 Program Register */
  RwReg   EFUSE_3_PROG_1; /**< (EFUSE_MISC_REGS Offset: 0x60) EFUSE_3_1 Program Register */
  RwReg   EFUSE_3_PROG_2; /**< (EFUSE_MISC_REGS Offset: 0x64) EFUSE_3_2 Program Register */
  RwReg   EFUSE_3_PROG_3; /**< (EFUSE_MISC_REGS Offset: 0x68) EFUSE_3_3 Program Register */
  RoReg   EFUSE_3_STATUS_0; /**< (EFUSE_MISC_REGS Offset: 0x6C) EFUSE_3_0 Status */
  RoReg   EFUSE_3_STATUS_1; /**< (EFUSE_MISC_REGS Offset: 0x70) EFUSE_3_1 Status */
  RoReg   EFUSE_3_STATUS_2; /**< (EFUSE_MISC_REGS Offset: 0x74) EFUSE_3_2 Status */
  RoReg   EFUSE_3_STATUS_3; /**< (EFUSE_MISC_REGS Offset: 0x78) EFUSE_3_3 Status */
  RwReg   EFUSE_4_PROG_0; /**< (EFUSE_MISC_REGS Offset: 0x7C) EFUSE_4_0 Program Register */
  RwReg   EFUSE_4_PROG_1; /**< (EFUSE_MISC_REGS Offset: 0x80) EFUSE_4_1 Program Register */
  RwReg   EFUSE_4_PROG_2; /**< (EFUSE_MISC_REGS Offset: 0x84) EFUSE_4_2 Program Register */
  RwReg   EFUSE_4_PROG_3; /**< (EFUSE_MISC_REGS Offset: 0x88) EFUSE_4_3 Program Register */
  RoReg   EFUSE_4_STATUS_0; /**< (EFUSE_MISC_REGS Offset: 0x8C) EFUSE_4_0 Status */
  RoReg   EFUSE_4_STATUS_1; /**< (EFUSE_MISC_REGS Offset: 0x90) EFUSE_4_1 Status */
  RoReg   EFUSE_4_STATUS_2; /**< (EFUSE_MISC_REGS Offset: 0x94) EFUSE_4_2 Status */
  RoReg   EFUSE_4_STATUS_3; /**< (EFUSE_MISC_REGS Offset: 0x98) EFUSE_4_3 Status */
  RwReg   EFUSE_5_PROG_0; /**< (EFUSE_MISC_REGS Offset: 0x9C) EFUSE_4_0 Program Register */
  RwReg   EFUSE_5_PROG_1; /**< (EFUSE_MISC_REGS Offset: 0xA0) EFUSE_5_1 Program Register */
  RwReg   EFUSE_5_PROG_2; /**< (EFUSE_MISC_REGS Offset: 0xA4) EFUSE_5_2 Program Register */
  RwReg   EFUSE_5_PROG_3; /**< (EFUSE_MISC_REGS Offset: 0xA8) EFUSE_5_3 Program Register */
  RoReg   EFUSE_5_STATUS_0; /**< (EFUSE_MISC_REGS Offset: 0xAC) EFUSE_5_0 Status */
  RoReg   EFUSE_5_STATUS_1; /**< (EFUSE_MISC_REGS Offset: 0xB0) EFUSE_5_1 Status */
  RoReg   EFUSE_5_STATUS_2; /**< (EFUSE_MISC_REGS Offset: 0xB4) EFUSE_5_2 Status */
  RoReg   EFUSE_5_STATUS_3; /**< (EFUSE_MISC_REGS Offset: 0xB8) EFUSE_5_3 Status */
  RwReg   EFUSE_6_PROG_0; /**< (EFUSE_MISC_REGS Offset: 0xBC) EFUSE_6_0 Program Register */
  RwReg   EFUSE_6_PROG_1; /**< (EFUSE_MISC_REGS Offset: 0xC0) EFUSE_6_1 Program Register */
  RwReg   EFUSE_6_PROG_2; /**< (EFUSE_MISC_REGS Offset: 0xC4) EFUSE_6_2 Program Register */
  RwReg   EFUSE_6_PROG_3; /**< (EFUSE_MISC_REGS Offset: 0xC8) EFUSE_6_3 Program Register */
  RoReg   EFUSE_6_STATUS_0; /**< (EFUSE_MISC_REGS Offset: 0xCC) EFUSE_6_0 Status */
  RoReg   EFUSE_6_STATUS_1; /**< (EFUSE_MISC_REGS Offset: 0xD0) EFUSE_6_1 Status */
  RoReg   EFUSE_6_STATUS_2; /**< (EFUSE_MISC_REGS Offset: 0xD4) EFUSE_6_2 Status */
  RoReg   EFUSE_6_STATUS_3; /**< (EFUSE_MISC_REGS Offset: 0xD8) EFUSE_6_3 Status */
  RoReg8  EFUSE_MISC_CTRL; /**< (EFUSE_MISC_REGS Offset: 0xDC) EFUSE 6 Control Register */
} EfuseMiscRegs;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief EFUSE_MISC_REGS hardware registers */
typedef struct {  /* EFUSE Misc Registers */
  __IO EFUSE_MISC_REGS_EFUSE_GLOBAL_RESET_Type EFUSE_GLOBAL_RESET; /**< Offset: 0x00 (R/W   8) Active Low Global Reset */
       RoReg8                         Reserved1[0x3];
  __IO EFUSE_MISC_REGS_EFUSE_1_CONTROL_Type EFUSE_1_CONTROL; /**< Offset: 0x04 (R/W  32) EFUSE 1 Control Register */
  __IO EFUSE_MISC_REGS_EFUSE_2_CONTROL_Type EFUSE_2_CONTROL; /**< Offset: 0x08 (R/W  32) EFUSE 2 Control Register */
  __IO EFUSE_MISC_REGS_EFUSE_3_CONTROL_Type EFUSE_3_CONTROL; /**< Offset: 0x0C (R/W  32) EFUSE 3 Control Register */
  __IO EFUSE_MISC_REGS_EFUSE_4_CONTROL_Type EFUSE_4_CONTROL; /**< Offset: 0x10 (R/W  32) EFUSE 4 Control Register */
  __IO EFUSE_MISC_REGS_EFUSE_5_CONTROL_Type EFUSE_5_CONTROL; /**< Offset: 0x14 (R/W  32) EFUSE 5 Control Register */
  __IO EFUSE_MISC_REGS_EFUSE_6_CONTROL_Type EFUSE_6_CONTROL; /**< Offset: 0x18 (R/W  32) EFUSE 6 Control Register */
  __IO EFUSE_MISC_REGS_EFUSE_1_PROG_0_Type EFUSE_1_PROG_0; /**< Offset: 0x1C (R/W  32) EFUSE_1_0 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_1_PROG_1_Type EFUSE_1_PROG_1; /**< Offset: 0x20 (R/W  32) EFUSE_1_1 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_1_PROG_2_Type EFUSE_1_PROG_2; /**< Offset: 0x24 (R/W  32) EFUSE_1_2 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_1_PROG_3_Type EFUSE_1_PROG_3; /**< Offset: 0x28 (R/W  32) EFUSE_1_3 Program Register */
  __I  EFUSE_MISC_REGS_EFUSE_1_STATUS_0_Type EFUSE_1_STATUS_0; /**< Offset: 0x2C (R/   32) EFUSE_1_0 Status */
  __I  EFUSE_MISC_REGS_EFUSE_1_STATUS_1_Type EFUSE_1_STATUS_1; /**< Offset: 0x30 (R/   32) EFUSE_1_1 Status */
  __I  EFUSE_MISC_REGS_EFUSE_1_STATUS_2_Type EFUSE_1_STATUS_2; /**< Offset: 0x34 (R/   32) EFUSE_1_2 Status */
  __I  EFUSE_MISC_REGS_EFUSE_1_STATUS_3_Type EFUSE_1_STATUS_3; /**< Offset: 0x38 (R/   32) EFUSE_1_3 Status */
  __IO EFUSE_MISC_REGS_EFUSE_2_PROG_0_Type EFUSE_2_PROG_0; /**< Offset: 0x3C (R/W  32) EFUSE_2_0 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_2_PROG_1_Type EFUSE_2_PROG_1; /**< Offset: 0x40 (R/W  32) EFUSE_2_1 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_2_PROG_2_Type EFUSE_2_PROG_2; /**< Offset: 0x44 (R/W  32) EFUSE_2_2 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_2_PROG_3_Type EFUSE_2_PROG_3; /**< Offset: 0x48 (R/W  32) EFUSE_2_3 Program Register */
  __I  EFUSE_MISC_REGS_EFUSE_2_STATUS_0_Type EFUSE_2_STATUS_0; /**< Offset: 0x4C (R/   32) EFUSE_2_0 Status */
  __I  EFUSE_MISC_REGS_EFUSE_2_STATUS_1_Type EFUSE_2_STATUS_1; /**< Offset: 0x50 (R/   32) EFUSE_2_1 Status */
  __I  EFUSE_MISC_REGS_EFUSE_2_STATUS_2_Type EFUSE_2_STATUS_2; /**< Offset: 0x54 (R/   32) EFUSE_2_2 Status */
  __I  EFUSE_MISC_REGS_EFUSE_2_STATUS_3_Type EFUSE_2_STATUS_3; /**< Offset: 0x58 (R/   32) EFUSE_2_3 Status */
  __IO EFUSE_MISC_REGS_EFUSE_3_PROG_0_Type EFUSE_3_PROG_0; /**< Offset: 0x5C (R/W  32) EFUSE_3_0 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_3_PROG_1_Type EFUSE_3_PROG_1; /**< Offset: 0x60 (R/W  32) EFUSE_3_1 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_3_PROG_2_Type EFUSE_3_PROG_2; /**< Offset: 0x64 (R/W  32) EFUSE_3_2 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_3_PROG_3_Type EFUSE_3_PROG_3; /**< Offset: 0x68 (R/W  32) EFUSE_3_3 Program Register */
  __I  EFUSE_MISC_REGS_EFUSE_3_STATUS_0_Type EFUSE_3_STATUS_0; /**< Offset: 0x6C (R/   32) EFUSE_3_0 Status */
  __I  EFUSE_MISC_REGS_EFUSE_3_STATUS_1_Type EFUSE_3_STATUS_1; /**< Offset: 0x70 (R/   32) EFUSE_3_1 Status */
  __I  EFUSE_MISC_REGS_EFUSE_3_STATUS_2_Type EFUSE_3_STATUS_2; /**< Offset: 0x74 (R/   32) EFUSE_3_2 Status */
  __I  EFUSE_MISC_REGS_EFUSE_3_STATUS_3_Type EFUSE_3_STATUS_3; /**< Offset: 0x78 (R/   32) EFUSE_3_3 Status */
  __IO EFUSE_MISC_REGS_EFUSE_4_PROG_0_Type EFUSE_4_PROG_0; /**< Offset: 0x7C (R/W  32) EFUSE_4_0 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_4_PROG_1_Type EFUSE_4_PROG_1; /**< Offset: 0x80 (R/W  32) EFUSE_4_1 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_4_PROG_2_Type EFUSE_4_PROG_2; /**< Offset: 0x84 (R/W  32) EFUSE_4_2 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_4_PROG_3_Type EFUSE_4_PROG_3; /**< Offset: 0x88 (R/W  32) EFUSE_4_3 Program Register */
  __I  EFUSE_MISC_REGS_EFUSE_4_STATUS_0_Type EFUSE_4_STATUS_0; /**< Offset: 0x8C (R/   32) EFUSE_4_0 Status */
  __I  EFUSE_MISC_REGS_EFUSE_4_STATUS_1_Type EFUSE_4_STATUS_1; /**< Offset: 0x90 (R/   32) EFUSE_4_1 Status */
  __I  EFUSE_MISC_REGS_EFUSE_4_STATUS_2_Type EFUSE_4_STATUS_2; /**< Offset: 0x94 (R/   32) EFUSE_4_2 Status */
  __I  EFUSE_MISC_REGS_EFUSE_4_STATUS_3_Type EFUSE_4_STATUS_3; /**< Offset: 0x98 (R/   32) EFUSE_4_3 Status */
  __IO EFUSE_MISC_REGS_EFUSE_5_PROG_0_Type EFUSE_5_PROG_0; /**< Offset: 0x9C (R/W  32) EFUSE_4_0 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_5_PROG_1_Type EFUSE_5_PROG_1; /**< Offset: 0xA0 (R/W  32) EFUSE_5_1 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_5_PROG_2_Type EFUSE_5_PROG_2; /**< Offset: 0xA4 (R/W  32) EFUSE_5_2 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_5_PROG_3_Type EFUSE_5_PROG_3; /**< Offset: 0xA8 (R/W  32) EFUSE_5_3 Program Register */
  __I  EFUSE_MISC_REGS_EFUSE_5_STATUS_0_Type EFUSE_5_STATUS_0; /**< Offset: 0xAC (R/   32) EFUSE_5_0 Status */
  __I  EFUSE_MISC_REGS_EFUSE_5_STATUS_1_Type EFUSE_5_STATUS_1; /**< Offset: 0xB0 (R/   32) EFUSE_5_1 Status */
  __I  EFUSE_MISC_REGS_EFUSE_5_STATUS_2_Type EFUSE_5_STATUS_2; /**< Offset: 0xB4 (R/   32) EFUSE_5_2 Status */
  __I  EFUSE_MISC_REGS_EFUSE_5_STATUS_3_Type EFUSE_5_STATUS_3; /**< Offset: 0xB8 (R/   32) EFUSE_5_3 Status */
  __IO EFUSE_MISC_REGS_EFUSE_6_PROG_0_Type EFUSE_6_PROG_0; /**< Offset: 0xBC (R/W  32) EFUSE_6_0 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_6_PROG_1_Type EFUSE_6_PROG_1; /**< Offset: 0xC0 (R/W  32) EFUSE_6_1 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_6_PROG_2_Type EFUSE_6_PROG_2; /**< Offset: 0xC4 (R/W  32) EFUSE_6_2 Program Register */
  __IO EFUSE_MISC_REGS_EFUSE_6_PROG_3_Type EFUSE_6_PROG_3; /**< Offset: 0xC8 (R/W  32) EFUSE_6_3 Program Register */
  __I  EFUSE_MISC_REGS_EFUSE_6_STATUS_0_Type EFUSE_6_STATUS_0; /**< Offset: 0xCC (R/   32) EFUSE_6_0 Status */
  __I  EFUSE_MISC_REGS_EFUSE_6_STATUS_1_Type EFUSE_6_STATUS_1; /**< Offset: 0xD0 (R/   32) EFUSE_6_1 Status */
  __I  EFUSE_MISC_REGS_EFUSE_6_STATUS_2_Type EFUSE_6_STATUS_2; /**< Offset: 0xD4 (R/   32) EFUSE_6_2 Status */
  __I  EFUSE_MISC_REGS_EFUSE_6_STATUS_3_Type EFUSE_6_STATUS_3; /**< Offset: 0xD8 (R/   32) EFUSE_6_3 Status */
  __I  EFUSE_MISC_REGS_EFUSE_MISC_CTRL_Type EFUSE_MISC_CTRL; /**< Offset: 0xDC (R/    8) EFUSE 6 Control Register */
} EfuseMiscRegs;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_EFUSE_MISC_REGS_COMPONENT_ */
