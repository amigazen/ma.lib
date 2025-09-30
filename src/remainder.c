/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * remainder(x,p)
 * Return: returns x REM p = x - [x/p]*p as if in infinite 
 * precise arithmetic, where [x/p] is the (infinite bit) 
 * integer nearest x/p (in half way case choose the even one).
 */

#include <math.h>
#include "include/internal/m99_math.h"

double remainder(double x, double y)
{
    double n, r;
    
    /* Handle special cases */
    if (y == 0.0) {
        return NAN;  /* remainder(x,0) is NaN */
    }
    
    if (x != x || y != y) {  /* NaN */
        return NAN;
    }
    
    /* Calculate n = round(x/y) using rint for proper round-to-even */
    n = rint(x / y);
    
    /* Calculate r = x - n*y */
    r = x - n * y;
    
    /* Ensure result is in range [-|y|/2, |y|/2] */
    if (r > fabs(y) / 2.0) {
        r -= fabs(y);
    } else if (r <= -fabs(y) / 2.0) {
        r += fabs(y);
    }
    
    return r;
}