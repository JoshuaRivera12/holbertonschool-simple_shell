#include "shell.h"

/**
 * fetch_command_path - Resolves the full path of a command.
 * @env_vars: Array of environment variables.
 * @cmd: Command to resolve.
 * @status_code: Pointer to the last executed command status.
 * Return: Pointer to the resolved full path or NULL if not found.
 */

char *fetch_command_path(char **env_vars, char *cmd, int *status_code)
{
    (void)status_code;

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	return (locate_command(env_vars, cmd));
}

