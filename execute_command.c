#include "shell.h"
#include <errno.h>

/**
 * run_command - Forks and executes the command via execve.
 * @path: The full path to the executable.
 * @args: The array of arguments.
 *
 * Return: exit code of the child process, or 1 if fork fails.
 */
static int run_command(const char *path, char **args)
{
	pid_t pid;
	int status, ret_code = 0; /* Initialize ret_code to 0 */

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

		if (WIFEXITED(status))
		{
			ret_code = WEXITSTATUS(status);
		}
		else
		{
			ret_code = 2;
		}
	}
	return (ret_code);
}

/**
 * execute_command - Executes a command or checks built-ins first.
 * @args: Array of argument strings (e.g. {"ls", "-l", NULL})
 * @shell_name: Name of the shell (currently unused)
 * @cmd_count: Count of commands run so far (currently unused)
 *
 * Return: 0 if the shell should exit, 1 otherwise (continue),
 *         or the child process's exit code.
 */
int execute_command(char **args, char *shell_name, int cmd_count)
{
	int builtin_result;
	char *command_path;
	int ret_val;

	/* Mark unused params to avoid -Wunused-parameter error */
	(void)shell_name;
	(void)cmd_count;

	builtin_result = handle_builtin(args);
	if (builtin_result != -1)
		return (builtin_result);

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

	ret_val = run_command(command_path, args);

	if (command_path != args[0])
		free(command_path);

	return (ret_val);
}

