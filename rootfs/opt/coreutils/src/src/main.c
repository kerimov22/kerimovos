// SPDX-License-Identifier: GPL-3.0-or-later
// coreutils/src/main.c — coreutils multiplexer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *pn = strrchr(argv[0], '/');
    pn = pn ? pn + 1 : argv[0];

    if (strcmp(pn, "cp") == 0) {
        if (argc < 3) { fprintf(stderr, "cp: missing file operand\n"); return 1; }
        printf("cp: copying %s -> %s (TODO)\n", argv[1], argv[2]);
        return 0;
    }
    if (strcmp(pn, "ls") == 0) { printf("ls: TODO\n"); return 0; }
    if (strcmp(pn, "cat") == 0) { printf("cat: TODO\n"); return 0; }
    if (strcmp(pn, "mv") == 0) { printf("mv: TODO\n"); return 0; }
    if (strcmp(pn, "rm") == 0) { printf("rm: TODO\n"); return 0; }
    if (strcmp(pn, "mkdir") == 0) { printf("mkdir: TODO\n"); return 0; }

    printf("%s: not implemented (TODO)\n", pn);
    return 0;
}
