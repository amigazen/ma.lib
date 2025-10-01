/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_frexp.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double frexp(double x, int *eptr)
 * for non-zero x 
 *	x = frexp(arg,&exp);
 * return a double fp quantity x such that 0.5 <= |x| <1.0
 * and the corresponding binary exponent "exp". That is
 *	arg = x*2^exp.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

static const double
two54 =  1.80143985094819840000e+16; /* 0x43500000, 0x00000000 */

/****** ma.lib/frexp ********************************************************
* 
*   NAME	
* 	frexp -- Return significand and exponent of x. (V1.0)
*
*   SYNOPSIS
*	double result = frexp(double x, int *eptr);
*	  D0		   D0
*	double frexp(double x, int *eptr);
*
*   FUNCTION
*	Break x into a normalized fraction and an integral power of 2. The
*	result is x = result * 2^eptr, where result is in the range [0.5, 1.0)
*	or 0, and eptr is the exponent. This implementation uses high-precision
*	algorithms from fdlibm for maximum accuracy.
* 
*   INPUTS
*	x - Input value.
*	eptr - Pointer to integer to store exponent.
*	
*   RESULT
*	result - Normalized fraction in range [0.5, 1.0) or 0. Returns 0 if
*	        x is 0, returns x if x is ±Infinity or NaN.
* 
*   EXAMPLE
*	double x = 3.14159;
*	int exp;
*	double result = frexp(x, &exp);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	The exponent is stored in the integer pointed to by eptr.
* 
*   SEE ALSO
*	ldexp(), scalbn(), scalb(), math.h
* 
******************************************************************************/

double frexp(double x, int *eptr)
{
    int  hx, ix, lx;
    hx = __HI(x);
    ix = 0x7fffffff&hx;
    lx = __LO(x);
    *eptr = 0;
    if(ix>=0x7ff00000||((ix|lx)==0)) return x;	/* 0,inf,nan */
    if (ix<0x00100000) {		/* subnormal */
        x *= two54;
        hx = __HI(x);
        ix = hx&0x7fffffff;
        *eptr = -54;
    }
    *eptr += (ix>>20)-1022;
    hx = (hx&0x800fffff)|0x3fe00000;
    __HI(x) = hx;
    return x;
}