#include "shell.h"

/**
 * _myhistory - displays the history list.
 *              with line numbers,at 0.
 * @info: Structure containing potential.
 * constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias
 * @info: parameter struc
 * @str: the string aka
 *
 * Return: Always 0 on success, 1 on err
 */
int unset_alias(info_t *info, char *str)
{
	char *q, d;
	int ret;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	d = *q;
	*q = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = d;
	return (ret);
}

/**
 * set_alias - alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 error
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - display alias string
 * @node: the alias nodes
 *
 * Return: Always 0 on success, 1 error
 */
int print_alias(list_t *node)
{
	char *q = NULL, *a = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (a = node->str; a <= q; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *q = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		q = _strchr(info->argv[a], '=');
		if (q)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
}
