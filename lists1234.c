#include "shell.h"

/**
 * list_size - Counts the number of nodes in a linked list
 * @head: Pointer to the first node of the list
 *
 * Return: The number of nodes in the list
 */
size_t list_size(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - Converts a linked list of strings to an array of strings
 * @head: Pointer to the first node of the list
 *
 * Return: An array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t count = list_size(head), i;
	char **strs;
	char *str;

	if (!head || !count)
		return (NULL);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (count = 0; count < i; count++)
				free(strs[count]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - Prints all elements of a linked list
 * @head: Pointer to the first node of the list
 *
 * Return: The number of nodes in the list
 */
size_t print_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * node_starts_with - Finds the first node whose string starts with a prefix
 * @node: Pointer to the first node of the list
 * @prefix: The prefix string to match
 * @c: The next character after prefix to match (-1 to ignore)
 *
 * Return: A pointer to the matching node or NULL if not found
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *pr = NULL;

	while (node)
	{
		pr = starts_with(node->str, prefix);
		if (pr && ((c == -1) || (*pr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node in a linked list
 * @head: Pointer to the first node of the list
 * @node: Pointer to the node whose index to find
 *
 * Return: The index of the node or -1 if not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}

