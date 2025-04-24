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
/* Function Prototypes */
void display_prompt(void);
char *read_command_line(void);
char **split_line(char *line);
int execute_command(char **args, char *program_name);
int is_only_whitespace(char *str);
void free_args(char **args);
char *find_command_in_path(char *command);
int check_for_builtin(char **args);
void print_environment(void);
char *_getenv(const char *name);

extern char **environ;

#endif /* SHELL_H */
