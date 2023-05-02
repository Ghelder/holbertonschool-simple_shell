#include "main.h"

/**
  * signal_handler - function to to execute if a signal exist
  * @sig: The signal number
  * If C-c (Ctrl-c) is pressed just print the prompt
  *
  * Return: Void
  *
  */

void signal_handler(int sig)
{
	UNUSED(sig);
	printf("\n#cisfun$ ");
	fflush(stdout);
}

/**
  * trim_spaces - function to clean spaces at the beginning
  * @str: The string to be cleaned
  * Delete spaces at the beginning of the command
  *
  * Return: the new command
  *
  */

char *trim_spaces(char *str)
{
	char *command;

	command = str;
	if (*(str + 0) == 32 || *(str + 0) == 9)
	{
		while (*command)
		{
			if (*command != 32 && *command != 9)
				return (command);
			command++;
		}
	}
	return (str);
}

/**
  * help_builtin - function to print help
  * @cmd: The comand to be helped
  * Print help information of a builtin command
  *
  * Return: Void
  *
  */

void help_builtin(char *cmd)
{
	char *help = NULL;

	help = calloc(sizeof(char), (_strlen(cmd) + 11));
	sprintf(help, "bash -c '%s'", cmd);
	help[_strlen(cmd) + 10] = '\0';
	system(help);
	free(help);
}
