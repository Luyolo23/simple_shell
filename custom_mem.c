#include "shell.h"

/**
 * _cpy - copies information between void pointers.
 * @dest: destination pointer.
 * @src: source pointer.
 * @size: size of the destination pointer.
 */
void _cpy(void *dest, const void *src, unsigned int size)
{
char *d = (char *)dest;
const char *s = (const char *)src;

for (unsigned int i = 0; i < size; i++)
d[i] = s[i];
}

/**
 * _reallocate - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old: size, in bytes, of the allocated space of ptr.
 * @new: new size, in bytes, of the new memory block.
 * Return: ptr.
 */
void *_reallocate(void *ptr, unsigned int old, unsigned int new)
{
void *newptr;

if (ptr == NULL)
return (malloc(new));

if (new == 0)
{
free(ptr);
return (NULL);
}

if (new == old)
return (ptr);

newptr = malloc(new);
if (newptr == NULL)
return (NULL);

if (new < old)
_cpy(newptr, ptr, new);
else
_cpy(newptr, ptr, old);

free(ptr);
return (newptr);
}

/**
 * _reallocate_dp - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old: size, in bytes, of the allocated space of ptr.
 * @new: new size, in bytes, of the new memory block.
 * Return: ptr.
 */
char **_reallocate_dp(char **ptr, unsigned int old, unsigned int new)
{
char **newptr;

if (ptr == NULL)
return (malloc(sizeof(char *) * new));

if (new == old)
return (ptr);

newptr = malloc(sizeof(char *) * new);
if (newptr == NULL)
return (NULL);

for (unsigned int i = 0; i < old; i++)
newptr[i] = ptr[i];

free(ptr);

return (newptr);
}

