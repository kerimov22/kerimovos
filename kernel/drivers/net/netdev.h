// SPDX-License-Identifier: GPL-3.0-or-later
/* netdev.h — network device interface. */

#ifndef KERNEL_NETDEV_H
#define KERNEL_NETDEV_H

#include <stddef.h>
#include <stdint.h>

#define NET_MAX_DEV 4

struct netdev {
    char name[16];
    uint8_t mac[6];
    int (*send)(struct netdev *dev, const uint8_t *buf, int len);
    int (*recv)(struct netdev *dev, uint8_t *buf, int maxlen);
};

extern "C" void netdev_register(struct netdev *dev);
extern "C" struct netdev *netdev_get(const char *name);

#endif
