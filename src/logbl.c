/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_logb.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * long double logbl(x)
 * IEEE 754 logb. Included to pass IEEE test suite. Not recommend.
 * Use ilogb instead.
 * Note: SAS/C maps long double to double, so delegate to logb()
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/logbl *********************************************************
* 
*   NAME	
* 	logbl -- Return unbiased exponent of long double. (V1.0)
*
*   SYNOPSIS
*	long double result = logbl(long double x);
*	  D0		   D0
*	long double logbl(long double x);
*
*   FUNCTION
*	Extract the unbiased exponent of a long double value. This returns
*	the exponent as a floating-point number. This implementation uses
*	the double precision logb() function.
* 
*   INPUTS
*	x - Long double value.
*	
*   RESULT
*	result - Unbiased exponent. Returns -Infinity if x is 0,
*	        returns +Infinity if x is ±Infinity.
* 
*   EXAMPLE
*	long double x = 8.0L;
*	long double result = logbl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision logb() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	logb(), ilogbl(), frexpl(), math.h
* 
******************************************************************************/

long double logbl(long double x)
{
    /* SAS/C maps long double to double, so delegate to logb() */
    return (long double)logb((double)x);
}


