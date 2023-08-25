#include "simple_shell.h"

/**
 * buff_input - The buffer commands
 * @cu_info: The parameter struct
 * @buff: The address of the buffer
 * @len: The address of then len var
 * Return: The number of bytes read by the function
 */
ssize_t buff_input(cm_info *cu_info, char **buff, size_t *len)
{
	ssize_t num = 0;
	size_t length_p = 0;

	if (!*len) /* if nothing left in buffer, fill it */
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandle);
#if USE_GETLINE
		num = getline(buff, &length_p, stdin);
#else
		num = _getline(cu_info, buff, &length_p);
#endif
		if (num > 0)
		{
			if ((*buff)[num - 1] == '\n')
			{
				/* remove trailing newline */
				(*buff)[num - 1] = '\0';
				num--;
			}
			cu_info->linecount_flag = 1;
			change_comments(*buff);
			build_history_list(cu_info, *buff, cu_info->histcount++);
			{
				*len = num;
				cu_info->cmd_buf = buff;
			}
		}
	}
	return (num);
}

/**
 * _get_input - It gets a line without the newline
 * @cu_info: The custom parameter struct
 * Return: The number of bytes read
 */
ssize_t _get_input(cm_info *cu_info)
{
	static char *buff;
	static size_t a, b, len;
	ssize_t num = 0;
	char **buff_p = &(cu_info->arg), *pt;

	_putchar(BUFF_FLUSH);
	num = input_buff(cu_info, &buff, &len);
	if (num == -1) /* EOF */
		return (-1);
	if (len)
	{
		b = a;
		pt = buff + a;

		check_chain(cu_info, buff, &b, a, len);
		while (b < len)
		{
			if (is_chain(cu_info, buff, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			cu_info->cmd_buf_type = CMD_NORM;
		}

		*buff_p = pt;
		return (str_len(pt));
	}

	*buff_p = buff;
	return (num);
}

/**
 * _read_buff - It reads the buffer
 * @cu_info: The param struct
 * @buff: The buffer
 * @sz: The size of buffer
 * Return: The number of bytes
 */
ssize_t _read_buff(cm_info *cu_info, char *buff, size_t *sz)
{
	ssize_t num = 0;

	if (*sz)
		return (0);
	
	num = read(cu_info->readfd, buff, READ_BUFF_SIZE);
	if (num >= 0)
		*sz = num;
	return (num);
}

/**
 * _get_line - A dopplegang of getline
 * @cu_info: The param struct
 * @ptr: The address of pointer to buffe
 * @len: The size of preallocated ptr
 * Return: The number of bytes
 */
int _get_line(cm_info *cu_info, char **ptr, size_t *len)
{
	static char buff[READ_BUFF_SIZE];
	static size_t ai, length;
	size_t jb;
	ssize_t num = 0, s = 0;
	char *p = NULL, *new_p = NULL, *ch;

	p = *ptr;
	if (p && len)
		s = *len;
	if (ai == length)
		ai = length = 0;

	num = read_buff(cu_info, buff, &length);
	if (num == -1 || (num == 0 && length == 0))
		return (-1);

	ch = str_chr(buff + ai, '\n');
	jb = ch ? 1 + (unsigned int)(ch - buff) : length;
	new_p = _realloc(p, s, s ? s + jb : jb + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		str_cat(new_p, buff + ai, jb - ai);
	else
		str_cpy(new_p, buff + ai, jb - ai + 1);

	s += jb - ai;
	ai = jb;
	p = new_p;

	if (len)
		*len = s;
	*ptr = p;
	return (s);
}

/**
 * ctrl_c_handler - It handles ctrl-C, when its pressed
 * @sig_num: The signal number
 * Return: Nothing
 */
void ctrl_c_handler(__attribute__((unused))int sig_num)
{
	_puts_("\n");
	_puts_("$GshellX$>>> ");
	_putchar_(BUFF_FLUSH);
}
