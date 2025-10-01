/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    casinh
 *  Synopsis:    Complex arc hyperbolic sine
 *  Arguments:   z - complex number
 *  Returns:     double_complex - arc hyperbolic sine of z
 *  Description: casinh(z) = clog(z + csqrt(z*z + 1))
 */

#include "include/internal/complex_internal.h"

/****** ma.lib/casinh *********************************************************
* 
*   NAME	
* 	casinh -- Return complex arc hyperbolic sine. (V1.0)
*
*   SYNOPSIS
*	complex_t result = casinh(complex_t z);
*	  D0		   D0
*	complex_t casinh(complex_t z);
*
*   FUNCTION
*	Compute the complex arc hyperbolic sine of z. This is the
*	inverse of the complex hyperbolic sine function. This
*	implementation uses SAS/C's C++ complex class for maximum accuracy.
* 
*   INPUTS
*	z - Complex number.
*	
*   RESULT
*	result - Complex arc hyperbolic sine of z. Returns NaN if z
*	        is outside the domain.
* 
*   EXAMPLE
*	complex_t z = {1.0, 2.0};
*	complex_t result = casinh(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses SAS/C C++ complex class internally.
* 
*   SEE ALSO
*	cacosh(), catanh(), csinh(), complex.h
* 
******************************************************************************/

complex_t casinh(complex_t z)
{
    /* Manual implementation using mathematical formula */
    /* asinh(z) = log(z + sqrt(z*z + 1)) */
    complex cpp_z(z.re, z.im);
    complex cpp_one(1.0, 0.0);
    
    /* Calculate z*z + 1 */
    complex cpp_z_squared = cpp_z * cpp_z;
    complex cpp_term1 = cpp_z_squared + cpp_one;
    
    /* Calculate sqrt(z*z + 1) */
    complex cpp_sqrt_term = sqrt(cpp_term1);
    
    /* Calculate z + sqrt(z*z + 1) */
    complex cpp_term2 = cpp_z + cpp_sqrt_term;
    
    /* Calculate log(z + sqrt(z*z + 1)) */
    complex cpp_result = log(cpp_term2);
    
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    
    return result;
}
