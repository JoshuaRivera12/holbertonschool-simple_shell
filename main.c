#include "shell.h"

/**
 * main - Entry point for the shell application.
 * @argc: Argument count (unused).
 * @argv: Argument vector (unused).
 * @env_vars: Array of environment variables.
 * Return: 0 on success, or the status of the last command.
 */
int main(int argc, char **argv, char **env_vars)
{
	char *input_line = NULL;
	size_t line_length = 0;
	ssize_t read_length;
	char *parsed_args[10];
	int exit_status = 0;
	int interactive_mode = isatty(STDIN_FILENO);

	(void)argc;
	(void)argv;

	while (1)
	{
		if (interactive_mode)
			write(STDOUT_FILENO, "$ ", 2);

		read_length = getline(&input_line, &line_length, stdin);
		if (read_length == -1)
		{
			if (interactive_mode)
				write(STDOUT_FILENO, "Exiting shell...\n", 17);
			break;
		}
		if (read_length > 0)
			input_line[read_length - 1] = '\0';

		split_input(input_line, parsed_args);
		if (parsed_args[0] != NULL)
		{
			if (manage_builtin(parsed_args, env_vars, &exit_status))
				continue;
			run_program(env_vars, parsed_args, &exit_status);
		}
	}
	free(input_line);
	return (exit_status);
}

