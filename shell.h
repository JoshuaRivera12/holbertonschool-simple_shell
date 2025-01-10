#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

char *get_env(char **environ, const char *name);
char *find_command(char **environ, char *command);
void execute_command(char **environ, char **args, int *last_status);
void print_env(char **environ);
int handle_builtin(char **args, char **environ, int *last_status);
void tokenize_input(char *line, char **args);
char *resolve_path(char **environ, char *command, int *last_status);

#endif

