#include "kade.h"

/**
 * kade_myexit - exits the shell
 * @info: Structure containing potential arguments.
 *
 * Return: exits with a given exit status.
 */
int kade_myexit(info_t *info)
{
    int exitcheck;
    int i;

    for (i = 0; info->argv[i] != NULL; i++) {
        if (info->argv[1]) {
            exitcheck = kade_erratoi(info->argv[1]);
            if (exitcheck == -1) {
                info->status = 2;
                kade_print_error(info, "Illegal number: ");
                kade_eputs(info->argv[1]);
                kade_eputchar('\n');
                return 1;
            }
            info->err_num = kade_erratoi(info->argv[1]);
            return -2;
        }
    }
    info->err_num = -1;
    return -2;
}

/**
 * kade_mycd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int kade_mycd(info_t *info)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    if (info->argv[1] != NULL) {
        s = getcwd(buffer, 1024);
        if (!s)
            kade_puts("TODO: >>getcwd failure emsg here<<\n");
        if (!info->argv[1]) {
            dir = kade_getenv(info, "HOME=");
            if (!dir) {
                chdir_ret = chdir((dir = kade_getenv(info, "PWD=")) ? dir : "/");
            } else {
                chdir_ret = chdir(dir);
            }
        } else if (kade_strcmp(info->argv[1], "-") == 0) {
            if (!kade_getenv(info, "OLDPWD=")) {
                kade_puts(s);
                kade_putchar('\n');
                return 1;
            }
            kade_puts(kade_getenv(info, "OLDPWD="));
            kade_putchar('\n');
            chdir_ret = chdir((dir = kade_getenv(info, "OLDPWD=")) ? dir : "/");
        } else {
            chdir_ret = chdir(info->argv[1]);
        }
        if (chdir_ret == -1) {
            kade_print_error(info, "can't cd to ");
            kade_eputs(info->argv[1]);
            kade_eputchar('\n');
        } else {
            kade_setenv(info, "OLDPWD", kade_getenv(info, "PWD="));
            kade_setenv(info, "PWD", getcwd(buffer, 1024));
        }
        return 0;
    }
    return 0;
}

/**
 * kade_myhelp - prints a help message (not implemented)
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int kade_myhelp(info_t *info)
{
    int i;
    char **arg_array;

    arg_array = info->argv;
    kade_puts("help call works. Function not yet implemented \n");
    for (i = 0; arg_array[i] != NULL; i++) {
        if (0)
            kade_puts(*arg_array); /* temp att_unused workaround */
    }
    return 0;
}
