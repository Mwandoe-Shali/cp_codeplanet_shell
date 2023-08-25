#include "simple_shell.h"

/**
 * len_lists - It finds length of a linked list
 * @ptr_node: The address to the pointer to first node
 * Return: list's size
 */
size_t len_lists(const list_st *ptr_node)
{
	size_t ai = 0;

	while (ptr_node)
	{
		ptr_node = ptr_node->next;
		ai++;
	}
	return (ai);
}

/**
 * list_of_strings - returns an array of strings of a lis
 * @head: address to the pointer to first node
 * Return: an array of strings
 */
char **list_of_strings(list_st *head)
{
	list_st *node = head;
	size_t ai = lists_len(head), jb;
	char **strs;
	char *st;

	if (!head || !ai)
		return (NULL);
	strs = malloc(sizeof(char *) * (ai + 1));
	if (!strs)
		return (NULL);
	for (ai = 0; node; node = node->next, ai++)
	{
		st = malloc(_strlen(node->str) + 1);
		if (!st)
		{
			for (jb = 0; jb < ai; jb++)
				free(strs[jb]);
			free(strs);
			return (NULL);
		}

		st = _strcpy(st, node->str);
		strs[ai] = st;
	}
	strs[ai] = NULL;
	return (strs);
}


/**
 * prints_list - Prints all elements of a linked list
 * @ptr_node: The address to the pointer to first node
 * Return: List's szie
 */
size_t prints_list(const list_st *ptr_node)
{
	size_t ai = 0;

	while (ptr_node)
	{
		_puts(convert_num(ptr_node->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(ptr_node->str ? ptr_node->str : "(nil)");
		_puts("\n");
		ptr_node = ptr_node->next;
		ai++;
	}
	return (ai);
}

/**
 * node_starts_ - returns node whose string starts with a givenprefix
 * @ptr_head: The address pointer to list head
 * @prefix: string to get
 * @ch: the character after prefix to find
 * Return: match node
 */
list_st *node_starts_(list_st *ptr_head, char *prefix, char ch)
{
	char *p = NULL;

	while (ptr_head)
	{
		p = starts_(ptr_head->str, prefix);
		if (p && ((ch == -1) || (*p == ch)))
			return (ptr_head);
		ptr_head = ptr_head->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a certain node
 * @ptr_head: The address pointer to list head
 * @ptr_node: adress topointer to the node
  * Return:nodes index or -1
 */
ssize_t get_node_index(list_st *ptr_head, list_st *node)
{
	size_t ai = 0;

	while (ptr_head)
	{
		if (ptr_head == ptr_node)
			return (i);
		ptr_head = ptr_head->next;
		ai++;
	}
	return (-1);
}
