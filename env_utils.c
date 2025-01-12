#include "shell.h"

/**
 * fetch_env_var - Retrieves the value of an environment variable.
 * @env_vars: Array of environment variables.
 * @var_name: Name of the variable to retrieve.
 *
 * Return: Pointer to the variable's value or NULL if not found.
 */

char *fetch_env_var(char **env_vars, const char *var_name)
{
	int index = 0;
	size_t name_length = strlen(var_name);

	while (env_vars[index])
	{
		if (strncmp(env_vars[index], var_name, name_length) == 0 &&
			env_vars[index][name_length] == '=')
			return (env_vars[index] + name_length + 1);
		index++;
	}
	return (NULL);
}

/**
 * display_environment - Outputs all environment variables.
 * @env_vars: Array of environment variables.
 *
 * Return: Void.
 */

void display_environment(char **env_vars)
{
	int index = 0;

	while (env_vars[index])
	{
		printf("%s\n", env_vars[index]);
		index++;
	}
}

