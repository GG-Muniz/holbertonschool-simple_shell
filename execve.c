#include "shell.h"
/**
 * execute_command - Execute a command with its arguments
 * @args: Array of strings containing the command and its arguments
 * @program_name: Name of the shell program for error messages
 *
 * Return: 1 to continue the shell, 0 to exit
 */
int execute_command(char **args, char *program_name)
{
	pid_t pid;
	int status;
	char *command_path;

	/* Find the full path of the command if it's not an absolute path */
	if (args[0][0] != '/' && args[0][0] != '.')
	{
		command_path = find_command_in_path(args[0]);
		if (command_path == NULL)
		{
			fprintf(stderr, "%s: No such file or directory\n", program_name);
			return (1);
		}
		free(args[0]);
		args[0] = command_path;
	}
	/* Fork a child process */
	pid = fork();

	if (pid == -1)
	{
		/* Fork error */
		perror("Error forking process");
		return (1);
	}

	if (pid == 0)
	{
		/* Child process - attempt to execute the command */
		if (execve(args[0], args, environ) == -1)
		{
			/* Format error message to match expected output */
			fprintf(stderr, "%s: No such file or directory\n", program_name);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process - wait for child to complete */
		waitpid(pid, &status, 0);
	}

	return (1);
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

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	command_len = strlen(command);
	dir = strtok(path_copy, ":");

	while (dir)
	{
		dir_len = strlen(dir);
		full_path = malloc(dir_len + command_len + 2); /* +2 for '/' and null terminator */
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		/* Check if this path exists and is executable */
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
