#include "shell.h"
#include <sys/stat.h> /* For struct stat and stat function */

#define PROMPT "$_SHELL "
#define BUFFER_SIZE 1024 /* Define BUFFER_SIZE */

extern char **environ; /* Declare the external environ variable */

/**
 * main - Entry point of the shell
 *
 * Return: 0 on success, or an exit status on failure
 */
int main(void)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		/* Display the prompt only if running interactively */
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		}

		line = read_line(); /* Read input */
		if (!line)
			break; /* Handle EOF */

		args = parse_line(line); /* Parse the input */
		if (args[0] != NULL)
			status = execute_command(args); /* Execute the command */

		free(line);
		free_array(args);
	}

	return (0);
}

/**
 * parse_line - Splits a line into arguments
 * @line: Input line
 *
 * Return: Array of arguments
 */
char **parse_line(char *line)
{
	size_t bufsize = BUFFER_SIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += BUFFER_SIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n");
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * find_command_path - Finds the full path of a command
 * @command: The command to find
 *
 * Return: Full path to the command, or NULL if not found
 */
char *find_command_path(char *command)
{
	char *path = NULL;
	char *path_copy, *token, *full_path;
	struct stat st;
	int i;

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = environ[i] + 5;
			break;
		}
	}
	if (!path)
		return (NULL);

	/* First check if the command starts with './' */
	if (command[0] == '.' && command[1] == '/')
	{
		if (stat(command, &st) == 0)
		{
			return (strdup(command)); /* Return the command as is if it exists */
		}
		return (NULL); /* Return NULL if the file doesn't exist */
	}

	/* Check in the PATH variable */
	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * execute_command - Executes a command
 * @args: Array of arguments
 *
 * Return: 0 on success, -1 on failure, or 1 to continue the shell loop
 */

int execute_command(char **args)
{
	pid_t pid;
	int status;
	int builtin_result;
	char *command_path;

	/* Step 1: Check built-ins (exit, env, etc.) */
	builtin_result = handle_builtin(args);
	if (builtin_result != -1)
	{
		/* If handle_builtin returns 0 => exit the shell */
		/* If it returns 1 => done handling builtin, keep running */
		return (builtin_result);
	}

	/* Step 2: Not a builtin => find command in PATH (if not an absolute or "./" path) */
	if (args[0][0] != '/' && !(args[0][0] == '.' && args[0][1] == '/'))
	{
		command_path = find_command_path(args[0]);
		if (!command_path)
		{
			fprintf(stderr, "%s: command not found\n", args[0]);
			return (1);
		}
	}
	else
	{
		command_path = args[0];
	}

	/* Step 3: Fork a child process to run the external command */
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (command_path != args[0])
			free(command_path);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(command_path, args, environ) == -1)
		{
			perror(args[0]);
			if (command_path != args[0])
				free(command_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	if (command_path != args[0])
		free(command_path);

	return (1);
}


/**
 * free_array - Frees a dynamically allocated array of strings
 * @arr: Array to free
 */
void free_array(char **arr)
{
	free(arr);
}

