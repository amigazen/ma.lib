/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * remainder(x,p)
 * Return: returns x REM p = x - [x/p]*p as if in infinite 
 * precise arithmetic, where [x/p] is the (infinite bit) 
 * integer nearest x/p (in half way case choose the even one).
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/remainder ************************************************
* 
*   NAME	
* 	remainder -- Return IEEE remainder of x/y. (V1.0)
*
*   SYNOPSIS
*	double result = remainder(double x, double y);
*	  D0		   D0
*	double remainder(double x, double y);
*
*   FUNCTION
*	Compute the IEEE remainder of x/y. The remainder is x - n*y where n
*	is the integer nearest to x/y. In case of a tie, n is chosen to be
*	even. The result is always in the range [-|y|/2, |y|/2].
* 
*   INPUTS
*	x - Dividend value.
*	y - Divisor value. Must be non-zero for valid result.
*	
*   RESULT
*	result - IEEE remainder of x/y. Returns NaN if y is 0 or if either
*	        argument is NaN, returns x if y is ±Infinity.
* 
*   EXAMPLE
*	double x = 5.0, y = 2.0;
*	double rem = remainder(x, y);
*
*   NOTES
*	This function is C99 compliant and provides IEEE 754 accuracy.
*	Uses round-to-even for tie cases as required by IEEE 754.
* 
*   SEE ALSO
*	fmod(), remquo(), rint(), math.h
* 
******************************************************************************/

double remainder(double x, double y)
{
    double n, r;
    
    /* Handle special cases */
    if (y == 0.0) {
        return NAN;  /* remainder(x,0) is NaN */
    }
    
    if (x != x || y != y) {  /* NaN */
        return NAN;
    }
    
    /* Calculate n = round(x/y) using rint for proper round-to-even */
    n = rint(x / y);
    
    /* Calculate r = x - n*y */
    r = x - n * y;
    
    /* Ensure result is in range [-|y|/2, |y|/2] */
    if (r > fabs(y) / 2.0) {
        r -= fabs(y);
    } else if (r <= -fabs(y) / 2.0) {
        r += fabs(y);
    }
    
    return r;
}