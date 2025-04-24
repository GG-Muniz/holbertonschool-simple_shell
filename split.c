#include "shell.h"

/**
 * split_line - Split a line into tokens (command and arguments)
 * @line: The line to parse
 *
 * Return: An array of tokens, or NULL if only whitespace
 */
char **split_line(char *line)
{
	int bufsize = 64;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;
	char *delimiters = " \t\r\n\a";

	if (!tokens)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}

	/* Use strtok to split the line by whitespace */
	token = strtok(line, delimiters);

	/* Handle empty input or whitespace-only input */
	if (token == NULL)
	{
		free(tokens);
		return NULL;
	}

	while (token != NULL)
	{
		tokens[position] = strdup(token);
		if (!tokens[position])
		{
			/* Clean up on error */
			free_args(tokens);
			perror("strdup error");
			exit(EXIT_FAILURE);
		}
		position++;

		/* Expand array if needed */
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

		token = strtok(NULL, delimiters);
	}

	tokens[position] = NULL;
	return tokens;
}
