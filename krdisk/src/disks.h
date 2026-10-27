// SPDX-License-Identifier: GPL-3.0-or-later
/* disks.h */

#ifndef DISKS_H
#define DISKS_H

#define MAX_DISKS 16
#include <stdint.h>

struct disk {
    int index;
    uint64_t size_bytes;
    char model[64];
    char label[32];
    int fs_type; /* 0 unknown, 1 fat32, 2 ntfs */
    int part_count;
};

int disk_list(void);
int disks_enumerate(struct disk *out, int max);

#endif
