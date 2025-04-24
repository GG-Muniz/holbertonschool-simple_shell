#include "shell.h"
/**
 * is_only_whitespace - checks if a string contains only whitespaces.
 * @str: string to check
 *
 * Return: 1 if string is only whitespace, else 0.
 */
int is_only_whitespace(char *str)
{
	int i;

	if (str == NULL)
		return (1);

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
			return (0);
	}
	return (1);
}
/**
 * display_prompt - displays shell prompt.
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		printf("#cisfun$ ");
}
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
