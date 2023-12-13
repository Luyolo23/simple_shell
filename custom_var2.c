#include "shell.h"

/**
 * duplicate_info - duplicates information to create
 * a new variable or setting
 * @name: name (variable or setting)
 * @value: value (variable or setting)
 *
 * Return: new variable or setting.
 */
char *duplicate_info(char *name, char *value)
{
char *new_info;
int len_name, len_value, len;

len_name = _strlen(name);
len_value = _strlen(value);
len = len_name + len_value + 2;
new_info = malloc(sizeof(char) * (len));
_strcpy(new_info, name);
_strcat(new_info, "=");
_strcat(new_info, value);
_strcat(new_info, "\0");

return (new_info);
}

/**
 * set_variable - sets a variable or setting
 *
 * @name: name of the variable or setting
 * @value: value of the variable or setting
 * @shell_data: data structure (variables or settings)
 * Return: no return
 */
void set_variable(char *name, char *value, shell_data *shell_data)
{
int i;
char *var_info, *name_info;

for (i = 0; shell_data->_variables[i]; i++)
{
var_info = _strdup(shell_data->_variables[i]);
name_info = _strtok(var_info, "=");
if (_strcmp(name_info, name) == 0)
{
free(shell_data->_variables[i]);
shell_data->_variables[i] = duplicate_info(name_info, value);
free(var_info);
return;
}
free(var_info);
}

shell_data->_variables = _reallocdp
(shell_data->_variables, i, sizeof(char *) * (i + 2));
shell_data->_variables[i] = duplicate_info(name, value);
shell_data->_variables[i + 1] = NULL;
}

/**
 * _set_variable - compares variable names and sets a new variable or setting
 * @shell_data: data relevant (variable name and variable value)
 *
 * Return: 1 on success.
 */
int _set_variable(shell_data *shell_data)
{
if (shell_data->args[1] == NULL || shell_data->args[2] == NULL)
{
get_error(shell_data, -1);
return (1);
}

set_variable(shell_data->args[1], shell_data->args[2], shell_data);

return (1);
}

/**
 * _unset_variable - deletes a variable or setting
 *
 * @shell_data: data relevant (variable name)
 *
 * Return: 1 on success.
 */
int _unset_variable(shell_data *shell_data)
{
char **realloc_variables;
char *var_info, *name_info;
int i, j, k;

if (shell_data->args[1] == NULL)
{
get_error(shell_data, -1);
return (1);
}
k = -1;
for (i = 0; shell_data->_variables[i]; i++)
{
var_info = _strdup(shell_data->_variables[i]);
name_info = _strtok(var_info, "=");
if (_strcmp(name_info, shell_data->args[1]) == 0)
{
k = i;
}
free(var_info);
}
if (k == -1)
{
get_error(shell_data, -1);
return (1);
}
realloc_variables = malloc(sizeof(char *) * (i));
for (i = j = 0; shell_data->_variables[i]; i++)
{
if (i != k)
{
realloc_variables[j] = shell_data->_variables[i];
j++;
}
}
realloc_variables[j] = NULL;
free(shell_data->_variables[k]);
free(shell_data->_variables);
shell_data->_variables = realloc_variables;
return (1);
}
