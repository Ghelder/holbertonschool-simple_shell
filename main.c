#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#define UNUSED(x) (void)(x)

/**
 * main - Entry point
 * @argc: The number of arguments passed
 * @argv: The array containing the arguments
 * @envp: The array of variable enviroments
 *
 * Execute my own shell
 *
 * Return: 0 all success
 *
 */
int main(int argc, char **argv, char **envp)
{
	ssize_t chars, rtn;
	int i, run = 1;
	size_t size = 10;
	char *s;

	UNUSED(argc);
	s = malloc(sizeof(char) * size);

	i = 0;
	while (*(s + i))
	{
		*(s + i) = '\0';
		i++;
	}
	while (run)
	{
		printf("#cisfun$ ");
		chars = getline(&s, &size, stdin);
		if (chars == -1)
		{
			putchar(10);
			free(s);
			break;
		}

		if (strcmp(s, "exit\n") == 0)
		{
			free(s);
			break;
		}
		if (*s == '\n')
			printf("%s", "");
		else
		{
			rtn = execve(s, argv, envp);
			if (rtn == -1)
				printf("%s: No such file or directory\n", argv[0]);
		}
	}
	return (0);
}
