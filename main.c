#include "main.h"

#define UNUSED(x) (void)(x)
#define TOKENS_SIZE 10

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
	ssize_t rtn;
	pid_t pid;
	char *buff;

	buff = malloc(sizeof(char) * 10);
	if (!buff)
		return (0);
	pid = fork();

	switch (pid)
	{
		case -1:
			perror("Something went wrong with fork!");
			return (0);
		case 0:
		rtn = execve(buff, args, envp);
		if (rtn == -1)
			printf("%s: No such file or directory\n", argv[0]);
		free(buff);
		break;
	default:
		wait(NULL);
	}
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
	char **grid;
	char *token = NULL, *delim = " \t";
	int i;

	grid = malloc(sizeof(char *) * TOKENS_SIZE);
	if (!grid)
	{
		perror("tokens failed\n");
		return (NULL);
	}
	token = strtok(str, delim);
	i = 0;
	while (token)
	{
		grid[i] = malloc(sizeof(char *) * (_strlen(token) + 1));
		if (!grid[i])
		{
			free(grid);
			perror("token failed\n");
			return (NULL);
		}
		_strcpy(grid[i], token);
		token = strtok(NULL, delim);
		i++;
	}
	grid[i] = NULL;
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
	int j, run = 1;
	size_t size = 10;
	char *s = NULL, **args;

	UNUSED(argc);
	UNUSED(argv);

	while (run)
	{
		printf("#cisfun$ ");
		chars = getline(&s, &size, stdin);
		if (chars == -1)
		{
			if (feof(stdin))
			{
				putchar(10);
				free(s);
				break;
			}
			else
			{
				perror("Something went wrong!\n");
				free(s);
				break;
			}
		}
		*(s + _strlen(s) - 1) = '\0';
		args = tokenize(s);
		run = execute_program(args, argv, envp);
		for (j = 0; j < TOKENS_SIZE; j++)
			free(args[j]);
		free(args);
	}
	return (0);
}
