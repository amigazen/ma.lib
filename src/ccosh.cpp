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

/****** ma.lib/ccosh **********************************************************
* 
*   NAME	
* 	ccosh -- Return complex hyperbolic cosine of z. (V1.0)
*
*   SYNOPSIS
*	complex_t result = ccosh(complex_t z);
*	  D0		   D0
*	complex_t ccosh(complex_t z);
*
*   FUNCTION
*	Compute the complex hyperbolic cosine of z. This returns cosh(z)
*	where z is a complex number. This implementation uses SAS/C's
*	C++ complex class for maximum accuracy.
* 
*   INPUTS
*	z - Complex number.
*	
*   RESULT
*	result - Complex hyperbolic cosine of z. Returns NaN if z is NaN.
* 
*   EXAMPLE
*	complex_t z = {1.0, 2.0};
*	complex_t result = ccosh(z);  
*
*   NOTES
*	This function is C89 compliant and provides IEEE 754 accuracy.
*	Uses SAS/C C++ complex class internally.
* 
*   SEE ALSO
*	csinh(), ctanh(), cacosh(), complex.h
* 
******************************************************************************/

complex_t ccosh(complex_t z)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    
    // Use SAS/C's C++ cosh() function
    complex cpp_result = cosh(cpp_z);
    
    // Convert back to our struct
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    return result;
}
