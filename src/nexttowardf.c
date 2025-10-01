/*
 * nexttowardf.c - Next representable value toward another (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/nexttowardf ***************************************************
* 
*   NAME	
* 	nexttowardf -- Next representable float toward long double. (V1.0)
*
*   SYNOPSIS
*	float result = nexttowardf(float x, long double y);
*	  D0		   D0
*	float nexttowardf(float x, long double y);
*
*   FUNCTION
*	Return the next representable float value after x in the
*	direction toward y. This is useful for implementing floating-point
*	algorithms that need to step through representable values.
*	This implementation uses the double precision nexttoward() function.
* 
*   INPUTS
*	x - Starting float value.
*	y - Target long double value (direction).
*	
*   RESULT
*	result - Next representable float value toward y.
* 
*   EXAMPLE
*	float x = 1.0f;
*	long double y = 2.0L;
*	float result = nexttowardf(x, y);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision nexttoward() internally for accuracy.
* 
*   SEE ALSO
*	nexttoward(), nextafterf(), math.h
* 
******************************************************************************/

float nexttowardf(float x, long double y)
{
    return (float)nexttoward((double)x, y);
}

