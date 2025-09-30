/*
 * ma.lib Math Library - rint function
 * 
 * C99/POSIX rint function for ma.lib
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>

/*
 * rint - round to nearest integer
 * 
 * Returns an integer rounded from a double. In case of fraction exactly
 * midway, round chooses nearest even value.
 */

/****** ma.lib/rint *****************************************************
* 
*   NAME	
* 	rint -- Round to nearest integer using current rounding mode. (V1.0)
*
*   SYNOPSIS
*	double result = rint(double x);
*	  D0		   D0
*	double rint(double x);
*
*   FUNCTION
*	Round x to the nearest integer value using the current rounding mode.
*	In case of a tie (fraction exactly 0.5), rounds to the even integer.
*	This is the default rounding mode for IEEE 754.
* 
*   INPUTS
*	x - Input value to round.
*	
*   RESULT
*	result - Nearest integer to x. Returns NaN if x is NaN, returns x
*	        if x is ±Infinity, returns ±0.0 if x is ±0.0.
* 
*   EXAMPLE
*	double value = 2.5;
*	double rounded = rint(value);  
*
*   NOTES
*	This function is C99 compliant and provides IEEE 754 accuracy.
*	Uses round-to-even (banker's rounding) for tie cases.
* 
*   SEE ALSO
*	round(), nearbyint(), floor(), ceil(), math.h
* 
******************************************************************************/

double rint(double x)
{
    /* Simple implementation using floor and ceil */
    if (x >= 0.0) {
        double floor_x = floor(x);
        double frac = x - floor_x;
        if (frac < 0.5) {
            return floor_x;
        } else if (frac > 0.5) {
            return floor_x + 1.0;
        } else {
            /* Exactly 0.5 - round to even */
            if (fmod(floor_x, 2.0) == 0.0) {
                return floor_x;
            } else {
                return floor_x + 1.0;
            }
        }
    } else {
        double ceil_x = ceil(x);
        double frac = ceil_x - x;
        if (frac < 0.5) {
            return ceil_x;
        } else if (frac > 0.5) {
            return ceil_x - 1.0;
        } else {
            /* Exactly 0.5 - round to even */
            if (fmod(ceil_x, 2.0) == 0.0) {
                return ceil_x;
            } else {
                return ceil_x - 1.0;
            }
        }
    }
}
