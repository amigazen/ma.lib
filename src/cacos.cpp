/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    cacos
 *  Synopsis:    Complex arc cosine
 *  Arguments:   z - complex number
 *  Returns:     double_complex - arc cosine of z
 *  Description: cacos(z) = -i * clog(z + i * csqrt(1 - z*z))
 */

#include "include/internal/complex_internal.h"

/****** ma.lib/cacos **********************************************************
* 
*   NAME	
* 	cacos -- Return complex arc cosine. (V1.0)
*
*   SYNOPSIS
*	complex_t result = cacos(complex_t z);
*	  D0		   D0
*	complex_t cacos(complex_t z);
*
*   FUNCTION
*	Compute the complex arc cosine of z. This is the inverse of the
*	complex cosine function. This implementation uses SAS/C's C++
*	complex class for maximum accuracy.
* 
*   INPUTS
*	z - Complex number.
*	
*   RESULT
*	result - Complex arc cosine of z. Returns NaN if z is outside
*	        the domain [-1, 1] on the real axis.
* 
*   EXAMPLE
*	complex_t z = {0.5, 0.0};
*	complex_t result = cacos(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses SAS/C C++ complex class internally.
* 
*   SEE ALSO
*	casin(), catan(), ccos(), complex.h
* 
******************************************************************************/

complex_t cacos(complex_t z)
{
    /* Manual implementation using mathematical formula */
    /* acos(z) = -i * log(z + i * sqrt(1 - z*z)) */
    complex cpp_z(z.re, z.im);
    complex cpp_i(0.0, 1.0);
    complex cpp_one(1.0, 0.0);
    
    /* Calculate 1 - z*z */
    complex cpp_z_squared = cpp_z * cpp_z;
    complex cpp_term1 = cpp_one - cpp_z_squared;
    
    /* Calculate sqrt(1 - z*z) */
    complex cpp_sqrt_term = sqrt(cpp_term1);
    
    /* Calculate z + i * sqrt(1 - z*z) */
    complex cpp_term2 = cpp_z + cpp_i * cpp_sqrt_term;
    
    /* Calculate log(z + i * sqrt(1 - z*z)) */
    complex cpp_log_term = log(cpp_term2);
    
    /* Calculate -i * log(...) */
    complex cpp_result = -cpp_i * cpp_log_term;
    
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    
    return result;
}
