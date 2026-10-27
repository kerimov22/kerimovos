// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/drivers/ata.cpp

#include "ata.h"

void ata_init(void) { /* TODO */ }
int ata_read_sectors(uint8_t drive, uint64_t lba, uint32_t count, void *buf) {
    (void)drive; (void)lba; (void)count; (void)buf; return -1;
}
