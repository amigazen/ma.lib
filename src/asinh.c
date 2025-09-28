/*
 * ma.lib Math Library - asinh function
 * 
 * C99/POSIX asinh function for ma.lib
 * Copyright Abandoned, 1987, Fred Fish - Public Domain 
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "include/internal/m99_math.h"

/*
 * asinh - double precision hyperbolic arc sine
 * 
 * Returns double precision hyperbolic arc sine of double precision
 * floating point number.
 * 
 * The domain of the ASINH function is the entire real axis
 * however the evaluation of x squared may cause overflow
 * for large magnitudes.
 * 
 * Computes asinh(x) from:
 * 1. Let xmax = sqrt(MAXDOUBLE - 1)
 * 2. If x < -xmax or xmax < x then let x = xmax and flag overflow.
 * 3. asinh(x) = log [x+sqrt(x**2 + 1)]
 */
double asinh(double x)
{
    struct exception xcpt;
    
    if (x < -SQRT_MAXDOUBLE || x > SQRT_MAXDOUBLE) {
        xcpt.type = OVERFLOW;
        xcpt.name = "asinh";
        xcpt.arg1 = x;
        if (!matherr(&xcpt)) {
            fprintf(stderr, "asinh: OVERFLOW error\n");
            errno = ERANGE;
            xcpt.retval = log(2 * SQRT_MAXDOUBLE);
        }
        return xcpt.retval;
    } else {
        return log(x + sqrt(x * x + 1.0));
    }
}
