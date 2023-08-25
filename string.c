#include "simple_shell.h"

/**
 * str_len - Returns the length of a string
 * @str: Pointer to the string
 * Return: Length of the string
 */
int str_len(const char *str)
{
	int counter = 0;

	while (*str != '\0')
	{
		counter++;
		str++;
	}

	return (counter);
}

/**
 * str_cmp - compares two strangs.
 * @str1: first string to compare
 * @str2: 2nd string to compare
 * Return: -1 if s1 < s2,
 * 		1 if s1 > s2,
 * 		0 if s1 is same as s2.
 */
int str_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * _starts_with - checks whether a pearl begins with sea
 * @sea: string to be searched
 * @pearl: the substring to be searched
 * Return: address to the next char of haystack or NULL
 */
char *_starts_with(const char *sea, const char *pearl)
{
	while (*pearl)
		if (*pearl++ != *sea++)
			return (NULL);
	return ((char *)sea);
}

/**
 * str_cat - concatenates two supplied strings
 * @dest: the destination memory
 * @src: the source memory
 * Return: pointer to the destination memory
 */
char *str_cat(char *dest, char *src)
{
	char *retan = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (retan);
}
