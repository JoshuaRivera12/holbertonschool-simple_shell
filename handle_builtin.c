#include "shell.h"

/**
 * manage_builtin - Handles built-in commands.
 * @arguments: Command-line arguments.
 * @env_vars: Array of environment variables.
 * @status_code: Pointer to the last executed command status.
 * Return: 1 if a built-in command is executed, 0 otherwise.
 */

int manage_builtin(char **arguments, char **env_vars, int *status_code)
{
	if (strcmp(arguments[0], "exit") == 0)
		release_memory(arguments);
		exit(*status_code);

	if (strcmp(arguments[0], "env") == 0)
	{
		display_environment(env_vars);
		return (1);
	}
	return (0);
}

