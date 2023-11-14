#include "shell.h"

/**
 * customExit - exits the shell
 * @infoStruct: Structure containing potential arguments.
 * Return: Exits with a given exit status (0) if infoStruct->args[0] != "exit"
 */
int customExit(info_t *infoStruct)
{
	int exitCode;

	if (infoStruct->args[1])  /* If there is an exit argument */
	{
		exitCode = _erratoi(infoStruct->args[1]);
		if (exitCode == -1)
		{
			infoStruct->status = 2;
			printError(infoStruct, "Illegal number: ");
			_eputs(infoStruct->args[1]);
			_eputchar('\n');
			return 1;
		}
		infoStruct->errNum = _erratoi(infoStruct->args[1]);
		return -2;
	}
	infoStruct->errNum = -1;
	return -2;
}

/**
 * customCd - changes the current directory of the process
 * @infoStruct: Structure containing potential arguments.
 * Return: Always 0
 */
int customCd(info_t *infoStruct)
{
	char *currentDir, *newDir, buffer[1024];
	int chdirResult;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!infoStruct->args[1])
	{
		newDir = _getenv(infoStruct, "HOME=");
		if (!newDir)
			chdirResult = chdir((newDir = _getenv(infoStruct, "PWD=")) ? newDir : "/");
		else
			chdirResult = chdir(newDir);
	}
	else if (_strcmp(infoStruct->args[1], "-") == 0)
	{
		if (!_getenv(infoStruct, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return 1;
		}
		_puts(_getenv(infoStruct, "OLDPWD="));
		_putchar('\n');
		chdirResult = chdir((newDir = _getenv(infoStruct, "OLDPWD=")) ? newDir : "/");
	}
	else
	{
		chdirResult = chdir(infoStruct->args[1]);
	}

	if (chdirResult == -1)
	{
		printError(infoStruct, "can't cd to ");
		_eputs(infoStruct->args[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(infoStruct, "OLDPWD", _getenv(infoStruct, "PWD="));
		_setenv(infoStruct, "PWD", getcwd(buffer, 1024));
	}
	return 0;
}

/**
 * customHelp - displays help message
 * @infoStruct: Structure containing potential arguments.
 * Return: Always 0
 */
int customHelp(info_t *infoStruct)
{
	char **argArray;

	argArray = infoStruct->args;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArray); /* temporary unused variable workaround */
	return 0;
}

