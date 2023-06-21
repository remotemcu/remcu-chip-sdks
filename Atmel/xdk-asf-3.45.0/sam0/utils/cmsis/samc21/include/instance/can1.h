/**
 * \file
 *
 * \brief Instance description for CAN1
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

#ifndef _SAMC21_CAN1_INSTANCE_
#define _SAMC21_CAN1_INSTANCE_

/* ========== Register definition for CAN1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_CAN1_CREL              (0x42002000U) /**< \brief (CAN1) Core Release */
#define REG_CAN1_ENDN              (0x42002004U) /**< \brief (CAN1) Endian */
#define REG_CAN1_MRCFG             (0x42002008U) /**< \brief (CAN1) Message RAM Configuration */
#define REG_CAN1_DBTP              (0x4200200CU) /**< \brief (CAN1) Fast Bit Timing and Prescaler */
#define REG_CAN1_TEST              (0x42002010U) /**< \brief (CAN1) Test */
#define REG_CAN1_RWD               (0x42002014U) /**< \brief (CAN1) RAM Watchdog */
#define REG_CAN1_CCCR              (0x42002018U) /**< \brief (CAN1) CC Control */
#define REG_CAN1_NBTP              (0x4200201CU) /**< \brief (CAN1) Nominal Bit Timing and Prescaler */
#define REG_CAN1_TSCC              (0x42002020U) /**< \brief (CAN1) Timestamp Counter Configuration */
#define REG_CAN1_TSCV              (0x42002024U) /**< \brief (CAN1) Timestamp Counter Value */
#define REG_CAN1_TOCC              (0x42002028U) /**< \brief (CAN1) Timeout Counter Configuration */
#define REG_CAN1_TOCV              (0x4200202CU) /**< \brief (CAN1) Timeout Counter Value */
#define REG_CAN1_ECR               (0x42002040U) /**< \brief (CAN1) Error Counter */
#define REG_CAN1_PSR               (0x42002044U) /**< \brief (CAN1) Protocol Status */
#define REG_CAN1_TDCR              (0x42002048U) /**< \brief (CAN1) Extended ID Filter Configuration */
#define REG_CAN1_IR                (0x42002050U) /**< \brief (CAN1) Interrupt */
#define REG_CAN1_IE                (0x42002054U) /**< \brief (CAN1) Interrupt Enable */
#define REG_CAN1_ILS               (0x42002058U) /**< \brief (CAN1) Interrupt Line Select */
#define REG_CAN1_ILE               (0x4200205CU) /**< \brief (CAN1) Interrupt Line Enable */
#define REG_CAN1_GFC               (0x42002080U) /**< \brief (CAN1) Global Filter Configuration */
#define REG_CAN1_SIDFC             (0x42002084U) /**< \brief (CAN1) Standard ID Filter Configuration */
#define REG_CAN1_XIDFC             (0x42002088U) /**< \brief (CAN1) Extended ID Filter Configuration */
#define REG_CAN1_XIDAM             (0x42002090U) /**< \brief (CAN1) Extended ID AND Mask */
#define REG_CAN1_HPMS              (0x42002094U) /**< \brief (CAN1) High Priority Message Status */
#define REG_CAN1_NDAT1             (0x42002098U) /**< \brief (CAN1) New Data 1 */
#define REG_CAN1_NDAT2             (0x4200209CU) /**< \brief (CAN1) New Data 2 */
#define REG_CAN1_RXF0C             (0x420020A0U) /**< \brief (CAN1) Rx FIFO 0 Configuration */
#define REG_CAN1_RXF0S             (0x420020A4U) /**< \brief (CAN1) Rx FIFO 0 Status */
#define REG_CAN1_RXF0A             (0x420020A8U) /**< \brief (CAN1) Rx FIFO 0 Acknowledge */
#define REG_CAN1_RXBC              (0x420020ACU) /**< \brief (CAN1) Rx Buffer Configuration */
#define REG_CAN1_RXF1C             (0x420020B0U) /**< \brief (CAN1) Rx FIFO 1 Configuration */
#define REG_CAN1_RXF1S             (0x420020B4U) /**< \brief (CAN1) Rx FIFO 1 Status */
#define REG_CAN1_RXF1A             (0x420020B8U) /**< \brief (CAN1) Rx FIFO 1 Acknowledge */
#define REG_CAN1_RXESC             (0x420020BCU) /**< \brief (CAN1) Rx Buffer / FIFO Element Size Configuration */
#define REG_CAN1_TXBC              (0x420020C0U) /**< \brief (CAN1) Tx Buffer Configuration */
#define REG_CAN1_TXFQS             (0x420020C4U) /**< \brief (CAN1) Tx FIFO / Queue Status */
#define REG_CAN1_TXESC             (0x420020C8U) /**< \brief (CAN1) Tx Buffer Element Size Configuration */
#define REG_CAN1_TXBRP             (0x420020CCU) /**< \brief (CAN1) Tx Buffer Request Pending */
#define REG_CAN1_TXBAR             (0x420020D0U) /**< \brief (CAN1) Tx Buffer Add Request */
#define REG_CAN1_TXBCR             (0x420020D4U) /**< \brief (CAN1) Tx Buffer Cancellation Request */
#define REG_CAN1_TXBTO             (0x420020D8U) /**< \brief (CAN1) Tx Buffer Transmission Occurred */
#define REG_CAN1_TXBCF             (0x420020DCU) /**< \brief (CAN1) Tx Buffer Cancellation Finished */
#define REG_CAN1_TXBTIE            (0x420020E0U) /**< \brief (CAN1) Tx Buffer Transmission Interrupt Enable */
#define REG_CAN1_TXBCIE            (0x420020E4U) /**< \brief (CAN1) Tx Buffer Cancellation Finished Interrupt Enable */
#define REG_CAN1_TXEFC             (0x420020F0U) /**< \brief (CAN1) Tx Event FIFO Configuration */
#define REG_CAN1_TXEFS             (0x420020F4U) /**< \brief (CAN1) Tx Event FIFO Status */
#define REG_CAN1_TXEFA             (0x420020F8U) /**< \brief (CAN1) Tx Event FIFO Acknowledge */
#else
#define REG_CAN1_CREL              (*(RoReg  *)0x42002000U) /**< \brief (CAN1) Core Release */
#define REG_CAN1_ENDN              (*(RoReg  *)0x42002004U) /**< \brief (CAN1) Endian */
#define REG_CAN1_MRCFG             (*(RwReg  *)0x42002008U) /**< \brief (CAN1) Message RAM Configuration */
#define REG_CAN1_DBTP              (*(RwReg  *)0x4200200CU) /**< \brief (CAN1) Fast Bit Timing and Prescaler */
#define REG_CAN1_TEST              (*(RwReg  *)0x42002010U) /**< \brief (CAN1) Test */
#define REG_CAN1_RWD               (*(RwReg  *)0x42002014U) /**< \brief (CAN1) RAM Watchdog */
#define REG_CAN1_CCCR              (*(RwReg  *)0x42002018U) /**< \brief (CAN1) CC Control */
#define REG_CAN1_NBTP              (*(RwReg  *)0x4200201CU) /**< \brief (CAN1) Nominal Bit Timing and Prescaler */
#define REG_CAN1_TSCC              (*(RwReg  *)0x42002020U) /**< \brief (CAN1) Timestamp Counter Configuration */
#define REG_CAN1_TSCV              (*(RoReg  *)0x42002024U) /**< \brief (CAN1) Timestamp Counter Value */
#define REG_CAN1_TOCC              (*(RwReg  *)0x42002028U) /**< \brief (CAN1) Timeout Counter Configuration */
#define REG_CAN1_TOCV              (*(RwReg  *)0x4200202CU) /**< \brief (CAN1) Timeout Counter Value */
#define REG_CAN1_ECR               (*(RoReg  *)0x42002040U) /**< \brief (CAN1) Error Counter */
#define REG_CAN1_PSR               (*(RoReg  *)0x42002044U) /**< \brief (CAN1) Protocol Status */
#define REG_CAN1_TDCR              (*(RwReg  *)0x42002048U) /**< \brief (CAN1) Extended ID Filter Configuration */
#define REG_CAN1_IR                (*(RwReg  *)0x42002050U) /**< \brief (CAN1) Interrupt */
#define REG_CAN1_IE                (*(RwReg  *)0x42002054U) /**< \brief (CAN1) Interrupt Enable */
#define REG_CAN1_ILS               (*(RwReg  *)0x42002058U) /**< \brief (CAN1) Interrupt Line Select */
#define REG_CAN1_ILE               (*(RwReg  *)0x4200205CU) /**< \brief (CAN1) Interrupt Line Enable */
#define REG_CAN1_GFC               (*(RwReg  *)0x42002080U) /**< \brief (CAN1) Global Filter Configuration */
#define REG_CAN1_SIDFC             (*(RwReg  *)0x42002084U) /**< \brief (CAN1) Standard ID Filter Configuration */
#define REG_CAN1_XIDFC             (*(RwReg  *)0x42002088U) /**< \brief (CAN1) Extended ID Filter Configuration */
#define REG_CAN1_XIDAM             (*(RwReg  *)0x42002090U) /**< \brief (CAN1) Extended ID AND Mask */
#define REG_CAN1_HPMS              (*(RoReg  *)0x42002094U) /**< \brief (CAN1) High Priority Message Status */
#define REG_CAN1_NDAT1             (*(RwReg  *)0x42002098U) /**< \brief (CAN1) New Data 1 */
#define REG_CAN1_NDAT2             (*(RwReg  *)0x4200209CU) /**< \brief (CAN1) New Data 2 */
#define REG_CAN1_RXF0C             (*(RwReg  *)0x420020A0U) /**< \brief (CAN1) Rx FIFO 0 Configuration */
#define REG_CAN1_RXF0S             (*(RoReg  *)0x420020A4U) /**< \brief (CAN1) Rx FIFO 0 Status */
#define REG_CAN1_RXF0A             (*(RwReg  *)0x420020A8U) /**< \brief (CAN1) Rx FIFO 0 Acknowledge */
#define REG_CAN1_RXBC              (*(RwReg  *)0x420020ACU) /**< \brief (CAN1) Rx Buffer Configuration */
#define REG_CAN1_RXF1C             (*(RwReg  *)0x420020B0U) /**< \brief (CAN1) Rx FIFO 1 Configuration */
#define REG_CAN1_RXF1S             (*(RoReg  *)0x420020B4U) /**< \brief (CAN1) Rx FIFO 1 Status */
#define REG_CAN1_RXF1A             (*(RwReg  *)0x420020B8U) /**< \brief (CAN1) Rx FIFO 1 Acknowledge */
#define REG_CAN1_RXESC             (*(RwReg  *)0x420020BCU) /**< \brief (CAN1) Rx Buffer / FIFO Element Size Configuration */
#define REG_CAN1_TXBC              (*(RwReg  *)0x420020C0U) /**< \brief (CAN1) Tx Buffer Configuration */
#define REG_CAN1_TXFQS             (*(RoReg  *)0x420020C4U) /**< \brief (CAN1) Tx FIFO / Queue Status */
#define REG_CAN1_TXESC             (*(RwReg  *)0x420020C8U) /**< \brief (CAN1) Tx Buffer Element Size Configuration */
#define REG_CAN1_TXBRP             (*(RoReg  *)0x420020CCU) /**< \brief (CAN1) Tx Buffer Request Pending */
#define REG_CAN1_TXBAR             (*(RwReg  *)0x420020D0U) /**< \brief (CAN1) Tx Buffer Add Request */
#define REG_CAN1_TXBCR             (*(RwReg  *)0x420020D4U) /**< \brief (CAN1) Tx Buffer Cancellation Request */
#define REG_CAN1_TXBTO             (*(RoReg  *)0x420020D8U) /**< \brief (CAN1) Tx Buffer Transmission Occurred */
#define REG_CAN1_TXBCF             (*(RoReg  *)0x420020DCU) /**< \brief (CAN1) Tx Buffer Cancellation Finished */
#define REG_CAN1_TXBTIE            (*(RwReg  *)0x420020E0U) /**< \brief (CAN1) Tx Buffer Transmission Interrupt Enable */
#define REG_CAN1_TXBCIE            (*(RwReg  *)0x420020E4U) /**< \brief (CAN1) Tx Buffer Cancellation Finished Interrupt Enable */
#define REG_CAN1_TXEFC             (*(RwReg  *)0x420020F0U) /**< \brief (CAN1) Tx Event FIFO Configuration */
#define REG_CAN1_TXEFS             (*(RoReg  *)0x420020F4U) /**< \brief (CAN1) Tx Event FIFO Status */
#define REG_CAN1_TXEFA             (*(RwReg  *)0x420020F8U) /**< \brief (CAN1) Tx Event FIFO Acknowledge */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for CAN1 peripheral ========== */
#define CAN1_CLK_AHB_ID             9        // Index of AHB clock
#define CAN1_DMAC_ID_DEBUG          15       // DMA CAN Debug Req
#define CAN1_GCLK_ID                27       // Index of Generic Clock
#define CAN1_MSG_RAM_ADDR           0x200000000
#define CAN1_QOS_RESET_VAL          2        // QOS reset value

#endif /* _SAMC21_CAN1_INSTANCE_ */
