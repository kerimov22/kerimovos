// SPDX-License-Identifier: GPL-3.0-or-later
// kpt/src/main.c — kpt package manager stub

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("kpt — KerimovOS Package Manager\n");
        printf("Usage: kpt <command> [args]\n");
        printf("Commands: --list --list-installed install remove search info update --version --help\n");
        return 0;
    }
    if (strcmp(argv[1], "--list") == 0) {
        printf("Available packages: htop grep krdisk kfdisk kpt curl ksh hello calc shell coreutils\n");
    } else if (strcmp(argv[1], "--version") == 0) {
        printf("kpt 1.0.0 (KerimovOS package manager)\n");
    } else if (strcmp(argv[1], "install") == 0) {
        if (argc < 3) { fprintf(stderr, "kpt: specify a package\n"); return 1; }
        printf("kpt: installing %s (TODO)\n", argv[2]);
    } else if (strcmp(argv[1], "remove") == 0) {
        if (argc < 3) { fprintf(stderr, "kpt: specify a package\n"); return 1; }
        printf("kpt: removing %s (TODO)\n", argv[2]);
    } else {
        printf("kpt: unknown command: %s\n", argv[1]);
    }
    return 0;
}
