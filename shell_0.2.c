#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024
#define TOKEN_DELIM " \t\r\n\a"

/**
 * tokenize_line - Split a line into tokens
 * @line: Input command line
 *
 * Return: Array of tokens
 */
char **tokenize_line(char *line)
{
	int buffer_size = BUFFER_SIZE, position = 0;
	char **tokens = malloc(buffer_size * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOKEN_DELIM);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		if (position >= buffer_size)
		{
			buffer_size += BUFFER_SIZE;
			tokens = realloc(tokens, buffer_size * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "Memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOKEN_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * check_abs_path - Check if cmd is absolute path
 * @cmd: Command to check
 *
 * Return: Full path if valid, NULL if not valid
 */
char *check_abs_path(char *cmd)
{
	if (strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
		{
			return (strdup(cmd));
		}
	}
	return (NULL);
}

/**
 * search_path - Search for command in PATH
 * @cmd: Command to search for
 *
 * Return: Full path if found, NULL if not found
 */
char *search_path(char *cmd)
{
	char *path, *path_copy, *path_token, *file_path;
	int cmd_len, dir_len;

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	cmd_len = strlen(cmd);
	path_token = strtok(path_copy, ":");

	while (path_token)
	{
		dir_len = strlen(path_token);
		file_path = malloc(dir_len + cmd_len + 2);
		if (!file_path)
		{
			free(path_copy);
			return (NULL);
		}
		strcpy(file_path, path_token);
		strcat(file_path, "/");
		strcat(file_path, cmd);

		if (access(file_path, X_OK) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		free(file_path);
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * find_command - Check if a command exists
 * @command: Command to check
 *
 * Return: Full path if found, NULL if not found
 */
char *find_command(char *command)
{
	char *result;

	result = check_abs_path(command);
	if (result)
		return (result);

	return (search_path(command));
}

/**
 * read_line - Read a line from stdin
 *
 * Return: Pointer to the line read
 */
char *read_line(void)
{
	int buffer_size = BUFFER_SIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * buffer_size);
	int c;

	if (!buffer)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		c = getchar();
		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}
		buffer[position++] = c;

		if (position >= buffer_size)
		{
			buffer_size += BUFFER_SIZE;
			buffer = realloc(buffer, buffer_size);
			if (!buffer)
			{
				fprintf(stderr, "Memory allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}
