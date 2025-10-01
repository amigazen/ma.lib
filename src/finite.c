/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_finite.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * finite(x) returns 1 if x is finite, else 0; no branching!
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

/****** ma.lib/finite *******************************************************
* 
*   NAME	
* 	finite -- Test if value is finite. (V1.0)
*
*   SYNOPSIS
*	int result = finite(double x);
*	  D0		   D0
*	int finite(double x);
*
*   FUNCTION
*	Test if x is a finite value. This returns 1 if x is finite (not NaN
*	and not ±Infinity), 0 otherwise. This implementation uses high-precision
*	algorithms from fdlibm for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	
*   RESULT
*	result - 1 if x is finite, 0 if x is NaN or ±Infinity.
* 
*   EXAMPLE
*	double x = 3.14;
*	int result = finite(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to !isnan(x) && !isinf(x).
* 
*   SEE ALSO
*	isnan(), isinf(), math.h
* 
******************************************************************************/

int finite(double x)
{
    int hx; 
    hx = __HI(x);
    return (unsigned)((hx&0x7fffffff)-0x7ff00000)>>31;
}
