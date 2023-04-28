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
