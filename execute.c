#include "shell.h"

/**
 * execute_command - executes a command
 * @args: command arguments
 */
void execute_command(char **args)
{
	pid_t pid;
