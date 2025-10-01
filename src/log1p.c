/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * log1p(x) = log(1+x)
 * 
 * The log1p function is designed to avoid the significant loss of precision
 * that arises from direct evaluation when x is small.
 * 
 * Based on Python's _math.c implementation with modifications for C89/SAS/C
 */

#include <math.h>
#include <float.h>
#include "include/internal/m99_math.h"

/*
 * log1p(x) = log(1+x).  The log1p function is designed to avoid the
 * significant loss of precision that arises from direct evaluation when x is
 * small.
 * 
 * For x small, we use the following approach.  Let y be the nearest float
 * to 1+x, then
 *
 *     1+x = y * (1 - (y-1-x)/y)
 *
 * so log(1+x) = log(y) + log(1-(y-1-x)/y).  Since (y-1-x)/y is tiny, the
 * second term is well approximated by (y-1-x)/y.  If abs(x) >=
 * DBL_EPSILON/2 or the rounding-mode is some form of round-to-nearest
 * then y-1-x will be exactly representable, and is computed exactly by
 * (y-1)-x.
 *
 * If abs(x) < DBL_EPSILON/2 and the rounding mode is not known to be
 * round-to-nearest then this method is slightly dangerous: 1+x could be
 * rounded up to 1+DBL_EPSILON instead of down to 1, and in that case
 * y-1-x will not be exactly representable any more and the result can be
 * off by many ulps.  But this is easily fixed: for a floating-point
 * number |x| < DBL_EPSILON/2., the closest floating-point number to
 * log(1+x) is exactly x.
 */

/****** ma.lib/log1p **********************************************************
* 
*   NAME	
* 	log1p -- Return log(1 + x). (V1.0)
*
*   SYNOPSIS
*	double result = log1p(double x);
*	  D0		   D0
*	double log1p(double x);
*
*   FUNCTION
*	Compute log(1 + x). This function is designed to avoid the significant
*	loss of precision that arises from direct evaluation when x is small.
*	This implementation uses high-precision algorithms for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Must be > -1 for valid result.
*	
*   RESULT
*	result - log(1 + x). Returns -Infinity if x is -1, returns x if x is
*	        ±0, returns NaN if x < -1, returns +Infinity if x is +Infinity.
* 
*   EXAMPLE
*	double x = 0.001;
*	double result = log1p(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	More accurate than log(1 + x) for small x values.
* 
*   SEE ALSO
*	log(), expm1(), math.h
* 
******************************************************************************/

double log1p(double x)
{
    double y;
    
    /* Handle special case of zero input directly */
    if (x == 0.0) {
        return x;
    }
    
    if (fabs(x) < DBL_EPSILON/2.) {
        return x;
    }
    else if (-0.5 <= x && x <= 1.) {
        /* WARNING: it's possible than an overeager compiler
           will incorrectly optimize the following two lines
           to the equivalent of "return log(1.+x)". If this
           happens, then results from log1p will be inaccurate
           for small x. */
        y = 1.+x;
        return log(y)-((y-1.)-x)/y;
    }
    else {
        /* NaNs and infinities should end up here */
        return log(1.+x);
    }
}
