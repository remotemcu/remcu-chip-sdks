/**
 * \file
 *
 * \brief Instance description for TAL
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

#ifndef _SAMC21_TAL_INSTANCE_
#define _SAMC21_TAL_INSTANCE_

/* ========== Register definition for TAL peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TAL_CTRLA              (0x42006000U) /**< \brief (TAL) Control A */
#define REG_TAL_RSTCTRL            (0x42006004U) /**< \brief (TAL) Reset Control */
#define REG_TAL_EXTCTRL            (0x42006005U) /**< \brief (TAL) External Break Control */
#define REG_TAL_EVCTRL             (0x42006006U) /**< \brief (TAL) Event Control */
#define REG_TAL_INTENCLR           (0x42006008U) /**< \brief (TAL) Interrupt Enable Clear */
#define REG_TAL_INTENSET           (0x42006009U) /**< \brief (TAL) Interrupt Enable Set */
#define REG_TAL_INTFLAG            (0x4200600AU) /**< \brief (TAL) Interrupt Flag Status and Clear */
#define REG_TAL_GLOBMASK           (0x4200600BU) /**< \brief (TAL) Global Break Requests Mask */
#define REG_TAL_HALT               (0x4200600CU) /**< \brief (TAL) Debug Halt Request */
#define REG_TAL_RESTART            (0x4200600DU) /**< \brief (TAL) Debug Restart Request */
#define REG_TAL_BRKSTATUS          (0x4200600EU) /**< \brief (TAL) Break Request Status */
#define REG_TAL_CTICTRLA0          (0x42006010U) /**< \brief (TAL) Cross-Trigger Interface 0 Control A */
#define REG_TAL_CTIMASK0           (0x42006011U) /**< \brief (TAL) Cross-Trigger Interface 0 Mask */
#define REG_TAL_CTICTRLA1          (0x42006012U) /**< \brief (TAL) Cross-Trigger Interface 1 Control A */
#define REG_TAL_CTIMASK1           (0x42006013U) /**< \brief (TAL) Cross-Trigger Interface 1 Mask */
#define REG_TAL_CTICTRLA2          (0x42006014U) /**< \brief (TAL) Cross-Trigger Interface 2 Control A */
#define REG_TAL_CTIMASK2           (0x42006015U) /**< \brief (TAL) Cross-Trigger Interface 2 Mask */
#define REG_TAL_INTSTATUS0         (0x42006020U) /**< \brief (TAL) Interrupt 0 Status */
#define REG_TAL_INTSTATUS1         (0x42006021U) /**< \brief (TAL) Interrupt 1 Status */
#define REG_TAL_INTSTATUS2         (0x42006022U) /**< \brief (TAL) Interrupt 2 Status */
#define REG_TAL_INTSTATUS3         (0x42006023U) /**< \brief (TAL) Interrupt 3 Status */
#define REG_TAL_INTSTATUS4         (0x42006024U) /**< \brief (TAL) Interrupt 4 Status */
#define REG_TAL_INTSTATUS5         (0x42006025U) /**< \brief (TAL) Interrupt 5 Status */
#define REG_TAL_INTSTATUS6         (0x42006026U) /**< \brief (TAL) Interrupt 6 Status */
#define REG_TAL_INTSTATUS7         (0x42006027U) /**< \brief (TAL) Interrupt 7 Status */
#define REG_TAL_INTSTATUS8         (0x42006028U) /**< \brief (TAL) Interrupt 8 Status */
#define REG_TAL_INTSTATUS9         (0x42006029U) /**< \brief (TAL) Interrupt 9 Status */
#define REG_TAL_INTSTATUS10        (0x4200602AU) /**< \brief (TAL) Interrupt 10 Status */
#define REG_TAL_INTSTATUS11        (0x4200602BU) /**< \brief (TAL) Interrupt 11 Status */
#define REG_TAL_INTSTATUS12        (0x4200602CU) /**< \brief (TAL) Interrupt 12 Status */
#define REG_TAL_INTSTATUS13        (0x4200602DU) /**< \brief (TAL) Interrupt 13 Status */
#define REG_TAL_INTSTATUS14        (0x4200602EU) /**< \brief (TAL) Interrupt 14 Status */
#define REG_TAL_INTSTATUS15        (0x4200602FU) /**< \brief (TAL) Interrupt 15 Status */
#define REG_TAL_INTSTATUS16        (0x42006030U) /**< \brief (TAL) Interrupt 16 Status */
#define REG_TAL_INTSTATUS17        (0x42006031U) /**< \brief (TAL) Interrupt 17 Status */
#define REG_TAL_INTSTATUS18        (0x42006032U) /**< \brief (TAL) Interrupt 18 Status */
#define REG_TAL_INTSTATUS19        (0x42006033U) /**< \brief (TAL) Interrupt 19 Status */
#define REG_TAL_INTSTATUS20        (0x42006034U) /**< \brief (TAL) Interrupt 20 Status */
#define REG_TAL_INTSTATUS21        (0x42006035U) /**< \brief (TAL) Interrupt 21 Status */
#define REG_TAL_INTSTATUS22        (0x42006036U) /**< \brief (TAL) Interrupt 22 Status */
#define REG_TAL_INTSTATUS23        (0x42006037U) /**< \brief (TAL) Interrupt 23 Status */
#define REG_TAL_INTSTATUS24        (0x42006038U) /**< \brief (TAL) Interrupt 24 Status */
#define REG_TAL_INTSTATUS25        (0x42006039U) /**< \brief (TAL) Interrupt 25 Status */
#define REG_TAL_INTSTATUS26        (0x4200603AU) /**< \brief (TAL) Interrupt 26 Status */
#define REG_TAL_INTSTATUS27        (0x4200603BU) /**< \brief (TAL) Interrupt 27 Status */
#define REG_TAL_INTSTATUS28        (0x4200603CU) /**< \brief (TAL) Interrupt 28 Status */
#define REG_TAL_INTSTATUS29        (0x4200603DU) /**< \brief (TAL) Interrupt 29 Status */
#define REG_TAL_INTSTATUS30        (0x4200603EU) /**< \brief (TAL) Interrupt 30 Status */
#define REG_TAL_IRQTRIG            (0x42006060U) /**< \brief (TAL) Interrupt Trigger */
#define REG_TAL_CPUIRQS0           (0x42006064U) /**< \brief (TAL) Interrupt Status for CPU 0 */
#else
#define REG_TAL_CTRLA              (*(RwReg8 *)0x42006000U) /**< \brief (TAL) Control A */
#define REG_TAL_RSTCTRL            (*(RwReg8 *)0x42006004U) /**< \brief (TAL) Reset Control */
#define REG_TAL_EXTCTRL            (*(RwReg8 *)0x42006005U) /**< \brief (TAL) External Break Control */
#define REG_TAL_EVCTRL             (*(RwReg8 *)0x42006006U) /**< \brief (TAL) Event Control */
#define REG_TAL_INTENCLR           (*(RwReg8 *)0x42006008U) /**< \brief (TAL) Interrupt Enable Clear */
#define REG_TAL_INTENSET           (*(RwReg8 *)0x42006009U) /**< \brief (TAL) Interrupt Enable Set */
#define REG_TAL_INTFLAG            (*(RwReg8 *)0x4200600AU) /**< \brief (TAL) Interrupt Flag Status and Clear */
#define REG_TAL_GLOBMASK           (*(RwReg8 *)0x4200600BU) /**< \brief (TAL) Global Break Requests Mask */
#define REG_TAL_HALT               (*(WoReg8 *)0x4200600CU) /**< \brief (TAL) Debug Halt Request */
#define REG_TAL_RESTART            (*(WoReg8 *)0x4200600DU) /**< \brief (TAL) Debug Restart Request */
#define REG_TAL_BRKSTATUS          (*(RoReg16*)0x4200600EU) /**< \brief (TAL) Break Request Status */
#define REG_TAL_CTICTRLA0          (*(RwReg8 *)0x42006010U) /**< \brief (TAL) Cross-Trigger Interface 0 Control A */
#define REG_TAL_CTIMASK0           (*(RwReg8 *)0x42006011U) /**< \brief (TAL) Cross-Trigger Interface 0 Mask */
#define REG_TAL_CTICTRLA1          (*(RwReg8 *)0x42006012U) /**< \brief (TAL) Cross-Trigger Interface 1 Control A */
#define REG_TAL_CTIMASK1           (*(RwReg8 *)0x42006013U) /**< \brief (TAL) Cross-Trigger Interface 1 Mask */
#define REG_TAL_CTICTRLA2          (*(RwReg8 *)0x42006014U) /**< \brief (TAL) Cross-Trigger Interface 2 Control A */
#define REG_TAL_CTIMASK2           (*(RwReg8 *)0x42006015U) /**< \brief (TAL) Cross-Trigger Interface 2 Mask */
#define REG_TAL_INTSTATUS0         (*(RoReg8 *)0x42006020U) /**< \brief (TAL) Interrupt 0 Status */
#define REG_TAL_INTSTATUS1         (*(RoReg8 *)0x42006021U) /**< \brief (TAL) Interrupt 1 Status */
#define REG_TAL_INTSTATUS2         (*(RoReg8 *)0x42006022U) /**< \brief (TAL) Interrupt 2 Status */
#define REG_TAL_INTSTATUS3         (*(RoReg8 *)0x42006023U) /**< \brief (TAL) Interrupt 3 Status */
#define REG_TAL_INTSTATUS4         (*(RoReg8 *)0x42006024U) /**< \brief (TAL) Interrupt 4 Status */
#define REG_TAL_INTSTATUS5         (*(RoReg8 *)0x42006025U) /**< \brief (TAL) Interrupt 5 Status */
#define REG_TAL_INTSTATUS6         (*(RoReg8 *)0x42006026U) /**< \brief (TAL) Interrupt 6 Status */
#define REG_TAL_INTSTATUS7         (*(RoReg8 *)0x42006027U) /**< \brief (TAL) Interrupt 7 Status */
#define REG_TAL_INTSTATUS8         (*(RoReg8 *)0x42006028U) /**< \brief (TAL) Interrupt 8 Status */
#define REG_TAL_INTSTATUS9         (*(RoReg8 *)0x42006029U) /**< \brief (TAL) Interrupt 9 Status */
#define REG_TAL_INTSTATUS10        (*(RoReg8 *)0x4200602AU) /**< \brief (TAL) Interrupt 10 Status */
#define REG_TAL_INTSTATUS11        (*(RoReg8 *)0x4200602BU) /**< \brief (TAL) Interrupt 11 Status */
#define REG_TAL_INTSTATUS12        (*(RoReg8 *)0x4200602CU) /**< \brief (TAL) Interrupt 12 Status */
#define REG_TAL_INTSTATUS13        (*(RoReg8 *)0x4200602DU) /**< \brief (TAL) Interrupt 13 Status */
#define REG_TAL_INTSTATUS14        (*(RoReg8 *)0x4200602EU) /**< \brief (TAL) Interrupt 14 Status */
#define REG_TAL_INTSTATUS15        (*(RoReg8 *)0x4200602FU) /**< \brief (TAL) Interrupt 15 Status */
#define REG_TAL_INTSTATUS16        (*(RoReg8 *)0x42006030U) /**< \brief (TAL) Interrupt 16 Status */
#define REG_TAL_INTSTATUS17        (*(RoReg8 *)0x42006031U) /**< \brief (TAL) Interrupt 17 Status */
#define REG_TAL_INTSTATUS18        (*(RoReg8 *)0x42006032U) /**< \brief (TAL) Interrupt 18 Status */
#define REG_TAL_INTSTATUS19        (*(RoReg8 *)0x42006033U) /**< \brief (TAL) Interrupt 19 Status */
#define REG_TAL_INTSTATUS20        (*(RoReg8 *)0x42006034U) /**< \brief (TAL) Interrupt 20 Status */
#define REG_TAL_INTSTATUS21        (*(RoReg8 *)0x42006035U) /**< \brief (TAL) Interrupt 21 Status */
#define REG_TAL_INTSTATUS22        (*(RoReg8 *)0x42006036U) /**< \brief (TAL) Interrupt 22 Status */
#define REG_TAL_INTSTATUS23        (*(RoReg8 *)0x42006037U) /**< \brief (TAL) Interrupt 23 Status */
#define REG_TAL_INTSTATUS24        (*(RoReg8 *)0x42006038U) /**< \brief (TAL) Interrupt 24 Status */
#define REG_TAL_INTSTATUS25        (*(RoReg8 *)0x42006039U) /**< \brief (TAL) Interrupt 25 Status */
#define REG_TAL_INTSTATUS26        (*(RoReg8 *)0x4200603AU) /**< \brief (TAL) Interrupt 26 Status */
#define REG_TAL_INTSTATUS27        (*(RoReg8 *)0x4200603BU) /**< \brief (TAL) Interrupt 27 Status */
#define REG_TAL_INTSTATUS28        (*(RoReg8 *)0x4200603CU) /**< \brief (TAL) Interrupt 28 Status */
#define REG_TAL_INTSTATUS29        (*(RoReg8 *)0x4200603DU) /**< \brief (TAL) Interrupt 29 Status */
#define REG_TAL_INTSTATUS30        (*(RoReg8 *)0x4200603EU) /**< \brief (TAL) Interrupt 30 Status */
#define REG_TAL_IRQTRIG            (*(RwReg16*)0x42006060U) /**< \brief (TAL) Interrupt Trigger */
#define REG_TAL_CPUIRQS0           (*(RoReg  *)0x42006064U) /**< \brief (TAL) Interrupt Status for CPU 0 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for TAL peripheral ========== */
#define TAL_CPU_NUM                 1        // Number of CPUs
#define TAL_CTI_NUM                 3        // Number of Cross-Trigger Interfaces
#define TAL_DMA_CH_NUM              12       // Number of DMAC Channels
#define TAL_EV_CH_NUM               12       // Number of EVSYS Channels
#define TAL_EXTINT_NUM              16       // Number of EIC External Interrrupts
#define TAL_INT_NUM                 31       // Number of Interrupt Requests

#endif /* _SAMC21_TAL_INSTANCE_ */
