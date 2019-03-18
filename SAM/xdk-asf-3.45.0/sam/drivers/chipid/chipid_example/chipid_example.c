/**
 * \file
 *
 * \brief Chip Identifier (CHIPID) example for SAM.
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


/**
 * \mainpage CHIPID Example
 * 
 * \par Purpose
 *
 * The CHIPID Example will help new users get familiar with Atmel's SAM
 * microcontrollers. This example application shows how to read chip Id
 * information data.
 *
 * \par Requirements
 *
 * This example can be used on any SAM3/4 boards and SAMV71 Xplained Ultra board.
 *
 * \par Description
 *
 * The example program reads Chip ID information and dump these information
 * to debug console.
 *
 * \par Usage
 *
 * -# Build the program and download it inside the evaluation board.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear
 *    (values depend on the board and chip used):
 *    \code
	-- CHIPID Example --
	-- xxxxx-xx
	-- Compiled: xxx xx xxxx xx:xx:xx --
	Version                                   0x0.
	Embedded Processor                        Cortex-xx.
	Nonvolatile program memory size           xxx bytes.
	Second nonvolatile program memory size    None.
	Internal SRAM size                        xxx bytes.
	Architecture identifier                   xxxxxxxx Series.
	Nonvolatile program memory type           Embedded Flash Memory.
	...
\endcode
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <string.h>
#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
extern "C" {
#endif
/**INDENT-ON**/
/// @endcond

#define STRING_EOL    "\r"
#define STRING_HEADER "-- CHIPID Example --\r\n" \
		"-- "BOARD_NAME" --\r\n" \
		"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

//! Chip ID catalog information: Type ID and its description stream
typedef struct chipidtype {

	/// Identifier
	uint32_t num;
	/// Type
	uint8_t  p_str[80];
} chipidtype_t;

//! Number of Embedded Processors Supported
#define CHIPID_EPROC_SIZE    7
//! Embedded Processors support list
const chipidtype_t chipid_eproc[CHIPID_EPROC_SIZE] = {

	// identifier       description
	{0x1,               "ARM946ES"},
	{0x2,               "ARM7TDMI"},
	{0x3,               "Cortex-M3"},
	{0x4,               "ARM920T"},
	{0x5,               "ARM926EJS"},
	{0x6,               "Cortex-A5"},
	{0x7,               "Cortex-M4"}
};

//! Number of 1st Non-Volatile Program Memories Supported
#define CHIPID_NVPSIZE_SIZE    16
//! 1st Non-Volatile Program Memories support list
const chipidtype_t chipid_nvpsize[CHIPID_NVPSIZE_SIZE] = {

	// identifier       description
	{0x0,               "None"},
	{0x1,               "8K bytes"},
	{0x2,               "16K bytes"},
	{0x3,               "32K bytes"},
	{0x4,               "Reserved"},
	{0x5,               "64K bytes"},
	{0x6,               "Reserved"},
	{0x7,               "128K bytes"},
	{0x8,               "Reserved"},
	{0x9,               "256K bytes"},
	{0xA,               "512K bytes"},
	{0xB,               "Reserved"},
	{0xC,               "1024K bytes"},
	{0xD,               "Reserved"},
	{0xE,               "2048K bytes"},
	{0xF,               "Reserved"}
};

//! Number of 2nd Non-Volatile Program Memories Supported
#define CHIPID_NVPSIZE2_SIZE    16
//! 2nd Non-Volatile Program Memories support list
const chipidtype_t chipid_nvpsize2[CHIPID_NVPSIZE2_SIZE] = {

	// identifier       description
	{0x0,               "None"},
	{0x1,               "8K bytes"},
	{0x2,               "16K bytes"},
	{0x3,               "32K bytes"},
	{0x4,               "Reserved"},
	{0x5,               "64K bytes"},
	{0x6,               "Reserved"},
	{0x7,               "128K bytes"},
	{0x8,               "Reserved"},
	{0x9,               "256K bytes"},
	{0xA,               "512K bytes"},
	{0xB,               "Reserved"},
	{0xC,               "1024K bytes"},
	{0xD,               "Reserved"},
	{0xE,               "2048K bytes"},
	{0xF,               "Reserved"}
};

//! Number of SRAMs Supported
#define CHIPID_SRAMSIZE_SIZE    16
//! SRAMs support list
const chipidtype_t chipid_sramsize[CHIPID_SRAMSIZE_SIZE] = {

	// identifier       description
	{0x0,               "48K bytes"},
	{0x1,               "192K bytes"},
	{0x2,               "384K bytes"},
	{0x3,               "6K bytes"},
	{0x4,               "112K bytes"},
	{0x5,               "4K bytes"},
	{0x6,               "80K bytes"},
	{0x7,               "160K bytes"},
	{0x8,               "8K bytes"},
	{0x9,               "16K bytes"},
	{0xA,               "32K bytes"},
	{0xB,               "64K bytes"},
	{0xC,               "128K bytes"},
	{0xD,               "256K bytes"},
	{0xE,               "96K bytes"},
	{0xF,               "512K bytes"}
};

//! Number of architectures Supported
#define CHIPID_ARCH_SIZE    47
//! Architectures support list
const chipidtype_t chipid_archsize[CHIPID_ARCH_SIZE] = {

	// identifier       description
	{0x10,              "ATSAME70 Series"},
	{0x11,              "ATSAMS70 Series"},
	{0x12,              "ATSAMV71 Series"},
	{0x13,              "ATSAMV70 Series"},
	{0x19,              "AT91SAM9xx Series"},
	{0x29,              "AT91SAM9XExx Series"},
	{0x34,              "AT91x34 series"},
	{0x37,              "CAP7 Series"},
	{0x39,              "CAP9 Series"},
	{0x3B,              "CAP11 Series"},
	{0x3C,              "SAM4E Series"},
	{0x40,              "AT91x40 Series"},
	{0x42,              "AT91x42 Series"},
	{0x43,              "AT91SAMG51 Series"},
	{0x44,              "AT91SAMG55 Series(49-lead version)"},
	{0x45,              "AT91SAMG55 Series(64-lead version)"},
	{0x46,              "AT91SAMG55 Series(100-lead version)"},
	{0x47,              "AT91SAMG53/SAMG54 Series"},
	{0x55,              "AT91x55 Series"},
	{0x60,              "AT91SAM7Axx Series"},
	{0x61,              "AT91SAM7AQxx Series"},
	{0x63,              "AT91x63 Series"},
	{0x64,              "SAM4CxC Series"},
	{0x70,              "AT91SAM7Sxx Series"},
	{0x71,              "AT91SAM7XCxx Series"},
	{0x72,              "AT91SAM7SExx Series"},
	{0x73,              "AT91SAM7Lxx Series"},
	{0x75,              "AT91SAM7Xxx Series"},
	{0x76,              "AT91SAM7SLxx Series"},
	{0x80,              "ATSAM3UxC Series"},
	{0x81,              "ATSAM3UxE Series"},
	{0x83,              "ATSAM3A/SAM4A xC Series"},
	{0x84,              "ATSAM3X/SAM4X xC Series"},
	{0x85,              "ATSAM3X/SAM4X xE Series"},
	{0x86,              "ATSAM3X/SAM4X xG Series"},
	{0x88,              "ATSAM3S/SAM4S xA Series"},
	{0x89,              "ATSAM3S/SAM4S xB Series"},
	{0x8A,              "ATSAM3S/SAM4S xC Series"},
	{0x92,              "AT91x92 Series"},
	{0x93,              "ATSAM3NxA/SAM4NxA Series"},
	{0x94,              "ATSAM3NxB/SAM4NxB Series"},
	{0x95,              "ATSAM3NxC/SAM4NxC Series"},
	{0x98,              "ATSAM3SD/SAM4SD xA Series"},
	{0x99,              "ATSAM3SD/SAM4SD xB Series"},
	{0x9A,              "ATSAM3SD/SAM4SD xC Series"},
	{0xA5,              "ATSAM5A Series"},
	{0xF0,              "AT75Cxx Series"}
};

//! Number of ROMs Supported
#define CHIPID_NVPTYPE_SIZE    5
//! ROMs support list
const chipidtype_t chipid_nvptype[CHIPID_NVPTYPE_SIZE] = {

	/* identifier       description */
	{0x0,               "ROM"},
	{0x1,               "ROMless or on-chip Flash"},
	{0x4,               "SRAM emulating ROM"},
	{0x2,               "Embedded Flash Memory"},
	{0x3,               "ROM and Embedded Flash Memory, NVPSIZ is ROM size, NVPSIZ2 is Flash size"}
};

//! ChipID data read
chipid_data_t g_chipid_data;

/**
 *  \brief The function finds chipid from specific list according to ul_id
 *  
 *  \param p_cid_types  Pointer to the chipid list.
 *  \param ul_size      chipid list size
 *  \param ul_id        chipid number
 *  \param p_cid_type   pointer to chipid type
 *  \return true if ID is found in list
 */
static bool chipid_find(const chipidtype_t *p_cid_types,
	uint32_t ul_size, uint32_t ul_id, chipidtype_t *p_cid_type)
{
	uint32_t ul_counter;

	for (ul_counter = 0; ul_counter < ul_size; ul_counter++) {
		if (p_cid_types[ul_counter].num == ul_id) {
			memcpy(p_cid_type, &p_cid_types[ul_counter], sizeof(chipidtype_t));
			return true;
		}
	}

	return false;
}

/**
 *  \brief The function prints specific chipid data structure.
 *  
 *  \param p_chipid_data  Pointer to the chipid data.
 */
static void chipid_print(chipid_data_t *p_chipid_data)
{
	bool b_found;
	chipidtype_t cid_type;

	/* Version */
	printf("Version\t0x%lx.\r\n", (unsigned long)p_chipid_data->ul_version);

	/* Find Embedded Processor */
	b_found = chipid_find(chipid_eproc, CHIPID_EPROC_SIZE,
			p_chipid_data->ul_eproc, &cid_type);
	if (b_found) {
		printf("Embedded Processor\t%s.\r\n", cid_type.p_str);
	}
	/* Find non-volatile program memory size */
	b_found = chipid_find(chipid_nvpsize, CHIPID_NVPSIZE_SIZE,
			p_chipid_data->ul_nvpsiz, &cid_type);
	if (b_found) {
		printf("Nonvolatile program memory size\t%s.\r\n", cid_type.p_str);
	}
	/* Find the second non-volatile program memory size */
	b_found = chipid_find(chipid_nvpsize2, CHIPID_NVPSIZE2_SIZE,
			p_chipid_data->ul_nvpsiz2, &cid_type);
	if (b_found) {
		printf("Second nonvolatile program memory size\t%s.\r\n",
			cid_type.p_str);
	}
	/* Find internal SRAM size */
	b_found = chipid_find(chipid_sramsize, CHIPID_SRAMSIZE_SIZE,
			p_chipid_data->ul_sramsiz, &cid_type);
	if (b_found) {
		printf("Internal SRAM size\t%s.\r\n", cid_type.p_str);
	}
	/* Find architecture identifier */
	b_found = chipid_find(chipid_archsize, CHIPID_ARCH_SIZE,
			p_chipid_data->ul_arch, &cid_type);
	if (b_found) {
		printf("Architecture identifier\t%s.\r\n", cid_type.p_str);
	}
	/* Find non-volatile program memory type */
	b_found = chipid_find(chipid_nvptype, CHIPID_NVPTYPE_SIZE,
			p_chipid_data->ul_nvptyp, &cid_type);
	if (b_found) {
		printf("Nonvolatile program memory type\t%s.\r\n", cid_type.p_str);
	}
	/* Find extension flag */
	if (p_chipid_data->ul_extflag) {
		printf("Extended chip ID is\t0x%lx. \r\n",
			(unsigned long)p_chipid_data->ul_extid);
	} else {
		puts("Extended chip ID does not exist. \r");
	}

}

/**
 *  \brief Configure UART console.
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

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
}

/**
 *  \brief  Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Initialize the system */
	sysclk_init();
	board_init();

	/* Initialize the console uart */
	configure_console();

	puts(STRING_HEADER);
	
	/* Read CHIPID */
	chipid_read(CHIPID, &g_chipid_data);
	/* Dump CHIPID information */
	chipid_print(&g_chipid_data);

	while (1) {
	}
}

/// @cond 0
/**INDENT-OFF**/
#ifdef __cplusplus
}
#endif
/**INDENT-ON**/
/// @endcond
