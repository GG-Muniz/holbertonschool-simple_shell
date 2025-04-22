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

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
			return (0);
	}
	return (1);
}

/**
 * free_args - frees the memory for the argument array.
 * @args: the argument array to free.
 */
void free_args(char **args)
{
	int i;

	if (args)
	{
		for (i = 0 ; args[i]; i++)
			free(args[i]);
		free(args);
	}
}
