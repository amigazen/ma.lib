/*
 * scalblnl.c - Scale by long integer (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/scalblnl ******************************************************
* 
*   NAME	
* 	scalblnl -- Scale long double by 2^n (long int). (V1.0)
*
*   SYNOPSIS
*	long double result = scalblnl(long double x, long n);
*	  D0		   D0
*	long double scalblnl(long double x, long n);
*
*   FUNCTION
*	Scale a long double value by 2^n using exponent manipulation.
*	This is more efficient than multiplication for powers of 2.
*	This implementation uses the double precision scalbln() function.
* 
*   INPUTS
*	x - Long double value to scale.
*	n - Power of 2 to scale by (long int).
*	
*   RESULT
*	result - x * 2^n. Returns NaN if x is NaN, returns x if x is ±Infinity.
* 
*   EXAMPLE
*	long double x = 3.0L;
*	long double result = scalblnl(x, 2L);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision scalbln() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	scalbln(), scalbnl(), ldexpl(), math.h
* 
******************************************************************************/

long double scalblnl(long double x, long n)
{
    return (long double)scalbln((double)x, n);
}

