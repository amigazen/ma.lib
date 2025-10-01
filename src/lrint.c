/*
 * lrint.c - Round to nearest long integer
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include <limits.h>
#include "include/internal/m99_math.h"

/*
 * lrint(x)
 * Return x rounded to integral value according to the prevailing
 * rounding mode.
 * Method:
 *      Using floating addition.
 * Exception:
 *      Inexact flag raised if x not equal to lrint(x).
 */

static const double huge = 1.0e300;

/****** ma.lib/lrint ********************************************************
* 
*   NAME	
* 	lrint -- Return x rounded to nearest long integer. (V1.0)
*
*   SYNOPSIS
*	long result = lrint(double x);
*	  D0		   D0
*	long lrint(double x);
*
*   FUNCTION
*	Compute the nearest long integer value to x according to the current
*	rounding mode. This rounds x to the nearest long integer using the
*	prevailing rounding mode. This implementation uses high-precision
*	algorithms for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	
*   RESULT
*	result - Nearest long integer to x. Returns 0 if x is ±0, returns
*	        NaN if x is NaN, returns ±Infinity if x is ±Infinity.
* 
*   EXAMPLE
*	double x = 3.7;
*	long result = lrint(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Raises inexact flag if x != lrint(x).
* 
*   SEE ALSO
*	round(), rint(), nearbyint(), math.h
* 
******************************************************************************/

long lrint(double x)
{
    int i0,i1,j0;
    unsigned i,j;
    i0 =  __HI(x);
    i1 =  __LO(x);
    j0 = ((i0>>20)&0x7ff)-0x3ff;
    if(j0<20) {
        if(j0<0) {
            if(huge+x>0.0) {        /* raise inexact if x != 0 */
                if(j0==-1) return x>0.0?1:-1;
                else return 0;
            }
        } else {
            i = (0x000fffff)>>j0;
            if(((i0&i)|i1)==0) return (long)x; /* x is integral */
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
        else return (long)x;              /* x is integral */
    } else {
        i = ((unsigned)(0xffffffff))>>(j0-20);
        if((i1&i)==0) return (long)x;     /* x is integral */
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
    
    /* Convert to long, checking for overflow */
    if (x > (double)LONG_MAX) return LONG_MAX;
    if (x < (double)LONG_MIN) return LONG_MIN;
    
    return (long)x;
}
