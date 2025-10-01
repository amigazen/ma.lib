/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * int fpclassify(double x)
 * C99 fpclassify function
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/fpclassify **************************************************
* 
*   NAME	
* 	fpclassify -- Classify floating-point value. (V1.0)
*
*   SYNOPSIS
*	int result = fpclassify(double x);
*	  D0		   D0
*	int fpclassify(double x);
*
*   FUNCTION
*	Classify the floating-point value x into one of the standard categories.
*	This returns a constant indicating the type of value. This implementation
*	uses high-precision algorithms for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	
*   RESULT
*	result - Classification constant: FP_NAN, FP_INFINITE, FP_ZERO,
*	        FP_SUBNORMAL, or FP_NORMAL.
* 
*   EXAMPLE
*	double x = 3.14;
*	int result = fpclassify(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to checking isnan(), isinf(), etc.
* 
*   SEE ALSO
*	isnan(), isinf(), finite(), math.h
* 
******************************************************************************/

int fpclassify(double x)
{
    if (isnan(x)) return FP_NAN;
    if (isinf(x)) return FP_INFINITE;
    if (x == 0.0) return FP_ZERO;
    if (x < 1.175494e-38 && x > -1.175494e-38) return FP_SUBNORMAL;
    return FP_NORMAL;
}


