#include "shell.h"

/**
 * custom_strcat_cd - function that concatenates the message for cd error
 *
 * @custom_data: data relevant (directory)
 * @custom_msg: message to print
 * @custom_error: output message
 * @custom_ver_str: counter lines
 * Return: error message
 */
char *custom_strcat_cd(custom_shell_data *custom_data, char *custom_msg,
		char *custom_error, char *custom_ver_str)
{
char *custom_illegal_flag;

custom_strcpy(custom_error, custom_data->custom_arg_name);
custom_strcat(custom_error, ": ");
custom_strcat(custom_error, custom_ver_str);
custom_strcat(custom_error, ": ");
custom_strcat(custom_error, custom_data->custom_args[0]);
custom_strcat(custom_error, custom_msg);

if (custom_data->custom_args[1][0] == '-')
{
custom_illegal_flag = malloc(3);
custom_illegal_flag[0] = '-';
custom_illegal_flag[1] = custom_data->custom_args[1][1];
custom_illegal_flag[2] = '\0';
custom_strcat(custom_error, custom_illegal_flag);
free(custom_illegal_flag);
}
else
{
custom_strcat(custom_error, custom_data->custom_args[1]);
}

custom_strcat(custom_error, "\n");
custom_strcat(custom_error, "\0");
return (custom_error);
}

/**
 * custom_error_get_cd - error message for cd command in get_cd
 * @custom_data: data relevant (directory)
 * Return: Error message
 */
char *custom_error_get_cd(custom_shell_data *custom_data)
{
int custom_length, custom_len_id;
char *custom_error, *custom_ver_str, *custom_msg;

custom_ver_str = custom_aux_itoa(custom_data->custom_counter);
if (custom_data->custom_args[1][0] == '-')
{
custom_msg = ": Illegal option ";
custom_len_id = 2;
}
else
{
custom_msg = ": can't cd to ";
custom_len_id = custom_strlen(custom_data->custom_args[1]);
}

custom_length = custom_strlen(custom_data->custom_arg_name) +
custom_strlen(custom_data->custom_args[0]) +
custom_strlen(custom_ver_str) + custom_strlen(custom_msg) +
custom_len_id + 5;

custom_error = malloc(sizeof(char) * (custom_length + 1));

if (custom_error == 0)
{
free(custom_ver_str);
return (NULL);
}

custom_error = custom_strcat_cd(custom_data, custom_msg, custom_error,
		custom_ver_str);

free(custom_ver_str);

return (custom_error);
}

/**
 * custom_error_not_found - generic error message for command not found
 * @custom_data: data relevant (counter, arguments)
 * Return: Error message
 */
char *custom_error_not_found(custom_shell_data *custom_data)
{
int custom_length;
char *custom_error;
char *custom_ver_str;

custom_ver_str = custom_aux_itoa(custom_data->custom_counter);
custom_length = custom_strlen(custom_data->custom_arg_name) +
	custom_strlen(custom_ver_str) +
	custom_strlen(custom_data->custom_args[0]) + 16;
custom_error = malloc(sizeof(char) * (custom_length + 1));
if (custom_error == 0)
{
free(custom_error);
free(custom_ver_str);
return (NULL);
}
custom_strcpy(custom_error, custom_data->custom_arg_name);
custom_strcat(custom_error, ": ");
custom_strcat(custom_error, custom_ver_str);
custom_strcat(custom_error, ": ");
custom_strcat(custom_error, custom_data->custom_args[0]);
custom_strcat(custom_error, ": not found\n");
custom_strcat(custom_error, "\0");
free(custom_ver_str);
return (custom_error);
}

/**
 * custom_error_exit_shell - generic error message for exit in get_exit
 * @custom_data: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *custom_error_exit_shell(custom_shell_data *custom_data)
{
int custom_length;
char *custom_error;
char *custom_ver_str;

custom_ver_str = custom_aux_itoa(custom_data->custom_counter);
custom_length = custom_strlen(custom_data->custom_arg_name) +
custom_strlen(custom_ver_str) +
custom_strlen(custom_data->custom_args[0]) +
custom_strlen(custom_data->custom_args[1]) + 23;
custom_error = malloc(sizeof(char) * (custom_length + 1));
if (custom_error == 0)
{
free(custom_ver_str);
return (NULL);
}
custom_strcpy(custom_error, custom_data->custom_arg_name);
custom_strcat(custom_error, ": ");
custom_strcat(custom_error, custom_ver_str);
custom_strcat(custom_error, ": ");
custom_strcat(custom_error, custom_data->custom_args[0]);
custom_strcat(custom_error, ": Illegal number: ");
custom_strcat(custom_error, custom_data->custom_args[1]);
custom_strcat(custom_error, "\n\0");
free(custom_ver_str);

return (custom_error);
}

