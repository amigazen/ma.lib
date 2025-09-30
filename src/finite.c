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

/****** ma.lib/finite ***************************************************
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
*	Test if the given floating-point value is finite (not infinity or NaN).
*	Finite values are normal numbers, subnormal numbers, and zero.
* 
*   INPUTS
*	x - Floating-point value to test.
*	
*   RESULT
*	result - Non-zero if x is finite, zero if x is infinity or NaN.
* 
*   EXAMPLE
*	double value = 3.14159;
*	if (finite(value)) {
*	    printf("Value is finite\n");
*	}
*
*   NOTES
*	This function is C99 compliant and uses bit manipulation for
*	maximum performance. No branching is used in the implementation.
* 
*   SEE ALSO
*	isnan(), isinf(), fpclassify(), math.h
* 
******************************************************************************/

int finite(double x)
{
    int hx; 
    hx = __HI(x);
    return (unsigned)((hx&0x7fffffff)-0x7ff00000)>>31;
}
