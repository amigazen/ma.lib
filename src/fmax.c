/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * double fmax(double x, double y)
 * IEEE 754 fmax function
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/fmax *********************************************************
* 
*   NAME	
* 	fmax -- Return maximum of two values. (V1.0)
*
*   SYNOPSIS
*	double result = fmax(double x, double y);
*	  D0		   D0
*	double fmax(double x, double y);
*
*   FUNCTION
*	Return the maximum of two floating-point values. If one argument is NaN,
*	return the other argument. If both arguments are NaN, return NaN.
*	If the arguments are equal, return the one with positive zero.
* 
*   INPUTS
*	x - First value to compare.
*	y - Second value to compare.
*	
*   RESULT
*	result - Maximum of x and y. Returns NaN if both arguments are NaN.
* 
*   EXAMPLE
*	double x = 3.14, y = 2.71;
*	double result = fmax(x, y);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to (x > y) ? x : y with proper NaN handling.
* 
*   SEE ALSO
*	fmin(), fabs(), math.h
* 
******************************************************************************/

double fmax(double x, double y)
{
    if (isnan(x)) return y;
    if (isnan(y)) return x;
    if (x > y) return x;
    if (y > x) return y;
    /* x == y, return the one with positive zero */
    if (signbit(x)) return y;
    return x;
}
