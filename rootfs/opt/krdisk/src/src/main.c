// SPDX-License-Identifier: GPL-3.0-or-later
// krdisk/src/main.c — krdisk disk editor stub

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        printf("krdisk — KerimovOS disk partition editor (TUI)\n");
        printf("Usage: krdisk --list | //phys/pdN\n");
        return 0;
    }
    if (strcmp(argv[1], "--list") == 0 || strcmp(argv[1], "-l") == 0) {
        printf("KerimovOS disks (//phys/pdN):\n");
        printf("  //phys/pd0   QEMU HARDDISK   32 GiB   FAT32\n");
        return 0;
    }
    printf("krdisk: editing %s (TUI TODO)\n", argv[1]);
    return 0;
}
