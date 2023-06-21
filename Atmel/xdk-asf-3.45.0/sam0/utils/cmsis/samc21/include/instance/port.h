/**
 * \file
 *
 * \brief Instance description for PORT
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

#ifndef _SAMC21_PORT_INSTANCE_
#define _SAMC21_PORT_INSTANCE_

/* ========== Register definition for PORT peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_PORT_DIR0              (0x41000000U) /**< \brief (PORT) Data Direction 0 */
#define REG_PORT_DIRCLR0           (0x41000004U) /**< \brief (PORT) Data Direction Clear 0 */
#define REG_PORT_DIRSET0           (0x41000008U) /**< \brief (PORT) Data Direction Set 0 */
#define REG_PORT_DIRTGL0           (0x4100000CU) /**< \brief (PORT) Data Direction Toggle 0 */
#define REG_PORT_OUT0              (0x41000010U) /**< \brief (PORT) Data Output Value 0 */
#define REG_PORT_OUTCLR0           (0x41000014U) /**< \brief (PORT) Data Output Value Clear 0 */
#define REG_PORT_OUTSET0           (0x41000018U) /**< \brief (PORT) Data Output Value Set 0 */
#define REG_PORT_OUTTGL0           (0x4100001CU) /**< \brief (PORT) Data Output Value Toggle 0 */
#define REG_PORT_IN0               (0x41000020U) /**< \brief (PORT) Data Input Value 0 */
#define REG_PORT_CTRL0             (0x41000024U) /**< \brief (PORT) Control 0 */
#define REG_PORT_WRCONFIG0         (0x41000028U) /**< \brief (PORT) Write Configuration 0 */
#define REG_PORT_EVCTRL0           (0x4100002CU) /**< \brief (PORT) Event Input Control 0 */
#define REG_PORT_PMUX0             (0x41000030U) /**< \brief (PORT) Peripheral Multiplexing 0 */
#define REG_PORT_PINCFG0           (0x41000040U) /**< \brief (PORT) Pin Configuration 0 */
#define REG_PORT_DIR1              (0x41000080U) /**< \brief (PORT) Data Direction 1 */
#define REG_PORT_DIRCLR1           (0x41000084U) /**< \brief (PORT) Data Direction Clear 1 */
#define REG_PORT_DIRSET1           (0x41000088U) /**< \brief (PORT) Data Direction Set 1 */
#define REG_PORT_DIRTGL1           (0x4100008CU) /**< \brief (PORT) Data Direction Toggle 1 */
#define REG_PORT_OUT1              (0x41000090U) /**< \brief (PORT) Data Output Value 1 */
#define REG_PORT_OUTCLR1           (0x41000094U) /**< \brief (PORT) Data Output Value Clear 1 */
#define REG_PORT_OUTSET1           (0x41000098U) /**< \brief (PORT) Data Output Value Set 1 */
#define REG_PORT_OUTTGL1           (0x4100009CU) /**< \brief (PORT) Data Output Value Toggle 1 */
#define REG_PORT_IN1               (0x410000A0U) /**< \brief (PORT) Data Input Value 1 */
#define REG_PORT_CTRL1             (0x410000A4U) /**< \brief (PORT) Control 1 */
#define REG_PORT_WRCONFIG1         (0x410000A8U) /**< \brief (PORT) Write Configuration 1 */
#define REG_PORT_EVCTRL1           (0x410000ACU) /**< \brief (PORT) Event Input Control 1 */
#define REG_PORT_PMUX1             (0x410000B0U) /**< \brief (PORT) Peripheral Multiplexing 1 */
#define REG_PORT_PINCFG1           (0x410000C0U) /**< \brief (PORT) Pin Configuration 1 */
#else
#define REG_PORT_DIR0              (*(RwReg  *)0x41000000U) /**< \brief (PORT) Data Direction 0 */
#define REG_PORT_DIRCLR0           (*(RwReg  *)0x41000004U) /**< \brief (PORT) Data Direction Clear 0 */
#define REG_PORT_DIRSET0           (*(RwReg  *)0x41000008U) /**< \brief (PORT) Data Direction Set 0 */
#define REG_PORT_DIRTGL0           (*(RwReg  *)0x4100000CU) /**< \brief (PORT) Data Direction Toggle 0 */
#define REG_PORT_OUT0              (*(RwReg  *)0x41000010U) /**< \brief (PORT) Data Output Value 0 */
#define REG_PORT_OUTCLR0           (*(RwReg  *)0x41000014U) /**< \brief (PORT) Data Output Value Clear 0 */
#define REG_PORT_OUTSET0           (*(RwReg  *)0x41000018U) /**< \brief (PORT) Data Output Value Set 0 */
#define REG_PORT_OUTTGL0           (*(RwReg  *)0x4100001CU) /**< \brief (PORT) Data Output Value Toggle 0 */
#define REG_PORT_IN0               (*(RoReg  *)0x41000020U) /**< \brief (PORT) Data Input Value 0 */
#define REG_PORT_CTRL0             (*(RwReg  *)0x41000024U) /**< \brief (PORT) Control 0 */
#define REG_PORT_WRCONFIG0         (*(WoReg  *)0x41000028U) /**< \brief (PORT) Write Configuration 0 */
#define REG_PORT_EVCTRL0           (*(RwReg  *)0x4100002CU) /**< \brief (PORT) Event Input Control 0 */
#define REG_PORT_PMUX0             (*(RwReg  *)0x41000030U) /**< \brief (PORT) Peripheral Multiplexing 0 */
#define REG_PORT_PINCFG0           (*(RwReg  *)0x41000040U) /**< \brief (PORT) Pin Configuration 0 */
#define REG_PORT_DIR1              (*(RwReg  *)0x41000080U) /**< \brief (PORT) Data Direction 1 */
#define REG_PORT_DIRCLR1           (*(RwReg  *)0x41000084U) /**< \brief (PORT) Data Direction Clear 1 */
#define REG_PORT_DIRSET1           (*(RwReg  *)0x41000088U) /**< \brief (PORT) Data Direction Set 1 */
#define REG_PORT_DIRTGL1           (*(RwReg  *)0x4100008CU) /**< \brief (PORT) Data Direction Toggle 1 */
#define REG_PORT_OUT1              (*(RwReg  *)0x41000090U) /**< \brief (PORT) Data Output Value 1 */
#define REG_PORT_OUTCLR1           (*(RwReg  *)0x41000094U) /**< \brief (PORT) Data Output Value Clear 1 */
#define REG_PORT_OUTSET1           (*(RwReg  *)0x41000098U) /**< \brief (PORT) Data Output Value Set 1 */
#define REG_PORT_OUTTGL1           (*(RwReg  *)0x4100009CU) /**< \brief (PORT) Data Output Value Toggle 1 */
#define REG_PORT_IN1               (*(RoReg  *)0x410000A0U) /**< \brief (PORT) Data Input Value 1 */
#define REG_PORT_CTRL1             (*(RwReg  *)0x410000A4U) /**< \brief (PORT) Control 1 */
#define REG_PORT_WRCONFIG1         (*(WoReg  *)0x410000A8U) /**< \brief (PORT) Write Configuration 1 */
#define REG_PORT_EVCTRL1           (*(RwReg  *)0x410000ACU) /**< \brief (PORT) Event Input Control 1 */
#define REG_PORT_PMUX1             (*(RwReg  *)0x410000B0U) /**< \brief (PORT) Peripheral Multiplexing 1 */
#define REG_PORT_PINCFG1           (*(RwReg  *)0x410000C0U) /**< \brief (PORT) Pin Configuration 1 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for PORT peripheral ========== */
#define PORT_BITS                   64      
#define PORT_DIR_DEFAULT_VAL        { 0x00000000, 0x00000000 }
#define PORT_DIR_IMPLEMENTED        { 0xDBFFFFFF, 0xC0C3FFFF }
#define PORT_DRVSTR                 1        // DRVSTR supported
#define PORT_DRVSTR_DEFAULT_VAL     { 0x00000000, 0x00000000 }
#define PORT_DRVSTR_IMPLEMENTED     { 0xDBFFFFFF, 0xC0C3FFFF }
#define PORT_EVENT_IMPLEMENTED      { 0xCBFFFFFF, 0xC0C3FFFF }
#define PORT_EV_NUM                 4       
#define PORT_INEN_DEFAULT_VAL       { 0x00000000, 0x00000000 }
#define PORT_INEN_IMPLEMENTED       { 0xDBFFFFFF, 0xC0C3FFFF }
#define PORT_ODRAIN                 0        // ODRAIN supported
#define PORT_ODRAIN_DEFAULT_VAL     { 0x00000000, 0x00000000 }
#define PORT_ODRAIN_IMPLEMENTED     { 0x00000000, 0x00000000 }
#define PORT_OUT_DEFAULT_VAL        { 0x00000000, 0x00000000 }
#define PORT_OUT_IMPLEMENTED        { 0xDBFFFFFF, 0xC0C3FFFF }
#define PORT_PIN_IMPLEMENTED        { 0xDBFFFFFF, 0xC0C3FFFF }
#define PORT_PMUXBIT0_DEFAULT_VAL   { 0x00000000, 0x00000000 }
#define PORT_PMUXBIT0_IMPLEMENTED   { 0xDBFFFFFF, 0xC0C3FFFF }
#define PORT_PMUXBIT1_DEFAULT_VAL   { 0x40000000, 0x00000000 }
#define PORT_PMUXBIT1_IMPLEMENTED   { 0xDBFFFFF3, 0xC0C3FF0F }
#define PORT_PMUXBIT2_DEFAULT_VAL   { 0x40000000, 0x00000000 }
#define PORT_PMUXBIT2_IMPLEMENTED   { 0xDBFFFFF3, 0xC0C3FF0F }
#define PORT_PMUXBIT3_DEFAULT_VAL   { 0x00000000, 0x00000000 }
#define PORT_PMUXBIT3_IMPLEMENTED   { 0xC3CF0FF0, 0x00C3CFC7 }
#define PORT_PMUXEN_DEFAULT_VAL     { 0x40000000, 0x00000000 }
#define PORT_PMUXEN_IMPLEMENTED     { 0xDBFFFFFF, 0xC0C3FFFF }
#define PORT_PULLEN_DEFAULT_VAL     { 0x00000000, 0x00000000 }
#define PORT_PULLEN_IMPLEMENTED     { 0xDBFFFFFF, 0xC0C3FFFF }
#define PORT_SLEWLIM                0        // SLEWLIM supported
#define PORT_SLEWLIM_DEFAULT_VAL    { 0x00000000, 0x00000000 }
#define PORT_SLEWLIM_IMPLEMENTED    { 0x00000000, 0x00000000 }

#endif /* _SAMC21_PORT_INSTANCE_ */
