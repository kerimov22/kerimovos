// SPDX-License-Identifier: GPL-3.0-or-later
/* exec.h — execve with shebang stub. */

#ifndef KERNEL_EXEC_H
#define KERNEL_EXEC_H

extern "C" int exec_execve(const char *path);

#endif
