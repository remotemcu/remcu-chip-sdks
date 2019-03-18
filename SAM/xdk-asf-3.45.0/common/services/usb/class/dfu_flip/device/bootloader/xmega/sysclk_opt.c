/**
 * \file
 *
 * \brief Chip-specific system clock management functions
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

#include <compiler.h>

#include <sysclk.h>
#include <osc.h>
#include <pll.h>
#if (CONFIG_OSC_RC32_CAL==48000000UL)
#include <nvm.h>
#endif

void sysclk_init_opt(void)
{
	sysclk_set_prescalers(CONFIG_SYSCLK_PSADIV,CONFIG_SYSCLK_PSBCDIV);
	/* Loads 48MHz internal RC calibration value */
	DFLLRC32M.CALA=nvm_read_production_signature_row(
			nvm_get_production_signature_row_offset(USBRCOSCA));
	DFLLRC32M.CALB=nvm_read_production_signature_row(
			nvm_get_production_signature_row_offset(USBRCOSC));
	osc_enable(OSC_ID_RC32MHZ);
	osc_wait_ready(OSC_ID_RC32MHZ);
	ccp_write_io((uint8_t *)&CLK.CTRL, CONFIG_SYSCLK_SOURCE);
	OSC.DFLLCTRL &= ~(OSC_RC32MCREF_gm);
	// Calibrate 32MRC at 48MHz using USB SOF
	// 48MHz/1kHz=0xBB80
	DFLLRC32M.COMP1=0x80;
	DFLLRC32M.COMP2=0xBB;
	OSC.DFLLCTRL |= OSC_RC32MCREF_USBSOF_gc;
	DFLLRC32M.CTRL |= DFLL_ENABLE_bm;
}


/**
 * \brief Enable clock for the USB module
 *
 * \pre CONFIG_USBCLK_SOURCE must be defined.
 *
 * \param freq The required USB clock frequency in MHz:
 * \arg \c 6 for 6 MHz
 * \arg \c 48 for 48 MHz
 */
void sysclk_enable_usb_opt(uint8_t freq)
{
	Assert(freq == 48);
	sysclk_enable_module(SYSCLK_PORT_GEN, SYSCLK_USB);
	ccp_write_io((uint8_t *)&CLK.USBCTRL, 0
		| CLK_USBSRC_RC32M_gc
		| CLK_USBSEN_bm);
}

/**
 * \brief Disable clock for the USB module
 */
void sysclk_disable_usb_opt(void)
{
	ccp_write_io((uint8_t *)&CLK.USBCTRL, 0);
}
