#include "shell.h"

/**
 *_eputs - prints an input str
 * @str: the string to be print
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
 * _eputchar - writes the character c  stderr
 * @c: The character to prints
 *
 * Return: On success 1
 * On error, -1 is returned, and err appropriately.
 */
int _eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given
 * @c: The character to prints
 * @fd: The filedescriptor to write
 *
 * Return: On success 1.
 * On error, -1 is returned, and err is set appropriate
 */
int _putfd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 *_putsfd - prints an input str
 * @str: the string to be print
 * @fd: the filedescriptor to write
 *
 * Return: the number of chars
 */
int _putsfd(char *str, int fd)
{
	int d = 0;

	if (!str)
		return (0);
	while (*str)
	{
	d += _putfd(*str++, fd);
	}
	return (d);
}
