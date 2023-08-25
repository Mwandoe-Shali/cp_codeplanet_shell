#include "simple_shell.h"

/**
 * gets_history -  It finds history file
 * @cu_info: The custom struct
 * Return: The string containing history file
 */
char *gets_history(cm_info *cu_info)
{
	char *buff, *dir;

	dir = _getenv(cu_info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * creates_history - It creates or appends to an existing file
 * @cu_info: The param struct
 * Return: 1 on success,  -1 on failure
 */
int creates_history(cm_info *cu_info)
{
	ssize_t fd;
	char *file = get_history(cu_info);
	list_st *node = NULL;

	if (!file)
		return (-1);

	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (fd == -1)
		return (-1);
	for (node = cu_info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * reads_history - It reads history from file
 * @cu_info: The param struct
 * Return: The history count on success, 0 on failure
 */
int reads_history(cm_info *cu_info)
{
	int ai, last = 0, lc = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history(cu_info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (ai = 0; ai < fsize; ai++)
		if (buff[ai] == '\n')
		{
			buff[ai] = 0;
			build_history_list(cu_info, buff + last, lc++);
			last = ai + 1;
		}
	if (last != i)
		build_history_list(cu_info, buff + last, lc++);
	free(buff);
	cu_info->histcount = lc;
	while (cu_info->histcount-- >= HIST_MAX)
		del_node_at_index(&(cu_info->history), 0);
	number_history(cu_info);
	return (cu_info->histcount);
}

/**
 * builds_history_list - It appends entry to a history linked list
 * @cu_info: The struct containing potential arguments.
 * @buff: The buffer to build to.
 * @linecount: The history linecount, histcount
 *
 * Return: Always (0)
 */
int builds_history_list(cm_info *cu_info, char *buff, int linecount)
{
	list_st *node = NULL;

	if (cu_info->history)
		node = cu_info->history;
	ins_node_end(&node, buff, linecount);

	if (!cu_info->history)
		cu_info->history = node;
	return (0);
}

/**
 * numbers_history - It numbers the history linked list afresh after changes
 * @info: The struct containing potential arguments
 * Return: The new history count
 */
int numbers_history(cm_info *cu_info)
{
	list_st *node = cu_info->history;
	int ai = 0;

	while (node)
	{
		node->num = ai++;
		node = node->next;
	}
	return (cu_info->histcount = ai);
}
