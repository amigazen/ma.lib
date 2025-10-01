/*
 * llroundl.c - Round to nearest long long integer (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"
#include "include/internal/longlong.h"

/****** ma.lib/llroundl ******************************************************
* 
*   NAME	
* 	llroundl -- Round long double to nearest long long integer. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = llroundl(long double x);
*	  D0		   D0
*	long_long_t llroundl(long double x);
*
*   FUNCTION
*	Round a long double value to the nearest long long integer. This rounds to the
*	nearest integer, with halfway cases rounded away from zero.
*	This implementation uses the double precision llround() function.
* 
*   INPUTS
*	x - Long double value to round.
*	
*   RESULT
*	result - Rounded long_long_t integer. Returns LONG_LONG_MAX or LONG_LONG_MIN on overflow.
* 
*   EXAMPLE
*	long double x = 3.7L;
*	long_long_t result = llroundl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision llround() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	llround(), lroundl(), roundl(), longlong.h
* 
******************************************************************************/

long_long_t llroundl(long double x)
{
    return llround((double)x);
}
