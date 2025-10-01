/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/e_asin.c and w_asin.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double asin(double x)
 * Method :                  
 *	Since  asin(x) = x + x^3/6 + x^5*3/40 + x^7*15/336 + ...
 *	we approximate asin(x) on [0,0.5] by
 *		asin(x) = x + x*x^2*R(x^2)
 *	where
 *		R(x^2) is a rational approximation of (asin(x)-x)/x^3 
 *	and its remez error is bounded by
 *		|(asin(x)-x)/x^3 - R(x^2)| < 2^(-58.75)
 */

#include <math.h>
#include <errno.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

static const double
one =  1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
huge =  1.000e+300,
pio2_hi =  1.57079632679489655800e+00, /* 0x3FF921FB, 0x54442D18 */
pio2_lo =  6.12323399573676603587e-17, /* 0x3C91A626, 0x33145C07 */
pio4_hi =  7.85398163397448278999e-01, /* 0x3FE921FB, 0x54442D18 */
	/* coefficient for R(x^2) */
pS0 =  1.66666666666666657415e-01, /* 0x3FC55555, 0x55555555 */
pS1 = -3.25565818622400915405e-01, /* 0xBFD4D612, 0x03EB6F7D */
pS2 =  2.01212532134862925881e-01, /* 0x3FC9C155, 0x0E884455 */
pS3 = -4.00555345006794114027e-02, /* 0xBFA48228, 0xB5688F3B */
pS4 =  7.91534994289814532176e-04, /* 0x3F49EFE0, 0x7501B288 */
pS5 =  3.47933107596021167570e-05, /* 0x3F023DE1, 0x0DFDF709 */
qS1 = -2.40339491173441421878e+00, /* 0xC0033A27, 0x1C8A2D4B */
qS2 =  2.02094576023350569471e+00, /* 0x40002AE5, 0x9C598AC8 */
qS3 = -6.88283971605453293030e-01, /* 0xBFE6066C, 0x1B8D0159 */
qS4 =  7.70381505559019352791e-02; /* 0x3FB3B8C5, 0xB12E9282 */

static double __ieee754_asin(double x)
{
    double t, w, p, q, c, r, s;
    int hx, ix;
    hx = __HI(x);
    ix = hx&0x7fffffff;
    if(ix>= 0x3ff00000) {		/* |x|>= 1 */
        if(((ix-0x3ff00000)|__LO(x))==0)
                /* asin(1)=+-pi/2 with inexact */
            return x*pio2_hi+x*pio2_lo;	
        return (x-x)/(x-x);		/* asin(|x|>1) is NaN */   
    } else if (ix<0x3fe00000) {	/* |x|<0.5 */
        if(ix<0x3e400000) {		/* if |x| < 2**-27 */
            if(huge+x>one) return x;/* return x with inexact if x!=0*/
        } else 
            t = x*x;
            p = t*(pS0+t*(pS1+t*(pS2+t*(pS3+t*(pS4+t*pS5)))));
            q = one+t*(qS1+t*(qS2+t*(qS3+t*qS4)));
            w = p/q;
            return x+x*w;
    }
    /* 1> |x|>= 0.5 */
    w = one-fabs(x);
    t = w*0.5;
    p = t*(pS0+t*(pS1+t*(pS2+t*(pS3+t*(pS4+t*pS5)))));
    q = one+t*(qS1+t*(qS2+t*(qS3+t*qS4)));
    s = sqrt(t);
    if(ix>=0x3FEF3333) { 	/* if |x| > 0.975 */
        w = p/q;
        t = pio2_hi-(2.0*(s+s*w)-pio2_lo);
    } else {
        w  = s;
        __LO(w) = 0;
        c  = (t-w*w)/(s+w);
        r  = p/q;
        p  = 2.0*s*r-(pio2_lo-2.0*c);
        q  = pio4_hi-2.0*w;
        t  = pio4_hi-(p-q);
    }    
    if(hx>0) return t; else return -t;    
}

/****** ma.lib/asin *********************************************************
* 
*   NAME	
* 	asin -- Return arc sine of x. (V1.0)
*
*   SYNOPSIS
*	double result = asin(double x);
*	  D0		   D0
*	double asin(double x);
*
*   FUNCTION
*	Compute the arc sine of x. The arc sine is the inverse of the sine
*	function, returning the angle whose sine is x. This implementation
*	uses high-precision algorithms from fdlibm for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Must be in the range [-1, 1] for valid result.
*	
*   RESULT
*	result - Arc sine of x in radians, in the range [-π/2, π/2]. Returns
*	        NaN if |x| > 1, returns x if x is ±0, returns NaN if x is NaN.
* 
*   EXAMPLE
*	double x = 0.5;
*	double angle = asin(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Sets errno to EDOM for |x| > 1.
* 
*   SEE ALSO
*	acos(), atan(), sin(), math.h
* 
******************************************************************************/

double asin(double x)
{
    double result = __ieee754_asin(x);
    
    /* Set errno for domain error (|x| > 1) */
    if (x < -1.0 || x > 1.0) {
        errno = EDOM;
    }
    
    return result;
}
