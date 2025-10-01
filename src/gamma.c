/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/e_gamma.c and w_gamma.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * gamma(x) - Gamma function
 * Return the logarithm of the Gamma function of x.
 */

#include <math.h>
#include "include/internal/m99_math.h"

/****** ma.lib/gamma *********************************************************
* 
*   NAME	
* 	gamma -- Return gamma function of x. (V1.0)
*
*   SYNOPSIS
*	double result = gamma(double x);
*	  D0		   D0
*	double gamma(double x);
*
*   FUNCTION
*	Compute the gamma function of x. This is equivalent to tgamma(x)
*	but uses the global signgam variable. This implementation uses
*	high-precision algorithms from fdlibm for maximum accuracy.
* 
*   INPUTS
*	x - Input value. Range is [-∞, +∞].
*	
*   RESULT
*	result - Gamma function Γ(x). Returns +Infinity if x is a
*	        non-positive integer, returns NaN if x is NaN.
* 
*   EXAMPLE
*	double x = 2.5;
*	double result = gamma(x);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses global signgam variable for sign information.
* 
*   SEE ALSO
*	tgamma(), lgamma(), gamma_r(), math.h
* 
******************************************************************************/

/* External signgam variable */
extern int signgam;

/* Forward declaration */
double gamma_r(double x, int *signgamp);

double gamma(double x)
{
    return gamma_r(x, &signgam);
}
