#include "simple_shell.h"

/**
 * _is_interactive - returns true when shell is on interactive mode
 * @cu_info: struct address
 * Return: 1 when on interactive mode, 0 otherwise
 */
int _is_interactive(cm_info *cu_info)
{
	return (isatty(STDIN_FILENO) && cu_info->readfd <= 2);
}

/**
 * _is_delim - checks whether a char is a delimeter
 * @ch: char to check
 * @delim: the delimeter
 * Return: 1 on true, 0 on false
 */
int _is_delim(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}

/**
 * _is_alpha - checks whether acharacter is an alphabet
 * @ch: character to check
 * Return: 1 if alphabetic, 0 if not
 */

int _is_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi_ - converts a string to an integer
 * @str: String to be converted
 * Return: The converted integer if valid, otherwise 0
 */
int _atoi_(char *str)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	/* Loop through the string */
	for (a = 0;  str[a] != '\0' && flag != 2; a++)
	{
		/* Check for a negative sign */
		if (str[a] == '-')
			sign *= -1;

		/* Check if the character is a digit */
		if (str[a] >= '0' && str[a] <= '9')
		{
			flag = 1;
			/* Convert character to digit and add to result */
			result *= 10;
			result += (str[a] - '0');
		}
		/* If non-digit character appears after digits, stop processing */
		else if (flag == 1)
			flag = 2;
	}

	/* Apply sign to the result */
	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
