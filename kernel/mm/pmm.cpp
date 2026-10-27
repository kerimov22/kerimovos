// SPDX-License-Identifier: GPL-3.0-or-later
/* pmm.cpp — bitmap physical allocator stub. */

#include "pmm.h"

#include <stddef.h>
#include <stdint.h>

extern "C" void pmm_init(struct multiboot_info *mbi) {
    (void)mbi;
    /* TODO: parse E820/UEFI memory map, build bitmap. */
}

extern "C" void *pmm_alloc(void) {
    /* TODO: return a free 4 KiB page. */
    return (void *)0x100000;
}

extern "C" void pmm_free(void *addr) {
    (void)addr;
    /* TODO: free page back to bitmap. */
}
