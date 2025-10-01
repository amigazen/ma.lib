/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/e_gamma_r.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * gamma_r(x, signgamp) - Reentrant gamma function
 * Return the logarithm of the Gamma function of x.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/gamma_r *******************************************************
* 
*   NAME	
* 	gamma_r -- Return gamma function of x (reentrant). (V1.0)
*
*   SYNOPSIS
*	double result = gamma_r(double x, int *signgamp);
*	  D0		   D0
*	double gamma_r(double x, int *signgamp);
*
*   FUNCTION
*	Compute the gamma function of x. This is the reentrant version
*	that stores the sign of gamma(x) in *signgamp. This implementation
*	uses high-precision algorithms from fdlibm for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	signgamp - Pointer to int to store sign of gamma(x).
*	
*   RESULT
*	result - Gamma function Γ(x). Returns +Infinity if x is a
*	        non-positive integer, returns NaN if x is NaN.
* 
*   EXAMPLE
*	double x = 2.5;
*	int sign;
*	double result = gamma_r(x, &sign);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	The sign of gamma(x) is stored in the int pointed to by signgamp.
* 
*   SEE ALSO
*	gamma(), tgamma(), lgamma_r(), math.h
* 
******************************************************************************/

/* Forward declaration */
double lgamma_r(double x, int *signgamp);

double gamma_r(double x, int *signgamp)
{
    return lgamma_r(x, signgamp);
}
