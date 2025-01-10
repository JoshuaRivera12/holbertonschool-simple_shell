#include "shell.h"

/**
 * release_memory - Frees a dynamically allocated array of strings.
 * @array: The array to free.
 *
 * Return: Void.
 */

void release_memory(char **array)
{
	int i = 0;

	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

