// SPDX-License-Identifier: GPL-3.0-or-later
/* math_stub.c — TODO: real libm implementation. */

#include "math.h"

double ker_sin(double x) { (void)x; return 0.0; }
double ker_cos(double x) { (void)x; return 1.0; }
double ker_sqrt(double x) { (void)x; return 0.0; }
double ker_fabs(double x) { return x < 0 ? -x : x; }
