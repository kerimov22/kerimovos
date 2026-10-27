// SPDX-License-Identifier: GPL-3.0-or-later
/* cmds.cpp — stub. */

#include "cmds.h"
#include "printf.h"

extern "C" int cmd_help(int argc, char **argv) {
    (void)argc;(void)argv;
    kprintf("KerimovOS builtin commands: help, ls, cd, pwd, cat, mem, reboot, bootlist, disks, mount, umount, cp, mv, rm, mkdir, ifconfig, ip, ping, dhcp, nslookup\n");
    return 0;
}
