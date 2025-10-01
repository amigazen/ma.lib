/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * double nan(const char *tagp)
 * float nanf(const char *tagp)
 * long double nanl(const char *tagp)
 * IEEE 754 nan functions
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/nan ************************************************************
* 
*   NAME	
* 	nan -- Return NaN (Not a Number). (V1.0)
*
*   SYNOPSIS
*	double result = nan(const char *tagp);
*	  D0		   A0
*	double nan(const char *tagp);
*
*   FUNCTION
*	Generate a NaN (Not a Number) value. The tagp parameter is ignored
*	in this implementation but is provided for C99 compatibility.
*	This function is useful for testing NaN handling in code.
* 
*   INPUTS
*	tagp - Tag string (ignored in this implementation).
*	
*   RESULT
*	result - NaN value. Always returns the same NaN representation.
* 
*   EXAMPLE
*	double nan_val = nan("test");
*	if (isnan(nan_val)) {
*	    printf("Generated NaN\n");
*	}
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	The tagp parameter is ignored for compatibility.
* 
*   SEE ALSO
*	isnan(), isinf(), math.h
* 
******************************************************************************/

double nan(const char *tagp)
{
    (void)tagp; /* unused parameter */
    return NAN;
}

float nanf(const char *tagp)
{
    (void)tagp; /* unused parameter */
    return (float)NAN;
}

long double nanl(const char *tagp)
{
    (void)tagp; /* unused parameter */
    return (long double)NAN;
}
