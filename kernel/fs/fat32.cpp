// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/fs/fat32.cpp — FAT32 driver stub

#include "fat32.h"

void fat32_init(void) { /* TODO: implement FAT32 reader */ }
int fat32_mount(const char *device) { (void)device; return -1; }
int fat32_read_file(const char *path, void *buf, uint32_t max) {
    (void)path; (void)buf; (void)max; return -1;
}
int fat32_write_file(const char *path, const void *buf, uint32_t len) {
    (void)path; (void)buf; (void)len; return -1;
}
