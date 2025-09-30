/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_fabs.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * fabs(x) returns the absolute value of x.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x

/****** ma.lib/fabs *****************************************************
* 
*   NAME	
* 	fabs -- Return absolute value of x. (V1.0)
*
*   SYNOPSIS
*	double result = fabs(double x);
*	  D0		   D0
*	double fabs(double x);
*
*   FUNCTION
*	Compute the absolute value of x. For positive x, returns x.
*	For negative x, returns -x. For zero, returns +0.0.
*	This implementation uses bit manipulation for maximum performance.
* 
*   INPUTS
*	x - Input value.
*	
*   RESULT
*	result - Absolute value of x, always non-negative. Returns NaN if
*	        x is NaN, +Infinity if x is ±Infinity.
* 
*   EXAMPLE
*	double value = -3.14;
*	double abs = fabs(value);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses bit manipulation for optimal performance.
* 
*   SEE ALSO
*	abs(), labs(), llabs(), math.h
* 
******************************************************************************/

double fabs(double x)
{
    __HI(x) &= 0x7fffffff;
    return x;
}
