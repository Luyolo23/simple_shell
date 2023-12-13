#include "shell.h"

/**
 * add_separator_node_end - adds a separator found at the end
 * of a separator list.
 * @head: head of the linked list.
 * @separator: separator found (; | &).
 * Return: address of the head.
 */
sep_list *add_separator_node_end(sep_list **head, char separator)
{
sep_list *new_node, *temp_node;

new_node = malloc(sizeof(sep_list));
if (new_node == NULL)
return (NULL);

new_node->separator = separator;
new_node->next = NULL;
temp_node = *head;

if (temp_node == NULL)
{
*head = new_node;
}
else
{
while (temp_node->next != NULL)
temp_node = temp_node->next;
temp_node->next = new_node;
}

return (*head);
}

/**
 * free_separator_list - frees a separator list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_separator_list(sep_list **head)
{
sep_list *temp_node, *curr_node;

if (head != NULL)
{
curr_node = *head;
while ((temp_node = curr_node) != NULL)
{
curr_node = curr_node->next;
free(temp_node);
}
*head = NULL;
}
}

/**
 * add_line_node_end - adds a command line at the end
 * of a line list.
 * @head: head of the linked list.
 * @command_line: command line.
 * Return: address of the head.
 */
line_list *add_line_node_end(line_list **head, char *command_line)
{
line_list *new_node, *temp_node;

new_node = malloc(sizeof(line_list));
if (new_node == NULL)
return (NULL);

new_node->line = command_line;
new_node->next = NULL;
temp_node = *head;

if (temp_node == NULL)
{
*head = new_node;
}
else
{
while (temp_node->next != NULL)
temp_node = temp_node->next;
temp_node->next = new_node;
}

return (*head);
}

/**
 * free_line_list - frees a line list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_line_list(line_list **head)
{
line_list *temp_node, *curr_node;

if (head != NULL)
{
curr_node = *head;
while ((temp_node = curr_node) != NULL)
{
curr_node = curr_node->next;
free(temp_node);
}
*head = NULL;
}
}

