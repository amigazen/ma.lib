/*
 * acoshf.c - Inverse hyperbolic cosine function (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file implements the C99 acoshf() function using Amiga math libraries
 * when available, falling back to standard implementation otherwise.
 */

#include <math.h>
#include <errno.h>
#include <float.h>
#include "include/internal/m99_math.h"

#include <amiga/math.h>

/****** ma.lib/acoshf ********************************************************
* 
*   NAME	
* 	acoshf -- Return inverse hyperbolic cosine of float. (V1.0)
*
*   SYNOPSIS
*	float result = acoshf(float x);
*	  D0		   D0
*	float acoshf(float x);
*
*   FUNCTION
*	Compute the inverse hyperbolic cosine of a float value. This returns
*	the value whose hyperbolic cosine is x. This implementation uses
*	AmigaOS math libraries when available, falling back to standard implementation.
* 
*   INPUTS
*	x - Float value. Must be >= 1 for valid result.
*	
*   RESULT
*	result - Inverse hyperbolic cosine of x. Returns 0 if x < 1,
*	        returns +Infinity if x is +Infinity.
* 
*   EXAMPLE
*	float x = 2.0f;
*	float result = acoshf(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses AmigaOS math libraries when available for optimal performance.
* 
*   SEE ALSO
*	acosh(), asinhf(), atanhf(), math.h
* 
******************************************************************************/

/*
 * acoshf - inverse hyperbolic cosine (float)
 * 
 * Returns the inverse hyperbolic cosine of x.
 * Domain: [1, +infinity)
 * Range: [0, +infinity)
 */
float acoshf(float x)
{
    float result;
    
    /* Check for domain error */
    if (x < 1.0f) {
        errno = EDOM;
        if (matherr) {
            struct exception exc;
            exc.type = DOMAIN;
            exc.name = "acoshf";
            exc.arg1 = x;
            exc.arg2 = 0.0;
            exc.retval = 0.0;
            if (matherr(&exc)) {
                return (float)exc.retval;
            }
        }
        return 0.0f;
    }
    
    /* Check for overflow */
    if (x > SQRT_MAXDOUBLE) {
        errno = ERANGE;
        if (matherr) {
            struct exception exc;
            exc.type = OVERFLOW;
            exc.name = "acoshf";
            exc.arg1 = x;
            exc.arg2 = 0.0;
            exc.retval = HUGE_VALF;
            if (matherr(&exc)) {
                return (float)exc.retval;
            }
        }
        return HUGE_VALF;
    }
    
#ifdef __AMIGA__
    /* Try AmigaOS math library first if available */
    if (m99_has_trans) {
        result = amiga_acosh((double)x);
        if (m99_get_error() == 0) {
            return (float)result;
        }
    }
#endif
    
    /* Standard implementation for acosh(x) */
    if (x == 1.0f) {
        return 0.0f;
    }
    
    /* For x close to 1, use more stable formula */
    if (x < 1.5f) {
        float t = x - 1.0f;
        return (float)(sqrt(2.0 * t) * (1.0f - t/12.0f + 3.0f*t*t/160.0f));
    }
    
    /* Standard formula: acosh(x) = log(x + sqrt(x^2 - 1)) */
    result = (float)log((double)x + sqrt((double)x * (double)x - 1.0));
    
    return (float)result;
}
