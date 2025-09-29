/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * log1pf(x) = log(1+x) for float
 * 
 * Based on Python's _math.c implementation with modifications for C89/SAS/C
 */

#include <math.h>
#include <float.h>
#include "include/internal/m99_math.h"

float log1pf(float x)
{
    float y;
    
    /* Handle special case of zero input directly */
    if (x == 0.0f) {
        return x;
    }
    
    if (fabsf(x) < FLT_EPSILON/2.0f) {
        return x;
    }
    else if (-0.5f <= x && x <= 1.0f) {
        y = 1.0f + x;
        return logf(y) - ((y - 1.0f) - x) / y;
    }
    else {
        /* NaNs and infinities should end up here */
        return logf(1.0f + x);
    }
}
