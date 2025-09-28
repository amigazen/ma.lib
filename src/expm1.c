/*
 * expm1.c - exp(x) - 1 function
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file implements the C99 expm1() function which provides
 * more accurate results than exp(x) - 1 for small values of x.
 */

#include <math.h>
#include <errno.h>
#include <float.h>
#include "include/internal/m99_math.h"

#include <amiga/math.h>

/*
 * expm1 - exp(x) - 1
 * 
 * Returns exp(x) - 1, computed in a way that is accurate even
 * for small values of x.
 * 
 * This function is useful when x is close to zero, as exp(x) - 1
 * can suffer from cancellation errors.
 */
double expm1(double x)
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
        return -1.0;
    }
    
    if (x != x) {  /* NaN */
        return NAN;
    }
    
#ifdef __AMIGA__
    /* Use AmigaOS math library if available */
    if (m99_has_trans()) {
        result = amiga_expm1(x);
        if (m99_get_error() == M99_ERR_NONE) {
            return result;
        }
    }
#endif
    
    /* For small x, use Taylor series to avoid cancellation */
    if (fabs(x) < 0.5) {
        double x2 = x * x;
        double x3 = x2 * x;
        double x4 = x3 * x;
        double x5 = x4 * x;
        
        /* Taylor series: x + x^2/2! + x^3/3! + x^4/4! + x^5/5! + ... */
        return x * (1.0 + x/2.0 + x2/6.0 + x3/24.0 + x4/120.0 + x5/720.0);
    }
    
    /* For larger x, use standard formula but check for overflow */
    if (x > 700.0) {
        errno = ERANGE;
        return INFINITY;
    }
    
    if (x < -700.0) {
        return -1.0;
    }
    
    result = exp(x) - 1.0;
    
    /* Check for overflow */
    if (result == INFINITY) {
        errno = ERANGE;
    }
    
    return result;
}
