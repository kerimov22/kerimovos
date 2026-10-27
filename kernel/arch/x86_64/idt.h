/* SPDX-License-Identifier: GPL-3.0-or-later */
/* kernel/arch/x86_64/idt.h */

#ifndef KERNEL_IDT_H
#define KERNEL_IDT_H
extern "C" void idt_init(void);
extern "C" void isr_handler(void);
#endif
