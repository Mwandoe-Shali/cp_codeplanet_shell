#include "simple_shell.h"

/**
 * _init_info - It initializes cm_info struct
 * @cu_info: The struct address'
 * Returns: Nothing
 */
void _init_info(cm_info *cu_info)
{
	cu_info->arg = NULL;
	cu_info->argv = NULL;
	cu_info->path = NULL;
	cu_info->argc = 0;
}

/**
 * sets_info - It sets cm_info struct
 * @cu_info: struct address
 * @args: The argument parsed
 */
void sets_info(cm_info *cu_info, char **args)
{
	int num = 0;

	cu_info->fname = args[0];
	if (cu_info->arg)
	{
		cu_info->argv = strtow(cu_info->arg, " \t");
		if (!cu_info->argv)
		{

			cu_info->argv = malloc(sizeof(char *) * 2);
			if (cu_info->argv)
			{
				cu_info->argv[0] = _strdup(cu_info->arg);
				cu_info->argv[1] = NULL;
			}
		}
		for (num = 0; cu_info->argv && cu_info->argv[num]; num++)
			;
		cu_info->argc = num;

		replace_alias(cu_info);
		replace_vars(cu_info);
	}
}

/**
 * frees_cu_info - It frees struct fields
 * @cu_info: The struct's address
 * @all: Its true when freeing all the fields
 */
void frees_cu_info(cm_info *cu_info, int all)
{
	sfree(cu_info->argv);
	cu_info->argv = NULL;
	cu_info->path = NULL;
	if (all)
	{
		if (!cu_info->cmd_buf)
			free(cu_info->arg);
		if (cu_info->env)
			freeLists(&(cu_info->env));
		if (cu_info->history)
			freeLists(&(cu_info->history));
		if (cu_info->alias)
			freeLists(&(cu_info->alias));
		sfree(cu_info->environ);
			cu_info->environ = NULL;
		my_free((void **)cu_info->cmd_buf);
		if (cu_info->readfd > 2)
			close(cu_info->readfd);
		_putchar(BUFF_FLUSH);
	}
}
