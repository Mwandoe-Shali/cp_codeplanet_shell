#include "simple_shell.h"

/**
 * free_ptr - frees a pointer and NULLs the address
 * @ptr: address of  pointer to be freed
 * Return: 1 if freed, else 0.
 */
int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
