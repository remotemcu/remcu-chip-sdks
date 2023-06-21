/**
 * \file
 *
 * \brief SAM CRC32 Driver Quick Start
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>

COMPILER_ALIGNED(4)
static const uint32_t crc_data[10] = {
	0x00000000, 0x11111111, 0x22222222, 0x33333333, 0x44444444,
	0x55555555, 0x66666666, 0x77777777, 0x88888888, 0x99999999
};
const uint32_t expected_crc = 0xf8ee400b;
static 	uint32_t crc_result;

int main(void)
{
	enum status_code status;

	system_init();
	dsu_crc32_init();

	crc_result = 0xFFFFFFFF;
	status = dsu_crc32_cal((const uint32_t)crc_data,sizeof(crc_data),&crc_result);
	if (status != STATUS_OK) {
		while (1);
	}

	crc_result = ~crc_result;

	if (crc_result != expected_crc) {
		while (1);
	}

	while (1) {
	}
}
