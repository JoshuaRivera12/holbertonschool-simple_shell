#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Global environment variable for the 'env' built-in */
extern char **environ;


char *read_line(void);                /* read_line.c */
char **parse_line(char *line);       /* parse_line.c */
char *find_command_in_path(char *command); /* path.c */
void execute_command(char **args);         /* execute.c */
int handle_builtin(char **args);           /* builtin.c */
void free_array(char **arr);      /* for freeing arrays */

#endif
