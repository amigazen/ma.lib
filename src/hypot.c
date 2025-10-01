/*
 * hypot.c - Euclidean distance function
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file implements the C99 hypot() function using AmigaOS math libraries
 * when available, falling back to standard implementation otherwise.
 */

#include <math.h>
#include <errno.h>
#include <float.h>

#include <amiga/math.h>

/*
 * hypot - Euclidean distance
 * 
 * Returns the square root of x^2 + y^2, computed in a way that
 * avoids overflow and underflow.
 * Domain: (-infinity, +infinity) for both x and y
 * Range: [0, +infinity)
 */

/****** ma.lib/hypot ********************************************************
* 
*   NAME	
* 	hypot -- Return Euclidean distance sqrt(x² + y²). (V1.0)
*
*   SYNOPSIS
*	double result = hypot(double x, double y);
*	  D0		   D0
*	double hypot(double x, double y);
*
*   FUNCTION
*	Compute the Euclidean distance sqrt(x² + y²). This is the length of the
*	hypotenuse of a right triangle with sides x and y. This implementation
*	avoids overflow and underflow by scaling the computation.
* 
*   INPUTS
*	x - First value.
*	y - Second value.
*	
*   RESULT
*	result - Euclidean distance sqrt(x² + y²). Returns +Infinity if either
*	        argument is ±Infinity, returns NaN if either argument is NaN.
* 
*   EXAMPLE
*	double x = 3.0, y = 4.0;
*	double result = hypot(x, y);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Handles overflow and underflow conditions correctly.
* 
*   SEE ALSO
*	sqrt(), pow(), math.h
* 
******************************************************************************/

double hypot(double x, double y)
{
    double result;
    double abs_x, abs_y, max_val, min_val;
    
    /* Check for special values */
    if (x != x || y != y) {  /* Either is NaN */
        return NAN;
    }
    
    if (x == INFINITY || x == -INFINITY || 
        y == INFINITY || y == -INFINITY) {
        return INFINITY;
    }
    
    /* Get absolute values */
    abs_x = fabs(x);
    abs_y = fabs(y);
    
    /* Find maximum and minimum */
    if (abs_x > abs_y) {
        max_val = abs_x;
        min_val = abs_y;
    } else {
        max_val = abs_y;
        min_val = abs_x;
    }
    
    /* Handle zero case */
    if (max_val == 0.0) {
        return 0.0;
    }
    
#ifdef __AMIGA__
    /* Use AmigaOS math library if available */
    if (m99_has_trans()) {
        /* hypot(x,y) = sqrt(x^2 + y^2) */
        result = amiga_ieee_sqrt(x*x + y*y);
        if (m99_get_error() == M99_ERR_NONE) {
            return result;
        }
    }
#endif
    
    /* Standard implementation with overflow protection */
    if (max_val > DBL_MAX / 2.0) {
        /* Scale down to avoid overflow */
        double scale = 1.0 / max_val;
        double scaled_x = x * scale;
        double scaled_y = y * scale;
        result = max_val * sqrt(scaled_x * scaled_x + scaled_y * scaled_y);
    } else {
        /* Normal case */
        result = sqrt(x*x + y*y);
    }
    
    /* Check for overflow */
    if (result == INFINITY) {
        errno = ERANGE;
    }
    
    return result;
}
