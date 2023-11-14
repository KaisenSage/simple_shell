#include "shell.h"

/**
 * displayEnvironment - prints the current environment
 * @infoStruct: Structure containing potential arguments.
 * Return: Always 0
 */
int displayEnvironment(info_t *infoStruct)
{
    printStringList(infoStruct->environment);
    return 0;
}

/**
 * getEnvironmentVariable - gets the value of an environment variable
 * @infoStruct: Structure containing potential arguments.
 * @name: Environment variable name
 * Return: the value
 */
char *getEnvironmentVariable(info_t *infoStruct, const char *name)
{
    list_t *node = infoStruct->environment;
    char *p;

    while (node)
    {
        p = startsWith(node->str, name);
        if (p && *p)
            return p;
        node = node->next;
    }
    return NULL;
}

/**
 * setEnvironmentVariable - Initialize a new environment variable
 *                         or modify an existing one
 * @infoStruct: Structure containing potential arguments.
 * Return: Always 0
 */
int setEnvironmentVariable(info_t *infoStruct)
{
    if (infoStruct->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }
    if (_setenv(infoStruct, infoStruct->argv[1], infoStruct->argv[2]))
        return 0;
    return 1;
}

/**
 * unsetEnvironmentVariable - Remove an environment variable
 * @infoStruct: Structure containing potential arguments.
 * Return: Always 0
 */
int unsetEnvironmentVariable(info_t *infoStruct)
{
    int i;

    if (infoStruct->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }
    for (i = 1; i <= infoStruct->argc; i++)
        _unsetenv(infoStruct, infoStruct->argv[i]);

    return 0;
}

/**
 * initializeEnvironmentList - populates environment linked list
 * @infoStruct: Structure containing potential arguments.
 * Return: Always 0
 */
int initializeEnvironmentList(info_t *infoStruct)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        addNodeEnd(&node, environ[i], 0);
    infoStruct->environment = node;
    return 0;
}

