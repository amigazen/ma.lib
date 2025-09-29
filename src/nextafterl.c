/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_nextafter.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * nextafterl(long double x, long double y)
 * return the next machine floating-point number of x in the
 * direction toward y.
 * Note: SAS/C maps long double to double, so delegate to nextafter()
 */

#include <math.h>
#include "include/internal/m99_math.h"

long double nextafterl(long double x, long double y)
{
    /* SAS/C maps long double to double, so delegate to nextafter() */
    return (long double)nextafter((double)x, (double)y);
}
