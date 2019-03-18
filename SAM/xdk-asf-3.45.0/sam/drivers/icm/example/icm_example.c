/**
 * \file
 *
 * \brief ICM example for SAM.
 *
 * Copyright (c) 2013-2018 Microchip Technology Inc. and its subsidiaries.
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

/**
 * \mainpage
 * \section intro Introduction
 * This example demonstrates how to use ICM driver to check integrity of internal SRAM.
 *
 * \section files Main Files
 *  - icm.c ICM driver implementation
 *  - icm.h ICM driver definitions
 *  - icm_example.c example application
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench
 * for Atmel. Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * All SAM devices with a ICM can be used.
 *
 * \section exampledescription Description of the example
 * After an initialization phase, the ICM will compute memory region0 and region1 hash value
 * and write back to hash area. Next set the region monitoring mode to compare mode and
 * modify memory region0 and region1 value, then the mismatch interrupt will be generated.
 *
 * \section configinfo Configuration Information
 * - PC terminal settings:
 *   - 115200 bps,
 *   - 8 data bits,
 *   - no parity bit,
 *   - 1 stop bit,
 *   - no flow control.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 * Support and FAQ: https://www.microchip.com/support/
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>

/* Region descriptor in main list */
COMPILER_ALIGNED(64)
struct icm_region_descriptor_main_list reg_descriptor[2];

COMPILER_ALIGNED(4)
/* Region descriptor in secondary list */
struct icm_region_descriptor_sec_list reg_descriptor_sec;

/* Hash area */
COMPILER_ALIGNED(128)
uint32_t output_sha[0x20];

/* Memory region0 area, string "abc" */
volatile uint32_t message_sha_0[16] = {
	0x80636261,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x18000000
};

/* Memory region1 main list area, string "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq" */
volatile uint32_t message_sha_1_main[16] = {
	0x64636261,
	0x65646362,
	0x66656463,
	0x67666564,
	0x68676665,
	0x69686766,
	0x6a696867,
	0x6b6a6968,
	0x6c6b6a69,
	0x6d6c6b6a,
	0x6e6d6c6b,
	0x6f6e6d6c,
	0x706f6e6d,
	0x71706f6e,
	0x00000080,
	0x00000000
};

/* Memory region1 secondary list area */
volatile uint32_t message_sha_1_sec[16] = {
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0xc0010000
};

/**
 *  Configure serial console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
#endif
		.paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
#endif
	};

	/* Configure console. */
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

static void reg_dig_mismatch_handler(uint8_t reg_num)
{
	if(reg_num == ICM_REGION_NUM_0) {
		printf( " Memory region0 is modified \n\r");
	} else if(reg_num == ICM_REGION_NUM_1) {
		printf( " Memory region1 is modified \n\r");
	}
}

/**
 * \brief Application entry point for ICM example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* ICM configuration */
	struct icm_config icm_cfg;

	/* Initialize the SAM system */
	sysclk_init();
	board_init();
	sleepmgr_init();

	/* Initialize the console uart */
	configure_console();

	/* Output example information */
	printf("-- ICM Example --\r\n");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* ICM initialization */
	icm_cfg.is_write_back= false;
	icm_cfg.is_dis_end_mon = false;
	icm_cfg.is_sec_list_branch = false;
	icm_cfg.bbc = 0;
	icm_cfg.is_auto_mode = false;
	icm_cfg.is_dual_buf = false;
	icm_cfg.is_user_hash = false;
	icm_cfg.ualgo = ICM_SHA_1;
	icm_cfg.hash_area_val = 0;
	icm_cfg.des_area_val = 0;
	icm_init(ICM, &icm_cfg);

	/* Set region0 descriptor */
	reg_descriptor[0].start_addr = (uint32_t)message_sha_0;
	reg_descriptor[0].cfg.is_compare_mode = false;
	reg_descriptor[0].cfg.is_wrap = false;
	reg_descriptor[0].cfg.is_end_mon = false;
	reg_descriptor[0].cfg.reg_hash_int_en = false;
	reg_descriptor[0].cfg.dig_mis_int_en = false;
	reg_descriptor[0].cfg.bus_err_int_en = false;
	reg_descriptor[0].cfg.wrap_con_int_en = false;
	reg_descriptor[0].cfg.ebit_con_int_en = false;
	reg_descriptor[0].cfg.status_upt_con_int_en = false;
	reg_descriptor[0].cfg.is_pro_dly = false;
	reg_descriptor[0].cfg.mem_reg_val = 0;
	reg_descriptor[0].cfg.algo = ICM_SHA_1;
	reg_descriptor[0].tran_size = 0;
	reg_descriptor[0].next_addr = 0;

	/* Set region1 descriptor in main list */
	reg_descriptor[1].start_addr = (uint32_t)message_sha_1_main;
	reg_descriptor[1].cfg.is_compare_mode = false;
	reg_descriptor[1].cfg.is_wrap = false;
	reg_descriptor[1].cfg.is_end_mon = true;
	reg_descriptor[1].cfg.reg_hash_int_en = false;
	reg_descriptor[1].cfg.dig_mis_int_en = false;
	reg_descriptor[1].cfg.bus_err_int_en = false;
	reg_descriptor[1].cfg.wrap_con_int_en = false;
	reg_descriptor[1].cfg.ebit_con_int_en = false;
	reg_descriptor[1].cfg.status_upt_con_int_en = false;
	reg_descriptor[1].cfg.is_pro_dly = false;
	reg_descriptor[1].cfg.mem_reg_val = 0;
	reg_descriptor[1].cfg.algo = ICM_SHA_1;
	reg_descriptor[1].tran_size = 0;
	reg_descriptor[1].next_addr = &reg_descriptor_sec;

	/* Set region1 descriptor in secondary list */
	reg_descriptor_sec.start_addr = (uint32_t)message_sha_1_sec;
	reg_descriptor_sec.tran_size = 0;
	reg_descriptor_sec.next_addr = 0;

	/* Set region descriptor start address */
	icm_set_reg_des_addr(ICM, (uint32_t)&reg_descriptor[0]);

	/* Set hash area start address */
	icm_set_hash_area_addr(ICM, (uint32_t)output_sha);

	/* Enable ICM */
	icm_enable(ICM);

	delay_ms(200);

	/* Set region monitoring mode to compare mode */
	reg_descriptor[0].cfg.is_compare_mode = true;
	reg_descriptor[1].cfg.is_compare_mode = true;

	/* Set callback function for digest mismatch interrupt handler */
	icm_set_callback(ICM, reg_dig_mismatch_handler, ICM_REGION_NUM_0,
			ICM_INTERRUPT_RDM, 1);
	icm_set_callback(ICM, reg_dig_mismatch_handler, ICM_REGION_NUM_1,
			ICM_INTERRUPT_RDM, 1);

	/* Modify memory region value */
	message_sha_0[0] = 0x12345678;
	message_sha_1_sec[0] = 0x12345678;

	/* Enable ICM */
	icm_enable(ICM);

	while (1) {
	}
}
