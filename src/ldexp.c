/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_ldexp.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double ldexp(double value, int exp)
 * Returns value * 2^exp
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/ldexp ********************************************************
* 
*   NAME	
* 	ldexp -- Return value * 2^exp. (V1.0)
*
*   SYNOPSIS
*	double result = ldexp(double value, int exp);
*	  D0		   D0
*	double ldexp(double value, int exp);
*
*   FUNCTION
*	Compute value * 2^exp. This scales value by a power of 2. This
*	implementation uses high-precision algorithms from fdlibm for maximum
*	accuracy.
* 
*   INPUTS
*	value - Input value.
*	exp - Exponent value.
*	
*   RESULT
*	result - value * 2^exp. Returns NaN if value is NaN, returns ±Infinity
*	        for large results, returns ±0 for small results.
* 
*   EXAMPLE
*	double value = 3.0;
*	int exp = 2;
*	double result = ldexp(value, exp);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to scalbn(value, exp).
* 
*   SEE ALSO
*	scalbn(), scalb(), frexp(), math.h
* 
******************************************************************************/

double ldexp(double value, int exp)
{
    if(!finite(value)||value==0.0) return value;
    value = scalbn(value,exp);
    if(!finite(value)||value==0.0) {
        /* Set errno to ERANGE if available */
        /* errno = ERANGE; */
    }
    return value;
}