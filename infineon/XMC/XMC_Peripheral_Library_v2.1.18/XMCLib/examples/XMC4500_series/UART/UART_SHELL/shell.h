/*
 * Code derived from fNET Shell (https://github.com/butok/FNET/)
 *
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

#ifndef SHELL_H
#define SHELL_H

#define SHELL_PROMPT "SHELL> "
#define SHELL_CMDLINE_SIZE 256
#define SHELL_ARGS_MAX 16

typedef void(*shell_cmd_function_t)(int32_t argc, char **argv);

typedef struct shell_command
{
    char *name;          /**< @brief Command name (null-terminated string). */
    int8_t                min_args;       /**< @brief Minimum number of arguments the command accepts.*/
    int8_t                max_args;       /**< @brief Maximum number of arguments the command accepts.*/
    shell_cmd_function_t   cmd_ptr;        /**< @brief Pointer to the actual command function defined by
                                                *   the @ref shell_cmd_function_t type    */
    char *description;   /**< @brief Brief description of the command (null-terminated string). @n
                                                * This field is used by the @ref shell_help() function.@n*/
    char *syntax;        /**< @brief Syntax of the command (null-terminated string). @n
                                                * This field is used by the @ref shell_help() function.
                                                * The standard command line syntax information
                                                * which will be helpful to describe the possible command
                                                * line parameters in a help display is:
                                                * - @c [] = When a parameter is surrounded with square
                                                * brackets, this means the parameter is optional.
                                                * - @c <> = When a parameter is surrounded with angle
                                                * brackets, this means the parameter is required for
                                                * normal operations of command.
                                                * - @c | = The vertical bar means a choice between
                                                * parameter value is acceptable.*/
} shell_command_t;

#ifdef __cplusplus
extern "C" {
#endif

void shell_init(const shell_command_t *const cmd_table, void (*init)(void));
void shell_state_machine(void);
void shell_help(void);
int32_t shell_println(const char *format, ... );

#ifdef __cplusplus
}
#endif

#endif
