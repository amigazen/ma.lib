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

/****** ma.lib/cpow *****************************************************
* 
*   NAME	
* 	cpow -- Return z raised to the power of w. (V1.0)
*
*   SYNOPSIS
*	complex_t result = cpow(complex_t z, complex_t w);
*	  D0		   D0
*	complex_t cpow(complex_t z, complex_t w);
*
*   FUNCTION
*	Compute z raised to the power of w. This is equivalent to z^w.
*	For complex numbers, this is defined as exp(w * log(z)).
*	This implementation wraps SAS/C's C++ complex class.
* 
*   INPUTS
*	z - Base complex number.
*	w - Exponent complex number.
*	
*   RESULT
*	result - z^w. Returns NaN+NaN*i if z is 0 and w is 0, returns
*	        +Infinity+NaN*i if z is 0 and real part of w is negative,
*	        returns +0.0+0.0*i if z is 0 and real part of w is positive.
* 
*   EXAMPLE
*	complex_t z = {2.0, 0.0}, w = {2.0, 0.0}; 
*	complex_t pow_z = cpow(z, w);  
*
*   NOTES
*	This function wraps SAS/C's C++ complex class for maximum
*	compatibility and performance.
* 
*   SEE ALSO
*	cpow(), cexp(), clog(), complex.h
* 
******************************************************************************/

complex_t cpow(complex_t z, complex_t w)
{
    // Convert to SAS/C C++ complex class
    complex cpp_z(z.re, z.im);
    complex cpp_w(w.re, w.im);
    
    // Use SAS/C's C++ pow() function
    complex cpp_result = pow(cpp_z, cpp_w);
    
    // Convert back to our struct
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    return result;
}
