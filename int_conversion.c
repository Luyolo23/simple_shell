#include "shell.h"

/**
 * get_len - Get the length of a number.
 * @n: type int number.
 * Return: length of a number.
 */
int get_len(int n)
{
unsigned int n1;
int length = 1;

if (n < 0)
{
length++;
n1 = n * -1;
}
else
{
n1 = n;
}
while (n1 > 9)
{
length++;
n1 = n1 / 10;
}

return (length);
}
/**
 * custom_itoa - converts int to string.
 * @n: type int number
 * Return: String.
 */
char *custom_itoa(int n)
{
unsigned int n1;
int length = get_len(n);
char *buffer;

buffer = malloc(sizeof(char) * (length + 1));
if (buffer == 0)
return (NULL);

*(buffer + length) = '\0';

if (n < 0)
{
n1 = n * -1;
buffer[0] = '-';
}
else
{
n1 = n;
}

length--;
do {
*(buffer + length) = (n1 % 10) + '0';
n1 = n1 / 10;
length--;
}
while (n1 > 0)
;
return (buffer);
}

/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi(char *s)
{
unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

while (*(s + count) != '\0')
{
if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
break;

if (*(s + count) == '-')
pn *= -1;

if ((*(s + count) >= '0') && (*(s + count) <= '9'))
{
if (size > 0)
m *= 10;
size++;
}
count++;
}

for (i = count - size; i < count; i++)
{
oi = oi + ((*(s + i) - 48) * m);
m /= 10;
}
return (oi *pn);
}
