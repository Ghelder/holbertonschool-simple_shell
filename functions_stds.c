#include "main.h"
/**
  * _strcpy - funcion
  * @dest: variable
  * @src: variable
  * Return: dest
  */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/**
  * _strlen - funcion
  * @s: variable
  * Return:nada
  */
int _strlen(char *s)
{
	int i;

	for (i = 0; *s != '\0'; s++)
	{
		i++;
	}
	return (i);
}
/**
  * _strcat - funcion
  * @dest: puntero 1
  * @src: puntero 2
  * Return: dest
  */
char *_strcat(char *dest, char *src)
{
	int d = 0;
	int s = 0;
	int co;

	while (dest[d] != '\0')
		d++;
	while (src[s] != '\0')
		s++;
	for (co = 0; co <= s; co++)
	{
		dest[d] = src[co];
		d++;
	}
	return (dest);
}
