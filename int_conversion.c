#include "shell.h"

/**
 * get_num_length - Get the length of a number.
 * @num: An integer number.
 * Return: Length of the number.
 */
int get_num_length(int num)
{
unsigned int positive_num;
int length = 1;

if (num < 0)
{
length++;
positive_num = (unsigned int)(-num);
}
else
{
positive_num = (unsigned int)num;
}

while (positive_num > 9)
{
length++;
positive_num /= 10;
}

return (length);
}

/**
 * int_to_str - Convert an integer to a string.
 * @num: An integer number.
 * Return: Dynamically allocated string representing the integer.
 */
char *int_to_str(int num)
{
unsigned int positive_num;
int length = get_num_length(num);
char *result_str;

result_str = malloc(sizeof(char) * (length + 1));
if (result_str == NULL)
return (NULL);

result_str[length] = '\0';

if (num < 0)
{
positive_num = (unsigned int)(-num);
result_str[0] = '-';
}
else
{
positive_num = (unsigned int)num;
}

length--;
do {
result_str[length] = (positive_num % 10) + '0';
positive_num /= 10;
length--;
} while (positive_num > 0);

return (result_str);
}

/**
 * str_to_int - Convert a string to an integer.
 * @s: Input string.
 * Return: The converted integer.
 */
int str_to_int(char *s)
{
unsigned int count = 0, digit_count = 0, result = 0,
	     sign = 1, multiplier = 1, i;

while (s[count] != '\0')
{
if (digit_count > 0 && (s[count] < '0' || s[count] > '9'))
break;

if (s[count] == '-')
sign *= -1;

if (s[count] >= '0' && s[count] <= '9')
{
if (digit_count > 0)
multiplier *= 10;
digit_count++;
}
count++;
}

for (i = count - digit_count; i < count; i++)
{
result = result + ((s[i] - '0') * multiplier);
multiplier /= 10;
}

return ((int)(result *sign));
}
