; SPDX-License-Identifier: GPL-3.0-or-later
; boot.asm — KerimovOS kernel entry (Multiboot2, long mode).
;
; GRUB loads the kernel at 1 MiB and passes:
;   RAX = multiboot magic number (0x36d76289)
;   RBX = pointer to multiboot_info structure
;
; We switch to 64-bit long mode and jump to kernel_main(RBX).

[BITS 32]
[ORG 0x100000]

; Multiboot2 header (must be within first 8 KB of kernel, aligned on 8 bytes)
section .multiboot_header
align 8
    multiboot_header_start:
        dd 0xe85250d6                ; magic number (multiboot2)
        dd 0                        ; architecture 0 = i386 (protected mode)
        dd header_end - header_start ; header length
        dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) ; checksum

        ; Optional tags (empty = end)
        dw 0                        ; tag type 0 = end
        dw 0                        ; flags
        dd 8                        ; size
    multiboot_header_end:

section .text
global _start
extern kernel_main

_start:
    ; Save multiboot info pointer from GRUB (RBX)
    mov rdi, rbx                    ; RDI = multiboot_info pointer (1st arg)
    mov rsp, stack_top              ; Set up stack

    ; Enable SSE
    mov eax, cr0
    or eax, 1 << 5                  ; CR0.COPY? no, CR0.EM=0, CR0.MP=1
    mov cr0, eax

    ; Enable long mode via CR4.PAE + EFER.LME + CR0.PG
    mov eax, cr4
    or eax, 1 << 5                  ; CR4.PAE
    mov cr4, eax

    mov ecx, 0xC0000080             ; EFER MSR
    rdmsr
    or eax, 1 << 8                  ; EFER.LME
    wrmsr

    mov eax, cr0
    or eax, 1 << 31                 ; CR0.PG
    mov cr0, eax

    ; Jump to 64-bit code
    jmp 0x08:long_mode_start

section .data
align 4096
stack_bottom:
    resb 16384                      ; 16 KiB kernel stack
stack_top:

section .text64
align 16
[BITS 64]
long_mode_start:
    mov ax, 0x10                    ; data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; RDI already holds multiboot_info pointer
    call kernel_main

.halt:
    cli
    hlt
    jmp .halt
