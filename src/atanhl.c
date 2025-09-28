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
