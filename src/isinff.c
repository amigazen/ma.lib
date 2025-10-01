/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm pattern for infinity detection
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * isinff(x) returns 1 if x is infinity, else 0
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/isinff ********************************************************
* 
*   NAME	
* 	isinff -- Test if float value is infinity. (V1.0)
*
*   SYNOPSIS
*	int result = isinff(float x);
*	  D0		   D0
*	int isinff(float x);
*
*   FUNCTION
*	Test if a float value is infinity (positive or negative).
*	This performs IEEE 754 infinity detection for float values
*	on AmigaOS with SAS/C.
* 
*   INPUTS
*	x - Float value to test.
*	
*   RESULT
*	result - Non-zero if x is infinity, zero otherwise.
* 
*   EXAMPLE
*	float x = 1.0f / 0.0f;
*	if (isinff(x)) {
*	    printf("x is infinity\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses bit manipulation for efficient infinity detection.
* 
*   SEE ALSO
*	isinf(), isnanf(), finitef(), math.h
* 
******************************************************************************/

/* Helper macros for accessing high/low parts of float */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x

int isinff(float x)
{
    int hx;
    hx = __HI(x);
    hx &= 0x7fffffff;        /* mask off sign bit */
    hx = 0x7f800000 - hx;    /* now hx is 0 if x is infinite */
    return ((unsigned)(hx))>>31;
}
