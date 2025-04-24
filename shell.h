#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS 64

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Function Prototypes */
void display_prompt(void);
char *read_command_line(void);
int execute_command(char **args);
char **split_line(char *line);
int is_only_whitespace(char *str);
void free_args(char **args);
void parse_line(char *line, char **args);
char *read_line(void);
char **tokenize_line(char *line);
char *check_abs_path(char *cmd);
char *search_path(char *cmd);
char *find_command(char *command);
int execute_command(char **args);

extern char **environ;

#endif /* SHELL_H */
