#include "main.h"

/**
 * check_cmd - function to execute the command
 * @args: The array of tokens
 * @argv: The array of arguments
 * @envp: The variable environments
 * @flag: The flag to check the use of malloc
 * @path: The path to search a command
 * @counter: The counter for every command executed
 * @str: The string got from getline
 *
 * Return: 0 on success, 1 otherwise
 *
 */
int check_cmd(char **args, char **envp, char **argv,
		int *flag, char **path, int counter, char *str)
{
	int fd;

	if (args[0][0] != '/' && args[0][0] != '.')
	{
		*path = tokenizer_path(args, envp);
		if (*path == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
					argv[0], counter, args[0]);
			if (!isatty(STDIN_FILENO))/* Check if fildes is open */
			{
				free(*path);
				free(args);
				free(str);
				exit(127);
			}
			return (1);
		}
		*flag = 1; /* To know if we are using malloc in path variable */
	}
	else
	{
		fd = open(args[0], O_RDONLY);
		if (fd == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
					argv[0], counter, args[0]);
			if (!isatty(STDIN_FILENO))
			{
				free(args);
				free(*path);
				free(str);
				exit(127);
			}
			return (1);
		}
		close(fd);
		*path = args[0];
	}
	return (0);
}

/**
 * check_env - function to check the env
 * @envp: The variable environments
 * Print the current environment variable
 *
 * Return: 1 on success, 0 otherwise
 *
 */
int check_env(char **envp)
{
	char **my_envp;

	if (!envp)
	{
		printf("\n");
		return (0);
	}
	my_envp = envp;
	/* Print every environment variable */
	while (*my_envp)
	{
		printf("%s\n", *my_envp);
		my_envp++;
	}
	return (1);
}
