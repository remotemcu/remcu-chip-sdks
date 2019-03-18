/**
 * \file
 *
 * \brief Component description for RFCTRL
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

#ifndef _SAMR21_RFCTRL_COMPONENT_
#define _SAMR21_RFCTRL_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR RFCTRL */
/* ========================================================================== */
/** \addtogroup SAMR21_RFCTRL RF233 control module */
/*@{*/

#define RFCTRL_U2233
#define REV_RFCTRL                  0x100

/* -------- RFCTRL_FECFG : (RFCTRL Offset: 0x0) (R/W 16) Front-end control bus configuration -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union {
  struct {
    uint16_t F0CFG:2;          /*!< bit:  0.. 1  Front-end control signal 0 configuration */
    uint16_t F1CFG:2;          /*!< bit:  2.. 3  Front-end control signal 1 configuration */
    uint16_t F2CFG:2;          /*!< bit:  4.. 5  Front-end control signal 2 configuration */
    uint16_t F3CFG:2;          /*!< bit:  6.. 7  Front-end control signal 3 configuration */
    uint16_t F4CFG:2;          /*!< bit:  8.. 9  Front-end control signal 4 configuration */
    uint16_t F5CFG:2;          /*!< bit: 10..11  Front-end control signal 5 configuration */
    uint16_t :4;               /*!< bit: 12..15  Reserved                           */
  } bit;                       /*!< Structure used for bit  access                  */
  uint16_t reg;                /*!< Type      used for register access              */
} RFCTRL_FECFG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define RFCTRL_FECFG_OFFSET         0x0          /**< \brief (RFCTRL_FECFG offset) Front-end control bus configuration */
#define RFCTRL_FECFG_RESETVALUE     0x0000ul     /**< \brief (RFCTRL_FECFG reset_value) Front-end control bus configuration */

#define RFCTRL_FECFG_F0CFG_Pos      0            /**< \brief (RFCTRL_FECFG) Front-end control signal 0 configuration */
#define RFCTRL_FECFG_F0CFG_Msk      (0x3ul << RFCTRL_FECFG_F0CFG_Pos)
#define RFCTRL_FECFG_F0CFG(value)   (RFCTRL_FECFG_F0CFG_Msk & ((value) << RFCTRL_FECFG_F0CFG_Pos))
#define RFCTRL_FECFG_F1CFG_Pos      2            /**< \brief (RFCTRL_FECFG) Front-end control signal 1 configuration */
#define RFCTRL_FECFG_F1CFG_Msk      (0x3ul << RFCTRL_FECFG_F1CFG_Pos)
#define RFCTRL_FECFG_F1CFG(value)   (RFCTRL_FECFG_F1CFG_Msk & ((value) << RFCTRL_FECFG_F1CFG_Pos))
#define RFCTRL_FECFG_F2CFG_Pos      4            /**< \brief (RFCTRL_FECFG) Front-end control signal 2 configuration */
#define RFCTRL_FECFG_F2CFG_Msk      (0x3ul << RFCTRL_FECFG_F2CFG_Pos)
#define RFCTRL_FECFG_F2CFG(value)   (RFCTRL_FECFG_F2CFG_Msk & ((value) << RFCTRL_FECFG_F2CFG_Pos))
#define RFCTRL_FECFG_F3CFG_Pos      6            /**< \brief (RFCTRL_FECFG) Front-end control signal 3 configuration */
#define RFCTRL_FECFG_F3CFG_Msk      (0x3ul << RFCTRL_FECFG_F3CFG_Pos)
#define RFCTRL_FECFG_F3CFG(value)   (RFCTRL_FECFG_F3CFG_Msk & ((value) << RFCTRL_FECFG_F3CFG_Pos))
#define RFCTRL_FECFG_F4CFG_Pos      8            /**< \brief (RFCTRL_FECFG) Front-end control signal 4 configuration */
#define RFCTRL_FECFG_F4CFG_Msk      (0x3ul << RFCTRL_FECFG_F4CFG_Pos)
#define RFCTRL_FECFG_F4CFG(value)   (RFCTRL_FECFG_F4CFG_Msk & ((value) << RFCTRL_FECFG_F4CFG_Pos))
#define RFCTRL_FECFG_F5CFG_Pos      10           /**< \brief (RFCTRL_FECFG) Front-end control signal 5 configuration */
#define RFCTRL_FECFG_F5CFG_Msk      (0x3ul << RFCTRL_FECFG_F5CFG_Pos)
#define RFCTRL_FECFG_F5CFG(value)   (RFCTRL_FECFG_F5CFG_Msk & ((value) << RFCTRL_FECFG_F5CFG_Pos))
#define RFCTRL_FECFG_MASK           0x0FFFul     /**< \brief (RFCTRL_FECFG) MASK Register */

/** \brief RFCTRL hardware registers */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
  __IO RFCTRL_FECFG_Type         FECFG;       /**< \brief Offset: 0x0 (R/W 16) Front-end control bus configuration */
} Rfctrl;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/*@}*/

#endif /* _SAMR21_RFCTRL_COMPONENT_ */
