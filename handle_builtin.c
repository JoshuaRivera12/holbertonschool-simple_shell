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
	/* If no command was typed, do nothing */
	if (!args[0])
		return (-1);

	/* 1) Exit built-in */
	if (strcmp(args[0], "exit") == 0)
	{
		/* Return 0 => main loop stops => shell exits */
		return (0);
	}

	/* 2) env built-in */
	if (strcmp(args[0], "env") == 0)
	{
		/* Print environment variables */
		int i;
		for (i = 0; environ[i] != NULL; i++)
			puts(environ[i]);

		/* Return 1 => keep shell running after printing */
		return (1);
	}

	/* Not a builtin */
	return (-1);
}
