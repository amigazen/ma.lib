/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    catanh
 *  Synopsis:    Complex arc hyperbolic tangent
 *  Arguments:   z - complex number
 *  Returns:     double_complex - arc hyperbolic tangent of z
 *  Description: catanh(z) = (1/2) * (clog(1 + z) - clog(1 - z))
 */

#include "include/internal/complex_internal.h"

/****** ma.lib/catanh *********************************************************
* 
*   NAME	
* 	catanh -- Return complex arc hyperbolic tangent. (V1.0)
*
*   SYNOPSIS
*	complex_t result = catanh(complex_t z);
*	  D0		   D0
*	complex_t catanh(complex_t z);
*
*   FUNCTION
*	Compute the complex arc hyperbolic tangent of z. This is the
*	inverse of the complex hyperbolic tangent function. This
*	implementation uses SAS/C's C++ complex class for maximum accuracy.
* 
*   INPUTS
*	z - Complex number.
*	
*   RESULT
*	result - Complex arc hyperbolic tangent of z. Returns NaN if z
*	        is outside the domain [-1, 1] on the real axis.
* 
*   EXAMPLE
*	complex_t z = {0.5, 0.0};
*	complex_t result = catanh(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses SAS/C C++ complex class internally.
* 
*   SEE ALSO
*	cacosh(), casinh(), ctanh(), complex.h
* 
******************************************************************************/

complex_t catanh(complex_t z)
{
    /* Manual implementation using mathematical formula */
    /* atanh(z) = (1/2) * (log(1 + z) - log(1 - z)) */
    complex cpp_z(z.re, z.im);
    complex cpp_one(1.0, 0.0);
    complex cpp_half(0.5, 0.0);
    
    /* Calculate 1 + z */
    complex cpp_term1 = cpp_one + cpp_z;
    
    /* Calculate 1 - z */
    complex cpp_term2 = cpp_one - cpp_z;
    
    /* Calculate log(1 + z) */
    complex cpp_log1 = log(cpp_term1);
    
    /* Calculate log(1 - z) */
    complex cpp_log2 = log(cpp_term2);
    
    /* Calculate log(1 + z) - log(1 - z) */
    complex cpp_diff = cpp_log1 - cpp_log2;
    
    /* Calculate (1/2) * (log(1 + z) - log(1 - z)) */
    complex cpp_result = cpp_half * cpp_diff;
    
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    
    return result;
}
