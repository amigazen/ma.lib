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
 * finitel(x) returns 1 if x is finite, else 0
 * Note: SAS/C maps long double to double, so delegate to finite()
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/finitel *******************************************************
* 
*   NAME	
* 	finitel -- Test if long double value is finite. (V1.0)
*
*   SYNOPSIS
*	int result = finitel(long double x);
*	  D0		   D0
*	int finitel(long double x);
*
*   FUNCTION
*	Test if a long double value is finite (not infinity or NaN). This performs
*	IEEE 754 finite detection for long double values on AmigaOS with SAS/C.
* 
*   INPUTS
*	x - Long double value to test.
*	
*   RESULT
*	result - Non-zero if x is finite, zero otherwise.
* 
*   EXAMPLE
*	long double x = 3.14L;
*	if (finitel(x)) {
*	    printf("x is finite\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Delegates to finite() since SAS/C maps long double to double.
* 
*   SEE ALSO
*	finite(), isinf(), isnan(), math.h
* 
******************************************************************************/

int finitel(long double x)
{
    /* SAS/C maps long double to double, so delegate to finite() */
    return finite((double)x);
}
