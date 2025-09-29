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
