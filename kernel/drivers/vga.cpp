// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/drivers/vga.cpp

#include "vga.h"

static volatile uint16_t *vga_buf = (volatile uint16_t *)0xB8000;
static int rows = 25, cols = 80, col = 0, row = 0;

void vga_init(uint32_t r, uint32_t c, uint32_t boot_mode) {
    (void)boot_mode;
    if (r > 0) rows = (int)r;
    if (c > 0) cols = (int)c;
    col = 0; row = 0; vga_clear();
}

void vga_clear(void) {
    for (int i = 0; i < rows * cols; i++) vga_buf[i] = 0x0700 | ' ';
    col = 0; row = 0;
}

void vga_putc(char ch) {
    if (ch == '\n') { col = 0; if (++row >= rows) row = 0; }
    else if (ch == '\r') { col = 0; }
    else { vga_buf[row * cols + col] = (uint16_t)ch | 0x0700; if (++col >= cols) { col = 0; if (++row >= rows) row = 0; } }
}

void vga_puts(const char *s) { while (*s) vga_putc(*s++); }
