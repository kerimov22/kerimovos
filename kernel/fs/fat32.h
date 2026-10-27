// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/fs/fat32.h

#ifndef KERNEL_FAT32_H
#define KERNEL_FAT32_H
#include <stddef.h>
#include <stdint.h>
extern "C" void fat32_init(void);
extern "C" int fat32_mount(const char *device);
extern "C" int fat32_read_file(const char *path, void *buf, uint32_t max);
extern "C" int fat32_write_file(const char *path, const void *buf, uint32_t len);
#endif
