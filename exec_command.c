#include "shell.h"

/**
 * execute_command - Execute a command
 * @args: Command and arguments
 *
 * Return: 1 to continue, 0 to exit shell
 */
int execute_command(char **args)
{
	pid_t pid;
	int status;
	char *command_path;

	if (!args[0])
		return (1);

	if (strcmp(args[0], "exit") == 0)
		return (0);

	command_path = find_command(args[0]);
	if (!command_path)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execv(command_path, args) == -1)
		{
			perror("execv");
		exit(EXIT_FAILURE);
		}
		{
	else if (pid < 0)
		perror("fork");
		}
		{
	else
		waitpid(pid, &status, 0);
		}
	}

	free(command_path);
	return (1);
}
