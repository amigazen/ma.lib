/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * double fmin(double x, double y)
 * IEEE 754 fmin function
 */

#include <math.h>
#include "include/internal/m99_math.h"

double fmin(double x, double y)
{
    if (isnan(x)) return y;
    if (isnan(y)) return x;
    if (x < y) return x;
    if (y < x) return y;
    /* x == y, return the one with positive zero */
    if (signbit(x)) return x;
    return y;
}
