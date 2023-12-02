#include "shell.h"

/**
 * readCmd - Reads a command from standard input
 * @command: The buffer to store the command
 * @size: The size of the buffer
 */
void readCmd(char *command, size_t size)
{
if (fgets(command, size, stdin) == NULL)
{
if (feof(stdin))
{
display("\n");
exit(EXIT_SUCCESS);
}
else
{
display("Error reading input.\n");
exit(EXIT_FAILURE);
}
}
command[strcspn(command, "\n")] = '\0';
}
