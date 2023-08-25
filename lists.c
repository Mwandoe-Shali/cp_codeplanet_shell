#include "simple_shell.h"

/**
 * add_node_beginning - It adds a node at the beginning
 * @head: The address of pointer to  the head node
 * @str: The str's field of a node
 * @num: The index os node used  *
 * Return: The list size
 */
list_st *add_node_beginning(list_st **head, const char *str, int num)
{
	list_st *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_st));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_st));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * ins_node_end - inserts a node to the end of a list
 * @head: address of a pointer to the head node
 * @str: str's node field
 * @num: index of the node
 * Return: list's size
 */
list_st *ins_node_end(list_st **head, const char *str, int num)
{
	list_st *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_st));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_st));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - It prints str elements of list_st linked list
 * @ptr: The pointer to start node
 * Return: The list's node
 */
size_t print_list_str(const list_st *ptr)
{
	size_t ai = 0;

	while (ptr)
	{
		_puts(ptr->str ? ptr->str : "(nil)");
		_puts("\n");
		ptr = ptr->next;
		ai++;
	}
	return (ai);
}

/**
 * del_node_at_index - deletes node at a given index
 * @head: address of pointer to first node
 * @index: index of node to be deleted *
 * Return: on success 1, on failure 0
 */
int del_node_at_index(list_st **head, unsigned int index)
{
	list_st *node, *prev_node;
	unsigned int ai = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (ai == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		ai++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * frees_lists - It frees all lists
 * @ptr_head: The pointer to head node
 * Return: Nothing
 */
void frees_lists(list_st **ptr_head)
{
	list_st *node, *next_node, *head;

	if (!ptr_head || !*ptr_head)
		return;
	head = *ptr_head;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*ptr_head = NULL;
}
