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
	int builtin_status;
	char *program_name = av[0];
	int last_status = 0;

	(void)ac;

	while (status)
	{
		/* Display prompt if shell is running in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		/* Read a line from the user */
		read = getline(&line, &len, stdin);
		if (read == -1)
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
		if (!args || !args[0])
		{
			free_args(args);
			continue;
		}

		/* Check for built-in commands first */
		builtin_status = check_for_builtin(args);
		if (builtin_status == 1)
		{
			/* Regular builtin executed */
			free_args(args);
			continue;
		}
		else if (builtin_status == 2)
		{
			/* Exit command */
			free_args(args);
			free(line);
			exit(last_status);
		}

		/* Execute the command with arguments */
		status = execute_command(args, program_name);

		/* Get the exit status of the last command */
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);

		free_args(args);
	}

	free(line);
	return (0);
}
