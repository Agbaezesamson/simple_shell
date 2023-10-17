#include "shell.h"

/**
 * _strncpy - this copies a string
 * @dest: this is the destination string to be copied to
 * @src: the source
 * @n: number of char to be copied
 *
 * Return: pointer to concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int d = 0;
	int k;
	char *s = dest;

	while (src[d] != '\0' && d < n - 1)
	{
		dest[d] = src[d];
		d++;
	}
	if (d < n)
	{
		k = d;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 * _strncat - program that concatenates two strings
 * @dest: 1st string
 * @src: 2nd string
 * @n: max num of bytes to be used
 *
 * Return: pointer to the concatenated str
 */
char *_strncat(char *dest, char *src, int n)
{
	int d = 0;
	int k = 0;
	char *s = dest;

	while (dest[d] != '\0')
		d++;
	while (src[k] != '\0' && k < n)
	{
		dest[d] = src[k];
		d++;
		k++;
	}
	if (k < n)
		dest[d] = '\0';
	return (s);
}

/**
 * _strchr - program that locate character in string
 * @s: string parsed
 * @c: character to check
 *
 * Return: pointe to memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

