/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * log1pl(x) = log(1+x) for long double
 * 
 * Based on Python's _math.c implementation with modifications for C89/SAS/C
 * Note: SAS/C maps long double to double, so this is essentially log1p()
 */

#include <math.h>
#include <float.h>
#include "include/internal/m99_math.h"

/****** ma.lib/log1pl ********************************************************
* 
*   NAME	
* 	log1pl -- Return log(1+x) for long double. (V1.0)
*
*   SYNOPSIS
*	long double result = log1pl(long double x);
*	  D0		   D0
*	long double log1pl(long double x);
*
*   FUNCTION
*	Compute log(1+x) for long double values. This provides accurate
*	logarithm computation for values close to zero. This implementation
*	uses the double precision log1p() function.
* 
*   INPUTS
*	x - Long double value. Range is [-1, +∞].
*	
*   RESULT
*	result - log(1+x). Returns -Infinity if x is -1,
*	        returns NaN if x < -1.
* 
*   EXAMPLE
*	long double x = 0.1L;
*	long double result = log1pl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision log1p() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	log1p(), logl(), expl(), math.h
* 
******************************************************************************/

long double log1pl(long double x)
{
    /* SAS/C maps long double to double, so delegate to log1p() */
    return (long double)log1p((double)x);
}
