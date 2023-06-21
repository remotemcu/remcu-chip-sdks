/**
 * \file
 *
 * \brief Component description for I2C
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

#ifndef _SAMB11_I2C_COMPONENT_
#define _SAMB11_I2C_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR I2C */
/* ========================================================================== */
/** \addtogroup SAMB11_I2C I2C Master/Slave Controller 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define I2C_I1234
#define REV_I2C                          0x100

/* -------- I2C_TRANSMIT_DATA : (I2C Offset: 0x00) (/W 16) Writes one byte to I2C Transmit Data FIFO.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t TX_DATA:8;                 /**< bit:   0..7  Represents either Tx Data, or Address and Direction if address flag is set.  */
    uint16_t ADDRESS_FLAG:1;            /**< bit:      8  Specifies that tx_data field is used for address and direction. */
    uint16_t :7;                        /**< bit:  9..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} I2C_TRANSMIT_DATA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_TRANSMIT_DATA_OFFSET            0x00                                          /**<  (I2C_TRANSMIT_DATA) Writes one byte to I2C Transmit Data FIFO.   Offset */
#define I2C_TRANSMIT_DATA_RESETVALUE        0x00u                                         /**<  (I2C_TRANSMIT_DATA) Writes one byte to I2C Transmit Data FIFO.   Reset Value */

#define I2C_TRANSMIT_DATA_TX_DATA_Pos       0                                              /**< (I2C_TRANSMIT_DATA) Represents either Tx Data, or Address and Direction if address flag is set.  Position */
#define I2C_TRANSMIT_DATA_TX_DATA_Msk       (0xFFu << I2C_TRANSMIT_DATA_TX_DATA_Pos)       /**< (I2C_TRANSMIT_DATA) Represents either Tx Data, or Address and Direction if address flag is set.  Mask */
#define I2C_TRANSMIT_DATA_TX_DATA(value)    (I2C_TRANSMIT_DATA_TX_DATA_Msk & ((value) << I2C_TRANSMIT_DATA_TX_DATA_Pos))
#define I2C_TRANSMIT_DATA_ADDRESS_FLAG_Pos  8                                              /**< (I2C_TRANSMIT_DATA) Specifies that tx_data field is used for address and direction. Position */
#define I2C_TRANSMIT_DATA_ADDRESS_FLAG_Msk  (0x1u << I2C_TRANSMIT_DATA_ADDRESS_FLAG_Pos)   /**< (I2C_TRANSMIT_DATA) Specifies that tx_data field is used for address and direction. Mask */
#define I2C_TRANSMIT_DATA_ADDRESS_FLAG      I2C_TRANSMIT_DATA_ADDRESS_FLAG_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_TRANSMIT_DATA_ADDRESS_FLAG_Msk instead */
#define   I2C_TRANSMIT_DATA_ADDRESS_FLAG_0_Val 0x0u                                           /**< (I2C_TRANSMIT_DATA) tx_data field bits 7:0 are Transmit Data  */
#define   I2C_TRANSMIT_DATA_ADDRESS_FLAG_1_Val 0x1u                                           /**< (I2C_TRANSMIT_DATA) tx_data field bit 0 is direction (0: write to slave, 1: read from slave), and bits 7:1 are the Address to transmit.  */
#define I2C_TRANSMIT_DATA_ADDRESS_FLAG_0    (I2C_TRANSMIT_DATA_ADDRESS_FLAG_0_Val << I2C_TRANSMIT_DATA_ADDRESS_FLAG_Pos)  /**< (I2C_TRANSMIT_DATA) tx_data field bits 7:0 are Transmit Data Position  */
#define I2C_TRANSMIT_DATA_ADDRESS_FLAG_1    (I2C_TRANSMIT_DATA_ADDRESS_FLAG_1_Val << I2C_TRANSMIT_DATA_ADDRESS_FLAG_Pos)  /**< (I2C_TRANSMIT_DATA) tx_data field bit 0 is direction (0: write to slave, 1: read from slave), and bits 7:1 are the Address to transmit. Position  */
#define I2C_TRANSMIT_DATA_MASK              0x1FFu                                         /**< \deprecated (I2C_TRANSMIT_DATA) Register MASK  (Use I2C_TRANSMIT_DATA_Msk instead)  */
#define I2C_TRANSMIT_DATA_Msk               0x1FFu                                         /**< (I2C_TRANSMIT_DATA) Register Mask  */

/* -------- I2C_RECEIVE_DATA : (I2C Offset: 0x04) (R/ 8) Read one byte from I2C Receive Data FIFO.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RX_BYTE:8;                 /**< bit:   0..7  Oldest data in receive FIFO.             */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} I2C_RECEIVE_DATA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_RECEIVE_DATA_OFFSET             0x04                                          /**<  (I2C_RECEIVE_DATA) Read one byte from I2C Receive Data FIFO.   Offset */
#define I2C_RECEIVE_DATA_RESETVALUE         0x00u                                         /**<  (I2C_RECEIVE_DATA) Read one byte from I2C Receive Data FIFO.   Reset Value */

#define I2C_RECEIVE_DATA_RX_BYTE_Pos        0                                              /**< (I2C_RECEIVE_DATA) Oldest data in receive FIFO.  Position */
#define I2C_RECEIVE_DATA_RX_BYTE_Msk        (0xFFu << I2C_RECEIVE_DATA_RX_BYTE_Pos)        /**< (I2C_RECEIVE_DATA) Oldest data in receive FIFO.  Mask */
#define I2C_RECEIVE_DATA_RX_BYTE(value)     (I2C_RECEIVE_DATA_RX_BYTE_Msk & ((value) << I2C_RECEIVE_DATA_RX_BYTE_Pos))
#define I2C_RECEIVE_DATA_MASK               0xFFu                                          /**< \deprecated (I2C_RECEIVE_DATA) Register MASK  (Use I2C_RECEIVE_DATA_Msk instead)  */
#define I2C_RECEIVE_DATA_Msk                0xFFu                                          /**< (I2C_RECEIVE_DATA) Register Mask  */

/* -------- I2C_TRANSMIT_STATUS : (I2C Offset: 0x08) (R/ 8) Status of the I2C transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TX_FIFO_NOT_FULL:1;        /**< bit:      0  Active High indication when Tx FIFO can still accepts at least one more character. */
    uint8_t  TX_FIFO_0P25_EMPTY:1;      /**< bit:      1  Active High indication when Tx FIFO is at least quarter empty. Reset when more.  */
    uint8_t  TX_FIFO_0P5_EMPTY:1;       /**< bit:      2  Active High indication when Tx FIFO is at least half empty. Reset when more.  */
    uint8_t  TX_FIFO_0P75_EMPTY:1;      /**< bit:      3  Active High indication when Tx FIFO is at least three quarters empty. Reset when more.  */
    uint8_t  TX_FIFO_EMPTY:1;           /**< bit:      4  Active High indication when Tx FIFO is Empty and has no more character to transmit  */
    uint8_t  :3;                        /**< bit:   5..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} I2C_TRANSMIT_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_TRANSMIT_STATUS_OFFSET          0x08                                          /**<  (I2C_TRANSMIT_STATUS) Status of the I2C transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.   Offset */
#define I2C_TRANSMIT_STATUS_RESETVALUE      0x00u                                         /**<  (I2C_TRANSMIT_STATUS) Status of the I2C transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.   Reset Value */

#define I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Pos 0                                              /**< (I2C_TRANSMIT_STATUS) Active High indication when Tx FIFO can still accepts at least one more character. Position */
#define I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Msk (0x1u << I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Pos)  /**< (I2C_TRANSMIT_STATUS) Active High indication when Tx FIFO can still accepts at least one more character. Mask */
#define I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Msk instead */
#define   I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_0_Val 0x0u                                           /**< (I2C_TRANSMIT_STATUS) TX FIFO Full  */
#define   I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_1_Val 0x1u                                           /**< (I2C_TRANSMIT_STATUS) TX FIFO not Full  */
#define I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_0 (I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_0_Val << I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Pos)  /**< (I2C_TRANSMIT_STATUS) TX FIFO Full Position  */
#define I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_1 (I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_1_Val << I2C_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Pos)  /**< (I2C_TRANSMIT_STATUS) TX FIFO not Full Position  */
#define I2C_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Pos 1                                              /**< (I2C_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least quarter empty. Reset when more.  Position */
#define I2C_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Msk (0x1u << I2C_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Pos)  /**< (I2C_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least quarter empty. Reset when more.  Mask */
#define I2C_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY I2C_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Msk instead */
#define I2C_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Pos 2                                              /**< (I2C_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least half empty. Reset when more.  Position */
#define I2C_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Msk (0x1u << I2C_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Pos)  /**< (I2C_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least half empty. Reset when more.  Mask */
#define I2C_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY I2C_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Msk instead */
#define I2C_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Pos 3                                              /**< (I2C_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least three quarters empty. Reset when more.  Position */
#define I2C_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Msk (0x1u << I2C_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Pos)  /**< (I2C_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least three quarters empty. Reset when more.  Mask */
#define I2C_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY I2C_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Msk instead */
#define I2C_TRANSMIT_STATUS_TX_FIFO_EMPTY_Pos 4                                              /**< (I2C_TRANSMIT_STATUS) Active High indication when Tx FIFO is Empty and has no more character to transmit  Position */
#define I2C_TRANSMIT_STATUS_TX_FIFO_EMPTY_Msk (0x1u << I2C_TRANSMIT_STATUS_TX_FIFO_EMPTY_Pos)  /**< (I2C_TRANSMIT_STATUS) Active High indication when Tx FIFO is Empty and has no more character to transmit  Mask */
#define I2C_TRANSMIT_STATUS_TX_FIFO_EMPTY   I2C_TRANSMIT_STATUS_TX_FIFO_EMPTY_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_TRANSMIT_STATUS_TX_FIFO_EMPTY_Msk instead */
#define I2C_TRANSMIT_STATUS_MASK            0x1Fu                                          /**< \deprecated (I2C_TRANSMIT_STATUS) Register MASK  (Use I2C_TRANSMIT_STATUS_Msk instead)  */
#define I2C_TRANSMIT_STATUS_Msk             0x1Fu                                          /**< (I2C_TRANSMIT_STATUS) Register Mask  */

/* -------- I2C_RECEIVE_STATUS : (I2C Offset: 0x0c) (R/ 8) Status of the I2C receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RX_FIFO_NOT_EMPTY:1;       /**< bit:      0  Active High indication when data is available in Rx FIFO */
    uint8_t  RX_FIFO_0P25_FULL:1;       /**< bit:      1  Active High indication when FIFO is at least quarter full. Reset when less.  */
    uint8_t  RX_FIFO_0P5_FULL:1;        /**< bit:      2  Active High indication when FIFO is at least half full. Reset when less.  */
    uint8_t  RX_FIFO_0P75_FULL:1;       /**< bit:      3  Active High indication when FIFO is at least three quarters full. Reset when less.  */
    uint8_t  FIFO_OVERRUN:1;            /**< bit:      4  Active High indication when character is received but FIFO is full. Reset by reading  the status register.  */
    uint8_t  NAK:1;                     /**< bit:      5  Active High indication when NAK is received. The I2C module will retry transmission  unless transaction aborted by the flush register.  */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} I2C_RECEIVE_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_RECEIVE_STATUS_OFFSET           0x0C                                          /**<  (I2C_RECEIVE_STATUS) Status of the I2C receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.   Offset */
#define I2C_RECEIVE_STATUS_RESETVALUE       0x00u                                         /**<  (I2C_RECEIVE_STATUS) Status of the I2C receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.   Reset Value */

#define I2C_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Pos 0                                              /**< (I2C_RECEIVE_STATUS) Active High indication when data is available in Rx FIFO Position */
#define I2C_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Msk (0x1u << I2C_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Pos)  /**< (I2C_RECEIVE_STATUS) Active High indication when data is available in Rx FIFO Mask */
#define I2C_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY I2C_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Msk instead */
#define I2C_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Pos 1                                              /**< (I2C_RECEIVE_STATUS) Active High indication when FIFO is at least quarter full. Reset when less.  Position */
#define I2C_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Msk (0x1u << I2C_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Pos)  /**< (I2C_RECEIVE_STATUS) Active High indication when FIFO is at least quarter full. Reset when less.  Mask */
#define I2C_RECEIVE_STATUS_RX_FIFO_0P25_FULL I2C_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Msk instead */
#define I2C_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Pos 2                                              /**< (I2C_RECEIVE_STATUS) Active High indication when FIFO is at least half full. Reset when less.  Position */
#define I2C_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Msk (0x1u << I2C_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Pos)  /**< (I2C_RECEIVE_STATUS) Active High indication when FIFO is at least half full. Reset when less.  Mask */
#define I2C_RECEIVE_STATUS_RX_FIFO_0P5_FULL I2C_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Msk instead */
#define I2C_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Pos 3                                              /**< (I2C_RECEIVE_STATUS) Active High indication when FIFO is at least three quarters full. Reset when less.  Position */
#define I2C_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Msk (0x1u << I2C_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Pos)  /**< (I2C_RECEIVE_STATUS) Active High indication when FIFO is at least three quarters full. Reset when less.  Mask */
#define I2C_RECEIVE_STATUS_RX_FIFO_0P75_FULL I2C_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Msk instead */
#define I2C_RECEIVE_STATUS_FIFO_OVERRUN_Pos 4                                              /**< (I2C_RECEIVE_STATUS) Active High indication when character is received but FIFO is full. Reset by reading  the status register.  Position */
#define I2C_RECEIVE_STATUS_FIFO_OVERRUN_Msk (0x1u << I2C_RECEIVE_STATUS_FIFO_OVERRUN_Pos)  /**< (I2C_RECEIVE_STATUS) Active High indication when character is received but FIFO is full. Reset by reading  the status register.  Mask */
#define I2C_RECEIVE_STATUS_FIFO_OVERRUN     I2C_RECEIVE_STATUS_FIFO_OVERRUN_Msk            /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_RECEIVE_STATUS_FIFO_OVERRUN_Msk instead */
#define I2C_RECEIVE_STATUS_NAK_Pos          5                                              /**< (I2C_RECEIVE_STATUS) Active High indication when NAK is received. The I2C module will retry transmission  unless transaction aborted by the flush register.  Position */
#define I2C_RECEIVE_STATUS_NAK_Msk          (0x1u << I2C_RECEIVE_STATUS_NAK_Pos)           /**< (I2C_RECEIVE_STATUS) Active High indication when NAK is received. The I2C module will retry transmission  unless transaction aborted by the flush register.  Mask */
#define I2C_RECEIVE_STATUS_NAK              I2C_RECEIVE_STATUS_NAK_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_RECEIVE_STATUS_NAK_Msk instead */
#define I2C_RECEIVE_STATUS_MASK             0x3Fu                                          /**< \deprecated (I2C_RECEIVE_STATUS) Register MASK  (Use I2C_RECEIVE_STATUS_Msk instead)  */
#define I2C_RECEIVE_STATUS_Msk              0x3Fu                                          /**< (I2C_RECEIVE_STATUS) Register Mask  */

/* -------- I2C_CLOCK_SOURCE_SELECT : (I2C Offset: 0x10) (R/W 8) Clock Source Select -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CLOCK:2;                   /**< bit:   0..1  Clock Used to Generate Divided Clock     */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} I2C_CLOCK_SOURCE_SELECT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_CLOCK_SOURCE_SELECT_OFFSET      0x10                                          /**<  (I2C_CLOCK_SOURCE_SELECT) Clock Source Select  Offset */
#define I2C_CLOCK_SOURCE_SELECT_RESETVALUE  0x00u                                         /**<  (I2C_CLOCK_SOURCE_SELECT) Clock Source Select  Reset Value */

#define I2C_CLOCK_SOURCE_SELECT_CLOCK_Pos   0                                              /**< (I2C_CLOCK_SOURCE_SELECT) Clock Used to Generate Divided Clock Position */
#define I2C_CLOCK_SOURCE_SELECT_CLOCK_Msk   (0x3u << I2C_CLOCK_SOURCE_SELECT_CLOCK_Pos)    /**< (I2C_CLOCK_SOURCE_SELECT) Clock Used to Generate Divided Clock Mask */
#define I2C_CLOCK_SOURCE_SELECT_CLOCK(value) (I2C_CLOCK_SOURCE_SELECT_CLOCK_Msk & ((value) << I2C_CLOCK_SOURCE_SELECT_CLOCK_Pos))
#define   I2C_CLOCK_SOURCE_SELECT_CLOCK_0_Val 0x0u                                           /**< (I2C_CLOCK_SOURCE_SELECT) 26 MHz Clock  */
#define   I2C_CLOCK_SOURCE_SELECT_CLOCK_1_Val 0x1u                                           /**< (I2C_CLOCK_SOURCE_SELECT) 13 MHz Clock  */
#define   I2C_CLOCK_SOURCE_SELECT_CLOCK_2_Val 0x2u                                           /**< (I2C_CLOCK_SOURCE_SELECT) 6.5 MHz Clock  */
#define   I2C_CLOCK_SOURCE_SELECT_CLOCK_3_Val 0x3u                                           /**< (I2C_CLOCK_SOURCE_SELECT) 3.25 MHz Clock  */
#define I2C_CLOCK_SOURCE_SELECT_CLOCK_0     (I2C_CLOCK_SOURCE_SELECT_CLOCK_0_Val << I2C_CLOCK_SOURCE_SELECT_CLOCK_Pos)  /**< (I2C_CLOCK_SOURCE_SELECT) 26 MHz Clock Position  */
#define I2C_CLOCK_SOURCE_SELECT_CLOCK_1     (I2C_CLOCK_SOURCE_SELECT_CLOCK_1_Val << I2C_CLOCK_SOURCE_SELECT_CLOCK_Pos)  /**< (I2C_CLOCK_SOURCE_SELECT) 13 MHz Clock Position  */
#define I2C_CLOCK_SOURCE_SELECT_CLOCK_2     (I2C_CLOCK_SOURCE_SELECT_CLOCK_2_Val << I2C_CLOCK_SOURCE_SELECT_CLOCK_Pos)  /**< (I2C_CLOCK_SOURCE_SELECT) 6.5 MHz Clock Position  */
#define I2C_CLOCK_SOURCE_SELECT_CLOCK_3     (I2C_CLOCK_SOURCE_SELECT_CLOCK_3_Val << I2C_CLOCK_SOURCE_SELECT_CLOCK_Pos)  /**< (I2C_CLOCK_SOURCE_SELECT) 3.25 MHz Clock Position  */
#define I2C_CLOCK_SOURCE_SELECT_MASK        0x03u                                          /**< \deprecated (I2C_CLOCK_SOURCE_SELECT) Register MASK  (Use I2C_CLOCK_SOURCE_SELECT_Msk instead)  */
#define I2C_CLOCK_SOURCE_SELECT_Msk         0x03u                                          /**< (I2C_CLOCK_SOURCE_SELECT) Register Mask  */

/* -------- I2C_MODULE_ENABLE : (I2C Offset: 0x14) (R/W 8) I2C Enable -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ENABLE:1;                  /**< bit:      0  Enables I2C Operation                    */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} I2C_MODULE_ENABLE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_MODULE_ENABLE_OFFSET            0x14                                          /**<  (I2C_MODULE_ENABLE) I2C Enable  Offset */
#define I2C_MODULE_ENABLE_RESETVALUE        0x00u                                         /**<  (I2C_MODULE_ENABLE) I2C Enable  Reset Value */

#define I2C_MODULE_ENABLE_ENABLE_Pos        0                                              /**< (I2C_MODULE_ENABLE) Enables I2C Operation Position */
#define I2C_MODULE_ENABLE_ENABLE_Msk        (0x1u << I2C_MODULE_ENABLE_ENABLE_Pos)         /**< (I2C_MODULE_ENABLE) Enables I2C Operation Mask */
#define I2C_MODULE_ENABLE_ENABLE            I2C_MODULE_ENABLE_ENABLE_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_MODULE_ENABLE_ENABLE_Msk instead */
#define I2C_MODULE_ENABLE_MASK              0x01u                                          /**< \deprecated (I2C_MODULE_ENABLE) Register MASK  (Use I2C_MODULE_ENABLE_Msk instead)  */
#define I2C_MODULE_ENABLE_Msk               0x01u                                          /**< (I2C_MODULE_ENABLE) Register Mask  */

/* -------- I2C_CLK_DIVIDER : (I2C Offset: 0x18) (R/W 16) Register sets the divide ratio used to generate the sck clock from the module's input clock.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t I2C_DIVIDE_RATIO:16;       /**< bit:  0..15  Clock Divide Ratio. The input clock signal is divided by (n+1) where n is the value set in  this field.  The minimum division is by 2; a value of 0 is illegal.  */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} I2C_CLK_DIVIDER_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_CLK_DIVIDER_OFFSET              0x18                                          /**<  (I2C_CLK_DIVIDER) Register sets the divide ratio used to generate the sck clock from the module's input clock.   Offset */
#define I2C_CLK_DIVIDER_RESETVALUE          0x00u                                         /**<  (I2C_CLK_DIVIDER) Register sets the divide ratio used to generate the sck clock from the module's input clock.   Reset Value */

#define I2C_CLK_DIVIDER_I2C_DIVIDE_RATIO_Pos 0                                              /**< (I2C_CLK_DIVIDER) Clock Divide Ratio. The input clock signal is divided by (n+1) where n is the value set in  this field.  The minimum division is by 2; a value of 0 is illegal.  Position */
#define I2C_CLK_DIVIDER_I2C_DIVIDE_RATIO_Msk (0xFFFFu << I2C_CLK_DIVIDER_I2C_DIVIDE_RATIO_Pos)  /**< (I2C_CLK_DIVIDER) Clock Divide Ratio. The input clock signal is divided by (n+1) where n is the value set in  this field.  The minimum division is by 2; a value of 0 is illegal.  Mask */
#define I2C_CLK_DIVIDER_I2C_DIVIDE_RATIO(value) (I2C_CLK_DIVIDER_I2C_DIVIDE_RATIO_Msk & ((value) << I2C_CLK_DIVIDER_I2C_DIVIDE_RATIO_Pos))
#define I2C_CLK_DIVIDER_MASK                0xFFFFu                                        /**< \deprecated (I2C_CLK_DIVIDER) Register MASK  (Use I2C_CLK_DIVIDER_Msk instead)  */
#define I2C_CLK_DIVIDER_Msk                 0xFFFFu                                        /**< (I2C_CLK_DIVIDER) Register Mask  */

/* -------- I2C_MASTER_MODE : (I2C Offset: 0x1c) (R/W 8) Selects I2C Master or Slave Mode.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  MASTER_ENABLE:1;           /**< bit:      0  Active High I2C Master Mode Enable       */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} I2C_MASTER_MODE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_MASTER_MODE_OFFSET              0x1C                                          /**<  (I2C_MASTER_MODE) Selects I2C Master or Slave Mode.   Offset */
#define I2C_MASTER_MODE_RESETVALUE          0x00u                                         /**<  (I2C_MASTER_MODE) Selects I2C Master or Slave Mode.   Reset Value */

#define I2C_MASTER_MODE_MASTER_ENABLE_Pos   0                                              /**< (I2C_MASTER_MODE) Active High I2C Master Mode Enable Position */
#define I2C_MASTER_MODE_MASTER_ENABLE_Msk   (0x1u << I2C_MASTER_MODE_MASTER_ENABLE_Pos)    /**< (I2C_MASTER_MODE) Active High I2C Master Mode Enable Mask */
#define I2C_MASTER_MODE_MASTER_ENABLE       I2C_MASTER_MODE_MASTER_ENABLE_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_MASTER_MODE_MASTER_ENABLE_Msk instead */
#define   I2C_MASTER_MODE_MASTER_ENABLE_0_Val 0x0u                                           /**< (I2C_MASTER_MODE) I2C Slave  */
#define   I2C_MASTER_MODE_MASTER_ENABLE_1_Val 0x1u                                           /**< (I2C_MASTER_MODE) I2C Master  */
#define I2C_MASTER_MODE_MASTER_ENABLE_0     (I2C_MASTER_MODE_MASTER_ENABLE_0_Val << I2C_MASTER_MODE_MASTER_ENABLE_Pos)  /**< (I2C_MASTER_MODE) I2C Slave Position  */
#define I2C_MASTER_MODE_MASTER_ENABLE_1     (I2C_MASTER_MODE_MASTER_ENABLE_1_Val << I2C_MASTER_MODE_MASTER_ENABLE_Pos)  /**< (I2C_MASTER_MODE) I2C Master Position  */
#define I2C_MASTER_MODE_MASK                0x01u                                          /**< \deprecated (I2C_MASTER_MODE) Register MASK  (Use I2C_MASTER_MODE_Msk instead)  */
#define I2C_MASTER_MODE_Msk                 0x01u                                          /**< (I2C_MASTER_MODE) Register Mask  */

/* -------- I2C_ONBUS : (I2C Offset: 0x20) (R/W 8) Enable/Disable transactions when in Master Mode.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ONBUS_ENABLE:1;            /**< bit:      0  Active High Enable to initiate transactions when in Master Mode. */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} I2C_ONBUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_ONBUS_OFFSET                    0x20                                          /**<  (I2C_ONBUS) Enable/Disable transactions when in Master Mode.   Offset */
#define I2C_ONBUS_RESETVALUE                0x00u                                         /**<  (I2C_ONBUS) Enable/Disable transactions when in Master Mode.   Reset Value */

#define I2C_ONBUS_ONBUS_ENABLE_Pos          0                                              /**< (I2C_ONBUS) Active High Enable to initiate transactions when in Master Mode. Position */
#define I2C_ONBUS_ONBUS_ENABLE_Msk          (0x1u << I2C_ONBUS_ONBUS_ENABLE_Pos)           /**< (I2C_ONBUS) Active High Enable to initiate transactions when in Master Mode. Mask */
#define I2C_ONBUS_ONBUS_ENABLE              I2C_ONBUS_ONBUS_ENABLE_Msk                     /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_ONBUS_ONBUS_ENABLE_Msk instead */
#define   I2C_ONBUS_ONBUS_ENABLE_0_Val      0x0u                                           /**< (I2C_ONBUS) Master completes current byte and generates stop condition on bus.  */
#define   I2C_ONBUS_ONBUS_ENABLE_1_Val      0x1u                                           /**< (I2C_ONBUS) Master tranmits contents of FIFO until empty.  */
#define I2C_ONBUS_ONBUS_ENABLE_0            (I2C_ONBUS_ONBUS_ENABLE_0_Val << I2C_ONBUS_ONBUS_ENABLE_Pos)  /**< (I2C_ONBUS) Master completes current byte and generates stop condition on bus. Position  */
#define I2C_ONBUS_ONBUS_ENABLE_1            (I2C_ONBUS_ONBUS_ENABLE_1_Val << I2C_ONBUS_ONBUS_ENABLE_Pos)  /**< (I2C_ONBUS) Master tranmits contents of FIFO until empty. Position  */
#define I2C_ONBUS_MASK                      0x01u                                          /**< \deprecated (I2C_ONBUS) Register MASK  (Use I2C_ONBUS_Msk instead)  */
#define I2C_ONBUS_Msk                       0x01u                                          /**< (I2C_ONBUS) Register Mask  */

/* -------- I2C_SLAVE_ADDRESS : (I2C Offset: 0x24) (R/W 8) Configures the I2C slave Address.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ADDRESS:7;                 /**< bit:   0..6  I2C Slave Address                        */
    uint8_t  :1;                        /**< bit:      7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} I2C_SLAVE_ADDRESS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_SLAVE_ADDRESS_OFFSET            0x24                                          /**<  (I2C_SLAVE_ADDRESS) Configures the I2C slave Address.   Offset */
#define I2C_SLAVE_ADDRESS_RESETVALUE        0x00u                                         /**<  (I2C_SLAVE_ADDRESS) Configures the I2C slave Address.   Reset Value */

#define I2C_SLAVE_ADDRESS_ADDRESS_Pos       0                                              /**< (I2C_SLAVE_ADDRESS) I2C Slave Address  Position */
#define I2C_SLAVE_ADDRESS_ADDRESS_Msk       (0x7Fu << I2C_SLAVE_ADDRESS_ADDRESS_Pos)       /**< (I2C_SLAVE_ADDRESS) I2C Slave Address  Mask */
#define I2C_SLAVE_ADDRESS_ADDRESS(value)    (I2C_SLAVE_ADDRESS_ADDRESS_Msk & ((value) << I2C_SLAVE_ADDRESS_ADDRESS_Pos))
#define I2C_SLAVE_ADDRESS_MASK              0x7Fu                                          /**< \deprecated (I2C_SLAVE_ADDRESS) Register MASK  (Use I2C_SLAVE_ADDRESS_Msk instead)  */
#define I2C_SLAVE_ADDRESS_Msk               0x7Fu                                          /**< (I2C_SLAVE_ADDRESS) Register Mask  */

/* -------- I2C_STATUS : (I2C Offset: 0x28) (R/ 8) Status of I2C Module.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  I2C_ACTIVE:1;              /**< bit:      0  Active High indicatation that the I2C Module is active. While set, I2C configuration  should not be modified.  */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} I2C_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_STATUS_OFFSET                   0x28                                          /**<  (I2C_STATUS) Status of I2C Module.   Offset */
#define I2C_STATUS_RESETVALUE               0x00u                                         /**<  (I2C_STATUS) Status of I2C Module.   Reset Value */

#define I2C_STATUS_I2C_ACTIVE_Pos           0                                              /**< (I2C_STATUS) Active High indicatation that the I2C Module is active. While set, I2C configuration  should not be modified.  Position */
#define I2C_STATUS_I2C_ACTIVE_Msk           (0x1u << I2C_STATUS_I2C_ACTIVE_Pos)            /**< (I2C_STATUS) Active High indicatation that the I2C Module is active. While set, I2C configuration  should not be modified.  Mask */
#define I2C_STATUS_I2C_ACTIVE               I2C_STATUS_I2C_ACTIVE_Msk                      /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_STATUS_I2C_ACTIVE_Msk instead */
#define I2C_STATUS_MASK                     0x01u                                          /**< \deprecated (I2C_STATUS) Register MASK  (Use I2C_STATUS_Msk instead)  */
#define I2C_STATUS_Msk                      0x01u                                          /**< (I2C_STATUS) Register Mask  */

/* -------- I2C_TX_INTERRUPT_MASK : (I2C Offset: 0x2c) (R/W 8) Enable or Disable the generation of interrupts by the tx_status register.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TX_FIFO_NOT_FULL_MASK:1;   /**< bit:      0  Active High Enable of tx_fifo_not_full interrupt  */
    uint8_t  TX_FIFO_0P25_EMPTY_MASK:1;  /**< bit:      1  Active High Enable of tx_fifo_0p25_empty interrupt  */
    uint8_t  TX_FIFO_0P5_EMPTY_MASK:1;  /**< bit:      2  Active High Enable of tx_fifo_0p5_empty interrupt  */
    uint8_t  TX_FIFO_0P75_EMPTY_MASK:1;  /**< bit:      3  Active High Enable of tx_fifo_0p75_empty interrupt  */
    uint8_t  TX_FIFO_EMPTY_MASK:1;      /**< bit:      4  Active High Enable of tx_fifo_empty interrupt  */
    uint8_t  :3;                        /**< bit:   5..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} I2C_TX_INTERRUPT_MASK_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_TX_INTERRUPT_MASK_OFFSET        0x2C                                          /**<  (I2C_TX_INTERRUPT_MASK) Enable or Disable the generation of interrupts by the tx_status register.   Offset */
#define I2C_TX_INTERRUPT_MASK_RESETVALUE    0x00u                                         /**<  (I2C_TX_INTERRUPT_MASK) Enable or Disable the generation of interrupts by the tx_status register.   Reset Value */

#define I2C_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Pos 0                                              /**< (I2C_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_not_full interrupt  Position */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Msk (0x1u << I2C_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Pos)  /**< (I2C_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_not_full interrupt  Mask */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK I2C_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Msk instead */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Pos 1                                              /**< (I2C_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p25_empty interrupt  Position */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Msk (0x1u << I2C_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Pos)  /**< (I2C_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p25_empty interrupt  Mask */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK I2C_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Msk instead */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Pos 2                                              /**< (I2C_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p5_empty interrupt  Position */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Msk (0x1u << I2C_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Pos)  /**< (I2C_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p5_empty interrupt  Mask */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK I2C_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Msk instead */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Pos 3                                              /**< (I2C_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p75_empty interrupt  Position */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Msk (0x1u << I2C_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Pos)  /**< (I2C_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p75_empty interrupt  Mask */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK I2C_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Msk instead */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Pos 4                                              /**< (I2C_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_empty interrupt  Position */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Msk (0x1u << I2C_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Pos)  /**< (I2C_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_empty interrupt  Mask */
#define I2C_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK I2C_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Msk instead */
#define I2C_TX_INTERRUPT_MASK_Msk           0x1Fu                                          /**< (I2C_TX_INTERRUPT_MASK) Register Mask  */

/* -------- I2C_RX_INTERRUPT_MASK : (I2C Offset: 0x30) (R/W 8) Enable or Disable the generation of interrupts by the rx_status register.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RX_FIFO_NOT_EMPTY_MASK:1;  /**< bit:      0  Active High Enable of rx_fifo_not_empty interrupt  */
    uint8_t  RX_FIFO_0P25_FULL_MASK:1;  /**< bit:      1  Active High Enable of rx_fifo_0p25_full interrupt  */
    uint8_t  RX_FIFO_0P5_FULL_MASK:1;   /**< bit:      2  Active High Enable of rx_fifo_0p5_full interrupt  */
    uint8_t  RX_FIFO_0P75_FULL_MASK:1;  /**< bit:      3  Active High Enable of rx_fifo_0p75_full interrupt  */
    uint8_t  FIFO_OVERRUN_MASK:1;       /**< bit:      4  Active High Enable of FIFO overrun interrupt  */
    uint8_t  NAK_MASK:1;                /**< bit:      5  Active High Enable NAK interrupt         */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} I2C_RX_INTERRUPT_MASK_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_RX_INTERRUPT_MASK_OFFSET        0x30                                          /**<  (I2C_RX_INTERRUPT_MASK) Enable or Disable the generation of interrupts by the rx_status register.   Offset */
#define I2C_RX_INTERRUPT_MASK_RESETVALUE    0x00u                                         /**<  (I2C_RX_INTERRUPT_MASK) Enable or Disable the generation of interrupts by the rx_status register.   Reset Value */

#define I2C_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Pos 0                                              /**< (I2C_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_not_empty interrupt  Position */
#define I2C_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Msk (0x1u << I2C_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Pos)  /**< (I2C_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_not_empty interrupt  Mask */
#define I2C_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK I2C_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Msk instead */
#define I2C_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Pos 1                                              /**< (I2C_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p25_full interrupt  Position */
#define I2C_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Msk (0x1u << I2C_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Pos)  /**< (I2C_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p25_full interrupt  Mask */
#define I2C_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK I2C_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Msk instead */
#define I2C_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Pos 2                                              /**< (I2C_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p5_full interrupt  Position */
#define I2C_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Msk (0x1u << I2C_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Pos)  /**< (I2C_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p5_full interrupt  Mask */
#define I2C_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK I2C_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Msk instead */
#define I2C_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Pos 3                                              /**< (I2C_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p75_full interrupt  Position */
#define I2C_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Msk (0x1u << I2C_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Pos)  /**< (I2C_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p75_full interrupt  Mask */
#define I2C_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK I2C_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Msk instead */
#define I2C_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Pos 4                                              /**< (I2C_RX_INTERRUPT_MASK) Active High Enable of FIFO overrun interrupt  Position */
#define I2C_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Msk (0x1u << I2C_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Pos)  /**< (I2C_RX_INTERRUPT_MASK) Active High Enable of FIFO overrun interrupt  Mask */
#define I2C_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK I2C_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Msk instead */
#define I2C_RX_INTERRUPT_MASK_NAK_MASK_Pos  5                                              /**< (I2C_RX_INTERRUPT_MASK) Active High Enable NAK interrupt  Position */
#define I2C_RX_INTERRUPT_MASK_NAK_MASK_Msk  (0x1u << I2C_RX_INTERRUPT_MASK_NAK_MASK_Pos)   /**< (I2C_RX_INTERRUPT_MASK) Active High Enable NAK interrupt  Mask */
#define I2C_RX_INTERRUPT_MASK_NAK_MASK      I2C_RX_INTERRUPT_MASK_NAK_MASK_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_RX_INTERRUPT_MASK_NAK_MASK_Msk instead */
#define I2C_RX_INTERRUPT_MASK_Msk           0x3Fu                                          /**< (I2C_RX_INTERRUPT_MASK) Register Mask  */

/* -------- I2C_FLUSH : (I2C Offset: 0x34) (/W 8) Writing to this address  flushes the contents of both the Tx and Rx FIFOs. The value written has no effect. Flushing the Tx FIFO will abort ongoing transactions when the current byte has been transmitted.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  I2C_FLUSH:1;               /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} I2C_FLUSH_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define I2C_FLUSH_OFFSET                    0x34                                          /**<  (I2C_FLUSH) Writing to this address  flushes the contents of both the Tx and Rx FIFOs. The value written has no effect. Flushing the Tx FIFO will abort ongoing transactions when the current byte has been transmitted.   Offset */
#define I2C_FLUSH_RESETVALUE                0x00u                                         /**<  (I2C_FLUSH) Writing to this address  flushes the contents of both the Tx and Rx FIFOs. The value written has no effect. Flushing the Tx FIFO will abort ongoing transactions when the current byte has been transmitted.   Reset Value */

#define I2C_FLUSH_I2C_FLUSH_Pos             0                                              /**< (I2C_FLUSH)  Position */
#define I2C_FLUSH_I2C_FLUSH_Msk             (0x1u << I2C_FLUSH_I2C_FLUSH_Pos)              /**< (I2C_FLUSH)  Mask */
#define I2C_FLUSH_I2C_FLUSH                 I2C_FLUSH_I2C_FLUSH_Msk                        /**< \deprecated Old style mask definition for 1 bit bitfield. Use I2C_FLUSH_I2C_FLUSH_Msk instead */
#define I2C_FLUSH_MASK                      0x01u                                          /**< \deprecated (I2C_FLUSH) Register MASK  (Use I2C_FLUSH_Msk instead)  */
#define I2C_FLUSH_Msk                       0x01u                                          /**< (I2C_FLUSH) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief I2C hardware registers */
typedef struct {  /* I2C Master/Slave Controller */
  WoReg16 TRANSMIT_DATA;  /**< (I2C Offset: 0x00) Writes one byte to I2C Transmit Data FIFO.  */
  __I  uint8_t  Reserved1[2];
  RoReg8  RECEIVE_DATA;   /**< (I2C Offset: 0x04) Read one byte from I2C Receive Data FIFO.  */
  __I  uint8_t  Reserved2[3];
  RoReg8  TRANSMIT_STATUS; /**< (I2C Offset: 0x08) Status of the I2C transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.  */
  __I  uint8_t  Reserved3[3];
  RoReg8  RECEIVE_STATUS; /**< (I2C Offset: 0x0C) Status of the I2C receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.  */
  __I  uint8_t  Reserved4[3];
  RwReg8  CLOCK_SOURCE_SELECT; /**< (I2C Offset: 0x10) Clock Source Select */
  __I  uint8_t  Reserved5[3];
  RwReg8  I2C_MODULE_ENABLE; /**< (I2C Offset: 0x14) I2C Enable */
  __I  uint8_t  Reserved6[3];
  RwReg16 I2C_CLK_DIVIDER; /**< (I2C Offset: 0x18) Register sets the divide ratio used to generate the sck clock from the module's input clock.  */
  __I  uint8_t  Reserved7[2];
  RwReg8  I2C_MASTER_MODE; /**< (I2C Offset: 0x1C) Selects I2C Master or Slave Mode.  */
  __I  uint8_t  Reserved8[3];
  RwReg8  I2C_ONBUS;      /**< (I2C Offset: 0x20) Enable/Disable transactions when in Master Mode.  */
  __I  uint8_t  Reserved9[3];
  RwReg8  I2C_SLAVE_ADDRESS; /**< (I2C Offset: 0x24) Configures the I2C slave Address.  */
  __I  uint8_t  Reserved10[3];
  RoReg8  I2C_STATUS;     /**< (I2C Offset: 0x28) Status of I2C Module.  */
  __I  uint8_t  Reserved11[3];
  RwReg8  TX_INTERRUPT_MASK; /**< (I2C Offset: 0x2C) Enable or Disable the generation of interrupts by the tx_status register.  */
  __I  uint8_t  Reserved12[3];
  RwReg8  RX_INTERRUPT_MASK; /**< (I2C Offset: 0x30) Enable or Disable the generation of interrupts by the rx_status register.  */
  __I  uint8_t  Reserved13[3];
  WoReg8  I2C_FLUSH;      /**< (I2C Offset: 0x34) Writing to this address  flushes the contents of both the Tx and Rx FIFOs. The value written has no effect. Flushing the Tx FIFO will abort ongoing transactions when the current byte has been transmitted.  */
} I2c;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief I2C hardware registers */
typedef struct {  /* I2C Master/Slave Controller */
  __O  I2C_TRANSMIT_DATA_Type         TRANSMIT_DATA;  /**< Offset: 0x00 ( /W  16) Writes one byte to I2C Transmit Data FIFO.  */
       RoReg8                         Reserved1[0x2];
  __I  I2C_RECEIVE_DATA_Type          RECEIVE_DATA;   /**< Offset: 0x04 (R/    8) Read one byte from I2C Receive Data FIFO.  */
       RoReg8                         Reserved2[0x3];
  __I  I2C_TRANSMIT_STATUS_Type       TRANSMIT_STATUS; /**< Offset: 0x08 (R/    8) Status of the I2C transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.  */
       RoReg8                         Reserved3[0x3];
  __I  I2C_RECEIVE_STATUS_Type        RECEIVE_STATUS; /**< Offset: 0x0C (R/    8) Status of the I2C receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.  */
       RoReg8                         Reserved4[0x3];
  __IO I2C_CLOCK_SOURCE_SELECT_Type   CLOCK_SOURCE_SELECT; /**< Offset: 0x10 (R/W   8) Clock Source Select */
       RoReg8                         Reserved5[0x3];
  __IO I2C_MODULE_ENABLE_Type         I2C_MODULE_ENABLE; /**< Offset: 0x14 (R/W   8) I2C Enable */
       RoReg8                         Reserved6[0x3];
  __IO I2C_CLK_DIVIDER_Type           I2C_CLK_DIVIDER; /**< Offset: 0x18 (R/W  16) Register sets the divide ratio used to generate the sck clock from the module's input clock.  */
       RoReg8                         Reserved7[0x2];
  __IO I2C_MASTER_MODE_Type           I2C_MASTER_MODE; /**< Offset: 0x1C (R/W   8) Selects I2C Master or Slave Mode.  */
       RoReg8                         Reserved8[0x3];
  __IO I2C_ONBUS_Type                 I2C_ONBUS;      /**< Offset: 0x20 (R/W   8) Enable/Disable transactions when in Master Mode.  */
       RoReg8                         Reserved9[0x3];
  __IO I2C_SLAVE_ADDRESS_Type         I2C_SLAVE_ADDRESS; /**< Offset: 0x24 (R/W   8) Configures the I2C slave Address.  */
       RoReg8                         Reserved10[0x3];
  __I  I2C_STATUS_Type                I2C_STATUS;     /**< Offset: 0x28 (R/    8) Status of I2C Module.  */
       RoReg8                         Reserved11[0x3];
  __IO I2C_TX_INTERRUPT_MASK_Type     TX_INTERRUPT_MASK; /**< Offset: 0x2C (R/W   8) Enable or Disable the generation of interrupts by the tx_status register.  */
       RoReg8                         Reserved12[0x3];
  __IO I2C_RX_INTERRUPT_MASK_Type     RX_INTERRUPT_MASK; /**< Offset: 0x30 (R/W   8) Enable or Disable the generation of interrupts by the rx_status register.  */
       RoReg8                         Reserved13[0x3];
  __O  I2C_FLUSH_Type                 I2C_FLUSH;      /**< Offset: 0x34 ( /W   8) Writing to this address  flushes the contents of both the Tx and Rx FIFOs. The value written has no effect. Flushing the Tx FIFO will abort ongoing transactions when the current byte has been transmitted.  */
} I2c;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_I2C_COMPONENT_ */
