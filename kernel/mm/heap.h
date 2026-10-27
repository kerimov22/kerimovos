// SPDX-License-Identifier: GPL-3.0-or-later
/* heap.h — kmalloc/kfree. */

#ifndef KERNEL_HEAP_H
#define KERNEL_HEAP_H

#include <stddef.h>

extern "C" void heap_init(void);
extern "C" void *kmalloc(size_t size);
extern "C" void  kfree(void *ptr);

#endif
