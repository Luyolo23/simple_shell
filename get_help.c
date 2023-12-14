#include "shell.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @datash: data structure (args and input)
 * Return: Return 0
*/
int get_help(custom_shell_data *datash)
{

if (datash->args[1] == 0)
disp_general_help();
else if (_strcmp(datash->args[1], "setenv") == 0)
disp_setenv_help();
else if (_strcmp(datash->args[1], "env") == 0)
disp_env_help();
else if (_strcmp(datash->args[1], "unsetenv") == 0)
disp_unsetenv_help();
else if (_strcmp(datash->args[1], "help") == 0)
displayHelpInfo();
else if (_strcmp(datash->args[1], "exit") == 0)
disp_exit_help();
else if (_strcmp(datash->args[1], "cd") == 0)
displayCdHelp();
else if (_strcmp(datash->args[1], "alias") == 0)
displayAliasHelp();
else
write(STDERR_FILENO, datash->args[0],
_strlen(datash->args[0]));

datash->status = 0;
return (1);
}
