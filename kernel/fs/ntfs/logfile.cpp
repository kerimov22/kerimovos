// SPDX-License-Identifier: GPL-3.0-or-later
/* logfile.cpp — $LogFile replay stub (dirty volume handling). */

#include "ntfs_internal.h"
#include "printf.h"

extern "C" void ntfs_logfile_replay(void) {
    kprintf("ntfs: $LogFile replay not implemented; dirty volume -> read-only\n");
}
