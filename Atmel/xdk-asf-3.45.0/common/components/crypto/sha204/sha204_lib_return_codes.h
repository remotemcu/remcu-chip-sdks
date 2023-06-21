/*
 * \file
 *
 * \brief ATSHA204 library return codes
 *
 *
 * Copyright (c) 2011-2018 Microchip Technology Inc. and its subsidiaries.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef SHA204_LIB_RETURN_CODES_H
#   define SHA204_LIB_RETURN_CODES_H

#include <compiler.h>               //!< compiler dependent definitions

#define SHA204_SUCCESS              ((uint8_t)  0x00) //!< Function succeeded.
#define SHA204_PARSE_ERROR          ((uint8_t)  0xD2) //!< response status byte indicates parsing error
#define SHA204_CMD_FAIL             ((uint8_t)  0xD3) //!< response status byte indicates command execution error
#define SHA204_STATUS_CRC           ((uint8_t)  0xD4) //!< response status byte indicates CRC error
#define SHA204_FUNC_FAIL            ((uint8_t)  0xE0) //!< Function could not execute due to incorrect condition / state.
#define SHA204_BAD_PARAM            ((uint8_t)  0xE2) //!< bad argument (out of range, null pointer, etc.)
#define SHA204_INVALID_SIZE         ((uint8_t)  0xE4) //!< Count value is out of range or greater than buffer size.
#define SHA204_BAD_CRC              ((uint8_t)  0xE5) //!< incorrect CRC received
#define SHA204_RX_FAIL              ((uint8_t)  0xE6) //!< Timed out while waiting for response. Number of bytes received is > 0.
#define SHA204_RX_NO_RESPONSE       ((uint8_t)  0xE7) //!< Not an error while the Command layer is polling for a command response.
#define SHA204_RESYNC_WITH_WAKEUP   ((uint8_t)  0xE8) //!< re-synchronization succeeded, but only after generating a Wake-up

#define SHA204_COMM_FAIL            ((uint8_t)  0xF0) //!< Communication with device failed. Same as in hardware dependent modules.
#define SHA204_TIMEOUT              ((uint8_t)  0xF1) //!< Timed out while waiting for response. Number of bytes received is 0.

#endif
