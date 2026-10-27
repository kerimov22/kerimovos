// SPDX-License-Identifier: GPL-3.0-or-later
/* repl.c — interactive REPL with prompt, history, line editing. */

#include "repl.h"
#include "parser.h"
#include "eval.h"
#include "history.h"
#include "readline.h"
#include "ansi.h"
#include "vars.h"
#include "libker.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

static char prompt[256] = "\033[1;32mkerimovos\033[0m\033[1;34m:\033[0m\033[1;36m\w\033[0m\033[1;32m$ \033[0m";

int repl_run(void) {
    history_load();
    for (;;) {
        /* expand \w in prompt to cwd */
        char disp[512];
        ker_snprintf(disp, sizeof(disp), "%s", prompt);
        char *p = disp;
        while (*p) {
            if (p[0] == '\\' && p[1] == 'w') {
                ker_puts("\033[1;36m/");
                ker_puts(vars_get("PWD") ? vars_get("PWD") : "/");
                ker_puts("\033[0m");
                p += 2;
                continue;
            }
            ker_putchar(*p++);
        }
        char *line = readline("");
        if (!line) { ker_puts("exit"); break; }
        if (line[0]) history_add(line);
        int rc = eval_line(line);
        free(line);
        if (rc == -2) break; /* exit */
    }
    history_save();
    return 0;
}
