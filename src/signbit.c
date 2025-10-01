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

/****** ma.lib/signbit ******************************************************
* 
*   NAME	
* 	signbit -- Test if value is negative. (V1.0)
*
*   SYNOPSIS
*	int result = signbit(double x);
*	  D0		   D0
*	int signbit(double x);
*
*   FUNCTION
*	Test if x is negative by checking the sign bit. This returns 1 if x
*	is negative (including negative zero), 0 otherwise. This implementation
*	uses high-precision algorithms for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	
*   RESULT
*	result - 1 if x is negative, 0 if x is positive or zero.
* 
*   EXAMPLE
*	double x = -3.14;
*	int result = signbit(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This properly handles negative zero.
* 
*   SEE ALSO
*	copysign(), fabs(), math.h
* 
******************************************************************************/

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
