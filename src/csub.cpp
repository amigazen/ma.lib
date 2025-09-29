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
#include "include/internal/complex_internal.h"

/*
 * csub - complex subtraction
 * 
 * Subtracts two complex numbers: result = a - b
 * 
 * This wraps SAS/C's C++ operator- function.
 */
complex_t csub(complex_t a, complex_t b)
{
    // Convert to SAS/C C++ complex class
    complex cpp_a(a.re, a.im);
    complex cpp_b(b.re, b.im);
    
    // Use SAS/C's C++ operator-
    complex cpp_result = cpp_a - cpp_b;
    
    // Convert back to our struct
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    return result;
}