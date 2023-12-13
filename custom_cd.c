#include "shell.h"

/**
 * cd_parent - changes to the parent directory
 *
 * @data: shell data (environ)
 *
 * Return: no return
 */
void cd_parent(custom_shell_data *data)
{
char pwd[PATH_MAX];
char *dir, *cp_pwd, *cp_strtok_pwd;

getcwd(pwd, sizeof(pwd));
cp_pwd = _strdup(pwd);
set_variable("OLDPWD", cp_pwd, data);
dir = data->args[1];

if (_strcmp(".", dir) == 0)
{
set_variable("PWD", cp_pwd, data);
free(cp_pwd);
return;
}

if (_strcmp("/", cp_pwd) == 0)
{
free(cp_pwd);
return;
}

cp_strtok_pwd = cp_pwd;
rev_string(cp_strtok_pwd);
cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");

if (cp_strtok_pwd != NULL)
{
cp_strtok_pwd = _strtok(NULL, "\0");

if (cp_strtok_pwd != NULL)
rev_string(cp_strtok_pwd);
}

if (cp_strtok_pwd != NULL)
{
chdir(cp_strtok_pwd);
set_variable("PWD", cp_strtok_pwd, data);
}
else
{
chdir("/");
set_variable("PWD", "/", data);
}

data->status = 0;
free(cp_pwd);
}

/**
 * cd_to_dir - changes to a directory
 * @data: shell data (directories)
 * Return: no return
 */
void cd_to_dir(custom_shell_data *data)
{
char pwd[PATH_MAX];
char *dir, *cp_pwd, *cp_dir;

getcwd(pwd, sizeof(pwd));

dir = data->args[1];
if (chdir(dir) == -1)
{
get_error(data, 2);
return;
}

cp_pwd = _strdup(pwd);
set_variable("OLDPWD", cp_pwd, data);

cp_dir = _strdup(dir);
set_variable("PWD", cp_dir, data);

free(cp_pwd);
free(cp_dir);

data->status = 0;

chdir(dir);
}

/**
 * cd_prev - changes to the previous directory
 *
 * @data: shell data (environ)
 * Return: no return
 */
void cd_prev(custom_shell_data *data)
{
char pwd[PATH_MAX];
char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

getcwd(pwd, sizeof(pwd));
cp_pwd = _strdup(pwd);

p_oldpwd = get_variable("OLDPWD", data->environment);

if (p_oldpwd == NULL)
cp_oldpwd = cp_pwd;
else
cp_oldpwd = _strdup(p_oldpwd);

set_variable("OLDPWD", cp_pwd, data);

if (chdir(cp_oldpwd) == -1)
set_variable("PWD", cp_pwd, data);
else
set_variable("PWD", cp_oldpwd, data);

p_pwd = get_variable("PWD", data->environment);

write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
write(STDOUT_FILENO, "\n", 1);

free(cp_pwd);
if (p_oldpwd)
free(cp_oldpwd);

data->status = 0;

chdir(p_pwd);
}

/**
 * cd_home - changes to home directory
 *
 * @data: shell data (environ)
 * Return: no return
 */
void cd_home(custom_shell_data *data)
{
char *p_pwd, *home;
char pwd[PATH_MAX];

getcwd(pwd, sizeof(pwd));
p_pwd = _strdup(pwd);

home = get_variable("HOME", data->environment);

if (home == NULL)
{
set_variable("OLDPWD", p_pwd, data);
free(p_pwd);
return;
}

if (chdir(home) == -1)
{
get_error(data, 2);
free(p_pwd);
return;
}

set_variable("OLDPWD", p_pwd, data);
set_variable("PWD", home, data);
free(p_pwd);
data->status = 0;
}
