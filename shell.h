#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>

/* Function Prototypes */
void display_prompt(void);
char *read_command_line(void);
int execute_command (char *command);

#endif /* SHELL_H */
