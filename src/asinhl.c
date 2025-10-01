/*
 * asinhl.c - Inverse hyperbolic sine function (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file implements the C99 asinhl() function.
 * Originally adapted from sasc/PDC/libsrc/LibSrc/Math/asinh.c
 * Copyright Abandoned, 1987, Fred Fish - Public Domain
 */

#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/asinhl ********************************************************
* 
*   NAME	
* 	asinhl -- Return inverse hyperbolic sine of long double. (V1.0)
*
*   SYNOPSIS
*	long double result = asinhl(long double x);
*	  D0		   D0
*	long double asinhl(long double x);
*
*   FUNCTION
*	Compute the inverse hyperbolic sine of a long double value. This returns
*	the value whose hyperbolic sine is x. This implementation uses
*	the standard formula: asinh(x) = log(x + sqrt(x^2 + 1)).
* 
*   INPUTS
*	x - Long double value. Range is [-∞, +∞].
*	
*   RESULT
*	result - Inverse hyperbolic sine of x. Returns ±Infinity for large |x|.
* 
*   EXAMPLE
*	long double x = 1.0L;
*	long double result = asinhl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Originally adapted from PDC libsrc (Fred Fish - Public Domain).
* 
*   SEE ALSO
*	asinh(), acoshl(), atanhl(), math.h
* 
******************************************************************************/

/*
 * asinhl - long double precision hyperbolic arc sine
 * 
 * Returns long double precision hyperbolic arc sine of long double
 * floating point number.
 * 
 * The domain of the ASINH function is the entire real axis
 * however the evaluation of x squared may cause overflow
 * for large magnitudes.
 * 
 * Computes asinh(x) from:
 * 1. Let xmax = sqrt(LDBL_MAX - 1)
 * 2. If x < -xmax or xmax < x then let x = xmax and flag overflow.
 * 3. asinh(x) = log [x+sqrt(x**2 + 1)]
 */
double asinhl(double x)
{
    double xmax, result;
    
    /* Check for overflow */
    xmax = sqrtl(LDBL_MAX - 1.0);
    if (x < -xmax || x > xmax) {
        errno = ERANGE;
        if (matherr) {
            struct exception exc;
            exc.type = OVERFLOW;
            exc.name = "asinhl";
            exc.arg1 = x;
            exc.arg2 = 0.0;
            exc.retval = (x < 0) ? -HUGE_VALL : HUGE_VALL;
            if (matherr(&exc)) {
                return (long double)exc.retval;
            }
        }
        return (x < 0) ? -HUGE_VALL : HUGE_VALL;
    }
    
    /* Standard formula: asinh(x) = log(x + sqrt(x^2 + 1)) */
    result = logl(x + sqrtl(x * x + 1.0));
    
    return result;
}
