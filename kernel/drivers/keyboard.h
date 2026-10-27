// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/drivers/keyboard.h

#ifndef KERNEL_KEYBOARD_H
#define KERNEL_KEYBOARD_H
#include <stddef.h>
void keyboard_init(void);
int  keyboard_getchar(void);
#endif
