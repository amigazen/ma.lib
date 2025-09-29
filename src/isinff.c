/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm pattern for infinity detection
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * isinff(x) returns 1 if x is infinity, else 0
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of float */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x

int isinff(float x)
{
    int hx;
    hx = __HI(x);
    hx &= 0x7fffffff;        /* mask off sign bit */
    hx = 0x7f800000 - hx;    /* now hx is 0 if x is infinite */
    return ((unsigned)(hx))>>31;
}
