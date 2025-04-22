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
int execute_command(char **args, char *program_name);
char **split_line(char *line);
int is_only_whitespace(char *str);

extern char **environ;



#endif /* SHELL_H */
