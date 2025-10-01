/*
 * scalblnf.c - Scale by long integer (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/scalblnf ******************************************************
* 
*   NAME	
* 	scalblnf -- Scale float by 2^n (long int). (V1.0)
*
*   SYNOPSIS
*	float result = scalblnf(float x, long n);
*	  D0		   D0
*	float scalblnf(float x, long n);
*
*   FUNCTION
*	Scale a float value by 2^n using exponent manipulation.
*	This is more efficient than multiplication for powers of 2.
*	This implementation uses the double precision scalbln() function.
* 
*   INPUTS
*	x - Float value to scale.
*	n - Power of 2 to scale by (long int).
*	
*   RESULT
*	result - x * 2^n. Returns NaN if x is NaN, returns x if x is ±Infinity.
* 
*   EXAMPLE
*	float x = 3.0f;
*	float result = scalblnf(x, 2L);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision scalbln() internally for accuracy.
* 
*   SEE ALSO
*	scalbln(), scalbnf(), ldexpf(), math.h
* 
******************************************************************************/

float scalblnf(float x, long n)
{
    return (float)scalbln((double)x, n);
}

