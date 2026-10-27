; SPDX-License-Identifier: GPL-3.0-or-later
; lib/libker/src/syscall.S

[BITS 64]
global ker_syscall

ker_syscall:
    syscall
    ret
