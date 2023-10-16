#include "shell.h"

/**
 * freePointer - Frees a pointer and sets the address to NULL
 * @ptr: Address of the pointer to release
 *
 * Return: 1 if successfully freed, otherwise 0.
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
