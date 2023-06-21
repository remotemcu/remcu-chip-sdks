/**
 * \file
 *
 * \brief SAM Non Volatile Memory Driver Quick Start
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
#include <asf.h>

void configure_nvm(void);

//! [setup]
void configure_nvm(void)
{
//! [setup_1]
	struct nvm_config config_nvm;
//! [setup_1]

//! [setup_2]
	nvm_get_config_defaults(&config_nvm);
//! [setup_2]

//! [setup_3]
	config_nvm.manual_page_write = false;
//! [setup_3]

//! [setup_4]
	nvm_set_config(&config_nvm);
//! [setup_4]
}
//! [setup]

int main(void)
{
	//! [setup_init]
	configure_nvm();
	//! [setup_init]

//! [main]
	//! [main_1]
	uint8_t page_buffer[NVMCTRL_PAGE_SIZE];
	//! [main_1]

	//! [main_2]
	for (uint32_t i = 0; i < NVMCTRL_PAGE_SIZE; i++) {
		page_buffer[i] = i;
	}
	//! [main_2]

	//! [main_3]
	enum status_code error_code;
	//! [main_3]

	//! [main_4]
	do
	{
		error_code = nvm_erase_row(
				100 * NVMCTRL_ROW_PAGES * NVMCTRL_PAGE_SIZE);
	} while (error_code == STATUS_BUSY);
	//! [main_4]

	//! [main_5]
	do
	{
		error_code = nvm_write_buffer(
				100 * NVMCTRL_ROW_PAGES * NVMCTRL_PAGE_SIZE,
				page_buffer, NVMCTRL_PAGE_SIZE);
	} while (error_code == STATUS_BUSY);
	//! [main_5]

	//! [main_6]
	do
	{
		error_code = nvm_read_buffer(
				100 * NVMCTRL_ROW_PAGES * NVMCTRL_PAGE_SIZE,
				page_buffer, NVMCTRL_PAGE_SIZE);
	} while (error_code == STATUS_BUSY);
	//! [main_6]

//! [main]

	while (true) {
		/* Do nothing */
	}
}

