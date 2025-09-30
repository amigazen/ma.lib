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

/****** ma.lib/cos ******************************************************
* 
*   NAME	
* 	cos -- Return cosine function of x. (V1.0)
*
*   SYNOPSIS
*	double result = cos(double x);
*	  D0		   D0
*	double cos(double x);
*
*   FUNCTION
*	Compute the cosine of x, where x is in radians. The cosine function
*	returns values in the range [-1, 1]. This implementation uses
*	high-precision algorithms from fdlibm for maximum accuracy.
* 
*   INPUTS
*	x - Input value in radians. Range is approximately [-2^63, 2^63].
*	
*   RESULT
*	result - Cosine of x, in the range [-1, 1]. Returns NaN if x is NaN,
*	        returns 1.0 if x is ±0, returns NaN if x is ±Infinity.
* 
*   EXAMPLE
*	double angle = M_PI / 3.0;  
*	double cosine = cos(angle); 
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Performance is optimized for the Amiga platform.
* 
*   SEE ALSO
*	sin(), tan(), acos(), math.h
* 
******************************************************************************/

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

