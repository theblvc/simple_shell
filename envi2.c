#include "shell.h"

/**
 * getEnvironmentVariable - Retrieve the string array of environment variables.
 * @info: Structure containing potential arguments.
 * Return: The string array of environment variables.
 */
char **getEnvironmentVariable(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = listToStringArray(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unsetEnvironmentVariable - Remove an environment variable.
 * @info: Structure containing potential arguments.
 * @var: The environment variable property to remove.
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int unsetEnvironmentVariable(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = deleteNodeAtIndex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable or modify an existing one.
 * @info: Structure containing potential arguments.
 * @var: The environment variable property.
 * @value: The environment variable value.
 * Return: Always 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

