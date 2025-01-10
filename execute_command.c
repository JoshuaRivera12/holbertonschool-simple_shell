#include "shell.h"

/**
 * run_command - Forks and executes the command via execve.
 * @path: The full path to the executable.
 * @args: The array of arguments.
 *
 * Return: 1 to continue the shell loop in the parent.
 */
static int run_command(const char *path, char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

/**
 * execute_command - Executes a command or checks built-ins first.
 * @args: Array of argument strings.
 *
 * Return: 0 if the shell should exit, 1 otherwise (continue).
 */
int execute_command(char **args)
{
	int builtin_result;
	char *command_path;
	int ret_val;

	builtin_result = handle_builtin(args);
	if (builtin_result != -1)
		return (builtin_result);

	/* Handle absolute or relative paths (starts with '/' or '.') */
	if (args[0][0] == '/' || args[0][0] == '.')
	{
		command_path = args[0];
	}
	else
	{
		command_path = find_command_path(args[0]);
		if (!command_path)
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
			return (1);
		}
	}

	/* Actually run the command with fork + exec */
	ret_val = run_command(command_path, args);

	/* If find_command_path allocated memory, free it */
	if (command_path != args[0])
		free(command_path);

	/* Return the child's result to indicate continuing (or 0 to exit if desired) */
	return (ret_val);
}

