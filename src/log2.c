/*
 * log2.c - Base-2 logarithm function
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include <errno.h>
#include "include/internal/m99_math.h"

/*
 * log2(x) = log(x) / log(2)
 * 
 * Simple implementation using log(x) / log(2)
 */

/****** ma.lib/log2 *****************************************************
* 
*   NAME	
* 	log2 -- Return base-2 logarithm of x. (V1.0)
*
*   SYNOPSIS
*	double result = log2(double x);
*	  D0		   D0
*	double log2(double x);
*
*   FUNCTION
*	Compute the base-2 logarithm of x. This is equivalent to log(x)/log(2).
*	This implementation uses log(x) / ln(2) for accuracy.
* 
*   INPUTS
*	x - Input value. Must be positive for valid result.
*	
*   RESULT
*	result - Base-2 logarithm of x. Returns -Infinity if x is +0.0,
*	        NaN if x is negative or NaN, +Infinity if x is +Infinity.
* 
*   EXAMPLE
*	double value = 8.0;
*	double log2_val = log2(value); 
*
*   NOTES
*	This function is C99 compliant and provides IEEE 754 accuracy.
*	Sets errno to EDOM for non-positive arguments.
* 
*   SEE ALSO
*	log(), exp2(), pow(), math.h
* 
******************************************************************************/

double log2(double x)
{
    /* Handle special cases first */
    if (x <= 0.0) {
        errno = EDOM;
        if (x == 0.0) {
            return -INFINITY;
        } else {
            return NAN;  /* log2 of negative number */
        }
    }
    
    /* Use log(x) / log(2) */
    return log(x) / M_LN2;
}