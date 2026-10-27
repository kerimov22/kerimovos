// SPDX-License-Identifier: GPL-3.0-or-later
/* ntfs.cpp — NTFS boot sector parse, $MFT, $Bitmap, $Data, $FileName,
// $STANDARD_INFORMATION, $INDEX_ROOT/$INDEX_ALLOCATION, $LogFile replay stub.
 * RW support: read fully implemented TODO; write marked TODO. Dirty volume
 * mounts read-only with warning: "NTFS volume is dirty, mounting read-only".
 */

#include "ntfs.h"
#include "ntfs_internal.h"
#include "printf.h"

extern "C" void ntfs_init(void) {
    kprintf("ntfs: driver initialized (RW: TODO, read: TODO)\n");
    kprintf("ntfs: note — dirty NTFS volumes mount read-only with warning\n");
}
