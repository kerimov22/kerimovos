// SPDX-License-Identifier: GPL-3.0-or-later
/* disks.c — enumerate //phys/pdN disks. */

#include "disks.h"
#include "libker.h"
#include "stdio.h"
#include <string.h>

static struct disk g_disks[MAX_DISKS];
static int g_ndisks = 0;

int disk_list(void) {
    int n = disks_enumerate(g_disks, MAX_DISKS);
    ker_puts("DEVICE           MODEL                      SIZE      FS");
    ker_puts("-----------------------------------------------------------");
    for (int i = 0; i < n; i++) {
        const char *fs = "unknown";
        if (g_disks[i].fs_type == 1) fs = "FAT32";
        else if (g_disks[i].fs_type == 2) fs = "NTFS";
        ker_printf("//phys/pd%d  %-24s %9llu bytes  %s\n",
                   g_disks[i].index, g_disks[i].model,
                   (unsigned long long)g_disks[i].size_bytes, fs);
    }
    return 0;
}

int disks_enumerate(struct disk *out, int max) {
    (void)out;(void)max;
    g_ndisks = 0;
    /* TODO: read partition table from block devices */
    return g_ndisks;
}
