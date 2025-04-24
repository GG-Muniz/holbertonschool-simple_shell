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
 * free_args - Frees the memory allocated for the argument array
 * @args: Array of arguments to free
 */
void free_args(char **args)
{
    int i;

    if (args)
    {
        for (i = 0; args[i]; i++)
            free(args[i]);
        free(args);
    }
}
