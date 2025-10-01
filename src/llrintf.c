/*
 * llrintf.c - Round to nearest long long integer (float)
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <math.h>
#include "include/internal/m99_math.h"
#include "include/internal/longlong.h"

/****** ma.lib/llrintf *******************************************************
* 
*   NAME	
* 	llrintf -- Round float to nearest long long integer. (V1.0)
*
*   SYNOPSIS
*	long_long_t result = llrintf(float x);
*	  D0		   D0
*	long_long_t llrintf(float x);
*
*   FUNCTION
*	Round a float value to the nearest long long integer. This rounds to the
*	nearest integer using the current rounding mode. This implementation
*	uses the double precision llrint() function.
* 
*   INPUTS
*	x - Float value to round.
*	
*   RESULT
*	result - Rounded long_long_t integer. Returns LONG_LONG_MAX or LONG_LONG_MIN on overflow.
* 
*   EXAMPLE
*	float x = 3.7f;
*	long_long_t result = llrintf(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses double precision llrint() internally for accuracy.
* 
*   SEE ALSO
*	llrint(), lrintf(), rintf(), longlong.h
* 
******************************************************************************/

long_long_t llrintf(float x)
{
    return llrint((double)x);
}
