#include "shell.h"

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

