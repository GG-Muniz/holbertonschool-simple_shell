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

	/* Find command path */
	command_path = find_command_in_path(args[0]);
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
		exit(127);
	}

	/* Fork only if command exists */
	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		free(command_path);
		return (1);
	}

	if (pid == 0)
	{
		/* Child process */
		if (execve(command_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
			free(command_path);
			exit(127);
		}
	}
	else
	{
		/* Parent process */
		wait(&status);
		free(command_path);
	}

	return (1);
}
