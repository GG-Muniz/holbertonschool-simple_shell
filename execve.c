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

	/* Get the full command path */
	command_path = find_command_in_path(args[0]);

	/* If command not found, print error and return without forking */
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
		/* For non-interactive mode, use the correct error code */
		if (!isatty(STDIN_FILENO))
			exit(127);
		return (1); /* Continue the shell */
	}

	/* Only fork if we found the command */
	pid = fork();
	if (pid == -1)
	{
		/* Fork error */
		perror("Error forking process");
		free(command_path);
		return (1);
	}

	if (pid == 0)
	{
		/* Child process - attempt to execute the command */
		/* Use the full path we found */
		if (execve(command_path, args, environ) == -1)
		{
			/* Format error message to match expected output */
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
			free(command_path);
			exit(127);  /* Exit with command not found status */
		}
		exit(0); /* This line won't be reached if execve succeeds */
	}
	else
	{
		/* Parent process - wait for child to complete */
		waitpid(pid, &status, 0);
		free(command_path);
	}

	return (1);
}
