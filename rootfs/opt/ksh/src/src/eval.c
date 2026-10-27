// SPDX-License-Identifier: GPL-3.0-or-later
/* eval.c — evaluate a parsed line: builtins or external command. */

#include "eval.h"
#include "builtins.h"
#include "exec_cmd.h"
#include "parser.h"
#include "vars.h"
#include "libker.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

int eval_line(char *line) {
    while (*line == ' ') line++;
    if (!*line) return 0;
    command_t cmds[8];
    int ncmds = parse_line(line, cmds, 8);
    if (ncmds <= 0) return 0;
    command_t *c = &cmds[0];
    if (!c->argv || !c->argv[0]) return 0;
    /* builtins */
    if (!strcmp(c->argv[0], "exit")) return builtin_exit(c->argc, c->argv);
    if (!strcmp(c->argv[0], "cd")) return builtin_cd(c->argc, c->argv);
    if (!strcmp(c->argv[0], "pwd")) return builtin_pwd(c->argc, c->argv);
    if (!strcmp(c->argv[0], "export")) return builtin_export(c->argc, c->argv);
    if (!strcmp(c->argv[0], "unset")) return builtin_unset(c->argc, c->argv);
    if (!strcmp(c->argv[0], "echo")) return builtin_echo(c->argc, c->argv);
    if (!strcmp(c->argv[0], "type")) return builtin_type(c->argc, c->argv);
    if (!strcmp(c->argv[0], "history")) return builtin_history(c->argc, c->argv);
    if (!strcmp(c->argv[0], "alias")) return builtin_alias(c->argc, c->argv);
    if (!strcmp(c->argv[0], "set")) return builtin_set(c->argc, c->argv);
    return exec_command(c);
}
