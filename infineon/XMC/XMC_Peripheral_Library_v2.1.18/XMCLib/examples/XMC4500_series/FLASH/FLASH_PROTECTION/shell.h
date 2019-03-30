#define SHELL_PROMPT "SHELL> "
#define SHELL_CMDLINE_SIZE 256
#define SHELL_ARGS_MAX 16


/**************************************************************************/ /*!
 * @brief Command callback function prototype.
 *
 * @param desc      Shell descriptor.
 *
 * @param srgc      This parameter is a count of the arguments supplied to
 *                  the command function. @n
 *                  It is equal to @c 1 when the command was entered without
 *                  any argument.
 *
 * @param srgv      This parameter is an array of pointers to the strings
 *                  which are the command arguments.
 *                  The first array element points to the command name.
 *
 ******************************************************************************/
typedef void(*shell_cmd_function_t)(int32_t argc, char **argv);

struct fnet_shell_command;
/**************************************************************************/ /*!
 * @brief Shell command control structure.
 *
 * This structure is used to define properties of a command that will be
 * supported by the shell.@n
 * An application should define the command table and pass it to the
 * @c fnet_shell structure. @n
 * The last table element must have all fields
 * set to zero as the end-of-table mark.
 * The good example of @ref fnet_shell_command usage is in the FNET Shell application.
 *
 * @see fnet_shell
 ******************************************************************************/
typedef struct shell_command
{
    char *name;          /**< @brief Command name (null-terminated string). */
    int8_t                min_args;       /**< @brief Minimum number of arguments the command accepts.*/
    int8_t                max_args;       /**< @brief Maximum number of arguments the command accepts.*/
    shell_cmd_function_t   cmd_ptr;        /**< @brief Pointer to the actual command function defined by
                                                *   the @ref fnet_shell_cmd_function_t type    */
    char *description;   /**< @brief Brief description of the command (null-terminated string). @n
                                                * This field is used by the @ref fnet_shell_help() function.@n*/
    char *syntax;        /**< @brief Syntax of the command (null-terminated string). @n
                                                * This field is used by the @ref fnet_shell_help() function.
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

void shell_init(const shell_command_t *const cmd_table, void (*init)(void));
void shell_state_machine(void);
void shell_help(void);
int32_t shell_println(const char *format, ... );
