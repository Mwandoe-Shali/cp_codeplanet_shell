#include "simple_shell.h"

/**
 * prompt - the prompt loop
 * @cu_info: the custom information struct
 * @av: an array of null terminated strings
 * Return: 0 on success, 1 on failure
 */
int prompt(cm_info *cu_info, char **av)
{
	ssize_t retan = 0;
	int builtin_retan = 0;

	while (retan != -1 && builtin_retan != -2)
	{
		init_info(cu_info);
		if (is_interactive(cu_info))
			_puts("$ ");
		_eputchar(BUFF_FLUSH);
		retan = get_input(cu_info);
		if (retan != -1)
		{
			set_info(cu_info, av);
			builtin_retan = get_builtin(cu_info);
			if (builtin_retan == -1)
				get_cmd(cu_info);
		}
		else if (is_interactive(cu_info))
			_putchar('\n');
		free_info(cu_info, 0);
	}
	create_history(cu_info);
	free_info(cu_info, 1);
	if (!is_interactive(cu_info) && cu_info->status)
		exit(cu_info->status);
	if (builtin_retan == -2)
	{
		if (cu_info->err_num == -1)
			exit(cu_info->status);
		exit(cu_info->err_num);
	}
	return (builtin_retan);
}

/**
 * _get_builtin - gets a builtin cmd
 * @cu_info: the custom information struct
 * Return: -1 if builtin fails,
 *			0 when builtin is successfully,
 *			1 when builtin found but fails,
 *			-2 when builtin signals exit()
 */
int _get_builtin(cm_info *cu_info)
{
	int j, builtin_return = -1;
	builtin_table built_tbl[] = {
		{"exit", _exit_},
		{"env", _env_},
		{"help", _help_},
		{"history", _history_},
		{"setenv", _setenv_},
		{"unsetenv", _unsetenv_},
		{"cd", _cd_},
		{"alias", _alias_},
		{NULL, NULL}
	};

	for (j = 0; built_tbl[j].type; j++)
		if (_strcmp(cu_info->argv[0], built_tbl[j].type) == 0)
		{
			cu_info->line_count++;
			builtin_return = built_tbl[j].func(cu_info);
			break;
		}
	return (builtin_return);
}

/**
 * _get_cmd - looks for a command in PATH
 * @cu_info: custom information struct
 * Return: void
 */
void _get_cmd(cm_info *cu_info)
{
	char *path = NULL;
	int a, b;

	cu_info->path = cu_info->argv[0];
	if (cu_info->linecount_flag == 1)
	{
		cu_info->line_count++;
		cu_info->linecount_flag = 0;
	}
	for (a = 0, b = 0; cu_info->arg[a]; a++)
		if (!is_delim(cu_info->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = _get_location(cu_info, _get_env(cu_info, "PATH="), cu_info->argv[0]);
	if (path)
	{
		cu_info->path = path;
		_fork_(cu_info);
	}
	else
	{
		if ((is_interactive(cu_info) || _get_env(cu_info, "PATH=")
			|| cu_info->argv[0][0] == '/') && check_cmd(cu_info, cu_info->argv[0]))
			_fork_(cu_info);
		else if (*(cu_info->arg) != '\n')
		{
			cu_info->status = 127;
			print_err(cu_info, "not found\n");
		}
	}
}

/**
 * _fork_ - creates a child process
 * @cu_info: info struct
 * Return: void
 */
void _fork_(cm_info *cu_info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(cu_info->path, cu_info->argv, find_environ(cu_info)) == -1)
		{
			free_info(cu_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(cu_info->status));
		if (WIFEXITED(cu_info->status))
		{
			cu_info->status = WEXITSTATUS(cu_info->status);
			if (cu_info->status == 126)
				print_err(cu_info, "Permission denied\n");
		}
	}
}
