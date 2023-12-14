#include "shell.h"

/**
 * free_data - frees data structure
 *
 * @datash: data structure
 * Return: no return
 */
void free_data(custom_shell_data *datash)
{
unsigned int i;

for (i = 0; datash->environment[i]; i++)
{
free(datash->environment[i]);
}

free(datash->environment);
free(datash->process_id);
}

/**
 * set_data - Initialize data structure
 *
 * @datash: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(custom_shell_data *datash, char **av)
{
unsigned int i;

datash->av = av;
datash->input = NULL;
datash->arguments = NULL;
datash->status = 0;
datash->custom_counter = 1;

for (i = 0; environ[i]; i++)
;

datash->environment = malloc(sizeof(char *) * (i + 1));

for (i = 0; environ[i]; i++)
{
datash->environment[i] = _strdup(environ[i]);
}

datash->environment[i] = NULL;
datash->process_id = int_to_str(getpid());
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
custom_shell_data datash;
(void) ac;

signal(SIGINT, get_sigint);
set_data(&datash, av);
shell_loop(&datash);
free_data(&datash);
if (datash.status < 0)
return (255);
return (datash.status);
}
