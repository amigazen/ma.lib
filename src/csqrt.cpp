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
 * csqrt - complex square root
 * 
 * Returns the complex square root of z.
 * csqrt(z) = sqrt(z)
 * 
 * This wraps SAS/C's C++ sqrt() function.
 */

/****** ma.lib/csqrt ****************************************************
* 
*   NAME	
* 	csqrt -- Return complex square root of z. (V1.0)
*
*   SYNOPSIS
*	complex_t result = csqrt(complex_t z);
*	  D0		   D0
*	complex_t csqrt(complex_t z);
*
*   FUNCTION
*	Compute the complex square root of z. For z = a + bi, the complex
*	square root is: csqrt(z) = sqrt((|z| + a)/2) + i*sign(b)*sqrt((|z| - a)/2)
*	This implementation wraps SAS/C's C++ complex class.
* 
*   INPUTS
*	z - Complex number structure with real and imaginary parts.
*	
*   RESULT
*	result - Complex square root of z. Returns +0.0+0.0*i if z is +0.0,
*	        +Infinity+NaN*i if z is +Infinity, NaN+NaN*i if z is NaN.
* 
*   EXAMPLE
*	complex_t z = {4.0, 0.0}; 
*	complex_t sqrt_z = csqrt(z);  
*
*   NOTES
*	This function wraps SAS/C's C++ complex class for maximum
*	compatibility and performance.
* 
*   SEE ALSO
*	sqrt(), cpow(), cabs(), complex.h
* 
******************************************************************************/

complex_t csqrt(complex_t z)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    
    // Use SAS/C's C++ sqrt() function
    complex cpp_result = sqrt(cpp_z);
    
    // Convert back to our struct
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    return result;
}
