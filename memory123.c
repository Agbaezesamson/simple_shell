#include "shell.h"

/**
 * freePointer - release pointer and sets the address to NULL
 * @ptr: pointer to release
 *
 * Return: 1 for  success, otherwise 0.
 */
int freePointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
