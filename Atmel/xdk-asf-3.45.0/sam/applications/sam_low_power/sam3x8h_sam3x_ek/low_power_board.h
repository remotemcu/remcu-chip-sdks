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
 * Push button definitions for wakeup.
 * @{
 */
#define PIN_PUSHBUTTON_WAKEUP_PIO   PIN_PUSHBUTTON_2_PIO
#define PIN_PUSHBUTTON_WAKEUP_MASK  PIN_PUSHBUTTON_2_MASK
#define PIN_PUSHBUTTON_WAKEUP_ID    PIN_PUSHBUTTON_2_ID
#define PIN_PUSHBUTTON_WAKEUP_ATTR  PIN_PUSHBUTTON_2_ATTR
/** @} */

/** Wakeup pin for wait mode: RIGHT CLICK */
#define WAKEUP_WAIT_INPUT_ID     (1u << 14)

/** Wakeup pin for backup mode: RIGHT CLICK */
#define WAKEUP_BACKUP_INPUT_ID   (1u << 14)

/** Hint message for active mode */
#define STRING_ACTIVE \
		"Enter into active mode.\n\r" \
		"- Press RIGHT CLICK button to go out.\n\r"

/** Hint message for sleep mode */
#define STRING_SLEEP \
		"Enter into sleep mode.\n\r" \
		"- Press RIGHT CLICK button to wake up.\n\r"

/** Hint message for wait mode */
#define STRING_WAIT \
		"Enter into wait mode.\n\r" \
		"- Switch to 4MHz Fast RC oscillator, PLL stopped.\n\r" \
		"- Press RIGHT CLICK button to wake up.\n\r"

/** Hint message for backup mode */
#define STRING_BACKUP \
		"Enter into backup mode.\n\r" \
		"- Press RIGHT CLICK button to wake up.\n\r"

/** Internal Flash Controller 0. */
#define EFC     EFC0

#define CLOCK_LIST_MENU \
		"\n\rSelect one of the following clock configurations:\n\r" \
		"  1: 125KHz from Fast RC\n\r"                     \
		"  2: 250KHz from Fast RC\n\r"                     \
		"  3: 500KHz from Fast RC\n\r"                     \
		"  4: 1MHz from Fast RC\n\r"                       \
		"  5: 2MHz from Fast RC\n\r"                       \
		"  6: 4MHz from Fast RC\n\r"                       \
		"  7: 8MHz from Fast RC\n\r"                       \
		"  8: 12MHz from Fast RC\n\r"                      \
		"  a: 24MHz from PLL clock\n\r"                    \
		"  b: 32MHz from PLL clock\n\r"                    \
		"  c: 48MHz from PLL clock\n\r"                    \
		"  d: 60MHz from PLL clock\n\r"                    \
		"  e: 72MHz from PLL clock\n\r"                    \
		"  f: 84MHz from PLL clock\n\r"

#define MIN_CLOCK_FAST_RC_ITEM '1'
#define MAX_CLOCK_FAST_RC_ITEM '8'
#define MIN_CLOCK_PLL_ITEM     'a'
#define MAX_CLOCK_PLL_ITEM     'f'

extern uint32_t g_fastrc_clock_list[][3];
extern uint32_t g_pll_clock_list[][4];

void init_specific_board(void);

#endif /* LOW_POWER_BOARD_H_INCLUDED */
