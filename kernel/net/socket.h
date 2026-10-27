// SPDX-License-Identifier: GPL-3.0-or-later
/* socket.h — socket API stub. */

#ifndef KERNEL_SOCKET_H
#define KERNEL_SOCKET_H

extern "C" int net_socket(int domain, int type, int protocol);
extern "C" int net_connect(int fd, const void *addr, int addrlen);
extern "C" int net_send(int fd, const void *buf, int len, int flags);
extern "C" int net_recv(int fd, void *buf, int len, int flags);
extern "C" int net_close(int fd);

#endif
