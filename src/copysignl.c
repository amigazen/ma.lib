/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_copysign.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * copysignl(long double x, long double y)
 * copysignl(x,y) returns a value with the magnitude of x and
 * with the sign bit of y.
 * Note: SAS/C maps long double to double, so delegate to copysign()
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/copysignl *****************************************************
* 
*   NAME	
* 	copysignl -- Copy sign bit from long double to another. (V1.0)
*
*   SYNOPSIS
*	long double result = copysignl(long double x, long double y);
*	  D0		   D0
*	long double copysignl(long double x, long double y);
*
*   FUNCTION
*	Copy the sign bit from y to x, returning a value with the
*	magnitude of x and the sign of y. This implementation uses
*	the double precision copysign() function.
* 
*   INPUTS
*	x - Long double value to copy magnitude from.
*	y - Long double value to copy sign from.
*	
*   RESULT
*	result - Value with magnitude of x and sign of y.
* 
*   EXAMPLE
*	long double x = -3.0L;
*	long double y = 2.0L;
*	long double result = copysignl(x, y);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision copysign() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	copysign(), copysignf(), fabsl(), math.h
* 
******************************************************************************/

long double copysignl(long double x, long double y)
{
    /* SAS/C maps long double to double, so delegate to copysign() */
    return (long double)copysign((double)x, (double)y);
}
