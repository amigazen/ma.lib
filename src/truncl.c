/*
 * truncl.c - Truncate toward zero (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/truncl ********************************************************
* 
*   NAME	
* 	truncl -- Truncate long double toward zero. (V1.0)
*
*   SYNOPSIS
*	long double result = truncl(long double x);
*	  D0		   D0
*	long double truncl(long double x);
*
*   FUNCTION
*	Truncate a long double value toward zero. This removes the
*	fractional part and returns the integer part. This implementation
*	uses the double precision trunc() function.
* 
*   INPUTS
*	x - Long double value to truncate.
*	
*   RESULT
*	result - Truncated long double value. Returns NaN if x is NaN,
*	        returns x if x is ±Infinity.
* 
*   EXAMPLE
*	long double x = 3.7L;
*	long double result = truncl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision trunc() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	trunc(), floorl(), ceill(), roundl(), math.h
* 
******************************************************************************/

long double truncl(long double x)
{
    return (long double)trunc((double)x);
}

