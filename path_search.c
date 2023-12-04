#include "shell.h"

/**
 * is_executable - determines if a file is an executable command
 * @info: the info struct
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(info_t *info, char *file_path)
{
struct stat file_stat;

(void)info;
if (!file_path || stat(file_path, &file_stat))
return (0);

if (file_stat.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
 * copy_chars - duplicates characters
 * @source_str: the source string
 * @start_index: starting index
 * @stop_index: stopping index
 *
 * Return: pointer to new buffer
 */
char *copy_chars(char *source_str, int start_index, int stop_index)
{
static char buffer[1024];
int buffer_index = 0;
int source_index = start_index;

for (; source_index < stop_index; source_index++)
{
if (source_str[source_index] != ':')
buffer[buffer_index++] = source_str[source_index];
}
buffer[buffer_index] = '\0';
return (buffer);
}

/**
 * find_executable_path - finds the path of an executable in the PATH string
 * @info: the info struct
 * @path_str: the PATH string
 * @command: the command to find
 *
 * Return: full path of the command if found or NULL
 */
char *find_executable_path(info_t *info, char *path_str, char *command)
{
int path_index = 0;
int current_pos = 0;
char *path;

if (!path_str)
return (NULL);

if ((_strlen(command) > 2) && starts_with(command, "./"))
{
if (is_executable(info, command))
return (command);
}

while (1)
{
if (!path_str[path_index] || path_str[path_index] == ':')
{
path = copy_chars(path_str, current_pos, path_index);
if (!*path)
_strcat(path, command);
else
{
_strcat(path, "/");
_strcat(path, command);
}

if (is_executable(info, path))
return (path);

if (!path_str[path_index])
break;

current_pos = path_index;
}
path_index++;
}
return (NULL);
}

