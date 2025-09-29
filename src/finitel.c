/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_finite.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * finitel(x) returns 1 if x is finite, else 0
 * Note: SAS/C maps long double to double, so delegate to finite()
 */

#include <math.h>
#include "include/internal/m99_math.h"

int finitel(long double x)
{
    /* SAS/C maps long double to double, so delegate to finite() */
    return finite((double)x);
}
