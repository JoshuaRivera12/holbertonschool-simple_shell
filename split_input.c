#include "shell.h"

/**
 * split_input - Splits an input string into tokens.
 * @input: The input string.
 * @args: Array to store the tokens.
 * Return: Void.
 */

void split_input(char *input, char **args)
{
	int i = 0;

	args[i] = strtok(input, " \t");
	while (args[i] && i < 99) /* Leave space for NULL terminator */
	{
		i++;
		args[i] = strtok(NULL, " \t");
	}
	args[i] = NULL; /* Ensure the last element is NULL */
}

