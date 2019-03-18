/**
 * \file
 *
 * \brief SAM L22 SLCD Features Example Application
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \license
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
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
 /**
 * \mainpage
 * \section intro Introduction
 * This is the documentation for the data structures, functions, variables,
 * defines, enums, and typedefs for the SAM L22 Xplained pro SLCD example
 * application. 
 *
 * This example demonstrates SAM L22 how to use the SAM L22 SLCD.
 *
 * The supported board list:
 *    - SAM L22 Xplained Pro
 *
 * \section compilinfo Compilation Information
 * This software is written for GNU GCC and IAR Embedded Workbench for Atmel.
 * Other compilers may or may not work.
 *
 * \section deviceinfo Device Information
 * SEGMENT LCD1 Xplained Pro extension board connected to SAM L22 Xplained Pro
 * board. 
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
#include <string.h>
#include <conf_slcd.h>
#include <conf_example.h>

/* DMA and User scrolling string buffer length */
#define BUFFER_LEN 30

/* DMA resource and descriptor */
struct dma_resource example_resource;

COMPILER_ALIGNED(16)
DmacDescriptor example_descriptor;

/* Variables used for DMA transfer */
static volatile uint32_t dma_source_buf[BUFFER_LEN];
static volatile bool transfer_is_done = false;
static volatile uint32_t dma_break = 0, dma_block_count = 0;

/* User scrolling string */
static char user_scrolling_str[BUFFER_LEN] = {"HELLO WORLD     "};

bool is_scrolling = false;
bool is_blinking = false;
bool is_bitmapping = false;
uint8_t bitmapping_repeat_count = 0;

/* Module instances */
static struct usart_module usart_instance;

/* Segment LCD1 Xplained Pro look-up table */
uint16_t DIGI_LUT[] = {
/*  0x0000,     -m0dnlcekjbfiga0h               */
	0x0000, /* 0b0000000000000000, - 32 - Space */
	0x0000, /* 0b0000000000000000, - 33 - !     */
	0x0000, /* 0b0000000000000000, - 34 - "     */
	0x0000, /* 0b0000000000000000, - 35 - #     */
	0x0000, /* 0b0000000000000000, - 36 - $     */
	0x0000, /* 0b0000000000000000, - 37 - %     */
	0x0000, /* 0b0000000000000000, - 38 - &     */
	0x0000, /* 0b0000000000000000, - 39 - '     */
	0x0000, /* 0b0000000000000000, - 40 - (     */
	0x0000, /* 0b0000000000000000, - 41 - )     */
	0x99D9, /* 0b1001100111011001, - 42 - *     */
	0x8181, /* 0b1000000110000001, - 43 - +     */
	0x0000, /* 0b0000000000000000, - 44 - ,     */
	0x0100, /* 0b0000000100000000, - 45 - -     */
	0x0000, /* 0b0000000000000000, - 46 - .     */
	0x0810, /* 0b0000100000010000, - 47 - /     */
	0x2E74, /* 0b0010111001110100, - 48 - 0     */
	0x0440, /* 0b0000010001000000, - 49 - 1     */
	0x23C4, /* 0b0010001111000100, - 50 - 2     */
	0x25C4, /* 0b0010010111000100, - 51 - 3     */
	0x05E0, /* 0b0000010111100000, - 52 - 4     */
	0x25A4, /* 0b0010010110100100, - 53 - 5     */
	0x27A4, /* 0b0010011110100100, - 54 - 6     */
	0x0444, /* 0b0000010001000100, - 55 - 7     */
	0x27E4, /* 0b0010011111100100, - 56 - 8     */
	0x25E4, /* 0b0010010111100100, - 57 - 9     */
	0x0000, /* 0b0000000000000000, - 58 - :     */
	0x0000, /* 0b0000000000000000, - 59 - ;     */
	0x1010, /* 0b0001000000010000, - 60 - <     */
	0x0000, /* 0b0000000000000000, - 61 - =     */
	0x0808, /* 0b0000100000001000, - 62 - >     */
	0x0000, /* 0b0000000000000000, - 63 - ?     */
	0x0000, /* 0b0000000000000000, - 64 - @     */
	0x07E4, /* 0b0000011111100100, - 65 - A     */
	0xA545, /* 0b1010010101000101, - 66 - B     */
	0x2224, /* 0b0010001000100100, - 67 - C     */
	0xA445, /* 0b1010010001000101, - 68 - D     */
	0x23A4, /* 0b0010001110100100, - 69 - E     */
	0x03A4, /* 0b0000001110100100, - 70 - F     */
	0x2724, /* 0b0010011100100100, - 71 - G     */
	0x07E0, /* 0b0000011111100000, - 72 - H     */
	0xA005, /* 0b1010000000000101, - 73 - I     */
	0x2640, /* 0b0010011001000000, - 74 - J     */
	0x12B0, /* 0b0001001010110000, - 75 - K     */
	0x2220, /* 0b0010001000100000, - 76 - L     */
	0x0678, /* 0b0000011001111000, - 77 - M     */
	0x1668, /* 0b0001011001101000, - 78 - N     */
	0x2664, /* 0b0010011001100100, - 79 - O     */
	0x03E4, /* 0b0000001111100100, - 80 - P     */
	0x3664, /* 0b0011011001100100, - 81 - Q     */
	0x13E4, /* 0b0001001111100100, - 82 - R     */
	0x25A4, /* 0b0010010110100100, - 83 - S     */
	0x8005, /* 0b1000000000000101, - 84 - T     */
	0x2660, /* 0b0010011001100000, - 85 - U     */
	0x0A30, /* 0b0000101000110000, - 86 - V     */
	0x1E60, /* 0b0001111001100000, - 87 - W     */
	0x1818, /* 0b0001100000011000, - 88 - X     */
	0x8018, /* 0b1000000000011000, - 89 - Y     */
	0x2814, /* 0b0010100000010100, - 90 - Z     */
};

/**
* \name Function Prototypes
* @{
*/

void xpro_lcd_init(void);
void display_menu(void);
void xpro_lcd_show_all(void);
void xpro_lcd_clear_all(void);
void xpro_lcd_show_icon(uint8_t icon_com, uint8_t icon_seg);
void xpro_lcd_clear_icon(uint8_t icon_com, uint8_t icon_seg);
void xpro_lcd_blink_icon_start(uint8_t icon_com, uint8_t icon_seg);
void xpro_lcd_blink_icon_stop(uint8_t icon_com, uint8_t icon_seg);
void xpro_lcd_blink_screen(void);
void xpro_lcd_blink_disable(void);
void xpro_lcd_set_contrast(uint8_t contrast);
void xpro_lcd_show_numeric_dec(int32_t value);
void xpro_lcd_clear_numeric_dec(void);
void xpro_lcd_text_scrolling_start(char *data);
void xpro_lcd_text_bitmapping_start(uint8_t user_style);
void xpro_lcd_text_bitmapping_stop(void);
void xpro_lcd_text_scrolling_stop(void);
void xpro_lcd_show_text(const uint8_t *data);
void xpro_lcd_clear_text(void);

/**
* \brief Stop the XPRO_LCD automated character display mode.
*
* \note This function also disables the DMA channel associated with the
* XPRO_LCD module.
*/
static inline void xpro_lcd_automated_char_stop(void)
{
	/* Disable automated character mode */
	slcd_disable_automated_character();
	is_scrolling = false;

	/* Disable DMA channel */
	dma_free(&example_resource);
}

/**
* \brief Stop the XPRO_LCD automated bit mapping display mode.
*
* \note This function also disables the DMA channel associated with the
* XPRO_LCD module.
*/
static inline void xpro_lcd_automated_bit_stop(void)
{
	/* Disable automated bit mapping mode */
	slcd_disable_automated_bit();
	is_bitmapping = false;

	/* Disable DMA channel */
	dma_free(&example_resource);
}

/**
* \brief configure DMA resource.
*/
static void configure_dma_resource(struct dma_resource *resource)
{
	struct dma_resource_config config;
	/* Get the default configuration */
	dma_get_config_defaults(&config);

	if (true == is_scrolling) {
		/* Set the peripheral trigger source */
		config.peripheral_trigger = SLCD_DMAC_ID_ACMDRDY;
		/* Set the trigger action */
		config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
	}

	if (true == is_bitmapping) {
		/* Set the peripheral trigger source */
		config.peripheral_trigger = SLCD_DMAC_ID_ABMDRDY;
		/* Set the trigger action */
		config.trigger_action = DMA_TRIGGER_ACTION_BEAT;
	}

	dma_allocate(resource, &config);
}

/**
* \brief configure DMA transfer descriptor.
*/
static void setup_transfer_descriptor(DmacDescriptor *descriptor)
{
	struct dma_descriptor_config descriptor_config;

	if (true == is_scrolling) {
		/* Get the default configuration */
		dma_descriptor_get_config_defaults(&descriptor_config);

		descriptor_config.beat_size = DMA_BEAT_SIZE_WORD;
		descriptor_config.src_increment_enable = true;
		descriptor_config.dst_increment_enable = false;
		descriptor_config.step_size = (DMA_ADDRESS_INCREMENT_STEP_SIZE_1);
		descriptor_config.step_selection = DMA_STEPSEL_SRC;
		descriptor_config.block_action = DMA_BLOCK_ACTION_INT;

		/* DMA transfer count found by Block count variable at
		 * run time from the scrolling string.
		 */
		descriptor_config.block_transfer_count = dma_block_count;
		descriptor_config.source_address = (uint32_t)dma_source_buf +
				(dma_block_count * sizeof(dma_source_buf[0]));
		descriptor_config.destination_address = (uint32_t)(&SLCD->CMDATA.reg);
		descriptor_config.next_descriptor_address = ( uint32_t )descriptor;

		/* Create a DMA descriptor */
		dma_descriptor_create(descriptor, &descriptor_config);
	}

	if (true == is_bitmapping) {
		/* Get the default configuration */
		dma_descriptor_get_config_defaults(&descriptor_config);

		descriptor_config.beat_size = DMA_BEAT_SIZE_WORD;
		descriptor_config.src_increment_enable = true;
		descriptor_config.dst_increment_enable = false;
		descriptor_config.step_size = (DMA_ADDRESS_INCREMENT_STEP_SIZE_1);
		descriptor_config.step_selection = DMA_STEPSEL_SRC;
		descriptor_config.block_action = DMA_BLOCK_ACTION_INT;

		/* Block count manipulated number of the frame elements respective
		 * style chosen by the user at run time.
		 */
		descriptor_config.block_transfer_count = dma_block_count;
		descriptor_config.source_address = (uint32_t)dma_source_buf +
				(dma_block_count * sizeof(dma_source_buf[0]));
		descriptor_config.destination_address = (uint32_t)(&SLCD->ISDATA.reg);
		descriptor_config.next_descriptor_address = (uint32_t)descriptor;

		/* Create a DMA descriptor */
		dma_descriptor_create(descriptor, &descriptor_config);
	}
}

/**
* \brief DMA callback function for transfer complete.
*/
static void dma_callback(struct dma_resource* const resource)
{
	transfer_is_done = true;
	dma_break++;
	if (true == is_scrolling) {
		/* Used for automatically exit implementation */
		if ((dma_block_count * 4) <= dma_break) {
			dma_break = 0;
			/* Stop Automated character mode */
			xpro_lcd_automated_char_stop();
			printf("Exits from scrolling mode.\n\n\r");
			display_menu();
		}
	}

	if (true == is_bitmapping) {
		/* Used for automatically exit implementation */
		if ((bitmapping_repeat_count) <= dma_break) {
			dma_break = 0;
			/* Stop Automated bit mode */
			xpro_lcd_automated_bit_stop();
			printf("Exits from Bit mapping mode.\n\n\r");
			display_menu();
		}
	}
}

/**
* \brief Config DMA to make peripheral-to-memory transfer scrolling string to
* SLCD memory.
*/
static void configure_dma(void)
{
	configure_dma_resource(&example_resource);
	setup_transfer_descriptor(&example_descriptor);

	if (STATUS_OK != dma_add_descriptor(&example_resource,
			&example_descriptor)) {
		printf("Descriptor status error\n\n\r");
	}

	dma_register_callback(&example_resource, dma_callback,
			DMA_CALLBACK_TRANSFER_DONE);
	dma_enable_callback(&example_resource, DMA_CALLBACK_TRANSFER_DONE);
}

/**
* \brief Configure serial console.
*/
static void configure_console(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);
	config_usart.baudrate    = 115200;
	config_usart.mux_setting = EDBG_CDC_SERCOM_MUX_SETTING;
	config_usart.pinmux_pad0 = EDBG_CDC_SERCOM_PINMUX_PAD0;
	config_usart.pinmux_pad1 = EDBG_CDC_SERCOM_PINMUX_PAD1;
	config_usart.pinmux_pad2 = EDBG_CDC_SERCOM_PINMUX_PAD2;
	config_usart.pinmux_pad3 = EDBG_CDC_SERCOM_PINMUX_PAD3;
	stdio_serial_init(&usart_instance, EDBG_CDC_MODULE, &config_usart);
	usart_enable(&usart_instance);
}

/**
* \brief Get the user string on the terminal.
*/
static void get_userstr(char *data, uint16_t length)
{
	do {
		printf("Type the user input string and press Enter\n\r");

		if (25 == length) {
			printf("Note:-\n\r"
			       "Max 25 characters (A-Z,0-9 and 'space' only).\n\n\r");
			scanf("%25[0-9A-Z ]s", data);
			strcat(data,"     ");
		} else {
			printf("Note:-\n\r"
			       "Max 5 characters (A-Z,0-9 and 'space' only).\n\n\r");
			scanf("%5[0-9A-Z ]s", data);
		}

		/* flushing stdio .... */
		fflush(stdout);

		printf("The input string entered is \"%s\" \n\n\r", data);
		printf("-----------------------------------------------\n\r");
		printf("Press 'e' to re-type or press any key to continue\n\n\r");
		getchar();
	} while (getchar() == 'e');
}

/**
* \brief Clear the data buffers.
*/
static void clear_buffer(void)
{
	uint32_t loop_count = 0;
	while ((BUFFER_LEN - 1) >= loop_count) {
		dma_source_buf[loop_count] = 0;

		/* Clears the user scrolling string */
		if (false == is_bitmapping) {
			user_scrolling_str[loop_count] = 0;
		}
		loop_count++;
	}
}

/**
* \name Function Definitions
* @{
*/

/**
* \brief Display the user menu on the terminal.
*/
void display_menu(void)
{
	printf("\n\r");
	printf("===============================================\n\r");
	printf("Menu: Select the option.\n\r");
	printf("===============================================\n\r");

	printf("  1 : Display UART user input string in SLCD \n\r");
	printf("  2 : Character mapping feature \n\r");
	printf("  3 : Auto Character mapping feature \n\r");
	printf("  4 : Blinking feature \n\r");
	printf("  5 : Auto Bit mapping feature \n\n\r");

	printf("  c : Clear the SLCD screen \n\r");
	printf("  e : To change the user scrolling string input \n\r");

	printf("-----------------------------------------------\n\r");
	printf(">>");
}

/**
* \brief Initialize the XPRO_LCD LCD Glass component.
*
* This function initializes the LCD driver to control the LCD glass.
* It perform LCD module initialization according to the XPRO_LCD
* characteristics.
*
*/
void xpro_lcd_init(void)
{
	struct slcd_config config;
	slcd_get_config_defaults(&config);
	config.waveform_mode = SLCD_LOW_POWER_WAVEFORM_MODE;
	/* Initialize SLCD */
	slcd_init(&config);

	slcd_set_frame_counter(SLCD_FRAME_COUNTER_0, false, CONF_XPRO_LCD_FC0);
	slcd_set_frame_counter(SLCD_FRAME_COUNTER_1, false, CONF_XPRO_LCD_FC1);
	slcd_set_frame_counter(SLCD_FRAME_COUNTER_2, false, CONF_XPRO_LCD_FC2);
	/* Set SLCD software contrast level */
	slcd_set_contrast(CONF_XPRO_LCD_CONTRAST);
}

/**
* \brief Show all content of the LCD glass.
*
* This function sets all pixels and areas of the LCD glass XPRO_LCD.
*
*/
void xpro_lcd_show_all(void)
{
	slcd_disable();
	slcd_disable_blink();
	slcd_disable_circular_shift();
	slcd_set_display_memory();
	slcd_enable();
}

/**
* \brief Clear all content of the LCD glass.
*
* This function clears all pixels and areas of the LCD glass XPRO_LCD.
*
*/
void xpro_lcd_clear_all(void)
{
	slcd_disable_blink();
	slcd_disable_circular_shift();
	slcd_clear_display_memory();
	xpro_lcd_text_scrolling_stop();
	xpro_lcd_text_bitmapping_stop();
	dma_break = 0;
}

/**
* \brief Show a specific icon on the LCD glass.
*
* This function will show a specific icon.
*
* \param icon_com  Pixel coordinate - COM - of the icon.
* \param icon_seg  Pixel coordinate - SEG - of the icon.
*
* \note Use the icon define in header file.
*/
void xpro_lcd_show_icon(uint8_t icon_com, uint8_t icon_seg)
{
	slcd_set_pixel(icon_com, icon_seg);
}

/**
* \brief Clear a specific icon on the LCD glass.
*
* This function will clear a specific icon.
*
* \param icon_com  Pixel coordinate - COM - of the icon.
* \param icon_seg  Pixel coordinate - SEG - of the icon.
*
* \note Use the icon define in header file.
*/
void xpro_lcd_clear_icon(uint8_t icon_com, uint8_t icon_seg)
{
	slcd_clear_pixel(icon_com, icon_seg);
}

/**
* \brief Blink a specific icon on the LCD glass.
*
* This function will blink a specific icon.
*
* \param icon_com  Pixel coordinate - COM - of the icon.
* \param icon_seg  Pixel coordinate - SEG - of the icon.
*
* \note Use the icon define in header file(with selected segments
* blinking feature).
*/
void xpro_lcd_blink_icon_start(uint8_t icon_com, uint8_t icon_seg)
{
	if (icon_seg < 2) {
		xpro_lcd_show_icon(icon_com,icon_seg);
		slcd_disable();
		struct slcd_blink_config blink_config;
		slcd_blink_get_config_defaults(&blink_config);
		blink_config.blink_all_seg = false;
		blink_config.fc = CONF_XPRO_LCD_BLINK_TIMER;
		slcd_blink_set_config(&blink_config);
		slcd_set_blink_pixel(icon_com, icon_seg);
		slcd_enable_frame_counter(CONF_XPRO_LCD_BLINK_TIMER);
		slcd_enable_blink();
		slcd_enable();
	}
}

/**
* \brief Stop blink a specific icon on the LCD glass.
*
* This function will stop blink a specific icon.
*
* \param icon_com  Pixel coordinate - COM - of the icon.
* \param icon_seg  Pixel coordinate - SEG - of the icon.
*
* \note Use the icon define in header file(with selected segments
* blinking feature).
*/
void xpro_lcd_blink_icon_stop(uint8_t icon_com, uint8_t icon_seg)
{
	if (icon_seg < 2) {
		slcd_disable_blink();
		slcd_disable();
		slcd_clear_blink_pixel(icon_com, icon_seg);
		slcd_enable_blink();
		slcd_enable();
	}
}

/**
* \brief Blink the current screen content.
*
* This function will make the current screen blink.
*
*/
void xpro_lcd_blink_screen(void)
{
	slcd_disable_blink();
	slcd_disable();
	struct slcd_blink_config blink_config;
	slcd_blink_get_config_defaults(&blink_config);
	blink_config.blink_all_seg = true;
	blink_config.fc = CONF_XPRO_LCD_BLINK_TIMER;
	slcd_blink_set_config(&blink_config);

	slcd_enable_frame_counter(CONF_XPRO_LCD_BLINK_TIMER);
	slcd_enable_blink();
	slcd_enable();
}

/**
* \brief Disable all Blink.
*
* This function will disable all Blink content.
*
*/
void xpro_lcd_blink_disable(void)
{
	slcd_disable_frame_counter(CONF_XPRO_LCD_BLINK_TIMER);
	slcd_disable_blink();
}

/**
* \brief Set the XPRO_LCD LCD glass contrast.
*
*  This function allows to adjust the contrast of the XPRO_LCD LCD glass.
*
*  \param contrast 0 <= contrast value <= 15.
*/
void xpro_lcd_set_contrast(uint8_t contrast)
{
	slcd_set_contrast(contrast);
}

/**
* \brief Show a decimal numeric value to LCD glass.
*
* This function displays an int32 value to the LCD numeric field of the glass.
*
* \param value The int32_t value to be displayed
*
* \note The value range is [-199999,199999].
*/
void xpro_lcd_show_numeric_dec(int32_t value)
{
	uint32_t tmp=0;
	Assert(value > -200000);
	Assert(value < 200000);

	slcd_character_map_set(SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT, 3);

	if (value < 0) {
		slcd_set_pixel(XPRO_LCD_ICON_MINUS);
		} else {
		slcd_clear_pixel(XPRO_LCD_ICON_MINUS);
	}

	tmp = Abs(value);

	if (tmp > 99999) {
		slcd_set_pixel(XPRO_LCD_ICON_MINUS_SEG1);
		slcd_set_pixel(XPRO_LCD_ICON_MINUS_SEG2);
		tmp -= 100000;
		} else {
		slcd_clear_pixel(XPRO_LCD_ICON_MINUS_SEG1);
		slcd_clear_pixel(XPRO_LCD_ICON_MINUS_SEG2);
	}

	for (int32_t i = XPRO_LCD_MAX_NUM-1; (i >= 0); i--) {
		slcd_character_write_data(0,(XPRO_LCD_NUM_SEG_INDEX_S +
				i * (XPRO_LCD_MAX_NUM-1)), DIGI_LUT[(tmp%10) + 15], 0x4002);
		tmp /=10;
	}
}

/**
* \brief Clear XPRO_LCD LCD glass numeric field.
*
* This function will clear the numeric field of the LCD glass.
*/
void xpro_lcd_clear_numeric_dec(void)
{
	slcd_clear_pixel(XPRO_LCD_ICON_MINUS);
	slcd_clear_pixel(XPRO_LCD_ICON_MINUS_SEG1);
	slcd_clear_pixel(XPRO_LCD_ICON_MINUS_SEG2);

	slcd_clear_pixel(XPRO_LCD_ICON_DOT_1);
	slcd_clear_pixel(XPRO_LCD_ICON_DOT_2);
	slcd_clear_pixel(XPRO_LCD_ICON_DOT_3);
	slcd_clear_pixel(XPRO_LCD_ICON_DOT_4);

	slcd_clear_pixel(XPRO_LCD_ICON_AM);
	slcd_clear_pixel(XPRO_LCD_ICON_PM);
	slcd_clear_pixel(XPRO_LCD_ICON_DEGREE_C);
	slcd_clear_pixel(XPRO_LCD_ICON_DEGREE_F);
	slcd_clear_pixel(XPRO_LCD_ICON_VOLT);
	slcd_clear_pixel(XPRO_LCD_ICON_MILLI_VOLT);
	slcd_character_map_set(SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT, 3);
	for (uint32_t i = 0 ; i < XPRO_LCD_MAX_NUM; i++) {
		slcd_character_write_data(0, XPRO_LCD_NUM_SEG_INDEX_S +
				i * (XPRO_LCD_MAX_NUM-1), 0, 0x4002);
	}
}

/**
* \brief Scrolling start.
*
* This function start the text scrolling.
*
* \param data Data string buffer.
* \param length Data string length.
*/
void xpro_lcd_text_scrolling_start(char *data)
{
	/* Structures for the ACM configurations */
	struct slcd_automated_char_config automated_char_config;

	uint16_t i=0;
	dma_block_count = 0;

	/* used to copy the user scrolling string into dma_source
	 * buffer for the DMA transfer 
	 * The scrolling may be runtime user input string 25char max
	 * or the default scrolling string in user_scrolling_str[].
	 */
	while (*data != '\0'){
		/* Copying the scrolling string into DMA source buffer*/
		dma_source_buf[i++] = DIGI_LUT[*(data++) - 32];
		/* To find the scrolling string length */
		dma_block_count++;
	}

	if (true == is_scrolling) {
		/* configuration for Auto character mapping scrolling mode */
		/* Get default config for the ACM mode */
		slcd_automated_char_get_config_default(&automated_char_config);
		/* Segment mapping order. (CMCFG.DEC bit) */
		automated_char_config.order =
				SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT;
		/* select the number of segment used per digit,
		 * it equal to number of SEG line - 1. (CMCFG.DEC).
		 */
		automated_char_config.seg_line_num = 3;

		/* Define the number of digit per row. (ACMCFG.NDROW) */
		automated_char_config.row_digit_num = XPRO_LCD_MAX_CHAR;
		/* Define the index of the first segment terminal of the digit
		 * to display. (ACMCFG.STSEG).
		 */
		automated_char_config.start_seg_line = XPRO_LCD_TXT_SEG_INDEX_S;
		/* Define the number of digit, it must be greater than 1.
		 * (ACMCFG.NDIG).
		 */
		automated_char_config.digit_num = XPRO_LCD_MAX_CHAR;

		/* STEPS = string length - digit_num + 1. (ACMCFG.STEPS) */
		automated_char_config.scrolling_step = dma_block_count - 5 + 1;
		/* Select the ACM mode (ACMCFG.MODE) */
		automated_char_config.mode  = SLCD_AUTOMATED_CHAR_SCROLL;
		/* Select the frame counter for the ACM mode. (ACMCFG.FCS) */
		automated_char_config.fc = SLCD_FRAME_COUNTER_1;

		/* Configure the mask value in the CMDMASK register */
		automated_char_config.data_mask = 0x00FF4002;
	}

	/* Disable SLCD to write the enable-protected registers */
	slcd_disable();
	/* write the SLCD ACM configurations in the respective registers */
	slcd_automated_char_set_config(&automated_char_config);

	/* Disable Frame counter to write the enable-protected registers */
	slcd_disable_frame_counter(automated_char_config.fc);
	slcd_dma_display_memory_update_fc_sel(automated_char_config.fc);

	/* Set the Frame counter configurations and enable it */
	slcd_set_frame_counter(automated_char_config.fc, 0, 0x1);
	slcd_enable_frame_counter(automated_char_config.fc);

	/* Enable SLCD */
	slcd_enable();

	/* Configure DMA */
	configure_dma();

	/* Start DMA transfer, once DMA gets the peripheral trigger from the ACM,
	 * the data transfer starts.
	 */
	dma_start_transfer_job(&example_resource);

	/* Enable ACM mode */
	slcd_enable_automated_character();
}

/**
* \brief Scrolling stop.
*
* This function stop the text scrolling.
*/
void xpro_lcd_text_scrolling_stop(void)
{
	xpro_lcd_automated_char_stop();
}

/**
* \brief Scrolling start.
*
* This function start the Bit mapping text.
*
* \param data Data string buffer.
* \param length Data string length.
*/
void xpro_lcd_text_bitmapping_start(uint8_t user_style)
{
	/* Default config for automated bit mapping */
	uint8_t config_user_style = (user_style & 0x03);
	uint8_t config_size = 0;
	uint8_t config_fc_value = 0;
	enum slcd_frame_counter config_fc = SLCD_FRAME_COUNTER_0;

	/* User buffer to load the user style. In this array new styles can be
	 * added as a new row with the same column width.
	 * At the end of the each style's array member value should be kept
	 * as 0x0000FF00 to calculate the block_count.
	 * The empty elements between the style members should be 0x0000FFFF.
	 */
	uint16_t i=0;
	uint32_t user_style_buf[5][30] = {
		{
			/* STYLE 0 */
			0x00000040, 0x000600e0, 0x000C0070, 0x00120000, /*'A' 0x07e4 */
			0x00010005, 0x00070000, 0x000D0000, 0x00130008, /*'T' 0x8005 */
			0x00010085, 0x00070070, 0x000D0060, 0x00130008, /*'M' 0x0678 */
			0x00020004, 0x0008000a, 0x000E0003, 0x00140002, /*'E' 0x23a4 */
			0x00020004, 0x0008002a, 0x000E0023, 0x00140022, /*'L' 0x2220 */
			0x0000FF00, 0x0000FF00, 0x0000FF00, 0x0000FF00
		},
		{
			/* STYLE 1 */
			0x00000040,0x00070000,0x000D0060,0x00140002,
			0x000600e0,0x000D0060,0x00130008,0x00020004,
			0x000C0070,0x00130008,0x00020004,0x0008000a,
			0x00120000,0x00010005,0x0008002a,0x000E0003,
			0x00010085,0x00070070,0x000E0023,0x00140022,
			0x0000FF00,0x0000FF00,0x0000FF00,0x0000FF00
		},
		{
			/* STYLE 2 */
			0x00000040,0x00010004,0x00020004,0x00010045,
			0x00060060,0x00070070,0x00010085,0x000600E0,
			0x00080022,0x0008002a,0x000C0010,0x000E0001,
			0x000C0070,0x000D0060,0x000E0023,0x00130008,
			0x00140022,0x0000FF00,0x0000FF00,0x0000FF00,
			0x0000FF00,0x0000FF00,0x0000FF00,0x0000FF00
		},
		{
			/* STYLE 3 */
			0x00000040,0x00010044,0x0000FFFF,0x0000FFFF,
			0x00020044,0x00080040,0x00000000,0x00010000,
			0x000E0040,0x00140022,0x00020000,0x00080000,
			0x00120020,0x00130022,0x000E0000,0x00140000,
			0x000C0020,0x00060020,0x00120000,0x00130000,
			0x00000040,0x000C0000,0x00060000,0x0000FF00
		},
		{
			/* SPARE x */
			0x00000040,0x00010004,0x00020004,0x00010045,
			0x00060060,0x00070070,0x00010085,0x000600E0,
			0x00080022,0x0008002a,0x000C0010,0x000E0001,
			0x000C0070,0x000D0060,0x000E0023,0x00130008,
			0x00140022,0x0000FF00,0x0000FF00,0x0000FF00,
			0x0000FF00,0x0000FF00,0x0000FF00,0x0000FF00
		}
	};

	/* Variable use to find the DMA transfer block count at runtime based
	 * on the user input string/style.
	 */
	dma_block_count = 0;

	/* Clears the previous values present in the dma_source_buf */
	clear_buffer();

	/* used to copy the user style to dma_source buffer for the DMA transfer.
	 * The user style options are Style0, Style1, Style2 & Style3.
	 */
	while (0x0000FF00 != user_style_buf[config_user_style][i]) {
		dma_source_buf[i] = user_style_buf[config_user_style][i];
		/* To find the user style number of segment data */
		dma_block_count++;
		i++;
	}

	/* user configurations for automated bit mapping */
	if ((uint8_t) 0x03 == config_user_style) {
		config_size = 1;
		config_fc_value = 0x01;
		bitmapping_repeat_count = 0x05;
	} else {
		config_size = 3;
		config_fc_value = 0x0F;
		bitmapping_repeat_count = 0x01;
	}
	config_fc = SLCD_FRAME_COUNTER_1;

	/* Disable SLCD to write the enable-protected registers */
	slcd_disable();
	/* write the SLCD ABM configurations in the respective registers */
	slcd_set_automated_bit(config_size, config_fc);

	/* Disable Frame counter to write the enable-protected registers */
	slcd_disable_frame_counter(config_fc);
	/* Set the frame counter configurations and enable it */
	slcd_set_frame_counter(config_fc, 1, config_fc_value);
	slcd_enable_frame_counter(config_fc);

	/* Enable SLCD */
	slcd_enable();

	/* Configure DMA */
	configure_dma();

	/* Start DMA transfer, once DMA gets the peripheral trigger from the ABM,
	 * the data transfer starts.
	 */
	dma_start_transfer_job(&example_resource);

	/* Enable ACM mode */
	slcd_enable_automated_bit();
}

/**
* \brief Scrolling stop.
*
* This function stop the auto bit mapping mode.
*/
void xpro_lcd_text_bitmapping_stop(void)
{
	xpro_lcd_automated_bit_stop();
}

/**
* \brief Show text on XPRO_LCD LCD glass alphanumeric field.
*
* This function will show text on the alphanumeric field of the LCD glass.
*
* \param data Pointer to the input string(max length is 7)
*/
void xpro_lcd_show_text(const uint8_t *data)
{
	Assert(data);
	uint32_t len = (uint32_t)strlen((char *) data);

	len = (len > XPRO_LCD_MAX_CHAR) ? XPRO_LCD_MAX_CHAR : len;

	slcd_character_map_set(SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT,
			XPRO_LCD_MAX_NUM-2);
	for (uint32_t i = 0; *data != '\0'; i++) {
		slcd_character_write_data(0, XPRO_LCD_TXT_SEG_INDEX_S +
				i * (XPRO_LCD_MAX_NUM-1), DIGI_LUT[*(data++) - 32], 0x4002);
	}
}

/**
* \brief Clear XPRO_LCD LCD glass alphanumeric field.
*
* This function will clear the alphanumeric field of the LCD glass.
*/
void xpro_lcd_clear_text(void)
{
	slcd_character_map_set(SLCD_AUTOMATED_CHAR_START_FROM_BOTTOM_RIGHT,
			XPRO_LCD_MAX_NUM-2);
	for (uint32_t i = 0; i < XPRO_LCD_MAX_CHAR; i++) {
		slcd_character_write_data(0,XPRO_LCD_TXT_SEG_INDEX_S +
				i * (XPRO_LCD_MAX_NUM-1), 0, 0x4002);
	}
}

int main(void)
{
	uint8_t key = 0;
	/* Temporary buffer used for get the user input string */
	char user_str[] = {""};

	/* Initialize the SAM system */
	system_init();
	/* Set NVM wait state */
	NVMCTRL->CTRLB.bit.RWS = 3;
	board_init();

	/* Initialize the console USART */
	configure_console();

	/* Output example information */
	printf("\n\r");
	printf("===============================================\n\r");
	printf("         -- SLCD Example --                \n\r");
	printf("===============================================\n\n\r");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\n\r", __DATE__, __TIME__);

	printf("-----------------------------------------------\n\r");
	printf("\n\r");

	/* Turn on the backlight. */
	port_pin_set_output_level(SLCD_BACLKLIGHT,true);

	/* Initialize the XPRO_LCD LCD glass component. */
	xpro_lcd_init();

	/* Enable SLCD */
	slcd_enable();

	/* Enables all the segments in the SLCD */
	printf("Printing all of the SLCD segments.\n\n\r");
	xpro_lcd_show_all();

	printf("Press any key to continue.\n\n\r");
	scanf("%c", (char *)&key);

	/* Clear the SLCD and disables all the running modes */
	xpro_lcd_clear_all();

	/* Display menu */
	display_menu();

	while (1) {
		/* Get the user option */
		scanf("%c", (char *)&key);

		switch (key) {
		case 'c':
		case 'C':
			printf("c: Clear the SLCD screen \n\n\r");
			printf("Clearing... \n\r");
			xpro_lcd_clear_all();
			display_menu();
			break;

		case 'e':
		case 'E':
			printf("e: To change the user scrolling string input \n\n\r");
			xpro_lcd_clear_all();
			clear_buffer();
			get_userstr(user_str, 25);
			strcpy(user_scrolling_str, user_str);
			display_menu();
			break;

		case '1':
			printf("1: Display UART user input string in SLCD \n\n\r");
			get_userstr(user_str, 5);
			xpro_lcd_clear_all();
			printf("Printing -- [ %s ] \n\r", user_str);
			xpro_lcd_show_text((const uint8_t *)user_str);
			display_menu();
			break;

		case '2':
			xpro_lcd_clear_all();
			printf("2: Character mapping feature.\n\n\r");
			printf("Running... \n\r");
			xpro_lcd_show_text((const uint8_t *)"ATMEL");
			delay_s(2);

			xpro_lcd_clear_all();
			/* values range -199999 to 199999 */
			xpro_lcd_show_numeric_dec(-123456); 
			delay_s(2);
			display_menu();
			break;

		case '3':
			xpro_lcd_clear_all();
			printf("3: Auto Character mapping feature.\n\n\r"
			       "Text scrolling...\n\n\r");
			is_scrolling = true;
			xpro_lcd_text_scrolling_start(user_scrolling_str);
			printf("Press 'c' to exit scrolling and clear display.\n\r"
			       "Otherwise it will exit automatically.\n\n\r");
			xpro_lcd_show_icon(XPRO_LCD_ICON_ATMEL);
			printf("-----------------------------------------------\n\r");
			break;

		case '4':
			xpro_lcd_clear_all();
			printf("4: Blinking feature.\n\n\r");
			printf("Blink screen...\n\r");
			xpro_lcd_show_text((const uint8_t *)"BLINK");
			xpro_lcd_blink_screen();
			delay_s(2);
			display_menu();
			break;

		case '5':
			xpro_lcd_clear_all();
			printf("5: Auto Bit mapping feature.\n\n\r"
			       "Select the user style\n\r"
			       "Press 0 for Style0\n\r"
			       "Press 1 for Style1\n\r"
			       "Press 2 for Style2\n\r"
			       "Press 3 for Style3\n\r" 
			       "\n\r");
			is_bitmapping = true;
			/* Get the user option */
			scanf("%c", (char *)&key);
			switch (key) {
			case '0':
			case '1':
			case '2':
			case '3':
				printf("Style%c selected.\n\n\r", key);
				xpro_lcd_text_bitmapping_start(key);
				printf("Press 'c' to exit Auto bit mapping and"
				       "clear display. \n\r"
				       "Otherwise it will exit automatically\n\n\r");
				break;
			default:
				printf("Invalid input received.\n\n\r");
				display_menu();
				break;
			}
			break;

		default:
			break;
		}//switch
	}//while

}
