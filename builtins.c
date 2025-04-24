#include "shell.h"

/**
 * check_for_builtin - Check if command is a built-in and execute if it is
 * @args: Command arguments
 *
 * Return: 1 if builtin was executed, 0 otherwise
 */
int check_for_builtin(char **args)
{
	if (args == NULL || args[0] == NULL)
		return (0);

	/* Check for exit command */
	if (strcmp(args[0], "exit") == 0)
	{
		/* Exit immediately with success status */
		exit(0);
	}

	/* Check for env command */
	if (strcmp(args[0], "env") == 0)
	{
		print_environment();
		return (1);
	}

	return (0); /* Not a builtin command */
}

/**
 * print_environment - Print all environment variables
 */
void print_environment(void)
{
	int i;

	/* Handle case when environ is NULL */
	if (environ == NULL)
		return;

	for (i = 0; environ[i]; i++)
	{
		/* Use write for more reliable output */
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
