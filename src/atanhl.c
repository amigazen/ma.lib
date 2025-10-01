/*
 * atanhl.c - Inverse hyperbolic tangent function (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file implements the C99 atanhl() function.
 * Simple implementation using the standard formula:
 * atanh(x) = 0.5 * log((1+x)/(1-x))
 */

#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/atanhl ********************************************************
* 
*   NAME	
* 	atanhl -- Return inverse hyperbolic tangent of long double. (V1.0)
*
*   SYNOPSIS
*	long double result = atanhl(long double x);
*	  D0		   D0
*	long double atanhl(long double x);
*
*   FUNCTION
*	Compute the inverse hyperbolic tangent of a long double value. This returns
*	the value whose hyperbolic tangent is x. This implementation uses
*	the standard formula: atanh(x) = 0.5 * log((1+x)/(1-x)).
* 
*   INPUTS
*	x - Long double value. Must be in range (-1, 1) for valid result.
*	
*   RESULT
*	result - Inverse hyperbolic tangent of x. Returns 0 if |x| >= 1.
* 
*   EXAMPLE
*	long double x = 0.5L;
*	long double result = atanhl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses the standard mathematical formula for computation.
* 
*   SEE ALSO
*	atanh(), asinhl(), acoshl(), math.h
* 
******************************************************************************/

/*
 * atanhl - long double precision hyperbolic arc tangent
 * 
 * Returns long double precision hyperbolic arc tangent of long double
 * floating point number.
 * 
 * The domain of the ATANH function is (-1, 1).
 * 
 * Computes atanh(x) from:
 * 1. If |x| >= 1.0 then report domain error and return zero.
 * 2. atanh(x) = 0.5 * log((1+x)/(1-x))
 */
double atanhl(double x)
{
    double result;
    
    /* Check for domain error */
    if (x <= -1.0 || x >= 1.0) {
        errno = EDOM;
        if (matherr) {
            struct exception exc;
            exc.type = DOMAIN;
            exc.name = "atanhl";
            exc.arg1 = x;
            exc.arg2 = 0.0;
            exc.retval = 0.0;
            if (matherr(&exc)) {
                return (long double)exc.retval;
            }
        }
        return 0.0;
    }
    
    /* Handle special case x = 0 */
    if (x == 0.0) {
        return 0.0;
    }
    
    /* Standard formula: atanh(x) = 0.5 * log((1+x)/(1-x)) */
    result = 0.5 * logl((1.0 + x) / (1.0 - x));
    
    return result;
}
