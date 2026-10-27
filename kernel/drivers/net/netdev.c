// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/drivers/net/netdev.c

#include "netdev.h"

static struct net_device *devices[8];
static int device_count = 0;

int netdev_register(struct net_device *dev) {
    if (device_count >= 8) return -1;
    devices[device_count++] = dev;
    return device_count - 1;
}
