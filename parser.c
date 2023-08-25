#include "simple_shell.h"

/**
 * checks_cmd - checks whether supplied input is an executable command
 * @cu_info: struct custom info
 * @path: is the files path
 * Return: 1 on success, 0 on fail
 */
int checks_cmd(cm_info *cu_info, char *path)
{
	struct stat sc;

	(void)cu_info;
	if (!path || stat(path, &sc))
		return (0);

	if (sc.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * copy_chars - creates a copy of characters
 * @str_path: the strings path
 * @start: first index
 * @end: last index
 *
 * Return: the new buffer
 */
char *copy_chars(char *str_path, int start, int end)
{
	static char buff[1024];
	int a = 0, b = 0;

	for (j = 0, a = start; a < end; a++)
		if (str_path[a] != ':')
			buff[b++] = strpath[a];
	buff[b] = 0;
	return (buff);
}

/**
 * get_loc - gets the command path
 * @cu_info:  info struct
 * @str_path: the PATH string
 * @command: the command
 * Return: full path to the command
 */
char *get_loc(cm_info *cu_info, char *str_path, char *command)
{
	int a = 0, current = 0;
	char *path;

	if (!str_path)
		return (NULL);
	if ((_strlen(command) > 2) && starts_(command, "./"))
	{
		if (check_cmd(cu_info, command))
			return (command);
	}
	while (1)
	{
		if (!str_path[a] || str_path[a] == ':')
		{
			path = copy_chars(str_path, current, a);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (check_cmd(cu_info, path))
				return (path);
			if (!str_path[a])
				break;
			current = a;
		}
		a++;
	}
	return (NULL);
}
