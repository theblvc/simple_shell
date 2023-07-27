#include "shell.h"

/**
 * shell_memset - Fills memory with a constant byte.
 * @dest: Pointer to memory area.
 * @value: Byte value to fill @dest with.
 * @size: The number of bytes to be filled.
 * Return: Pointer to the memory area @dest.
 */
char *shell_memset(char *dest, char value, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		dest[i] = value;
	return (dest);
}

/**
 * shell_free_strings - Frees an array of strings.
 * @str_arr: Array of strings.
 */
void shell_free_strings(char **str_arr)
{
	char **ptr = str_arr;

	if (!str_arr)
		return;

	while (*str_arr)
	{
		free(*str_arr);
		str_arr++;
	}
	free(ptr);
}

/**
 * shell_realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous allocated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 * Return: Pointer to the reallocated memory block.
 */
void *shell_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = (old_size < new_size) ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (new_ptr);
}

/**
 * shell_free_and_null - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 * Return: 1 if freed, otherwise 0.
 */
int shell_free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
