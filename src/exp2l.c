/*
 * exp2l.c - Base-2 exponential function (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/exp2l *********************************************************
* 
*   NAME	
* 	exp2l -- Return 2 raised to the power of long double. (V1.0)
*
*   SYNOPSIS
*	long double result = exp2l(long double x);
*	  D0		   D0
*	long double exp2l(long double x);
*
*   FUNCTION
*	Compute 2 raised to the power of a long double value. This returns
*	2^x. This implementation uses the double precision exp2() function.
* 
*   INPUTS
*	x - Long double exponent.
*	
*   RESULT
*	result - 2^x. Returns +Infinity if x is +Infinity,
*	        returns 0 if x is -Infinity, returns NaN if x is NaN.
* 
*   EXAMPLE
*	long double x = 3.0L;
*	long double result = exp2l(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision exp2() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	exp2(), expl(), log2l(), math.h
* 
******************************************************************************/

long double exp2l(long double x)
{
    return (long double)exp2((double)x);
}

