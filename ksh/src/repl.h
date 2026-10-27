// SPDX-License-Identifier: GPL-3.0-or-later
/* repl.h — read-eval-print loop. */

#ifndef REPL_H
#define REPL_H

int repl_run(void);
int run_script(const char *path, char **args, int nargs);

#endif
