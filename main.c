#include "simple_shell.h"

/**
 * main - Shell's entry point
 * @agc: The count of arguements supplied
 * @agv: An array of null terminated characters
 * Return: 0 on success 1 on failure
 */
int main(int agc, char **agv)
{
	cm_info cu_info[] = { INFO_INIT };
	int file_d = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_d)
		: "r" (file_d));

	if (agc == 2)
	{
		file_d = open(agv[1], O_RDONLY);
		if (file_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(agv[0]);
				_eputs(": 0: Open error! ");
				_eputs(agv[1]);
				_eputchar('\n');
				_eputchar(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		cu_info->readfd = file_d;
	}
	env_list(cu_info);
	read_history(cu_info);
	prompt(cu_info, agv);
	return (EXIT_SUCCESS);
}
