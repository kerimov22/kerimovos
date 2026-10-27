; SPDX-License-Identifier: GPL-3.0-or-later
; irq.asm — IRQ stubs (32-47).

[BITS 64]
section .text
global irq_handlers

irq_handlers:
    times 16 dq irq_stub

irq_stub:
    iretq
