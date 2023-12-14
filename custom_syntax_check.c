#include "shell.h"

/**
 * count_repeated - counts repeated characters
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int count_repeated(char *input, int i)
{
if (*(input - 1) == *input)
return (count_repeated(input - 1, i + 1));

return (i);
}

/**
 * find_syntax_error - finds syntax errors in separators
 * @input: input string
 * @i: index
 * @last: last char
 * Return: index of error. 0 for no errors
 */
int find_syntax_error(char *input, int i, char last)
{
int count;

count = 0;
if (!*input)
return (0);

while (*input == ' ' || *input == '\t')
input++;

if (*input == ';' && (last == '|' || last == '&' || last == ';'))
return (i);

if (*input == '|')
{
if ((last == ';' || last == '&') || (last == '|' &&
(count = count_repeated(input, 0)) && (count == 0 || count > 1)))
return (i);
}

if (*input == '&')
{
if ((last == ';' || last == '|') || (last == '&'
&& (count = count_repeated(input, 0)) && (count == 0 || count > 1)))
return (i);
}
return (find_syntax_error(input + 1, i + 1, *input));
}

/**
 * find_first_char_index - finds index of first non-whitespace char
 *
 * @input: input string
 * @index: index
 * Return: 1 if error. 0 otherwise
 */
int find_first_char_index(char *input, int *index)
{
for (*index = 0; input[*index]; *index += 1)
{
if (input[*index] == ' ' || input[*index] == '\t')
continue;

if (input[*index] == ';' || input[*index] == '|' || input[*index] == '&')
return (-1);

break;
}

return (0);
}

/**
 * print_syntax_error_msg - prints syntax error message
 *
 * @datash: data structure
 * @input: input string
 * @index: index of the error
 * @_bool: control flag
 * Return: no return
 */
void print_syntax_error_msg(custom_shell_data *datash,
		char *input, int index, int _bool)
{
char *msg, *msg2, *msg3, *error, *counter;
int length;

if (input[index] == ';')
msg = (_bool == 0) ? (input[index + 1] == ';') ? ";;" : ";" :
(input[index - 1] == ';') ? ";;" : ";";

if (input[index] == '|')
msg = (input[index + 1] == '|') ? "||" : "|";

if (input[index] == '&')
msg = (input[index + 1] == '&') ? "&&" : "&";

msg2 = ": Syntax error: \"";
msg3 = "\" unexpected\n";
counter = int_to_str(datash->custom_counter);
length = _strlen(datash->av[0]) + _strlen(counter) + _strlen(msg) +
_strlen(msg2) + _strlen(msg3) + 2;

error = malloc(sizeof(char) * (length + 1));
if (!error)
{
free(counter);
return;
}
_strcpy(error, datash->av[0]);
_strcat(error, ": ");
_strcat(error, counter);
_strcat(error, msg2);
_strcat(error, msg);
_strcat(error, msg3);
_strcat(error, "\0");

write(STDERR_FILENO, error, length);
free(error);
free(counter);
}

/**
 * check_syntax_error - checks for syntax errors in the input string
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if error. 0 otherwise
 */
int check_syntax_error(custom_shell_data *datash, char *input)
{
int begin = 0;
int f_char_result = find_first_char_index(input, &begin);
if (f_char_result == -1)
{
print_syntax_error_msg(datash, input, begin, 0);
return (1);
}

int i = find_syntax_error(input + begin, 0, *(input + begin));
if (i != 0)
{
print_syntax_error_msg(datash, input, begin + i, 1);
return (1);
}

return (0);
}

