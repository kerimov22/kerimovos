// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/drivers/ata.h

#ifndef KERNEL_ATA_H
#define KERNEL_ATA_H
#include <stddef.h>
#include <stdint.h>
void ata_init(void);
int ata_read_sectors(uint8_t drive, uint64_t lba, uint32_t count, void *buf);
#endif
