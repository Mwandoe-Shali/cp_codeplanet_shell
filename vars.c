#include "simple_shell.h"

/**
 * is_chain - Checks whther  current char is a chain delimeter
 * @cu_info: The param struct
 * @buff: Char buffer
 * @ptr: Address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(cm_info *cu_info, char *buff, size_t *ptr)
{
	size_t jb = *ptr;

	if (buff[jb] == '|' && buff[jb + 1] == '|')
	{
		buff[jb] = 0;
		jb++;
		cu_info->cmd_buf_type = CMD_OR;
	}
	else if (buff[jb] == '&' && buff[jb + 1] == '&')
	{
		buff[jb] = 0;
		jb++;
		cu_info->cmd_buf_type = CMD_AND;
	}
	else if (buff[jb] == ';') /* found end of this command */
	{
		buff[jb] = 0; /* replace semicolon with null */
		cu_info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = jb;
	return (1);
}

/**
 * checks_chain - Checks continuing chaining based on last status
 * @cu_info: The param struct
 * @buff: The char buffer
 * @ptr: Address of current position in buffer
 * @ai: Starting position in buffer
 * @len: Length of buffer
 * Return: Nothing
 */
void checks_chain(cm_info *cu_info, char *buff, size_t *ptr, size_t ai, size_t len)
{
	size_t jb = *ptr;

	if (cu_info->cmd_buf_type == CMD_AND)
	{
		if (cu_info->status)
		{
			buff[ai] = 0;
			jb = len;
		}
	}
	if (cu_info->cmd_buf_type == CMD_OR)
	{
		if (!cu_info->status)
		{
			buff[ai] = 0;
			jb = len;
		}
	}

	*ptr = jb;
}

/**
 * replace_alias - Replaces aliases in the tokenized string
 * @cu_info: The param struct
 * Return: 1 if successful, 0 on failure
 */
int replace_alias(cm_info *cu_info)
{
	int ai;
	list_st *node;
	char *ch;

	for (ai = 0; ai < 10; ai++)
	{
		node = node_starts_(cu_info->alias, cu_info->argv[0], '=');
		if (!node)
			return (0);
		free(cu_info->argv[0]);
		ch = str_chr(node->str, '=');
		if (!ch)
			return (0);
		ch = _strdup(ch + 1);
		if (!ch)
			return (0);
		cu_info->argv[0] = ch;
	}
	return (1);
}

/**
 * replace_vars - Replaces vars in the tokenized string
 * @cu_info: The parameter struct
 *
 * Return: 1 on success, 0 on failure
 */
int replace_vars(cm_info *cu_info)
{
	int ai = 0;
	list_st *node;

	for (ai = 0; cu_info->argv[ai]; ai++)
	{
		if (cu_info->argv[ai][0] != '$' || !cu_info->argv[ai][1])
			continue;

		if (!_strcmp(cu_info->argv[ai], "$?"))
		{
			replace_string(&(cu_info->argv[ai]),
				_strdup(convert_num(cu_info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(cu_info->argv[ai], "$$"))
		{
			replace_string(&(cu_info->argv[ai]),
				_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_(cu_info->env, &cu_info->argv[ai][1], '=');
		if (node)
		{
			replace_string(&(cu_info->argv[ai]),
				_strdup(str_chr(node->str, '=') + 1));
			continue;
		}
		replace_string(&cu_info->argv[ai], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Replaces string
 * @old: Address of old string
 * @new: The new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
