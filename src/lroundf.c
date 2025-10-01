/*
 * lroundf.c - Round to nearest long integer (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/lroundf *******************************************************
* 
*   NAME	
* 	lroundf -- Round float to nearest long integer. (V1.0)
*
*   SYNOPSIS
*	long result = lroundf(float x);
*	  D0		   D0
*	long lroundf(float x);
*
*   FUNCTION
*	Round a float value to the nearest long integer. This rounds to the
*	nearest integer, with halfway cases rounded away from zero.
*	This implementation uses the double precision lround() function.
* 
*   INPUTS
*	x - Float value to round.
*	
*   RESULT
*	result - Rounded long integer. Returns LONG_MAX or LONG_MIN on overflow.
* 
*   EXAMPLE
*	float x = 3.7f;
*	long result = lroundf(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision lround() internally for accuracy.
* 
*   SEE ALSO
*	lround(), llroundf(), roundf(), math.h
* 
******************************************************************************/

long lroundf(float x)
{
    return lround((double)x);
}

