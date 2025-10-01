/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * double remquo(double x, double y, int *quo)
 * C99 remquo function
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/remquo *******************************************************
* 
*   NAME	
* 	remquo -- Return remainder and quotient of x/y. (V1.0)
*
*   SYNOPSIS
*	double result = remquo(double x, double y, int *quo);
*	  D0		   D0
*	double remquo(double x, double y, int *quo);
*
*   FUNCTION
*	Compute the remainder of x/y and store the quotient in *quo. The
*	remainder has the same sign as x and magnitude less than |y|. The
*	quotient is stored in the integer pointed to by quo.
* 
*   INPUTS
*	x - Numerator value.
*	y - Denominator value.
*	quo - Pointer to integer to store quotient.
*	
*   RESULT
*	result - Remainder of x/y. Returns NaN if y is 0 or if either
*	        argument is NaN, returns x if y is ±Infinity.
* 
*   EXAMPLE
*	double x = 5.0, y = 2.0;
*	int q;
*	double result = remquo(x, y, &q);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	The quotient is stored in the integer pointed to by quo.
* 
*   SEE ALSO
*	remainder(), fmod(), math.h
* 
******************************************************************************/

double remquo(double x, double y, int *quo)
{
    double r;
    int q;
    
    if (y == 0.0) {
        *quo = 0;
        return NAN;
    }
    
    r = remainder(x, y);
    q = (int)((x - r) / y);
    *quo = q;
    
    return r;
}
