# Kerimov Shell (ksh)

## Location
Binary: /opt/ksh/ksh
Sources: /opt/ksh/src/
Symlink: /bin/ksh -> /opt/ksh/ksh, /bin/sh -> ksh

## Overview
Kerimov Shell (ksh) is the native shell of KerimovOS. Despite the name,
it is NOT Korn shell — it is a zsh-like terminal shell written from
scratch for KerimovOS.

## Builtins
cd, pwd, exit, export, unset, set, alias, unalias, echo, read, test,
[, true, false, :, source, ., eval, exec, shift, return, type, command,
jobs, fg, bg, wait, kill, trap, history, bindkey, autoload, prompt

## Features
- ANSI-coloured prompt (PS1/PROMPT)
- Command history (Up/Down, Ctrl+R, !!, !$, !n)
- Line editing (Ctrl+A/E/U/K/W, Ctrl+arrow keys)
- Tab completion (commands, paths, options)
- Autosuggestions (TODO)
- Syntax highlighting (TODO)
- Globbing: *, ?, [abc], {a,b,c}, **/*.txt
- Pipes and redirections: \|, >, >>, <, 2>, 2>&1
- Here-doc: <<EOF, here-string: <<<
- Arithmetic: $((...)), let, ((...)), $[...]
- Conditionals: if/then/elif/else/fi, case/in/esac
- Loops: for x in ..., for ((...)), while, until, repeat N
- set -e, set -x, set -u

## Profiles
- /etc/profile — system-wide profile
- /etc/kshrc — shell rc
- /usr/account/root/.profile — root profile
- /usr/account/user/.profile — user profile

## Script Execution
- ksh script.sh — run script
- ./script.sh — direct execution (shebang #!/bin/ksh)
- #!/bin/ksh -e — with error exit
- #!/bin/sh — POSIX compatibility
