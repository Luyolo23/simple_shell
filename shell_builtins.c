#include "shell.h"

/**
 * my_exit - exits the shell
 * @info: Structure containing potential arguments.
 *  Return: exits with a given exit status
 *         (0) if info->argv[0] != "exit"
 */
int my_exit(info_t *info)
{
int exit_check;

if (info->argv[1])
{
exit_check = _erratoi(info->argv[1]);
if (exit_check == -1)
{
info->status = 2;
print_error(info, "Illegal number: ");
_eputs(info->argv[1]);
_eputchar('\n');
return (1);
}
info->err_num = _erratoi(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int my_cd(info_t *info)
{
char *current_dir, *new_dir, buffer[1024];
int chdir_ret;
current_dir = getcwd(buffer, 1024);
if (!current_dir)
{
print_error(info, "getcwd failure\n");
return (1);
}
if (!info->argv[1])
{
new_dir = _getenv(info, "HOME=");
if (!new_dir)
chdir_ret = chdir((new_dir = _getenv(info, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(new_dir);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(current_dir);
_putchar('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
chdir_ret = chdir((new_dir = _getenv(info, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
print_error(info, "can't cd to ");
_eputs(info->argv[1]), _eputchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * my_help - Displays help information
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int my_help(info_t *info)
{
(void)info;
_puts("help call works. Function not yet implemented\n");
return (0);
}
