#include "shell.h"

/**
 * _strlen - computes the length of a stri
 * @s: pointer to the string
 *
 * Return: the length of the strin
 */
int _strlen(char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*s++)
		length++;
	return (length);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if the strings are equal, a negative value if s1 is < s2,
 *         or a positive value if s1 is greater than s2
 */
int _strcmp(char *s1, char *s2)
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
 * starts_with - checks if a string starts with a specified substring
 * @haystack: the string to search in
 * @needle: the substring to look for
 *
 * Return: a pointer to the start of the substring within haystack if found,
 *         NULL otherwise
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: a pointer to the resulting string (dest)
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
