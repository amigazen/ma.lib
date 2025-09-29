/*
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 *  Function:    ctan
 *  Synopsis:    Complex tangent
 *  Arguments:   z - complex number
 *  Returns:     double_complex - tangent of z
 *  Description: ctan(z) = csin(z) / ccos(z)
 */

#include "include/internal/complex_internal.h"

complex_t ctan(complex_t z)
{
    /* Use SAS/C C++ complex class for implementation */
    /* tan(z) = sin(z) / cos(z) */
    complex cpp_z(z.re, z.im);
    complex cpp_sin = sin(cpp_z);
    complex cpp_cos = cos(cpp_z);
    complex cpp_result = cpp_sin / cpp_cos;
    
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    
    return result;
}
