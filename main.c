#include "shell.h"

#define PROMPT "$_SHELL "

/**
 * main - Entry point of the simple shell
 * @argc: Unused argument count
 * @argv: Argument vector (argv[0] is shell name)
 *
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
	char *line;
	char **args;
	int status = 1;
	char *shell_name;
	int cmd_count = 0;

	(void)argc; /* if unused, silence warnings */
	shell_name = argv[0]; /* e.g. "./hsh" */

	while (status)
	{
		cmd_count++;

		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));

		line = read_line();
		if (!line)
			break;

		args = parse_line(line);
		if (args[0])
			status = execute_command(args, shell_name, cmd_count);

		free(line);
		free_array(args);
	}
	return (status);
}

