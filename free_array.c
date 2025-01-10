#include "shell.h"

/**
 * free_array - Frees a dynamically allocated array of strings.
 * @arr: The array to free.
 */

void free_array(char **arr)
{
free(arr);
}

