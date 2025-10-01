/*
 * nexttowardl.c - Next representable value toward another (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/nexttowardl ***************************************************
* 
*   NAME	
* 	nexttowardl -- Next representable long double toward another. (V1.0)
*
*   SYNOPSIS
*	long double result = nexttowardl(long double x, long double y);
*	  D0		   D0
*	long double nexttowardl(long double x, long double y);
*
*   FUNCTION
*	Return the next representable long double value after x in the
*	direction toward y. This is useful for implementing floating-point
*	algorithms that need to step through representable values.
*	This implementation uses the double precision nexttoward() function.
* 
*   INPUTS
*	x - Starting long double value.
*	y - Target long double value (direction).
*	
*   RESULT
*	result - Next representable long double value toward y.
* 
*   EXAMPLE
*	long double x = 1.0L;
*	long double y = 2.0L;
*	long double result = nexttowardl(x, y);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision nexttoward() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	nexttoward(), nextafterl(), math.h
* 
******************************************************************************/

long double nexttowardl(long double x, long double y)
{
    return (long double)nexttoward((double)x, (double)y);
}

