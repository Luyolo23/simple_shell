#include "shell.h"

/**
 * _strdup - duplicates a string in heap memory.
 * @original_str: Type char pointer to the original string.
 * Return: duplicated string.
 */
char *_strdup(const char *original_str)
{
char *duplicate_str;
size_t length;

length = _strlen(original_str);
duplicate_str = malloc(sizeof(char) * (length + 1));

if (duplicate_str == NULL)
return (NULL);

_memcpy(duplicate_str, original_str, length + 1);
return (duplicate_str);
}

/**
 * _strlen - Returns the length of a string.
 * @str: Type char pointer to the string.
 * Return: Length of the string.
 */
int _strlen(const char *str)
{
int length;

for (length = 0; str[length] != 0; length++)
{
}
return (length);
}

/**
 * chars_equal - compare characters of strings
 * @str: input string.
 * @delim: delimiter.
 * Return: 1 if characters are equal, 0 if not.
 */
int chars_equal(char str[], const char *delim)
{
unsigned int i, j, equal_count;

for (i = 0, equal_count = 0; str[i]; i++)
{
for (j = 0; delim[j]; j++)
{
if (str[i] == delim[j])
{
equal_count++;
break;
}
}
}
if (i == equal_count)
return (1);
return (0);
}

/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 * Return: string split.
 */
char *_strtok(char str[], const char *delim)
{
static char *current_token, *end_of_str;
char *token_start;
unsigned int i, found_token;

if (str != NULL)
{
if (chars_equal(str, delim))
return (NULL);

current_token = str;
i = _strlen(str);
end_of_str = &str[i];
}

token_start = current_token;

if (token_start == end_of_str)
return (NULL);

for (found_token = 0; *current_token; current_token++)
{

if (current_token != token_start)
if (*current_token && *(current_token - 1) == '\0')
break;

for (i = 0; delim[i]; i++)
{
if (*current_token == delim[i])
{
*current_token = '\0';
if (current_token == token_start)
token_start++;
break;
}
}

if (found_token == 0 && *current_token)
found_token = 1;
}

if (found_token == 0)
return (NULL);

return (token_start);
}

/**
 * _isdigit - defines if a string passed is a number
 * @s: input string
 * Return: 1 if string is a number. 0 otherwise.
 */
int _isdigit(const char *s)
{
unsigned int i;

for (i = 0; s[i]; i++)
{
if (s[i] < '0' || s[i] > '9')
return (0);
}
return (1);
}
