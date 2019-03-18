/**
 * \file
 *
 * \brief CAN transceiver SN65HVD234 driver.
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

#ifndef CAN_SN65HVD234_H
#define CAN_SN65HVD234_H

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	/** PIO dedicated to RS pin index. */
	uint32_t pio_rs_idx;
	/** PIO dedicated to EN pin index. */
	uint32_t pio_en_idx;
} sn65hvd234_ctrl_t;

void sn65hvd234_set_rs(sn65hvd234_ctrl_t *p_component, uint32_t pin_idx);
void sn65hvd234_set_en(sn65hvd234_ctrl_t *p_component, uint32_t pin_idx);
void sn65hvd234_enable(sn65hvd234_ctrl_t *p_component);
void sn65hvd234_disable(sn65hvd234_ctrl_t *p_component);
void sn65hvd234_enable_low_power(sn65hvd234_ctrl_t *p_component);
void sn65hvd234_disable_low_power(sn65hvd234_ctrl_t *p_component);

#ifdef __cplusplus
}
#endif
#endif /* CAN_SN65HVD234_H */
