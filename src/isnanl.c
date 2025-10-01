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
 * isnanl(x) returns 1 if x is nan, else 0
 * Note: SAS/C maps long double to double, so delegate to isnan()
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/isnanl ********************************************************
* 
*   NAME	
* 	isnanl -- Test if long double value is NaN. (V1.0)
*
*   SYNOPSIS
*	int result = isnanl(long double x);
*	  D0		   D0
*	int isnanl(long double x);
*
*   FUNCTION
*	Test if a long double value is NaN (Not a Number). This performs
*	IEEE 754 NaN detection for long double values on AmigaOS with SAS/C.
* 
*   INPUTS
*	x - Long double value to test.
*	
*   RESULT
*	result - Non-zero if x is NaN, zero otherwise.
* 
*   EXAMPLE
*	long double x = 0.0L / 0.0L;
*	if (isnanl(x)) {
*	    printf("x is NaN\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Delegates to isnan() since SAS/C maps long double to double.
* 
*   SEE ALSO
*	isnan(), isinf(), finitel(), math.h
* 
******************************************************************************/

int isnanl(long double x)
{
    /* SAS/C maps long double to double, so delegate to isnan() */
    return isnan((double)x);
}
