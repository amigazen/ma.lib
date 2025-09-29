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
