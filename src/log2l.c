/*
 * log2l.c - Base-2 logarithm function (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

long double log2l(long double x)
{
    return (long double)log2((double)x);
}
