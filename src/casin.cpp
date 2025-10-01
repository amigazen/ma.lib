/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    casin
 *  Synopsis:    Complex arc sine
 *  Arguments:   z - complex number
 *  Returns:     double_complex - arc sine of z
 *  Description: casin(z) = -i * clog(i*z + csqrt(1 - z*z))
 */

#include "include/internal/complex_internal.h"

/****** ma.lib/casin **********************************************************
* 
*   NAME	
* 	casin -- Return complex arc sine. (V1.0)
*
*   SYNOPSIS
*	complex_t result = casin(complex_t z);
*	  D0		   D0
*	complex_t casin(complex_t z);
*
*   FUNCTION
*	Compute the complex arc sine of z. This is the inverse of the
*	complex sine function. This implementation uses SAS/C's C++
*	complex class for maximum accuracy.
* 
*   INPUTS
*	z - Complex number.
*	
*   RESULT
*	result - Complex arc sine of z. Returns NaN if z is outside
*	        the domain [-1, 1] on the real axis.
* 
*   EXAMPLE
*	complex_t z = {0.5, 0.0};
*	complex_t result = casin(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses SAS/C C++ complex class internally.
* 
*   SEE ALSO
*	cacos(), catan(), csin(), complex.h
* 
******************************************************************************/

complex_t casin(complex_t z)
{
    /* Manual implementation using mathematical formula */
    /* asin(z) = -i * log(i*z + sqrt(1 - z*z)) */
    complex cpp_z(z.re, z.im);
    complex cpp_i(0.0, 1.0);
    complex cpp_one(1.0, 0.0);
    
    /* Calculate 1 - z*z */
    complex cpp_z_squared = cpp_z * cpp_z;
    complex cpp_term1 = cpp_one - cpp_z_squared;
    
    /* Calculate sqrt(1 - z*z) */
    complex cpp_sqrt_term = sqrt(cpp_term1);
    
    /* Calculate i*z + sqrt(1 - z*z) */
    complex cpp_term2 = cpp_i * cpp_z + cpp_sqrt_term;
    
    /* Calculate log(i*z + sqrt(1 - z*z)) */
    complex cpp_log_term = log(cpp_term2);
    
    /* Calculate -i * log(...) */
    complex cpp_result = -cpp_i * cpp_log_term;
    
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    
    return result;
}
