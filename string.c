#include "shell.h"

/**
 * _strlen - Computes the length of a string.
 * @s: Pointer to the string.
 *
 * Return: The length of the string.
 */
int _strlen(const char *s)
{
	int length = 0;

	if (!s)
	return (0);

	while (*s++)
	length++;
	return (length);
}

/**
 * _strcmp - Compares two strings.
 * @s1: First string.
 * @s2: Second string.
 *
 * Return: 0 if the strings are equal, a negative value if s1 is < s2,
 *         or a positive value if s1 is greater than s2.
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
	if (*s1 != *s2)
	return (*s1 - *s2);
	s1++;
	s2++;
	}
	if (*s1 == *s2)
	return (0);
	else
	return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Checks if a string starts with a specified substring.
 * @haystack: The string to search in.
 * @needle: The substring to look for.
 *
 * Return: A pointer to the start of the substring within haystack if found,
 *         NULL otherwise.
 */
const char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
	if (*needle++ != *haystack++)
	return (NULL);
	}
	return (haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: A pointer to the resulting string (dest).
 */
char *_strcat(char *dest, const char *src)
{
	int len = _strlen(dest);
	unsigned int i;

	for (i = 0; i < _strlen(src); i++)
		dest[len + i] = src[i];

	return (dest);
}
