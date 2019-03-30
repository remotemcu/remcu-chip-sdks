#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <strings.h>
#include <stdarg.h>
#include "shell.h"

#define SHELL_ERR_SYNTAX   ("Error: Invalid syntax for: %s")
#define SHELL_ERR_CMD      ("Error: No such command: %s")

#define SHELL_BACKSPACE    ((char)(0x08))  /* Backspace. */
#define SHELL_DELETE       ((char)(0x7F))  /* Delete. */
#define SHELL_CTRLC        ((char)(0x03))  /* Ctrl + C. */
#define SHELL_CR           ((char)(0x0D))  /* CR. */
#define SHELL_LF           ((char)(0x0A))  /* LF. */
#define SHELL_ESC          ((char)(0x1B))  /* Esc. */
#define SHELL_SPACE        ((char)(0x20))  /* Space. */

typedef enum SHELL_STATE
{
  SHELL_STATE_INIT,              /* The Shell service is not initialized. */
  SHELL_STATE_GET_USER_INPUT,    /* The Shell service is accepting user commnads. */
  SHELL_STATE_EXEC_CMD,          /* The Shell service is executing user commnads. */
  SHELL_STATE_END_CMD            /* The Shell service finished command execution. */
} SHELL_STATE_t;

static const shell_command_t *shell_cmd_table;
static SHELL_STATE_t shell_state;
static uint32_t shell_cmdline_pos;
static char shell_cmdline[SHELL_CMDLINE_SIZE];

int32_t shell_println(const char *format, ... )
{
  int32_t result;
  va_list ap;

  va_start(ap, format);
  result = vprintf(format, ap);
  result += printf("\r\n"); /* Add new line.*/

  return result;
}

static int32_t shell_make_argv(char *cmdline, char *argv[])
{
  int32_t argc = 0;
  int32_t i;
  bool in_text_flag = false;

  if ((cmdline != NULL) && (argv != NULL))
  {
    for (i = 0u; cmdline[i] != '\0'; ++i)
    {
      if (cmdline[i] == ' ')
      {
        in_text_flag = false;
        cmdline[i] = '\0';
      }
      else
      {
        if (argc < SHELL_ARGS_MAX)
        {
          if (in_text_flag == false)
          {
            in_text_flag = true;
            argv[argc] = &cmdline[i];
            argc++;
          }
        }
        else /* Return argc.*/
        {
          break;
        }
      }
    }

    argv[argc] = 0;
  }

  return argc;
}

void shell_state_machine(void)
{
  char *argv[SHELL_ARGS_MAX + 1u]; /* One extra for 0 terminator.*/
  int32_t argc;
  int32_t ch;

  switch (shell_state)
  {
    case SHELL_STATE_INIT:
      printf("%s", SHELL_PROMPT);
      shell_state = SHELL_STATE_GET_USER_INPUT;
      break;

    case SHELL_STATE_GET_USER_INPUT:
      if ((ch = getchar()) != EOF)
      {
        if (((char)ch != SHELL_CR) && (shell_cmdline_pos < SHELL_CMDLINE_SIZE))
        {
          switch(ch)
          {
            case SHELL_BACKSPACE:
            case SHELL_DELETE:
            if (shell_cmdline_pos > 0U)
            {
              shell_cmdline_pos -= 1U;
              putchar(SHELL_BACKSPACE);
              putchar(' ');
              putchar(SHELL_BACKSPACE);
            }
            break;

            default:
              if ((shell_cmdline_pos + 1U) < SHELL_CMDLINE_SIZE)
              {
                /* Only printable characters. */
                if (((char)ch >= SHELL_SPACE) && ((char)ch <= SHELL_DELETE))
                {
                  shell_cmdline[shell_cmdline_pos] = (char)ch;
                  shell_cmdline_pos++;
                  putchar((char)ch);
                }
              }
              break;
          }
        }
        else
        {
          shell_cmdline[shell_cmdline_pos] = '\0';

          putchar(SHELL_CR);
          putchar(SHELL_LF);

          shell_state = SHELL_STATE_EXEC_CMD;
        }
      }
      break;

    case SHELL_STATE_EXEC_CMD:
      argc = shell_make_argv(shell_cmdline, argv);

      if (argc != 0)
      {
        const shell_command_t *cur_command = shell_cmd_table;
        while (cur_command->name)
        {
          if (strcasecmp(cur_command->name, argv[0]) == 0) /* Command is found. */
          {
            if (((argc - 1u) >= cur_command->min_args) && ((argc - 1u) <= cur_command->max_args))
            {
               if (cur_command->cmd_ptr)
               {
                 ((void(*)(int32_t cmd_ptr_argc, char **cmd_ptr_argv))(cur_command->cmd_ptr))(argc, argv);
               }
            }
            else /* Wrong command syntax. */
            {
              shell_println(SHELL_ERR_SYNTAX, argv[0]);
            }

            break;
          }
          cur_command++;
        }

        if (cur_command->name == 0)
        {
          shell_println(SHELL_ERR_CMD, argv[0]);
        }
      }

      shell_state = SHELL_STATE_END_CMD;
      break;

    case SHELL_STATE_END_CMD:
      shell_state = SHELL_STATE_INIT;
      shell_cmdline_pos = 0u;
      shell_cmdline[0] = 0u;
      break;

    default:
        break;

  }
}

void shell_help(void)
{
  const shell_command_t *cur_command = shell_cmd_table;

  while (cur_command->name)
  {
    shell_println(">%7s %-32s- %s", cur_command->name,
                                      cur_command->syntax,
                                      cur_command->description);
    cur_command++;
  }
}

void shell_init(const shell_command_t *const cmd_table, void (*init)(void))
{
  setbuf(stdout, NULL);

  shell_state = SHELL_STATE_INIT;
  shell_cmdline_pos = 0u;
  shell_cmdline[0] = 0u;
  shell_cmd_table = cmd_table;

  init();
}

