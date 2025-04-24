#include "shell.h"
/**
 * execute_command - Execute a command with its arguments
 * @args: Array of strings containing the command and its arguments
 * @program_name: Name of the shell program for error messages
 *
 * Return: 1 to continue the shell, 0 to exit
 */
int execute_command(char **args)
{
	pid_t pid;
	int status;

	/* Fork a child process */
	pid = fork();

	if (pid == -1)
	{
		/* Fork error */
		perror("Error forking process");
		return 1;
	}

	if (pid == 0)
	{
		/* Child process - attempt to execute the command */
		if (execve(args[0], args, environ) == -1)
		{
			/* Format error message to match expected output */
			fprintf(stderr, "%s: No such file or directory\n", args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process - wait for child to complete */
		waitpid(pid, &status, 0);
	}

	return 1;
}
