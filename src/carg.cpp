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
 * carg - complex argument (phase angle)
 * 
 * Returns the argument (phase angle) of a complex number.
 * carg(z) = atan2(cimag(z), creal(z))
 * 
 * This wraps SAS/C's C++ arg() function.
 */
double carg(double_complex z)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    
    // Use SAS/C's C++ arg() function
    return arg(cpp_z);
}