; SPDX-License-Identifier: GPL-3.0-or-later
; idt.asm — IDT stub entries (ISRs wired to common handler).

[BITS 64]
section .data

isr_stub_common:
    ; placeholder — real ISRs in isr.asm
    ret

idt_entries:
    times 256 dq 0

idt_desc:
    dw 256 * 8 - 1
    dq idt_entries

global idt_load
idt_load:
    lidt [idt_desc]
    ret
