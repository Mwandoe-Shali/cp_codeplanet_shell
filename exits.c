#include "simple_shell.h"

/**
 * str_cpy - copies a string to another buffer
 * @dest: the destination string
 * @src: the source string
 * @num: the number of chars to be copied
 * Return: The copied string
 */
char *str_cpy(char *dest, char *src, int num)
{
	int a, b;
	char *str = dest;

	a = 0;
	while (src[a] != '\0' && a < num - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < num)
	{
		b = a;
		while (b < num)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (str);
}

/**
 * str_cat - concatenates  strings
 * @dest: first string
 * @src: second string
 * @num: the num of chars  used
 * Return: the concatenated string
 */
char *str_cat(char *dest, char *src, int num)
{
	int a, b;
	char *str = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < num)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < num)
		dest[a] = '\0';
	return (str);
}

/**
 * find_chr - finds a character in a string
 * @str: the string to be passed
 * @ch: the character to be searched
 * Return: (s) a pointer to  s
 */
char *find_chr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
