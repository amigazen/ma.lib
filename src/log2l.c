/*
 * log2l.c - Base-2 logarithm function (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/log2l *********************************************************
* 
*   NAME	
* 	log2l -- Return base-2 logarithm of long double. (V1.0)
*
*   SYNOPSIS
*	long double result = log2l(long double x);
*	  D0		   D0
*	long double log2l(long double x);
*
*   FUNCTION
*	Compute the base-2 logarithm of a long double value. This returns
*	log₂(x). This implementation uses the double precision log2() function.
* 
*   INPUTS
*	x - Long double value. Must be > 0 for valid result.
*	
*   RESULT
*	result - Base-2 logarithm of x. Returns -Infinity if x is 0,
*	        returns NaN if x < 0, returns +Infinity if x is +Infinity.
* 
*   EXAMPLE
*	long double x = 8.0L;
*	long double result = log2l(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision log2() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	log2(), logl(), exp2l(), math.h
* 
******************************************************************************/

long double log2l(long double x)
{
    return (long double)log2((double)x);
}

