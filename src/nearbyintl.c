/*
 * nearbyintl.c - Round to nearest integer (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/nearbyintl ****************************************************
* 
*   NAME	
* 	nearbyintl -- Round long double to nearest integer. (V1.0)
*
*   SYNOPSIS
*	long double result = nearbyintl(long double x);
*	  D0		   D0
*	long double nearbyintl(long double x);
*
*   FUNCTION
*	Round a long double value to the nearest integer. This rounds to the
*	nearest integer using the current rounding mode. This implementation
*	uses the double precision nearbyint() function.
* 
*   INPUTS
*	x - Long double value to round.
*	
*   RESULT
*	result - Rounded long double value. Returns NaN if x is NaN,
*	        returns x if x is ±Infinity.
* 
*   EXAMPLE
*	long double x = 3.7L;
*	long double result = nearbyintl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision nearbyint() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	nearbyint(), roundl(), rintl(), math.h
* 
******************************************************************************/

long double nearbyintl(long double x)
{
    return (long double)nearbyint((double)x);
}

