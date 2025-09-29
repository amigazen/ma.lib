/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_cos.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double cos(double x)
 * Return cosine function of x.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x

/* Internal functions for cos - reuse from sin.c */
extern int __ieee754_rem_pio2(double x, double *y);
extern double __kernel_sin(double x, double y, int iy);
extern double __kernel_cos(double x, double y);

double cos(double x)
{
    double y[2], z=0.0;
    int n, ix;

    /* High word of x. */
    ix = __HI(x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;
    if(ix <= 0x3fe921fb) return __kernel_cos(x,z);

    /* cos(Inf or NaN) is NaN */
    else if (ix>=0x7ff00000) return x-x;

    /* argument reduction needed */
    else {
        n = __ieee754_rem_pio2(x,y);
        switch(n&3) {
            case 0: return  __kernel_cos(y[0],y[1]);
            case 1: return -__kernel_sin(y[0],y[1],1);
            case 2: return -__kernel_cos(y[0],y[1]);
            default:
                    return  __kernel_sin(y[0],y[1],1);
        }
    }
}
