/**
 * \file
 *
 * \brief WM8904 driver for SAM
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#include "wm8904.h"
#include "pio.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

/*
 * \brief Write data to WM8904 Register.
 *
 * \param uc_register_address Register address to write
 * \param us_data Data to write.
 */
void wm8904_write_register(uint8_t uc_register_address, uint16_t us_data)
{
	uint8_t uc_temp_data[2];
	twihs_packet_t packet;

	uc_temp_data[0] = (us_data & 0xff00) >> 8;
	uc_temp_data[1] = us_data & 0xff;

	packet.addr[0]     = uc_register_address;
	packet.addr_length = 0x1;
	packet.buffer      = uc_temp_data;
	packet.length      = 0x2;
	packet.chip        = WM8904_SLAVE_ADDRESS;

	twihs_master_write(WM8904_TWIHS, &packet);
}

/*
 * \brief Read data from WM8904 Register.
 *
 * \param uc_register_address Register address to write
 * \retun Register value.
 */
uint16_t wm8904_read_register(uint8_t uc_register_address)
{
	uint8_t uc_temp_data[2];
	twihs_packet_t packet;
	uint16_t us_data;

	packet.addr[0]     = uc_register_address;
	packet.addr_length = 0x1;
	packet.buffer      = uc_temp_data;
	packet.length      = 0x2;
	packet.chip        = WM8904_SLAVE_ADDRESS;

	twihs_master_read(WM8904_TWIHS, &packet);
	us_data = (((uint16_t)uc_temp_data[0] << 8) & 0xff00) | uc_temp_data[1];

	return us_data;
}

/*
 * \brief Initialize TWIHS connect to WM8904.
 *
 * \retun TWIHS_SUCCESS if initialization is complete, error code otherwise.
 */
uint32_t wm8904_twi_init(void)
{
	pio_configure_pin(WM8904_TK_PIO, WM8904_TK_FLAGS);
	pio_configure_pin(WM8904_TF_PIO, WM8904_TF_FLAGS);
	pio_configure_pin(WM8904_TD_PIO, WM8904_TD_FLAGS);
	pio_configure_pin(WM8904_RK_PIO, WM8904_RK_FLAGS);
	pio_configure_pin(WM8904_RF_PIO, WM8904_RF_FLAGS);
	pio_configure_pin(WM8904_RD_PIO, WM8904_RD_FLAGS);
	pio_configure_pin(WM8904_PCK2_PIO, WM8904_PCK2_FLAGS);

	twihs_options_t opt;
	opt.master_clk = sysclk_get_cpu_hz();
	opt.speed = WM8904_TWIHS_CLK;
	return twihs_master_setup(WM8904_TWIHS, &opt);
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond

