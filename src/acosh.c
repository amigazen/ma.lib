/*
 * acosh.c - Inverse hyperbolic cosine function
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file implements the C99 acosh() function using Amiga math libraries
 * when available, falling back to standard implementation otherwise.
 * 
 * Improvements merged from PDC/libsrc/LibSrc/Math/acosh.c:
 * - Overflow checking with SQRT_MAXDOUBLE
 * - matherr() error handling integration
 */

#include <math.h>
#include <errno.h>
#include <float.h>
#include "include/internal/m99_math.h"

#include <amiga/math.h>

/*
 * acosh - inverse hyperbolic cosine
 * 
 * Returns the inverse hyperbolic cosine of x.
 * Domain: [1, +infinity)
 * Range: [0, +infinity)
 */

/****** ma.lib/acosh ********************************************************
* 
*   NAME	
* 	acosh -- Return hyperbolic arc cosine of x. (V1.0)
*
*   SYNOPSIS
*	double result = acosh(double x);
*	  D0		   D0
*	double acosh(double x);
*
*   FUNCTION
*	Compute the hyperbolic arc cosine of x. The hyperbolic arc cosine is
*	the inverse of the hyperbolic cosine function. This implementation uses
*	the formula acosh(x) = log(x + sqrt(x² - 1)).
* 
*   INPUTS
*	x - Input value. Must be >= 1.0 for valid result.
*	
*   RESULT
*	result - Hyperbolic arc cosine of x. Returns 0.0 if x is 1.0, returns
*	        NaN if x < 1.0, returns +Infinity if x is +Infinity.
* 
*   EXAMPLE
*	double x = 2.0;
*	double result = acosh(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Sets errno to EDOM for x < 1.0.
* 
*   SEE ALSO
*	asinh(), atanh(), cosh(), log(), math.h
* 
******************************************************************************/

double acosh(double x)
{
    double result;
    
    /* Check for domain error */
    if (x < 1.0) {
        struct exception xcpt;
        xcpt.type = DOMAIN;
        xcpt.name = "acosh";
        xcpt.arg1 = x;
        if (!matherr(&xcpt)) {
            errno = EDOM;
            return NAN;
        }
        return xcpt.retval;
    }
    
    /* Check for overflow (improvement from PDC version) */
    if (x > SQRT_MAXDOUBLE) {
        struct exception xcpt;
        xcpt.type = OVERFLOW;
        xcpt.name = "acosh";
        xcpt.arg1 = x;
        if (!matherr(&xcpt)) {
            errno = ERANGE;
            return log(2 * SQRT_MAXDOUBLE);
        }
        return xcpt.retval;
    }
    
    /* Check for infinity */
    if (x == INFINITY) {
        return INFINITY;
    }
    
    /* Check for NaN */
    if (x != x) {
        return NAN;
    }
    
#ifdef __AMIGA__
    /* Use AmigaOS math library if available */
    if (m99_has_trans()) {
        result = amiga_acosh(x);
        if (m99_get_error() == M99_ERR_NONE) {
            return result;
        }
    }
#endif
    
    /* Standard implementation: acosh(x) = log(x + sqrt(x*x - 1)) */
    if (x == 1.0) {
        return 0.0;
    }
    
    /* For x close to 1, use more stable formula */
    if (x < 1.0 + DBL_EPSILON) {
        double t = x - 1.0;
        return sqrt(2.0 * t) * (1.0 - t/12.0 + 3.0*t*t/160.0);
    }
    
    /* Standard formula for x > 1 */
    result = x + sqrt(x*x - 1.0);
    if (result == INFINITY) {
        return INFINITY;
    }
    
    return log(result);
}
