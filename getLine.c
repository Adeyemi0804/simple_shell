#include "kade.h"

/**
 * kade_input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t kade_input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len) {
        /*bfree((void **)info->cmd_buf);*/
        free(*buf);
        *buf = NULL;
        signal(SIGINT, kade_sigintHandler);
#if USE_GETLINE
        r = getline(buf, &len_p, stdin);
#else
        r = kade_getline(info, buf, &len_p);
#endif
        if (r > 0) {
            if ((*buf)[r - 1] == '\n') {
                (*buf)[r - 1] = '\0';
                r--;
            }
            info->linecount_flag = 1;
            kade_remove_comments(*buf);
            kade_build_history_list(info, *buf, info->histcount++);
            /* if (_strchr(*buf, ';')) is this a command chain? */
            {
                *len = r;
                info->cmd_buf = buf;
            }
        }
    }
    return (r);
}

/**
 * kade_get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t kade_get_input(info_t *info)
{
    static char *buf;
    static size_t i, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    kade_putchar(BUF_FLUSH);
    r = kade_input_buf(info, &buf, &len);
    if (r == -1)
        return (-1);
    if (len) {
        j = i;
        p = buf + i;

        kade_check_chain(info, buf, &j, i, len);
        for (j = i; j < len; j++) {
            if (kade_is_chain(info, buf, &j))
                break;
        }

        i = j + 1;
        if (i >= len) {
            i = len = 0;
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p;
        return (kade_strlen(p));
    }

    *buf_p = buf;
    return (r);
}

/**
 * kade_read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t kade_read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return (0);
    r = read(info->readfd, buf, READ_BUF_SIZE);
    if (r >= 0)
        *i = r;
    return (r);
}

/**
 * kade_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int kade_getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = kade_read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return (-1);

    c = kade_strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = kade_realloc(p, s, s ? s + k : k + 1);
    if (!new_p)
        return (p ? free(p), -1 : -1);

    if (s)
        kade_strncat(new_p, buf + i, k - i);
    else
        kade_strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return (s);
}

/**
 * kade_sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void kade_sigintHandler(__attribute__((unused)) int sig_num)
{
    kade_puts("\n");
    kade_puts("$ ");
    kade_putchar(BUF_FLUSH);
}
