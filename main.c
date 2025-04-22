#include "shell.h"

/**
 * main - entry point for the simple shell.
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 if successfull.
 */
int main(int ac, char **av)
{
	char *line = NULL;
	char **args = NULL;
	size_t len = 0;
	ssize_t read;
	int status = 1;

	/* Store program name for error messages. */
	char *program_name = av[0];
	(void)ac; /* Silence unused parameter warning */

	/* Main loop that keeps the shell running in interactive mdoe */
	while (status)
	{
		/* Show if shell is running in interactive mode*/
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		/* Read the user's imput */
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n ", 1);
			break;
		}

		/* Remove trailing newline character. */
		if (read > 0 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		/* Remove trailing newline character. */
		if (is_only_whitespace(line))
			continue;

		/* Split the line into command and arguments. */
		args = split_line(line);
		if (args == NULL || args[0] == NULL)
		{
			continue;
		}
		/* Execute the status of the command and update's */
		status = execute_command(args, program_name);

		/* Free allocated memory*/
		free(args);
	}
	/* Free line buffer. */
	free(line);
	return (0);
}
