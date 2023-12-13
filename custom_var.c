#include "shell.h"

/**
 * compare_variable_name - compares variable names
 * @var: name of the variable
 * @name: name passed
 *
 * Return: 0 if they are not equal. Another value if they are.
 */
int compare_variable_name(const char *var, const char *name)
{
int i;

for (i = 0; var[i] != '='; i++)
{
if (var[i] != name[i])
{
return (0);
}
}

return (i + 1);
}

/**
 * get_variable - get a variable value
 * @name: name of the variable
 * @variables: array of variables
 *
 * Return: value of the variable if found. Otherwise, returns NULL.
 */
char *get_variable(const char *name, char **variables)
{
char *ptr_var;
int i, mov;

ptr_var = NULL;
mov = 0;
for (i = 0; variables[i]; i++)
{
mov = compare_variable_name(variables[i], name);
if (mov)
{
ptr_var = variables[i];
break;
}
}

return (ptr_var + mov);
}

/**
 * print_variables - prints the variables
 *
 * @shell_data: data relevant.
 * Return: 1 on success.
 */
int print_variables(shell_data *shell_data)
{
int i, j;

for (i = 0; shell_data->variables[i]; i++)
{
for (j = 0; shell_data->variables[i][j]; j++)
;

write(STDOUT_FILENO, shell_data->variables[i], j);
write(STDOUT_FILENO, "\n", 1);
}
shell_data->status = 0;

return (1);
}
