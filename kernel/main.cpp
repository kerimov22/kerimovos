// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/main.cpp — kernel_main(struct multiboot_info *)
// Called by GRUB (Multiboot2) with RBX = multiboot_info pointer.

#include "multiboot.h"
#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "irq.h"
#include "pmm.h"
#include "vmm.h"
#include "heap.h"
#include "vfs.h"
#include "bootstrapfs.h"
#include "scheduler.h"
#include "syscall.h"
#include "net_config.h"
#include "blockdev.h"
#include "fat32.h"
#include "ntfs/ntfs.h"
#include "mount.h"
#include "printf.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" void kernel_main(uint32_t magic, struct multiboot_info *mbi) {
    (void)magic;

    /* Default text mode */
    uint32_t text_rows = 25;
    uint32_t text_cols = 80;

    /* Parse multiboot tags */
    if (mbi) {
        struct multiboot_tag *tag = mbi->tags;
        while (tag->type != MULTIBOOT_TAG_TYPE_END) {
            if (tag->type == MULTIBOOT_TAG_TYPE_CMDLINE) {
                struct multiboot_tag_string *cmdline =
                    (struct multiboot_tag_string *)tag;
                kprintf("Cmdline: %s\n", cmdline->string);
            } else if (tag->type == MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME) {
                struct multiboot_tag_string *bl =
                    (struct multiboot_tag_string *)tag;
                kprintf("Boot loader: %s\n", bl->string);
            } else if (tag->type == MULTIBOOT_TAG_TYPE_FRAMEBUFFER) {
                /* Framebuffer tag — text mode info could be extracted here */
                kprintf("Framebuffer tag present\n");
            }
            tag = MULTIBOOT_TAG_NEXT(tag);
        }
    }

    kprintf("KerimovOS kernel v1.8.2\n");
    kprintf("Boot mode: GRUB (Multiboot2)\n");
    kprintf("Text mode: %ux%u\n", text_cols, text_rows);

    gdt_init();
    idt_init();
    isr_install();
    irq_install();

    pmm_init(mbi);
    vmm_init();
    heap_init();
    kprintf("Memory initialised\n");

    blockdev_init(0);

    vfs_init();
    fat32_init();
    ntfs_init();
    mount_root();

    bootstrapfs_run(mbi);

    scheduler_init();
    syscalls_init();
    net_init();

    kprintf("Starting init (userspace)...\n");
    spawn_init();

    kprintf("Kernel: userspace exited, halting\n");
    for (;;) __asm__ __volatile__("hlt");
}
