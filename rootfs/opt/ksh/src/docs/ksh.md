# Kerimov Shell (ksh) — documentation

Kerimov Shell (ksh) is the native shell of KerimovOS. Despite the name it is
not Korn shell; it is a zsh-like terminal shell written from scratch for
KerimovOS.

## Location
Binary: /opt/ksh/ksh
Sources: /opt/ksh/src/ (also in /usr/src/kerimovos/ksh/)
Symlink: /bin/ksh -> /opt/ksh/ksh

## Builtins
cd, pwd, exit, export, unset, set, alias, unalias, echo, read, test, source,
eval, exec, shift, return, type, command, jobs, fg, bg, wait, kill, trap,
history, bindkey, autoload, prompt.

## Features
- ANSI-coloured prompt (PS1/PROMPT)
- History (Up/Down, Ctrl+R, !!, !$, !n)
- Line editing (Ctrl+A/E/U/K/W, Ctrl+arrows)
- Tab completion, autosuggestions, syntax highlighting (TODO)
- Globbing *, ?, [abc], {a,b,c}, **/*.txt
- Pipes and redirections | > >> < 2> 2>&1
- here-doc <<EOF, here-string <<<
- Arithmetic $((...)), let, ((...))
- set -e -x -u

## Build
cd /opt/ksh && make   (or from /usr/src/kerimovos: make ksh)
