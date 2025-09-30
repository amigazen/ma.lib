/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_isnan.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * isnan(x) returns 1 if x is nan, else 0; no branching!
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of double */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x
#define __LO(x) *(1+(int*)&x)

/****** ma.lib/isnan ****************************************************
* 
*   NAME	
* 	isnan -- Test if value is NaN (Not a Number). (V1.0)
*
*   SYNOPSIS
*	int result = isnan(double x);
*	  D0		   D0
*	int isnan(double x);
*
*   FUNCTION
*	Test if the given floating-point value is NaN (Not a Number).
*	NaN values are special floating-point values that represent
*	undefined or unrepresentable results.
* 
*   INPUTS
*	x - Floating-point value to test.
*	
*   RESULT
*	result - Non-zero if x is NaN, zero if x is a valid number.
* 
*   EXAMPLE
*	double value = 0.0 / 0.0;  
*	if (isnan(value)) {
*	    printf("Value is NaN\n");
*	}
*
*   NOTES
*	This function is C99 compliant and uses bit manipulation for
*	maximum performance. No branching is used in the implementation.
* 
*   SEE ALSO
*	isinf(), finite(), fpclassify(), math.h
* 
******************************************************************************/

int isnan(double x)
{
    int hx,lx;
    hx = (__HI(x)&0x7fffffff);
    lx = __LO(x);
    hx |= (unsigned)(lx|(-lx))>>31;	
    hx = 0x7ff00000 - hx;
    return ((unsigned)(hx))>>31;
}
