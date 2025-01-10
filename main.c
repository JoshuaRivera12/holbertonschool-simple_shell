#include "shell.h"

/**
 * File: main.c
 * Description: Contains the main function for the simple shell.
 */

/**
 * main - Entry point of the simple shell
 * Return: 0 on success
 */

#define PROMPT "$_SHELL "

int main(void)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

		line = read_line();
		if (!line)
			break;

		args = parse_line(line);
		if (args[0])
			status = execute_command(args);

		free(line);
		free_array(args);
	}
	return (0);
}

