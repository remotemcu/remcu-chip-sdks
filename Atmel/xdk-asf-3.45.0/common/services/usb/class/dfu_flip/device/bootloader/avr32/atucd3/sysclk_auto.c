/**
 * \file
 *
 * \brief Application-specific system clock management to support automatic
 * detection of external oscillator
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

#include "preprocessor.h"
#include "compiler.h"
#include "board.h"
#include "pm_uc3d.h"
#include "scif_uc3d.h"
#include "ast.h"
#include "cycle_counter.h"
#include "flashcdw.h"
#include "sysclk_auto.h"
#include "freq_detect.h"

/*! \name External routines required by main.c file and usbc driver
 */
//! \{

/**
 * \brief  Detects extern OSC frequency and initialize system clocks on it
 */
void sysclk_auto_init(void)
{
	int mul;

	// Switch to OSC ISP
	// Set max startup time to make sure any crystal will be supported
	// We cannot use a TC to measure this OSC frequency
	// because the master clock must be faster than the clock selected by the TC

	// Configure OSC0 in crystal mode, external crystal
	// with a fcrystal Hz frequency.
	scif_configure_osc_crystalmode(SCIF_OSC0, 12000000);
	// Enable the OSC0
	scif_enable_osc(SCIF_OSC0, AVR32_SCIF_OSCCTRL0_STARTUP_16384_RCOSC,
			true);
	flashcdw_set_flash_waitstate_and_readmode(12000000);
	pm_set_mclk_source(PM_CLK_SRC_OSC0);

	// Initialize the AST with the internal RC oscillator
	// AST will count at the frequency of 115KHz/2
	if (!ast_init_counter(&AVR32_AST, AST_OSC_RC, 0, 0)) {
		while (1);
	}
	// Enable the AST
	ast_enable(&AVR32_AST);

	// Detect the frequency
	switch (freq_detect_start()) {
	case 8000000:
		mul = 5;
		break;
	case 16000000:
		mul = 2;
		break;
	case 12000000:
	default:
		mul = 3;
		break;
	}

	scif_pll_opt_t opt;

	// Set PLL0 VCO @ 96 MHz
	// Set PLL0 @ 48 MHz
	opt.osc = SCIF_OSC0;
	opt.lockcount = 63;
	opt.div = 0;
	opt.mul = mul;
	opt.pll_div2 = 1;
	opt.pll_wbwdisable = 0;
	opt.pll_freq = 1;

	// lockcount in main clock for the PLL wait lock
	scif_pll_setup(SCIF_PLL0, &opt);

	/* Enable PLL0 */
	scif_pll_enable(SCIF_PLL0);

	/* Wait for PLL0 locked */
	scif_wait_for_pll_locked(SCIF_PLL0);

	// Use 1 flash wait state
	flashcdw_set_wait_state(1);

	// Switch the main clock to PLL0
	pm_set_mclk_source(PM_CLK_SRC_PLL0);

	// fCPU: 48 MHz  // USBC request a CPU clock >25MHz
	// fHSB: 48 MHz
	// fPBA: 48 MHz
	// fPBB: 48 MHz
	pm_disable_clk_domain_div(PM_CLK_DOMAIN_0);	// CPU
	pm_disable_clk_domain_div(PM_CLK_DOMAIN_1);	// HSB
	pm_disable_clk_domain_div(PM_CLK_DOMAIN_2);	// PBA
	pm_disable_clk_domain_div(PM_CLK_DOMAIN_3);	// PBB

	// Use 0 flash wait state
	flashcdw_set_wait_state(1);
}


/**
 * \brief Enable the USB generic clock
 *
 * \pre The USB generic clock must be configured to 48MHz.
 */
void sysclk_auto_enable_usb(void)
{
	// Setup USB GCLK
	scif_gc_setup(AVR32_SCIF_GCLK_USBC,
			SCIF_GCCTRL_PLL0, AVR32_SCIF_GC_NO_DIV_CLOCK, 0);
	// Enable USB GCLK
	scif_gc_enable(AVR32_SCIF_GCLK_USBC);
}


/**
 * \brief Disable the USB generic clock
 */
void sysclk_auto_disable_usb(void)
{
	AVR32_SCIF.gcctrl[AVR32_SCIF_GCLK_USBC] = 0;
	scif_gc_setup(AVR32_SCIF_GCLK_USBC,
			SCIF_GCCTRL_PLL0, AVR32_SCIF_GC_NO_DIV_CLOCK, 0);
}
//! \}

/*! \name External routines required by frequency detection service
 */
//! \{

//! Callback used to reset the counter of the reference's oscillator.
void freq_detect_iface_ref_cnt_reset(void)
{
	ast_set_counter_value(&AVR32_AST, 0);
}

//! Callback used to read the counter value of the reference's oscillator.
int freq_detect_iface_ref_cnt_value(void)
{
	return ast_get_counter_value(&AVR32_AST) * 2;
}

//! Callback used to reset the counter of the target oscillator.
void freq_detect_iface_target_cnt_reset(void)
{
	Set_sys_count(0);
}

//! Callback used to read the counter value of the target oscillator.
int freq_detetc_iface_target_cnt_value(void)
{
	return Get_sys_count();
}
//! \}
