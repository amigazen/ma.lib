/*
 * roundl.c - Round to nearest integer (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/roundl ********************************************************
* 
*   NAME	
* 	roundl -- Round long double to nearest integer. (V1.0)
*
*   SYNOPSIS
*	long double result = roundl(long double x);
*	  D0		   D0
*	long double roundl(long double x);
*
*   FUNCTION
*	Round a long double value to the nearest integer. This rounds to the
*	nearest integer, with halfway cases rounded away from zero.
*	This implementation uses the double precision round() function.
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
*	long double result = roundl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision round() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	round(), truncl(), floorl(), ceill(), math.h
* 
******************************************************************************/

long double roundl(long double x)
{
    return (long double)round((double)x);
}

