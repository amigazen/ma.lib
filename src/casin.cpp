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
