/**
 * \file
 *
 * \brief Instance description for CAN0
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

#ifndef _SAMC21_CAN0_INSTANCE_
#define _SAMC21_CAN0_INSTANCE_

/* ========== Register definition for CAN0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_CAN0_CREL              (0x42001C00U) /**< \brief (CAN0) Core Release */
#define REG_CAN0_ENDN              (0x42001C04U) /**< \brief (CAN0) Endian */
#define REG_CAN0_MRCFG             (0x42001C08U) /**< \brief (CAN0) Message RAM Configuration */
#define REG_CAN0_DBTP              (0x42001C0CU) /**< \brief (CAN0) Fast Bit Timing and Prescaler */
#define REG_CAN0_TEST              (0x42001C10U) /**< \brief (CAN0) Test */
#define REG_CAN0_RWD               (0x42001C14U) /**< \brief (CAN0) RAM Watchdog */
#define REG_CAN0_CCCR              (0x42001C18U) /**< \brief (CAN0) CC Control */
#define REG_CAN0_NBTP              (0x42001C1CU) /**< \brief (CAN0) Nominal Bit Timing and Prescaler */
#define REG_CAN0_TSCC              (0x42001C20U) /**< \brief (CAN0) Timestamp Counter Configuration */
#define REG_CAN0_TSCV              (0x42001C24U) /**< \brief (CAN0) Timestamp Counter Value */
#define REG_CAN0_TOCC              (0x42001C28U) /**< \brief (CAN0) Timeout Counter Configuration */
#define REG_CAN0_TOCV              (0x42001C2CU) /**< \brief (CAN0) Timeout Counter Value */
#define REG_CAN0_ECR               (0x42001C40U) /**< \brief (CAN0) Error Counter */
#define REG_CAN0_PSR               (0x42001C44U) /**< \brief (CAN0) Protocol Status */
#define REG_CAN0_TDCR              (0x42001C48U) /**< \brief (CAN0) Extended ID Filter Configuration */
#define REG_CAN0_IR                (0x42001C50U) /**< \brief (CAN0) Interrupt */
#define REG_CAN0_IE                (0x42001C54U) /**< \brief (CAN0) Interrupt Enable */
#define REG_CAN0_ILS               (0x42001C58U) /**< \brief (CAN0) Interrupt Line Select */
#define REG_CAN0_ILE               (0x42001C5CU) /**< \brief (CAN0) Interrupt Line Enable */
#define REG_CAN0_GFC               (0x42001C80U) /**< \brief (CAN0) Global Filter Configuration */
#define REG_CAN0_SIDFC             (0x42001C84U) /**< \brief (CAN0) Standard ID Filter Configuration */
#define REG_CAN0_XIDFC             (0x42001C88U) /**< \brief (CAN0) Extended ID Filter Configuration */
#define REG_CAN0_XIDAM             (0x42001C90U) /**< \brief (CAN0) Extended ID AND Mask */
#define REG_CAN0_HPMS              (0x42001C94U) /**< \brief (CAN0) High Priority Message Status */
#define REG_CAN0_NDAT1             (0x42001C98U) /**< \brief (CAN0) New Data 1 */
#define REG_CAN0_NDAT2             (0x42001C9CU) /**< \brief (CAN0) New Data 2 */
#define REG_CAN0_RXF0C             (0x42001CA0U) /**< \brief (CAN0) Rx FIFO 0 Configuration */
#define REG_CAN0_RXF0S             (0x42001CA4U) /**< \brief (CAN0) Rx FIFO 0 Status */
#define REG_CAN0_RXF0A             (0x42001CA8U) /**< \brief (CAN0) Rx FIFO 0 Acknowledge */
#define REG_CAN0_RXBC              (0x42001CACU) /**< \brief (CAN0) Rx Buffer Configuration */
#define REG_CAN0_RXF1C             (0x42001CB0U) /**< \brief (CAN0) Rx FIFO 1 Configuration */
#define REG_CAN0_RXF1S             (0x42001CB4U) /**< \brief (CAN0) Rx FIFO 1 Status */
#define REG_CAN0_RXF1A             (0x42001CB8U) /**< \brief (CAN0) Rx FIFO 1 Acknowledge */
#define REG_CAN0_RXESC             (0x42001CBCU) /**< \brief (CAN0) Rx Buffer / FIFO Element Size Configuration */
#define REG_CAN0_TXBC              (0x42001CC0U) /**< \brief (CAN0) Tx Buffer Configuration */
#define REG_CAN0_TXFQS             (0x42001CC4U) /**< \brief (CAN0) Tx FIFO / Queue Status */
#define REG_CAN0_TXESC             (0x42001CC8U) /**< \brief (CAN0) Tx Buffer Element Size Configuration */
#define REG_CAN0_TXBRP             (0x42001CCCU) /**< \brief (CAN0) Tx Buffer Request Pending */
#define REG_CAN0_TXBAR             (0x42001CD0U) /**< \brief (CAN0) Tx Buffer Add Request */
#define REG_CAN0_TXBCR             (0x42001CD4U) /**< \brief (CAN0) Tx Buffer Cancellation Request */
#define REG_CAN0_TXBTO             (0x42001CD8U) /**< \brief (CAN0) Tx Buffer Transmission Occurred */
#define REG_CAN0_TXBCF             (0x42001CDCU) /**< \brief (CAN0) Tx Buffer Cancellation Finished */
#define REG_CAN0_TXBTIE            (0x42001CE0U) /**< \brief (CAN0) Tx Buffer Transmission Interrupt Enable */
#define REG_CAN0_TXBCIE            (0x42001CE4U) /**< \brief (CAN0) Tx Buffer Cancellation Finished Interrupt Enable */
#define REG_CAN0_TXEFC             (0x42001CF0U) /**< \brief (CAN0) Tx Event FIFO Configuration */
#define REG_CAN0_TXEFS             (0x42001CF4U) /**< \brief (CAN0) Tx Event FIFO Status */
#define REG_CAN0_TXEFA             (0x42001CF8U) /**< \brief (CAN0) Tx Event FIFO Acknowledge */
#else
#define REG_CAN0_CREL              (*(RoReg  *)0x42001C00U) /**< \brief (CAN0) Core Release */
#define REG_CAN0_ENDN              (*(RoReg  *)0x42001C04U) /**< \brief (CAN0) Endian */
#define REG_CAN0_MRCFG             (*(RwReg  *)0x42001C08U) /**< \brief (CAN0) Message RAM Configuration */
#define REG_CAN0_DBTP              (*(RwReg  *)0x42001C0CU) /**< \brief (CAN0) Fast Bit Timing and Prescaler */
#define REG_CAN0_TEST              (*(RwReg  *)0x42001C10U) /**< \brief (CAN0) Test */
#define REG_CAN0_RWD               (*(RwReg  *)0x42001C14U) /**< \brief (CAN0) RAM Watchdog */
#define REG_CAN0_CCCR              (*(RwReg  *)0x42001C18U) /**< \brief (CAN0) CC Control */
#define REG_CAN0_NBTP              (*(RwReg  *)0x42001C1CU) /**< \brief (CAN0) Nominal Bit Timing and Prescaler */
#define REG_CAN0_TSCC              (*(RwReg  *)0x42001C20U) /**< \brief (CAN0) Timestamp Counter Configuration */
#define REG_CAN0_TSCV              (*(RoReg  *)0x42001C24U) /**< \brief (CAN0) Timestamp Counter Value */
#define REG_CAN0_TOCC              (*(RwReg  *)0x42001C28U) /**< \brief (CAN0) Timeout Counter Configuration */
#define REG_CAN0_TOCV              (*(RwReg  *)0x42001C2CU) /**< \brief (CAN0) Timeout Counter Value */
#define REG_CAN0_ECR               (*(RoReg  *)0x42001C40U) /**< \brief (CAN0) Error Counter */
#define REG_CAN0_PSR               (*(RoReg  *)0x42001C44U) /**< \brief (CAN0) Protocol Status */
#define REG_CAN0_TDCR              (*(RwReg  *)0x42001C48U) /**< \brief (CAN0) Extended ID Filter Configuration */
#define REG_CAN0_IR                (*(RwReg  *)0x42001C50U) /**< \brief (CAN0) Interrupt */
#define REG_CAN0_IE                (*(RwReg  *)0x42001C54U) /**< \brief (CAN0) Interrupt Enable */
#define REG_CAN0_ILS               (*(RwReg  *)0x42001C58U) /**< \brief (CAN0) Interrupt Line Select */
#define REG_CAN0_ILE               (*(RwReg  *)0x42001C5CU) /**< \brief (CAN0) Interrupt Line Enable */
#define REG_CAN0_GFC               (*(RwReg  *)0x42001C80U) /**< \brief (CAN0) Global Filter Configuration */
#define REG_CAN0_SIDFC             (*(RwReg  *)0x42001C84U) /**< \brief (CAN0) Standard ID Filter Configuration */
#define REG_CAN0_XIDFC             (*(RwReg  *)0x42001C88U) /**< \brief (CAN0) Extended ID Filter Configuration */
#define REG_CAN0_XIDAM             (*(RwReg  *)0x42001C90U) /**< \brief (CAN0) Extended ID AND Mask */
#define REG_CAN0_HPMS              (*(RoReg  *)0x42001C94U) /**< \brief (CAN0) High Priority Message Status */
#define REG_CAN0_NDAT1             (*(RwReg  *)0x42001C98U) /**< \brief (CAN0) New Data 1 */
#define REG_CAN0_NDAT2             (*(RwReg  *)0x42001C9CU) /**< \brief (CAN0) New Data 2 */
#define REG_CAN0_RXF0C             (*(RwReg  *)0x42001CA0U) /**< \brief (CAN0) Rx FIFO 0 Configuration */
#define REG_CAN0_RXF0S             (*(RoReg  *)0x42001CA4U) /**< \brief (CAN0) Rx FIFO 0 Status */
#define REG_CAN0_RXF0A             (*(RwReg  *)0x42001CA8U) /**< \brief (CAN0) Rx FIFO 0 Acknowledge */
#define REG_CAN0_RXBC              (*(RwReg  *)0x42001CACU) /**< \brief (CAN0) Rx Buffer Configuration */
#define REG_CAN0_RXF1C             (*(RwReg  *)0x42001CB0U) /**< \brief (CAN0) Rx FIFO 1 Configuration */
#define REG_CAN0_RXF1S             (*(RoReg  *)0x42001CB4U) /**< \brief (CAN0) Rx FIFO 1 Status */
#define REG_CAN0_RXF1A             (*(RwReg  *)0x42001CB8U) /**< \brief (CAN0) Rx FIFO 1 Acknowledge */
#define REG_CAN0_RXESC             (*(RwReg  *)0x42001CBCU) /**< \brief (CAN0) Rx Buffer / FIFO Element Size Configuration */
#define REG_CAN0_TXBC              (*(RwReg  *)0x42001CC0U) /**< \brief (CAN0) Tx Buffer Configuration */
#define REG_CAN0_TXFQS             (*(RoReg  *)0x42001CC4U) /**< \brief (CAN0) Tx FIFO / Queue Status */
#define REG_CAN0_TXESC             (*(RwReg  *)0x42001CC8U) /**< \brief (CAN0) Tx Buffer Element Size Configuration */
#define REG_CAN0_TXBRP             (*(RoReg  *)0x42001CCCU) /**< \brief (CAN0) Tx Buffer Request Pending */
#define REG_CAN0_TXBAR             (*(RwReg  *)0x42001CD0U) /**< \brief (CAN0) Tx Buffer Add Request */
#define REG_CAN0_TXBCR             (*(RwReg  *)0x42001CD4U) /**< \brief (CAN0) Tx Buffer Cancellation Request */
#define REG_CAN0_TXBTO             (*(RoReg  *)0x42001CD8U) /**< \brief (CAN0) Tx Buffer Transmission Occurred */
#define REG_CAN0_TXBCF             (*(RoReg  *)0x42001CDCU) /**< \brief (CAN0) Tx Buffer Cancellation Finished */
#define REG_CAN0_TXBTIE            (*(RwReg  *)0x42001CE0U) /**< \brief (CAN0) Tx Buffer Transmission Interrupt Enable */
#define REG_CAN0_TXBCIE            (*(RwReg  *)0x42001CE4U) /**< \brief (CAN0) Tx Buffer Cancellation Finished Interrupt Enable */
#define REG_CAN0_TXEFC             (*(RwReg  *)0x42001CF0U) /**< \brief (CAN0) Tx Event FIFO Configuration */
#define REG_CAN0_TXEFS             (*(RoReg  *)0x42001CF4U) /**< \brief (CAN0) Tx Event FIFO Status */
#define REG_CAN0_TXEFA             (*(RwReg  *)0x42001CF8U) /**< \brief (CAN0) Tx Event FIFO Acknowledge */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* ========== Instance parameters for CAN0 peripheral ========== */
#define CAN0_CLK_AHB_ID             8        // Index of AHB clock
#define CAN0_DMAC_ID_DEBUG          14       // DMA CAN Debug Req
#define CAN0_GCLK_ID                26       // Index of Generic Clock
#define CAN0_MSG_RAM_ADDR           0x200000000
#define CAN0_QOS_RESET_VAL          2        // QOS reset value

#endif /* _SAMC21_CAN0_INSTANCE_ */
