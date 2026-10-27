// SPDX-License-Identifier: GPL-3.0-or-later
// ksh/src/main.c — Kerimov Shell entry point

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    printf("Kerimov Shell (ksh) v1.0 — KerimovOS\n");
    printf("Type 'help' for builtins. All messages in English.\n");
    for (;;) {
        printf("kerimovos@shell:~$ ");
        fflush(stdout);
        char line[4096];
        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        size_t n = strlen(line);
        while (n > 0 && (line[n-1] == '\n' || line[n-1] == '\r'))
            line[--n] = 0;
        if (line[0] == 0) continue;
        if (strcmp(line, "exit") == 0) break;
        if (strcmp(line, "help") == 0) {
            printf("Builtins: cd pwd exit help echo\n");
            continue;
        }
        if (strcmp(line, "cd") == 0) {
            printf("cd: TODO\n");
            continue;
        }
        if (strcmp(line, "pwd") == 0) {
            printf("/\n");
            continue;
        }
        if (strcmp(line, "echo") == 0) {
            printf("echo: TODO\n");
            continue;
        }
        printf("ksh: %s: command not found\n", line);
    }
    return 0;
}
