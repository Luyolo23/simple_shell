#ifndef SHELL_H
#define SHELL_H

#include <limits.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;

/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @custom_arg_name: name of the arguments
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
char *custom_arg_name;
char **av;
char *input;
char **args;
int status;
int counter;
char **_environ;
char *pid;

} custom_shell_data;

/**
 * struct sep_list - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list
{
	char separator;
	struct sep_list *next;
} sep_list;

/**
 * struct line_list - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list
{
	char *line;
	struct line_list *next;
} line_list;

/**
 * struct r_var - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var
{
	int len_var;
	char *val;
	int len_val;
	struct r_var *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;


/* shows the prompt */
void show_prompt(void);

/* display - Writes a message to standard output */
void display(const char *text);

/* readCmd - Reads a command from standard input */
void readCmd(char *command, size_t size);

/* execCmd - Executes a shell command */
void execCmd(const char *command);

/* is_executable - Determines if a file is an executable command */
int is_executable(info_t *info, char *file_path);

/* copy_chars - Duplicates characters from a source string */
char *copy_chars(char *source_str, int start_index, int stop_index);

/* find_executable_path - Finds the path of an executable in the PATH string */
char *find_executable_path(info_t *info, char *path_str, char *command);

/* custom_help */
void disp_env_help(void);
void disp_setenv_help(void);
void disp_unsetenv_help(void);
void disp_general_help(void);
void disp_exit_help(void);

/* custom_help2 */
void displayHelpInfo(void);
void displayAliasHelp(void);
void displayCdHelp(void);

/* custom_split */
char *swap_special_chars(char *input, int is_swapping);
void add_sep_and_commands(sep_list **sep_head,
		line_list **cmd_head, char *input);
void move_to_next(sep_list **sep_list, line_list **cmd_list, data_shell *data);
int process_commands(data_shell *data, char *input);

/* custom_lists1 */
sep_list *add_separator_node_end(sep_list **head, char separator);
void free_separator_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *command_line);
void free_line_list(line_list **head);

/* custom_lists2 */
r_var *add_var_node(r_var **h, int len_var, char *val, int len_val);
void free_var_list(r_var **h);

/* custom_error */
char *custom_strcat_cd(custom_shell_data *custom_data, char *custom_msg,
		char *custom_error, char *custom_ver_str);
char *custom_error_get_cd(custom_shell_data *custom_data);
char *custom_error_not_found(custom_shell_data *custom_data);
char *custom_error_exit_shell(custom_shell_data *custom_data);

/* custom_error2 */
char *custom_aux_itoa(int num);
size_t custom_strlen(const char *str);
char *custom_strcpy(char *dest, const char *src);
char *custom_strcat(char *dest, const char *src);
char *custom_error_env(custom_shell_data *custom_data);
char *custom_error_path_126(custom_shell_data *custom_data);

/* custom_mem */
void _cpy(void *dest, const void *src, unsigned int size);
void *_reallocate(void *ptr, unsigned int old, unsigned int new);
char **_reallocate_dp(char **ptr, unsigned int old, unsigned int new);

/* custom_cd */
void cd_parent(shell_data *data);
void cd_to_dir(shell_data *data);
void cd_prev(shell_data *data);
void cd_home(shell_data *data);

/* custom_cd2 */
void cd_shell(shell_data *data);

/* custom_syntax_check */
int count_repeated(char *input, int i);
int find_syntax_error(char *input, int i, char last);
int find_first_char_index(char *input, int *index);
void print_syntax_error_msg(data_shell *datash,
		char *input, int index, int bool);
int check_syntax_error(data_shell *datash, char *input);

/* custom_var */
int compare_variable_name(const char *var, const char *name);
char *get_variable(const char *name, char **variables);
int print_variables(shell_data *shell_data);

/* custom_var2 */
char *duplicate_info(char *name, char *value);
void set_variable(char *name, char *value, shell_data *shell_data);
int _set_variable(shell_data *shell_data);
int _unset_variable(shell_data *shell_data);

/* int_conversion */
int get_num_length(int num);
int str_to_int(char *s);
char *int_to_str(int num);

/* str_func */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* custom_str */
char *_strdup(const char *original_str);
int _strlen(const char *str);
int chars_equal(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* custom_exit_sh */
int exit_shell(data_shell *datash);

/* read_line.c */
char *read_line(int *i_eof);

#endif /* SHELL_H */
