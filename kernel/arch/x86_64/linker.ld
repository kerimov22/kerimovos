# SPDX-License-Identifier: GPL-3.0-or-later
# kernel linker script — x86_64 long mode, Multiboot2 compliant

OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)

SECTIONS
{
    /* Multiboot2 header must be within first 8 KB of kernel image */
    . = 0x100000;

    .multiboot_header : {
        *(.multiboot_header)
    }

    .text : {
        *(.text)
        *(.text.*)
    }

    .text64 : {
        *(.text64)
        *(.text64.*)
    }

    .rodata : {
        *(.rodata)
        *(.rodata.*)
    }

    .data : {
        *(.data)
        *(.data.*)
    }

    .bss : {
        *(.bss)
        *(.bss.*)
        COMMON
    }

    /DISCARD/ : {
        *(.eh_frame)
        *(.note.GNU-stack)
        *(.comment)
    }
}
