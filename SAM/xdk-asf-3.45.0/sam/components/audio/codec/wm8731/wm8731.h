/**
 * \file
 *
 * \brief WM8731 driver for SAM
 *
 * Copyright (c) 2012-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef WM8731_H_INCLUDED
#define WM8731_H_INCLUDED

#include "twi_master.h"
#include "conf_wm8731.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \defgroup sam_components_audio_codec_wm8731_group WM8731 Audio Codec
 *
 * See \ref sam_wm8731_quickstart
 *
 * \par Purpose
 *
 * The module provides useful API of WM8731 audio codec through a TWI interface.
 *
 * \section dependencies Dependencies
 * This driver depends on the following module:
 * - \ref twi_group for common TWI service.
 * @{
 */

//! Checking board configuration of the WM8731
#if !defined(TWI_WM8731)
# warning The WM8731 TWI instance has not been defined. Using default settings.
# define TWI_WM8731 0 /* TWI instance (TWI0) */
#endif
#if !defined(WM8731_SLAVE_ADDRESS)
# warning The WM8731 TWI address has not been defined. Using default settings.
# define WM8731_SLAVE_ADDRESS 0 /* TWI codec address (0x1bu) */
#endif

/* \brief WM8731 Configuration Register Setting */

/* --------WM8731_REG_LEFT_LINE_IN : (Offset: 0x00) Left Line in Control -------- */
#define WM8731_REG_LEFT_LINE_IN (0x00u)
#define WM8731_REG_LEFT_LINE_IN_LINVOL_POS 0
#define WM8731_REG_LEFT_LINE_IN_LINVOL_MSK (0x1fu << WM8731_REG_LEFT_LINE_IN_LINVOL_POS)
#define WM8731_REG_LEFT_LINE_IN_LINVOL(value) ((WM8731_REG_LEFT_LINE_IN_LINVOL_MSK & ((value) << WM8731_REG_LEFT_LINE_IN_LINVOL_POS)))
#define WM8731_REG_LEFT_LINE_IN_LINMUTE (0x1u << 7)
#define WM8731_REG_LEFT_LINE_IN_LRINBOTH (0x1u << 8)
/* --------WM8731_REG_RIGHT_LINE_IN : (Offset: 0x01) Right Line in Control -------- */
#define WM8731_REG_RIGHT_LINE_IN (0x01u)
#define WM8731_REG_RIGHT_LINE_IN_RINVOL_POS 0
#define WM8731_REG_RIGHT_LINE_IN_RINVOL_MSK (0x1fu << WM8731_REG_RIGHT_LINE_IN_RINVOL_POS)
#define WM8731_REG_RIGHT_LINE_IN_RINVOL(value) ((WM8731_REG_RIGHT_LINE_IN_RINVOL_MSK & ((value) << WM8731_REG_RIGHT_LINE_IN_RINVOL_POS)))
#define WM8731_REG_RIGHT_LINE_IN_RINMUTE (0x1u << 7)
#define WM8731_REG_RIGHT_LINE_IN_RLINBOTH (0x1u << 8)
/* --------WM8731_REG_LEFT_HEADPHONE_OUT : (Offset: 0x02) Left Headphone out Control -------- */
#define WM8731_REG_LEFT_HEADPHONE_OUT (0x02u)
#define WM8731_REG_LEFT_HEADPHONE_OUT_LHPVOL_POS 0
#define WM8731_REG_LEFT_HEADPHONE_OUT_LHPVOL_MSK (0x7fu << WM8731_REG_LEFT_HEADPHONE_OUT_LHPVOL_POS)
#define WM8731_REG_LEFT_HEADPHONE_OUT_LHPVOL(value) ((WM8731_REG_LEFT_HEADPHONE_OUT_LHPVOL_MSK & ((value) << WM8731_REG_LEFT_HEADPHONE_OUT_LHPVOL_POS)))
#define WM8731_REG_LEFT_HEADPHONE_OUT_LZCEN (0x1u << 7)
#define WM8731_REG_LEFT_HEADPHONE_OUT_LRHPBOTH (0x1u << 8)
/* --------WM8731_REG_RIGHT_HEADPHONE_OUT : (Offset: 0x03) Right Headphone out Control -------- */
#define WM8731_REG_RIGHT_HEADPHONE_OUT (0x03u)
#define WM8731_REG_RIGHT_HEADPHONE_OUT_RHPVOL_POS 0
#define WM8731_REG_RIGHT_HEADPHONE_OUT_RHPVOL_MSK (0x7fu << WM8731_REG_RIGHT_HEADPHONE_OUT_RHPVOL_POS)
#define WM8731_REG_RIGHT_HEADPHONE_OUT_RHPVOL(value) ((WM8731_REG_RIGHT_HEADPHONE_OUT_RHPVOL_MSK & ((value) << WM8731_REG_RIGHT_HEADPHONE_OUT_RHPVOL_POS)))
#define WM8731_REG_RIGHT_HEADPHONE_OUT_RZCEN (0x1u << 7)
#define WM8731_REG_RIGHT_HEADPHONE_OUT_RLHPBOTH (0x1u << 8)
/* --------WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL : (Offset: 0x04) Analogue Audio Path Control -------- */
#define WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL (0x04u)
#define WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_MICBOOST (0x1u << 0)
#define WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_MUTEMIC (0x1u << 1)
#define WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_INSEL_MIC (0x1u << 2)
#define WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_BYPASS (0x1u << 3)
#define WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_DACSEL (0x1u << 4)
#define WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_SIDETONE (0x1u << 5)
#define WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_SIDETONE_ATTENUATION_POS 6
#define WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_SIDETONE_ATTENUATION_MSK (0x3u << WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_SIDETONE_ATTENUATION_POS)
#define WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_SIDETONE_ATTENUATION(value) ((WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_SIDETONE_ATTENUATION_MSK & ((value) << WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_SIDETONE_ATTENUATION_POS)))
/* --------WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL : (Offset: 0x05) Digital Audio Path Control -------- */
#define WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL (0x05u)
#define WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL_ADCHPD (0x1u << 0)
#define WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL_DEEMP_DISABLE (0x0u << 1)
#define WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL_DEEMP_32K (0x1u << 1)
#define WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL_DEEMP_44_1K (0x2u << 1)
#define WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL_DEEMP_48K (0x3u << 1)
#define WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL_DACMU (0x1u << 3)
#define WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL_HPOR (0x1u << 4)
/* --------WM8731_REG_POWER_DOWN_CONTROL : (Offset: 0x06) Power Down Control -------- */
#define WM8731_REG_POWER_DOWN_CONTROL (0x06u)
#define WM8731_REG_POWER_DOWN_CONTROL_LINEINPD (0x1u << 0)
#define WM8731_REG_POWER_DOWN_CONTROL_MICPD (0x1u << 1)
#define WM8731_REG_POWER_DOWN_CONTROL_ADCPD (0x1u << 2)
#define WM8731_REG_POWER_DOWN_CONTROL_DACPD (0x1u << 3)
#define WM8731_REG_POWER_DOWN_CONTROL_OUTPD (0x1u << 4)
#define WM8731_REG_POWER_DOWN_CONTROL_OSCPD (0x1u << 5)
#define WM8731_REG_POWER_DOWN_CONTROL_CLKOUTPD (0x1u << 6)
#define WM8731_REG_POWER_DOWN_CONTROL_POWEROFF (0x1u << 7)
/* --------WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT : (Offset: 0x07) Digital Audio Interface Control -------- */
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT (0x07u)
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_MSB_RIGHT_JUSTIFIED (0x0u << 0)
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_MSB_LEFT_JUSTIFIED (0x1u << 0)
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_I2S (0x2u << 0)
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_DSP (0x3u << 0)
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_IWL_16_BIT (0x0u << 2)
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_IWL_20_BIT (0x1u << 2)
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_IWL_24_BIT (0x2u << 2)
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_IWL_32_BIT (0x3u << 2)
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_LRP (0x1u << 4)
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_LRSWAP (0x1u << 5)
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_MS (0x1u << 6)
#define WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_BCLKINV (0x1u << 7)
/* --------WM8731_REG_SAMPLING_CONTROL : (Offset: 0x08) Sampling Control -------- */
#define WM8731_REG_SAMPLING_CONTROL (0x08u)
#define WM8731_REG_SAMPLING_CONTROL_USB_MODE (0x1u << 0)
#define WM8731_REG_SAMPLING_CONTROL_BOSR (0x1u << 1)
#define WM8731_REG_SAMPLING_CONTROL_SR_POS 2
#define WM8731_REG_SAMPLING_CONTROL_SR_MSK (0xf << WM8731_REG_SAMPLING_CONTROL_SR_POS)
#define WM8731_REG_SAMPLING_CONTROL_SR(value) ((WM8731_REG_SAMPLING_CONTROL_SR_MSK & ((value) << WM8731_REG_SAMPLING_CONTROL_SR_POS)))
#define WM8731_REG_SAMPLING_CONTROL_CLKIDIV2 (0x1u << 6)
#define WM8731_REG_SAMPLING_CONTROL_CLKODIV2 (0x1u << 7)
/* --------WM8731_REG_ACTIVE_CONTROL : (Offset: 0x09) Active Control -------- */
#define WM8731_REG_ACTIVE_CONTROL (0x09u)
#define WM8731_REG_ACTIVE_CONTROL_ACTIVE (0x1u << 0)
/* --------WM8731_REG_RESET : (Offset: 0x09) Reset Control -------- */
#define WM8731_REG_RESET (0x0Fu)
#define WM8731_REG_RESET_VALUE_POS 0
#define WM8731_REG_RESET_VALUE_MSK (0x1ffu << WM8731_REG_RESET_VALUE_POS)
#define WM8731_REG_RESET_VALUE(value) ((WM8731_REG_RESET_VALUE_MSK & ((value) << WM8731_REG_RESET_VALUE_POS)))

void wm8731_left_line_in_volume_set(uint16_t us_value);
void wm8731_set_left_line_in_mute(uint32_t ul_flag);
void wm8731_right_line_in_volume_set(uint16_t us_value);
void wm8731_set_right_line_in_mute(uint32_t ul_flag);
void wm8731_left_headphone_volume_set(uint16_t us_value);
void wm8731_right_headphone_volume_set(uint16_t us_value);
void wm8731_set_mic_boost(uint32_t ul_flag);
void wm8731_set_mic_mute(uint32_t ul_flag);
void wm8731_adc_input_select(uint32_t ul_flag);
void wm8731_set_bypass_enable(uint32_t ul_flag);
void wm8731_dac_select(uint32_t ul_flag);
void wm8731_enable_adc_high_pass_filter(uint32_t ul_flag);
void wm8731_set_deemphasis(uint32_t ul_value);
void wm8731_set_dac_soft_mute(uint32_t ul_flag);
void wm8731_set_power_down_line_in(uint32_t ul_flag);
void wm8731_set_power_down_mic(uint32_t ul_flag);
void wm8731_set_power_down_adc(uint32_t ul_flag);
void wm8731_set_power_down_dac(uint32_t ul_flag);
void wm8731_set_power_down_output(uint32_t ul_flag);
void wm8731_set_power_down_osc(uint32_t ul_flag);
void wm8731_set_power_down_clkout(uint32_t ul_flag);
void wm8731_set_power_off(uint32_t ul_flag);
void wm8731_power_mode_all_active(void);
void wm8731_power_mode_dac(void);
void wm8731_power_mode_adc_line_in(void);
void wm8731_power_mode_adc_mic(void);
void wm8731_power_mode_standby(void);
void wm8731_set_digital_audio_interface_format(uint32_t ul_value);
void wm8731_set_digital_audio_data_bit_length(uint32_t ul_value);
void wm8731_set_dac_phase(uint32_t ul_value);
void wm8731_set_master_or_slave_mode(uint32_t ul_flag);
void wm8731_set_sampling_control(uint32_t ul_mode_flag,
		uint32_t ul_bosr, uint32_t ul_value);
void wm8731_set_core_clock_divider(uint32_t ul_flag);
void wm8731_set_output_clock_divider(uint32_t ul_flag);
void wm8731_set_active(uint32_t ul_flag);
void wm8731_reset(void);

//@}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

/**
 * \page sam_wm8731_quickstart Quick start guide for the SAM WM8731 module
 *
 * This is the quick start guide for the \ref sam_components_audio_codec_wm8731_group
 * "WM8731 Audio Codec", with step-by-step instructions on how to configure
 * and use the driver in a selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section wm8731_use_cases WM8731 use cases
 * - \ref wm8731_basic_use_case Basic use case - Configurate the WM8731 to DAC
 * mode
 *
 * \section wm8731_basic_use_case Basic use case - Configurate the WM8731 to
 * DAC mode
 * In this use case, the WM8731 module is configured to DAC mode with I2S audio
 * interface.
 *
 * \section wm8731_basic_use_case_setup Setup
 *
 * \subsection wm8731_basic_use_case_setup_prereq Prerequisites
 * -# \ref gpio_group "General Purpose I/O Management (gpio)"
 *
 * \subsection wm8731_basic_use_case_setup_code Code
 * The following function needs to be added to the user application, to
 * configurate the TWI interface.
 * 
 * \code
	static void init_twi_wm8731(void)
	{
	     twi_options_t opt;

	    opt.master_clk = sysclk_get_peripheral_hz();
	    opt.speed		= TWI_WM8731_CLK;
	    opt.chip		= WM8731_SLAVE_ADDRESS;
	    twi_master_setup(TWI_WM8731, &opt);
	}
\endcode
 *
 * \section wm8731_basic_use_case_setup_flow Workflow
 *
 * -# reset the WM8731:
 *    - \code wm8731_reset(); \endcode
 * -# Select the WM8731 DAC:
 *    - \code wm8731_dac_select(1); \endcode
 * -# Set the WM8731 to usb mode and 48K DAC:
 *    - \code wm8731_set_sampling_control(1,0,0); \endcode
 * -# Set the WM8731 audio interface to I2S mode:
 *    - \code ul_value = WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_I2S;
\endcode
 *    - \code wm8731_set_digital_audio_data_bit_length(ul_value); \endcode
 * -# Set the WM8731 audio data bit length to 16bit:
 *    - \code ul_value = WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_IWL_16_BIT;
\endcode
 *    - \code wm8731_set_digital_audio_data_bit_length(ul_value); \endcode
 * -# Disable the WM8731 DAC soft mute:
 *    - \code wm8731_set_dac_soft_mute(0); \endcode
 * -# Power up the WM8731 DAC:
 *    - \code wm8731_power_mode_dac(); \endcode
 * -# Active the WM8731:
 *    - \code wm8731_set_active(1); \endcode
 *
 */

#endif /* WM8731_H_INCLUDED */

