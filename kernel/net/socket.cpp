// SPDX-License-Identifier: GPL-3.0-or-later
/* socket.cpp — stub. */

#include "socket.h"
#include "printf.h"

extern "C" int net_socket(int d, int t, int p) { (void)d;(void)t;(void)p; kprintf("socket: stub\n"); return -1; }
extern "C" int net_connect(int fd, const void *a, int l) { (void)fd;(void)a;(void)l; return -1; }
extern "C" int net_send(int fd, const void *b, int l, int f) { (void)fd;(void)b;(void)l;(void)f; return -1; }
extern "C" int net_recv(int fd, void *b, int l, int f) { (void)fd;(void)b;(void)l;(void)f; return -1; }
extern "C" int net_close(int fd) { (void)fd; return -1; }
