#include "shell.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @custom_data: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(custom_shell_data *custom_data, int eval)
{
char *error;

switch (eval)
{
case -1:
error = custom_error_env(custom_data);
break;
case 126:
error = custom_error_path_126(custom_data);
break;
case 127:
error = custom_error_not_found(custom_data);
break;
case 2:
if (_strcmp("exit", custom_data->args[0]) == 0)
error = custom_error_exit_shell(custom_data);
else if (_strcmp("cd", custom_data->args[0]) == 0)
error = custom_error_get_cd(custom_data);
break;
}

if (error)
{
write(STDERR_FILENO, error, _strlen(error));
free(error);
}

custom_data->status = eval;
return (eval);
}
