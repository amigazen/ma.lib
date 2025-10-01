/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    ctanh
 *  Synopsis:    Complex hyperbolic tangent
 *  Arguments:   z - complex number
 *  Returns:     double_complex - hyperbolic tangent of z
 *  Description: ctanh(z) = csinh(z) / ccosh(z)
 */

#include "include/internal/complex_internal.h"

/****** ma.lib/ctanh **********************************************************
* 
*   NAME	
* 	ctanh -- Return complex hyperbolic tangent of z. (V1.0)
*
*   SYNOPSIS
*	complex_t result = ctanh(complex_t z);
*	  D0		   D0
*	complex_t ctanh(complex_t z);
*
*   FUNCTION
*	Compute the complex hyperbolic tangent of z. This returns tanh(z)
*	where z is a complex number. This implementation uses SAS/C's
*	C++ complex class for maximum accuracy.
* 
*   INPUTS
*	z - Complex number.
*	
*   RESULT
*	result - Complex hyperbolic tangent of z. Returns NaN if z is NaN.
* 
*   EXAMPLE
*	complex_t z = {1.0, 2.0};
*	complex_t result = ctanh(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses SAS/C C++ complex class internally.
* 
*   SEE ALSO
*	csinh(), ccosh(), catanh(), complex.h
* 
******************************************************************************/

complex_t ctanh(complex_t z)
{
    /* Use SAS/C C++ complex class for implementation */
    /* tanh(z) = sinh(z) / cosh(z) */
    complex cpp_z(z.re, z.im);
    complex cpp_sinh = sinh(cpp_z);
    complex cpp_cosh = cosh(cpp_z);
    complex cpp_result = cpp_sinh / cpp_cosh;
    
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    
    return result;
}
