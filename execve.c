#include "shell.h"

/**
 * execute_command - will execute the command inputed.
 * @command: what will be executed.
 *
 * Return: 1 to continue shell loop or 0 to exit.
 *
 */
int execute_command(char *command)
{
	pid_t child_pit;
	int status;
	char *argv[2];

	/* If command is empty, return to prompt. */
	if (command[0] == '\0')
		return (1);

	/* Set up arguments for execve */
	argv[0] = command;
	argv[1] = NULL;

	/* Create a child process. */
	child_pit = fork();

	if (child_pit == -1) /* Failed */
	{
		perror("Erorr");
		return (1);
	}
	if (child_pit == 0) /* Child Process */
	{
		if (execve(command, argv, NULL) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Wait for child process to finish.*/
		wait(&status);
	}
	return (1);
}
