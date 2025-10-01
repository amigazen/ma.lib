/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    cneg
 *  Synopsis:    Negate a complex number
 *  Arguments:   z - complex number to negate
 *  Returns:     double_complex - negated complex number
 *  Description: cneg(z) = -z = (-real(z), -imag(z))
 */

#include "include/internal/complex_internal.h"

/****** ma.lib/cneg **********************************************************
* 
*   NAME	
* 	cneg -- Return negation of complex number. (V1.0)
*
*   SYNOPSIS
*	complex_t result = cneg(complex_t z);
*	  D0		   D0
*	complex_t cneg(complex_t z);
*
*   FUNCTION
*	Negate a complex number. This returns -z by negating both the
*	real and imaginary parts of the complex number.
* 
*   INPUTS
*	z - Complex number to negate.
*	
*   RESULT
*	result - Negated complex number. Returns (-z.re, -z.im).
* 
*   EXAMPLE
*	complex_t z = {3.0, 4.0};
*	complex_t result = cneg(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	This is equivalent to cscale(z, -1.0).
* 
*   SEE ALSO
*	cscale(), cadd(), complex.h
* 
******************************************************************************/

complex_t cneg(complex_t z)
{
    complex_t result;

    /*
     *  Negate both real and imaginary parts
     */
    result.re = -z.re;
    result.im = -z.im;

    /*
     *  Return the result
     */
    return result;
}