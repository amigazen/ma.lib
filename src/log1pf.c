/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * log1pf(x) = log(1+x) for float
 * 
 * Based on Python's _math.c implementation with modifications for C89/SAS/C
 */

#include <math.h>
#include <float.h>
#include "include/internal/m99_math.h"

/****** ma.lib/log1pf ********************************************************
* 
*   NAME	
* 	log1pf -- Return log(1+x) for float. (V1.0)
*
*   SYNOPSIS
*	float result = log1pf(float x);
*	  D0		   D0
*	float log1pf(float x);
*
*   FUNCTION
*	Compute log(1+x) for float values. This provides accurate
*	logarithm computation for values close to zero. This
*	implementation uses high-precision algorithms for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-1, +∞].
*	
*   RESULT
*	result - log(1+x). Returns -Infinity if x is -1,
*	        returns NaN if x < -1.
* 
*   EXAMPLE
*	float x = 0.1f;
*	float result = log1pf(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	More accurate than logf(1+x) for small x values.
* 
*   SEE ALSO
*	log1p(), logf(), expf(), math.h
* 
******************************************************************************/

float log1pf(float x)
{
    float y;
    
    /* Handle special case of zero input directly */
    if (x == 0.0f) {
        return x;
    }
    
    if (fabsf(x) < FLT_EPSILON/2.0f) {
        return x;
    }
    else if (-0.5f <= x && x <= 1.0f) {
        y = 1.0f + x;
        return logf(y) - ((y - 1.0f) - x) / y;
    }
    else {
        /* NaNs and infinities should end up here */
        return logf(1.0f + x);
    }
}
