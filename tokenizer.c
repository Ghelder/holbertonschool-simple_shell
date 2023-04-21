#include "main.h"
/**
  * my_strchr - buscar la ultima similitatd de un caracter
  * @s: stringdonde se buscará
  * @c: caracter a buscar
  * Return: lo que sigue a lo que se busca
  */
char *my_strrchr(const char *s, int c)
{
	char *result = NULL;
	char ch;

	while ((ch = *s++) != '\0')
	{
		if (ch == c)
		{
			result = (char *)(s - 1);
		}
	}
	return (result);
}
/**
  * tokenizer_path - busca el path y ejecuta el comando si existe
  * @args: lo que obtenemos del getline
  * @envp: envirement
  * Return: path
  */
char *tokenizer_path(char **args, char **envp)
{
	char *slash, *path, *copy_path, *full_path, *dir;
	int fd = -1, i;

	slash = my_strrchr(*args, '/');
	if (slash)
		*args = slash;
	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break;
		}
	}
	if (path == NULL)
		return (NULL);
	copy_path = strdup(path);
	dir = strtok(copy_path, ":");
	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(args[0]) + 2);
		if (full_path == NULL)
		{
			free(copy_path);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, args[0]);
		fd = open(full_path, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			break;
		}
		free(full_path);
		full_path = NULL;
		dir = strtok(NULL, ":");
	}
	free(copy_path);
	return (full_path);
}
