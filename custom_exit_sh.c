#include "shell.h"

/**
 * exit_shell - exits the shell
 *
 * @data: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(data_shell *data)
{
unsigned int ustatus;
int is_digit;
int str_len;
int big_number;

if (data->arguments[1] != NULL)
{
ustatus = _atoi(data->arguments[1]);
is_digit = _isdigit(data->arguments[1]);
str_len = _strlen(data->arguments[1]);
big_number = ustatus > (unsigned int)INT_MAX;
if (!is_digit || str_len > 10 || big_number)
{
get_error(data, 2);
data->status = 2;
return (1);
}
data->status = (ustatus % 256);
}
return (0);
}
