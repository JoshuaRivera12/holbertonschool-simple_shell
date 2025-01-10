#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

/* Function prototypes */
char *fetch_env_var(char **env_vars, const char *var_name);
char *locate_command(char **env_vars, char *cmd);
void run_program(char **env_vars, char **arguments, int *status_code);
void display_environment(char **env_vars);
int manage_builtin(char **arguments, char **env_vars, int *status_code);
void split_input(char *input, char **args);
char *fetch_command_path(char **env_vars, char *cmd, int *status_code);
void release_memory(char **array);

#endif

