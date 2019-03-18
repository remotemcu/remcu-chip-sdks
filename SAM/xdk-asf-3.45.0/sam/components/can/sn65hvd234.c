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

/**
 * \defgroup sam_component_sn65hvd234_transceiver_group CAN - SN65HVD234
 *  Transceiver
 *
 * This driver provides access to the main features of the SN65HVD234
 * transceiver.
 *
 * Control the RS and EN pin level for SN65HVD234.
 *
 * \{
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include "board.h"
#include "sn65hvd234.h"
#include "ioport.h"

#define CAN_RS_HIGH true
#define CAN_RS_LOW  false
#define CAN_EN_HIGH true
#define CAN_EN_LOW  false

/**
 * \brief Initialize RS pin for transceiver.
 *
 * \param p_component Pointer to SN65HVD234 control structure.
 * \param pin_idx     The pin index value for transceiver RS pin.
 */
void sn65hvd234_set_rs(sn65hvd234_ctrl_t *p_component, uint32_t pin_idx)
{
	p_component->pio_rs_idx = pin_idx;
}

/**
 * \brief Initialize EN pin for transceiver.
 *
 * \param p_component Pointer to SN65HVD234 control structure.
 * \param pin_idx     The pin index value for transceiver EN pin.
 */
void sn65hvd234_set_en(sn65hvd234_ctrl_t *p_component, uint32_t pin_idx)
{
	p_component->pio_en_idx = pin_idx;
}

/**
 * \brief Enable transceiver.
 *
 * \param p_component Pointer to SN65HVD234 control structure.
 */
void sn65hvd234_enable(sn65hvd234_ctrl_t *p_component)
{
	/* Raise EN pin of SN65HVD234 to High Level (Vcc). */
	ioport_set_pin_level(p_component->pio_en_idx, CAN_EN_HIGH);
}

/**
 * \brief Disable transceiver.
 *
 * \param p_component Pointer to SN65HVD234 control structure.
 */
void sn65hvd234_disable(sn65hvd234_ctrl_t *p_component)
{
	/* Lower EN pin of SN65HVD234 to Low Level (0.0v). */
	ioport_set_pin_level(p_component->pio_en_idx, CAN_EN_LOW);
}

/**
 * \brief Turn the component into low power mode, listening only.
 *
 * \param p_component Pointer to SN65HVD234 control structure.
 */
void sn65hvd234_enable_low_power(sn65hvd234_ctrl_t *p_component)
{
	/* Raise RS pin of SN65HVD234 to more than 0.75v. */
	ioport_set_pin_level(p_component->pio_rs_idx, CAN_RS_HIGH);
}

/**
 * \brief Resume to Normal mode by exiting from low power mode.
 *
 * \param p_component Pointer to SN65HVD234 control structure.
 */
void sn65hvd234_disable_low_power(sn65hvd234_ctrl_t *p_component)
{
	/* Lower RS pin of SN65HVD234 to 0.0v~0.33v. */
	ioport_set_pin_level(p_component->pio_rs_idx, CAN_RS_LOW);
}

/**
 * \}
 */
