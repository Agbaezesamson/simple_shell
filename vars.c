#include "shell.h"

/**
 * is_chain - prog that checks current char in the buffer
 * @info: para structure
 * @buf: charac buffer
 * @pr: pointer of the current position in buffer
 *
 * Return: 1 for chain delimiter, 0 if it is not
 */
int is_chain(info_t *info, char *buf, size_t *pr)
{
	size_t m = *pr;

	if (buf[m] == '|' && buf[m + 1] == '|')
	{
		buf[m] = 0;
		m++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[m] == '&' && buf[m + 1] == '&')
	{
		buf[m] = 0;
		m++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[m] == ';') /* found end of this command */
	{
		buf[m] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pr = m;
	return (1);
}

/**
 * check_chain - program that checks if we should continue chaining based
 * @info: para struct
 * @buf: char buff
 * @pr: pointer of the current position in buff
 * @d: beginning position in buf
 * @len:the  length of buffer
 *
 * Return: 0
 */
void check_chain(info_t *info, char *buf, size_t *pr, size_t d, size_t len)
{
	size_t m = *pr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[d] = 0;
			m = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[d] = 0;
			m = len;
		}
	}

	*pr = m;
}

/**
 * replace_alias - prog that replaces an alias in the tokenized string
 * @info: the parameter structure
 *
 * Return: 1 for replaced, 0 if not
 */
int replace_alias(info_t *info)
{
	int d;
	list_t *node;
	char *p;

	for (d = 0; d < 10; d++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - prog that replaces variables in the tokenized string
 * @info: parameter structure
 *
 * Return: 1 for replaced, 0if not
 */
int replace_vars(info_t *info)
{
	int d = 0;
	list_t *node;

	for (d = 0; info->argv[d]; d++)
	{
		if (info->argv[d][0] != '$' || !info->argv[d][1])
			continue;

		if (!_strcmp(info->argv[d], "$?"))
		{
			replace_string(&(info->argv[d]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[d], "$$"))
		{
			replace_string(&(info->argv[d]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[d][1], '=');
		if (node)
		{
			replace_string(&(info->argv[d]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[d], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - prog that replaces a string
 * @old: pointer of the old string
 * @new: the recent string
 *
 * Return: 1 for replaced, 0 if not
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

