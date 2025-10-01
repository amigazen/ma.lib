/*
 * truncf.c - Truncate toward zero (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/truncf ********************************************************
* 
*   NAME	
* 	truncf -- Truncate float toward zero. (V1.0)
*
*   SYNOPSIS
*	float result = truncf(float x);
*	  D0		   D0
*	float truncf(float x);
*
*   FUNCTION
*	Truncate a float value toward zero. This removes the
*	fractional part and returns the integer part. This implementation
*	uses the double precision trunc() function.
* 
*   INPUTS
*	x - Float value to truncate.
*	
*   RESULT
*	result - Truncated float value. Returns NaN if x is NaN,
*	        returns x if x is ±Infinity.
* 
*   EXAMPLE
*	float x = 3.7f;
*	float result = truncf(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision trunc() internally for accuracy.
* 
*   SEE ALSO
*	trunc(), floorf(), ceilf(), roundf(), math.h
* 
******************************************************************************/

float truncf(float x)
{
    return (float)trunc((double)x);
}

