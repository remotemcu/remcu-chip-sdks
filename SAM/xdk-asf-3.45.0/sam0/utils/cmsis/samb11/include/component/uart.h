/**
 * \file
 *
 * \brief Component description for UART
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

#ifndef _SAMB11_UART_COMPONENT_
#define _SAMB11_UART_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR UART */
/* ========================================================================== */
/** \addtogroup SAMB11_UART UART Controller 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define UART_U1234
#define REV_UART                         0x100

/* -------- UART_TRANSMIT_DATA : (UART Offset: 0x00) (/W 8) Writes one byte to UART Transmit Data FIFO.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TX_BYTE:8;                 /**< bit:   0..7  Writes data in transmit FIFO. If byte length is set to 7, the MSB should be set to 0.  */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} UART_TRANSMIT_DATA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define UART_TRANSMIT_DATA_OFFSET           0x00                                          /**<  (UART_TRANSMIT_DATA) Writes one byte to UART Transmit Data FIFO.   Offset */
#define UART_TRANSMIT_DATA_RESETVALUE       0x00u                                         /**<  (UART_TRANSMIT_DATA) Writes one byte to UART Transmit Data FIFO.   Reset Value */

#define UART_TRANSMIT_DATA_TX_BYTE_Pos      0                                              /**< (UART_TRANSMIT_DATA) Writes data in transmit FIFO. If byte length is set to 7, the MSB should be set to 0.  Position */
#define UART_TRANSMIT_DATA_TX_BYTE_Msk      (0xFFu << UART_TRANSMIT_DATA_TX_BYTE_Pos)      /**< (UART_TRANSMIT_DATA) Writes data in transmit FIFO. If byte length is set to 7, the MSB should be set to 0.  Mask */
#define UART_TRANSMIT_DATA_TX_BYTE(value)   (UART_TRANSMIT_DATA_TX_BYTE_Msk & ((value) << UART_TRANSMIT_DATA_TX_BYTE_Pos))
#define UART_TRANSMIT_DATA_MASK             0xFFu                                          /**< \deprecated (UART_TRANSMIT_DATA) Register MASK  (Use UART_TRANSMIT_DATA_Msk instead)  */
#define UART_TRANSMIT_DATA_Msk              0xFFu                                          /**< (UART_TRANSMIT_DATA) Register Mask  */

/* -------- UART_TRANSMIT_STATUS : (UART Offset: 0x04) (R/ 8) Status of the UART transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TX_FIFO_NOT_FULL:1;        /**< bit:      0  Active High indication when Tx FIFO can still accepts at least one more character. 0: TX FIFO Full. 1: TX FIFO not Full.  */
    uint8_t  TX_FIFO_0P25_EMPTY:1;      /**< bit:      1  Active High indication when Tx FIFO is at least quarter empty. Reset when more.  */
    uint8_t  TX_FIFO_0P5_EMPTY:1;       /**< bit:      2  Active High indication when Tx FIFO is at least half empty. Reset when more.  */
    uint8_t  TX_FIFO_0P75_EMPTY:1;      /**< bit:      3  Active High indication when Tx FIFO is at least three quarters empty. Reset when more.  */
    uint8_t  TX_FIFO_EMPTY:1;           /**< bit:      4  Active High indication when Tx FIFO is Empty and has no more character to transmit  */
    uint8_t  CTS_ACTIVE:1;              /**< bit:      5  Active High indication when flow control signal "cts" is active. Unaffected by cts  enable bit in config register.  */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} UART_TRANSMIT_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define UART_TRANSMIT_STATUS_OFFSET         0x04                                          /**<  (UART_TRANSMIT_STATUS) Status of the UART transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.   Offset */
#define UART_TRANSMIT_STATUS_RESETVALUE     0x00u                                         /**<  (UART_TRANSMIT_STATUS) Status of the UART transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.   Reset Value */

#define UART_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Pos 0                                              /**< (UART_TRANSMIT_STATUS) Active High indication when Tx FIFO can still accepts at least one more character. 0: TX FIFO Full. 1: TX FIFO not Full.  Position */
#define UART_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Msk (0x1u << UART_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Pos)  /**< (UART_TRANSMIT_STATUS) Active High indication when Tx FIFO can still accepts at least one more character. 0: TX FIFO Full. 1: TX FIFO not Full.  Mask */
#define UART_TRANSMIT_STATUS_TX_FIFO_NOT_FULL UART_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Msk instead */
#define UART_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Pos 1                                              /**< (UART_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least quarter empty. Reset when more.  Position */
#define UART_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Msk (0x1u << UART_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Pos)  /**< (UART_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least quarter empty. Reset when more.  Mask */
#define UART_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY UART_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Msk instead */
#define UART_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Pos 2                                              /**< (UART_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least half empty. Reset when more.  Position */
#define UART_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Msk (0x1u << UART_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Pos)  /**< (UART_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least half empty. Reset when more.  Mask */
#define UART_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY UART_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Msk instead */
#define UART_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Pos 3                                              /**< (UART_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least three quarters empty. Reset when more.  Position */
#define UART_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Msk (0x1u << UART_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Pos)  /**< (UART_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least three quarters empty. Reset when more.  Mask */
#define UART_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY UART_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Msk instead */
#define UART_TRANSMIT_STATUS_TX_FIFO_EMPTY_Pos 4                                              /**< (UART_TRANSMIT_STATUS) Active High indication when Tx FIFO is Empty and has no more character to transmit  Position */
#define UART_TRANSMIT_STATUS_TX_FIFO_EMPTY_Msk (0x1u << UART_TRANSMIT_STATUS_TX_FIFO_EMPTY_Pos)  /**< (UART_TRANSMIT_STATUS) Active High indication when Tx FIFO is Empty and has no more character to transmit  Mask */
#define UART_TRANSMIT_STATUS_TX_FIFO_EMPTY  UART_TRANSMIT_STATUS_TX_FIFO_EMPTY_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_TRANSMIT_STATUS_TX_FIFO_EMPTY_Msk instead */
#define UART_TRANSMIT_STATUS_CTS_ACTIVE_Pos 5                                              /**< (UART_TRANSMIT_STATUS) Active High indication when flow control signal "cts" is active. Unaffected by cts  enable bit in config register.  Position */
#define UART_TRANSMIT_STATUS_CTS_ACTIVE_Msk (0x1u << UART_TRANSMIT_STATUS_CTS_ACTIVE_Pos)  /**< (UART_TRANSMIT_STATUS) Active High indication when flow control signal "cts" is active. Unaffected by cts  enable bit in config register.  Mask */
#define UART_TRANSMIT_STATUS_CTS_ACTIVE     UART_TRANSMIT_STATUS_CTS_ACTIVE_Msk            /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_TRANSMIT_STATUS_CTS_ACTIVE_Msk instead */
#define UART_TRANSMIT_STATUS_MASK           0x3Fu                                          /**< \deprecated (UART_TRANSMIT_STATUS) Register MASK  (Use UART_TRANSMIT_STATUS_Msk instead)  */
#define UART_TRANSMIT_STATUS_Msk            0x3Fu                                          /**< (UART_TRANSMIT_STATUS) Register Mask  */

/* -------- UART_TX_INTERRUPT_MASK : (UART Offset: 0x08) (R/W 8) Enable or Disable the generation of interrupts by the tx_status register.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TX_FIFO_NOT_FULL_MASK:1;   /**< bit:      0  Active High Enable of tx_fifo_not_full interrupt  */
    uint8_t  TX_FIFO_0P25_EMPTY_MASK:1;  /**< bit:      1  Active High Enable of tx_fifo_0p25_empty interrupt  */
    uint8_t  TX_FIFO_0P5_EMPTY_MASK:1;  /**< bit:      2  Active High Enable of tx_fifo_0p5_empty interrupt  */
    uint8_t  TX_FIFO_0P75_EMPTY_MASK:1;  /**< bit:      3  Active High Enable of tx_fifo_0p75_empty interrupt  */
    uint8_t  TX_FIFO_EMPTY_MASK:1;      /**< bit:      4  Active High Enable of tx_fifo_empty interrupt  */
    uint8_t  CTS_ACTIVE_MASK:1;         /**< bit:      5  Active High Enable of cts_active interrupt  */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} UART_TX_INTERRUPT_MASK_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define UART_TX_INTERRUPT_MASK_OFFSET       0x08                                          /**<  (UART_TX_INTERRUPT_MASK) Enable or Disable the generation of interrupts by the tx_status register.   Offset */
#define UART_TX_INTERRUPT_MASK_RESETVALUE   0x00u                                         /**<  (UART_TX_INTERRUPT_MASK) Enable or Disable the generation of interrupts by the tx_status register.   Reset Value */

#define UART_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Pos 0                                              /**< (UART_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_not_full interrupt  Position */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Msk (0x1u << UART_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Pos)  /**< (UART_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_not_full interrupt  Mask */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK UART_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Msk instead */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Pos 1                                              /**< (UART_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p25_empty interrupt  Position */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Msk (0x1u << UART_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Pos)  /**< (UART_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p25_empty interrupt  Mask */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK UART_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Msk instead */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Pos 2                                              /**< (UART_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p5_empty interrupt  Position */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Msk (0x1u << UART_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Pos)  /**< (UART_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p5_empty interrupt  Mask */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK UART_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Msk instead */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Pos 3                                              /**< (UART_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p75_empty interrupt  Position */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Msk (0x1u << UART_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Pos)  /**< (UART_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p75_empty interrupt  Mask */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK UART_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Msk instead */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Pos 4                                              /**< (UART_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_empty interrupt  Position */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Msk (0x1u << UART_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Pos)  /**< (UART_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_empty interrupt  Mask */
#define UART_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK UART_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Msk instead */
#define UART_TX_INTERRUPT_MASK_CTS_ACTIVE_MASK_Pos 5                                              /**< (UART_TX_INTERRUPT_MASK) Active High Enable of cts_active interrupt  Position */
#define UART_TX_INTERRUPT_MASK_CTS_ACTIVE_MASK_Msk (0x1u << UART_TX_INTERRUPT_MASK_CTS_ACTIVE_MASK_Pos)  /**< (UART_TX_INTERRUPT_MASK) Active High Enable of cts_active interrupt  Mask */
#define UART_TX_INTERRUPT_MASK_CTS_ACTIVE_MASK UART_TX_INTERRUPT_MASK_CTS_ACTIVE_MASK_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_TX_INTERRUPT_MASK_CTS_ACTIVE_MASK_Msk instead */
#define UART_TX_INTERRUPT_MASK_Msk          0x3Fu                                          /**< (UART_TX_INTERRUPT_MASK) Register Mask  */

/* -------- UART_RECEIVE_DATA : (UART Offset: 0x10) (R/ 8) Read one byte from UART Receive Data FIFO.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RX_BYTE:8;                 /**< bit:   0..7  Oldest data in receive FIFO. If byte length is set to 7, the MSB is set to 0.  */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} UART_RECEIVE_DATA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define UART_RECEIVE_DATA_OFFSET            0x10                                          /**<  (UART_RECEIVE_DATA) Read one byte from UART Receive Data FIFO.   Offset */
#define UART_RECEIVE_DATA_RESETVALUE        0x00u                                         /**<  (UART_RECEIVE_DATA) Read one byte from UART Receive Data FIFO.   Reset Value */

#define UART_RECEIVE_DATA_RX_BYTE_Pos       0                                              /**< (UART_RECEIVE_DATA) Oldest data in receive FIFO. If byte length is set to 7, the MSB is set to 0.  Position */
#define UART_RECEIVE_DATA_RX_BYTE_Msk       (0xFFu << UART_RECEIVE_DATA_RX_BYTE_Pos)       /**< (UART_RECEIVE_DATA) Oldest data in receive FIFO. If byte length is set to 7, the MSB is set to 0.  Mask */
#define UART_RECEIVE_DATA_RX_BYTE(value)    (UART_RECEIVE_DATA_RX_BYTE_Msk & ((value) << UART_RECEIVE_DATA_RX_BYTE_Pos))
#define UART_RECEIVE_DATA_MASK              0xFFu                                          /**< \deprecated (UART_RECEIVE_DATA) Register MASK  (Use UART_RECEIVE_DATA_Msk instead)  */
#define UART_RECEIVE_DATA_Msk               0xFFu                                          /**< (UART_RECEIVE_DATA) Register Mask  */

/* -------- UART_RECEIVE_STATUS : (UART Offset: 0x14) (R/ 8) Status of the UART receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RX_FIFO_NOT_EMPTY:1;       /**< bit:      0  Active High indication when data is available in Rx FIFO. 0: RX FIFO Empty. 1: RX FIFO contains at least one byte of data.  */
    uint8_t  RX_FIFO_0P25_FULL:1;       /**< bit:      1  Active High indication when FIFO is at least quarter full. Reset when less.  */
    uint8_t  RX_FIFO_0P5_FULL:1;        /**< bit:      2  Active High indication when FIFO is at least half full. Reset when less.  */
    uint8_t  RX_FIFO_0P75_FULL:1;       /**< bit:      3  Active High indication when FIFO is at least three quarters full. Reset when less.  */
    uint8_t  TIMEOUT:1;                 /**< bit:      4  Active High indication when the timeout set in the rx_timeout register has elapsed since  the last interaction with the receiver. Reset by reading the status register.   */
    uint8_t  PARITY_ERROR:1;            /**< bit:      5  Active High indication when a receive parity error is detected. Reset by reading the status register.  */
    uint8_t  FIFO_OVERRUN:1;            /**< bit:      6  Active High indication when character is received but FIFO is full. Reset by reading the status register.  */
    uint8_t  FRAMING_ERROR:1;           /**< bit:      7  Active High indication when no stop bit is detected. Reset by reading the status register.  */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} UART_RECEIVE_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define UART_RECEIVE_STATUS_OFFSET          0x14                                          /**<  (UART_RECEIVE_STATUS) Status of the UART receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.   Offset */
#define UART_RECEIVE_STATUS_RESETVALUE      0x00u                                         /**<  (UART_RECEIVE_STATUS) Status of the UART receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.   Reset Value */

#define UART_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Pos 0                                              /**< (UART_RECEIVE_STATUS) Active High indication when data is available in Rx FIFO. 0: RX FIFO Empty. 1: RX FIFO contains at least one byte of data.  Position */
#define UART_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Msk (0x1u << UART_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Pos)  /**< (UART_RECEIVE_STATUS) Active High indication when data is available in Rx FIFO. 0: RX FIFO Empty. 1: RX FIFO contains at least one byte of data.  Mask */
#define UART_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY UART_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Msk instead */
#define UART_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Pos 1                                              /**< (UART_RECEIVE_STATUS) Active High indication when FIFO is at least quarter full. Reset when less.  Position */
#define UART_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Msk (0x1u << UART_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Pos)  /**< (UART_RECEIVE_STATUS) Active High indication when FIFO is at least quarter full. Reset when less.  Mask */
#define UART_RECEIVE_STATUS_RX_FIFO_0P25_FULL UART_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Msk instead */
#define UART_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Pos 2                                              /**< (UART_RECEIVE_STATUS) Active High indication when FIFO is at least half full. Reset when less.  Position */
#define UART_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Msk (0x1u << UART_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Pos)  /**< (UART_RECEIVE_STATUS) Active High indication when FIFO is at least half full. Reset when less.  Mask */
#define UART_RECEIVE_STATUS_RX_FIFO_0P5_FULL UART_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Msk instead */
#define UART_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Pos 3                                              /**< (UART_RECEIVE_STATUS) Active High indication when FIFO is at least three quarters full. Reset when less.  Position */
#define UART_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Msk (0x1u << UART_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Pos)  /**< (UART_RECEIVE_STATUS) Active High indication when FIFO is at least three quarters full. Reset when less.  Mask */
#define UART_RECEIVE_STATUS_RX_FIFO_0P75_FULL UART_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Msk instead */
#define UART_RECEIVE_STATUS_TIMEOUT_Pos     4                                              /**< (UART_RECEIVE_STATUS) Active High indication when the timeout set in the rx_timeout register has elapsed since  the last interaction with the receiver. Reset by reading the status register.   Position */
#define UART_RECEIVE_STATUS_TIMEOUT_Msk     (0x1u << UART_RECEIVE_STATUS_TIMEOUT_Pos)      /**< (UART_RECEIVE_STATUS) Active High indication when the timeout set in the rx_timeout register has elapsed since  the last interaction with the receiver. Reset by reading the status register.   Mask */
#define UART_RECEIVE_STATUS_TIMEOUT         UART_RECEIVE_STATUS_TIMEOUT_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RECEIVE_STATUS_TIMEOUT_Msk instead */
#define UART_RECEIVE_STATUS_PARITY_ERROR_Pos 5                                              /**< (UART_RECEIVE_STATUS) Active High indication when a receive parity error is detected. Reset by reading the status register.  Position */
#define UART_RECEIVE_STATUS_PARITY_ERROR_Msk (0x1u << UART_RECEIVE_STATUS_PARITY_ERROR_Pos)  /**< (UART_RECEIVE_STATUS) Active High indication when a receive parity error is detected. Reset by reading the status register.  Mask */
#define UART_RECEIVE_STATUS_PARITY_ERROR    UART_RECEIVE_STATUS_PARITY_ERROR_Msk           /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RECEIVE_STATUS_PARITY_ERROR_Msk instead */
#define UART_RECEIVE_STATUS_FIFO_OVERRUN_Pos 6                                              /**< (UART_RECEIVE_STATUS) Active High indication when character is received but FIFO is full. Reset by reading the status register.  Position */
#define UART_RECEIVE_STATUS_FIFO_OVERRUN_Msk (0x1u << UART_RECEIVE_STATUS_FIFO_OVERRUN_Pos)  /**< (UART_RECEIVE_STATUS) Active High indication when character is received but FIFO is full. Reset by reading the status register.  Mask */
#define UART_RECEIVE_STATUS_FIFO_OVERRUN    UART_RECEIVE_STATUS_FIFO_OVERRUN_Msk           /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RECEIVE_STATUS_FIFO_OVERRUN_Msk instead */
#define UART_RECEIVE_STATUS_FRAMING_ERROR_Pos 7                                              /**< (UART_RECEIVE_STATUS) Active High indication when no stop bit is detected. Reset by reading the status register.  Position */
#define UART_RECEIVE_STATUS_FRAMING_ERROR_Msk (0x1u << UART_RECEIVE_STATUS_FRAMING_ERROR_Pos)  /**< (UART_RECEIVE_STATUS) Active High indication when no stop bit is detected. Reset by reading the status register.  Mask */
#define UART_RECEIVE_STATUS_FRAMING_ERROR   UART_RECEIVE_STATUS_FRAMING_ERROR_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RECEIVE_STATUS_FRAMING_ERROR_Msk instead */
#define UART_RECEIVE_STATUS_MASK            0xFFu                                          /**< \deprecated (UART_RECEIVE_STATUS) Register MASK  (Use UART_RECEIVE_STATUS_Msk instead)  */
#define UART_RECEIVE_STATUS_Msk             0xFFu                                          /**< (UART_RECEIVE_STATUS) Register Mask  */

/* -------- UART_RX_INTERRUPT_MASK : (UART Offset: 0x18) (R/W 8) Enable or Disable the generation of interrupts by the rx_status register.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RX_FIFO_NOT_EMPTY_MASK:1;  /**< bit:      0  Active High Enable of rx_fifo_not_empty interrupt  */
    uint8_t  RX_FIFO_0P25_FULL_MASK:1;  /**< bit:      1  Active High Enable of rx_fifo_0p25_full interrupt  */
    uint8_t  RX_FIFO_0P5_FULL_MASK:1;   /**< bit:      2  Active High Enable of rx_fifo_0p5_full interrupt  */
    uint8_t  RX_FIFO_0P75_FULL_MASK:1;  /**< bit:      3  Active High Enable of rx_fifo_0p75_full interrupt  */
    uint8_t  TIMEOUT_MASK:1;            /**< bit:      4  Active High Enable of timeout interrupt  */
    uint8_t  PARITY_ERROR_MASK:1;       /**< bit:      5  Active High Enable of parity error interrupt  */
    uint8_t  FIFO_OVERRUN_MASK:1;       /**< bit:      6  Active High Enable of FIFO overrun interrupt  */
    uint8_t  FRAMING_ERROR_MASK:1;      /**< bit:      7  Active High Enable of framing error interrupt  */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} UART_RX_INTERRUPT_MASK_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define UART_RX_INTERRUPT_MASK_OFFSET       0x18                                          /**<  (UART_RX_INTERRUPT_MASK) Enable or Disable the generation of interrupts by the rx_status register.   Offset */
#define UART_RX_INTERRUPT_MASK_RESETVALUE   0x00u                                         /**<  (UART_RX_INTERRUPT_MASK) Enable or Disable the generation of interrupts by the rx_status register.   Reset Value */

#define UART_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Pos 0                                              /**< (UART_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_not_empty interrupt  Position */
#define UART_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Msk (0x1u << UART_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Pos)  /**< (UART_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_not_empty interrupt  Mask */
#define UART_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK UART_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Msk instead */
#define UART_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Pos 1                                              /**< (UART_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p25_full interrupt  Position */
#define UART_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Msk (0x1u << UART_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Pos)  /**< (UART_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p25_full interrupt  Mask */
#define UART_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK UART_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Msk instead */
#define UART_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Pos 2                                              /**< (UART_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p5_full interrupt  Position */
#define UART_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Msk (0x1u << UART_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Pos)  /**< (UART_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p5_full interrupt  Mask */
#define UART_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK UART_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Msk instead */
#define UART_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Pos 3                                              /**< (UART_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p75_full interrupt  Position */
#define UART_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Msk (0x1u << UART_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Pos)  /**< (UART_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p75_full interrupt  Mask */
#define UART_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK UART_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Msk instead */
#define UART_RX_INTERRUPT_MASK_TIMEOUT_MASK_Pos 4                                              /**< (UART_RX_INTERRUPT_MASK) Active High Enable of timeout interrupt  Position */
#define UART_RX_INTERRUPT_MASK_TIMEOUT_MASK_Msk (0x1u << UART_RX_INTERRUPT_MASK_TIMEOUT_MASK_Pos)  /**< (UART_RX_INTERRUPT_MASK) Active High Enable of timeout interrupt  Mask */
#define UART_RX_INTERRUPT_MASK_TIMEOUT_MASK UART_RX_INTERRUPT_MASK_TIMEOUT_MASK_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RX_INTERRUPT_MASK_TIMEOUT_MASK_Msk instead */
#define UART_RX_INTERRUPT_MASK_PARITY_ERROR_MASK_Pos 5                                              /**< (UART_RX_INTERRUPT_MASK) Active High Enable of parity error interrupt  Position */
#define UART_RX_INTERRUPT_MASK_PARITY_ERROR_MASK_Msk (0x1u << UART_RX_INTERRUPT_MASK_PARITY_ERROR_MASK_Pos)  /**< (UART_RX_INTERRUPT_MASK) Active High Enable of parity error interrupt  Mask */
#define UART_RX_INTERRUPT_MASK_PARITY_ERROR_MASK UART_RX_INTERRUPT_MASK_PARITY_ERROR_MASK_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RX_INTERRUPT_MASK_PARITY_ERROR_MASK_Msk instead */
#define UART_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Pos 6                                              /**< (UART_RX_INTERRUPT_MASK) Active High Enable of FIFO overrun interrupt  Position */
#define UART_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Msk (0x1u << UART_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Pos)  /**< (UART_RX_INTERRUPT_MASK) Active High Enable of FIFO overrun interrupt  Mask */
#define UART_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK UART_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Msk instead */
#define UART_RX_INTERRUPT_MASK_FRAMING_ERROR_MASK_Pos 7                                              /**< (UART_RX_INTERRUPT_MASK) Active High Enable of framing error interrupt  Position */
#define UART_RX_INTERRUPT_MASK_FRAMING_ERROR_MASK_Msk (0x1u << UART_RX_INTERRUPT_MASK_FRAMING_ERROR_MASK_Pos)  /**< (UART_RX_INTERRUPT_MASK) Active High Enable of framing error interrupt  Mask */
#define UART_RX_INTERRUPT_MASK_FRAMING_ERROR_MASK UART_RX_INTERRUPT_MASK_FRAMING_ERROR_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_RX_INTERRUPT_MASK_FRAMING_ERROR_MASK_Msk instead */
#define UART_RX_INTERRUPT_MASK_Msk          0xFFu                                          /**< (UART_RX_INTERRUPT_MASK) Register Mask  */

/* -------- UART_RECEIVE_TIMEOUT : (UART Offset: 0x1c) (R/W 8) Timeout counter configuration.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TIMEOUT_VALUE:8;           /**< bit:   0..7  Timeout counter reload value, after status register is read or character received.  Counter decrements at baud rate clock.  */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} UART_RECEIVE_TIMEOUT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define UART_RECEIVE_TIMEOUT_OFFSET         0x1C                                          /**<  (UART_RECEIVE_TIMEOUT) Timeout counter configuration.   Offset */
#define UART_RECEIVE_TIMEOUT_RESETVALUE     0x00u                                         /**<  (UART_RECEIVE_TIMEOUT) Timeout counter configuration.   Reset Value */

#define UART_RECEIVE_TIMEOUT_TIMEOUT_VALUE_Pos 0                                              /**< (UART_RECEIVE_TIMEOUT) Timeout counter reload value, after status register is read or character received.  Counter decrements at baud rate clock.  Position */
#define UART_RECEIVE_TIMEOUT_TIMEOUT_VALUE_Msk (0xFFu << UART_RECEIVE_TIMEOUT_TIMEOUT_VALUE_Pos)  /**< (UART_RECEIVE_TIMEOUT) Timeout counter reload value, after status register is read or character received.  Counter decrements at baud rate clock.  Mask */
#define UART_RECEIVE_TIMEOUT_TIMEOUT_VALUE(value) (UART_RECEIVE_TIMEOUT_TIMEOUT_VALUE_Msk & ((value) << UART_RECEIVE_TIMEOUT_TIMEOUT_VALUE_Pos))
#define UART_RECEIVE_TIMEOUT_MASK           0xFFu                                          /**< \deprecated (UART_RECEIVE_TIMEOUT) Register MASK  (Use UART_RECEIVE_TIMEOUT_Msk instead)  */
#define UART_RECEIVE_TIMEOUT_Msk            0xFFu                                          /**< (UART_RECEIVE_TIMEOUT) Register Mask  */

/* -------- UART_CONFIGURATION : (UART Offset: 0x20) (R/W 8) UART Operation Configuration Register, for both Rx and Tx.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  NUMBER_OF_BITS:1;          /**< bit:      0  Number of bits per character, not including parity */
    uint8_t  PARITY_ENABLE:1;           /**< bit:      1  Active High parity checking and generation enable */
    uint8_t  PARITY_MODE:2;             /**< bit:   2..3  Parity Mode Select                       */
    uint8_t  STOP_BITS:1;               /**< bit:      4  Number of stop bits                      */
    uint8_t  CTS_ENABLE:1;              /**< bit:      5  Active High Flow Control Enable. When enabled, transmission starts when cts signal is asserted */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} UART_CONFIGURATION_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define UART_CONFIGURATION_OFFSET           0x20                                          /**<  (UART_CONFIGURATION) UART Operation Configuration Register, for both Rx and Tx.   Offset */
#define UART_CONFIGURATION_RESETVALUE       0x00u                                         /**<  (UART_CONFIGURATION) UART Operation Configuration Register, for both Rx and Tx.   Reset Value */

#define UART_CONFIGURATION_NUMBER_OF_BITS_Pos 0                                              /**< (UART_CONFIGURATION) Number of bits per character, not including parity Position */
#define UART_CONFIGURATION_NUMBER_OF_BITS_Msk (0x1u << UART_CONFIGURATION_NUMBER_OF_BITS_Pos)  /**< (UART_CONFIGURATION) Number of bits per character, not including parity Mask */
#define UART_CONFIGURATION_NUMBER_OF_BITS   UART_CONFIGURATION_NUMBER_OF_BITS_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_CONFIGURATION_NUMBER_OF_BITS_Msk instead */
#define   UART_CONFIGURATION_NUMBER_OF_BITS_0_Val 0x0u                                           /**< (UART_CONFIGURATION) 8 bits  */
#define   UART_CONFIGURATION_NUMBER_OF_BITS_1_Val 0x1u                                           /**< (UART_CONFIGURATION) 7 bits  */
#define UART_CONFIGURATION_NUMBER_OF_BITS_0 (UART_CONFIGURATION_NUMBER_OF_BITS_0_Val << UART_CONFIGURATION_NUMBER_OF_BITS_Pos)  /**< (UART_CONFIGURATION) 8 bits Position  */
#define UART_CONFIGURATION_NUMBER_OF_BITS_1 (UART_CONFIGURATION_NUMBER_OF_BITS_1_Val << UART_CONFIGURATION_NUMBER_OF_BITS_Pos)  /**< (UART_CONFIGURATION) 7 bits Position  */
#define UART_CONFIGURATION_PARITY_ENABLE_Pos 1                                              /**< (UART_CONFIGURATION) Active High parity checking and generation enable Position */
#define UART_CONFIGURATION_PARITY_ENABLE_Msk (0x1u << UART_CONFIGURATION_PARITY_ENABLE_Pos)  /**< (UART_CONFIGURATION) Active High parity checking and generation enable Mask */
#define UART_CONFIGURATION_PARITY_ENABLE    UART_CONFIGURATION_PARITY_ENABLE_Msk           /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_CONFIGURATION_PARITY_ENABLE_Msk instead */
#define   UART_CONFIGURATION_PARITY_ENABLE_0_Val 0x0u                                           /**< (UART_CONFIGURATION) Disable  */
#define   UART_CONFIGURATION_PARITY_ENABLE_1_Val 0x1u                                           /**< (UART_CONFIGURATION) Enable  */
#define UART_CONFIGURATION_PARITY_ENABLE_0  (UART_CONFIGURATION_PARITY_ENABLE_0_Val << UART_CONFIGURATION_PARITY_ENABLE_Pos)  /**< (UART_CONFIGURATION) Disable Position  */
#define UART_CONFIGURATION_PARITY_ENABLE_1  (UART_CONFIGURATION_PARITY_ENABLE_1_Val << UART_CONFIGURATION_PARITY_ENABLE_Pos)  /**< (UART_CONFIGURATION) Enable Position  */
#define UART_CONFIGURATION_PARITY_MODE_Pos  2                                              /**< (UART_CONFIGURATION) Parity Mode Select Position */
#define UART_CONFIGURATION_PARITY_MODE_Msk  (0x3u << UART_CONFIGURATION_PARITY_MODE_Pos)   /**< (UART_CONFIGURATION) Parity Mode Select Mask */
#define UART_CONFIGURATION_PARITY_MODE(value) (UART_CONFIGURATION_PARITY_MODE_Msk & ((value) << UART_CONFIGURATION_PARITY_MODE_Pos))
#define   UART_CONFIGURATION_PARITY_MODE_0_Val 0x0u                                           /**< (UART_CONFIGURATION) Even Parity  */
#define   UART_CONFIGURATION_PARITY_MODE_1_Val 0x1u                                           /**< (UART_CONFIGURATION) Odd Parity  */
#define   UART_CONFIGURATION_PARITY_MODE_2_Val 0x2u                                           /**< (UART_CONFIGURATION) Parity bit is space  */
#define   UART_CONFIGURATION_PARITY_MODE_3_Val 0x3u                                           /**< (UART_CONFIGURATION) Parity bit is mark  */
#define UART_CONFIGURATION_PARITY_MODE_0    (UART_CONFIGURATION_PARITY_MODE_0_Val << UART_CONFIGURATION_PARITY_MODE_Pos)  /**< (UART_CONFIGURATION) Even Parity Position  */
#define UART_CONFIGURATION_PARITY_MODE_1    (UART_CONFIGURATION_PARITY_MODE_1_Val << UART_CONFIGURATION_PARITY_MODE_Pos)  /**< (UART_CONFIGURATION) Odd Parity Position  */
#define UART_CONFIGURATION_PARITY_MODE_2    (UART_CONFIGURATION_PARITY_MODE_2_Val << UART_CONFIGURATION_PARITY_MODE_Pos)  /**< (UART_CONFIGURATION) Parity bit is space Position  */
#define UART_CONFIGURATION_PARITY_MODE_3    (UART_CONFIGURATION_PARITY_MODE_3_Val << UART_CONFIGURATION_PARITY_MODE_Pos)  /**< (UART_CONFIGURATION) Parity bit is mark Position  */
#define UART_CONFIGURATION_STOP_BITS_Pos    4                                              /**< (UART_CONFIGURATION) Number of stop bits Position */
#define UART_CONFIGURATION_STOP_BITS_Msk    (0x1u << UART_CONFIGURATION_STOP_BITS_Pos)     /**< (UART_CONFIGURATION) Number of stop bits Mask */
#define UART_CONFIGURATION_STOP_BITS        UART_CONFIGURATION_STOP_BITS_Msk               /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_CONFIGURATION_STOP_BITS_Msk instead */
#define   UART_CONFIGURATION_STOP_BITS_0_Val 0x0u                                           /**< (UART_CONFIGURATION) One Bit  */
#define   UART_CONFIGURATION_STOP_BITS_1_Val 0x1u                                           /**< (UART_CONFIGURATION) Two Bits  */
#define UART_CONFIGURATION_STOP_BITS_0      (UART_CONFIGURATION_STOP_BITS_0_Val << UART_CONFIGURATION_STOP_BITS_Pos)  /**< (UART_CONFIGURATION) One Bit Position  */
#define UART_CONFIGURATION_STOP_BITS_1      (UART_CONFIGURATION_STOP_BITS_1_Val << UART_CONFIGURATION_STOP_BITS_Pos)  /**< (UART_CONFIGURATION) Two Bits Position  */
#define UART_CONFIGURATION_CTS_ENABLE_Pos   5                                              /**< (UART_CONFIGURATION) Active High Flow Control Enable. When enabled, transmission starts when cts signal is asserted Position */
#define UART_CONFIGURATION_CTS_ENABLE_Msk   (0x1u << UART_CONFIGURATION_CTS_ENABLE_Pos)    /**< (UART_CONFIGURATION) Active High Flow Control Enable. When enabled, transmission starts when cts signal is asserted Mask */
#define UART_CONFIGURATION_CTS_ENABLE       UART_CONFIGURATION_CTS_ENABLE_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use UART_CONFIGURATION_CTS_ENABLE_Msk instead */
#define   UART_CONFIGURATION_CTS_ENABLE_0_Val 0x0u                                           /**< (UART_CONFIGURATION) Disable-Transmission starts only when cts signal is asserted  */
#define   UART_CONFIGURATION_CTS_ENABLE_1_Val 0x1u                                           /**< (UART_CONFIGURATION) Enable-Transmission starts regardless of cts signal  */
#define UART_CONFIGURATION_CTS_ENABLE_0     (UART_CONFIGURATION_CTS_ENABLE_0_Val << UART_CONFIGURATION_CTS_ENABLE_Pos)  /**< (UART_CONFIGURATION) Disable-Transmission starts only when cts signal is asserted Position  */
#define UART_CONFIGURATION_CTS_ENABLE_1     (UART_CONFIGURATION_CTS_ENABLE_1_Val << UART_CONFIGURATION_CTS_ENABLE_Pos)  /**< (UART_CONFIGURATION) Enable-Transmission starts regardless of cts signal Position  */
#define UART_CONFIGURATION_MASK             0x3Fu                                          /**< \deprecated (UART_CONFIGURATION) Register MASK  (Use UART_CONFIGURATION_Msk instead)  */
#define UART_CONFIGURATION_Msk              0x3Fu                                          /**< (UART_CONFIGURATION) Register Mask  */

/* -------- UART_BAUD_RATE : (UART Offset: 0x24) (R/W 16) Baud Rate Control Register. Bits 15:3 specify the integral division of the clock (divide by n),  and bit 2:0 specify the fractional division.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t FRACTIONAL_DIVISION:3;     /**< bit:   0..2  Fractional Division Part. If non-zero, the integer part must be at least set to 3.  */
    uint16_t INTEGER_DIVISION:13;       /**< bit:  3..15  Integral Division Part. Must be at least set to 2.  */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} UART_BAUD_RATE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define UART_BAUD_RATE_OFFSET               0x24                                          /**<  (UART_BAUD_RATE) Baud Rate Control Register. Bits 15:3 specify the integral division of the clock (divide by n),  and bit 2:0 specify the fractional division.   Offset */
#define UART_BAUD_RATE_RESETVALUE           0x00u                                         /**<  (UART_BAUD_RATE) Baud Rate Control Register. Bits 15:3 specify the integral division of the clock (divide by n),  and bit 2:0 specify the fractional division.   Reset Value */

#define UART_BAUD_RATE_FRACTIONAL_DIVISION_Pos 0                                              /**< (UART_BAUD_RATE) Fractional Division Part. If non-zero, the integer part must be at least set to 3.  Position */
#define UART_BAUD_RATE_FRACTIONAL_DIVISION_Msk (0x7u << UART_BAUD_RATE_FRACTIONAL_DIVISION_Pos)  /**< (UART_BAUD_RATE) Fractional Division Part. If non-zero, the integer part must be at least set to 3.  Mask */
#define UART_BAUD_RATE_FRACTIONAL_DIVISION(value) (UART_BAUD_RATE_FRACTIONAL_DIVISION_Msk & ((value) << UART_BAUD_RATE_FRACTIONAL_DIVISION_Pos))
#define UART_BAUD_RATE_INTEGER_DIVISION_Pos 3                                              /**< (UART_BAUD_RATE) Integral Division Part. Must be at least set to 2.  Position */
#define UART_BAUD_RATE_INTEGER_DIVISION_Msk (0x1FFFu << UART_BAUD_RATE_INTEGER_DIVISION_Pos)  /**< (UART_BAUD_RATE) Integral Division Part. Must be at least set to 2.  Mask */
#define UART_BAUD_RATE_INTEGER_DIVISION(value) (UART_BAUD_RATE_INTEGER_DIVISION_Msk & ((value) << UART_BAUD_RATE_INTEGER_DIVISION_Pos))
#define UART_BAUD_RATE_MASK                 0xFFFFu                                        /**< \deprecated (UART_BAUD_RATE) Register MASK  (Use UART_BAUD_RATE_Msk instead)  */
#define UART_BAUD_RATE_Msk                  0xFFFFu                                        /**< (UART_BAUD_RATE) Register Mask  */

/* -------- UART_CLOCK_SOURCE : (UART Offset: 0x28) (R/W 8) Selects Source of UART Clock  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CLOCK_SELECT:2;            /**< bit:   0..1  Selects one of the four possible clock sources. */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} UART_CLOCK_SOURCE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define UART_CLOCK_SOURCE_OFFSET            0x28                                          /**<  (UART_CLOCK_SOURCE) Selects Source of UART Clock   Offset */
#define UART_CLOCK_SOURCE_RESETVALUE        0x00u                                         /**<  (UART_CLOCK_SOURCE) Selects Source of UART Clock   Reset Value */

#define UART_CLOCK_SOURCE_CLOCK_SELECT_Pos  0                                              /**< (UART_CLOCK_SOURCE) Selects one of the four possible clock sources. Position */
#define UART_CLOCK_SOURCE_CLOCK_SELECT_Msk  (0x3u << UART_CLOCK_SOURCE_CLOCK_SELECT_Pos)   /**< (UART_CLOCK_SOURCE) Selects one of the four possible clock sources. Mask */
#define UART_CLOCK_SOURCE_CLOCK_SELECT(value) (UART_CLOCK_SOURCE_CLOCK_SELECT_Msk & ((value) << UART_CLOCK_SOURCE_CLOCK_SELECT_Pos))
#define   UART_CLOCK_SOURCE_CLOCK_SELECT_0_Val 0x0u                                           /**< (UART_CLOCK_SOURCE) Clock input 0  */
#define   UART_CLOCK_SOURCE_CLOCK_SELECT_1_Val 0x1u                                           /**< (UART_CLOCK_SOURCE) Clock input 1  */
#define   UART_CLOCK_SOURCE_CLOCK_SELECT_2_Val 0x2u                                           /**< (UART_CLOCK_SOURCE) Clock input 2  */
#define   UART_CLOCK_SOURCE_CLOCK_SELECT_3_Val 0x3u                                           /**< (UART_CLOCK_SOURCE) Clock input 3  */
#define UART_CLOCK_SOURCE_CLOCK_SELECT_0    (UART_CLOCK_SOURCE_CLOCK_SELECT_0_Val << UART_CLOCK_SOURCE_CLOCK_SELECT_Pos)  /**< (UART_CLOCK_SOURCE) Clock input 0 Position  */
#define UART_CLOCK_SOURCE_CLOCK_SELECT_1    (UART_CLOCK_SOURCE_CLOCK_SELECT_1_Val << UART_CLOCK_SOURCE_CLOCK_SELECT_Pos)  /**< (UART_CLOCK_SOURCE) Clock input 1 Position  */
#define UART_CLOCK_SOURCE_CLOCK_SELECT_2    (UART_CLOCK_SOURCE_CLOCK_SELECT_2_Val << UART_CLOCK_SOURCE_CLOCK_SELECT_Pos)  /**< (UART_CLOCK_SOURCE) Clock input 2 Position  */
#define UART_CLOCK_SOURCE_CLOCK_SELECT_3    (UART_CLOCK_SOURCE_CLOCK_SELECT_3_Val << UART_CLOCK_SOURCE_CLOCK_SELECT_Pos)  /**< (UART_CLOCK_SOURCE) Clock input 3 Position  */
#define UART_CLOCK_SOURCE_MASK              0x03u                                          /**< \deprecated (UART_CLOCK_SOURCE) Register MASK  (Use UART_CLOCK_SOURCE_Msk instead)  */
#define UART_CLOCK_SOURCE_Msk               0x03u                                          /**< (UART_CLOCK_SOURCE) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief UART hardware registers */
typedef struct {  /* UART Controller */
  WoReg8  TRANSMIT_DATA;  /**< (UART Offset: 0x00) Writes one byte to UART Transmit Data FIFO.  */
  __I  uint8_t  Reserved1[3];
  RoReg8  TRANSMIT_STATUS; /**< (UART Offset: 0x04) Status of the UART transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.  */
  __I  uint8_t  Reserved2[3];
  RwReg8  TX_INTERRUPT_MASK; /**< (UART Offset: 0x08) Enable or Disable the generation of interrupts by the tx_status register.  */
  __I  uint8_t  Reserved3[7];
  RoReg8  RECEIVE_DATA;   /**< (UART Offset: 0x10) Read one byte from UART Receive Data FIFO.  */
  __I  uint8_t  Reserved4[3];
  RoReg8  RECEIVE_STATUS; /**< (UART Offset: 0x14) Status of the UART receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.  */
  __I  uint8_t  Reserved5[3];
  RwReg8  RX_INTERRUPT_MASK; /**< (UART Offset: 0x18) Enable or Disable the generation of interrupts by the rx_status register.  */
  __I  uint8_t  Reserved6[3];
  RwReg8  RECEIVE_TIMEOUT; /**< (UART Offset: 0x1C) Timeout counter configuration.  */
  __I  uint8_t  Reserved7[3];
  RwReg8  UART_CONFIGURATION; /**< (UART Offset: 0x20) UART Operation Configuration Register, for both Rx and Tx.  */
  __I  uint8_t  Reserved8[3];
  RwReg16 UART_BAUD_RATE; /**< (UART Offset: 0x24) Baud Rate Control Register. Bits 15:3 specify the integral division of the clock (divide by n),  and bit 2:0 specify the fractional division.  */
  __I  uint8_t  Reserved9[2];
  RwReg8  UART_CLOCK_SOURCE; /**< (UART Offset: 0x28) Selects Source of UART Clock  */
} Uart;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief UART hardware registers */
typedef struct {  /* UART Controller */
  __O  UART_TRANSMIT_DATA_Type        TRANSMIT_DATA;  /**< Offset: 0x00 ( /W   8) Writes one byte to UART Transmit Data FIFO.  */
       RoReg8                         Reserved1[0x3];
  __I  UART_TRANSMIT_STATUS_Type      TRANSMIT_STATUS; /**< Offset: 0x04 (R/    8) Status of the UART transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.  */
       RoReg8                         Reserved2[0x3];
  __IO UART_TX_INTERRUPT_MASK_Type    TX_INTERRUPT_MASK; /**< Offset: 0x08 (R/W   8) Enable or Disable the generation of interrupts by the tx_status register.  */
       RoReg8                         Reserved3[0x7];
  __I  UART_RECEIVE_DATA_Type         RECEIVE_DATA;   /**< Offset: 0x10 (R/    8) Read one byte from UART Receive Data FIFO.  */
       RoReg8                         Reserved4[0x3];
  __I  UART_RECEIVE_STATUS_Type       RECEIVE_STATUS; /**< Offset: 0x14 (R/    8) Status of the UART receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.  */
       RoReg8                         Reserved5[0x3];
  __IO UART_RX_INTERRUPT_MASK_Type    RX_INTERRUPT_MASK; /**< Offset: 0x18 (R/W   8) Enable or Disable the generation of interrupts by the rx_status register.  */
       RoReg8                         Reserved6[0x3];
  __IO UART_RECEIVE_TIMEOUT_Type      RECEIVE_TIMEOUT; /**< Offset: 0x1C (R/W   8) Timeout counter configuration.  */
       RoReg8                         Reserved7[0x3];
  __IO UART_CONFIGURATION_Type        UART_CONFIGURATION; /**< Offset: 0x20 (R/W   8) UART Operation Configuration Register, for both Rx and Tx.  */
       RoReg8                         Reserved8[0x3];
  __IO UART_BAUD_RATE_Type            UART_BAUD_RATE; /**< Offset: 0x24 (R/W  16) Baud Rate Control Register. Bits 15:3 specify the integral division of the clock (divide by n),  and bit 2:0 specify the fractional division.  */
       RoReg8                         Reserved9[0x2];
  __IO UART_CLOCK_SOURCE_Type         UART_CLOCK_SOURCE; /**< Offset: 0x28 (R/W   8) Selects Source of UART Clock  */
} Uart;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_UART_COMPONENT_ */
