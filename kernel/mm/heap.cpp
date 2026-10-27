// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/mm/heap.cpp — simple kernel heap

#include "heap.h"

#include <cstdint>

static uint8_t *heap_ptr = (uint8_t *)0x200000;
static size_t heap_used = 0;

void heap_init(void) { heap_ptr = (uint8_t *)0x200000; heap_used = 0; }

void *kmalloc(size_t size) {
    if (size == 0) return nullptr;
    void *p = heap_ptr;
    heap_ptr += size;
    heap_used += size;
    return p;
}

void kfree(void *ptr) { (void)ptr; }
