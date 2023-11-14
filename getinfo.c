#include "shell.h"

/**
 * initializeInfo - initializes info_t struct
 * @info: struct address
 */
void initializeInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * populateInfo - initializes info_t struct
 * @info: struct address
 * @argumentVector: argument vector
 */
void populateInfo(info_t *info, char **argumentVector)
{
	int i = 0;

	info->fname = argumentVector[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceAlias(info);
		replaceVariables(info);
	}
}

/**
 * freeInfo - frees info_t struct fields
 * @info: struct address
 * @freeAll: true if freeing all fields
 */
void freeInfo(info_t *info, int freeAll)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (freeAll)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

