/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * double fdim(double x, double y)
 * IEEE 754 fdim function
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/fdim *********************************************************
* 
*   NAME	
* 	fdim -- Return positive difference of two values. (V1.0)
*
*   SYNOPSIS
*	double result = fdim(double x, double y);
*	  D0		   D0
*	double fdim(double x, double y);
*
*   FUNCTION
*	Return the positive difference of two floating-point values. This is
*	equivalent to max(x - y, 0). If either argument is NaN, return NaN.
*	If x > y, return x - y, otherwise return 0.
* 
*   INPUTS
*	x - First value.
*	y - Second value.
*	
*   RESULT
*	result - Positive difference max(x - y, 0). Returns NaN if either
*	        argument is NaN.
* 
*   EXAMPLE
*	double x = 5.0, y = 3.0;
*	double result = fdim(x, y);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to fmax(x - y, 0.0).
* 
*   SEE ALSO
*	fmax(), fmin(), fabs(), math.h
* 
******************************************************************************/

double fdim(double x, double y)
{
    if (isnan(x) || isnan(y)) return x + y;
    if (x > y) return x - y;
    return 0.0;
}
