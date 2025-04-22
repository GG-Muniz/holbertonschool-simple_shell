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

	if (args == NULL || args[0] == NULL)
		return 1;  /* Nothing to execute, return to prompt */

	/* Create a new process */
	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, environ) == -1)
		{
			/* Make error message match the example */
			fprintf(stderr, "%s: 1: %s: not found\n", 
					program_name, args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		/* Fork error */
		perror("fork error");
	}
	else
	{
		/* Parent process - wait for child to finish */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}
