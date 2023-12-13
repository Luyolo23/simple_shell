#include "shell.h"

/**
 * custom_error_env - error message for custom_env in custom_get_env.
 * @custom_data: data relevant (counter, arguments)
 * Return: error message.
 */
char *custom_error_env(custom_shell_data *custom_data)
{
int length;
char *custom_error;
char *custom_ver_str;
char *custom_msg;

custom_ver_str = custom_aux_itoa(custom_data->custom_counter);
custom_msg = ": Unable to add/remove from environment\n";
length = custom_strlen(custom_data->custom_arg_name) +
custom_strlen(custom_ver_str) + custom_strlen(custom_data->custom_arg_name[0]) +
custom_strlen(custom_msg) + 4;

custom_error = malloc(sizeof(char) * (length + 1));
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
custom_strcat(custom_error, custom_data->custom_arg_name[0]);
custom_strcat(custom_error, custom_msg);
custom_strcat(custom_error, "\0");
free(custom_ver_str);

return (custom_error);
}

/**
 * custom_error_path_126 - error message for path
 * and failure denied permission.
 * @custom_data: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *custom_error_path_126(custom_shell_data *custom_data)
{
int length;
char *custom_ver_str;
char *custom_error;

custom_ver_str = custom_aux_itoa(custom_data->custom_counter);
length = custom_strlen(custom_data->custom_arg_name) +
custom_strlen(custom_ver_str) +
custom_strlen(custom_data->custom_arg_name[0]) + 24;

custom_error = malloc(sizeof(char) * (length + 1));
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
custom_strcat(custom_error, custom_data->custom_arg_name[0]);
custom_strcat(custom_error, ": Permission denied\n");
custom_strcat(custom_error, "\0");
free(custom_ver_str);

return (custom_error);
}

