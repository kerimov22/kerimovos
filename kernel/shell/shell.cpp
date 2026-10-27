// SPDX_LICENSE-Identifier: GPL-3.0-or-later
/* shell.cpp — kernel shell builtins stub. */

#include "shell.h"
#include "cmds.h"
#include "printf.h"

extern "C" void shell_run(void) {
    kprintf("KerimovOS kernel shell builtins available: help ls cd pwd cat mem reboot bootlist disks mount umount cp mv rm mkdir ifconfig ip ping dhcp nslookup\n");
    kprintf("(Full interactive shell is /bin/ksh in userspace.)\n");
}
