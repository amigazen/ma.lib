/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm pattern for infinity detection
 * 
 * isinf(x) returns 1 if x is infinity, else 0
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros are defined in m99_math.h */

/****** ma.lib/isinf ****************************************************
* 
*   NAME	
* 	isinf -- Test if value is infinity. (V1.0)
*
*   SYNOPSIS
*	int result = isinf(double x);
*	  D0		   D0
*	int isinf(double x);
*
*   FUNCTION
*	Test if the given floating-point value is infinity (positive or
*	negative). Infinity values represent values that are too large
*	to be represented in the floating-point format.
* 
*   INPUTS
*	x - Floating-point value to test.
*	
*   RESULT
*	result - Non-zero if x is ±Infinity, zero if x is finite or NaN.
* 
*   EXAMPLE
*	double value = 1.0 / 0.0;  
*	if (isinf(value)) {
*	    printf("Value is infinity\n");
*	}
*
*   NOTES
*	This function is C99 compliant and uses bit manipulation for
*	maximum performance. Checks both IEEE 754 infinity bit patterns
*	and HUGE_VAL for compatibility.
* 
*   SEE ALSO
*	isnan(), finite(), fpclassify(), math.h
* 
******************************************************************************/

int isinf(double x)
{
    int hx, lx;
    hx = __HI(x);
    lx = __LO(x);
    
    /* Check if exponent is all 1s (0x7ff) and mantissa is 0 */
    if ((hx & 0x7ff00000) == 0x7ff00000) {
        if ((hx & 0x000fffff) == 0 && lx == 0) {
            return 1;  /* infinity */
        }
    }
    
    /* Also check for HUGE_VAL which is (1.0/0.0) */
    if (x == HUGE_VAL || x == -HUGE_VAL) {
        return 1;
    }
    
    return 0;  /* not infinity */
}

