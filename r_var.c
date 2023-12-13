#include "shell.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @list: head of linked list
 * @input: input string
 * @data: data structure
 * Return: no return
 */
void check_env(r_var **list, char *input, data_shell *data)
{
int row, chr, j, lval;
char **env_vars;

env_vars = data->environment;
for (row = 0; env_vars[row]; row++)
 {
for (j = 1, chr = 0; env_vars[row][chr]; chr++)
{
if (env_vars[row][chr] == '=')
{
lval = _strlen(env_vars[row] + chr + 1);
add_var_node(list, j, env_vars[row] + chr + 1, lval);
return;
}

if (input[j] == env_vars[row][chr])
j++;
else
break;
}
}

for (j = 0; input[j]; j++)
{
if (input[j] == ' ' || input[j] == '\t' || input[j] == ';' || input[j] == '\n')
break;
}

add_var_node(list, j, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @list: head of the linked list
 * @input: input string
 * @status: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(r_var **list, char *input, char *status, data_shell *data)
{
int i, status_len, pid_len;

status_len = _strlen(status);
pid_len = _strlen(data->process_id);

for (i = 0; input[i]; i++)
{
if (input[i] == '$')
{
if (input[i + 1] == '?')
add_var_node(list, 2, status, status_len), i++;
else if (input[i + 1] == '$')
add_var_node(list, 2, data->process_id, pid_len), i++;
else if (input[i + 1] == '\n' || input[i + 1] == '\0' || input[i + 1] == ' ' ||
input[i + 1] == '\t' || input[i + 1] == ';')
add_var_node(list, 0, NULL, 0);
else
check_env(list, input + i, data);
}
}

return (i);
}

/**
 * replaced_input - replaces string into variables
 *
 * @list: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @new_len: new length
 * Return: replaced string
 */
char *replaced_input(r_var **list, char *input, char *new_input, int new_len)
{
r_var *current;
int i, j, k;

current = *list;
for (j = i = 0; i < new_len; i++)
{
if (input[j] == '$')
{
if (!(current->len_var) && !(current->len_val))
{
new_input[i] = input[j];
j++;
}
else if (current->len_var && !(current->len_val))
{
for (k = 0; k < current->len_var; k++)
j++;
i--;
}
else
{
for (k = 0; k < current->len_val; k++)
{
new_input[i] = current->value[k];
i++;
}
j += (current->len_var);
i--;
}
current = current->next;
}
else
{
new_input[i] = input[j];
j++;
}
}

return (new_input);
}

/**
 * replace_variables - calls functions to replace string into vars
 *
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *replace_variables(char *input, data_shell *datash)
{
r_var *list, *current;
char *status, *new_input;
int original_len, new_len;

status = int_to_str(datash->status);
list = NULL;

original_len = check_vars(&list, input, status, datash);

if (list == NULL)
{
free(status);
return (input);
}

current = list;
new_len = 0;

while (current != NULL)
{
new_len += (current->len_val - current->len_var);
current = current->next;
}

new_len += original_len;

new_input = malloc(sizeof(char) * (new_len + 1));
new_input[new_len] = '\0';

new_input = replaced_input(&list, input, new_input, new_len);

free(input);
free(status);
free_var_node(&list);

return (new_input);
}

