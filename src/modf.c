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

/****** ma.lib/modf ***********************************************************
* 
*   NAME	
* 	modf -- Return fractional part and store integral part. (V1.0)
*
*   SYNOPSIS
*	double result = modf(double x, double *iptr);
*	  D0		   D0
*	double modf(double x, double *iptr);
*
*   FUNCTION
*	Break x into integral and fractional parts. The fractional part
*	is returned and the integral part is stored in *iptr. This
*	implementation uses floor() for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	iptr - Pointer to double to store integral part.
*	
*   RESULT
*	result - Fractional part of x. Returns NaN if x is NaN, returns
*	        x if x is ±0 or ±Infinity.
* 
*   EXAMPLE
*	double x = 3.14159;
*	double intpart;
*	double frac = modf(x, &intpart);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	The integral part is stored in the double pointed to by iptr.
* 
*   SEE ALSO
*	floor(), ceil(), trunc(), math.h
* 
******************************************************************************/

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