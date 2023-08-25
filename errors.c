#include "simple_shell.h"

/**
 * _eputs_ - prints an err string
 * @s: the err to be printed
 * Returns: void
 */
void _eputs_(char *s)
{
	int a = 0;

	if (!s)
		return;
	while (s[a] != '\0')
	{
		_eputchar_(s[a]);
		a++;
	}
}

/**
 * _eputchar_ - writes a character to stderr
 * @ch: character to be printed
 * Return: 1 on success, On error -1
 */
int _eputchar_(char ch)
{
	static int a;
	static char buff[WRITE_BUFF_SIZE];

	if (ch == BUFF_FLUSH || a >= WRITE_BUFF_SIZE)
	{
		write(2, buff, a);
		a = 0;
	}
	if (ch != BUFF_FLUSH)
		buff[a++] = ch;
	return (1);
}

/**
 * _put_fd - writes the character ch to given file_d
 * @ch: character tobe printend
 * @fd: The file to write to *
 * Return: On success 1. -1 on error
 */
int _put_fd(char ch, int fd)
{
	static int a;
	static char buff[WRITE_BUFF_SIZE];

	if (ch == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buff, a);
		a = 0;
	}
	if (ch != BUFF_FLUSH)
		buff[a++] = ch;
	return (1);
}

/**
 * _puts_fd - prints string suplied
 * @s: string to print
 * @fd: file descriptor
 * Return: 1 on success, on error NULL
 */
int _puts_fd(char *s, int fd)
{
	int a = 0;

	if (!s)
		return (0);
	while (*s)
	{
		a += _put_fd(*s++, fd);
	}
	return (a);
}
