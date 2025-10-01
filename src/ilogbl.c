/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_ilogb.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * ilogbl(long double x)
 * return the binary exponent of non-zero x
 * ilogbl(0) = 0x80000001
 * ilogbl(inf/NaN) = 0x7fffffff (no signal is raised)
 * Note: SAS/C maps long double to double, so delegate to ilogb()
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/ilogbl ********************************************************
* 
*   NAME	
* 	ilogbl -- Return binary exponent of long double. (V1.0)
*
*   SYNOPSIS
*	int result = ilogbl(long double x);
*	  D0		   D0
*	int ilogbl(long double x);
*
*   FUNCTION
*	Extract the binary exponent of a long double value. This returns
*	the exponent as an integer. This implementation uses
*	the double precision ilogb() function.
* 
*   INPUTS
*	x - Long double value.
*	
*   RESULT
*	result - Binary exponent. Returns 0x80000001 if x is 0,
*	        returns 0x7fffffff if x is ±Infinity or NaN.
* 
*   EXAMPLE
*	long double x = 8.0L;
*	int result = ilogbl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision ilogb() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	ilogb(), logbl(), frexpl(), math.h
* 
******************************************************************************/

int ilogbl(long double x)
{
    /* SAS/C maps long double to double, so delegate to ilogb() */
    return ilogb((double)x);
}


