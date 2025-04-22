#include "shell.h"
/**
 * read_command_line - function will read a line from the stdin.
 * Return: pointer to input string, or NULL on EOF error.
 *
 */
char *read_command_line(void)
{
	char *line = NULL;
	size_t buffer_size = 0;
	ssize_t chars_read;

	/* Read line from stdin. */
	chars_read = getline(&line, &buffer_size, stdin);

	/* Check for EOF or error. */
	if (chars_read == -1)
	{
		/* Free memory if getline fails. */
		free(line);
		return (NULL);
	}

	/* Remove the trailing newline character */
	if (line[chars_read - 1] == '\n')
		line[chars_read - 1] = '\0';

	return (line);
}
