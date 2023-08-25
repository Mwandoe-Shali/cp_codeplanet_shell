#include "simple_shell.h"

/**
 * str_tow - splits a string into words
 * @str: the  string to split
 * @delim: the delimeter string
 * Return: a pointer to an array of strings
 */
char **str_tow(char *str, char *delim)
{
	int a, b, c, m, num_words = 0;
	char **token;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], delim) && (is_delim(str[a + 1], delim) || !str[a + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	token = malloc((1 + num_words) * sizeof(char *));
	if (!token)
		return (NULL);
	for (a = 0, b = 0; b < num_words; b++)
	{
		while (is_delim(str[a], delim))
			a++;
		c = 0;
		while (!is_delim(str[a + c], delim) && str[a + c])
			c++;
		token[b] = malloc((c + 1) * sizeof(char));
		if (!token[b])
		{
			for (c = 0; c < b; c++)
				free(token[c]);
			free(token);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			token[b][m] = str[a++];
		token[b][m] = 0;
	}
	token[b] = NULL;
	return (token);
}

/**
 * _str_tow - splits a string into words
 * @str: input string
 * @delim: delimeter
 * Return: a pointer to an array of strings
 */
char **_str_tow(char *str, char delim)
{
	int a, b, c, m, num_words = 0;
	char **token;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != delim && str[a + 1] == delim) ||
		    (str[a] != delim && !str[a + 1]) || str[a + 1] == delim)
			num_words++;
	if (num_words == 0)
		return (NULL);
	token = malloc((1 + num_words) * sizeof(char *));
	if (!token)
		return (NULL);
	for (a = 0, b = 0; b < num_words; b++)
	{
		while (str[a] == delim && str[a] != delim)
			a++;
		c = 0;
		while (str[a + c] != delim && str[a + c] && str[a + c] != delim)
			c++;
		token[b] = malloc((c + 1) * sizeof(char));
		if (!token[b])
		{
			for (c = 0; c < b; c++)
				free(token[c]);
			free(token);
			return (NULL);
		}
		for (m = 0; m < c; m++)
			token[b][m] = str[a++];
		token[b][m] = 0;
	}
	token[b] = NULL;
	return (token);
}
