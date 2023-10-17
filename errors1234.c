#include "shell.h"

/**
 * _erratoi - change a string to an int
 * @s: the string to be converted
 *
 * Return: 0 when num in str, converted number otherwise,
 * -1 on error
 */
int _erratoi(char *s)
{
	int d = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (d = 0; s[d] != '\0'; d++)
	{
		if (s[d] >= '0' && s[d] <= '9')
		{
			result *= 10;
			result += (s[d] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - to print an error mess
 * @info: the para & return info str
 * @estr: the str containing spec error type
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - to write a dec (int) num (base 10)
 * @input: for input
 * @fd: for filedescriptor to print to
 *
 * Return: num of char printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int d, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (d = 1000000000; d > 1; d /= 10)
	{
		if (_abs_ / d)
		{
			__putchar('0' + current / d);
			count++;
		}
		current %= d;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - to convert a num to a str in the spec base
 * @num: the num
 * @base: the base
 * @flags: the arg flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - to replace first instance of '#' with '\0'
 * @buf: the address of the string to modify
 */
void remove_comments(char *buf)
{
	int d;

	for (d = 0; buf[d] != '\0'; d++)
		if (buf[d] == '#' && (!d || buf[d - 1] == ' '))
		{
			buf[d] = '\0';
			break;
		}
}

