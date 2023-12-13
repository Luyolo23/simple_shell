#include "shell.h"

/**
 * swap_special_chars - swaps | and & for non-printed chars
 *
 * @input: input string
 * @is_swapping: type of swap
 * Return: swapped string
 */
char *swap_special_chars(char *input, int is_swapping)
{
int i;

if (is_swapping == 0)
{
for (i = 0; input[i]; i++)
{
if (input[i] == '|')
{
if (input[i + 1] != '|')
input[i] = 16;
else
i++;
}

if (input[i] == '&')
{
if (input[i + 1] != '&')
input[i] = 12;
else
i++;
}
}
}
else
{
for (i = 0; input[i]; i++)
{
input[i] = (input[i] == 16 ? '|' : input[i]);
input[i] = (input[i] == 12 ? '&' : input[i]);
}
}
return (input);
}

/**
 * add_sep_and_commands - add separators and command lines in the lists
 *
 * @sep_head: head of separator list
 * @cmd_head: head of command lines list
 * @input: input string
 * Return: no return
 */
void add_sep_and_commands(sep_list **sep_head,
		line_list **cmd_head, char *input)
{
int i;
char *line;

input = swap_special_chars(input, 0);

for (i = 0; input[i]; i++)
{
if (input[i] == ';')
add_separator_node_end(sep_head, input[i]);

if (input[i] == '|' || input[i] == '&')
{
add_separator_node_end(sep_head, input[i]);
i++;
}
}

line = _strtok(input, ";|&");
do {
line = swap_special_chars(line, 1);
add_line_node_end(cmd_head, line);
line = _strtok(NULL, ";|&");
} while (line != NULL);
}

/**
 * move_to_next - go to the next command line stored
 *
 * @sep_list: separator list
 * @cmd_list: command line list
 * @data: data structure
 * Return: no return
 */
void move_to_next(sep_list **sep_list, line_list **cmd_list,
		custom_shell_data *data)
{
sep_list *current_sep;
line_list *current_cmd;
int loop_sep;

loop_sep = 1;
current_sep = *sep_list;
current_cmd = *cmd_list;

while (current_sep != NULL && loop_sep)
{
if (data->status == 0)
{
if (current_sep->separator == '&' || current_sep->separator == ';')
loop_sep = 0;
if (current_sep->separator == '|')
current_cmd = current_cmd->next, current_sep = current_sep->next;
}
else
{
if (current_sep->separator == '|' || current_sep->separator == ';')
loop_sep = 0;
if (current_sep->separator == '&')
current_cmd = current_cmd->next, current_sep = current_sep->next;
}
if (current_sep != NULL && !loop_sep)
current_sep = current_sep->next;
}

*sep_list = current_sep;
*cmd_list = current_cmd;
}

/**
 * process_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @data: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int process_commands(custom_shell_data *data, char *input)
{

sep_list *sep_head, *current_sep;
line_list *cmd_head, *current_cmd;
int loop;

sep_head = NULL;
cmd_head = NULL;

add_sep_and_commands(&sep_head, &cmd_head, input);

current_sep = sep_head;
current_cmd = cmd_head;

while (current_cmd != NULL)
{
data->input = current_cmd->line;
data->arguments = split_cmd_line(data->input);
loop = exec_line(data);
free(data->arguments);

if (loop == 0)
break;

move_to_next(&current_sep, &current_cmd, data);

if (current_cmd != NULL)
current_cmd = current_cmd->next;
}

free_separator_list(&sep_head);
free_line_list(&cmd_head);

if (loop == 0)
return (0);
return (1);
}

/**
 * split_cmd_line - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **split_cmd_line(char *input)
{
size_t bsize;
size_t i;
char **tokens;
char *token;

bsize = TOK_BUFSIZE;
tokens = malloc(sizeof(char *) * (bsize));
if (tokens == NULL)
{
write(STDERR_FILENO, ": allocation error\n", 18);
exit(EXIT_FAILURE);
}

token = _strtok(input, TOK_DELIM);
tokens[0] = token;

for (i = 1; token != NULL; i++)
{
if (i == bsize)
{
bsize += TOK_BUFSIZE;
tokens = _reallocate_dp(tokens, i, sizeof(char *) * bsize);
if (tokens == NULL)
{
write(STDERR_FILENO, ": allocation error\n", 18);
exit(EXIT_FAILURE);
}
}
token = _strtok(NULL, TOK_DELIM);
tokens[i] = token;
}

return (tokens);
}
