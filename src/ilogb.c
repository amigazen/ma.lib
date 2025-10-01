/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_ilogb.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * ilogb(double x)
 * return the binary exponent of non-zero x
 * ilogb(0) = 0x80000001
 * ilogb(inf/NaN) = 0x7fffffff (no signal is raised)
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

/****** ma.lib/ilogb ********************************************************
* 
*   NAME	
* 	ilogb -- Return binary exponent of x as integer. (V1.0)
*
*   SYNOPSIS
*	int result = ilogb(double x);
*	  D0		   D0
*	int ilogb(double x);
*
*   FUNCTION
*	Extract the binary exponent of x as an integer. This is equivalent to
*	the exponent part of the floating-point representation. This
*	implementation uses high-precision algorithms from fdlibm for maximum
*	accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	
*   RESULT
*	result - Binary exponent of x. Returns 0x80000001 if x is 0, returns
*	        0x7fffffff if x is ±Infinity or NaN.
* 
*   EXAMPLE
*	double x = 8.0;
*	int exp = ilogb(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to the exponent part of frexp().
* 
*   SEE ALSO
*	frexp(), logb(), scalbn(), math.h
* 
******************************************************************************/

int ilogb(double x)
{
    int hx, lx, ix;

    hx  = (__HI(x))&0x7fffffff;	/* high word of x */
    if(hx<0x00100000) {
        lx = __LO(x);
        if((hx|lx)==0) 
            return 0x80000001;	/* ilogb(0) = 0x80000001 */
        else			/* subnormal x */
            if(hx==0) {
                for (ix = -1043; lx>0; lx<<=1) ix -=1;
            } else {
                for (ix = -1022,hx<<=11; hx>0; hx<<=1) ix -=1;
            }
        return ix;
    }
    else if (hx<0x7ff00000) return (hx>>20)-1023;
    else return 0x7fffffff;
}

