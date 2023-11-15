#include "kade.h"

/**
 * kade_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void kade_eputs(char *str)
{
    int i = 0;

    if (!str)
        return;
    for (i = 0; str[i] != '\0'; i++)
    {
        kade_eputchar(str[i]);
    }
}

/**
 * kade_eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int kade_eputchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * kade_putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int kade_putfd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * kade_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int kade_putsfd(char *str, int fd)
{
    int count = 0;

    if (!str)
        return 0;
    for (; *str != '\0'; str++)
    {
        count += kade_putfd(*str, fd);
    }
    return count;
}
