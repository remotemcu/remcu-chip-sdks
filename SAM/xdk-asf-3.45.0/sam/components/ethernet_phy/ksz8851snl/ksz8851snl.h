/**
 *
 * \file
 *
 * \brief KS8851SNL driver for SAM.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef KSZ8851SNL_H_INCLUDED
#define KSZ8851SNL_H_INCLUDED

#include "gpio.h"

void configure_intn(void (*p_handler) (uint32_t, uint32_t));
void ksz8851_reg_setbits(uint16_t reg, uint16_t bits_to_set);
void ksz8851_reg_clrbits(uint16_t reg, uint16_t bits_to_clr);
void ksz8851_fifo_read(uint8_t *buf, uint32_t len);
void ksz8851_fifo_write(uint8_t *buf, uint32_t tot_len, uint32_t len);
void ksz8851_fifo_dummy(uint32_t len);
void ksz8851_reg_write(uint16_t reg, uint16_t wrdata);
uint16_t ksz8851_reg_read(uint16_t reg);
uint32_t ksz8851snl_init(void);

#endif /* KSZ8851SNL_H_INCLUDED */
