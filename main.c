#include "main.h"

/**
 * execute_program - function to execute the command
 * @args: The array of tokens
 * @argv: The array of arguments
 * @envp: The variable environments
 * @counter: The counter for commands executed
 * @str: The string got from getline
 * Search for a command and execute it if it was found
 *
 * Return: 1 on success, 0 otherwise
 *
 */
int execute_program(char **args, char **argv, char **envp,
		int counter, char *str)
{
	pid_t pid;
	ssize_t exe;
	int status, flag = 0, check;
	char *path;

	if (!args)
		return (1);
	check = check_cmd(args, envp, argv, &flag, &path, counter, str);
	if (check)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		if (flag == 1)
			free(path);
		return (0);
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
	/* Check if fildes is open and execve fails*/
	if (!isatty(STDIN_FILENO) && status > 0)
	{
		free(args);
		free(str);
		exit(2);
	}
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
	int run = 1, counter = 0;
	size_t	size = 0;
	char *s = NULL, **args, *cmd;

	while (run)
	{
		signal(SIGINT, signal_handler);
		if (isatty(STDIN_FILENO)) /* Checks if fildes is open */
			printf("#cisfun$ ");
		chars = getline(&s, &size, stdin);
		counter++;
		if (chars == -1)
		{
			free(s);
			return (0);
		}
		cmd = trim_spaces(s);
		if (strncmp(cmd, "help", 4) == 0)
		{
			help_builtin(cmd);
			continue;
		}
		args = tokenizer_cmd(cmd);
		if (check_builtins(args, envp, counter, argv) == 1)
			continue;
		else if (check_builtins(args, envp, counter, argv) == 0)
			break;
		run = execute_program(args, argv, envp, counter, cmd);
		free(args);
	}
	free(s);
	return (0);
}
