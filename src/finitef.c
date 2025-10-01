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
 * finitef(x) returns 1 if x is finite, else 0; no branching!
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/finitef *******************************************************
* 
*   NAME	
* 	finitef -- Test if float value is finite. (V1.0)
*
*   SYNOPSIS
*	int result = finitef(float x);
*	  D0		   D0
*	int finitef(float x);
*
*   FUNCTION
*	Test if a float value is finite (not infinity or NaN). This performs
*	IEEE 754 finite detection for float values on AmigaOS with SAS/C.
* 
*   INPUTS
*	x - Float value to test.
*	
*   RESULT
*	result - Non-zero if x is finite, zero otherwise.
* 
*   EXAMPLE
*	float x = 3.14f;
*	if (finitef(x)) {
*	    printf("x is finite\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses bit manipulation for efficient finite detection.
* 
*   SEE ALSO
*	finite(), isinf(), isnan(), math.h
* 
******************************************************************************/

/* Helper macros for accessing high/low parts of float */
/* SAS/C uses big-endian, so high word is first */
#define __HI(x) *(int*)&x

int finitef(float x)
{
    int hx; 
    hx = __HI(x);
    return (unsigned)((hx&0x7fffffff)-0x7f800000)>>31;
}
