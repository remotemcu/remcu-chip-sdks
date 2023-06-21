/**
 * \file
 *
 * \brief Component description for PROV_DMA_CTRL
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

#ifndef _SAMB11_PROV_DMA_CTRL_COMPONENT_
#define _SAMB11_PROV_DMA_CTRL_COMPONENT_

/* ========================================================================== */
/**  SOFTWARE API DEFINITION FOR PROV_DMA_CTRL */
/* ========================================================================== */
/** \addtogroup SAMB11_PROV_DMA_CTRL 4 Channel DMA Controller 
 *  @{
 */

#ifndef COMPONENT_TYPEDEF_STYLE
  #define COMPONENT_TYPEDEF_STYLE 'N'  /**< Defines default style of typedefs for the component header files ('R' = RFO, 'N' = NTO*/
#endif

#define PROV_DMA_CTRL_PDC1234
#define REV_PROV_DMA_CTRL                0x100

/* -------- PROV_DMA_CTRL_CH0_CMD_REG0 : (PROV_DMA_CTRL Offset: 0x00) (R/W 32) Channel 0 First Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_START_ADDR:32;          /**< bit:  0..31  Start Address of Read Buffer             */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_CMD_REG0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_CMD_REG0_OFFSET   0x00                                          /**<  (PROV_DMA_CTRL_CH0_CMD_REG0) Channel 0 First Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH0_CMD_REG0_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_CMD_REG0) Channel 0 First Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH0_CMD_REG0_RD_START_ADDR_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_CMD_REG0) Start Address of Read Buffer Position */
#define PROV_DMA_CTRL_CH0_CMD_REG0_RD_START_ADDR_Msk (0xFFFFFFFFu << PROV_DMA_CTRL_CH0_CMD_REG0_RD_START_ADDR_Pos)  /**< (PROV_DMA_CTRL_CH0_CMD_REG0) Start Address of Read Buffer Mask */
#define PROV_DMA_CTRL_CH0_CMD_REG0_RD_START_ADDR(value) (PROV_DMA_CTRL_CH0_CMD_REG0_RD_START_ADDR_Msk & ((value) << PROV_DMA_CTRL_CH0_CMD_REG0_RD_START_ADDR_Pos))
#define PROV_DMA_CTRL_CH0_CMD_REG0_MASK     0xFFFFFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH0_CMD_REG0) Register MASK  (Use PROV_DMA_CTRL_CH0_CMD_REG0_Msk instead)  */
#define PROV_DMA_CTRL_CH0_CMD_REG0_Msk      0xFFFFFFFFu                                    /**< (PROV_DMA_CTRL_CH0_CMD_REG0) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_CMD_REG1 : (PROV_DMA_CTRL Offset: 0x04) (R/W 32) Channel 0 Second Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t WR_START_ADDR:32;          /**< bit:  0..31  Start Address of Write Buffer            */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_CMD_REG1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_CMD_REG1_OFFSET   0x04                                          /**<  (PROV_DMA_CTRL_CH0_CMD_REG1) Channel 0 Second Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH0_CMD_REG1_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_CMD_REG1) Channel 0 Second Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH0_CMD_REG1_WR_START_ADDR_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_CMD_REG1) Start Address of Write Buffer Position */
#define PROV_DMA_CTRL_CH0_CMD_REG1_WR_START_ADDR_Msk (0xFFFFFFFFu << PROV_DMA_CTRL_CH0_CMD_REG1_WR_START_ADDR_Pos)  /**< (PROV_DMA_CTRL_CH0_CMD_REG1) Start Address of Write Buffer Mask */
#define PROV_DMA_CTRL_CH0_CMD_REG1_WR_START_ADDR(value) (PROV_DMA_CTRL_CH0_CMD_REG1_WR_START_ADDR_Msk & ((value) << PROV_DMA_CTRL_CH0_CMD_REG1_WR_START_ADDR_Pos))
#define PROV_DMA_CTRL_CH0_CMD_REG1_MASK     0xFFFFFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH0_CMD_REG1) Register MASK  (Use PROV_DMA_CTRL_CH0_CMD_REG1_Msk instead)  */
#define PROV_DMA_CTRL_CH0_CMD_REG1_Msk      0xFFFFFFFFu                                    /**< (PROV_DMA_CTRL_CH0_CMD_REG1) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_CMD_REG2 : (PROV_DMA_CTRL Offset: 0x08) (R/W 16) Channel 0 Third Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t BUFFER_SIZE:13;            /**< bit:  0..12  Size (in Bytes) of Buffer to Transfer    */
    uint16_t :3;                        /**< bit: 13..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_CMD_REG2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_CMD_REG2_OFFSET   0x08                                          /**<  (PROV_DMA_CTRL_CH0_CMD_REG2) Channel 0 Third Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH0_CMD_REG2_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_CMD_REG2) Channel 0 Third Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH0_CMD_REG2_BUFFER_SIZE_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_CMD_REG2) Size (in Bytes) of Buffer to Transfer Position */
#define PROV_DMA_CTRL_CH0_CMD_REG2_BUFFER_SIZE_Msk (0x1FFFu << PROV_DMA_CTRL_CH0_CMD_REG2_BUFFER_SIZE_Pos)  /**< (PROV_DMA_CTRL_CH0_CMD_REG2) Size (in Bytes) of Buffer to Transfer Mask */
#define PROV_DMA_CTRL_CH0_CMD_REG2_BUFFER_SIZE(value) (PROV_DMA_CTRL_CH0_CMD_REG2_BUFFER_SIZE_Msk & ((value) << PROV_DMA_CTRL_CH0_CMD_REG2_BUFFER_SIZE_Pos))
#define PROV_DMA_CTRL_CH0_CMD_REG2_MASK     0x1FFFu                                        /**< \deprecated (PROV_DMA_CTRL_CH0_CMD_REG2) Register MASK  (Use PROV_DMA_CTRL_CH0_CMD_REG2_Msk instead)  */
#define PROV_DMA_CTRL_CH0_CMD_REG2_Msk      0x1FFFu                                        /**< (PROV_DMA_CTRL_CH0_CMD_REG2) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_CMD_REG3 : (PROV_DMA_CTRL Offset: 0x0c) (R/W 32) Channel 0 Fourth Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CMD_SET_INT:1;             /**< bit:      0  Active High Interrupt Enable once buffer has been transfered */
    uint32_t CMD_LAST:1;                /**< bit:      1  If set, channel stops when buffer done, otherwise load from CMD_NEXT_ADDR */
    uint32_t CMD_NEXT_ADDR:30;          /**< bit:  2..31  Address of next command if CMD_LAST is not set */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_CMD_REG3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_CMD_REG3_OFFSET   0x0C                                          /**<  (PROV_DMA_CTRL_CH0_CMD_REG3) Channel 0 Fourth Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH0_CMD_REG3_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_CMD_REG3) Channel 0 Fourth Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH0_CMD_REG3_CMD_SET_INT_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_CMD_REG3) Active High Interrupt Enable once buffer has been transfered Position */
#define PROV_DMA_CTRL_CH0_CMD_REG3_CMD_SET_INT_Msk (0x1u << PROV_DMA_CTRL_CH0_CMD_REG3_CMD_SET_INT_Pos)  /**< (PROV_DMA_CTRL_CH0_CMD_REG3) Active High Interrupt Enable once buffer has been transfered Mask */
#define PROV_DMA_CTRL_CH0_CMD_REG3_CMD_SET_INT PROV_DMA_CTRL_CH0_CMD_REG3_CMD_SET_INT_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_CMD_REG3_CMD_SET_INT_Msk instead */
#define PROV_DMA_CTRL_CH0_CMD_REG3_CMD_LAST_Pos 1                                              /**< (PROV_DMA_CTRL_CH0_CMD_REG3) If set, channel stops when buffer done, otherwise load from CMD_NEXT_ADDR Position */
#define PROV_DMA_CTRL_CH0_CMD_REG3_CMD_LAST_Msk (0x1u << PROV_DMA_CTRL_CH0_CMD_REG3_CMD_LAST_Pos)  /**< (PROV_DMA_CTRL_CH0_CMD_REG3) If set, channel stops when buffer done, otherwise load from CMD_NEXT_ADDR Mask */
#define PROV_DMA_CTRL_CH0_CMD_REG3_CMD_LAST PROV_DMA_CTRL_CH0_CMD_REG3_CMD_LAST_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_CMD_REG3_CMD_LAST_Msk instead */
#define PROV_DMA_CTRL_CH0_CMD_REG3_CMD_NEXT_ADDR_Pos 2                                              /**< (PROV_DMA_CTRL_CH0_CMD_REG3) Address of next command if CMD_LAST is not set Position */
#define PROV_DMA_CTRL_CH0_CMD_REG3_CMD_NEXT_ADDR_Msk (0x3FFFFFFFu << PROV_DMA_CTRL_CH0_CMD_REG3_CMD_NEXT_ADDR_Pos)  /**< (PROV_DMA_CTRL_CH0_CMD_REG3) Address of next command if CMD_LAST is not set Mask */
#define PROV_DMA_CTRL_CH0_CMD_REG3_CMD_NEXT_ADDR(value) (PROV_DMA_CTRL_CH0_CMD_REG3_CMD_NEXT_ADDR_Msk & ((value) << PROV_DMA_CTRL_CH0_CMD_REG3_CMD_NEXT_ADDR_Pos))
#define PROV_DMA_CTRL_CH0_CMD_REG3_MASK     0xFFFFFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH0_CMD_REG3) Register MASK  (Use PROV_DMA_CTRL_CH0_CMD_REG3_Msk instead)  */
#define PROV_DMA_CTRL_CH0_CMD_REG3_Msk      0xFFFFFFFFu                                    /**< (PROV_DMA_CTRL_CH0_CMD_REG3) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_STATIC_REG0 : (PROV_DMA_CTRL Offset: 0x10) (R/W 32) Channel 0 Static Configuration Read -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_BURST_MAX_SIZE:7;       /**< bit:   0..6  Maximum number of bytes of an AHB read burst */
    uint32_t :9;                        /**< bit:  7..15  Reserved */
    uint32_t RD_TOKENS:6;               /**< bit: 16..21  Number of AHB read commands to issue before channel is released */
    uint32_t :9;                        /**< bit: 22..30  Reserved */
    uint32_t RD_INCR:1;                 /**< bit:     31  If set the controller will increment the next burst address */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_STATIC_REG0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_STATIC_REG0_OFFSET 0x10                                          /**<  (PROV_DMA_CTRL_CH0_STATIC_REG0) Channel 0 Static Configuration Read  Offset */
#define PROV_DMA_CTRL_CH0_STATIC_REG0_RESETVALUE 0x80010000u                                   /**<  (PROV_DMA_CTRL_CH0_STATIC_REG0) Channel 0 Static Configuration Read  Reset Value */

#define PROV_DMA_CTRL_CH0_STATIC_REG0_RD_BURST_MAX_SIZE_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_STATIC_REG0) Maximum number of bytes of an AHB read burst Position */
#define PROV_DMA_CTRL_CH0_STATIC_REG0_RD_BURST_MAX_SIZE_Msk (0x7Fu << PROV_DMA_CTRL_CH0_STATIC_REG0_RD_BURST_MAX_SIZE_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG0) Maximum number of bytes of an AHB read burst Mask */
#define PROV_DMA_CTRL_CH0_STATIC_REG0_RD_BURST_MAX_SIZE(value) (PROV_DMA_CTRL_CH0_STATIC_REG0_RD_BURST_MAX_SIZE_Msk & ((value) << PROV_DMA_CTRL_CH0_STATIC_REG0_RD_BURST_MAX_SIZE_Pos))
#define PROV_DMA_CTRL_CH0_STATIC_REG0_RD_TOKENS_Pos 16                                             /**< (PROV_DMA_CTRL_CH0_STATIC_REG0) Number of AHB read commands to issue before channel is released Position */
#define PROV_DMA_CTRL_CH0_STATIC_REG0_RD_TOKENS_Msk (0x3Fu << PROV_DMA_CTRL_CH0_STATIC_REG0_RD_TOKENS_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG0) Number of AHB read commands to issue before channel is released Mask */
#define PROV_DMA_CTRL_CH0_STATIC_REG0_RD_TOKENS(value) (PROV_DMA_CTRL_CH0_STATIC_REG0_RD_TOKENS_Msk & ((value) << PROV_DMA_CTRL_CH0_STATIC_REG0_RD_TOKENS_Pos))
#define PROV_DMA_CTRL_CH0_STATIC_REG0_RD_INCR_Pos 31                                             /**< (PROV_DMA_CTRL_CH0_STATIC_REG0) If set the controller will increment the next burst address Position */
#define PROV_DMA_CTRL_CH0_STATIC_REG0_RD_INCR_Msk (0x1u << PROV_DMA_CTRL_CH0_STATIC_REG0_RD_INCR_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG0) If set the controller will increment the next burst address Mask */
#define PROV_DMA_CTRL_CH0_STATIC_REG0_RD_INCR PROV_DMA_CTRL_CH0_STATIC_REG0_RD_INCR_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_STATIC_REG0_RD_INCR_Msk instead */
#define PROV_DMA_CTRL_CH0_STATIC_REG0_MASK  0x803F007Fu                                    /**< \deprecated (PROV_DMA_CTRL_CH0_STATIC_REG0) Register MASK  (Use PROV_DMA_CTRL_CH0_STATIC_REG0_Msk instead)  */
#define PROV_DMA_CTRL_CH0_STATIC_REG0_Msk   0x803F007Fu                                    /**< (PROV_DMA_CTRL_CH0_STATIC_REG0) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_STATIC_REG1 : (PROV_DMA_CTRL Offset: 0x14) (R/W 32) Channel 0 Static Configuration Write -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t WR_BURST_MAX_SIZE:7;       /**< bit:   0..6  Maximum number of bytes of an AHB write burst */
    uint32_t :9;                        /**< bit:  7..15  Reserved */
    uint32_t WR_TOKENS:6;               /**< bit: 16..21  Number of AHB write commands to issue before channel is released */
    uint32_t :9;                        /**< bit: 22..30  Reserved */
    uint32_t WR_INCR:1;                 /**< bit:     31  If set the controller will increment the next burst address */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_STATIC_REG1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_STATIC_REG1_OFFSET 0x14                                          /**<  (PROV_DMA_CTRL_CH0_STATIC_REG1) Channel 0 Static Configuration Write  Offset */
#define PROV_DMA_CTRL_CH0_STATIC_REG1_RESETVALUE 0x80010000u                                   /**<  (PROV_DMA_CTRL_CH0_STATIC_REG1) Channel 0 Static Configuration Write  Reset Value */

#define PROV_DMA_CTRL_CH0_STATIC_REG1_WR_BURST_MAX_SIZE_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_STATIC_REG1) Maximum number of bytes of an AHB write burst Position */
#define PROV_DMA_CTRL_CH0_STATIC_REG1_WR_BURST_MAX_SIZE_Msk (0x7Fu << PROV_DMA_CTRL_CH0_STATIC_REG1_WR_BURST_MAX_SIZE_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG1) Maximum number of bytes of an AHB write burst Mask */
#define PROV_DMA_CTRL_CH0_STATIC_REG1_WR_BURST_MAX_SIZE(value) (PROV_DMA_CTRL_CH0_STATIC_REG1_WR_BURST_MAX_SIZE_Msk & ((value) << PROV_DMA_CTRL_CH0_STATIC_REG1_WR_BURST_MAX_SIZE_Pos))
#define PROV_DMA_CTRL_CH0_STATIC_REG1_WR_TOKENS_Pos 16                                             /**< (PROV_DMA_CTRL_CH0_STATIC_REG1) Number of AHB write commands to issue before channel is released Position */
#define PROV_DMA_CTRL_CH0_STATIC_REG1_WR_TOKENS_Msk (0x3Fu << PROV_DMA_CTRL_CH0_STATIC_REG1_WR_TOKENS_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG1) Number of AHB write commands to issue before channel is released Mask */
#define PROV_DMA_CTRL_CH0_STATIC_REG1_WR_TOKENS(value) (PROV_DMA_CTRL_CH0_STATIC_REG1_WR_TOKENS_Msk & ((value) << PROV_DMA_CTRL_CH0_STATIC_REG1_WR_TOKENS_Pos))
#define PROV_DMA_CTRL_CH0_STATIC_REG1_WR_INCR_Pos 31                                             /**< (PROV_DMA_CTRL_CH0_STATIC_REG1) If set the controller will increment the next burst address Position */
#define PROV_DMA_CTRL_CH0_STATIC_REG1_WR_INCR_Msk (0x1u << PROV_DMA_CTRL_CH0_STATIC_REG1_WR_INCR_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG1) If set the controller will increment the next burst address Mask */
#define PROV_DMA_CTRL_CH0_STATIC_REG1_WR_INCR PROV_DMA_CTRL_CH0_STATIC_REG1_WR_INCR_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_STATIC_REG1_WR_INCR_Msk instead */
#define PROV_DMA_CTRL_CH0_STATIC_REG1_MASK  0x803F007Fu                                    /**< \deprecated (PROV_DMA_CTRL_CH0_STATIC_REG1) Register MASK  (Use PROV_DMA_CTRL_CH0_STATIC_REG1_Msk instead)  */
#define PROV_DMA_CTRL_CH0_STATIC_REG1_Msk   0x803F007Fu                                    /**< (PROV_DMA_CTRL_CH0_STATIC_REG1) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_STATIC_REG2 : (PROV_DMA_CTRL Offset: 0x18) (R/W 32) Channel 0 Block Mode -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :16;                       /**< bit:  0..15  Reserved */
    uint32_t JOINT:1;                   /**< bit:     16  If set channel will work in joint mode   */
    uint32_t :11;                       /**< bit: 17..27  Reserved */
    uint32_t END_SWAP:2;                /**< bit: 28..29  Endianness Byte Swapping                 */
    uint32_t :2;                        /**< bit: 30..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_STATIC_REG2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_STATIC_REG2_OFFSET 0x18                                          /**<  (PROV_DMA_CTRL_CH0_STATIC_REG2) Channel 0 Block Mode  Offset */
#define PROV_DMA_CTRL_CH0_STATIC_REG2_RESETVALUE 0x10000u                                      /**<  (PROV_DMA_CTRL_CH0_STATIC_REG2) Channel 0 Block Mode  Reset Value */

#define PROV_DMA_CTRL_CH0_STATIC_REG2_JOINT_Pos 16                                             /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) If set channel will work in joint mode Position */
#define PROV_DMA_CTRL_CH0_STATIC_REG2_JOINT_Msk (0x1u << PROV_DMA_CTRL_CH0_STATIC_REG2_JOINT_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) If set channel will work in joint mode Mask */
#define PROV_DMA_CTRL_CH0_STATIC_REG2_JOINT PROV_DMA_CTRL_CH0_STATIC_REG2_JOINT_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_STATIC_REG2_JOINT_Msk instead */
#define PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_Pos 28                                             /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) Endianness Byte Swapping Position */
#define PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_Msk (0x3u << PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) Endianness Byte Swapping Mask */
#define PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP(value) (PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_Msk & ((value) << PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_Pos))
#define   PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_0_Val 0x0u                                           /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) No Swapping  */
#define   PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_1_Val 0x1u                                           /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) Swap bytes within 16 bits  */
#define   PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_2_Val 0x2u                                           /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) Swap bytes within 32 bits  */
#define   PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_3_Val 0x3u                                           /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) Swap bytes within 64 bits  */
#define PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_0 (PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_0_Val << PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) No Swapping Position  */
#define PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_1 (PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_1_Val << PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) Swap bytes within 16 bits Position  */
#define PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_2 (PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_2_Val << PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) Swap bytes within 32 bits Position  */
#define PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_3 (PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_3_Val << PROV_DMA_CTRL_CH0_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) Swap bytes within 64 bits Position  */
#define PROV_DMA_CTRL_CH0_STATIC_REG2_MASK  0x30010000u                                    /**< \deprecated (PROV_DMA_CTRL_CH0_STATIC_REG2) Register MASK  (Use PROV_DMA_CTRL_CH0_STATIC_REG2_Msk instead)  */
#define PROV_DMA_CTRL_CH0_STATIC_REG2_Msk   0x30010000u                                    /**< (PROV_DMA_CTRL_CH0_STATIC_REG2) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_STATIC_REG4 : (PROV_DMA_CTRL Offset: 0x20) (R/W 32) Channel 0 Static Configuration Peripheral -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_PERIPH_NUM:5;           /**< bit:   0..4  Number of peripheral to read from (0 if memory or no peripheral flow control) */
    uint32_t :3;                        /**< bit:   5..7  Reserved */
    uint32_t RD_PERIPH_DELAY:3;         /**< bit:  8..10  Number of cycles to wait for read request signal to update after issuing the read clear signal */
    uint32_t :5;                        /**< bit: 11..15  Reserved */
    uint32_t WR_PERIPH_NUM:5;           /**< bit: 16..20  Number of peripheral to write from (0 if memory or no peripheral flow control) */
    uint32_t :3;                        /**< bit: 21..23  Reserved */
    uint32_t WR_PERIPH_DELAY:3;         /**< bit: 24..26  Number of cycles to wait for write request signal to update after issuing the write clear signal */
    uint32_t :5;                        /**< bit: 27..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_STATIC_REG4_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_STATIC_REG4_OFFSET 0x20                                          /**<  (PROV_DMA_CTRL_CH0_STATIC_REG4) Channel 0 Static Configuration Peripheral  Offset */
#define PROV_DMA_CTRL_CH0_STATIC_REG4_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_STATIC_REG4) Channel 0 Static Configuration Peripheral  Reset Value */

#define PROV_DMA_CTRL_CH0_STATIC_REG4_RD_PERIPH_NUM_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_STATIC_REG4) Number of peripheral to read from (0 if memory or no peripheral flow control) Position */
#define PROV_DMA_CTRL_CH0_STATIC_REG4_RD_PERIPH_NUM_Msk (0x1Fu << PROV_DMA_CTRL_CH0_STATIC_REG4_RD_PERIPH_NUM_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG4) Number of peripheral to read from (0 if memory or no peripheral flow control) Mask */
#define PROV_DMA_CTRL_CH0_STATIC_REG4_RD_PERIPH_NUM(value) (PROV_DMA_CTRL_CH0_STATIC_REG4_RD_PERIPH_NUM_Msk & ((value) << PROV_DMA_CTRL_CH0_STATIC_REG4_RD_PERIPH_NUM_Pos))
#define PROV_DMA_CTRL_CH0_STATIC_REG4_RD_PERIPH_DELAY_Pos 8                                              /**< (PROV_DMA_CTRL_CH0_STATIC_REG4) Number of cycles to wait for read request signal to update after issuing the read clear signal Position */
#define PROV_DMA_CTRL_CH0_STATIC_REG4_RD_PERIPH_DELAY_Msk (0x7u << PROV_DMA_CTRL_CH0_STATIC_REG4_RD_PERIPH_DELAY_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG4) Number of cycles to wait for read request signal to update after issuing the read clear signal Mask */
#define PROV_DMA_CTRL_CH0_STATIC_REG4_RD_PERIPH_DELAY(value) (PROV_DMA_CTRL_CH0_STATIC_REG4_RD_PERIPH_DELAY_Msk & ((value) << PROV_DMA_CTRL_CH0_STATIC_REG4_RD_PERIPH_DELAY_Pos))
#define PROV_DMA_CTRL_CH0_STATIC_REG4_WR_PERIPH_NUM_Pos 16                                             /**< (PROV_DMA_CTRL_CH0_STATIC_REG4) Number of peripheral to write from (0 if memory or no peripheral flow control) Position */
#define PROV_DMA_CTRL_CH0_STATIC_REG4_WR_PERIPH_NUM_Msk (0x1Fu << PROV_DMA_CTRL_CH0_STATIC_REG4_WR_PERIPH_NUM_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG4) Number of peripheral to write from (0 if memory or no peripheral flow control) Mask */
#define PROV_DMA_CTRL_CH0_STATIC_REG4_WR_PERIPH_NUM(value) (PROV_DMA_CTRL_CH0_STATIC_REG4_WR_PERIPH_NUM_Msk & ((value) << PROV_DMA_CTRL_CH0_STATIC_REG4_WR_PERIPH_NUM_Pos))
#define PROV_DMA_CTRL_CH0_STATIC_REG4_WR_PERIPH_DELAY_Pos 24                                             /**< (PROV_DMA_CTRL_CH0_STATIC_REG4) Number of cycles to wait for write request signal to update after issuing the write clear signal Position */
#define PROV_DMA_CTRL_CH0_STATIC_REG4_WR_PERIPH_DELAY_Msk (0x7u << PROV_DMA_CTRL_CH0_STATIC_REG4_WR_PERIPH_DELAY_Pos)  /**< (PROV_DMA_CTRL_CH0_STATIC_REG4) Number of cycles to wait for write request signal to update after issuing the write clear signal Mask */
#define PROV_DMA_CTRL_CH0_STATIC_REG4_WR_PERIPH_DELAY(value) (PROV_DMA_CTRL_CH0_STATIC_REG4_WR_PERIPH_DELAY_Msk & ((value) << PROV_DMA_CTRL_CH0_STATIC_REG4_WR_PERIPH_DELAY_Pos))
#define PROV_DMA_CTRL_CH0_STATIC_REG4_MASK  0x71F071Fu                                     /**< \deprecated (PROV_DMA_CTRL_CH0_STATIC_REG4) Register MASK  (Use PROV_DMA_CTRL_CH0_STATIC_REG4_Msk instead)  */
#define PROV_DMA_CTRL_CH0_STATIC_REG4_Msk   0x71F071Fu                                     /**< (PROV_DMA_CTRL_CH0_STATIC_REG4) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_RESRICT_REG : (PROV_DMA_CTRL Offset: 0x2c) (R/ 16) Channel 0 Restrictions Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t RD_ALLOW_FULL_FIFO:1;      /**< bit:      0  Read start address does not restrict burst size */
    uint16_t WR_ALLOW_FULL_FIFO:1;      /**< bit:      1  Write start address does not restrict burst size */
    uint16_t ALLOW_FULL_FIFO:1;         /**< bit:      2  Burst sizes can equal data buffer size, otherwise max burst is half data buffer size */
    uint16_t ALLOW_FULL_BURST:1;        /**< bit:      3  Maximum burst of 16 strobes can be used (joint mode only) */
    uint16_t ALLOW_JOINT_BURST:1;       /**< bit:      4  Joint bursts are currently active        */
    uint16_t :3;                        /**< bit:   5..7  Reserved */
    uint16_t SIMPLE_MEM:1;              /**< bit:      8  Configuration is aligned and peripherals are not used */
    uint16_t :7;                        /**< bit:  9..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_RESRICT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_RESRICT_REG_OFFSET 0x2C                                          /**<  (PROV_DMA_CTRL_CH0_RESRICT_REG) Channel 0 Restrictions Status Register  Offset */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_RESRICT_REG) Channel 0 Restrictions Status Register  Reset Value */

#define PROV_DMA_CTRL_CH0_RESRICT_REG_RD_ALLOW_FULL_FIFO_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Read start address does not restrict burst size Position */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_RD_ALLOW_FULL_FIFO_Msk (0x1u << PROV_DMA_CTRL_CH0_RESRICT_REG_RD_ALLOW_FULL_FIFO_Pos)  /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Read start address does not restrict burst size Mask */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_RD_ALLOW_FULL_FIFO PROV_DMA_CTRL_CH0_RESRICT_REG_RD_ALLOW_FULL_FIFO_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_RESRICT_REG_RD_ALLOW_FULL_FIFO_Msk instead */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_WR_ALLOW_FULL_FIFO_Pos 1                                              /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Write start address does not restrict burst size Position */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_WR_ALLOW_FULL_FIFO_Msk (0x1u << PROV_DMA_CTRL_CH0_RESRICT_REG_WR_ALLOW_FULL_FIFO_Pos)  /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Write start address does not restrict burst size Mask */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_WR_ALLOW_FULL_FIFO PROV_DMA_CTRL_CH0_RESRICT_REG_WR_ALLOW_FULL_FIFO_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_RESRICT_REG_WR_ALLOW_FULL_FIFO_Msk instead */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_FULL_FIFO_Pos 2                                              /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Burst sizes can equal data buffer size, otherwise max burst is half data buffer size Position */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_FULL_FIFO_Msk (0x1u << PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_FULL_FIFO_Pos)  /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Burst sizes can equal data buffer size, otherwise max burst is half data buffer size Mask */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_FULL_FIFO PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_FULL_FIFO_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_FULL_FIFO_Msk instead */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_FULL_BURST_Pos 3                                              /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Maximum burst of 16 strobes can be used (joint mode only) Position */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_FULL_BURST_Msk (0x1u << PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_FULL_BURST_Pos)  /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Maximum burst of 16 strobes can be used (joint mode only) Mask */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_FULL_BURST PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_FULL_BURST_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_FULL_BURST_Msk instead */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_JOINT_BURST_Pos 4                                              /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Joint bursts are currently active Position */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_JOINT_BURST_Msk (0x1u << PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_JOINT_BURST_Pos)  /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Joint bursts are currently active Mask */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_JOINT_BURST PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_JOINT_BURST_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_RESRICT_REG_ALLOW_JOINT_BURST_Msk instead */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_SIMPLE_MEM_Pos 8                                              /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Configuration is aligned and peripherals are not used Position */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_SIMPLE_MEM_Msk (0x1u << PROV_DMA_CTRL_CH0_RESRICT_REG_SIMPLE_MEM_Pos)  /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Configuration is aligned and peripherals are not used Mask */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_SIMPLE_MEM PROV_DMA_CTRL_CH0_RESRICT_REG_SIMPLE_MEM_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_RESRICT_REG_SIMPLE_MEM_Msk instead */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_MASK  0x11Fu                                         /**< \deprecated (PROV_DMA_CTRL_CH0_RESRICT_REG) Register MASK  (Use PROV_DMA_CTRL_CH0_RESRICT_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH0_RESRICT_REG_Msk   0x11Fu                                         /**< (PROV_DMA_CTRL_CH0_RESRICT_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG : (PROV_DMA_CTRL Offset: 0x38) (R/ 32) Channel 0 FIFO Fullness Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_GAP:13;                 /**< bit:  0..12  Remaining space (in bytes) in FIFO for read data */
    uint32_t :3;                        /**< bit: 13..15  Reserved */
    uint32_t WR_FULLNESS:13;            /**< bit: 16..28  Occupied space (in bytes) in FIFO by write data */
    uint32_t :3;                        /**< bit: 29..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_OFFSET 0x38                                          /**<  (PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG) Channel 0 FIFO Fullness Status Register  Offset */
#define PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG) Channel 0 FIFO Fullness Status Register  Reset Value */

#define PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_RD_GAP_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG) Remaining space (in bytes) in FIFO for read data Position */
#define PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_RD_GAP_Msk (0x1FFFu << PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_RD_GAP_Pos)  /**< (PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG) Remaining space (in bytes) in FIFO for read data Mask */
#define PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_RD_GAP(value) (PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_RD_GAP_Msk & ((value) << PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_RD_GAP_Pos))
#define PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_WR_FULLNESS_Pos 16                                             /**< (PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG) Occupied space (in bytes) in FIFO by write data Position */
#define PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_WR_FULLNESS_Msk (0x1FFFu << PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_WR_FULLNESS_Pos)  /**< (PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG) Occupied space (in bytes) in FIFO by write data Mask */
#define PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_WR_FULLNESS(value) (PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_WR_FULLNESS_Msk & ((value) << PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_WR_FULLNESS_Pos))
#define PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_MASK 0x1FFF1FFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG) Register MASK  (Use PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_Msk 0x1FFF1FFFu                                    /**< (PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_CH_ENABLE_REG : (PROV_DMA_CTRL Offset: 0x40) (R/W 8) Channel 0 Channel Enable Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH0_CH_ENABLE_REG:1;       /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_CH_ENABLE_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_CH_ENABLE_REG_OFFSET 0x40                                          /**<  (PROV_DMA_CTRL_CH0_CH_ENABLE_REG) Channel 0 Channel Enable Register  Offset */
#define PROV_DMA_CTRL_CH0_CH_ENABLE_REG_RESETVALUE 0x01u                                         /**<  (PROV_DMA_CTRL_CH0_CH_ENABLE_REG) Channel 0 Channel Enable Register  Reset Value */

#define PROV_DMA_CTRL_CH0_CH_ENABLE_REG_CH0_CH_ENABLE_REG_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_CH_ENABLE_REG)  Position */
#define PROV_DMA_CTRL_CH0_CH_ENABLE_REG_CH0_CH_ENABLE_REG_Msk (0x1u << PROV_DMA_CTRL_CH0_CH_ENABLE_REG_CH0_CH_ENABLE_REG_Pos)  /**< (PROV_DMA_CTRL_CH0_CH_ENABLE_REG)  Mask */
#define PROV_DMA_CTRL_CH0_CH_ENABLE_REG_CH0_CH_ENABLE_REG PROV_DMA_CTRL_CH0_CH_ENABLE_REG_CH0_CH_ENABLE_REG_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_CH_ENABLE_REG_CH0_CH_ENABLE_REG_Msk instead */
#define PROV_DMA_CTRL_CH0_CH_ENABLE_REG_MASK 0x01u                                          /**< \deprecated (PROV_DMA_CTRL_CH0_CH_ENABLE_REG) Register MASK  (Use PROV_DMA_CTRL_CH0_CH_ENABLE_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH0_CH_ENABLE_REG_Msk 0x01u                                          /**< (PROV_DMA_CTRL_CH0_CH_ENABLE_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_CH_START_REG : (PROV_DMA_CTRL Offset: 0x44) (/W 8) Channel 0 Channel Start Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH0_CH_START_REG:1;        /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_CH_START_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_CH_START_REG_OFFSET 0x44                                          /**<  (PROV_DMA_CTRL_CH0_CH_START_REG) Channel 0 Channel Start Register  Offset */
#define PROV_DMA_CTRL_CH0_CH_START_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_CH_START_REG) Channel 0 Channel Start Register  Reset Value */

#define PROV_DMA_CTRL_CH0_CH_START_REG_CH0_CH_START_REG_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_CH_START_REG)  Position */
#define PROV_DMA_CTRL_CH0_CH_START_REG_CH0_CH_START_REG_Msk (0x1u << PROV_DMA_CTRL_CH0_CH_START_REG_CH0_CH_START_REG_Pos)  /**< (PROV_DMA_CTRL_CH0_CH_START_REG)  Mask */
#define PROV_DMA_CTRL_CH0_CH_START_REG_CH0_CH_START_REG PROV_DMA_CTRL_CH0_CH_START_REG_CH0_CH_START_REG_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_CH_START_REG_CH0_CH_START_REG_Msk instead */
#define PROV_DMA_CTRL_CH0_CH_START_REG_MASK 0x01u                                          /**< \deprecated (PROV_DMA_CTRL_CH0_CH_START_REG) Register MASK  (Use PROV_DMA_CTRL_CH0_CH_START_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH0_CH_START_REG_Msk  0x01u                                          /**< (PROV_DMA_CTRL_CH0_CH_START_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_CH_ACTIVE_REG : (PROV_DMA_CTRL Offset: 0x48) (R/ 8) Channel 0 Channel Active Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_RD_ACTIVE:1;            /**< bit:      0  Set if channel is enabled and all read data has been received */
    uint8_t  CH_WR_ACTIVE:1;            /**< bit:      1  Set if channel is enabled and all write data has been transfered */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_OFFSET 0x48                                          /**<  (PROV_DMA_CTRL_CH0_CH_ACTIVE_REG) Channel 0 Channel Active Status Register  Offset */
#define PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_CH_ACTIVE_REG) Channel 0 Channel Active Status Register  Reset Value */

#define PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_CH_RD_ACTIVE_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_CH_ACTIVE_REG) Set if channel is enabled and all read data has been received Position */
#define PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_CH_RD_ACTIVE_Msk (0x1u << PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_CH_RD_ACTIVE_Pos)  /**< (PROV_DMA_CTRL_CH0_CH_ACTIVE_REG) Set if channel is enabled and all read data has been received Mask */
#define PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_CH_RD_ACTIVE PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_CH_RD_ACTIVE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_CH_RD_ACTIVE_Msk instead */
#define PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_CH_WR_ACTIVE_Pos 1                                              /**< (PROV_DMA_CTRL_CH0_CH_ACTIVE_REG) Set if channel is enabled and all write data has been transfered Position */
#define PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_CH_WR_ACTIVE_Msk (0x1u << PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_CH_WR_ACTIVE_Pos)  /**< (PROV_DMA_CTRL_CH0_CH_ACTIVE_REG) Set if channel is enabled and all write data has been transfered Mask */
#define PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_CH_WR_ACTIVE PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_CH_WR_ACTIVE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_CH_WR_ACTIVE_Msk instead */
#define PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_MASK 0x03u                                          /**< \deprecated (PROV_DMA_CTRL_CH0_CH_ACTIVE_REG) Register MASK  (Use PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_Msk 0x03u                                          /**< (PROV_DMA_CTRL_CH0_CH_ACTIVE_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_COUNT_REG : (PROV_DMA_CTRL Offset: 0x50) (R/ 32) Channel 0 Buffer Counter Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BUFF_COUNT:12;             /**< bit:  0..11  Number of buffers transferred by channel since started */
    uint32_t :4;                        /**< bit: 12..15  Reserved */
    uint32_t INT_COUNT:4;               /**< bit: 16..19  Number of unserviced end interrupts      */
    uint32_t :12;                       /**< bit: 20..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_COUNT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_COUNT_REG_OFFSET  0x50                                          /**<  (PROV_DMA_CTRL_CH0_COUNT_REG) Channel 0 Buffer Counter Status Register  Offset */
#define PROV_DMA_CTRL_CH0_COUNT_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_COUNT_REG) Channel 0 Buffer Counter Status Register  Reset Value */

#define PROV_DMA_CTRL_CH0_COUNT_REG_BUFF_COUNT_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_COUNT_REG) Number of buffers transferred by channel since started Position */
#define PROV_DMA_CTRL_CH0_COUNT_REG_BUFF_COUNT_Msk (0xFFFu << PROV_DMA_CTRL_CH0_COUNT_REG_BUFF_COUNT_Pos)  /**< (PROV_DMA_CTRL_CH0_COUNT_REG) Number of buffers transferred by channel since started Mask */
#define PROV_DMA_CTRL_CH0_COUNT_REG_BUFF_COUNT(value) (PROV_DMA_CTRL_CH0_COUNT_REG_BUFF_COUNT_Msk & ((value) << PROV_DMA_CTRL_CH0_COUNT_REG_BUFF_COUNT_Pos))
#define PROV_DMA_CTRL_CH0_COUNT_REG_INT_COUNT_Pos 16                                             /**< (PROV_DMA_CTRL_CH0_COUNT_REG) Number of unserviced end interrupts Position */
#define PROV_DMA_CTRL_CH0_COUNT_REG_INT_COUNT_Msk (0xFu << PROV_DMA_CTRL_CH0_COUNT_REG_INT_COUNT_Pos)  /**< (PROV_DMA_CTRL_CH0_COUNT_REG) Number of unserviced end interrupts Mask */
#define PROV_DMA_CTRL_CH0_COUNT_REG_INT_COUNT(value) (PROV_DMA_CTRL_CH0_COUNT_REG_INT_COUNT_Msk & ((value) << PROV_DMA_CTRL_CH0_COUNT_REG_INT_COUNT_Pos))
#define PROV_DMA_CTRL_CH0_COUNT_REG_MASK    0xF0FFFu                                       /**< \deprecated (PROV_DMA_CTRL_CH0_COUNT_REG) Register MASK  (Use PROV_DMA_CTRL_CH0_COUNT_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH0_COUNT_REG_Msk     0xF0FFFu                                       /**< (PROV_DMA_CTRL_CH0_COUNT_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG : (PROV_DMA_CTRL Offset: 0xa0) (R/W 8) Channel 0 Interrupt Raw Status (Write 1 to any field to issue interrupt) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Indicates an unserviced channel end interrupt */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  AHB read slave error                     */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  AHB write slave error                    */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  FIFO has been overflown                  */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  FIFO has been underflown                 */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Read timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Write timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  WDT:1;                     /**< bit:      7  Channel active but did not start a burst for 2048 cycles */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_OFFSET 0xA0                                          /**<  (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) Channel 0 Interrupt Raw Status (Write 1 to any field to issue interrupt)  Offset */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) Channel 0 Interrupt Raw Status (Write 1 to any field to issue interrupt)  Reset Value */

#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) Indicates an unserviced channel end interrupt Position */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) Indicates an unserviced channel end interrupt Mask */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_CH_END PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_CH_END_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) AHB read slave error Position */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) AHB read slave error Mask */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_RD_SLVERR PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) AHB write slave error Position */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) AHB write slave error Mask */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_WR_SLVERR PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) FIFO has been overflown Position */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) FIFO has been overflown Mask */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) FIFO has been underflown Position */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) FIFO has been underflown Mask */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_TIMEOUT_RD PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_TIMEOUT_WR PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) Channel active but did not start a burst for 2048 cycles Position */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) Channel active but did not start a burst for 2048 cycles Mask */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_WDT PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_WDT_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) Register MASK  (Use PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_INT_CLEAR_REG : (PROV_DMA_CTRL Offset: 0xa4) (R/W 8) Channel 0 Interrupt Clear (Write 1 to clear) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Clear channel end interrupt. Decrements INT_COUNT register */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  Clear AHB read slave error               */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  Clear AHB write slave error              */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  Clears FIFO overflow                     */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  Clears FIFO underflow                    */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Clears Read Timeout                      */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Clears Write Timeout                     */
    uint8_t  WDT:1;                     /**< bit:      7  Clears WDT                               */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_INT_CLEAR_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_OFFSET 0xA4                                          /**<  (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Channel 0 Interrupt Clear (Write 1 to clear)  Offset */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Channel 0 Interrupt Clear (Write 1 to clear)  Reset Value */

#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clear channel end interrupt. Decrements INT_COUNT register Position */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_CLEAR_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clear channel end interrupt. Decrements INT_COUNT register Mask */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_CH_END PROV_DMA_CTRL_CH0_INT_CLEAR_REG_CH_END_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_CLEAR_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clear AHB read slave error Position */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_CLEAR_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clear AHB read slave error Mask */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_RD_SLVERR PROV_DMA_CTRL_CH0_INT_CLEAR_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_CLEAR_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clear AHB write slave error Position */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_CLEAR_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clear AHB write slave error Mask */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_WR_SLVERR PROV_DMA_CTRL_CH0_INT_CLEAR_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_CLEAR_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clears FIFO overflow Position */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_CLEAR_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clears FIFO overflow Mask */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH0_INT_CLEAR_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_CLEAR_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clears FIFO underflow Position */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_CLEAR_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clears FIFO underflow Mask */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH0_INT_CLEAR_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_CLEAR_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clears Read Timeout Position */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_CLEAR_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clears Read Timeout Mask */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_TIMEOUT_RD PROV_DMA_CTRL_CH0_INT_CLEAR_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_CLEAR_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clears Write Timeout Position */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_CLEAR_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clears Write Timeout Mask */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_TIMEOUT_WR PROV_DMA_CTRL_CH0_INT_CLEAR_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_CLEAR_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clears WDT Position */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_CLEAR_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Clears WDT Mask */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_WDT PROV_DMA_CTRL_CH0_INT_CLEAR_REG_WDT_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_CLEAR_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Register MASK  (Use PROV_DMA_CTRL_CH0_INT_CLEAR_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH0_INT_CLEAR_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH0_INT_CLEAR_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_INT_ENABLE_REG : (PROV_DMA_CTRL Offset: 0xa8) (R/W 8) Channel 0 Interrupt Enable -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Enables end of channel interrupt         */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  Enables AHB read slave error interrupt   */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  Enables AHB write slave error interrupt  */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  Enables FIFO overflow interrupt          */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  Enables FIFO underflow interrupt         */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Enables AHB Read timeout interrupt       */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Enables AHB Write timeout interrupt      */
    uint8_t  WDT:1;                     /**< bit:      7  Enables WDT interrupt                    */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_INT_ENABLE_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_OFFSET 0xA8                                          /**<  (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Channel 0 Interrupt Enable  Offset */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Channel 0 Interrupt Enable  Reset Value */

#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables end of channel interrupt Position */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_ENABLE_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables end of channel interrupt Mask */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_CH_END PROV_DMA_CTRL_CH0_INT_ENABLE_REG_CH_END_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_ENABLE_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables AHB read slave error interrupt Position */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_ENABLE_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables AHB read slave error interrupt Mask */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_RD_SLVERR PROV_DMA_CTRL_CH0_INT_ENABLE_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_ENABLE_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables AHB write slave error interrupt Position */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_ENABLE_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables AHB write slave error interrupt Mask */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_WR_SLVERR PROV_DMA_CTRL_CH0_INT_ENABLE_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_ENABLE_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables FIFO overflow interrupt Position */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_ENABLE_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables FIFO overflow interrupt Mask */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH0_INT_ENABLE_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_ENABLE_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables FIFO underflow interrupt Position */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_ENABLE_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables FIFO underflow interrupt Mask */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH0_INT_ENABLE_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_ENABLE_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables AHB Read timeout interrupt Position */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_ENABLE_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables AHB Read timeout interrupt Mask */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_TIMEOUT_RD PROV_DMA_CTRL_CH0_INT_ENABLE_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_ENABLE_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables AHB Write timeout interrupt Position */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_ENABLE_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables AHB Write timeout interrupt Mask */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_TIMEOUT_WR PROV_DMA_CTRL_CH0_INT_ENABLE_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_ENABLE_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables WDT interrupt Position */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_ENABLE_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Enables WDT interrupt Mask */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_WDT PROV_DMA_CTRL_CH0_INT_ENABLE_REG_WDT_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_ENABLE_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Register MASK  (Use PROV_DMA_CTRL_CH0_INT_ENABLE_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH0_INT_ENABLE_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH0_INT_ENABLE_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH0_INT_STATUS_REG : (PROV_DMA_CTRL Offset: 0xac) (R/W 8) Channel 0 Interrupt Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Indicates an unserviced channel end interrupt */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  AHB read slave error                     */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  AHB write slave error                    */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  FIFO has been overflown                  */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  FIFO has been underflown                 */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Read timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Write timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  WDT:1;                     /**< bit:      7  Channel active but did not start a burst for 2048 cycles */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH0_INT_STATUS_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_OFFSET 0xAC                                          /**<  (PROV_DMA_CTRL_CH0_INT_STATUS_REG) Channel 0 Interrupt Status  Offset */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH0_INT_STATUS_REG) Channel 0 Interrupt Status  Reset Value */

#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) Indicates an unserviced channel end interrupt Position */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_STATUS_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) Indicates an unserviced channel end interrupt Mask */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_CH_END PROV_DMA_CTRL_CH0_INT_STATUS_REG_CH_END_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_STATUS_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) AHB read slave error Position */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_STATUS_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) AHB read slave error Mask */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_RD_SLVERR PROV_DMA_CTRL_CH0_INT_STATUS_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_STATUS_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) AHB write slave error Position */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_STATUS_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) AHB write slave error Mask */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_WR_SLVERR PROV_DMA_CTRL_CH0_INT_STATUS_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_STATUS_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) FIFO has been overflown Position */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_STATUS_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) FIFO has been overflown Mask */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH0_INT_STATUS_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_STATUS_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) FIFO has been underflown Position */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_STATUS_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) FIFO has been underflown Mask */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH0_INT_STATUS_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_STATUS_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_STATUS_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_TIMEOUT_RD PROV_DMA_CTRL_CH0_INT_STATUS_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_STATUS_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_STATUS_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_TIMEOUT_WR PROV_DMA_CTRL_CH0_INT_STATUS_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_STATUS_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) Channel active but did not start a burst for 2048 cycles Position */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH0_INT_STATUS_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) Channel active but did not start a burst for 2048 cycles Mask */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_WDT PROV_DMA_CTRL_CH0_INT_STATUS_REG_WDT_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH0_INT_STATUS_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH0_INT_STATUS_REG) Register MASK  (Use PROV_DMA_CTRL_CH0_INT_STATUS_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH0_INT_STATUS_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH0_INT_STATUS_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_CMD_REG0 : (PROV_DMA_CTRL Offset: 0x100) (R/W 32) Channel 1 First Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_START_ADDR:32;          /**< bit:  0..31  Start Address of Read Buffer             */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_CMD_REG0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_CMD_REG0_OFFSET   0x100                                         /**<  (PROV_DMA_CTRL_CH1_CMD_REG0) Channel 1 First Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH1_CMD_REG0_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_CMD_REG0) Channel 1 First Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH1_CMD_REG0_RD_START_ADDR_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_CMD_REG0) Start Address of Read Buffer Position */
#define PROV_DMA_CTRL_CH1_CMD_REG0_RD_START_ADDR_Msk (0xFFFFFFFFu << PROV_DMA_CTRL_CH1_CMD_REG0_RD_START_ADDR_Pos)  /**< (PROV_DMA_CTRL_CH1_CMD_REG0) Start Address of Read Buffer Mask */
#define PROV_DMA_CTRL_CH1_CMD_REG0_RD_START_ADDR(value) (PROV_DMA_CTRL_CH1_CMD_REG0_RD_START_ADDR_Msk & ((value) << PROV_DMA_CTRL_CH1_CMD_REG0_RD_START_ADDR_Pos))
#define PROV_DMA_CTRL_CH1_CMD_REG0_MASK     0xFFFFFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH1_CMD_REG0) Register MASK  (Use PROV_DMA_CTRL_CH1_CMD_REG0_Msk instead)  */
#define PROV_DMA_CTRL_CH1_CMD_REG0_Msk      0xFFFFFFFFu                                    /**< (PROV_DMA_CTRL_CH1_CMD_REG0) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_CMD_REG1 : (PROV_DMA_CTRL Offset: 0x104) (R/W 32) Channel 1 Second Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t WR_START_ADDR:32;          /**< bit:  0..31  Start Address of Write Buffer            */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_CMD_REG1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_CMD_REG1_OFFSET   0x104                                         /**<  (PROV_DMA_CTRL_CH1_CMD_REG1) Channel 1 Second Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH1_CMD_REG1_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_CMD_REG1) Channel 1 Second Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH1_CMD_REG1_WR_START_ADDR_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_CMD_REG1) Start Address of Write Buffer Position */
#define PROV_DMA_CTRL_CH1_CMD_REG1_WR_START_ADDR_Msk (0xFFFFFFFFu << PROV_DMA_CTRL_CH1_CMD_REG1_WR_START_ADDR_Pos)  /**< (PROV_DMA_CTRL_CH1_CMD_REG1) Start Address of Write Buffer Mask */
#define PROV_DMA_CTRL_CH1_CMD_REG1_WR_START_ADDR(value) (PROV_DMA_CTRL_CH1_CMD_REG1_WR_START_ADDR_Msk & ((value) << PROV_DMA_CTRL_CH1_CMD_REG1_WR_START_ADDR_Pos))
#define PROV_DMA_CTRL_CH1_CMD_REG1_MASK     0xFFFFFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH1_CMD_REG1) Register MASK  (Use PROV_DMA_CTRL_CH1_CMD_REG1_Msk instead)  */
#define PROV_DMA_CTRL_CH1_CMD_REG1_Msk      0xFFFFFFFFu                                    /**< (PROV_DMA_CTRL_CH1_CMD_REG1) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_CMD_REG2 : (PROV_DMA_CTRL Offset: 0x108) (R/W 16) Channel 1 Third Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t BUFFER_SIZE:13;            /**< bit:  0..12  Size (in Bytes) of Buffer to Transfer    */
    uint16_t :3;                        /**< bit: 13..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_CMD_REG2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_CMD_REG2_OFFSET   0x108                                         /**<  (PROV_DMA_CTRL_CH1_CMD_REG2) Channel 1 Third Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH1_CMD_REG2_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_CMD_REG2) Channel 1 Third Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH1_CMD_REG2_BUFFER_SIZE_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_CMD_REG2) Size (in Bytes) of Buffer to Transfer Position */
#define PROV_DMA_CTRL_CH1_CMD_REG2_BUFFER_SIZE_Msk (0x1FFFu << PROV_DMA_CTRL_CH1_CMD_REG2_BUFFER_SIZE_Pos)  /**< (PROV_DMA_CTRL_CH1_CMD_REG2) Size (in Bytes) of Buffer to Transfer Mask */
#define PROV_DMA_CTRL_CH1_CMD_REG2_BUFFER_SIZE(value) (PROV_DMA_CTRL_CH1_CMD_REG2_BUFFER_SIZE_Msk & ((value) << PROV_DMA_CTRL_CH1_CMD_REG2_BUFFER_SIZE_Pos))
#define PROV_DMA_CTRL_CH1_CMD_REG2_MASK     0x1FFFu                                        /**< \deprecated (PROV_DMA_CTRL_CH1_CMD_REG2) Register MASK  (Use PROV_DMA_CTRL_CH1_CMD_REG2_Msk instead)  */
#define PROV_DMA_CTRL_CH1_CMD_REG2_Msk      0x1FFFu                                        /**< (PROV_DMA_CTRL_CH1_CMD_REG2) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_CMD_REG3 : (PROV_DMA_CTRL Offset: 0x10c) (R/W 32) Channel 1 Fourth Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CMD_SET_INT:1;             /**< bit:      0  Active High Interrupt Enable once buffer has been transfered */
    uint32_t CMD_LAST:1;                /**< bit:      1  If set, channel stops when buffer done, otherwise load from CMD_NEXT_ADDR */
    uint32_t CMD_NEXT_ADDR:30;          /**< bit:  2..31  Address of next command if CMD_LAST is not set */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_CMD_REG3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_CMD_REG3_OFFSET   0x10C                                         /**<  (PROV_DMA_CTRL_CH1_CMD_REG3) Channel 1 Fourth Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH1_CMD_REG3_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_CMD_REG3) Channel 1 Fourth Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH1_CMD_REG3_CMD_SET_INT_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_CMD_REG3) Active High Interrupt Enable once buffer has been transfered Position */
#define PROV_DMA_CTRL_CH1_CMD_REG3_CMD_SET_INT_Msk (0x1u << PROV_DMA_CTRL_CH1_CMD_REG3_CMD_SET_INT_Pos)  /**< (PROV_DMA_CTRL_CH1_CMD_REG3) Active High Interrupt Enable once buffer has been transfered Mask */
#define PROV_DMA_CTRL_CH1_CMD_REG3_CMD_SET_INT PROV_DMA_CTRL_CH1_CMD_REG3_CMD_SET_INT_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_CMD_REG3_CMD_SET_INT_Msk instead */
#define PROV_DMA_CTRL_CH1_CMD_REG3_CMD_LAST_Pos 1                                              /**< (PROV_DMA_CTRL_CH1_CMD_REG3) If set, channel stops when buffer done, otherwise load from CMD_NEXT_ADDR Position */
#define PROV_DMA_CTRL_CH1_CMD_REG3_CMD_LAST_Msk (0x1u << PROV_DMA_CTRL_CH1_CMD_REG3_CMD_LAST_Pos)  /**< (PROV_DMA_CTRL_CH1_CMD_REG3) If set, channel stops when buffer done, otherwise load from CMD_NEXT_ADDR Mask */
#define PROV_DMA_CTRL_CH1_CMD_REG3_CMD_LAST PROV_DMA_CTRL_CH1_CMD_REG3_CMD_LAST_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_CMD_REG3_CMD_LAST_Msk instead */
#define PROV_DMA_CTRL_CH1_CMD_REG3_CMD_NEXT_ADDR_Pos 2                                              /**< (PROV_DMA_CTRL_CH1_CMD_REG3) Address of next command if CMD_LAST is not set Position */
#define PROV_DMA_CTRL_CH1_CMD_REG3_CMD_NEXT_ADDR_Msk (0x3FFFFFFFu << PROV_DMA_CTRL_CH1_CMD_REG3_CMD_NEXT_ADDR_Pos)  /**< (PROV_DMA_CTRL_CH1_CMD_REG3) Address of next command if CMD_LAST is not set Mask */
#define PROV_DMA_CTRL_CH1_CMD_REG3_CMD_NEXT_ADDR(value) (PROV_DMA_CTRL_CH1_CMD_REG3_CMD_NEXT_ADDR_Msk & ((value) << PROV_DMA_CTRL_CH1_CMD_REG3_CMD_NEXT_ADDR_Pos))
#define PROV_DMA_CTRL_CH1_CMD_REG3_MASK     0xFFFFFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH1_CMD_REG3) Register MASK  (Use PROV_DMA_CTRL_CH1_CMD_REG3_Msk instead)  */
#define PROV_DMA_CTRL_CH1_CMD_REG3_Msk      0xFFFFFFFFu                                    /**< (PROV_DMA_CTRL_CH1_CMD_REG3) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_STATIC_REG0 : (PROV_DMA_CTRL Offset: 0x110) (R/W 32) Channel 1 Static Configuration Read -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_BURST_MAX_SIZE:7;       /**< bit:   0..6  Maximum number of bytes of an AHB read burst */
    uint32_t :9;                        /**< bit:  7..15  Reserved */
    uint32_t RD_TOKENS:6;               /**< bit: 16..21  Number of AHB read commands to issue before channel is released */
    uint32_t :9;                        /**< bit: 22..30  Reserved */
    uint32_t RD_INCR:1;                 /**< bit:     31  If set the controller will increment the next burst address */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_STATIC_REG0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_STATIC_REG0_OFFSET 0x110                                         /**<  (PROV_DMA_CTRL_CH1_STATIC_REG0) Channel 1 Static Configuration Read  Offset */
#define PROV_DMA_CTRL_CH1_STATIC_REG0_RESETVALUE 0x80010000u                                   /**<  (PROV_DMA_CTRL_CH1_STATIC_REG0) Channel 1 Static Configuration Read  Reset Value */

#define PROV_DMA_CTRL_CH1_STATIC_REG0_RD_BURST_MAX_SIZE_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_STATIC_REG0) Maximum number of bytes of an AHB read burst Position */
#define PROV_DMA_CTRL_CH1_STATIC_REG0_RD_BURST_MAX_SIZE_Msk (0x7Fu << PROV_DMA_CTRL_CH1_STATIC_REG0_RD_BURST_MAX_SIZE_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG0) Maximum number of bytes of an AHB read burst Mask */
#define PROV_DMA_CTRL_CH1_STATIC_REG0_RD_BURST_MAX_SIZE(value) (PROV_DMA_CTRL_CH1_STATIC_REG0_RD_BURST_MAX_SIZE_Msk & ((value) << PROV_DMA_CTRL_CH1_STATIC_REG0_RD_BURST_MAX_SIZE_Pos))
#define PROV_DMA_CTRL_CH1_STATIC_REG0_RD_TOKENS_Pos 16                                             /**< (PROV_DMA_CTRL_CH1_STATIC_REG0) Number of AHB read commands to issue before channel is released Position */
#define PROV_DMA_CTRL_CH1_STATIC_REG0_RD_TOKENS_Msk (0x3Fu << PROV_DMA_CTRL_CH1_STATIC_REG0_RD_TOKENS_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG0) Number of AHB read commands to issue before channel is released Mask */
#define PROV_DMA_CTRL_CH1_STATIC_REG0_RD_TOKENS(value) (PROV_DMA_CTRL_CH1_STATIC_REG0_RD_TOKENS_Msk & ((value) << PROV_DMA_CTRL_CH1_STATIC_REG0_RD_TOKENS_Pos))
#define PROV_DMA_CTRL_CH1_STATIC_REG0_RD_INCR_Pos 31                                             /**< (PROV_DMA_CTRL_CH1_STATIC_REG0) If set the controller will increment the next burst address Position */
#define PROV_DMA_CTRL_CH1_STATIC_REG0_RD_INCR_Msk (0x1u << PROV_DMA_CTRL_CH1_STATIC_REG0_RD_INCR_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG0) If set the controller will increment the next burst address Mask */
#define PROV_DMA_CTRL_CH1_STATIC_REG0_RD_INCR PROV_DMA_CTRL_CH1_STATIC_REG0_RD_INCR_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_STATIC_REG0_RD_INCR_Msk instead */
#define PROV_DMA_CTRL_CH1_STATIC_REG0_MASK  0x803F007Fu                                    /**< \deprecated (PROV_DMA_CTRL_CH1_STATIC_REG0) Register MASK  (Use PROV_DMA_CTRL_CH1_STATIC_REG0_Msk instead)  */
#define PROV_DMA_CTRL_CH1_STATIC_REG0_Msk   0x803F007Fu                                    /**< (PROV_DMA_CTRL_CH1_STATIC_REG0) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_STATIC_REG1 : (PROV_DMA_CTRL Offset: 0x114) (R/W 32) Channel 1 Static Configuration Write -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t WR_BURST_MAX_SIZE:7;       /**< bit:   0..6  Maximum number of bytes of an AHB write burst */
    uint32_t :9;                        /**< bit:  7..15  Reserved */
    uint32_t WR_TOKENS:6;               /**< bit: 16..21  Number of AHB write commands to issue before channel is released */
    uint32_t :9;                        /**< bit: 22..30  Reserved */
    uint32_t WR_INCR:1;                 /**< bit:     31  If set the controller will increment the next burst address */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_STATIC_REG1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_STATIC_REG1_OFFSET 0x114                                         /**<  (PROV_DMA_CTRL_CH1_STATIC_REG1) Channel 1 Static Configuration Write  Offset */
#define PROV_DMA_CTRL_CH1_STATIC_REG1_RESETVALUE 0x80010000u                                   /**<  (PROV_DMA_CTRL_CH1_STATIC_REG1) Channel 1 Static Configuration Write  Reset Value */

#define PROV_DMA_CTRL_CH1_STATIC_REG1_WR_BURST_MAX_SIZE_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_STATIC_REG1) Maximum number of bytes of an AHB write burst Position */
#define PROV_DMA_CTRL_CH1_STATIC_REG1_WR_BURST_MAX_SIZE_Msk (0x7Fu << PROV_DMA_CTRL_CH1_STATIC_REG1_WR_BURST_MAX_SIZE_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG1) Maximum number of bytes of an AHB write burst Mask */
#define PROV_DMA_CTRL_CH1_STATIC_REG1_WR_BURST_MAX_SIZE(value) (PROV_DMA_CTRL_CH1_STATIC_REG1_WR_BURST_MAX_SIZE_Msk & ((value) << PROV_DMA_CTRL_CH1_STATIC_REG1_WR_BURST_MAX_SIZE_Pos))
#define PROV_DMA_CTRL_CH1_STATIC_REG1_WR_TOKENS_Pos 16                                             /**< (PROV_DMA_CTRL_CH1_STATIC_REG1) Number of AHB write commands to issue before channel is released Position */
#define PROV_DMA_CTRL_CH1_STATIC_REG1_WR_TOKENS_Msk (0x3Fu << PROV_DMA_CTRL_CH1_STATIC_REG1_WR_TOKENS_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG1) Number of AHB write commands to issue before channel is released Mask */
#define PROV_DMA_CTRL_CH1_STATIC_REG1_WR_TOKENS(value) (PROV_DMA_CTRL_CH1_STATIC_REG1_WR_TOKENS_Msk & ((value) << PROV_DMA_CTRL_CH1_STATIC_REG1_WR_TOKENS_Pos))
#define PROV_DMA_CTRL_CH1_STATIC_REG1_WR_INCR_Pos 31                                             /**< (PROV_DMA_CTRL_CH1_STATIC_REG1) If set the controller will increment the next burst address Position */
#define PROV_DMA_CTRL_CH1_STATIC_REG1_WR_INCR_Msk (0x1u << PROV_DMA_CTRL_CH1_STATIC_REG1_WR_INCR_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG1) If set the controller will increment the next burst address Mask */
#define PROV_DMA_CTRL_CH1_STATIC_REG1_WR_INCR PROV_DMA_CTRL_CH1_STATIC_REG1_WR_INCR_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_STATIC_REG1_WR_INCR_Msk instead */
#define PROV_DMA_CTRL_CH1_STATIC_REG1_MASK  0x803F007Fu                                    /**< \deprecated (PROV_DMA_CTRL_CH1_STATIC_REG1) Register MASK  (Use PROV_DMA_CTRL_CH1_STATIC_REG1_Msk instead)  */
#define PROV_DMA_CTRL_CH1_STATIC_REG1_Msk   0x803F007Fu                                    /**< (PROV_DMA_CTRL_CH1_STATIC_REG1) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_STATIC_REG2 : (PROV_DMA_CTRL Offset: 0x118) (R/W 32) Channel 1 Block Mode -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :16;                       /**< bit:  0..15  Reserved */
    uint32_t JOINT:1;                   /**< bit:     16  If set channel will work in joint mode   */
    uint32_t :11;                       /**< bit: 17..27  Reserved */
    uint32_t END_SWAP:2;                /**< bit: 28..29  Endianness Byte Swapping                 */
    uint32_t :2;                        /**< bit: 30..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_STATIC_REG2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_STATIC_REG2_OFFSET 0x118                                         /**<  (PROV_DMA_CTRL_CH1_STATIC_REG2) Channel 1 Block Mode  Offset */
#define PROV_DMA_CTRL_CH1_STATIC_REG2_RESETVALUE 0x10000u                                      /**<  (PROV_DMA_CTRL_CH1_STATIC_REG2) Channel 1 Block Mode  Reset Value */

#define PROV_DMA_CTRL_CH1_STATIC_REG2_JOINT_Pos 16                                             /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) If set channel will work in joint mode Position */
#define PROV_DMA_CTRL_CH1_STATIC_REG2_JOINT_Msk (0x1u << PROV_DMA_CTRL_CH1_STATIC_REG2_JOINT_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) If set channel will work in joint mode Mask */
#define PROV_DMA_CTRL_CH1_STATIC_REG2_JOINT PROV_DMA_CTRL_CH1_STATIC_REG2_JOINT_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_STATIC_REG2_JOINT_Msk instead */
#define PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_Pos 28                                             /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) Endianness Byte Swapping Position */
#define PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_Msk (0x3u << PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) Endianness Byte Swapping Mask */
#define PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP(value) (PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_Msk & ((value) << PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_Pos))
#define   PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_0_Val 0x0u                                           /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) No Swapping  */
#define   PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_1_Val 0x1u                                           /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) Swap bytes within 16 bits  */
#define   PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_2_Val 0x2u                                           /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) Swap bytes within 32 bits  */
#define   PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_3_Val 0x3u                                           /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) Swap bytes within 64 bits  */
#define PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_0 (PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_0_Val << PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) No Swapping Position  */
#define PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_1 (PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_1_Val << PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) Swap bytes within 16 bits Position  */
#define PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_2 (PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_2_Val << PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) Swap bytes within 32 bits Position  */
#define PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_3 (PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_3_Val << PROV_DMA_CTRL_CH1_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) Swap bytes within 64 bits Position  */
#define PROV_DMA_CTRL_CH1_STATIC_REG2_MASK  0x30010000u                                    /**< \deprecated (PROV_DMA_CTRL_CH1_STATIC_REG2) Register MASK  (Use PROV_DMA_CTRL_CH1_STATIC_REG2_Msk instead)  */
#define PROV_DMA_CTRL_CH1_STATIC_REG2_Msk   0x30010000u                                    /**< (PROV_DMA_CTRL_CH1_STATIC_REG2) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_STATIC_REG4 : (PROV_DMA_CTRL Offset: 0x120) (R/W 32) Channel 1 Static Configuration Peripheral -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_PERIPH_NUM:5;           /**< bit:   0..4  Number of peripheral to read from (0 if memory or no peripheral flow control) */
    uint32_t :3;                        /**< bit:   5..7  Reserved */
    uint32_t RD_PERIPH_DELAY:3;         /**< bit:  8..10  Number of cycles to wait for read request signal to update after issuing the read clear signal */
    uint32_t :5;                        /**< bit: 11..15  Reserved */
    uint32_t WR_PERIPH_NUM:5;           /**< bit: 16..20  Number of peripheral to write from (0 if memory or no peripheral flow control) */
    uint32_t :3;                        /**< bit: 21..23  Reserved */
    uint32_t WR_PERIPH_DELAY:3;         /**< bit: 24..26  Number of cycles to wait for write request signal to update after issuing the write clear signal */
    uint32_t :5;                        /**< bit: 27..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_STATIC_REG4_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_STATIC_REG4_OFFSET 0x120                                         /**<  (PROV_DMA_CTRL_CH1_STATIC_REG4) Channel 1 Static Configuration Peripheral  Offset */
#define PROV_DMA_CTRL_CH1_STATIC_REG4_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_STATIC_REG4) Channel 1 Static Configuration Peripheral  Reset Value */

#define PROV_DMA_CTRL_CH1_STATIC_REG4_RD_PERIPH_NUM_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_STATIC_REG4) Number of peripheral to read from (0 if memory or no peripheral flow control) Position */
#define PROV_DMA_CTRL_CH1_STATIC_REG4_RD_PERIPH_NUM_Msk (0x1Fu << PROV_DMA_CTRL_CH1_STATIC_REG4_RD_PERIPH_NUM_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG4) Number of peripheral to read from (0 if memory or no peripheral flow control) Mask */
#define PROV_DMA_CTRL_CH1_STATIC_REG4_RD_PERIPH_NUM(value) (PROV_DMA_CTRL_CH1_STATIC_REG4_RD_PERIPH_NUM_Msk & ((value) << PROV_DMA_CTRL_CH1_STATIC_REG4_RD_PERIPH_NUM_Pos))
#define PROV_DMA_CTRL_CH1_STATIC_REG4_RD_PERIPH_DELAY_Pos 8                                              /**< (PROV_DMA_CTRL_CH1_STATIC_REG4) Number of cycles to wait for read request signal to update after issuing the read clear signal Position */
#define PROV_DMA_CTRL_CH1_STATIC_REG4_RD_PERIPH_DELAY_Msk (0x7u << PROV_DMA_CTRL_CH1_STATIC_REG4_RD_PERIPH_DELAY_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG4) Number of cycles to wait for read request signal to update after issuing the read clear signal Mask */
#define PROV_DMA_CTRL_CH1_STATIC_REG4_RD_PERIPH_DELAY(value) (PROV_DMA_CTRL_CH1_STATIC_REG4_RD_PERIPH_DELAY_Msk & ((value) << PROV_DMA_CTRL_CH1_STATIC_REG4_RD_PERIPH_DELAY_Pos))
#define PROV_DMA_CTRL_CH1_STATIC_REG4_WR_PERIPH_NUM_Pos 16                                             /**< (PROV_DMA_CTRL_CH1_STATIC_REG4) Number of peripheral to write from (0 if memory or no peripheral flow control) Position */
#define PROV_DMA_CTRL_CH1_STATIC_REG4_WR_PERIPH_NUM_Msk (0x1Fu << PROV_DMA_CTRL_CH1_STATIC_REG4_WR_PERIPH_NUM_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG4) Number of peripheral to write from (0 if memory or no peripheral flow control) Mask */
#define PROV_DMA_CTRL_CH1_STATIC_REG4_WR_PERIPH_NUM(value) (PROV_DMA_CTRL_CH1_STATIC_REG4_WR_PERIPH_NUM_Msk & ((value) << PROV_DMA_CTRL_CH1_STATIC_REG4_WR_PERIPH_NUM_Pos))
#define PROV_DMA_CTRL_CH1_STATIC_REG4_WR_PERIPH_DELAY_Pos 24                                             /**< (PROV_DMA_CTRL_CH1_STATIC_REG4) Number of cycles to wait for write request signal to update after issuing the write clear signal Position */
#define PROV_DMA_CTRL_CH1_STATIC_REG4_WR_PERIPH_DELAY_Msk (0x7u << PROV_DMA_CTRL_CH1_STATIC_REG4_WR_PERIPH_DELAY_Pos)  /**< (PROV_DMA_CTRL_CH1_STATIC_REG4) Number of cycles to wait for write request signal to update after issuing the write clear signal Mask */
#define PROV_DMA_CTRL_CH1_STATIC_REG4_WR_PERIPH_DELAY(value) (PROV_DMA_CTRL_CH1_STATIC_REG4_WR_PERIPH_DELAY_Msk & ((value) << PROV_DMA_CTRL_CH1_STATIC_REG4_WR_PERIPH_DELAY_Pos))
#define PROV_DMA_CTRL_CH1_STATIC_REG4_MASK  0x71F071Fu                                     /**< \deprecated (PROV_DMA_CTRL_CH1_STATIC_REG4) Register MASK  (Use PROV_DMA_CTRL_CH1_STATIC_REG4_Msk instead)  */
#define PROV_DMA_CTRL_CH1_STATIC_REG4_Msk   0x71F071Fu                                     /**< (PROV_DMA_CTRL_CH1_STATIC_REG4) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_RESRICT_REG : (PROV_DMA_CTRL Offset: 0x12c) (R/ 16) Channel 1 Restrictions Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t RD_ALLOW_FULL_FIFO:1;      /**< bit:      0  Read start address does not restrict burst size */
    uint16_t WR_ALLOW_FULL_FIFO:1;      /**< bit:      1  Write start address does not restrict burst size */
    uint16_t ALLOW_FULL_FIFO:1;         /**< bit:      2  Burst sizes can equal data buffer size, otherwise max burst is half data buffer size */
    uint16_t ALLOW_FULL_BURST:1;        /**< bit:      3  Maximum burst of 16 strobes can be used (joint mode only) */
    uint16_t ALLOW_JOINT_BURST:1;       /**< bit:      4  Joint bursts are currently active        */
    uint16_t :3;                        /**< bit:   5..7  Reserved */
    uint16_t SIMPLE_MEM:1;              /**< bit:      8  Configuration is aligned and peripherals are not used */
    uint16_t :7;                        /**< bit:  9..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_RESRICT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_RESRICT_REG_OFFSET 0x12C                                         /**<  (PROV_DMA_CTRL_CH1_RESRICT_REG) Channel 1 Restrictions Status Register  Offset */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_RESRICT_REG) Channel 1 Restrictions Status Register  Reset Value */

#define PROV_DMA_CTRL_CH1_RESRICT_REG_RD_ALLOW_FULL_FIFO_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Read start address does not restrict burst size Position */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_RD_ALLOW_FULL_FIFO_Msk (0x1u << PROV_DMA_CTRL_CH1_RESRICT_REG_RD_ALLOW_FULL_FIFO_Pos)  /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Read start address does not restrict burst size Mask */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_RD_ALLOW_FULL_FIFO PROV_DMA_CTRL_CH1_RESRICT_REG_RD_ALLOW_FULL_FIFO_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_RESRICT_REG_RD_ALLOW_FULL_FIFO_Msk instead */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_WR_ALLOW_FULL_FIFO_Pos 1                                              /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Write start address does not restrict burst size Position */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_WR_ALLOW_FULL_FIFO_Msk (0x1u << PROV_DMA_CTRL_CH1_RESRICT_REG_WR_ALLOW_FULL_FIFO_Pos)  /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Write start address does not restrict burst size Mask */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_WR_ALLOW_FULL_FIFO PROV_DMA_CTRL_CH1_RESRICT_REG_WR_ALLOW_FULL_FIFO_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_RESRICT_REG_WR_ALLOW_FULL_FIFO_Msk instead */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_FULL_FIFO_Pos 2                                              /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Burst sizes can equal data buffer size, otherwise max burst is half data buffer size Position */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_FULL_FIFO_Msk (0x1u << PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_FULL_FIFO_Pos)  /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Burst sizes can equal data buffer size, otherwise max burst is half data buffer size Mask */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_FULL_FIFO PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_FULL_FIFO_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_FULL_FIFO_Msk instead */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_FULL_BURST_Pos 3                                              /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Maximum burst of 16 strobes can be used (joint mode only) Position */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_FULL_BURST_Msk (0x1u << PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_FULL_BURST_Pos)  /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Maximum burst of 16 strobes can be used (joint mode only) Mask */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_FULL_BURST PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_FULL_BURST_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_FULL_BURST_Msk instead */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_JOINT_BURST_Pos 4                                              /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Joint bursts are currently active Position */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_JOINT_BURST_Msk (0x1u << PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_JOINT_BURST_Pos)  /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Joint bursts are currently active Mask */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_JOINT_BURST PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_JOINT_BURST_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_RESRICT_REG_ALLOW_JOINT_BURST_Msk instead */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_SIMPLE_MEM_Pos 8                                              /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Configuration is aligned and peripherals are not used Position */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_SIMPLE_MEM_Msk (0x1u << PROV_DMA_CTRL_CH1_RESRICT_REG_SIMPLE_MEM_Pos)  /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Configuration is aligned and peripherals are not used Mask */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_SIMPLE_MEM PROV_DMA_CTRL_CH1_RESRICT_REG_SIMPLE_MEM_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_RESRICT_REG_SIMPLE_MEM_Msk instead */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_MASK  0x11Fu                                         /**< \deprecated (PROV_DMA_CTRL_CH1_RESRICT_REG) Register MASK  (Use PROV_DMA_CTRL_CH1_RESRICT_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH1_RESRICT_REG_Msk   0x11Fu                                         /**< (PROV_DMA_CTRL_CH1_RESRICT_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG : (PROV_DMA_CTRL Offset: 0x138) (R/ 32) Channel 1 FIFO Fullness Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_GAP:13;                 /**< bit:  0..12  Remaining space (in bytes) in FIFO for read data */
    uint32_t :3;                        /**< bit: 13..15  Reserved */
    uint32_t WR_FULLNESS:13;            /**< bit: 16..28  Occupied space (in bytes) in FIFO by write data */
    uint32_t :3;                        /**< bit: 29..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_OFFSET 0x138                                         /**<  (PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG) Channel 1 FIFO Fullness Status Register  Offset */
#define PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG) Channel 1 FIFO Fullness Status Register  Reset Value */

#define PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_RD_GAP_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG) Remaining space (in bytes) in FIFO for read data Position */
#define PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_RD_GAP_Msk (0x1FFFu << PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_RD_GAP_Pos)  /**< (PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG) Remaining space (in bytes) in FIFO for read data Mask */
#define PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_RD_GAP(value) (PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_RD_GAP_Msk & ((value) << PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_RD_GAP_Pos))
#define PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_WR_FULLNESS_Pos 16                                             /**< (PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG) Occupied space (in bytes) in FIFO by write data Position */
#define PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_WR_FULLNESS_Msk (0x1FFFu << PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_WR_FULLNESS_Pos)  /**< (PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG) Occupied space (in bytes) in FIFO by write data Mask */
#define PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_WR_FULLNESS(value) (PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_WR_FULLNESS_Msk & ((value) << PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_WR_FULLNESS_Pos))
#define PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_MASK 0x1FFF1FFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG) Register MASK  (Use PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_Msk 0x1FFF1FFFu                                    /**< (PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_CH_ENABLE_REG : (PROV_DMA_CTRL Offset: 0x140) (R/W 8) Channel 1 Channel Enable Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH1_CH_ENABLE_REG:1;       /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_CH_ENABLE_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_CH_ENABLE_REG_OFFSET 0x140                                         /**<  (PROV_DMA_CTRL_CH1_CH_ENABLE_REG) Channel 1 Channel Enable Register  Offset */
#define PROV_DMA_CTRL_CH1_CH_ENABLE_REG_RESETVALUE 0x01u                                         /**<  (PROV_DMA_CTRL_CH1_CH_ENABLE_REG) Channel 1 Channel Enable Register  Reset Value */

#define PROV_DMA_CTRL_CH1_CH_ENABLE_REG_CH1_CH_ENABLE_REG_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_CH_ENABLE_REG)  Position */
#define PROV_DMA_CTRL_CH1_CH_ENABLE_REG_CH1_CH_ENABLE_REG_Msk (0x1u << PROV_DMA_CTRL_CH1_CH_ENABLE_REG_CH1_CH_ENABLE_REG_Pos)  /**< (PROV_DMA_CTRL_CH1_CH_ENABLE_REG)  Mask */
#define PROV_DMA_CTRL_CH1_CH_ENABLE_REG_CH1_CH_ENABLE_REG PROV_DMA_CTRL_CH1_CH_ENABLE_REG_CH1_CH_ENABLE_REG_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_CH_ENABLE_REG_CH1_CH_ENABLE_REG_Msk instead */
#define PROV_DMA_CTRL_CH1_CH_ENABLE_REG_MASK 0x01u                                          /**< \deprecated (PROV_DMA_CTRL_CH1_CH_ENABLE_REG) Register MASK  (Use PROV_DMA_CTRL_CH1_CH_ENABLE_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH1_CH_ENABLE_REG_Msk 0x01u                                          /**< (PROV_DMA_CTRL_CH1_CH_ENABLE_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_CH_START_REG : (PROV_DMA_CTRL Offset: 0x144) (/W 8) Channel 1 Channel Start Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH1_CH_START_REG:1;        /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_CH_START_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_CH_START_REG_OFFSET 0x144                                         /**<  (PROV_DMA_CTRL_CH1_CH_START_REG) Channel 1 Channel Start Register  Offset */
#define PROV_DMA_CTRL_CH1_CH_START_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_CH_START_REG) Channel 1 Channel Start Register  Reset Value */

#define PROV_DMA_CTRL_CH1_CH_START_REG_CH1_CH_START_REG_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_CH_START_REG)  Position */
#define PROV_DMA_CTRL_CH1_CH_START_REG_CH1_CH_START_REG_Msk (0x1u << PROV_DMA_CTRL_CH1_CH_START_REG_CH1_CH_START_REG_Pos)  /**< (PROV_DMA_CTRL_CH1_CH_START_REG)  Mask */
#define PROV_DMA_CTRL_CH1_CH_START_REG_CH1_CH_START_REG PROV_DMA_CTRL_CH1_CH_START_REG_CH1_CH_START_REG_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_CH_START_REG_CH1_CH_START_REG_Msk instead */
#define PROV_DMA_CTRL_CH1_CH_START_REG_MASK 0x01u                                          /**< \deprecated (PROV_DMA_CTRL_CH1_CH_START_REG) Register MASK  (Use PROV_DMA_CTRL_CH1_CH_START_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH1_CH_START_REG_Msk  0x01u                                          /**< (PROV_DMA_CTRL_CH1_CH_START_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_CH_ACTIVE_REG : (PROV_DMA_CTRL Offset: 0x148) (R/ 8) Channel 1 Channel Active Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_RD_ACTIVE:1;            /**< bit:      0  Set if channel is enabled and all read data has been received */
    uint8_t  CH_WR_ACTIVE:1;            /**< bit:      1  Set if channel is enabled and all write data has been transfered */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_OFFSET 0x148                                         /**<  (PROV_DMA_CTRL_CH1_CH_ACTIVE_REG) Channel 1 Channel Active Status Register  Offset */
#define PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_CH_ACTIVE_REG) Channel 1 Channel Active Status Register  Reset Value */

#define PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_CH_RD_ACTIVE_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_CH_ACTIVE_REG) Set if channel is enabled and all read data has been received Position */
#define PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_CH_RD_ACTIVE_Msk (0x1u << PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_CH_RD_ACTIVE_Pos)  /**< (PROV_DMA_CTRL_CH1_CH_ACTIVE_REG) Set if channel is enabled and all read data has been received Mask */
#define PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_CH_RD_ACTIVE PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_CH_RD_ACTIVE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_CH_RD_ACTIVE_Msk instead */
#define PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_CH_WR_ACTIVE_Pos 1                                              /**< (PROV_DMA_CTRL_CH1_CH_ACTIVE_REG) Set if channel is enabled and all write data has been transfered Position */
#define PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_CH_WR_ACTIVE_Msk (0x1u << PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_CH_WR_ACTIVE_Pos)  /**< (PROV_DMA_CTRL_CH1_CH_ACTIVE_REG) Set if channel is enabled and all write data has been transfered Mask */
#define PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_CH_WR_ACTIVE PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_CH_WR_ACTIVE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_CH_WR_ACTIVE_Msk instead */
#define PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_MASK 0x03u                                          /**< \deprecated (PROV_DMA_CTRL_CH1_CH_ACTIVE_REG) Register MASK  (Use PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_Msk 0x03u                                          /**< (PROV_DMA_CTRL_CH1_CH_ACTIVE_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_COUNT_REG : (PROV_DMA_CTRL Offset: 0x150) (R/ 32) Channel 1 Buffer Counter Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BUFF_COUNT:12;             /**< bit:  0..11  Number of buffers transferred by channel since started */
    uint32_t :4;                        /**< bit: 12..15  Reserved */
    uint32_t INT_COUNT:4;               /**< bit: 16..19  Number of unserviced end interrupts      */
    uint32_t :12;                       /**< bit: 20..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_COUNT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_COUNT_REG_OFFSET  0x150                                         /**<  (PROV_DMA_CTRL_CH1_COUNT_REG) Channel 1 Buffer Counter Status Register  Offset */
#define PROV_DMA_CTRL_CH1_COUNT_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_COUNT_REG) Channel 1 Buffer Counter Status Register  Reset Value */

#define PROV_DMA_CTRL_CH1_COUNT_REG_BUFF_COUNT_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_COUNT_REG) Number of buffers transferred by channel since started Position */
#define PROV_DMA_CTRL_CH1_COUNT_REG_BUFF_COUNT_Msk (0xFFFu << PROV_DMA_CTRL_CH1_COUNT_REG_BUFF_COUNT_Pos)  /**< (PROV_DMA_CTRL_CH1_COUNT_REG) Number of buffers transferred by channel since started Mask */
#define PROV_DMA_CTRL_CH1_COUNT_REG_BUFF_COUNT(value) (PROV_DMA_CTRL_CH1_COUNT_REG_BUFF_COUNT_Msk & ((value) << PROV_DMA_CTRL_CH1_COUNT_REG_BUFF_COUNT_Pos))
#define PROV_DMA_CTRL_CH1_COUNT_REG_INT_COUNT_Pos 16                                             /**< (PROV_DMA_CTRL_CH1_COUNT_REG) Number of unserviced end interrupts Position */
#define PROV_DMA_CTRL_CH1_COUNT_REG_INT_COUNT_Msk (0xFu << PROV_DMA_CTRL_CH1_COUNT_REG_INT_COUNT_Pos)  /**< (PROV_DMA_CTRL_CH1_COUNT_REG) Number of unserviced end interrupts Mask */
#define PROV_DMA_CTRL_CH1_COUNT_REG_INT_COUNT(value) (PROV_DMA_CTRL_CH1_COUNT_REG_INT_COUNT_Msk & ((value) << PROV_DMA_CTRL_CH1_COUNT_REG_INT_COUNT_Pos))
#define PROV_DMA_CTRL_CH1_COUNT_REG_MASK    0xF0FFFu                                       /**< \deprecated (PROV_DMA_CTRL_CH1_COUNT_REG) Register MASK  (Use PROV_DMA_CTRL_CH1_COUNT_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH1_COUNT_REG_Msk     0xF0FFFu                                       /**< (PROV_DMA_CTRL_CH1_COUNT_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG : (PROV_DMA_CTRL Offset: 0x1a0) (R/W 8) Channel 1 Interrupt Raw Status (Write 1 to any field to issue interrupt) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Indicates an unserviced channel end interrupt */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  AHB read slave error                     */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  AHB write slave error                    */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  FIFO has been overflown                  */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  FIFO has been underflown                 */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Read timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Write timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  WDT:1;                     /**< bit:      7  Channel active but did not start a burst for 2048 cycles */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_OFFSET 0x1A0                                         /**<  (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) Channel 1 Interrupt Raw Status (Write 1 to any field to issue interrupt)  Offset */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) Channel 1 Interrupt Raw Status (Write 1 to any field to issue interrupt)  Reset Value */

#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) Indicates an unserviced channel end interrupt Position */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) Indicates an unserviced channel end interrupt Mask */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_CH_END PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_CH_END_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) AHB read slave error Position */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) AHB read slave error Mask */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_RD_SLVERR PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) AHB write slave error Position */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) AHB write slave error Mask */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_WR_SLVERR PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) FIFO has been overflown Position */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) FIFO has been overflown Mask */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) FIFO has been underflown Position */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) FIFO has been underflown Mask */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_TIMEOUT_RD PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_TIMEOUT_WR PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) Channel active but did not start a burst for 2048 cycles Position */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) Channel active but did not start a burst for 2048 cycles Mask */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_WDT PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_WDT_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) Register MASK  (Use PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_INT_CLEAR_REG : (PROV_DMA_CTRL Offset: 0x1a4) (R/W 8) Channel 1 Interrupt Clear (Write 1 to clear) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Clear channel end interrupt. Decrements INT_COUNT register */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  Clear AHB read slave error               */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  Clear AHB write slave error              */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  Clears FIFO overflow                     */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  Clears FIFO underflow                    */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Clears Read Timeout                      */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Clears Write Timeout                     */
    uint8_t  WDT:1;                     /**< bit:      7  Clears WDT                               */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_INT_CLEAR_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_OFFSET 0x1A4                                         /**<  (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Channel 1 Interrupt Clear (Write 1 to clear)  Offset */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Channel 1 Interrupt Clear (Write 1 to clear)  Reset Value */

#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clear channel end interrupt. Decrements INT_COUNT register Position */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_CLEAR_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clear channel end interrupt. Decrements INT_COUNT register Mask */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_CH_END PROV_DMA_CTRL_CH1_INT_CLEAR_REG_CH_END_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_CLEAR_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clear AHB read slave error Position */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_CLEAR_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clear AHB read slave error Mask */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_RD_SLVERR PROV_DMA_CTRL_CH1_INT_CLEAR_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_CLEAR_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clear AHB write slave error Position */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_CLEAR_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clear AHB write slave error Mask */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_WR_SLVERR PROV_DMA_CTRL_CH1_INT_CLEAR_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_CLEAR_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clears FIFO overflow Position */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_CLEAR_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clears FIFO overflow Mask */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH1_INT_CLEAR_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_CLEAR_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clears FIFO underflow Position */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_CLEAR_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clears FIFO underflow Mask */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH1_INT_CLEAR_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_CLEAR_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clears Read Timeout Position */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_CLEAR_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clears Read Timeout Mask */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_TIMEOUT_RD PROV_DMA_CTRL_CH1_INT_CLEAR_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_CLEAR_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clears Write Timeout Position */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_CLEAR_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clears Write Timeout Mask */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_TIMEOUT_WR PROV_DMA_CTRL_CH1_INT_CLEAR_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_CLEAR_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clears WDT Position */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_CLEAR_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Clears WDT Mask */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_WDT PROV_DMA_CTRL_CH1_INT_CLEAR_REG_WDT_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_CLEAR_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Register MASK  (Use PROV_DMA_CTRL_CH1_INT_CLEAR_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH1_INT_CLEAR_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH1_INT_CLEAR_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_INT_ENABLE_REG : (PROV_DMA_CTRL Offset: 0x1a8) (R/W 8) Channel 1 Interrupt Enable -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Enables end of channel interrupt         */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  Enables AHB read slave error interrupt   */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  Enables AHB write slave error interrupt  */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  Enables FIFO overflow interrupt          */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  Enables FIFO underflow interrupt         */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Enables AHB Read timeout interrupt       */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Enables AHB Write timeout interrupt      */
    uint8_t  WDT:1;                     /**< bit:      7  Enables WDT interrupt                    */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_INT_ENABLE_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_OFFSET 0x1A8                                         /**<  (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Channel 1 Interrupt Enable  Offset */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Channel 1 Interrupt Enable  Reset Value */

#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables end of channel interrupt Position */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_ENABLE_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables end of channel interrupt Mask */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_CH_END PROV_DMA_CTRL_CH1_INT_ENABLE_REG_CH_END_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_ENABLE_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables AHB read slave error interrupt Position */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_ENABLE_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables AHB read slave error interrupt Mask */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_RD_SLVERR PROV_DMA_CTRL_CH1_INT_ENABLE_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_ENABLE_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables AHB write slave error interrupt Position */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_ENABLE_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables AHB write slave error interrupt Mask */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_WR_SLVERR PROV_DMA_CTRL_CH1_INT_ENABLE_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_ENABLE_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables FIFO overflow interrupt Position */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_ENABLE_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables FIFO overflow interrupt Mask */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH1_INT_ENABLE_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_ENABLE_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables FIFO underflow interrupt Position */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_ENABLE_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables FIFO underflow interrupt Mask */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH1_INT_ENABLE_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_ENABLE_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables AHB Read timeout interrupt Position */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_ENABLE_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables AHB Read timeout interrupt Mask */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_TIMEOUT_RD PROV_DMA_CTRL_CH1_INT_ENABLE_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_ENABLE_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables AHB Write timeout interrupt Position */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_ENABLE_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables AHB Write timeout interrupt Mask */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_TIMEOUT_WR PROV_DMA_CTRL_CH1_INT_ENABLE_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_ENABLE_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables WDT interrupt Position */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_ENABLE_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Enables WDT interrupt Mask */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_WDT PROV_DMA_CTRL_CH1_INT_ENABLE_REG_WDT_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_ENABLE_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Register MASK  (Use PROV_DMA_CTRL_CH1_INT_ENABLE_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH1_INT_ENABLE_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH1_INT_ENABLE_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH1_INT_STATUS_REG : (PROV_DMA_CTRL Offset: 0x1ac) (R/W 8) Channel 1 Interrupt Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Indicates an unserviced channel end interrupt */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  AHB read slave error                     */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  AHB write slave error                    */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  FIFO has been overflown                  */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  FIFO has been underflown                 */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Read timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Write timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  WDT:1;                     /**< bit:      7  Channel active but did not start a burst for 2048 cycles */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH1_INT_STATUS_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_OFFSET 0x1AC                                         /**<  (PROV_DMA_CTRL_CH1_INT_STATUS_REG) Channel 1 Interrupt Status  Offset */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH1_INT_STATUS_REG) Channel 1 Interrupt Status  Reset Value */

#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) Indicates an unserviced channel end interrupt Position */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_STATUS_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) Indicates an unserviced channel end interrupt Mask */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_CH_END PROV_DMA_CTRL_CH1_INT_STATUS_REG_CH_END_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_STATUS_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) AHB read slave error Position */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_STATUS_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) AHB read slave error Mask */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_RD_SLVERR PROV_DMA_CTRL_CH1_INT_STATUS_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_STATUS_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) AHB write slave error Position */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_STATUS_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) AHB write slave error Mask */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_WR_SLVERR PROV_DMA_CTRL_CH1_INT_STATUS_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_STATUS_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) FIFO has been overflown Position */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_STATUS_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) FIFO has been overflown Mask */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH1_INT_STATUS_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_STATUS_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) FIFO has been underflown Position */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_STATUS_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) FIFO has been underflown Mask */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH1_INT_STATUS_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_STATUS_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_STATUS_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_TIMEOUT_RD PROV_DMA_CTRL_CH1_INT_STATUS_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_STATUS_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_STATUS_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_TIMEOUT_WR PROV_DMA_CTRL_CH1_INT_STATUS_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_STATUS_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) Channel active but did not start a burst for 2048 cycles Position */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH1_INT_STATUS_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) Channel active but did not start a burst for 2048 cycles Mask */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_WDT PROV_DMA_CTRL_CH1_INT_STATUS_REG_WDT_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH1_INT_STATUS_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH1_INT_STATUS_REG) Register MASK  (Use PROV_DMA_CTRL_CH1_INT_STATUS_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH1_INT_STATUS_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH1_INT_STATUS_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_CMD_REG0 : (PROV_DMA_CTRL Offset: 0x200) (R/W 32) Channel 2 First Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_START_ADDR:32;          /**< bit:  0..31  Start Address of Read Buffer             */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_CMD_REG0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_CMD_REG0_OFFSET   0x200                                         /**<  (PROV_DMA_CTRL_CH2_CMD_REG0) Channel 2 First Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH2_CMD_REG0_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_CMD_REG0) Channel 2 First Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH2_CMD_REG0_RD_START_ADDR_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_CMD_REG0) Start Address of Read Buffer Position */
#define PROV_DMA_CTRL_CH2_CMD_REG0_RD_START_ADDR_Msk (0xFFFFFFFFu << PROV_DMA_CTRL_CH2_CMD_REG0_RD_START_ADDR_Pos)  /**< (PROV_DMA_CTRL_CH2_CMD_REG0) Start Address of Read Buffer Mask */
#define PROV_DMA_CTRL_CH2_CMD_REG0_RD_START_ADDR(value) (PROV_DMA_CTRL_CH2_CMD_REG0_RD_START_ADDR_Msk & ((value) << PROV_DMA_CTRL_CH2_CMD_REG0_RD_START_ADDR_Pos))
#define PROV_DMA_CTRL_CH2_CMD_REG0_MASK     0xFFFFFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH2_CMD_REG0) Register MASK  (Use PROV_DMA_CTRL_CH2_CMD_REG0_Msk instead)  */
#define PROV_DMA_CTRL_CH2_CMD_REG0_Msk      0xFFFFFFFFu                                    /**< (PROV_DMA_CTRL_CH2_CMD_REG0) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_CMD_REG1 : (PROV_DMA_CTRL Offset: 0x204) (R/W 32) Channel 2 Second Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t WR_START_ADDR:32;          /**< bit:  0..31  Start Address of Write Buffer            */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_CMD_REG1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_CMD_REG1_OFFSET   0x204                                         /**<  (PROV_DMA_CTRL_CH2_CMD_REG1) Channel 2 Second Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH2_CMD_REG1_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_CMD_REG1) Channel 2 Second Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH2_CMD_REG1_WR_START_ADDR_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_CMD_REG1) Start Address of Write Buffer Position */
#define PROV_DMA_CTRL_CH2_CMD_REG1_WR_START_ADDR_Msk (0xFFFFFFFFu << PROV_DMA_CTRL_CH2_CMD_REG1_WR_START_ADDR_Pos)  /**< (PROV_DMA_CTRL_CH2_CMD_REG1) Start Address of Write Buffer Mask */
#define PROV_DMA_CTRL_CH2_CMD_REG1_WR_START_ADDR(value) (PROV_DMA_CTRL_CH2_CMD_REG1_WR_START_ADDR_Msk & ((value) << PROV_DMA_CTRL_CH2_CMD_REG1_WR_START_ADDR_Pos))
#define PROV_DMA_CTRL_CH2_CMD_REG1_MASK     0xFFFFFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH2_CMD_REG1) Register MASK  (Use PROV_DMA_CTRL_CH2_CMD_REG1_Msk instead)  */
#define PROV_DMA_CTRL_CH2_CMD_REG1_Msk      0xFFFFFFFFu                                    /**< (PROV_DMA_CTRL_CH2_CMD_REG1) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_CMD_REG2 : (PROV_DMA_CTRL Offset: 0x208) (R/W 16) Channel 2 Third Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t BUFFER_SIZE:13;            /**< bit:  0..12  Size (in Bytes) of Buffer to Transfer    */
    uint16_t :3;                        /**< bit: 13..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_CMD_REG2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_CMD_REG2_OFFSET   0x208                                         /**<  (PROV_DMA_CTRL_CH2_CMD_REG2) Channel 2 Third Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH2_CMD_REG2_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_CMD_REG2) Channel 2 Third Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH2_CMD_REG2_BUFFER_SIZE_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_CMD_REG2) Size (in Bytes) of Buffer to Transfer Position */
#define PROV_DMA_CTRL_CH2_CMD_REG2_BUFFER_SIZE_Msk (0x1FFFu << PROV_DMA_CTRL_CH2_CMD_REG2_BUFFER_SIZE_Pos)  /**< (PROV_DMA_CTRL_CH2_CMD_REG2) Size (in Bytes) of Buffer to Transfer Mask */
#define PROV_DMA_CTRL_CH2_CMD_REG2_BUFFER_SIZE(value) (PROV_DMA_CTRL_CH2_CMD_REG2_BUFFER_SIZE_Msk & ((value) << PROV_DMA_CTRL_CH2_CMD_REG2_BUFFER_SIZE_Pos))
#define PROV_DMA_CTRL_CH2_CMD_REG2_MASK     0x1FFFu                                        /**< \deprecated (PROV_DMA_CTRL_CH2_CMD_REG2) Register MASK  (Use PROV_DMA_CTRL_CH2_CMD_REG2_Msk instead)  */
#define PROV_DMA_CTRL_CH2_CMD_REG2_Msk      0x1FFFu                                        /**< (PROV_DMA_CTRL_CH2_CMD_REG2) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_CMD_REG3 : (PROV_DMA_CTRL Offset: 0x20c) (R/W 32) Channel 2 Fourth Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CMD_SET_INT:1;             /**< bit:      0  Active High Interrupt Enable once buffer has been transfered */
    uint32_t CMD_LAST:1;                /**< bit:      1  If set, channel stops when buffer done, otherwise load from CMD_NEXT_ADDR */
    uint32_t CMD_NEXT_ADDR:30;          /**< bit:  2..31  Address of next command if CMD_LAST is not set */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_CMD_REG3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_CMD_REG3_OFFSET   0x20C                                         /**<  (PROV_DMA_CTRL_CH2_CMD_REG3) Channel 2 Fourth Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH2_CMD_REG3_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_CMD_REG3) Channel 2 Fourth Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH2_CMD_REG3_CMD_SET_INT_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_CMD_REG3) Active High Interrupt Enable once buffer has been transfered Position */
#define PROV_DMA_CTRL_CH2_CMD_REG3_CMD_SET_INT_Msk (0x1u << PROV_DMA_CTRL_CH2_CMD_REG3_CMD_SET_INT_Pos)  /**< (PROV_DMA_CTRL_CH2_CMD_REG3) Active High Interrupt Enable once buffer has been transfered Mask */
#define PROV_DMA_CTRL_CH2_CMD_REG3_CMD_SET_INT PROV_DMA_CTRL_CH2_CMD_REG3_CMD_SET_INT_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_CMD_REG3_CMD_SET_INT_Msk instead */
#define PROV_DMA_CTRL_CH2_CMD_REG3_CMD_LAST_Pos 1                                              /**< (PROV_DMA_CTRL_CH2_CMD_REG3) If set, channel stops when buffer done, otherwise load from CMD_NEXT_ADDR Position */
#define PROV_DMA_CTRL_CH2_CMD_REG3_CMD_LAST_Msk (0x1u << PROV_DMA_CTRL_CH2_CMD_REG3_CMD_LAST_Pos)  /**< (PROV_DMA_CTRL_CH2_CMD_REG3) If set, channel stops when buffer done, otherwise load from CMD_NEXT_ADDR Mask */
#define PROV_DMA_CTRL_CH2_CMD_REG3_CMD_LAST PROV_DMA_CTRL_CH2_CMD_REG3_CMD_LAST_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_CMD_REG3_CMD_LAST_Msk instead */
#define PROV_DMA_CTRL_CH2_CMD_REG3_CMD_NEXT_ADDR_Pos 2                                              /**< (PROV_DMA_CTRL_CH2_CMD_REG3) Address of next command if CMD_LAST is not set Position */
#define PROV_DMA_CTRL_CH2_CMD_REG3_CMD_NEXT_ADDR_Msk (0x3FFFFFFFu << PROV_DMA_CTRL_CH2_CMD_REG3_CMD_NEXT_ADDR_Pos)  /**< (PROV_DMA_CTRL_CH2_CMD_REG3) Address of next command if CMD_LAST is not set Mask */
#define PROV_DMA_CTRL_CH2_CMD_REG3_CMD_NEXT_ADDR(value) (PROV_DMA_CTRL_CH2_CMD_REG3_CMD_NEXT_ADDR_Msk & ((value) << PROV_DMA_CTRL_CH2_CMD_REG3_CMD_NEXT_ADDR_Pos))
#define PROV_DMA_CTRL_CH2_CMD_REG3_MASK     0xFFFFFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH2_CMD_REG3) Register MASK  (Use PROV_DMA_CTRL_CH2_CMD_REG3_Msk instead)  */
#define PROV_DMA_CTRL_CH2_CMD_REG3_Msk      0xFFFFFFFFu                                    /**< (PROV_DMA_CTRL_CH2_CMD_REG3) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_STATIC_REG0 : (PROV_DMA_CTRL Offset: 0x210) (R/W 32) Channel 2 Static Configuration Read -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_BURST_MAX_SIZE:7;       /**< bit:   0..6  Maximum number of bytes of an AHB read burst */
    uint32_t :9;                        /**< bit:  7..15  Reserved */
    uint32_t RD_TOKENS:6;               /**< bit: 16..21  Number of AHB read commands to issue before channel is released */
    uint32_t :9;                        /**< bit: 22..30  Reserved */
    uint32_t RD_INCR:1;                 /**< bit:     31  If set the controller will increment the next burst address */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_STATIC_REG0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_STATIC_REG0_OFFSET 0x210                                         /**<  (PROV_DMA_CTRL_CH2_STATIC_REG0) Channel 2 Static Configuration Read  Offset */
#define PROV_DMA_CTRL_CH2_STATIC_REG0_RESETVALUE 0x80010000u                                   /**<  (PROV_DMA_CTRL_CH2_STATIC_REG0) Channel 2 Static Configuration Read  Reset Value */

#define PROV_DMA_CTRL_CH2_STATIC_REG0_RD_BURST_MAX_SIZE_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_STATIC_REG0) Maximum number of bytes of an AHB read burst Position */
#define PROV_DMA_CTRL_CH2_STATIC_REG0_RD_BURST_MAX_SIZE_Msk (0x7Fu << PROV_DMA_CTRL_CH2_STATIC_REG0_RD_BURST_MAX_SIZE_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG0) Maximum number of bytes of an AHB read burst Mask */
#define PROV_DMA_CTRL_CH2_STATIC_REG0_RD_BURST_MAX_SIZE(value) (PROV_DMA_CTRL_CH2_STATIC_REG0_RD_BURST_MAX_SIZE_Msk & ((value) << PROV_DMA_CTRL_CH2_STATIC_REG0_RD_BURST_MAX_SIZE_Pos))
#define PROV_DMA_CTRL_CH2_STATIC_REG0_RD_TOKENS_Pos 16                                             /**< (PROV_DMA_CTRL_CH2_STATIC_REG0) Number of AHB read commands to issue before channel is released Position */
#define PROV_DMA_CTRL_CH2_STATIC_REG0_RD_TOKENS_Msk (0x3Fu << PROV_DMA_CTRL_CH2_STATIC_REG0_RD_TOKENS_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG0) Number of AHB read commands to issue before channel is released Mask */
#define PROV_DMA_CTRL_CH2_STATIC_REG0_RD_TOKENS(value) (PROV_DMA_CTRL_CH2_STATIC_REG0_RD_TOKENS_Msk & ((value) << PROV_DMA_CTRL_CH2_STATIC_REG0_RD_TOKENS_Pos))
#define PROV_DMA_CTRL_CH2_STATIC_REG0_RD_INCR_Pos 31                                             /**< (PROV_DMA_CTRL_CH2_STATIC_REG0) If set the controller will increment the next burst address Position */
#define PROV_DMA_CTRL_CH2_STATIC_REG0_RD_INCR_Msk (0x1u << PROV_DMA_CTRL_CH2_STATIC_REG0_RD_INCR_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG0) If set the controller will increment the next burst address Mask */
#define PROV_DMA_CTRL_CH2_STATIC_REG0_RD_INCR PROV_DMA_CTRL_CH2_STATIC_REG0_RD_INCR_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_STATIC_REG0_RD_INCR_Msk instead */
#define PROV_DMA_CTRL_CH2_STATIC_REG0_MASK  0x803F007Fu                                    /**< \deprecated (PROV_DMA_CTRL_CH2_STATIC_REG0) Register MASK  (Use PROV_DMA_CTRL_CH2_STATIC_REG0_Msk instead)  */
#define PROV_DMA_CTRL_CH2_STATIC_REG0_Msk   0x803F007Fu                                    /**< (PROV_DMA_CTRL_CH2_STATIC_REG0) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_STATIC_REG1 : (PROV_DMA_CTRL Offset: 0x214) (R/W 32) Channel 2 Static Configuration Write -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t WR_BURST_MAX_SIZE:7;       /**< bit:   0..6  Maximum number of bytes of an AHB write burst */
    uint32_t :9;                        /**< bit:  7..15  Reserved */
    uint32_t WR_TOKENS:6;               /**< bit: 16..21  Number of AHB write commands to issue before channel is released */
    uint32_t :9;                        /**< bit: 22..30  Reserved */
    uint32_t WR_INCR:1;                 /**< bit:     31  If set the controller will increment the next burst address */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_STATIC_REG1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_STATIC_REG1_OFFSET 0x214                                         /**<  (PROV_DMA_CTRL_CH2_STATIC_REG1) Channel 2 Static Configuration Write  Offset */
#define PROV_DMA_CTRL_CH2_STATIC_REG1_RESETVALUE 0x80010000u                                   /**<  (PROV_DMA_CTRL_CH2_STATIC_REG1) Channel 2 Static Configuration Write  Reset Value */

#define PROV_DMA_CTRL_CH2_STATIC_REG1_WR_BURST_MAX_SIZE_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_STATIC_REG1) Maximum number of bytes of an AHB write burst Position */
#define PROV_DMA_CTRL_CH2_STATIC_REG1_WR_BURST_MAX_SIZE_Msk (0x7Fu << PROV_DMA_CTRL_CH2_STATIC_REG1_WR_BURST_MAX_SIZE_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG1) Maximum number of bytes of an AHB write burst Mask */
#define PROV_DMA_CTRL_CH2_STATIC_REG1_WR_BURST_MAX_SIZE(value) (PROV_DMA_CTRL_CH2_STATIC_REG1_WR_BURST_MAX_SIZE_Msk & ((value) << PROV_DMA_CTRL_CH2_STATIC_REG1_WR_BURST_MAX_SIZE_Pos))
#define PROV_DMA_CTRL_CH2_STATIC_REG1_WR_TOKENS_Pos 16                                             /**< (PROV_DMA_CTRL_CH2_STATIC_REG1) Number of AHB write commands to issue before channel is released Position */
#define PROV_DMA_CTRL_CH2_STATIC_REG1_WR_TOKENS_Msk (0x3Fu << PROV_DMA_CTRL_CH2_STATIC_REG1_WR_TOKENS_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG1) Number of AHB write commands to issue before channel is released Mask */
#define PROV_DMA_CTRL_CH2_STATIC_REG1_WR_TOKENS(value) (PROV_DMA_CTRL_CH2_STATIC_REG1_WR_TOKENS_Msk & ((value) << PROV_DMA_CTRL_CH2_STATIC_REG1_WR_TOKENS_Pos))
#define PROV_DMA_CTRL_CH2_STATIC_REG1_WR_INCR_Pos 31                                             /**< (PROV_DMA_CTRL_CH2_STATIC_REG1) If set the controller will increment the next burst address Position */
#define PROV_DMA_CTRL_CH2_STATIC_REG1_WR_INCR_Msk (0x1u << PROV_DMA_CTRL_CH2_STATIC_REG1_WR_INCR_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG1) If set the controller will increment the next burst address Mask */
#define PROV_DMA_CTRL_CH2_STATIC_REG1_WR_INCR PROV_DMA_CTRL_CH2_STATIC_REG1_WR_INCR_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_STATIC_REG1_WR_INCR_Msk instead */
#define PROV_DMA_CTRL_CH2_STATIC_REG1_MASK  0x803F007Fu                                    /**< \deprecated (PROV_DMA_CTRL_CH2_STATIC_REG1) Register MASK  (Use PROV_DMA_CTRL_CH2_STATIC_REG1_Msk instead)  */
#define PROV_DMA_CTRL_CH2_STATIC_REG1_Msk   0x803F007Fu                                    /**< (PROV_DMA_CTRL_CH2_STATIC_REG1) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_STATIC_REG2 : (PROV_DMA_CTRL Offset: 0x218) (R/W 32) Channel 2 Block Mode -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :16;                       /**< bit:  0..15  Reserved */
    uint32_t JOINT:1;                   /**< bit:     16  If set channel will work in joint mode   */
    uint32_t :11;                       /**< bit: 17..27  Reserved */
    uint32_t END_SWAP:2;                /**< bit: 28..29  Endianness Byte Swapping                 */
    uint32_t :2;                        /**< bit: 30..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_STATIC_REG2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_STATIC_REG2_OFFSET 0x218                                         /**<  (PROV_DMA_CTRL_CH2_STATIC_REG2) Channel 2 Block Mode  Offset */
#define PROV_DMA_CTRL_CH2_STATIC_REG2_RESETVALUE 0x10000u                                      /**<  (PROV_DMA_CTRL_CH2_STATIC_REG2) Channel 2 Block Mode  Reset Value */

#define PROV_DMA_CTRL_CH2_STATIC_REG2_JOINT_Pos 16                                             /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) If set channel will work in joint mode Position */
#define PROV_DMA_CTRL_CH2_STATIC_REG2_JOINT_Msk (0x1u << PROV_DMA_CTRL_CH2_STATIC_REG2_JOINT_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) If set channel will work in joint mode Mask */
#define PROV_DMA_CTRL_CH2_STATIC_REG2_JOINT PROV_DMA_CTRL_CH2_STATIC_REG2_JOINT_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_STATIC_REG2_JOINT_Msk instead */
#define PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_Pos 28                                             /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) Endianness Byte Swapping Position */
#define PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_Msk (0x3u << PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) Endianness Byte Swapping Mask */
#define PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP(value) (PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_Msk & ((value) << PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_Pos))
#define   PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_0_Val 0x0u                                           /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) No Swapping  */
#define   PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_1_Val 0x1u                                           /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) Swap bytes within 16 bits  */
#define   PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_2_Val 0x2u                                           /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) Swap bytes within 32 bits  */
#define   PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_3_Val 0x3u                                           /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) Swap bytes within 64 bits  */
#define PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_0 (PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_0_Val << PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) No Swapping Position  */
#define PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_1 (PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_1_Val << PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) Swap bytes within 16 bits Position  */
#define PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_2 (PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_2_Val << PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) Swap bytes within 32 bits Position  */
#define PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_3 (PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_3_Val << PROV_DMA_CTRL_CH2_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) Swap bytes within 64 bits Position  */
#define PROV_DMA_CTRL_CH2_STATIC_REG2_MASK  0x30010000u                                    /**< \deprecated (PROV_DMA_CTRL_CH2_STATIC_REG2) Register MASK  (Use PROV_DMA_CTRL_CH2_STATIC_REG2_Msk instead)  */
#define PROV_DMA_CTRL_CH2_STATIC_REG2_Msk   0x30010000u                                    /**< (PROV_DMA_CTRL_CH2_STATIC_REG2) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_STATIC_REG4 : (PROV_DMA_CTRL Offset: 0x220) (R/W 32) Channel 2 Static Configuration Peripheral -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_PERIPH_NUM:5;           /**< bit:   0..4  Number of peripheral to read from (0 if memory or no peripheral flow control) */
    uint32_t :3;                        /**< bit:   5..7  Reserved */
    uint32_t RD_PERIPH_DELAY:3;         /**< bit:  8..10  Number of cycles to wait for read request signal to update after issuing the read clear signal */
    uint32_t :5;                        /**< bit: 11..15  Reserved */
    uint32_t WR_PERIPH_NUM:5;           /**< bit: 16..20  Number of peripheral to write from (0 if memory or no peripheral flow control) */
    uint32_t :3;                        /**< bit: 21..23  Reserved */
    uint32_t WR_PERIPH_DELAY:3;         /**< bit: 24..26  Number of cycles to wait for write request signal to update after issuing the write clear signal */
    uint32_t :5;                        /**< bit: 27..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_STATIC_REG4_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_STATIC_REG4_OFFSET 0x220                                         /**<  (PROV_DMA_CTRL_CH2_STATIC_REG4) Channel 2 Static Configuration Peripheral  Offset */
#define PROV_DMA_CTRL_CH2_STATIC_REG4_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_STATIC_REG4) Channel 2 Static Configuration Peripheral  Reset Value */

#define PROV_DMA_CTRL_CH2_STATIC_REG4_RD_PERIPH_NUM_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_STATIC_REG4) Number of peripheral to read from (0 if memory or no peripheral flow control) Position */
#define PROV_DMA_CTRL_CH2_STATIC_REG4_RD_PERIPH_NUM_Msk (0x1Fu << PROV_DMA_CTRL_CH2_STATIC_REG4_RD_PERIPH_NUM_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG4) Number of peripheral to read from (0 if memory or no peripheral flow control) Mask */
#define PROV_DMA_CTRL_CH2_STATIC_REG4_RD_PERIPH_NUM(value) (PROV_DMA_CTRL_CH2_STATIC_REG4_RD_PERIPH_NUM_Msk & ((value) << PROV_DMA_CTRL_CH2_STATIC_REG4_RD_PERIPH_NUM_Pos))
#define PROV_DMA_CTRL_CH2_STATIC_REG4_RD_PERIPH_DELAY_Pos 8                                              /**< (PROV_DMA_CTRL_CH2_STATIC_REG4) Number of cycles to wait for read request signal to update after issuing the read clear signal Position */
#define PROV_DMA_CTRL_CH2_STATIC_REG4_RD_PERIPH_DELAY_Msk (0x7u << PROV_DMA_CTRL_CH2_STATIC_REG4_RD_PERIPH_DELAY_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG4) Number of cycles to wait for read request signal to update after issuing the read clear signal Mask */
#define PROV_DMA_CTRL_CH2_STATIC_REG4_RD_PERIPH_DELAY(value) (PROV_DMA_CTRL_CH2_STATIC_REG4_RD_PERIPH_DELAY_Msk & ((value) << PROV_DMA_CTRL_CH2_STATIC_REG4_RD_PERIPH_DELAY_Pos))
#define PROV_DMA_CTRL_CH2_STATIC_REG4_WR_PERIPH_NUM_Pos 16                                             /**< (PROV_DMA_CTRL_CH2_STATIC_REG4) Number of peripheral to write from (0 if memory or no peripheral flow control) Position */
#define PROV_DMA_CTRL_CH2_STATIC_REG4_WR_PERIPH_NUM_Msk (0x1Fu << PROV_DMA_CTRL_CH2_STATIC_REG4_WR_PERIPH_NUM_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG4) Number of peripheral to write from (0 if memory or no peripheral flow control) Mask */
#define PROV_DMA_CTRL_CH2_STATIC_REG4_WR_PERIPH_NUM(value) (PROV_DMA_CTRL_CH2_STATIC_REG4_WR_PERIPH_NUM_Msk & ((value) << PROV_DMA_CTRL_CH2_STATIC_REG4_WR_PERIPH_NUM_Pos))
#define PROV_DMA_CTRL_CH2_STATIC_REG4_WR_PERIPH_DELAY_Pos 24                                             /**< (PROV_DMA_CTRL_CH2_STATIC_REG4) Number of cycles to wait for write request signal to update after issuing the write clear signal Position */
#define PROV_DMA_CTRL_CH2_STATIC_REG4_WR_PERIPH_DELAY_Msk (0x7u << PROV_DMA_CTRL_CH2_STATIC_REG4_WR_PERIPH_DELAY_Pos)  /**< (PROV_DMA_CTRL_CH2_STATIC_REG4) Number of cycles to wait for write request signal to update after issuing the write clear signal Mask */
#define PROV_DMA_CTRL_CH2_STATIC_REG4_WR_PERIPH_DELAY(value) (PROV_DMA_CTRL_CH2_STATIC_REG4_WR_PERIPH_DELAY_Msk & ((value) << PROV_DMA_CTRL_CH2_STATIC_REG4_WR_PERIPH_DELAY_Pos))
#define PROV_DMA_CTRL_CH2_STATIC_REG4_MASK  0x71F071Fu                                     /**< \deprecated (PROV_DMA_CTRL_CH2_STATIC_REG4) Register MASK  (Use PROV_DMA_CTRL_CH2_STATIC_REG4_Msk instead)  */
#define PROV_DMA_CTRL_CH2_STATIC_REG4_Msk   0x71F071Fu                                     /**< (PROV_DMA_CTRL_CH2_STATIC_REG4) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_RESRICT_REG : (PROV_DMA_CTRL Offset: 0x22c) (R/ 16) Channel 2 Restrictions Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t RD_ALLOW_FULL_FIFO:1;      /**< bit:      0  Read start address does not restrict burst size */
    uint16_t WR_ALLOW_FULL_FIFO:1;      /**< bit:      1  Write start address does not restrict burst size */
    uint16_t ALLOW_FULL_FIFO:1;         /**< bit:      2  Burst sizes can equal data buffer size, otherwise max burst is half data buffer size */
    uint16_t ALLOW_FULL_BURST:1;        /**< bit:      3  Maximum burst of 16 strobes can be used (joint mode only) */
    uint16_t ALLOW_JOINT_BURST:1;       /**< bit:      4  Joint bursts are currently active        */
    uint16_t :3;                        /**< bit:   5..7  Reserved */
    uint16_t SIMPLE_MEM:1;              /**< bit:      8  Configuration is aligned and peripherals are not used */
    uint16_t :7;                        /**< bit:  9..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_RESRICT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_RESRICT_REG_OFFSET 0x22C                                         /**<  (PROV_DMA_CTRL_CH2_RESRICT_REG) Channel 2 Restrictions Status Register  Offset */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_RESRICT_REG) Channel 2 Restrictions Status Register  Reset Value */

#define PROV_DMA_CTRL_CH2_RESRICT_REG_RD_ALLOW_FULL_FIFO_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Read start address does not restrict burst size Position */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_RD_ALLOW_FULL_FIFO_Msk (0x1u << PROV_DMA_CTRL_CH2_RESRICT_REG_RD_ALLOW_FULL_FIFO_Pos)  /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Read start address does not restrict burst size Mask */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_RD_ALLOW_FULL_FIFO PROV_DMA_CTRL_CH2_RESRICT_REG_RD_ALLOW_FULL_FIFO_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_RESRICT_REG_RD_ALLOW_FULL_FIFO_Msk instead */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_WR_ALLOW_FULL_FIFO_Pos 1                                              /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Write start address does not restrict burst size Position */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_WR_ALLOW_FULL_FIFO_Msk (0x1u << PROV_DMA_CTRL_CH2_RESRICT_REG_WR_ALLOW_FULL_FIFO_Pos)  /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Write start address does not restrict burst size Mask */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_WR_ALLOW_FULL_FIFO PROV_DMA_CTRL_CH2_RESRICT_REG_WR_ALLOW_FULL_FIFO_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_RESRICT_REG_WR_ALLOW_FULL_FIFO_Msk instead */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_FULL_FIFO_Pos 2                                              /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Burst sizes can equal data buffer size, otherwise max burst is half data buffer size Position */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_FULL_FIFO_Msk (0x1u << PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_FULL_FIFO_Pos)  /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Burst sizes can equal data buffer size, otherwise max burst is half data buffer size Mask */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_FULL_FIFO PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_FULL_FIFO_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_FULL_FIFO_Msk instead */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_FULL_BURST_Pos 3                                              /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Maximum burst of 16 strobes can be used (joint mode only) Position */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_FULL_BURST_Msk (0x1u << PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_FULL_BURST_Pos)  /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Maximum burst of 16 strobes can be used (joint mode only) Mask */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_FULL_BURST PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_FULL_BURST_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_FULL_BURST_Msk instead */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_JOINT_BURST_Pos 4                                              /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Joint bursts are currently active Position */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_JOINT_BURST_Msk (0x1u << PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_JOINT_BURST_Pos)  /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Joint bursts are currently active Mask */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_JOINT_BURST PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_JOINT_BURST_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_RESRICT_REG_ALLOW_JOINT_BURST_Msk instead */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_SIMPLE_MEM_Pos 8                                              /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Configuration is aligned and peripherals are not used Position */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_SIMPLE_MEM_Msk (0x1u << PROV_DMA_CTRL_CH2_RESRICT_REG_SIMPLE_MEM_Pos)  /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Configuration is aligned and peripherals are not used Mask */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_SIMPLE_MEM PROV_DMA_CTRL_CH2_RESRICT_REG_SIMPLE_MEM_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_RESRICT_REG_SIMPLE_MEM_Msk instead */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_MASK  0x11Fu                                         /**< \deprecated (PROV_DMA_CTRL_CH2_RESRICT_REG) Register MASK  (Use PROV_DMA_CTRL_CH2_RESRICT_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH2_RESRICT_REG_Msk   0x11Fu                                         /**< (PROV_DMA_CTRL_CH2_RESRICT_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG : (PROV_DMA_CTRL Offset: 0x238) (R/ 32) Channel 2 FIFO Fullness Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_GAP:13;                 /**< bit:  0..12  Remaining space (in bytes) in FIFO for read data */
    uint32_t :3;                        /**< bit: 13..15  Reserved */
    uint32_t WR_FULLNESS:13;            /**< bit: 16..28  Occupied space (in bytes) in FIFO by write data */
    uint32_t :3;                        /**< bit: 29..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_OFFSET 0x238                                         /**<  (PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG) Channel 2 FIFO Fullness Status Register  Offset */
#define PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG) Channel 2 FIFO Fullness Status Register  Reset Value */

#define PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_RD_GAP_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG) Remaining space (in bytes) in FIFO for read data Position */
#define PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_RD_GAP_Msk (0x1FFFu << PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_RD_GAP_Pos)  /**< (PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG) Remaining space (in bytes) in FIFO for read data Mask */
#define PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_RD_GAP(value) (PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_RD_GAP_Msk & ((value) << PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_RD_GAP_Pos))
#define PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_WR_FULLNESS_Pos 16                                             /**< (PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG) Occupied space (in bytes) in FIFO by write data Position */
#define PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_WR_FULLNESS_Msk (0x1FFFu << PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_WR_FULLNESS_Pos)  /**< (PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG) Occupied space (in bytes) in FIFO by write data Mask */
#define PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_WR_FULLNESS(value) (PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_WR_FULLNESS_Msk & ((value) << PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_WR_FULLNESS_Pos))
#define PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_MASK 0x1FFF1FFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG) Register MASK  (Use PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_Msk 0x1FFF1FFFu                                    /**< (PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_CH_ENABLE_REG : (PROV_DMA_CTRL Offset: 0x240) (R/W 8) Channel 2 Channel Enable Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH2_CH_ENABLE_REG:1;       /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_CH_ENABLE_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_CH_ENABLE_REG_OFFSET 0x240                                         /**<  (PROV_DMA_CTRL_CH2_CH_ENABLE_REG) Channel 2 Channel Enable Register  Offset */
#define PROV_DMA_CTRL_CH2_CH_ENABLE_REG_RESETVALUE 0x01u                                         /**<  (PROV_DMA_CTRL_CH2_CH_ENABLE_REG) Channel 2 Channel Enable Register  Reset Value */

#define PROV_DMA_CTRL_CH2_CH_ENABLE_REG_CH2_CH_ENABLE_REG_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_CH_ENABLE_REG)  Position */
#define PROV_DMA_CTRL_CH2_CH_ENABLE_REG_CH2_CH_ENABLE_REG_Msk (0x1u << PROV_DMA_CTRL_CH2_CH_ENABLE_REG_CH2_CH_ENABLE_REG_Pos)  /**< (PROV_DMA_CTRL_CH2_CH_ENABLE_REG)  Mask */
#define PROV_DMA_CTRL_CH2_CH_ENABLE_REG_CH2_CH_ENABLE_REG PROV_DMA_CTRL_CH2_CH_ENABLE_REG_CH2_CH_ENABLE_REG_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_CH_ENABLE_REG_CH2_CH_ENABLE_REG_Msk instead */
#define PROV_DMA_CTRL_CH2_CH_ENABLE_REG_MASK 0x01u                                          /**< \deprecated (PROV_DMA_CTRL_CH2_CH_ENABLE_REG) Register MASK  (Use PROV_DMA_CTRL_CH2_CH_ENABLE_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH2_CH_ENABLE_REG_Msk 0x01u                                          /**< (PROV_DMA_CTRL_CH2_CH_ENABLE_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_CH_START_REG : (PROV_DMA_CTRL Offset: 0x244) (/W 8) Channel 2 Channel Start Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH2_CH_START_REG:1;        /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_CH_START_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_CH_START_REG_OFFSET 0x244                                         /**<  (PROV_DMA_CTRL_CH2_CH_START_REG) Channel 2 Channel Start Register  Offset */
#define PROV_DMA_CTRL_CH2_CH_START_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_CH_START_REG) Channel 2 Channel Start Register  Reset Value */

#define PROV_DMA_CTRL_CH2_CH_START_REG_CH2_CH_START_REG_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_CH_START_REG)  Position */
#define PROV_DMA_CTRL_CH2_CH_START_REG_CH2_CH_START_REG_Msk (0x1u << PROV_DMA_CTRL_CH2_CH_START_REG_CH2_CH_START_REG_Pos)  /**< (PROV_DMA_CTRL_CH2_CH_START_REG)  Mask */
#define PROV_DMA_CTRL_CH2_CH_START_REG_CH2_CH_START_REG PROV_DMA_CTRL_CH2_CH_START_REG_CH2_CH_START_REG_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_CH_START_REG_CH2_CH_START_REG_Msk instead */
#define PROV_DMA_CTRL_CH2_CH_START_REG_MASK 0x01u                                          /**< \deprecated (PROV_DMA_CTRL_CH2_CH_START_REG) Register MASK  (Use PROV_DMA_CTRL_CH2_CH_START_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH2_CH_START_REG_Msk  0x01u                                          /**< (PROV_DMA_CTRL_CH2_CH_START_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_CH_ACTIVE_REG : (PROV_DMA_CTRL Offset: 0x248) (R/ 8) Channel 2 Channel Active Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_RD_ACTIVE:1;            /**< bit:      0  Set if channel is enabled and all read data has been received */
    uint8_t  CH_WR_ACTIVE:1;            /**< bit:      1  Set if channel is enabled and all write data has been transfered */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_OFFSET 0x248                                         /**<  (PROV_DMA_CTRL_CH2_CH_ACTIVE_REG) Channel 2 Channel Active Status Register  Offset */
#define PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_CH_ACTIVE_REG) Channel 2 Channel Active Status Register  Reset Value */

#define PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_CH_RD_ACTIVE_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_CH_ACTIVE_REG) Set if channel is enabled and all read data has been received Position */
#define PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_CH_RD_ACTIVE_Msk (0x1u << PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_CH_RD_ACTIVE_Pos)  /**< (PROV_DMA_CTRL_CH2_CH_ACTIVE_REG) Set if channel is enabled and all read data has been received Mask */
#define PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_CH_RD_ACTIVE PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_CH_RD_ACTIVE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_CH_RD_ACTIVE_Msk instead */
#define PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_CH_WR_ACTIVE_Pos 1                                              /**< (PROV_DMA_CTRL_CH2_CH_ACTIVE_REG) Set if channel is enabled and all write data has been transfered Position */
#define PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_CH_WR_ACTIVE_Msk (0x1u << PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_CH_WR_ACTIVE_Pos)  /**< (PROV_DMA_CTRL_CH2_CH_ACTIVE_REG) Set if channel is enabled and all write data has been transfered Mask */
#define PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_CH_WR_ACTIVE PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_CH_WR_ACTIVE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_CH_WR_ACTIVE_Msk instead */
#define PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_MASK 0x03u                                          /**< \deprecated (PROV_DMA_CTRL_CH2_CH_ACTIVE_REG) Register MASK  (Use PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_Msk 0x03u                                          /**< (PROV_DMA_CTRL_CH2_CH_ACTIVE_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_COUNT_REG : (PROV_DMA_CTRL Offset: 0x250) (R/ 32) Channel 2 Buffer Counter Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BUFF_COUNT:12;             /**< bit:  0..11  Number of buffers transferred by channel since started */
    uint32_t :4;                        /**< bit: 12..15  Reserved */
    uint32_t INT_COUNT:4;               /**< bit: 16..19  Number of unserviced end interrupts      */
    uint32_t :12;                       /**< bit: 20..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_COUNT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_COUNT_REG_OFFSET  0x250                                         /**<  (PROV_DMA_CTRL_CH2_COUNT_REG) Channel 2 Buffer Counter Status Register  Offset */
#define PROV_DMA_CTRL_CH2_COUNT_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_COUNT_REG) Channel 2 Buffer Counter Status Register  Reset Value */

#define PROV_DMA_CTRL_CH2_COUNT_REG_BUFF_COUNT_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_COUNT_REG) Number of buffers transferred by channel since started Position */
#define PROV_DMA_CTRL_CH2_COUNT_REG_BUFF_COUNT_Msk (0xFFFu << PROV_DMA_CTRL_CH2_COUNT_REG_BUFF_COUNT_Pos)  /**< (PROV_DMA_CTRL_CH2_COUNT_REG) Number of buffers transferred by channel since started Mask */
#define PROV_DMA_CTRL_CH2_COUNT_REG_BUFF_COUNT(value) (PROV_DMA_CTRL_CH2_COUNT_REG_BUFF_COUNT_Msk & ((value) << PROV_DMA_CTRL_CH2_COUNT_REG_BUFF_COUNT_Pos))
#define PROV_DMA_CTRL_CH2_COUNT_REG_INT_COUNT_Pos 16                                             /**< (PROV_DMA_CTRL_CH2_COUNT_REG) Number of unserviced end interrupts Position */
#define PROV_DMA_CTRL_CH2_COUNT_REG_INT_COUNT_Msk (0xFu << PROV_DMA_CTRL_CH2_COUNT_REG_INT_COUNT_Pos)  /**< (PROV_DMA_CTRL_CH2_COUNT_REG) Number of unserviced end interrupts Mask */
#define PROV_DMA_CTRL_CH2_COUNT_REG_INT_COUNT(value) (PROV_DMA_CTRL_CH2_COUNT_REG_INT_COUNT_Msk & ((value) << PROV_DMA_CTRL_CH2_COUNT_REG_INT_COUNT_Pos))
#define PROV_DMA_CTRL_CH2_COUNT_REG_MASK    0xF0FFFu                                       /**< \deprecated (PROV_DMA_CTRL_CH2_COUNT_REG) Register MASK  (Use PROV_DMA_CTRL_CH2_COUNT_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH2_COUNT_REG_Msk     0xF0FFFu                                       /**< (PROV_DMA_CTRL_CH2_COUNT_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG : (PROV_DMA_CTRL Offset: 0x2a0) (R/W 8) Channel 2 Interrupt Raw Status (Write 1 to any field to issue interrupt) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Indicates an unserviced channel end interrupt */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  AHB read slave error                     */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  AHB write slave error                    */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  FIFO has been overflown                  */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  FIFO has been underflown                 */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Read timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Write timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  WDT:1;                     /**< bit:      7  Channel active but did not start a burst for 2048 cycles */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_OFFSET 0x2A0                                         /**<  (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) Channel 2 Interrupt Raw Status (Write 1 to any field to issue interrupt)  Offset */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) Channel 2 Interrupt Raw Status (Write 1 to any field to issue interrupt)  Reset Value */

#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) Indicates an unserviced channel end interrupt Position */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) Indicates an unserviced channel end interrupt Mask */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_CH_END PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_CH_END_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) AHB read slave error Position */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) AHB read slave error Mask */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_RD_SLVERR PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) AHB write slave error Position */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) AHB write slave error Mask */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_WR_SLVERR PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) FIFO has been overflown Position */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) FIFO has been overflown Mask */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) FIFO has been underflown Position */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) FIFO has been underflown Mask */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_TIMEOUT_RD PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_TIMEOUT_WR PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) Channel active but did not start a burst for 2048 cycles Position */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) Channel active but did not start a burst for 2048 cycles Mask */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_WDT PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_WDT_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) Register MASK  (Use PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_INT_CLEAR_REG : (PROV_DMA_CTRL Offset: 0x2a4) (R/W 8) Channel 2 Interrupt Clear (Write 1 to clear) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Clear channel end interrupt. Decrements INT_COUNT register */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  Clear AHB read slave error               */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  Clear AHB write slave error              */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  Clears FIFO overflow                     */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  Clears FIFO underflow                    */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Clears Read Timeout                      */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Clears Write Timeout                     */
    uint8_t  WDT:1;                     /**< bit:      7  Clears WDT                               */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_INT_CLEAR_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_OFFSET 0x2A4                                         /**<  (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Channel 2 Interrupt Clear (Write 1 to clear)  Offset */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Channel 2 Interrupt Clear (Write 1 to clear)  Reset Value */

#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clear channel end interrupt. Decrements INT_COUNT register Position */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_CLEAR_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clear channel end interrupt. Decrements INT_COUNT register Mask */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_CH_END PROV_DMA_CTRL_CH2_INT_CLEAR_REG_CH_END_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_CLEAR_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clear AHB read slave error Position */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_CLEAR_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clear AHB read slave error Mask */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_RD_SLVERR PROV_DMA_CTRL_CH2_INT_CLEAR_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_CLEAR_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clear AHB write slave error Position */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_CLEAR_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clear AHB write slave error Mask */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_WR_SLVERR PROV_DMA_CTRL_CH2_INT_CLEAR_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_CLEAR_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clears FIFO overflow Position */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_CLEAR_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clears FIFO overflow Mask */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH2_INT_CLEAR_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_CLEAR_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clears FIFO underflow Position */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_CLEAR_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clears FIFO underflow Mask */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH2_INT_CLEAR_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_CLEAR_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clears Read Timeout Position */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_CLEAR_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clears Read Timeout Mask */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_TIMEOUT_RD PROV_DMA_CTRL_CH2_INT_CLEAR_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_CLEAR_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clears Write Timeout Position */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_CLEAR_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clears Write Timeout Mask */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_TIMEOUT_WR PROV_DMA_CTRL_CH2_INT_CLEAR_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_CLEAR_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clears WDT Position */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_CLEAR_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Clears WDT Mask */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_WDT PROV_DMA_CTRL_CH2_INT_CLEAR_REG_WDT_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_CLEAR_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Register MASK  (Use PROV_DMA_CTRL_CH2_INT_CLEAR_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH2_INT_CLEAR_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH2_INT_CLEAR_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_INT_ENABLE_REG : (PROV_DMA_CTRL Offset: 0x2a8) (R/W 8) Channel 2 Interrupt Enable -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Enables end of channel interrupt         */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  Enables AHB read slave error interrupt   */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  Enables AHB write slave error interrupt  */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  Enables FIFO overflow interrupt          */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  Enables FIFO underflow interrupt         */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Enables AHB Read timeout interrupt       */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Enables AHB Write timeout interrupt      */
    uint8_t  WDT:1;                     /**< bit:      7  Enables WDT interrupt                    */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_INT_ENABLE_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_OFFSET 0x2A8                                         /**<  (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Channel 2 Interrupt Enable  Offset */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Channel 2 Interrupt Enable  Reset Value */

#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables end of channel interrupt Position */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_ENABLE_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables end of channel interrupt Mask */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_CH_END PROV_DMA_CTRL_CH2_INT_ENABLE_REG_CH_END_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_ENABLE_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables AHB read slave error interrupt Position */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_ENABLE_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables AHB read slave error interrupt Mask */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_RD_SLVERR PROV_DMA_CTRL_CH2_INT_ENABLE_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_ENABLE_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables AHB write slave error interrupt Position */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_ENABLE_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables AHB write slave error interrupt Mask */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_WR_SLVERR PROV_DMA_CTRL_CH2_INT_ENABLE_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_ENABLE_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables FIFO overflow interrupt Position */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_ENABLE_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables FIFO overflow interrupt Mask */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH2_INT_ENABLE_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_ENABLE_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables FIFO underflow interrupt Position */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_ENABLE_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables FIFO underflow interrupt Mask */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH2_INT_ENABLE_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_ENABLE_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables AHB Read timeout interrupt Position */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_ENABLE_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables AHB Read timeout interrupt Mask */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_TIMEOUT_RD PROV_DMA_CTRL_CH2_INT_ENABLE_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_ENABLE_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables AHB Write timeout interrupt Position */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_ENABLE_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables AHB Write timeout interrupt Mask */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_TIMEOUT_WR PROV_DMA_CTRL_CH2_INT_ENABLE_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_ENABLE_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables WDT interrupt Position */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_ENABLE_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Enables WDT interrupt Mask */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_WDT PROV_DMA_CTRL_CH2_INT_ENABLE_REG_WDT_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_ENABLE_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Register MASK  (Use PROV_DMA_CTRL_CH2_INT_ENABLE_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH2_INT_ENABLE_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH2_INT_ENABLE_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH2_INT_STATUS_REG : (PROV_DMA_CTRL Offset: 0x2ac) (R/W 8) Channel 2 Interrupt Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Indicates an unserviced channel end interrupt */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  AHB read slave error                     */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  AHB write slave error                    */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  FIFO has been overflown                  */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  FIFO has been underflown                 */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Read timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Write timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  WDT:1;                     /**< bit:      7  Channel active but did not start a burst for 2048 cycles */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH2_INT_STATUS_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_OFFSET 0x2AC                                         /**<  (PROV_DMA_CTRL_CH2_INT_STATUS_REG) Channel 2 Interrupt Status  Offset */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH2_INT_STATUS_REG) Channel 2 Interrupt Status  Reset Value */

#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) Indicates an unserviced channel end interrupt Position */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_STATUS_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) Indicates an unserviced channel end interrupt Mask */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_CH_END PROV_DMA_CTRL_CH2_INT_STATUS_REG_CH_END_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_STATUS_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) AHB read slave error Position */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_STATUS_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) AHB read slave error Mask */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_RD_SLVERR PROV_DMA_CTRL_CH2_INT_STATUS_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_STATUS_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) AHB write slave error Position */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_STATUS_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) AHB write slave error Mask */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_WR_SLVERR PROV_DMA_CTRL_CH2_INT_STATUS_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_STATUS_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) FIFO has been overflown Position */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_STATUS_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) FIFO has been overflown Mask */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH2_INT_STATUS_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_STATUS_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) FIFO has been underflown Position */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_STATUS_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) FIFO has been underflown Mask */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH2_INT_STATUS_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_STATUS_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_STATUS_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_TIMEOUT_RD PROV_DMA_CTRL_CH2_INT_STATUS_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_STATUS_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_STATUS_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_TIMEOUT_WR PROV_DMA_CTRL_CH2_INT_STATUS_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_STATUS_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) Channel active but did not start a burst for 2048 cycles Position */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH2_INT_STATUS_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) Channel active but did not start a burst for 2048 cycles Mask */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_WDT PROV_DMA_CTRL_CH2_INT_STATUS_REG_WDT_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH2_INT_STATUS_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH2_INT_STATUS_REG) Register MASK  (Use PROV_DMA_CTRL_CH2_INT_STATUS_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH2_INT_STATUS_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH2_INT_STATUS_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_CMD_REG0 : (PROV_DMA_CTRL Offset: 0x300) (R/W 32) Channel 3 First Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_START_ADDR:32;          /**< bit:  0..31  Start Address of Read Buffer             */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_CMD_REG0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_CMD_REG0_OFFSET   0x300                                         /**<  (PROV_DMA_CTRL_CH3_CMD_REG0) Channel 3 First Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH3_CMD_REG0_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_CMD_REG0) Channel 3 First Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH3_CMD_REG0_RD_START_ADDR_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_CMD_REG0) Start Address of Read Buffer Position */
#define PROV_DMA_CTRL_CH3_CMD_REG0_RD_START_ADDR_Msk (0xFFFFFFFFu << PROV_DMA_CTRL_CH3_CMD_REG0_RD_START_ADDR_Pos)  /**< (PROV_DMA_CTRL_CH3_CMD_REG0) Start Address of Read Buffer Mask */
#define PROV_DMA_CTRL_CH3_CMD_REG0_RD_START_ADDR(value) (PROV_DMA_CTRL_CH3_CMD_REG0_RD_START_ADDR_Msk & ((value) << PROV_DMA_CTRL_CH3_CMD_REG0_RD_START_ADDR_Pos))
#define PROV_DMA_CTRL_CH3_CMD_REG0_MASK     0xFFFFFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH3_CMD_REG0) Register MASK  (Use PROV_DMA_CTRL_CH3_CMD_REG0_Msk instead)  */
#define PROV_DMA_CTRL_CH3_CMD_REG0_Msk      0xFFFFFFFFu                                    /**< (PROV_DMA_CTRL_CH3_CMD_REG0) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_CMD_REG1 : (PROV_DMA_CTRL Offset: 0x304) (R/W 32) Channel 3 Second Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t WR_START_ADDR:32;          /**< bit:  0..31  Start Address of Write Buffer            */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_CMD_REG1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_CMD_REG1_OFFSET   0x304                                         /**<  (PROV_DMA_CTRL_CH3_CMD_REG1) Channel 3 Second Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH3_CMD_REG1_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_CMD_REG1) Channel 3 Second Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH3_CMD_REG1_WR_START_ADDR_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_CMD_REG1) Start Address of Write Buffer Position */
#define PROV_DMA_CTRL_CH3_CMD_REG1_WR_START_ADDR_Msk (0xFFFFFFFFu << PROV_DMA_CTRL_CH3_CMD_REG1_WR_START_ADDR_Pos)  /**< (PROV_DMA_CTRL_CH3_CMD_REG1) Start Address of Write Buffer Mask */
#define PROV_DMA_CTRL_CH3_CMD_REG1_WR_START_ADDR(value) (PROV_DMA_CTRL_CH3_CMD_REG1_WR_START_ADDR_Msk & ((value) << PROV_DMA_CTRL_CH3_CMD_REG1_WR_START_ADDR_Pos))
#define PROV_DMA_CTRL_CH3_CMD_REG1_MASK     0xFFFFFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH3_CMD_REG1) Register MASK  (Use PROV_DMA_CTRL_CH3_CMD_REG1_Msk instead)  */
#define PROV_DMA_CTRL_CH3_CMD_REG1_Msk      0xFFFFFFFFu                                    /**< (PROV_DMA_CTRL_CH3_CMD_REG1) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_CMD_REG2 : (PROV_DMA_CTRL Offset: 0x308) (R/W 16) Channel 3 Third Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t BUFFER_SIZE:13;            /**< bit:  0..12  Size (in Bytes) of Buffer to Transfer    */
    uint16_t :3;                        /**< bit: 13..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_CMD_REG2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_CMD_REG2_OFFSET   0x308                                         /**<  (PROV_DMA_CTRL_CH3_CMD_REG2) Channel 3 Third Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH3_CMD_REG2_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_CMD_REG2) Channel 3 Third Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH3_CMD_REG2_BUFFER_SIZE_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_CMD_REG2) Size (in Bytes) of Buffer to Transfer Position */
#define PROV_DMA_CTRL_CH3_CMD_REG2_BUFFER_SIZE_Msk (0x1FFFu << PROV_DMA_CTRL_CH3_CMD_REG2_BUFFER_SIZE_Pos)  /**< (PROV_DMA_CTRL_CH3_CMD_REG2) Size (in Bytes) of Buffer to Transfer Mask */
#define PROV_DMA_CTRL_CH3_CMD_REG2_BUFFER_SIZE(value) (PROV_DMA_CTRL_CH3_CMD_REG2_BUFFER_SIZE_Msk & ((value) << PROV_DMA_CTRL_CH3_CMD_REG2_BUFFER_SIZE_Pos))
#define PROV_DMA_CTRL_CH3_CMD_REG2_MASK     0x1FFFu                                        /**< \deprecated (PROV_DMA_CTRL_CH3_CMD_REG2) Register MASK  (Use PROV_DMA_CTRL_CH3_CMD_REG2_Msk instead)  */
#define PROV_DMA_CTRL_CH3_CMD_REG2_Msk      0x1FFFu                                        /**< (PROV_DMA_CTRL_CH3_CMD_REG2) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_CMD_REG3 : (PROV_DMA_CTRL Offset: 0x30c) (R/W 32) Channel 3 Fourth Line Channel Command -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CMD_SET_INT:1;             /**< bit:      0  Active High Interrupt Enable once buffer has been transfered */
    uint32_t CMD_LAST:1;                /**< bit:      1  If set, channel stops when buffer done, otherwise load from CMD_NEXT_ADDR */
    uint32_t CMD_NEXT_ADDR:30;          /**< bit:  2..31  Address of next command if CMD_LAST is not set */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_CMD_REG3_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_CMD_REG3_OFFSET   0x30C                                         /**<  (PROV_DMA_CTRL_CH3_CMD_REG3) Channel 3 Fourth Line Channel Command  Offset */
#define PROV_DMA_CTRL_CH3_CMD_REG3_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_CMD_REG3) Channel 3 Fourth Line Channel Command  Reset Value */

#define PROV_DMA_CTRL_CH3_CMD_REG3_CMD_SET_INT_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_CMD_REG3) Active High Interrupt Enable once buffer has been transfered Position */
#define PROV_DMA_CTRL_CH3_CMD_REG3_CMD_SET_INT_Msk (0x1u << PROV_DMA_CTRL_CH3_CMD_REG3_CMD_SET_INT_Pos)  /**< (PROV_DMA_CTRL_CH3_CMD_REG3) Active High Interrupt Enable once buffer has been transfered Mask */
#define PROV_DMA_CTRL_CH3_CMD_REG3_CMD_SET_INT PROV_DMA_CTRL_CH3_CMD_REG3_CMD_SET_INT_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_CMD_REG3_CMD_SET_INT_Msk instead */
#define PROV_DMA_CTRL_CH3_CMD_REG3_CMD_LAST_Pos 1                                              /**< (PROV_DMA_CTRL_CH3_CMD_REG3) If set, channel stops when buffer done, otherwise load from CMD_NEXT_ADDR Position */
#define PROV_DMA_CTRL_CH3_CMD_REG3_CMD_LAST_Msk (0x1u << PROV_DMA_CTRL_CH3_CMD_REG3_CMD_LAST_Pos)  /**< (PROV_DMA_CTRL_CH3_CMD_REG3) If set, channel stops when buffer done, otherwise load from CMD_NEXT_ADDR Mask */
#define PROV_DMA_CTRL_CH3_CMD_REG3_CMD_LAST PROV_DMA_CTRL_CH3_CMD_REG3_CMD_LAST_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_CMD_REG3_CMD_LAST_Msk instead */
#define PROV_DMA_CTRL_CH3_CMD_REG3_CMD_NEXT_ADDR_Pos 2                                              /**< (PROV_DMA_CTRL_CH3_CMD_REG3) Address of next command if CMD_LAST is not set Position */
#define PROV_DMA_CTRL_CH3_CMD_REG3_CMD_NEXT_ADDR_Msk (0x3FFFFFFFu << PROV_DMA_CTRL_CH3_CMD_REG3_CMD_NEXT_ADDR_Pos)  /**< (PROV_DMA_CTRL_CH3_CMD_REG3) Address of next command if CMD_LAST is not set Mask */
#define PROV_DMA_CTRL_CH3_CMD_REG3_CMD_NEXT_ADDR(value) (PROV_DMA_CTRL_CH3_CMD_REG3_CMD_NEXT_ADDR_Msk & ((value) << PROV_DMA_CTRL_CH3_CMD_REG3_CMD_NEXT_ADDR_Pos))
#define PROV_DMA_CTRL_CH3_CMD_REG3_MASK     0xFFFFFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH3_CMD_REG3) Register MASK  (Use PROV_DMA_CTRL_CH3_CMD_REG3_Msk instead)  */
#define PROV_DMA_CTRL_CH3_CMD_REG3_Msk      0xFFFFFFFFu                                    /**< (PROV_DMA_CTRL_CH3_CMD_REG3) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_STATIC_REG0 : (PROV_DMA_CTRL Offset: 0x310) (R/W 32) Channel 3 Static Configuration Read -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_BURST_MAX_SIZE:7;       /**< bit:   0..6  Maximum number of bytes of an AHB read burst */
    uint32_t :9;                        /**< bit:  7..15  Reserved */
    uint32_t RD_TOKENS:6;               /**< bit: 16..21  Number of AHB read commands to issue before channel is released */
    uint32_t :9;                        /**< bit: 22..30  Reserved */
    uint32_t RD_INCR:1;                 /**< bit:     31  If set the controller will increment the next burst address */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_STATIC_REG0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_STATIC_REG0_OFFSET 0x310                                         /**<  (PROV_DMA_CTRL_CH3_STATIC_REG0) Channel 3 Static Configuration Read  Offset */
#define PROV_DMA_CTRL_CH3_STATIC_REG0_RESETVALUE 0x80010000u                                   /**<  (PROV_DMA_CTRL_CH3_STATIC_REG0) Channel 3 Static Configuration Read  Reset Value */

#define PROV_DMA_CTRL_CH3_STATIC_REG0_RD_BURST_MAX_SIZE_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_STATIC_REG0) Maximum number of bytes of an AHB read burst Position */
#define PROV_DMA_CTRL_CH3_STATIC_REG0_RD_BURST_MAX_SIZE_Msk (0x7Fu << PROV_DMA_CTRL_CH3_STATIC_REG0_RD_BURST_MAX_SIZE_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG0) Maximum number of bytes of an AHB read burst Mask */
#define PROV_DMA_CTRL_CH3_STATIC_REG0_RD_BURST_MAX_SIZE(value) (PROV_DMA_CTRL_CH3_STATIC_REG0_RD_BURST_MAX_SIZE_Msk & ((value) << PROV_DMA_CTRL_CH3_STATIC_REG0_RD_BURST_MAX_SIZE_Pos))
#define PROV_DMA_CTRL_CH3_STATIC_REG0_RD_TOKENS_Pos 16                                             /**< (PROV_DMA_CTRL_CH3_STATIC_REG0) Number of AHB read commands to issue before channel is released Position */
#define PROV_DMA_CTRL_CH3_STATIC_REG0_RD_TOKENS_Msk (0x3Fu << PROV_DMA_CTRL_CH3_STATIC_REG0_RD_TOKENS_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG0) Number of AHB read commands to issue before channel is released Mask */
#define PROV_DMA_CTRL_CH3_STATIC_REG0_RD_TOKENS(value) (PROV_DMA_CTRL_CH3_STATIC_REG0_RD_TOKENS_Msk & ((value) << PROV_DMA_CTRL_CH3_STATIC_REG0_RD_TOKENS_Pos))
#define PROV_DMA_CTRL_CH3_STATIC_REG0_RD_INCR_Pos 31                                             /**< (PROV_DMA_CTRL_CH3_STATIC_REG0) If set the controller will increment the next burst address Position */
#define PROV_DMA_CTRL_CH3_STATIC_REG0_RD_INCR_Msk (0x1u << PROV_DMA_CTRL_CH3_STATIC_REG0_RD_INCR_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG0) If set the controller will increment the next burst address Mask */
#define PROV_DMA_CTRL_CH3_STATIC_REG0_RD_INCR PROV_DMA_CTRL_CH3_STATIC_REG0_RD_INCR_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_STATIC_REG0_RD_INCR_Msk instead */
#define PROV_DMA_CTRL_CH3_STATIC_REG0_MASK  0x803F007Fu                                    /**< \deprecated (PROV_DMA_CTRL_CH3_STATIC_REG0) Register MASK  (Use PROV_DMA_CTRL_CH3_STATIC_REG0_Msk instead)  */
#define PROV_DMA_CTRL_CH3_STATIC_REG0_Msk   0x803F007Fu                                    /**< (PROV_DMA_CTRL_CH3_STATIC_REG0) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_STATIC_REG1 : (PROV_DMA_CTRL Offset: 0x314) (R/W 32) Channel 3 Static Configuration Write -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t WR_BURST_MAX_SIZE:7;       /**< bit:   0..6  Maximum number of bytes of an AHB write burst */
    uint32_t :9;                        /**< bit:  7..15  Reserved */
    uint32_t WR_TOKENS:6;               /**< bit: 16..21  Number of AHB write commands to issue before channel is released */
    uint32_t :9;                        /**< bit: 22..30  Reserved */
    uint32_t WR_INCR:1;                 /**< bit:     31  If set the controller will increment the next burst address */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_STATIC_REG1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_STATIC_REG1_OFFSET 0x314                                         /**<  (PROV_DMA_CTRL_CH3_STATIC_REG1) Channel 3 Static Configuration Write  Offset */
#define PROV_DMA_CTRL_CH3_STATIC_REG1_RESETVALUE 0x80010000u                                   /**<  (PROV_DMA_CTRL_CH3_STATIC_REG1) Channel 3 Static Configuration Write  Reset Value */

#define PROV_DMA_CTRL_CH3_STATIC_REG1_WR_BURST_MAX_SIZE_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_STATIC_REG1) Maximum number of bytes of an AHB write burst Position */
#define PROV_DMA_CTRL_CH3_STATIC_REG1_WR_BURST_MAX_SIZE_Msk (0x7Fu << PROV_DMA_CTRL_CH3_STATIC_REG1_WR_BURST_MAX_SIZE_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG1) Maximum number of bytes of an AHB write burst Mask */
#define PROV_DMA_CTRL_CH3_STATIC_REG1_WR_BURST_MAX_SIZE(value) (PROV_DMA_CTRL_CH3_STATIC_REG1_WR_BURST_MAX_SIZE_Msk & ((value) << PROV_DMA_CTRL_CH3_STATIC_REG1_WR_BURST_MAX_SIZE_Pos))
#define PROV_DMA_CTRL_CH3_STATIC_REG1_WR_TOKENS_Pos 16                                             /**< (PROV_DMA_CTRL_CH3_STATIC_REG1) Number of AHB write commands to issue before channel is released Position */
#define PROV_DMA_CTRL_CH3_STATIC_REG1_WR_TOKENS_Msk (0x3Fu << PROV_DMA_CTRL_CH3_STATIC_REG1_WR_TOKENS_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG1) Number of AHB write commands to issue before channel is released Mask */
#define PROV_DMA_CTRL_CH3_STATIC_REG1_WR_TOKENS(value) (PROV_DMA_CTRL_CH3_STATIC_REG1_WR_TOKENS_Msk & ((value) << PROV_DMA_CTRL_CH3_STATIC_REG1_WR_TOKENS_Pos))
#define PROV_DMA_CTRL_CH3_STATIC_REG1_WR_INCR_Pos 31                                             /**< (PROV_DMA_CTRL_CH3_STATIC_REG1) If set the controller will increment the next burst address Position */
#define PROV_DMA_CTRL_CH3_STATIC_REG1_WR_INCR_Msk (0x1u << PROV_DMA_CTRL_CH3_STATIC_REG1_WR_INCR_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG1) If set the controller will increment the next burst address Mask */
#define PROV_DMA_CTRL_CH3_STATIC_REG1_WR_INCR PROV_DMA_CTRL_CH3_STATIC_REG1_WR_INCR_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_STATIC_REG1_WR_INCR_Msk instead */
#define PROV_DMA_CTRL_CH3_STATIC_REG1_MASK  0x803F007Fu                                    /**< \deprecated (PROV_DMA_CTRL_CH3_STATIC_REG1) Register MASK  (Use PROV_DMA_CTRL_CH3_STATIC_REG1_Msk instead)  */
#define PROV_DMA_CTRL_CH3_STATIC_REG1_Msk   0x803F007Fu                                    /**< (PROV_DMA_CTRL_CH3_STATIC_REG1) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_STATIC_REG2 : (PROV_DMA_CTRL Offset: 0x318) (R/W 32) Channel 3 Block Mode -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :16;                       /**< bit:  0..15  Reserved */
    uint32_t JOINT:1;                   /**< bit:     16  If set channel will work in joint mode   */
    uint32_t :11;                       /**< bit: 17..27  Reserved */
    uint32_t END_SWAP:2;                /**< bit: 28..29  Endianness Byte Swapping                 */
    uint32_t :2;                        /**< bit: 30..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_STATIC_REG2_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_STATIC_REG2_OFFSET 0x318                                         /**<  (PROV_DMA_CTRL_CH3_STATIC_REG2) Channel 3 Block Mode  Offset */
#define PROV_DMA_CTRL_CH3_STATIC_REG2_RESETVALUE 0x10000u                                      /**<  (PROV_DMA_CTRL_CH3_STATIC_REG2) Channel 3 Block Mode  Reset Value */

#define PROV_DMA_CTRL_CH3_STATIC_REG2_JOINT_Pos 16                                             /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) If set channel will work in joint mode Position */
#define PROV_DMA_CTRL_CH3_STATIC_REG2_JOINT_Msk (0x1u << PROV_DMA_CTRL_CH3_STATIC_REG2_JOINT_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) If set channel will work in joint mode Mask */
#define PROV_DMA_CTRL_CH3_STATIC_REG2_JOINT PROV_DMA_CTRL_CH3_STATIC_REG2_JOINT_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_STATIC_REG2_JOINT_Msk instead */
#define PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_Pos 28                                             /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) Endianness Byte Swapping Position */
#define PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_Msk (0x3u << PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) Endianness Byte Swapping Mask */
#define PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP(value) (PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_Msk & ((value) << PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_Pos))
#define   PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_0_Val 0x0u                                           /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) No Swapping  */
#define   PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_1_Val 0x1u                                           /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) Swap bytes within 16 bits  */
#define   PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_2_Val 0x2u                                           /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) Swap bytes within 32 bits  */
#define   PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_3_Val 0x3u                                           /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) Swap bytes within 64 bits  */
#define PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_0 (PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_0_Val << PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) No Swapping Position  */
#define PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_1 (PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_1_Val << PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) Swap bytes within 16 bits Position  */
#define PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_2 (PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_2_Val << PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) Swap bytes within 32 bits Position  */
#define PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_3 (PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_3_Val << PROV_DMA_CTRL_CH3_STATIC_REG2_END_SWAP_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) Swap bytes within 64 bits Position  */
#define PROV_DMA_CTRL_CH3_STATIC_REG2_MASK  0x30010000u                                    /**< \deprecated (PROV_DMA_CTRL_CH3_STATIC_REG2) Register MASK  (Use PROV_DMA_CTRL_CH3_STATIC_REG2_Msk instead)  */
#define PROV_DMA_CTRL_CH3_STATIC_REG2_Msk   0x30010000u                                    /**< (PROV_DMA_CTRL_CH3_STATIC_REG2) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_STATIC_REG4 : (PROV_DMA_CTRL Offset: 0x320) (R/W 32) Channel 3 Static Configuration Peripheral -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_PERIPH_NUM:5;           /**< bit:   0..4  Number of peripheral to read from (0 if memory or no peripheral flow control) */
    uint32_t :3;                        /**< bit:   5..7  Reserved */
    uint32_t RD_PERIPH_DELAY:3;         /**< bit:  8..10  Number of cycles to wait for read request signal to update after issuing the read clear signal */
    uint32_t :5;                        /**< bit: 11..15  Reserved */
    uint32_t WR_PERIPH_NUM:5;           /**< bit: 16..20  Number of peripheral to write from (0 if memory or no peripheral flow control) */
    uint32_t :3;                        /**< bit: 21..23  Reserved */
    uint32_t WR_PERIPH_DELAY:3;         /**< bit: 24..26  Number of cycles to wait for write request signal to update after issuing the write clear signal */
    uint32_t :5;                        /**< bit: 27..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_STATIC_REG4_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_STATIC_REG4_OFFSET 0x320                                         /**<  (PROV_DMA_CTRL_CH3_STATIC_REG4) Channel 3 Static Configuration Peripheral  Offset */
#define PROV_DMA_CTRL_CH3_STATIC_REG4_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_STATIC_REG4) Channel 3 Static Configuration Peripheral  Reset Value */

#define PROV_DMA_CTRL_CH3_STATIC_REG4_RD_PERIPH_NUM_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_STATIC_REG4) Number of peripheral to read from (0 if memory or no peripheral flow control) Position */
#define PROV_DMA_CTRL_CH3_STATIC_REG4_RD_PERIPH_NUM_Msk (0x1Fu << PROV_DMA_CTRL_CH3_STATIC_REG4_RD_PERIPH_NUM_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG4) Number of peripheral to read from (0 if memory or no peripheral flow control) Mask */
#define PROV_DMA_CTRL_CH3_STATIC_REG4_RD_PERIPH_NUM(value) (PROV_DMA_CTRL_CH3_STATIC_REG4_RD_PERIPH_NUM_Msk & ((value) << PROV_DMA_CTRL_CH3_STATIC_REG4_RD_PERIPH_NUM_Pos))
#define PROV_DMA_CTRL_CH3_STATIC_REG4_RD_PERIPH_DELAY_Pos 8                                              /**< (PROV_DMA_CTRL_CH3_STATIC_REG4) Number of cycles to wait for read request signal to update after issuing the read clear signal Position */
#define PROV_DMA_CTRL_CH3_STATIC_REG4_RD_PERIPH_DELAY_Msk (0x7u << PROV_DMA_CTRL_CH3_STATIC_REG4_RD_PERIPH_DELAY_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG4) Number of cycles to wait for read request signal to update after issuing the read clear signal Mask */
#define PROV_DMA_CTRL_CH3_STATIC_REG4_RD_PERIPH_DELAY(value) (PROV_DMA_CTRL_CH3_STATIC_REG4_RD_PERIPH_DELAY_Msk & ((value) << PROV_DMA_CTRL_CH3_STATIC_REG4_RD_PERIPH_DELAY_Pos))
#define PROV_DMA_CTRL_CH3_STATIC_REG4_WR_PERIPH_NUM_Pos 16                                             /**< (PROV_DMA_CTRL_CH3_STATIC_REG4) Number of peripheral to write from (0 if memory or no peripheral flow control) Position */
#define PROV_DMA_CTRL_CH3_STATIC_REG4_WR_PERIPH_NUM_Msk (0x1Fu << PROV_DMA_CTRL_CH3_STATIC_REG4_WR_PERIPH_NUM_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG4) Number of peripheral to write from (0 if memory or no peripheral flow control) Mask */
#define PROV_DMA_CTRL_CH3_STATIC_REG4_WR_PERIPH_NUM(value) (PROV_DMA_CTRL_CH3_STATIC_REG4_WR_PERIPH_NUM_Msk & ((value) << PROV_DMA_CTRL_CH3_STATIC_REG4_WR_PERIPH_NUM_Pos))
#define PROV_DMA_CTRL_CH3_STATIC_REG4_WR_PERIPH_DELAY_Pos 24                                             /**< (PROV_DMA_CTRL_CH3_STATIC_REG4) Number of cycles to wait for write request signal to update after issuing the write clear signal Position */
#define PROV_DMA_CTRL_CH3_STATIC_REG4_WR_PERIPH_DELAY_Msk (0x7u << PROV_DMA_CTRL_CH3_STATIC_REG4_WR_PERIPH_DELAY_Pos)  /**< (PROV_DMA_CTRL_CH3_STATIC_REG4) Number of cycles to wait for write request signal to update after issuing the write clear signal Mask */
#define PROV_DMA_CTRL_CH3_STATIC_REG4_WR_PERIPH_DELAY(value) (PROV_DMA_CTRL_CH3_STATIC_REG4_WR_PERIPH_DELAY_Msk & ((value) << PROV_DMA_CTRL_CH3_STATIC_REG4_WR_PERIPH_DELAY_Pos))
#define PROV_DMA_CTRL_CH3_STATIC_REG4_MASK  0x71F071Fu                                     /**< \deprecated (PROV_DMA_CTRL_CH3_STATIC_REG4) Register MASK  (Use PROV_DMA_CTRL_CH3_STATIC_REG4_Msk instead)  */
#define PROV_DMA_CTRL_CH3_STATIC_REG4_Msk   0x71F071Fu                                     /**< (PROV_DMA_CTRL_CH3_STATIC_REG4) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_RESRICT_REG : (PROV_DMA_CTRL Offset: 0x32c) (R/ 16) Channel 3 Restrictions Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t RD_ALLOW_FULL_FIFO:1;      /**< bit:      0  Read start address does not restrict burst size */
    uint16_t WR_ALLOW_FULL_FIFO:1;      /**< bit:      1  Write start address does not restrict burst size */
    uint16_t ALLOW_FULL_FIFO:1;         /**< bit:      2  Burst sizes can equal data buffer size, otherwise max burst is half data buffer size */
    uint16_t ALLOW_FULL_BURST:1;        /**< bit:      3  Maximum burst of 16 strobes can be used (joint mode only) */
    uint16_t ALLOW_JOINT_BURST:1;       /**< bit:      4  Joint bursts are currently active        */
    uint16_t :3;                        /**< bit:   5..7  Reserved */
    uint16_t SIMPLE_MEM:1;              /**< bit:      8  Configuration is aligned and peripherals are not used */
    uint16_t :7;                        /**< bit:  9..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_RESRICT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_RESRICT_REG_OFFSET 0x32C                                         /**<  (PROV_DMA_CTRL_CH3_RESRICT_REG) Channel 3 Restrictions Status Register  Offset */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_RESRICT_REG) Channel 3 Restrictions Status Register  Reset Value */

#define PROV_DMA_CTRL_CH3_RESRICT_REG_RD_ALLOW_FULL_FIFO_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Read start address does not restrict burst size Position */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_RD_ALLOW_FULL_FIFO_Msk (0x1u << PROV_DMA_CTRL_CH3_RESRICT_REG_RD_ALLOW_FULL_FIFO_Pos)  /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Read start address does not restrict burst size Mask */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_RD_ALLOW_FULL_FIFO PROV_DMA_CTRL_CH3_RESRICT_REG_RD_ALLOW_FULL_FIFO_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_RESRICT_REG_RD_ALLOW_FULL_FIFO_Msk instead */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_WR_ALLOW_FULL_FIFO_Pos 1                                              /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Write start address does not restrict burst size Position */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_WR_ALLOW_FULL_FIFO_Msk (0x1u << PROV_DMA_CTRL_CH3_RESRICT_REG_WR_ALLOW_FULL_FIFO_Pos)  /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Write start address does not restrict burst size Mask */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_WR_ALLOW_FULL_FIFO PROV_DMA_CTRL_CH3_RESRICT_REG_WR_ALLOW_FULL_FIFO_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_RESRICT_REG_WR_ALLOW_FULL_FIFO_Msk instead */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_FULL_FIFO_Pos 2                                              /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Burst sizes can equal data buffer size, otherwise max burst is half data buffer size Position */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_FULL_FIFO_Msk (0x1u << PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_FULL_FIFO_Pos)  /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Burst sizes can equal data buffer size, otherwise max burst is half data buffer size Mask */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_FULL_FIFO PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_FULL_FIFO_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_FULL_FIFO_Msk instead */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_FULL_BURST_Pos 3                                              /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Maximum burst of 16 strobes can be used (joint mode only) Position */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_FULL_BURST_Msk (0x1u << PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_FULL_BURST_Pos)  /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Maximum burst of 16 strobes can be used (joint mode only) Mask */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_FULL_BURST PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_FULL_BURST_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_FULL_BURST_Msk instead */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_JOINT_BURST_Pos 4                                              /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Joint bursts are currently active Position */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_JOINT_BURST_Msk (0x1u << PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_JOINT_BURST_Pos)  /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Joint bursts are currently active Mask */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_JOINT_BURST PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_JOINT_BURST_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_RESRICT_REG_ALLOW_JOINT_BURST_Msk instead */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_SIMPLE_MEM_Pos 8                                              /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Configuration is aligned and peripherals are not used Position */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_SIMPLE_MEM_Msk (0x1u << PROV_DMA_CTRL_CH3_RESRICT_REG_SIMPLE_MEM_Pos)  /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Configuration is aligned and peripherals are not used Mask */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_SIMPLE_MEM PROV_DMA_CTRL_CH3_RESRICT_REG_SIMPLE_MEM_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_RESRICT_REG_SIMPLE_MEM_Msk instead */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_MASK  0x11Fu                                         /**< \deprecated (PROV_DMA_CTRL_CH3_RESRICT_REG) Register MASK  (Use PROV_DMA_CTRL_CH3_RESRICT_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH3_RESRICT_REG_Msk   0x11Fu                                         /**< (PROV_DMA_CTRL_CH3_RESRICT_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG : (PROV_DMA_CTRL Offset: 0x338) (R/ 32) Channel 3 FIFO Fullness Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t RD_GAP:13;                 /**< bit:  0..12  Remaining space (in bytes) in FIFO for read data */
    uint32_t :3;                        /**< bit: 13..15  Reserved */
    uint32_t WR_FULLNESS:13;            /**< bit: 16..28  Occupied space (in bytes) in FIFO by write data */
    uint32_t :3;                        /**< bit: 29..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_OFFSET 0x338                                         /**<  (PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG) Channel 3 FIFO Fullness Status Register  Offset */
#define PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG) Channel 3 FIFO Fullness Status Register  Reset Value */

#define PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_RD_GAP_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG) Remaining space (in bytes) in FIFO for read data Position */
#define PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_RD_GAP_Msk (0x1FFFu << PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_RD_GAP_Pos)  /**< (PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG) Remaining space (in bytes) in FIFO for read data Mask */
#define PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_RD_GAP(value) (PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_RD_GAP_Msk & ((value) << PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_RD_GAP_Pos))
#define PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_WR_FULLNESS_Pos 16                                             /**< (PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG) Occupied space (in bytes) in FIFO by write data Position */
#define PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_WR_FULLNESS_Msk (0x1FFFu << PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_WR_FULLNESS_Pos)  /**< (PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG) Occupied space (in bytes) in FIFO by write data Mask */
#define PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_WR_FULLNESS(value) (PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_WR_FULLNESS_Msk & ((value) << PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_WR_FULLNESS_Pos))
#define PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_MASK 0x1FFF1FFFu                                    /**< \deprecated (PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG) Register MASK  (Use PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_Msk 0x1FFF1FFFu                                    /**< (PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_CH_ENABLE_REG : (PROV_DMA_CTRL Offset: 0x340) (R/W 8) Channel 3 Channel Enable Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH3_CH_ENABLE_REG:1;       /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_CH_ENABLE_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_CH_ENABLE_REG_OFFSET 0x340                                         /**<  (PROV_DMA_CTRL_CH3_CH_ENABLE_REG) Channel 3 Channel Enable Register  Offset */
#define PROV_DMA_CTRL_CH3_CH_ENABLE_REG_RESETVALUE 0x01u                                         /**<  (PROV_DMA_CTRL_CH3_CH_ENABLE_REG) Channel 3 Channel Enable Register  Reset Value */

#define PROV_DMA_CTRL_CH3_CH_ENABLE_REG_CH3_CH_ENABLE_REG_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_CH_ENABLE_REG)  Position */
#define PROV_DMA_CTRL_CH3_CH_ENABLE_REG_CH3_CH_ENABLE_REG_Msk (0x1u << PROV_DMA_CTRL_CH3_CH_ENABLE_REG_CH3_CH_ENABLE_REG_Pos)  /**< (PROV_DMA_CTRL_CH3_CH_ENABLE_REG)  Mask */
#define PROV_DMA_CTRL_CH3_CH_ENABLE_REG_CH3_CH_ENABLE_REG PROV_DMA_CTRL_CH3_CH_ENABLE_REG_CH3_CH_ENABLE_REG_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_CH_ENABLE_REG_CH3_CH_ENABLE_REG_Msk instead */
#define PROV_DMA_CTRL_CH3_CH_ENABLE_REG_MASK 0x01u                                          /**< \deprecated (PROV_DMA_CTRL_CH3_CH_ENABLE_REG) Register MASK  (Use PROV_DMA_CTRL_CH3_CH_ENABLE_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH3_CH_ENABLE_REG_Msk 0x01u                                          /**< (PROV_DMA_CTRL_CH3_CH_ENABLE_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_CH_START_REG : (PROV_DMA_CTRL Offset: 0x344) (/W 8) Channel 3 Channel Start Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH3_CH_START_REG:1;        /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_CH_START_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_CH_START_REG_OFFSET 0x344                                         /**<  (PROV_DMA_CTRL_CH3_CH_START_REG) Channel 3 Channel Start Register  Offset */
#define PROV_DMA_CTRL_CH3_CH_START_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_CH_START_REG) Channel 3 Channel Start Register  Reset Value */

#define PROV_DMA_CTRL_CH3_CH_START_REG_CH3_CH_START_REG_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_CH_START_REG)  Position */
#define PROV_DMA_CTRL_CH3_CH_START_REG_CH3_CH_START_REG_Msk (0x1u << PROV_DMA_CTRL_CH3_CH_START_REG_CH3_CH_START_REG_Pos)  /**< (PROV_DMA_CTRL_CH3_CH_START_REG)  Mask */
#define PROV_DMA_CTRL_CH3_CH_START_REG_CH3_CH_START_REG PROV_DMA_CTRL_CH3_CH_START_REG_CH3_CH_START_REG_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_CH_START_REG_CH3_CH_START_REG_Msk instead */
#define PROV_DMA_CTRL_CH3_CH_START_REG_MASK 0x01u                                          /**< \deprecated (PROV_DMA_CTRL_CH3_CH_START_REG) Register MASK  (Use PROV_DMA_CTRL_CH3_CH_START_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH3_CH_START_REG_Msk  0x01u                                          /**< (PROV_DMA_CTRL_CH3_CH_START_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_CH_ACTIVE_REG : (PROV_DMA_CTRL Offset: 0x348) (R/ 8) Channel 3 Channel Active Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_RD_ACTIVE:1;            /**< bit:      0  Set if channel is enabled and all read data has been received */
    uint8_t  CH_WR_ACTIVE:1;            /**< bit:      1  Set if channel is enabled and all write data has been transfered */
    uint8_t  :6;                        /**< bit:   2..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_OFFSET 0x348                                         /**<  (PROV_DMA_CTRL_CH3_CH_ACTIVE_REG) Channel 3 Channel Active Status Register  Offset */
#define PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_CH_ACTIVE_REG) Channel 3 Channel Active Status Register  Reset Value */

#define PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_CH_RD_ACTIVE_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_CH_ACTIVE_REG) Set if channel is enabled and all read data has been received Position */
#define PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_CH_RD_ACTIVE_Msk (0x1u << PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_CH_RD_ACTIVE_Pos)  /**< (PROV_DMA_CTRL_CH3_CH_ACTIVE_REG) Set if channel is enabled and all read data has been received Mask */
#define PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_CH_RD_ACTIVE PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_CH_RD_ACTIVE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_CH_RD_ACTIVE_Msk instead */
#define PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_CH_WR_ACTIVE_Pos 1                                              /**< (PROV_DMA_CTRL_CH3_CH_ACTIVE_REG) Set if channel is enabled and all write data has been transfered Position */
#define PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_CH_WR_ACTIVE_Msk (0x1u << PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_CH_WR_ACTIVE_Pos)  /**< (PROV_DMA_CTRL_CH3_CH_ACTIVE_REG) Set if channel is enabled and all write data has been transfered Mask */
#define PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_CH_WR_ACTIVE PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_CH_WR_ACTIVE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_CH_WR_ACTIVE_Msk instead */
#define PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_MASK 0x03u                                          /**< \deprecated (PROV_DMA_CTRL_CH3_CH_ACTIVE_REG) Register MASK  (Use PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_Msk 0x03u                                          /**< (PROV_DMA_CTRL_CH3_CH_ACTIVE_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_COUNT_REG : (PROV_DMA_CTRL Offset: 0x350) (R/ 32) Channel 3 Buffer Counter Status Register -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t BUFF_COUNT:12;             /**< bit:  0..11  Number of buffers transferred by channel since started */
    uint32_t :4;                        /**< bit: 12..15  Reserved */
    uint32_t INT_COUNT:4;               /**< bit: 16..19  Number of unserviced end interrupts      */
    uint32_t :12;                       /**< bit: 20..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_COUNT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_COUNT_REG_OFFSET  0x350                                         /**<  (PROV_DMA_CTRL_CH3_COUNT_REG) Channel 3 Buffer Counter Status Register  Offset */
#define PROV_DMA_CTRL_CH3_COUNT_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_COUNT_REG) Channel 3 Buffer Counter Status Register  Reset Value */

#define PROV_DMA_CTRL_CH3_COUNT_REG_BUFF_COUNT_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_COUNT_REG) Number of buffers transferred by channel since started Position */
#define PROV_DMA_CTRL_CH3_COUNT_REG_BUFF_COUNT_Msk (0xFFFu << PROV_DMA_CTRL_CH3_COUNT_REG_BUFF_COUNT_Pos)  /**< (PROV_DMA_CTRL_CH3_COUNT_REG) Number of buffers transferred by channel since started Mask */
#define PROV_DMA_CTRL_CH3_COUNT_REG_BUFF_COUNT(value) (PROV_DMA_CTRL_CH3_COUNT_REG_BUFF_COUNT_Msk & ((value) << PROV_DMA_CTRL_CH3_COUNT_REG_BUFF_COUNT_Pos))
#define PROV_DMA_CTRL_CH3_COUNT_REG_INT_COUNT_Pos 16                                             /**< (PROV_DMA_CTRL_CH3_COUNT_REG) Number of unserviced end interrupts Position */
#define PROV_DMA_CTRL_CH3_COUNT_REG_INT_COUNT_Msk (0xFu << PROV_DMA_CTRL_CH3_COUNT_REG_INT_COUNT_Pos)  /**< (PROV_DMA_CTRL_CH3_COUNT_REG) Number of unserviced end interrupts Mask */
#define PROV_DMA_CTRL_CH3_COUNT_REG_INT_COUNT(value) (PROV_DMA_CTRL_CH3_COUNT_REG_INT_COUNT_Msk & ((value) << PROV_DMA_CTRL_CH3_COUNT_REG_INT_COUNT_Pos))
#define PROV_DMA_CTRL_CH3_COUNT_REG_MASK    0xF0FFFu                                       /**< \deprecated (PROV_DMA_CTRL_CH3_COUNT_REG) Register MASK  (Use PROV_DMA_CTRL_CH3_COUNT_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH3_COUNT_REG_Msk     0xF0FFFu                                       /**< (PROV_DMA_CTRL_CH3_COUNT_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG : (PROV_DMA_CTRL Offset: 0x3a0) (R/W 8) Channel 3 Interrupt Raw Status (Write 1 to any field to issue interrupt) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Indicates an unserviced channel end interrupt */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  AHB read slave error                     */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  AHB write slave error                    */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  FIFO has been overflown                  */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  FIFO has been underflown                 */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Read timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Write timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  WDT:1;                     /**< bit:      7  Channel active but did not start a burst for 2048 cycles */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_OFFSET 0x3A0                                         /**<  (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) Channel 3 Interrupt Raw Status (Write 1 to any field to issue interrupt)  Offset */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) Channel 3 Interrupt Raw Status (Write 1 to any field to issue interrupt)  Reset Value */

#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) Indicates an unserviced channel end interrupt Position */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) Indicates an unserviced channel end interrupt Mask */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_CH_END PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_CH_END_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) AHB read slave error Position */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) AHB read slave error Mask */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_RD_SLVERR PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) AHB write slave error Position */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) AHB write slave error Mask */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_WR_SLVERR PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) FIFO has been overflown Position */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) FIFO has been overflown Mask */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) FIFO has been underflown Position */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) FIFO has been underflown Mask */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_TIMEOUT_RD PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_TIMEOUT_WR PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) Channel active but did not start a burst for 2048 cycles Position */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) Channel active but did not start a burst for 2048 cycles Mask */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_WDT PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_WDT_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) Register MASK  (Use PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_INT_CLEAR_REG : (PROV_DMA_CTRL Offset: 0x3a4) (R/W 8) Channel 3 Interrupt Clear (Write 1 to clear) -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Clear channel end interrupt. Decrements INT_COUNT register */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  Clear AHB read slave error               */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  Clear AHB write slave error              */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  Clears FIFO overflow                     */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  Clears FIFO underflow                    */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Clears Read Timeout                      */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Clears Write Timeout                     */
    uint8_t  WDT:1;                     /**< bit:      7  Clears WDT                               */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_INT_CLEAR_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_OFFSET 0x3A4                                         /**<  (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Channel 3 Interrupt Clear (Write 1 to clear)  Offset */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Channel 3 Interrupt Clear (Write 1 to clear)  Reset Value */

#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clear channel end interrupt. Decrements INT_COUNT register Position */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_CLEAR_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clear channel end interrupt. Decrements INT_COUNT register Mask */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_CH_END PROV_DMA_CTRL_CH3_INT_CLEAR_REG_CH_END_Msk     /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_CLEAR_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clear AHB read slave error Position */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_CLEAR_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clear AHB read slave error Mask */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_RD_SLVERR PROV_DMA_CTRL_CH3_INT_CLEAR_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_CLEAR_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clear AHB write slave error Position */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_CLEAR_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clear AHB write slave error Mask */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_WR_SLVERR PROV_DMA_CTRL_CH3_INT_CLEAR_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_CLEAR_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clears FIFO overflow Position */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_CLEAR_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clears FIFO overflow Mask */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH3_INT_CLEAR_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_CLEAR_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clears FIFO underflow Position */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_CLEAR_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clears FIFO underflow Mask */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH3_INT_CLEAR_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_CLEAR_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clears Read Timeout Position */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_CLEAR_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clears Read Timeout Mask */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_TIMEOUT_RD PROV_DMA_CTRL_CH3_INT_CLEAR_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_CLEAR_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clears Write Timeout Position */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_CLEAR_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clears Write Timeout Mask */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_TIMEOUT_WR PROV_DMA_CTRL_CH3_INT_CLEAR_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_CLEAR_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clears WDT Position */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_CLEAR_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Clears WDT Mask */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_WDT PROV_DMA_CTRL_CH3_INT_CLEAR_REG_WDT_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_CLEAR_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Register MASK  (Use PROV_DMA_CTRL_CH3_INT_CLEAR_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH3_INT_CLEAR_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH3_INT_CLEAR_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_INT_ENABLE_REG : (PROV_DMA_CTRL Offset: 0x3a8) (R/W 8) Channel 3 Interrupt Enable -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Enables end of channel interrupt         */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  Enables AHB read slave error interrupt   */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  Enables AHB write slave error interrupt  */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  Enables FIFO overflow interrupt          */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  Enables FIFO underflow interrupt         */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Enables AHB Read timeout interrupt       */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Enables AHB Write timeout interrupt      */
    uint8_t  WDT:1;                     /**< bit:      7  Enables WDT interrupt                    */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_INT_ENABLE_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_OFFSET 0x3A8                                         /**<  (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Channel 3 Interrupt Enable  Offset */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Channel 3 Interrupt Enable  Reset Value */

#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables end of channel interrupt Position */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_ENABLE_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables end of channel interrupt Mask */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_CH_END PROV_DMA_CTRL_CH3_INT_ENABLE_REG_CH_END_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_ENABLE_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables AHB read slave error interrupt Position */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_ENABLE_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables AHB read slave error interrupt Mask */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_RD_SLVERR PROV_DMA_CTRL_CH3_INT_ENABLE_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_ENABLE_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables AHB write slave error interrupt Position */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_ENABLE_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables AHB write slave error interrupt Mask */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_WR_SLVERR PROV_DMA_CTRL_CH3_INT_ENABLE_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_ENABLE_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables FIFO overflow interrupt Position */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_ENABLE_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables FIFO overflow interrupt Mask */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH3_INT_ENABLE_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_ENABLE_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables FIFO underflow interrupt Position */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_ENABLE_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables FIFO underflow interrupt Mask */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH3_INT_ENABLE_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_ENABLE_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables AHB Read timeout interrupt Position */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_ENABLE_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables AHB Read timeout interrupt Mask */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_TIMEOUT_RD PROV_DMA_CTRL_CH3_INT_ENABLE_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_ENABLE_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables AHB Write timeout interrupt Position */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_ENABLE_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables AHB Write timeout interrupt Mask */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_TIMEOUT_WR PROV_DMA_CTRL_CH3_INT_ENABLE_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_ENABLE_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables WDT interrupt Position */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_ENABLE_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Enables WDT interrupt Mask */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_WDT PROV_DMA_CTRL_CH3_INT_ENABLE_REG_WDT_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_ENABLE_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Register MASK  (Use PROV_DMA_CTRL_CH3_INT_ENABLE_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH3_INT_ENABLE_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH3_INT_ENABLE_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CH3_INT_STATUS_REG : (PROV_DMA_CTRL Offset: 0x3ac) (R/W 8) Channel 3 Interrupt Status -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_END:1;                  /**< bit:      0  Indicates an unserviced channel end interrupt */
    uint8_t  RD_SLVERR:1;               /**< bit:      1  AHB read slave error                     */
    uint8_t  WR_SLVERR:1;               /**< bit:      2  AHB write slave error                    */
    uint8_t  FIFO_OVERFLOW:1;           /**< bit:      3  FIFO has been overflown                  */
    uint8_t  FIFO_UNDERFLOW:1;          /**< bit:      4  FIFO has been underflown                 */
    uint8_t  TIMEOUT_RD:1;              /**< bit:      5  Read timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  TIMEOUT_WR:1;              /**< bit:      6  Write timeout on AHB bus (timeout value fixed at 1024 cycles) */
    uint8_t  WDT:1;                     /**< bit:      7  Channel active but did not start a burst for 2048 cycles */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CH3_INT_STATUS_REG_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_OFFSET 0x3AC                                         /**<  (PROV_DMA_CTRL_CH3_INT_STATUS_REG) Channel 3 Interrupt Status  Offset */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CH3_INT_STATUS_REG) Channel 3 Interrupt Status  Reset Value */

#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_CH_END_Pos 0                                              /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) Indicates an unserviced channel end interrupt Position */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_CH_END_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_STATUS_REG_CH_END_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) Indicates an unserviced channel end interrupt Mask */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_CH_END PROV_DMA_CTRL_CH3_INT_STATUS_REG_CH_END_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_STATUS_REG_CH_END_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_RD_SLVERR_Pos 1                                              /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) AHB read slave error Position */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_RD_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_STATUS_REG_RD_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) AHB read slave error Mask */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_RD_SLVERR PROV_DMA_CTRL_CH3_INT_STATUS_REG_RD_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_STATUS_REG_RD_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_WR_SLVERR_Pos 2                                              /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) AHB write slave error Position */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_WR_SLVERR_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_STATUS_REG_WR_SLVERR_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) AHB write slave error Mask */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_WR_SLVERR PROV_DMA_CTRL_CH3_INT_STATUS_REG_WR_SLVERR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_STATUS_REG_WR_SLVERR_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_FIFO_OVERFLOW_Pos 3                                              /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) FIFO has been overflown Position */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_FIFO_OVERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_STATUS_REG_FIFO_OVERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) FIFO has been overflown Mask */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_FIFO_OVERFLOW PROV_DMA_CTRL_CH3_INT_STATUS_REG_FIFO_OVERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_STATUS_REG_FIFO_OVERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_FIFO_UNDERFLOW_Pos 4                                              /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) FIFO has been underflown Position */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_FIFO_UNDERFLOW_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_STATUS_REG_FIFO_UNDERFLOW_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) FIFO has been underflown Mask */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_FIFO_UNDERFLOW PROV_DMA_CTRL_CH3_INT_STATUS_REG_FIFO_UNDERFLOW_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_STATUS_REG_FIFO_UNDERFLOW_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_TIMEOUT_RD_Pos 5                                              /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_TIMEOUT_RD_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_STATUS_REG_TIMEOUT_RD_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) Read timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_TIMEOUT_RD PROV_DMA_CTRL_CH3_INT_STATUS_REG_TIMEOUT_RD_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_STATUS_REG_TIMEOUT_RD_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_TIMEOUT_WR_Pos 6                                              /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Position */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_TIMEOUT_WR_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_STATUS_REG_TIMEOUT_WR_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) Write timeout on AHB bus (timeout value fixed at 1024 cycles) Mask */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_TIMEOUT_WR PROV_DMA_CTRL_CH3_INT_STATUS_REG_TIMEOUT_WR_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_STATUS_REG_TIMEOUT_WR_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_WDT_Pos 7                                              /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) Channel active but did not start a burst for 2048 cycles Position */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_WDT_Msk (0x1u << PROV_DMA_CTRL_CH3_INT_STATUS_REG_WDT_Pos)  /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) Channel active but did not start a burst for 2048 cycles Mask */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_WDT PROV_DMA_CTRL_CH3_INT_STATUS_REG_WDT_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CH3_INT_STATUS_REG_WDT_Msk instead */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_MASK 0xFFu                                          /**< \deprecated (PROV_DMA_CTRL_CH3_INT_STATUS_REG) Register MASK  (Use PROV_DMA_CTRL_CH3_INT_STATUS_REG_Msk instead)  */
#define PROV_DMA_CTRL_CH3_INT_STATUS_REG_Msk 0xFFu                                          /**< (PROV_DMA_CTRL_CH3_INT_STATUS_REG) Register Mask  */

/* -------- PROV_DMA_CTRL_CORE_INT_STATUS : (PROV_DMA_CTRL Offset: 0x800) (R/ 8) Indicates which channels caused interrupt -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CHANNEL_0:1;               /**< bit:      0  Indicates channel 0 caused interrupt     */
    uint8_t  CHANNEL_1:1;               /**< bit:      1  Indicates channel 1 caused interrupt     */
    uint8_t  CHANNEL_2:1;               /**< bit:      2  Indicates channel 2 caused interrupt     */
    uint8_t  CHANNEL_3:1;               /**< bit:      3  Indicates channel 3 caused interrupt     */
    uint8_t  :4;                        /**< bit:   4..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  CHANNEL_:4;                /**< bit:   0..3  Indicates channel 3 caused interrupt     */
    uint8_t  :4;                        /**< bit:   4..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CORE_INT_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CORE_INT_STATUS_OFFSET 0x800                                         /**<  (PROV_DMA_CTRL_CORE_INT_STATUS) Indicates which channels caused interrupt  Offset */
#define PROV_DMA_CTRL_CORE_INT_STATUS_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CORE_INT_STATUS) Indicates which channels caused interrupt  Reset Value */

#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_0_Pos 0                                              /**< (PROV_DMA_CTRL_CORE_INT_STATUS) Indicates channel 0 caused interrupt Position */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_0_Msk (0x1u << PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_0_Pos)  /**< (PROV_DMA_CTRL_CORE_INT_STATUS) Indicates channel 0 caused interrupt Mask */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_0 PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_0_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_0_Msk instead */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_1_Pos 1                                              /**< (PROV_DMA_CTRL_CORE_INT_STATUS) Indicates channel 1 caused interrupt Position */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_1_Msk (0x1u << PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_1_Pos)  /**< (PROV_DMA_CTRL_CORE_INT_STATUS) Indicates channel 1 caused interrupt Mask */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_1 PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_1_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_1_Msk instead */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_2_Pos 2                                              /**< (PROV_DMA_CTRL_CORE_INT_STATUS) Indicates channel 2 caused interrupt Position */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_2_Msk (0x1u << PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_2_Pos)  /**< (PROV_DMA_CTRL_CORE_INT_STATUS) Indicates channel 2 caused interrupt Mask */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_2 PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_2_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_2_Msk instead */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_3_Pos 3                                              /**< (PROV_DMA_CTRL_CORE_INT_STATUS) Indicates channel 3 caused interrupt Position */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_3_Msk (0x1u << PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_3_Pos)  /**< (PROV_DMA_CTRL_CORE_INT_STATUS) Indicates channel 3 caused interrupt Mask */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_3 PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_3_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_3_Msk instead */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL__Pos 0                                              /**< (PROV_DMA_CTRL_CORE_INT_STATUS Position) Indicates channel 3 caused interrupt */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL__Msk (0xFu << PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL__Pos)  /**< (PROV_DMA_CTRL_CORE_INT_STATUS Mask) CHANNEL_ */
#define PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL_(value) (PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL__Msk & ((value) << PROV_DMA_CTRL_CORE_INT_STATUS_CHANNEL__Pos))  
#define PROV_DMA_CTRL_CORE_INT_STATUS_MASK  0x0Fu                                          /**< \deprecated (PROV_DMA_CTRL_CORE_INT_STATUS) Register MASK  (Use PROV_DMA_CTRL_CORE_INT_STATUS_Msk instead)  */
#define PROV_DMA_CTRL_CORE_INT_STATUS_Msk   0x0Fu                                          /**< (PROV_DMA_CTRL_CORE_INT_STATUS) Register Mask  */

/* -------- PROV_DMA_CTRL_CORE_JOINT_MODE : (PROV_DMA_CTRL Offset: 0x830) (R/W 8) If set, core works in joint mode -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CORE_JOINT_MODE:1;         /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CORE_JOINT_MODE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CORE_JOINT_MODE_OFFSET 0x830                                         /**<  (PROV_DMA_CTRL_CORE_JOINT_MODE) If set, core works in joint mode  Offset */
#define PROV_DMA_CTRL_CORE_JOINT_MODE_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CORE_JOINT_MODE) If set, core works in joint mode  Reset Value */

#define PROV_DMA_CTRL_CORE_JOINT_MODE_CORE_JOINT_MODE_Pos 0                                              /**< (PROV_DMA_CTRL_CORE_JOINT_MODE)  Position */
#define PROV_DMA_CTRL_CORE_JOINT_MODE_CORE_JOINT_MODE_Msk (0x1u << PROV_DMA_CTRL_CORE_JOINT_MODE_CORE_JOINT_MODE_Pos)  /**< (PROV_DMA_CTRL_CORE_JOINT_MODE)  Mask */
#define PROV_DMA_CTRL_CORE_JOINT_MODE_CORE_JOINT_MODE PROV_DMA_CTRL_CORE_JOINT_MODE_CORE_JOINT_MODE_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_JOINT_MODE_CORE_JOINT_MODE_Msk instead */
#define PROV_DMA_CTRL_CORE_JOINT_MODE_MASK  0x01u                                          /**< \deprecated (PROV_DMA_CTRL_CORE_JOINT_MODE) Register MASK  (Use PROV_DMA_CTRL_CORE_JOINT_MODE_Msk instead)  */
#define PROV_DMA_CTRL_CORE_JOINT_MODE_Msk   0x01u                                          /**< (PROV_DMA_CTRL_CORE_JOINT_MODE) Register Mask  */

/* -------- PROV_DMA_CTRL_CORE_PRIORITY : (PROV_DMA_CTRL Offset: 0x838) (R/W 16) Core Priority Channels -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t RD_PRIO_TOP_NUM:3;         /**< bit:   0..2  Core Read Top Priority Channel Number    */
    uint16_t RD_PRIO_TOP:1;             /**< bit:      3  Core Read Top Priority Enable            */
    uint16_t RD_PRIO_HIGH_NUM:3;        /**< bit:   4..6  Core Read High Priority Channel Number   */
    uint16_t RD_PRIO_HIGH:1;            /**< bit:      7  Core Read High Priority Enable           */
    uint16_t WR_PRIO_TOP_NUM:3;         /**< bit:  8..10  Core Write Top Priority Channel Number   */
    uint16_t WR_PRIO_TOP:1;             /**< bit:     11  Core Write Top Priority Enable           */
    uint16_t WR_PRIO_HIGH_NUM:3;        /**< bit: 12..14  Core Write High Priority Channel Number  */
    uint16_t WR_PRIO_HIGH:1;            /**< bit:     15  Core Write High Priority Enable          */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CORE_PRIORITY_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CORE_PRIORITY_OFFSET  0x838                                         /**<  (PROV_DMA_CTRL_CORE_PRIORITY) Core Priority Channels  Offset */
#define PROV_DMA_CTRL_CORE_PRIORITY_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CORE_PRIORITY) Core Priority Channels  Reset Value */

#define PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_TOP_NUM_Pos 0                                              /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Read Top Priority Channel Number Position */
#define PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_TOP_NUM_Msk (0x7u << PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_TOP_NUM_Pos)  /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Read Top Priority Channel Number Mask */
#define PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_TOP_NUM(value) (PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_TOP_NUM_Msk & ((value) << PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_TOP_NUM_Pos))
#define PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_TOP_Pos 3                                              /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Read Top Priority Enable Position */
#define PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_TOP_Msk (0x1u << PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_TOP_Pos)  /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Read Top Priority Enable Mask */
#define PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_TOP PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_TOP_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_TOP_Msk instead */
#define PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_HIGH_NUM_Pos 4                                              /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Read High Priority Channel Number Position */
#define PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_HIGH_NUM_Msk (0x7u << PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_HIGH_NUM_Pos)  /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Read High Priority Channel Number Mask */
#define PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_HIGH_NUM(value) (PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_HIGH_NUM_Msk & ((value) << PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_HIGH_NUM_Pos))
#define PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_HIGH_Pos 7                                              /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Read High Priority Enable Position */
#define PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_HIGH_Msk (0x1u << PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_HIGH_Pos)  /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Read High Priority Enable Mask */
#define PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_HIGH PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_HIGH_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_PRIORITY_RD_PRIO_HIGH_Msk instead */
#define PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_TOP_NUM_Pos 8                                              /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Write Top Priority Channel Number Position */
#define PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_TOP_NUM_Msk (0x7u << PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_TOP_NUM_Pos)  /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Write Top Priority Channel Number Mask */
#define PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_TOP_NUM(value) (PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_TOP_NUM_Msk & ((value) << PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_TOP_NUM_Pos))
#define PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_TOP_Pos 11                                             /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Write Top Priority Enable Position */
#define PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_TOP_Msk (0x1u << PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_TOP_Pos)  /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Write Top Priority Enable Mask */
#define PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_TOP PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_TOP_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_TOP_Msk instead */
#define PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_HIGH_NUM_Pos 12                                             /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Write High Priority Channel Number Position */
#define PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_HIGH_NUM_Msk (0x7u << PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_HIGH_NUM_Pos)  /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Write High Priority Channel Number Mask */
#define PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_HIGH_NUM(value) (PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_HIGH_NUM_Msk & ((value) << PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_HIGH_NUM_Pos))
#define PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_HIGH_Pos 15                                             /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Write High Priority Enable Position */
#define PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_HIGH_Msk (0x1u << PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_HIGH_Pos)  /**< (PROV_DMA_CTRL_CORE_PRIORITY) Core Write High Priority Enable Mask */
#define PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_HIGH PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_HIGH_Msk   /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_PRIORITY_WR_PRIO_HIGH_Msk instead */
#define PROV_DMA_CTRL_CORE_PRIORITY_MASK    0xFFFFu                                        /**< \deprecated (PROV_DMA_CTRL_CORE_PRIORITY) Register MASK  (Use PROV_DMA_CTRL_CORE_PRIORITY_Msk instead)  */
#define PROV_DMA_CTRL_CORE_PRIORITY_Msk     0xFFFFu                                        /**< (PROV_DMA_CTRL_CORE_PRIORITY) Register Mask  */

/* -------- PROV_DMA_CTRL_CORE_CLKDIV : (PROV_DMA_CTRL Offset: 0x840) (R/W 8) Ratio between main clock and core clock -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CORE_CLKDIV:4;             /**< bit:   0..3                                           */
    uint8_t  :4;                        /**< bit:   4..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CORE_CLKDIV_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CORE_CLKDIV_OFFSET    0x840                                         /**<  (PROV_DMA_CTRL_CORE_CLKDIV) Ratio between main clock and core clock  Offset */
#define PROV_DMA_CTRL_CORE_CLKDIV_RESETVALUE 0x01u                                         /**<  (PROV_DMA_CTRL_CORE_CLKDIV) Ratio between main clock and core clock  Reset Value */

#define PROV_DMA_CTRL_CORE_CLKDIV_CORE_CLKDIV_Pos 0                                              /**< (PROV_DMA_CTRL_CORE_CLKDIV)  Position */
#define PROV_DMA_CTRL_CORE_CLKDIV_CORE_CLKDIV_Msk (0xFu << PROV_DMA_CTRL_CORE_CLKDIV_CORE_CLKDIV_Pos)  /**< (PROV_DMA_CTRL_CORE_CLKDIV)  Mask */
#define PROV_DMA_CTRL_CORE_CLKDIV_CORE_CLKDIV(value) (PROV_DMA_CTRL_CORE_CLKDIV_CORE_CLKDIV_Msk & ((value) << PROV_DMA_CTRL_CORE_CLKDIV_CORE_CLKDIV_Pos))
#define PROV_DMA_CTRL_CORE_CLKDIV_MASK      0x0Fu                                          /**< \deprecated (PROV_DMA_CTRL_CORE_CLKDIV) Register MASK  (Use PROV_DMA_CTRL_CORE_CLKDIV_Msk instead)  */
#define PROV_DMA_CTRL_CORE_CLKDIV_Msk       0x0Fu                                          /**< (PROV_DMA_CTRL_CORE_CLKDIV) Register Mask  */

/* -------- PROV_DMA_CTRL_CORE_CH_START : (PROV_DMA_CTRL Offset: 0x848) (/W 8) Channel Start -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CH_0:1;                    /**< bit:      0  Starts Channel 0                         */
    uint8_t  CH_1:1;                    /**< bit:      1  Starts Channel 1                         */
    uint8_t  CH_2:1;                    /**< bit:      2  Starts Channel 2                         */
    uint8_t  CH_3:1;                    /**< bit:      3  Starts Channel 3                         */
    uint8_t  :4;                        /**< bit:   4..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  struct {
    uint8_t  CH_:4;                     /**< bit:   0..3  Starts Channel 3                         */
    uint8_t  :4;                        /**< bit:   4..7 Reserved */
  } vec;                                /**< Structure used for vec  access  */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CORE_CH_START_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CORE_CH_START_OFFSET  0x848                                         /**<  (PROV_DMA_CTRL_CORE_CH_START) Channel Start  Offset */
#define PROV_DMA_CTRL_CORE_CH_START_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_CORE_CH_START) Channel Start  Reset Value */

#define PROV_DMA_CTRL_CORE_CH_START_CH_0_Pos 0                                              /**< (PROV_DMA_CTRL_CORE_CH_START) Starts Channel 0 Position */
#define PROV_DMA_CTRL_CORE_CH_START_CH_0_Msk (0x1u << PROV_DMA_CTRL_CORE_CH_START_CH_0_Pos)  /**< (PROV_DMA_CTRL_CORE_CH_START) Starts Channel 0 Mask */
#define PROV_DMA_CTRL_CORE_CH_START_CH_0    PROV_DMA_CTRL_CORE_CH_START_CH_0_Msk           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_CH_START_CH_0_Msk instead */
#define PROV_DMA_CTRL_CORE_CH_START_CH_1_Pos 1                                              /**< (PROV_DMA_CTRL_CORE_CH_START) Starts Channel 1 Position */
#define PROV_DMA_CTRL_CORE_CH_START_CH_1_Msk (0x1u << PROV_DMA_CTRL_CORE_CH_START_CH_1_Pos)  /**< (PROV_DMA_CTRL_CORE_CH_START) Starts Channel 1 Mask */
#define PROV_DMA_CTRL_CORE_CH_START_CH_1    PROV_DMA_CTRL_CORE_CH_START_CH_1_Msk           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_CH_START_CH_1_Msk instead */
#define PROV_DMA_CTRL_CORE_CH_START_CH_2_Pos 2                                              /**< (PROV_DMA_CTRL_CORE_CH_START) Starts Channel 2 Position */
#define PROV_DMA_CTRL_CORE_CH_START_CH_2_Msk (0x1u << PROV_DMA_CTRL_CORE_CH_START_CH_2_Pos)  /**< (PROV_DMA_CTRL_CORE_CH_START) Starts Channel 2 Mask */
#define PROV_DMA_CTRL_CORE_CH_START_CH_2    PROV_DMA_CTRL_CORE_CH_START_CH_2_Msk           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_CH_START_CH_2_Msk instead */
#define PROV_DMA_CTRL_CORE_CH_START_CH_3_Pos 3                                              /**< (PROV_DMA_CTRL_CORE_CH_START) Starts Channel 3 Position */
#define PROV_DMA_CTRL_CORE_CH_START_CH_3_Msk (0x1u << PROV_DMA_CTRL_CORE_CH_START_CH_3_Pos)  /**< (PROV_DMA_CTRL_CORE_CH_START) Starts Channel 3 Mask */
#define PROV_DMA_CTRL_CORE_CH_START_CH_3    PROV_DMA_CTRL_CORE_CH_START_CH_3_Msk           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_CH_START_CH_3_Msk instead */
#define PROV_DMA_CTRL_CORE_CH_START_CH__Pos 0                                              /**< (PROV_DMA_CTRL_CORE_CH_START Position) Starts Channel 3 */
#define PROV_DMA_CTRL_CORE_CH_START_CH__Msk (0xFu << PROV_DMA_CTRL_CORE_CH_START_CH__Pos)  /**< (PROV_DMA_CTRL_CORE_CH_START Mask) CH_ */
#define PROV_DMA_CTRL_CORE_CH_START_CH_(value) (PROV_DMA_CTRL_CORE_CH_START_CH__Msk & ((value) << PROV_DMA_CTRL_CORE_CH_START_CH__Pos))  
#define PROV_DMA_CTRL_CORE_CH_START_MASK    0x0Fu                                          /**< \deprecated (PROV_DMA_CTRL_CORE_CH_START) Register MASK  (Use PROV_DMA_CTRL_CORE_CH_START_Msk instead)  */
#define PROV_DMA_CTRL_CORE_CH_START_Msk     0x0Fu                                          /**< (PROV_DMA_CTRL_CORE_CH_START) Register Mask  */

/* -------- PROV_DMA_CTRL_PERIPH_RX_CTRL : (PROV_DMA_CTRL Offset: 0x850) (R/W 32) Direct control of peripheral RX request -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t RX_REQ:31;                 /**< bit:  1..31  Allows direct control of the peripheral RX request bus */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_PERIPH_RX_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_PERIPH_RX_CTRL_OFFSET 0x850                                         /**<  (PROV_DMA_CTRL_PERIPH_RX_CTRL) Direct control of peripheral RX request  Offset */
#define PROV_DMA_CTRL_PERIPH_RX_CTRL_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_PERIPH_RX_CTRL) Direct control of peripheral RX request  Reset Value */

#define PROV_DMA_CTRL_PERIPH_RX_CTRL_RX_REQ_Pos 1                                              /**< (PROV_DMA_CTRL_PERIPH_RX_CTRL) Allows direct control of the peripheral RX request bus Position */
#define PROV_DMA_CTRL_PERIPH_RX_CTRL_RX_REQ_Msk (0x7FFFFFFFu << PROV_DMA_CTRL_PERIPH_RX_CTRL_RX_REQ_Pos)  /**< (PROV_DMA_CTRL_PERIPH_RX_CTRL) Allows direct control of the peripheral RX request bus Mask */
#define PROV_DMA_CTRL_PERIPH_RX_CTRL_RX_REQ(value) (PROV_DMA_CTRL_PERIPH_RX_CTRL_RX_REQ_Msk & ((value) << PROV_DMA_CTRL_PERIPH_RX_CTRL_RX_REQ_Pos))
#define PROV_DMA_CTRL_PERIPH_RX_CTRL_MASK   0xFFFFFFFEu                                    /**< \deprecated (PROV_DMA_CTRL_PERIPH_RX_CTRL) Register MASK  (Use PROV_DMA_CTRL_PERIPH_RX_CTRL_Msk instead)  */
#define PROV_DMA_CTRL_PERIPH_RX_CTRL_Msk    0xFFFFFFFEu                                    /**< (PROV_DMA_CTRL_PERIPH_RX_CTRL) Register Mask  */

/* -------- PROV_DMA_CTRL_PERIPH_TX_CTRL : (PROV_DMA_CTRL Offset: 0x860) (R/W 32) Direct control of peripheral TX request -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t :1;                        /**< bit:      0  Reserved */
    uint32_t TX_REQ:31;                 /**< bit:  1..31  Allows direct control of the peripheral TX request bus */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_PERIPH_TX_CTRL_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_PERIPH_TX_CTRL_OFFSET 0x860                                         /**<  (PROV_DMA_CTRL_PERIPH_TX_CTRL) Direct control of peripheral TX request  Offset */
#define PROV_DMA_CTRL_PERIPH_TX_CTRL_RESETVALUE 0x00u                                         /**<  (PROV_DMA_CTRL_PERIPH_TX_CTRL) Direct control of peripheral TX request  Reset Value */

#define PROV_DMA_CTRL_PERIPH_TX_CTRL_TX_REQ_Pos 1                                              /**< (PROV_DMA_CTRL_PERIPH_TX_CTRL) Allows direct control of the peripheral TX request bus Position */
#define PROV_DMA_CTRL_PERIPH_TX_CTRL_TX_REQ_Msk (0x7FFFFFFFu << PROV_DMA_CTRL_PERIPH_TX_CTRL_TX_REQ_Pos)  /**< (PROV_DMA_CTRL_PERIPH_TX_CTRL) Allows direct control of the peripheral TX request bus Mask */
#define PROV_DMA_CTRL_PERIPH_TX_CTRL_TX_REQ(value) (PROV_DMA_CTRL_PERIPH_TX_CTRL_TX_REQ_Msk & ((value) << PROV_DMA_CTRL_PERIPH_TX_CTRL_TX_REQ_Pos))
#define PROV_DMA_CTRL_PERIPH_TX_CTRL_MASK   0xFFFFFFFEu                                    /**< \deprecated (PROV_DMA_CTRL_PERIPH_TX_CTRL) Register MASK  (Use PROV_DMA_CTRL_PERIPH_TX_CTRL_Msk instead)  */
#define PROV_DMA_CTRL_PERIPH_TX_CTRL_Msk    0xFFFFFFFEu                                    /**< (PROV_DMA_CTRL_PERIPH_TX_CTRL) Register Mask  */

/* -------- PROV_DMA_CTRL_CORE_IDLE : (PROV_DMA_CTRL Offset: 0x8d0) (R/ 8) Indicates all channels have stopped and transactions have completed -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint8_t  CORE_IDLE:1;               /**< bit:      0                                           */
    uint8_t  :7;                        /**< bit:   1..7  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint8_t  reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CORE_IDLE_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CORE_IDLE_OFFSET      0x8D0                                         /**<  (PROV_DMA_CTRL_CORE_IDLE) Indicates all channels have stopped and transactions have completed  Offset */
#define PROV_DMA_CTRL_CORE_IDLE_RESETVALUE  0x00u                                         /**<  (PROV_DMA_CTRL_CORE_IDLE) Indicates all channels have stopped and transactions have completed  Reset Value */

#define PROV_DMA_CTRL_CORE_IDLE_CORE_IDLE_Pos 0                                              /**< (PROV_DMA_CTRL_CORE_IDLE)  Position */
#define PROV_DMA_CTRL_CORE_IDLE_CORE_IDLE_Msk (0x1u << PROV_DMA_CTRL_CORE_IDLE_CORE_IDLE_Pos)  /**< (PROV_DMA_CTRL_CORE_IDLE)  Mask */
#define PROV_DMA_CTRL_CORE_IDLE_CORE_IDLE   PROV_DMA_CTRL_CORE_IDLE_CORE_IDLE_Msk          /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_IDLE_CORE_IDLE_Msk instead */
#define PROV_DMA_CTRL_CORE_IDLE_MASK        0x01u                                          /**< \deprecated (PROV_DMA_CTRL_CORE_IDLE) Register MASK  (Use PROV_DMA_CTRL_CORE_IDLE_Msk instead)  */
#define PROV_DMA_CTRL_CORE_IDLE_Msk         0x01u                                          /**< (PROV_DMA_CTRL_CORE_IDLE) Register Mask  */

/* -------- PROV_DMA_CTRL_USER_DEF_STATUS : (PROV_DMA_CTRL Offset: 0x8e0) (R/ 32) User Defined Configurations -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t INT_NUM:4;                 /**< bit:   0..3  Number of bits in interrupt bus          */
    uint32_t :1;                        /**< bit:      4  Reserved */
    uint32_t DUAL_CORE:1;               /**< bit:      5  If set the design has two cores          */
    uint32_t IC:1;                      /**< bit:      6  If set an AHB matrix is used             */
    uint32_t IC_DUAL_PORT:1;            /**< bit:      7  If set AHB matrix has two output ports   */
    uint32_t CLKGATE:1;                 /**< bit:      8  If set design contains functional clock gates */
    uint32_t PORT0_MUX:1;               /**< bit:      9  If set AHB port 0 is using an AHB mux    */
    uint32_t PORT1_MUX:1;               /**< bit:     10  If set AHB port 1 is using an AHB mux    */
    uint32_t :20;                       /**< bit: 11..30  Reserved */
    uint32_t PROJ:1;                    /**< bit:     31  User Defined Project                     */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_USER_DEF_STATUS_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_USER_DEF_STATUS_OFFSET 0x8E0                                         /**<  (PROV_DMA_CTRL_USER_DEF_STATUS) User Defined Configurations  Offset */
#define PROV_DMA_CTRL_USER_DEF_STATUS_RESETVALUE 0x80000001u                                   /**<  (PROV_DMA_CTRL_USER_DEF_STATUS) User Defined Configurations  Reset Value */

#define PROV_DMA_CTRL_USER_DEF_STATUS_INT_NUM_Pos 0                                              /**< (PROV_DMA_CTRL_USER_DEF_STATUS) Number of bits in interrupt bus Position */
#define PROV_DMA_CTRL_USER_DEF_STATUS_INT_NUM_Msk (0xFu << PROV_DMA_CTRL_USER_DEF_STATUS_INT_NUM_Pos)  /**< (PROV_DMA_CTRL_USER_DEF_STATUS) Number of bits in interrupt bus Mask */
#define PROV_DMA_CTRL_USER_DEF_STATUS_INT_NUM(value) (PROV_DMA_CTRL_USER_DEF_STATUS_INT_NUM_Msk & ((value) << PROV_DMA_CTRL_USER_DEF_STATUS_INT_NUM_Pos))
#define PROV_DMA_CTRL_USER_DEF_STATUS_DUAL_CORE_Pos 5                                              /**< (PROV_DMA_CTRL_USER_DEF_STATUS) If set the design has two cores Position */
#define PROV_DMA_CTRL_USER_DEF_STATUS_DUAL_CORE_Msk (0x1u << PROV_DMA_CTRL_USER_DEF_STATUS_DUAL_CORE_Pos)  /**< (PROV_DMA_CTRL_USER_DEF_STATUS) If set the design has two cores Mask */
#define PROV_DMA_CTRL_USER_DEF_STATUS_DUAL_CORE PROV_DMA_CTRL_USER_DEF_STATUS_DUAL_CORE_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_USER_DEF_STATUS_DUAL_CORE_Msk instead */
#define PROV_DMA_CTRL_USER_DEF_STATUS_IC_Pos 6                                              /**< (PROV_DMA_CTRL_USER_DEF_STATUS) If set an AHB matrix is used Position */
#define PROV_DMA_CTRL_USER_DEF_STATUS_IC_Msk (0x1u << PROV_DMA_CTRL_USER_DEF_STATUS_IC_Pos)  /**< (PROV_DMA_CTRL_USER_DEF_STATUS) If set an AHB matrix is used Mask */
#define PROV_DMA_CTRL_USER_DEF_STATUS_IC    PROV_DMA_CTRL_USER_DEF_STATUS_IC_Msk           /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_USER_DEF_STATUS_IC_Msk instead */
#define PROV_DMA_CTRL_USER_DEF_STATUS_IC_DUAL_PORT_Pos 7                                              /**< (PROV_DMA_CTRL_USER_DEF_STATUS) If set AHB matrix has two output ports Position */
#define PROV_DMA_CTRL_USER_DEF_STATUS_IC_DUAL_PORT_Msk (0x1u << PROV_DMA_CTRL_USER_DEF_STATUS_IC_DUAL_PORT_Pos)  /**< (PROV_DMA_CTRL_USER_DEF_STATUS) If set AHB matrix has two output ports Mask */
#define PROV_DMA_CTRL_USER_DEF_STATUS_IC_DUAL_PORT PROV_DMA_CTRL_USER_DEF_STATUS_IC_DUAL_PORT_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_USER_DEF_STATUS_IC_DUAL_PORT_Msk instead */
#define PROV_DMA_CTRL_USER_DEF_STATUS_CLKGATE_Pos 8                                              /**< (PROV_DMA_CTRL_USER_DEF_STATUS) If set design contains functional clock gates Position */
#define PROV_DMA_CTRL_USER_DEF_STATUS_CLKGATE_Msk (0x1u << PROV_DMA_CTRL_USER_DEF_STATUS_CLKGATE_Pos)  /**< (PROV_DMA_CTRL_USER_DEF_STATUS) If set design contains functional clock gates Mask */
#define PROV_DMA_CTRL_USER_DEF_STATUS_CLKGATE PROV_DMA_CTRL_USER_DEF_STATUS_CLKGATE_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_USER_DEF_STATUS_CLKGATE_Msk instead */
#define PROV_DMA_CTRL_USER_DEF_STATUS_PORT0_MUX_Pos 9                                              /**< (PROV_DMA_CTRL_USER_DEF_STATUS) If set AHB port 0 is using an AHB mux Position */
#define PROV_DMA_CTRL_USER_DEF_STATUS_PORT0_MUX_Msk (0x1u << PROV_DMA_CTRL_USER_DEF_STATUS_PORT0_MUX_Pos)  /**< (PROV_DMA_CTRL_USER_DEF_STATUS) If set AHB port 0 is using an AHB mux Mask */
#define PROV_DMA_CTRL_USER_DEF_STATUS_PORT0_MUX PROV_DMA_CTRL_USER_DEF_STATUS_PORT0_MUX_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_USER_DEF_STATUS_PORT0_MUX_Msk instead */
#define PROV_DMA_CTRL_USER_DEF_STATUS_PORT1_MUX_Pos 10                                             /**< (PROV_DMA_CTRL_USER_DEF_STATUS) If set AHB port 1 is using an AHB mux Position */
#define PROV_DMA_CTRL_USER_DEF_STATUS_PORT1_MUX_Msk (0x1u << PROV_DMA_CTRL_USER_DEF_STATUS_PORT1_MUX_Pos)  /**< (PROV_DMA_CTRL_USER_DEF_STATUS) If set AHB port 1 is using an AHB mux Mask */
#define PROV_DMA_CTRL_USER_DEF_STATUS_PORT1_MUX PROV_DMA_CTRL_USER_DEF_STATUS_PORT1_MUX_Msk    /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_USER_DEF_STATUS_PORT1_MUX_Msk instead */
#define PROV_DMA_CTRL_USER_DEF_STATUS_PROJ_Pos 31                                             /**< (PROV_DMA_CTRL_USER_DEF_STATUS) User Defined Project Position */
#define PROV_DMA_CTRL_USER_DEF_STATUS_PROJ_Msk (0x1u << PROV_DMA_CTRL_USER_DEF_STATUS_PROJ_Pos)  /**< (PROV_DMA_CTRL_USER_DEF_STATUS) User Defined Project Mask */
#define PROV_DMA_CTRL_USER_DEF_STATUS_PROJ  PROV_DMA_CTRL_USER_DEF_STATUS_PROJ_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_USER_DEF_STATUS_PROJ_Msk instead */
#define PROV_DMA_CTRL_USER_DEF_STATUS_MASK  0x800007EFu                                    /**< \deprecated (PROV_DMA_CTRL_USER_DEF_STATUS) Register MASK  (Use PROV_DMA_CTRL_USER_DEF_STATUS_Msk instead)  */
#define PROV_DMA_CTRL_USER_DEF_STATUS_Msk   0x800007EFu                                    /**< (PROV_DMA_CTRL_USER_DEF_STATUS) Register Mask  */

/* -------- PROV_DMA_CTRL_CORE_DEF_STATUS0 : (PROV_DMA_CTRL Offset: 0x8f0) (R/ 32) User Defined Core Configurations 0 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint32_t CH_NUM:4;                  /**< bit:   0..3  Number of channels (reads 1, should read 4) */
    uint32_t FIFO_SIZE:4;               /**< bit:   4..7  Log2 of FIFO size per channel            */
    uint32_t WCMD_DEPTH:4;              /**< bit:  8..11  Log2 of maximum number of pending write commands */
    uint32_t RCMD_DEPTH:4;              /**< bit: 12..15  Log2 of maximum number of pending read commands */
    uint32_t ADDR_BITS:6;               /**< bit: 16..21  Number of bits in address buses          */
    uint32_t AHB_BUS_32:1;              /**< bit:     22  If set AHB bus is 32 bit otherwise 64 bit */
    uint32_t :1;                        /**< bit:     23  Reserved */
    uint32_t BUFF_BITS:5;               /**< bit: 24..28  Number of bits in BUFFER_SIZE            */
    uint32_t :3;                        /**< bit: 29..31  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint32_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CORE_DEF_STATUS0_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CORE_DEF_STATUS0_OFFSET 0x8F0                                         /**<  (PROV_DMA_CTRL_CORE_DEF_STATUS0) User Defined Core Configurations 0  Offset */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_RESETVALUE 0xA601151u                                    /**<  (PROV_DMA_CTRL_CORE_DEF_STATUS0) User Defined Core Configurations 0  Reset Value */

#define PROV_DMA_CTRL_CORE_DEF_STATUS0_CH_NUM_Pos 0                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Number of channels (reads 1, should read 4) Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_CH_NUM_Msk (0xFu << PROV_DMA_CTRL_CORE_DEF_STATUS0_CH_NUM_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Number of channels (reads 1, should read 4) Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_CH_NUM(value) (PROV_DMA_CTRL_CORE_DEF_STATUS0_CH_NUM_Msk & ((value) << PROV_DMA_CTRL_CORE_DEF_STATUS0_CH_NUM_Pos))
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_FIFO_SIZE_Pos 4                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Log2 of FIFO size per channel Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_FIFO_SIZE_Msk (0xFu << PROV_DMA_CTRL_CORE_DEF_STATUS0_FIFO_SIZE_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Log2 of FIFO size per channel Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_FIFO_SIZE(value) (PROV_DMA_CTRL_CORE_DEF_STATUS0_FIFO_SIZE_Msk & ((value) << PROV_DMA_CTRL_CORE_DEF_STATUS0_FIFO_SIZE_Pos))
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_WCMD_DEPTH_Pos 8                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Log2 of maximum number of pending write commands Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_WCMD_DEPTH_Msk (0xFu << PROV_DMA_CTRL_CORE_DEF_STATUS0_WCMD_DEPTH_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Log2 of maximum number of pending write commands Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_WCMD_DEPTH(value) (PROV_DMA_CTRL_CORE_DEF_STATUS0_WCMD_DEPTH_Msk & ((value) << PROV_DMA_CTRL_CORE_DEF_STATUS0_WCMD_DEPTH_Pos))
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_RCMD_DEPTH_Pos 12                                             /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Log2 of maximum number of pending read commands Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_RCMD_DEPTH_Msk (0xFu << PROV_DMA_CTRL_CORE_DEF_STATUS0_RCMD_DEPTH_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Log2 of maximum number of pending read commands Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_RCMD_DEPTH(value) (PROV_DMA_CTRL_CORE_DEF_STATUS0_RCMD_DEPTH_Msk & ((value) << PROV_DMA_CTRL_CORE_DEF_STATUS0_RCMD_DEPTH_Pos))
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_ADDR_BITS_Pos 16                                             /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Number of bits in address buses Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_ADDR_BITS_Msk (0x3Fu << PROV_DMA_CTRL_CORE_DEF_STATUS0_ADDR_BITS_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Number of bits in address buses Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_ADDR_BITS(value) (PROV_DMA_CTRL_CORE_DEF_STATUS0_ADDR_BITS_Msk & ((value) << PROV_DMA_CTRL_CORE_DEF_STATUS0_ADDR_BITS_Pos))
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_AHB_BUS_32_Pos 22                                             /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) If set AHB bus is 32 bit otherwise 64 bit Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_AHB_BUS_32_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS0_AHB_BUS_32_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) If set AHB bus is 32 bit otherwise 64 bit Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_AHB_BUS_32 PROV_DMA_CTRL_CORE_DEF_STATUS0_AHB_BUS_32_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS0_AHB_BUS_32_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_BUFF_BITS_Pos 24                                             /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Number of bits in BUFFER_SIZE Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_BUFF_BITS_Msk (0x1Fu << PROV_DMA_CTRL_CORE_DEF_STATUS0_BUFF_BITS_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Number of bits in BUFFER_SIZE Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_BUFF_BITS(value) (PROV_DMA_CTRL_CORE_DEF_STATUS0_BUFF_BITS_Msk & ((value) << PROV_DMA_CTRL_CORE_DEF_STATUS0_BUFF_BITS_Pos))
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_MASK 0x1F7FFFFFu                                    /**< \deprecated (PROV_DMA_CTRL_CORE_DEF_STATUS0) Register MASK  (Use PROV_DMA_CTRL_CORE_DEF_STATUS0_Msk instead)  */
#define PROV_DMA_CTRL_CORE_DEF_STATUS0_Msk  0x1F7FFFFFu                                    /**< (PROV_DMA_CTRL_CORE_DEF_STATUS0) Register Mask  */

/* -------- PROV_DMA_CTRL_CORE_DEF_STATUS1 : (PROV_DMA_CTRL Offset: 0x8f4) (R/ 16) User Defined Core Configurations 1 -------- */
#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef union { 
  struct {
    uint16_t WDT:1;                     /**< bit:      0  Set if core has watchdog timer           */
    uint16_t AHB_TIMEOUT:1;             /**< bit:      1  Set if core supports timeouts on AHB read and write buses */
    uint16_t TOKENS:1;                  /**< bit:      2  Set if core has tokens support           */
    uint16_t PRIO:1;                    /**< bit:      3  Set if core has priority modes support   */
    uint16_t OUTS:1;                    /**< bit:      4  Set if core supports outstanding mode    */
    uint16_t WAIT:1;                    /**< bit:      5  Set if core supports scheduled channels  */
    uint16_t BLOCK:1;                   /**< bit:      6  Set if core supports block transfer      */
    uint16_t JOINT:1;                   /**< bit:      7  Set if core supports joint mode          */
    uint16_t INDEPENDENT:1;             /**< bit:      8  Set if core supports independent mode    */
    uint16_t PERIPH:1;                  /**< bit:      9  Set if core supports peripherals         */
    uint16_t LISTS:1;                   /**< bit:     10  Set if core supports command lists       */
    uint16_t END:1;                     /**< bit:     11  Set if core supports endianness swapping */
    uint16_t CLKDIV:1;                  /**< bit:     12  Set if core supports clock division ratios */
    uint16_t :3;                        /**< bit: 13..15  Reserved */
  } bit;                                /**< Structure used for bit  access */
  uint16_t reg;                         /**< Type used for register access */
} PROV_DMA_CTRL_CORE_DEF_STATUS1_Type;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#define PROV_DMA_CTRL_CORE_DEF_STATUS1_OFFSET 0x8F4                                         /**<  (PROV_DMA_CTRL_CORE_DEF_STATUS1) User Defined Core Configurations 1  Offset */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_RESETVALUE 0xF87u                                        /**<  (PROV_DMA_CTRL_CORE_DEF_STATUS1) User Defined Core Configurations 1  Reset Value */

#define PROV_DMA_CTRL_CORE_DEF_STATUS1_WDT_Pos 0                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core has watchdog timer Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_WDT_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_WDT_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core has watchdog timer Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_WDT  PROV_DMA_CTRL_CORE_DEF_STATUS1_WDT_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_WDT_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_AHB_TIMEOUT_Pos 1                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports timeouts on AHB read and write buses Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_AHB_TIMEOUT_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_AHB_TIMEOUT_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports timeouts on AHB read and write buses Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_AHB_TIMEOUT PROV_DMA_CTRL_CORE_DEF_STATUS1_AHB_TIMEOUT_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_AHB_TIMEOUT_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_TOKENS_Pos 2                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core has tokens support Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_TOKENS_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_TOKENS_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core has tokens support Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_TOKENS PROV_DMA_CTRL_CORE_DEF_STATUS1_TOKENS_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_TOKENS_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_PRIO_Pos 3                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core has priority modes support Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_PRIO_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_PRIO_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core has priority modes support Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_PRIO PROV_DMA_CTRL_CORE_DEF_STATUS1_PRIO_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_PRIO_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_OUTS_Pos 4                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports outstanding mode Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_OUTS_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_OUTS_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports outstanding mode Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_OUTS PROV_DMA_CTRL_CORE_DEF_STATUS1_OUTS_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_OUTS_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_WAIT_Pos 5                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports scheduled channels Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_WAIT_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_WAIT_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports scheduled channels Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_WAIT PROV_DMA_CTRL_CORE_DEF_STATUS1_WAIT_Msk        /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_WAIT_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_BLOCK_Pos 6                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports block transfer Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_BLOCK_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_BLOCK_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports block transfer Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_BLOCK PROV_DMA_CTRL_CORE_DEF_STATUS1_BLOCK_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_BLOCK_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_JOINT_Pos 7                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports joint mode Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_JOINT_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_JOINT_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports joint mode Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_JOINT PROV_DMA_CTRL_CORE_DEF_STATUS1_JOINT_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_JOINT_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_INDEPENDENT_Pos 8                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports independent mode Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_INDEPENDENT_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_INDEPENDENT_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports independent mode Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_INDEPENDENT PROV_DMA_CTRL_CORE_DEF_STATUS1_INDEPENDENT_Msk  /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_INDEPENDENT_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_PERIPH_Pos 9                                              /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports peripherals Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_PERIPH_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_PERIPH_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports peripherals Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_PERIPH PROV_DMA_CTRL_CORE_DEF_STATUS1_PERIPH_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_PERIPH_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_LISTS_Pos 10                                             /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports command lists Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_LISTS_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_LISTS_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports command lists Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_LISTS PROV_DMA_CTRL_CORE_DEF_STATUS1_LISTS_Msk       /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_LISTS_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_END_Pos 11                                             /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports endianness swapping Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_END_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_END_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports endianness swapping Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_END  PROV_DMA_CTRL_CORE_DEF_STATUS1_END_Msk         /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_END_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_CLKDIV_Pos 12                                             /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports clock division ratios Position */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_CLKDIV_Msk (0x1u << PROV_DMA_CTRL_CORE_DEF_STATUS1_CLKDIV_Pos)  /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Set if core supports clock division ratios Mask */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_CLKDIV PROV_DMA_CTRL_CORE_DEF_STATUS1_CLKDIV_Msk      /**< \deprecated Old style mask definition for 1 bit bitfield. Use PROV_DMA_CTRL_CORE_DEF_STATUS1_CLKDIV_Msk instead */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_MASK 0x1FFFu                                        /**< \deprecated (PROV_DMA_CTRL_CORE_DEF_STATUS1) Register MASK  (Use PROV_DMA_CTRL_CORE_DEF_STATUS1_Msk instead)  */
#define PROV_DMA_CTRL_CORE_DEF_STATUS1_Msk  0x1FFFu                                        /**< (PROV_DMA_CTRL_CORE_DEF_STATUS1) Register Mask  */

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#if COMPONENT_TYPEDEF_STYLE == 'R'
/** \brief PROV_DMA_CTRL hardware registers */
typedef struct {  /* 4 Channel DMA Controller */
  RwReg   CH0_CMD_REG0;   /**< (PROV_DMA_CTRL Offset: 0x00) Channel 0 First Line Channel Command */
  RwReg   CH0_CMD_REG1;   /**< (PROV_DMA_CTRL Offset: 0x04) Channel 0 Second Line Channel Command */
  RwReg16 CH0_CMD_REG2;   /**< (PROV_DMA_CTRL Offset: 0x08) Channel 0 Third Line Channel Command */
  __I  uint8_t  Reserved1[2];
  RwReg   CH0_CMD_REG3;   /**< (PROV_DMA_CTRL Offset: 0x0C) Channel 0 Fourth Line Channel Command */
  RwReg   CH0_STATIC_REG0; /**< (PROV_DMA_CTRL Offset: 0x10) Channel 0 Static Configuration Read */
  RwReg   CH0_STATIC_REG1; /**< (PROV_DMA_CTRL Offset: 0x14) Channel 0 Static Configuration Write */
  RwReg   CH0_STATIC_REG2; /**< (PROV_DMA_CTRL Offset: 0x18) Channel 0 Block Mode */
  __I  uint32_t Reserved2[1];
  RwReg   CH0_STATIC_REG4; /**< (PROV_DMA_CTRL Offset: 0x20) Channel 0 Static Configuration Peripheral */
  __I  uint32_t Reserved3[2];
  RoReg16 CH0_RESRICT_REG; /**< (PROV_DMA_CTRL Offset: 0x2C) Channel 0 Restrictions Status Register */
  __I  uint8_t  Reserved4[10];
  RoReg   CH0_FIFO_FULLNESS_REG; /**< (PROV_DMA_CTRL Offset: 0x38) Channel 0 FIFO Fullness Status Register */
  __I  uint32_t Reserved5[1];
  RwReg8  CH0_CH_ENABLE_REG; /**< (PROV_DMA_CTRL Offset: 0x40) Channel 0 Channel Enable Register */
  __I  uint8_t  Reserved6[3];
  WoReg8  CH0_CH_START_REG; /**< (PROV_DMA_CTRL Offset: 0x44) Channel 0 Channel Start Register */
  __I  uint8_t  Reserved7[3];
  RoReg8  CH0_CH_ACTIVE_REG; /**< (PROV_DMA_CTRL Offset: 0x48) Channel 0 Channel Active Status Register */
  __I  uint8_t  Reserved8[7];
  RoReg   CH0_COUNT_REG;  /**< (PROV_DMA_CTRL Offset: 0x50) Channel 0 Buffer Counter Status Register */
  __I  uint32_t Reserved9[19];
  RwReg8  CH0_INT_RAWSTAT_REG; /**< (PROV_DMA_CTRL Offset: 0xA0) Channel 0 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
  __I  uint8_t  Reserved10[3];
  RwReg8  CH0_INT_CLEAR_REG; /**< (PROV_DMA_CTRL Offset: 0xA4) Channel 0 Interrupt Clear (Write 1 to clear) */
  __I  uint8_t  Reserved11[3];
  RwReg8  CH0_INT_ENABLE_REG; /**< (PROV_DMA_CTRL Offset: 0xA8) Channel 0 Interrupt Enable */
  __I  uint8_t  Reserved12[3];
  RwReg8  CH0_INT_STATUS_REG; /**< (PROV_DMA_CTRL Offset: 0xAC) Channel 0 Interrupt Status */
  __I  uint8_t  Reserved13[83];
  RwReg   CH1_CMD_REG0;   /**< (PROV_DMA_CTRL Offset: 0x100) Channel 1 First Line Channel Command */
  RwReg   CH1_CMD_REG1;   /**< (PROV_DMA_CTRL Offset: 0x104) Channel 1 Second Line Channel Command */
  RwReg16 CH1_CMD_REG2;   /**< (PROV_DMA_CTRL Offset: 0x108) Channel 1 Third Line Channel Command */
  __I  uint8_t  Reserved14[2];
  RwReg   CH1_CMD_REG3;   /**< (PROV_DMA_CTRL Offset: 0x10C) Channel 1 Fourth Line Channel Command */
  RwReg   CH1_STATIC_REG0; /**< (PROV_DMA_CTRL Offset: 0x110) Channel 1 Static Configuration Read */
  RwReg   CH1_STATIC_REG1; /**< (PROV_DMA_CTRL Offset: 0x114) Channel 1 Static Configuration Write */
  RwReg   CH1_STATIC_REG2; /**< (PROV_DMA_CTRL Offset: 0x118) Channel 1 Block Mode */
  __I  uint32_t Reserved15[1];
  RwReg   CH1_STATIC_REG4; /**< (PROV_DMA_CTRL Offset: 0x120) Channel 1 Static Configuration Peripheral */
  __I  uint32_t Reserved16[2];
  RoReg16 CH1_RESRICT_REG; /**< (PROV_DMA_CTRL Offset: 0x12C) Channel 1 Restrictions Status Register */
  __I  uint8_t  Reserved17[10];
  RoReg   CH1_FIFO_FULLNESS_REG; /**< (PROV_DMA_CTRL Offset: 0x138) Channel 1 FIFO Fullness Status Register */
  __I  uint32_t Reserved18[1];
  RwReg8  CH1_CH_ENABLE_REG; /**< (PROV_DMA_CTRL Offset: 0x140) Channel 1 Channel Enable Register */
  __I  uint8_t  Reserved19[3];
  WoReg8  CH1_CH_START_REG; /**< (PROV_DMA_CTRL Offset: 0x144) Channel 1 Channel Start Register */
  __I  uint8_t  Reserved20[3];
  RoReg8  CH1_CH_ACTIVE_REG; /**< (PROV_DMA_CTRL Offset: 0x148) Channel 1 Channel Active Status Register */
  __I  uint8_t  Reserved21[7];
  RoReg   CH1_COUNT_REG;  /**< (PROV_DMA_CTRL Offset: 0x150) Channel 1 Buffer Counter Status Register */
  __I  uint32_t Reserved22[19];
  RwReg8  CH1_INT_RAWSTAT_REG; /**< (PROV_DMA_CTRL Offset: 0x1A0) Channel 1 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
  __I  uint8_t  Reserved23[3];
  RwReg8  CH1_INT_CLEAR_REG; /**< (PROV_DMA_CTRL Offset: 0x1A4) Channel 1 Interrupt Clear (Write 1 to clear) */
  __I  uint8_t  Reserved24[3];
  RwReg8  CH1_INT_ENABLE_REG; /**< (PROV_DMA_CTRL Offset: 0x1A8) Channel 1 Interrupt Enable */
  __I  uint8_t  Reserved25[3];
  RwReg8  CH1_INT_STATUS_REG; /**< (PROV_DMA_CTRL Offset: 0x1AC) Channel 1 Interrupt Status */
  __I  uint8_t  Reserved26[83];
  RwReg   CH2_CMD_REG0;   /**< (PROV_DMA_CTRL Offset: 0x200) Channel 2 First Line Channel Command */
  RwReg   CH2_CMD_REG1;   /**< (PROV_DMA_CTRL Offset: 0x204) Channel 2 Second Line Channel Command */
  RwReg16 CH2_CMD_REG2;   /**< (PROV_DMA_CTRL Offset: 0x208) Channel 2 Third Line Channel Command */
  __I  uint8_t  Reserved27[2];
  RwReg   CH2_CMD_REG3;   /**< (PROV_DMA_CTRL Offset: 0x20C) Channel 2 Fourth Line Channel Command */
  RwReg   CH2_STATIC_REG0; /**< (PROV_DMA_CTRL Offset: 0x210) Channel 2 Static Configuration Read */
  RwReg   CH2_STATIC_REG1; /**< (PROV_DMA_CTRL Offset: 0x214) Channel 2 Static Configuration Write */
  RwReg   CH2_STATIC_REG2; /**< (PROV_DMA_CTRL Offset: 0x218) Channel 2 Block Mode */
  __I  uint32_t Reserved28[1];
  RwReg   CH2_STATIC_REG4; /**< (PROV_DMA_CTRL Offset: 0x220) Channel 2 Static Configuration Peripheral */
  __I  uint32_t Reserved29[2];
  RoReg16 CH2_RESRICT_REG; /**< (PROV_DMA_CTRL Offset: 0x22C) Channel 2 Restrictions Status Register */
  __I  uint8_t  Reserved30[10];
  RoReg   CH2_FIFO_FULLNESS_REG; /**< (PROV_DMA_CTRL Offset: 0x238) Channel 2 FIFO Fullness Status Register */
  __I  uint32_t Reserved31[1];
  RwReg8  CH2_CH_ENABLE_REG; /**< (PROV_DMA_CTRL Offset: 0x240) Channel 2 Channel Enable Register */
  __I  uint8_t  Reserved32[3];
  WoReg8  CH2_CH_START_REG; /**< (PROV_DMA_CTRL Offset: 0x244) Channel 2 Channel Start Register */
  __I  uint8_t  Reserved33[3];
  RoReg8  CH2_CH_ACTIVE_REG; /**< (PROV_DMA_CTRL Offset: 0x248) Channel 2 Channel Active Status Register */
  __I  uint8_t  Reserved34[7];
  RoReg   CH2_COUNT_REG;  /**< (PROV_DMA_CTRL Offset: 0x250) Channel 2 Buffer Counter Status Register */
  __I  uint32_t Reserved35[19];
  RwReg8  CH2_INT_RAWSTAT_REG; /**< (PROV_DMA_CTRL Offset: 0x2A0) Channel 2 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
  __I  uint8_t  Reserved36[3];
  RwReg8  CH2_INT_CLEAR_REG; /**< (PROV_DMA_CTRL Offset: 0x2A4) Channel 2 Interrupt Clear (Write 1 to clear) */
  __I  uint8_t  Reserved37[3];
  RwReg8  CH2_INT_ENABLE_REG; /**< (PROV_DMA_CTRL Offset: 0x2A8) Channel 2 Interrupt Enable */
  __I  uint8_t  Reserved38[3];
  RwReg8  CH2_INT_STATUS_REG; /**< (PROV_DMA_CTRL Offset: 0x2AC) Channel 2 Interrupt Status */
  __I  uint8_t  Reserved39[83];
  RwReg   CH3_CMD_REG0;   /**< (PROV_DMA_CTRL Offset: 0x300) Channel 3 First Line Channel Command */
  RwReg   CH3_CMD_REG1;   /**< (PROV_DMA_CTRL Offset: 0x304) Channel 3 Second Line Channel Command */
  RwReg16 CH3_CMD_REG2;   /**< (PROV_DMA_CTRL Offset: 0x308) Channel 3 Third Line Channel Command */
  __I  uint8_t  Reserved40[2];
  RwReg   CH3_CMD_REG3;   /**< (PROV_DMA_CTRL Offset: 0x30C) Channel 3 Fourth Line Channel Command */
  RwReg   CH3_STATIC_REG0; /**< (PROV_DMA_CTRL Offset: 0x310) Channel 3 Static Configuration Read */
  RwReg   CH3_STATIC_REG1; /**< (PROV_DMA_CTRL Offset: 0x314) Channel 3 Static Configuration Write */
  RwReg   CH3_STATIC_REG2; /**< (PROV_DMA_CTRL Offset: 0x318) Channel 3 Block Mode */
  __I  uint32_t Reserved41[1];
  RwReg   CH3_STATIC_REG4; /**< (PROV_DMA_CTRL Offset: 0x320) Channel 3 Static Configuration Peripheral */
  __I  uint32_t Reserved42[2];
  RoReg16 CH3_RESRICT_REG; /**< (PROV_DMA_CTRL Offset: 0x32C) Channel 3 Restrictions Status Register */
  __I  uint8_t  Reserved43[10];
  RoReg   CH3_FIFO_FULLNESS_REG; /**< (PROV_DMA_CTRL Offset: 0x338) Channel 3 FIFO Fullness Status Register */
  __I  uint32_t Reserved44[1];
  RwReg8  CH3_CH_ENABLE_REG; /**< (PROV_DMA_CTRL Offset: 0x340) Channel 3 Channel Enable Register */
  __I  uint8_t  Reserved45[3];
  WoReg8  CH3_CH_START_REG; /**< (PROV_DMA_CTRL Offset: 0x344) Channel 3 Channel Start Register */
  __I  uint8_t  Reserved46[3];
  RoReg8  CH3_CH_ACTIVE_REG; /**< (PROV_DMA_CTRL Offset: 0x348) Channel 3 Channel Active Status Register */
  __I  uint8_t  Reserved47[7];
  RoReg   CH3_COUNT_REG;  /**< (PROV_DMA_CTRL Offset: 0x350) Channel 3 Buffer Counter Status Register */
  __I  uint32_t Reserved48[19];
  RwReg8  CH3_INT_RAWSTAT_REG; /**< (PROV_DMA_CTRL Offset: 0x3A0) Channel 3 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
  __I  uint8_t  Reserved49[3];
  RwReg8  CH3_INT_CLEAR_REG; /**< (PROV_DMA_CTRL Offset: 0x3A4) Channel 3 Interrupt Clear (Write 1 to clear) */
  __I  uint8_t  Reserved50[3];
  RwReg8  CH3_INT_ENABLE_REG; /**< (PROV_DMA_CTRL Offset: 0x3A8) Channel 3 Interrupt Enable */
  __I  uint8_t  Reserved51[3];
  RwReg8  CH3_INT_STATUS_REG; /**< (PROV_DMA_CTRL Offset: 0x3AC) Channel 3 Interrupt Status */
  __I  uint8_t  Reserved52[1107];
  RoReg8  CORE_INT_STATUS; /**< (PROV_DMA_CTRL Offset: 0x800) Indicates which channels caused interrupt */
  __I  uint8_t  Reserved53[47];
  RwReg8  CORE_JOINT_MODE; /**< (PROV_DMA_CTRL Offset: 0x830) If set, core works in joint mode */
  __I  uint8_t  Reserved54[7];
  RwReg16 CORE_PRIORITY;  /**< (PROV_DMA_CTRL Offset: 0x838) Core Priority Channels */
  __I  uint8_t  Reserved55[6];
  RwReg8  CORE_CLKDIV;    /**< (PROV_DMA_CTRL Offset: 0x840) Ratio between main clock and core clock */
  __I  uint8_t  Reserved56[7];
  WoReg8  CORE_CH_START;  /**< (PROV_DMA_CTRL Offset: 0x848) Channel Start */
  __I  uint8_t  Reserved57[7];
  RwReg   PERIPH_RX_CTRL; /**< (PROV_DMA_CTRL Offset: 0x850) Direct control of peripheral RX request */
  __I  uint32_t Reserved58[3];
  RwReg   PERIPH_TX_CTRL; /**< (PROV_DMA_CTRL Offset: 0x860) Direct control of peripheral TX request */
  __I  uint32_t Reserved59[27];
  RoReg8  CORE_IDLE;      /**< (PROV_DMA_CTRL Offset: 0x8D0) Indicates all channels have stopped and transactions have completed */
  __I  uint8_t  Reserved60[15];
  RoReg   USER_DEF_STATUS; /**< (PROV_DMA_CTRL Offset: 0x8E0) User Defined Configurations */
  __I  uint32_t Reserved61[3];
  RoReg   CORE_DEF_STATUS0; /**< (PROV_DMA_CTRL Offset: 0x8F0) User Defined Core Configurations 0 */
  RoReg16 CORE_DEF_STATUS1; /**< (PROV_DMA_CTRL Offset: 0x8F4) User Defined Core Configurations 1 */
} ProvDmaCtrl;

#elif COMPONENT_TYPEDEF_STYLE == 'N'
/** \brief PROV_DMA_CTRL hardware registers */
typedef struct {  /* 4 Channel DMA Controller */
  __IO PROV_DMA_CTRL_CH0_CMD_REG0_Type CH0_CMD_REG0;   /**< Offset: 0x00 (R/W  32) Channel 0 First Line Channel Command */
  __IO PROV_DMA_CTRL_CH0_CMD_REG1_Type CH0_CMD_REG1;   /**< Offset: 0x04 (R/W  32) Channel 0 Second Line Channel Command */
  __IO PROV_DMA_CTRL_CH0_CMD_REG2_Type CH0_CMD_REG2;   /**< Offset: 0x08 (R/W  16) Channel 0 Third Line Channel Command */
       RoReg8                         Reserved1[0x2];
  __IO PROV_DMA_CTRL_CH0_CMD_REG3_Type CH0_CMD_REG3;   /**< Offset: 0x0C (R/W  32) Channel 0 Fourth Line Channel Command */
  __IO PROV_DMA_CTRL_CH0_STATIC_REG0_Type CH0_STATIC_REG0; /**< Offset: 0x10 (R/W  32) Channel 0 Static Configuration Read */
  __IO PROV_DMA_CTRL_CH0_STATIC_REG1_Type CH0_STATIC_REG1; /**< Offset: 0x14 (R/W  32) Channel 0 Static Configuration Write */
  __IO PROV_DMA_CTRL_CH0_STATIC_REG2_Type CH0_STATIC_REG2; /**< Offset: 0x18 (R/W  32) Channel 0 Block Mode */
       RoReg8                         Reserved2[0x4];
  __IO PROV_DMA_CTRL_CH0_STATIC_REG4_Type CH0_STATIC_REG4; /**< Offset: 0x20 (R/W  32) Channel 0 Static Configuration Peripheral */
       RoReg8                         Reserved3[0x8];
  __I  PROV_DMA_CTRL_CH0_RESRICT_REG_Type CH0_RESRICT_REG; /**< Offset: 0x2C (R/   16) Channel 0 Restrictions Status Register */
       RoReg8                         Reserved4[0xA];
  __I  PROV_DMA_CTRL_CH0_FIFO_FULLNESS_REG_Type CH0_FIFO_FULLNESS_REG; /**< Offset: 0x38 (R/   32) Channel 0 FIFO Fullness Status Register */
       RoReg8                         Reserved5[0x4];
  __IO PROV_DMA_CTRL_CH0_CH_ENABLE_REG_Type CH0_CH_ENABLE_REG; /**< Offset: 0x40 (R/W   8) Channel 0 Channel Enable Register */
       RoReg8                         Reserved6[0x3];
  __O  PROV_DMA_CTRL_CH0_CH_START_REG_Type CH0_CH_START_REG; /**< Offset: 0x44 ( /W   8) Channel 0 Channel Start Register */
       RoReg8                         Reserved7[0x3];
  __I  PROV_DMA_CTRL_CH0_CH_ACTIVE_REG_Type CH0_CH_ACTIVE_REG; /**< Offset: 0x48 (R/    8) Channel 0 Channel Active Status Register */
       RoReg8                         Reserved8[0x7];
  __I  PROV_DMA_CTRL_CH0_COUNT_REG_Type CH0_COUNT_REG;  /**< Offset: 0x50 (R/   32) Channel 0 Buffer Counter Status Register */
       RoReg8                         Reserved9[0x4C];
  __IO PROV_DMA_CTRL_CH0_INT_RAWSTAT_REG_Type CH0_INT_RAWSTAT_REG; /**< Offset: 0xA0 (R/W   8) Channel 0 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
       RoReg8                         Reserved10[0x3];
  __IO PROV_DMA_CTRL_CH0_INT_CLEAR_REG_Type CH0_INT_CLEAR_REG; /**< Offset: 0xA4 (R/W   8) Channel 0 Interrupt Clear (Write 1 to clear) */
       RoReg8                         Reserved11[0x3];
  __IO PROV_DMA_CTRL_CH0_INT_ENABLE_REG_Type CH0_INT_ENABLE_REG; /**< Offset: 0xA8 (R/W   8) Channel 0 Interrupt Enable */
       RoReg8                         Reserved12[0x3];
  __IO PROV_DMA_CTRL_CH0_INT_STATUS_REG_Type CH0_INT_STATUS_REG; /**< Offset: 0xAC (R/W   8) Channel 0 Interrupt Status */
       RoReg8                         Reserved13[0x53];
  __IO PROV_DMA_CTRL_CH1_CMD_REG0_Type CH1_CMD_REG0;   /**< Offset: 0x100 (R/W  32) Channel 1 First Line Channel Command */
  __IO PROV_DMA_CTRL_CH1_CMD_REG1_Type CH1_CMD_REG1;   /**< Offset: 0x104 (R/W  32) Channel 1 Second Line Channel Command */
  __IO PROV_DMA_CTRL_CH1_CMD_REG2_Type CH1_CMD_REG2;   /**< Offset: 0x108 (R/W  16) Channel 1 Third Line Channel Command */
       RoReg8                         Reserved14[0x2];
  __IO PROV_DMA_CTRL_CH1_CMD_REG3_Type CH1_CMD_REG3;   /**< Offset: 0x10C (R/W  32) Channel 1 Fourth Line Channel Command */
  __IO PROV_DMA_CTRL_CH1_STATIC_REG0_Type CH1_STATIC_REG0; /**< Offset: 0x110 (R/W  32) Channel 1 Static Configuration Read */
  __IO PROV_DMA_CTRL_CH1_STATIC_REG1_Type CH1_STATIC_REG1; /**< Offset: 0x114 (R/W  32) Channel 1 Static Configuration Write */
  __IO PROV_DMA_CTRL_CH1_STATIC_REG2_Type CH1_STATIC_REG2; /**< Offset: 0x118 (R/W  32) Channel 1 Block Mode */
       RoReg8                         Reserved15[0x4];
  __IO PROV_DMA_CTRL_CH1_STATIC_REG4_Type CH1_STATIC_REG4; /**< Offset: 0x120 (R/W  32) Channel 1 Static Configuration Peripheral */
       RoReg8                         Reserved16[0x8];
  __I  PROV_DMA_CTRL_CH1_RESRICT_REG_Type CH1_RESRICT_REG; /**< Offset: 0x12C (R/   16) Channel 1 Restrictions Status Register */
       RoReg8                         Reserved17[0xA];
  __I  PROV_DMA_CTRL_CH1_FIFO_FULLNESS_REG_Type CH1_FIFO_FULLNESS_REG; /**< Offset: 0x138 (R/   32) Channel 1 FIFO Fullness Status Register */
       RoReg8                         Reserved18[0x4];
  __IO PROV_DMA_CTRL_CH1_CH_ENABLE_REG_Type CH1_CH_ENABLE_REG; /**< Offset: 0x140 (R/W   8) Channel 1 Channel Enable Register */
       RoReg8                         Reserved19[0x3];
  __O  PROV_DMA_CTRL_CH1_CH_START_REG_Type CH1_CH_START_REG; /**< Offset: 0x144 ( /W   8) Channel 1 Channel Start Register */
       RoReg8                         Reserved20[0x3];
  __I  PROV_DMA_CTRL_CH1_CH_ACTIVE_REG_Type CH1_CH_ACTIVE_REG; /**< Offset: 0x148 (R/    8) Channel 1 Channel Active Status Register */
       RoReg8                         Reserved21[0x7];
  __I  PROV_DMA_CTRL_CH1_COUNT_REG_Type CH1_COUNT_REG;  /**< Offset: 0x150 (R/   32) Channel 1 Buffer Counter Status Register */
       RoReg8                         Reserved22[0x4C];
  __IO PROV_DMA_CTRL_CH1_INT_RAWSTAT_REG_Type CH1_INT_RAWSTAT_REG; /**< Offset: 0x1A0 (R/W   8) Channel 1 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
       RoReg8                         Reserved23[0x3];
  __IO PROV_DMA_CTRL_CH1_INT_CLEAR_REG_Type CH1_INT_CLEAR_REG; /**< Offset: 0x1A4 (R/W   8) Channel 1 Interrupt Clear (Write 1 to clear) */
       RoReg8                         Reserved24[0x3];
  __IO PROV_DMA_CTRL_CH1_INT_ENABLE_REG_Type CH1_INT_ENABLE_REG; /**< Offset: 0x1A8 (R/W   8) Channel 1 Interrupt Enable */
       RoReg8                         Reserved25[0x3];
  __IO PROV_DMA_CTRL_CH1_INT_STATUS_REG_Type CH1_INT_STATUS_REG; /**< Offset: 0x1AC (R/W   8) Channel 1 Interrupt Status */
       RoReg8                         Reserved26[0x53];
  __IO PROV_DMA_CTRL_CH2_CMD_REG0_Type CH2_CMD_REG0;   /**< Offset: 0x200 (R/W  32) Channel 2 First Line Channel Command */
  __IO PROV_DMA_CTRL_CH2_CMD_REG1_Type CH2_CMD_REG1;   /**< Offset: 0x204 (R/W  32) Channel 2 Second Line Channel Command */
  __IO PROV_DMA_CTRL_CH2_CMD_REG2_Type CH2_CMD_REG2;   /**< Offset: 0x208 (R/W  16) Channel 2 Third Line Channel Command */
       RoReg8                         Reserved27[0x2];
  __IO PROV_DMA_CTRL_CH2_CMD_REG3_Type CH2_CMD_REG3;   /**< Offset: 0x20C (R/W  32) Channel 2 Fourth Line Channel Command */
  __IO PROV_DMA_CTRL_CH2_STATIC_REG0_Type CH2_STATIC_REG0; /**< Offset: 0x210 (R/W  32) Channel 2 Static Configuration Read */
  __IO PROV_DMA_CTRL_CH2_STATIC_REG1_Type CH2_STATIC_REG1; /**< Offset: 0x214 (R/W  32) Channel 2 Static Configuration Write */
  __IO PROV_DMA_CTRL_CH2_STATIC_REG2_Type CH2_STATIC_REG2; /**< Offset: 0x218 (R/W  32) Channel 2 Block Mode */
       RoReg8                         Reserved28[0x4];
  __IO PROV_DMA_CTRL_CH2_STATIC_REG4_Type CH2_STATIC_REG4; /**< Offset: 0x220 (R/W  32) Channel 2 Static Configuration Peripheral */
       RoReg8                         Reserved29[0x8];
  __I  PROV_DMA_CTRL_CH2_RESRICT_REG_Type CH2_RESRICT_REG; /**< Offset: 0x22C (R/   16) Channel 2 Restrictions Status Register */
       RoReg8                         Reserved30[0xA];
  __I  PROV_DMA_CTRL_CH2_FIFO_FULLNESS_REG_Type CH2_FIFO_FULLNESS_REG; /**< Offset: 0x238 (R/   32) Channel 2 FIFO Fullness Status Register */
       RoReg8                         Reserved31[0x4];
  __IO PROV_DMA_CTRL_CH2_CH_ENABLE_REG_Type CH2_CH_ENABLE_REG; /**< Offset: 0x240 (R/W   8) Channel 2 Channel Enable Register */
       RoReg8                         Reserved32[0x3];
  __O  PROV_DMA_CTRL_CH2_CH_START_REG_Type CH2_CH_START_REG; /**< Offset: 0x244 ( /W   8) Channel 2 Channel Start Register */
       RoReg8                         Reserved33[0x3];
  __I  PROV_DMA_CTRL_CH2_CH_ACTIVE_REG_Type CH2_CH_ACTIVE_REG; /**< Offset: 0x248 (R/    8) Channel 2 Channel Active Status Register */
       RoReg8                         Reserved34[0x7];
  __I  PROV_DMA_CTRL_CH2_COUNT_REG_Type CH2_COUNT_REG;  /**< Offset: 0x250 (R/   32) Channel 2 Buffer Counter Status Register */
       RoReg8                         Reserved35[0x4C];
  __IO PROV_DMA_CTRL_CH2_INT_RAWSTAT_REG_Type CH2_INT_RAWSTAT_REG; /**< Offset: 0x2A0 (R/W   8) Channel 2 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
       RoReg8                         Reserved36[0x3];
  __IO PROV_DMA_CTRL_CH2_INT_CLEAR_REG_Type CH2_INT_CLEAR_REG; /**< Offset: 0x2A4 (R/W   8) Channel 2 Interrupt Clear (Write 1 to clear) */
       RoReg8                         Reserved37[0x3];
  __IO PROV_DMA_CTRL_CH2_INT_ENABLE_REG_Type CH2_INT_ENABLE_REG; /**< Offset: 0x2A8 (R/W   8) Channel 2 Interrupt Enable */
       RoReg8                         Reserved38[0x3];
  __IO PROV_DMA_CTRL_CH2_INT_STATUS_REG_Type CH2_INT_STATUS_REG; /**< Offset: 0x2AC (R/W   8) Channel 2 Interrupt Status */
       RoReg8                         Reserved39[0x53];
  __IO PROV_DMA_CTRL_CH3_CMD_REG0_Type CH3_CMD_REG0;   /**< Offset: 0x300 (R/W  32) Channel 3 First Line Channel Command */
  __IO PROV_DMA_CTRL_CH3_CMD_REG1_Type CH3_CMD_REG1;   /**< Offset: 0x304 (R/W  32) Channel 3 Second Line Channel Command */
  __IO PROV_DMA_CTRL_CH3_CMD_REG2_Type CH3_CMD_REG2;   /**< Offset: 0x308 (R/W  16) Channel 3 Third Line Channel Command */
       RoReg8                         Reserved40[0x2];
  __IO PROV_DMA_CTRL_CH3_CMD_REG3_Type CH3_CMD_REG3;   /**< Offset: 0x30C (R/W  32) Channel 3 Fourth Line Channel Command */
  __IO PROV_DMA_CTRL_CH3_STATIC_REG0_Type CH3_STATIC_REG0; /**< Offset: 0x310 (R/W  32) Channel 3 Static Configuration Read */
  __IO PROV_DMA_CTRL_CH3_STATIC_REG1_Type CH3_STATIC_REG1; /**< Offset: 0x314 (R/W  32) Channel 3 Static Configuration Write */
  __IO PROV_DMA_CTRL_CH3_STATIC_REG2_Type CH3_STATIC_REG2; /**< Offset: 0x318 (R/W  32) Channel 3 Block Mode */
       RoReg8                         Reserved41[0x4];
  __IO PROV_DMA_CTRL_CH3_STATIC_REG4_Type CH3_STATIC_REG4; /**< Offset: 0x320 (R/W  32) Channel 3 Static Configuration Peripheral */
       RoReg8                         Reserved42[0x8];
  __I  PROV_DMA_CTRL_CH3_RESRICT_REG_Type CH3_RESRICT_REG; /**< Offset: 0x32C (R/   16) Channel 3 Restrictions Status Register */
       RoReg8                         Reserved43[0xA];
  __I  PROV_DMA_CTRL_CH3_FIFO_FULLNESS_REG_Type CH3_FIFO_FULLNESS_REG; /**< Offset: 0x338 (R/   32) Channel 3 FIFO Fullness Status Register */
       RoReg8                         Reserved44[0x4];
  __IO PROV_DMA_CTRL_CH3_CH_ENABLE_REG_Type CH3_CH_ENABLE_REG; /**< Offset: 0x340 (R/W   8) Channel 3 Channel Enable Register */
       RoReg8                         Reserved45[0x3];
  __O  PROV_DMA_CTRL_CH3_CH_START_REG_Type CH3_CH_START_REG; /**< Offset: 0x344 ( /W   8) Channel 3 Channel Start Register */
       RoReg8                         Reserved46[0x3];
  __I  PROV_DMA_CTRL_CH3_CH_ACTIVE_REG_Type CH3_CH_ACTIVE_REG; /**< Offset: 0x348 (R/    8) Channel 3 Channel Active Status Register */
       RoReg8                         Reserved47[0x7];
  __I  PROV_DMA_CTRL_CH3_COUNT_REG_Type CH3_COUNT_REG;  /**< Offset: 0x350 (R/   32) Channel 3 Buffer Counter Status Register */
       RoReg8                         Reserved48[0x4C];
  __IO PROV_DMA_CTRL_CH3_INT_RAWSTAT_REG_Type CH3_INT_RAWSTAT_REG; /**< Offset: 0x3A0 (R/W   8) Channel 3 Interrupt Raw Status (Write 1 to any field to issue interrupt) */
       RoReg8                         Reserved49[0x3];
  __IO PROV_DMA_CTRL_CH3_INT_CLEAR_REG_Type CH3_INT_CLEAR_REG; /**< Offset: 0x3A4 (R/W   8) Channel 3 Interrupt Clear (Write 1 to clear) */
       RoReg8                         Reserved50[0x3];
  __IO PROV_DMA_CTRL_CH3_INT_ENABLE_REG_Type CH3_INT_ENABLE_REG; /**< Offset: 0x3A8 (R/W   8) Channel 3 Interrupt Enable */
       RoReg8                         Reserved51[0x3];
  __IO PROV_DMA_CTRL_CH3_INT_STATUS_REG_Type CH3_INT_STATUS_REG; /**< Offset: 0x3AC (R/W   8) Channel 3 Interrupt Status */
       RoReg8                         Reserved52[0x453];
  __I  PROV_DMA_CTRL_CORE_INT_STATUS_Type CORE_INT_STATUS; /**< Offset: 0x800 (R/    8) Indicates which channels caused interrupt */
       RoReg8                         Reserved53[0x2F];
  __IO PROV_DMA_CTRL_CORE_JOINT_MODE_Type CORE_JOINT_MODE; /**< Offset: 0x830 (R/W   8) If set, core works in joint mode */
       RoReg8                         Reserved54[0x7];
  __IO PROV_DMA_CTRL_CORE_PRIORITY_Type CORE_PRIORITY;  /**< Offset: 0x838 (R/W  16) Core Priority Channels */
       RoReg8                         Reserved55[0x6];
  __IO PROV_DMA_CTRL_CORE_CLKDIV_Type CORE_CLKDIV;    /**< Offset: 0x840 (R/W   8) Ratio between main clock and core clock */
       RoReg8                         Reserved56[0x7];
  __O  PROV_DMA_CTRL_CORE_CH_START_Type CORE_CH_START;  /**< Offset: 0x848 ( /W   8) Channel Start */
       RoReg8                         Reserved57[0x7];
  __IO PROV_DMA_CTRL_PERIPH_RX_CTRL_Type PERIPH_RX_CTRL; /**< Offset: 0x850 (R/W  32) Direct control of peripheral RX request */
       RoReg8                         Reserved58[0xC];
  __IO PROV_DMA_CTRL_PERIPH_TX_CTRL_Type PERIPH_TX_CTRL; /**< Offset: 0x860 (R/W  32) Direct control of peripheral TX request */
       RoReg8                         Reserved59[0x6C];
  __I  PROV_DMA_CTRL_CORE_IDLE_Type   CORE_IDLE;      /**< Offset: 0x8D0 (R/    8) Indicates all channels have stopped and transactions have completed */
       RoReg8                         Reserved60[0xF];
  __I  PROV_DMA_CTRL_USER_DEF_STATUS_Type USER_DEF_STATUS; /**< Offset: 0x8E0 (R/   32) User Defined Configurations */
       RoReg8                         Reserved61[0xC];
  __I  PROV_DMA_CTRL_CORE_DEF_STATUS0_Type CORE_DEF_STATUS0; /**< Offset: 0x8F0 (R/   32) User Defined Core Configurations 0 */
  __I  PROV_DMA_CTRL_CORE_DEF_STATUS1_Type CORE_DEF_STATUS1; /**< Offset: 0x8F4 (R/   16) User Defined Core Configurations 1 */
} ProvDmaCtrl;

#else /* COMPONENT_TYPEDEF_STYLE */
#error Unknown component typedef style
#endif /* COMPONENT_TYPEDEF_STYLE */

#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/** @}*/


#endif /* _SAMB11_PROV_DMA_CTRL_COMPONENT_ */
