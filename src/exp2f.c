/*
 * exp2f.c - Base-2 exponential function (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/exp2f ****************************************************
* 
*   NAME	
* 	exp2f -- Return 2 raised to the power of x (float). (V1.0)
*
*   SYNOPSIS
*	float result = exp2f(float x);
*	  D0		   D0
*	float exp2f(float x);
*
*   FUNCTION
*	Compute 2 raised to the power of x for float values. This is
*	equivalent to 2^x. This implementation uses the double precision
*	exp2() function for accuracy.
* 
*   INPUTS
*	x - Input value (float). Range is approximately [-128, 128] for
*	    finite results.
*	
*   RESULT
*	result - 2^x (float). Returns +Infinity for large positive x,
*	        +0.0 for large negative x, NaN for NaN input.
* 
*   EXAMPLE
*	float power = 3.0f;
*	float result = exp2f(power);  
*
*   NOTES
*	This function is C99 compliant and provides IEEE 754 accuracy.
*	Overflow occurs for x > 128, underflow for x < -128.
* 
*   SEE ALSO
*	exp2(), expf(), log2f(), math.h
* 
******************************************************************************/

float exp2f(float x)
{
    return (float)exp2((double)x);
}
