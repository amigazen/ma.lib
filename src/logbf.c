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
 * float logbf(x)
 * IEEE 754 logb. Included to pass IEEE test suite. Not recommend.
 * Use ilogb instead.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of float */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x

/****** ma.lib/logbf *********************************************************
* 
*   NAME	
* 	logbf -- Return unbiased exponent of float. (V1.0)
*
*   SYNOPSIS
*	float result = logbf(float x);
*	  D0		   D0
*	float logbf(float x);
*
*   FUNCTION
*	Extract the unbiased exponent of a float value. This returns
*	the exponent as a floating-point number. This implementation
*	uses high-precision algorithms from fdlibm.
* 
*   INPUTS
*	x - Float value.
*	
*   RESULT
*	result - Unbiased exponent. Returns -Infinity if x is 0,
*	        returns +Infinity if x is ±Infinity.
* 
*   EXAMPLE
*	float x = 8.0f;
*	float result = logbf(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses direct bit manipulation for optimal performance.
* 
*   SEE ALSO
*	logb(), ilogbf(), frexpf(), math.h
* 
******************************************************************************/

float logbf(float x)
{
    int ix;
    ix = (__HI(x))&0x7fffffff;	/* high |x| */
    if(ix==0) return -1.0/fabsf(x);
    if(ix>=0x7f800000) return x*x;
    if((ix>>=23)==0) 		/* IEEE 754 logb */
        return -126.0; 
    else
        return (float) (ix-127); 
}


