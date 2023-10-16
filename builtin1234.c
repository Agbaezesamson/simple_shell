#include "shell.h"

/**
 * my_history - Display the command history with line numbers.
 * @data: Structure containing necessary arguments.
 *
 * Return: Always 0
 */
int my_history(shell_data_t *data)
{
	print_command_history(data->history);
	return (0);
}

/**
 * unset_user_alias - Remove an alias.
 * @data: Parameter structure.
 * @alias_str: The alias string.
 *
 * Return: 0 on success, 1 on error
 */
int unset_user_alias(shell_data_t *data, char *alias_str)
{
	char *equal_sign, saved_char;
	int result;

	equal_sign = _strchr(alias_str, '=');
	if (!equal_sign)
		return (1);

	saved_char = *equal_sign;
	*equal_sign = 0;
	result = delete_alias(&(data->alias), find_alias(data->alias, alias_str, -1));
	*equal_sign = saved_char;

	return (result);
}

/**
 * set_user_alias - Set an alias.
 * @data: Parameter structure.
 * @alias_str: The alias string.
 *
 * Return: 0 on success, 1 on error
 */
int set_user_alias(shell_data_t *data, char *alias_str)
{
	char *equal_sign;

	equal_sign = _strchr(alias_str, '=');

	if (!equal_sign)
		return (1);

	if (!*++equal_sign)
		return (unset_user_alias(data, alias_str));

	unset_user_alias(data, alias_str);
	return (add_alias(&(data->alias), alias_str, 0) == NULL);
}

/**
 * display_user_alias - Display an alias.
 * @alias: The alias node.
 *
 * Return: 0 on success, 1 on error
 */
int display_user_alias(alias_t *alias)
{
	char *equal_sign, *alias_start;

	if (alias)
	{
		equal_sign = _strchr(alias->str, '=');
		for (alias_start = alias->str; alias_start <= equal_sign; alias_start++)
			_putchar(*alias_start);

		_putchar('\'');
		_puts(equal_sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - Manage user aliases.
 * @data: Structure containing necessary arguments.
 *
 * Return: Always 0
 */
int my_alias(shell_data_t *data)
{
	int index;
	char *equal_sign;
	alias_t *alias_node = NULL;

	if (data->argc == 1)
	{
		alias_node = data->alias;
		while (alias_node)
		{
			display_user_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (index = 1; data->argv[index]; index++)
	{
		equal_sign = _strchr(data->argv[index], '=');
		if (equal_sign)
			set_user_alias(data, data->argv[index]);
		else
			display_user_alias(find_alias(data->alias, data->argv[index], '='));
	}

	return (0);
}
