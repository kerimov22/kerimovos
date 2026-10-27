// SPDX-License-Identifier: GPL-3.0-or-later
/* vmm.cpp — identity paging stub (kernel already runs at 1 MiB identity-mapped). */

#include "vmm.h"

extern "C" void vmm_init(void) {
    /* TODO: set up PML4/PDPT/PD/PT and enable paging with CR4.PAE + CR4.PGE. */
}
