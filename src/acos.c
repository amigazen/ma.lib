/*
 * m99 Math Library - acos function
 * 
 * C99/POSIX acos function for m99.lib
 * Copyright Abandoned, 1987, Fred Fish - Public Domain
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef _WITH_SCLIB

#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "include/internal/m99_math.h"

/*
 * acos - double precision arc cosine
 * 
 * Returns double precision arc cosine of double precision
 * floating point argument.
 * 
 * Computes arccosine(x) from:
 * 1. If x < -1.0 or x > +1.0 then call matherr and return 0.0 by default.
 * 2. If x = 0.0 then acos(x) = PI/2.
 * 3. If x = 1.0 then acos(x) = 0.0
 * 4. If x = -1.0 then acos(x) = PI.
 * 5. If 0.0 < x < 1.0 then acos(x) = atan(sqrt[1-(x**2)] / x)
 * 6. If -1.0 < x < 0.0 then acos(x) = atan(sqrt[1-(x**2)] / x) + PI
 */
double acos(double x)
{
    double y;
    struct exception xcpt;
    
    if (x > 1.0 || x < -1.0) {
        xcpt.type = DOMAIN;
        xcpt.name = "acos";
        xcpt.arg1 = x;
        if (!matherr(&xcpt)) {
            fprintf(stderr, "acos: DOMAIN error\n");
            errno = EDOM;
            xcpt.retval = 0.0;
        }
        return xcpt.retval;
    } else if (x == 0.0) {
        return HALFPI;
    } else if (x == 1.0) {
        return 0.0;
    } else if (x == -1.0) {
        return PI;
    } else {
        y = atan(sqrt(1.0 - (x * x)) / x);
        if (x > 0.0) {
            return y;
        } else {
            return y + PI;
        }
    }
}

#endif /* _WITH_SCLIB */
