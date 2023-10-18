#include "shell.h"

/**
 * myenv - program that parints the current environ
 * @info: Struc containing potential arg.this maintain
 *         constant function prototype.
 * Return:  0
 */
int myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * mygetenv - prog that gets the value of an environ var
 * @info: Stru containing potential arg.  maintain
 *         constant func prototype.
 * @name: environ varia name
 *
 * Return: a value
 */
char *mygetenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *pr;

	while (node)
	{
		pr = starts_with(node->str, name);
		if (pr && *pr)
			return (pr);
		node = node->next;
	}
	return (NULL);
}

/**
 * mysetenv - prog that Initialize a new environ varia,
 *             or modifies an existing
 * @info: Struc containing potential arg. maintain
 *         constant func prototype.
 * Return: 0
 */
int mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * myunsetenv - prog that delete an environ var
 * @info: Struc containing potential arg. maintain
 *         constant func prototype.
 * Return: 0
 */
int myunsetenv(info_t *info)
{
	int d;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (d = 1; d <= info->argc; d++)
		_unsetenv(info, info->argv[d]);

	return (0);
}

/**
 * populate_env_list - prog that populates environ linked list
 * @info: Struc containing potential arg. maintain
 *         constant func prototype.
 * Return: 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t pr;

	for (pr = 0; environ[pr]; pr++)
		add_node_end(&node, environ[pr], 0);
	info->env = node;
	return (0);
}

