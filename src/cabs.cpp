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
 * cabs - complex absolute value (modulus)
 * 
 * Returns the absolute value (modulus) of a complex number.
 * cabs(z) = sqrt(creal(z)^2 + cimag(z)^2)
 * 
 * This wraps SAS/C's C++ abs() function.
 */
double cabs(double_complex z)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    
    // Use SAS/C's C++ abs() function
    return abs(cpp_z);
}