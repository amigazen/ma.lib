/*
 * llroundf.c - Round to nearest long long integer (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"
#include "include/internal/longlong.h"

/****** ma.lib/llroundf ******************************************************
* 
*   NAME	
* 	llroundf -- Round float to nearest long long integer. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = llroundf(float x);
*	  D0		   D0
*	long_long_t llroundf(float x);
*
*   FUNCTION
*	Round a float value to the nearest long long integer. This rounds to the
*	nearest integer, with halfway cases rounded away from zero.
*	This implementation uses the double precision llround() function.
* 
*   INPUTS
*	x - Float value to round.
*	
*   RESULT
*	result - Rounded long_long_t integer. Returns LONG_LONG_MAX or LONG_LONG_MIN on overflow.
* 
*   EXAMPLE
*	float x = 3.7f;
*	long_long_t result = llroundf(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision llround() internally for accuracy.
* 
*   SEE ALSO
*	llround(), lroundf(), roundf(), longlong.h
* 
******************************************************************************/

long_long_t llroundf(float x)
{
    return llround((double)x);
}
