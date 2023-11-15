#include "kade.h"

/**
 * kade_clear_info - initializes info_t struct
 * @info: struct address
 */
void kade_clear_info(info_t *info) {
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * kade_set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void kade_set_info(info_t *info, char **av) {
    int i = 0;

    info->fname = av[0];
    if (info->arg) {
        info->argv = kade_strtow(info->arg, " \t");
        if (!info->argv) {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv) {
                info->argv[0] = kade_strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++) {
            /* Keep going till the end of info->argv */
        }
        info->argc = i;

        kade_replace_alias(info);
        kade_replace_vars(info);
    }
}

/**
 * kade_free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void kade_free_info(info_t *info, int all) {
    kade_ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (all) {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->env)
            kade_free_list(&(info->env));
        if (info->history)
            kade_free_list(&(info->history));
        if (info->alias)
            kade_free_list(&(info->alias));
        kade_ffree(info->environ);
        info->environ = NULL;
        kade_bfree((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        kade_putchar(BUF_FLUSH);
    }
}
