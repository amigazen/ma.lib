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
 * finitef(x) returns 1 if x is finite, else 0; no branching!
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of float */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x

int finitef(float x)
{
    int hx; 
    hx = __HI(x);
    return (unsigned)((hx&0x7fffffff)-0x7f800000)>>31;
}
