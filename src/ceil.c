/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_ceil.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * ceil(x)
 * Return x rounded toward -inf to integral value
 * Method: Bit twiddling.
 * Exception: Inexact flag raised if x not equal to ceil(x).
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

static const double huge = 1.0e300;

/****** ma.lib/ceil *********************************************************
* 
*   NAME	
* 	ceil -- Return smallest integer >= x. (V1.0)
*
*   SYNOPSIS
*	double result = ceil(double x);
*	  D0		   D0
*	double ceil(double x);
*
*   FUNCTION
*	Compute the smallest integer value not less than x. This rounds x
*	toward positive infinity. This implementation uses high-precision
*	algorithms from fdlibm for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	
*   RESULT
*	result - Smallest integer >= x. Returns x if x is ±0, returns NaN if
*	        x is NaN, returns ±Infinity if x is ±Infinity.
* 
*   EXAMPLE
*	double x = 3.2;
*	double result = ceil(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Raises inexact flag if x != ceil(x).
* 
*   SEE ALSO
*	floor(), round(), trunc(), math.h
* 
******************************************************************************/

double ceil(double x)
{
    int i0, i1, j0;
    unsigned i, j;
    i0 =  __HI(x);
    i1 =  __LO(x);
    j0 = ((i0>>20)&0x7ff)-0x3ff;
    if(j0<20) {
        if(j0<0) { 	/* raise inexact if x != 0 */
            if(huge+x>0.0) {/* return 0*sign(x) if |x|<1 */
                if(i0<0) {i0=0x80000000;i1=0;} 
                else if((i0|i1)!=0) { i0=0x3ff00000;i1=0;}
            }
        } else {
            i = (0x000fffff)>>j0;
            if(((i0&i)|i1)==0) return x; /* x is integral */
            if(huge+x>0.0) {	/* raise inexact flag */
                if(i0>0) i0 += (0x00100000)>>j0;
                i0 &= (~i); i1=0;
            }
        }
    } else if (j0>51) {
        if(j0==0x400) return x+x;	/* inf or NaN */
        else return x;		/* x is integral */
    } else {
        i = ((unsigned)(0xffffffff))>>(j0-20);
        if((i1&i)==0) return x;	/* x is integral */
        if(huge+x>0.0) { 		/* raise inexact flag */
            if(i0>0) {
                if(j0==20) i0+=1; 
                else {
                    j = i1 + (1<<(52-j0));
                    if(j<i1) i0+=1;	/* got a carry */
                    i1 = j;
                }
            }
            i1 &= (~i);
        }
    }
    __HI(x) = i0;
    __LO(x) = i1;
    return x;
}


