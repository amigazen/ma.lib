/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_copysign.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * copysignf(float x, float y)
 * copysignf(x,y) returns a value with the magnitude of x and
 * with the sign bit of y.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/copysignf *****************************************************
* 
*   NAME	
* 	copysignf -- Copy sign bit from float to another. (V1.0)
*
*   SYNOPSIS
*	float result = copysignf(float x, float y);
*	  D0		   D0
*	float copysignf(float x, float y);
*
*   FUNCTION
*	Copy the sign bit from y to x, returning a value with the
*	magnitude of x and the sign of y. This implementation uses
*	high-precision algorithms from fdlibm.
* 
*   INPUTS
*	x - Float value to copy magnitude from.
*	y - Float value to copy sign from.
*	
*   RESULT
*	result - Value with magnitude of x and sign of y.
* 
*   EXAMPLE
*	float x = -3.0f;
*	float y = 2.0f;
*	float result = copysignf(x, y);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses direct bit manipulation for optimal performance.
* 
*   SEE ALSO
*	copysign(), copysignl(), fabsf(), math.h
* 
******************************************************************************/

/* Helper macros for accessing high/low parts of float */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x

float copysignf(float x, float y)
{
    __HI(x) = (__HI(x)&0x7fffffff)|(__HI(y)&0x80000000);
    return x;
}
