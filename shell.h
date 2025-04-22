#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

void prompt(void);
void execute_command(char **args);
void parse_line(char *line, char **args);

#endif /* SHELL_H */
