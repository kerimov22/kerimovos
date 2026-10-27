// SPDX-License-Identifier: GPL-3.0-or-later
/* ethernet.cpp — stub. */

#include "ethernet.h"
#include "printf.h"

extern "C" void ethernet_input(const uint8_t *buf, int len) {
    (void)buf;(void)len;
    kprintf("ethernet: packet in (TODO)\n");
}
