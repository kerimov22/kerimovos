// SPDX-License-Identifier: GPL-3.0-or-later
/* scheduler.cpp — stub. */

#include "scheduler.h"
#include "printf.h"

extern "C" void scheduler_init(void) { kprintf("scheduler: stub\n"); }

extern "C" void spawn_init(void) {
    /* TODO: spawn init userspace process */
    kprintf("spawn_init: stub\n");
}
