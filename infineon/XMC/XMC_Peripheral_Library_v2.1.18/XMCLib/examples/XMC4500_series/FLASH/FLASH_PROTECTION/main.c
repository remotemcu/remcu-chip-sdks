#include <xmc_common.h>
#include <xmc_scu.h>
#include <xmc_flash.h>
#include <xmc_gpio.h>

#include "serial.h"
#include "shell.h"

#define LED1 P3_9

void flash_protection_cmd(int32_t argc, char **argv)
{
  if (argc == 2)
  {
	if (strcmp(argv[1], "on") == 0)
	{
	  XMC_FLASH_ResumeProtection();
	  shell_println("Protection re-enabled");
	}
	else if (strcmp(argv[1], "off") == 0)
	{
	  if (XMC_FLASH_VerifyReadProtection(0xdeadbeef, 0xcafecafe))
	  {
	    shell_println("Protection disabled");
	  }
	  else
	  {
	    shell_println("ERROR: A problem occur while disabling the read protection!!");
	  }
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
  {"protection", 1u, 1u, flash_protection_cmd, "Disables/reenables global read protection", "<on|off>"},
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

  if ((XMC_FLASH_GetStatus() & XMC_FLASH_STATUS_PROTECTION_INSTALLED) == 0)
  {
	/* if no protection is installed */
	XMC_FLASH_EraseUCB(XMC_FLASH_UCB0);
	XMC_FLASH_InstallProtection(0, XMC_FLASH_PROTECTION_READ_GLOBAL, 0xdeadbeef, 0xcafecafe);
    XMC_FLASH_ConfirmProtection(0);

    XMC_SCU_RESET_ClearDeviceResetReason();
    NVIC_SystemReset();
  }

  serial_init();

  shell_init(cmd_table, my_shell_init);

  while (1)
  {
    shell_state_machine();
  }
}
