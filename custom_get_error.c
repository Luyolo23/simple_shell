#include "shell.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @data: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(data_shell *data, int eval)
{
char *error;

switch (eval)
{
case -1:
error = error_env(data);
break;
case 126:
error = error_path_126(data);
break;
case 127:
error = error_not_found(data);
break;
case 2:
if (_strcmp("exit", data->arguments[0]) == 0)
error = error_exit_shell(data);
else if (_strcmp("cd", data->arguments[0]) == 0)
error = error_get_cd(data);
break;
}

if (error)
{
write(STDERR_FILENO, error, _strlen(error));
free(error);
}

data->status = eval;
return (eval);
}
