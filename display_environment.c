#include "shell.h"

/**
 * display_environment - Outputs all environment variables.
 * @env_vars: Array of environment variables.
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

