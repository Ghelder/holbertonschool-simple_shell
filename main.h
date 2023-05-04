#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define UNUSED(x) (void)(x)

char *_strcat(char *dest, char *src);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *tokenizer_path(char **args, char **envp);
char **tokenizer_cmd(char *);
int check_env(char **envp);
int check_builtins(char **args, char **envp, int, char **argv);
int check_cmd(char **args, char **envp, char **argv,
		int *flag, char **path, int counter, char *);
char *_strchr(char *s, char c);
void signal_handler(int);
char *trim_spaces(char *);
void help_builtin(char *);
#endif
