#include "simple_shell.h"

/**
 * _history_ - Displays the history list. 1 command per line.
 * @cu_info: The custom info struct
 *  Return: 0
 */
int _history_(cm_info *cu_info)
{
	printList(cu_info->history);
	return (0);
}

/**
 * _unset_alias - Sets alias to a string
 * @cu_info:  A custom Infostruct
 * @str:  String alias
 * Return: 0 on success, 1 on error
 */
int _unset_alias(cm_info *cu_info, char *str)
{
	char *ptr, ch;
	int retan;

	ptr = str_chr(str, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	retan = del_node_at_index(&(cu_info->alias),
		get_node_index(cu_info->alias, node_starts_(cu_info->alias, str, -1)));
	*ptr = ch;
	return (retan);
}

/**
 * _set_alias - sets alias
 * @cu_info: struct
 * @str: alias to string
 * Return: Always 0 on success, 1 on error
 */
int _set_alias(cm_info *cu_info, char *str)
{
	char *pt;

	pt = str_chr(str, '=');
	if (!pt)
		return (1);
	if (!*++pt)
		return (unset_alias(cu_info, str));

	unset_alias(cu_info, str);
	return (ins_node_end(&(cu_info->alias), str, 0) == NULL);
}

/**
 * _print_alias - prints string alias
 * @al_node: the alias node
 * Return: 0 on success, 1 on error
 */
int _print_alias(list_st *al_node)
{
	char *j = NULL, *ptr = NULL;

	if (al_node)
	{
		ptr = str_chr(al_node->str, '=');
		for (j = al_node->str; j <= ptr; j++)
			_putchar(*j);
		_putchar('\'');
		_puts_(ptr + 1);
		_puts_("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias_ - Custom alias builtin function (man alias)
 * @cu_info: Custom struct info.
 *  Return: 0
 */
int _alias_(cm_info *cu_info)
{
	int j = 0;
	char *ptr = NULL;
	list_st *node = NULL;

	if (cu_info->argc == 1)
	{
		node = cu_info->alias;
		while (node)
		{
			_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; cu_info->argv[j]; j++)
	{
		ptr = str_chr(cu_info->argv[j], '=');
		if (ptr)
			_set_alias(cu_info, cu_info->argv[j]);
		else
			_print_alias(node_starts_(cu_info->alias, cu_info->argv[j], '='));
	}

	return (0);
}
