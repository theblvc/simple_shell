#include "shell.h"

/**
 * isChainDelimiter - Tests if the current character in the buffer is a chain delimiter.
 * @info: Pointer to the info_t struct.
 * @buf: The character buffer.
 * @p: Address of the current position in the buffer.
 * Return: 1 if the chain delimiter is found, 0 otherwise.
 **/
int isChainDelimiter(info_t *info, char *buf, size_t *p)
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
	else if (buf[i] == ';') /* Found a command */
	{
		buf[i] = 0; /* Replace ';' with null terminator */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return 0;

	*p = i;
	return 1;
}

/**
 * checkChain - Checks for continued chaining based on the command buffer type.
 * @info: Pointer to the info_t struct.
 * @buf: The character buffer.
 * @p: Address of the current position in the buffer.
 * @i: Starting position.
 * @len: Length of the buffer.
 * Return: Void.
 */
void checkChain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
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
 * replaceAliases - Replaces aliases in the tokenized string.
 * @info: Pointer to the info_t struct.
 * Return: 1 if an alias is replaced, 0 otherwise.
 */
int replaceAliases(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = findNodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return 0;

		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return 0;

		p = _strdup(p + 1);
		if (!p)
			return 0;

		info->argv[0] = p;
	}

	return 1;
}

/**
 * replaceVariables - Replaces environment variables in the tokenized string.
 * @info: Pointer to the info_t struct.
 * Return: 1 if a variable is replaced, 0 otherwise.
 */
int replaceVariables(info_t *info)
{
	int b = 0;
	list_t *node;

	for (b = 0; info->argv[b]; b++)
	{
		if (info->argv[b][0] != '$' || !info->argv[b][1])
			continue;

		if (!_strcmp(info->argv[b], "$?"))
		{
			replaceString(&(info->argv[b]), _strdup(convertNumber(info->status, 10, 0)));
			continue;
		}

		if (!_strcmp(info->argv[b], "$$"))
		{
			replaceString(&(info->argv[b]), _strdup(convertNumber(getpid(), 10, 0)));
			continue;
		}

		node = findNodeStartsWith(info->env, &info->argv[b][1], '=');
		if (node)
		{
			replaceString(&(info->argv[b]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}

		replaceString(&info->argv[b], _strdup(""));
	}

	return 0;
}

/**
 * replaceString - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 * Return: 1 if replaced, 0 otherwise.
 */
int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return 1;
}
