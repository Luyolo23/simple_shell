#include "shell.h"

/**
 * free_data - frees data structure
 *
 * @data: data structure
 * Return: no return
 */
void free_data(data_shell *data)
{
unsigned int i;

for (i = 0; data->_environ[i]; i++)
{
free(data->_environ[i]);
}

free(data->_environ);
free(data->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @data: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(data_shell *data, char **av)
{
unsigned int i;

data->av = av;
data->input = NULL;
data->arguments = NULL;
data->status = 0;
data->custom_counter = 1;

for (i = 0; environ[i]; i++)
;

data->_environ = malloc(sizeof(char *) * (i + 1));

for (i = 0; environ[i]; i++)
{
data->_environ[i] = _strdup(environ[i]);
}

data->_environ[i] = NULL;
data->pid = custom_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
data_shell data;
(void) ac;

signal(SIGINT, get_sigint);
set_data(&data, av);
shell_loop(&data);
free_data(&data);
if (data.status < 0)
return (255);
return (data.status);
}
