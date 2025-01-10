#ifndef SHELLE_H
#define SHELLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

/* Global environment variable for the 'env' built-in */
extern char **environ;
extern char *shell_name;
extern int cmd_count;

/* Function prototypes */
char *read_line(void);
char **parse_line(char *line);
char *find_command_path(char *command);
int execute_command(char **args);
int handle_builtin(char **args);
void free_array(char **arr);

#endif /* SHELLE_H */
