/***************************************************************************//**
 * @file cli_config.h
 * @brief Command Line Interface configuration file
 * @version 5.1.1
 *******************************************************************************
 * @section License
 * <b>Copyright 2016 Silicon Laboratories, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#ifndef _CLI_CONFIG_H_
#define _CLI_CONFIG_H_

#include <stdio.h>

#define CLI_CONFIG_DEFAULT_VSPRINTF_FUNCTION    vsprintf

#define CLI_CONFIG_CMDLINE_MAX_STRING_LENGTH    80
#define CLI_CONFIG_CMDLINE_MAX_ARGUMENT_COUNT   16
#define CLI_CONFIG_CMDLINE_HISTORY_COUNT        5
#define CLI_CONFIG_CMDLINE_DEFAULT_TIMEOUT      1
#define CLI_CONFIG_MAX_INLINE_HELP_CMDS         3

#define CLI_CONFIG_PRINTF_BUFFER_SIZE           256

#define CLI_CONFIG_MAX_STRING_LENGTH            256

#define CLI_CONFIG_CMD_MAX_STRING_LENGTH        16

#define CLI_CONFIG_LOGIN_ATTEMPT_COUNT          3
#define CLI_CONFIG_LOGOUT_FUNC_MAX_ARGS         3

#define CLI_CONFIG_USER_LEVEL_MAX               10
#define CLI_CONFIG_USER_MAX_COUNT               1
#define CLI_CONFIG_USER_NAME_MAX_LENGTH         8
#define CLI_CONFIG_USER_PASS_MAX_LENGTH         8

#define CLI_CONFIG_PROMPT_STRING_LENGTH         8

#define CLI_CONFIG_MAX_CMDS                     128

#define CLI_CONFIG_CMDLINE_CHAR_COMPUTER_PREFIX ':'

#endif /* _CLI_CONFIG_H_ */

