// SPDX-License-Identifier: GPL-3.0-or-later
/* exec_cmd.c — execute external command. */

#include "exec_cmd.h"
#include "parser.h"
#include "libker.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int exec_command(command_t *c) {
#ifdef HOST_BUILD
    pid_t pid = fork();
    if (pid < 0) { ker_puts("exec: fork failed"); return 1; }
    if (pid == 0) {
        execvp(c->argv[0], c->argv);
        ker_printf("ksh: command not found: %s\n", c->argv[0]);
        _exit(127);
    }
    if (!c->background) {
        int status;
        waitpid(pid, &status, 0);
        return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    }
    return 0;
#else
    ker_printf("ksh: exec %s (KerimovOS execve: TODO)\n", c->argv[0]);
    return 0;
#endif
}
