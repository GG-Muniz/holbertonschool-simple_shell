#include "shell.h"

/**
 * handle_builtin - Handles built-in commands
 * @args:
 * Command arguments
 *
 * Return: 1 if the command is not a built-in, 0 to exit.
 */
int handle_builtin(char **args)
{
	if (args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0)
		return (0); /* Exit shell */

	return (1); /* Not a built-in */
}
