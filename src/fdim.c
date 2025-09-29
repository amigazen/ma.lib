/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * double fdim(double x, double y)
 * IEEE 754 fdim function
 */

#include <math.h>
#include "include/internal/m99_math.h"

double fdim(double x, double y)
{
    if (isnan(x) || isnan(y)) return x + y;
    if (x > y) return x - y;
    return 0.0;
}
