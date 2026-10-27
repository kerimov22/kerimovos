; SPDX-License-Identifier: GPL-3.0-or-later
; isr.asm — ISR stubs (exceptions 0-31).

[BITS 64]
section .text
global isr_handlers

isr_handlers:
    times 32 dq isr_stub

isr_stud_label:  ; placeholder symbol
isr_stub:
    iretq
