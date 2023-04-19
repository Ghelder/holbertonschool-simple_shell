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
		/**
		 * if (strcmp(s, "exit") == 0)
		 * {
		 * free(s);
		 * break;
		 * }
		 **/
		args = tokenize(s);
		run = execute_program(args, argv, envp);
		for (j = 0; j < TOKENS_SIZE; j++)
			free(args[j]);
		free(args);
	}
	return (0);
}
