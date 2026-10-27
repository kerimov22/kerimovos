// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/drivers/blockdev.h

#ifndef KERNEL_BLOCKDEV_H
#define KERNEL_BLOCKDEV_H
#include <stddef.h>
#include <cstdint>

void blockdev_init(uint32_t count);
int blockdev_read(uint32_t disk, uint64_t lba, uint32_t count, void *buf);
int blockdev_write(uint32_t disk, uint64_t lba, uint32_t count, const void *buf);
#endif
