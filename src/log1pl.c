/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * log1pl(x) = log(1+x) for long double
 * 
 * Based on Python's _math.c implementation with modifications for C89/SAS/C
 * Note: SAS/C maps long double to double, so this is essentially log1p()
 */

#include <math.h>
#include <float.h>
#include "include/internal/m99_math.h"

long double log1pl(long double x)
{
    /* SAS/C maps long double to double, so delegate to log1p() */
    return (long double)log1p((double)x);
}
