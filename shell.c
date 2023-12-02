#include "shell.h"

/**
 * main - The main function for the shell program
 *
 * Return: Always 0 on success
 */
int main(void)
{
char command[120];

while (true)
{
show_prompt();
readCmd(command, sizeof(command));
execCmd(command);
}

return (0);
}
