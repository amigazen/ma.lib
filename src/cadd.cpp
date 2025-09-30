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
 * cadd - complex addition
 * 
 * Adds two complex numbers: result = a + b
 * 
 * This wraps SAS/C's C++ operator+ function.
 */

/****** ma.lib/cadd *****************************************************
* 
*   NAME	
* 	cadd -- Add two complex numbers. (V1.0)
*
*   SYNOPSIS
*	complex_t result = cadd(complex_t a, complex_t b);
*	  D0		   D0
*	complex_t cadd(complex_t a, complex_t b);
*
*   FUNCTION
*	Add two complex numbers. For a = a1 + a2*i and b = b1 + b2*i,
*	the result is (a1 + b1) + (a2 + b2)*i.
*	This implementation wraps SAS/C's C++ complex class.
* 
*   INPUTS
*	a - First complex number.
*	b - Second complex number.
*	
*   RESULT
*	result - Sum of a and b. Returns NaN+NaN*i if either argument is NaN,
*	        returns +Infinity+NaN*i if either argument is +Infinity.
* 
*   EXAMPLE
*	complex_t a = {1.0, 2.0}, b = {3.0, 4.0};  
*	complex_t sum = cadd(a, b);  
*
*   NOTES
*	This function wraps SAS/C's C++ complex class for maximum
*	compatibility and performance.
* 
*   SEE ALSO
*	csub(), cmul(), cdiv(), complex.h
* 
******************************************************************************/

complex_t cadd(complex_t a, complex_t b)
{
    // Convert to SAS/C C++ complex class
    complex cpp_a(a.re, a.im);
    complex cpp_b(b.re, b.im);
    
    // Use SAS/C's C++ operator+
    complex cpp_result = cpp_a + cpp_b;
    
    // Convert back to our struct
    complex_t result;
    result.re = real(cpp_result);
    result.im = imag(cpp_result);
    return result;
}