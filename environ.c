#include "simple_shell.h"

/**
 * _myenv_ - It prints the current environ
 * @cu_info: The struct contaning info.
 * Return: Always (0)
 */
int _myenv_(cm_info *cu_info)
{
	print_list_str(cu_info->env);
	return (0);
}

/**
 * _getenv_ - It gets the value of an environment var
 * @cu_info: The struct containing potential arguments
 * @name: The environment variable name
 * Return: The value of the variable
 */
char *_getenv_(cm_info *cu_info, const char *name)
{
	list_st *node = cu_info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv_ - It creates new environment variable,
 *             or modifies an existing one
 * @cu_info: The struct containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always (0)
 */
int _mysetenv_(cm_info *cu_info)
{
	if (cu_info->argc != 3)
	{
		_eputs("Incorrect number of arguements \n");
		return (1);
	}
	if (_setenv(cu_info, cu_info->argv[1], cu_info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv_ - It removes an environment variable
 * @cu_info: The struct containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always (0)
 */
int _myunsetenv_(cm_info *cu_info)
{
	int ai;

	if (cu_info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (ai = 1; ai <= cu_info->argc; ai++)
		_unsetenv(cu_info, cu_info->argv[ai]);

	return (0);
}

/**
 * _env_list - It generates env linked list
 * @cu_info: The struct containing potential arguments.
 * Return: Always 0
 */
int _env_list(cm_info *cu_info)
{
	list_st *node = NULL;
	size_t ai;

	for (ai = 0; environ[ai]; ai++)
		ins_node_end(&node, environ[ai], 0);
	cu_info->env = node;
	return (0);
}
