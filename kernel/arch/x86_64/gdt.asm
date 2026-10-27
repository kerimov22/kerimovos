; SPDX-License-Identifier: GPL-3.0-or-later
; gdt.asm — GDT descriptors for x86_64 long mode.

[BITS 64]
section .data

gdt_null:
    dq 0
gdt_code:   ; 0x08 — kernel code (executable, readable)
    dw 0xFFFF
    dw 0
    db 0
    db 10011010b
    db 10101111b
    db 0
gdt_data:   ; 0x10 — kernel data
    dw 0xFFFF
    dw 0
    db 0
    db 10010010b
    db 10101111b
    db 0
gdt_code32: ; 0x18 — compatibility code (not used)
    dq 0
gdt_data32: ; 0x20
    dq 0
gdt_end:

gdt_desc:
    dw gdt_end - gdt_null - 1
    dq gdt_null

global gdt_load
gdt_load:
    lgdt [gdt_desc]
    ret

; TSS stub (not used yet)
tss:
    times 104 db 0
