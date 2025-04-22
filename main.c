#include "shell.h"

/**
 * main - entry point for simple shell
 *
 * Return: always 0
 */
int main(void)
{
	char *line + NULL;
	size_t len = 0:
	ssize_t read;
	char *args[MAX_ARGS];

	while (1)
	{
		prompt();
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			break;
		}

		if (line[read - 1] == '\n')
		    line[read - 1] = '\0;

		parse_line(line, args);
		if (args[0] != NULL)
			execute_command(args);
	}

	return (0);
}

/**
 * prompt - displays the shell prompt
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	   write(STDOUT_FILENO, "$ ", 2);
}
