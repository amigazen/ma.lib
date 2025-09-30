/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/e_lgamma.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * lgamma(x) - Log gamma function
 * Return the logarithm of the Gamma function of x.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/* External signgam variable */
extern int signgam;

/* Forward declaration */
double lgamma_r(double x, int *signgamp);

/****** ma.lib/lgamma ***************************************************
* 
*   NAME	
* 	lgamma -- Return logarithm of gamma function. (V1.0)
*
*   SYNOPSIS
*	double result = lgamma(double x);
*	  D0		   D0
*	double lgamma(double x);
*
*   FUNCTION
*	Compute the natural logarithm of the absolute value of the gamma
*	function of x. The gamma function is a generalization of the
*	factorial function to real and complex numbers.
* 
*   INPUTS
*	x - Input value. Must be positive for valid result.
*	
*   RESULT
*	result - Log gamma of x. Returns +Infinity if x is 0 or negative
*	        integer, NaN if x is NaN, +Infinity if x is +Infinity.
*	        The sign of the gamma function is stored in the global
*	        variable signgam.
* 
*   EXAMPLE
*	double x = 5.0;
*	double log_gamma = lgamma(x); 
*
*   NOTES
*	This function is POSIX.1 compliant and provides IEEE 754 accuracy.
*	Uses high-precision algorithms from fdlibm. The sign of the result
*	is stored in the global variable signgam.
* 
*   SEE ALSO
*	tgamma(), gamma(), lgamma_r(), signgam, math.h
* 
******************************************************************************/

double lgamma(double x)
{
    return lgamma_r(x, &signgam);
}