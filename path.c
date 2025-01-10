#include "shell.h"

/**
 * get_path_value - Retrieves the PATH environment value.
 *
 * Return: pointer to the PATH string in the environment, or NULL if not found.
 */

static char *get_path_value(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}
	return (NULL);
}

/**
 * build_and_check - Builds directory/command and checks if it exists.
 * @dir: Directory from PATH.
 * @cmd: The command name (e.g., "ls").
 *
 * Return: Newly allocated full path if file exists, or NULL if not found.
 */

static char *build_and_check(const char *dir, const char *cmd)
{
	struct stat st;
	char *f_path;

	f_path = malloc(strlen(dir) + strlen(cmd) + 2);
	if (!f_path)
		return (NULL);

	strcpy(f_path, dir);
	strcat(f_path, "/");
	strcat(f_path, cmd);
	if (stat(f_path, &st) == 0)
		return (f_path);

	free(f_path);
	return (NULL);
}

/**
 * find_command_path - Finds the full path of a given command
 * @command: The command to find
 *
 * Return: Full path to the command, or NULL if not found
 */

char *find_command_path(char *command)
{
	struct stat s;
	char *path_copy, *token, *res;
	char *path = NULL;

	if (command[0] == '.' && command[1] == '/')
	{
		if (stat(command, &s) == 0)
			return (strdup(command));
		return (NULL);
	}
	path = get_path_value();
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
		res = build_and_check(token, command);
		if (res)
		{
			free(path_copy);
			return (res);
		}
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

