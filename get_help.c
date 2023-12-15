#include "shell.h"

/**
 * get_help - retrieves help messages according builtin
 * @data: data structure
 * Return: Return 0
*/
int get_help(data_shell *data)
{

if (data->arguments[1] == 0)
custom_help_general();
else if (_strcmp(data->arguments[1], "setenv") == 0)
custom_help_setenv();
else if (_strcmp(data->arguments[1], "env") == 0)
custom_help_env();
else if (_strcmp(data->arguments[1], "unsetenv") == 0)
custom_help_unsetenv();
else if (_strcmp(data->arguments[1], "help") == 0)
custom_help();
else if (_strcmp(data->arguments[1], "exit") == 0)
custom_help_exit();
else if (_strcmp(data->arguments[1], "cd") == 0)
custom_help_cd();
else if (_strcmp(data->arguments[1], "alias") == 0)
custom_help_alias();
else
write(STDERR_FILENO, data->arguments[0],
_strlen(data->arguments[0]));

data->status = 0;
return (1);
}
