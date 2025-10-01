/*
 * roundf.c - Round to nearest integer (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/roundf ********************************************************
* 
*   NAME	
* 	roundf -- Round float to nearest integer. (V1.0)
*
*   SYNOPSIS
*	float result = roundf(float x);
*	  D0		   D0
*	float result = roundf(float x);
*
*   FUNCTION
*	Round a float value to the nearest integer. This rounds to the
*	nearest integer, with halfway cases rounded away from zero.
*	This implementation uses the double precision round() function.
* 
*   INPUTS
*	x - Float value to round.
*	
*   RESULT
*	result - Rounded float value. Returns NaN if x is NaN,
*	        returns x if x is ±Infinity.
* 
*   EXAMPLE
*	float x = 3.7f;
*	float result = roundf(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision round() internally for accuracy.
* 
*   SEE ALSO
*	round(), truncf(), floorf(), ceilf(), math.h
* 
******************************************************************************/

float roundf(float x)
{
    return (float)round((double)x);
}

