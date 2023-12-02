#include "shell.h"

/**
 * display - Writes a message to standard output
 * @text: The message to be displayed
 */
void display(const char *text)
{
	write(STDOUT_FILENO, text, strlen(text));
}
