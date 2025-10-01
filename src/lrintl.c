/*
 * lrintl.c - Round to nearest long integer (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/lrintl ********************************************************
* 
*   NAME	
* 	lrintl -- Round long double to nearest long integer. (V1.0)
*
*   SYNOPSIS
*	long result = lrintl(long double x);
*	  D0		   D0
*	long lrintl(long double x);
*
*   FUNCTION
*	Round a long double value to the nearest long integer. This rounds to the
*	nearest integer using the current rounding mode. This implementation
*	uses the double precision lrint() function.
* 
*   INPUTS
*	x - Long double value to round.
*	
*   RESULT
*	result - Rounded long integer. Returns LONG_MAX or LONG_MIN on overflow.
* 
*   EXAMPLE
*	long double x = 3.7L;
*	long result = lrintl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision lrint() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	lrint(), llrintl(), rintl(), math.h
* 
******************************************************************************/

long lrintl(long double x)
{
    return lrint((double)x);
}

