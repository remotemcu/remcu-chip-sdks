/*****************************************************************************
 *
 * \file
 *
 * \brief Configuration file for NF Driver.
 *
 * \note The values defined in this file are device-specific. See the device
 *       datasheet for further information.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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
 ******************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _SMC_NF_H_
#define _SMC_NF_H_


//! SMC Peripheral Memory Size in Bytes
#define EXT_SM_SIZE            0x200001

//! SMC Data Bus Width
#define SMC_DBW                8

//! Whether 8-bit SM chips are connected on the SMC
#define SMC_8_BIT_CHIPS        true



// NCS setup time. Unit: ns.
#define NCS_WR_SETUP            0

// NCS pulse time. Unit: ns.
#define NCS_WR_PULSE            100

// NCS hold time. Unit: ns.
#define NCS_WR_HOLD             0

// NWE setup time. Unit: ns.
#define NWE_SETUP               20

// NWE pulse time. Unit: ns.
#define NWE_PULSE               40

// NWE hold time. Unit: ns.
#define NWE_HOLD                40

// Write cycle time. Unit: ns.
#define NWE_CYCLE               Max((NCS_WR_SETUP + NCS_WR_PULSE + NCS_WR_HOLD),(NWE_SETUP + NWE_PULSE + NWE_HOLD))

// NCS setup time. Unit: ns.
#define NCS_RD_SETUP            0

// NCS pulse time. Unit: ns.
#define NCS_RD_PULSE            100

// NCS hold time. Unit: ns.
#define NCS_RD_HOLD             0

// NRD setup time. Unit: ns.
#define NRD_SETUP               20

// NRD pulse time. Unit: ns.
#define NRD_PULSE               40

// NRD hold time. Unit: ns.
#define NRD_HOLD                40

// Read cycle time. Unit: ns.
#define NRD_CYCLE               Max((NCS_RD_SETUP + NCS_RD_PULSE + NCS_RD_HOLD),(NRD_SETUP + NRD_PULSE + NRD_HOLD))



// Data float time
#define TDF_CYCLES              0
#define TDF_OPTIM               false

// Page mode
#define PAGE_MODE               false
#define PAGE_SIZE               0

//! Whether read is controlled by NCS or by NRD
#define NCS_CONTROLLED_READ     false

//! Whether write is controlled by NCS or by NWE
#define NCS_CONTROLLED_WRITE    false

//! Whether to use the NWAIT pin
#define NWAIT_MODE              AVR32_SMC_EXNW_MODE_DISABLED

#endif //_SMC_NF_H_
