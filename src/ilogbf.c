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
 * ilogbf(float x)
 * return the binary exponent of non-zero x
 * ilogbf(0) = 0x80000001
 * ilogbf(inf/NaN) = 0x7fffffff (no signal is raised)
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of float */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x

int ilogbf(float x)
{
    int hx, ix;

    hx  = (__HI(x))&0x7fffffff;	/* high word of x */
    if(hx<0x00800000) {
        if(hx==0) 
            return 0x80000001;	/* ilogbf(0) = 0x80000001 */
        else			/* subnormal x */
            for (ix = -126; hx>0; hx<<=1) ix -=1;
        return ix;
    }
    else if (hx<0x7f800000) return (hx>>23)-127;
    else return 0x7fffffff;
}
