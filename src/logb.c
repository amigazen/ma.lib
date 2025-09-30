/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_logb.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double logb(x)
 * IEEE 754 logb. Included to pass IEEE test suite. Not recommend.
 * Use ilogb instead.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

/****** ma.lib/logb *****************************************************
* 
*   NAME	
* 	logb -- Return binary exponent of x. (V1.0)
*
*   SYNOPSIS
*	double result = logb(double x);
*	  D0		   D0
*	double logb(double x);
*
*   FUNCTION
*	Extract the binary exponent of x as a floating-point value.
*	This is equivalent to floor(log2(|x|)) for normal numbers.
*	This function is included for IEEE 754 compliance.
* 
*   INPUTS
*	x - Input value.
*	
*   RESULT
*	result - Binary exponent of x. Returns -Infinity if x is 0.0,
*	        returns +Infinity if x is ±Infinity, returns NaN if x is NaN.
* 
*   EXAMPLE
*	double x = 8.0; 
*	double exp = logb(x);  
*
*   NOTES
*	This function is C99 compliant and provides IEEE 754 accuracy.
*	Use ilogb() instead for better performance in most cases.
* 
*   SEE ALSO
*	ilogb(), frexp(), scalbn(), math.h
* 
******************************************************************************/

double logb(double x)
{
    int lx, ix;
    ix = (__HI(x))&0x7fffffff;	/* high |x| */
    lx = __LO(x);		/* low x */
    if((ix|lx)==0) return -1.0/fabs(x);
    if(ix>=0x7ff00000) return x*x;
    if((ix>>=20)==0) 		/* IEEE 754 logb */
        return -1022.0; 
    else
        return (double) (ix-1023); 
}

