/**
 * \file
 *
 * \brief Component description for LINCTRL
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES,
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

#ifndef _SAMHA0_LINCTRL_COMPONENT_
#define _SAMHA0_LINCTRL_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR LINCTRL */
/* ========================================================================== */
/** \addtogroup SAMHA0_LINCTRL LIN control module */
/*@{*/

#define LINCTRL_U2255
#define REV_LINCTRL                 0x100

/* -------- LINCTRL_CTRL : (LINCTRL Offset: 0x0) (R/W 16) control register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t WOCFG:2;          /*!< bit:  0.. 1  wkout observation select           */
    uint16_t :14;              /*!< bit:  2..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} LINCTRL_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define LINCTRL_CTRL_OFFSET         0x0          /**< \brief (LINCTRL_CTRL offset) control register */
#define LINCTRL_CTRL_RESETVALUE     _U_(0x0000)  /**< \brief (LINCTRL_CTRL reset_value) control register */

#define LINCTRL_CTRL_WOCFG_Pos      0            /**< \brief (LINCTRL_CTRL) wkout observation select */
#define LINCTRL_CTRL_WOCFG_Msk      (_U_(0x3) << LINCTRL_CTRL_WOCFG_Pos)
#define LINCTRL_CTRL_WOCFG(value)   (LINCTRL_CTRL_WOCFG_Msk & ((value) << LINCTRL_CTRL_WOCFG_Pos))
#define LINCTRL_CTRL_MASK           _U_(0x0003)  /**< \brief (LINCTRL_CTRL) MASK Register */

/** \brief LINCTRL hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  __IO LINCTRL_CTRL_Type         CTRL;        /**< \brief Offset: 0x0 (R/W 16) control register */
} Linctrl;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMHA0_LINCTRL_COMPONENT_ */
