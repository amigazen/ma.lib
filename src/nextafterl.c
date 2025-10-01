/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_nextafter.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * nextafterl(long double x, long double y)
 * return the next machine floating-point number of x in the
 * direction toward y.
 * Note: SAS/C maps long double to double, so delegate to nextafter()
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/nextafterl ****************************************************
* 
*   NAME	
* 	nextafterl -- Next representable long double toward another. (V1.0)
*
*   SYNOPSIS
*	long double result = nextafterl(long double x, long double y);
*	  D0		   D0
*	long double nextafterl(long double x, long double y);
*
*   FUNCTION
*	Return the next representable long double value after x in the
*	direction toward y. This is useful for implementing floating-point
*	algorithms that need to step through representable values.
*	This implementation uses the double precision nextafter() function.
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
*	long double result = nextafterl(x, y);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision nextafter() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	nextafter(), nexttowardl(), math.h
* 
******************************************************************************/

long double nextafterl(long double x, long double y)
{
    /* SAS/C maps long double to double, so delegate to nextafter() */
    return (long double)nextafter((double)x, (double)y);
}


