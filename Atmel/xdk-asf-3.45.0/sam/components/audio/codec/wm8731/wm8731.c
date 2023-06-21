/**
 * \file
 *
 * \brief WM8731 driver for SAM
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

#include "wm8731.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/* Value in register */
uint16_t g_us_wm8731_reg_left_line_in_value = 0x0097;
uint16_t g_us_wm8731_reg_right_line_in_value = 0x0097;
uint16_t g_us_wm8731_reg_left_headphone_out_value = 0x0079;
uint16_t g_us_wm8731_reg_right_headphone_out_value = 0x0079;
uint16_t g_us_wm8731_reg_analogue_audio_path_control_value = 0x000A;
uint16_t g_us_wm8731_reg_digital_audio_path_control_value = 0x0008;
uint16_t g_us_wm8731_reg_power_down_control_value = 0x009F;
uint16_t g_us_wm8731_reg_digital_audio_interface_format_value = 0x000A;
uint16_t g_us_wm8731_reg_sampling_control_value = 0x0000;
uint16_t g_us_wm8731_reg_active_control_value = 0x0000;

/*
 * Write data to WM8731 Register.
 *
 * \param ul_register_address Register address to write.
 * \param us_data Data to write.
 */
static void wm8731_write_register(uint32_t ul_register_address,
		uint16_t us_data)
{
	uint8_t uc_temp_data[2];
	uint16_t us_temp;
	twi_packet_t packet;

	us_temp = ((ul_register_address & 0x7f) << 9) | (us_data & 0x1ff);

	uc_temp_data[0] = (us_temp & 0xff00) >> 8;
	uc_temp_data[1] = us_temp & 0xff;

	packet.addr_length = 0x0;
	packet.buffer      = uc_temp_data;
	packet.length      = 2;
	packet.chip        = WM8731_SLAVE_ADDRESS;

	twi_master_write(TWI_WM8731, &packet);
}

/*
 * Set WM8731 left line in volume value.
 *
 * \param us_value Line in volume value, default is 0x17.
 */
void wm8731_left_line_in_volume_set(uint16_t us_value)
{
	g_us_wm8731_reg_left_line_in_value &=
			~WM8731_REG_LEFT_LINE_IN_LINVOL_MSK;

	g_us_wm8731_reg_left_line_in_value |=
			WM8731_REG_LEFT_LINE_IN_LINVOL(us_value);

	wm8731_write_register(WM8731_REG_LEFT_LINE_IN,
			g_us_wm8731_reg_left_line_in_value);
}

/*
 * Set WM8731 left line in mute.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_left_line_in_mute(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_left_line_in_value |=
				WM8731_REG_LEFT_LINE_IN_LINMUTE;
	} else {
		g_us_wm8731_reg_left_line_in_value &=
				~WM8731_REG_LEFT_LINE_IN_LINMUTE;
	}

	wm8731_write_register(WM8731_REG_LEFT_LINE_IN,
			g_us_wm8731_reg_left_line_in_value);
}

/*
 * Set WM8731 right line in volume value.
 *
 * \param us_value Line in volume value, default is 0x17.
 */
void wm8731_right_line_in_volume_set(uint16_t us_value)
{
	g_us_wm8731_reg_right_line_in_value &=
			~WM8731_REG_RIGHT_LINE_IN_RINVOL_MSK;

	g_us_wm8731_reg_right_line_in_value |=
			WM8731_REG_RIGHT_LINE_IN_RINVOL(us_value);

	wm8731_write_register(WM8731_REG_RIGHT_LINE_IN,
			g_us_wm8731_reg_right_line_in_value);
}

/*
 * Set WM8731 right line in mute.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_right_line_in_mute(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_right_line_in_value |=
				WM8731_REG_RIGHT_LINE_IN_RINMUTE;
	} else {
		g_us_wm8731_reg_right_line_in_value &=
				~WM8731_REG_RIGHT_LINE_IN_RINMUTE;
	}

	wm8731_write_register(WM8731_REG_RIGHT_LINE_IN,
			g_us_wm8731_reg_right_line_in_value);
}

/*
 * Set WM8731 left headphone volume value.
 *
 * \param us_value Headphone volume value, default is 0x79.
 */
void wm8731_left_headphone_volume_set(uint16_t us_value)
{
	g_us_wm8731_reg_left_headphone_out_value &=
			~WM8731_REG_LEFT_HEADPHONE_OUT_LHPVOL_MSK;

	g_us_wm8731_reg_left_headphone_out_value |=
			WM8731_REG_LEFT_HEADPHONE_OUT_LHPVOL(us_value);

	wm8731_write_register(WM8731_REG_LEFT_HEADPHONE_OUT,
			g_us_wm8731_reg_left_headphone_out_value);
}

/*
 * Set WM8731 right headphone volume value.
 *
 * \param us_value Headphone volume value, default is 0x79.
 */
void wm8731_right_headphone_volume_set(uint16_t us_value)
{
	g_us_wm8731_reg_right_headphone_out_value &=
			~WM8731_REG_RIGHT_HEADPHONE_OUT_RHPVOL_MSK;

	g_us_wm8731_reg_right_headphone_out_value |=
			WM8731_REG_RIGHT_HEADPHONE_OUT_RHPVOL(us_value);

	wm8731_write_register(WM8731_REG_RIGHT_HEADPHONE_OUT,
			g_us_wm8731_reg_right_headphone_out_value);
}

/*
 * Set WM8731 MIC boost.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_mic_boost(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_analogue_audio_path_control_value |=
				WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_MICBOOST;
	} else {
		g_us_wm8731_reg_analogue_audio_path_control_value &=
				~WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_MICBOOST;
	}

	wm8731_write_register(WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL,
			g_us_wm8731_reg_analogue_audio_path_control_value);
}

/*
 * Set WM8731 MIC mute.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_mic_mute(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_analogue_audio_path_control_value |=
				WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_MUTEMIC;
	} else {
		g_us_wm8731_reg_analogue_audio_path_control_value &=
				~WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_MUTEMIC;
	}

	wm8731_write_register(WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL,
			g_us_wm8731_reg_analogue_audio_path_control_value);
}

/*
 * Select WM8731 ADC input source.
 *
 * \param ul_flag 0 for line in, 1 for MIC.
 */
void wm8731_adc_input_select(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_analogue_audio_path_control_value |=
				WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_INSEL_MIC;
	} else {
		g_us_wm8731_reg_analogue_audio_path_control_value &=
				~WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_INSEL_MIC;
	}

	wm8731_write_register(WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL,
			g_us_wm8731_reg_analogue_audio_path_control_value);
}

/*
 * Set WM8731 bypass enable.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_bypass_enable(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_analogue_audio_path_control_value |=
				WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_BYPASS;
	} else {
		g_us_wm8731_reg_analogue_audio_path_control_value &=
				~WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_BYPASS;
	}

	wm8731_write_register(WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL,
			g_us_wm8731_reg_analogue_audio_path_control_value);
}

/*
 * Select WM8731 DAC mode.
 *
 * \param ul_flag 1 for select, 0 for not.
 */
void wm8731_dac_select(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_analogue_audio_path_control_value |=
				WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_DACSEL;
	} else {
		g_us_wm8731_reg_analogue_audio_path_control_value &=
				~WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL_DACSEL;
	}

	wm8731_write_register(WM8731_REG_ANALOGUE_AUDIO_PATH_CONTROL,
			g_us_wm8731_reg_analogue_audio_path_control_value);
}

/*
 * Enable WM8731 ADC high pass filter.
 *
 * \param ul_flag 1 for enable, 0 for not.
 */
void wm8731_enable_adc_high_pass_filter(uint32_t ul_flag)
{
	if (!ul_flag) {
		g_us_wm8731_reg_analogue_audio_path_control_value |=
				WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL_ADCHPD;
	} else {
		g_us_wm8731_reg_analogue_audio_path_control_value &=
				~WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL_ADCHPD;
	}

	wm8731_write_register(WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL,
			g_us_wm8731_reg_digital_audio_path_control_value);
}

/*
 * Set WM8731 de-emphasis.
 *
 * \param ul_value Use the definition related with de-emphasis in head file.
 */
void wm8731_set_deemphasis(uint32_t ul_value)
{
	g_us_wm8731_reg_digital_audio_path_control_value &=
			~WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL_DEEMP_48K;

	g_us_wm8731_reg_digital_audio_path_control_value |= ul_value;

	wm8731_write_register(WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL,
			g_us_wm8731_reg_digital_audio_path_control_value);
}

/*
 * Set WM8731 DAC soft mute control.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_dac_soft_mute(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_digital_audio_path_control_value |=
				WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL_DACMU;
	} else {
		g_us_wm8731_reg_digital_audio_path_control_value &=
				~WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL_DACMU;
	}

	wm8731_write_register(WM8731_REG_DIGITAL_AUDIO_PATH_CONTROL,
			g_us_wm8731_reg_digital_audio_path_control_value);
}

/*
 * Set WM8731 line in power down.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_power_down_line_in(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_power_down_control_value |=
				WM8731_REG_POWER_DOWN_CONTROL_LINEINPD;
	} else {
		g_us_wm8731_reg_power_down_control_value &=
				~WM8731_REG_POWER_DOWN_CONTROL_LINEINPD;
	}

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 MIC power down.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_power_down_mic(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_power_down_control_value |=
				WM8731_REG_POWER_DOWN_CONTROL_MICPD;
	} else {
		g_us_wm8731_reg_power_down_control_value &=
				~WM8731_REG_POWER_DOWN_CONTROL_MICPD;
	}

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 ADC power down.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_power_down_adc(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_power_down_control_value |=
				WM8731_REG_POWER_DOWN_CONTROL_ADCPD;
	} else {
		g_us_wm8731_reg_power_down_control_value &=
				~WM8731_REG_POWER_DOWN_CONTROL_ADCPD;
	}

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 DAC power down.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_power_down_dac(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_power_down_control_value |=
				WM8731_REG_POWER_DOWN_CONTROL_DACPD;
	} else {
		g_us_wm8731_reg_power_down_control_value &=
				~WM8731_REG_POWER_DOWN_CONTROL_DACPD;
	}

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 output power down.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_power_down_output(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_power_down_control_value |=
				WM8731_REG_POWER_DOWN_CONTROL_OUTPD;
	} else {
		g_us_wm8731_reg_power_down_control_value &=
				~WM8731_REG_POWER_DOWN_CONTROL_OUTPD;
	}

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 OSC power down.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_power_down_osc(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_power_down_control_value |=
				WM8731_REG_POWER_DOWN_CONTROL_OSCPD;
	} else {
		g_us_wm8731_reg_power_down_control_value &=
				~WM8731_REG_POWER_DOWN_CONTROL_OSCPD;
	}

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 clock out power down.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_power_down_clkout(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_power_down_control_value |=
				WM8731_REG_POWER_DOWN_CONTROL_CLKOUTPD;
	} else {
		g_us_wm8731_reg_power_down_control_value &=
				~WM8731_REG_POWER_DOWN_CONTROL_CLKOUTPD;
	}

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 power off.
 *
 * \param ul_flag 1 for enable, 0 for disable.
 */
void wm8731_set_power_off(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_power_down_control_value |=
				WM8731_REG_POWER_DOWN_CONTROL_POWEROFF;
	} else {
		g_us_wm8731_reg_power_down_control_value &=
				~WM8731_REG_POWER_DOWN_CONTROL_POWEROFF;
	}

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 power mode to all active.
 */
void wm8731_power_mode_all_active(void)
{
	g_us_wm8731_reg_power_down_control_value = 0;

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 power mode to play back only.
 */
void wm8731_power_mode_dac(void)
{
	g_us_wm8731_reg_power_down_control_value = 0x07;

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 power mode to line in record only.
 */
void wm8731_power_mode_adc_line_in(void)
{
	g_us_wm8731_reg_power_down_control_value = 0x1A;

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 power mode to MIC record only.
 */
void wm8731_power_mode_adc_mic(void)
{
	g_us_wm8731_reg_power_down_control_value = 0x19;

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 power mode to standby.
 */
void wm8731_power_mode_standby(void)
{
	g_us_wm8731_reg_power_down_control_value = 0x7F;

	wm8731_write_register(WM8731_REG_POWER_DOWN_CONTROL,
			g_us_wm8731_reg_power_down_control_value);
}

/*
 * Set WM8731 digital audio interface format.
 *
 * \param ul_value Use the definition related with audio data format
 * in head file.
 */
void wm8731_set_digital_audio_interface_format(uint32_t ul_value)
{
	g_us_wm8731_reg_digital_audio_interface_format_value &=
			~WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_DSP;

	g_us_wm8731_reg_digital_audio_interface_format_value |= ul_value;
	/* digital audio path control setting */
	wm8731_write_register(WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT,
			g_us_wm8731_reg_digital_audio_interface_format_value);
}

/*
 * Set WM8731 digital audio data bit length.
 *
 * \param ul_value Use the definition related with audio data bit length
 * in head file.
 */
void wm8731_set_digital_audio_data_bit_length(uint32_t ul_value)
{
	g_us_wm8731_reg_digital_audio_interface_format_value &=
			~WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_IWL_32_BIT;

	g_us_wm8731_reg_digital_audio_interface_format_value |= ul_value;
	/* digital audio path control setting */
	wm8731_write_register(WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT,
			g_us_wm8731_reg_digital_audio_interface_format_value);
}

/*
 * Set WM8731 DAC phase.
 *
 * \param ul_value 1 or 0, reference the WM8731 spec for detail.
 */
void wm8731_set_dac_phase(uint32_t ul_value)
{
	if (ul_value) {
		g_us_wm8731_reg_digital_audio_interface_format_value |=
				WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_LRP;
	} else {
		g_us_wm8731_reg_digital_audio_interface_format_value &=
				~WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_LRP;
	}

	wm8731_write_register(WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT,
			g_us_wm8731_reg_digital_audio_interface_format_value);
}

/*
 * Set WM8731 master/slave mode.
 *
 * \param ul_flag 1 for master, 0 for slave.
 */
void wm8731_set_master_or_slave_mode(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_digital_audio_interface_format_value |=
				WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_MS;
	} else {
		g_us_wm8731_reg_digital_audio_interface_format_value &=
				~WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT_MS;
	}

	wm8731_write_register(WM8731_REG_DIGITAL_AUDIO_INTERFACE_FORMAT,
			g_us_wm8731_reg_digital_audio_interface_format_value);
}

/*
 * Set WM8731 sampling rates. Be careful about the clock and reference the
 * tables in datasheet to set all the parameters.
 *
 * \param ul_mode_flag 1 for usb, 0 for normal.
 * \param ul_bosr value for bosr bit.
 * \param ul_value ADC/DAC sample rate control value.
 */
void wm8731_set_sampling_control(uint32_t ul_mode_flag,
		uint32_t ul_bosr, uint32_t ul_value)
{
	if (ul_mode_flag) {
		g_us_wm8731_reg_sampling_control_value |=
				WM8731_REG_SAMPLING_CONTROL_USB_MODE;
	} else {
		g_us_wm8731_reg_sampling_control_value &=
				~WM8731_REG_SAMPLING_CONTROL_USB_MODE;
	}

	if (ul_bosr) {
		g_us_wm8731_reg_sampling_control_value |=
				WM8731_REG_SAMPLING_CONTROL_BOSR;
	} else {
		g_us_wm8731_reg_sampling_control_value &=
				~WM8731_REG_SAMPLING_CONTROL_BOSR;
	}

	g_us_wm8731_reg_sampling_control_value &=
			~WM8731_REG_SAMPLING_CONTROL_SR_MSK;

	g_us_wm8731_reg_sampling_control_value |=
			WM8731_REG_SAMPLING_CONTROL_SR(ul_value);

	wm8731_write_register(WM8731_REG_SAMPLING_CONTROL,
			g_us_wm8731_reg_sampling_control_value);
}

/*
 * Set WM8731 core clock divider.
 *
 * \param ul_flag 1 for divider to MCLK/2, 0 for MCLK.
 */
void wm8731_set_core_clock_divider(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_sampling_control_value |=
				WM8731_REG_SAMPLING_CONTROL_CLKIDIV2;
	} else {
		g_us_wm8731_reg_sampling_control_value &=
				~WM8731_REG_SAMPLING_CONTROL_CLKIDIV2;
	}

	wm8731_write_register(WM8731_REG_SAMPLING_CONTROL,
			g_us_wm8731_reg_sampling_control_value);
}

/*
 * Set WM8731 output clock divider.
 *
 * \param ul_flag 1 for core clock divided by 2, 0 for core clock.
 */
void wm8731_set_output_clock_divider(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_sampling_control_value |=
				WM8731_REG_SAMPLING_CONTROL_CLKODIV2;
	} else {
		g_us_wm8731_reg_sampling_control_value &=
				~WM8731_REG_SAMPLING_CONTROL_CLKODIV2;
	}

	wm8731_write_register(WM8731_REG_SAMPLING_CONTROL,
			g_us_wm8731_reg_sampling_control_value);
}

/*
 * Set WM8731active mode.
 *
 * \param ul_flag 1 for active, 0 for inactive.
 */
void wm8731_set_active(uint32_t ul_flag)
{
	if (ul_flag) {
		g_us_wm8731_reg_active_control_value |=
				WM8731_REG_ACTIVE_CONTROL_ACTIVE;
	} else {
		g_us_wm8731_reg_active_control_value &=
				~WM8731_REG_ACTIVE_CONTROL_ACTIVE;
	}

	wm8731_write_register(WM8731_REG_ACTIVE_CONTROL,
			g_us_wm8731_reg_active_control_value);
}

/*
 * Reset WM8731.
 */
void wm8731_reset(void)
{
	wm8731_write_register(WM8731_REG_RESET, WM8731_REG_RESET_VALUE(0));
}


/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

