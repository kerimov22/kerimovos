// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/drivers/vga.h

#ifndef KERNEL_VGA_H
#define KERNEL_VGA_H
#include <stddef.h>
#include <stdint.h>
void vga_init(uint32_t rows, uint32_t cols, uint32_t boot_mode);
void vga_clear(void);
void vga_putc(char c);
void vga_puts(const char *s);
#endif
