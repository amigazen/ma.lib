/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm pattern for infinity detection
 * 
 * isinf(x) returns 1 if x is infinity, else 0
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros are defined in m99_math.h */

int isinf(double x)
{
    int hx, lx;
    hx = __HI(x);
    lx = __LO(x);
    
    /* Check if exponent is all 1s (0x7ff) and mantissa is 0 */
    if ((hx & 0x7ff00000) == 0x7ff00000) {
        if ((hx & 0x000fffff) == 0 && lx == 0) {
            return 1;  /* infinity */
        }
    }
    
    /* Also check for HUGE_VAL which is (1.0/0.0) */
    if (x == HUGE_VAL || x == -HUGE_VAL) {
        return 1;
    }
    
    return 0;  /* not infinity */
}

