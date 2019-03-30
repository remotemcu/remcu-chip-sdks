/*
 * Copyright (C) 2018 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

#include <xmc_common.h>
#include <xmc_gpio.h>

#include "serial.h"
#include "shell.h"

#define LED1 P0_0

void led_cmd(int32_t argc, char **argv)
{
  if (argc == 2)
  {
	if (strcmp(argv[1], "on") == 0)
	{
	  XMC_GPIO_SetOutputLow(LED1);
	}
	else if (strcmp(argv[1], "off") == 0)
	{
	  XMC_GPIO_SetOutputHigh(LED1);
	}
	else
	{
	  shell_println("Argument not supported");
	}
  }
}

void help_cmd(int32_t argc, char **argv)
{
  (void)argc;
  (void)argv;

  shell_help();
}

const shell_command_t cmd_table[] =
{
  {"help", 0u, 0u, help_cmd, "Display this help message", ""},
  {"led", 1u, 1u, led_cmd, "Led control", "<on|off>"},
  {0, 0u, 0u, 0, 0, 0}
};

void my_shell_init(void)
{
  const char DELIMITER_STR[] = "************************************************";

  shell_println("\r\n%s", DELIMITER_STR);
  shell_println(" %s", "Shell Application");
  shell_println(DELIMITER_STR);
  shell_println(" Version %s", "1.0.0");
  shell_println(" Built %s", __DATE__ " at " __TIME__);

  shell_println("\n Enter 'help' for command list.");
  shell_println("%s\n", DELIMITER_STR);

}

int main(void)
{
  XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
  XMC_GPIO_SetOutputHigh(LED1);

  serial_init();

  shell_init(cmd_table, my_shell_init);

  while (1)
  {
    shell_state_machine();
  }
}
