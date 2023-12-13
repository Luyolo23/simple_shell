#include "shell.h"

/**
 * cd_shell - changes the current directory
 * @data: data relevant
 * Return: 1 on success
 */
int cd_shell(shell_data *data)
{
char *dir;
int is_home, is_home2, is_ddash;

dir = data->args[1];

if (dir != NULL)
{
is_home = _strcmp("$HOME", dir);
is_home2 = _strcmp("~", dir);
is_ddash = _strcmp("--", dir);
}

if (dir == NULL || !is_home || !is_home2 || !is_ddash)
{
cd_home(data);
return (1);
}

if (_strcmp("-", dir) == 0)
{
cd_prev(data);
return (1);
}

if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
{
cd_parent(data);
return (1);
}

cd_to_dir(data);

return (1);
}

