#include "shell.h"

/**
 * add_node - prog that Adds a node to the start of the list
 * @head: pointe to head node
 * @str: Str field of the node
 * @num: the index used by history
 *
 * Return: the Pointer to the new node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - prog that Add a node to the end of the list
 * @head:pointer to head node
 * @str: the Str field of the node
 * @num: the Node index used by history
 *
 * Return: this Pointe to the newly added node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prog that Prints only the str element of linked list
 * @h: to Pointe to the first node
 *
 * Return: the list
 */
size_t print_list_str(const list_t *h)
{
	size_t q = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		q++;
	}
	return (q);
}

/**
 * delete_node_at_index - prog that Delete node at the given index
 * @head: pointe to the first node
 * @index: the Index node to delete
 *
 * Return: 1 if success, 0 for  failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int q = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (q == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		q++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - prog that Frees all nodes of a list
 * @head_ptr: pointe to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

