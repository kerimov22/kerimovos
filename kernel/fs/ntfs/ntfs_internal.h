// SPDX-License-Identifier: GPL-3.0-or-later
/* ntfs_internal.h — internal NTFS structures (on-disk). */

#ifndef NTFS_INTERNAL_H
#define NTFS_INTERNAL_H

#include <stdint.h>

/* NTFS boot sector (first 512 bytes of volume) */
struct ntfs_boot_sector {
    uint8_t  jump[3];
    char     oem[8];
    uint16_t bps;
    uint8_t  spc;
    uint16_t reserved;
    uint8_t  media;
    uint16_t unused;
    uint32_t unused2;
    uint8_t  unused3;
    uint8_t  code[438];
    uint64_t total_sectors;
    uint64_t mft_lcn;
    uint64_t mftmirr_lcn;
    int32_t  clusters_per_mft_record;
    int32_t  clusters_per_index_block;
    uint32_t unused4;
    uint64_t volume_serial;
    uint32_t checksum;
} __attribute__((packed));

/* MFT record header */
struct mft_record {
    uint32_t magic;        // "FILE" / "BAAD"
    uint16_t usa_offset;
    uint16_t usa_count;
    uint64_t lsn;
    uint16_t sequence;
    uint16_t link_count;
    uint16_t attrs_offset;
    uint16_t flags;
    uint32_t bytes_in_use;
    uint32_t bytes_allocated;
} __attribute__((packed));

/* Attribute header */
struct attr_header {
    uint32_t type;         // $STANDARD_INFORMATION=0x10, $FILENAME=0x30, $DATA=0x80, etc.
    uint32_t length;
    uint8_t  non_resident;
    uint8_t  name_length;
    uint16_t name_offset;
    uint16_t flags;
    uint16_t instance;
    uint64_t value_size;    // resident
    uint16_t value_offset;
    uint8_t  indexed;
    uint8_t  padding;
} __attribute__((packed));

/* INDEX_ROOT / INDEX_ALLOCATION */
struct index_root {
    uint32_t type;
    uint16_t collation_rule;
    uint16_t index_block_size;
    uint8_t  clusters_per_index_block;
} __attribute__((packed));

#endif
