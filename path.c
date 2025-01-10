#include "shell.h"

/**
 * find_command - Searches for a command in the PATH.
 * @environ: Array of environment variables.
 * @command: Command to search for.
 * Return: Full path to the command or NULL if not found.
 */

char *find_command(char **environ, char *command)
{
	char *path = get_env(environ, "PATH"), *dir, *full_path;
	size_t len;

	if (!path || *path == '\0')
		return (NULL);

	path = strdup(path);
	dir = strtok(path, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
			break;

		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

