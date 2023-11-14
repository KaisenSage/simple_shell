#include "shell.h"

/**
 * checkInteractive - returns true if shell is in interactive mode
 * @infoStruct: struct containing information
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int checkInteractive(info_t *infoStruct)
{
    return (isatty(STDIN_FILENO) && infoStruct->readFileDescriptor <= 2);
}

/**
 * isDelimiter - checks if character is a delimiter
 * @character: the char to check
 * @delimiters: the delimiter string
 * Return: 1 if true, 0 if false
 */
int isDelimiter(char character, char *delimiters)
{
    while (*delimiters)
        if (*delimiters++ == character)
            return (1);
    return (0);
}

/**
 * isAlphabetic - checks for alphabetic character
 * @ch: The character to input
 * Return: 1 if ch is alphabetic, 0 otherwise
 */
int isAlphabetic(int ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * stringToInteger - converts a string to an integer
 * @inputString: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int stringToInteger(char *inputString)
{
    int index, sign = 1, flag = 0, result = 0;

    for (index = 0;  inputString[index] != '\0' && flag != 2; index++)
    {
        if (inputString[index] == '-')
            sign *= -1;

        if (inputString[index] >= '0' && inputString[index] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (inputString[index] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    if (sign == -1)
        return -result;
    else
        return result;
}

