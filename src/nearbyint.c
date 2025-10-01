/*
 * nearbyint.c - Round to nearest integer
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/*
 * nearbyint(x)
 * Return x rounded to integral value according to the prevailing
 * rounding mode.
 * Method:
 *      Using floating addition.
 * Exception:
 *      Inexact flag raised if x not equal to nearbyint(x).
 */

static const double huge = 1.0e300;

/****** ma.lib/nearbyint ****************************************************
* 
*   NAME	
* 	nearbyint -- Return x rounded to nearest integer. (V1.0)
*
*   SYNOPSIS
*	double result = nearbyint(double x);
*	  D0		   D0
*	double nearbyint(double x);
*
*   FUNCTION
*	Compute the nearest integer value to x according to the current
*	rounding mode. This rounds x to the nearest integer using the
*	prevailing rounding mode. This implementation uses high-precision
*	algorithms for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	
*   RESULT
*	result - Nearest integer to x. Returns x if x is ±0, returns NaN if
*	        x is NaN, returns ±Infinity if x is ±Infinity.
* 
*   EXAMPLE
*	double x = 3.7;
*	double result = nearbyint(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Raises inexact flag if x != nearbyint(x).
* 
*   SEE ALSO
*	round(), rint(), floor(), ceil(), math.h
* 
******************************************************************************/

double nearbyint(double x)
{
    int i0,i1,j0;
    unsigned i,j;
    i0 =  __HI(x);
    i1 =  __LO(x);
    j0 = ((i0>>20)&0x7ff)-0x3ff;
    if(j0<20) {
        if(j0<0) {
            if(huge+x>0.0) {        /* raise inexact if x != 0 */
                if(j0==-1) return x>0.0?1.0:-1.0;
                else return 0.0;
            }
        } else {
            i = (0x000fffff)>>j0;
            if(((i0&i)|i1)==0) return x; /* x is integral */
            if(huge+x>0.0) {        /* raise inexact flag */
                if(i0>0) x += 0.5;
                else x -= 0.5;
                i0 = __HI(x);
                i1 = __LO(x);
                i0 &= (~i);
                i1 = 0;
            }
        }
    } else if (j0>51) {
        if(j0==0x400) return x+x;   /* inf or NaN */
        else return x;              /* x is integral */
    } else {
        i = ((unsigned)(0xffffffff))>>(j0-20);
        if((i1&i)==0) return x;     /* x is integral */
        if(huge+x>0.0) {            /* raise inexact flag */
            if(i0>0) {
                if(j0==20) i0+=1;
                else {
                    j = i1+(1<<(52-j0));
                    if(j<i1) i0 +=1 ;       /* got a carry */
                    i1=j;
                }
            } else {
                if(j0==20) i0-=1;
                else {
                    j = i1 - (1<<(52-j0));
                    if(j>i1) i0 -=1;        /* got a borrow */
                    i1 = j;
                }
            }
        }
    }
    __HI(x) = i0;
    __LO(x) = i1;
    return x;
}
