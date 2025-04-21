#include "shell.h"

/**
 * main - entry point for the simple shell.
 * Return: 0 if successfull.
 */
int main(void)
{
	char *command_line = NULL;
	int status = 1;

	while (status)
	{
		/* Show the shell Prompt */
		display_prompt();

		/* Read the user's imput */
		command_line = read_command_line();

		/* Handle the End-Of-File (eof) condition (Ctrl+D) */
		if (command_line == NULL)
		{
			if (isatty(STDIN_FILENO)) /* Shows if we are in interactive mode */
				printf("\n");
			break;
		}

		/* Execute the status of the command and update's */
		status = execute_command(command_line);

		/* Free allocated memory*/
		free(command_line);
	}

	return (0);
}
