#include "shell.h"

/**
 * handle_builtin - checks and executes builtin commands (exit, env, etc.)
 * @args: array of argument strings
 *
 * Return:
 *  0 if the command is 'exit' => the shell loop in main should stop
 *  1 if a builtin command (like 'env') was handled and we should continue
 * -1 if it's not a builtin => proceed with normal command execution
 */

int handle_builtin(char **args)
{
	if (!args[0])
		return (-1);

	if (strcmp(args[0], "exit") == 0)
	{
		int exit_code = 0;

		if (args[1])
		{
			char *endptr;

			exit_code = strtol(args[1], &endptr, 10);
			if (*endptr != '\0')
			{
				fprintf(stderr, "exit: numeric argument required\n");
				exit_code = 2;
			}
		}
		free_array(args);
		exit(exit_code);
	}
	if (strcmp(args[0], "env") == 0)
	{
		int i;

		for (i = 0; environ[i] != NULL; i++)
			puts(environ[i]);
		return (1);
	}
	return (-1);
}
