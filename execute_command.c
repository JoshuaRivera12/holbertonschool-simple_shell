#include "shell.h"
#include <errno.h>

/**
 * run_program - Executes a command with arguments.
 * @env_vars: Array of environment variables.
 * @arguments: Tokenized command-line arguments.
 * @status_code: Pointer to the status of the last executed command.
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

