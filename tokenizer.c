#include "main.h"

/**
  * tokenizer_path - Search PATH and the command if exist
  * @args: Array of tokens from getline
  * @envp: The environment
  *
  * Return: The full path
  */
char *tokenizer_path(char **args, char **envp)
{
	char *path = NULL, *copy_path, *full_path = NULL, *token;
	int fd, i, len;

	/* Search for the PATH environment variable */
	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break;
		}
	}
	if (!path)
		return (NULL);
	copy_path = strdup(path);
	token = strtok(copy_path, ":");
	while (token)
	{
		len = _strlen(token) + _strlen(args[0]) + 2;
		full_path = malloc(sizeof(char) * len);
		if (full_path == NULL)
		{
			free(copy_path);
			return (NULL);
		}
		/* Fill full_path with custom string */
		sprintf(full_path, "%s/%s", token, args[0]);
		full_path[len - 1] = '\0';
		fd = open(full_path, O_RDONLY);
		if (fd > 0)
		{
			close(fd);
			break;
		}
		free(full_path);
		full_path = NULL;
		token = strtok(NULL, ":");
	}
	free(copy_path);
	return (full_path);
}

/**
 * tokenizer_cmd - function to create tokens
 * @str: The string to be splitted
 * Split a string in words
 *
 * Return: Pointer to the array of tokens
 *
 */
char **tokenizer_cmd(char *str)
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
			free(cmd_cpy);
			return (NULL);
		}

		token = strtok(str, delim);
		/* Fill every token in the grid */
		while (token)
		{
			grid[i] = token;
			token = strtok(NULL, delim);
			i++;
		}
		/* The grid must be null terminated - check man exceve */
		grid[i] = NULL;
	}
	free(cmd_cpy);
	return (grid);
}

