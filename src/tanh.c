/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_tanh.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double tanh(double x)
 * Return the Hyperbolic Tangent of x
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

static const double one=1.0, two=2.0, tiny = 1.0e-300;

/****** ma.lib/tanh *********************************************************
* 
*   NAME	
* 	tanh -- Return hyperbolic tangent of x. (V1.0)
*
*   SYNOPSIS
*	double result = tanh(double x);
*	  D0		   D0
*	double tanh(double x);
*
*   FUNCTION
*	Compute the hyperbolic tangent of x. The hyperbolic tangent is defined
*	as sinh(x) / cosh(x). This implementation uses high-precision algorithms
*	from fdlibm for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	
*   RESULT
*	result - Hyperbolic tangent of x, in the range [-1, 1]. Returns x if
*	        x is ±0, returns ±1 for large |x|, returns NaN if x is NaN.
* 
*   EXAMPLE
*	double x = 1.0;
*	double result = tanh(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
* 
*   SEE ALSO
*	sinh(), cosh(), atanh(), math.h
* 
******************************************************************************/

double tanh(double x)
{
    double t, z;
    int jx, ix;

    /* High word of |x|. */
    jx = __HI(x);
    ix = jx&0x7fffffff;

    /* x is INF or NaN */
    if(ix>=0x7ff00000) { 
        if (jx>=0) return one/x+one;    /* tanh(+-inf)=+-1 */
        else       return one/x-one;    /* tanh(NaN) = NaN */
    }

    /* |x| < 22 */
    if (ix < 0x40360000) {		/* |x|<22 */
        if (ix<0x3c800000) 		/* |x|<2**-55 */
            return x*(one+x);    	/* tanh(small) = small */
        if (ix>=0x3ff00000) {	/* |x|>=1  */
            t = expm1(two*fabs(x));
            z = one - two/(t+two);
        } else {
            t = expm1(-two*fabs(x));
            z= -t/(t+two);
        }
    /* |x| > 22, return +-1 */
    } else {
        z = one - tiny;		/* raised inexact flag */
    }
    return (jx>=0)? z: -z;
}


