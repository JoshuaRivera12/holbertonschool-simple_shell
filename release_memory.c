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

	if (array == NULL)
		return;

	while (array[i])
	{
		free(array[i]); /* Only valid for dynamically allocated strings */
		i++;
	}
	free(array); /* Free the array itself if it was dynamically allocated */
}
