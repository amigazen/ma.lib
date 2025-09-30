/*
 * signbit.c - Sign bit detection function
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/*
 * signbit(x) - returns 1 if x is negative, 0 otherwise
 * 
 * This function properly handles negative zero by checking the sign bit
 * directly in the IEEE 754 representation.
 */
int signbit(double x)
{
    int hx;
    
    hx = __HI(x);
    
    /* Check sign bit (bit 31) */
    if (hx < 0) {
        return 1;  /* negative */
    } else {
        return 0;  /* positive or zero */
    }
}
