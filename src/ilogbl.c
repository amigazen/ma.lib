/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_ilogb.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * ilogbl(long double x)
 * return the binary exponent of non-zero x
 * ilogbl(0) = 0x80000001
 * ilogbl(inf/NaN) = 0x7fffffff (no signal is raised)
 * Note: SAS/C maps long double to double, so delegate to ilogb()
 */

#include <math.h>
#include "include/internal/m99_math.h"

int ilogbl(long double x)
{
    /* SAS/C maps long double to double, so delegate to ilogb() */
    return ilogb((double)x);
}

