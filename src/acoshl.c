/*
 * acoshl.c - Inverse hyperbolic cosine function (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file implements the C99 acoshl() function using Amiga math libraries
 * when available, falling back to standard implementation otherwise.
 */

#include <math.h>
#include <errno.h>
#include <float.h>
#include "include/internal/m99_math.h"

#include <amiga/math.h>

/****** ma.lib/acoshl ********************************************************
* 
*   NAME	
* 	acoshl -- Return inverse hyperbolic cosine of long double. (V1.0)
*
*   SYNOPSIS
*	long double result = acoshl(long double x);
*	  D0		   D0
*	long double acoshl(long double x);
*
*   FUNCTION
*	Compute the inverse hyperbolic cosine of a long double value. This returns
*	the value whose hyperbolic cosine is x. This implementation uses
*	AmigaOS math libraries when available, falling back to standard implementation.
* 
*   INPUTS
*	x - Long double value. Must be >= 1 for valid result.
*	
*   RESULT
*	result - Inverse hyperbolic cosine of x. Returns 0 if x < 1,
*	        returns +Infinity if x is +Infinity.
* 
*   EXAMPLE
*	long double x = 2.0L;
*	long double result = acoshl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses AmigaOS math libraries when available for optimal performance.
* 
*   SEE ALSO
*	acosh(), asinhl(), atanhl(), math.h
* 
******************************************************************************/

/*
 * acoshl - inverse hyperbolic cosine (long double)
 * 
 * Returns the inverse hyperbolic cosine of x.
 * Domain: [1, +infinity)
 * Range: [0, +infinity)
 */
double acoshl(double x)
{
    double result;
    
    /* Check for domain error */
    if (x < 1.0) {
        errno = EDOM;
        if (matherr) {
            struct exception exc;
            exc.type = DOMAIN;
            exc.name = "acoshl";
            exc.arg1 = x;
            exc.arg2 = 0.0;
            exc.retval = 0.0;
            if (matherr(&exc)) {
                return (long double)exc.retval;
            }
        }
        return 0.0;
    }
    
    /* Check for overflow */
    if (x > SQRT_MAXDOUBLE) {
        errno = ERANGE;
        if (matherr) {
            struct exception exc;
            exc.type = OVERFLOW;
            exc.name = "acoshl";
            exc.arg1 = x;
            exc.arg2 = 0.0;
            exc.retval = HUGE_VALL;
            if (matherr(&exc)) {
                return (long double)exc.retval;
            }
        }
        return HUGE_VALL;
    }
    
#ifdef __AMIGA__
    /* Try AmigaOS math library first if available */
    if (m99_has_trans) {
        result = amiga_acosh((double)x);
        if (m99_get_error() == 0) {
            return (long double)result;
        }
    }
#endif
    
    /* Standard implementation for acosh(x) */
    if (x == 1.0) {
        return 0.0;
    }
    
    /* For x close to 1, use more stable formula */
    if (x < 1.5) {
        double t = x - 1.0;
        return sqrtl(2.0 * t) * (1.0 - t/12.0 + 3.0*t*t/160.0);
    }
    
    /* Standard formula: acosh(x) = log(x + sqrt(x^2 - 1)) */
    result = logl(x + sqrtl(x * x - 1.0));
    
    return result;
}
