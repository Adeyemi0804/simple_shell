#include "kade.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int kade_myhistory(info_t *info)
{
	kade_print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int kade_unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = kade_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = kade_delete_node_at_index(&(info->alias),
		kade_get_node_index(info->alias, kade_node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int kade_set_alias(info_t *info, char *str)
{
	char *p;

	p = kade_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (kade_unset_alias(info, str));

	kade_unset_alias(info, str);
	return (kade_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int kade_print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = kade_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		kade_putchar(*a);
		kade_putchar('\'');
		kade_puts(p + 1);
		kade_puts("'\n");
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
int kade_myalias(info_t *info)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            kade_print_alias(node);
            node = node->next;
        }
        return 0;
    }

    i = 1;
    while (info->argv[i])
    {
        p = kade_strchr(info->argv[i], '=');
        if (p)
            kade_set_alias(info, info->argv[i]);
        else
            kade_print_alias(kade_node_starts_with(info->alias, info->argv[i], '='));

        i++;
    }

    return 0;
}
