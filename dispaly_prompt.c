#include "shell.h"
/**
 * display_prompt - displays shell prompt.
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 9);
}
