#include "simple_shell.h"

/**
 * find_env - prints a list of environ
 * @cu_info: info struct
 * Return: Always (0)
 */
char **find_env(cm_info *cu_info)
{
	if (!cu_info->environ || cu_info->env_changed)
	{
		cu_info->environ = list_of_strings(cu_info->env);
		cu_info->env_changed = 0;
	}

	return (cu_info->environ);
}

/**
 * _unsetenv_ - It unsets an environment
 * @cu_info: The potential arguments for cm_info struct.
 * @value: The value to find environ
 * Return: 1 on success, 0 on failure
 */
int _unsetenv_(cm_info *cu_info, char *value)
{
	char *p;
	list_st *node = cu_info->env;
	size_t ai = 0;

	if (!node || !value)
		return (0);

	while (node)
	{
		p = starts_(node->str, value);
		if (p && *p == '=')
		{
			cu_info->env_changed = del_node_at_index(&(cu_info->env), ai);
			ai = 0;
			node = cu_info->env;
			continue;
		}
		node = node->next;
		ai++;
	}
	return (cu_info->env_changed);
}

/**
 * _setenv_ - It sets environments
 * @cu_info: The struct holding potential arguments
 * @var: The environment variable
 * @value: The value
 * Return: Always (0)
 */
int _setenv_(cm_info *cu_info, char *var, char *value)
{
	char *buff = NULL;
	list_st *node;
	char *ch;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = cu_info->env;
	while (node)
	{
		ch = starts_(cu_info->str, var);
		if (ch && *ch == '=')
		{
			free(node->str);
			node->str = buff;
			cu_info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	ins_node_end(&(cu_info->env), buff, 0);
	free(buff);
	cu_info->env_changed = 1;
	return (0);
}
