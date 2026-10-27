// SPDX-License-Identifier: GPL-3.0-or-later
/* ethernet.h — Ethernet II framing stub. */

#ifndef KERNEL_ETHERNET_H
#define KERNEL_ETHERNET_H

#include <stddef.h>
#include <stdint.h>

extern "C" void ethernet_input(const uint8_t *buf, int len);

#endif
