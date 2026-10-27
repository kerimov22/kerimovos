// SPDX-License-Identifier: GPL-3.0-or-later
// kfdisk/src/main.c — kfdisk fdisk-like editor stub

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        printf("kfdisk — KerimovOS fdisk-like partition editor\n");
        printf("Usage: kfdisk [-l] [-t dos|gpt] [//phys/pdN]\n");
        return 0;
    }
    int list = 0;
    const char *disk = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) list = 1;
        else disk = argv[i];
    }
    if (list) {
        if (!disk) disk = "//phys/pd0";
        printf("Disk %s: ... sectors\n", disk);
        printf("Device  Boot  Start  End  Sectors  Size  Type\n");
        printf("(no partitions)\n");
        return 0;
    }
    if (!disk) { printf("kfdisk: specify a disk\n"); return 1; }
    printf("kfdisk: interactive mode on %s (TODO)\n", disk);
    return 0;
}
