#include "shell.h"

/**
 * locate_command - Finds a command in the PATH directories.
 * @env_vars: Array of environment variables.
 * @cmd: The command to search for.
 *
 * Return: Full path of the command, or NULL if not found.
 */

char *locate_command(char **env_vars, char *cmd)
{
	char *path_var = fetch_env_var(env_vars, "PATH"), *directory, *complete_path;
	size_t path_len;

	if (!path_var || *path_var == '\0')
		return (NULL);

	path_var = strdup(path_var);
	directory = strtok(path_var, ":");
	while (directory)
	{
		path_len = strlen(directory) + strlen(cmd) + 2;
		complete_path = malloc(path_len);
		if (!complete_path)
			break;

		snprintf(complete_path, path_len, "%s/%s", directory, cmd);
		if (access(complete_path, X_OK) == 0)
		{
			free(path_var);
			return (complete_path);
		}
		free(complete_path);
		directory = strtok(NULL, ":");
	}
	free(path_var);
	return (NULL);
}

/**
 * fetch_command_path - Resolves the full path of a command.
 * @env_vars: Array of environment variables.
 * @cmd: Command to resolve.
 * @status_code: Pointer to the last command's status.
 *
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

