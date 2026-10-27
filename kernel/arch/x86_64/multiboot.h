// SPDX-License-Identifier: GPL-3.0-or-later
/* multiboot.h — Multiboot2 information structures (passed by GRUB in RBX). */

#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stddef.h>
#include <stdint.h>

#define MULTIBOOT_MAGIC   0x36d76289

/* Tag types */
#define MULTIBOOT_TAG_TYPE_END             0
#define MULTIBOOT_TAG_TYPE_CMDLINE         1
#define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME 2
#define MULTIBOOT_TAG_TYPE_MODULE          3
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO   4
#define MULTIBOOT_TAG_TYPE_BOOTDEV         5
#define MULTIBOOT_TAG_TYPE_MMAP            6
#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER     7

/* Memory map entry types */
#define MULTIBOOT_MEMORY_AVAILABLE         1
#define MULTIBOOT_MEMORY_RESERVED          2
#define MULTIBOOT_MEMORY_ACPI              3
#define MULTIBOOT_MEMORY_NVS               4
#define MULTIBOOT_MEMORY_BADRAM            5

struct multiboot_tag {
    uint32_t type;
    uint32_t size;
} __attribute__((packed));

struct multiboot_tag_string {
    uint32_t type;
    uint32_t size;
    char     string[0];
} __attribute__((packed));

struct multiboot_tag_basic_meminfo {
    uint32_t type;
    uint32_t size;
    uint32_t mem_lower;
    uint32_t mem_upper;
} __attribute__((packed));

struct multiboot_tag_mmap {
    uint32_t type;
    uint32_t size;
    uint32_t entry_size;
    uint32_t entry_version;
    struct {
        uint64_t addr;
        uint64_t len;
        uint32_t type;
        uint32_t zero;
    } entries[0];
} __attribute__((packed));

struct multiboot_info {
    uint32_t total_size;
    uint32_t reserved;
    struct multiboot_tag tags[0];
} __attribute__((packed));

/* Helper: iterate over multiboot tags */
#define MULTIBOOT_TAG_END(mbi) \
    ((struct multiboot_tag *)((uint8_t *)(mbi) + (mbi)->total_size))

#define MULTIBOOT_TAG_NEXT(tag) \
    ((struct multiboot_tag *)((uint8_t *)(tag) + (tag)->size))

#endif /* MULTIBOOT_H */
