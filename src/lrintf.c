/*
 * lrintf.c - Round to nearest long integer (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/lrintf ********************************************************
* 
*   NAME	
* 	lrintf -- Round float to nearest long integer. (V1.0)
*
*   SYNOPSIS
*	long result = lrintf(float x);
*	  D0		   D0
*	long lrintf(float x);
*
*   FUNCTION
*	Round a float value to the nearest long integer. This rounds to the
*	nearest integer using the current rounding mode. This implementation
*	uses the double precision lrint() function.
* 
*   INPUTS
*	x - Float value to round.
*	
*   RESULT
*	result - Rounded long integer. Returns LONG_MAX or LONG_MIN on overflow.
* 
*   EXAMPLE
*	float x = 3.7f;
*	long result = lrintf(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision lrint() internally for accuracy.
* 
*   SEE ALSO
*	lrint(), llrintf(), rintf(), math.h
* 
******************************************************************************/

long lrintf(float x)
{
    return lrint((double)x);
}

