/**
 *
 * \file
 *
 * \brief SAM SLCD Quick Start.
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

#include <asf.h>

//! [slcd_var]
struct dma_resource example_resource_abm;
struct dma_resource example_resource_acm;
COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor_acm ;
COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor_abm;
COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor_abm1;
COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor_abm2;
COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor_abm3;

struct usart_module usart_instance;
//! [slcd_var]

//! [slcd_data]
/*Character map 0-9,A-Z*/
const uint32_t character_map[] = {
	0x2e74,0x440,0x23c4,0x25c4,0x5e0,0x25a4,0x27a4,0x444,0x27e4,0x25e4, /*0-9*/
	0x7e4,0xa545,0x2224,0xa445,0x23a4,0x3a4,0x2724, /*A-G*/
	0x7e0,0xa005,0x2640,0x12b0,0x2220,0x678,0x1668, /*H-N*/
	0x2664,0x3e4,0x3664,0x13e4,0x25a4,0x8005,/*O-T*/
	0x2660,0xa30,0x1e60,0x1818,0x8018,0x2814/*U-Z*/
};

/* HELLO ATMEL map */
uint32_t display_array[11]={0x7e0,0x23a4,0x2220,0x2220,0x2664,0,
							0x7e4,0x8005,0x678,0x23a4,0x2220};
#define DISPLAY_ARRAY_SIZE (sizeof(display_array)/sizeof(uint32_t))

/*ICON COM/SEG map */
#define C42412A_ICON_USB            1, 1
#define C42412A_ICON_BAT            0, 0
#define C42412A_ICON_ATMEL          0, 1

/* Automated Bit Mapping
 Format: [00,offset,data mask,data]
 data:[7-0]
 data mask:[15-8]
 offset:[21-16]
*/
const uint32_t abm_matrix_string0[] = {
	0x00002f10,0x00012211,0x00022211, /* COM0  */
	0x00060f00,0x00070000,0x00080000, /* COM1  */
	0x000c0f80,0x000d0088,0x000e0088, /* COM2 */
	0x00124f10,0x00134411,0x00144411  /* COM3 */
 };

const uint32_t abm_matrix_string1[] = {
	0x00002f10,0x00012211,0x00022211, /* COM0  */
	0x00060f80,0x00070088,0x00080088, /* COM1  */
	0x000c0f90,0x000d0099,0x000e0099, /* COM2  */
	0x00124f10,0x00134411,0x00144411  /* COM3  */
 };

const uint32_t abm_matrix_string2[] = {
	0x00002f90,0x00012299,0x00022299, /* COM0  */
	0x00060f10,0x00070011,0x00080011, /* COM1  */
	0x000c0f80,0x000d0088,0x000e0088, /* COM2  */
	0x00124f10,0x00134411,0x00144411  /* COM3  */
 };

const uint32_t abm_matrix_string3[] = {
	0x00002f10,0x00012211,0x00022211, /* COM0  */
	0x00060f00,0x00070000,0x00080000, /* COM1  */
	0x000c0f00,0x000d0000,0x000e0000, /* COM2  */
	0x00124f80,0x00134488,0x00144488  /* COM3  */
 };

#define ABM_MATRIX_SIZE (sizeof(abm_matrix_string0)/sizeof(uint32_t))
//! [slcd_data]

//! [setup]
/**
 *  Configure serial console.
 */
static void configure_console(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate    = 38400;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	stdio_serial_init(&usart_instance, EDBG_CDC_MODULE, &config_usart);
	usart_enable(&usart_instance);
}
/**
 *  Configure automated character mapping with DMA.
 */
static void configure_dma_acm(void)
{
	struct dma_resource_config acm_config;

	dma_get_config_defaults(&acm_config);

	acm_config.peripheral_trigger = SLCD_DMAC_ID_ACMDRDY;
	acm_config.trigger_action = DMA_TRIGGER_ACTION_BEAT;

	dma_allocate(&example_resource_acm, &acm_config);

	struct dma_descriptor_config acm_descriptor_config;

	dma_descriptor_get_config_defaults(&acm_descriptor_config);

	acm_descriptor_config.beat_size = DMA_BEAT_SIZE_WORD;
	acm_descriptor_config.src_increment_enable = true;
	acm_descriptor_config.block_transfer_count = DISPLAY_ARRAY_SIZE;
	acm_descriptor_config.step_selection = DMA_STEPSEL_SRC;
	acm_descriptor_config.dst_increment_enable = false;
	acm_descriptor_config.source_address = (uint32_t)display_array
											+ sizeof(display_array);
	acm_descriptor_config.destination_address = (uint32_t)&SLCD->CMDATA.reg;
    acm_descriptor_config.next_descriptor_address =  (uint32_t)&example_descriptor_acm;

	dma_descriptor_create(&example_descriptor_acm, &acm_descriptor_config);

	dma_add_descriptor(&example_resource_acm, &example_descriptor_acm);
	dma_start_transfer_job(&example_resource_acm);
}

/**
 *  Configure automated bit mapping with DMA.
 */
static void configure_dma_abm(void)
{

	struct dma_resource_config abm_config;
	dma_get_config_defaults(&abm_config);
	abm_config.peripheral_trigger = SLCD_DMAC_ID_ABMDRDY;
	abm_config.trigger_action = DMA_TRIGGER_ACTION_BEAT;

	dma_allocate(&example_resource_abm, &abm_config);

	struct dma_descriptor_config abm_descriptor_config;
	dma_descriptor_get_config_defaults(&abm_descriptor_config);

	abm_descriptor_config.beat_size = DMA_BEAT_SIZE_WORD;
	abm_descriptor_config.src_increment_enable = true;
	abm_descriptor_config.step_selection = DMA_STEPSEL_SRC;
	abm_descriptor_config.dst_increment_enable = false;
	abm_descriptor_config.block_transfer_count = ABM_MATRIX_SIZE;
	abm_descriptor_config.source_address = (uint32_t)abm_matrix_string0
											+ sizeof(abm_matrix_string0);
	abm_descriptor_config.destination_address = (uint32_t)&SLCD->ISDATA.reg;
	abm_descriptor_config.next_descriptor_address =  (uint32_t)&example_descriptor_abm1;

	dma_descriptor_create(&example_descriptor_abm, &abm_descriptor_config);

	abm_descriptor_config.source_address = (uint32_t)abm_matrix_string1
											+ sizeof(abm_matrix_string1);
	abm_descriptor_config.next_descriptor_address =  (uint32_t)&example_descriptor_abm2;
	dma_descriptor_create(&example_descriptor_abm1, &abm_descriptor_config);

	abm_descriptor_config.source_address = (uint32_t)abm_matrix_string2
											+ sizeof(abm_matrix_string2);
	abm_descriptor_config.next_descriptor_address =  (uint32_t)&example_descriptor_abm3;
	dma_descriptor_create(&example_descriptor_abm2, &abm_descriptor_config);

	abm_descriptor_config.source_address = (uint32_t)abm_matrix_string3
											+ sizeof(abm_matrix_string3);
	abm_descriptor_config.next_descriptor_address =  (uint32_t)&example_descriptor_abm;
	dma_descriptor_create(&example_descriptor_abm3, &abm_descriptor_config);

	dma_add_descriptor(&example_resource_abm, &example_descriptor_abm);
	dma_start_transfer_job(&example_resource_abm);
}
//! [setup]

int main(void)
{
//! [setup_init]

	struct slcd_config config;
	system_init();
	configure_console();
	delay_init();

	/* Turn on the backlight. */
	port_pin_set_output_level(SLCD_BACLKLIGHT,true);

	printf("SLCD example starts\r\n");
//! [setup_config]
	slcd_get_config_defaults(&config);
	slcd_init(&config);
	slcd_set_contrast(0x8);
//! [setup_config]
//! [slcd_dma_config]
	configure_dma_acm();
	configure_dma_abm();
//! [slcd_dma_config]

//! [module_enable]
	slcd_enable();
//! [module_enable]

//! [setup_init]

//! [use_cases]
//! [use_cases_1]
	/* 1. Display all*/
	slcd_set_display_memory();
	delay_s(1);
	slcd_clear_display_memory();
//! [use_cases_1]

//! [use_cases_2]
	/* 2. Display icon*/
	slcd_set_pixel(C42412A_ICON_USB);
	slcd_set_pixel(C42412A_ICON_BAT);
	slcd_set_pixel(C42412A_ICON_ATMEL);
	delay_s(1);
//! [use_cases_2]

//! [use_cases_3]
	/* 3. Character map*/
	slcd_character_map_set(SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT,3);
	for(uint32_t i = 0 ; i < 5 ; i++) {
		slcd_character_write_data(0,4+i*4,character_map[10+i],0xFF4002);
	}
	delay_s(2);
//! [use_cases_3]

//! [use_cases_4]
	/* 4. Blinking*/
	slcd_disable();
	struct slcd_blink_config blink_config;
	slcd_blink_get_config_defaults(&blink_config);
	blink_config.blink_all_seg = false;
	slcd_blink_set_config(&blink_config);

	for(uint32_t i=0; i<4; i++){
		slcd_set_blink_pixel(i,0);
		slcd_set_blink_pixel(i,1);
	}

	slcd_set_frame_counter(SLCD_FRAME_COUNTER_0,true,0x18);
	slcd_enable_frame_counter(SLCD_FRAME_COUNTER_0);

	slcd_enable_blink();
	slcd_enable();
	delay_s(2);
//! [use_cases_4]

//! [use_cases_5]
	/* 5. Automated Character Mapping*/
	slcd_disable();
	struct slcd_automated_char_config acm_config;
	slcd_automated_char_get_config_default(&acm_config);
	acm_config.order = SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT;
	acm_config.fc = SLCD_FRAME_COUNTER_1;
	acm_config.mode = SLCD_AUTOMATED_CHAR_SCROLL;
	acm_config.seg_line_num = 3;
	acm_config.start_seg_line = 4;
	acm_config.row_digit_num = 5;
	acm_config.digit_num = 5;
	acm_config.scrolling_step = sizeof(display_array) - 5 + 1;
	acm_config.com_line_num = 4;
	acm_config.data_mask = 0xFF4002;
	slcd_automated_char_set_config(&acm_config);

	slcd_set_frame_counter(SLCD_FRAME_COUNTER_1,true,0x1E);
	slcd_enable_frame_counter(SLCD_FRAME_COUNTER_1);

	slcd_enable_automated_character();
	slcd_enable();
	delay_s(3);
//! [use_cases_5]

//! [use_cases_6]
	/* 6. Automated Bit Mapping*/
	slcd_disable();
	slcd_disable_automated_character();
	slcd_clear_display_memory();
	slcd_disable_frame_counter(SLCD_FRAME_COUNTER_2);
	slcd_set_automated_bit(ABM_MATRIX_SIZE,SLCD_FRAME_COUNTER_2);
	slcd_set_frame_counter(SLCD_FRAME_COUNTER_2,true,0x1F);
	slcd_enable_frame_counter(SLCD_FRAME_COUNTER_2);
	slcd_enable_automated_bit();
	slcd_enable();
//! [use_cases_6]
//! [use_cases]
    while(1){

    }

}

