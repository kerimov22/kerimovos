// SPDX-License-Identifier: GPL-3.0-or-later
/* pmm.h — physical memory allocator (bitmap). */

#ifndef KERNEL_PMM_H
#define KERNEL_PMM_H

#include <stddef.h>
#include <stdint.h>

struct multiboot_info;

extern "C" void pmm_init(struct multiboot_info *mbi);
extern "C" void *pmm_alloc(void);
extern "C" void  pmm_free(void *addr);

#endif
