/**
 * \file
 *
 * \brief Component description for DUALTIMER
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

#ifndef _SAMB11_DUALTIMER_COMPONENT_
#define _SAMB11_DUALTIMER_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR DUALTIMER */
/* ========================================================================== */
/** \addtogroup SAMB11_DUALTIMER ARM General Purpose Dual Timer 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define DUALTIMER_DT1234
#define REV_DUALTIMER                    0x100

/* -------- DUALTIMER_TIMER1LOAD : (DUALTIMER Offset: 0x00) (R/W 32) Timer 1 Load Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t TIMER1LOAD:32;             /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DUALTIMER_TIMER1LOAD_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER1LOAD_OFFSET         0x00                                          /**<  (DUALTIMER_TIMER1LOAD) Timer 1 Load Register  Offset */
#define DUALTIMER_TIMER1LOAD_RESETVALUE     0x00u                                         /**<  (DUALTIMER_TIMER1LOAD) Timer 1 Load Register  Reset Value */

#define DUALTIMER_TIMER1LOAD_TIMER1LOAD_Pos 0                                              /**< (DUALTIMER_TIMER1LOAD)  Position */
#define DUALTIMER_TIMER1LOAD_TIMER1LOAD_Msk (0xFFFFFFFFu << DUALTIMER_TIMER1LOAD_TIMER1LOAD_Pos)  /**< (DUALTIMER_TIMER1LOAD)  Mask */
#define DUALTIMER_TIMER1LOAD_TIMER1LOAD(value) (DUALTIMER_TIMER1LOAD_TIMER1LOAD_Msk & ((value) << DUALTIMER_TIMER1LOAD_TIMER1LOAD_Pos))
#define DUALTIMER_TIMER1LOAD_MASK           0xFFFFFFFFu                                    /**< \deprecated (DUALTIMER_TIMER1LOAD) Register MASK  (Use DUALTIMER_TIMER1LOAD_Msk instead)  */
#define DUALTIMER_TIMER1LOAD_Msk            0xFFFFFFFFu                                    /**< (DUALTIMER_TIMER1LOAD) Register Mask  */

/* -------- DUALTIMER_TIMER1VALUE : (DUALTIMER Offset: 0x04) (R/ 32) Timer 1 Current Value Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t TIMER1VALUE:32;            /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DUALTIMER_TIMER1VALUE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER1VALUE_OFFSET        0x04                                          /**<  (DUALTIMER_TIMER1VALUE) Timer 1 Current Value Register  Offset */
#define DUALTIMER_TIMER1VALUE_RESETVALUE    0xFFFFFFFFu                                   /**<  (DUALTIMER_TIMER1VALUE) Timer 1 Current Value Register  Reset Value */

#define DUALTIMER_TIMER1VALUE_TIMER1VALUE_Pos 0                                              /**< (DUALTIMER_TIMER1VALUE)  Position */
#define DUALTIMER_TIMER1VALUE_TIMER1VALUE_Msk (0xFFFFFFFFu << DUALTIMER_TIMER1VALUE_TIMER1VALUE_Pos)  /**< (DUALTIMER_TIMER1VALUE)  Mask */
#define DUALTIMER_TIMER1VALUE_TIMER1VALUE(value) (DUALTIMER_TIMER1VALUE_TIMER1VALUE_Msk & ((value) << DUALTIMER_TIMER1VALUE_TIMER1VALUE_Pos))
#define DUALTIMER_TIMER1VALUE_MASK          0xFFFFFFFFu                                    /**< \deprecated (DUALTIMER_TIMER1VALUE) Register MASK  (Use DUALTIMER_TIMER1VALUE_Msk instead)  */
#define DUALTIMER_TIMER1VALUE_Msk           0xFFFFFFFFu                                    /**< (DUALTIMER_TIMER1VALUE) Register Mask  */

/* -------- DUALTIMER_TIMER1CONTROL : (DUALTIMER Offset: 0x08) (R/W 8) Timer 1 Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ONE_SHOT_COUNT:1;          /**< bit:      0  Mode Select                              */
    uint8_t  TIMER_SIZE:1;              /**< bit:      1  Timer Size                               */
    uint8_t  TIMERPRE:2;                /**< bit:   2..3  Prescale Bits                            */
    uint8_t  RESERVED4:1;               /**< bit:      4  Reserved bit do not use                  */
    uint8_t  INTERRUPT_ENABLE:1;        /**< bit:      5  Active High Interrupt Enable Bit         */
    uint8_t  TIMER_MODE:1;              /**< bit:      6  Mode Bit                                 */
    uint8_t  TIMER_ENABLE:1;            /**< bit:      7  Active High Timer Enable                 */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMER1CONTROL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER1CONTROL_OFFSET      0x08                                          /**<  (DUALTIMER_TIMER1CONTROL) Timer 1 Control Register  Offset */
#define DUALTIMER_TIMER1CONTROL_RESETVALUE  0x20u                                         /**<  (DUALTIMER_TIMER1CONTROL) Timer 1 Control Register  Reset Value */

#define DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_Pos 0                                              /**< (DUALTIMER_TIMER1CONTROL) Mode Select Position */
#define DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_Msk (0x1u << DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_Pos)  /**< (DUALTIMER_TIMER1CONTROL) Mode Select Mask */
#define DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_Msk instead */
#define   DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_0_Val 0x0u                                           /**< (DUALTIMER_TIMER1CONTROL) Wrapping Mode  */
#define   DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_1_Val 0x1u                                           /**< (DUALTIMER_TIMER1CONTROL) One-Shot Mode  */
#define DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_0 (DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_0_Val << DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_Pos)  /**< (DUALTIMER_TIMER1CONTROL) Wrapping Mode Position  */
#define DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_1 (DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_1_Val << DUALTIMER_TIMER1CONTROL_ONE_SHOT_COUNT_Pos)  /**< (DUALTIMER_TIMER1CONTROL) One-Shot Mode Position  */
#define DUALTIMER_TIMER1CONTROL_TIMER_SIZE_Pos 1                                              /**< (DUALTIMER_TIMER1CONTROL) Timer Size Position */
#define DUALTIMER_TIMER1CONTROL_TIMER_SIZE_Msk (0x1u << DUALTIMER_TIMER1CONTROL_TIMER_SIZE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) Timer Size Mask */
#define DUALTIMER_TIMER1CONTROL_TIMER_SIZE  DUALTIMER_TIMER1CONTROL_TIMER_SIZE_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER1CONTROL_TIMER_SIZE_Msk instead */
#define   DUALTIMER_TIMER1CONTROL_TIMER_SIZE_0_Val 0x0u                                           /**< (DUALTIMER_TIMER1CONTROL) 16-bit Counter  */
#define   DUALTIMER_TIMER1CONTROL_TIMER_SIZE_1_Val 0x1u                                           /**< (DUALTIMER_TIMER1CONTROL) 32-bit Counter  */
#define DUALTIMER_TIMER1CONTROL_TIMER_SIZE_0 (DUALTIMER_TIMER1CONTROL_TIMER_SIZE_0_Val << DUALTIMER_TIMER1CONTROL_TIMER_SIZE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) 16-bit Counter Position  */
#define DUALTIMER_TIMER1CONTROL_TIMER_SIZE_1 (DUALTIMER_TIMER1CONTROL_TIMER_SIZE_1_Val << DUALTIMER_TIMER1CONTROL_TIMER_SIZE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) 32-bit Counter Position  */
#define DUALTIMER_TIMER1CONTROL_TIMERPRE_Pos 2                                              /**< (DUALTIMER_TIMER1CONTROL) Prescale Bits Position */
#define DUALTIMER_TIMER1CONTROL_TIMERPRE_Msk (0x3u << DUALTIMER_TIMER1CONTROL_TIMERPRE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) Prescale Bits Mask */
#define DUALTIMER_TIMER1CONTROL_TIMERPRE(value) (DUALTIMER_TIMER1CONTROL_TIMERPRE_Msk & ((value) << DUALTIMER_TIMER1CONTROL_TIMERPRE_Pos))
#define   DUALTIMER_TIMER1CONTROL_TIMERPRE_0_Val 0x0u                                           /**< (DUALTIMER_TIMER1CONTROL) 0 Stages, Clock Divided by 1  */
#define   DUALTIMER_TIMER1CONTROL_TIMERPRE_1_Val 0x1u                                           /**< (DUALTIMER_TIMER1CONTROL) 4 Stages, Clock Divided by 16  */
#define   DUALTIMER_TIMER1CONTROL_TIMERPRE_2_Val 0x2u                                           /**< (DUALTIMER_TIMER1CONTROL) 8 Stages, Clock Divided by 256  */
#define   DUALTIMER_TIMER1CONTROL_TIMERPRE_3_Val 0x3u                                           /**< (DUALTIMER_TIMER1CONTROL) Undefined, do not use  */
#define DUALTIMER_TIMER1CONTROL_TIMERPRE_0  (DUALTIMER_TIMER1CONTROL_TIMERPRE_0_Val << DUALTIMER_TIMER1CONTROL_TIMERPRE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) 0 Stages, Clock Divided by 1 Position  */
#define DUALTIMER_TIMER1CONTROL_TIMERPRE_1  (DUALTIMER_TIMER1CONTROL_TIMERPRE_1_Val << DUALTIMER_TIMER1CONTROL_TIMERPRE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) 4 Stages, Clock Divided by 16 Position  */
#define DUALTIMER_TIMER1CONTROL_TIMERPRE_2  (DUALTIMER_TIMER1CONTROL_TIMERPRE_2_Val << DUALTIMER_TIMER1CONTROL_TIMERPRE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) 8 Stages, Clock Divided by 256 Position  */
#define DUALTIMER_TIMER1CONTROL_TIMERPRE_3  (DUALTIMER_TIMER1CONTROL_TIMERPRE_3_Val << DUALTIMER_TIMER1CONTROL_TIMERPRE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) Undefined, do not use Position  */
#define DUALTIMER_TIMER1CONTROL_RESERVED4_Pos 4                                              /**< (DUALTIMER_TIMER1CONTROL) Reserved bit do not use Position */
#define DUALTIMER_TIMER1CONTROL_RESERVED4_Msk (0x1u << DUALTIMER_TIMER1CONTROL_RESERVED4_Pos)  /**< (DUALTIMER_TIMER1CONTROL) Reserved bit do not use Mask */
#define DUALTIMER_TIMER1CONTROL_RESERVED4   DUALTIMER_TIMER1CONTROL_RESERVED4_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER1CONTROL_RESERVED4_Msk instead */
#define DUALTIMER_TIMER1CONTROL_INTERRUPT_ENABLE_Pos 5                                              /**< (DUALTIMER_TIMER1CONTROL) Active High Interrupt Enable Bit Position */
#define DUALTIMER_TIMER1CONTROL_INTERRUPT_ENABLE_Msk (0x1u << DUALTIMER_TIMER1CONTROL_INTERRUPT_ENABLE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) Active High Interrupt Enable Bit Mask */
#define DUALTIMER_TIMER1CONTROL_INTERRUPT_ENABLE DUALTIMER_TIMER1CONTROL_INTERRUPT_ENABLE_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER1CONTROL_INTERRUPT_ENABLE_Msk instead */
#define DUALTIMER_TIMER1CONTROL_TIMER_MODE_Pos 6                                              /**< (DUALTIMER_TIMER1CONTROL) Mode Bit Position */
#define DUALTIMER_TIMER1CONTROL_TIMER_MODE_Msk (0x1u << DUALTIMER_TIMER1CONTROL_TIMER_MODE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) Mode Bit Mask */
#define DUALTIMER_TIMER1CONTROL_TIMER_MODE  DUALTIMER_TIMER1CONTROL_TIMER_MODE_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER1CONTROL_TIMER_MODE_Msk instead */
#define   DUALTIMER_TIMER1CONTROL_TIMER_MODE_0_Val 0x0u                                           /**< (DUALTIMER_TIMER1CONTROL) Free-Running Mode  */
#define   DUALTIMER_TIMER1CONTROL_TIMER_MODE_1_Val 0x1u                                           /**< (DUALTIMER_TIMER1CONTROL) Periodic Mode  */
#define DUALTIMER_TIMER1CONTROL_TIMER_MODE_0 (DUALTIMER_TIMER1CONTROL_TIMER_MODE_0_Val << DUALTIMER_TIMER1CONTROL_TIMER_MODE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) Free-Running Mode Position  */
#define DUALTIMER_TIMER1CONTROL_TIMER_MODE_1 (DUALTIMER_TIMER1CONTROL_TIMER_MODE_1_Val << DUALTIMER_TIMER1CONTROL_TIMER_MODE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) Periodic Mode Position  */
#define DUALTIMER_TIMER1CONTROL_TIMER_ENABLE_Pos 7                                              /**< (DUALTIMER_TIMER1CONTROL) Active High Timer Enable Position */
#define DUALTIMER_TIMER1CONTROL_TIMER_ENABLE_Msk (0x1u << DUALTIMER_TIMER1CONTROL_TIMER_ENABLE_Pos)  /**< (DUALTIMER_TIMER1CONTROL) Active High Timer Enable Mask */
#define DUALTIMER_TIMER1CONTROL_TIMER_ENABLE DUALTIMER_TIMER1CONTROL_TIMER_ENABLE_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER1CONTROL_TIMER_ENABLE_Msk instead */
#define DUALTIMER_TIMER1CONTROL_MASK        0xFFu                                          /**< \deprecated (DUALTIMER_TIMER1CONTROL) Register MASK  (Use DUALTIMER_TIMER1CONTROL_Msk instead)  */
#define DUALTIMER_TIMER1CONTROL_Msk         0xFFu                                          /**< (DUALTIMER_TIMER1CONTROL) Register Mask  */

/* -------- DUALTIMER_TIMER1INTCLR : (DUALTIMER Offset: 0x0c) (/W 8) Timer 1 Interrupt Clear Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMER1INTCLR:1;            /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMER1INTCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER1INTCLR_OFFSET       0x0C                                          /**<  (DUALTIMER_TIMER1INTCLR) Timer 1 Interrupt Clear Register  Offset */
#define DUALTIMER_TIMER1INTCLR_RESETVALUE   0x00u                                         /**<  (DUALTIMER_TIMER1INTCLR) Timer 1 Interrupt Clear Register  Reset Value */

#define DUALTIMER_TIMER1INTCLR_TIMER1INTCLR_Pos 0                                              /**< (DUALTIMER_TIMER1INTCLR)  Position */
#define DUALTIMER_TIMER1INTCLR_TIMER1INTCLR_Msk (0x1u << DUALTIMER_TIMER1INTCLR_TIMER1INTCLR_Pos)  /**< (DUALTIMER_TIMER1INTCLR)  Mask */
#define DUALTIMER_TIMER1INTCLR_TIMER1INTCLR DUALTIMER_TIMER1INTCLR_TIMER1INTCLR_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER1INTCLR_TIMER1INTCLR_Msk instead */
#define DUALTIMER_TIMER1INTCLR_MASK         0x01u                                          /**< \deprecated (DUALTIMER_TIMER1INTCLR) Register MASK  (Use DUALTIMER_TIMER1INTCLR_Msk instead)  */
#define DUALTIMER_TIMER1INTCLR_Msk          0x01u                                          /**< (DUALTIMER_TIMER1INTCLR) Register Mask  */

/* -------- DUALTIMER_TIMER1RIS : (DUALTIMER Offset: 0x10) (R/ 8) Timer 1 Raw Interrupt Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMER1RIS:1;               /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMER1RIS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER1RIS_OFFSET          0x10                                          /**<  (DUALTIMER_TIMER1RIS) Timer 1 Raw Interrupt Status Register  Offset */
#define DUALTIMER_TIMER1RIS_RESETVALUE      0x00u                                         /**<  (DUALTIMER_TIMER1RIS) Timer 1 Raw Interrupt Status Register  Reset Value */

#define DUALTIMER_TIMER1RIS_TIMER1RIS_Pos   0                                              /**< (DUALTIMER_TIMER1RIS)  Position */
#define DUALTIMER_TIMER1RIS_TIMER1RIS_Msk   (0x1u << DUALTIMER_TIMER1RIS_TIMER1RIS_Pos)    /**< (DUALTIMER_TIMER1RIS)  Mask */
#define DUALTIMER_TIMER1RIS_TIMER1RIS       DUALTIMER_TIMER1RIS_TIMER1RIS_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER1RIS_TIMER1RIS_Msk instead */
#define DUALTIMER_TIMER1RIS_MASK            0x01u                                          /**< \deprecated (DUALTIMER_TIMER1RIS) Register MASK  (Use DUALTIMER_TIMER1RIS_Msk instead)  */
#define DUALTIMER_TIMER1RIS_Msk             0x01u                                          /**< (DUALTIMER_TIMER1RIS) Register Mask  */

/* -------- DUALTIMER_TIMER1MIS : (DUALTIMER Offset: 0x14) (R/ 8) Timer 1 Masked Interrupt Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMER1MIS:1;               /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMER1MIS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER1MIS_OFFSET          0x14                                          /**<  (DUALTIMER_TIMER1MIS) Timer 1 Masked Interrupt Status Register  Offset */
#define DUALTIMER_TIMER1MIS_RESETVALUE      0x00u                                         /**<  (DUALTIMER_TIMER1MIS) Timer 1 Masked Interrupt Status Register  Reset Value */

#define DUALTIMER_TIMER1MIS_TIMER1MIS_Pos   0                                              /**< (DUALTIMER_TIMER1MIS)  Position */
#define DUALTIMER_TIMER1MIS_TIMER1MIS_Msk   (0x1u << DUALTIMER_TIMER1MIS_TIMER1MIS_Pos)    /**< (DUALTIMER_TIMER1MIS)  Mask */
#define DUALTIMER_TIMER1MIS_TIMER1MIS       DUALTIMER_TIMER1MIS_TIMER1MIS_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER1MIS_TIMER1MIS_Msk instead */
#define DUALTIMER_TIMER1MIS_MASK            0x01u                                          /**< \deprecated (DUALTIMER_TIMER1MIS) Register MASK  (Use DUALTIMER_TIMER1MIS_Msk instead)  */
#define DUALTIMER_TIMER1MIS_Msk             0x01u                                          /**< (DUALTIMER_TIMER1MIS) Register Mask  */

/* -------- DUALTIMER_TIMER1BGLOAD : (DUALTIMER Offset: 0x18) (R/W 32) Timer 1 Background Load Register (Reload Value for Period Mode) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t TIMER1BGLOAD:32;           /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DUALTIMER_TIMER1BGLOAD_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER1BGLOAD_OFFSET       0x18                                          /**<  (DUALTIMER_TIMER1BGLOAD) Timer 1 Background Load Register (Reload Value for Period Mode)  Offset */
#define DUALTIMER_TIMER1BGLOAD_RESETVALUE   0x00u                                         /**<  (DUALTIMER_TIMER1BGLOAD) Timer 1 Background Load Register (Reload Value for Period Mode)  Reset Value */

#define DUALTIMER_TIMER1BGLOAD_TIMER1BGLOAD_Pos 0                                              /**< (DUALTIMER_TIMER1BGLOAD)  Position */
#define DUALTIMER_TIMER1BGLOAD_TIMER1BGLOAD_Msk (0xFFFFFFFFu << DUALTIMER_TIMER1BGLOAD_TIMER1BGLOAD_Pos)  /**< (DUALTIMER_TIMER1BGLOAD)  Mask */
#define DUALTIMER_TIMER1BGLOAD_TIMER1BGLOAD(value) (DUALTIMER_TIMER1BGLOAD_TIMER1BGLOAD_Msk & ((value) << DUALTIMER_TIMER1BGLOAD_TIMER1BGLOAD_Pos))
#define DUALTIMER_TIMER1BGLOAD_MASK         0xFFFFFFFFu                                    /**< \deprecated (DUALTIMER_TIMER1BGLOAD) Register MASK  (Use DUALTIMER_TIMER1BGLOAD_Msk instead)  */
#define DUALTIMER_TIMER1BGLOAD_Msk          0xFFFFFFFFu                                    /**< (DUALTIMER_TIMER1BGLOAD) Register Mask  */

/* -------- DUALTIMER_TIMER2LOAD : (DUALTIMER Offset: 0x20) (R/W 32) Timer 2 Load Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t TIMER2LOAD:32;             /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DUALTIMER_TIMER2LOAD_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER2LOAD_OFFSET         0x20                                          /**<  (DUALTIMER_TIMER2LOAD) Timer 2 Load Register  Offset */
#define DUALTIMER_TIMER2LOAD_RESETVALUE     0x00u                                         /**<  (DUALTIMER_TIMER2LOAD) Timer 2 Load Register  Reset Value */

#define DUALTIMER_TIMER2LOAD_TIMER2LOAD_Pos 0                                              /**< (DUALTIMER_TIMER2LOAD)  Position */
#define DUALTIMER_TIMER2LOAD_TIMER2LOAD_Msk (0xFFFFFFFFu << DUALTIMER_TIMER2LOAD_TIMER2LOAD_Pos)  /**< (DUALTIMER_TIMER2LOAD)  Mask */
#define DUALTIMER_TIMER2LOAD_TIMER2LOAD(value) (DUALTIMER_TIMER2LOAD_TIMER2LOAD_Msk & ((value) << DUALTIMER_TIMER2LOAD_TIMER2LOAD_Pos))
#define DUALTIMER_TIMER2LOAD_MASK           0xFFFFFFFFu                                    /**< \deprecated (DUALTIMER_TIMER2LOAD) Register MASK  (Use DUALTIMER_TIMER2LOAD_Msk instead)  */
#define DUALTIMER_TIMER2LOAD_Msk            0xFFFFFFFFu                                    /**< (DUALTIMER_TIMER2LOAD) Register Mask  */

/* -------- DUALTIMER_TIMER2VALUE : (DUALTIMER Offset: 0x24) (R/ 32) Timer 2 Current Value Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t TIMER2VALUE:32;            /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DUALTIMER_TIMER2VALUE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER2VALUE_OFFSET        0x24                                          /**<  (DUALTIMER_TIMER2VALUE) Timer 2 Current Value Register  Offset */
#define DUALTIMER_TIMER2VALUE_RESETVALUE    0xFFFFFFFFu                                   /**<  (DUALTIMER_TIMER2VALUE) Timer 2 Current Value Register  Reset Value */

#define DUALTIMER_TIMER2VALUE_TIMER2VALUE_Pos 0                                              /**< (DUALTIMER_TIMER2VALUE)  Position */
#define DUALTIMER_TIMER2VALUE_TIMER2VALUE_Msk (0xFFFFFFFFu << DUALTIMER_TIMER2VALUE_TIMER2VALUE_Pos)  /**< (DUALTIMER_TIMER2VALUE)  Mask */
#define DUALTIMER_TIMER2VALUE_TIMER2VALUE(value) (DUALTIMER_TIMER2VALUE_TIMER2VALUE_Msk & ((value) << DUALTIMER_TIMER2VALUE_TIMER2VALUE_Pos))
#define DUALTIMER_TIMER2VALUE_MASK          0xFFFFFFFFu                                    /**< \deprecated (DUALTIMER_TIMER2VALUE) Register MASK  (Use DUALTIMER_TIMER2VALUE_Msk instead)  */
#define DUALTIMER_TIMER2VALUE_Msk           0xFFFFFFFFu                                    /**< (DUALTIMER_TIMER2VALUE) Register Mask  */

/* -------- DUALTIMER_TIMER2CONTROL : (DUALTIMER Offset: 0x28) (R/W 8) Timer 2 Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ONE_SHOT_COUNT:1;          /**< bit:      0  Mode Select                              */
    uint8_t  TIMER_SIZE:1;              /**< bit:      1  Timer Size                               */
    uint8_t  TIMERPRE:2;                /**< bit:   2..3  Prescale Bits                            */
    uint8_t  RESERVED4:1;               /**< bit:      4  Reserved bit do not use                  */
    uint8_t  INTERRUPT_ENABLE:1;        /**< bit:      5  Active High Interrupt Enable Bit         */
    uint8_t  TIMER_MODE:1;              /**< bit:      6  Mode Bit                                 */
    uint8_t  TIMER_ENABLE:1;            /**< bit:      7  Active High Timer Enable                 */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMER2CONTROL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER2CONTROL_OFFSET      0x28                                          /**<  (DUALTIMER_TIMER2CONTROL) Timer 2 Control Register  Offset */
#define DUALTIMER_TIMER2CONTROL_RESETVALUE  0x20u                                         /**<  (DUALTIMER_TIMER2CONTROL) Timer 2 Control Register  Reset Value */

#define DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_Pos 0                                              /**< (DUALTIMER_TIMER2CONTROL) Mode Select Position */
#define DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_Msk (0x1u << DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_Pos)  /**< (DUALTIMER_TIMER2CONTROL) Mode Select Mask */
#define DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_Msk instead */
#define   DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_0_Val 0x0u                                           /**< (DUALTIMER_TIMER2CONTROL) Wrapping Mode  */
#define   DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_1_Val 0x1u                                           /**< (DUALTIMER_TIMER2CONTROL) One-Shot Mode  */
#define DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_0 (DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_0_Val << DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_Pos)  /**< (DUALTIMER_TIMER2CONTROL) Wrapping Mode Position  */
#define DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_1 (DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_1_Val << DUALTIMER_TIMER2CONTROL_ONE_SHOT_COUNT_Pos)  /**< (DUALTIMER_TIMER2CONTROL) One-Shot Mode Position  */
#define DUALTIMER_TIMER2CONTROL_TIMER_SIZE_Pos 1                                              /**< (DUALTIMER_TIMER2CONTROL) Timer Size Position */
#define DUALTIMER_TIMER2CONTROL_TIMER_SIZE_Msk (0x1u << DUALTIMER_TIMER2CONTROL_TIMER_SIZE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) Timer Size Mask */
#define DUALTIMER_TIMER2CONTROL_TIMER_SIZE  DUALTIMER_TIMER2CONTROL_TIMER_SIZE_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER2CONTROL_TIMER_SIZE_Msk instead */
#define   DUALTIMER_TIMER2CONTROL_TIMER_SIZE_0_Val 0x0u                                           /**< (DUALTIMER_TIMER2CONTROL) 16-bit Counter  */
#define   DUALTIMER_TIMER2CONTROL_TIMER_SIZE_1_Val 0x1u                                           /**< (DUALTIMER_TIMER2CONTROL) 32-bit Counter  */
#define DUALTIMER_TIMER2CONTROL_TIMER_SIZE_0 (DUALTIMER_TIMER2CONTROL_TIMER_SIZE_0_Val << DUALTIMER_TIMER2CONTROL_TIMER_SIZE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) 16-bit Counter Position  */
#define DUALTIMER_TIMER2CONTROL_TIMER_SIZE_1 (DUALTIMER_TIMER2CONTROL_TIMER_SIZE_1_Val << DUALTIMER_TIMER2CONTROL_TIMER_SIZE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) 32-bit Counter Position  */
#define DUALTIMER_TIMER2CONTROL_TIMERPRE_Pos 2                                              /**< (DUALTIMER_TIMER2CONTROL) Prescale Bits Position */
#define DUALTIMER_TIMER2CONTROL_TIMERPRE_Msk (0x3u << DUALTIMER_TIMER2CONTROL_TIMERPRE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) Prescale Bits Mask */
#define DUALTIMER_TIMER2CONTROL_TIMERPRE(value) (DUALTIMER_TIMER2CONTROL_TIMERPRE_Msk & ((value) << DUALTIMER_TIMER2CONTROL_TIMERPRE_Pos))
#define   DUALTIMER_TIMER2CONTROL_TIMERPRE_0_Val 0x0u                                           /**< (DUALTIMER_TIMER2CONTROL) 0 Stages, Clock Divided by 1  */
#define   DUALTIMER_TIMER2CONTROL_TIMERPRE_1_Val 0x1u                                           /**< (DUALTIMER_TIMER2CONTROL) 4 Stages, Clock Divided by 16  */
#define   DUALTIMER_TIMER2CONTROL_TIMERPRE_2_Val 0x2u                                           /**< (DUALTIMER_TIMER2CONTROL) 8 Stages, Clock Divided by 256  */
#define   DUALTIMER_TIMER2CONTROL_TIMERPRE_3_Val 0x3u                                           /**< (DUALTIMER_TIMER2CONTROL) Undefined, do not use  */
#define DUALTIMER_TIMER2CONTROL_TIMERPRE_0  (DUALTIMER_TIMER2CONTROL_TIMERPRE_0_Val << DUALTIMER_TIMER2CONTROL_TIMERPRE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) 0 Stages, Clock Divided by 1 Position  */
#define DUALTIMER_TIMER2CONTROL_TIMERPRE_1  (DUALTIMER_TIMER2CONTROL_TIMERPRE_1_Val << DUALTIMER_TIMER2CONTROL_TIMERPRE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) 4 Stages, Clock Divided by 16 Position  */
#define DUALTIMER_TIMER2CONTROL_TIMERPRE_2  (DUALTIMER_TIMER2CONTROL_TIMERPRE_2_Val << DUALTIMER_TIMER2CONTROL_TIMERPRE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) 8 Stages, Clock Divided by 256 Position  */
#define DUALTIMER_TIMER2CONTROL_TIMERPRE_3  (DUALTIMER_TIMER2CONTROL_TIMERPRE_3_Val << DUALTIMER_TIMER2CONTROL_TIMERPRE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) Undefined, do not use Position  */
#define DUALTIMER_TIMER2CONTROL_RESERVED4_Pos 4                                              /**< (DUALTIMER_TIMER2CONTROL) Reserved bit do not use Position */
#define DUALTIMER_TIMER2CONTROL_RESERVED4_Msk (0x1u << DUALTIMER_TIMER2CONTROL_RESERVED4_Pos)  /**< (DUALTIMER_TIMER2CONTROL) Reserved bit do not use Mask */
#define DUALTIMER_TIMER2CONTROL_RESERVED4   DUALTIMER_TIMER2CONTROL_RESERVED4_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER2CONTROL_RESERVED4_Msk instead */
#define DUALTIMER_TIMER2CONTROL_INTERRUPT_ENABLE_Pos 5                                              /**< (DUALTIMER_TIMER2CONTROL) Active High Interrupt Enable Bit Position */
#define DUALTIMER_TIMER2CONTROL_INTERRUPT_ENABLE_Msk (0x1u << DUALTIMER_TIMER2CONTROL_INTERRUPT_ENABLE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) Active High Interrupt Enable Bit Mask */
#define DUALTIMER_TIMER2CONTROL_INTERRUPT_ENABLE DUALTIMER_TIMER2CONTROL_INTERRUPT_ENABLE_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER2CONTROL_INTERRUPT_ENABLE_Msk instead */
#define DUALTIMER_TIMER2CONTROL_TIMER_MODE_Pos 6                                              /**< (DUALTIMER_TIMER2CONTROL) Mode Bit Position */
#define DUALTIMER_TIMER2CONTROL_TIMER_MODE_Msk (0x1u << DUALTIMER_TIMER2CONTROL_TIMER_MODE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) Mode Bit Mask */
#define DUALTIMER_TIMER2CONTROL_TIMER_MODE  DUALTIMER_TIMER2CONTROL_TIMER_MODE_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER2CONTROL_TIMER_MODE_Msk instead */
#define   DUALTIMER_TIMER2CONTROL_TIMER_MODE_0_Val 0x0u                                           /**< (DUALTIMER_TIMER2CONTROL) Free-Running Mode  */
#define   DUALTIMER_TIMER2CONTROL_TIMER_MODE_1_Val 0x1u                                           /**< (DUALTIMER_TIMER2CONTROL) Periodic Mode  */
#define DUALTIMER_TIMER2CONTROL_TIMER_MODE_0 (DUALTIMER_TIMER2CONTROL_TIMER_MODE_0_Val << DUALTIMER_TIMER2CONTROL_TIMER_MODE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) Free-Running Mode Position  */
#define DUALTIMER_TIMER2CONTROL_TIMER_MODE_1 (DUALTIMER_TIMER2CONTROL_TIMER_MODE_1_Val << DUALTIMER_TIMER2CONTROL_TIMER_MODE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) Periodic Mode Position  */
#define DUALTIMER_TIMER2CONTROL_TIMER_ENABLE_Pos 7                                              /**< (DUALTIMER_TIMER2CONTROL) Active High Timer Enable Position */
#define DUALTIMER_TIMER2CONTROL_TIMER_ENABLE_Msk (0x1u << DUALTIMER_TIMER2CONTROL_TIMER_ENABLE_Pos)  /**< (DUALTIMER_TIMER2CONTROL) Active High Timer Enable Mask */
#define DUALTIMER_TIMER2CONTROL_TIMER_ENABLE DUALTIMER_TIMER2CONTROL_TIMER_ENABLE_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER2CONTROL_TIMER_ENABLE_Msk instead */
#define DUALTIMER_TIMER2CONTROL_MASK        0xFFu                                          /**< \deprecated (DUALTIMER_TIMER2CONTROL) Register MASK  (Use DUALTIMER_TIMER2CONTROL_Msk instead)  */
#define DUALTIMER_TIMER2CONTROL_Msk         0xFFu                                          /**< (DUALTIMER_TIMER2CONTROL) Register Mask  */

/* -------- DUALTIMER_TIMER2INTCLR : (DUALTIMER Offset: 0x2c) (/W 8) Timer 2 Interrupt Clear Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMER2INTCLR:1;            /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMER2INTCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER2INTCLR_OFFSET       0x2C                                          /**<  (DUALTIMER_TIMER2INTCLR) Timer 2 Interrupt Clear Register  Offset */
#define DUALTIMER_TIMER2INTCLR_RESETVALUE   0x00u                                         /**<  (DUALTIMER_TIMER2INTCLR) Timer 2 Interrupt Clear Register  Reset Value */

#define DUALTIMER_TIMER2INTCLR_TIMER2INTCLR_Pos 0                                              /**< (DUALTIMER_TIMER2INTCLR)  Position */
#define DUALTIMER_TIMER2INTCLR_TIMER2INTCLR_Msk (0x1u << DUALTIMER_TIMER2INTCLR_TIMER2INTCLR_Pos)  /**< (DUALTIMER_TIMER2INTCLR)  Mask */
#define DUALTIMER_TIMER2INTCLR_TIMER2INTCLR DUALTIMER_TIMER2INTCLR_TIMER2INTCLR_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER2INTCLR_TIMER2INTCLR_Msk instead */
#define DUALTIMER_TIMER2INTCLR_MASK         0x01u                                          /**< \deprecated (DUALTIMER_TIMER2INTCLR) Register MASK  (Use DUALTIMER_TIMER2INTCLR_Msk instead)  */
#define DUALTIMER_TIMER2INTCLR_Msk          0x01u                                          /**< (DUALTIMER_TIMER2INTCLR) Register Mask  */

/* -------- DUALTIMER_TIMER2RIS : (DUALTIMER Offset: 0x30) (R/ 8) Timer 2 Raw Interrupt Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMER2RIS:1;               /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMER2RIS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER2RIS_OFFSET          0x30                                          /**<  (DUALTIMER_TIMER2RIS) Timer 2 Raw Interrupt Status Register  Offset */
#define DUALTIMER_TIMER2RIS_RESETVALUE      0x00u                                         /**<  (DUALTIMER_TIMER2RIS) Timer 2 Raw Interrupt Status Register  Reset Value */

#define DUALTIMER_TIMER2RIS_TIMER2RIS_Pos   0                                              /**< (DUALTIMER_TIMER2RIS)  Position */
#define DUALTIMER_TIMER2RIS_TIMER2RIS_Msk   (0x1u << DUALTIMER_TIMER2RIS_TIMER2RIS_Pos)    /**< (DUALTIMER_TIMER2RIS)  Mask */
#define DUALTIMER_TIMER2RIS_TIMER2RIS       DUALTIMER_TIMER2RIS_TIMER2RIS_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER2RIS_TIMER2RIS_Msk instead */
#define DUALTIMER_TIMER2RIS_MASK            0x01u                                          /**< \deprecated (DUALTIMER_TIMER2RIS) Register MASK  (Use DUALTIMER_TIMER2RIS_Msk instead)  */
#define DUALTIMER_TIMER2RIS_Msk             0x01u                                          /**< (DUALTIMER_TIMER2RIS) Register Mask  */

/* -------- DUALTIMER_TIMER2MIS : (DUALTIMER Offset: 0x34) (R/ 8) Timer 2 Masked Interrupt Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMER2MIS:1;               /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMER2MIS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER2MIS_OFFSET          0x34                                          /**<  (DUALTIMER_TIMER2MIS) Timer 2 Masked Interrupt Status Register  Offset */
#define DUALTIMER_TIMER2MIS_RESETVALUE      0x00u                                         /**<  (DUALTIMER_TIMER2MIS) Timer 2 Masked Interrupt Status Register  Reset Value */

#define DUALTIMER_TIMER2MIS_TIMER2MIS_Pos   0                                              /**< (DUALTIMER_TIMER2MIS)  Position */
#define DUALTIMER_TIMER2MIS_TIMER2MIS_Msk   (0x1u << DUALTIMER_TIMER2MIS_TIMER2MIS_Pos)    /**< (DUALTIMER_TIMER2MIS)  Mask */
#define DUALTIMER_TIMER2MIS_TIMER2MIS       DUALTIMER_TIMER2MIS_TIMER2MIS_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMER2MIS_TIMER2MIS_Msk instead */
#define DUALTIMER_TIMER2MIS_MASK            0x01u                                          /**< \deprecated (DUALTIMER_TIMER2MIS) Register MASK  (Use DUALTIMER_TIMER2MIS_Msk instead)  */
#define DUALTIMER_TIMER2MIS_Msk             0x01u                                          /**< (DUALTIMER_TIMER2MIS) Register Mask  */

/* -------- DUALTIMER_TIMER2BGLOAD : (DUALTIMER Offset: 0x38) (R/W 32) Timer 2 Background Load Register (Reload Value for Period Mode) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t TIMER2BGLOAD:32;           /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} DUALTIMER_TIMER2BGLOAD_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMER2BGLOAD_OFFSET       0x38                                          /**<  (DUALTIMER_TIMER2BGLOAD) Timer 2 Background Load Register (Reload Value for Period Mode)  Offset */
#define DUALTIMER_TIMER2BGLOAD_RESETVALUE   0x00u                                         /**<  (DUALTIMER_TIMER2BGLOAD) Timer 2 Background Load Register (Reload Value for Period Mode)  Reset Value */

#define DUALTIMER_TIMER2BGLOAD_TIMER2BGLOAD_Pos 0                                              /**< (DUALTIMER_TIMER2BGLOAD)  Position */
#define DUALTIMER_TIMER2BGLOAD_TIMER2BGLOAD_Msk (0xFFFFFFFFu << DUALTIMER_TIMER2BGLOAD_TIMER2BGLOAD_Pos)  /**< (DUALTIMER_TIMER2BGLOAD)  Mask */
#define DUALTIMER_TIMER2BGLOAD_TIMER2BGLOAD(value) (DUALTIMER_TIMER2BGLOAD_TIMER2BGLOAD_Msk & ((value) << DUALTIMER_TIMER2BGLOAD_TIMER2BGLOAD_Pos))
#define DUALTIMER_TIMER2BGLOAD_MASK         0xFFFFFFFFu                                    /**< \deprecated (DUALTIMER_TIMER2BGLOAD) Register MASK  (Use DUALTIMER_TIMER2BGLOAD_Msk instead)  */
#define DUALTIMER_TIMER2BGLOAD_Msk          0xFFFFFFFFu                                    /**< (DUALTIMER_TIMER2BGLOAD) Register Mask  */

/* -------- DUALTIMER_TIMERITCR : (DUALTIMER Offset: 0xf00) (R/W 8) Integration Test Control Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMERITCR:1;               /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERITCR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERITCR_OFFSET          0xF00                                         /**<  (DUALTIMER_TIMERITCR) Integration Test Control Register  Offset */
#define DUALTIMER_TIMERITCR_RESETVALUE      0x00u                                         /**<  (DUALTIMER_TIMERITCR) Integration Test Control Register  Reset Value */

#define DUALTIMER_TIMERITCR_TIMERITCR_Pos   0                                              /**< (DUALTIMER_TIMERITCR)  Position */
#define DUALTIMER_TIMERITCR_TIMERITCR_Msk   (0x1u << DUALTIMER_TIMERITCR_TIMERITCR_Pos)    /**< (DUALTIMER_TIMERITCR)  Mask */
#define DUALTIMER_TIMERITCR_TIMERITCR       DUALTIMER_TIMERITCR_TIMERITCR_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMERITCR_TIMERITCR_Msk instead */
#define DUALTIMER_TIMERITCR_MASK            0x01u                                          /**< \deprecated (DUALTIMER_TIMERITCR) Register MASK  (Use DUALTIMER_TIMERITCR_Msk instead)  */
#define DUALTIMER_TIMERITCR_Msk             0x01u                                          /**< (DUALTIMER_TIMERITCR) Register Mask  */

/* -------- DUALTIMER_TIMERITOP : (DUALTIMER Offset: 0xf04) (/W 8) Integration Test Output Set Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  INT_TEST_TIMINT1_VALUE:1;  /**< bit:      0  Value Output on TIMINT1 in Integration Test Mode */
    uint8_t  INT_TEST_TIMING2_VALUE:1;  /**< bit:      1  Value Output on TIMINT2 in Integration Test Mode */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERITOP_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERITOP_OFFSET          0xF04                                         /**<  (DUALTIMER_TIMERITOP) Integration Test Output Set Register  Offset */
#define DUALTIMER_TIMERITOP_RESETVALUE      0x00u                                         /**<  (DUALTIMER_TIMERITOP) Integration Test Output Set Register  Reset Value */

#define DUALTIMER_TIMERITOP_INT_TEST_TIMINT1_VALUE_Pos 0                                              /**< (DUALTIMER_TIMERITOP) Value Output on TIMINT1 in Integration Test Mode Position */
#define DUALTIMER_TIMERITOP_INT_TEST_TIMINT1_VALUE_Msk (0x1u << DUALTIMER_TIMERITOP_INT_TEST_TIMINT1_VALUE_Pos)  /**< (DUALTIMER_TIMERITOP) Value Output on TIMINT1 in Integration Test Mode Mask */
#define DUALTIMER_TIMERITOP_INT_TEST_TIMINT1_VALUE DUALTIMER_TIMERITOP_INT_TEST_TIMINT1_VALUE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMERITOP_INT_TEST_TIMINT1_VALUE_Msk instead */
#define DUALTIMER_TIMERITOP_INT_TEST_TIMING2_VALUE_Pos 1                                              /**< (DUALTIMER_TIMERITOP) Value Output on TIMINT2 in Integration Test Mode Position */
#define DUALTIMER_TIMERITOP_INT_TEST_TIMING2_VALUE_Msk (0x1u << DUALTIMER_TIMERITOP_INT_TEST_TIMING2_VALUE_Pos)  /**< (DUALTIMER_TIMERITOP) Value Output on TIMINT2 in Integration Test Mode Mask */
#define DUALTIMER_TIMERITOP_INT_TEST_TIMING2_VALUE DUALTIMER_TIMERITOP_INT_TEST_TIMING2_VALUE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMERITOP_INT_TEST_TIMING2_VALUE_Msk instead */
#define DUALTIMER_TIMERITOP_MASK            0x03u                                          /**< \deprecated (DUALTIMER_TIMERITOP) Register MASK  (Use DUALTIMER_TIMERITOP_Msk instead)  */
#define DUALTIMER_TIMERITOP_Msk             0x03u                                          /**< (DUALTIMER_TIMERITOP) Register Mask  */

/* -------- DUALTIMER_TIMERPERIPHID4 : (DUALTIMER Offset: 0xfd0) (R/ 8) Peripheral ID Register 4 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  JEP106_C_CODE:4;           /**< bit:   0..3  JEP106 C Code                            */
    uint8_t  BLOCK_COUNT:4;             /**< bit:   4..7  Block Count                              */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERPERIPHID4_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERPERIPHID4_OFFSET     0xFD0                                         /**<  (DUALTIMER_TIMERPERIPHID4) Peripheral ID Register 4  Offset */
#define DUALTIMER_TIMERPERIPHID4_RESETVALUE 0x04u                                         /**<  (DUALTIMER_TIMERPERIPHID4) Peripheral ID Register 4  Reset Value */

#define DUALTIMER_TIMERPERIPHID4_JEP106_C_CODE_Pos 0                                              /**< (DUALTIMER_TIMERPERIPHID4) JEP106 C Code Position */
#define DUALTIMER_TIMERPERIPHID4_JEP106_C_CODE_Msk (0xFu << DUALTIMER_TIMERPERIPHID4_JEP106_C_CODE_Pos)  /**< (DUALTIMER_TIMERPERIPHID4) JEP106 C Code Mask */
#define DUALTIMER_TIMERPERIPHID4_JEP106_C_CODE(value) (DUALTIMER_TIMERPERIPHID4_JEP106_C_CODE_Msk & ((value) << DUALTIMER_TIMERPERIPHID4_JEP106_C_CODE_Pos))
#define DUALTIMER_TIMERPERIPHID4_BLOCK_COUNT_Pos 4                                              /**< (DUALTIMER_TIMERPERIPHID4) Block Count Position */
#define DUALTIMER_TIMERPERIPHID4_BLOCK_COUNT_Msk (0xFu << DUALTIMER_TIMERPERIPHID4_BLOCK_COUNT_Pos)  /**< (DUALTIMER_TIMERPERIPHID4) Block Count Mask */
#define DUALTIMER_TIMERPERIPHID4_BLOCK_COUNT(value) (DUALTIMER_TIMERPERIPHID4_BLOCK_COUNT_Msk & ((value) << DUALTIMER_TIMERPERIPHID4_BLOCK_COUNT_Pos))
#define DUALTIMER_TIMERPERIPHID4_MASK       0xFFu                                          /**< \deprecated (DUALTIMER_TIMERPERIPHID4) Register MASK  (Use DUALTIMER_TIMERPERIPHID4_Msk instead)  */
#define DUALTIMER_TIMERPERIPHID4_Msk        0xFFu                                          /**< (DUALTIMER_TIMERPERIPHID4) Register Mask  */

/* -------- DUALTIMER_TIMERPERIPHID5 : (DUALTIMER Offset: 0xfd4) (R/ 8) Peripheral ID Register 5 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMERPERIPHID5:8;          /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERPERIPHID5_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERPERIPHID5_OFFSET     0xFD4                                         /**<  (DUALTIMER_TIMERPERIPHID5) Peripheral ID Register 5  Offset */
#define DUALTIMER_TIMERPERIPHID5_RESETVALUE 0x00u                                         /**<  (DUALTIMER_TIMERPERIPHID5) Peripheral ID Register 5  Reset Value */

#define DUALTIMER_TIMERPERIPHID5_TIMERPERIPHID5_Pos 0                                              /**< (DUALTIMER_TIMERPERIPHID5)  Position */
#define DUALTIMER_TIMERPERIPHID5_TIMERPERIPHID5_Msk (0xFFu << DUALTIMER_TIMERPERIPHID5_TIMERPERIPHID5_Pos)  /**< (DUALTIMER_TIMERPERIPHID5)  Mask */
#define DUALTIMER_TIMERPERIPHID5_TIMERPERIPHID5(value) (DUALTIMER_TIMERPERIPHID5_TIMERPERIPHID5_Msk & ((value) << DUALTIMER_TIMERPERIPHID5_TIMERPERIPHID5_Pos))
#define DUALTIMER_TIMERPERIPHID5_MASK       0xFFu                                          /**< \deprecated (DUALTIMER_TIMERPERIPHID5) Register MASK  (Use DUALTIMER_TIMERPERIPHID5_Msk instead)  */
#define DUALTIMER_TIMERPERIPHID5_Msk        0xFFu                                          /**< (DUALTIMER_TIMERPERIPHID5) Register Mask  */

/* -------- DUALTIMER_TIMERPERIPHID6 : (DUALTIMER Offset: 0xfd8) (R/ 8) Peripheral ID Register 6 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMERPERIPHID6:8;          /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERPERIPHID6_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERPERIPHID6_OFFSET     0xFD8                                         /**<  (DUALTIMER_TIMERPERIPHID6) Peripheral ID Register 6  Offset */
#define DUALTIMER_TIMERPERIPHID6_RESETVALUE 0x00u                                         /**<  (DUALTIMER_TIMERPERIPHID6) Peripheral ID Register 6  Reset Value */

#define DUALTIMER_TIMERPERIPHID6_TIMERPERIPHID6_Pos 0                                              /**< (DUALTIMER_TIMERPERIPHID6)  Position */
#define DUALTIMER_TIMERPERIPHID6_TIMERPERIPHID6_Msk (0xFFu << DUALTIMER_TIMERPERIPHID6_TIMERPERIPHID6_Pos)  /**< (DUALTIMER_TIMERPERIPHID6)  Mask */
#define DUALTIMER_TIMERPERIPHID6_TIMERPERIPHID6(value) (DUALTIMER_TIMERPERIPHID6_TIMERPERIPHID6_Msk & ((value) << DUALTIMER_TIMERPERIPHID6_TIMERPERIPHID6_Pos))
#define DUALTIMER_TIMERPERIPHID6_MASK       0xFFu                                          /**< \deprecated (DUALTIMER_TIMERPERIPHID6) Register MASK  (Use DUALTIMER_TIMERPERIPHID6_Msk instead)  */
#define DUALTIMER_TIMERPERIPHID6_Msk        0xFFu                                          /**< (DUALTIMER_TIMERPERIPHID6) Register Mask  */

/* -------- DUALTIMER_TIMERPERIPHID7 : (DUALTIMER Offset: 0xfdc) (R/ 8) Peripheral ID Register 7 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMERPERIPHID7:8;          /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERPERIPHID7_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERPERIPHID7_OFFSET     0xFDC                                         /**<  (DUALTIMER_TIMERPERIPHID7) Peripheral ID Register 7  Offset */
#define DUALTIMER_TIMERPERIPHID7_RESETVALUE 0x00u                                         /**<  (DUALTIMER_TIMERPERIPHID7) Peripheral ID Register 7  Reset Value */

#define DUALTIMER_TIMERPERIPHID7_TIMERPERIPHID7_Pos 0                                              /**< (DUALTIMER_TIMERPERIPHID7)  Position */
#define DUALTIMER_TIMERPERIPHID7_TIMERPERIPHID7_Msk (0xFFu << DUALTIMER_TIMERPERIPHID7_TIMERPERIPHID7_Pos)  /**< (DUALTIMER_TIMERPERIPHID7)  Mask */
#define DUALTIMER_TIMERPERIPHID7_TIMERPERIPHID7(value) (DUALTIMER_TIMERPERIPHID7_TIMERPERIPHID7_Msk & ((value) << DUALTIMER_TIMERPERIPHID7_TIMERPERIPHID7_Pos))
#define DUALTIMER_TIMERPERIPHID7_MASK       0xFFu                                          /**< \deprecated (DUALTIMER_TIMERPERIPHID7) Register MASK  (Use DUALTIMER_TIMERPERIPHID7_Msk instead)  */
#define DUALTIMER_TIMERPERIPHID7_Msk        0xFFu                                          /**< (DUALTIMER_TIMERPERIPHID7) Register Mask  */

/* -------- DUALTIMER_TIMERPERIPHID0 : (DUALTIMER Offset: 0xfe0) (R/ 8) Peripheral ID Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PART_NUMBER:8;             /**< bit:   0..7  Part Number Bits 7:0                     */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERPERIPHID0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERPERIPHID0_OFFSET     0xFE0                                         /**<  (DUALTIMER_TIMERPERIPHID0) Peripheral ID Register 0  Offset */
#define DUALTIMER_TIMERPERIPHID0_RESETVALUE 0x23u                                         /**<  (DUALTIMER_TIMERPERIPHID0) Peripheral ID Register 0  Reset Value */

#define DUALTIMER_TIMERPERIPHID0_PART_NUMBER_Pos 0                                              /**< (DUALTIMER_TIMERPERIPHID0) Part Number Bits 7:0 Position */
#define DUALTIMER_TIMERPERIPHID0_PART_NUMBER_Msk (0xFFu << DUALTIMER_TIMERPERIPHID0_PART_NUMBER_Pos)  /**< (DUALTIMER_TIMERPERIPHID0) Part Number Bits 7:0 Mask */
#define DUALTIMER_TIMERPERIPHID0_PART_NUMBER(value) (DUALTIMER_TIMERPERIPHID0_PART_NUMBER_Msk & ((value) << DUALTIMER_TIMERPERIPHID0_PART_NUMBER_Pos))
#define DUALTIMER_TIMERPERIPHID0_MASK       0xFFu                                          /**< \deprecated (DUALTIMER_TIMERPERIPHID0) Register MASK  (Use DUALTIMER_TIMERPERIPHID0_Msk instead)  */
#define DUALTIMER_TIMERPERIPHID0_Msk        0xFFu                                          /**< (DUALTIMER_TIMERPERIPHID0) Register Mask  */

/* -------- DUALTIMER_TIMERPERIPHID1 : (DUALTIMER Offset: 0xfe4) (R/ 8) Peripheral ID Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  PART_NUMBER:4;             /**< bit:   0..3  Part Number Bits 11:8                    */
    uint8_t  JEP106_ID_3_0:4;           /**< bit:   4..7  JEP106 ID Bits 3:0                       */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERPERIPHID1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERPERIPHID1_OFFSET     0xFE4                                         /**<  (DUALTIMER_TIMERPERIPHID1) Peripheral ID Register 1  Offset */
#define DUALTIMER_TIMERPERIPHID1_RESETVALUE 0xB8u                                         /**<  (DUALTIMER_TIMERPERIPHID1) Peripheral ID Register 1  Reset Value */

#define DUALTIMER_TIMERPERIPHID1_PART_NUMBER_Pos 0                                              /**< (DUALTIMER_TIMERPERIPHID1) Part Number Bits 11:8 Position */
#define DUALTIMER_TIMERPERIPHID1_PART_NUMBER_Msk (0xFu << DUALTIMER_TIMERPERIPHID1_PART_NUMBER_Pos)  /**< (DUALTIMER_TIMERPERIPHID1) Part Number Bits 11:8 Mask */
#define DUALTIMER_TIMERPERIPHID1_PART_NUMBER(value) (DUALTIMER_TIMERPERIPHID1_PART_NUMBER_Msk & ((value) << DUALTIMER_TIMERPERIPHID1_PART_NUMBER_Pos))
#define DUALTIMER_TIMERPERIPHID1_JEP106_ID_3_0_Pos 4                                              /**< (DUALTIMER_TIMERPERIPHID1) JEP106 ID Bits 3:0 Position */
#define DUALTIMER_TIMERPERIPHID1_JEP106_ID_3_0_Msk (0xFu << DUALTIMER_TIMERPERIPHID1_JEP106_ID_3_0_Pos)  /**< (DUALTIMER_TIMERPERIPHID1) JEP106 ID Bits 3:0 Mask */
#define DUALTIMER_TIMERPERIPHID1_JEP106_ID_3_0(value) (DUALTIMER_TIMERPERIPHID1_JEP106_ID_3_0_Msk & ((value) << DUALTIMER_TIMERPERIPHID1_JEP106_ID_3_0_Pos))
#define DUALTIMER_TIMERPERIPHID1_MASK       0xFFu                                          /**< \deprecated (DUALTIMER_TIMERPERIPHID1) Register MASK  (Use DUALTIMER_TIMERPERIPHID1_Msk instead)  */
#define DUALTIMER_TIMERPERIPHID1_Msk        0xFFu                                          /**< (DUALTIMER_TIMERPERIPHID1) Register Mask  */

/* -------- DUALTIMER_TIMERPERIPHID2 : (DUALTIMER Offset: 0xfe8) (R/ 8) Peripheral ID Register 2 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  JEP106_ID_6_4:3;           /**< bit:   0..2  JEP106 ID Bits 6:4                       */
    uint8_t  JEDEC_USED:1;              /**< bit:      3  JEDEC Used                               */
    uint8_t  REVISION:4;                /**< bit:   4..7  Revision                                 */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERPERIPHID2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERPERIPHID2_OFFSET     0xFE8                                         /**<  (DUALTIMER_TIMERPERIPHID2) Peripheral ID Register 2  Offset */
#define DUALTIMER_TIMERPERIPHID2_RESETVALUE 0x1Bu                                         /**<  (DUALTIMER_TIMERPERIPHID2) Peripheral ID Register 2  Reset Value */

#define DUALTIMER_TIMERPERIPHID2_JEP106_ID_6_4_Pos 0                                              /**< (DUALTIMER_TIMERPERIPHID2) JEP106 ID Bits 6:4 Position */
#define DUALTIMER_TIMERPERIPHID2_JEP106_ID_6_4_Msk (0x7u << DUALTIMER_TIMERPERIPHID2_JEP106_ID_6_4_Pos)  /**< (DUALTIMER_TIMERPERIPHID2) JEP106 ID Bits 6:4 Mask */
#define DUALTIMER_TIMERPERIPHID2_JEP106_ID_6_4(value) (DUALTIMER_TIMERPERIPHID2_JEP106_ID_6_4_Msk & ((value) << DUALTIMER_TIMERPERIPHID2_JEP106_ID_6_4_Pos))
#define DUALTIMER_TIMERPERIPHID2_JEDEC_USED_Pos 3                                              /**< (DUALTIMER_TIMERPERIPHID2) JEDEC Used Position */
#define DUALTIMER_TIMERPERIPHID2_JEDEC_USED_Msk (0x1u << DUALTIMER_TIMERPERIPHID2_JEDEC_USED_Pos)  /**< (DUALTIMER_TIMERPERIPHID2) JEDEC Used Mask */
#define DUALTIMER_TIMERPERIPHID2_JEDEC_USED DUALTIMER_TIMERPERIPHID2_JEDEC_USED_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use DUALTIMER_TIMERPERIPHID2_JEDEC_USED_Msk instead */
#define DUALTIMER_TIMERPERIPHID2_REVISION_Pos 4                                              /**< (DUALTIMER_TIMERPERIPHID2) Revision Position */
#define DUALTIMER_TIMERPERIPHID2_REVISION_Msk (0xFu << DUALTIMER_TIMERPERIPHID2_REVISION_Pos)  /**< (DUALTIMER_TIMERPERIPHID2) Revision Mask */
#define DUALTIMER_TIMERPERIPHID2_REVISION(value) (DUALTIMER_TIMERPERIPHID2_REVISION_Msk & ((value) << DUALTIMER_TIMERPERIPHID2_REVISION_Pos))
#define DUALTIMER_TIMERPERIPHID2_MASK       0xFFu                                          /**< \deprecated (DUALTIMER_TIMERPERIPHID2) Register MASK  (Use DUALTIMER_TIMERPERIPHID2_Msk instead)  */
#define DUALTIMER_TIMERPERIPHID2_Msk        0xFFu                                          /**< (DUALTIMER_TIMERPERIPHID2) Register Mask  */

/* -------- DUALTIMER_TIMERPERIPHID3 : (DUALTIMER Offset: 0xfec) (R/ 8) Peripheral ID Register 3 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CUSTOMER_MOD_NUMBER:4;     /**< bit:   0..3  Customer Modification Number             */
    uint8_t  ECO_REV_NUMBER:4;          /**< bit:   4..7  ECO Revision Number                      */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERPERIPHID3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERPERIPHID3_OFFSET     0xFEC                                         /**<  (DUALTIMER_TIMERPERIPHID3) Peripheral ID Register 3  Offset */
#define DUALTIMER_TIMERPERIPHID3_RESETVALUE 0x00u                                         /**<  (DUALTIMER_TIMERPERIPHID3) Peripheral ID Register 3  Reset Value */

#define DUALTIMER_TIMERPERIPHID3_CUSTOMER_MOD_NUMBER_Pos 0                                              /**< (DUALTIMER_TIMERPERIPHID3) Customer Modification Number Position */
#define DUALTIMER_TIMERPERIPHID3_CUSTOMER_MOD_NUMBER_Msk (0xFu << DUALTIMER_TIMERPERIPHID3_CUSTOMER_MOD_NUMBER_Pos)  /**< (DUALTIMER_TIMERPERIPHID3) Customer Modification Number Mask */
#define DUALTIMER_TIMERPERIPHID3_CUSTOMER_MOD_NUMBER(value) (DUALTIMER_TIMERPERIPHID3_CUSTOMER_MOD_NUMBER_Msk & ((value) << DUALTIMER_TIMERPERIPHID3_CUSTOMER_MOD_NUMBER_Pos))
#define DUALTIMER_TIMERPERIPHID3_ECO_REV_NUMBER_Pos 4                                              /**< (DUALTIMER_TIMERPERIPHID3) ECO Revision Number Position */
#define DUALTIMER_TIMERPERIPHID3_ECO_REV_NUMBER_Msk (0xFu << DUALTIMER_TIMERPERIPHID3_ECO_REV_NUMBER_Pos)  /**< (DUALTIMER_TIMERPERIPHID3) ECO Revision Number Mask */
#define DUALTIMER_TIMERPERIPHID3_ECO_REV_NUMBER(value) (DUALTIMER_TIMERPERIPHID3_ECO_REV_NUMBER_Msk & ((value) << DUALTIMER_TIMERPERIPHID3_ECO_REV_NUMBER_Pos))
#define DUALTIMER_TIMERPERIPHID3_MASK       0xFFu                                          /**< \deprecated (DUALTIMER_TIMERPERIPHID3) Register MASK  (Use DUALTIMER_TIMERPERIPHID3_Msk instead)  */
#define DUALTIMER_TIMERPERIPHID3_Msk        0xFFu                                          /**< (DUALTIMER_TIMERPERIPHID3) Register Mask  */

/* -------- DUALTIMER_TIMERPCELLID0 : (DUALTIMER Offset: 0xff0) (R/ 8) Component ID Register 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMERPCELLID0:8;           /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERPCELLID0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERPCELLID0_OFFSET      0xFF0                                         /**<  (DUALTIMER_TIMERPCELLID0) Component ID Register 0  Offset */
#define DUALTIMER_TIMERPCELLID0_RESETVALUE  0x0Du                                         /**<  (DUALTIMER_TIMERPCELLID0) Component ID Register 0  Reset Value */

#define DUALTIMER_TIMERPCELLID0_TIMERPCELLID0_Pos 0                                              /**< (DUALTIMER_TIMERPCELLID0)  Position */
#define DUALTIMER_TIMERPCELLID0_TIMERPCELLID0_Msk (0xFFu << DUALTIMER_TIMERPCELLID0_TIMERPCELLID0_Pos)  /**< (DUALTIMER_TIMERPCELLID0)  Mask */
#define DUALTIMER_TIMERPCELLID0_TIMERPCELLID0(value) (DUALTIMER_TIMERPCELLID0_TIMERPCELLID0_Msk & ((value) << DUALTIMER_TIMERPCELLID0_TIMERPCELLID0_Pos))
#define DUALTIMER_TIMERPCELLID0_MASK        0xFFu                                          /**< \deprecated (DUALTIMER_TIMERPCELLID0) Register MASK  (Use DUALTIMER_TIMERPCELLID0_Msk instead)  */
#define DUALTIMER_TIMERPCELLID0_Msk         0xFFu                                          /**< (DUALTIMER_TIMERPCELLID0) Register Mask  */

/* -------- DUALTIMER_TIMERPCELLID1 : (DUALTIMER Offset: 0xff4) (R/ 8) Component ID Register 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMERPCELLID1:8;           /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERPCELLID1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERPCELLID1_OFFSET      0xFF4                                         /**<  (DUALTIMER_TIMERPCELLID1) Component ID Register 1  Offset */
#define DUALTIMER_TIMERPCELLID1_RESETVALUE  0xF0u                                         /**<  (DUALTIMER_TIMERPCELLID1) Component ID Register 1  Reset Value */

#define DUALTIMER_TIMERPCELLID1_TIMERPCELLID1_Pos 0                                              /**< (DUALTIMER_TIMERPCELLID1)  Position */
#define DUALTIMER_TIMERPCELLID1_TIMERPCELLID1_Msk (0xFFu << DUALTIMER_TIMERPCELLID1_TIMERPCELLID1_Pos)  /**< (DUALTIMER_TIMERPCELLID1)  Mask */
#define DUALTIMER_TIMERPCELLID1_TIMERPCELLID1(value) (DUALTIMER_TIMERPCELLID1_TIMERPCELLID1_Msk & ((value) << DUALTIMER_TIMERPCELLID1_TIMERPCELLID1_Pos))
#define DUALTIMER_TIMERPCELLID1_MASK        0xFFu                                          /**< \deprecated (DUALTIMER_TIMERPCELLID1) Register MASK  (Use DUALTIMER_TIMERPCELLID1_Msk instead)  */
#define DUALTIMER_TIMERPCELLID1_Msk         0xFFu                                          /**< (DUALTIMER_TIMERPCELLID1) Register Mask  */

/* -------- DUALTIMER_TIMERPCELLID2 : (DUALTIMER Offset: 0xff8) (R/ 8) Component ID Register 2 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMERPCELLID2:8;           /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERPCELLID2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERPCELLID2_OFFSET      0xFF8                                         /**<  (DUALTIMER_TIMERPCELLID2) Component ID Register 2  Offset */
#define DUALTIMER_TIMERPCELLID2_RESETVALUE  0x05u                                         /**<  (DUALTIMER_TIMERPCELLID2) Component ID Register 2  Reset Value */

#define DUALTIMER_TIMERPCELLID2_TIMERPCELLID2_Pos 0                                              /**< (DUALTIMER_TIMERPCELLID2)  Position */
#define DUALTIMER_TIMERPCELLID2_TIMERPCELLID2_Msk (0xFFu << DUALTIMER_TIMERPCELLID2_TIMERPCELLID2_Pos)  /**< (DUALTIMER_TIMERPCELLID2)  Mask */
#define DUALTIMER_TIMERPCELLID2_TIMERPCELLID2(value) (DUALTIMER_TIMERPCELLID2_TIMERPCELLID2_Msk & ((value) << DUALTIMER_TIMERPCELLID2_TIMERPCELLID2_Pos))
#define DUALTIMER_TIMERPCELLID2_MASK        0xFFu                                          /**< \deprecated (DUALTIMER_TIMERPCELLID2) Register MASK  (Use DUALTIMER_TIMERPCELLID2_Msk instead)  */
#define DUALTIMER_TIMERPCELLID2_Msk         0xFFu                                          /**< (DUALTIMER_TIMERPCELLID2) Register Mask  */

/* -------- DUALTIMER_TIMERPCELLID3 : (DUALTIMER Offset: 0xffc) (R/ 8) Component ID Register 3 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMERPCELLID3:8;           /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} DUALTIMER_TIMERPCELLID3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define DUALTIMER_TIMERPCELLID3_OFFSET      0xFFC                                         /**<  (DUALTIMER_TIMERPCELLID3) Component ID Register 3  Offset */
#define DUALTIMER_TIMERPCELLID3_RESETVALUE  0xB1u                                         /**<  (DUALTIMER_TIMERPCELLID3) Component ID Register 3  Reset Value */

#define DUALTIMER_TIMERPCELLID3_TIMERPCELLID3_Pos 0                                              /**< (DUALTIMER_TIMERPCELLID3)  Position */
#define DUALTIMER_TIMERPCELLID3_TIMERPCELLID3_Msk (0xFFu << DUALTIMER_TIMERPCELLID3_TIMERPCELLID3_Pos)  /**< (DUALTIMER_TIMERPCELLID3)  Mask */
#define DUALTIMER_TIMERPCELLID3_TIMERPCELLID3(value) (DUALTIMER_TIMERPCELLID3_TIMERPCELLID3_Msk & ((value) << DUALTIMER_TIMERPCELLID3_TIMERPCELLID3_Pos))
#define DUALTIMER_TIMERPCELLID3_MASK        0xFFu                                          /**< \deprecated (DUALTIMER_TIMERPCELLID3) Register MASK  (Use DUALTIMER_TIMERPCELLID3_Msk instead)  */
#define DUALTIMER_TIMERPCELLID3_Msk         0xFFu                                          /**< (DUALTIMER_TIMERPCELLID3) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief DUALTIMER hardware registers */
typedef struct {  /* ARM General Purpose Dual Timer */
  RwReg   TIMER1LOAD;     /**< (DUALTIMER Offset: 0x00) Timer 1 Load Register */
  RoReg   TIMER1VALUE;    /**< (DUALTIMER Offset: 0x04) Timer 1 Current Value Register */
  RwReg8  TIMER1CONTROL;  /**< (DUALTIMER Offset: 0x08) Timer 1 Control Register */
  __I  uint8_t  Reserved1[3];
  WoReg8  TIMER1INTCLR;   /**< (DUALTIMER Offset: 0x0C) Timer 1 Interrupt Clear Register */
  __I  uint8_t  Reserved2[3];
  RoReg8  TIMER1RIS;      /**< (DUALTIMER Offset: 0x10) Timer 1 Raw Interrupt Status Register */
  __I  uint8_t  Reserved3[3];
  RoReg8  TIMER1MIS;      /**< (DUALTIMER Offset: 0x14) Timer 1 Masked Interrupt Status Register */
  __I  uint8_t  Reserved4[3];
  RwReg   TIMER1BGLOAD;   /**< (DUALTIMER Offset: 0x18) Timer 1 Background Load Register (Reload Value for Period Mode) */
  __I  uint32_t Reserved5[1];
  RwReg   TIMER2LOAD;     /**< (DUALTIMER Offset: 0x20) Timer 2 Load Register */
  RoReg   TIMER2VALUE;    /**< (DUALTIMER Offset: 0x24) Timer 2 Current Value Register */
  RwReg8  TIMER2CONTROL;  /**< (DUALTIMER Offset: 0x28) Timer 2 Control Register */
  __I  uint8_t  Reserved6[3];
  WoReg8  TIMER2INTCLR;   /**< (DUALTIMER Offset: 0x2C) Timer 2 Interrupt Clear Register */
  __I  uint8_t  Reserved7[3];
  RoReg8  TIMER2RIS;      /**< (DUALTIMER Offset: 0x30) Timer 2 Raw Interrupt Status Register */
  __I  uint8_t  Reserved8[3];
  RoReg8  TIMER2MIS;      /**< (DUALTIMER Offset: 0x34) Timer 2 Masked Interrupt Status Register */
  __I  uint8_t  Reserved9[3];
  RwReg   TIMER2BGLOAD;   /**< (DUALTIMER Offset: 0x38) Timer 2 Background Load Register (Reload Value for Period Mode) */
  __I  uint32_t Reserved10[945];
  RwReg8  TIMERITCR;      /**< (DUALTIMER Offset: 0xF00) Integration Test Control Register */
  __I  uint8_t  Reserved11[3];
  WoReg8  TIMERITOP;      /**< (DUALTIMER Offset: 0xF04) Integration Test Output Set Register */
  __I  uint8_t  Reserved12[203];
  RoReg8  TIMERPERIPHID4; /**< (DUALTIMER Offset: 0xFD0) Peripheral ID Register 4 */
  __I  uint8_t  Reserved13[3];
  RoReg8  TIMERPERIPHID5; /**< (DUALTIMER Offset: 0xFD4) Peripheral ID Register 5 */
  __I  uint8_t  Reserved14[3];
  RoReg8  TIMERPERIPHID6; /**< (DUALTIMER Offset: 0xFD8) Peripheral ID Register 6 */
  __I  uint8_t  Reserved15[3];
  RoReg8  TIMERPERIPHID7; /**< (DUALTIMER Offset: 0xFDC) Peripheral ID Register 7 */
  __I  uint8_t  Reserved16[3];
  RoReg8  TIMERPERIPHID0; /**< (DUALTIMER Offset: 0xFE0) Peripheral ID Register 0 */
  __I  uint8_t  Reserved17[3];
  RoReg8  TIMERPERIPHID1; /**< (DUALTIMER Offset: 0xFE4) Peripheral ID Register 1 */
  __I  uint8_t  Reserved18[3];
  RoReg8  TIMERPERIPHID2; /**< (DUALTIMER Offset: 0xFE8) Peripheral ID Register 2 */
  __I  uint8_t  Reserved19[3];
  RoReg8  TIMERPERIPHID3; /**< (DUALTIMER Offset: 0xFEC) Peripheral ID Register 3 */
  __I  uint8_t  Reserved20[3];
  RoReg8  TIMERPCELLID0;  /**< (DUALTIMER Offset: 0xFF0) Component ID Register 0 */
  __I  uint8_t  Reserved21[3];
  RoReg8  TIMERPCELLID1;  /**< (DUALTIMER Offset: 0xFF4) Component ID Register 1 */
  __I  uint8_t  Reserved22[3];
  RoReg8  TIMERPCELLID2;  /**< (DUALTIMER Offset: 0xFF8) Component ID Register 2 */
  __I  uint8_t  Reserved23[3];
  RoReg8  TIMERPCELLID3;  /**< (DUALTIMER Offset: 0xFFC) Component ID Register 3 */
} Dualtimer;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief DUALTIMER hardware registers */
typedef struct {  /* ARM General Purpose Dual Timer */
  __IO DUALTIMER_TIMER1LOAD_Type      TIMER1LOAD;     /**< Offset: 0x00 (R/W  32) Timer 1 Load Register */
  __I  DUALTIMER_TIMER1VALUE_Type     TIMER1VALUE;    /**< Offset: 0x04 (R/   32) Timer 1 Current Value Register */
  __IO DUALTIMER_TIMER1CONTROL_Type   TIMER1CONTROL;  /**< Offset: 0x08 (R/W   8) Timer 1 Control Register */
       RoReg8                         Reserved1[0x3];
  __O  DUALTIMER_TIMER1INTCLR_Type    TIMER1INTCLR;   /**< Offset: 0x0C ( /W   8) Timer 1 Interrupt Clear Register */
       RoReg8                         Reserved2[0x3];
  __I  DUALTIMER_TIMER1RIS_Type       TIMER1RIS;      /**< Offset: 0x10 (R/    8) Timer 1 Raw Interrupt Status Register */
       RoReg8                         Reserved3[0x3];
  __I  DUALTIMER_TIMER1MIS_Type       TIMER1MIS;      /**< Offset: 0x14 (R/    8) Timer 1 Masked Interrupt Status Register */
       RoReg8                         Reserved4[0x3];
  __IO DUALTIMER_TIMER1BGLOAD_Type    TIMER1BGLOAD;   /**< Offset: 0x18 (R/W  32) Timer 1 Background Load Register (Reload Value for Period Mode) */
       RoReg8                         Reserved5[0x4];
  __IO DUALTIMER_TIMER2LOAD_Type      TIMER2LOAD;     /**< Offset: 0x20 (R/W  32) Timer 2 Load Register */
  __I  DUALTIMER_TIMER2VALUE_Type     TIMER2VALUE;    /**< Offset: 0x24 (R/   32) Timer 2 Current Value Register */
  __IO DUALTIMER_TIMER2CONTROL_Type   TIMER2CONTROL;  /**< Offset: 0x28 (R/W   8) Timer 2 Control Register */
       RoReg8                         Reserved6[0x3];
  __O  DUALTIMER_TIMER2INTCLR_Type    TIMER2INTCLR;   /**< Offset: 0x2C ( /W   8) Timer 2 Interrupt Clear Register */
       RoReg8                         Reserved7[0x3];
  __I  DUALTIMER_TIMER2RIS_Type       TIMER2RIS;      /**< Offset: 0x30 (R/    8) Timer 2 Raw Interrupt Status Register */
       RoReg8                         Reserved8[0x3];
  __I  DUALTIMER_TIMER2MIS_Type       TIMER2MIS;      /**< Offset: 0x34 (R/    8) Timer 2 Masked Interrupt Status Register */
       RoReg8                         Reserved9[0x3];
  __IO DUALTIMER_TIMER2BGLOAD_Type    TIMER2BGLOAD;   /**< Offset: 0x38 (R/W  32) Timer 2 Background Load Register (Reload Value for Period Mode) */
       RoReg8                         Reserved10[0xEC4];
  __IO DUALTIMER_TIMERITCR_Type       TIMERITCR;      /**< Offset: 0xF00 (R/W   8) Integration Test Control Register */
       RoReg8                         Reserved11[0x3];
  __O  DUALTIMER_TIMERITOP_Type       TIMERITOP;      /**< Offset: 0xF04 ( /W   8) Integration Test Output Set Register */
       RoReg8                         Reserved12[0xCB];
  __I  DUALTIMER_TIMERPERIPHID4_Type  TIMERPERIPHID4; /**< Offset: 0xFD0 (R/    8) Peripheral ID Register 4 */
       RoReg8                         Reserved13[0x3];
  __I  DUALTIMER_TIMERPERIPHID5_Type  TIMERPERIPHID5; /**< Offset: 0xFD4 (R/    8) Peripheral ID Register 5 */
       RoReg8                         Reserved14[0x3];
  __I  DUALTIMER_TIMERPERIPHID6_Type  TIMERPERIPHID6; /**< Offset: 0xFD8 (R/    8) Peripheral ID Register 6 */
       RoReg8                         Reserved15[0x3];
  __I  DUALTIMER_TIMERPERIPHID7_Type  TIMERPERIPHID7; /**< Offset: 0xFDC (R/    8) Peripheral ID Register 7 */
       RoReg8                         Reserved16[0x3];
  __I  DUALTIMER_TIMERPERIPHID0_Type  TIMERPERIPHID0; /**< Offset: 0xFE0 (R/    8) Peripheral ID Register 0 */
       RoReg8                         Reserved17[0x3];
  __I  DUALTIMER_TIMERPERIPHID1_Type  TIMERPERIPHID1; /**< Offset: 0xFE4 (R/    8) Peripheral ID Register 1 */
       RoReg8                         Reserved18[0x3];
  __I  DUALTIMER_TIMERPERIPHID2_Type  TIMERPERIPHID2; /**< Offset: 0xFE8 (R/    8) Peripheral ID Register 2 */
       RoReg8                         Reserved19[0x3];
  __I  DUALTIMER_TIMERPERIPHID3_Type  TIMERPERIPHID3; /**< Offset: 0xFEC (R/    8) Peripheral ID Register 3 */
       RoReg8                         Reserved20[0x3];
  __I  DUALTIMER_TIMERPCELLID0_Type   TIMERPCELLID0;  /**< Offset: 0xFF0 (R/    8) Component ID Register 0 */
       RoReg8                         Reserved21[0x3];
  __I  DUALTIMER_TIMERPCELLID1_Type   TIMERPCELLID1;  /**< Offset: 0xFF4 (R/    8) Component ID Register 1 */
       RoReg8                         Reserved22[0x3];
  __I  DUALTIMER_TIMERPCELLID2_Type   TIMERPCELLID2;  /**< Offset: 0xFF8 (R/    8) Component ID Register 2 */
       RoReg8                         Reserved23[0x3];
  __I  DUALTIMER_TIMERPCELLID3_Type   TIMERPCELLID3;  /**< Offset: 0xFFC (R/    8) Component ID Register 3 */
} Dualtimer;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_DUALTIMER_COMPONENT_ */
