/*
 * log2f.c - Base-2 logarithm function (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/log2f ****************************************************
* 
*   NAME	
* 	log2f -- Return base-2 logarithm of x (float). (V1.0)
*
*   SYNOPSIS
*	float result = log2f(float x);
*	  D0		   D0
*	float log2f(float x);
*
*   FUNCTION
*	Compute the base-2 logarithm of x for float values. This is
*	equivalent to log(x)/log(2). This implementation uses the double
*	precision log2() function for accuracy.
* 
*   INPUTS
*	x - Input value (float). Must be positive for valid result.
*	
*   RESULT
*	result - Base-2 logarithm of x (float). Returns -Infinity if x is +0.0,
*	        NaN if x is negative or NaN, +Infinity if x is +Infinity.
* 
*   EXAMPLE
*	float value = 8.0f;
*	float log2_val = log2f(value);  
*
*   NOTES
*	This function is C99 compliant and provides IEEE 754 accuracy.
*	Sets errno to EDOM for non-positive arguments.
* 
*   SEE ALSO
*	log2(), logf(), exp2f(), math.h
* 
******************************************************************************/

float log2f(float x)
{
    return (float)log2((double)x);
}
