/**
 * \file
 *
 * \brief AT25DFx SerialFlash driver public SPI HAL interface.
 *
 * Copyright (C) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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
 * Support and FAQ: visit <a href="http://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef AT25DFX_HAL_H
#define AT25DFX_HAL_H

#include <spi_master_vec.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup asfdoc_common2_at25dfx_group
 *
 * @{
 */

/** Typedef for SPI HAL */
typedef struct spi_master_vec_module at25dfx_spi_module_t;

/**
 * \brief Initialize SPI configuration
 *
 * This function initializes the SPI configuration struct with default settings
 * that should work with SerialFlash devices.
 *
 * The user can change the baud rate and the MUX settings for SERCOM and GPIO
 * pads, but should leave all other settings intact.
 *
 * \param[out] config Address of config struct to initialize.
 */
static inline void at25dfx_spi_master_vec_get_config_defaults(
		struct spi_master_vec_config *const config)
{
	spi_master_vec_get_config_defaults(config);
}

/** @ */

#ifdef __cplusplus
}
#endif

#endif // AT25DFX_HAL_H