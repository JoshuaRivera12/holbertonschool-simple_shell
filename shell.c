#include "shell.h"

/**
 * manage_builtin - Handles built-in commands.
 * @arguments: Command-line arguments.
 * @env_vars: Array of environment variables.
 * @status_code: Pointer to the status of the last executed command.
 *
 * Return: 1 if a built-in command is executed, 0 otherwise.
 */

int manage_builtin(char **arguments, char **env_vars, int *status_code)
{
	if (strcmp(arguments[0], "exit") == 0)
	{
		exit(*status_code);
	}

	if (strcmp(arguments[0], "env") == 0)
	{
		display_environment(env_vars);
		return (1);
	}
	return (0);
}

/**
 * run_program - Executes an external command.
 * @env_vars: Array of environment variables.
 * @arguments: Command-line arguments.
 * @status_code: Pointer to the status of the last executed command.
 *
 * Return: Void.
 */

void run_program(char **env_vars, char **arguments, int *status_code)
{
	pid_t process_id;
	int exit_status;
	char *resolved_path = fetch_command_path(env_vars, arguments[0], status_code);

	if (!resolved_path)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", arguments[0]);
		*status_code = 127;
		return;
	}

	process_id = fork();
	if (process_id == 0)
	{
		execve(resolved_path, arguments, env_vars);
		perror("Execution Error");
		if (resolved_path != arguments[0])
			free(resolved_path);
		exit(EXIT_FAILURE);
	}
	else if (process_id > 0)
	{
		waitpid(process_id, &exit_status, 0);
		*status_code = WEXITSTATUS(exit_status);
	}
	else
	{
		perror("Forking Failed");
		*status_code = 1;
	}
	if (resolved_path != arguments[0])
		free(resolved_path);
}

/**
 * main - Entry point for the shell application.
 * @argc: Argument count (unused).
 * @argv: Argument vector (unused).
 * @env_vars: Array of environment variables.
 *
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
		release_memory(parsed_args);
	}
	free(input_line);
	return (exit_status);
}

