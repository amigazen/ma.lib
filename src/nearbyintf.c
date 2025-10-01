/*
 * nearbyintf.c - Round to nearest integer (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/nearbyintf ****************************************************
* 
*   NAME	
* 	nearbyintf -- Round float to nearest integer. (V1.0)
*
*   SYNOPSIS
*	float result = nearbyintf(float x);
*	  D0		   D0
*	float nearbyintf(float x);
*
*   FUNCTION
*	Round a float value to the nearest integer. This rounds to the
*	nearest integer using the current rounding mode. This implementation
*	uses the double precision nearbyint() function.
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
*	float result = nearbyintf(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision nearbyint() internally for accuracy.
* 
*   SEE ALSO
*	nearbyint(), roundf(), rintf(), math.h
* 
******************************************************************************/

float nearbyintf(float x)
{
    return (float)nearbyint((double)x);
}

