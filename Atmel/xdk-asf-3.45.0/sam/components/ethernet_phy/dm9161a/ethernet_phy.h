/**
 * \file
 *
 * \brief API driver for DM9161A PHY component.
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

#ifndef DM9161A_H_INCLUDED
#define DM9161A_H_INCLUDED

#include "compiler.h"
#include "board.h"
#include "emac.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
 extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \brief Perform a HW initialization to the PHY ( via RSTC ) and set up clocks.
 *
 * This should be called only once to initialize the PHY pre-settings.
 * The PHY address is the reset status of CRS, RXD[3:0] (the emacPins' pullups).
 * The COL pin is used to select MII mode on reset (pulled up for Reduced MII).
 * The RXDV pin is used to select test mode on reset (pulled up for test mode).
 * The above pins should be predefined for corresponding settings in resetPins.
 * The EMAC peripheral pins are configured after the reset is done.
 *
 * \param p_emac   Pointer to the EMAC instance. 
 * \param uc_phy_addr PHY address.
 * \param ul_mck EMAC MCK. 
 *
 * Return EMAC_OK if successfully, EMAC_TIMEOUT if timeout.
 */
uint8_t ethernet_phy_init(Emac *p_emac, uint8_t uc_phy_addr, uint32_t ul_mck);


/**
 * \brief Get the Link & speed settings, and automatically set up the EMAC with the
 * settings.
 *
 * \param p_emac   Pointer to the EMAC instance. 
 * \param uc_phy_addr PHY address.
 * \param uc_apply_setting_flag Set to 0 to not apply the PHY configurations, else to apply.
 *
 * Return EMAC_OK if successfully, EMAC_TIMEOUT if timeout. 
 */
uint8_t ethernet_phy_set_link(Emac *p_emac, uint8_t uc_phy_addr,
		uint8_t uc_apply_setting_flag);


/**
 * \brief Issue an auto negotiation of the PHY.
 *
 * \param p_emac   Pointer to the EMAC instance. 
 * \param uc_phy_addr PHY address.
 *
 * Return EMAC_OK if successfully, EMAC_TIMEOUT if timeout. 
 */
uint8_t ethernet_phy_auto_negotiate(Emac *p_emac, uint8_t uc_phy_addr);

/**
 * \brief Issue a SW reset to reset all registers of the PHY.
 *
 * \param p_emac   Pointer to the EMAC instance. 
 * \param uc_phy_addr PHY address.
 *
 * \Return EMAC_OK if successfully, EMAC_TIMEOUT if timeout.
 */
uint8_t ethernet_phy_reset(Emac *p_emac, uint8_t uc_phy_addr);

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

#endif /* DM9161A_H_INCLUDED */
