/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * modf(double x, double *iptr) 
 * return fraction part of x, and return x's integral part in *iptr.
 * Simple implementation using floor().
 */

#include <math.h>
#include "include/internal/m99_math.h"

double modf(double x, double *iptr)
{
    double intpart;
    
    /* Handle special cases */
    if (x != x) {  /* NaN */
        *iptr = x;
        return x;
    }
    
    if (x == 0.0) {
        *iptr = x;
        return x;
    }
    
    /* Use floor to get integer part */
    if (x >= 0.0) {
        intpart = floor(x);
    } else {
        intpart = -floor(-x);
    }
    
    *iptr = intpart;
    return x - intpart;
}