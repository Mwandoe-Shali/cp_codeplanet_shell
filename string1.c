#include "simple_shell.h"

/**
 * str_cpy - copies a string to anothe buffr
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer to destination buffer
 */
char *str_cpy(char *dest, char *src)
{
	int k = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[k])
	{
		dest[k] = src[k];
		k++;
	}
	dest[k] = 0;
	return (dest);
}

/**
 * str_dup - creates a duplicate of a string
 * @str: the string to be duplicated
 * Return: pointer tonew duplicated string
 */
char *str_dup(const char *str)
{
	int length = 0;
	char *retan;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	retan = malloc(sizeof(char) * (length + 1));
	if (!retan)
		return (NULL);
	for (length++; length--;)
		retan[length] = *--str;
	return (retan);
}

/**
 *_puts_ - outputs an a string to the standard output
 *@str: the string to be printed
 * Return: void
 */
void _puts_(char *str)
{
	int k = 0;

	if (!str)
		return;
	while (str[k] != '\0')
	{
		_putchar_(str[k]);
		k++;
	}
}

/**
 * _putchar_ - writes a character c to stdout
 * @ch: The character to supplied *
 * Return: 1 on success, -1, on error
 */
int _putchar_(char ch)
{
	static int j;
	static char buff[WRITE_BUFF_SIZE];

	if (ch == BUFF_FLUSH || j >= WRITE_BUFF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		buff[j++] = ch;
	return (1);
}
