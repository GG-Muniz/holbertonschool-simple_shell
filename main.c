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
	int status = 1;
	char *program_name = av[0];

	(void)ac; /* Silence unused parameter warning */

	/* Main loop that keeps the shell running until exit */
	while (status)
	{
		/* Display prompt if shell is running in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

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

		/* Parse input into arguments, handling whitespace properly */
		args = split_line(line);

		/* Skip empty commands */
		if (args == NULL || args[0] == NULL)
		{
			free(args);
			continue;
		}
		/* Execute the command with arguments */
		status = execute_command(args, program_name);

		/* Free allocated memory */
		free(args);
	}
	/* Free the line buffer */
	free(line);
	return (0);
}

