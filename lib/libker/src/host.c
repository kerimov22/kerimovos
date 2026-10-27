// SPDX-License-Identifier: GPL-3.0-or-later
/* host.c — host build glue: only compiled when HOST_BUILD is defined.
 * Provides the main() entry that KerimovOS apps use on the host so they
 * are real, runnable programs (their KerimovOS entry is syscall-based).
 */

// This file is intentionally tiny; each app provides its own main().
