#include "main.h"

/**
 * execute_program - function to execute the command
 * @args: The array of tokens
 * @argv: The array of arguments
 * @envp: The variable environments
 * Split a string in words
 *
 * Return: Pointer to the array of tokens
 *
 */
int execute_program(char **args, char **argv, char **envp)
{
	pid_t pid;
	ssize_t exe;
	int status, fd;
	char *path;

	if (!args)
		return (1);
	path = tokenizer_path(args, envp);
	if (path == NULL)
	{
		printf("%s: No such file or directory\n", argv[0]);
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror(path);
		free(path);
		return (1);
	}
	close(fd);
	pid = fork();
	if (pid == -1)
	{
		free(path);
		return (0);
	}
	if (pid == 0)
	{
		exe = execve(path, args, envp);
		if (exe == -1)
		{
			free(path);
			return (0);
		}
	}
	else
		wait(&status);
	free(path);
	return (1);
}

/**
 * tokenize - function to create tokens
 * @str: The string to be splitted
 * Split a string in words
 *
 * Return: Pointer to the array of tokens
 *
 */
char **tokenize(char *str)
{
	char **grid = NULL, *cmd_cpy;
	char *token = NULL, *delim = " \t\n";
	int i = 0, argc = 0;

	cmd_cpy = strdup(str);
	token = strtok(cmd_cpy, delim);
	if (token)
	{
		while (token)
		{
			token = strtok(NULL, delim);
			argc++;
		}

		grid = malloc(sizeof(char *) * (argc + 1));
		if (!grid)
		{
			perror("tokens failed\n");
			return (NULL);
		}

		token = strtok(str, delim);
		while (token)
		{
			grid[i] = token;
			token = strtok(NULL, delim);
			i++;
		}
		grid[i] = NULL;
	}
	free(cmd_cpy);
	return (grid);
}

/**
 * main - Entry point
 * @argc: The number of arguments passed
 * @argv: The array containing the arguments
 * @envp: The array of variable enviroments
 *
 * Execute my own shell
 *
 * Return: 0 all success
 */
int main(int argc, char **argv, char **envp)
{
	ssize_t chars;
	int run = 1, fd_is_open;
	size_t size = 0;
	char *s = NULL, **args;

	UNUSED(argc);

	while (run)
	{
		fd_is_open = isatty(STDIN_FILENO);
		if (fd_is_open)
			printf("#cisfun$ ");
		chars = getline(&s, &size, stdin);
		if (chars == -1)
		{
			if (feof(stdin))
			{
				free(s);
				return (0);
			}
			else
			{
				perror("Something went wrong!\n");
				free(s);
				return (0);
			}
		}
		args = tokenize(s);
		run = execute_program(args, argv, envp);
		free(args);
	}
	free(s);
	return (0);
}
