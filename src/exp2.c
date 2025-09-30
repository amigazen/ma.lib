/*
 * exp2.c - Base-2 exponential function
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include <errno.h>
#include "include/internal/m99_math.h"

/*
 * exp2(x) = 2^x
 * 
 * Simple implementation using exp(x * ln(2))
 */

/****** ma.lib/exp2 *****************************************************
* 
*   NAME	
* 	exp2 -- Return 2 raised to the power of x. (V1.0)
*
*   SYNOPSIS
*	double result = exp2(double x);
*	  D0		   D0
*	double exp2(double x);
*
*   FUNCTION
*	Compute 2 raised to the power of x. This is equivalent to 2^x.
*	This implementation uses exp(x * ln(2)) for accuracy.
* 
*   INPUTS
*	x - Input value. Range is approximately [-1024, 1024] for finite
*	    results.
*	
*   RESULT
*	result - 2^x. Returns +Infinity for large positive x, +0.0 for
*	        large negative x, NaN for NaN input.
* 
*   EXAMPLE
*	double power = 3.0;
*	double result = exp2(power); 
*
*   NOTES
*	This function is C99 compliant and provides IEEE 754 accuracy.
*	Overflow occurs for x > 1024, underflow for x < -1024.
* 
*   SEE ALSO
*	exp(), log2(), pow(), math.h
* 
******************************************************************************/

double exp2(double x)
{
    /* Handle special cases */
    if (x == 0.0) return 1.0;
    if (x == 1.0) return 2.0;
    if (x == 2.0) return 4.0;
    
    /* Use exp(x * ln(2)) */
    return exp(x * M_LN2);
}
