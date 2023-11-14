#include "shell.h"

/**
 * bufferChainedCommands - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of length var
 *
 * Return: bytes read
 */
ssize_t bufferChainedCommands(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytesRead = 0;
	size_t length_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		bytesRead = getline(buffer, &length_p, stdin);
#else
		bytesRead = customGetline(info, buffer, &length_p);
#endif
		if (bytesRead > 0)
		{
			if ((*buffer)[bytesRead - 1] == '\n')
			{
				(*buffer)[bytesRead - 1] = '\0';
				bytesRead--;
			}
			info->lineCountFlag = 1;
			removeComments(*buffer);
			buildHistoryList(info, *buffer, info->historyCount++);
			{
				*length = bytesRead;
				info->commandBuffer = buffer;
			}
		}
	}
	return bytesRead;
}

/**
 * getInput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInput(info_t *info)
{
	static char *buffer;
	static size_t iterator, j, length;
	ssize_t bytesRead = 0;
	char **buffer_p = &(info->arguments), *p;

	_putchar(BUF_FLUSH);
	bytesRead = bufferChainedCommands(info, &buffer, &length);
	if (bytesRead == -1)
		return (-1);
	if (length)
	{
		j = iterator;
		p = buffer + iterator;

		checkChain(info, buffer, &j, iterator, length);
		while (j < length)
		{
			if (isChain(info, buffer, &j))
				break;
			j++;
		}

		iterator = j + 1;
		if (iterator >= length)
		{
			iterator = length = 0;
			info->commandBufferType = CMD_NORMAL;
		}

		*buffer_p = p;
		return (_strlen(p));
	}

	*buffer_p = buffer;
	return bytesRead;
}

/**
 * readBuffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: bytesRead
 */
ssize_t readBuffer(info_t *info, char *buffer, size_t *i)
{
	ssize_t bytesRead = 0;

	if (*i)
		return (0);
	bytesRead = read(info->readfd, buffer, READ_BUFFER_SIZE);
	if (bytesRead >= 0)
		*i = bytesRead;
	return bytesRead;
}

/**
 * customGetline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int customGetline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t iterator, length;
	size_t k;
	ssize_t bytesRead = 0, size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		size = *length;
	if (iterator == length)
		iterator = length = 0;

	bytesRead = readBuffer(info, buffer, &length);
	if (bytesRead == -1 || (bytesRead == 0 && length == 0))
		return (-1);

	c = _strchr(buffer + iterator, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : length;
	new_p = _realloc(p, size, size ? size + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (size)
		_strncat(new_p, buffer + iterator, k - iterator);
	else
		_strncpy(new_p, buffer + iterator, k - iterator + 1);

	size += k - iterator;
	iterator = k;
	p = new_p;

	if (length)
		*length = size;
	*ptr = p;
	return size;
}

/**
 * sigintHandler - blocks ctrl-C
 * @sigNum: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sigNum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

