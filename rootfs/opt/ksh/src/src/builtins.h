// SPDX-License-Identifier: GPL-3.0-or-later
/* builtins.h */

#ifndef BUILTINS_H
#define BUILTINS_H

int builtin_exit(int argc, char **argv);
int builtin_cd(int argc, char **argv);
int builtin_pwd(int argc, char **argv);
int builtin_export(int argc, char **argv);
int builtin_unset(int argc, char **argv);
int builtin_echo(int argc, char **argv);
int builtin_type(int argc, char **argv);
int builtin_history(int argc, char **argv);
int builtin_alias(int argc, char **argv);
int builtin_set(int argc, char **argv);

#endif
