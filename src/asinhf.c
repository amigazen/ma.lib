/*
 * asinhf.c - Inverse hyperbolic sine function (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file implements the C99 asinhf() function.
 * Originally adapted from sasc/PDC/libsrc/LibSrc/Math/asinh.c
 * Copyright Abandoned, 1987, Fred Fish - Public Domain
 */

#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/asinhf ********************************************************
* 
*   NAME	
* 	asinhf -- Return inverse hyperbolic sine of float. (V1.0)
*
*   SYNOPSIS
*	float result = asinhf(float x);
*	  D0		   D0
*	float asinhf(float x);
*
*   FUNCTION
*	Compute the inverse hyperbolic sine of a float value. This returns
*	the value whose hyperbolic sine is x. This implementation uses
*	the standard formula: asinh(x) = log(x + sqrt(x^2 + 1)).
* 
*   INPUTS
*	x - Float value. Range is [-∞, +∞].
*	
*   RESULT
*	result - Inverse hyperbolic sine of x. Returns ±Infinity for large |x|.
* 
*   EXAMPLE
*	float x = 1.0f;
*	float result = asinhf(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Originally adapted from PDC libsrc (Fred Fish - Public Domain).
* 
*   SEE ALSO
*	asinh(), acoshf(), atanhf(), math.h
* 
******************************************************************************/

/*
 * asinhf - double precision hyperbolic arc sine (float)
 * 
 * Returns float precision hyperbolic arc sine of float
 * floating point number.
 * 
 * The domain of the ASINH function is the entire real axis
 * however the evaluation of x squared may cause overflow
 * for large magnitudes.
 * 
 * Computes asinh(x) from:
 * 1. Let xmax = sqrt(MAXFLOAT - 1)
 * 2. If x < -xmax or xmax < x then let x = xmax and flag overflow.
 * 3. asinh(x) = log [x+sqrt(x**2 + 1)]
 */
float asinhf(float x)
{
    float xmax, result;
    
    /* Check for overflow */
    xmax = (float)sqrt(FLT_MAX - 1.0);
    if (x < -xmax || x > xmax) {
        errno = ERANGE;
        if (matherr) {
            struct exception exc;
            exc.type = OVERFLOW;
            exc.name = "asinhf";
            exc.arg1 = x;
            exc.arg2 = 0.0;
            if (x < 0) {
                exc.retval = -HUGE_VALF;
            } else {
                exc.retval = HUGE_VALF;
            }
            if (matherr(&exc)) {
                return (float)exc.retval;
            }
        }
        if (x < 0) {
            return -HUGE_VALF;
        } else {
            return HUGE_VALF;
        }
    }
    
    /* Standard formula: asinh(x) = log(x + sqrt(x^2 + 1)) */
    result = (float)log((double)x + sqrt((double)x * (double)x + 1.0));
    
    return result;
}
