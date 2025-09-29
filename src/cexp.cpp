/*
 * C99 complex number functions - C wrapper around SAS/C C++ complex class
 * 
 * This file provides C99-compliant complex number functions that wrap
 * SAS/C's existing C++ complex class implementation.
 * 
 * Copyright (c) 2025 amigazen project
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <complex.h>
#include <math.h>
#include "include/internal/complex_internal.h"

/*
 * cexp - complex exponential
 * 
 * Returns the complex exponential of z.
 * cexp(z) = e^z
 * 
 * This wraps SAS/C's C++ exp() function.
 */
complex_t cexp(complex_t z)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    
    // Use SAS/C's C++ exp() function
    complex cpp_result = exp(cpp_z);
    
    // Convert back to our struct
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    return result;
}
