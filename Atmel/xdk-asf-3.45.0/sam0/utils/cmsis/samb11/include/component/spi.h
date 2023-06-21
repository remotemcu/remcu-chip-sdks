/**
 * \file
 *
 * \brief Component description for SPI
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

#ifndef _SAMB11_SPI_COMPONENT_
#define _SAMB11_SPI_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR SPI */
/* ========================================================================== */
/** \addtogroup SAMB11_SPI SPI Master/Slave Controller 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define SPI_S1234
#define REV_SPI                          0x100

/* -------- SPI_TRANSMIT_DATA : (SPI Offset: 0x00) (/W 8) Writes one byte to SPI Transmit Data FIFO.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  TX_BYTE:8;                 /**< bit:   0..7  Writes data in transmit FIFO.            */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_TRANSMIT_DATA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_TRANSMIT_DATA_OFFSET            0x00                                          /**<  (SPI_TRANSMIT_DATA) Writes one byte to SPI Transmit Data FIFO.   Offset */
#define SPI_TRANSMIT_DATA_RESETVALUE        0x00u                                         /**<  (SPI_TRANSMIT_DATA) Writes one byte to SPI Transmit Data FIFO.   Reset Value */

#define SPI_TRANSMIT_DATA_TX_BYTE_Pos       0                                              /**< (SPI_TRANSMIT_DATA) Writes data in transmit FIFO.  Position */
#define SPI_TRANSMIT_DATA_TX_BYTE_Msk       (0xFFu << SPI_TRANSMIT_DATA_TX_BYTE_Pos)       /**< (SPI_TRANSMIT_DATA) Writes data in transmit FIFO.  Mask */
#define SPI_TRANSMIT_DATA_TX_BYTE(value)    (SPI_TRANSMIT_DATA_TX_BYTE_Msk & ((value) << SPI_TRANSMIT_DATA_TX_BYTE_Pos))
#define SPI_TRANSMIT_DATA_MASK              0xFFu                                          /**< \deprecated (SPI_TRANSMIT_DATA) Register MASK  (Use SPI_TRANSMIT_DATA_Msk instead)  */
#define SPI_TRANSMIT_DATA_Msk               0xFFu                                          /**< (SPI_TRANSMIT_DATA) Register Mask  */

/* -------- SPI_RECEIVE_DATA : (SPI Offset: 0x04) (R/ 8) Read one byte from SPI Receive Data FIFO.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RX_BYTE:8;                 /**< bit:   0..7  Oldest data in receive FIFO.             */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_RECEIVE_DATA_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_RECEIVE_DATA_OFFSET             0x04                                          /**<  (SPI_RECEIVE_DATA) Read one byte from SPI Receive Data FIFO.   Offset */
#define SPI_RECEIVE_DATA_RESETVALUE         0x00u                                         /**<  (SPI_RECEIVE_DATA) Read one byte from SPI Receive Data FIFO.   Reset Value */

#define SPI_RECEIVE_DATA_RX_BYTE_Pos        0                                              /**< (SPI_RECEIVE_DATA) Oldest data in receive FIFO.  Position */
#define SPI_RECEIVE_DATA_RX_BYTE_Msk        (0xFFu << SPI_RECEIVE_DATA_RX_BYTE_Pos)        /**< (SPI_RECEIVE_DATA) Oldest data in receive FIFO.  Mask */
#define SPI_RECEIVE_DATA_RX_BYTE(value)     (SPI_RECEIVE_DATA_RX_BYTE_Msk & ((value) << SPI_RECEIVE_DATA_RX_BYTE_Pos))
#define SPI_RECEIVE_DATA_MASK               0xFFu                                          /**< \deprecated (SPI_RECEIVE_DATA) Register MASK  (Use SPI_RECEIVE_DATA_Msk instead)  */
#define SPI_RECEIVE_DATA_Msk                0xFFu                                          /**< (SPI_RECEIVE_DATA) Register Mask  */

/* -------- SPI_TRANSMIT_STATUS : (SPI Offset: 0x08) (R/ 8) Status of the SPI transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.  -------- */
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
} SPI_TRANSMIT_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_TRANSMIT_STATUS_OFFSET          0x08                                          /**<  (SPI_TRANSMIT_STATUS) Status of the SPI transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.   Offset */
#define SPI_TRANSMIT_STATUS_RESETVALUE      0x00u                                         /**<  (SPI_TRANSMIT_STATUS) Status of the SPI transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.   Reset Value */

#define SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Pos 0                                              /**< (SPI_TRANSMIT_STATUS) Active High indication when Tx FIFO can still accepts at least one more character. Position */
#define SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Msk (0x1u << SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Pos)  /**< (SPI_TRANSMIT_STATUS) Active High indication when Tx FIFO can still accepts at least one more character. Mask */
#define SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Msk instead */
#define   SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_0_Val 0x0u                                           /**< (SPI_TRANSMIT_STATUS) TX FIFO Full  */
#define   SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_1_Val 0x1u                                           /**< (SPI_TRANSMIT_STATUS) TX FIFO not Full  */
#define SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_0 (SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_0_Val << SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Pos)  /**< (SPI_TRANSMIT_STATUS) TX FIFO Full Position  */
#define SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_1 (SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_1_Val << SPI_TRANSMIT_STATUS_TX_FIFO_NOT_FULL_Pos)  /**< (SPI_TRANSMIT_STATUS) TX FIFO not Full Position  */
#define SPI_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Pos 1                                              /**< (SPI_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least quarter empty. Reset when more.  Position */
#define SPI_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Msk (0x1u << SPI_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Pos)  /**< (SPI_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least quarter empty. Reset when more.  Mask */
#define SPI_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY SPI_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_TRANSMIT_STATUS_TX_FIFO_0P25_EMPTY_Msk instead */
#define SPI_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Pos 2                                              /**< (SPI_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least half empty. Reset when more.  Position */
#define SPI_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Msk (0x1u << SPI_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Pos)  /**< (SPI_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least half empty. Reset when more.  Mask */
#define SPI_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY SPI_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_TRANSMIT_STATUS_TX_FIFO_0P5_EMPTY_Msk instead */
#define SPI_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Pos 3                                              /**< (SPI_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least three quarters empty. Reset when more.  Position */
#define SPI_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Msk (0x1u << SPI_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Pos)  /**< (SPI_TRANSMIT_STATUS) Active High indication when Tx FIFO is at least three quarters empty. Reset when more.  Mask */
#define SPI_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY SPI_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_TRANSMIT_STATUS_TX_FIFO_0P75_EMPTY_Msk instead */
#define SPI_TRANSMIT_STATUS_TX_FIFO_EMPTY_Pos 4                                              /**< (SPI_TRANSMIT_STATUS) Active High indication when Tx FIFO is Empty and has no more character to transmit  Position */
#define SPI_TRANSMIT_STATUS_TX_FIFO_EMPTY_Msk (0x1u << SPI_TRANSMIT_STATUS_TX_FIFO_EMPTY_Pos)  /**< (SPI_TRANSMIT_STATUS) Active High indication when Tx FIFO is Empty and has no more character to transmit  Mask */
#define SPI_TRANSMIT_STATUS_TX_FIFO_EMPTY   SPI_TRANSMIT_STATUS_TX_FIFO_EMPTY_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_TRANSMIT_STATUS_TX_FIFO_EMPTY_Msk instead */
#define SPI_TRANSMIT_STATUS_MASK            0x1Fu                                          /**< \deprecated (SPI_TRANSMIT_STATUS) Register MASK  (Use SPI_TRANSMIT_STATUS_Msk instead)  */
#define SPI_TRANSMIT_STATUS_Msk             0x1Fu                                          /**< (SPI_TRANSMIT_STATUS) Register Mask  */

/* -------- SPI_RECEIVE_STATUS : (SPI Offset: 0x0c) (R/ 8) Status of the SPI receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RX_FIFO_NOT_EMPTY:1;       /**< bit:      0  Active High indication when data is available in Rx FIFO */
    uint8_t  RX_FIFO_0P25_FULL:1;       /**< bit:      1  Active High indication when FIFO is at least quarter full. Reset when less.  */
    uint8_t  RX_FIFO_0P5_FULL:1;        /**< bit:      2  Active High indication when FIFO is at least half full. Reset when less.  */
    uint8_t  RX_FIFO_0P75_FULL:1;       /**< bit:      3  Active High indication when FIFO is at least three quarters full. Reset when less.  */
    uint8_t  FAULT:1;                   /**< bit:      4  Active High indication when two masters attempt to access the SPI bus at the same time. The SPI interface will put itself in slave mode in this case. This bit is reset when the status register is read.   */
    uint8_t  FIFO_OVERRUN:1;            /**< bit:      5  Active High indication when character is received but FIFO is full. Reset by reading  the status register.  */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_RECEIVE_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_RECEIVE_STATUS_OFFSET           0x0C                                          /**<  (SPI_RECEIVE_STATUS) Status of the SPI receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.   Offset */
#define SPI_RECEIVE_STATUS_RESETVALUE       0x00u                                         /**<  (SPI_RECEIVE_STATUS) Status of the SPI receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.   Reset Value */

#define SPI_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Pos 0                                              /**< (SPI_RECEIVE_STATUS) Active High indication when data is available in Rx FIFO Position */
#define SPI_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Msk (0x1u << SPI_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Pos)  /**< (SPI_RECEIVE_STATUS) Active High indication when data is available in Rx FIFO Mask */
#define SPI_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY SPI_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_RECEIVE_STATUS_RX_FIFO_NOT_EMPTY_Msk instead */
#define SPI_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Pos 1                                              /**< (SPI_RECEIVE_STATUS) Active High indication when FIFO is at least quarter full. Reset when less.  Position */
#define SPI_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Msk (0x1u << SPI_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Pos)  /**< (SPI_RECEIVE_STATUS) Active High indication when FIFO is at least quarter full. Reset when less.  Mask */
#define SPI_RECEIVE_STATUS_RX_FIFO_0P25_FULL SPI_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_RECEIVE_STATUS_RX_FIFO_0P25_FULL_Msk instead */
#define SPI_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Pos 2                                              /**< (SPI_RECEIVE_STATUS) Active High indication when FIFO is at least half full. Reset when less.  Position */
#define SPI_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Msk (0x1u << SPI_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Pos)  /**< (SPI_RECEIVE_STATUS) Active High indication when FIFO is at least half full. Reset when less.  Mask */
#define SPI_RECEIVE_STATUS_RX_FIFO_0P5_FULL SPI_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_RECEIVE_STATUS_RX_FIFO_0P5_FULL_Msk instead */
#define SPI_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Pos 3                                              /**< (SPI_RECEIVE_STATUS) Active High indication when FIFO is at least three quarters full. Reset when less.  Position */
#define SPI_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Msk (0x1u << SPI_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Pos)  /**< (SPI_RECEIVE_STATUS) Active High indication when FIFO is at least three quarters full. Reset when less.  Mask */
#define SPI_RECEIVE_STATUS_RX_FIFO_0P75_FULL SPI_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_RECEIVE_STATUS_RX_FIFO_0P75_FULL_Msk instead */
#define SPI_RECEIVE_STATUS_FAULT_Pos        4                                              /**< (SPI_RECEIVE_STATUS) Active High indication when two masters attempt to access the SPI bus at the same time. The SPI interface will put itself in slave mode in this case. This bit is reset when the status register is read.   Position */
#define SPI_RECEIVE_STATUS_FAULT_Msk        (0x1u << SPI_RECEIVE_STATUS_FAULT_Pos)         /**< (SPI_RECEIVE_STATUS) Active High indication when two masters attempt to access the SPI bus at the same time. The SPI interface will put itself in slave mode in this case. This bit is reset when the status register is read.   Mask */
#define SPI_RECEIVE_STATUS_FAULT            SPI_RECEIVE_STATUS_FAULT_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_RECEIVE_STATUS_FAULT_Msk instead */
#define SPI_RECEIVE_STATUS_FIFO_OVERRUN_Pos 5                                              /**< (SPI_RECEIVE_STATUS) Active High indication when character is received but FIFO is full. Reset by reading  the status register.  Position */
#define SPI_RECEIVE_STATUS_FIFO_OVERRUN_Msk (0x1u << SPI_RECEIVE_STATUS_FIFO_OVERRUN_Pos)  /**< (SPI_RECEIVE_STATUS) Active High indication when character is received but FIFO is full. Reset by reading  the status register.  Mask */
#define SPI_RECEIVE_STATUS_FIFO_OVERRUN     SPI_RECEIVE_STATUS_FIFO_OVERRUN_Msk            /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_RECEIVE_STATUS_FIFO_OVERRUN_Msk instead */
#define SPI_RECEIVE_STATUS_MASK             0x3Fu                                          /**< \deprecated (SPI_RECEIVE_STATUS) Register MASK  (Use SPI_RECEIVE_STATUS_Msk instead)  */
#define SPI_RECEIVE_STATUS_Msk              0x3Fu                                          /**< (SPI_RECEIVE_STATUS) Register Mask  */

/* -------- SPI_CLOCK_SOURCE_SELECT : (SPI Offset: 0x10) (R/W 8) Clock Source Select -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CLOCK:2;                   /**< bit:   0..1  Clock Used to Generate Divided Clock     */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_CLOCK_SOURCE_SELECT_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_CLOCK_SOURCE_SELECT_OFFSET      0x10                                          /**<  (SPI_CLOCK_SOURCE_SELECT) Clock Source Select  Offset */
#define SPI_CLOCK_SOURCE_SELECT_RESETVALUE  0x00u                                         /**<  (SPI_CLOCK_SOURCE_SELECT) Clock Source Select  Reset Value */

#define SPI_CLOCK_SOURCE_SELECT_CLOCK_Pos   0                                              /**< (SPI_CLOCK_SOURCE_SELECT) Clock Used to Generate Divided Clock Position */
#define SPI_CLOCK_SOURCE_SELECT_CLOCK_Msk   (0x3u << SPI_CLOCK_SOURCE_SELECT_CLOCK_Pos)    /**< (SPI_CLOCK_SOURCE_SELECT) Clock Used to Generate Divided Clock Mask */
#define SPI_CLOCK_SOURCE_SELECT_CLOCK(value) (SPI_CLOCK_SOURCE_SELECT_CLOCK_Msk & ((value) << SPI_CLOCK_SOURCE_SELECT_CLOCK_Pos))
#define   SPI_CLOCK_SOURCE_SELECT_CLOCK_0_Val 0x0u                                           /**< (SPI_CLOCK_SOURCE_SELECT) 26 MHz Clock  */
#define   SPI_CLOCK_SOURCE_SELECT_CLOCK_1_Val 0x1u                                           /**< (SPI_CLOCK_SOURCE_SELECT) 13 MHz Clock  */
#define   SPI_CLOCK_SOURCE_SELECT_CLOCK_2_Val 0x2u                                           /**< (SPI_CLOCK_SOURCE_SELECT) 6.5 MHz Clock  */
#define   SPI_CLOCK_SOURCE_SELECT_CLOCK_3_Val 0x3u                                           /**< (SPI_CLOCK_SOURCE_SELECT) 3.25 MHz Clock  */
#define SPI_CLOCK_SOURCE_SELECT_CLOCK_0     (SPI_CLOCK_SOURCE_SELECT_CLOCK_0_Val << SPI_CLOCK_SOURCE_SELECT_CLOCK_Pos)  /**< (SPI_CLOCK_SOURCE_SELECT) 26 MHz Clock Position  */
#define SPI_CLOCK_SOURCE_SELECT_CLOCK_1     (SPI_CLOCK_SOURCE_SELECT_CLOCK_1_Val << SPI_CLOCK_SOURCE_SELECT_CLOCK_Pos)  /**< (SPI_CLOCK_SOURCE_SELECT) 13 MHz Clock Position  */
#define SPI_CLOCK_SOURCE_SELECT_CLOCK_2     (SPI_CLOCK_SOURCE_SELECT_CLOCK_2_Val << SPI_CLOCK_SOURCE_SELECT_CLOCK_Pos)  /**< (SPI_CLOCK_SOURCE_SELECT) 6.5 MHz Clock Position  */
#define SPI_CLOCK_SOURCE_SELECT_CLOCK_3     (SPI_CLOCK_SOURCE_SELECT_CLOCK_3_Val << SPI_CLOCK_SOURCE_SELECT_CLOCK_Pos)  /**< (SPI_CLOCK_SOURCE_SELECT) 3.25 MHz Clock Position  */
#define SPI_CLOCK_SOURCE_SELECT_MASK        0x03u                                          /**< \deprecated (SPI_CLOCK_SOURCE_SELECT) Register MASK  (Use SPI_CLOCK_SOURCE_SELECT_Msk instead)  */
#define SPI_CLOCK_SOURCE_SELECT_Msk         0x03u                                          /**< (SPI_CLOCK_SOURCE_SELECT) Register Mask  */

/* -------- SPI_CLK_DIVIDER : (SPI Offset: 0x14) (R/W 16) Register sets the divide ratio used to generate the sck clock from the module's input clock.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t SPI_DIVIDE_RATIO:16;       /**< bit:  0..15  Clock Divide Ratio. The input clock signal is divided by (n+1) where n is the value set in  this field.  The minimum division is by 2; a value of 0 is illegal.  */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} SPI_CLK_DIVIDER_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_CLK_DIVIDER_OFFSET              0x14                                          /**<  (SPI_CLK_DIVIDER) Register sets the divide ratio used to generate the sck clock from the module's input clock.   Offset */
#define SPI_CLK_DIVIDER_RESETVALUE          0x00u                                         /**<  (SPI_CLK_DIVIDER) Register sets the divide ratio used to generate the sck clock from the module's input clock.   Reset Value */

#define SPI_CLK_DIVIDER_SPI_DIVIDE_RATIO_Pos 0                                              /**< (SPI_CLK_DIVIDER) Clock Divide Ratio. The input clock signal is divided by (n+1) where n is the value set in  this field.  The minimum division is by 2; a value of 0 is illegal.  Position */
#define SPI_CLK_DIVIDER_SPI_DIVIDE_RATIO_Msk (0xFFFFu << SPI_CLK_DIVIDER_SPI_DIVIDE_RATIO_Pos)  /**< (SPI_CLK_DIVIDER) Clock Divide Ratio. The input clock signal is divided by (n+1) where n is the value set in  this field.  The minimum division is by 2; a value of 0 is illegal.  Mask */
#define SPI_CLK_DIVIDER_SPI_DIVIDE_RATIO(value) (SPI_CLK_DIVIDER_SPI_DIVIDE_RATIO_Msk & ((value) << SPI_CLK_DIVIDER_SPI_DIVIDE_RATIO_Pos))
#define SPI_CLK_DIVIDER_MASK                0xFFFFu                                        /**< \deprecated (SPI_CLK_DIVIDER) Register MASK  (Use SPI_CLK_DIVIDER_Msk instead)  */
#define SPI_CLK_DIVIDER_Msk                 0xFFFFu                                        /**< (SPI_CLK_DIVIDER) Register Mask  */

/* -------- SPI_MODULE_ENABLE : (SPI Offset: 0x18) (R/W 8) SPI Enable -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  ENABLE:1;                  /**< bit:      0  Enables SPI operation                    */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_MODULE_ENABLE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_MODULE_ENABLE_OFFSET            0x18                                          /**<  (SPI_MODULE_ENABLE) SPI Enable  Offset */
#define SPI_MODULE_ENABLE_RESETVALUE        0x00u                                         /**<  (SPI_MODULE_ENABLE) SPI Enable  Reset Value */

#define SPI_MODULE_ENABLE_ENABLE_Pos        0                                              /**< (SPI_MODULE_ENABLE) Enables SPI operation Position */
#define SPI_MODULE_ENABLE_ENABLE_Msk        (0x1u << SPI_MODULE_ENABLE_ENABLE_Pos)         /**< (SPI_MODULE_ENABLE) Enables SPI operation Mask */
#define SPI_MODULE_ENABLE_ENABLE            SPI_MODULE_ENABLE_ENABLE_Msk                   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_MODULE_ENABLE_ENABLE_Msk instead */
#define SPI_MODULE_ENABLE_MASK              0x01u                                          /**< \deprecated (SPI_MODULE_ENABLE) Register MASK  (Use SPI_MODULE_ENABLE_Msk instead)  */
#define SPI_MODULE_ENABLE_Msk               0x01u                                          /**< (SPI_MODULE_ENABLE) Register Mask  */

/* -------- SPI_MASTER_MODE : (SPI Offset: 0x1c) (R/W 8) SPI Master/Slave Mode. When clear, SPI is in Slave Mode.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  MASTER_ENABLE:1;           /**< bit:      0  Active High SPI Master Mode Enable       */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_MASTER_MODE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_MASTER_MODE_OFFSET              0x1C                                          /**<  (SPI_MASTER_MODE) SPI Master/Slave Mode. When clear, SPI is in Slave Mode.   Offset */
#define SPI_MASTER_MODE_RESETVALUE          0x00u                                         /**<  (SPI_MASTER_MODE) SPI Master/Slave Mode. When clear, SPI is in Slave Mode.   Reset Value */

#define SPI_MASTER_MODE_MASTER_ENABLE_Pos   0                                              /**< (SPI_MASTER_MODE) Active High SPI Master Mode Enable Position */
#define SPI_MASTER_MODE_MASTER_ENABLE_Msk   (0x1u << SPI_MASTER_MODE_MASTER_ENABLE_Pos)    /**< (SPI_MASTER_MODE) Active High SPI Master Mode Enable Mask */
#define SPI_MASTER_MODE_MASTER_ENABLE       SPI_MASTER_MODE_MASTER_ENABLE_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_MASTER_MODE_MASTER_ENABLE_Msk instead */
#define   SPI_MASTER_MODE_MASTER_ENABLE_0_Val 0x0u                                           /**< (SPI_MASTER_MODE) SPI Slave  */
#define   SPI_MASTER_MODE_MASTER_ENABLE_1_Val 0x1u                                           /**< (SPI_MASTER_MODE) SPI Master  */
#define SPI_MASTER_MODE_MASTER_ENABLE_0     (SPI_MASTER_MODE_MASTER_ENABLE_0_Val << SPI_MASTER_MODE_MASTER_ENABLE_Pos)  /**< (SPI_MASTER_MODE) SPI Slave Position  */
#define SPI_MASTER_MODE_MASTER_ENABLE_1     (SPI_MASTER_MODE_MASTER_ENABLE_1_Val << SPI_MASTER_MODE_MASTER_ENABLE_Pos)  /**< (SPI_MASTER_MODE) SPI Master Position  */
#define SPI_MASTER_MODE_MASK                0x01u                                          /**< \deprecated (SPI_MASTER_MODE) Register MASK  (Use SPI_MASTER_MODE_Msk instead)  */
#define SPI_MASTER_MODE_Msk                 0x01u                                          /**< (SPI_MASTER_MODE) Register Mask  */

/* -------- SPI_FAULT_ENABLE : (SPI Offset: 0x20) (R/W 8) SPI Fault Detection Mode. If set, SPI bus contention will be detected, and the fault  bit in the rx_status register will be set, forcing the SPI Module into idle state.  When a fault is detected, the current SPI transaction is abandoned and the interface switches  to slave mode in the wait state.   -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  FAULT_ENABLE:1;            /**< bit:      0  Active High SPI Fault Detect Enable      */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_FAULT_ENABLE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_FAULT_ENABLE_OFFSET             0x20                                          /**<  (SPI_FAULT_ENABLE) SPI Fault Detection Mode. If set, SPI bus contention will be detected, and the fault  bit in the rx_status register will be set, forcing the SPI Module into idle state.  When a fault is detected, the current SPI transaction is abandoned and the interface switches  to slave mode in the wait state.    Offset */
#define SPI_FAULT_ENABLE_RESETVALUE         0x00u                                         /**<  (SPI_FAULT_ENABLE) SPI Fault Detection Mode. If set, SPI bus contention will be detected, and the fault  bit in the rx_status register will be set, forcing the SPI Module into idle state.  When a fault is detected, the current SPI transaction is abandoned and the interface switches  to slave mode in the wait state.    Reset Value */

#define SPI_FAULT_ENABLE_FAULT_ENABLE_Pos   0                                              /**< (SPI_FAULT_ENABLE) Active High SPI Fault Detect Enable Position */
#define SPI_FAULT_ENABLE_FAULT_ENABLE_Msk   (0x1u << SPI_FAULT_ENABLE_FAULT_ENABLE_Pos)    /**< (SPI_FAULT_ENABLE) Active High SPI Fault Detect Enable Mask */
#define SPI_FAULT_ENABLE_FAULT_ENABLE       SPI_FAULT_ENABLE_FAULT_ENABLE_Msk              /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FAULT_ENABLE_FAULT_ENABLE_Msk instead */
#define   SPI_FAULT_ENABLE_FAULT_ENABLE_0_Val 0x0u                                           /**< (SPI_FAULT_ENABLE) Faults ignored on SPI bus  */
#define   SPI_FAULT_ENABLE_FAULT_ENABLE_1_Val 0x1u                                           /**< (SPI_FAULT_ENABLE) Faults detected on SPI bus  */
#define SPI_FAULT_ENABLE_FAULT_ENABLE_0     (SPI_FAULT_ENABLE_FAULT_ENABLE_0_Val << SPI_FAULT_ENABLE_FAULT_ENABLE_Pos)  /**< (SPI_FAULT_ENABLE) Faults ignored on SPI bus Position  */
#define SPI_FAULT_ENABLE_FAULT_ENABLE_1     (SPI_FAULT_ENABLE_FAULT_ENABLE_1_Val << SPI_FAULT_ENABLE_FAULT_ENABLE_Pos)  /**< (SPI_FAULT_ENABLE) Faults detected on SPI bus Position  */
#define SPI_FAULT_ENABLE_MASK               0x01u                                          /**< \deprecated (SPI_FAULT_ENABLE) Register MASK  (Use SPI_FAULT_ENABLE_Msk instead)  */
#define SPI_FAULT_ENABLE_Msk                0x01u                                          /**< (SPI_FAULT_ENABLE) Register Mask  */

/* -------- SPI_CONFIGURATION : (SPI Offset: 0x24) (R/W 8) SPI Operation Configuration Register. This register should not be modified while SPI bus is active,  otherwise the SPI Module state shall not be guaranteed.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SCK_POLARITY:1;            /**< bit:      0  Selects the level of sck in Idle State   */
    uint8_t  SCK_PHASE:1;               /**< bit:      1  Selects clock edge used for data sampling and launching */
    uint8_t  LSB_FIRST_ENABLE:1;        /**< bit:      2  Selects LSB bits to be transmitted first */
    uint8_t  BIDIRECTIONAL_ENABLE:1;    /**< bit:      3  Enable Bidirectional mode of operation   */
    uint8_t  OUTPUT_ENABLE:1;           /**< bit:      4  Active High Output Enable when in Bidirectional Mode */
    uint8_t  SSN_SHIFT_ENABLE:1;        /**< bit:      5  Active High Shift Enable when SSN signal is asserted */
    uint8_t  SSN_SYNC_ENABLE:1;         /**< bit:      6  Active High SSN Signal Synchronisation Enable */
    uint8_t  RX_DONE_SYNC_ENABLE:1;     /**< bit:      7  Active High rx_done Signal Synchronisation Enable */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_CONFIGURATION_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_CONFIGURATION_OFFSET            0x24                                          /**<  (SPI_CONFIGURATION) SPI Operation Configuration Register. This register should not be modified while SPI bus is active,  otherwise the SPI Module state shall not be guaranteed.   Offset */
#define SPI_CONFIGURATION_RESETVALUE        0xE0u                                         /**<  (SPI_CONFIGURATION) SPI Operation Configuration Register. This register should not be modified while SPI bus is active,  otherwise the SPI Module state shall not be guaranteed.   Reset Value */

#define SPI_CONFIGURATION_SCK_POLARITY_Pos  0                                              /**< (SPI_CONFIGURATION) Selects the level of sck in Idle State Position */
#define SPI_CONFIGURATION_SCK_POLARITY_Msk  (0x1u << SPI_CONFIGURATION_SCK_POLARITY_Pos)   /**< (SPI_CONFIGURATION) Selects the level of sck in Idle State Mask */
#define SPI_CONFIGURATION_SCK_POLARITY      SPI_CONFIGURATION_SCK_POLARITY_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_CONFIGURATION_SCK_POLARITY_Msk instead */
#define   SPI_CONFIGURATION_SCK_POLARITY_0_Val 0x0u                                           /**< (SPI_CONFIGURATION) SCK is Low  */
#define   SPI_CONFIGURATION_SCK_POLARITY_1_Val 0x1u                                           /**< (SPI_CONFIGURATION) SCK is High  */
#define SPI_CONFIGURATION_SCK_POLARITY_0    (SPI_CONFIGURATION_SCK_POLARITY_0_Val << SPI_CONFIGURATION_SCK_POLARITY_Pos)  /**< (SPI_CONFIGURATION) SCK is Low Position  */
#define SPI_CONFIGURATION_SCK_POLARITY_1    (SPI_CONFIGURATION_SCK_POLARITY_1_Val << SPI_CONFIGURATION_SCK_POLARITY_Pos)  /**< (SPI_CONFIGURATION) SCK is High Position  */
#define SPI_CONFIGURATION_SCK_PHASE_Pos     1                                              /**< (SPI_CONFIGURATION) Selects clock edge used for data sampling and launching Position */
#define SPI_CONFIGURATION_SCK_PHASE_Msk     (0x1u << SPI_CONFIGURATION_SCK_PHASE_Pos)      /**< (SPI_CONFIGURATION) Selects clock edge used for data sampling and launching Mask */
#define SPI_CONFIGURATION_SCK_PHASE         SPI_CONFIGURATION_SCK_PHASE_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_CONFIGURATION_SCK_PHASE_Msk instead */
#define   SPI_CONFIGURATION_SCK_PHASE_0_Val 0x0u                                           /**< (SPI_CONFIGURATION) Bits are sampled on the first edge and the following bit is output on the next edge  */
#define   SPI_CONFIGURATION_SCK_PHASE_1_Val 0x1u                                           /**< (SPI_CONFIGURATION) Bits are output on the first edge and are sampled on the following edge  */
#define SPI_CONFIGURATION_SCK_PHASE_0       (SPI_CONFIGURATION_SCK_PHASE_0_Val << SPI_CONFIGURATION_SCK_PHASE_Pos)  /**< (SPI_CONFIGURATION) Bits are sampled on the first edge and the following bit is output on the next edge Position  */
#define SPI_CONFIGURATION_SCK_PHASE_1       (SPI_CONFIGURATION_SCK_PHASE_1_Val << SPI_CONFIGURATION_SCK_PHASE_Pos)  /**< (SPI_CONFIGURATION) Bits are output on the first edge and are sampled on the following edge Position  */
#define SPI_CONFIGURATION_LSB_FIRST_ENABLE_Pos 2                                              /**< (SPI_CONFIGURATION) Selects LSB bits to be transmitted first Position */
#define SPI_CONFIGURATION_LSB_FIRST_ENABLE_Msk (0x1u << SPI_CONFIGURATION_LSB_FIRST_ENABLE_Pos)  /**< (SPI_CONFIGURATION) Selects LSB bits to be transmitted first Mask */
#define SPI_CONFIGURATION_LSB_FIRST_ENABLE  SPI_CONFIGURATION_LSB_FIRST_ENABLE_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_CONFIGURATION_LSB_FIRST_ENABLE_Msk instead */
#define   SPI_CONFIGURATION_LSB_FIRST_ENABLE_0_Val 0x0u                                           /**< (SPI_CONFIGURATION) Data transmitted MSB first  */
#define   SPI_CONFIGURATION_LSB_FIRST_ENABLE_1_Val 0x1u                                           /**< (SPI_CONFIGURATION) Data transmitted LSB first  */
#define SPI_CONFIGURATION_LSB_FIRST_ENABLE_0 (SPI_CONFIGURATION_LSB_FIRST_ENABLE_0_Val << SPI_CONFIGURATION_LSB_FIRST_ENABLE_Pos)  /**< (SPI_CONFIGURATION) Data transmitted MSB first Position  */
#define SPI_CONFIGURATION_LSB_FIRST_ENABLE_1 (SPI_CONFIGURATION_LSB_FIRST_ENABLE_1_Val << SPI_CONFIGURATION_LSB_FIRST_ENABLE_Pos)  /**< (SPI_CONFIGURATION) Data transmitted LSB first Position  */
#define SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_Pos 3                                              /**< (SPI_CONFIGURATION) Enable Bidirectional mode of operation Position */
#define SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_Msk (0x1u << SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_Pos)  /**< (SPI_CONFIGURATION) Enable Bidirectional mode of operation Mask */
#define SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_Msk instead */
#define   SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_0_Val 0x0u                                           /**< (SPI_CONFIGURATION) SPI is unidirectional, Tx and Rx each has dedicated one port  */
#define   SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_1_Val 0x1u                                           /**< (SPI_CONFIGURATION) SPI is bidirectional, Tx and Rx share one input/output port (MOSI if Master, MISO if Slave)  */
#define SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_0 (SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_0_Val << SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_Pos)  /**< (SPI_CONFIGURATION) SPI is unidirectional, Tx and Rx each has dedicated one port Position  */
#define SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_1 (SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_1_Val << SPI_CONFIGURATION_BIDIRECTIONAL_ENABLE_Pos)  /**< (SPI_CONFIGURATION) SPI is bidirectional, Tx and Rx share one input/output port (MOSI if Master, MISO if Slave) Position  */
#define SPI_CONFIGURATION_OUTPUT_ENABLE_Pos 4                                              /**< (SPI_CONFIGURATION) Active High Output Enable when in Bidirectional Mode Position */
#define SPI_CONFIGURATION_OUTPUT_ENABLE_Msk (0x1u << SPI_CONFIGURATION_OUTPUT_ENABLE_Pos)  /**< (SPI_CONFIGURATION) Active High Output Enable when in Bidirectional Mode Mask */
#define SPI_CONFIGURATION_OUTPUT_ENABLE     SPI_CONFIGURATION_OUTPUT_ENABLE_Msk            /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_CONFIGURATION_OUTPUT_ENABLE_Msk instead */
#define   SPI_CONFIGURATION_OUTPUT_ENABLE_0_Val 0x0u                                           /**< (SPI_CONFIGURATION) MISO is an input if in Slave mode. MOSI is an input if in Master mode  */
#define   SPI_CONFIGURATION_OUTPUT_ENABLE_1_Val 0x1u                                           /**< (SPI_CONFIGURATION) MISO is an output if in Slave mode. MOSI is an output if in Master mode  */
#define SPI_CONFIGURATION_OUTPUT_ENABLE_0   (SPI_CONFIGURATION_OUTPUT_ENABLE_0_Val << SPI_CONFIGURATION_OUTPUT_ENABLE_Pos)  /**< (SPI_CONFIGURATION) MISO is an input if in Slave mode. MOSI is an input if in Master mode Position  */
#define SPI_CONFIGURATION_OUTPUT_ENABLE_1   (SPI_CONFIGURATION_OUTPUT_ENABLE_1_Val << SPI_CONFIGURATION_OUTPUT_ENABLE_Pos)  /**< (SPI_CONFIGURATION) MISO is an output if in Slave mode. MOSI is an output if in Master mode Position  */
#define SPI_CONFIGURATION_SSN_SHIFT_ENABLE_Pos 5                                              /**< (SPI_CONFIGURATION) Active High Shift Enable when SSN signal is asserted Position */
#define SPI_CONFIGURATION_SSN_SHIFT_ENABLE_Msk (0x1u << SPI_CONFIGURATION_SSN_SHIFT_ENABLE_Pos)  /**< (SPI_CONFIGURATION) Active High Shift Enable when SSN signal is asserted Mask */
#define SPI_CONFIGURATION_SSN_SHIFT_ENABLE  SPI_CONFIGURATION_SSN_SHIFT_ENABLE_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_CONFIGURATION_SSN_SHIFT_ENABLE_Msk instead */
#define   SPI_CONFIGURATION_SSN_SHIFT_ENABLE_0_Val 0x0u                                           /**< (SPI_CONFIGURATION) Shift counter is enabled only when ssn is asserted  */
#define   SPI_CONFIGURATION_SSN_SHIFT_ENABLE_1_Val 0x1u                                           /**< (SPI_CONFIGURATION) Shift counter is always enabled  */
#define SPI_CONFIGURATION_SSN_SHIFT_ENABLE_0 (SPI_CONFIGURATION_SSN_SHIFT_ENABLE_0_Val << SPI_CONFIGURATION_SSN_SHIFT_ENABLE_Pos)  /**< (SPI_CONFIGURATION) Shift counter is enabled only when ssn is asserted Position  */
#define SPI_CONFIGURATION_SSN_SHIFT_ENABLE_1 (SPI_CONFIGURATION_SSN_SHIFT_ENABLE_1_Val << SPI_CONFIGURATION_SSN_SHIFT_ENABLE_Pos)  /**< (SPI_CONFIGURATION) Shift counter is always enabled Position  */
#define SPI_CONFIGURATION_SSN_SYNC_ENABLE_Pos 6                                              /**< (SPI_CONFIGURATION) Active High SSN Signal Synchronisation Enable Position */
#define SPI_CONFIGURATION_SSN_SYNC_ENABLE_Msk (0x1u << SPI_CONFIGURATION_SSN_SYNC_ENABLE_Pos)  /**< (SPI_CONFIGURATION) Active High SSN Signal Synchronisation Enable Mask */
#define SPI_CONFIGURATION_SSN_SYNC_ENABLE   SPI_CONFIGURATION_SSN_SYNC_ENABLE_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_CONFIGURATION_SSN_SYNC_ENABLE_Msk instead */
#define   SPI_CONFIGURATION_SSN_SYNC_ENABLE_0_Val 0x0u                                           /**< (SPI_CONFIGURATION) SSN internal synchronisation is bypassed  */
#define   SPI_CONFIGURATION_SSN_SYNC_ENABLE_1_Val 0x1u                                           /**< (SPI_CONFIGURATION) SSN is internally synchronised before being used  */
#define SPI_CONFIGURATION_SSN_SYNC_ENABLE_0 (SPI_CONFIGURATION_SSN_SYNC_ENABLE_0_Val << SPI_CONFIGURATION_SSN_SYNC_ENABLE_Pos)  /**< (SPI_CONFIGURATION) SSN internal synchronisation is bypassed Position  */
#define SPI_CONFIGURATION_SSN_SYNC_ENABLE_1 (SPI_CONFIGURATION_SSN_SYNC_ENABLE_1_Val << SPI_CONFIGURATION_SSN_SYNC_ENABLE_Pos)  /**< (SPI_CONFIGURATION) SSN is internally synchronised before being used Position  */
#define SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_Pos 7                                              /**< (SPI_CONFIGURATION) Active High rx_done Signal Synchronisation Enable Position */
#define SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_Msk (0x1u << SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_Pos)  /**< (SPI_CONFIGURATION) Active High rx_done Signal Synchronisation Enable Mask */
#define SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_Msk instead */
#define   SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_0_Val 0x0u                                           /**< (SPI_CONFIGURATION) rx_done internal synchronisation is bypassed  */
#define   SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_1_Val 0x1u                                           /**< (SPI_CONFIGURATION) rx_done is internally synchronised before being used  */
#define SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_0 (SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_0_Val << SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_Pos)  /**< (SPI_CONFIGURATION) rx_done internal synchronisation is bypassed Position  */
#define SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_1 (SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_1_Val << SPI_CONFIGURATION_RX_DONE_SYNC_ENABLE_Pos)  /**< (SPI_CONFIGURATION) rx_done is internally synchronised before being used Position  */
#define SPI_CONFIGURATION_MASK              0xFFu                                          /**< \deprecated (SPI_CONFIGURATION) Register MASK  (Use SPI_CONFIGURATION_Msk instead)  */
#define SPI_CONFIGURATION_Msk               0xFFu                                          /**< (SPI_CONFIGURATION) Register Mask  */

/* -------- SPI_BUS_STATUS : (SPI Offset: 0x28) (R/ 8) Status of SPI bus.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  SPI_ACTIVE:1;              /**< bit:      0  Active High indicatation that the SPI Module is active. While set, SPI configuration should not be modified.  */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_BUS_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_BUS_STATUS_OFFSET               0x28                                          /**<  (SPI_BUS_STATUS) Status of SPI bus.   Offset */
#define SPI_BUS_STATUS_RESETVALUE           0x00u                                         /**<  (SPI_BUS_STATUS) Status of SPI bus.   Reset Value */

#define SPI_BUS_STATUS_SPI_ACTIVE_Pos       0                                              /**< (SPI_BUS_STATUS) Active High indicatation that the SPI Module is active. While set, SPI configuration should not be modified.  Position */
#define SPI_BUS_STATUS_SPI_ACTIVE_Msk       (0x1u << SPI_BUS_STATUS_SPI_ACTIVE_Pos)        /**< (SPI_BUS_STATUS) Active High indicatation that the SPI Module is active. While set, SPI configuration should not be modified.  Mask */
#define SPI_BUS_STATUS_SPI_ACTIVE           SPI_BUS_STATUS_SPI_ACTIVE_Msk                  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_BUS_STATUS_SPI_ACTIVE_Msk instead */
#define SPI_BUS_STATUS_MASK                 0x01u                                          /**< \deprecated (SPI_BUS_STATUS) Register MASK  (Use SPI_BUS_STATUS_Msk instead)  */
#define SPI_BUS_STATUS_Msk                  0x01u                                          /**< (SPI_BUS_STATUS) Register Mask  */

/* -------- SPI_TX_INTERRUPT_MASK : (SPI Offset: 0x2c) (R/W 8) Enable or Disable the generation of interrupts by the tx_status register.  -------- */
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
} SPI_TX_INTERRUPT_MASK_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_TX_INTERRUPT_MASK_OFFSET        0x2C                                          /**<  (SPI_TX_INTERRUPT_MASK) Enable or Disable the generation of interrupts by the tx_status register.   Offset */
#define SPI_TX_INTERRUPT_MASK_RESETVALUE    0x00u                                         /**<  (SPI_TX_INTERRUPT_MASK) Enable or Disable the generation of interrupts by the tx_status register.   Reset Value */

#define SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Pos 0                                              /**< (SPI_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_not_full interrupt  Position */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Msk (0x1u << SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Pos)  /**< (SPI_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_not_full interrupt  Mask */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_TX_INTERRUPT_MASK_TX_FIFO_NOT_FULL_MASK_Msk instead */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Pos 1                                              /**< (SPI_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p25_empty interrupt  Position */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Msk (0x1u << SPI_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Pos)  /**< (SPI_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p25_empty interrupt  Mask */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK SPI_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_TX_INTERRUPT_MASK_TX_FIFO_0P25_EMPTY_MASK_Msk instead */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Pos 2                                              /**< (SPI_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p5_empty interrupt  Position */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Msk (0x1u << SPI_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Pos)  /**< (SPI_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p5_empty interrupt  Mask */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK SPI_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_TX_INTERRUPT_MASK_TX_FIFO_0P5_EMPTY_MASK_Msk instead */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Pos 3                                              /**< (SPI_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p75_empty interrupt  Position */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Msk (0x1u << SPI_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Pos)  /**< (SPI_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_0p75_empty interrupt  Mask */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK SPI_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_TX_INTERRUPT_MASK_TX_FIFO_0P75_EMPTY_MASK_Msk instead */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Pos 4                                              /**< (SPI_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_empty interrupt  Position */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Msk (0x1u << SPI_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Pos)  /**< (SPI_TX_INTERRUPT_MASK) Active High Enable of tx_fifo_empty interrupt  Mask */
#define SPI_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK SPI_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_TX_INTERRUPT_MASK_TX_FIFO_EMPTY_MASK_Msk instead */
#define SPI_TX_INTERRUPT_MASK_Msk           0x1Fu                                          /**< (SPI_TX_INTERRUPT_MASK) Register Mask  */

/* -------- SPI_RX_INTERRUPT_MASK : (SPI Offset: 0x30) (R/W 8) Enable or Disable the generation of interrupts by the rx_status register.  -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  RX_FIFO_NOT_EMPTY_MASK:1;  /**< bit:      0  Active High Enable of rx_fifo_not_empty interrupt  */
    uint8_t  RX_FIFO_0P25_FULL_MASK:1;  /**< bit:      1  Active High Enable of rx_fifo_0p25_full interrupt  */
    uint8_t  RX_FIFO_0P5_FULL_MASK:1;   /**< bit:      2  Active High Enable of rx_fifo_0p5_full interrupt  */
    uint8_t  RX_FIFO_0P75_FULL_MASK:1;  /**< bit:      3  Active High Enable of rx_fifo_0p75_full interrupt  */
    uint8_t  FAULT_DETECT_MASK:1;       /**< bit:      4  Active High Enable of fault detection interrupt  */
    uint8_t  FIFO_OVERRUN_MASK:1;       /**< bit:      5  Active High Enable of FIFO overrun interrupt  */
    uint8_t  :2;                        /**< bit:   6..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_RX_INTERRUPT_MASK_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_RX_INTERRUPT_MASK_OFFSET        0x30                                          /**<  (SPI_RX_INTERRUPT_MASK) Enable or Disable the generation of interrupts by the rx_status register.   Offset */
#define SPI_RX_INTERRUPT_MASK_RESETVALUE    0x00u                                         /**<  (SPI_RX_INTERRUPT_MASK) Enable or Disable the generation of interrupts by the rx_status register.   Reset Value */

#define SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Pos 0                                              /**< (SPI_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_not_empty interrupt  Position */
#define SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Msk (0x1u << SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Pos)  /**< (SPI_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_not_empty interrupt  Mask */
#define SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_RX_INTERRUPT_MASK_RX_FIFO_NOT_EMPTY_MASK_Msk instead */
#define SPI_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Pos 1                                              /**< (SPI_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p25_full interrupt  Position */
#define SPI_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Msk (0x1u << SPI_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Pos)  /**< (SPI_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p25_full interrupt  Mask */
#define SPI_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK SPI_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_RX_INTERRUPT_MASK_RX_FIFO_0P25_FULL_MASK_Msk instead */
#define SPI_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Pos 2                                              /**< (SPI_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p5_full interrupt  Position */
#define SPI_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Msk (0x1u << SPI_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Pos)  /**< (SPI_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p5_full interrupt  Mask */
#define SPI_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK SPI_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_RX_INTERRUPT_MASK_RX_FIFO_0P5_FULL_MASK_Msk instead */
#define SPI_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Pos 3                                              /**< (SPI_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p75_full interrupt  Position */
#define SPI_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Msk (0x1u << SPI_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Pos)  /**< (SPI_RX_INTERRUPT_MASK) Active High Enable of rx_fifo_0p75_full interrupt  Mask */
#define SPI_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK SPI_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_RX_INTERRUPT_MASK_RX_FIFO_0P75_FULL_MASK_Msk instead */
#define SPI_RX_INTERRUPT_MASK_FAULT_DETECT_MASK_Pos 4                                              /**< (SPI_RX_INTERRUPT_MASK) Active High Enable of fault detection interrupt  Position */
#define SPI_RX_INTERRUPT_MASK_FAULT_DETECT_MASK_Msk (0x1u << SPI_RX_INTERRUPT_MASK_FAULT_DETECT_MASK_Pos)  /**< (SPI_RX_INTERRUPT_MASK) Active High Enable of fault detection interrupt  Mask */
#define SPI_RX_INTERRUPT_MASK_FAULT_DETECT_MASK SPI_RX_INTERRUPT_MASK_FAULT_DETECT_MASK_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_RX_INTERRUPT_MASK_FAULT_DETECT_MASK_Msk instead */
#define SPI_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Pos 5                                              /**< (SPI_RX_INTERRUPT_MASK) Active High Enable of FIFO overrun interrupt  Position */
#define SPI_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Msk (0x1u << SPI_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Pos)  /**< (SPI_RX_INTERRUPT_MASK) Active High Enable of FIFO overrun interrupt  Mask */
#define SPI_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK SPI_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_RX_INTERRUPT_MASK_FIFO_OVERRUN_MASK_Msk instead */
#define SPI_RX_INTERRUPT_MASK_Msk           0x3Fu                                          /**< (SPI_RX_INTERRUPT_MASK) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief SPI hardware registers */
typedef struct {  /* SPI Master/Slave Controller */
  WoReg8  TRANSMIT_DATA;  /**< (SPI Offset: 0x00) Writes one byte to SPI Transmit Data FIFO.  */
  __I  uint8_t  Reserved1[3];
  RoReg8  RECEIVE_DATA;   /**< (SPI Offset: 0x04) Read one byte from SPI Receive Data FIFO.  */
  __I  uint8_t  Reserved2[3];
  RoReg8  TRANSMIT_STATUS; /**< (SPI Offset: 0x08) Status of the SPI transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.  */
  __I  uint8_t  Reserved3[3];
  RoReg8  RECEIVE_STATUS; /**< (SPI Offset: 0x0C) Status of the SPI receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.  */
  __I  uint8_t  Reserved4[3];
  RwReg8  CLOCK_SOURCE_SELECT; /**< (SPI Offset: 0x10) Clock Source Select */
  __I  uint8_t  Reserved5[3];
  RwReg16 SPI_CLK_DIVIDER; /**< (SPI Offset: 0x14) Register sets the divide ratio used to generate the sck clock from the module's input clock.  */
  __I  uint8_t  Reserved6[2];
  RwReg8  SPI_MODULE_ENABLE; /**< (SPI Offset: 0x18) SPI Enable */
  __I  uint8_t  Reserved7[3];
  RwReg8  SPI_MASTER_MODE; /**< (SPI Offset: 0x1C) SPI Master/Slave Mode. When clear, SPI is in Slave Mode.  */
  __I  uint8_t  Reserved8[3];
  RwReg8  SPI_FAULT_ENABLE; /**< (SPI Offset: 0x20) SPI Fault Detection Mode. If set, SPI bus contention will be detected, and the fault  bit in the rx_status register will be set, forcing the SPI Module into idle state.  When a fault is detected, the current SPI transaction is abandoned and the interface switches  to slave mode in the wait state.   */
  __I  uint8_t  Reserved9[3];
  RwReg8  SPI_CONFIGURATION; /**< (SPI Offset: 0x24) SPI Operation Configuration Register. This register should not be modified while SPI bus is active,  otherwise the SPI Module state shall not be guaranteed.  */
  __I  uint8_t  Reserved10[3];
  RoReg8  SPI_BUS_STATUS; /**< (SPI Offset: 0x28) Status of SPI bus.  */
  __I  uint8_t  Reserved11[3];
  RwReg8  TX_INTERRUPT_MASK; /**< (SPI Offset: 0x2C) Enable or Disable the generation of interrupts by the tx_status register.  */
  __I  uint8_t  Reserved12[3];
  RwReg8  RX_INTERRUPT_MASK; /**< (SPI Offset: 0x30) Enable or Disable the generation of interrupts by the rx_status register.  */
} Spi;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief SPI hardware registers */
typedef struct {  /* SPI Master/Slave Controller */
  __O  SPI_TRANSMIT_DATA_Type         TRANSMIT_DATA;  /**< Offset: 0x00 ( /W   8) Writes one byte to SPI Transmit Data FIFO.  */
       RoReg8                         Reserved1[0x3];
  __I  SPI_RECEIVE_DATA_Type          RECEIVE_DATA;   /**< Offset: 0x04 (R/    8) Read one byte from SPI Receive Data FIFO.  */
       RoReg8                         Reserved2[0x3];
  __I  SPI_TRANSMIT_STATUS_Type       TRANSMIT_STATUS; /**< Offset: 0x08 (R/    8) Status of the SPI transmitter. Each field can generate an interrupt if corresponding bit in  the Tx interrupt mask register is set.  */
       RoReg8                         Reserved3[0x3];
  __I  SPI_RECEIVE_STATUS_Type        RECEIVE_STATUS; /**< Offset: 0x0C (R/    8) Status of the SPI receiver. Each field can generate an interrupt if corresponding bit in  the Rx interrupt mask register is set.  */
       RoReg8                         Reserved4[0x3];
  __IO SPI_CLOCK_SOURCE_SELECT_Type   CLOCK_SOURCE_SELECT; /**< Offset: 0x10 (R/W   8) Clock Source Select */
       RoReg8                         Reserved5[0x3];
  __IO SPI_CLK_DIVIDER_Type           SPI_CLK_DIVIDER; /**< Offset: 0x14 (R/W  16) Register sets the divide ratio used to generate the sck clock from the module's input clock.  */
       RoReg8                         Reserved6[0x2];
  __IO SPI_MODULE_ENABLE_Type         SPI_MODULE_ENABLE; /**< Offset: 0x18 (R/W   8) SPI Enable */
       RoReg8                         Reserved7[0x3];
  __IO SPI_MASTER_MODE_Type           SPI_MASTER_MODE; /**< Offset: 0x1C (R/W   8) SPI Master/Slave Mode. When clear, SPI is in Slave Mode.  */
       RoReg8                         Reserved8[0x3];
  __IO SPI_FAULT_ENABLE_Type          SPI_FAULT_ENABLE; /**< Offset: 0x20 (R/W   8) SPI Fault Detection Mode. If set, SPI bus contention will be detected, and the fault  bit in the rx_status register will be set, forcing the SPI Module into idle state.  When a fault is detected, the current SPI transaction is abandoned and the interface switches  to slave mode in the wait state.   */
       RoReg8                         Reserved9[0x3];
  __IO SPI_CONFIGURATION_Type         SPI_CONFIGURATION; /**< Offset: 0x24 (R/W   8) SPI Operation Configuration Register. This register should not be modified while SPI bus is active,  otherwise the SPI Module state shall not be guaranteed.  */
       RoReg8                         Reserved10[0x3];
  __I  SPI_BUS_STATUS_Type            SPI_BUS_STATUS; /**< Offset: 0x28 (R/    8) Status of SPI bus.  */
       RoReg8                         Reserved11[0x3];
  __IO SPI_TX_INTERRUPT_MASK_Type     TX_INTERRUPT_MASK; /**< Offset: 0x2C (R/W   8) Enable or Disable the generation of interrupts by the tx_status register.  */
       RoReg8                         Reserved12[0x3];
  __IO SPI_RX_INTERRUPT_MASK_Type     RX_INTERRUPT_MASK; /**< Offset: 0x30 (R/W   8) Enable or Disable the generation of interrupts by the rx_status register.  */
} Spi;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_SPI_COMPONENT_ */
