#include "shelle.h"

#define PROMPT "$ "
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
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT)); /* Display the prompt */

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
 * execute_command - Executes a command
 * @args: Array of arguments
 *
 * Return: 0 on success, -1 on failure, or 1 to continue the shell loop
 */
int execute_command(char **args)
{
	pid_t pid;
	int status;

	if (strcmp(args[0], "exit") == 0)
		return (0); /* Exit the shell */

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, environ) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

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

