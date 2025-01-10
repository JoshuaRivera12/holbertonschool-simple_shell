#include "shell.h"

/**
 * release_memory - Frees a dynamically allocated array of strings.
 * @array: The array to free.
 * Return: Void.
 */

void release_memory(char **array)
{
	int index = 0;
	
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

