/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Based on fdlibm/w_gamma.c and e_gamma.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * 
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * 
 * double tgamma(double x)
 * Return the Gamma function of x.
 * 
 * Method: call gamma_r and return exp(gamma_r)
 */

#include <math.h>
#include "include/internal/m99_math.h"

extern int signgam;

static double __ieee754_gamma_r(double x, int *signgamp)
{
    return lgamma_r(x, signgamp);
}

/****** ma.lib/tgamma ***************************************************
* 
*   NAME	
* 	tgamma -- Return true gamma function of x. (V1.0)
*
*   SYNOPSIS
*	double result = tgamma(double x);
*	  D0		   D0
*	double tgamma(double x);
*
*   FUNCTION
*	Compute the true gamma function of x. The gamma function is a
*	generalization of the factorial function to real and complex numbers.
*	For positive integers n, tgamma(n) = (n-1)!
* 
*   INPUTS
*	x - Input value. Must be positive for valid result.
*	
*   RESULT
*	result - Gamma function of x. Returns +Infinity if x is 0 or negative
*	        integer, NaN if x is NaN, +Infinity if x is +Infinity.
* 
*   EXAMPLE
*	double x = 5.0;
*	double gamma = tgamma(x);  
*
*   NOTES
*	This function is POSIX.1 compliant and provides IEEE 754 accuracy.
*	Uses high-precision algorithms from fdlibm.
* 
*   SEE ALSO
*	lgamma(), gamma(), lgamma_r(), math.h
* 
******************************************************************************/

double tgamma(double x)
{
    double y;
    y = __ieee754_gamma_r(x,&signgam);
    if(!finite(y)&&finite(x)) {
        if(floor(x)==x&&x<=0.0) {
            /* gamma pole */
            return y;
        } else {
            /* gamma overflow */
            return y;
        }
    } else {
        return exp(y);
    }
}
