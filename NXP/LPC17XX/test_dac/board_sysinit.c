/*
 * @brief NXP LPC1769 LPCXpresso Sysinit file
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"

/* The System initialization code is called prior to the application and
   initializes the board for run-time operation. Board initialization
   includes clock setup and default pin muxing configuration. */

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* Pin muxing configuration */
STATIC const PINMUX_GRP_T pinmuxing[] = {
	{0,  0,   IOCON_MODE_INACT | IOCON_FUNC2},	/* TXD3 */
	{0,  1,   IOCON_MODE_INACT | IOCON_FUNC2},	/* RXD3 */
	{0,  4,   IOCON_MODE_INACT | IOCON_FUNC2},	/* CAN-RD2 */
	{0,  5,   IOCON_MODE_INACT | IOCON_FUNC2},	/* CAN-TD2 */
	{0,  22,  IOCON_MODE_INACT | IOCON_FUNC0},	/* Led 0 */
	{0,  24,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ADC 1 */
	{0,  25,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ADC 2 */
	//{0,  26,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ADC 3 */
	{0,  26,  IOCON_MODE_INACT | IOCON_FUNC2},	/* DAC */

	/* ENET */
	{0x1, 0,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_TXD0 */
	{0x1, 1,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_TXD1 */
	{0x1, 4,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_TX_EN */
	{0x1, 8,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_CRS */
	{0x1, 9,  IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_RXD0 */
	{0x1, 10, IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_RXD1 */
	{0x1, 14, IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_RX_ER */
	{0x1, 15, IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_REF_CLK */
	{0x1, 16, IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_MDC */
	{0x1, 17, IOCON_MODE_INACT | IOCON_FUNC1},	/* ENET_MDIO */
	{0x1, 27, IOCON_MODE_INACT | IOCON_FUNC1},	/* CLKOUT */

	/* Joystick buttons. */
	{2, 3,  IOCON_MODE_INACT | IOCON_FUNC0},	/* JOYSTICK_UP */
	{0, 15, IOCON_MODE_INACT | IOCON_FUNC0},	/* JOYSTICK_DOWN */
	{2, 4,  IOCON_MODE_INACT | IOCON_FUNC0},	/* JOYSTICK_LEFT */
	{0, 16, IOCON_MODE_INACT | IOCON_FUNC0},	/* JOYSTICK_RIGHT */
	{0, 17, IOCON_MODE_INACT | IOCON_FUNC0},	/* JOYSTICK_PRESS */

};

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Sets up system pin muxing */
void Board_SetupMuxing(void)
{
	Chip_IOCON_SetPinMuxing(LPC_IOCON, pinmuxing, sizeof(pinmuxing) / sizeof(PINMUX_GRP_T));
}

/* Setup system clocking */
void Board_SetupClocking(void)
{
	Chip_SetupXtalClocking();

	/* Setup FLASH access to 4 clocks (100MHz clock) */
	Chip_SYSCTL_SetFLASHAccess(FLASHTIM_100MHZ_CPU);
}

/* Set up and initialize hardware prior to call to main */
void Board_SystemInit(void)
{
	Board_SetupMuxing();
	Board_SetupClocking();
}
