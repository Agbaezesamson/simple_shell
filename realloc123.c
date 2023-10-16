#include "shell.h"

/**
 * _memory_set - Fills memory with a given byte
 * @mem: Pointer to the memory area
 * @byte: The byte to fill @mem with
 * @size: The number of bytes to be filled
 *
 * Return: A pointer to the filled memory area (@mem)
 */
char *_memory_set(char *mem, char byte, unsigned int size)
{
	unsigned int index;

	for (index = 0; index < size; index++)
		mem[index] = byte;
	return (mem);
}

/**
 * free_strings - Frees an array of strings
 * @str_array: Array of strings
 */
void free_strings(char **str_array)
{
	char **current = str_array;

	if (!str_array)
		return;
	while (*str_array)
		free(*str_array++);
	free(current);
}

/**
 * _realloc_memory - Reallocates a block of memory
 * @ptr: Pointer to the previous memory block
 * @old_size: Byte size of the previous block
 * @new_size: Byte size of the new block
 *
 * Return: Pointer to the updated memory block
 */
void *_realloc_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
