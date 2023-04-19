#include "main.h"

/**
 * _strcpy - function to copy a string
 * @dest: New string copied
 * @src: The string to be copied
 * Copy an string to another variable
 *
 * Return: Pointer to dest
 *
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
 * _strlen - function to get the length
 * @s: The string to be evaluated
 * Swap values of two integers
 *
 * Return: Length of a string
 *
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; *s != '\0'; s++)
		i++;
	return (i);
}

/**
 * _strcat - function to concatenate
 * @dest: The character to be evaluated
 * @src: The character to be evaluated
 * Concatenates two strings
 *
 * Return: Pointer to the resulting dest
 *
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
