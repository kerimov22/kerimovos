; SPDX-License-Identifier: GPL-3.0-or-later
; context.asm — context switch stub (ring 0 <-> ring 3 placeholder).

[BITS 64]
section .text
global context_switch
global restore_user_context

context_switch:
    ; TODO: save current task registers, load next task's
    ret

restore_user_context:
    ; TODO: iretq to user ring-3 context
    ret
