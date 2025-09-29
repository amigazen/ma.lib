/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_copysign.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * copysignl(long double x, long double y)
 * copysignl(x,y) returns a value with the magnitude of x and
 * with the sign bit of y.
 * Note: SAS/C maps long double to double, so delegate to copysign()
 */

#include <math.h>
#include "include/internal/m99_math.h"

long double copysignl(long double x, long double y)
{
    /* SAS/C maps long double to double, so delegate to copysign() */
    return (long double)copysign((double)x, (double)y);
}
