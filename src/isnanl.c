/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_isnan.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * isnanl(x) returns 1 if x is nan, else 0
 * Note: SAS/C maps long double to double, so delegate to isnan()
 */

#include <math.h>
#include "include/internal/m99_math.h"

int isnanl(long double x)
{
    /* SAS/C maps long double to double, so delegate to isnan() */
    return isnan((double)x);
}
