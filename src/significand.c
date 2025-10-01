/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_significand.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double significand(double x)
 * significand(x) computes just
 * 	scalb(x, (double) -ilogb(x)),
 * for exercising the fraction-part(F) IEEE 754-1985 test vector.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/significand **************************************************
* 
*   NAME	
* 	significand -- Return significand of x. (V1.0)
*
*   SYNOPSIS
*	double result = significand(double x);
*	  D0		   D0
*	double significand(double x);
*
*   FUNCTION
*	Compute the significand of x. The significand is the fractional part
*	of the floating-point number, normalized to the range [1, 2). This
*	implementation uses scalb(x, -ilogb(x)) for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	
*   RESULT
*	result - Significand of x. Returns x if x is ±0, returns NaN if
*	        x is NaN, returns ±Infinity if x is ±Infinity.
* 
*   EXAMPLE
*	double x = 3.14159;
*	double result = significand(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to scalb(x, -ilogb(x)).
* 
*   SEE ALSO
*	scalb(), ilogb(), math.h
* 
******************************************************************************/

double significand(double x)
{
    return scalb(x, (double) -ilogb(x));
}
