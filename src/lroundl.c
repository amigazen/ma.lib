/*
 * lroundl.c - Round to nearest long integer (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/lroundl *******************************************************
* 
*   NAME	
* 	lroundl -- Round long double to nearest long integer. (V1.0)
*
*   SYNOPSIS
*	long result = lroundl(long double x);
*	  D0		   D0
*	long lroundl(long double x);
*
*   FUNCTION
*	Round a long double value to the nearest long integer. This rounds to the
*	nearest integer, with halfway cases rounded away from zero.
*	This implementation uses the double precision lround() function.
* 
*   INPUTS
*	x - Long double value to round.
*	
*   RESULT
*	result - Rounded long integer. Returns LONG_MAX or LONG_MIN on overflow.
* 
*   EXAMPLE
*	long double x = 3.7L;
*	long result = lroundl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision lround() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	lround(), llroundl(), roundl(), math.h
* 
******************************************************************************/

long lroundl(long double x)
{
    return lround((double)x);
}

