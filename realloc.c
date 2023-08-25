#include "simple_shell.h"

/**
 **_memset_ - stores in a memory a constant byte
 *@store: pointer to the memory
 *@b: byte to fill a string with
 *@num: amt of bytes to be filled
 *Return: a pointer to the memory area s
 */
char *_memset_(char *store, char b, unsigned int num)
{
	unsigned int j;

	for (j = 0; j < num; j++)
		store[j] = b;
	return (store);
}

/**
 * free_str - frees a string of strings
 * @ds: string of strings (double string)
 */
void free_str(char **ds)
{
	char **str = ds;

	if (!ds)
		return;
	while (*ds)
		free(*ds++);
	free(str);
}

/**
 * _realloc_ - reallocates a block of memory
 * @ptr: pointer to previous malloc allocated block
 * @prev_size: byte size of prev block
 * @new_size: byte size of the new block
 * Return: pointer to old memory.
 */
void *_realloc_(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	char *str;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == prev_size)
		return (ptr);

	str = malloc(new_size);
	if (!str)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		str[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (str);
}
