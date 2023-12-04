#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

/**
 * struct info_s - Information structure for the shell
 * @argv: Argument vector
 * @env: Environment variables
 * @status: Exit status
 * @line_count: Line count
 * @linecount_flag: Line count flag
 * @path: Path of the command
 * @arg: Argument string
 */
typedef struct info_s
{
    char **argv;
    char **env;
    int status;
    size_t line_count;
    int linecount_flag;
    char *path;
    char *arg;
} info_t;

int _erratoi(const char *str);
void print_error(info_t *info, const char *message);
void _eputs(const char *str);
void _eputchar(char c);

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

/**
 * is_executable - Determines if a file is an executable command.
 * @info: The info struct.
 * @file_path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_executable(info_t *info, char *file_path);

/**
 * copy_chars - Duplicates characters from a source string.
 * @source_str: The source string.
 * @start_index: Starting index.
 * @stop_index: Stopping index.
 *
 * Return: Pointer to a new buffer.
 */
char *copy_chars(char *source_str, int start_index, int stop_index);

/**
 * find_executable_path - Finds the path of an executable in the PATH string.
 * @info: The info struct.
 * @path_str: The PATH string.
 * @command: The command to find.
 *
 * Return: Full path of the command if found or NULL.
 */
char *find_executable_path(info_t *info, char *path_str, char *command);

/**
 * my_exit - Exits the shell.
 * @info: Structure containing potential arguments.
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int my_exit(info_t *info);

/**
 * my_cd - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int my_cd(info_t *info);

/**
 * my_help - Displays help information.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int my_help(info_t *info);

int is_executable(info_t *info, char *file_path);
#endif /* SHELL_H */

