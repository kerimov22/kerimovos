# Contributing to KerimovOS

KerimovOS is open source (GPLv3). Contributions are welcome.

## How to contribute
1. Fork the repository.
2. Create a feature branch.
3. Make your change (all strings that the OS prints must be in English;
   SPDX header `// SPDX-License-Identifier: GPL-3.0-or-later` in every
   source file).
4. Build locally: `cd /usr/src/kerimovos && make` (kbuild).
5. Test in QEMU: `make run-uefi` / `make run`.
6. Submit a pull request.

## Code style
- C: K&R-ish, 4 spaces, SPDX header first line.
- Assembly: NASM, 4 spaces.
- Comments in code may be in any language; user-facing strings in English.
