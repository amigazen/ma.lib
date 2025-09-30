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

/****** ma.lib/cexp *****************************************************
* 
*   NAME	
* 	cexp -- Return complex exponential of z. (V1.0)
*
*   SYNOPSIS
*	complex_t result = cexp(complex_t z);
*	  D0		   D0
*	complex_t cexp(complex_t z);
*
*   FUNCTION
*	Compute the complex exponential of z. This is equivalent to e^z.
*	For z = a + bi, cexp(z) = e^a * (cos(b) + i*sin(b)).
*	This implementation wraps SAS/C's C++ complex class.
* 
*   INPUTS
*	z - Complex number structure with real and imaginary parts.
*	
*   RESULT
*	result - Complex exponential of z. Returns NaN+NaN*i if z is NaN,
*	        +Infinity+NaN*i if real part is +Infinity and imaginary
*	        part is finite, +0.0+0.0*i if real part is -Infinity.
* 
*   EXAMPLE
*	complex_t z = {0.0, M_PI};  
*	complex_t exp_z = cexp(z);  
*
*   NOTES
*	This function wraps SAS/C's C++ complex class for maximum
*	compatibility and performance.
* 
*   SEE ALSO
*	clog(), csin(), ccos(), complex.h
* 
******************************************************************************/

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
