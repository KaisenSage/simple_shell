#include "shell.h"

/**
 * displayHistory - displays the history list, one command by line, preceded
 *                  with line numbers, starting at 0.
 * @infoStruct: Structure containing potential arguments.
 * Return: Always 0
 */
int displayHistory(info_t *infoStruct)
{
    printStringList(infoStruct->history);
    return 0;
}

/**
 * removeAlias - removes an alias
 * @infoStruct: parameter struct
 * @aliasString: the string alias
 * Return: Always 0 on success, 1 on error
 */
int removeAlias(info_t *infoStruct, char *aliasString)
{
    char *p, c;
    int result;

    p = _strchr(aliasString, '=');
    if (!p)
        return 1;
    c = *p;
    *p = 0;
    result = deleteNodeAtIndex(&(infoStruct->alias),
        getNodeIndex(infoStruct->alias, nodeStartsWith(infoStruct->alias, aliasString, -1)));
    *p = c;
    return result;
}

/**
 * setAlias - sets an alias to a string
 * @infoStruct: parameter struct
 * @aliasString: the string alias
 * Return: Always 0 on success, 1 on error
 */
int setAlias(info_t *infoStruct, char *aliasString)
{
    char *p;

    p = _strchr(aliasString, '=');
    if (!p)
        return 1;
    if (!*++p)
        return removeAlias(infoStruct, aliasString);

    removeAlias(infoStruct, aliasString);
    return (addNodeEnd(&(infoStruct->alias), aliasString, 0) == NULL);
}

/**
 * printAlias - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int printAlias(list_t *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = _strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * manageAlias - mimics the alias builtin (man alias)
 * @infoStruct: Structure containing potential arguments.
 * Return: Always 0
 */
int manageAlias(info_t *infoStruct)
{
    int i = 0;
    char *p = NULL;
    list_t *node = NULL;

    if (infoStruct->argc == 1)
    {
        node = infoStruct->alias;
        while (node)
        {
            printAlias(node);
            node = node->next;
        }
        return 0;
    }
    for (i = 1; infoStruct->argv[i]; i++)
    {
        p = _strchr(infoStruct->argv[i], '=');
        if (p)
            setAlias(infoStruct, infoStruct->argv[i]);
        else
            printAlias(nodeStartsWith(infoStruct->alias, infoStruct->argv[i], '='));
    }

    return 0;
}

