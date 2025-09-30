/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * int fpclassify(double x)
 * C99 fpclassify function
 */

#include <math.h>
#include "include/internal/m99_math.h"

int fpclassify(double x)
{
    if (isnan(x)) return FP_NAN;
    if (isinf(x)) return FP_INFINITE;
    if (x == 0.0) return FP_ZERO;
    if (x < 1.175494e-38 && x > -1.175494e-38) return FP_SUBNORMAL;
    return FP_NORMAL;
}

