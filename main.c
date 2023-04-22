#include "main.h"

/**
 * check_cmd - function to execute the command
 * @args: The array of tokens
 * @argv: The array of arguments
 * @envp: The variable environments
 * @flag: The flag to check the use of malloc
 * @path: The path to search a command
 *
 * Return: 0 on success, 1 otherwise
 *
 */
int check_cmd(char **args, char **envp, char **argv, int *flag, char **path)
{
	int fd;

	if (args[0][0] != '/' && args[0][0] != '.')
	{
		*path = tokenizer_path(args, envp);
		if (*path == NULL)
		{
			printf("%s: No such file or directory\n", argv[0]);
			return (1);
		}
		*flag = 1;
	}
	else
	{
		fd = open(args[0], O_RDONLY);
		if (fd == -1)
		{
			printf("%s: No such file or directory\n", argv[0]);
			return (1);
		}
		close(fd);
		*path = args[0];
	}
	return (0);
}
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
	int status, flag = 0, check;
	char *path;

	if (!args)
		return (1);
	check = check_cmd(args, envp, argv, &flag, &path);
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
			return (0);
		}
	}
	else
	{
		wait(&status);
		if (flag == 1)
			free(path);
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
				return (0);
			}
		}
		args = tokenizer_cmd(s);
		run = execute_program(args, argv, envp);
		free(args);
	}
	free(s);
	return (0);
}
