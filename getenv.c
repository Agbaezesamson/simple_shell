#include "shell.h"

/**
 * get_environ - prog that return the string array copy of our environment
 * @info: the Struc containing potential arg. Used to maintain
 *        constant function prototype.
 *
 * Return: string array copy  environment
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - prog that Remove an environ variable
 * @info: the Struct containing potential arg. Used to maintain
 *        constant function prototype.
 * @var: the string environ varia prop
 *
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t d = 0;
	char *pr;

	if (!node || !var)
		return (0);

	while (node)
	{
		pr = starts_with(node->str, var);
		if (pr && *pr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), d);
			d = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		d++;
	}
	return (info->env_changed);
}

/**
 * _setenv - prog that Initialize a new environ varia,
 *           or modify an existing one
 * @info: this is Struc containing potential arg. Used to maintain
 *        constant function prototype.
 * @var: string environ variab property
 * @value: string environ varia value
 *
 * Return: 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *pr;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		pr = starts_with(node->str, var);
		if (pr && *pr == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

