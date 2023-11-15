#include "kade.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av) {
    ssize_t r = 0;
    int builtin_ret = 0;

    while (r != -1 && builtin_ret != -2) {
        kade_clear_info(info);
        if (kade_interactive(info))
            kade_puts("$ ");
        kade_eputchar(BUF_FLUSH);
        r = kade_get_input(info);
        if (r != -1) {
            kade_set_info(info, av);
            builtin_ret = kade_find_builtin(info);
            if (builtin_ret == -1)
                kade_find_cmd(info);
        } else if (kade_interactive(info))
            kade_putchar('\n');
        kade_free_info(info, 0);
    }
    kade_write_history(info);
    kade_free_info(info, 1);
    if (!kade_interactive(info) && info->status)
        exit(info->status);
    if (builtin_ret == -2) {
        if (info->err_num == -1)
            exit(info->status);
        exit(info->err_num);
    }
    return (builtin_ret);
}

/**
 * kade_find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int kade_find_builtin(info_t *info) {
    int i, built_in_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", kade_myexit},
        {"env", kade_myenv},
        {"help", kade_myhelp},
        {"history", _myhistory},
        {"setenv", kade_mysetenv},
        {"unsetenv", kade_myunsetenv},
        {"cd", kade_mycd},
        {"alias", kade_myalias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++)
        if (kade_strcmp(info->argv[0], builtintbl[i].type) == 0) {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    return built_in_ret;
}

/**
 * kade_find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void kade_find_cmd(info_t *info) {
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];
    if (info->linecount_flag == 1) {
        info->line_count++;
        info->linecount_flag = 0;
    }
    for (i = 0, k = 0; info->arg[i]; i++)
        if (!kade_is_delim(info->arg[i], " \t\n"))
            k++;
    if (!k)
        return;

    path = kade_find_path(info, kade_getenv(info, "PATH="), info->argv[0]);
    if (path) {
        info->path = path;
        kade_fork_cmd(info);
    } else {
        if ((kade_interactive(info) || kade_getenv(info, "PATH=")
            || info->argv[0][0] == '/') && kade_is_cmd(info, info->argv[0]))
            kade_fork_cmd(info);
        else if (*(info->arg) != '\n') {
            info->status = 127;
            kade_print_error(info, "not found\n");
        }
    }
}

/**
 * kade_fork_cmd - forks an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void kade_fork_cmd(info_t *info) {
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1) {
        /* TODO: PUT ERROR FUNCTION */
        perror("Error:");
        return;
    }
    if (child_pid == 0) {
        if (execve(info->path, info->argv, kade_get_environ(info)) == -1) {
            kade_free_info(info, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
        /* TODO: PUT ERROR FUNCTION */
    } else {
        wait(&(info->status));
        if (WIFEXITED(info->status)) {
            info->status = WEXITSTATUS(info->status);
            if (info->status == 126)
                kade_print_error(info, "Permission denied\n");
        }
    }
}
