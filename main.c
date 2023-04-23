#include "main.h"

/**
 * execute_program - function to execute the command
 * @args: The array of tokens
 * @argv: The array of arguments
 * @envp: The variable environments
 * @counter: The counter for commands executed
 * Search for a command and execute it if it was found
 *
 * Return: 1 on success, 0 otherwise
 *
 */
int execute_program(char **args, char **argv, char **envp, int counter)
{
	pid_t pid;
	ssize_t exe;
	int status, flag = 0, check;
	char *path;

	if (!args)
		return (1);
	check = check_cmd(args, envp, argv, &flag, &path, counter);
	if (check)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		if (flag == 1)
			free(path);
		exit(127);
	}
	if (pid == 0)
	{
		exe = execve(path, args, envp);
		if (exe == -1)
		{
			if (flag == 1)
				free(path);
		}
	}
	else
	{
		wait(&status);
		if (flag == 1)
			free(path);
	}
	if (!isatty(STDIN_FILENO))
		exit(2);
	return (1);
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
int main(__attribute__((unused))int argc, char **argv, char **envp)
{
	ssize_t chars;
	int run = 1, fd_is_open, counter = 0;
	size_t	size = 0;
	char *s = NULL, **args;

	while (run)
	{
		fd_is_open = isatty(STDIN_FILENO);
		if (fd_is_open)
			printf("#cisfun$ ");
		chars = getline(&s, &size, stdin);
		counter++;
		if (chars == -1)
		{
			if (feof(stdin))
			{
				free(s);
				exit(EXIT_SUCCESS);
			}
			else
			{
				perror("Something went wrong!\n");
				exit(EXIT_FAILURE);
			}
		}
		if (strcmp(s, "exit\n") == 0)
			break;
		else if (strcmp(s, "env\n") == 0)
		{
			if (check_env(envp))
				continue;
			else
				break;
		}
		args = tokenizer_cmd(s);
		run = execute_program(args, argv, envp, counter);
		free(args);
	}
	free(s);
	return (0);
}
