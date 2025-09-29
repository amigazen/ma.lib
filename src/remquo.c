/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * double remquo(double x, double y, int *quo)
 * C99 remquo function
 */

#include <math.h>
#include "include/internal/m99_math.h"

double remquo(double x, double y, int *quo)
{
    double r;
    int q;
    
    if (y == 0.0) {
        *quo = 0;
        return NAN;
    }
    
    r = remainder(x, y);
    q = (int)((x - r) / y);
    *quo = q;
    
    return r;
}
