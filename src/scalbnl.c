/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/s_scalbn.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * scalbnl (long double x, int n)
 * scalbnl(x,n) returns x* 2**n  computed by  exponent  
 * manipulation rather than by actually performing an 
 * exponentiation or a multiplication.
 * Note: SAS/C maps long double to double, so delegate to scalbn()
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/scalbnl *******************************************************
* 
*   NAME	
* 	scalbnl -- Scale long double by 2^n. (V1.0)
*
*   SYNOPSIS
*	long double result = scalbnl(long double x, int n);
*	  D0		   D0
*	long double scalbnl(long double x, int n);
*
*   FUNCTION
*	Scale a long double value by 2^n using exponent manipulation.
*	This is more efficient than multiplication for powers of 2.
*	This implementation uses the double precision scalbn() function.
* 
*   INPUTS
*	x - Long double value to scale.
*	n - Power of 2 to scale by.
*	
*   RESULT
*	result - x * 2^n. Returns NaN if x is NaN, returns x if x is ±Infinity.
* 
*   EXAMPLE
*	long double x = 3.0L;
*	long double result = scalbnl(x, 2);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision scalbn() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	scalbn(), scalblnl(), ldexp(), math.h
* 
******************************************************************************/

long double scalbnl(long double x, int n)
{
    /* SAS/C maps long double to double, so delegate to scalbn() */
    return (long double)scalbn((double)x, n);
}


