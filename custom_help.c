#include "shell.h"

/**
 * disp_env_help - Help information for the builtin env
 * Return: no return
 */
void disp_env_help(void)
{
char *eHelp = "env: env [option] [name=value] [command [args]]\n\t";
write(STDOUT_FILENO, eHelp, _strlen(eHelp));

char *eDesc = "Print the environment of the shell.\n";
write(STDOUT_FILENO, eDesc, _strlen(eDesc));
}

/**
 * disp_setenv_help - Help information for the builtin setenv
 * Return: no return
 */
void disp_setenv_help(void)
{
char *sHelp = "setenv: setenv (const char *name, const char *value, int replace)\n\t";
write(STDOUT_FILENO, sHelp, _strlen(sHelp));

char *sDesc = "Add a new definition to the environment.\n";
write(STDOUT_FILENO, sDesc, _strlen(sDesc));
}

/**
 * disp_unsetenv_help - Help information for the builtin unsetenv
 * Return: no return
 */
void disp_unsetenv_help(void)
{
char *uHelp = "unsetenv: unsetenv (const char *name)\n\t";
write(STDOUT_FILENO, uHelp, _strlen(uHelp));

char *uDesc = "Remove an entry completely from the environment.\n";
write(STDOUT_FILENO, uDesc, _strlen(uDesc));
}

/**
 * disp_general_help - Entry point for help information for the help builtin
 * Return: no return
 */
void disp_general_help(void)
{
char *gHelp = "^-^ bash, version 1.0(1)-release\n";
write(STDOUT_FILENO, gHelp, _strlen(gHelp));

char *gDesc = "These commands are defined internally. Type 'help' to see the list. ";
gDesc += "Type 'help name' to find out more about the function 'name'.\n\n ";
write(STDOUT_FILENO, gDesc, _strlen(gDesc));

char *cmdList = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] [dir]\n";
cmdList += "exit: exit [n]\n  env: env [option] [name=value] [command [args]]\n";
cmdList += "  setenv: setenv [variable] [value]\n  unsetenv: unsetenv [variable]\n";
write(STDOUT_FILENO, cmdList, _strlen(cmdList));
}

/**
 * disp_exit_help - Help information for the builtin exit
 * Return: no return
 */
void disp_exit_help(void)
{
char *exHelp = "exit: exit [n]\n Exit shell.\n";
write(STDOUT_FILENO, exHelp, _strlen(exHelp));

char *exDesc = "Exits the shell with a status of N. If N is omitted, the exit ";
exDesc += "status is that of the last command executed.\n";
write(STDOUT_FILENO, exDesc, _strlen(exDesc));
}

