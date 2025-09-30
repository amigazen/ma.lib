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
 * copysign(double x, double y)
 * copysign(x,y) returns a value with the magnitude of x and
 * with the sign bit of y.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

/****** ma.lib/copysign *************************************************
* 
*   NAME	
* 	copysign -- Copy sign bit from y to x. (V1.0)
*
*   SYNOPSIS
*	double result = copysign(double x, double y);
*	  D0		   D0
*	double copysign(double x, double y);
*
*   FUNCTION
*	Copy the sign bit from y to x. Returns a value with the magnitude
*	of x and the sign of y. This function is useful for ensuring
*	consistent sign handling in mathematical operations.
* 
*   INPUTS
*	x - Value whose magnitude will be used.
*	y - Value whose sign will be used.
*	
*   RESULT
*	result - Value with magnitude of x and sign of y. Returns +0.0 if
*	        x is +0.0, returns -0.0 if x is -0.0, returns NaN if x is NaN.
* 
*   EXAMPLE
*	double x = 3.14, y = -2.0;
*	double result = copysign(x, y);
*
*   NOTES
*	This function is C99 compliant and provides IEEE 754 accuracy.
*	Uses bit manipulation for optimal performance.
* 
*   SEE ALSO
*	signbit(), fabs(), math.h
* 
******************************************************************************/

double copysign(double x, double y)
{
    __HI(x) = (__HI(x)&0x7fffffff)|(__HI(y)&0x80000000);
    return x;
}
