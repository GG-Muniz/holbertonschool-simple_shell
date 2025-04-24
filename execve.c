#include "shell.h"

/**
 * execute_command - Execute a command with its arguments
 * @args: Array of strings containing the command and its arguments
 * @program_name: Name of the shell program for error messages
 *
 * Return: The status of the command execution
 */
int execute_command(char **args, char *program_name)
{
	pid_t pid;
	int status;
	char *command_path;

	/* Get the full command path */
	command_path = find_command_in_path(args[0]);

	/* If command not found, print error and return without forking */
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
		return (127 << 8); /* Return 127 as the exit status, just like bash */
	}

	/* Only fork if we found the command */
	pid = fork();
	if (pid == -1)
	{
		/* Fork error */
		perror("Error forking process");
		free(command_path);
		return (1 << 8);
	}

	if (pid == 0)
	{
		/* Child process - attempt to execute the command */
		if (execve(command_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
			free(command_path);
			exit(127); /* Exit with command not found status */
		}
	}
	else
	{
		/* Parent process - wait for child to complete */
		waitpid(pid, &status, 0);
		free(command_path);
		return (status);
	}

	/* This line won't be reached, but keeps compiler happy */
	return (0);
}
