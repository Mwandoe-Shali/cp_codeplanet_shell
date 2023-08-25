#include "simple_shell.h"

/**
 * _exit_ - Quits the shell
 * @cu_info: info struct containing possible args. Used to maintain
 * constant function prototype.
 *
 *  Return: quits shell with a given exit status
 */
int _exit_(cm_info *cu_info)
{
	int check_exit;

	if (cu_info->argv[1])
	{
		check_exit = _err_atoi(cu_info->argv[1]);
		if (check_exit == -1)
		{
			cu_info->status = 2;
			print_err(cu_info, "Invalid number: ");
			_eputs(cu_info->argv[1]);
			_eputchar('\n');
			return (1);
		}

		cu_info->err_num = _err_atoi(cu_info->argv[1]);
		return (-2);
	}
	cu_info->err_num = -1;
	return (-2);
}

/**
 * _cd_ - changes  directory
 * @cu_info: info struct
 *  Return: 0 on success
 */
int _cd_(cm_info *cu_info)
{
	char *str, *dir, buff[1024];
	int chdir_return;

	str = getcwd(buff, 1024);
	if (!str)
		_puts_("getcwd failure \n");
	if (!cu_info->argv[1])
	{
		dir = _getenv(cu_info, "HOME=");
		if (!dir)
			chdir_return =
				chdir((dir = _getenv(cu_info, "PWD=")) ? dir : "/");
		else
			chdir_return = chdir(dir);
	}
	else if (_strcmp(cu_info->argv[1], "-") == 0)
	{
		if (!_getenv(cu_info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(cu_info, "OLDPWD=")), _putchar('\n');
		chdir_return =
			chdir((dir = _getenv(cu_info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_return = chdir(cu_info->argv[1]);
	if (chdir_return == -1)
	{
		_print_err(cu_info, "Unable to change directory");
		_eputs(cu_info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv_(cu_info, "OLDPWD", _getenv_(cu_info, "PWD="));
		_setenv_(cu_info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _help_ - help function
 * @cu_info: info struct
 *  Return: (0) Always.
 */
int _help_(cm_info *cu_info)
{
	char **arg_arr;

	arg_arr = cu_info->argv;
	_puts("Not yet implemented!!! \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
