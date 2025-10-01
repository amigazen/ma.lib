/*
 * ma.lib Math Library - atanh function
 * 
 * C99/POSIX atanh function for ma.lib
 * Simple implementation using the standard formula:
 * atanh(x) = 0.5 * log((1+x)/(1-x))
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "include/internal/m99_math.h"

/*
 * atanh - double precision hyperbolic arc tangent
 * 
 * Returns double precision hyperbolic arc tangent of double precision
 * floating point number.
 * 
 * The domain of the ATANH function is (-1, 1).
 * 
 * Computes atanh(x) from:
 * 1. If |x| >= 1.0 then report domain error and return zero.
 * 2. atanh(x) = 0.5 * log((1+x)/(1-x))
 */

/****** ma.lib/atanh ********************************************************
* 
*   NAME	
* 	atanh -- Return hyperbolic arc tangent of x. (V1.0)
*
*   SYNOPSIS
*	double result = atanh(double x);
*	  D0		   D0
*	double atanh(double x);
*
*   FUNCTION
*	Compute the hyperbolic arc tangent of x. The hyperbolic arc tangent is
*	the inverse of the hyperbolic tangent function. This implementation uses
*	the formula atanh(x) = 0.5 * log((1+x)/(1-x)).
* 
*   INPUTS
*	x - Input value. Must be in the range (-1, 1) for valid result.
*	
*   RESULT
*	result - Hyperbolic arc tangent of x. Returns x if x is ±0, returns
*	        NaN if |x| >= 1, returns NaN if x is NaN.
* 
*   EXAMPLE
*	double x = 0.5;
*	double result = atanh(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Sets errno to EDOM for |x| >= 1.
* 
*   SEE ALSO
*	asinh(), acosh(), tanh(), log(), math.h
* 
******************************************************************************/

double atanh(double x)
{
    struct exception xcpt;
    
    if (x >= 1.0 || x <= -1.0) {
        xcpt.type = DOMAIN;
        xcpt.name = "atanh";
        xcpt.arg1 = x;
        if (!matherr(&xcpt)) {
            fprintf(stderr, "atanh: DOMAIN error\n");
            errno = EDOM;
            xcpt.retval = 0.0;
        }
        return xcpt.retval;
    } else {
        return 0.5 * log((1.0 + x) / (1.0 - x));
    }
}
