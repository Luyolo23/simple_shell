#include "shell.h"

/**
 * execCmd - Executes a shell command
 * @command: The command to be executed
 */
void execCmd(const char *command)
{
pid_t childPid = fork();

if (childPid == -1)
{
display("Error forking process.\n");
exit(EXIT_FAILURE);
}
else if (childPid == 0)
{
char *args[128];
int argCount = 0;

char *token = strtok((char *)command, " ");
while (token != NULL)
{
args[argCount++] = token;
token = strtok(NULL, " ");
}
args[argCount] = NULL;

execvp(args[0], args);

display("Error executing command.\n");
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}
