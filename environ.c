#include "kade.h"

/**
 * kade_myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int kade_myenv(info_t *info)
{
	kade_print_list_str(info->env);
	return (0);
}

/**
 * kade_getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *kade_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = kade_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * kade_mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int kade_mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		kade_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (kade_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * kade_myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int kade_myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		kade_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		kade_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * kade_populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int kade_populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		kade_add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
