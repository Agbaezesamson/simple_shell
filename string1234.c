#include "shell.h"

/**
 * copy_string - Copies the content of one string to another.
 * @target: The destination string.
 * @source: The source string.
 *
 * Return: A pointer to the destination string.
 */
char *copy_string(char *target, char *source)
{
	int index = 0;

	if (target == source || source == NULL)
		return (target);

	while (source[index])
	{
		target[index] = source[index];
		index++;
	}
	target[index] = '\0';
	return (target);
}

/**
 * duplicate_string - Duplicates a string.
 * @str_to_dup: The string to duplicate.
 *
 * Return: A pointer to the duplicated string.
 */
char *duplicate_string(const char *str_to_dup)
{
	int len = 0;
	char *duplicate;

	if (str_to_dup == NULL)
		return (NULL);

	while (*str_to_dup++)
		len++;

	duplicate = malloc(sizeof(char) * (len + 1));

	if (!duplicate)
		return (NULL);

	for (len++; len--;)
		duplicate[len] = *--str_to_dup;

	return (duplicate);
}

/**
 * print_string - Prints a given string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void print_string(char *str)
{
	int index = 0;

	if (!str)
		return;

	while (str[index] != '\0')
	{
		print_character(str[index]);
		index++;
	}
}

/**
 * print_character - Writes a character to the standard output.
 * @ch: The character to be printed.
 *
 * Return: On success, 1. On error, -1 is returned with the exact error handle
 */
int print_character(char ch)
{
	static int index
		static char buffer[WRITE_BUFFER_SIZE];

	if (ch == FLUSH_BUFFER || index >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}
	if (ch != FLUSH_BUFFER)
		buffer[index++] = ch;
	return (1);
}
