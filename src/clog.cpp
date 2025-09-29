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
 * clog - complex natural logarithm
 * 
 * Returns the complex natural logarithm of z.
 * clog(z) = ln(z)
 * 
 * This wraps SAS/C's C++ log() function.
 */
/* Internal implementation function to avoid clog conflict */
complex_t clog_c99(complex_t z)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    
    // Use SAS/C's C++ log() function
    complex cpp_result = log(cpp_z);
    
    // Convert back to our struct
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    return result;
}

/* Provide clog as a macro to avoid iostream conflict */
#define clog clog_c99
