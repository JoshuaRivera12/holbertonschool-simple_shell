#include "shell.h"

/**
 * parse_line - Splits a line into arguments using strtok.
 * @line: The input line.
 *
 * Return: Array of arguments (NULL-terminated),
 *         or NULL if allocation fails.
 */

#define BUFFER_SIZE 1024

char **parse_line(char *line)
{
	size_t bufsize = BUFFER_SIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n");
	while (token)
	{
		tokens[position] = token;
		position++;
		if (position >= bufsize)
		{
			bufsize += BUFFER_SIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \t\r\n");
	}
	tokens[position] = NULL;
	return (tokens);
}

