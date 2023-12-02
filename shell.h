#ifndef SHELL_H
#define SHELL_H

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

/**
 * show_prompt - Displays the shell prompt
 */
void show_prompt(void);

/**
 * display - Writes a message to standard output
 * @text: The message to be displayed
 */
void display(const char *text);

/**
 * readCmd - Reads a command from standard input
 * @command: The buffer to store the command
 * @size: The size of the buffer
 */
void readCmd(char *command, size_t size);

/**
 * execCmd - Executes a shell command
 * @command: The command to be executed
 */
void execCmd(const char *command);

#endif /* SHELL_H */

