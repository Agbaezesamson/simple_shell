#include "shell.h"

/**
 * input_buf - program that buffers chained commands
 * @info: the parameter structure
 * @buf: the address of buffer
 * @len: the address of len variables
 *
 * Return: only the bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t y = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		y = getline(buf, &len_p, stdin);
#else
		y = _getline(info, buf, &len_p);
#endif
		if (y > 0)
		{
			if ((*buf)[y - 1] == '\n')
			{
				(*buf)[y - 1] = '\0'; /* remove trailing newline */
				y--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = y;
				info->cmd_buf = buf;
			}
		}
	}
	return (y);
}

/**
 * get_input - prog that get line minus the newline
 * @info: for the parameter structure
 *
 * Return: only the bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t z, x, len;
	ssize_t y = 0;
	char **buf_p = &(info->arg), *pr;

	_putchar(BUF_FLUSH);
	y = input_buf(info, &buf, &len);
	if (y == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		x = z; /* init new iterator to current buf position */
		pr = buf + z; /* get pointer for return */

		check_chain(info, buf, &x, z, len);
		while (x < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &x))
				break;
			x++;
		}

		z = x + 1; /* increment past nulled ';'' */
		if (z >= len) /* reached end of buffer? */
		{
			z = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = pr; /* pass back pointer to current command position */
		return (_strlen(pr)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (y); /* return length of buffer from _getline() */
}

/**
 * read_buf - prog that reads a buffer
 * @info: this is the parameter structure
 * @buf: for the buffer
 * @i: for the size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - prog that gets the next line of input from STDIN
 * @info: the parameters structures
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: for the size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t z, len;
	size_t k;
	ssize_t y = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (z == len)
		z = len = 0;

	y = read_buf(info, buf, &len);
	if (y == -1 || (y == 0 && len == 0))
		return (-1);

	c = _strchr(buf + z, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + z, k - z);
	else
		_strncpy(new_p, buf + z, k - z + 1);

	s += k - z;
	z = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - prog that blocks ctrl-C
 * @sig_num: for signal num
 *
 * Return: nothing
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
