#include "shell.h"

/**
 * displayHelpInfo - Help information for the builtin help.
 * Return: no return
 */
void displayHelpInfo(void)
{
char *info = "help: help [-dms] [pattern ...]\n";
write(STDOUT_FILENO, info, _strlen(info));

info = "\tDisplay information about builtin commands.\n ";
write(STDOUT_FILENO, info, _strlen(info));

info = "Displays brief summaries of builtin commands.\n";
write(STDOUT_FILENO, info, _strlen(info));
}

/**
 * displayAliasHelp - Help information for the builtin alias.
 * Return: no return
 */
void displayAliasHelp(void)
{
char *info = "alias: alias [-p] [name[=value]...]\n";
write(STDOUT_FILENO, info, _strlen(info));

info = "\tDefine or display aliases.\n ";
write(STDOUT_FILENO, info, _strlen(info));
}

/**
 * displayCdHelp - Help information for the builtin cd.
 * Return: no return
 */
void displayCdHelp(void)
{
char *info = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";
write(STDOUT_FILENO, info, _strlen(info));

info = "\tChange the shell working directory.\n ";
write(STDOUT_FILENO, info, _strlen(info));
}

