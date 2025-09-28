/*
 * atanhf.c - Inverse hyperbolic tangent function (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file implements the C99 atanhf() function.
 * Simple implementation using the standard formula:
 * atanh(x) = 0.5 * log((1+x)/(1-x))
 */

#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "include/internal/m99_math.h"

/*
 * atanhf - double precision hyperbolic arc tangent (float)
 * 
 * Returns float precision hyperbolic arc tangent of float
 * floating point number.
 * 
 * The domain of the ATANH function is (-1, 1).
 * 
 * Computes atanh(x) from:
 * 1. If |x| >= 1.0 then report domain error and return zero.
 * 2. atanh(x) = 0.5 * log((1+x)/(1-x))
 */
float atanhf(float x)
{
    float result;
    
    /* Check for domain error */
    if (x <= -1.0f || x >= 1.0f) {
        errno = EDOM;
        if (matherr) {
            struct exception exc;
            exc.type = DOMAIN;
            exc.name = "atanhf";
            exc.arg1 = x;
            exc.arg2 = 0.0;
            exc.retval = 0.0;
            if (matherr(&exc)) {
                return (float)exc.retval;
            }
        }
        return 0.0f;
    }
    
    /* Handle special case x = 0 */
    if (x == 0.0f) {
        return 0.0f;
    }
    
    /* Standard formula: atanh(x) = 0.5 * log((1+x)/(1-x)) */
    result = 0.5f * (float)log((1.0 + (double)x) / (1.0 - (double)x));
    
    return result;
}
