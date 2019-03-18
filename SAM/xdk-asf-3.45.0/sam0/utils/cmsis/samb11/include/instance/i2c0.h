/**
 * \file
 *
 * \brief Instance description for I2C0
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

#ifndef _SAMB11_I2C0_INSTANCE_
#define _SAMB11_I2C0_INSTANCE_

/* ========== Register definition for I2C0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))

#define REG_I2C0_TRANSMIT_DATA  (0x40003000U) /**< (I2C0) Writes one byte to I2C Transmit Data FIFO.  */
#define REG_I2C0_RECEIVE_DATA   (0x40003004U) /**< (I2C0) Read one byte from I2C Receive Data FIFO.  */
#define REG_I2C0_TRANSMIT_STATUS (0x40003008U) /**< (I2C0) Status of the I2C transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.  */
#define REG_I2C0_RECEIVE_STATUS (0x4000300CU) /**< (I2C0) Status of the I2C receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.  */
#define REG_I2C0_CLOCK_SOURCE_SELECT (0x40003010U) /**< (I2C0) Clock Source Select */
#define REG_I2C0_MODULE_ENABLE  (0x40003014U) /**< (I2C0) I2C Enable */
#define REG_I2C0_CLK_DIVIDER    (0x40003018U) /**< (I2C0) Register sets the divide ratio used to generate the sck clock from the module's input clock.  */
#define REG_I2C0_MASTER_MODE    (0x4000301CU) /**< (I2C0) Selects I2C Master or Slave Mode.  */
#define REG_I2C0_ONBUS          (0x40003020U) /**< (I2C0) Enable/Disable transactions when in Master Mode.  */
#define REG_I2C0_SLAVE_ADDRESS  (0x40003024U) /**< (I2C0) Configures the I2C slave Address.  */
#define REG_I2C0_STATUS         (0x40003028U) /**< (I2C0) Status of I2C Module.  */
#define REG_I2C0_TX_INTERRUPT_MASK (0x4000302CU) /**< (I2C0) Enable or Disable the generation of interrupts by the tx_status register.  */
#define REG_I2C0_RX_INTERRUPT_MASK (0x40003030U) /**< (I2C0) Enable or Disable the generation of interrupts by the rx_status register.  */
#define REG_I2C0_FLUSH          (0x40003034U) /**< (I2C0) Writing to this address  flushes the contents of both the Tx and Rx FIFOs. The value written has no effect. Flushing the Tx FIFO will abort ongoing transactions when the current byte has been transmitted.  */

#else

#define REG_I2C0_TRANSMIT_DATA  (*(__O  uint16_t*)0x40003000U) /**< (I2C0) Writes one byte to I2C Transmit Data FIFO.  */
#define REG_I2C0_RECEIVE_DATA   (*(__I  uint8_t*)0x40003004U) /**< (I2C0) Read one byte from I2C Receive Data FIFO.  */
#define REG_I2C0_TRANSMIT_STATUS (*(__I  uint8_t*)0x40003008U) /**< (I2C0) Status of the I2C transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.  */
#define REG_I2C0_RECEIVE_STATUS (*(__I  uint8_t*)0x4000300CU) /**< (I2C0) Status of the I2C receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.  */
#define REG_I2C0_CLOCK_SOURCE_SELECT (*(__IO uint8_t*)0x40003010U) /**< (I2C0) Clock Source Select */
#define REG_I2C0_MODULE_ENABLE  (*(__IO uint8_t*)0x40003014U) /**< (I2C0) I2C Enable */
#define REG_I2C0_CLK_DIVIDER    (*(__IO uint16_t*)0x40003018U) /**< (I2C0) Register sets the divide ratio used to generate the sck clock from the module's input clock.  */
#define REG_I2C0_MASTER_MODE    (*(__IO uint8_t*)0x4000301CU) /**< (I2C0) Selects I2C Master or Slave Mode.  */
#define REG_I2C0_ONBUS          (*(__IO uint8_t*)0x40003020U) /**< (I2C0) Enable/Disable transactions when in Master Mode.  */
#define REG_I2C0_SLAVE_ADDRESS  (*(__IO uint8_t*)0x40003024U) /**< (I2C0) Configures the I2C slave Address.  */
#define REG_I2C0_STATUS         (*(__I  uint8_t*)0x40003028U) /**< (I2C0) Status of I2C Module.  */
#define REG_I2C0_TX_INTERRUPT_MASK (*(__IO uint8_t*)0x4000302CU) /**< (I2C0) Enable or Disable the generation of interrupts by the tx_status register.  */
#define REG_I2C0_RX_INTERRUPT_MASK (*(__IO uint8_t*)0x40003030U) /**< (I2C0) Enable or Disable the generation of interrupts by the rx_status register.  */
#define REG_I2C0_FLUSH          (*(__O  uint8_t*)0x40003034U) /**< (I2C0) Writing to this address  flushes the contents of both the Tx and Rx FIFOs. The value written has no effect. Flushing the Tx FIFO will abort ongoing transactions when the current byte has been transmitted.  */

#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMB11_I2C0_INSTANCE_ */
