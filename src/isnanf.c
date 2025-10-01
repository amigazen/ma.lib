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
 * isnanf(x) returns 1 if x is nan, else 0; no branching!
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* Helper macros for accessing high/low parts of float */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x

/****** ma.lib/isnanf ********************************************************
* 
*   NAME	
* 	isnanf -- Test if float value is NaN. (V1.0)
*
*   SYNOPSIS
*	int result = isnanf(float x);
*	  D0		   D0
*	int isnanf(float x);
*
*   FUNCTION
*	Test if a float value is NaN (Not a Number). This performs
*	IEEE 754 NaN detection for float values on AmigaOS with SAS/C.
* 
*   INPUTS
*	x - Float value to test.
*	
*   RESULT
*	result - Non-zero if x is NaN, zero otherwise.
* 
*   EXAMPLE
*	float x = 0.0f / 0.0f;
*	if (isnanf(x)) {
*	    printf("x is NaN\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses bit manipulation for efficient NaN detection.
* 
*   SEE ALSO
*	isnan(), isinf(), finitef(), math.h
* 
******************************************************************************/

int isnanf(float x)
{
    int hx;
    hx = (__HI(x)&0x7fffffff);
    hx = 0x7f800000 - hx;
    return ((unsigned)(hx))>>31;
}
