/**
 * \file
 *
 * \brief Atmel AVR and AVR UC3 Sensor NVRAM Interfaces
 *
 * This module provides general access to the NVRAM interfaces
 * in the Atmel Software Framework.
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

#ifndef _SENSOR_NVRAM_H_
#define _SENSOR_NVRAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <compiler.h>

/** \brief Data type for NVRAM memory addresses. */
typedef uint16_t nvram_addr_t;

/** \brief Atmel platform non-volatile memory spaces. */
/** @{ */
#if XMEGA
#   include <nvm.h>

#   define SENSOR_NVM_BASE      (USER_SIGNATURES_START)
#   define SENSOR_NVM_OFFSET    (0)
#   define SENSOR_NVM_SIZE      (USER_SIGNATURES_SIZE)
#elif defined(AVR32_FLASHC)
#   include <flashc.h>

#   define SENSOR_NVM_BASE      (AVR32_FLASHC_USER_PAGE_ADDRESS)
#   define SENSOR_NVM_OFFSET    (0x10)
#   define SENSOR_NVM_SIZE      (AVR32_FLASHC_USER_PAGE_SIZE)
#elif defined(AVR32_FLASHCDW)
#   include <flashcdw.h>

#   define SENSOR_NVM_BASE      (AVR32_FLASHCDW_USER_PAGE_ADDRESS)
#   define SENSOR_NVM_OFFSET    (0x10)
#   define SENSOR_NVM_SIZE      (AVR32_FLASHCDW_USER_PAGE_SIZE)
#endif
/** @} */

/** \brief Write a buffer to non-volatile RAM
 *
 * This routine writes \c count Bytes to the NVRAM destination pointed
 * to by \c dst from the source buffer pointed to by \c src.
 *
 * \param   dst     the write destination in the NVRAM address space
 * \param   src     the source buffer in program data memory space
 * \param   count   the number of Bytes to write
 *
 * \return  Nothing.
 */
extern void nvram_write(nvram_addr_t dst, const void *src, size_t count);

/** \brief Read a buffer from non-volatile RAM
 *
 * This routine reads \c count Bytes from the NVRAM source pointed
 * to by \c src to the destination buffer pointed to by \c dst.
 *
 * \param   src     the read source in the NVRAM address space
 * \param   dst     the destination buffer in program data memory space
 * \param   count   the number of Bytes to read
 *
 * \return  Nothing.
 */
extern void nvram_read(nvram_addr_t src, void *dst, size_t count);

#ifdef __cplusplus
}
#endif

#endif
