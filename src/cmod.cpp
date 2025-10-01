/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    cmod
 *  Synopsis:    Calculate the modulus (absolute value) of a complex number
 *  Arguments:   z - complex number
 *  Returns:     double - the modulus
 *  Description: cmod(z) = sqrt(real(z)^2 + imag(z)^2)
 *               This is equivalent to cabs(z) but provided for completeness
 */

#include <math.h>
#include "include/internal/complex_internal.h"

/****** ma.lib/cmod **********************************************************
* 
*   NAME	
* 	cmod -- Return modulus (absolute value) of complex number. (V1.0)
*
*   SYNOPSIS
*	double result = cmod(complex_t z);
*	  D0		   D0
*	double cmod(complex_t z);
*
*   FUNCTION
*	Calculate the modulus (absolute value) of a complex number. This
*	returns the distance from the origin to the point representing
*	the complex number. This is equivalent to cabs(z).
* 
*   INPUTS
*	z - Complex number.
*	
*   RESULT
*	result - Modulus of z. Returns sqrt(z.re^2 + z.im^2).
* 
*   EXAMPLE
*	complex_t z = {3.0, 4.0};
*	double mod = cmod(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to cabs(z) but provided for completeness.
* 
*   SEE ALSO
*	cabs(), carg(), complex.h
* 
******************************************************************************/

double cmod(complex_t z)
{
    double mod;

    /*
     *  Calculate the modulus using the C99 complex number structure
     */
    mod = sqrt(z.re * z.re + z.im * z.im);

    /*
     *  Return the answer
     */
    return mod;
}

/*========================================================================*
                                   END
 *========================================================================*/
