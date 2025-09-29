/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    catan
 *  Synopsis:    Complex arc tangent
 *  Arguments:   z - complex number
 *  Returns:     double_complex - arc tangent of z
 *  Description: catan(z) = (i/2) * (clog(1 - i*z) - clog(1 + i*z))
 */

#include "include/internal/complex_internal.h"

complex_t catan(complex_t z)
{
    /* Manual implementation using mathematical formula */
    /* atan(z) = (i/2) * (log(1 - i*z) - log(1 + i*z)) */
    complex cpp_z(z.re, z.im);
    complex cpp_i(0.0, 1.0);
    complex cpp_one(1.0, 0.0);
    complex cpp_half_i(0.0, 0.5);
    
    /* Calculate 1 - i*z */
    complex cpp_term1 = cpp_one - cpp_i * cpp_z;
    
    /* Calculate 1 + i*z */
    complex cpp_term2 = cpp_one + cpp_i * cpp_z;
    
    /* Calculate log(1 - i*z) */
    complex cpp_log1 = log(cpp_term1);
    
    /* Calculate log(1 + i*z) */
    complex cpp_log2 = log(cpp_term2);
    
    /* Calculate log(1 - i*z) - log(1 + i*z) */
    complex cpp_diff = cpp_log1 - cpp_log2;
    
    /* Calculate (i/2) * (log(1 - i*z) - log(1 + i*z)) */
    complex cpp_result = cpp_half_i * cpp_diff;
    
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    
    return result;
}
