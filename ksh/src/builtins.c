// SPDX-License-Identifier: GPL-3.0-or-later
/* builtins.c — shell builtins. */

#include "builtins.h"
#include "vars.h"
#include "history.h"
#include "alias.h"
#include "libker.h"
#include "stdio.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int builtin_exit(int argc, char **argv) {
    (void)argc;(void)argv;
    return -2;
}

int builtin_cd(int argc, char **argv) {
    const char *dir = (argc > 1) ? argv[1] : vars_get("HOME");
    if (!dir) dir = "/";
    if (chdir(dir) != 0) { ker_printf("cd: no such directory: %s\n", dir); return 1; }
    vars_set("PWD", dir, 1);
    return 0;
}

int builtin_pwd(int argc, char **argv) {
    (void)argc;(void)argv;
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd))) ker_puts(cwd);
    else ker_puts("/");
    return 0;
}

int builtin_export(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        char *eq = strchr(argv[i], '=');
        if (eq) { *eq = '\0'; vars_set(argv[i], eq+1, 1); *eq = '='; }
        else { const char *v = vars_get(argv[i]); if (v) ker_printf("%s=%s\n", argv[i], v); }
    }
    return 0;
}

int builtin_unset(int argc, char **argv) {
    int rc = 0;
    for (int i = 1; i < argc; i++)
        if (vars_unset(argv[i]) != 0) { ker_printf("unset: %s: not found\n", argv[i]); rc = 1; }
    return rc;
}

int builtin_echo(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        ker_puts(argv[i]);
        if (i < argc - 1) ker_putchar(' ');
    }
    ker_putchar('\n');
    return 0;
}

int builtin_type(int argc, char **argv) {
    if (argc < 2) return 0;
    if (!strcmp(argv[1], "cd") || !strcmp(argv[1], "exit") || !strcmp(argv[1], "echo"))
        ker_printf("%s is a shell builtin\n", argv[1]);
    else ker_printf("%s: not found\n", argv[1]);
    return 0;
}

int builtin_history(int argc, char **argv) {
    (void)argc;(void)argv;
    ker_puts("history: stub");
    return 0;
}

int builtin_alias(int argc, char **argv) {
    (void)argc;(void)argv;
    ker_puts("alias: stub");
    return 0;
}

int builtin_set(int argc, char **argv) {
    (void)argc;(void)argv;
    ker_puts("set: stub");
    return 0;
}
