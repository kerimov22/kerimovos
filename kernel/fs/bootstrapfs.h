// SPDX-License-Identifier: GPL-3.0-or-later
/* bootstrapfs.h — create FHS tree on boot device + unpack sources. */

#ifndef KERNEL_BOOTSTRAPFS_H
#define KERNEL_BOOTSTRAPFS_H

#include <stddef.h>

struct multiboot_info;

extern "C" void bootstrapfs_run(struct multiboot_info *mbi);

#endif
