/**
 * \file
 *
 * \brief Board specific definition for low power example.
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

#ifndef LOW_POWER_BOARD_H_INCLUDED
#define LOW_POWER_BOARD_H_INCLUDED

/**
 * Push button definitions for sleep mode and active mode
 * @{
 */
#define PIN_PUSHBUTTON_WAKEUP_PIO    PIOA
#define PIN_PUSHBUTTON_WAKEUP_MASK   PIO_PA2
#define PIN_PUSHBUTTON_WAKEUP_ID     ID_PIOA
#define PIN_PUSHBUTTON_WAKEUP_ATTR   PIO_DEFAULT
/** @} */

/** Wakeup pin for wait mode: SW0 */
#define WAKEUP_WAIT_INPUT_ID    (1u << 2)
/** Wakeup pin for backup mode: Touchscreen controller IRQ pin */
#define WAKEUP_BACKUP_INPUT_ID  (1u << 2)

/** Hint message for active mode */
#define STRING_ACTIVE \
		"Entering active mode:\n\r" \
		"- Press SW0 button to go out.\n\r"

/** Hint message for sleep mode */
#define STRING_SLEEP \
		"Enter into sleep mode.\n\r" \
		"- Press SW0 button to wake up.\n\r"

/** Hint message for wait mode */
#define STRING_WAIT \
		"Entering wait mode:\n\r" \
		"- Switching to 8MHz Fast RC oscillator and stop PLL.\n\r" \
		"- Press SW0 button to wake up.\n\r"

/** Hint message for backup mode */
#define STRING_BACKUP \
		"Enter into backup mode.\n\r" \
		"- Press SW0 button to wake up.\n\r"

#define CLOCK_LIST_MENU \
		"\n\rSelect one of the following clock configurations:\n\r" \
		"  1: 250KHz from Fast RC\n\r"                     \
		"  2: 500KHz from Fast RC\n\r"                     \
		"  3: 1MHz from Fast RC\n\r"                       \
		"  4: 2MHz from Fast RC\n\r"                       \
		"  5: 4MHz from Fast RC\n\r"                       \
		"  6: 8MHz from Fast RC\n\r"                       \
		"  7: 16MHz from Fast RC\n\r"                      \
		"  8: 24MHz from Fast RC\n\r"                      \
		"  a: 48MHz from PLL clock\n\r"                    \
		"  b: 96MHz from PLL clock\n\r"                    \

#define MIN_CLOCK_FAST_RC_ITEM '1'
#define MAX_CLOCK_FAST_RC_ITEM '8'
#define MIN_CLOCK_PLL_ITEM     'a'
#define MAX_CLOCK_PLL_ITEM     'b'

#define example_set_wakeup_from_backup_mode() \
	supc_set_wakeup_inputs(SUPC, WAKEUP_BACKUP_INPUT_ID, \
			0)

extern uint32_t g_fastrc_clock_list[][3];
extern uint32_t g_pll_clock_list[][4];

#define PLL_DEFAULT_MUL  1465
#define PLL_DEFAULT_DIV  1
#define MCK_DEFAULT_DIV  PMC_MCKR_PRES_CLK_1

void init_specific_board(void);

#endif /* LOW_POWER_BOARD_H_INCLUDED */
