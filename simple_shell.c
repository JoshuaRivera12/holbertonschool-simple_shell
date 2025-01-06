#include "shell.h"

#define PROMPT "$ "

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

    return 0;
}

/**
 * read_line - Reads a line of input from the user
 *
 * Return: Pointer to the input line, or NULL on EOF
 */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            free(line);
            return NULL; /* Handle EOF (Ctrl+D) */
        }
        perror("getline");
        free(line);
        return NULL;
    }

    /* Remove trailing newline */
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';

    return line;
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
    return tokens;
}

/**
 * execute_command - Executes a command
 * @args: Array of arguments
 *
 * Return: 1 to continue, 0 to exit
 */
int execute_command(char **args)
{
    pid_t pid;
    int status;

    if (strcmp(args[0], "exit") == 0)
        return 0; /* Exit the shell */

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
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

    return 1;
}

/**
 * free_array - Frees a dynamically allocated array of strings
 * @arr: Array to free
 */
void free_array(char **arr)
{
    free(arr);
}

