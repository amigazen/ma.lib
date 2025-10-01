/*
 * llrintl.c - Round to nearest long long integer (long double)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"
#include "include/internal/longlong.h"

/****** ma.lib/llrintl *******************************************************
* 
*   NAME	
* 	llrintl -- Round long double to nearest long long integer. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = llrintl(long double x);
*	  D0		   D0
*	long_long_t llrintl(long double x);
*
*   FUNCTION
*	Round a long double value to the nearest long long integer. This rounds to the
*	nearest integer using the current rounding mode. This implementation
*	uses the double precision llrint() function.
* 
*   INPUTS
*	x - Long double value to round.
*	
*   RESULT
*	result - Rounded long_long_t integer. Returns LONG_LONG_MAX or LONG_LONG_MIN on overflow.
* 
*   EXAMPLE
*	long double x = 3.7L;
*	long_long_t result = llrintl(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision llrint() internally since SAS/C maps long double to double.
* 
*   SEE ALSO
*	llrint(), lrintl(), rintl(), longlong.h
* 
******************************************************************************/

long_long_t llrintl(long double x)
{
    return llrint((double)x);
}
