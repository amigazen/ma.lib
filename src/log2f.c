/*
 * log2f.c - Base-2 logarithm function (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

float log2f(float x)
{
    return (float)log2((double)x);
}
