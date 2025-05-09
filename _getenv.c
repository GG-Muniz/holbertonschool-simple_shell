#include "shell.h"

/**
 * _getenv - Custom implementation to get an environment variable
 * @name: Name of the environment variable
 *
 * Return: Value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	int name_len;

	if (!name || !environ)
		return (NULL);

	name_len = strlen(name);

	while (environ[i])
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
			return (environ[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

/**
 * find_command_in_path - Find a command in the PATH
 * @command: The command to find
 *
 * Return: Full path to the command if found, NULL otherwise
 */
char *find_command_in_path(char *command)
{
	char *path_env, *path_copy, *dir, *full_path;
	int command_len, dir_len;
	struct stat st;

	/* Handle null or empty command */
	if (!command || command[0] == '\0')
		return (NULL);

	/* If command contains a slash, check if it's executable */
	if (strchr(command, '/'))
	{
		if (stat(command, &st) == 0)
		{
			if (st.st_mode & S_IXUSR)
				return (strdup(command));
		}
		return (NULL);
	}

	/* Get PATH and check if it exists */
	path_env = _getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	command_len = strlen(command);
	dir = strtok(path_copy, ":");

	/* Search each directory in PATH */
	while (dir)
	{
		dir_len = strlen(dir);
		full_path = malloc(dir_len + command_len + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
