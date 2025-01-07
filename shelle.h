#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER_SIZE 1024

/* Function prototypes */
char *read_line(void);
char **parse_line(char *line);
int execute_command(char **args);
void free_array(char **arr);

#endif /* SHELL_H */

