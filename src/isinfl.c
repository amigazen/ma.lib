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
 * isinfl(x) returns 1 if x is infinity, else 0
 * Note: SAS/C maps long double to double, so delegate to isinf()
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/isinfl ********************************************************
* 
*   NAME	
* 	isinfl -- Test if long double value is infinity. (V1.0)
*
*   SYNOPSIS
*	int result = isinfl(long double x);
*	  D0		   D0
*	int isinfl(long double x);
*
*   FUNCTION
*	Test if a long double value is infinity (positive or negative).
*	This performs IEEE 754 infinity detection for long double values
*	on AmigaOS with SAS/C.
* 
*   INPUTS
*	x - Long double value to test.
*	
*   RESULT
*	result - Non-zero if x is infinity, zero otherwise.
* 
*   EXAMPLE
*	long double x = 1.0L / 0.0L;
*	if (isinfl(x)) {
*	    printf("x is infinity\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Delegates to isinf() since SAS/C maps long double to double.
* 
*   SEE ALSO
*	isinf(), isnanl(), finitel(), math.h
* 
******************************************************************************/

int isinfl(long double x)
{
    /* SAS/C maps long double to double, so delegate to isinf() */
    return isinf((double)x);
}
