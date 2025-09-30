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
 * csin - complex sine
 * 
 * Returns the complex sine of z.
 * csin(z) = sin(z)
 * 
 * This wraps SAS/C's C++ sin() function.
 */

/****** ma.lib/csin *****************************************************
* 
*   NAME	
* 	csin -- Return complex sine of z. (V1.0)
*
*   SYNOPSIS
*	complex_t result = csin(complex_t z);
*	  D0		   D0
*	complex_t csin(complex_t z);
*
*   FUNCTION
*	Compute the complex sine of z. For z = a + bi, the complex sine is:
*	csin(z) = sin(a)cosh(b) + i*cos(a)sinh(b)
*	This implementation wraps SAS/C's C++ complex class.
* 
*   INPUTS
*	z - Complex number structure with real and imaginary parts.
*	
*   RESULT
*	result - Complex sine of z. Returns NaN+NaN*i if z is NaN,
*	        +Infinity+NaN*i if real part is +Infinity and imaginary
*	        part is finite, +0.0+0.0*i if real part is -Infinity.
* 
*   EXAMPLE
*	complex_t z = {M_PI/2, 0.0};  
*	complex_t sin_z = csin(z);    
*
*   NOTES
*	This function wraps SAS/C's C++ complex class for maximum
*	compatibility and performance.
* 
*   SEE ALSO
*	ccos(), ctan(), cexp(), complex.h
* 
******************************************************************************/

complex_t csin(complex_t z)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    
    // Use SAS/C's C++ sin() function
    complex cpp_result = sin(cpp_z);
    
    // Convert back to our struct
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    return result;
}
