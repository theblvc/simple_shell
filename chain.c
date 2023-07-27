#include "shell.h"

/**
 * is_chain - test if current char in buffer
 * @info: the parameter strct
 * @buf: the char bufer
 * @p: address of curent position
 * Return: 1 if chain delimeter, 0 otherwi
 **/
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t i = *p;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ';') /* found command */
	{
		buf[i] = 0; /* replace ; with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * check_chain - checks continue chaining based
 * @info: the parameter strct
 * @buf: the char bufer
 * @p: address of curent position
 * @i: starting position
 * @len: length of buff
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces var tokenized str
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 other
 */
int replace_vars(info_t *info)
{
	int b = 0;
	list_t *node;

	for (b = 0; info->argv[b]; b++)
	{
		if (info->argv[b][0] != '$' || !info->argv[b][1])
			continue;

		if (!_strcmp(info->argv[b], "$?"))
		{
			replace_string(&(info->argv[b]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[b], "$$"))
		{
			replace_string(&(info->argv[b]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[b][1], '=');
		if (node)
		{
			replace_string(&(info->argv[b]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[b], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces str
 * @old: address of old str
 * @new: new str
 *
 * Return: 1 if replac, 0 otherws
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
