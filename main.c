#include "shell.h"

/**
 * main - Entry point for the simple shell program
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	char *line = NULL;
	char **args = NULL;
	size_t len = 0;
	ssize_t read;
	int continue_loop = 1;
	int last_status = 0;
	char *program_name = av[0];

	(void)ac; /* Silence unused parameter warning */

	/* Main loop that keeps the shell running until exit */
	while (continue_loop)
	{
		/* Display prompt if shell is running in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		/* Read a line from the user */
		read = getline(&line, &len, stdin);
		if (read == -1) /* Handle EOF (Ctrl+D) */
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Remove trailing newline character */
		if (read > 0 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		/* Skip empty commands or whitespace */
		if (is_only_whitespace(line))
			continue;

		/* Parse input into arguments */
		args = split_line(line);

		/* Skip empty commands */
		if (args == NULL || args[0] == NULL)
		{
			free_args(args);
			continue;
		}

		/* Check for built-in commands first */
		if (check_for_builtin(args, last_status))
		{
			free_args(args);
			continue;
		}

		/* Execute the command with arguments */
		last_status = execute_command(args, program_name);

		/* Free allocated memory */
		free_args(args);
	}

	/* Free the line buffer */
	free(line);
	return (last_status);
}
