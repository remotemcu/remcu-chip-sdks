/**
 * \file
 *
 * \brief SERCOM SPI master with vectored I/O driver configuration
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef CONF_SPI_MASTER_VEC_H
#define CONF_SPI_MASTER_VEC_H

#ifdef __FREERTOS__
#  include <FreeRTOS.h>
#  include <semphr.h>

#  define CONF_SPI_MASTER_VEC_OS_SUPPORT
#  define CONF_SPI_MASTER_VEC_SEMAPHORE_TYPE                   xSemaphoreHandle
#  define CONF_SPI_MASTER_VEC_CREATE_SEMAPHORE(semaphore)  \
		vSemaphoreCreateBinary(semaphore)
#  define CONF_SPI_MASTER_VEC_TAKE_SEMAPHORE(semaphore)  \
		xSemaphoreTake((semaphore), portMAX_DELAY)
#  define CONF_SPI_MASTER_VEC_GIVE_SEMAPHORE(semaphore)  \
		xSemaphoreGive((semaphore))
#  define CONF_SPI_MASTER_VEC_GIVE_SEMAPHORE_FROM_ISR(semaphore)  \
		xSemaphoreGiveFromISR((semaphore), NULL)
#endif

#endif // CONF_SPI_MASTER_VEC_H
