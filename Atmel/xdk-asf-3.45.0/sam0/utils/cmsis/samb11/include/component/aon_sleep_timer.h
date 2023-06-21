/**
 * \file
 *
 * \brief Component description for AON_SLEEP_TIMER
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

#ifndef _SAMB11_AON_SLEEP_TIMER_COMPONENT_
#define _SAMB11_AON_SLEEP_TIMER_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR AON_SLEEP_TIMER */
/* ========================================================================== */
/** \addtogroup SAMB11_AON_SLEEP_TIMER Always On Sleep Timer 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define AON_SLEEP_TIMER_AONST1234
#define REV_AON_SLEEP_TIMER              0x100

/* -------- AON_SLEEP_TIMER_CONTROL : (AON_SLEEP_TIMER Offset: 0x00) (R/W 32) Control for the Always On Sleep Timer -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RELOAD_ENABLE:1;           /**< bit:      0  Active High Reload Enable                */
    uint32_t SINGLE_COUNT_ENABLE:1;     /**< bit:      1  Rising Edge Single Count Enable          */
    uint32_t :2;                        /**< bit:   2..3  Reserved */
    uint32_t IRQ_CLEAR:1;               /**< bit:      4  Clears the interrupt. Auto clear. Must only be set after receiving the IRQ. */
    uint32_t :3;                        /**< bit:   5..7  Reserved */
    uint32_t SLP_TIMER_CLK_RELOAD_DLY:2;  /**< bit:   8..9  Current Status of slp_timer_clk_reload on the sleep clock */
    uint32_t :2;                        /**< bit: 10..11  Reserved */
    uint32_t SLP_TIMER_SINGLE_COUNT_ENABLE_DLY:3;  /**< bit: 12..14  Current status of slp_timer_clk_single_count_enable on the sleep clock */
    uint32_t :15;                       /**< bit: 15..29  Reserved */
    uint32_t SLEEP_TIMER_ACTIVE:1;      /**< bit:     30  If 1, indicates that the current sleep tiemr value is not 0 */
    uint32_t SLEEP_TIMER_NOT_ACTIVE:1;  /**< bit:     31  If 1, indicates that the current sleep timer value is 0 */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_SLEEP_TIMER_CONTROL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_SLEEP_TIMER_CONTROL_OFFSET      0x00                                          /**<  (AON_SLEEP_TIMER_CONTROL) Control for the Always On Sleep Timer  Offset */
#define AON_SLEEP_TIMER_CONTROL_RESETVALUE  0x00u                                         /**<  (AON_SLEEP_TIMER_CONTROL) Control for the Always On Sleep Timer  Reset Value */

#define AON_SLEEP_TIMER_CONTROL_RELOAD_ENABLE_Pos 0                                              /**< (AON_SLEEP_TIMER_CONTROL) Active High Reload Enable Position */
#define AON_SLEEP_TIMER_CONTROL_RELOAD_ENABLE_Msk (0x1u << AON_SLEEP_TIMER_CONTROL_RELOAD_ENABLE_Pos)  /**< (AON_SLEEP_TIMER_CONTROL) Active High Reload Enable Mask */
#define AON_SLEEP_TIMER_CONTROL_RELOAD_ENABLE AON_SLEEP_TIMER_CONTROL_RELOAD_ENABLE_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_SLEEP_TIMER_CONTROL_RELOAD_ENABLE_Msk instead */
#define AON_SLEEP_TIMER_CONTROL_SINGLE_COUNT_ENABLE_Pos 1                                              /**< (AON_SLEEP_TIMER_CONTROL) Rising Edge Single Count Enable Position */
#define AON_SLEEP_TIMER_CONTROL_SINGLE_COUNT_ENABLE_Msk (0x1u << AON_SLEEP_TIMER_CONTROL_SINGLE_COUNT_ENABLE_Pos)  /**< (AON_SLEEP_TIMER_CONTROL) Rising Edge Single Count Enable Mask */
#define AON_SLEEP_TIMER_CONTROL_SINGLE_COUNT_ENABLE AON_SLEEP_TIMER_CONTROL_SINGLE_COUNT_ENABLE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_SLEEP_TIMER_CONTROL_SINGLE_COUNT_ENABLE_Msk instead */
#define AON_SLEEP_TIMER_CONTROL_IRQ_CLEAR_Pos 4                                              /**< (AON_SLEEP_TIMER_CONTROL) Clears the interrupt. Auto clear. Must only be set after receiving the IRQ. Position */
#define AON_SLEEP_TIMER_CONTROL_IRQ_CLEAR_Msk (0x1u << AON_SLEEP_TIMER_CONTROL_IRQ_CLEAR_Pos)  /**< (AON_SLEEP_TIMER_CONTROL) Clears the interrupt. Auto clear. Must only be set after receiving the IRQ. Mask */
#define AON_SLEEP_TIMER_CONTROL_IRQ_CLEAR   AON_SLEEP_TIMER_CONTROL_IRQ_CLEAR_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_SLEEP_TIMER_CONTROL_IRQ_CLEAR_Msk instead */
#define AON_SLEEP_TIMER_CONTROL_SLP_TIMER_CLK_RELOAD_DLY_Pos 8                                              /**< (AON_SLEEP_TIMER_CONTROL) Current Status of slp_timer_clk_reload on the sleep clock Position */
#define AON_SLEEP_TIMER_CONTROL_SLP_TIMER_CLK_RELOAD_DLY_Msk (0x3u << AON_SLEEP_TIMER_CONTROL_SLP_TIMER_CLK_RELOAD_DLY_Pos)  /**< (AON_SLEEP_TIMER_CONTROL) Current Status of slp_timer_clk_reload on the sleep clock Mask */
#define AON_SLEEP_TIMER_CONTROL_SLP_TIMER_CLK_RELOAD_DLY(value) (AON_SLEEP_TIMER_CONTROL_SLP_TIMER_CLK_RELOAD_DLY_Msk & ((value) << AON_SLEEP_TIMER_CONTROL_SLP_TIMER_CLK_RELOAD_DLY_Pos))
#define AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_Pos 12                                             /**< (AON_SLEEP_TIMER_CONTROL) Current status of slp_timer_clk_single_count_enable on the sleep clock Position */
#define AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_Msk (0x7u << AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_Pos)  /**< (AON_SLEEP_TIMER_CONTROL) Current status of slp_timer_clk_single_count_enable on the sleep clock Mask */
#define AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY(value) (AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_Msk & ((value) << AON_SLEEP_TIMER_CONTROL_SLP_TIMER_SINGLE_COUNT_ENABLE_DLY_Pos))
#define AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_ACTIVE_Pos 30                                             /**< (AON_SLEEP_TIMER_CONTROL) If 1, indicates that the current sleep tiemr value is not 0 Position */
#define AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_ACTIVE_Msk (0x1u << AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_ACTIVE_Pos)  /**< (AON_SLEEP_TIMER_CONTROL) If 1, indicates that the current sleep tiemr value is not 0 Mask */
#define AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_ACTIVE AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_ACTIVE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_ACTIVE_Msk instead */
#define AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_NOT_ACTIVE_Pos 31                                             /**< (AON_SLEEP_TIMER_CONTROL) If 1, indicates that the current sleep timer value is 0 Position */
#define AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_NOT_ACTIVE_Msk (0x1u << AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_NOT_ACTIVE_Pos)  /**< (AON_SLEEP_TIMER_CONTROL) If 1, indicates that the current sleep timer value is 0 Mask */
#define AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_NOT_ACTIVE AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_NOT_ACTIVE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use AON_SLEEP_TIMER_CONTROL_SLEEP_TIMER_NOT_ACTIVE_Msk instead */
#define AON_SLEEP_TIMER_CONTROL_MASK        0xC0007313u                                    /**< \deprecated (AON_SLEEP_TIMER_CONTROL) Register MASK  (Use AON_SLEEP_TIMER_CONTROL_Msk instead)  */
#define AON_SLEEP_TIMER_CONTROL_Msk         0xC0007313u                                    /**< (AON_SLEEP_TIMER_CONTROL) Register Mask  */

/* -------- AON_SLEEP_TIMER_SINGLE_COUNT_DURATION : (AON_SLEEP_TIMER Offset: 0x04) (R/W 32) Count for the single count AND reload -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t SINGLE_COUNT_DURATION:32;  /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_OFFSET 0x04                                          /**<  (AON_SLEEP_TIMER_SINGLE_COUNT_DURATION) Count for the single count AND reload  Offset */
#define AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_RESETVALUE 0x00u                                         /**<  (AON_SLEEP_TIMER_SINGLE_COUNT_DURATION) Count for the single count AND reload  Reset Value */

#define AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_SINGLE_COUNT_DURATION_Pos 0                                              /**< (AON_SLEEP_TIMER_SINGLE_COUNT_DURATION)  Position */
#define AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_SINGLE_COUNT_DURATION_Msk (0xFFFFFFFFu << AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_SINGLE_COUNT_DURATION_Pos)  /**< (AON_SLEEP_TIMER_SINGLE_COUNT_DURATION)  Mask */
#define AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_SINGLE_COUNT_DURATION(value) (AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_SINGLE_COUNT_DURATION_Msk & ((value) << AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_SINGLE_COUNT_DURATION_Pos))
#define AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_MASK 0xFFFFFFFFu                                    /**< \deprecated (AON_SLEEP_TIMER_SINGLE_COUNT_DURATION) Register MASK  (Use AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_Msk instead)  */
#define AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_Msk 0xFFFFFFFFu                                    /**< (AON_SLEEP_TIMER_SINGLE_COUNT_DURATION) Register Mask  */

/* -------- AON_SLEEP_TIMER_CURRENT_COUNT_VALUE : (AON_SLEEP_TIMER Offset: 0x0c) (R/ 32) Current count of the sleep timer -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CURRENT_COUNT_VALUE:32;    /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_OFFSET 0x0C                                          /**<  (AON_SLEEP_TIMER_CURRENT_COUNT_VALUE) Current count of the sleep timer  Offset */
#define AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_RESETVALUE 0x00u                                         /**<  (AON_SLEEP_TIMER_CURRENT_COUNT_VALUE) Current count of the sleep timer  Reset Value */

#define AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_CURRENT_COUNT_VALUE_Pos 0                                              /**< (AON_SLEEP_TIMER_CURRENT_COUNT_VALUE)  Position */
#define AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_CURRENT_COUNT_VALUE_Msk (0xFFFFFFFFu << AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_CURRENT_COUNT_VALUE_Pos)  /**< (AON_SLEEP_TIMER_CURRENT_COUNT_VALUE)  Mask */
#define AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_CURRENT_COUNT_VALUE(value) (AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_CURRENT_COUNT_VALUE_Msk & ((value) << AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_CURRENT_COUNT_VALUE_Pos))
#define AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_MASK 0xFFFFFFFFu                                    /**< \deprecated (AON_SLEEP_TIMER_CURRENT_COUNT_VALUE) Register MASK  (Use AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_Msk instead)  */
#define AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_Msk 0xFFFFFFFFu                                    /**< (AON_SLEEP_TIMER_CURRENT_COUNT_VALUE) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief AON_SLEEP_TIMER hardware registers */
typedef struct {  /* Always On Sleep Timer */
  RwReg   CONTROL;        /**< (AON_SLEEP_TIMER Offset: 0x00) Control for the Always On Sleep Timer */
  RwReg   SINGLE_COUNT_DURATION; /**< (AON_SLEEP_TIMER Offset: 0x04) Count for the single count AND reload */
  __I  uint32_t Reserved1[1];
  RoReg   CURRENT_COUNT_VALUE; /**< (AON_SLEEP_TIMER Offset: 0x0C) Current count of the sleep timer */
} AonSleepTimer;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief AON_SLEEP_TIMER hardware registers */
typedef struct {  /* Always On Sleep Timer */
  __IO AON_SLEEP_TIMER_CONTROL_Type   CONTROL;        /**< Offset: 0x00 (R/W  32) Control for the Always On Sleep Timer */
  __IO AON_SLEEP_TIMER_SINGLE_COUNT_DURATION_Type SINGLE_COUNT_DURATION; /**< Offset: 0x04 (R/W  32) Count for the single count AND reload */
       RoReg8                         Reserved1[0x4];
  __I  AON_SLEEP_TIMER_CURRENT_COUNT_VALUE_Type CURRENT_COUNT_VALUE; /**< Offset: 0x0C (R/   32) Current count of the sleep timer */
} AonSleepTimer;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_AON_SLEEP_TIMER_COMPONENT_ */
