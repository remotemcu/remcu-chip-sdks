#ifndef BOARD_HPP
#define BOARD_HPP

#include <fsl_clock.h>
#include <fsl_common.h>
#include <fsl_debug_console.h>
#include <fsl_gpio.h>
#include <fsl_port.h>

#define LED_RED_GPIO GPIOB
#define LED_RED_GPIO_PORT PORTB
#define LED_RED_GPIO_PIN 22

#define LED_GREEN_GPIO GPIOE
#define LED_GREEN_GPIO_PORT PORTE
#define LED_GREEN_GPIO_PIN 26

#define LED_BLUE_GPIO GPIOB
#define LED_BLUE_GPIO_PORT PORTB
#define LED_BLUE_GPIO_PIN 21

namespace board {

void initLeds();
void initDebugConsole();

} /* namespace board */

#endif /* BOARD_HPP */
