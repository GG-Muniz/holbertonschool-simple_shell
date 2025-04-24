#include "shell.h"

/**
 * execute_command - Execute a command with its arguments
 * @args: Array of strings containing the command and its arguments
 * @program_name: Name of the shell program for error messages
 *
 * Return: Status code from the command execution
 */
int execute_command(char **args, char *program_name)
{
	pid_t pid;
	int status, exit_status = 0;
	char *command_path;

	/* Get the full command path */
	command_path = find_command_in_path(args[0]);

	/* If command not found, print error and return command not found status */
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
		return (127); /* Command not found status */
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
		if (execve(command_path, args, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
			free(command_path);
			exit(127);
		}
		exit(0); /* This line shouldn't be reached */
	}
	else
	{
		/* Parent process - wait for child to complete */
		waitpid(pid, &status, 0);
		free(command_path);

		/* Get the exit status of the child process */
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_status = 128 + WTERMSIG(status);
	}

	return (exit_status); /* Return the exit status of the command */
}
