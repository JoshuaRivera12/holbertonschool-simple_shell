#include "shell.h"
#include <errno.h>

/**
 * execute_command - Executes a command with arguments.
 * @environ: Array of environment variables.
 * @args: Tokenized arguments.
 * @last_status: Pointer to the last status variable.
 * Return: Void.
 */

void execute_command(char **environ, char **args, int *last_status)
{
	pid_t pid;
	int status;
	char *full_path = resolve_path(environ, args[0], last_status);

	if (!full_path)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		*last_status = 127;
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(full_path, args, environ);
		perror("Error");
		if (full_path != args[0])
			free(full_path);
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		*last_status = WEXITSTATUS(status);
	}
	else
	{
		perror("Fork failed");
		*last_status = 1;
	}
	if (full_path != args[0])
		free(full_path);
}
