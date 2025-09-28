/*
 * cbrt.c - Cube root function
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file implements the C99 cbrt() function using Amiga math libraries
 * when available, falling back to standard implementation otherwise.
 */

#include <math.h>
#include <errno.h>
#include <float.h>
#include "include/internal/m99_math.h"

#include <amiga/math.h>

/*
 * cbrt - cube root
 * 
 * Returns the cube root of x.
 * Domain: (-infinity, +infinity)
 * Range: (-infinity, +infinity)
 */
double cbrt(double x)
{
    double result;
    
    /* Check for special values */
    if (x == 0.0) {
        return 0.0;
    }
    
    if (x == INFINITY) {
        return INFINITY;
    }
    
    if (x == -INFINITY) {
        return -INFINITY;
    }
    
    if (x != x) {  /* NaN */
        return NAN;
    }
    
#ifdef __AMIGA__
    /* Use AmigaOS math library if available */
    if (m99_has_trans()) {
        /* cbrt(x) = pow(x, 1.0/3.0) */
        result = amiga_ieee_pow(x, 1.0/3.0);
        if (m99_get_error() == M99_ERR_NONE) {
            return result;
        }
    }
#endif
    
    /* Standard implementation using pow */
    result = pow(x, 1.0/3.0);
    
    /* Check for overflow */
    if (result == INFINITY) {
        errno = ERANGE;
    }
    
    return result;
}
