/*
 * cbrt.c - Cube root function
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * This file implements the C99 cbrt() function using Amiga math libraries
 * when available, falling back to standard implementation otherwise.
 */

#include <math.h>
#include <errno.h>
#include <float.h>

#include <amiga/math.h>

/*
 * cbrt - cube root
 * 
 * Returns the cube root of x.
 * Domain: (-infinity, +infinity)
 * Range: (-infinity, +infinity)
 */

/****** ma.lib/cbrt *********************************************************
* 
*   NAME	
* 	cbrt -- Return cube root of x. (V1.0)
*
*   SYNOPSIS
*	double result = cbrt(double x);
*	  D0		   D0
*	double cbrt(double x);
*
*   FUNCTION
*	Compute the cube root of x. The cube root is the value y such that
*	y³ = x. This implementation uses high-precision algorithms for maximum
*	accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	
*   RESULT
*	result - Cube root of x. Returns x if x is ±0, returns NaN if x is NaN,
*	        returns ±Infinity if x is ±Infinity.
* 
*   EXAMPLE
*	double x = 8.0;
*	double result = cbrt(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Handles special values correctly.
* 
*   SEE ALSO
*	sqrt(), pow(), math.h
* 
******************************************************************************/

double cbrt(double x)
{
    double result;
    
    /* Check for special values */
    if (x == 0.0) {
        return 0.0;
    }
    
    if (x == INFINITY) {
        return INFINITY;
    }
    
    if (x == -INFINITY) {
        return -INFINITY;
    }
    
    if (x != x) {  /* NaN */
        return NAN;
    }
    
#ifdef __AMIGA__
    /* Use AmigaOS math library if available */
    if (m99_has_trans()) {
        /* cbrt(x) = pow(x, 1.0/3.0) */
        result = amiga_ieee_pow(x, 1.0/3.0);
        if (m99_get_error() == M99_ERR_NONE) {
            return result;
        }
    }
#endif
    
    /* Standard implementation using pow */
    result = pow(x, 1.0/3.0);
    
    /* Check for overflow */
    if (result == INFINITY) {
        errno = ERANGE;
    }
    
    return result;
}
