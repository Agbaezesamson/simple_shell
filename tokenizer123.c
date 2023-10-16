#include "shell.h"

/**
 * **strtow - Duplicate the string into words using custom delimiters.
 * @str: the strings to duplicate
 * @d: delimeter string to duplicate
 * Return: Points to an array of strings.
 */

char **strtow(char *str, char *d)
{
	int p, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (p = 0; str[p] != '\0'; p++)
		if (!is_delim(str[p], d) && (is_delim(str[p + 1], d) || !str[p + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (p = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[p], d))
			p++;
		k = 0;
		while (!is_delim(str[p + k], d) && str[p + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[p++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - duplicate the string into words
 * @str: the string to duplicate
 * @d: delimeter strings to duplicate
 * Return: points to an array of strings
 */
char **strtow2(char *str, char d)
{
	int i, b, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, b = 0; b < numwords; b++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[b] = malloc((k + 1) * sizeof(char));
		if (!s[b])
		{
			for (k = 0; k < b; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[b][m] = str[i++];
		s[b][m] = 0;
	}
	s[b] = NULL;
	return (s);
}
