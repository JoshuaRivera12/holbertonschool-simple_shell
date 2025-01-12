#include "shell.h"

/**
 * split_input - Splits an input string into tokens.
 * @input: The input string.
 * @args: Array to store the tokens.
 *
 * Return: Void.
 */

void split_input(char *input, char **args)
{
	int i = 0;

	args[i] = strtok(input, " \t");
	while (args[i] && i < 99)
	{
		i++;
		args[i] = strtok(NULL, " \t");
	}
	args[i] = NULL;
}

/**
 * release_memory - Frees a dynamically allocated array of strings.
 * @array: The array to free.
 *
 * Return: Void.
 */

void release_memory(char **array)
{
	int i = 0;

	if (array == NULL)
		return;

	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

