/***************************************************************************//**
 * @file uartdrv_config.h
 * @brief UARTDRV configuration file.
 * @version 5.1.2
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2015 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/
#ifndef __SILICON_LABS_UARTDRV_CONFIG_H__
#define __SILICON_LABS_UARTDRV_CONFIG_H__

/***************************************************************************//**
 * @addtogroup emdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup UARTDRV
 * @{
 ******************************************************************************/

/// Size of the receive operation queue.
/// @details
///   The maximum number of receive operations that can be queued up for one
///   driver instance before @ref UARTDRV_Receive() returns
///   @ref ECODE_EMDRV_UARTDRV_QUEUE_FULL.
/// @note
///   This macro is not used by the UARTDRV itself, but is intended to be used
///   with the @ref DEFINE_BUF_QUEUE macro by the user of the driver to allocate
///   instances of the @ref UARTDRV_Buffer_FifoQueue_t struct.
#if !defined(EMDRV_UARTDRV_MAX_CONCURRENT_RX_BUFS)
#define EMDRV_UARTDRV_MAX_CONCURRENT_RX_BUFS    6
#endif

/// Size of the transmit operation queue.
/// @details
///   The maximum number of transmit operations that can be queued up for one
///   driver instance before @ref UARTDRV_Transmit() returns
///   @ref ECODE_EMDRV_UARTDRV_QUEUE_FULL.
/// @note
///   This macro is not used by the UARTDRV itself, but is intended to be used
///   with the @ref DEFINE_BUF_QUEUE macro by the user of the driver to allocate
///   instances of the @ref UARTDRV_Buffer_FifoQueue_t struct.
#if !defined(EMDRV_UARTDRV_MAX_CONCURRENT_TX_BUFS)
#define EMDRV_UARTDRV_MAX_CONCURRENT_TX_BUFS    6
#endif

/// Set to 1 to include flow control support
#if !defined(EMDRV_UARTDRV_FLOW_CONTROL_ENABLE)
#define EMDRV_UARTDRV_FLOW_CONTROL_ENABLE       1
#endif

/// Maximum number of driver instances.
/// @note
///   This maximum applies only when @ref EMDRV_UARTDRV_FLOW_CONTROL_ENABLE = 1.
#if !defined(EMDRV_UARTDRV_MAX_DRIVER_INSTANCES)
#define EMDRV_UARTDRV_MAX_DRIVER_INSTANCES      4
#endif

/// UART software flow control code: request peer to start TX
#if !defined(UARTDRV_FC_SW_XON)
#define UARTDRV_FC_SW_XON                       0x11
#endif

/// UART software flow control code: request peer to stop TX
#if !defined(UARTDRV_FC_SW_XOFF)
#define UARTDRV_FC_SW_XOFF                      0x13
#endif

/** @} (end addtogroup UARTDRV) */
/** @} (end addtogroup emdrv) */

#endif /* __SILICON_LABS_UARTDRV_CONFIG_H__ */
