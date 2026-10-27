// SPDX-License-Identifier: GPL-3.0-or-later
/* panic.cpp — kernel panic. */

#include "printf.h"
#include "vga.h"

extern "C" void kernel_panic(const char *msg) {
    kprintf("\n*** KERNEL PANIC: %s ***\n", msg);
    kprintf("System halted.\n");
    for (;;) __asm__ __volatile__("hlt");
}
