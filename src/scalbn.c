/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_scalbn.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * scalbn (double x, int n)
 * scalbn(x,n) returns x* 2**n  computed by  exponent  
 * manipulation rather than by actually performing an 
 * exponentiation or a multiplication.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

static const double
two54   =  1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
twom54  =  5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
huge   = 1.0e+300,
tiny   = 1.0e-300;

/****** ma.lib/scalbn ***************************************************
* 
*   NAME	
* 	scalbn -- Scale x by 2^n. (V1.0)
*
*   SYNOPSIS
*	double result = scalbn(double x, int n);
*	  D0		   D0
*	double scalbn(double x, int n);
*
*   FUNCTION
*	Scale x by 2^n. This is equivalent to x * 2^n but computed by
*	exponent manipulation rather than by actually performing a
*	multiplication. This is more efficient and accurate.
* 
*   INPUTS
*	x - Value to scale.
*	n - Power of 2 to scale by. Range is approximately [-1024, 1024].
*	
*   RESULT
*	result - x * 2^n. Returns ±Infinity for overflow, ±0.0 for underflow,
*	        NaN if x is NaN, ±Infinity if x is ±Infinity.
* 
*   EXAMPLE
*	double x = 3.0;
*	int n = 2;
*	double scaled = scalbn(x, n); 
*
*   NOTES
*	This function is C99 compliant and provides IEEE 754 accuracy.
*	Uses bit manipulation for optimal performance.
* 
*   SEE ALSO
*	scalbln(), ldexp(), frexp(), math.h
* 
******************************************************************************/

double scalbn(double x, int n)
{
    int  k, hx, lx;
    hx = __HI(x);
    lx = __LO(x);
    k = (hx&0x7ff00000)>>20;		/* extract exponent */
    if (k==0) {				/* 0 or subnormal x */
        if ((lx|(hx&0x7fffffff))==0) return x; /* +-0 */
        x *= two54; 
        hx = __HI(x);
        k = ((hx&0x7ff00000)>>20) - 54; 
        if (n< -50000) return tiny*x; 	/*underflow*/
    }
    if (k==0x7ff) return x+x;		/* NaN or Inf */
    k = k+n; 
    if (k >  0x7fe) return huge*copysign(huge,x); /* overflow  */
    if (k > 0) 				/* normal result */
        {__HI(x) = (hx&0x800fffff)|(k<<20); return x;}
    if (k <= -54)
        if (n > 50000) 	/* in case integer overflow in n+k */
            return huge*copysign(huge,x);	/*overflow*/
        else return tiny*copysign(tiny,x); 	/*underflow*/
    k += 54;				/* subnormal result */
    __HI(x) = (hx&0x800fffff)|(k<<20);
    return x*twom54;
}

