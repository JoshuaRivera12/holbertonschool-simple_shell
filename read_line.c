#include "shell.h"

/**
 * read_line - Reads a line from stdin using getline
 * Return: Pointer to the buffer containing the line (must be freed by caller),
 *         or NULL on EOF/error
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	nread = getline(&line, &bufsize, stdin);
	if (nread == -1)
	{
		/* EOF or error */
		free(line);
		return (NULL);
	}
	/* Remove trailing newline if present */
	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

