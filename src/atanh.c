/*
 * m99 Math Library - atanh function
 * 
 * C99/POSIX atanh function for m99.lib
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
