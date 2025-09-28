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
 * cpow - complex power
 * 
 * Returns z raised to the power of w.
 * cpow(z, w) = z^w
 * 
 * This wraps SAS/C's C++ pow() function.
 */
double_complex cpow(double_complex z, double_complex w)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    complex cpp_w(w.re, w.im);
    
    // Use SAS/C's C++ pow() function
    complex cpp_result = pow(cpp_z, cpp_w);
    
    // Convert back to our struct
    double_complex result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    return result;
}
