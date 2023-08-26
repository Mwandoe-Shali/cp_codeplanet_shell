#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read and wrtite buffers sizes */
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* for chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for converting a number functon */
#define CONVERT_LOWER    	1
#define CONVERT_UNSIGNED	2

/* when using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: number off ields
 * @str: a string
 * @next: pointer to the to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_st;

/**
 * struct custom_info - Contains arguments for shell functions
 * @arg: A command input obtained from the user
 * @argv: An array of arguments parsed from the input command
 * @line_count: Count of the current input line
 * @err_num: Error code for tracking errors
 * @linecount_flag: Flag indicating the line count mode
 * @fname: Filename of the shell program
 * @env: Linked list storing environment variables
 * @environ: Custom copy of the environment variable list
 * @history: Linked list for storing command history
 * @alias: Linked list for managing command aliases
 * @env_changed: Flag indicating environment changes
 * @status: Return status of the previous executed command
 * @cmd_buff: Address of a pointer to the command buffer
 * @cmd_buff_type: Type of command in the buffer
 * @readfd: File descriptor for reading line input
 * @histcount: History line number count
 * @path: Path to a file
 * @argc: Argument count for the current command
 */
typedef struct custom_info
{
    char *arg;
    char **argv;
    char *path;
    int argc;
    unsigned int line_count;
    int err_num;
    int linecount_flag;
    char *fname;
    list_t *env;
    list_t *history;
    list_t *alias;
    char **environ;
    int env_changed;
    int status;

    char **cmd_buff;
    int cmd_buff_type;
    int readfd;
    int histcount;
} cm_info;



#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains builtin function strings
 *@type: builtin command flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(cm_info *);
} builtin_table;


/* shell_loop.c */
int prompt(cm_info *cu_info, char **av);
int _get_builtin(cm_info *cu_info);
void _get_cmd(cm_info *cu_info);
void _fork_(cm_info *cu_info);

/* parser.c */
int checks_cmd(cm_info *cu_info, char *path);
char *copy_chars(char *str_path, int start, int end);
char *get_loc(cm_info *cu_info, char *str_path, char *command);

/* loop_prompt.c */
int loop_prompt(char **);

/* errors.c */
void _eputs_(char *s);
int _eputchar_(char ch);
int _put_fd(char ch, int fd);
int _puts_fd(char *s, int fd);

/* string.c */
int str_len(const char *str);
int str_cmp(char *str1, char *str2);
char *_starts_with(const char *sea, const char *pearl);
char *str_cat(char *dest, char *src);

/* string1.c */
char *str_cpy(char *dest, char *src);
char *str_dup(const char *str);
void _puts_(char *str);
int _putchar_(char ch);

/* exits.c */
char *str_cpy(char *dest, char *src, int num);
char *str_cat(char *dest, char *src, int num);
char *find_chr(char *str, char ch);

/* tokenizer.c */
char **str_tow(char *str, char *delim);
char **_str_tow(char *str, char delim);

/* realloc.c */
char *_memset_(char *store, char b, unsigned int num);
void free_str(char **ds);
void *_realloc_(void *ptr, unsigned int prev_size, unsigned int new_size);

/* memory.c */
int free_ptr(void **ptr);

/* _atoi.c */
int _is_interactive(cm_info *cu_info);
int _is_delim(char ch, char *delim);
int _is_alpha(int ch);
int _atoi_(char *str);

/* errors1.c */
int _err_atoi(char *str);
void _print_err(cm_info *cu_info, char *err_str);
int _print_dec(int input, int fd);
char *num_convert(long int num, int base, int flags);
void alt_comments(char *buff);

/* builtin.c */
int _exit_(cm_info *cu_info);
int _cd_(cm_info *cu_info);
int _help_(cm_info *cu_info);

/* builtin1.c */
int _history_(cm_info *cu_info);
int _unset_alias(cm_info *cu_info, char *str);
int _set_alias(cm_info *cu_info, char *str);
int _print_alias(list_st *al_node);
int _alias_(cm_info *cu_info;

/* getline.c */
ssize_t buff_input(cm_info *cu_info, char **buff, size_t *len);
ssize_t _get_input(cm_info *cu_info);
ssize_t _read_buff(cm_info *cu_info, char *buff, size_t *sz);
int _get_line(cm_info *cu_info, char **ptr, size_t *len);
void ctrl_c_handler(__attribute__((unused))int sig_num);

/* getinfo.c */
void _init_info(cm_info *cu_info);
void sets_info(cm_info *cu_info, char **args);
void frees_cu_info(cm_info *cu_info, int all);

/* environ.c */
int _myenv_(cm_info *cu_info);
char *_getenv_(cm_info *cu_info, const char *name);
int _mysetenv_(cm_info *cu_info);
int _myunsetenv_(cm_info *cu_info);
int _env_list(cm_info *cu_info);

/* getenv.c */
char **find_env(cm_info *cu_info);
int _unsetenv_(cm_info *cu_info, char *value);
int _setenv_(cm_info *cu_info, char *var, char *value);

/* history.c */
char *gets_history(cm_info *cu_info);
int creates_history(cm_info *cu_info);
int reads_history(cm_info *cu_info);
int builds_history_list(cm_info *cu_info, char *buff, int linecount);
int numbers_history(cm_info *cu_info);

/* lists.c */
list_st *add_node_beginning(list_st **head, const char *str, int num);
list_st *ins_node_end(list_st **head, const char *str, int num);
size_t print_list_str(const list_st *ptr);
int del_node_at_index(list_st **head, unsigned int index);
void frees_lists(list_st **ptr_head);

/* lists1.c */
size_t len_lists(const list_st *ptr_node);
char **list_of_strings(list_st *head);
size_t prints_list(const list_st *ptr_node);
list_st *node_starts_(list_st *ptr_head, char *prefix, char ch);
ssize_t get_node_index(list_st *ptr_head, list_st *node);

/* vars.c */
int is_chain(cm_info *cu_info, char *buff, size_t *ptr);
void checks_chain(cm_info *cu_info, char *buff, size_t *ptr, size_t ai, size_t len);
int replace_alias(cm_info *cu_info);
int replace_vars(cm_info *cu_info);
int replace_string(char **old, char *new);

#endif /* SIMPLE_SHELL_H */
