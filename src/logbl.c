/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_logb.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * long double logbl(x)
 * IEEE 754 logb. Included to pass IEEE test suite. Not recommend.
 * Use ilogb instead.
 * Note: SAS/C maps long double to double, so delegate to logb()
 */

#include <math.h>
#include "include/internal/m99_math.h"

long double logbl(long double x)
{
    /* SAS/C maps long double to double, so delegate to logb() */
    return (long double)logb((double)x);
}

