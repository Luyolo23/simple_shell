#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @arguments: tokens of the command line
 * @status: last status of the shell
 * @custom_counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **arguments;
	int status;
	int custom_counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *data);
} builtin_t;

/* custom_list1.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* custom_lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* str_func.c */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* custom_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/*custom_str.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/*rev_str.c */
void rev_string(char *s);

/* check_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_shell *data, char *input, int i, int bool);
int check_syntax_error(data_shell *data, char *input);

/* custom_loop.c */
char *without_comment(char *in);
void shell_loop(data_shell *data);

/* read_line.c */
char *read_line(int *i_eof);

/* custom_split.c */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *data);
int split_commands(data_shell *data, char *input);
char **split_line(char *input);

/* r_var.c */
void check_env(r_var **h, char *in, data_shell *data);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_shell *data);

/* custom_get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(data_shell *data);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *data);
int check_error_cmd(char *dir, data_shell *data);
int cmd_exec(data_shell *data);

/* custom_var.c */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *data);

/* custom_var2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *data);
int _setenv(data_shell *data);
int _unsetenv(data_shell *data);

/* custom_cd.c */
void cd_dot(data_shell *data);
void cd_to(data_shell *data);
void cd_previous(data_shell *data);
void cd_to_home(data_shell *data);

/* custom_cd2.c */
int cd_shell(data_shell *data);

/* get_builtin */
int (*get_builtin(char *cmd))(data_shell *data);

/* custom_exit_shell */
int exit_shell(data_shell *data);

/* int_conversion.c */
int get_len(int n);
char *custom_itoa(int n);
int _atoi(char *s);

/* custom_error.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *data);
char *error_not_found(data_shell *data);
char *error_exit_shell(data_shell *data);

/* custom_error2.c */
char *error_get_alias(char **arguments);
char *error_env(data_shell *data);
char *error_syntax(char **arguments);
char *error_permission(char **arguments);
char *error_path_126(data_shell *data);


/* custom_get_error.c */
int get_error(data_shell *data, int eval);

/* get_sigint.c */
void get_sigint(int sig);

/* custom_help.c */
void custom_help_env(void);
void custom_help_setenv(void);
void custom_help_unsetenv(void);
void custom_help_general(void);
void custom_help_exit(void);

/* custom_help2.c */
void custom_help(void);
void custom_help_alias(void);
void custom_help_cd(void);

/* get_help.c */
int get_help(data_shell *data);

#endif /*END SHELL_H*/
