#include "shell.h"

/**
 * safeAtoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int safeAtoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return -1;
		}
		else
			return -1;
	}
	return result;
}

/**
 * printError - prints an error message
 * @infoStruct: the parameter & return info struct
 * @errorMsg: string containing specified error type
 */
void printError(info_t *infoStruct, char *errorMsg)
{
	_eputs(infoStruct->fileName);
	_eputs(": ");
	printDecimal(infoStruct->lineCount, STDERR_FILENO);
	_eputs(": ");
	_eputs(infoStruct->argv[0]);
	_eputs(": ");
	_eputs(errorMsg);
}

/**
 * printDecimal - function prints a decimal (integer) number (base 10)
 * @number: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int printDecimal(int number, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;

	if (number < 0)
	{
		absolute = -number;
		__putchar('-');
		count++;
	}
	else
		absolute = number;

	current = absolute;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return count;
}

/**
 * convertNumber - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convertNumber(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return ptr;
}

/**
 * eliminateComments - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void eliminateComments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}

