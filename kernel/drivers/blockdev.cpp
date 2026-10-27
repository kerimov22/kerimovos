// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/drivers/blockdev.cpp

#include "blockdev.h"

void blockdev_init(uint32_t count) {
    (void)count;
}
int blockdev_read(uint32_t disk, uint64_t lba, uint32_t count, void *buf) {
    (void)disk; (void)lba; (void)count; (void)buf; return -1;
}
int blockdev_write(uint32_t disk, uint64_t lba, uint32_t count, const void *buf) {
    (void)disk; (void)lba; (void)count; (void)buf; return -1;
}
