/**
 * \file
 *
 * \brief Component description for SPI_FLASH
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

#ifndef _SAMB11_SPI_FLASH_COMPONENT_
#define _SAMB11_SPI_FLASH_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR SPI_FLASH */
/* ========================================================================== */
/** \addtogroup SAMB11_SPI_FLASH SPI Flash Controller 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define SPI_FLASH_SF1234
#define REV_SPI_FLASH                    0x100

/* -------- SPI_FLASH_MODE_CTRL : (SPI_FLASH Offset: 0x00) (R/W 8) SPI Flash Mode Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  MODE:2;                    /**< bit:   0..1  SPI Modes                                */
    uint8_t  BYPASS_CS_PRE:1;           /**< bit:      2  Bypass CS PRE state                      */
    uint8_t  BYPASS_CS_POST:1;          /**< bit:      3  Bypass CS POST state                     */
    uint8_t  :3;                        /**< bit:   4..6  Reserved */
    uint8_t  MODE_SELECT:1;             /**< bit:      7  Set to 1 to use external bits for mode   */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_FLASH_MODE_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_FLASH_MODE_CTRL_OFFSET          0x00                                          /**<  (SPI_FLASH_MODE_CTRL) SPI Flash Mode Control  Offset */
#define SPI_FLASH_MODE_CTRL_RESETVALUE      0x00u                                         /**<  (SPI_FLASH_MODE_CTRL) SPI Flash Mode Control  Reset Value */

#define SPI_FLASH_MODE_CTRL_MODE_Pos        0                                              /**< (SPI_FLASH_MODE_CTRL) SPI Modes Position */
#define SPI_FLASH_MODE_CTRL_MODE_Msk        (0x3u << SPI_FLASH_MODE_CTRL_MODE_Pos)         /**< (SPI_FLASH_MODE_CTRL) SPI Modes Mask */
#define SPI_FLASH_MODE_CTRL_MODE(value)     (SPI_FLASH_MODE_CTRL_MODE_Msk & ((value) << SPI_FLASH_MODE_CTRL_MODE_Pos))
#define   SPI_FLASH_MODE_CTRL_MODE_0_Val    0x0u                                           /**< (SPI_FLASH_MODE_CTRL) Mode 0  */
#define   SPI_FLASH_MODE_CTRL_MODE_1_Val    0x1u                                           /**< (SPI_FLASH_MODE_CTRL) Mode 1  */
#define   SPI_FLASH_MODE_CTRL_MODE_2_Val    0x2u                                           /**< (SPI_FLASH_MODE_CTRL) Mode 2  */
#define   SPI_FLASH_MODE_CTRL_MODE_3_Val    0x3u                                           /**< (SPI_FLASH_MODE_CTRL) Mode 3  */
#define SPI_FLASH_MODE_CTRL_MODE_0          (SPI_FLASH_MODE_CTRL_MODE_0_Val << SPI_FLASH_MODE_CTRL_MODE_Pos)  /**< (SPI_FLASH_MODE_CTRL) Mode 0 Position  */
#define SPI_FLASH_MODE_CTRL_MODE_1          (SPI_FLASH_MODE_CTRL_MODE_1_Val << SPI_FLASH_MODE_CTRL_MODE_Pos)  /**< (SPI_FLASH_MODE_CTRL) Mode 1 Position  */
#define SPI_FLASH_MODE_CTRL_MODE_2          (SPI_FLASH_MODE_CTRL_MODE_2_Val << SPI_FLASH_MODE_CTRL_MODE_Pos)  /**< (SPI_FLASH_MODE_CTRL) Mode 2 Position  */
#define SPI_FLASH_MODE_CTRL_MODE_3          (SPI_FLASH_MODE_CTRL_MODE_3_Val << SPI_FLASH_MODE_CTRL_MODE_Pos)  /**< (SPI_FLASH_MODE_CTRL) Mode 3 Position  */
#define SPI_FLASH_MODE_CTRL_BYPASS_CS_PRE_Pos 2                                              /**< (SPI_FLASH_MODE_CTRL) Bypass CS PRE state Position */
#define SPI_FLASH_MODE_CTRL_BYPASS_CS_PRE_Msk (0x1u << SPI_FLASH_MODE_CTRL_BYPASS_CS_PRE_Pos)  /**< (SPI_FLASH_MODE_CTRL) Bypass CS PRE state Mask */
#define SPI_FLASH_MODE_CTRL_BYPASS_CS_PRE   SPI_FLASH_MODE_CTRL_BYPASS_CS_PRE_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_MODE_CTRL_BYPASS_CS_PRE_Msk instead */
#define SPI_FLASH_MODE_CTRL_BYPASS_CS_POST_Pos 3                                              /**< (SPI_FLASH_MODE_CTRL) Bypass CS POST state Position */
#define SPI_FLASH_MODE_CTRL_BYPASS_CS_POST_Msk (0x1u << SPI_FLASH_MODE_CTRL_BYPASS_CS_POST_Pos)  /**< (SPI_FLASH_MODE_CTRL) Bypass CS POST state Mask */
#define SPI_FLASH_MODE_CTRL_BYPASS_CS_POST  SPI_FLASH_MODE_CTRL_BYPASS_CS_POST_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_MODE_CTRL_BYPASS_CS_POST_Msk instead */
#define SPI_FLASH_MODE_CTRL_MODE_SELECT_Pos 7                                              /**< (SPI_FLASH_MODE_CTRL) Set to 1 to use external bits for mode Position */
#define SPI_FLASH_MODE_CTRL_MODE_SELECT_Msk (0x1u << SPI_FLASH_MODE_CTRL_MODE_SELECT_Pos)  /**< (SPI_FLASH_MODE_CTRL) Set to 1 to use external bits for mode Mask */
#define SPI_FLASH_MODE_CTRL_MODE_SELECT     SPI_FLASH_MODE_CTRL_MODE_SELECT_Msk            /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_MODE_CTRL_MODE_SELECT_Msk instead */
#define SPI_FLASH_MODE_CTRL_MASK            0x8Fu                                          /**< \deprecated (SPI_FLASH_MODE_CTRL) Register MASK  (Use SPI_FLASH_MODE_CTRL_Msk instead)  */
#define SPI_FLASH_MODE_CTRL_Msk             0x8Fu                                          /**< (SPI_FLASH_MODE_CTRL) Register Mask  */

/* -------- SPI_FLASH_TRANSACTION_CTRL : (SPI_FLASH Offset: 0x04) (R/W 32) Transaction Control (Cleared after each transaction completes) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CMD_COUNT:3;               /**< bit:   0..2  Number of bytes to be transferred or received */
    uint32_t :4;                        /**< bit:   3..6  Reserved */
    uint32_t FLASH_TRANS_START:1;       /**< bit:      7  Rising Edge Flast Transaction Start      */
    uint32_t WDATA_COUNT:24;            /**< bit:  8..31  Number of bytes to be programmed to flash */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SPI_FLASH_TRANSACTION_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_FLASH_TRANSACTION_CTRL_OFFSET   0x04                                          /**<  (SPI_FLASH_TRANSACTION_CTRL) Transaction Control (Cleared after each transaction completes)  Offset */
#define SPI_FLASH_TRANSACTION_CTRL_RESETVALUE 0x04u                                         /**<  (SPI_FLASH_TRANSACTION_CTRL) Transaction Control (Cleared after each transaction completes)  Reset Value */

#define SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT_Pos 0                                              /**< (SPI_FLASH_TRANSACTION_CTRL) Number of bytes to be transferred or received Position */
#define SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT_Msk (0x7u << SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT_Pos)  /**< (SPI_FLASH_TRANSACTION_CTRL) Number of bytes to be transferred or received Mask */
#define SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT(value) (SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT_Msk & ((value) << SPI_FLASH_TRANSACTION_CTRL_CMD_COUNT_Pos))
#define SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START_Pos 7                                              /**< (SPI_FLASH_TRANSACTION_CTRL) Rising Edge Flast Transaction Start Position */
#define SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START_Msk (0x1u << SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START_Pos)  /**< (SPI_FLASH_TRANSACTION_CTRL) Rising Edge Flast Transaction Start Mask */
#define SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_TRANSACTION_CTRL_FLASH_TRANS_START_Msk instead */
#define SPI_FLASH_TRANSACTION_CTRL_WDATA_COUNT_Pos 8                                              /**< (SPI_FLASH_TRANSACTION_CTRL) Number of bytes to be programmed to flash Position */
#define SPI_FLASH_TRANSACTION_CTRL_WDATA_COUNT_Msk (0xFFFFFFu << SPI_FLASH_TRANSACTION_CTRL_WDATA_COUNT_Pos)  /**< (SPI_FLASH_TRANSACTION_CTRL) Number of bytes to be programmed to flash Mask */
#define SPI_FLASH_TRANSACTION_CTRL_WDATA_COUNT(value) (SPI_FLASH_TRANSACTION_CTRL_WDATA_COUNT_Msk & ((value) << SPI_FLASH_TRANSACTION_CTRL_WDATA_COUNT_Pos))
#define SPI_FLASH_TRANSACTION_CTRL_MASK     0xFFFFFF87u                                    /**< \deprecated (SPI_FLASH_TRANSACTION_CTRL) Register MASK  (Use SPI_FLASH_TRANSACTION_CTRL_Msk instead)  */
#define SPI_FLASH_TRANSACTION_CTRL_Msk      0xFFFFFF87u                                    /**< (SPI_FLASH_TRANSACTION_CTRL) Register Mask  */

/* -------- SPI_FLASH_READ_CTRL : (SPI_FLASH Offset: 0x08) (R/W 32) Read Control (Cleared after each transaction completes) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RDATA_COUNT:24;            /**< bit:  0..23  Number of data bytes to be read from flash */
    uint32_t :8;                        /**< bit: 24..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SPI_FLASH_READ_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_FLASH_READ_CTRL_OFFSET          0x08                                          /**<  (SPI_FLASH_READ_CTRL) Read Control (Cleared after each transaction completes)  Offset */
#define SPI_FLASH_READ_CTRL_RESETVALUE      0x00u                                         /**<  (SPI_FLASH_READ_CTRL) Read Control (Cleared after each transaction completes)  Reset Value */

#define SPI_FLASH_READ_CTRL_RDATA_COUNT_Pos 0                                              /**< (SPI_FLASH_READ_CTRL) Number of data bytes to be read from flash Position */
#define SPI_FLASH_READ_CTRL_RDATA_COUNT_Msk (0xFFFFFFu << SPI_FLASH_READ_CTRL_RDATA_COUNT_Pos)  /**< (SPI_FLASH_READ_CTRL) Number of data bytes to be read from flash Mask */
#define SPI_FLASH_READ_CTRL_RDATA_COUNT(value) (SPI_FLASH_READ_CTRL_RDATA_COUNT_Msk & ((value) << SPI_FLASH_READ_CTRL_RDATA_COUNT_Pos))
#define SPI_FLASH_READ_CTRL_MASK            0xFFFFFFu                                      /**< \deprecated (SPI_FLASH_READ_CTRL) Register MASK  (Use SPI_FLASH_READ_CTRL_Msk instead)  */
#define SPI_FLASH_READ_CTRL_Msk             0xFFFFFFu                                      /**< (SPI_FLASH_READ_CTRL) Register Mask  */

/* -------- SPI_FLASH_CMD_BUFFER0 : (SPI_FLASH Offset: 0x0c) (R/W 32) Command Buffer 0 (Bytes 3 - 0) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CMD_BUFFER0:32;            /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SPI_FLASH_CMD_BUFFER0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_FLASH_CMD_BUFFER0_OFFSET        0x0C                                          /**<  (SPI_FLASH_CMD_BUFFER0) Command Buffer 0 (Bytes 3 - 0)  Offset */
#define SPI_FLASH_CMD_BUFFER0_RESETVALUE    0x03u                                         /**<  (SPI_FLASH_CMD_BUFFER0) Command Buffer 0 (Bytes 3 - 0)  Reset Value */

#define SPI_FLASH_CMD_BUFFER0_CMD_BUFFER0_Pos 0                                              /**< (SPI_FLASH_CMD_BUFFER0)  Position */
#define SPI_FLASH_CMD_BUFFER0_CMD_BUFFER0_Msk (0xFFFFFFFFu << SPI_FLASH_CMD_BUFFER0_CMD_BUFFER0_Pos)  /**< (SPI_FLASH_CMD_BUFFER0)  Mask */
#define SPI_FLASH_CMD_BUFFER0_CMD_BUFFER0(value) (SPI_FLASH_CMD_BUFFER0_CMD_BUFFER0_Msk & ((value) << SPI_FLASH_CMD_BUFFER0_CMD_BUFFER0_Pos))
#define SPI_FLASH_CMD_BUFFER0_MASK          0xFFFFFFFFu                                    /**< \deprecated (SPI_FLASH_CMD_BUFFER0) Register MASK  (Use SPI_FLASH_CMD_BUFFER0_Msk instead)  */
#define SPI_FLASH_CMD_BUFFER0_Msk           0xFFFFFFFFu                                    /**< (SPI_FLASH_CMD_BUFFER0) Register Mask  */

/* -------- SPI_FLASH_CMD_BUFFER1 : (SPI_FLASH Offset: 0x10) (R/W 32) Command Buffer 1 (Bytes 7 - 4) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CMD_BUFFER1:32;            /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SPI_FLASH_CMD_BUFFER1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_FLASH_CMD_BUFFER1_OFFSET        0x10                                          /**<  (SPI_FLASH_CMD_BUFFER1) Command Buffer 1 (Bytes 7 - 4)  Offset */
#define SPI_FLASH_CMD_BUFFER1_RESETVALUE    0x00u                                         /**<  (SPI_FLASH_CMD_BUFFER1) Command Buffer 1 (Bytes 7 - 4)  Reset Value */

#define SPI_FLASH_CMD_BUFFER1_CMD_BUFFER1_Pos 0                                              /**< (SPI_FLASH_CMD_BUFFER1)  Position */
#define SPI_FLASH_CMD_BUFFER1_CMD_BUFFER1_Msk (0xFFFFFFFFu << SPI_FLASH_CMD_BUFFER1_CMD_BUFFER1_Pos)  /**< (SPI_FLASH_CMD_BUFFER1)  Mask */
#define SPI_FLASH_CMD_BUFFER1_CMD_BUFFER1(value) (SPI_FLASH_CMD_BUFFER1_CMD_BUFFER1_Msk & ((value) << SPI_FLASH_CMD_BUFFER1_CMD_BUFFER1_Pos))
#define SPI_FLASH_CMD_BUFFER1_MASK          0xFFFFFFFFu                                    /**< \deprecated (SPI_FLASH_CMD_BUFFER1) Register MASK  (Use SPI_FLASH_CMD_BUFFER1_Msk instead)  */
#define SPI_FLASH_CMD_BUFFER1_Msk           0xFFFFFFFFu                                    /**< (SPI_FLASH_CMD_BUFFER1) Register Mask  */

/* -------- SPI_FLASH_DIRECTION : (SPI_FLASH Offset: 0x14) (R/W 8) Read/Write bit for Bytes 7 - 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  DIRECTION:8;               /**< bit:   0..7                                           */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_FLASH_DIRECTION_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_FLASH_DIRECTION_OFFSET          0x14                                          /**<  (SPI_FLASH_DIRECTION) Read/Write bit for Bytes 7 - 0  Offset */
#define SPI_FLASH_DIRECTION_RESETVALUE      0x0Fu                                         /**<  (SPI_FLASH_DIRECTION) Read/Write bit for Bytes 7 - 0  Reset Value */

#define SPI_FLASH_DIRECTION_DIRECTION_Pos   0                                              /**< (SPI_FLASH_DIRECTION)  Position */
#define SPI_FLASH_DIRECTION_DIRECTION_Msk   (0xFFu << SPI_FLASH_DIRECTION_DIRECTION_Pos)   /**< (SPI_FLASH_DIRECTION)  Mask */
#define SPI_FLASH_DIRECTION_DIRECTION(value) (SPI_FLASH_DIRECTION_DIRECTION_Msk & ((value) << SPI_FLASH_DIRECTION_DIRECTION_Pos))
#define SPI_FLASH_DIRECTION_MASK            0xFFu                                          /**< \deprecated (SPI_FLASH_DIRECTION) Register MASK  (Use SPI_FLASH_DIRECTION_Msk instead)  */
#define SPI_FLASH_DIRECTION_Msk             0xFFu                                          /**< (SPI_FLASH_DIRECTION) Register Mask  */

/* -------- SPI_FLASH_IRQ_STATUS : (SPI_FLASH Offset: 0x18) (/W 8) IRQ Status (Write 0 to bit to clear, Read clears interupts) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  FLASH_TRANS_DONE:1;        /**< bit:      0  Current Flash Transaction Done           */
    uint8_t  AHB_ERROR_RESPONSE:1;      /**< bit:      1  AHB Error Response                       */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} SPI_FLASH_IRQ_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_FLASH_IRQ_STATUS_OFFSET         0x18                                          /**<  (SPI_FLASH_IRQ_STATUS) IRQ Status (Write 0 to bit to clear, Read clears interupts)  Offset */
#define SPI_FLASH_IRQ_STATUS_RESETVALUE     0x00u                                         /**<  (SPI_FLASH_IRQ_STATUS) IRQ Status (Write 0 to bit to clear, Read clears interupts)  Reset Value */

#define SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE_Pos 0                                              /**< (SPI_FLASH_IRQ_STATUS) Current Flash Transaction Done Position */
#define SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE_Msk (0x1u << SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE_Pos)  /**< (SPI_FLASH_IRQ_STATUS) Current Flash Transaction Done Mask */
#define SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_IRQ_STATUS_FLASH_TRANS_DONE_Msk instead */
#define SPI_FLASH_IRQ_STATUS_AHB_ERROR_RESPONSE_Pos 1                                              /**< (SPI_FLASH_IRQ_STATUS) AHB Error Response Position */
#define SPI_FLASH_IRQ_STATUS_AHB_ERROR_RESPONSE_Msk (0x1u << SPI_FLASH_IRQ_STATUS_AHB_ERROR_RESPONSE_Pos)  /**< (SPI_FLASH_IRQ_STATUS) AHB Error Response Mask */
#define SPI_FLASH_IRQ_STATUS_AHB_ERROR_RESPONSE SPI_FLASH_IRQ_STATUS_AHB_ERROR_RESPONSE_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_IRQ_STATUS_AHB_ERROR_RESPONSE_Msk instead */
#define SPI_FLASH_IRQ_STATUS_MASK           0x03u                                          /**< \deprecated (SPI_FLASH_IRQ_STATUS) Register MASK  (Use SPI_FLASH_IRQ_STATUS_Msk instead)  */
#define SPI_FLASH_IRQ_STATUS_Msk            0x03u                                          /**< (SPI_FLASH_IRQ_STATUS) Register Mask  */

/* -------- SPI_FLASH_DMA_START_ADDRESS : (SPI_FLASH Offset: 0x1c) (R/W 32) DMA Starting Address -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t DMA_START_ADDRESS:32;      /**< bit:  0..31                                           */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} SPI_FLASH_DMA_START_ADDRESS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_FLASH_DMA_START_ADDRESS_OFFSET  0x1C                                          /**<  (SPI_FLASH_DMA_START_ADDRESS) DMA Starting Address  Offset */
#define SPI_FLASH_DMA_START_ADDRESS_RESETVALUE 0x00u                                         /**<  (SPI_FLASH_DMA_START_ADDRESS) DMA Starting Address  Reset Value */

#define SPI_FLASH_DMA_START_ADDRESS_DMA_START_ADDRESS_Pos 0                                              /**< (SPI_FLASH_DMA_START_ADDRESS)  Position */
#define SPI_FLASH_DMA_START_ADDRESS_DMA_START_ADDRESS_Msk (0xFFFFFFFFu << SPI_FLASH_DMA_START_ADDRESS_DMA_START_ADDRESS_Pos)  /**< (SPI_FLASH_DMA_START_ADDRESS)  Mask */
#define SPI_FLASH_DMA_START_ADDRESS_DMA_START_ADDRESS(value) (SPI_FLASH_DMA_START_ADDRESS_DMA_START_ADDRESS_Msk & ((value) << SPI_FLASH_DMA_START_ADDRESS_DMA_START_ADDRESS_Pos))
#define SPI_FLASH_DMA_START_ADDRESS_MASK    0xFFFFFFFFu                                    /**< \deprecated (SPI_FLASH_DMA_START_ADDRESS) Register MASK  (Use SPI_FLASH_DMA_START_ADDRESS_Msk instead)  */
#define SPI_FLASH_DMA_START_ADDRESS_Msk     0xFFFFFFFFu                                    /**< (SPI_FLASH_DMA_START_ADDRESS) Register Mask  */

/* -------- SPI_FLASH_CONFIG : (SPI_FLASH Offset: 0x20) (R/W 16) SPI Flash Configuration -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t ENDIANNESS:1;              /**< bit:      0  1 for Little Endian                      */
    uint16_t REVERSE_CMD_BUFFER:1;      /**< bit:      1  Reverse bits of every byte in cmd_buffer */
    uint16_t RDATA_REVERSE:1;           /**< bit:      2  Reverse bits of every data byte read from flash */
    uint16_t REVERSE_INCOMIND_DATA:1;   /**< bit:      3  Reverse bits of status registers read from flash */
    uint16_t SPI_INTERFACE_CONFIG_DEBUG:4;  /**< bit:   4..7  Debug only                               */
    uint16_t WDATA_REVERSE:1;           /**< bit:      8  Reverse bits of every data byte written to flash */
    uint16_t :7;                        /**< bit:  9..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} SPI_FLASH_CONFIG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_FLASH_CONFIG_OFFSET             0x20                                          /**<  (SPI_FLASH_CONFIG) SPI Flash Configuration  Offset */
#define SPI_FLASH_CONFIG_RESETVALUE         0x103u                                        /**<  (SPI_FLASH_CONFIG) SPI Flash Configuration  Reset Value */

#define SPI_FLASH_CONFIG_ENDIANNESS_Pos     0                                              /**< (SPI_FLASH_CONFIG) 1 for Little Endian Position */
#define SPI_FLASH_CONFIG_ENDIANNESS_Msk     (0x1u << SPI_FLASH_CONFIG_ENDIANNESS_Pos)      /**< (SPI_FLASH_CONFIG) 1 for Little Endian Mask */
#define SPI_FLASH_CONFIG_ENDIANNESS         SPI_FLASH_CONFIG_ENDIANNESS_Msk                /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_CONFIG_ENDIANNESS_Msk instead */
#define SPI_FLASH_CONFIG_REVERSE_CMD_BUFFER_Pos 1                                              /**< (SPI_FLASH_CONFIG) Reverse bits of every byte in cmd_buffer Position */
#define SPI_FLASH_CONFIG_REVERSE_CMD_BUFFER_Msk (0x1u << SPI_FLASH_CONFIG_REVERSE_CMD_BUFFER_Pos)  /**< (SPI_FLASH_CONFIG) Reverse bits of every byte in cmd_buffer Mask */
#define SPI_FLASH_CONFIG_REVERSE_CMD_BUFFER SPI_FLASH_CONFIG_REVERSE_CMD_BUFFER_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_CONFIG_REVERSE_CMD_BUFFER_Msk instead */
#define SPI_FLASH_CONFIG_RDATA_REVERSE_Pos  2                                              /**< (SPI_FLASH_CONFIG) Reverse bits of every data byte read from flash Position */
#define SPI_FLASH_CONFIG_RDATA_REVERSE_Msk  (0x1u << SPI_FLASH_CONFIG_RDATA_REVERSE_Pos)   /**< (SPI_FLASH_CONFIG) Reverse bits of every data byte read from flash Mask */
#define SPI_FLASH_CONFIG_RDATA_REVERSE      SPI_FLASH_CONFIG_RDATA_REVERSE_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_CONFIG_RDATA_REVERSE_Msk instead */
#define SPI_FLASH_CONFIG_REVERSE_INCOMIND_DATA_Pos 3                                              /**< (SPI_FLASH_CONFIG) Reverse bits of status registers read from flash Position */
#define SPI_FLASH_CONFIG_REVERSE_INCOMIND_DATA_Msk (0x1u << SPI_FLASH_CONFIG_REVERSE_INCOMIND_DATA_Pos)  /**< (SPI_FLASH_CONFIG) Reverse bits of status registers read from flash Mask */
#define SPI_FLASH_CONFIG_REVERSE_INCOMIND_DATA SPI_FLASH_CONFIG_REVERSE_INCOMIND_DATA_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_CONFIG_REVERSE_INCOMIND_DATA_Msk instead */
#define SPI_FLASH_CONFIG_SPI_INTERFACE_CONFIG_DEBUG_Pos 4                                              /**< (SPI_FLASH_CONFIG) Debug only Position */
#define SPI_FLASH_CONFIG_SPI_INTERFACE_CONFIG_DEBUG_Msk (0xFu << SPI_FLASH_CONFIG_SPI_INTERFACE_CONFIG_DEBUG_Pos)  /**< (SPI_FLASH_CONFIG) Debug only Mask */
#define SPI_FLASH_CONFIG_SPI_INTERFACE_CONFIG_DEBUG(value) (SPI_FLASH_CONFIG_SPI_INTERFACE_CONFIG_DEBUG_Msk & ((value) << SPI_FLASH_CONFIG_SPI_INTERFACE_CONFIG_DEBUG_Pos))
#define SPI_FLASH_CONFIG_WDATA_REVERSE_Pos  8                                              /**< (SPI_FLASH_CONFIG) Reverse bits of every data byte written to flash Position */
#define SPI_FLASH_CONFIG_WDATA_REVERSE_Msk  (0x1u << SPI_FLASH_CONFIG_WDATA_REVERSE_Pos)   /**< (SPI_FLASH_CONFIG) Reverse bits of every data byte written to flash Mask */
#define SPI_FLASH_CONFIG_WDATA_REVERSE      SPI_FLASH_CONFIG_WDATA_REVERSE_Msk             /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_CONFIG_WDATA_REVERSE_Msk instead */
#define SPI_FLASH_CONFIG_MASK               0x1FFu                                         /**< \deprecated (SPI_FLASH_CONFIG) Register MASK  (Use SPI_FLASH_CONFIG_Msk instead)  */
#define SPI_FLASH_CONFIG_Msk                0x1FFu                                         /**< (SPI_FLASH_CONFIG) Register Mask  */

/* -------- SPI_FLASH_TX_CONTROL : (SPI_FLASH Offset: 0x24) (R/W 16) TX Control -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t DRIVE_0_ON_TX:1;           /**< bit:      0  Drive 0 on TX while reading              */
    uint16_t DRIVE_1_ON_TX:1;           /**< bit:      1  Drive 1 on TX while reading              */
    uint16_t TOGGLE_ON_TX:1;            /**< bit:      2  Toggle TX while reading                  */
    uint16_t DUMMY_ON_TX:1;             /**< bit:      3  Send dummy_byte while reading            */
    uint16_t :4;                        /**< bit:   4..7  Reserved */
    uint16_t DUMMY_BYTE:8;              /**< bit:  8..15  Byte to be sent for dummy_on_tx option   */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} SPI_FLASH_TX_CONTROL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_FLASH_TX_CONTROL_OFFSET         0x24                                          /**<  (SPI_FLASH_TX_CONTROL) TX Control  Offset */
#define SPI_FLASH_TX_CONTROL_RESETVALUE     0x00u                                         /**<  (SPI_FLASH_TX_CONTROL) TX Control  Reset Value */

#define SPI_FLASH_TX_CONTROL_DRIVE_0_ON_TX_Pos 0                                              /**< (SPI_FLASH_TX_CONTROL) Drive 0 on TX while reading Position */
#define SPI_FLASH_TX_CONTROL_DRIVE_0_ON_TX_Msk (0x1u << SPI_FLASH_TX_CONTROL_DRIVE_0_ON_TX_Pos)  /**< (SPI_FLASH_TX_CONTROL) Drive 0 on TX while reading Mask */
#define SPI_FLASH_TX_CONTROL_DRIVE_0_ON_TX  SPI_FLASH_TX_CONTROL_DRIVE_0_ON_TX_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_TX_CONTROL_DRIVE_0_ON_TX_Msk instead */
#define SPI_FLASH_TX_CONTROL_DRIVE_1_ON_TX_Pos 1                                              /**< (SPI_FLASH_TX_CONTROL) Drive 1 on TX while reading Position */
#define SPI_FLASH_TX_CONTROL_DRIVE_1_ON_TX_Msk (0x1u << SPI_FLASH_TX_CONTROL_DRIVE_1_ON_TX_Pos)  /**< (SPI_FLASH_TX_CONTROL) Drive 1 on TX while reading Mask */
#define SPI_FLASH_TX_CONTROL_DRIVE_1_ON_TX  SPI_FLASH_TX_CONTROL_DRIVE_1_ON_TX_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_TX_CONTROL_DRIVE_1_ON_TX_Msk instead */
#define SPI_FLASH_TX_CONTROL_TOGGLE_ON_TX_Pos 2                                              /**< (SPI_FLASH_TX_CONTROL) Toggle TX while reading Position */
#define SPI_FLASH_TX_CONTROL_TOGGLE_ON_TX_Msk (0x1u << SPI_FLASH_TX_CONTROL_TOGGLE_ON_TX_Pos)  /**< (SPI_FLASH_TX_CONTROL) Toggle TX while reading Mask */
#define SPI_FLASH_TX_CONTROL_TOGGLE_ON_TX   SPI_FLASH_TX_CONTROL_TOGGLE_ON_TX_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_TX_CONTROL_TOGGLE_ON_TX_Msk instead */
#define SPI_FLASH_TX_CONTROL_DUMMY_ON_TX_Pos 3                                              /**< (SPI_FLASH_TX_CONTROL) Send dummy_byte while reading Position */
#define SPI_FLASH_TX_CONTROL_DUMMY_ON_TX_Msk (0x1u << SPI_FLASH_TX_CONTROL_DUMMY_ON_TX_Pos)  /**< (SPI_FLASH_TX_CONTROL) Send dummy_byte while reading Mask */
#define SPI_FLASH_TX_CONTROL_DUMMY_ON_TX    SPI_FLASH_TX_CONTROL_DUMMY_ON_TX_Msk           /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_TX_CONTROL_DUMMY_ON_TX_Msk instead */
#define SPI_FLASH_TX_CONTROL_DUMMY_BYTE_Pos 8                                              /**< (SPI_FLASH_TX_CONTROL) Byte to be sent for dummy_on_tx option Position */
#define SPI_FLASH_TX_CONTROL_DUMMY_BYTE_Msk (0xFFu << SPI_FLASH_TX_CONTROL_DUMMY_BYTE_Pos)  /**< (SPI_FLASH_TX_CONTROL) Byte to be sent for dummy_on_tx option Mask */
#define SPI_FLASH_TX_CONTROL_DUMMY_BYTE(value) (SPI_FLASH_TX_CONTROL_DUMMY_BYTE_Msk & ((value) << SPI_FLASH_TX_CONTROL_DUMMY_BYTE_Pos))
#define SPI_FLASH_TX_CONTROL_MASK           0xFF0Fu                                        /**< \deprecated (SPI_FLASH_TX_CONTROL) Register MASK  (Use SPI_FLASH_TX_CONTROL_Msk instead)  */
#define SPI_FLASH_TX_CONTROL_Msk            0xFF0Fu                                        /**< (SPI_FLASH_TX_CONTROL) Register Mask  */

/* -------- SPI_FLASH_STATUS : (SPI_FLASH Offset: 0x28) (R/ 16) Misc Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t AHB_MASTER_STATE:2;        /**< bit:   0..1  AHB Master State                         */
    uint16_t :2;                        /**< bit:   2..3  Reserved */
    uint16_t FIFO_CTRL_STATE:3;         /**< bit:   4..6  FIFO Control State                       */
    uint16_t :1;                        /**< bit:      7  Reserved */
    uint16_t SPI_MASTER_STATE:3;        /**< bit:  8..10  SPI Master State                         */
    uint16_t :1;                        /**< bit:     11  Reserved */
    uint16_t SPI_MASTER_CSN:1;          /**< bit:     12  Inverted version of the SPI Master Chip Select */
    uint16_t :3;                        /**< bit: 13..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} SPI_FLASH_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define SPI_FLASH_STATUS_OFFSET             0x28                                          /**<  (SPI_FLASH_STATUS) Misc Status  Offset */
#define SPI_FLASH_STATUS_RESETVALUE         0x00u                                         /**<  (SPI_FLASH_STATUS) Misc Status  Reset Value */

#define SPI_FLASH_STATUS_AHB_MASTER_STATE_Pos 0                                              /**< (SPI_FLASH_STATUS) AHB Master State Position */
#define SPI_FLASH_STATUS_AHB_MASTER_STATE_Msk (0x3u << SPI_FLASH_STATUS_AHB_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) AHB Master State Mask */
#define SPI_FLASH_STATUS_AHB_MASTER_STATE(value) (SPI_FLASH_STATUS_AHB_MASTER_STATE_Msk & ((value) << SPI_FLASH_STATUS_AHB_MASTER_STATE_Pos))
#define   SPI_FLASH_STATUS_AHB_MASTER_STATE_0_Val 0x0u                                           /**< (SPI_FLASH_STATUS) IDLE  */
#define   SPI_FLASH_STATUS_AHB_MASTER_STATE_1_Val 0x1u                                           /**< (SPI_FLASH_STATUS) WAIT_GRANT  */
#define   SPI_FLASH_STATUS_AHB_MASTER_STATE_2_Val 0x2u                                           /**< (SPI_FLASH_STATUS) ADDR_PHASE  */
#define   SPI_FLASH_STATUS_AHB_MASTER_STATE_3_Val 0x3u                                           /**< (SPI_FLASH_STATUS) DATA_PHASE  */
#define SPI_FLASH_STATUS_AHB_MASTER_STATE_0 (SPI_FLASH_STATUS_AHB_MASTER_STATE_0_Val << SPI_FLASH_STATUS_AHB_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) IDLE Position  */
#define SPI_FLASH_STATUS_AHB_MASTER_STATE_1 (SPI_FLASH_STATUS_AHB_MASTER_STATE_1_Val << SPI_FLASH_STATUS_AHB_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) WAIT_GRANT Position  */
#define SPI_FLASH_STATUS_AHB_MASTER_STATE_2 (SPI_FLASH_STATUS_AHB_MASTER_STATE_2_Val << SPI_FLASH_STATUS_AHB_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) ADDR_PHASE Position  */
#define SPI_FLASH_STATUS_AHB_MASTER_STATE_3 (SPI_FLASH_STATUS_AHB_MASTER_STATE_3_Val << SPI_FLASH_STATUS_AHB_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) DATA_PHASE Position  */
#define SPI_FLASH_STATUS_FIFO_CTRL_STATE_Pos 4                                              /**< (SPI_FLASH_STATUS) FIFO Control State Position */
#define SPI_FLASH_STATUS_FIFO_CTRL_STATE_Msk (0x7u << SPI_FLASH_STATUS_FIFO_CTRL_STATE_Pos)  /**< (SPI_FLASH_STATUS) FIFO Control State Mask */
#define SPI_FLASH_STATUS_FIFO_CTRL_STATE(value) (SPI_FLASH_STATUS_FIFO_CTRL_STATE_Msk & ((value) << SPI_FLASH_STATUS_FIFO_CTRL_STATE_Pos))
#define   SPI_FLASH_STATUS_FIFO_CTRL_STATE_0_Val 0x0u                                           /**< (SPI_FLASH_STATUS) FLASH_IDLE  */
#define   SPI_FLASH_STATUS_FIFO_CTRL_STATE_1_Val 0x1u                                           /**< (SPI_FLASH_STATUS) GET_DATA_FROM_FLASH  */
#define   SPI_FLASH_STATUS_FIFO_CTRL_STATE_2_Val 0x2u                                           /**< (SPI_FLASH_STATUS) WRITE_DATA_TO_AHB  */
#define   SPI_FLASH_STATUS_FIFO_CTRL_STATE_3_Val 0x3u                                           /**< (SPI_FLASH_STATUS) GET_DATA_FROM_AHB  */
#define   SPI_FLASH_STATUS_FIFO_CTRL_STATE_4_Val 0x4u                                           /**< (SPI_FLASH_STATUS) WRITE_DATA_TO_FLASH  */
#define SPI_FLASH_STATUS_FIFO_CTRL_STATE_0  (SPI_FLASH_STATUS_FIFO_CTRL_STATE_0_Val << SPI_FLASH_STATUS_FIFO_CTRL_STATE_Pos)  /**< (SPI_FLASH_STATUS) FLASH_IDLE Position  */
#define SPI_FLASH_STATUS_FIFO_CTRL_STATE_1  (SPI_FLASH_STATUS_FIFO_CTRL_STATE_1_Val << SPI_FLASH_STATUS_FIFO_CTRL_STATE_Pos)  /**< (SPI_FLASH_STATUS) GET_DATA_FROM_FLASH Position  */
#define SPI_FLASH_STATUS_FIFO_CTRL_STATE_2  (SPI_FLASH_STATUS_FIFO_CTRL_STATE_2_Val << SPI_FLASH_STATUS_FIFO_CTRL_STATE_Pos)  /**< (SPI_FLASH_STATUS) WRITE_DATA_TO_AHB Position  */
#define SPI_FLASH_STATUS_FIFO_CTRL_STATE_3  (SPI_FLASH_STATUS_FIFO_CTRL_STATE_3_Val << SPI_FLASH_STATUS_FIFO_CTRL_STATE_Pos)  /**< (SPI_FLASH_STATUS) GET_DATA_FROM_AHB Position  */
#define SPI_FLASH_STATUS_FIFO_CTRL_STATE_4  (SPI_FLASH_STATUS_FIFO_CTRL_STATE_4_Val << SPI_FLASH_STATUS_FIFO_CTRL_STATE_Pos)  /**< (SPI_FLASH_STATUS) WRITE_DATA_TO_FLASH Position  */
#define SPI_FLASH_STATUS_SPI_MASTER_STATE_Pos 8                                              /**< (SPI_FLASH_STATUS) SPI Master State Position */
#define SPI_FLASH_STATUS_SPI_MASTER_STATE_Msk (0x7u << SPI_FLASH_STATUS_SPI_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) SPI Master State Mask */
#define SPI_FLASH_STATUS_SPI_MASTER_STATE(value) (SPI_FLASH_STATUS_SPI_MASTER_STATE_Msk & ((value) << SPI_FLASH_STATUS_SPI_MASTER_STATE_Pos))
#define   SPI_FLASH_STATUS_SPI_MASTER_STATE_0_Val 0x0u                                           /**< (SPI_FLASH_STATUS) IDLE  */
#define   SPI_FLASH_STATUS_SPI_MASTER_STATE_1_Val 0x1u                                           /**< (SPI_FLASH_STATUS) READ  */
#define   SPI_FLASH_STATUS_SPI_MASTER_STATE_2_Val 0x2u                                           /**< (SPI_FLASH_STATUS) WRITE  */
#define   SPI_FLASH_STATUS_SPI_MASTER_STATE_3_Val 0x3u                                           /**< (SPI_FLASH_STATUS) READ_FLASH  */
#define   SPI_FLASH_STATUS_SPI_MASTER_STATE_4_Val 0x4u                                           /**< (SPI_FLASH_STATUS) WRITE_FLASH  */
#define   SPI_FLASH_STATUS_SPI_MASTER_STATE_5_Val 0x5u                                           /**< (SPI_FLASH_STATUS) PRE_ACTION  */
#define   SPI_FLASH_STATUS_SPI_MASTER_STATE_6_Val 0x6u                                           /**< (SPI_FLASH_STATUS) POST_ACTION  */
#define   SPI_FLASH_STATUS_SPI_MASTER_STATE_7_Val 0x7u                                           /**< (SPI_FLASH_STATUS) WAIT_AHB  */
#define SPI_FLASH_STATUS_SPI_MASTER_STATE_0 (SPI_FLASH_STATUS_SPI_MASTER_STATE_0_Val << SPI_FLASH_STATUS_SPI_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) IDLE Position  */
#define SPI_FLASH_STATUS_SPI_MASTER_STATE_1 (SPI_FLASH_STATUS_SPI_MASTER_STATE_1_Val << SPI_FLASH_STATUS_SPI_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) READ Position  */
#define SPI_FLASH_STATUS_SPI_MASTER_STATE_2 (SPI_FLASH_STATUS_SPI_MASTER_STATE_2_Val << SPI_FLASH_STATUS_SPI_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) WRITE Position  */
#define SPI_FLASH_STATUS_SPI_MASTER_STATE_3 (SPI_FLASH_STATUS_SPI_MASTER_STATE_3_Val << SPI_FLASH_STATUS_SPI_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) READ_FLASH Position  */
#define SPI_FLASH_STATUS_SPI_MASTER_STATE_4 (SPI_FLASH_STATUS_SPI_MASTER_STATE_4_Val << SPI_FLASH_STATUS_SPI_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) WRITE_FLASH Position  */
#define SPI_FLASH_STATUS_SPI_MASTER_STATE_5 (SPI_FLASH_STATUS_SPI_MASTER_STATE_5_Val << SPI_FLASH_STATUS_SPI_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) PRE_ACTION Position  */
#define SPI_FLASH_STATUS_SPI_MASTER_STATE_6 (SPI_FLASH_STATUS_SPI_MASTER_STATE_6_Val << SPI_FLASH_STATUS_SPI_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) POST_ACTION Position  */
#define SPI_FLASH_STATUS_SPI_MASTER_STATE_7 (SPI_FLASH_STATUS_SPI_MASTER_STATE_7_Val << SPI_FLASH_STATUS_SPI_MASTER_STATE_Pos)  /**< (SPI_FLASH_STATUS) WAIT_AHB Position  */
#define SPI_FLASH_STATUS_SPI_MASTER_CSN_Pos 12                                             /**< (SPI_FLASH_STATUS) Inverted version of the SPI Master Chip Select Position */
#define SPI_FLASH_STATUS_SPI_MASTER_CSN_Msk (0x1u << SPI_FLASH_STATUS_SPI_MASTER_CSN_Pos)  /**< (SPI_FLASH_STATUS) Inverted version of the SPI Master Chip Select Mask */
#define SPI_FLASH_STATUS_SPI_MASTER_CSN     SPI_FLASH_STATUS_SPI_MASTER_CSN_Msk            /**< \deprecated Old style mask definition for 1 bit bitfield. Use SPI_FLASH_STATUS_SPI_MASTER_CSN_Msk instead */
#define SPI_FLASH_STATUS_MASK               0x1773u                                        /**< \deprecated (SPI_FLASH_STATUS) Register MASK  (Use SPI_FLASH_STATUS_Msk instead)  */
#define SPI_FLASH_STATUS_Msk                0x1773u                                        /**< (SPI_FLASH_STATUS) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief SPI_FLASH hardware registers */
typedef struct {  /* SPI Flash Controller */
  RwReg8  MODE_CTRL;      /**< (SPI_FLASH Offset: 0x00) SPI Flash Mode Control */
  __I  uint8_t  Reserved1[3];
  RwReg   TRANSACTION_CTRL; /**< (SPI_FLASH Offset: 0x04) Transaction Control (Cleared after each transaction completes) */
  RwReg   READ_CTRL;      /**< (SPI_FLASH Offset: 0x08) Read Control (Cleared after each transaction completes) */
  RwReg   CMD_BUFFER0;    /**< (SPI_FLASH Offset: 0x0C) Command Buffer 0 (Bytes 3 - 0) */
  RwReg   CMD_BUFFER1;    /**< (SPI_FLASH Offset: 0x10) Command Buffer 1 (Bytes 7 - 4) */
  RwReg8  DIRECTION;      /**< (SPI_FLASH Offset: 0x14) Read/Write bit for Bytes 7 - 0 */
  __I  uint8_t  Reserved2[3];
  WoReg8  IRQ_STATUS;     /**< (SPI_FLASH Offset: 0x18) IRQ Status (Write 0 to bit to clear, Read clears interupts) */
  __I  uint8_t  Reserved3[3];
  RwReg   DMA_START_ADDRESS; /**< (SPI_FLASH Offset: 0x1C) DMA Starting Address */
  RwReg16 CONFIG;         /**< (SPI_FLASH Offset: 0x20) SPI Flash Configuration */
  __I  uint8_t  Reserved4[2];
  RwReg16 TX_CONTROL;     /**< (SPI_FLASH Offset: 0x24) TX Control */
  __I  uint8_t  Reserved5[2];
  RoReg16 STATUS;         /**< (SPI_FLASH Offset: 0x28) Misc Status */
} SpiFlash;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief SPI_FLASH hardware registers */
typedef struct {  /* SPI Flash Controller */
  __IO SPI_FLASH_MODE_CTRL_Type       MODE_CTRL;      /**< Offset: 0x00 (R/W   8) SPI Flash Mode Control */
       RoReg8                         Reserved1[0x3];
  __IO SPI_FLASH_TRANSACTION_CTRL_Type TRANSACTION_CTRL; /**< Offset: 0x04 (R/W  32) Transaction Control (Cleared after each transaction completes) */
  __IO SPI_FLASH_READ_CTRL_Type       READ_CTRL;      /**< Offset: 0x08 (R/W  32) Read Control (Cleared after each transaction completes) */
  __IO SPI_FLASH_CMD_BUFFER0_Type     CMD_BUFFER0;    /**< Offset: 0x0C (R/W  32) Command Buffer 0 (Bytes 3 - 0) */
  __IO SPI_FLASH_CMD_BUFFER1_Type     CMD_BUFFER1;    /**< Offset: 0x10 (R/W  32) Command Buffer 1 (Bytes 7 - 4) */
  __IO SPI_FLASH_DIRECTION_Type       DIRECTION;      /**< Offset: 0x14 (R/W   8) Read/Write bit for Bytes 7 - 0 */
       RoReg8                         Reserved2[0x3];
  __O  SPI_FLASH_IRQ_STATUS_Type      IRQ_STATUS;     /**< Offset: 0x18 ( /W   8) IRQ Status (Write 0 to bit to clear, Read clears interupts) */
       RoReg8                         Reserved3[0x3];
  __IO SPI_FLASH_DMA_START_ADDRESS_Type DMA_START_ADDRESS; /**< Offset: 0x1C (R/W  32) DMA Starting Address */
  __IO SPI_FLASH_CONFIG_Type          CONFIG;         /**< Offset: 0x20 (R/W  16) SPI Flash Configuration */
       RoReg8                         Reserved4[0x2];
  __IO SPI_FLASH_TX_CONTROL_Type      TX_CONTROL;     /**< Offset: 0x24 (R/W  16) TX Control */
       RoReg8                         Reserved5[0x2];
  __I  SPI_FLASH_STATUS_Type          STATUS;         /**< Offset: 0x28 (R/   16) Misc Status */
} SpiFlash;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_SPI_FLASH_COMPONENT_ */
