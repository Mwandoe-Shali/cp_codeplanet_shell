#include "simple_shell.h"

/**
 * _err_atoi - converts a string to int
 * @str: string to be converted
 * Return: converted number
 *       -1 on error
 */
int _err_atoi(char *str)
{
	int a = 0;
	unsigned long int result = 0;

	/* Skip leading '+' sign */
	if (*str == '+')
		str++;
	for (a = 0;  str[a] != '\0'; a++)
	{
		/* Check if the character is a digit */
		if (str[a] >= '0' && str[a] <= '9')
		{
			result *= 10;
			result += (str[a] - '0');
			/* Check for integer overflow */
			if (result > INT_MAX)
				return (-1);
		}
		/* Non-digit character found, return error */
		else
			return (-1);
	}
	return (result);
}

/**
 * _print_err - prints an error message
 * @cu_info: the parameter & return custom info struct
 * @err_str: string containing  error type
 * Return: 0 if no nums, converted num else
 *        -1 on error
 */
void _print_err(cm_info *cu_info, char *err_str)
{
	_eputs(cu_info->fname);
	_eputs(": ");
	print_dec(cu_info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(cu_info->argv[0]);
	_eputs(": ");
	_eputs(err_str);
}

/**
 * _print_dec - function prints a (integer) decimal / base 10
 * @input: The input entered by user
 * @fd: The filedescriptor
 * Return: The number of chars printed
 */
int _print_dec(int input, int fd)
{
	int (*__putchar_)(char) = _putchar_;
	int a, b = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar_ = _eputchar_;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		b++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + curr / a);
			b++;
		}
		curr %= a;
	}
	__putchar('0' + curr);
	b++;

	return (b);
}

/**
 * num_convert - Custom replica atoi, converter function
 * @num: The number to be converted
 * @base: The base value
 * @flags: The argument's flags
 * Return: A string on success
 */
char *num_convert(long int num, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char sign = 0;
	char *ptr;
	unsigned long number = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		number = -num;
		sign = '-';

	}
	arr = flags & CONVERT_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[number % base];
		number /= base;
	} while (number != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * alt_comments - changes first instance of '#' with '\0'
 * @buff: address of the string to change
 * Return:  0;
 */
void alt_comments(char *buff)
{
	int ai;

	for (ai = 0; buff[ai] != '\0'; ai++)
		if (buff[ai] == '#' && (!ai || buff[ai - 1] == ' '))
		{
			buff[ai] = '\0';
			break;
		}
}
