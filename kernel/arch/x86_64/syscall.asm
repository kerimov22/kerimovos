; SPDX-License-Identifier: GPL-3.0-or-later
; syscall.asm — syscall entry stub.

[BITS 64]
section .text
global syscall_entry

syscall_entry:
    ; Save registers, dispatch via kernel syscall handler, then iretq
    push rax
    push rcx
    push r11
    mov r10, rcx          ; preserve syscall number? (convention varies)
    call syscall_dispatch
    pop r11
    pop rcx
    pop rax
    iretq

extern syscall_dispatch
