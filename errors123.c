#include "shell.h"

/**
 * _eputs - this print input string
 * @str: string to be printed
 *
 * Return: empty
 */
void _eputs(char *str)
{
	int d = 0;

	if (!str)
		return;
	while (str[d] != '\0')
	{
		_eputchar(str[d]);
		d++;
	}
}

/**
 * _eputchar - print character c on stderr
 * @c: char to print
 *
 * Return: success 1.
 * On error, -1 to be returned, also errno is set appropriately.
 */
int _eputchar(char c)
{
	static int d;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || d >= WRITE_BUF_SIZE)
	{
		write(2, buf, d);
		d = 0;
	}
	if (c != BUF_FLUSH)
		buf[d++] = c;
	return (1);
}

/**
 * _putfd - print character c to any given fd
 * @c: char to be printed
 * @fd: available filedescriptor
 *
 * Return: 1 when success.
 * On error, -1 to be returned, also errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int d;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || d >= WRITE_BUF_SIZE)
	{
		write(fd, buf, d);
		d = 0;
	}
	if (c != BUF_FLUSH)
		buf[d++] = c;
	return (1);
}

/**
 * _putsfd - write input string
 * @str: string to print
 * @fd: filedescriptor given
 *
 * Return: number of characters put
 */
int _putsfd(char *str, int fd)
{
	int d = 0;

	if (!str)
		return (0);
	while (*str)
	{
		d += _putfd(*str++, fd);
	}
	return (d);
}

