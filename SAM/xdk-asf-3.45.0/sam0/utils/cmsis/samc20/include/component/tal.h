/**
 * \file
 *
 * \brief Component description for TAL
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

#ifndef _SAMC20_TAL_COMPONENT_
#define _SAMC20_TAL_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR TAL */
/* ========================================================================== */
/** \addtogroup SAMC20_TAL Trigger Allocator */
/*@{*/

#define TAL_U2253
#define REV_TAL                     0x103

/* -------- TAL_CTRLA : (TAL Offset: 0x00) (R/W  8) Control A -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  SWRST:1;          /*!< bit:      0  Software Reset                     */
    uint8_t  ENABLE:1;         /*!< bit:      1  Enable                             */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_CTRLA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_CTRLA_OFFSET            0x00         /**< \brief (TAL_CTRLA offset) Control A */
#define TAL_CTRLA_RESETVALUE        0x00ul       /**< \brief (TAL_CTRLA reset_value) Control A */

#define TAL_CTRLA_SWRST_Pos         0            /**< \brief (TAL_CTRLA) Software Reset */
#define TAL_CTRLA_SWRST             (0x1ul << TAL_CTRLA_SWRST_Pos)
#define TAL_CTRLA_ENABLE_Pos        1            /**< \brief (TAL_CTRLA) Enable */
#define TAL_CTRLA_ENABLE            (0x1ul << TAL_CTRLA_ENABLE_Pos)
#define TAL_CTRLA_MASK              0x03ul       /**< \brief (TAL_CTRLA) MASK Register */

/* -------- TAL_RSTCTRL : (TAL Offset: 0x04) (R/W  8) Reset Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_RSTCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_RSTCTRL_OFFSET          0x04         /**< \brief (TAL_RSTCTRL offset) Reset Control */
#define TAL_RSTCTRL_RESETVALUE      0x00ul       /**< \brief (TAL_RSTCTRL reset_value) Reset Control */
#define TAL_RSTCTRL_MASK            0x00ul       /**< \brief (TAL_RSTCTRL) MASK Register */

/* -------- TAL_EXTCTRL : (TAL Offset: 0x05) (R/W  8) External Break Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  ENABLE:1;         /*!< bit:      0  Enable BRK Pin                     */
    uint8_t  INV:1;            /*!< bit:      1  Invert BRK Pin                     */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_EXTCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_EXTCTRL_OFFSET          0x05         /**< \brief (TAL_EXTCTRL offset) External Break Control */
#define TAL_EXTCTRL_RESETVALUE      0x00ul       /**< \brief (TAL_EXTCTRL reset_value) External Break Control */

#define TAL_EXTCTRL_ENABLE_Pos      0            /**< \brief (TAL_EXTCTRL) Enable BRK Pin */
#define TAL_EXTCTRL_ENABLE          (0x1ul << TAL_EXTCTRL_ENABLE_Pos)
#define TAL_EXTCTRL_INV_Pos         1            /**< \brief (TAL_EXTCTRL) Invert BRK Pin */
#define TAL_EXTCTRL_INV             (0x1ul << TAL_EXTCTRL_INV_Pos)
#define TAL_EXTCTRL_MASK            0x03ul       /**< \brief (TAL_EXTCTRL) MASK Register */

/* -------- TAL_EVCTRL : (TAL Offset: 0x06) (R/W  8) Event Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  BRKEI:1;          /*!< bit:      0  Break Input Event Enable           */
    uint8_t  BRKEO:1;          /*!< bit:      1  Break Output Event Enable          */
    uint8_t  :6;               /*!< bit:  2.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_EVCTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_EVCTRL_OFFSET           0x06         /**< \brief (TAL_EVCTRL offset) Event Control */
#define TAL_EVCTRL_RESETVALUE       0x00ul       /**< \brief (TAL_EVCTRL reset_value) Event Control */

#define TAL_EVCTRL_BRKEI_Pos        0            /**< \brief (TAL_EVCTRL) Break Input Event Enable */
#define TAL_EVCTRL_BRKEI            (0x1ul << TAL_EVCTRL_BRKEI_Pos)
#define TAL_EVCTRL_BRKEO_Pos        1            /**< \brief (TAL_EVCTRL) Break Output Event Enable */
#define TAL_EVCTRL_BRKEO            (0x1ul << TAL_EVCTRL_BRKEO_Pos)
#define TAL_EVCTRL_MASK             0x03ul       /**< \brief (TAL_EVCTRL) MASK Register */

/* -------- TAL_INTENCLR : (TAL Offset: 0x08) (R/W  8) Interrupt Enable Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  BRK:1;            /*!< bit:      0  Break Interrupt Enable             */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_INTENCLR_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_INTENCLR_OFFSET         0x08         /**< \brief (TAL_INTENCLR offset) Interrupt Enable Clear */
#define TAL_INTENCLR_RESETVALUE     0x00ul       /**< \brief (TAL_INTENCLR reset_value) Interrupt Enable Clear */

#define TAL_INTENCLR_BRK_Pos        0            /**< \brief (TAL_INTENCLR) Break Interrupt Enable */
#define TAL_INTENCLR_BRK            (0x1ul << TAL_INTENCLR_BRK_Pos)
#define TAL_INTENCLR_MASK           0x01ul       /**< \brief (TAL_INTENCLR) MASK Register */

/* -------- TAL_INTENSET : (TAL Offset: 0x09) (R/W  8) Interrupt Enable Set -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  BRK:1;            /*!< bit:      0  Break Interrupt Enable             */
    uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_INTENSET_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_INTENSET_OFFSET         0x09         /**< \brief (TAL_INTENSET offset) Interrupt Enable Set */
#define TAL_INTENSET_RESETVALUE     0x00ul       /**< \brief (TAL_INTENSET reset_value) Interrupt Enable Set */

#define TAL_INTENSET_BRK_Pos        0            /**< \brief (TAL_INTENSET) Break Interrupt Enable */
#define TAL_INTENSET_BRK            (0x1ul << TAL_INTENSET_BRK_Pos)
#define TAL_INTENSET_MASK           0x01ul       /**< \brief (TAL_INTENSET) MASK Register */

/* -------- TAL_INTFLAG : (TAL Offset: 0x0A) (R/W  8) Interrupt Flag Status and Clear -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { // __I to avoid read-modify-write on write-to-clear register
  struct {
    __I uint8_t  BRK:1;            /*!< bit:      0  Break                              */
    __I uint8_t  :7;               /*!< bit:  1.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_INTFLAG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_INTFLAG_OFFSET          0x0A         /**< \brief (TAL_INTFLAG offset) Interrupt Flag Status and Clear */
#define TAL_INTFLAG_RESETVALUE      0x00ul       /**< \brief (TAL_INTFLAG reset_value) Interrupt Flag Status and Clear */

#define TAL_INTFLAG_BRK_Pos         0            /**< \brief (TAL_INTFLAG) Break */
#define TAL_INTFLAG_BRK             (0x1ul << TAL_INTFLAG_BRK_Pos)
#define TAL_INTFLAG_MASK            0x01ul       /**< \brief (TAL_INTFLAG) MASK Register */

/* -------- TAL_GLOBMASK : (TAL Offset: 0x0B) (R/W  8) Global Break Requests Mask -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  CM0P:1;           /*!< bit:      0  CM0P Break Master                  */
    uint8_t  :5;               /*!< bit:  1.. 5  Reserved                           */
    uint8_t  EVBRK:1;          /*!< bit:      6  Event Break Master                 */
    uint8_t  EXTBRK:1;         /*!< bit:      7  External Break Master              */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_GLOBMASK_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_GLOBMASK_OFFSET         0x0B         /**< \brief (TAL_GLOBMASK offset) Global Break Requests Mask */
#define TAL_GLOBMASK_RESETVALUE     0x00ul       /**< \brief (TAL_GLOBMASK reset_value) Global Break Requests Mask */

#define TAL_GLOBMASK_CM0P_Pos       0            /**< \brief (TAL_GLOBMASK) CM0P Break Master */
#define TAL_GLOBMASK_CM0P           (0x1ul << TAL_GLOBMASK_CM0P_Pos)
#define TAL_GLOBMASK_EVBRK_Pos      6            /**< \brief (TAL_GLOBMASK) Event Break Master */
#define TAL_GLOBMASK_EVBRK          (0x1ul << TAL_GLOBMASK_EVBRK_Pos)
#define TAL_GLOBMASK_EXTBRK_Pos     7            /**< \brief (TAL_GLOBMASK) External Break Master */
#define TAL_GLOBMASK_EXTBRK         (0x1ul << TAL_GLOBMASK_EXTBRK_Pos)
#define TAL_GLOBMASK_MASK           0xC1ul       /**< \brief (TAL_GLOBMASK) MASK Register */

/* -------- TAL_HALT : (TAL Offset: 0x0C) ( /W  8) Debug Halt Request -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  CM0P:1;           /*!< bit:      0  CM0P Break Master                  */
    uint8_t  :5;               /*!< bit:  1.. 5  Reserved                           */
    uint8_t  EVBRK:1;          /*!< bit:      6  Event Break Master                 */
    uint8_t  EXTBRK:1;         /*!< bit:      7  External Break Master              */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_HALT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_HALT_OFFSET             0x0C         /**< \brief (TAL_HALT offset) Debug Halt Request */
#define TAL_HALT_RESETVALUE         0x00ul       /**< \brief (TAL_HALT reset_value) Debug Halt Request */

#define TAL_HALT_CM0P_Pos           0            /**< \brief (TAL_HALT) CM0P Break Master */
#define TAL_HALT_CM0P               (0x1ul << TAL_HALT_CM0P_Pos)
#define TAL_HALT_EVBRK_Pos          6            /**< \brief (TAL_HALT) Event Break Master */
#define TAL_HALT_EVBRK              (0x1ul << TAL_HALT_EVBRK_Pos)
#define TAL_HALT_EXTBRK_Pos         7            /**< \brief (TAL_HALT) External Break Master */
#define TAL_HALT_EXTBRK             (0x1ul << TAL_HALT_EXTBRK_Pos)
#define TAL_HALT_MASK               0xC1ul       /**< \brief (TAL_HALT) MASK Register */

/* -------- TAL_RESTART : (TAL Offset: 0x0D) ( /W  8) Debug Restart Request -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  CM0P:1;           /*!< bit:      0  CM0P Break Master                  */
    uint8_t  :6;               /*!< bit:  1.. 6  Reserved                           */
    uint8_t  EXTBRK:1;         /*!< bit:      7  External Break Master              */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_RESTART_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_RESTART_OFFSET          0x0D         /**< \brief (TAL_RESTART offset) Debug Restart Request */
#define TAL_RESTART_RESETVALUE      0x00ul       /**< \brief (TAL_RESTART reset_value) Debug Restart Request */

#define TAL_RESTART_CM0P_Pos        0            /**< \brief (TAL_RESTART) CM0P Break Master */
#define TAL_RESTART_CM0P            (0x1ul << TAL_RESTART_CM0P_Pos)
#define TAL_RESTART_EXTBRK_Pos      7            /**< \brief (TAL_RESTART) External Break Master */
#define TAL_RESTART_EXTBRK          (0x1ul << TAL_RESTART_EXTBRK_Pos)
#define TAL_RESTART_MASK            0x81ul       /**< \brief (TAL_RESTART) MASK Register */

/* -------- TAL_BRKSTATUS : (TAL Offset: 0x0E) (R/  16) Break Request Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t CM0P:2;           /*!< bit:  0.. 1  CM0P Break Request                 */
    uint16_t :10;              /*!< bit:  2..11  Reserved                           */
    uint16_t EVBRK:2;          /*!< bit: 12..13  Event Break Request                */
    uint16_t EXTBRK:2;         /*!< bit: 14..15  External Break Request             */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} TAL_BRKSTATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_BRKSTATUS_OFFSET        0x0E         /**< \brief (TAL_BRKSTATUS offset) Break Request Status */
#define TAL_BRKSTATUS_RESETVALUE    0x0000ul     /**< \brief (TAL_BRKSTATUS reset_value) Break Request Status */

#define TAL_BRKSTATUS_CM0P_Pos      0            /**< \brief (TAL_BRKSTATUS) CM0P Break Request */
#define TAL_BRKSTATUS_CM0P_Msk      (0x3ul << TAL_BRKSTATUS_CM0P_Pos)
#define TAL_BRKSTATUS_CM0P(value)   (TAL_BRKSTATUS_CM0P_Msk & ((value) << TAL_BRKSTATUS_CM0P_Pos))
#define TAL_BRKSTATUS_EVBRK_Pos     12           /**< \brief (TAL_BRKSTATUS) Event Break Request */
#define TAL_BRKSTATUS_EVBRK_Msk     (0x3ul << TAL_BRKSTATUS_EVBRK_Pos)
#define TAL_BRKSTATUS_EVBRK(value)  (TAL_BRKSTATUS_EVBRK_Msk & ((value) << TAL_BRKSTATUS_EVBRK_Pos))
#define TAL_BRKSTATUS_EXTBRK_Pos    14           /**< \brief (TAL_BRKSTATUS) External Break Request */
#define TAL_BRKSTATUS_EXTBRK_Msk    (0x3ul << TAL_BRKSTATUS_EXTBRK_Pos)
#define TAL_BRKSTATUS_EXTBRK(value) (TAL_BRKSTATUS_EXTBRK_Msk & ((value) << TAL_BRKSTATUS_EXTBRK_Pos))
#define TAL_BRKSTATUS_MASK          0xF003ul     /**< \brief (TAL_BRKSTATUS) MASK Register */

/* -------- TAL_CTICTRLA : (TAL Offset: 0x10) (R/W  8) CTIS Cross-Trigger Interface n Control A -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  ACTION:2;         /*!< bit:  0.. 1  Action when global break issued    */
    uint8_t  RESTART:1;        /*!< bit:      2  Action when global restart issued  */
    uint8_t  :5;               /*!< bit:  3.. 7  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_CTICTRLA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_CTICTRLA_OFFSET         0x10         /**< \brief (TAL_CTICTRLA offset) Cross-Trigger Interface n Control A */
#define TAL_CTICTRLA_RESETVALUE     0x00ul       /**< \brief (TAL_CTICTRLA reset_value) Cross-Trigger Interface n Control A */

#define TAL_CTICTRLA_ACTION_Pos     0            /**< \brief (TAL_CTICTRLA) Action when global break issued */
#define TAL_CTICTRLA_ACTION_Msk     (0x3ul << TAL_CTICTRLA_ACTION_Pos)
#define TAL_CTICTRLA_ACTION(value)  (TAL_CTICTRLA_ACTION_Msk & ((value) << TAL_CTICTRLA_ACTION_Pos))
#define   TAL_CTICTRLA_ACTION_BREAK_Val   0x0ul  /**< \brief (TAL_CTICTRLA) Break when requested */
#define   TAL_CTICTRLA_ACTION_INTERRUPT_Val 0x1ul  /**< \brief (TAL_CTICTRLA) Trigger DBG interrupt instead of break */
#define   TAL_CTICTRLA_ACTION_IGNORE_Val  0x2ul  /**< \brief (TAL_CTICTRLA) Ignore break request */
#define TAL_CTICTRLA_ACTION_BREAK   (TAL_CTICTRLA_ACTION_BREAK_Val << TAL_CTICTRLA_ACTION_Pos)
#define TAL_CTICTRLA_ACTION_INTERRUPT (TAL_CTICTRLA_ACTION_INTERRUPT_Val << TAL_CTICTRLA_ACTION_Pos)
#define TAL_CTICTRLA_ACTION_IGNORE  (TAL_CTICTRLA_ACTION_IGNORE_Val << TAL_CTICTRLA_ACTION_Pos)
#define TAL_CTICTRLA_RESTART_Pos    2            /**< \brief (TAL_CTICTRLA) Action when global restart issued */
#define TAL_CTICTRLA_RESTART        (0x1ul << TAL_CTICTRLA_RESTART_Pos)
#define TAL_CTICTRLA_MASK           0x07ul       /**< \brief (TAL_CTICTRLA) MASK Register */

/* -------- TAL_CTIMASK : (TAL Offset: 0x11) (R/W  8) CTIS Cross-Trigger Interface n Mask -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  CM0P:1;           /*!< bit:      0  CM0P Break Master                  */
    uint8_t  :5;               /*!< bit:  1.. 5  Reserved                           */
    uint8_t  EVBRK:1;          /*!< bit:      6  Event Break Master                 */
    uint8_t  EXTBRK:1;         /*!< bit:      7  External Break Master              */
  } bit;                       /*!< Structure used for bit  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_CTIMASK_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_CTIMASK_OFFSET          0x11         /**< \brief (TAL_CTIMASK offset) Cross-Trigger Interface n Mask */
#define TAL_CTIMASK_RESETVALUE      0x00ul       /**< \brief (TAL_CTIMASK reset_value) Cross-Trigger Interface n Mask */

#define TAL_CTIMASK_CM0P_Pos        0            /**< \brief (TAL_CTIMASK) CM0P Break Master */
#define TAL_CTIMASK_CM0P            (0x1ul << TAL_CTIMASK_CM0P_Pos)
#define TAL_CTIMASK_EVBRK_Pos       6            /**< \brief (TAL_CTIMASK) Event Break Master */
#define TAL_CTIMASK_EVBRK           (0x1ul << TAL_CTIMASK_EVBRK_Pos)
#define TAL_CTIMASK_EXTBRK_Pos      7            /**< \brief (TAL_CTIMASK) External Break Master */
#define TAL_CTIMASK_EXTBRK          (0x1ul << TAL_CTIMASK_EXTBRK_Pos)
#define TAL_CTIMASK_MASK            0xC1ul       /**< \brief (TAL_CTIMASK) MASK Register */

/* -------- TAL_INTSTATUS : (TAL Offset: 0x20) (R/   8) Interrupt n Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint8_t  IRQ0:1;           /*!< bit:      0  Interrupt Status for Interrupt Request 0 within Interrupt n */
    uint8_t  IRQ1:1;           /*!< bit:      1  Interrupt Status for Interrupt Request 1 within Interrupt n */
    uint8_t  IRQ2:1;           /*!< bit:      2  Interrupt Status for Interrupt Request 2 within Interrupt n */
    uint8_t  IRQ3:1;           /*!< bit:      3  Interrupt Status for Interrupt Request 3 within Interrupt n */
    uint8_t  IRQ4:1;           /*!< bit:      4  Interrupt Status for Interrupt Request 4 within Interrupt n */
    uint8_t  IRQ5:1;           /*!< bit:      5  Interrupt Status for Interrupt Request 5 within Interrupt n */
    uint8_t  IRQ6:1;           /*!< bit:      6  Interrupt Status for Interrupt Request 6 within Interrupt n */
    uint8_t  IRQ7:1;           /*!< bit:      7  Interrupt Status for Interrupt Request 7 within Interrupt n */
  } bit;                       /*!< Structure used for bit  access                  */
  struct {
    uint8_t  IRQ:8;            /*!< bit:  0.. 7  Interrupt Status for Interrupt Request x within Interrupt n */
  } vec;                       /*!< Structure used for vec  access                  */
  uint8_t reg;                 /*!< Type      used for register access              */
} TAL_INTSTATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_INTSTATUS_OFFSET        0x20         /**< \brief (TAL_INTSTATUS offset) Interrupt n Status */
#define TAL_INTSTATUS_RESETVALUE    0x00ul       /**< \brief (TAL_INTSTATUS reset_value) Interrupt n Status */

#define TAL_INTSTATUS_IRQ0_Pos      0            /**< \brief (TAL_INTSTATUS) Interrupt Status for Interrupt Request 0 within Interrupt n */
#define TAL_INTSTATUS_IRQ0          (1 << TAL_INTSTATUS_IRQ0_Pos)
#define TAL_INTSTATUS_IRQ1_Pos      1            /**< \brief (TAL_INTSTATUS) Interrupt Status for Interrupt Request 1 within Interrupt n */
#define TAL_INTSTATUS_IRQ1          (1 << TAL_INTSTATUS_IRQ1_Pos)
#define TAL_INTSTATUS_IRQ2_Pos      2            /**< \brief (TAL_INTSTATUS) Interrupt Status for Interrupt Request 2 within Interrupt n */
#define TAL_INTSTATUS_IRQ2          (1 << TAL_INTSTATUS_IRQ2_Pos)
#define TAL_INTSTATUS_IRQ3_Pos      3            /**< \brief (TAL_INTSTATUS) Interrupt Status for Interrupt Request 3 within Interrupt n */
#define TAL_INTSTATUS_IRQ3          (1 << TAL_INTSTATUS_IRQ3_Pos)
#define TAL_INTSTATUS_IRQ4_Pos      4            /**< \brief (TAL_INTSTATUS) Interrupt Status for Interrupt Request 4 within Interrupt n */
#define TAL_INTSTATUS_IRQ4          (1 << TAL_INTSTATUS_IRQ4_Pos)
#define TAL_INTSTATUS_IRQ5_Pos      5            /**< \brief (TAL_INTSTATUS) Interrupt Status for Interrupt Request 5 within Interrupt n */
#define TAL_INTSTATUS_IRQ5          (1 << TAL_INTSTATUS_IRQ5_Pos)
#define TAL_INTSTATUS_IRQ6_Pos      6            /**< \brief (TAL_INTSTATUS) Interrupt Status for Interrupt Request 6 within Interrupt n */
#define TAL_INTSTATUS_IRQ6          (1 << TAL_INTSTATUS_IRQ6_Pos)
#define TAL_INTSTATUS_IRQ7_Pos      7            /**< \brief (TAL_INTSTATUS) Interrupt Status for Interrupt Request 7 within Interrupt n */
#define TAL_INTSTATUS_IRQ7          (1 << TAL_INTSTATUS_IRQ7_Pos)
#define TAL_INTSTATUS_IRQ_Pos       0            /**< \brief (TAL_INTSTATUS) Interrupt Status for Interrupt Request x within Interrupt n */
#define TAL_INTSTATUS_IRQ_Msk       (0xFFul << TAL_INTSTATUS_IRQ_Pos)
#define TAL_INTSTATUS_IRQ(value)    (TAL_INTSTATUS_IRQ_Msk & ((value) << TAL_INTSTATUS_IRQ_Pos))
#define TAL_INTSTATUS_MASK          0xFFul       /**< \brief (TAL_INTSTATUS) MASK Register */

/* -------- TAL_IRQTRIG : (TAL Offset: 0x60) (R/W 16) Interrupt Trigger -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t ENABLE:1;         /*!< bit:      0  Trigger Enable                     */
    uint16_t IRQNUM:5;         /*!< bit:  1.. 5  Interrupt Request Number           */
    uint16_t :2;               /*!< bit:  6.. 7  Reserved                           */
    uint16_t OVERRIDE:8;       /*!< bit:  8..15  Interrupt Request Override Value   */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} TAL_IRQTRIG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_IRQTRIG_OFFSET          0x60         /**< \brief (TAL_IRQTRIG offset) Interrupt Trigger */
#define TAL_IRQTRIG_RESETVALUE      0x0000ul     /**< \brief (TAL_IRQTRIG reset_value) Interrupt Trigger */

#define TAL_IRQTRIG_ENABLE_Pos      0            /**< \brief (TAL_IRQTRIG) Trigger Enable */
#define TAL_IRQTRIG_ENABLE          (0x1ul << TAL_IRQTRIG_ENABLE_Pos)
#define TAL_IRQTRIG_IRQNUM_Pos      1            /**< \brief (TAL_IRQTRIG) Interrupt Request Number */
#define TAL_IRQTRIG_IRQNUM_Msk      (0x1Ful << TAL_IRQTRIG_IRQNUM_Pos)
#define TAL_IRQTRIG_IRQNUM(value)   (TAL_IRQTRIG_IRQNUM_Msk & ((value) << TAL_IRQTRIG_IRQNUM_Pos))
#define TAL_IRQTRIG_OVERRIDE_Pos    8            /**< \brief (TAL_IRQTRIG) Interrupt Request Override Value */
#define TAL_IRQTRIG_OVERRIDE_Msk    (0xFFul << TAL_IRQTRIG_OVERRIDE_Pos)
#define TAL_IRQTRIG_OVERRIDE(value) (TAL_IRQTRIG_OVERRIDE_Msk & ((value) << TAL_IRQTRIG_OVERRIDE_Pos))
#define TAL_IRQTRIG_MASK            0xFF3Ful     /**< \brief (TAL_IRQTRIG) MASK Register */

/* -------- TAL_CPUIRQS : (TAL Offset: 0x64) (R/  32) Interrupt Status for CPU n -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint32_t CPUIRQS:31;       /*!< bit:  0..30  Interrupt Requests for CPU n       */
    uint32_t :1;               /*!< bit:     31  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint32_t reg;                /*!< Type      used for register access              */
} TAL_CPUIRQS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define TAL_CPUIRQS_OFFSET          0x64         /**< \brief (TAL_CPUIRQS offset) Interrupt Status for CPU n */
#define TAL_CPUIRQS_RESETVALUE      0x00000000ul /**< \brief (TAL_CPUIRQS reset_value) Interrupt Status for CPU n */

#define TAL_CPUIRQS_CPUIRQS_Pos     0            /**< \brief (TAL_CPUIRQS) Interrupt Requests for CPU n */
#define TAL_CPUIRQS_CPUIRQS_Msk     (0x7FFFFFFFul << TAL_CPUIRQS_CPUIRQS_Pos)
#define TAL_CPUIRQS_CPUIRQS(value)  (TAL_CPUIRQS_CPUIRQS_Msk & ((value) << TAL_CPUIRQS_CPUIRQS_Pos))
#define TAL_CPUIRQS_MASK            0x7FFFFFFFul /**< \brief (TAL_CPUIRQS) MASK Register */

/** \brief TalCtis hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  __IO TAL_CTICTRLA_Type         CTICTRLA;    /**< \brief Offset: 0x00 (R/W  8) Cross-Trigger Interface n Control A */
  __IO TAL_CTIMASK_Type          CTIMASK;     /**< \brief Offset: 0x01 (R/W  8) Cross-Trigger Interface n Mask */
} TalCtis;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** \brief TAL hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  __IO TAL_CTRLA_Type            CTRLA;       /**< \brief Offset: 0x00 (R/W  8) Control A */
       RoReg8                    Reserved1[0x3];
  __IO TAL_RSTCTRL_Type          RSTCTRL;     /**< \brief Offset: 0x04 (R/W  8) Reset Control */
  __IO TAL_EXTCTRL_Type          EXTCTRL;     /**< \brief Offset: 0x05 (R/W  8) External Break Control */
  __IO TAL_EVCTRL_Type           EVCTRL;      /**< \brief Offset: 0x06 (R/W  8) Event Control */
       RoReg8                    Reserved2[0x1];
  __IO TAL_INTENCLR_Type         INTENCLR;    /**< \brief Offset: 0x08 (R/W  8) Interrupt Enable Clear */
  __IO TAL_INTENSET_Type         INTENSET;    /**< \brief Offset: 0x09 (R/W  8) Interrupt Enable Set */
  __IO TAL_INTFLAG_Type          INTFLAG;     /**< \brief Offset: 0x0A (R/W  8) Interrupt Flag Status and Clear */
  __IO TAL_GLOBMASK_Type         GLOBMASK;    /**< \brief Offset: 0x0B (R/W  8) Global Break Requests Mask */
  __O  TAL_HALT_Type             HALT;        /**< \brief Offset: 0x0C ( /W  8) Debug Halt Request */
  __O  TAL_RESTART_Type          RESTART;     /**< \brief Offset: 0x0D ( /W  8) Debug Restart Request */
  __I  TAL_BRKSTATUS_Type        BRKSTATUS;   /**< \brief Offset: 0x0E (R/  16) Break Request Status */
       TalCtis                   Ctis[3];     /**< \brief Offset: 0x10 TalCtis groups [CTI_NUM] */
       RoReg8                    Reserved3[0xA];
  __I  TAL_INTSTATUS_Type        INTSTATUS[31]; /**< \brief Offset: 0x20 (R/   8) Interrupt n Status */
       RoReg8                    Reserved4[0x21];
  __IO TAL_IRQTRIG_Type          IRQTRIG;     /**< \brief Offset: 0x60 (R/W 16) Interrupt Trigger */
       RoReg8                    Reserved5[0x2];
  __I  TAL_CPUIRQS_Type          CPUIRQS[1];  /**< \brief Offset: 0x64 (R/  32) Interrupt Status for CPU n */
} Tal;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMC20_TAL_COMPONENT_ */
