// SPDX-License-Identifier: GPL-3.0-or-later
// kernel/drivers/timer.h

#ifndef KERNEL_TIMER_H
#define KERNEL_TIMER_H
#include <stddef.h>
#include <cstdint>
void timer_init(uint32_t frequency_hz);
#endif
