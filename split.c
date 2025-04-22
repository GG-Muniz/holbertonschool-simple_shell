#include "shell.h"

/**
 * split_line - splitting line into tokens (command and arguments)
 * @line: The line to parse.
 *
 * Return: an array of tokens or NULL if only whitespace.
 */
char **split_line(char *line)
{
	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}

	/* System function strtok to split the line by spaces and tabs. */
	token = strtok(line, " \t\r\n\a");

	/* If there are only spaces in the input. */
	if (token == NULL)
	{
		free(tokens);
		return (NULL);
	}

	while (token != NULL)
	{
		tokens[positions = strdup(token);
		if (!tokens[position])
		{
			perror("strdup error");
			exit(EXIT_FAILURE);
		}
		position++;

		/* If we exceed the buffer, reallocate. */
		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("realloc error");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}
