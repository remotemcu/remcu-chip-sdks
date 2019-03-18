/**
 * \file
 *
 * \brief SAM L21 Xplained Pro board configuration.
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef CONF_CCL_EXAMPLE_H_INCLUDED
#define CONF_CCL_EXAMPLE_H_INCLUDED

#define CCL_TC                  TC4                   // Def TC
#define CCL_ALTTC               TC0                   // Alt TC
#define MUX_CCL_TC_OUT          MUX_PA18E_TC4_WO0     // Def TC mux out
#define PIN_CCL_TC_OUT          PIN_PA18E_TC4_WO0     // Def TC pin out
#define MUX_CCL_ALTTC_OUT       MUX_PB08E_TC0_WO0     // Alt TC mux out
#define PIN_CCL_ALTTC_OUT       PIN_PB08E_TC0_WO0     // Alt TC pin out
#define EVSYS_GEN_CCL_TC_OVF    EVSYS_ID_GEN_TC4_OVF  // Def TC event gen overflow
#define EVSYS_GEN_CCL_ALTTC_OVF EVSYS_ID_GEN_TC0_OVF  // Alt TC event gen overflow
#define EVSYS_USER_CCL_ALTTC    EVSYS_ID_USER_TC0_EVU // Alt TC event user
#define CCL_ALTTC_DMAC_OVF      TC0_DMAC_ID_OVF       // Alt TC DMAC trigger

#define MUX_CCL_OUTPUT          MUX_PA07I_CCL_OUT0    // CCL pin out
#define PIN_CCL_OUTPUT          PIN_PA07I_CCL_OUT0    // CCL mux out

#endif /* CONF_CCL_EXAMPLE_H_INCLUDED */
