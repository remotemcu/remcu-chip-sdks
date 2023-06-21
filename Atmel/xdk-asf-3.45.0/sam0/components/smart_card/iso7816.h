/**
 * \file
 *
 * \brief Smart Card Standard ISO7816 driver.
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef ISO7816_H_INCLUDED
#define ISO7816_H_INCLUDED

#include <compiler.h>
#include "port.h"
#include "usart.h"

#define ISO7816_PIN_POWER_ON    true
#define ISO7816_PIN_POWER_OFF   false

/** Flip flop for send and receive char. */
#define ISO7816_USART_SEND      0
#define ISO7816_USART_RCV       1

void iso7816_init(struct usart_module *const module, uint32_t pin_rst, \
				uint32_t clock_get_hz);
uint16_t iso7816_xfr_block_tpdu_t0(const uint8_t *p_apdu, uint8_t *p_message,
				uint16_t us_length);
void iso7816_data_block_atr(uint8_t *p_atr, uint8_t *p_length);
bool iso7816_get_reset_statuts(void);
void iso7816_cold_reset(void);
void iso7816_warm_reset(void);
void iso7816_decode_atr(uint8_t *p_atr);

#endif /* ISO7816_H_INCLUDED */

