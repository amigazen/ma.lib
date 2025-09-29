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
 * isnan(x) returns 1 if x is nan, else 0; no branching!
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

int isnan(double x)
{
    int hx,lx;
    hx = (__HI(x)&0x7fffffff);
    lx = __LO(x);
    hx |= (unsigned)(lx|(-lx))>>31;	
    hx = 0x7ff00000 - hx;
    return ((unsigned)(hx))>>31;
}
