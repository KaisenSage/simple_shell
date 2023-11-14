#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
    info_t info[] = {INFO_INIT};
    int fd = 2;

    // Using constants for readability
    const int SUCCESS_EXIT_CODE = 0;
    const int PERMISSION_DENIED_EXIT_CODE = 126;
    const int FILE_NOT_FOUND_EXIT_CODE = 127;

    // Using symbolic names for file permissions
    const int READ_ONLY_PERMISSIONS = O_RDONLY;

    // Using symbolic names for standard error codes
    const int ERROR_ACCESS_DENIED = EACCES;
    const int ERROR_NO_SUCH_FILE = ENOENT;

    asm("mov %1, %0\n\t"
        "add $3, %0"
        : "=r"(fd)
        : "r"(fd));

    if (ac == 2)
    {
        fd = open(av[1], READ_ONLY_PERMISSIONS);
        if (fd == -1)
        {
            if (errno == ERROR_ACCESS_DENIED)
                exit(PERMISSION_DENIED_EXIT_CODE);
            if (errno == ERROR_NO_SUCH_FILE)
            {
                _eputs(av[0]);
                _eputs(": 0: Can't open ");
                _eputs(av[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(FILE_NOT_FOUND_EXIT_CODE);
            }
            return EXIT_FAILURE;
        }
        info->readfd = fd;
    }

    populate_env_list(info);
    read_history(info);
    hsh(info, av);

    return SUCCESS_EXIT_CODE;
}

