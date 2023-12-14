#include "shell.h"

/**
 * get_builtin - builtin that pass the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(custom_shell_data *)
{
builtin_t builtin[] = {
{ "env", print_variables},
{ "exit", exit_shell },
{ "setenv", _set_variable },
{ "unsetenv", _unset_variable },
{ "cd", cd_shell },
{ "help", get_help },
{ NULL, NULL }
};
int i;

for (i = 0; builtin[i].name; i++)
{
if (_strcmp(builtin[i].name, cmd) == 0)
break;
}

return (builtin[i].f);
}
