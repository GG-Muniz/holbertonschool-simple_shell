# Holbertonschool-Simple-Shell
Holberton Coding School San Juan - Simple Shell Group Project

## Table of Content
:computer: 
:computer:
:computer:

## Description

Simple_shell is a lightweight, interactive shell that accepts user commands, parses them, and executes them using fork and execve. It supports command arguments, built-in commands like exit, and works in both interactive and non-interactive modes.

### What...

# Simple Shell - Command Execution and Prompt Display

This repository is part of a custom UNIX command line interpreter project. The files included here contribute to displaying the shell prompt and executing user commands using the `execve` system call.

## Files

### `display_prompt.c`

This file defines the `display_prompt` function, which is responsible for displaying the custom shell prompt `#cisfun$ ` when the shell is running in interactive mode.

#### Function: `display_prompt`

```c
void display_prompt(void);
Behavior: Checks if the input is coming from a terminal using isatty(STDIN_FILENO) and prints the shell prompt accordingly.

Purpose: Ensures a user-friendly shell experience during interactive sessions.

# Simple Shell - Command Execution and Prompt Display

This repository is part of a custom UNIX command line interpreter project. The files included here contribute to displaying the shell prompt and executing user commands using the `execve` system call.

## Files

### `display_prompt.c`

This file defines the `display_prompt` function, which is responsible for displaying the custom shell prompt `#cisfun$ ` when the shell is running in interactive mode.

#### Function: `display_prompt`

```c
void display_prompt(void);
Behavior: Checks if the input is coming from a terminal using isatty(STDIN_FILENO) and prints the shell prompt accordingly.

Purpose: Ensures a user-friendly shell experience during interactive sessions.

execve.c:

This file contains the execute_command function which handles forking and executing a command entered by the user.

helpers.c:

# Simple Shell - Helper Functions

This file provides utility functions used by the shell to handle common tasks such as input validation and memory management.

## File: `helpers.c`

### Functions

---

### `int is_only_whitespace(char *str)`

This function checks whether a given string contains only whitespace characters (spaces, tabs, newlines, or carriage returns).

#### Parameters:
- `str`: A pointer to the string to be checked.

#### Return Value:
- Returns `1` if the string is `NULL` or contains only whitespace characters.
- Returns `0` otherwise.

#### Usage:
Useful for ignoring empty or whitespace-only input lines in the shell loop.

#### Example:
```c
if (is_only_whitespace(input))
    continue;

main.c:
 This document explains the functionality of the shell's entry point and its role in handling user input, command execution, and shell control flow.

# Simple Shell - Main Entry Point

This file contains the entry point for a custom UNIX command line interpreter. It implements the main shell loop, handling input, parsing, execution, and built-in command checks.

## File: `main.c`

### Function: `int main(int ac, char **av)`

The core function of the shell program. It manages user interaction, command parsing, execution, and memory cleanup.

---

### Parameters

- `ac`: Argument count (unused in this implementation, silenced using `(void)ac`)
- `av`: Argument vector; `av[0]` is used to get the shell program's name for error messages

---

### Behavior

1. **Prompt Display**  
   Displays `#cisfun$ ` if the shell is running in an interactive terminal (`isatty(STDIN_FILENO)`).

2. **Input Handling**  
   Uses `getline()` to read input from the user. Handles `EOF` (Ctrl+D) gracefully by breaking the loop and printing a newline.

3. **Whitespace and Empty Line Check**  
   Uses the helper function `is_only_whitespace()` to skip processing empty or whitespace-only lines.

4. **Command Parsing**  
   Uses `split_line()` to tokenize the input into an array of strings (`args`).

5. **Built-in Command Check**  
   Invokes `check_for_builtin()` to handle built-in shell commands like `exit`. If a built-in command is found, the loop continues without forking a child process.

6. **Command Path Resolution**  
   Uses `find_command_in_path()` to locate the full path of a command using the environment's `PATH`.

7. **Error Handling**  
   If the command is not found:
   - Prints a formatted error message to `stderr`
   - Exits with status `127` in non-interactive mode
   - Skips to the next loop iteration in interactive mode

8. **Command Execution**  
   If the command exists, calls `execute_command()` to fork and execute the command with arguments.

9. **Memory Management**  
   - Frees argument arrays with `free_args()`
   - Frees the line buffer before exiting

---

### Return Value

- Always returns `0` on success or graceful exit.

---

## Dependencies

- `shell.h` for function declarations
- Utility functions:
  - `split_line()`
  - `is_only_whitespace()`
  - `find_command_in_path()`
  - `check_for_builtin()`
  - `execute_command()`
  - `free_args()`

---

## Example Usage

```bash
$ ./simple_shell
#cisfun$ ls
file1.c  file2.c  main.c
#cisfun$ exit
$
Designed to run in both interactive and non-interactive modes.

Follows a simple loop structure suitable for expansion with more built-in commands or PATH handling improvements.

man_1_simple_shell

# Simple Shell Manual Page (`man_1_simple_shell`)

This file defines the manual page for the **Simple Shell** program. It uses the traditional UNIX `man` format and is intended to be accessed with the `man` command (e.g., `man ./man_1_simple_shell`).

---

## File: `man_1_simple_shell`

A manual page written in troff/groff format that provides documentation for the `simple_shell` program. This is especially useful for users who want to understand the usage, return values, and behavior of the shell from the command line.

---

## Sections Explained

### `.TH SIMPLE SHELL "April 2025" "Holberton School of Coding San Juan Puerto Rico" "Simple Shell Manual"`
- **TH**: Title Header
- Displays the manual title, date, organization, and description.

---

### `.SH NAME`
Defines the name of the program.

read_command_line.c:

# Simple Shell - Read Command Line

This file contains the `read_command_line` function, which is responsible for reading user input from standard input (stdin) in the simple shell program.

---

## File: `read_command_line.c`

### Function: `char *read_command_line(void)`

Reads a line of input from the user using the `getline` function, handles EOF and input cleanup, and returns a sanitized string.

---

### Return Value

- Returns a pointer to a null-terminated string containing the user’s input (with the newline character removed).
- Returns `NULL` if an error occurs or EOF is encountered (e.g., user presses Ctrl+D).

---

### Behavior

1. Allocates memory dynamically to store the input line using `getline`.
2. Automatically resizes the buffer as needed based on user input length.
3. Removes the trailing newline character (`\n`) to simplify command parsing.
4. Frees memory and returns `NULL` if `getline` fails (e.g., on EOF).

---

### Example Usage

```c
char *line = read_command_line();
if (line == NULL)
{
    // Handle EOF or error (e.g., exit shell loop)
    break;
}
// Continue to tokenize and execute command

shell.h:

# Simple Shell - Header File (`shell.h`)

This is the main header file for the Simple Shell project. It defines the function prototypes and includes the necessary standard libraries required across all source files in the shell implementation.

---

## Purpose

`shell.h` ensures that all shell components—such as reading input, parsing commands, executing processes, and handling built-ins—are consistently declared and can be shared across multiple source files in the project.

---

## Included Libraries

The header includes essential C libraries and system headers used throughout the shell:

- `<stdio.h>`: Input/output functions (e.g., `printf`, `getline`)
- `<stdlib.h>`: Memory allocation (`malloc`, `free`, `exit`)
- `<unistd.h>`: POSIX API for system calls (`fork`, `execve`, `isatty`)
- `<string.h>`: String manipulation (`strcpy`, `strcmp`, etc.)
- `<sys/types.h>` and `<sys/wait.h>`: Process control (`pid_t`, `waitpid`)
- `<sys/stat.h>`: File status (e.g., for checking file existence)
- `<limits.h>`: System limits
- `<errno.h>`: Error codes used with system calls

---

## Function Prototypes

These are the declared functions used throughout the shell:

### Core Shell Functions
- `void display_prompt(void);`  
  Displays the shell prompt in interactive mode.

- `char *read_command_line(void);`  
  Reads input from stdin using `getline`.

- `char **split_line(char *line);`  
  Tokenizes a command line string into arguments.

- `int execute_command(char **args, char *program_name);`  
  Forks and executes a command with `execve`.

### Utility & Helper Functions
- `int is_only_whitespace(char *str);`  
  Checks if a line contains only whitespace.

- `void free_args(char **args);`  
  Frees the memory allocated for the argument array.

- `char *find_command_in_path(char *command);`  
  Searches for a command in the system `PATH`.

- `int check_for_builtin(char **args);`  
  Checks for and executes built-in shell commands like `exit`.

- `void print_environment(void);`  
  Prints the shell's current environment variables.

- `char *_getenv(const char *name);`  
  Retrieves the value of an environment variable.

---

## Global Variables

- `extern char **environ;`  
  Access to the environment variables for command execution.

---

## Usage

Include this file in every `.c` file of the project using:

```c
#include "shell.h"

split.c

# Simple Shell - Command Line Splitting

This file contains the implementation of the `split_line` function, which tokenizes a user's input into an array of arguments for command execution. It plays a key role in parsing the raw string input into manageable parts.

---

## File: `split.c`

### Function: `char **split_line(char *line)`

Parses a string input from the user and splits it into an array of words (tokens), using common shell delimiters like spaces, tabs, and newlines.

---

### Parameters

- `line`: A null-terminated string representing the input line from the user (usually read via `getline`).

---

### Return Value

- Returns a **NULL-terminated** array of strings (tokens).
- Returns `NULL` if the input line is empty or contains only whitespace.

---

### Behavior

1. **Tokenization**  
   Uses `strtok()` to split the input string based on delimiters:
   - Space `' '`
   - Tab `'\t'`
   - Carriage return `'\r'`
   - Newline `'\n'`
   - Alert `'\a'`

2. **Dynamic Allocation**  
   Allocates memory dynamically for the array of tokens. Reallocates more space if the number of tokens exceeds the initial buffer size.

3. **Memory Safety**  
   Uses `strdup()` to copy each token into the array to avoid pointer issues. Cleans up and exits with an error if any allocation fails.

4. **Whitespace Handling**  
   If the input line is empty or contains only delimiters, the function frees memory and returns `NULL`.


### Return

### Technology 
C program, C language, Linux Terminal, shell, Github

### Compilation
GNU 89
### Challenges
Create how to create a simple UNIX command-line interpreter (shell) from scratch. 

### Reference 
Holberton reference page:Everything you need to know to start coding your own shell Public
PID & PPID

### Developers

### Gabriel Garcia Muniz 
https://github.com/GG-Muniz

### Angel Bayo Torres
https://github.com/AngelD89
