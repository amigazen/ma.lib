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

/****** ma.lib/isinf ********************************************************
* 
*   NAME	
* 	isinf -- Test if value is infinity. (V1.0)
*
*   SYNOPSIS
*	int result = isinf(double x);
*	  D0		   D0
*	int isinf(double x);
*
*   FUNCTION
*	Test if x is infinity (positive or negative). This returns 1 if x is
*	±Infinity, 0 otherwise. This implementation uses high-precision
*	algorithms for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	
*   RESULT
*	result - 1 if x is ±Infinity, 0 if x is finite or NaN.
* 
*   EXAMPLE
*	double x = 1.0 / 0.0;
*	int result = isinf(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to x == INFINITY || x == -INFINITY.
* 
*   SEE ALSO
*	isnan(), finite(), math.h
* 
******************************************************************************/

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

