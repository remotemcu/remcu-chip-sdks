/**
 * \file
 *
 * \brief Tic Tac Toe application for SAM Xplained Pro with OLED1 Xplained Pro
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
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * \mainpage SAM Tic-Tac-Toe Example
 * See \ref appdoc_sam0_tictactoe_main "here" for project documentation.
 * \copydetails appdoc_preface
 *
 * \page appdoc_preface Overview
 * This application demonstrates the use of the OLED1 Xplained Pro extension
 * board for the SAM Xplained Pro with a Tic-tac-toe game.
 */

 /**
 * \page appdoc_sam0_tictactoe_main SAM Tic-Tac-Toe Example
 * Overview:
 * - \ref appdoc_sam0_tictactoe_intro
 * - \ref appdoc_sam0_tictactoe_setup
 * - \ref appdoc_sam0_tictactoe_compinfo
 * - \ref appdoc_sam0_tictactoe_contactinfo
 *
 * \section  appdoc_sam0_tictactoe_intro Introduction
 * This application demonstrates the use of the OLED1 Xplained Pro extension
 * board for the SAM Xplained Pro with a tic-tac-toe game.
 *
 * The game is controlled with the three mechanical buttons on the OLED1
 * Xplained Pro. The goal is to get three circles in a horizontal, diagonal or
 * vertical row, before the opponent (SAM devices) gets three crosses
 * in a row.
 *
 * This application has been tested on following boards:
 * - SAM D20/D21/R21/L21/L22/R30 Xplained Pro
 *
 * \section appdoc_sam0_tictactoe_setup Hardware Setup
 * The OLED1 Xplained Pro extension board must be connected to extension
 * header 3 on the SAM D20/D21/L21/L22 Xplained Pro, and extension header 1 on the SAM
 * R21/R30 Xplained Pro.
 * To use another extension header, edit the configuration in:
 * - \ref conf_board.h
 * - \ref conf_ssd1306.h
 * On the board of SAM D21 Xplained Pro, the PA03 Select jumper should be
 * connected to EXT3 to make the Button 3 of the OLED1 extension board
 * taking effect.
 *
 * \section appdoc_sam0_tictactoe_compinfo Compilation Info
 * This software was written for the GNU GCC and IAR for ARM.
 * Other compilers may or may not work.
 *
 * \section appdoc_sam0_tictactoe_contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.microchip.com">http://www.microchip.com</a>.
 */

/* Size of a square */
#define SQUARE_SIZE  (LCD_HEIGHT_PIXELS / 3)

/* Size of a cross */
#define CROSS_SIZE  (SQUARE_SIZE / 3)
/* Size of a circle */
#define CIRCLE_SIZE (SQUARE_SIZE / 4)

/* Square coordinates */
#define SQUARE0_X 0
#define SQUARE0_Y 0
#define SQUARE1_X (SQUARE0_X + SQUARE_SIZE)
#define SQUARE1_Y SQUARE0_Y
#define SQUARE2_X (SQUARE1_X + SQUARE_SIZE)
#define SQUARE2_Y SQUARE0_Y
#define SQUARE3_X SQUARE0_X
#define SQUARE3_Y (SQUARE0_Y + SQUARE_SIZE)
#define SQUARE4_X SQUARE1_X
#define SQUARE4_Y SQUARE3_Y
#define SQUARE5_X SQUARE2_X
#define SQUARE5_Y SQUARE3_Y
#define SQUARE6_X SQUARE0_X
#define SQUARE6_Y (SQUARE3_Y + SQUARE_SIZE)
#define SQUARE7_X SQUARE1_X
#define SQUARE7_Y SQUARE6_Y
#define SQUARE8_X SQUARE2_X
#define SQUARE8_Y SQUARE6_Y

/* Number of squares */
#define NUMBER_OF_SQUARES 9

/* X coordinate of strings */
#define STRING_X (SQUARE2_X + SQUARE_SIZE*2)

/* Length of strings */
#define STRING_LENGTH 20

/* X and Y coordinates for squares */
const uint8_t square_coord[9][2] = {
		{SQUARE0_X, SQUARE0_Y,},
		{SQUARE1_X, SQUARE1_Y,},
		{SQUARE2_X, SQUARE2_Y,},
		{SQUARE3_X, SQUARE3_Y,},
		{SQUARE4_X, SQUARE4_Y,},
		{SQUARE5_X, SQUARE5_Y,},
		{SQUARE6_X, SQUARE6_Y,},
		{SQUARE7_X, SQUARE7_Y,},
		{SQUARE8_X, SQUARE8_Y,},
};

/* Enum for the different buttons */
enum button {
	BUTTON_1,
	BUTTON_2,
	BUTTON_3,
	BUTTON_NONE,
};

/* Enum for the different players */
enum player {
	NONE,
	USER,
	COMPUTER,
};

/* Occupied squares */
enum player occupied_squares[3][3];

/* Variable to mark number of wins */
uint16_t wins = 0;

/* Variable to mark number of games */
uint16_t games = 0;

/* String to display number of wins */
char win_string[STRING_LENGTH];

/**
 * \brief Draws the Tic-tac-toe board on the display
 *
 */
static void setup_board(void)
{
	/* Clear screen */
	gfx_mono_draw_filled_rect(0, 0, LCD_WIDTH_PIXELS, LCD_HEIGHT_PIXELS,
			GFX_PIXEL_CLR);

	/* Draw vertical lines */
	gfx_mono_draw_line(SQUARE_SIZE, 0, SQUARE_SIZE, SQUARE_SIZE * 3,
			GFX_PIXEL_SET);
	gfx_mono_draw_line(SQUARE_SIZE * 2, 0, SQUARE_SIZE * 2, SQUARE_SIZE * 3,
			GFX_PIXEL_SET);

	/* Draw horizontal lines */
	gfx_mono_draw_line(0, SQUARE_SIZE, SQUARE_SIZE*3, SQUARE_SIZE,
			GFX_PIXEL_SET);
	gfx_mono_draw_line(0, SQUARE_SIZE * 2, SQUARE_SIZE * 3, SQUARE_SIZE * 2,
			GFX_PIXEL_SET);

	/* Print number of games */
	snprintf(win_string, STRING_LENGTH, "Games: %d", games);
	gfx_mono_draw_string(win_string, STRING_X, SQUARE0_Y, &sysfont);

	/* Print number of wins */
	snprintf(win_string, STRING_LENGTH, "Wins: %d", wins);
	gfx_mono_draw_string(win_string, STRING_X, SQUARE3_Y, &sysfont);

	/* Clear occupied squares */
	for (uint8_t i = 0; i < 3; i++) {
		for (uint8_t j = 0; j < 3; j++) {
			occupied_squares[i][j] = NONE;
		}
	}
}

/**
 * \brief Gets button push
 */
static enum button get_button(void)
{
	if (port_pin_get_input_level(WING_BUTTON_1) == false) {
		/* Wait for button to be released */
		while(!port_pin_get_input_level(WING_BUTTON_1)) {
		}
		return BUTTON_1;
	} else if (port_pin_get_input_level(WING_BUTTON_2) == false) {
		/* Wait for button to be released */
		while(!port_pin_get_input_level(WING_BUTTON_2)) {
		}
		return BUTTON_2;
	} else if (port_pin_get_input_level(WING_BUTTON_3) == false) {
		/* Wait for button to be released */
		while(!port_pin_get_input_level(WING_BUTTON_3)) {
		}
		return BUTTON_3;
	} else {
		/* No button pushed */
		return BUTTON_NONE;
	}
}

/**
 * \brief Initializes the display with explanatory text for the buttons
 */
static void init_display(void)
{
	/* Draw buttons */
	gfx_mono_draw_circle(10, SQUARE3_Y, CIRCLE_SIZE, GFX_PIXEL_SET, GFX_WHOLE);
	gfx_mono_draw_circle((LCD_WIDTH_PIXELS / 3) + 10, SQUARE3_Y, CIRCLE_SIZE,
			GFX_PIXEL_SET, GFX_WHOLE);
	gfx_mono_draw_circle((LCD_WIDTH_PIXELS / 3) * 2 + 10, SQUARE3_Y,
			CIRCLE_SIZE, GFX_PIXEL_SET, GFX_WHOLE);

	/* Print text */
	gfx_mono_draw_string("LEFT", 0, SQUARE6_Y, &sysfont);
	gfx_mono_draw_string("OK", (LCD_WIDTH_PIXELS / 3), SQUARE6_Y, &sysfont);
	gfx_mono_draw_string("RIGHT", (LCD_WIDTH_PIXELS / 3) * 2, SQUARE6_Y,
			&sysfont);
}

/**
 * \brief Draws a cross in selected square
 */
static void draw_cross(uint8_t square_num)
{
	uint8_t x = square_coord[square_num][0] + SQUARE_SIZE / 4;
	uint8_t y = square_coord[square_num][1] + SQUARE_SIZE / 4;

	/* Draw cross in selected square */
	gfx_mono_draw_line(x, y, x + CROSS_SIZE, y + CROSS_SIZE, GFX_PIXEL_SET);
	gfx_mono_draw_line(x + CROSS_SIZE, y, x, y + CROSS_SIZE, GFX_PIXEL_SET);
}

/**
 * \brief Draws a circle at selected point
 */
static void draw_circle(uint8_t square_num)
{
	uint8_t x = square_coord[square_num][0] + SQUARE_SIZE / 4;
	uint8_t y = square_coord[square_num][1] + SQUARE_SIZE / 4;
	/* Draw circle in selected square */
	gfx_mono_draw_circle(x + CIRCLE_SIZE, y + CIRCLE_SIZE, CIRCLE_SIZE,
			GFX_PIXEL_SET, GFX_WHOLE);
}

/**
 * \brief Highlights a square
 */
static void highlight_square(uint8_t square_num)
{
	static uint8_t last_square = 0;

	/* Clear current highlighting */
	uint8_t x = square_coord[last_square][0];
	uint8_t y = square_coord[last_square][1];
	gfx_mono_draw_rect(x + 1, y + 1, SQUARE_SIZE - 2, SQUARE_SIZE - 2,
			GFX_PIXEL_CLR);

	last_square = square_num;

	/* Highlight new square */
	x = square_coord[square_num][0];
	y = square_coord[square_num][1];
	gfx_mono_draw_rect(x + 1, y + 1, SQUARE_SIZE - 2, SQUARE_SIZE - 2,
			GFX_PIXEL_SET);
}

/**
 * \brief User turn
 * Waits for the user to push buttons and select a new square
 */
static void user_turn(void)
{
	static uint8_t square_num = 0;
	enum button button_pushed;
	highlight_square(square_num);

	while (true) {

		/* Wait for button interaction */
		do {
			button_pushed = get_button();
		} while (button_pushed == BUTTON_NONE);

		switch (button_pushed) {
		case BUTTON_1:
			/* Left */
			if (square_num > 0) {
				square_num--;
				highlight_square(square_num);
			}
			break;
		case BUTTON_2:
			if (occupied_squares[square_num / 3][square_num % 3] == NONE) {
				/* Select square and draw circle */
				occupied_squares[square_num / 3][square_num % 3] = USER;
				draw_circle(square_num);
				return;
			}
			/* Do not break, skip to next square */
		case BUTTON_3:
			/* Right */
			if (square_num < 8) {
				square_num++;
				highlight_square(square_num);
			}
			break;
		default:
			break;
		}
	}
}

/**
 * \brief Checks for winner
 *
 * \return Enum to say if there is a winner or not.
 * \retval NONE No winner
 * \retval COMPUTER Opponent won
 * \retval USER User won
 */
static uint8_t we_have_a_winner(void)
{
	uint8_t winner = 0;

	if (occupied_squares[0][0] == occupied_squares[0][1] &&
			occupied_squares[0][1] == occupied_squares[0][2] &&
			occupied_squares[0][0] != NONE) {

		/* Three in a row on top row */
		winner = occupied_squares[0][0];
	} else if (occupied_squares[0][0] == occupied_squares[1][0] &&
			occupied_squares[1][0] == occupied_squares[2][0] &&
			occupied_squares[0][0] != NONE) {

		/* Three in a row on first vertical row */
		winner = occupied_squares[0][0];
	} else if (occupied_squares[0][0] == occupied_squares[1][1] &&
			occupied_squares[1][1] == occupied_squares[2][2] &&
			occupied_squares[0][0] != NONE) {

		/* Three in a row on diagonal */
		winner = occupied_squares[0][0];
	} else if (occupied_squares[0][1] == occupied_squares[1][1] &&
			occupied_squares[1][1] == occupied_squares[2][1] &&
			occupied_squares[0][1] != NONE) {
		/* Three in a row on second vertical row */
		winner = occupied_squares[0][1];
	} else if (occupied_squares[0][2] == occupied_squares[1][2] &&
			occupied_squares[1][2] == occupied_squares[2][2] &&
			occupied_squares[0][2] != NONE) {

		/* Three in a row on third vertical row */
		winner = occupied_squares[0][2];
	} else if (occupied_squares[1][0] == occupied_squares[1][1] &&
			occupied_squares[1][1] == occupied_squares[1][2] &&
			occupied_squares[1][0] != NONE) {

		/* Three in a row on second row */
		winner = occupied_squares[1][0];
	} else if (occupied_squares[2][0] == occupied_squares[2][1] &&
			occupied_squares[2][1] == occupied_squares[2][2] &&
			occupied_squares[2][0] != NONE) {

		/* Three in a row on third row */
		winner = occupied_squares[2][0];
	} else if (occupied_squares[0][2] == occupied_squares[1][1] &&
			occupied_squares[1][1] == occupied_squares[2][0] &&
			occupied_squares[0][2] != NONE) {

		/* Three in a row on diagonal */
		winner = occupied_squares[0][2];
	}
	/* Return winner or NONE */
	return winner;
}

/**
 * \brief Selects a random, unoccupied square
 */
static void opponent_turn(void)
{
	uint8_t square_num;

	do {
		square_num = rand() % 9;
	} while (occupied_squares[square_num / 3][square_num % 3]);

	occupied_squares[square_num / 3][square_num % 3] = COMPUTER;
	draw_cross(square_num);
}

/**
 * \brief Configures buttons
 */
static void init_buttons(void)
{
	struct port_config conf;
	port_get_config_defaults(&conf);

	conf.direction = PORT_PIN_DIR_INPUT;
	conf.input_pull = PORT_PIN_PULL_UP;

	/* Configure all three buttons as inputs */
	port_pin_set_config(WING_BUTTON_1, &conf);
	port_pin_set_config(WING_BUTTON_2, &conf);
	port_pin_set_config(WING_BUTTON_3, &conf);
}

/**
 * \brief Main entry of example application
 */
int main(void)
{
	/* Variable to store the last winner */
	uint8_t winner;

	system_init();
	delay_init();
	gfx_mono_init();

	init_buttons();
	init_display();

	/* Start game */
	while (true) {
		winner = 0;
		/* Wait for button interaction */
		while (get_button() == BUTTON_NONE) {
		}
		/* Draw empty board */
		setup_board();

		/* Start playing */
		for (int i = 0; i < 5; i++) {
			/* User's turn */
			user_turn();

			/* Check if the game is over */
			winner = we_have_a_winner();
			if (winner || i == 4) {
				break;
			}

			/* Add a delay for the opponent to "think" */
			delay_ms(500);
			/* Opponent's turn */
			opponent_turn();

			/* Check if the game is over */
			winner = we_have_a_winner();
			if (winner) {
				break;
			}
		}

		/* Game over, print winner and get ready for restart */
		if (winner == 1) {
			/* User won */
			gfx_mono_draw_string("You won!", STRING_X, 0, &sysfont);
			wins++;
		} else if (winner == 2) {
			gfx_mono_draw_string("You lost!", STRING_X, 0, &sysfont);
		} else {
			gfx_mono_draw_string("No winner!", STRING_X, 0, &sysfont);
		}

		gfx_mono_draw_string("Press a button", STRING_X, SQUARE3_Y, &sysfont);
		games++;
	}
}
