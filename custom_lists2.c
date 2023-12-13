#include "shell.h"

/**
 * add_var_node - adds a variable at the end
 * of a variable list.
 * @h: head of the linked list.
 * @len_var: length of the variable.
 * @val: value of the variable.
 * @len_val: length of the value.
 * Return: address of the head.
 */
r_var *add_var_node(r_var **h, int len_var, char *val, int len_val)
{
r_var *n, *t;

n = malloc(sizeof(r_var));
if (n == NULL)
return (NULL);

n->len_var = len_var;
n->value = val;
n->len_val = len_val;

n->next = NULL;
t = *h;

if (t == NULL)
{
*h = n;
}
else
{
while (t->next != NULL)
t = t->next;
t->next = n;
}

return (*h);
}

/**
 * free_var_list - frees a variable list
 * @h: head of the linked list.
 * Return: no return.
 */
void free_var_list(r_var **h)
{
r_var *t, *c;

if (h != NULL)
{
c = *h;
while ((t = c) != NULL)
{
c = c->next;
free(t);
}
*h = NULL;
}
}

